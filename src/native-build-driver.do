// Filesystem and process execution for planned native builds.
// Pure command construction remains in native-build.do; this module owns
// incremental state, dependency signatures, compiler workers, and linking.

import { ProjectEmission } from "./emitter-project"
import { NativeCompilePlan, NativeCompileTask, batchNativeCompileTasks, isMsvcCompiler, planNativeCompile } from "./native-build"
import {
  NativeBuildState, NativeInputSignature, NativeTaskState, findNativeTaskState,
  parseMakeDependencies, parseMsvcDependencies, parseNativeBuildState, renderNativeBuildState,
} from "./native-build-state"
import { PkgConfigCommandResult, applyPkgConfigResult } from "./pkg-config"
import { BlobReader } from "std/blob"
import { sha256Hex, sha256HexString } from "std/crypto"
import { exists, isDirectory, metadata, mkdir, readBlob, readDir, readText, remove, rename, writeText } from "std/fs"
import { ExecOptions, env, run } from "std/os"

readonly MAX_NATIVE_OUTPUT_LINES = 40
readonly MAX_NATIVE_OUTPUT_BYTES = 262144L

class NativeCommandResult {
  readonly exitCode: int
  readonly output: readonly byte[] = []
  readonly error: string = ""
  readonly truncated: bool
  readonly quietSourcePath: string = ""
}

class NativeCompilerBatchResult {
  readonly exitCode: int
  readonly outputs: readonly NativeCommandResult[]
}

class NativeCompilerIdentity {
  command: string
  signature: string
}

isolated function runBuildCommand(
  command: string,
  arguments: string[],
  quietSourcePath: string = "",
): NativeCommandResult {
  executed := run(command, arguments, ExecOptions {
    withStdin: false,
    mergeStderrIntoStdout: true,
    maxOutputBytes: MAX_NATIVE_OUTPUT_BYTES,
  }) else error {
    return NativeCommandResult { exitCode: -1, error, truncated: false }
  }
  return NativeCommandResult {
    exitCode: executed.exitCode,
    output: executed.stdout,
    truncated: executed.stdoutTruncated,
    quietSourcePath,
  }
}

/** Identifies the standalone source-name line emitted by cl.exe for every successful compile. */
export function isMsvcSourceEcho(line: string, sourcePath: string): bool {
  if sourcePath == "" { return false }
  normalizedLine := line.trim().replaceAll("\\", "/")
  normalizedSource := sourcePath.replaceAll("\\", "/")
  let slash = -1
  for index of 0..<normalizedSource.length { if normalizedSource[index] == '/' { slash = index } }
  sourceName := if slash < 0 then normalizedSource else normalizedSource.substring(slash + 1, normalizedSource.length)
  return normalizedLine == normalizedSource || normalizedLine == sourceName
}

function printBuildOutput(result: NativeCommandResult, remainingLines: int): int {
  let remaining = remainingLines
  output := if result.error != "" then result.error else BlobReader(result.output).readString(long(result.output.length))
  for line of output.split("\n") {
    if line == "" { continue }
    if isMsvcSourceEcho(line, result.quietSourcePath) { continue }
    if remaining <= 0 { return 0 }
    println(line)
    remaining -= 1
  }
  return remaining
}

class NativeCompilerWorker {
  readonly tasks: readonly NativeCompileTask[]

  compile(): NativeCompilerBatchResult {
    let outputs: NativeCommandResult[] = []
    for task of this.tasks {
      result := runBuildCommand(
        task.compiler,
        mutableArguments(task.arguments),
        if isMsvcCompiler(task.compiler) then task.sourcePath else "",
      )
      outputs.push(result)
      if result.exitCode != 0 {
        return NativeCompilerBatchResult { exitCode: result.exitCode, outputs: outputs.drainToReadonly() }
      }
    }
    return NativeCompilerBatchResult { exitCode: 0, outputs: outputs.drainToReadonly() }
  }
}

export function buildNativeProject(
  compilerOverride: string,
  outputDirectory: string,
  outputPath: string,
  project: ProjectEmission,
  release: bool,
  platform: string,
): int {
  for packageName of project.nativeBuild.pkgConfigPackages {
    for mode of ["cflags", "libs"] {
      pkgConfigResult := runBuildCommand("pkg-config", ["--" + mode, packageName])
      output := BlobReader(pkgConfigResult.output).readString(long(pkgConfigResult.output.length))
      applied := applyPkgConfigResult(project.nativeBuild, packageName, mode, PkgConfigCommandResult {
        exitCode: pkgConfigResult.exitCode,
        output,
        error: pkgConfigResult.error,
      })
      _ := applied else error { println("error: " + error); return 1 }
    }
  }

  wasm := outputPath.endsWith(".wasm")
  let compiler = compilerOverride
  if compiler == "" && wasm { compiler = "em++" }
  if compiler == "" {
    configured := envCompiler()
    if configured != "" { compiler = configured }
  }
  if compiler == "" { compiler = if platform == "windows" then "cl.exe" else "c++" }
  plan := planNativeCompile(compiler, outputDirectory, outputPath, project.modules, project.nativeBuild, release, platform, project.wasmExportNames, wasm)
  return executeNativePlan(outputDirectory, plan, project)
}

function envCompiler(): string {
  value := env("CXX") else { return "" }
  return value
}

function executeNativePlan(outputDirectory: string, plan: NativeCompilePlan, project: ProjectEmission): int {
  for supportFile of plan.supportFiles {
    ensureDirectory(parentDirectory(supportFile.outputPath))
    writeTextIfChanged(supportFile.outputPath, supportFile.content)
  }
  statePath := joinOutput(outputDirectory, ".doof-native-build-state.json")
  previousState := readBuildState(statePath)
  nextState := NativeBuildState {}
  let identities: NativeCompilerIdentity[] = []
  let remainingOutputLines = MAX_NATIVE_OUTPUT_LINES
  let truncationReported = false
  let pchChanged = false

  if plan.precompiledHeaderTask != none {
    pchTask := plan.precompiledHeaderTask!
    ensureDirectory(parentDirectory(pchTask.outputPath))
    pchFingerprint := taskFingerprint(pchTask, identities)
    pchPrevious := findNativeTaskState(previousState, pchTask.id)
    if !taskIsCurrent(pchPrevious, pchFingerprint, pchTask.auxiliaryOutputPaths) {
      pchChanged = true
      pchResult := runBuildCommand(pchTask.compiler, mutableArguments(pchTask.arguments))
      remainingOutputLines = printBuildOutput(pchResult, remainingOutputLines)
      if pchResult.truncated { println("... native compiler output capture truncated after " + string(MAX_NATIVE_OUTPUT_BYTES) + " bytes"); truncationReported = true }
      if pchResult.exitCode != 0 {
        println("error: native compiler failed to build the precompiled runtime header with code " + string(pchResult.exitCode))
        return pchResult.exitCode
      }
      nextState.tasks.push(captureTaskState(pchTask, pchFingerprint))
    } else { nextState.tasks.push(pchPrevious!) }
  }

  let dirtyTasks: NativeCompileTask[] = []
  let dirtyTaskIds: string[] = []
  let taskFingerprints: string[] = []
  for task of plan.compileTasks {
    fingerprint := taskFingerprint(task, identities)
    taskFingerprints.push(fingerprint)
    previous := findNativeTaskState(previousState, task.id)
    if (task.usesPrecompiledHeader && pchChanged) || !taskIsCurrent(previous, fingerprint) {
      dirtyTasks.push(task)
      dirtyTaskIds.push(task.id)
    }
  }

  let workers: Actor<NativeCompilerWorker>[] = []
  let promises: Promise<NativeCompilerBatchResult>[] = []
  for task of dirtyTasks { ensureDirectory(parentDirectory(task.outputPath)) }
  for batch of batchNativeCompileTasks(dirtyTasks) {
    worker := Actor<NativeCompilerWorker>(batch)
    workers.push(worker)
    promises.push(async worker.compile())
  }
  let compileExitCode = 0
  for index of 0..<promises.length {
    batchResult := promises[index].get() else error {
      ignoredWorker := retire workers[index]
      println("error: native compiler worker failed: " + error)
      return 1
    }
    retire workers[index]
    for commandResult of batchResult.outputs {
      remainingOutputLines = printBuildOutput(commandResult, remainingOutputLines)
      if commandResult.truncated && !truncationReported { println("... native compiler output capture truncated after " + string(MAX_NATIVE_OUTPUT_BYTES) + " bytes"); truncationReported = true }
    }
    if compileExitCode == 0 && batchResult.exitCode != 0 { compileExitCode = batchResult.exitCode }
  }
  if remainingOutputLines == 0 && !truncationReported { println("... native compiler output truncated after " + string(MAX_NATIVE_OUTPUT_LINES) + " lines") }
  if compileExitCode != 0 { println("error: native object compiler exited with code " + string(compileExitCode)); return compileExitCode }

  let objectPaths: string[] = []
  if plan.precompiledHeaderTask != none {
    for path of plan.precompiledHeaderTask!.auxiliaryOutputPaths { objectPaths.push(path) }
  }
  for index of 0..<plan.compileTasks.length {
    task := plan.compileTasks[index]
    objectPaths.push(task.outputPath)
    if contains(dirtyTaskIds, task.id) { nextState.tasks.push(captureTaskState(task, taskFingerprints[index])) }
    else { nextState.tasks.push(findNativeTaskState(previousState, task.id)!) }
  }

  linkId := "link:" + plan.outputPath
  computedLinkFingerprint := linkFingerprint(plan.linker, plan.linkArguments, plan.outputPath, identities)
  linkPrevious := findNativeTaskState(previousState, linkId)
  if dirtyTasks.length > 0 || !taskIsCurrent(linkPrevious, computedLinkFingerprint) {
    linkResult := runBuildCommand(plan.linker, plan.linkArguments)
    ignored := printBuildOutput(linkResult, remainingOutputLines)
    if linkResult.truncated && !truncationReported { println("... native linker output capture truncated after " + string(MAX_NATIVE_OUTPUT_BYTES) + " bytes") }
    if linkResult.exitCode != 0 { println("error: native linker exited with code " + string(linkResult.exitCode)); return linkResult.exitCode }
    nextState.tasks.push(captureLinkState(plan.outputPath, computedLinkFingerprint, objectPaths))
  } else { nextState.tasks.push(linkPrevious!) }

  collectManagedOutputs(nextState.managedOutputs, outputDirectory, plan, project)
  removeStaleOutputs(previousState.managedOutputs, nextState.managedOutputs, outputDirectory)
  writeBuildState(statePath, nextState)
  return 0
}

function compilerIdentity(command: string, identities: NativeCompilerIdentity[]): string {
  for identity of identities { if identity.command == command { return identity.signature } }
  result := runBuildCommand(command, if isMsvcCompiler(command) then ["/?"] else ["--version"])
  let description = command
  if result.exitCode == 0 { description = description + "\n" + BlobReader(result.output).readString(long(result.output.length)) }
  signature := sha256HexString(description)
  identities.push(NativeCompilerIdentity { command, signature })
  return signature
}

function taskFingerprint(task: NativeCompileTask, identities: NativeCompilerIdentity[]): string {
  let value = task.id + "\n" + compilerIdentity(task.compiler, identities)
  for argument of task.arguments { value = value + "\n" + argument }
  return sha256HexString(value)
}

function linkFingerprint(linker: string, arguments: string[], outputPath: string, identities: NativeCompilerIdentity[]): string {
  let value = "link:" + outputPath + "\n" + compilerIdentity(linker, identities)
  for argument of arguments { value = value + "\n" + argument }
  return sha256HexString(value)
}

function pathSignature(path: string, contentHash: bool): NativeInputSignature | none {
  if !exists(path) || isDirectory(path) { return none }
  info := metadata(path) else { return none }
  modifiedNanos := info.modifiedAt.toEpochNanos()
  signature := if contentHash then sha256Hex(try! readBlob(path)) else string(info.size) + ":" + string(modifiedNanos)
  return NativeInputSignature { path, signature, contentHash, size: info.size, modifiedNanos }
}

function currentInputSignature(previous: NativeInputSignature): NativeInputSignature | none {
  if !exists(previous.path) || isDirectory(previous.path) { return none }
  info := metadata(previous.path) else { return none }
  modifiedNanos := info.modifiedAt.toEpochNanos()
  if previous.size == info.size && previous.modifiedNanos == modifiedNanos {
    return NativeInputSignature {
      path: previous.path, signature: previous.signature, contentHash: previous.contentHash,
      size: info.size, modifiedNanos,
    }
  }
  return pathSignature(previous.path, previous.contentHash)
}

function taskIsCurrent(
  previous: NativeTaskState | none,
  fingerprint: string,
  auxiliaryOutputPaths: readonly string[] = [],
): bool {
  if previous == none || !exists(previous!.outputPath) { return false }
  for path of auxiliaryOutputPaths { if !exists(path) || isDirectory(path) { return false } }
  info := metadata(previous!.outputPath) else { return false }
  let currentInputs: NativeInputSignature[] = []
  for input of previous!.inputs {
    signature := currentInputSignature(input)
    if signature == none { return false }
    currentInputs.push(signature!)
  }
  return nativeTaskStateIsCurrent(previous, fingerprint, info.size, info.modifiedAt.toEpochNanos(), currentInputs, true)
}

/** Pure invalidation rule used by the filesystem executor and focused tests. */
export function nativeTaskStateIsCurrent(
  previous: NativeTaskState | none,
  fingerprint: string,
  outputSize: long,
  outputModifiedNanos: long,
  currentInputs: NativeInputSignature[],
  auxiliaryOutputsCurrent: bool = true,
): bool {
  if !auxiliaryOutputsCurrent { return false }
  if previous == none || previous!.fingerprint != fingerprint { return false }
  if previous!.outputSize != outputSize || previous!.outputModifiedNanos != outputModifiedNanos { return false }
  if previous!.inputs.length == 0 || previous!.inputs.length != currentInputs.length { return false }
  for index of 0..<previous!.inputs.length {
    expected := previous!.inputs[index]
    current := currentInputs[index]
    if expected.path != current.path || expected.signature != current.signature || expected.contentHash != current.contentHash ||
      expected.size != current.size || expected.modifiedNanos != current.modifiedNanos { return false }
  }
  return true
}

function captureTaskState(task: NativeCompileTask, fingerprint: string): NativeTaskState {
  info := try! metadata(task.outputPath)
  state := NativeTaskState { id: task.id, fingerprint, outputPath: task.outputPath, outputSize: info.size, outputModifiedNanos: info.modifiedAt.toEpochNanos() }
  let paths: string[] = [task.sourcePath]
  if task.dependencyFilePath != "" && exists(task.dependencyFilePath) {
    dependencySource := try! readText(task.dependencyFilePath)
    dependencies := if task.dependencyFilePath.toLowerCase().endsWith(".json")
      then parseMsvcDependencies(dependencySource)
      else parseMakeDependencies(dependencySource)
    for path of dependencies { appendUnique(paths, path) }
  }
  for path of paths {
    signature := pathSignature(path, true)
    if signature != none { state.inputs.push(signature!) }
  }
  return state
}

function captureLinkState(outputPath: string, fingerprint: string, objectPaths: string[]): NativeTaskState {
  info := try! metadata(outputPath)
  state := NativeTaskState { id: "link:" + outputPath, fingerprint, outputPath, outputSize: info.size, outputModifiedNanos: info.modifiedAt.toEpochNanos() }
  for path of objectPaths {
    signature := pathSignature(path, false)
    if signature != none { state.inputs.push(signature!) }
  }
  return state
}

function readBuildState(path: string): NativeBuildState {
  if !exists(path) { return NativeBuildState {} }
  source := readText(path) else { return NativeBuildState {} }
  parsed := parseNativeBuildState(source)
  return if parsed == none then NativeBuildState {} else parsed!
}

function writeBuildState(path: string, state: NativeBuildState): none {
  temporaryPath := path + ".tmp"
  try! writeText(temporaryPath, renderNativeBuildState(state))
  try! rename(temporaryPath, path)
}

function writeTextIfChanged(path: string, content: string): none {
  if exists(path) {
    previous := readText(path) else { try! writeText(path, content); return }
    if !nativeSupportFileNeedsWrite(previous, content) { return }
  }
  try! writeText(path, content)
}

/** Keeps generated build inputs stable so unchanged PCH dependencies remain reusable. */
export function nativeSupportFileNeedsWrite(previous: string | none, content: string): bool {
  return previous == none || previous! != content
}

function collectManagedOutputs(outputs: string[], outputDirectory: string, plan: NativeCompilePlan, project: ProjectEmission): none {
  appendUnique(outputs, joinOutput(outputDirectory, "doof_runtime.hpp"))
  for supportFile of plan.supportFiles { appendUnique(outputs, supportFile.outputPath) }
  for module of project.modules {
    appendUnique(outputs, joinOutput(outputDirectory, module.headerName))
    appendUnique(outputs, joinOutput(outputDirectory, module.sourceName))
  }
  for supportFile of project.supportFiles { appendUnique(outputs, joinOutput(outputDirectory, supportFile.relativePath)) }
  for nativeCopy of project.nativeCopies {
    collectManagedNativeCopyOutputs(outputs, nativeCopy.sourcePath, joinOutput(outputDirectory, nativeCopy.relativePath))
  }
  if plan.precompiledHeaderTask != none {
    appendUnique(outputs, plan.precompiledHeaderTask!.outputPath)
    if plan.precompiledHeaderTask!.dependencyFilePath != "" { appendUnique(outputs, plan.precompiledHeaderTask!.dependencyFilePath) }
    for path of plan.precompiledHeaderTask!.auxiliaryOutputPaths { appendUnique(outputs, path) }
  }
  for task of plan.compileTasks {
    appendUnique(outputs, task.outputPath)
    if task.dependencyFilePath != "" { appendUnique(outputs, task.dependencyFilePath) }
    for path of task.auxiliaryOutputPaths { appendUnique(outputs, path) }
  }
  appendUnique(outputs, plan.outputPath)
}

function collectManagedNativeCopyOutputs(outputs: string[], sourcePath: string, outputPath: string): none {
  if !isDirectory(sourcePath) {
    appendUnique(outputs, outputPath)
    return
  }
  for entry of try! readDir(sourcePath) {
    collectManagedNativeCopyOutputs(outputs, joinOutput(sourcePath, entry.name), joinOutput(outputPath, entry.name))
  }
}

function removeStaleOutputs(previous: string[], current: string[], outputDirectory: string): none {
  prefix := if outputDirectory.endsWith("/") then outputDirectory else outputDirectory + "/"
  for path of previous {
    if contains(current, path) || !path.startsWith(prefix) || !exists(path) || isDirectory(path) { continue }
    try! remove(path)
  }
}

function mutableArguments(arguments: readonly string[]): string[] {
  let result: string[] = []
  for argument of arguments { result.push(argument) }
  return result
}

function contains(values: string[], value: string): bool {
  for existing of values { if existing == value { return true } }
  return false
}

function appendUnique(values: string[], value: string): none {
  if !contains(values, value) { values.push(value) }
}

function joinOutput(directory: string, name: string): string { return if directory.endsWith("/") then directory + name else directory + "/" + name }
function parentDirectory(path: string): string {
  let index = path.length - 1
  while index > 0 && path[index] != '/' { index -= 1 }
  return if index <= 0 then "/" else path.substring(0, index)
}

function ensureDirectory(path: string): none {
  if path == "" || exists(path) { return }
  parent := parentDirectory(path)
  if parent != path { ensureDirectory(parent) }
  try! mkdir(path)
}
