// Native macOS bundle, Mach-O embedding, signing, and archive boundary.
//
// The generic compiler driver delegates here after linking. This module owns
// Apple tool invocation and filesystem materialization; macos-app.do retains
// the deterministic metadata and command-argument model.

import { collectNestedCode, copyBundleResource, copyPath, ensureDirectory, removeTree } from "./app-bundle-files"
import { MacOSAppConfig, MacOSEmbeddedLibrary, MacOSPackageConfig, macOSCodesignArguments, renderMacOSInfoPlist } from "./macos-app"
import { BlobReader } from "std/blob"
import { exists, isDirectory, remove, writeText } from "std/fs"
import { ExecOptions, platform, run } from "std/os"
import { basename, dirname, join } from "std/path"

readonly MAX_MACOS_COMMAND_OUTPUT_BYTES = 262144L
readonly MACOS_NESTED_BUNDLE_EXTENSIONS = [".framework", ".appex", ".xpc"]

class MacOSCommandResult {
  exitCode: int
  output: readonly byte[] = []
  error: string = ""
}

function hostPlatform(): string {
  value := platform()
  return if value == "darwin" then "macos" else value
}

function outputPath(directory: string, name: string): string => join([directory, name])
function parentPath(path: string): string => dirname(path)
function fileName(path: string): string => basename(path)

function runMacOSCommand(command: string, arguments: string[]): MacOSCommandResult {
  executed := run(command, arguments, ExecOptions {
    withStdin: false,
    mergeStderrIntoStdout: true,
    maxOutputBytes: MAX_MACOS_COMMAND_OUTPUT_BYTES,
  }) else error {
    return MacOSCommandResult { exitCode: -1, error }
  }
  return MacOSCommandResult { exitCode: executed.exitCode, output: executed.stdout }
}

function runRequiredCommand(command: string, arguments: string[], description: string): Result<none, string> {
  result := runMacOSCommand(command, arguments)
  if result.exitCode != 0 {
    output := if result.error != "" then result.error else BlobReader(result.output).readString(long(result.output.length))
    return Failure(description + " failed: " + output)
  }
  return Success()
}

function generateMacOSIcon(iconPath: string, destinationPath: string, workRoot: string): Result<none, string> {
  iconset := outputPath(workRoot, ".doof-app.iconset")
  removeTree(iconset)
  ensureDirectory(iconset)
  readonly sizes = [16, 32, 32, 64, 128, 256, 256, 512, 512, 1024]
  readonly names = [
    "icon_16x16.png", "icon_16x16@2x.png", "icon_32x32.png", "icon_32x32@2x.png",
    "icon_128x128.png", "icon_128x128@2x.png", "icon_256x256.png", "icon_256x256@2x.png",
    "icon_512x512.png", "icon_512x512@2x.png",
  ]
  for index of 0..<sizes.length {
    try runRequiredCommand("sips", ["-z", string(sizes[index]), string(sizes[index]), iconPath, "--out", outputPath(iconset, names[index])], "macOS icon resize")
  }
  result := runRequiredCommand("iconutil", ["-c", "icns", iconset, "-o", destinationPath], "macOS icon generation")
  removeTree(iconset)
  return result
}

class EmbeddedCode {
  sourcePath: string
  bundledRoot: string
  bundledPath: string
  bundleReference: string
  installId: string = ""
}

function commandText(command: string, arguments: string[], description: string): Result<string, string> {
  result := runMacOSCommand(command, arguments)
  if result.exitCode != 0 {
    output := if result.error != "" then result.error else BlobReader(result.output).readString(long(result.output.length))
    return Failure(description + " failed: " + output)
  }
  return Success(BlobReader(result.output).readString(long(result.output.length)))
}

function resolveEmbeddedLibrary(name: string, libraryPaths: string[], buildDirectory: string): Result<string, string> {
  readonly candidates = ["lib" + name + ".dylib", name + ".dylib", "lib" + name + ".so", name + ".so", name + ".framework"]
  for libraryPath of libraryPaths {
    resolvedRoot := if libraryPath.startsWith("/") then libraryPath else outputPath(buildDirectory, libraryPath)
    for candidate of candidates {
      candidatePath := outputPath(resolvedRoot, candidate)
      if exists(candidatePath) { return Success(candidatePath) }
    }
  }
  return Failure("Could not resolve embedded linked library \"" + name + "\" in configured library paths")
}

function firstNonemptyOutputLine(output: string): string {
  for line of output.split("\n") {
    let start = 0
    while start < line.length && (line.substring(start, start + 1) == " " || line.substring(start, start + 1) == "\t") { start = start + 1 }
    if start < line.length { return line.substring(start, line.length) }
  }
  return ""
}

function readMachOInstallId(path: string): Result<string, string> {
  try commandOutput := commandText("otool", ["-D", path], "reading embedded library install name")
  let first = true
  for line of commandOutput.split("\n") {
    if first { first = false; continue }
    trimmed := firstNonemptyOutputLine(line)
    if trimmed != "" { return Success(trimmed) }
  }
  return Success("")
}

function frameworkBinary(frameworkPath: string): Result<string, string> {
  nameWithExtension := fileName(frameworkPath)
  name := nameWithExtension.substring(0, nameWithExtension.length - ".framework".length)
  direct := outputPath(frameworkPath, name)
  if exists(direct) { return Success(direct) }
  versioned := outputPath(frameworkPath, "Versions/Current/" + name)
  if exists(versioned) { return Success(versioned) }
  return Failure("Could not find executable in embedded framework: " + frameworkPath)
}

function frameworkReference(frameworkName: string, installId: string, bundledBinary: string, bundledRoot: string): string {
  marker := frameworkName + "/"
  for index of 0..<(installId.length - marker.length + 1) {
    if installId.substring(index, index + marker.length) == marker {
      return "@rpath/" + frameworkName + "/" + installId.substring(index + marker.length, installId.length)
    }
  }
  prefix := if bundledRoot.endsWith("/") then bundledRoot else bundledRoot + "/"
  relative := if bundledBinary.startsWith(prefix) then bundledBinary.substring(prefix.length, bundledBinary.length) else fileName(bundledBinary)
  return "@rpath/" + frameworkName + "/" + relative
}

function planEmbeddedCode(sourcePath: string, frameworksDirectory: string): Result<EmbeddedCode, string> {
  if !exists(sourcePath) { return Failure("Embedded library not found: " + sourcePath) }
  if sourcePath.endsWith(".framework") {
    if !isDirectory(sourcePath) { return Failure("Embedded framework must be a directory: " + sourcePath) }
    try sourceBinary := frameworkBinary(sourcePath)
    try installId := readMachOInstallId(sourceBinary)
    frameworkName := fileName(sourcePath)
    bundledRoot := outputPath(frameworksDirectory, frameworkName)
    sourcePrefix := if sourcePath.endsWith("/") then sourcePath else sourcePath + "/"
    relativeBinary := sourceBinary.substring(sourcePrefix.length, sourceBinary.length)
    bundledPath := outputPath(bundledRoot, relativeBinary)
    return Success(EmbeddedCode {
      sourcePath, bundledRoot, bundledPath,
      bundleReference: frameworkReference(frameworkName, installId, bundledPath, bundledRoot),
      installId,
    })
  }
  if !sourcePath.endsWith(".dylib") && !sourcePath.endsWith(".so") {
    return Failure("Embedded library must be a .dylib, .so, or .framework: " + sourcePath)
  }
  try installId := readMachOInstallId(sourcePath)
  destinationName := if installId == "" then fileName(sourcePath) else fileName(installId)
  bundledPath := outputPath(frameworksDirectory, destinationName)
  return Success(EmbeddedCode {
    sourcePath,
    bundledRoot: bundledPath,
    bundledPath,
    bundleReference: "@rpath/" + destinationName,
    installId,
  })
}

function machODependencies(path: string): Result<string[], string> {
  try commandOutput := commandText("otool", ["-L", path], "reading Mach-O dependencies")
  let dependencies: string[] = []
  let first = true
  for line of commandOutput.split("\n") {
    if first { first = false; continue }
    trimmed := firstNonemptyOutputLine(line)
    if trimmed == "" { continue }
    let end = 0
    while end < trimmed.length && trimmed.substring(end, end + 1) != " " && trimmed.substring(end, end + 1) != "\t" { end = end + 1 }
    if end > 0 { dependencies.push(trimmed.substring(0, end)) }
  }
  return Success(dependencies)
}

function isSystemMachODependency(path: string): bool {
  return path.startsWith("/System/Library/") || path.startsWith("/usr/lib/")
}

function embeddedDependency(dependency: string, embedded: EmbeddedCode[]): EmbeddedCode | none {
  for code of embedded {
    if dependency == code.bundleReference || dependency == code.sourcePath || dependency == code.installId ||
      fileName(dependency) == fileName(code.bundleReference) { return code }
  }
  return none
}

function rewriteEmbeddedDependencies(codePath: string, embedded: EmbeddedCode[]): Result<none, string> {
  try dependencies := machODependencies(codePath)
  for dependency of dependencies {
    if isSystemMachODependency(dependency) { continue }
    target := embeddedDependency(dependency, embedded)
    if target == none {
      return Failure("Mach-O file " + codePath + " references non-system dependency " + dependency + ", which is not listed in embeddedLibraries")
    }
    if dependency != target!.bundleReference {
      try runRequiredCommand("install_name_tool", ["-change", dependency, target!.bundleReference, codePath], "rewriting embedded library dependency")
    }
  }
  return Success()
}

function ensureMachORPath(codePath: string, rpath: string): Result<none, string> {
  try loadCommands := commandText("otool", ["-l", codePath], "reading Mach-O rpaths")
  if loadCommands.contains("path " + rpath + " ") { return Success() }
  return runRequiredCommand("install_name_tool", ["-add_rpath", rpath, codePath], "adding bundled library rpath")
}

function embedMacOSLibraries(
  executablePath: string,
  config: MacOSAppConfig,
  libraryPaths: string[],
  buildDirectory: string,
  contentsDirectory: string,
): Result<none, string> {
  if config.embeddedLibraries.length == 0 { return Success() }
  frameworksDirectory := outputPath(contentsDirectory, "Frameworks")
  ensureDirectory(frameworksDirectory)
  let embedded: EmbeddedCode[] = []
  let destinations: string[] = []
  for entry of config.embeddedLibraries {
    let sourcePath = entry.path
    if sourcePath == "" {
      try resolvedSourcePath := resolveEmbeddedLibrary(entry.library, libraryPaths, buildDirectory)
      sourcePath = resolvedSourcePath
    }
    try code := planEmbeddedCode(sourcePath, frameworksDirectory)
    if destinations.contains(code.bundledRoot) { return Failure("Duplicate embedded library destination: " + code.bundledRoot) }
    destinations.push(code.bundledRoot)
    removeTree(code.bundledRoot)
    copyPath(code.sourcePath, code.bundledRoot)
    if !isDirectory(code.bundledRoot) { try runRequiredCommand("chmod", ["+x", code.bundledRoot], "marking embedded library executable") }
    embedded.push(code)
  }
  try rewriteEmbeddedDependencies(executablePath, embedded)
  for code of embedded {
    try rewriteEmbeddedDependencies(code.bundledPath, embedded)
    try runRequiredCommand("install_name_tool", ["-id", code.bundleReference, code.bundledPath], "setting embedded library install name")
    try ensureMachORPath(code.bundledPath, "@loader_path")
  }
  try ensureMachORPath(executablePath, "@executable_path/../Frameworks")
  return Success()
}

export function assembleMacOSApp(
  buildDirectory: string,
  executablePath: string,
  config: MacOSAppConfig,
  libraryPaths: string[],
  vendorLibraries: string[] = [],
): Result<string, string> {
  if hostPlatform() != "macos" { return Failure("macOS app builds are only supported on macOS") }
  // Shared libraries from standard-package vendor builds embed like listed paths.
  for library of vendorLibraries {
    let listed = false
    for entry of config.embeddedLibraries { if entry.path == library { listed = true } }
    if !listed { config.embeddedLibraries.push(MacOSEmbeddedLibrary { path: library }) }
  }
  appPath := outputPath(buildDirectory, config.executableName + ".app")
  removeTree(appPath)
  contentsDirectory := outputPath(appPath, "Contents")
  macosDirectory := outputPath(contentsDirectory, "MacOS")
  resourcesDirectory := outputPath(contentsDirectory, "Resources")
  ensureDirectory(macosDirectory)
  ensureDirectory(resourcesDirectory)
  bundleExecutable := outputPath(macosDirectory, config.executableName)
  copyPath(executablePath, bundleExecutable)
  try runRequiredCommand("chmod", ["+x", bundleExecutable], "marking bundled executable")
  writeText(outputPath(contentsDirectory, "Info.plist"), renderMacOSInfoPlist(config))!
  writeText(outputPath(contentsDirectory, "PkgInfo"), "APPL????")!
  if config.iconPath != "" {
    try generateMacOSIcon(config.iconPath, outputPath(resourcesDirectory, config.executableName + ".icns"), buildDirectory)
  }
  let destinations: string[] = []
  for resource of config.resources {
    try copyBundleResource(resource.sourcePath, resource.destination, resourcesDirectory, destinations, "macOS")
  }
  try embedMacOSLibraries(bundleExecutable, config, libraryPaths, buildDirectory, contentsDirectory)
  let nested: string[] = []
  collectNestedCode(outputPath(contentsDirectory, "Frameworks"), MACOS_NESTED_BUNDLE_EXTENSIONS, nested)
  for path of nested {
    try runRequiredCommand("codesign", macOSCodesignArguments(path, "-", "ad-hoc"), "ad-hoc signing nested macOS code")
  }
  try runRequiredCommand("codesign", macOSCodesignArguments(appPath, "-", "ad-hoc"), "ad-hoc signing macOS app")
  return Success(appPath)
}

function developerIdIdentity(configured: string): Result<string, string> {
  if configured != "" { return Success(configured) }
  result := runMacOSCommand("security", ["find-identity", "-v", "-p", "codesigning"])
  if result.exitCode != 0 { return Failure("Could not discover Developer ID Application signing identities") }
  commandOutput := BlobReader(result.output).readString(long(result.output.length))
  let identities: string[] = []
  readonly marker = "\"Developer ID Application:"
  for line of commandOutput.split("\n") {
    let start = -1
    for index of 0..<(line.length - marker.length + 1) {
      if line.substring(index, index + marker.length) == marker { start = index + 1; break }
    }
    if start < 0 { continue }
    let end = start
    while end < line.length && line.substring(end, end + 1) != "\"" { end = end + 1 }
    if end > start { identities.push(line.substring(start, end)) }
  }
  if identities.length == 0 { return Failure("No Developer ID Application signing identity found; pass --macos-sign-identity or use --macos-signing ad-hoc") }
  if identities.length > 1 { return Failure("Multiple Developer ID Application identities found; pass --macos-sign-identity") }
  return Success(identities[0])
}

function effectiveEntitlements(config: MacOSPackageConfig, buildDirectory: string): Result<string, string> {
  if !config.sandbox { return Success(config.entitlementsPath) }
  destinationPath := outputPath(buildDirectory, ".doof-package-entitlements.plist")
  if config.entitlementsPath != "" {
    copyPath(config.entitlementsPath, destinationPath)
    sandboxValue := runMacOSCommand("plutil", ["-extract", "com.apple.security.app-sandbox", "raw", "-o", "-", destinationPath])
    if sandboxValue.exitCode == 0 {
      value := BlobReader(sandboxValue.output).readString(long(sandboxValue.output.length)).toLowerCase()
      if value.contains("false") {
        return Failure("macOS sandbox is enabled but the supplied entitlements explicitly disable it")
      }
    }
    replaced := runMacOSCommand("plutil", ["-replace", "com.apple.security.app-sandbox", "-bool", "YES", destinationPath])
    if replaced.exitCode != 0 {
      try runRequiredCommand("plutil", ["-insert", "com.apple.security.app-sandbox", "-bool", "YES", destinationPath], "enabling App Sandbox")
    }
  } else {
    writeText(destinationPath, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<plist version=\"1.0\"><dict><key>com.apple.security.app-sandbox</key><true/></dict></plist>\n")!
  }
  return Success(destinationPath)
}

/** Applies release signing, verifies the bundle, and creates the distributable zip. */
export function signAndArchiveMacOSApp(
  appPath: string,
  archivePath: string,
  config: MacOSPackageConfig,
  buildDirectory: string,
): Result<none, string> {
  let identity = "-"
  if config.signing != "ad-hoc" {
    try resolvedIdentity := developerIdIdentity(config.identity)
    identity = resolvedIdentity
  }
  try entitlementsPath := effectiveEntitlements(config, buildDirectory)
  let nested: string[] = []
  collectNestedCode(outputPath(appPath, "Contents/Frameworks"), MACOS_NESTED_BUNDLE_EXTENSIONS, nested)
  collectNestedCode(outputPath(appPath, "Contents/PlugIns"), MACOS_NESTED_BUNDLE_EXTENSIONS, nested)
  collectNestedCode(outputPath(appPath, "Contents/XPCServices"), MACOS_NESTED_BUNDLE_EXTENSIONS, nested)
  for path of nested { try runRequiredCommand("codesign", macOSCodesignArguments(path, identity, config.signing), "signing nested macOS code") }
  try runRequiredCommand("codesign", macOSCodesignArguments(appPath, identity, config.signing, entitlementsPath), "signing macOS app")
  try runRequiredCommand("codesign", ["--verify", "--deep", "--strict", "--verbose=2", appPath], "verifying macOS app signature")
  ensureDirectory(parentPath(archivePath))
  if exists(archivePath) { remove(archivePath)! }
  try runRequiredCommand("ditto", ["-c", "-k", "--sequesterRsrc", "--keepParent", appPath, archivePath], "archiving macOS app")
  return Success()
}
