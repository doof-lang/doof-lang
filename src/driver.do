// Runnable Doof compiler driver.
//
// The driver keeps filesystem access at the native-runtime boundary.  The
// compiler itself still receives ordinary SourceFile values, so this surface
// exercises the same resolver, analyzer, checker, and emitter used by the
// in-memory tests. This module routes CLI commands and owns the compile
// workflow; source loading, caching, materialization, testing, launching, and
// packaging live in the focused `*-driver` modules it delegates to.

import { compilerVersion } from "./version"
import { PhaseTimings } from "./phase-timings"
import { checkWithLoader, Compilation, compileWithLoader } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { CliRequest, cliUsage, parseCli } from "./cli"
import { EmissionConfiguration } from "./emitter-context"
import { planProjectEmission } from "./emitter-project"
import { ModuleNamespaceMapping } from "./emitter-names"
import {
  cachedModuleGraph, frontendCachePath, frontendConfigurationFingerprint, frontendEmissionCacheSupported,
  frontendStateForCompilation, frontendStateMatches, readFrontendState, removeStaleFrontendOutputs,
  reusableEmissionKeys, writeFrontendState,
} from "./frontend-cache-driver"
import { configureIOSNativeBuild } from "./ios-app-driver"
import { BuiltProjectLayout, buildAndLaunchProject } from "./launch-driver"
import {
  driverOutputPath, materializeObserverRuntime, materializeObserverUi, materializeProject, materializeRuntimeHeader,
} from "./materialize-driver"
import { packageProject } from "./package-driver"
import { hostPlatform, printDiagnostics } from "./process-driver"
import { ProjectSpec, environmentValue, joinPath, projectEntryRequestError, readProjectSpec } from "./project"
import { acquireProjectBuildLock } from "./project-build-lock"
import { debugTargetError } from "./debug-command"
import { observeTargetError } from "./observe-command"
import {
  driverRootLogicalPath, driverRootLogicalPrefix, ensureStdPackageReached,
  projectNativePackages, sourceLoaderForRequest, stdlibTargetForRequest,
} from "./source-loader-driver"
import { testRequest } from "./test-driver"
import { exists, isDirectory, remove } from "std/fs"
import { absolute } from "std/path"

import isolated function printFlushed(value: string): none from "doof_runtime.hpp" as doof::print_flushed

export function nativeBuildOutputName(projectName: string, nativePlatform: string): string {
  name := projectName.replaceAll("/", "-").replaceAll("\\", "-")
  if nativePlatform == "windows" && !name.toLowerCase().endsWith(".exe") { return name + ".exe" }
  return name
}

function projectExecutableName(project: ProjectSpec, nativePlatform: string): string {
  if project.target == "wasm" { return nativeBuildOutputName(project.name, "") + ".wasm" }
  if project.macosApp != none { return project.macosApp!.executableName }
  if project.iosApp != none { return project.iosApp!.executableName }
  return nativeBuildOutputName(project.name, nativePlatform)
}

/** Keeps timing reports available on early diagnostic and cache-hit returns. */
function emitRequest(request: CliRequest): int {
  timings := PhaseTimings { enabled: phaseTimingsEnabled(request.command, environmentValue("DOOF_TIMINGS")) }
  started := timings.start()
  result := emitRequestTimed(request, timings)
  timings.finish("command.total", started)
  if timings.enabled { printFlushed(timings.render()) }
  return result
}

export function phaseTimingsEnabled(command: string, value: string): bool {
  return (command == "emit" || command == "check") && value == "1"
}

function emitRequestTimed(request: CliRequest, timings: PhaseTimings): int {
  setupStart := timings.start()
  if request.nativePlatformOverride != "" && request.command != "emit" && request.command != "check" {
    println("error: --native-platform is only supported with emit and check")
    return 1
  }
  if request.command == "profile" && hostPlatform() != "macos" {
    println("error: doof profile is currently supported only on macOS")
    return 1
  }
  if request.command == "debug" && hostPlatform() != "macos" {
    println("error: doof debug is supported only on macOS")
    return 1
  }
  requestedNativePlatform := if request.nativePlatformOverride == "" then hostPlatform() else request.nativePlatformOverride
  let project = readProjectSpec(request.entry, requestedNativePlatform, request.targetOverride)
  entryError := projectEntryRequestError(project, request.entry)
  if entryError != "" {
    println("error: " + entryError)
    return 1
  }
  projectLock := acquireProjectBuildLock(project.rootDirectory, project.buildDirectory) else error {
    println("error: " + error)
    return 1
  }
  if request.command == "profile" && (project.target == "wasm" || project.iosApp != none) {
    println("error: doof profile supports native console executables and macOS applications")
    return 1
  }
  if request.command == "debug" {
    debugError := debugTargetError(hostPlatform(), project.target)
    if debugError != "" { println("error: " + debugError); return 1 }
  }
  if request.command == "observe" {
    observeError := observeTargetError(project.target, project.iosApp != none)
    if observeError != "" { println("error: " + observeError); return 1 }
    if project.observeUiRoot != "" && (!isDirectory(project.observeUiRoot) || !exists(joinPath(project.observeUiRoot, "index.html"))) {
      println("error: observe.ui must name a directory containing index.html: " + project.observeUiRoot)
      return 1
    }
  }
  iosDestination := if request.command == "package" then "device" else request.iosDestination
  nativePlatform := if project.iosApp == none then requestedNativePlatform else "ios-" + iosDestination
  if project.iosApp != none { project = readProjectSpec(request.entry, nativePlatform, request.targetOverride) }
  stdlibTarget := stdlibTargetForRequest(project.target, nativePlatform)
  rootManifest := project.manifest
  buildDirectory := if request.outputDirectory == ""
    then joinPath(project.rootDirectory, project.buildDirectory)
    else absolute(request.outputDirectory)!
  entryPath := joinPath(project.rootDirectory, project.entry)
  entry := driverRootLogicalPath(entryPath, project.rootDirectory, project.name)
  stdlibRoot := environmentValue("DOOF_STDLIB_ROOT")
  let namespaceMappings: ModuleNamespaceMapping[] = [ModuleNamespaceMapping {
    logicalPrefix: driverRootLogicalPrefix(project.name, project.rootDirectory),
    packageName: project.name,
    outputRoot: "",
  }]
  loader := sourceLoaderForRequest(
    entryPath, stdlibRoot, namespaceMappings, rootManifest, buildDirectory, nativePlatform, stdlibTarget,
  ) else error {
    println("error: " + error)
    return 1
  }
  if project.target == "wasm" {
    _ := ensureStdPackageReached("std/json") else error {
      println("error: " + error)
      return 1
    }
  }
  entryMode := if project.target == "wasm" then "wasm" else if project.iosApp == none then "executable" else "ios-app"
  outputDirectory := if request.command == "package"
    then joinPath(buildDirectory, "release")
    else if request.command == "profile" then joinPath(buildDirectory, "profile")
    else if request.command == "debug" then joinPath(buildDirectory, "debug")
    else if request.command == "observe" then joinPath(buildDirectory, "observe") else buildDirectory
  cacheDirectory := if request.command == "profile" || request.command == "debug" || request.command == "observe" then outputDirectory else buildDirectory
  frontendConfiguration := frontendConfigurationFingerprint(
    entry, entryMode, project.target, rootManifest, stdlibRoot, nativePlatform, stdlibTarget,
  )
  timings.finish("command.setup", setupStart)
  cacheStart := timings.start()
  checkCachePath := frontendCachePath(cacheDirectory, "check")
  if request.command == "check" && frontendStateMatches(readFrontendState(checkCachePath), frontendConfiguration, loader) {
    timings.finish("command.cache-lookup", cacheStart)
    return 0
  }
  emissionCachePath := frontendCachePath(cacheDirectory, "emission")
  previousEmissionState := readFrontendState(emissionCachePath)
  let reusedFrontend = false
  let result = Compilation { emission: none, diagnostics: [] }
  cachedGraph := if request.command == "emit" || request.command == "build" || request.command == "run" || request.command == "observe" || request.command == "profile" || request.command == "debug"
    then if !frontendEmissionCacheSupported(project.target)
      then none
      else if frontendStateMatches(previousEmissionState, frontendConfiguration, loader) && previousEmissionState != none
        then cachedModuleGraph(previousEmissionState!, outputDirectory)
        else none
    else none
  timings.finish("command.cache-lookup", cacheStart)
  compilerStart := timings.start()
  if cachedGraph != none {
    result = Compilation { emission: cachedGraph!, diagnostics: [] }
    reusedFrontend = true
  } else {
    result = if request.command == "check"
      then checkWithLoader([], entry, loader, entryMode, timings)
      else compileWithLoader(
        [], entry, loader, namespaceMappings, entryMode, false,
        if request.command == "package" || frontendConfiguration == "" then [] else reusableEmissionKeys(previousEmissionState, outputDirectory),
        frontendConfiguration,
        request.command == "profile" || request.command == "debug" || request.command == "observe", timings,
        EmissionConfiguration { observe: request.command == "observe", metricsClassLifecycle: request.command == "observe" },
      )
  }
  timings.finish("command.compiler", compilerStart)
  diagnosticsStart := timings.start()
  hasCompilationErrors := hasErrorDiagnostics(result.diagnostics)
  if result.diagnostics.length > 0 && (request.command != "run" || hasCompilationErrors) {
    printDiagnostics(result.diagnostics)
  }
  if hasCompilationErrors { return 1 }
  if request.command != "check" && request.command != "package" && !reusedFrontend && result.diagnostics.length == 0 {
    writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest))
  }
  timings.finish("command.diagnostics-check-cache", diagnosticsStart)
  if request.command == "check" {
    if result.diagnostics.length == 0 {
      writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest))
    }
    return 0
  }
  if result.emission == none { panic("compiler produced no emission") }
  projectStart := timings.start()
  emission := planProjectEmission(
    result.emission!,
    projectNativePackages(project.rootDirectory, rootManifest, stdlibRoot),
    request.command == "observe",
  )
  timings.finish("command.project-planning", projectStart)
  materializationStart := timings.start()
  _ := materializeProject(outputDirectory, emission) else error {
    println("error: " + error)
    return 1
  }
  materializeRuntimeHeader(outputDirectory)
  if request.command == "observe" {
    materializeObserverRuntime(outputDirectory)
    materializeObserverUi(outputDirectory)
  }
  observeUiRoot := if project.observeUiRoot != "" then project.observeUiRoot else driverOutputPath(outputDirectory, "observer-ui")
  legacyProvenance := driverOutputPath(outputDirectory, "provenance.json")
  if exists(legacyProvenance) { remove(legacyProvenance)! }
  if !reusedFrontend && request.command != "package" && frontendEmissionCacheSupported(project.target) {
    nextEmissionState := frontendStateForCompilation(result, frontendConfiguration, rootManifest)
    removeStaleFrontendOutputs(previousEmissionState, nextEmissionState, outputDirectory)
    writeFrontendState(emissionCachePath, nextEmissionState)
  }
  timings.finish("command.materialization-cache", materializationStart)
  if project.iosApp != none {
    _ := configureIOSNativeBuild(outputDirectory, project.iosApp!, iosDestination, emission.nativeBuild) else error {
      println("error: " + error)
      return 1
    }
  }
  executableName := projectExecutableName(project, nativePlatform)
  if request.command == "build" || request.command == "run" || request.command == "observe" || request.command == "profile" || request.command == "debug" {
    layout := BuiltProjectLayout {
      outputDirectory, cacheDirectory, buildDirectory, entryPath, nativePlatform, iosDestination, executableName, observeUiRoot,
    }
    return buildAndLaunchProject(request, project, emission, layout, projectLock)
  }
  if request.command == "package" {
    return packageProject(request, project, emission, outputDirectory, iosDestination, executableName)
  }
  return 0
}

function main(args: string[]): int {
  parsed := parseCli(args)
  if parsed.version { println("doof " + compilerVersion); return 0 }
  if parsed.help {
    println(cliUsage())
    return 0
  }
  if parsed.error != "" {
    println("error: " + parsed.error)
    println(cliUsage())
    return 2
  }
  if parsed.request!.command == "test" { return testRequest(parsed.request!) }
  return emitRequest(parsed.request!)
}
