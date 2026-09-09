import { exists, File } from "std/fs"
import { formatJsonValue } from "std/json"
import { parseInt } from "std/parse"
import { architecture, platform } from "std/os"
import { executablePath, homeDirectory, dirname } from "std/path"
import { capture, command, copyInputs, copyTree, developmentVersion, erase, files, installArtifacts, makeDirectory, path, read, require, resolveSeed, setting, stamp, stdlibDirectory, write } from "./common"
import { captureEnvironment } from "./snapshot"

export class BuildInputs {
  root: string
  work: string
  source: string
  stdlib: string
  seed: string
  version: string
}
export class BuildResult {
  artifacts: string
  generation: int
}
export function prepare(root: string, work: string, seed: string, version: string): Result<BuildInputs, string> {
  if !exists(path(work, "staged-layout-v2")) {
    for name of ["compiler", "stdlib-bundle-tool", "final-bundle-tool"] { try erase(path(work, name)) }
  }
  source := path(work, "source"); stdlib := path(work, "stdlib")
  try stamp(root, source, version)
  try liveStdlib := stdlibDirectory(root)
  try copyInputs(liveStdlib, stdlib)
  try write(path(work, "staged-layout-v2"), "")
  return Success(BuildInputs { root, work, source, stdlib, seed, version })
}
export function sourceArtifact(name: string): bool {
  for suffix of [".c", ".cc", ".cpp", ".h", ".hh", ".hpp", ".m", ".mm"] { if name.endsWith(suffix) { return true } }
  return false
}
export function generatedGraph(root: string): Result<Map<string, string>, string> {
  try discovered := files(root)
  result: Map<string, string> := {}
  for name of discovered {
    if !sourceArtifact(name) || name.contains("/.doof-") || name.startsWith(".doof-") || name.contains("/.reckon/") { continue }
    try content := read(path(root, name))
    result.set(name, content)
  }
  try require(result.size > 0, "Generated graph contains no source files: " + root)
  return Success(result)
}
export function graphsMatch(left: Map<string, string>, right: Map<string, string>): bool {
  if left.size != right.size { return false }
  for name, content of left { value := right.get(name) else { return false }; if value != content { return false } }
  return true
}
export function buildDebugger(source: string, stdlib: string, compiler: string, artifacts: string, environment: Map<string, string> = {}): Result<none, string> {
  output := path(source, "build/debugger-app")
  try command(compiler, ["build", path(source, "tools/debugger"), "-o", output], environment)
  try erase(path(artifacts, "Doof Debugger.app"))
  return copyTree(path(output, "DoofDebugger.app"), path(artifacts, "Doof Debugger.app"))
}
export function buildToolchain(inputs: BuildInputs, fixed: bool, record: bool = false): Result<BuildResult, string> {
  try require(platform() == "darwin" && architecture() == "arm64", "Toolchain builds currently require macOS arm64")
  maximum := parseInt(setting("DOOF_MAX_GENERATIONS", "6")) else { return Failure("DOOF_MAX_GENERATIONS must be an integer at least 2") }
  try require(maximum >= 2, "DOOF_MAX_GENERATIONS must be at least 2")
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: inputs.stdlib, DOOF_RUNTIME_HEADER: path(inputs.source, "runtime/doof_runtime.h") }
  bundle := path(inputs.work, "doof-stdlib.tar")
  try erase(bundle)
  try command(inputs.seed, ["run", path(inputs.source, "tools/stdlib-bundle.do"), "-o", path(inputs.work, "stdlib-bundle-tool"), "--", inputs.stdlib, bundle, "ios-device,ios-simulator,macos,wasm"], environment)
  let compiler = inputs.seed
  let generation = 0
  if fixed {
    let previous: Map<string, string> = {}
    let matched = false
    for number of 1..maximum {
      generation = number
      current := path(inputs.work, "generation-" + string(number))
      try erase(current)
      try command(compiler, ["build", inputs.source, "-o", current], environment)
      compiler = path(current, "doof")
      try version := capture(compiler, ["--version"])
      try require(version == "doof " + inputs.version, "Generation has unexpected version")
      try graph := generatedGraph(current)
      if number > 1 && graphsMatch(previous, graph) {
        println("Fixed point matched generations " + string(number - 1) + "/" + string(number) + " across " + string(graph.size) + " generated sources")
        matched = true; break
      }
      previous = graph
    }
    try require(matched, "No generated-source fixed point after " + string(maximum) + " generations")
  }
  artifacts := path(inputs.work, "artifacts")
  try erase(artifacts); try makeDirectory(artifacts)
  if record {
    try tool := executablePath()
    try captureEnvironment(inputs.work, tool, environment)
    try erase(path(inputs.work, "compiler"))
    try erase(path(inputs.source, "build/debugger-app"))
  }
  try command(compiler, ["package", inputs.source, "-o", path(inputs.work, "compiler"), "--distdir", artifacts], environment)
  bundleEnv: Map<string, string> := { DOOF_STDLIB_ROOT: inputs.stdlib, DOOF_RUNTIME_HEADER: path(inputs.source, "runtime/doof_runtime.h"), CXX: "c++" }
  try command(path(artifacts, "doof"), ["run", path(inputs.source, "tools/stdlib-bundle.do"), "-o", path(inputs.work, "final-bundle-tool"), "--", inputs.stdlib, path(artifacts, "doof-stdlib.tar"), "ios-device,ios-simulator,macos,wasm"], bundleEnv)
  try buildDebugger(inputs.source, inputs.stdlib, path(artifacts, "doof"), artifacts, environment)
  try version := capture(path(artifacts, "doof"), ["--version"])
  try require(version == "doof " + inputs.version, "Packaged compiler version mismatch")
  return Success(BuildResult { artifacts, generation })
}
export function developmentBuild(root: string, fixed: bool): Result<none, string> {
  try makeDirectory(path(root, "build"))
  lock := File { path: path(root, "build/toolchain.lock"), mode: .ReadWrite, create: true, lock: .Exclusive, waitForLock: false } else { return Failure("Another toolchain operation is running or the build lock is inaccessible") }
  try seed := resolveSeed(root, if fixed then "DOOF_SEED_COMPILER" else "DOOF_DEV_COMPILER")
  try version := developmentVersion(root)
  try home := homeDirectory()
  installation := setting("DOOF_HOME", path(home, ".doof"))
  try require(installation.startsWith("/") && installation != "/", "DOOF_HOME must be an absolute non-root directory")
  try inputs := prepare(root, path(root, if fixed then "build/toolchain-verify" else "build/dev-install"), seed, version)
  try built := buildToolchain(inputs, fixed, fixed)
  // Preserve prepared release assets while updating the developer test toolchain.
  try copyTree(built.artifacts, path(root, "dist"))
  if !fixed {
    try installArtifacts(root, built.artifacts, installation, "dev")
    println("Installed development compiler: " + path(installation, "bin/doof") + " (" + version + ")")
    println("Add to PATH: export PATH=" + quotePath(path(installation, "bin")) + ":$PATH")
  } else { println("Verified compiler: " + path(root, "dist/doof") + " (" + version + ")") }
  _ := lock.close() else { return Failure("Could not close toolchain lock") }
  return Success()
}
function quotePath(value: string): string => "\"" + value + "\""
