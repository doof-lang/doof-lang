// Filesystem and process execution for planned native builds.
// Pure command construction remains in native-build.do; this module owns
// incremental state, dependency signatures, compiler workers, and linking.

import { ProjectEmission } from "./emitter-project"
import { NativeBuildMode, NativeCompilePlan, NativeCompileTask, batchNativeCompileTasks, isMsvcCompiler, planNativeCompile } from "./native-build"
import {
  NativeBuildState, NativeInputSignature, NativeTaskState,
  parseMakeDependencies, parseMsvcDependencies, parseNativeBuildState, renderNativeBuildState,
} from "./native-build-state"
import { PkgConfigCommandResult, applyPkgConfigResult } from "./pkg-config"
import { BlobReader } from "std/blob"
import { sha256Hex, sha256HexString } from "std/crypto"
import { exists, isDirectory, metadata, mkdir, readBlob, readDir, readText, remove, rename, writeText } from "std/fs"
import { ExecOptions, env, run } from "std/os"

import isolated function printFlushed(value: string): none from "doof_runtime.hpp" as doof::print_flushed

readonly MAX_NATIVE_OUTPUT_BYTES = 262144L

export enum NativeBuildOutputMode {
  Silent,
  Progress,
}

class NativeCommandResult {
  readonly exitCode: int
  readonly output: readonly byte[] = []
  readonly error: string = ""
  readonly truncated: bool
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
  }
}

function printBuildOutput(result: NativeCommandResult): none {
  output := if result.error != "" then result.error else BlobReader(result.output).readString(long(result.output.length))
  for line of output.split("\n") {
    if line == "" { continue }
    println(line)
  }
}

/** Renders the concise native source progress heading, or nothing for a cache hit. */
export function nativeCompilationSummary(fileCount: int): string {
  if fileCount <= 0 { return "" }
  return "Compiling " + string(fileCount) + if fileCount == 1 then " file" else " files"
}

/** Renders one progress marker per successfully compiled native source. */
export function nativeCompilationProgress(fileCount: int): string {
  return if fileCount <= 0 then "" else ".".repeat(fileCount)
}

/** Selects whether a completed native command should advance visible progress. */
export function shouldPrintNativeCompilationMarker(outputMode: NativeBuildOutputMode, exitCode: int): bool {
  return outputMode == .Progress && exitCode == 0
}

/** Successful compiler chatter is hidden; failed commands disclose their captured output. */
export function shouldPrintNativeCommandOutput(exitCode: int): bool {
  return exitCode != 0
}

class NativeCompilerWorker {
  readonly tasks: readonly NativeCompileTask[]
  readonly outputMode: NativeBuildOutputMode

  compile(): NativeCompilerBatchResult {
    let outputs: NativeCommandResult[] = []
    for task of this.tasks {
      result := runBuildCommand(task.compiler, mutableArguments(task.arguments))
      outputs.push(result)
      if shouldPrintNativeCompilationMarker(this.outputMode, result.exitCode) { printFlushed(".") }
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
  mode: NativeBuildMode,
  platform: string,
  outputMode: NativeBuildOutputMode,
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
  plan := planNativeCompile(compiler, outputDirectory, outputPath, project.modules, project.nativeBuild, mode, platform, project.wasmExportNames, wasm)
  return executeNativePlan(outputDirectory, plan, project, outputMode)
}

function envCompiler(): string {
  value := env("CXX") else { return "" }
  return value
}

function executeNativePlan(
  outputDirectory: string,
  plan: NativeCompilePlan,
  project: ProjectEmission,
  outputMode: NativeBuildOutputMode,
): int {
  for supportFile of plan.supportFiles {
    ensureDirectory(parentDirectory(supportFile.outputPath))
    writeTextIfChanged(supportFile.outputPath, supportFile.content)
  }
  statePath := joinOutput(outputDirectory, ".doof-native-build-state.json")
  previousState := readBuildState(statePath)
  previousTasks := indexNativeTaskStates(previousState)
  nextState := NativeBuildState {}
  let identities: NativeCompilerIdentity[] = []
  let truncationReported = false
  let pchChanged = false

  if plan.precompiledHeaderTask != none {
    pchTask := plan.precompiledHeaderTask!
    ensureDirectory(parentDirectory(pchTask.outputPath))
    pchFingerprint := taskFingerprint(pchTask, identities)
    pchPrevious := indexedNativeTaskState(previousTasks, pchTask.id)
    if !taskIsCurrent(pchPrevious, pchFingerprint, pchTask.auxiliaryOutputPaths) {
      pchChanged = true
      pchResult := runBuildCommand(pchTask.compiler, mutableArguments(pchTask.arguments))
      if pchResult.exitCode != 0 {
        printBuildOutput(pchResult)
        if pchResult.truncated { println("... native compiler output capture truncated after " + string(MAX_NATIVE_OUTPUT_BYTES) + " bytes"); truncationReported = true }
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
    previous := indexedNativeTaskState(previousTasks, task.id)
    if (task.usesPrecompiledHeader && pchChanged) || !taskIsCurrent(previous, fingerprint) {
      dirtyTasks.push(task)
      dirtyTaskIds.push(task.id)
    }
  }

  if outputMode == .Progress && dirtyTasks.length > 0 {
    println(nativeCompilationSummary(dirtyTasks.length))
  }

  let workers: Actor<NativeCompilerWorker>[] = []
  let promises: Promise<NativeCompilerBatchResult>[] = []
  for task of dirtyTasks { ensureDirectory(parentDirectory(task.outputPath)) }
  for batch of batchNativeCompileTasks(dirtyTasks) {
    worker := Actor<NativeCompilerWorker>(batch, outputMode)
    workers.push(worker)
    promises.push(async worker.compile())
  }
  let compileExitCode = 0
  let batchResults: NativeCompilerBatchResult[] = []
  for index of 0..<promises.length {
    batchResult := promises[index].get() else error {
      ignoredWorker := retire workers[index]
      if outputMode == .Progress && dirtyTasks.length > 0 { println("") }
      println("error: native compiler worker failed: " + error)
      return 1
    }
    retire workers[index]
    batchResults.push(batchResult)
  }
  if outputMode == .Progress && dirtyTasks.length > 0 { println("") }
  for batchResult of batchResults {
    for commandResult of batchResult.outputs {
      if shouldPrintNativeCommandOutput(commandResult.exitCode) {
        printBuildOutput(commandResult)
        if commandResult.truncated && !truncationReported { println("... native compiler output capture truncated after " + string(MAX_NATIVE_OUTPUT_BYTES) + " bytes"); truncationReported = true }
      }
    }
    if compileExitCode == 0 && batchResult.exitCode != 0 { compileExitCode = batchResult.exitCode }
  }
  if compileExitCode != 0 { println("error: native object compiler exited with code " + string(compileExitCode)); return compileExitCode }

  let objectPaths: string[] = []
  if plan.precompiledHeaderTask != none {
    for path of plan.precompiledHeaderTask!.auxiliaryOutputPaths { objectPaths.push(path) }
  }
  for index of 0..<plan.compileTasks.length {
    task := plan.compileTasks[index]
    objectPaths.push(task.outputPath)
    if contains(dirtyTaskIds, task.id) { nextState.tasks.push(captureTaskState(task, taskFingerprints[index])) }
    else { nextState.tasks.push(indexedNativeTaskState(previousTasks, task.id)!) }
  }

  linkId := "link:" + plan.outputPath
  computedLinkFingerprint := linkFingerprint(plan.linker, plan.linkArguments, plan.outputPath, identities)
  linkPrevious := indexedNativeTaskState(previousTasks, linkId)
  let linkChanged = false
  if dirtyTasks.length > 0 || !taskIsCurrent(linkPrevious, computedLinkFingerprint) {
    linkChanged = true
    let executedLinkArguments = plan.linkArguments
    if isMsvcLinker(plan.linker) {
      responsePath := msvcLinkResponsePath(outputDirectory)
      writeTextIfChanged(responsePath, msvcLinkResponseFile(plan.linkArguments))
      executedLinkArguments = ["@" + responsePath]
    }
    linkResult := runBuildCommand(plan.linker, executedLinkArguments)
    if linkResult.exitCode != 0 {
      printBuildOutput(linkResult)
      if linkResult.truncated && !truncationReported { println("... native linker output capture truncated after " + string(MAX_NATIVE_OUTPUT_BYTES) + " bytes") }
      println("error: native linker exited with code " + string(linkResult.exitCode))
      return linkResult.exitCode
    }
    nextState.tasks.push(captureLinkState(plan.outputPath, computedLinkFingerprint, objectPaths))
  } else { nextState.tasks.push(linkPrevious!) }

  collectManagedOutputs(nextState.managedOutputs, outputDirectory, plan, project)
  removeStaleOutputs(previousState.managedOutputs, nextState.managedOutputs, outputDirectory)
  if pchChanged || dirtyTasks.length > 0 || linkChanged || nativeManagedOutputsChanged(previousState.managedOutputs, nextState.managedOutputs) {
    writeBuildState(statePath, nextState)
  }
  return 0
}

function indexNativeTaskStates(state: NativeBuildState): Map<string, NativeTaskState> {
  let indexed: Map<string, NativeTaskState> = {}
  for task of state.tasks { indexed.set(task.id, task) }
  return indexed
}

function indexedNativeTaskState(
  indexed: Map<string, NativeTaskState>,
  id: string,
): NativeTaskState | none {
  task := indexed.get(id) else { return none }
  return task
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

/** Renders one quoted MSVC linker argument per line for an @response file. */
export function msvcLinkResponseFile(arguments: string[]): string {
  let content = ""
  for argument of arguments { content = content + quoteMsvcResponseArgument(argument) + "\n" }
  return content
}

function quoteMsvcResponseArgument(argument: string): string {
  let quoted = "\""
  let backslashes = 0
  for index of 0..<argument.length {
    value := argument[index]
    if value == '\\' { backslashes += 1; continue }
    if value == '"' {
      quoted = quoted + "\\".repeat(backslashes * 2 + 1) + "\""
    } else {
      quoted = quoted + "\\".repeat(backslashes) + string(value)
    }
    backslashes = 0
  }
  return quoted + "\\".repeat(backslashes * 2) + "\""
}

function collectManagedOutputs(outputs: string[], outputDirectory: string, plan: NativeCompilePlan, project: ProjectEmission): none {
  let indexed: Set<string> = []
  for output of outputs { indexed.add(output) }
  collectManagedOutputsIndexed(outputs, indexed, outputDirectory, plan, project)
}

function collectManagedOutputsIndexed(
  outputs: string[],
  indexed: Set<string>,
  outputDirectory: string,
  plan: NativeCompilePlan,
  project: ProjectEmission,
): none {
  appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, "doof_runtime.hpp"))
  for supportFile of plan.supportFiles { appendManagedOutput(outputs, indexed, supportFile.outputPath) }
  for module of project.modules {
    appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, module.headerName))
    appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, module.sourceName))
  }
  for supportFile of project.supportFiles { appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, supportFile.relativePath)) }
  for nativeCopy of project.nativeCopies {
    collectManagedNativeCopyOutputs(outputs, indexed, nativeCopy.sourcePath, joinOutput(outputDirectory, nativeCopy.relativePath))
  }
  if plan.precompiledHeaderTask != none {
    appendManagedOutput(outputs, indexed, plan.precompiledHeaderTask!.outputPath)
    if plan.precompiledHeaderTask!.dependencyFilePath != "" { appendManagedOutput(outputs, indexed, plan.precompiledHeaderTask!.dependencyFilePath) }
    for path of plan.precompiledHeaderTask!.auxiliaryOutputPaths { appendManagedOutput(outputs, indexed, path) }
  }
  for task of plan.compileTasks {
    appendManagedOutput(outputs, indexed, task.outputPath)
    if task.dependencyFilePath != "" { appendManagedOutput(outputs, indexed, task.dependencyFilePath) }
    for path of task.auxiliaryOutputPaths { appendManagedOutput(outputs, indexed, path) }
  }
  if isMsvcLinker(plan.linker) { appendManagedOutput(outputs, indexed, msvcLinkResponsePath(outputDirectory)) }
  appendManagedOutput(outputs, indexed, plan.outputPath)
}

function collectManagedNativeCopyOutputs(outputs: string[], indexed: Set<string>, sourcePath: string, outputPath: string): none {
  if !isDirectory(sourcePath) {
    appendManagedOutput(outputs, indexed, outputPath)
    return
  }
  for entry of try! readDir(sourcePath) {
    collectManagedNativeCopyOutputs(outputs, indexed, joinOutput(sourcePath, entry.name), joinOutput(outputPath, entry.name))
  }
}

function removeStaleOutputs(previous: string[], current: string[], outputDirectory: string): none {
  for path of staleManagedOutputCandidates(previous, current, outputDirectory) {
    if exists(path) && !isDirectory(path) { try! remove(path) }
  }
}

/** Selects only obsolete outputs owned by this build directory without quadratic membership scans. */
export function staleManagedOutputCandidates(previous: string[], current: string[], outputDirectory: string): string[] {
  prefix := if outputDirectory.endsWith("/") then outputDirectory else outputDirectory + "/"
  let retained: Set<string> = []
  for path of current { retained.add(path) }
  let stale: string[] = []
  for path of previous {
    if retained.has(path) || !path.startsWith(prefix) { continue }
    stale.push(path)
  }
  return stale
}

/** Avoids serializing and replacing the native snapshot when its deterministic output inventory is unchanged. */
export function nativeManagedOutputsChanged(previous: string[], current: string[]): bool {
  if previous.length != current.length { return true }
  for index of 0..<previous.length {
    if previous[index] != current[index] { return true }
  }
  return false
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

function appendManagedOutput(outputs: string[], indexed: Set<string>, value: string): none {
  if indexed.has(value) { return }
  indexed.add(value)
  outputs.push(value)
}

function joinOutput(directory: string, name: string): string { return if directory.endsWith("/") then directory + name else directory + "/" + name }
function msvcLinkResponsePath(outputDirectory: string): string { return joinOutput(outputDirectory, ".doof-link.rsp") }
function isMsvcLinker(linker: string): bool {
  normalized := linker.replaceAll("\\", "/").toLowerCase()
  return normalized == "link" || normalized == "link.exe" || normalized.endsWith("/link") || normalized.endsWith("/link.exe")
}
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
