// Post-compile native build and launch for build, run, observe, profile, and
// debug commands across console programs, macOS apps, and iOS apps.

import { CliRequest } from "./cli"
import { launchDebugger } from "./debug-driver"
import { ProjectEmission } from "./emitter-project"
import { frontendCachePath } from "./frontend-cache-driver"
import { assembleIOSApp } from "./ios-app-driver"
import { resolveIOSDeviceIdentifier, resolveIOSDeviceSigningOptions, signIOSDeviceApp } from "./ios-device"
import { assembleMacOSApp } from "./macos-app-driver"
import { driverOutputPath, ensureOutputDirectory, synchronizeExecutableResources } from "./materialize-driver"
import { NativeBuildOutputMode, buildNativeProject } from "./native-build-driver"
import { observeEnvironment, planObservedMacOSAppRun } from "./observe-command"
import { MAX_NATIVE_COMPILER_OUTPUT_BYTES, hostPlatform, runNativeCommand } from "./process-driver"
import { planProfileCapture, planProfileOpen, planProfileSymbols } from "./profile-command"
import { ProjectSpec, joinPath, parentPath } from "./project"
import {
  planIOSDeviceInstall, planIOSDeviceLaunch, planIOSSimulatorInstall, planIOSSimulatorLaunch,
  planMacOSAppRun, planNativeProgramRun,
} from "./run-command"
import { File, exists, readText, remove } from "std/fs"
import { absolute } from "std/path"
import { Duration, Instant, Thread } from "std/time"

/** Paths and platform choices resolved by the compile workflow for the native build. */
export class BuiltProjectLayout {
  readonly outputDirectory: string
  readonly cacheDirectory: string
  readonly buildDirectory: string
  readonly entryPath: string
  readonly nativePlatform: string
  readonly iosDestination: string
  readonly executableName: string
  readonly observeUiRoot: string
}

/** Selects whether a top-level command may report successful native build progress. */
export function nativeBuildOutputModeForCommand(command: string): NativeBuildOutputMode {
  return if command == "run" || command == "observe" then .Silent else .Progress
}

/** Receives a detached macOS app's observer URL, then removes the token file. */
export function takeObserveUrlFile(path: string, attempts: int = 100): string {
  for _ of 0..<attempts {
    if exists(path) {
      content := readText(path) else { return "" }
      remove(path)!
      return content.trim()
    }
    Thread.sleep(Duration.ofMillis(50L))
  }
  return ""
}

/** Builds the native artifact, then launches it as the command requests. The project lock is released before launch. */
export function buildAndLaunchProject(
  request: CliRequest,
  project: ProjectSpec,
  emission: ProjectEmission,
  layout: BuiltProjectLayout,
  projectLock: File,
): int {
  if request.command == "run" && project.target == "wasm" {
    println("error: doof run is not supported for --target wasm; instantiate the generated .wasm from your host runtime")
    return 1
  }
  outputPath := driverOutputPath(layout.outputDirectory, layout.executableName)
  if project.macosApp == none && project.iosApp == none {
    synchronizeExecutableResources(project.resources, layout.outputDirectory, frontendCachePath(layout.cacheDirectory, "resources"))
  }
  exitCode := buildNativeProject(
    request.compiler, layout.outputDirectory, outputPath, emission,
    if request.command == "profile" then .Profile else if request.command == "debug" then .InteractiveDebug else .Debug, hostPlatform(),
    nativeBuildOutputModeForCommand(request.command),
  )
  if exitCode != 0 { return exitCode }
  if project.iosApp != none { return launchIOSApp(request, project, layout, outputPath, projectLock) }
  if project.macosApp != none { return launchMacOSApp(request, project, emission, layout, outputPath, projectLock) }
  return launchConsoleProgram(request, project, layout, outputPath, projectLock)
}

function launchIOSApp(
  request: CliRequest,
  project: ProjectSpec,
  layout: BuiltProjectLayout,
  outputPath: string,
  projectLock: File,
): int {
  outputDirectory := layout.outputDirectory
  appPath := assembleIOSApp(outputDirectory, outputPath, project.iosApp!, layout.iosDestination) else error {
    println("error: " + error)
    return 1
  }
  if request.command == "build" { return 0 }
  if layout.iosDestination == "device" {
    signingWorkDirectory := driverOutputPath(outputDirectory, ".doof-ios-signing-resolution")
    signing := resolveIOSDeviceSigningOptions(
      project.iosApp!.bundleId,
      request.iosSignIdentity,
      request.iosProvisioningProfile,
      signingWorkDirectory,
    ) else error {
      println("error: " + error)
      return 1
    }
    _ := signIOSDeviceApp(
      appPath,
      project.iosApp!.bundleId,
      signing,
      driverOutputPath(outputDirectory, ".doof-ios-sign"),
    ) else error {
      println("error: " + error)
      return 1
    }
    deviceIdentifier := resolveIOSDeviceIdentifier(
      request.iosDevice,
      driverOutputPath(outputDirectory, ".doof-ios-device-discovery"),
    ) else error {
      println("error: " + error)
      return 1
    }
    installPlan := planIOSDeviceInstall(appPath, deviceIdentifier, project.rootDirectory)
    installResult := runNativeCommand(installPlan.command, installPlan.arguments, installPlan.directory, true)
    if installResult.error != "" { println("error: " + installResult.error) }
    if installResult.exitCode != 0 { return installResult.exitCode }
    projectLock.close()!
    launchPlan := planIOSDeviceLaunch(project.iosApp!.bundleId, deviceIdentifier, project.rootDirectory)
    launchResult := runNativeCommand(launchPlan.command, launchPlan.arguments, launchPlan.directory, true)
    if launchResult.error != "" { println("error: " + launchResult.error) }
    return launchResult.exitCode
  }
  installPlan := planIOSSimulatorInstall(appPath, project.rootDirectory)
  installResult := runNativeCommand(installPlan.command, installPlan.arguments, installPlan.directory, true)
  if installResult.error != "" { println("error: " + installResult.error) }
  if installResult.exitCode != 0 { return installResult.exitCode }
  projectLock.close()!
  launchPlan := planIOSSimulatorLaunch(project.iosApp!.bundleId, project.rootDirectory)
  launchResult := runNativeCommand(launchPlan.command, launchPlan.arguments, launchPlan.directory, true)
  if launchResult.error != "" { println("error: " + launchResult.error) }
  return launchResult.exitCode
}

function launchMacOSApp(
  request: CliRequest,
  project: ProjectSpec,
  emission: ProjectEmission,
  layout: BuiltProjectLayout,
  outputPath: string,
  projectLock: File,
): int {
  outputDirectory := layout.outputDirectory
  appPath := assembleMacOSApp(outputDirectory, outputPath, project.macosApp!, emission.nativeBuild.libraryPaths, emission.nativeBuild.bundledLibraries) else error {
    println("error: " + error)
    return 1
  }
  if request.command == "build" { return 0 }
  if request.command == "debug" {
    projectLock.close()!
    return launchDebugger(
      joinPath(joinPath(appPath, "Contents/MacOS"), layout.executableName), layout.entryPath, project.rootDirectory,
      outputDirectory, request.programArguments, request.debugLaunchJson,
    )
  }
  if request.command == "profile" {
    return runProfileTarget(
      request, appPath, outputPath, appPath + ".dSYM",
      project.rootDirectory, layout.buildDirectory, layout.executableName, false,
    )
  }
  projectLock.close()!
  urlFile := driverOutputPath(outputDirectory, ".doof-observe-url-" + string(Instant.now().toEpochMillis()))
  launchPlan := if request.command == "observe"
    then planObservedMacOSAppRun(appPath, project.rootDirectory, observeEnvironment(request.observePort, request.observeNoOpen, request.observeRetainEvents, layout.observeUiRoot, urlFile))
    else planMacOSAppRun(appPath, project.rootDirectory)
  launchResult := runNativeCommand(launchPlan.command, launchPlan.arguments, launchPlan.directory, true)
  if launchResult.error != "" { println("error: " + launchResult.error) }
  if launchResult.exitCode == 0 && request.command == "observe" {
    url := takeObserveUrlFile(urlFile)
    if !url.startsWith("http://127.0.0.1:") {
      println("error: observed macOS app did not publish its local URL")
      return 1
    }
    println("DOOF_OBSERVE_URL=" + url)
  }
  return launchResult.exitCode
}

function launchConsoleProgram(
  request: CliRequest,
  project: ProjectSpec,
  layout: BuiltProjectLayout,
  outputPath: string,
  projectLock: File,
): int {
  if request.command == "build" { return 0 }
  if request.command == "debug" {
    projectLock.close()!
    return launchDebugger(outputPath, layout.entryPath, project.rootDirectory, layout.outputDirectory, request.programArguments, request.debugLaunchJson)
  }
  if request.command == "profile" {
    return runProfileTarget(
      request, outputPath, outputPath, outputPath + ".dSYM",
      project.rootDirectory, layout.buildDirectory, layout.executableName, true,
    )
  }
  projectLock.close()!
  runPlan := planNativeProgramRun(outputPath, request.programArguments, project.rootDirectory)
  let environment: Map<string, string> = {}
  if request.command == "observe" {
    environment = observeEnvironment(request.observePort, request.observeNoOpen, request.observeRetainEvents, layout.observeUiRoot)
  }
  runResult := runNativeCommand(runPlan.command, runPlan.arguments, runPlan.directory, true, .Inherited, MAX_NATIVE_COMPILER_OUTPUT_BYTES, environment)
  if runResult.error != "" { println("error: " + runResult.error) }
  return runResult.exitCode
}

function runProfileTarget(
  request: CliRequest,
  targetPath: string,
  binaryPath: string,
  symbolsPath: string,
  packageRoot: string,
  buildDirectory: string,
  traceName: string,
  consoleTarget: bool,
): int {
  symbolsPlan := planProfileSymbols(binaryPath, symbolsPath, packageRoot)
  symbolsResult := runNativeCommand(symbolsPlan.command, symbolsPlan.arguments, symbolsPlan.directory, true)
  if symbolsResult.error != "" { println("error: " + symbolsResult.error) }
  if symbolsResult.exitCode != 0 {
    println("error: could not create profiling symbols at " + symbolsPath)
    return symbolsResult.exitCode
  }
  tracePath := if request.traceOutput == ""
    then joinPath(joinPath(buildDirectory, "profiles"), traceName + "-" + string(Instant.now().toEpochMillis()) + ".trace")
    else absolute(request.traceOutput)!
  if exists(tracePath) {
    println("error: profile trace already exists: " + tracePath)
    return 1
  }
  ensureOutputDirectory(parentPath(tracePath))
  plan := planProfileCapture(
    targetPath, request.programArguments, packageRoot, tracePath,
    request.profileTimeLimit, consoleTarget,
  )
  result := runNativeCommand(plan.command, plan.arguments, plan.directory, true, .Inherited)
  if !exists(tracePath) {
    if result.error != "" { println("error: " + result.error) }
    println("error: profiling did not produce a trace at " + tracePath)
    return 1
  }
  if !request.profileNoOpen {
    openPlan := planProfileOpen(tracePath, packageRoot)
    opened := runNativeCommand(openPlan.command, openPlan.arguments, openPlan.directory)
    if opened.exitCode != 0 {
      println("error: profile trace was saved at " + tracePath + " but could not be opened")
      return 1
    }
  }
  return 0
}
