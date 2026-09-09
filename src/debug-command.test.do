import { Assert } from "std/assert"
import { DebugLaunch, debugLaunchError, debugTargetError, planDebuggerRun } from "./debug-command"
import { formatJsonValue, parseJsonValue } from "std/json"

export function testDebugLaunchContract(): none {
  launch := DebugLaunch { executable: "/tmp/工具 app", source: "/tmp/main.do", directory: "/tmp", symbols: "/tmp/app.dSYM", arguments: ["a b", "\"quoted\""] }
  Assert.equal(debugLaunchError(launch), "")
  decoded := try! DebugLaunch.fromJsonValue(try! parseJsonValue(formatJsonValue(launch.toJsonObject())))
  Assert.equal(decoded.executable, launch.executable)
  Assert.equal(decoded.arguments[1], "\"quoted\"")
  plan := planDebuggerRun("/tmp/Doof Debugger.app", "/tmp/a b.json", "/tmp")
  Assert.equal(plan.arguments.length, 1)
  Assert.equal(plan.arguments[0], "/tmp/a b.json")
  Assert.equal(plan.command, "/tmp/Doof Debugger.app/Contents/MacOS/DoofDebugger")
}

export function testDebugLaunchDiagnostics(): none {
  Assert.stringContains(debugTargetError("linux", ""), "macOS")
  Assert.stringContains(debugTargetError("macos", "wasm"), "native console")
  Assert.stringContains(debugTargetError("macos", "ios-app"), "native console")
  Assert.equal(debugTargetError("macos", "macos-app"), "")
  launch := DebugLaunch { executable: "relative", source: "/s", directory: "/d", symbols: "/s" }
  Assert.stringContains(debugLaunchError(launch), "absolute")
  unsupported := DebugLaunch { version: 2, executable: "/e", source: "/s", directory: "/d", symbols: "/s" }
  Assert.stringContains(debugLaunchError(unsupported), "version")
}
