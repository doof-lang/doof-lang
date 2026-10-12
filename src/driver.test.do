import { Assert } from "std/assert"
import { nativeBuildOutputName, phaseTimingsEnabled } from "./driver"

export function testPhaseTimingsOnlyReportFrontendCommands(): none {
  Assert.isTrue(phaseTimingsEnabled("emit", "1"))
  Assert.isTrue(phaseTimingsEnabled("check", "1"))
  Assert.isFalse(phaseTimingsEnabled("build", "1"))
  Assert.isFalse(phaseTimingsEnabled("emit", ""))
}

export function testNativeOutputNameFlattensPackagePathsAndAddsWindowsSuffix(): none {
  Assert.equal(nativeBuildOutputName("std/json", "macos"), "std-json")
  Assert.equal(nativeBuildOutputName("tool", "windows"), "tool.exe")
  Assert.equal(nativeBuildOutputName("tool.EXE", "windows"), "tool.EXE")
}

import { env, run, ExecOptions } from "std/os"
import { readText, remove, exists } from "std/fs"
import { DebugLaunch } from "./debug-command"
import { parseJsonValue } from "std/json"

// Enabled by tools/repository/verify.do with the freshly built compiler.
export function testDebugDriverExternalLaunchIntegration(): none {
  compiler := env("DOOF_DEBUG_DRIVER_COMPILER") else { return }
  fixture := env("DOOF_DEBUG_DRIVER_FIXTURE") else { return }
  descriptor := env("DOOF_DEBUG_DRIVER_DESCRIPTOR") else { return }
  output := env("DOOF_DEBUG_DRIVER_OUTPUT") else { return }
  for target of ["native", "macos-app"] {
    arguments := ["debug", fixture, "-o", output + "/" + target, "--launch-json", descriptor]
    if target == "macos-app" { arguments.push("--target"); arguments.push("macos-app") }
    arguments.push("--"); arguments.push("a b"); arguments.push("工具")
    result := run(compiler, arguments, ExecOptions { inheritOutput: true })!
    Assert.equal(result.exitCode, 0)
    launch := DebugLaunch.fromSerialValue(parseJsonValue(readText(descriptor)!)!)!
    Assert.isTrue(exists(launch.executable))
    Assert.isTrue(exists(launch.symbols))
    Assert.equal(launch.arguments.length, 2)
    Assert.equal(launch.arguments[0], "a b")
    Assert.equal(launch.arguments[1], "工具")
    Assert.stringContains(launch.executable, "/debug/")
    if target == "macos-app" { Assert.stringContains(launch.executable, ".app/Contents/MacOS/") }
    remove(descriptor)!
  }
}
