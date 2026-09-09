import { Assert } from "std/assert"
import { DebugLaunch } from "../../src/debug-command"
import { DebugSession } from "./session"
import { frameName } from "./frame-presentation"
import { textField } from "./protocol"
import { env } from "std/os"
import { readText } from "std/fs"
import { parseJsonValue } from "std/json"
import { Duration, Thread } from "std/time"

function checkPanic(mode: string, functionName: string, line: int): none {
  path := env("DOOF_DEBUG_PANIC_TEST_LAUNCH") else { return }
  original := try! DebugLaunch.fromJsonValue(try! parseJsonValue(try! readText(path)))
  launch := DebugLaunch { executable: original.executable, directory: original.directory, symbols: original.symbols, source: original.source, arguments: [mode] }
  session := DebugSession { launch }
  session.start()
  Assert.equal(session.breakpoints.has(launch.source), false)
  // A user breakpoint on the same requested line must survive startup cleanup.
  if mode == "explicit" { session.toggleBreakpoint(launch.source, 1) }
  let found = false
  for i of 0..<2000 {
    session.tick()
    if session.state == "Failed" || session.state == "Exited" { break }
    if session.state == "Stopped" && session.scopes.length > 0 {
      if session.status == "Stopped: panic" { found = true; break }
      session.control("continue")
    }
    Thread.sleep(Duration.ofMillis(10L))
  }
  if !found { println(session.status + "\n" + session.output) }
  Assert.equal(found, true)
  for i of 0..<200 {
    session.tick()
    if session.panicMessage != "" { break }
    Thread.sleep(Duration.ofMillis(10L))
  }
  Assert.equal(session.breakpoints.has(launch.source), mode == "explicit")
  if mode == "explicit" {
    points := try! session.breakpoints.get(launch.source)
    Assert.equal(points.length, 1)
    Assert.equal(points[0].line, 1)
  }
  Assert.equal(session.isPanicStop(), true)
  expected := if mode == "bounds" then "Index out of bounds" else if mode == "caught" then "caught panic" else "fixture panic"
  Assert.stringContains(session.panicMessage, expected)
  Assert.equal(session.panicMessage.startsWith("0x"), false)
  Assert.equal(session.sourcePath, launch.source)
  Assert.equal(session.sourceLine, line)
  let foundCaller = false
  for frame of session.frames {
    if frameName(textField(frame.data, "name")) == functionName { foundCaller = true }
  }
  Assert.equal(foundCaller, true)
  if mode == "explicit" {
    let foundLocal = false
    for i of 0..<200 {
      session.tick()
      for scope of session.scopes {
        for variable of scope.children {
          if textField(variable.data, "name") == "local" && textField(variable.data, "value") == "73" { foundLocal = true }
        }
      }
      if foundLocal { break }
      Thread.sleep(Duration.ofMillis(10L))
    }
    Assert.equal(foundLocal, true)
  }
  if mode == "caught" {
    session.control("continue")
    for i of 0..<1000 {
      session.tick()
      if session.state == "Exited" || session.state == "Failed" { break }
      Thread.sleep(Duration.ofMillis(10L))
    }
    Assert.equal(session.state, "Exited")
    Assert.equal(session.exitCode, 0)
    Assert.equal(session.isPanicStop(), false)
    Assert.stringContains(session.output, "recovered from panic")
  }
  session.shutdown()
}

export function testRealLldbPanicStopsAtExplicitCall(): none { checkPanic("explicit", "explicitPanic", 3) }
export function testRealLldbPanicStopsAtRuntimeBoundsFailure(): none { checkPanic("bounds", "boundsPanic", 8) }
export function testRealLldbPanicCanContinueIntoCatchPanic(): none { checkPanic("caught", "caughtPanic", 12) }
