import { Assert } from "std/assert"
import { structuredTestResult } from "./driver"
import { compilerCacheIdentity } from "./driver"
import { compilerVersion, compilerVersionStamped } from "./version"

export function testDriverUsesStampedCompilerIdentity(): none {
  Assert.equal(compilerCacheIdentity(), if compilerVersionStamped then compilerVersion else "")
}

export function testEditorDriverReportsExactIdentityAndExitStatus(): none {
  value := structuredTestResult("example.test.do::testOne", 7, "failure\n")
  Assert.equal(try! value.get("id"), "example.test.do::testOne")
  Assert.equal(try! value.get("exitCode"), 7)
  Assert.equal(try! value.get("output"), "failure\n")
}

import { frontendEmissionCacheSupported } from "./driver"
export function testBatchSelectionCacheTargetBoundaries(): none {
  Assert.isTrue(frontendEmissionCacheSupported("native"))
  Assert.isFalse(frontendEmissionCacheSupported("wasm"))
  Assert.isFalse(frontendEmissionCacheSupported("ios-app"))
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
    result := try! run(compiler, arguments, ExecOptions { inheritOutput: true })
    Assert.equal(result.exitCode, 0)
    launch := try! DebugLaunch.fromJsonValue(try! parseJsonValue(try! readText(descriptor)))
    Assert.isTrue(exists(launch.executable))
    Assert.isTrue(exists(launch.symbols))
    Assert.equal(launch.arguments.length, 2)
    Assert.equal(launch.arguments[0], "a b")
    Assert.equal(launch.arguments[1], "工具")
    Assert.stringContains(launch.executable, "/debug/")
    if target == "macos-app" { Assert.stringContains(launch.executable, ".app/Contents/MacOS/") }
    try! remove(descriptor)
  }
}
