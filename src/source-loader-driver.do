// Source loading for the driver.
//
// The resolver asks this module for source text only after an import is
// encountered. Bare modules come from doof.json dependencies, while local and
// std/* paths are resolved from their acquired roots. Packages reached while
// loading are recorded so native planning and caching see the same graph.

import { NativePackageInput } from "./emitter-project"
import { ModuleNamespaceMapping } from "./emitter-names"
import { ModuleAcquisition, acquiredManifestPath, acquiredModuleDiskPath, acquiredPackageForModule } from "./module-acquisition"
import { NativeBuildPlan, PackageManifest, parsePackageManifest } from "./package-manifest"
import { hostPlatform } from "./process-driver"
import { joinPath } from "./project"
import { SourceLoader } from "./resolver"
import { Diagnostic, SemanticLocation, SemanticSpan, SourceFile } from "./semantic"
import {
  StdlibBundleProvider, materializeStdlibBundlePackage, openStdlibBundle, stdlibBundleTargetKey,
} from "./stdlib-bundle"
import { exists, readText } from "std/fs"
import { absolute, resourcePath } from "std/path"

readonly vendorOnlyInStandardPackagesMessage = "build.native.vendor is only allowed in standard packages"

function driverWithExtension(path: string): string {
  if path.endsWith(".do") { return path }
  return path + ".do"
}

function driverLogicalPath(path: string): string {
  withExtension := driverWithExtension(path)
  sourceSuffix := driverSourceSuffix(withExtension)
  if sourceSuffix != withExtension { return sourceSuffix }
  if withExtension.startsWith("/") {
    return withExtension
  }
  return "/" + withExtension
}

function driverSourceSuffix(path: string): string {
  marker := "/src/"
  let index = 0
  while index + marker.length <= path.length {
    if path.substring(index, index + marker.length) == marker {
      return path.substring(index, path.length)
    }
    index = index + 1
  }
  return path
}

class DriverSourceRoot {
  logicalPrefix: string
  diskRoot: string
}

class DriverReachedPackage {
  acquisition: ModuleAcquisition
  manifest: PackageManifest
}

class DriverSourceState {
  localRoots: DriverSourceRoot[]
  acquisitions: ModuleAcquisition[]
  reachedPackages: DriverReachedPackage[]
  namespaceMappings: ModuleNamespaceMapping[]
  nativePlatform: string
  // Target whose files the bundled standard library materializes.
  stdlibTarget: string
  rootManifest: PackageManifest
  stdlibBundle: StdlibBundleProvider | none
  packageAcquisitionRoot: string
}

let configuredDriverSourceState: DriverSourceState = DriverSourceState {
  localRoots: [],
  acquisitions: [],
  reachedPackages: [],
  namespaceMappings: [],
  nativePlatform: "",
  stdlibTarget: "",
  rootManifest: PackageManifest { name: "", manifestPath: "", rootDirectory: "", nativeBuild: NativeBuildPlan {} },
  stdlibBundle: none,
  packageAcquisitionRoot: "",
}

function driverSourceDiskPath(
  logicalPath: string,
  localRoots: DriverSourceRoot[],
  acquisitions: ModuleAcquisition[],
): string {
  for root of localRoots {
    if logicalPath == root.logicalPrefix { return root.diskRoot }
    prefix := root.logicalPrefix + "/"
    if logicalPath.startsWith(prefix) {
      return joinPath(root.diskRoot, logicalPath.substring(prefix.length, logicalPath.length))
    }
  }
  acquiredPath := acquiredModuleDiskPath(logicalPath, acquisitions)
  if acquiredPath != none { return acquiredPath! }
  return logicalPath
}

function loadDriverSource(
  logicalPath: string,
  localRoots: DriverSourceRoot[],
  acquisitions: ModuleAcquisition[],
): Result<SourceFile | none, Diagnostic> {
  diskPath := driverSourceDiskPath(logicalPath, localRoots, acquisitions)
  if !exists(diskPath) { return Success(none) }
  source := readText(diskPath) else {
    return Failure(driverDiagnostic(logicalPath, "Could not read source file ${diskPath}"))
  }
  return Success(SourceFile { path: logicalPath, physicalPath: diskPath, source })
}

function configuredDriverSource(logicalPath: string): Result<SourceFile | none, Diagnostic> {
  if logicalPath.startsWith("/std/") {
    _ := ensureStdPackageAcquisition(logicalPath) else error {
      return Failure(driverDiagnostic(logicalPath, error))
    }
  }
  try source := loadDriverSource(
    logicalPath,
    configuredDriverSourceState.localRoots,
    configuredDriverSourceState.acquisitions,
  )
  if source != none {
    package := acquiredPackageForLoadedSource(logicalPath, configuredDriverSourceState)
    if package != none { try registerReachedPackage(package!) }
  }
  return Success(source)
}

function acquiredPackageForLoadedSource(logicalPath: string, state: DriverSourceState): ModuleAcquisition | none {
  for root of state.localRoots {
    if logicalPath == root.logicalPrefix || logicalPath.startsWith(root.logicalPrefix + "/") { return none }
  }
  return acquiredPackageForModule(logicalPath, state.acquisitions)
}

/** Parses dependency native inputs for the root build target, not the host default. */
export function parseDependencyManifestForTarget(
  source: string,
  manifestPath: string,
  rootDirectory: string,
  nativePlatform: string,
  rootTarget: string,
): Result<PackageManifest, string> {
  // Only wasm changes dependency native-fragment selection independently of
  // the native platform. App targets belong to the root package and must not
  // make ordinary dependencies parse as application bundles.
  dependencyTarget := if rootTarget == "wasm" then "wasm" else ""
  return parsePackageManifest(source, manifestPath, rootDirectory, nativePlatform, dependencyTarget)
}

function registerReachedPackage(acquisition: ModuleAcquisition): Result<none, Diagnostic> {
  for reached of configuredDriverSourceState.reachedPackages {
    if reached.acquisition.logicalPrefix == acquisition.logicalPrefix && reached.acquisition.diskRoot == acquisition.diskRoot {
      return Success()
    }
  }

  manifestPath := acquiredManifestPath(acquisition)
  manifestSource := readText(manifestPath) else {
    return Failure(driverDiagnostic(
      manifestPath,
      "Could not read doof.json for acquired package ${acquisition.logicalPrefix} at ${manifestPath}",
    ))
  }
  manifest := parseDependencyManifestForTarget(
    manifestSource,
    manifestPath,
    acquisition.diskRoot,
    configuredDriverSourceState.nativePlatform,
    configuredDriverSourceState.rootManifest.target,
  ) else error {
    return Failure(driverDiagnostic(manifestPath, error))
  }
  expectedName := acquisition.logicalPrefix.substring(1, acquisition.logicalPrefix.length)
  if manifest.name != expectedName {
    return Failure(driverDiagnostic(
      manifestPath,
      "Package " + acquisition.logicalPrefix + " must declare name \"" + expectedName + "\", got \"" + manifest.name + "\"",
    ))
  }
  if manifest.nativeBuild.vendorBuilds.length > 0 && !acquisition.logicalPrefix.startsWith("/std/") {
    return Failure(driverDiagnostic(manifestPath, vendorOnlyInStandardPackagesMessage))
  }
  configuredDriverSourceState.reachedPackages.push(DriverReachedPackage { acquisition, manifest })
  configuredDriverSourceState.namespaceMappings.push(ModuleNamespaceMapping {
    logicalPrefix: acquisition.logicalPrefix,
    packageName: manifest.name,
    outputRoot: driverPackageOutputRoot(acquisition.logicalPrefix),
  })
  return Success()
}

/** Maps either package-import probe shape to its bundled package identity. */
export function stdlibPackageNameForLogicalPath(logicalPath: string): string {
  remainder := logicalPath.substring(5, logicalPath.length)
  slash := remainder.indexOf("/")
  let shortName = if slash < 0 then remainder else remainder.substring(0, slash)
  if shortName.endsWith(".do") { shortName = shortName.substring(0, shortName.length - 3) }
  return "std/" + shortName
}

function ensureStdPackageAcquisition(logicalPath: string): Result<none, string> {
  if acquiredModuleDiskPath(logicalPath, configuredDriverSourceState.acquisitions) != none { return Success() }
  packageName := stdlibPackageNameForLogicalPath(logicalPath)
  provider := configuredDriverSourceState.stdlibBundle
  if provider == none {
    return Failure("Bundled standard library is unavailable while resolving " + packageName)
  }
  target := configuredDriverSourceState.stdlibTarget
  materialized := materializeStdlibBundlePackage(
    provider!, packageName, configuredDriverSourceState.packageAcquisitionRoot, stdlibBundleTargetKey(target), target,
  ) else error { return Failure("Could not materialize " + packageName + " from the bundled standard library: " + error) }
  acquisition := ModuleAcquisition { logicalPrefix: "/" + packageName, diskRoot: materialized.rootDirectory }
  configuredDriverSourceState.acquisitions.push(acquisition)
  return Success()
}

/** Makes an implicitly required standard package part of the reached graph. */
export function ensureStdPackageReached(packageName: string): Result<none, string> {
  logicalPath := "/" + packageName + "/index.do"
  try ensureStdPackageAcquisition(logicalPath)
  acquisition := acquiredPackageForModule(logicalPath, configuredDriverSourceState.acquisitions)
  if acquisition == none { return Failure("Could not resolve required standard package " + packageName) }
  _ := registerReachedPackage(acquisition!) else error { return Failure(error.message) }
  return Success()
}

function driverDiagnostic(module: string, message: string): Diagnostic {
  zero := SemanticLocation { line: 0, column: 0, offset: 0 }
  return Diagnostic {
    severity: "error",
    message,
    span: SemanticSpan { start: zero, end: zero },
    module,
  }
}

function driverSourceDiskRoot(path: string): string {
  marker := "/src/"
  let index = 0
  while index + marker.length <= path.length {
    if path.substring(index, index + marker.length) == marker {
      return path.substring(0, index + marker.length - 1)
    }
    index = index + 1
  }
  return ""
}

/** Keeps extracted standard packages with the selected build output. */
export function stdlibPackageAcquisitionRoot(buildDirectory: string): string {
  return joinPath(buildDirectory, ".doof/packages")
}

export function sourceLoaderForRequest(
  entryPath: string,
  stdlibRoot: string,
  namespaceMappings: ModuleNamespaceMapping[],
  rootManifest: PackageManifest,
  buildDirectory: string,
  nativePlatform: string = "",
  stdlibTarget: string = "",
): Result<SourceLoader, string> {
  let localRoots: DriverSourceRoot[] = []
  rootLogicalPrefix := driverRootLogicalPrefix(rootManifest.name, rootManifest.rootDirectory)
  // Keep an explicit root mapping even when POSIX logical paths happen to be
  // directly readable disk paths. Windows drive paths are represented with a
  // leading slash in the logical graph and must map back through this root.
  localRoots.push(DriverSourceRoot { logicalPrefix: rootLogicalPrefix, diskRoot: rootManifest.rootDirectory })
  sourceRoot := driverSourceDiskRoot(entryPath)
  if sourceRoot != "" {
    localRoots.push(DriverSourceRoot { logicalPrefix: "/src", diskRoot: sourceRoot })
  }
  let acquisitions: ModuleAcquisition[] = []
  let stdlibBundle: StdlibBundleProvider | none = none
  if stdlibRoot != "" {
    acquisition := ModuleAcquisition { logicalPrefix: "/std", diskRoot: absolute(stdlibRoot)!, containsPackages: true }
    acquisitions.push(acquisition)
  } else {
    bundleResourcePath := resourcePath("doof-stdlib.tar") else error {
      return Failure("Could not locate bundled standard library doof-stdlib.tar: " + error)
    }
    if !exists(bundleResourcePath) {
      return Failure("Bundled standard library is missing: " + bundleResourcePath)
    }
    opened := openStdlibBundle(bundleResourcePath) else error {
      return Failure("Could not open bundled standard library " + bundleResourcePath + ": " + error)
    }
    stdlibBundle = opened
  }
  packageAcquisitionRoot := stdlibPackageAcquisitionRoot(buildDirectory)
  platformName := if nativePlatform == "" then hostPlatform() else nativePlatform
  // A standard package checkout may be the root while its own tests run.
  if rootManifest.nativeBuild.vendorBuilds.length > 0 && !rootManifest.name.startsWith("std/") {
    return Failure(vendorOnlyInStandardPackagesMessage)
  }
  try configureDeclaredDependencies(rootManifest, rootManifest, platformName, acquisitions)
  configuredDriverSourceState = DriverSourceState {
    localRoots,
    acquisitions,
    reachedPackages: [],
    namespaceMappings,
    nativePlatform: if nativePlatform == "" then hostPlatform() else nativePlatform,
    stdlibTarget: if stdlibTarget != "" then stdlibTarget else platformName,
    rootManifest,
    stdlibBundle,
    packageAcquisitionRoot,
  }
  return Success(configuredDriverSource)
}

function configureDeclaredDependencies(
  manifest: PackageManifest,
  rootManifest: PackageManifest,
  nativePlatform: string,
  acquisitions: ModuleAcquisition[],
): Result<none, string> {
  for requested of manifest.dependencies {
    if requested.name.startsWith("std/") { continue }
    logicalPrefix := "/" + requested.name
    let diskRoot = absolute(requested.path)!
    for existing of acquisitions {
      if existing.logicalPrefix == logicalPrefix {
        if existing.diskRoot != diskRoot {
          return Failure("Package import prefix " + logicalPrefix + " resolves to multiple packages")
        }
        diskRoot = ""
      }
    }
    if diskRoot == "" { continue }
    acquisition := ModuleAcquisition { logicalPrefix, diskRoot }
    acquisitions.push(acquisition)
    dependencyManifestPath := acquiredManifestPath(acquisition)
    dependencySource := readText(dependencyManifestPath) else {
      return Failure("Could not read dependency manifest " + dependencyManifestPath)
    }
    try dependencyManifest := parseDependencyManifestForTarget(
      dependencySource,
      dependencyManifestPath,
      diskRoot,
      nativePlatform,
      rootManifest.target,
    )
    if dependencyManifest.name == "" { return Failure("Dependency package must declare a name: " + dependencyManifestPath) }
    if dependencyManifest.nativeBuild.vendorBuilds.length > 0 {
      return Failure(vendorOnlyInStandardPackagesMessage + ": " + dependencyManifestPath)
    }
    try configureDeclaredDependencies(dependencyManifest, rootManifest, nativePlatform, acquisitions)
  }
  return Success()
}

/** Names the target whose files the bundled standard library materializes. */
export function stdlibTargetForRequest(target: string, nativePlatform: string): string {
  return if target == "wasm" then "wasm" else nativePlatform
}

function driverLogicalPrefix(path: string): string {
  absolutePath := absolute(path)!
  sourceSuffix := driverSourceSuffix(absolutePath)
  if sourceSuffix != absolutePath { return sourceSuffix }
  if absolutePath.startsWith("/") { return absolutePath }
  return "/" + absolutePath
}

export function driverRootLogicalPrefix(packageName: string, rootDirectory: string): string {
  if packageName.startsWith("std/") { return "/" + packageName }
  return driverLogicalPrefix(rootDirectory)
}

export function driverRootLogicalPath(path: string, rootDirectory: string, packageName: string): string {
  if !packageName.startsWith("std/") { return driverLogicalPath(path) }
  prefix := driverRootLogicalPrefix(packageName, rootDirectory)
  absolutePath := absolute(path)!
  absoluteRoot := absolute(rootDirectory)!
  if absolutePath == absoluteRoot { return prefix }
  rootPrefix := if absoluteRoot.endsWith("/") then absoluteRoot else absoluteRoot + "/"
  if absolutePath.startsWith(rootPrefix) {
    return prefix + "/" + absolutePath.substring(rootPrefix.length, absolutePath.length)
  }
  return driverLogicalPath(absolutePath)
}

function driverPackageOutputRoot(logicalPrefix: string): string {
  let start = 0
  while start < logicalPrefix.length && logicalPrefix[start] == '/' { start = start + 1 }
  return logicalPrefix.substring(start, logicalPrefix.length)
}

export function projectNativePackages(projectRoot: string, projectManifest: PackageManifest, stdlibRoot: string = ""): NativePackageInput[] {
  let packages: NativePackageInput[] = [NativePackageInput {
    logicalPrefix: driverRootLogicalPrefix(projectManifest.name, projectRoot),
    outputRoot: "",
    manifest: projectManifest,
  }]
  if projectManifest.target == "wasm" && stdlibRoot != "" {
    jsonRoot := joinPath(stdlibRoot, "json")
    jsonManifestPath := joinPath(jsonRoot, "doof.json")
    jsonManifest := parsePackageManifest(readText(jsonManifestPath)!, jsonManifestPath, jsonRoot, "wasm")!
    packages.push(NativePackageInput {
      logicalPrefix: "/std/json",
      outputRoot: "std/json",
      manifest: jsonManifest,
    })
  }
  for reached of configuredDriverSourceState.reachedPackages {
    packages.push(NativePackageInput {
      logicalPrefix: reached.acquisition.logicalPrefix,
      outputRoot: driverPackageOutputRoot(reached.acquisition.logicalPrefix),
      manifest: reached.manifest,
    })
  }
  return packages
}

/** Identifies the configured standard library source for frontend cache fingerprints. */
export function configuredStdlibBundleFingerprint(): string {
  bundle := configuredDriverSourceState.stdlibBundle
  if bundle == none { return "override" }
  return bundle!.index.bundleDigest
}

/** Lists the manifests of packages reached while loading the current graph. */
export function reachedPackageManifestPaths(): string[] {
  let paths: string[] = []
  for reached of configuredDriverSourceState.reachedPackages { paths.push(reached.manifest.manifestPath) }
  return paths
}

/** Maps a logical module path to disk through the configured roots. */
export function configuredSourceDiskPath(logicalPath: string): string {
  return driverSourceDiskPath(
    logicalPath,
    configuredDriverSourceState.localRoots,
    configuredDriverSourceState.acquisitions,
  )
}
