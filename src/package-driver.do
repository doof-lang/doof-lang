// `doof package`: release native build, then copy resources or sign and
// archive macOS and iOS application bundles into the distribution directory.

import { CliRequest } from "./cli"
import { ProjectEmission } from "./emitter-project"
import { iosPackageArchiveName } from "./ios-app"
import { assembleIOSApp, signAndArchiveIOSApp } from "./ios-app-driver"
import { macOSPackageArchiveName } from "./macos-app"
import { assembleMacOSApp, signAndArchiveMacOSApp } from "./macos-app-driver"
import { driverOutputPath, ensureOutputDirectory, materializeExecutableResources } from "./materialize-driver"
import { buildNativeProject } from "./native-build-driver"
import { hostPlatform } from "./process-driver"
import { ProjectSpec, environmentValue } from "./project"
import { absolute } from "std/path"

/** Builds a release artifact and writes the distributable package for the project. */
export function packageProject(
  request: CliRequest,
  project: ProjectSpec,
  emission: ProjectEmission,
  outputDirectory: string,
  iosDestination: string,
  executableName: string,
): int {
  if project.packageConfig == none { panic("project package settings were not resolved") }
  distDirectory := if request.distDirectory != "" then absolute(request.distDirectory)! else project.packageConfig!.distDirectory
  ensureOutputDirectory(distDirectory)
  outputPath := if project.macosApp == none && project.iosApp == none
    then driverOutputPath(distDirectory, executableName)
    else driverOutputPath(outputDirectory, executableName)
  exitCode := buildNativeProject(
    request.compiler, outputDirectory, outputPath, emission, .Release, hostPlatform(), .Progress,
  )
  if exitCode != 0 { return exitCode }
  if project.macosApp == none && project.iosApp == none {
    materializeExecutableResources(project.resources, distDirectory)
    return 0
  }
  if project.iosApp != none {
    return packageIOSApp(request, project, outputDirectory, outputPath, distDirectory, iosDestination)
  }
  return packageMacOSApp(request, project, emission, outputDirectory, outputPath, distDirectory)
}

function packageIOSApp(
  request: CliRequest,
  project: ProjectSpec,
  outputDirectory: string,
  outputPath: string,
  distDirectory: string,
  iosDestination: string,
): int {
  appPath := assembleIOSApp(outputDirectory, outputPath, project.iosApp!, iosDestination) else error {
    println("error: " + error)
    return 1
  }
  if project.iosPackageConfig == none { panic("iOS package settings were not resolved") }
  iosConfig := project.iosPackageConfig!
  environmentIdentity := environmentValue("DOOF_IOS_SIGN_IDENTITY")
  if environmentIdentity != "" { iosConfig.identity = environmentIdentity }
  if request.iosSignIdentity != "" { iosConfig.identity = request.iosSignIdentity }
  environmentProfile := environmentValue("DOOF_IOS_PROVISIONING_PROFILE")
  if environmentProfile != "" { iosConfig.provisioningProfilePath = absolute(environmentProfile)! }
  if request.iosProvisioningProfile != "" { iosConfig.provisioningProfilePath = absolute(request.iosProvisioningProfile)! }
  archivePath := driverOutputPath(distDirectory, iosPackageArchiveName(project.iosApp!.executableName, project.iosApp!.version))
  _ := signAndArchiveIOSApp(appPath, archivePath, project.iosApp!.bundleId, iosConfig, outputDirectory) else error {
    println("error: " + error)
    return 1
  }
  println("Package: " + archivePath)
  return 0
}

function packageMacOSApp(
  request: CliRequest,
  project: ProjectSpec,
  emission: ProjectEmission,
  outputDirectory: string,
  outputPath: string,
  distDirectory: string,
): int {
  appPath := assembleMacOSApp(outputDirectory, outputPath, project.macosApp!, emission.nativeBuild.libraryPaths) else error {
    println("error: " + error)
    return 1
  }
  packageConfig := project.packageConfig!
  if request.macosSigning != "" { packageConfig.signing = request.macosSigning }
  environmentIdentity := environmentValue("DOOF_MACOS_SIGN_IDENTITY")
  if environmentIdentity != "" { packageConfig.identity = environmentIdentity }
  if request.macosSignIdentity != "" { packageConfig.identity = request.macosSignIdentity }
  if request.macosSandbox { packageConfig.sandbox = true }
  if request.macosEntitlements != "" { packageConfig.entitlementsPath = absolute(request.macosEntitlements)! }
  archivePath := driverOutputPath(distDirectory, macOSPackageArchiveName(project.macosApp!.executableName, project.macosApp!.version))
  _ := signAndArchiveMacOSApp(appPath, archivePath, packageConfig, outputDirectory) else error {
    println("error: " + error)
    return 1
  }
  println("Package: " + archivePath)
  return 0
}
