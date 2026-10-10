// Optional dependency detection owns pkg-config and bounded compile/link probes.
// Probes use the application's target compiler and flags; never execute outputs.
import { OptionalPkgConfigPackage } from "./native-dependency-config"
import { NativeBuildPlan } from "./package-manifest"
import { NativeCompilePlan, planNativeCompile } from "./native-build"
import { PkgConfigCommandResult, applyPkgConfigResult } from "./pkg-config"
import { BlobReader } from "std/blob"
import { exists, mkdir, remove } from "std/fs"
import { ExecOptions, env, run } from "std/os"
import { absolute } from "std/path"

export function nativePkgConfigProgram(configured: string): string {
  return if configured == "" then "pkg-config" else configured
}

export function optionalNativePath(outputDirectory: string, path: string): string {
  if path.startsWith("/") || path.startsWith("\\\\") || (path.length > 1 && path[1] == ':') { return path }
  return outputDirectory + "/" + path
}

function appendAll(target: string[], values: string[]): none {
  for value of values { if !target.contains(value) { target.push(value) } }
}

function appendInputs(target: NativeBuildPlan, source: NativeBuildPlan): none {
  appendAll(target.includePaths, source.includePaths)
  appendAll(target.libraryPaths, source.libraryPaths)
  appendAll(target.linkLibraries, source.linkLibraries)
  appendAll(target.frameworks, source.frameworks)
  appendAll(target.defines, source.defines)
  appendAll(target.compilerFlags, source.compilerFlags)
  appendAll(target.linkerFlags, source.linkerFlags)
}

/** Candidate metadata is transactional: a partial lookup never leaks flags. */
export function optionalPkgConfigInputs(
  native: NativeBuildPlan, name: string,
  cflags: PkgConfigCommandResult, libs: PkgConfigCommandResult,
): NativeBuildPlan | none {
  if cflags.exitCode != 0 || libs.exitCode != 0 { return none }
  candidate := NativeBuildPlan {}
  appendInputs(candidate, native)
  _ := applyPkgConfigResult(candidate, name, "cflags", cflags) else { return none }
  _ := applyPkgConfigResult(candidate, name, "libs", libs) else { return none }
  return candidate
}

/** Capability defines are owned by detection, including the explicit stub value. */
export function applyOptionalNativeSelection(
  native: NativeBuildPlan, define: string, selected: NativeBuildPlan | none,
): Result<none, string> {
  for existing of native.defines {
    if existing == define || existing.startsWith(define + "=") {
      return Failure("Optional native capability define \"" + define + "\" is already declared; give each optional dependency a unique define and do not set it manually")
    }
  }
  if selected != none {
    for supplied of selected!.defines {
      if supplied == define || supplied.startsWith(define + "=") {
        return Failure("pkg-config must not supply the optional capability define \"" + define + "\"")
      }
    }
    appendInputs(native, selected!)
  }
  native.defines.push(define + if selected == none then "=0" else "=1")
  return Success()
}

/** Reuses ordinary target argument planning without application sources or PCH. */
export function optionalNativeProbePlan(
  native: NativeBuildPlan, dependency: OptionalPkgConfigPackage,
  compiler: string, outputDirectory: string, platform: string, wasm: bool = false,
): NativeCompilePlan {
  candidate := NativeBuildPlan {}
  appendInputs(candidate, native)
  ignoredIncludes := candidate.includePaths.drainToReadonly()
  ignoredLibraries := candidate.libraryPaths.drainToReadonly()
  for path of native.includePaths { candidate.includePaths.push(optionalNativePath(outputDirectory, path)) }
  for path of native.libraryPaths { candidate.libraryPaths.push(optionalNativePath(outputDirectory, path)) }
  candidate.includePaths.push(outputDirectory)
  candidate.defines.push(dependency.define + "=1")
  candidate.sourceFiles.push(optionalNativePath(outputDirectory, dependency.probeSource))
  probeDirectory := outputDirectory + "/.doof-probes/" + dependency.define
  suffix := if wasm then ".wasm" else if platform == "windows" then ".exe" else ""
  return planNativeCompile(compiler, probeDirectory, probeDirectory + "/probe" + suffix, [], candidate, .Debug, platform, [], wasm, true)
}

function captured(command: string, arguments: readonly string[]): Result<PkgConfigCommandResult, string> {
  let mutableArguments: string[] = []
  for argument of arguments { mutableArguments.push(argument) }
  execution := run(command, mutableArguments, ExecOptions {
    withStdin: false, mergeStderrIntoStdout: true, maxOutputBytes: 262144L,
  }) else error { return Success(PkgConfigCommandResult { exitCode: -1, error }) }
  if execution.stdoutTruncated { return Failure("Optional native dependency command output was truncated: " + command) }
  return Success(PkgConfigCommandResult {
    exitCode: execution.exitCode,
    output: BlobReader(execution.stdout).readString(long(execution.stdout.length)),
  })
}

function configuredPkgConfigProgram(): string {
  configured := env("PKG_CONFIG") else { return "pkg-config" }
  return nativePkgConfigProgram(configured)
}

function probeDirectory(path: string): Result<none, string> {
  if exists(path) { return Success() }
  let end = path.length - 1
  while end > 0 && path[end] != '/' { end -= 1 }
  if end > 0 { try probeDirectory(path.substring(0, end)) }
  _ := mkdir(path) else error { return Failure("Could not create optional dependency probe directory " + path + ": " + string(error)) }
  return Success()
}

function discardProbeFile(path: string): Result<none, string> {
  if path == "" || !exists(path) { return Success() }
  _ := remove(path) else error { return Failure("Could not remove optional dependency probe output " + path + ": " + string(error)) }
  return Success()
}

/** Missing metadata or incompatible inputs select a stub; broken tools are errors. */
export function resolveOptionalNativeDependencies(
  native: NativeBuildPlan, compiler: string, outputDirectory: string, platform: string, wasm: bool,
  pkgConfigCommand: string = "",
): Result<string[], string> {
  let descriptions: string[] = []
  if native.optionalPkgConfigPackages.length == 0 { return Success(descriptions) }
  try buildDirectory := absolute(outputDirectory)
  program := if pkgConfigCommand == "" then configuredPkgConfigProgram() else pkgConfigCommand
  for dependency of native.optionalPkgConfigPackages {
    probeSource := optionalNativePath(buildDirectory, dependency.probeSource)
    if !exists(probeSource) { return Failure("Optional native dependency probe source is missing: " + probeSource) }
    let compatibleVersion = true
    if dependency.minimumVersion != "" {
      try version := captured(program, ["--atleast-version=" + dependency.minimumVersion, dependency.name])
      compatibleVersion = version.exitCode == 0
    }
    let selected: NativeBuildPlan | none = none
    if compatibleVersion {
      try cflags := captured(program, ["--cflags", dependency.name])
      try libs := captured(program, ["--libs", dependency.name])
      candidate := optionalPkgConfigInputs(native, dependency.name, cflags, libs)
      if candidate != none {
        plan := optionalNativeProbePlan(candidate!, dependency, compiler, buildDirectory, platform, wasm)
        try probeDirectory(buildDirectory + "/.doof-probes/" + dependency.define)
        let passed = true
        for task of plan.compileTasks {
          // Probe plans currently have one native object and no generated units.
          try probeDirectory(buildDirectory + "/.doof-probes/" + dependency.define + "/.doof-objects/native")
          try compilation := captured(task.compiler, task.arguments)
          if compilation.exitCode == -1 { return Failure("Failed to run optional dependency target compiler: " + compilation.error) }
          if compilation.exitCode != 0 { passed = false; break }
        }
        if passed {
          try linking := captured(plan.linker, plan.linkArguments.drainToReadonly())
          if linking.exitCode == -1 { return Failure("Failed to run optional dependency target linker: " + linking.error) }
          passed = linking.exitCode == 0
        }
        if passed { selected = candidate }
        // Probes are disposable detection products, not persistent build state.
        for task of plan.compileTasks {
          try discardProbeFile(task.outputPath)
          try discardProbeFile(task.dependencyFilePath)
        }
        try discardProbeFile(plan.outputPath)
      }
    }
    try applyOptionalNativeSelection(native, dependency.define, selected)
    descriptions.push("Optional native dependency " + dependency.name + if selected == none then " unavailable (" + dependency.define + "=0)" else " available (" + dependency.define + "=1)")
  }
  return Success(descriptions)
}
