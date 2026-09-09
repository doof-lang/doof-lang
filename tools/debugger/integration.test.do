import { isStringArray, collectionChildren, variableLabel } from "./collection-presentation"
import { sourceFrames, frameLabel } from "./frame-presentation"
import { sourceIdentifiers } from "./source-presentation"
import { visibleVariables, isGlobalScope, isSystemGlobal } from "./variable-presentation"
import { Assert } from "std/assert"
import { DebugLaunch } from "../../src/debug-command"
import { DebugSession } from "./session"
import { DebugRow } from "./model"
import { textField, intField } from "./protocol"
import { env } from "std/os"
import { readText } from "std/fs"
import { parseJsonValue } from "std/json"
import { Duration, Thread } from "std/time"

function waitForStop(session: DebugSession): none {
  for i of 0..<1500 {
    session.tick()
    if session.state == "Stopped" && session.scopes.length > 0 { return }
    if session.state == "Failed" || session.state == "Exited" { break }
    Thread.sleep(Duration.ofMillis(10L))
  }
  println(session.status + "\n" + session.output)
  Assert.equal(session.state, "Stopped")
  Assert.equal(session.scopes.length > 0, true)
}

export function testRealLldbSession(): none {
  path := env("DOOF_DEBUG_TEST_LAUNCH") else { return }
  launch := try! DebugLaunch.fromJsonValue(try! parseJsonValue(try! readText(path)))
  session := DebugSession { launch }
  session.toggleBreakpoint(launch.source, 5)
  session.start()
  waitForStop(session)
  // stopOnEntry may stop in the generated C main before entering Doof main.
  if session.sourcePath != launch.source || session.sourceLine != 5 {
    session.control("continue")
    waitForStop(session)
  }
  Assert.equal(session.sourcePath, launch.source)
  Assert.equal(session.sourceLine, 5)
  visibleFrames := sourceFrames(session.frames)
  Assert.equal(visibleFrames.length > 0, true)
  Assert.equal(frameLabel(visibleFrames[0]), "main · 5")
  Assert.equal((try! session.breakpoints.get(launch.source))[0].verified, true)
  for row of session.scopes { session.expandVariable(row) }
  for i of 0..<100 {
    session.tick()
    Thread.sleep(Duration.ofMillis(10L))
  }
  let found = false
  let foundArguments = false
  let foundGlobal = false
  for scope of session.scopes {
    identifiers := sourceIdentifiers(try! readText(launch.source))
    for variable of visibleVariables(scope.children, identifiers, false, isGlobalScope(scope)) {
      Assert.equal(textField(variable.data, "name").startsWith("_iterable_"), false)
      if isGlobalScope(scope) {
        Assert.equal(isSystemGlobal(textField(variable.data, "name")), false)
        if textField(variable.data, "name").endsWith("::debuggerGlobal") {
          Assert.equal(textField(variable.data, "value"), "73")
          foundGlobal = true
        }
      }
      if textField(variable.data, "name") == "arguments" {
        Assert.equal(isStringArray(variable), true)
        session.expandVariable(variable)
        for i of 0..<500 {
          session.tick()
          if collectionChildren(variable, false).length == 2 { break }
          Thread.sleep(Duration.ofMillis(10L))
        }
        elements := collectionChildren(variable, false)
        Assert.equal(elements.length, 2)
        Assert.equal(textField(elements[0].data, "name"), "[0]")
        Assert.equal(textField(elements[0].data, "value"), "\"argument space\"")
        Assert.equal(textField(elements[1].data, "value"), "\"工具\"")
        Assert.stringContains(variableLabel(variable, false), "string[]")
        foundArguments = true
      }
      if textField(variable.data, "name") == "count" {
        Assert.equal(textField(variable.data, "value"), "41")
        found = true
      }
    }
  }
  Assert.equal(found, true)
  Assert.equal(foundArguments, true)
  Assert.equal(foundGlobal, true)
  session.control("next")
  waitForStop(session)
  Assert.equal(session.sourceLine > 5, true)
  session.control("continue")
  for i of 0..<1000 {
    session.tick()
    if session.state == "Exited" || session.state == "Failed" { break }
    Thread.sleep(Duration.ofMillis(10L))
  }
  Assert.equal(session.state, "Exited")
  Assert.equal(session.exitCode, 0)
  Assert.stringContains(session.output, "42")
  Assert.stringContains(session.output, "argument space")
  Assert.stringContains(session.output, "debug-environment")
  session.shutdown()
}
