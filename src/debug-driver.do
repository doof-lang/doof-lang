// Filesystem/process boundary for launching the installed debugger application.
import { DebugLaunch, debugLaunchError, planDebuggerRun } from "./debug-command"
import { planProfileSymbols } from "./profile-command"
import { environmentValue, joinPath } from "./project"
import { exists, remove, writeText } from "std/fs"
import { formatJsonValue } from "std/json"
import { ExecOptions, run, pid } from "std/os"
import { resourcePath } from "std/path"
import { Instant } from "std/time"

export function launchDebugger(binary: string, source: string, directory: string, output: string, arguments: string[], launchJson: string = ""): int {
  let app = environmentValue("DOOF_DEBUGGER_APP")
  if launchJson == "" && app == "" {
    resolved := resourcePath("Doof Debugger.app") else {
      println("error: Doof Debugger.app is missing; reinstall the macOS Doof toolchain")
      return 1
    }
    app = resolved
  }
  if launchJson == "" && !exists(app + "/Contents/MacOS/DoofDebugger") {
    println("error: Doof Debugger.app is missing at " + app + "; run ./install.sh or reinstall Doof")
    return 1
  }
  symbols := binary + ".dSYM"
  plan := planProfileSymbols(binary, symbols, directory)
  built := run(plan.command, plan.arguments, ExecOptions { cwd: directory, inheritOutput: true }) else error {
    println("error: Could not generate debug symbols: " + error); return 1
  }
  if built.exitCode != 0 { return built.exitCode }
  launch := DebugLaunch { executable: binary, source, directory, symbols, arguments }
  descriptor := if launchJson != "" then launchJson else joinPath(output, "debug-session-" + string(pid()) + "-" + string(Instant.now().toEpochMillis()) + ".json")
  if writeDebugLaunch(launch, descriptor) != 0 { return 1 }
  // External DAP clients own this file and session; no application is required.
  if launchJson != "" { return 0 }
  invocation := planDebuggerRun(app, descriptor, directory)
  result := run(invocation.command, invocation.arguments, ExecOptions {
    cwd: directory, inheritOutput: true, withStdin: false,
  })
  _ := remove(descriptor) else { println("warning: Could not remove debugger launch descriptor " + descriptor) }
  case result {
    success: Success -> return success.value.exitCode,
    failure: Failure -> { println("error: Could not launch Doof Debugger: " + failure.error); return 1 },
  }
}

export function writeDebugLaunch(launch: DebugLaunch, descriptor: string): int {
  error := debugLaunchError(launch)
  if error != "" { println("error: " + error); return 1 }
  _ := writeText(descriptor, formatJsonValue(launch.toJsonObject())) else error {
    println("error: Could not write debugger launch: " + string(error)); return 1
  }
  return 0
}
