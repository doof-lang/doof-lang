// Acceptance gates use native commands directly; fixtures remain independent.
import { exists, File } from "std/fs"
import { parseJsonObject } from "std/json"
import { command, capture, copyInputs, erase, execute, installArtifacts, makeDirectory, path, read, require, setting, text, write } from "./common"
import { commandOutputChecks, interactiveCheck, projectLockChecks, cacheChecks } from "./process-checks"

export function runtimeChecks(root: string): Result<none, string> {
  work := path(root, "build/runtime-tests")
  try makeDirectory(work)
  binary := path(work, "scheduler")
  try command("c++", ["-std=c++17", "-O0", "-pthread", path(root, "runtime/doof_runtime.test.cpp"), "-o", binary])
  for mode of ["limit", "nested", "first-completed", "actor", "actor-waits", "failures", "application", "release", "priority", "configuration", "collections", "nulls", "string-builder", "string-padding"] { try command(binary, [mode]) }
  return Success()
}
export function debuggerChecks(root: string, compiler: string, stdlib: string): Result<none, string> {
  work := path(root, "build/debugger-integration")
  app := path(work, "Capture.app")
  executable := path(app, "Contents/MacOS/DoofDebugger")
  try write(executable, "#!/bin/sh\nset -eu\ncp \"$1\" \"$DOOF_DEBUG_TEST_LAUNCH\"\n")
  try command("chmod", ["+x", executable])
  environment: Map<string, string> := { DOOF_DEBUGGER_APP: app, DOOF_DEBUG_TEST_LAUNCH: path(work, "launch.json"), DOOF_DEBUG_FIXTURE_ENV: "debug-environment", DOOF_STDLIB_ROOT: stdlib }
  try command(compiler, ["debug", path(root, "tests/debugger-fixture"), "-o", path(work, "target"), "--", "argument space", "工具"], environment)
  try command(compiler, ["test", path(root, "tools/debugger"), "--filter", "testRealLldbSession"], environment)
  environment.set("DOOF_DEBUG_TEST_LAUNCH", path(work, "panic-launch.json"))
  environment.set("DOOF_DEBUG_PANIC_TEST_LAUNCH", path(work, "panic-launch.json"))
  try command(compiler, ["debug", path(root, "tests/debugger-panic-fixture"), "-o", path(work, "panic-target")], environment)
  try command(compiler, ["test", path(root, "tools/debugger"), "--filter", "testRealLldbPanic"], environment)
  environment.set("DOOF_DEBUG_DRIVER_COMPILER", compiler)
  environment.set("DOOF_DEBUG_DRIVER_FIXTURE", path(root, "tests/debugger-fixture"))
  environment.set("DOOF_DEBUG_DRIVER_DESCRIPTOR", path(work, "external 工具 launch.json"))
  environment.set("DOOF_DEBUG_DRIVER_OUTPUT", path(work, "external-target"))
  environment.set("DOOF_DEBUGGER_APP", path(work, "does-not-exist.app"))
  try command(compiler, ["test", path(root, "src"), "--filter", "testDebugDriverExternalLaunchIntegration"], environment)
  return Success()
}
export function testRepository(root: string, compiler: string, stdlib: string): Result<none, string> {
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib, DOOF_REPOSITORY_TEST_ROOT: root, DOOF_REPOSITORY_TEST_COMPILER: compiler }
  // All compiler test invocations are serial: they share native output roots.
  try command(compiler, ["test", path(root, "src")], environment, root)
  try command(compiler, ["test", path(root, "tools/repository")], environment, root)
  try runtimeChecks(root)
  try command(compiler, ["test", path(root, "tools/debugger")], environment, root)
  try debuggerChecks(root, compiler, stdlib)
  return Success()
}
function compilerOffline(compiler: string, arguments: string[], environment: Map<string, string>): Result<none, string> {
  args := ["-u", "DOOF_STDLIB_ROOT", "-u", "DOOF_RUNTIME_HEADER", compiler]
  for argument of arguments { args.push(argument) }
  return command("env", args, environment)
}
export function releaseVerification(root: string, compiler: string, stdlib: string): Result<none, string> {
  releaseRoot := path(root, "build/release-gate")
  fixtures := path(releaseRoot, "fixtures"); verify := path(releaseRoot, "verify")
  try erase(releaseRoot); try makeDirectory(verify); try makeDirectory(path(releaseRoot, "coverage"))
  try copyInputs(path(root, "tests/release-fixtures"), fixtures)
  try command("chmod", ["+x", path(fixtures, "offline-bin/git")])
  offline: Map<string, string> := { PATH: path(fixtures, "offline-bin") + ":" + setting("PATH") }
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib }
  try index := capture("tar", ["-xOf", path(root, "dist/doof-stdlib.tar"), "bundle-index.json"])
  try parsed := parseJsonObject(index)
  schema := parsed.get("schemaVersion")! as int else { return Failure("Missing stdlib schema version") }
  try require(schema == 4, "Unexpected stdlib bundle schema")
  try unknown := execute("env", ["-u", "DOOF_STDLIB_ROOT", compiler, "check", path(fixtures, "unknown-stdlib")], offline)
  try require(unknown.exitCode != 0 && text(unknown.stdout).contains("Unknown standard package std/not-a-package"), "Missing actionable unknown stdlib diagnostic")
  try command(compiler, ["test", path(root, "src"), "--coverage", "--coverage-output", path(releaseRoot, "coverage/compiler.json")], environment, root)
  try command(compiler, ["check", path(fixtures, "runtime")], environment)
  try command(compiler, ["emit", path(fixtures, "runtime"), "-o", path(verify, "emit")], environment)
  for name of ["native-interop", "stdlib", "bundled-webp", "bundled-http", "pkg-config", "module-initialization", "platform-framework"] {
    output := path(verify, name)
    arguments := ["build", path(fixtures, name), "-o", output]
    if ["stdlib", "bundled-webp", "bundled-http"].contains(name) { try compilerOffline(compiler, arguments, offline) }
    else if name == "pkg-config" {
      try command(compiler, arguments, { DOOF_STDLIB_ROOT: stdlib, PKG_CONFIG_PATH: path(fixtures, "pkg-config/pkgconfig") })
    } else { try command(compiler, arguments, environment) }
    try command(path(output, "doof-release-" + name), [], {}, releaseRoot)
    try require(!exists(path(output, "provenance.json")), "Unexpected build provenance output")
  }
  testFixture := path(fixtures, "test-runner")
  try command(compiler, ["test", testFixture, "--list"], environment)
  try command(compiler, ["test", testFixture, "--coverage", "--coverage-output", path(releaseRoot, "coverage/fixture.json")], environment)
  for name of ["runtime", "local-dependency"] {
    try command(compiler, ["package", path(fixtures, name), "-o", path(verify, name + "-package")], environment)
    try command(path(fixtures, name + "/dist/doof-release-" + name), [], {}, releaseRoot)
  }
  try require(exists(path(fixtures, "runtime/dist/release-resource.txt")), "Missing packaged resource")
  try interactiveCheck(compiler, path(fixtures, "interactive-run"), stdlib)
  try commandOutputChecks(compiler, fixtures, path(verify, "command-output"), stdlib)
  try command(compiler, ["build", path(fixtures, "manifestless-script/script.do"), "-o", path(verify, "manifestless-script")], environment)
  try command(path(verify, "manifestless-script/doof"), [], {}, releaseRoot)
  wasm := path(fixtures, "manifestless-wasm/library.do")
  try command(compiler, ["emit", wasm, "--target", "wasm", "-o", path(verify, "manifestless-wasm-emit")], environment)
  try wasmSource := read(path(verify, "manifestless-wasm-emit/doof_wasm.cpp"))
  try require(wasmSource.contains("doof_export_add"), "Missing Wasm export")
  // This is a release gate: missing toolchains must fail, never silently skip.
  try command(compiler, ["build", wasm, "--target", "wasm", "-o", path(verify, "manifestless-wasm")], environment)
  try require(exists(path(verify, "manifestless-wasm/doof.wasm")), "Missing Wasm binary")
  try command(compiler, ["test", path(fixtures, "wasm-test-runner"), "-o", path(verify, "wasm-test-runner")], environment)
  try command(compiler, ["build", path(fixtures, "ios-app"), "-o", path(verify, "ios-app"), "--ios-destination", "simulator"], environment)
  for name of ["DoofCompilerIOS", "Info.plist"] { try require(exists(path(verify, "ios-app/DoofCompilerIOS.app/" + name)), "Missing iOS artifact " + name) }
  try debuggerChecks(root, compiler, stdlib)
  println("Release acceptance passed: " + releaseRoot)
  return Success()
}
