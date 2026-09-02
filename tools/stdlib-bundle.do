// Builds the curated, offline standard-library source bundle shipped with a
// compiler release. The policy is deliberately empirical: the compiler owns a
// bundle index and this tool names the coarse source trees required by those
// packages rather than attempting general dependency analysis.

import { TarEntryKind, TarWriteEntry, writeTarBlob } from "std/archive"
import { BlobBuilder } from "std/blob"
import { sha256Hex, sha256HexString } from "std/crypto"
import { EntryKind, exists, readBlob, readDir, readText, writeBlob } from "std/fs"
import { formatJsonValue, parseJsonValue } from "std/json"
import { join } from "std/path"
import { zstdCompressWithLevel } from "std/zstd"

export class StdlibBundle {
  readonly data: readonly byte[]
  readonly packageCount: int
  readonly moduleCount: int
  readonly nativePackageCount: int
  readonly sourceBytes: long
  readonly bundleDigest: string
}

class DiscoveredStdlibPackage {
  readonly name: string
  readonly shortName: string
  readonly rootDirectory: string
}

class CuratedFile {
  readonly relativePath: string
  readonly data: readonly byte[]
  readonly mode: int
}

class BundleMember {
  readonly kind: string
  readonly packageName: string
  readonly logicalPath: string
  readonly memberPath: string
  readonly data: readonly byte[]
  readonly sourceBytes: long
  readonly sha256: string
}

function path(directory: string, name: string): string => join([directory, name])

function encoded(text: string): readonly byte[] {
  builder := BlobBuilder()
  builder.writeString(text)
  return builder.build()
}

function insertName(names: string[], name: string): none {
  names.push(name)
  let index = names.length - 1
  while index > 0 && names[index] < names[index - 1] {
    previous := names[index - 1]
    names[index - 1] = names[index]
    names[index] = previous
    index -= 1
  }
}

function within(relativePath: string, root: string): bool {
  return relativePath == root || relativePath.startsWith(root + "/")
}

function universalBundleTargets(): string[] {
  return ["ios-device", "ios-simulator", "linux", "macos", "wasm", "windows"]
}

function normalizedBundleTargets(targets: string[]): Result<string[], string> {
  source := if targets.length == 0 then universalBundleTargets() else targets
  let normalized: string[] = []
  for target of source {
    if !universalBundleTargets().contains(target) {
      return Failure("Unsupported stdlib bundle target " + target)
    }
    if normalized.contains(target) { return Failure("Duplicate stdlib bundle target " + target) }
    insertName(normalized, target)
  }
  return Success(normalized)
}

function isProjectOnlyRoot(relativePath: string): bool {
  first := relativePath.split("/")[0]
  return first == ".git" || first == ".github" || first == "build" ||
    first == "dist" || first == "docs" || first == "samples" || first == "tests"
}

function isProjectOnlyFile(relativePath: string): bool {
  if relativePath.contains("/") { return false }
  return relativePath == ".DS_Store" || relativePath == ".gitignore" ||
    relativePath == "README.md" || relativePath == "sample.do" ||
    relativePath == "test_support.do" || relativePath.endsWith(".test.do") ||
    relativePath.contains("_test_support.")
}

function vendorPathIncluded(packageName: string, relativePath: string, targets: string[]): bool {
  if relativePath == "vendor" { return true }
  for segment of relativePath.split("/") {
    if segment == ".doof-build" || segment == ".doof-build-work" || segment.startsWith(".doof-external") { return false }
  }

  if packageName == "std/gzip" {
    root := "vendor/zlib"
    if relativePath == root { return true }
    remainder := relativePath.substring(root.length + 1, relativePath.length)
    return relativePath.startsWith(root + "/") && !remainder.contains("/")
  }

  if packageName == "std/http" {
    if !targets.contains("linux") { return false }
    root := "vendor/curl"
    if relativePath == root { return true }
    if !relativePath.startsWith(root + "/") { return false }
    remainder := relativePath.substring(root.length + 1, relativePath.length)
    if !remainder.contains("/") { return !remainder.startsWith(".doof-external-native-") }
    return within(relativePath, root + "/CMake") || within(relativePath, root + "/include") ||
      within(relativePath, root + "/lib") || within(relativePath, root + "/m4") ||
      within(relativePath, root + "/scripts")
  }

  if packageName == "std/image" {
    root := "vendor/libwebp"
    if relativePath == root { return true }
    if !relativePath.startsWith(root + "/") { return false }
    remainder := relativePath.substring(root.length + 1, relativePath.length)
    return !remainder.contains("/") || within(relativePath, root + "/sharpyuv") ||
      within(relativePath, root + "/src/dsp") || within(relativePath, root + "/src/enc") ||
      within(relativePath, root + "/src/dec") || within(relativePath, root + "/src/utils") ||
      within(relativePath, root + "/src/webp")
  }

  if packageName == "std/js" {
    root := "vendor/quickjs"
    if !within(relativePath, root) { return false }
    return !within(relativePath, root + "/.github") && !within(relativePath, root + "/docs") &&
      !within(relativePath, root + "/examples") && !within(relativePath, root + "/gen") &&
      !within(relativePath, root + "/test262") && !within(relativePath, root + "/tests")
  }

  if packageName == "std/regex" {
    root := "vendor/pcre2"
    if relativePath == root { return true }
    if !relativePath.startsWith(root + "/") { return false }
    remainder := relativePath.substring(root.length + 1, relativePath.length)
    return !remainder.contains("/") || within(relativePath, root + "/src")
  }

  if packageName == "std/ts" {
    treeSitter := "vendor/tree-sitter"
    typescript := "vendor/tree-sitter-typescript"
    if relativePath == treeSitter || relativePath == typescript { return true }
    if relativePath.startsWith(treeSitter + "/") {
      remainder := relativePath.substring(treeSitter.length + 1, relativePath.length)
      return !remainder.contains("/") || within(relativePath, treeSitter + "/lib")
    }
    if relativePath.startsWith(typescript + "/") {
      remainder := relativePath.substring(typescript.length + 1, relativePath.length)
      return !remainder.contains("/") || within(relativePath, typescript + "/common") ||
        within(relativePath, typescript + "/typescript") || within(relativePath, typescript + "/tsx")
    }
    return false
  }

  if packageName == "std/zstd" {
    root := "vendor/zstd"
    if relativePath == root { return true }
    if !relativePath.startsWith(root + "/") { return false }
    remainder := relativePath.substring(root.length + 1, relativePath.length)
    return !remainder.contains("/") || within(relativePath, root + "/lib")
  }

  return false
}

// Exported so the fixed release policy can be covered without constructing a
// full stdlib checkout.
export function includeStdlibBundlePath(
  packageName: string,
  relativePath: string,
  targets: string[] = [],
): bool {
  if isProjectOnlyRoot(relativePath) || isProjectOnlyFile(relativePath) { return false }
  if relativePath == "vendor" || relativePath.startsWith("vendor/") {
    effectiveTargets := if targets.length == 0 then universalBundleTargets() else targets
    return vendorPathIncluded(packageName, relativePath, effectiveTargets)
  }
  return true
}

function archiveMode(packageName: string, relativePath: string): int {
  if relativePath.endsWith(".sh") { return 493 }
  if packageName == "std/http" && (
    relativePath == "vendor/curl/configure" || relativePath == "vendor/curl/compile" ||
    relativePath == "vendor/curl/config.guess" || relativePath == "vendor/curl/config.sub" ||
    relativePath == "vendor/curl/depcomp" || relativePath == "vendor/curl/install-sh" ||
    relativePath == "vendor/curl/ltmain.sh" || relativePath == "vendor/curl/missing"
  ) { return 493 }
  return 420
}

function collectFiles(
  packageName: string,
  packageRoot: string,
  relativeDirectory: string,
  files: CuratedFile[],
  targets: string[],
): Result<none, string> {
  directory := if relativeDirectory == "" then packageRoot else path(packageRoot, relativeDirectory)
  entries := readDir(directory) else { return Failure("Could not read " + directory) }
  let names: string[] = []
  for entry of entries { insertName(names, entry.name) }

  for name of names {
    relativePath := if relativeDirectory == "" then name else relativeDirectory + "/" + name
    if !includeStdlibBundlePath(packageName, relativePath, targets) { continue }
    fullPath := path(packageRoot, relativePath)
    let entryKind = EntryKind.Other
    for entry of entries { if entry.name == name { entryKind = entry.kind } }
    if entryKind == EntryKind.Directory {
      try collectFiles(packageName, packageRoot, relativePath, files, targets)
    } else if entryKind == EntryKind.File {
      data := readBlob(fullPath) else { return Failure("Could not read " + fullPath) }
      files.push(CuratedFile { relativePath, data, mode: archiveMode(packageName, relativePath) })
    } else {
      return Failure("Unsupported filesystem entry in stdlib bundle: " + fullPath)
    }
  }
  return Success()
}

function discoverStdlibPackages(stdlibRoot: string): Result<DiscoveredStdlibPackage[], string> {
  entries := readDir(stdlibRoot) else { return Failure("Could not read " + stdlibRoot) }
  let names: string[] = []
  for entry of entries { if entry.kind == EntryKind.Directory { insertName(names, entry.name) } }
  let packages: DiscoveredStdlibPackage[] = []
  for shortName of names {
    packageRoot := path(stdlibRoot, shortName)
    manifestPath := path(packageRoot, "doof.json")
    if !exists(manifestPath) { continue }
    source := readText(manifestPath) else { return Failure("Could not read " + manifestPath) }
    parsed := parseJsonValue(source) else error { return Failure("Invalid " + manifestPath + ": " + error) }
    object := parsed as JsonObject else { return Failure("Invalid " + manifestPath + ": root must be an object") }
    nameValue := object.get("name") else { continue }
    packageName := nameValue as string else { return Failure("Invalid " + manifestPath + ": name must be a string") }
    if !packageName.startsWith("std/") { continue }
    if packageName != "std/" + shortName {
      return Failure(manifestPath + " declares " + packageName + "; expected std/" + shortName)
    }
    packages.push(DiscoveredStdlibPackage { name: packageName, shortName, rootDirectory: packageRoot })
  }
  if packages.length == 0 { return Failure("No standard packages found in " + stdlibRoot) }
  return Success(packages)
}

function compressedTar(entries: TarWriteEntry[], level: int): Result<readonly byte[], string> {
  return zstdCompressWithLevel(writeTarBlob(entries.cloneReadonly()), level)
}

function requiredLicensePaths(packageName: string, targets: string[]): string[] {
  if packageName == "std/gzip" { return ["vendor/zlib/LICENSE"] }
  if packageName == "std/http" && targets.contains("linux") { return ["vendor/curl/COPYING"] }
  if packageName == "std/image" { return ["vendor/libwebp/COPYING", "vendor/libwebp/PATENTS"] }
  if packageName == "std/js" { return ["vendor/quickjs/LICENSE"] }
  if packageName == "std/regex" { return ["vendor/pcre2/LICENCE.md"] }
  if packageName == "std/ts" {
    return ["vendor/tree-sitter/LICENSE", "vendor/tree-sitter-typescript/LICENSE"]
  }
  if packageName == "std/zstd" { return ["vendor/zstd/COPYING", "vendor/zstd/LICENSE"] }
  return []
}

function validateRequiredLicenses(packageName: string, files: CuratedFile[], targets: string[]): Result<none, string> {
  for requiredPath of requiredLicensePaths(packageName, targets) {
    let found = false
    for file of files { if file.relativePath == requiredPath { found = true } }
    if !found { return Failure("Required vendored license is missing from " + packageName + ": " + requiredPath) }
  }
  return Success()
}

function addMember(
  members: BundleMember[],
  kind: string,
  packageName: string,
  logicalPath: string,
  memberPath: string,
  entries: TarWriteEntry[],
  sourceBytes: long,
  level: int,
): Result<none, string> {
  compressed := compressedTar(entries, level) else error {
    return Failure("Could not compress " + logicalPath + ": " + error)
  }
  members.push(BundleMember {
    kind, packageName, logicalPath, memberPath, data: compressed, sourceBytes,
    sha256: sha256Hex(compressed),
  })
  return Success()
}

function memberJson(member: BundleMember): JsonObject {
  let value: JsonObject = {}
  value.set("kind", member.kind)
  value.set("packageName", member.packageName)
  value.set("path", member.logicalPath)
  value.set("member", member.memberPath)
  value.set("sourceBytes", member.sourceBytes)
  value.set("compressedBytes", long(member.data.length))
  value.set("sha256", member.sha256)
  return value
}

function canonicalBundleDigest(
  packages: DiscoveredStdlibPackage[],
  members: BundleMember[],
  targets: string[],
): string {
  let canonical = "schema=4\n"
  for target of targets { canonical += "target=" + target + "\n" }
  for package_ of packages { canonical += "package=" + package_.name + "\n" }
  for member of members {
    canonical += "member=" + member.kind + "\u0000" + member.packageName + "\u0000" + member.logicalPath +
      "\u0000" + member.memberPath + "\u0000" + string(member.sourceBytes) + "\u0000" +
      string(member.data.length) + "\u0000" + member.sha256 + "\n"
  }
  for package_ of packages {
    for licensePath of requiredLicensePaths(package_.name, targets) {
      canonical += "license=" + package_.name + "\u0000" + licensePath + "\u0000native/" +
        package_.name.substring(4, package_.name.length) + ".tar.zst\n"
    }
  }
  return sha256HexString(canonical)
}

function bundleIndex(
  discovered: DiscoveredStdlibPackage[],
  level: int,
  bundleDigest: string,
  members: BundleMember[],
  targets: string[],
): readonly byte[] {
  let packages: JsonValue[] = []
  for package_ of discovered { packages.push(package_.name) }
  let targetValues: JsonValue[] = []
  for target of targets { targetValues.push(target) }
  let memberValues: JsonValue[] = []
  for member of members { memberValues.push(memberJson(member)) }
  let licenseValues: JsonValue[] = []
  for package_ of discovered {
    for licensePath of requiredLicensePaths(package_.name, targets) {
      let license: JsonObject = {}
      license.set("packageName", package_.name)
      license.set("path", licensePath)
      license.set("member", "native/" + package_.name.substring(4, package_.name.length) + ".tar.zst")
      licenseValues.push(license)
    }
  }

  let root: JsonObject = {}
  root.set("schemaVersion", 4)
  root.set("format", "doof-stdlib-tar-of-tar-zst")
  root.set("bundleDigest", bundleDigest)
  root.set("zstdLevel", level)
  root.set("targets", targetValues)
  root.set("packages", packages)
  root.set("members", memberValues)
  root.set("licenseFiles", licenseValues)
  return encoded(formatJsonValue(root) + "\n")
}

export function buildStdlibBundle(
  stdlibRoot: string,
  level: int = 9,
  targets: string[] = [],
): Result<StdlibBundle, string> {
  if level < 1 || level > 19 { return Failure("zstd level must be between 1 and 19") }
  try bundleTargets := normalizedBundleTargets(targets)
  try packages := discoverStdlibPackages(stdlibRoot)
  let members: BundleMember[] = []
  let moduleCount = 0
  let nativePackageCount = 0
  let sourceBytes = 0L

  for package_ of packages {
    shortName := package_.shortName
    packageRoot := package_.rootDirectory
    let files: CuratedFile[] = []
    try collectFiles(package_.name, packageRoot, "", files, bundleTargets)
    try validateRequiredLicenses(package_.name, files, bundleTargets)

    let nativeEntries: TarWriteEntry[] = []
    let nativeBytes = 0L
    let foundManifest = false
    for file of files {
      sourceBytes += long(file.data.length)
      if file.relativePath == "doof.json" {
        foundManifest = true
        try addMember(
          members, "manifest", package_.name, file.relativePath,
          "manifests/" + shortName + ".tar.zst",
          [TarWriteEntry { name: file.relativePath, data: file.data, mode: file.mode }],
          long(file.data.length), level,
        )
      } else if file.relativePath.endsWith(".do") {
        moduleCount += 1
        try addMember(
          members, "module", package_.name, file.relativePath,
          "modules/" + shortName + "/" + file.relativePath + ".tar.zst",
          [TarWriteEntry { name: file.relativePath, data: file.data, mode: file.mode }],
          long(file.data.length), level,
        )
      } else {
        nativeBytes += long(file.data.length)
        nativeEntries.push(TarWriteEntry { name: file.relativePath, data: file.data, mode: file.mode })
      }
    }
    if !foundManifest { return Failure("Catalog package has no curated doof.json: " + packageRoot) }
    if nativeEntries.length > 0 {
      nativePackageCount += 1
      try addMember(
        members, "native", package_.name, "", "native/" + shortName + ".tar.zst",
        nativeEntries, nativeBytes, level,
      )
    }
  }

  bundleDigest := canonicalBundleDigest(packages, members, bundleTargets)
  indexData := bundleIndex(packages, level, bundleDigest, members, bundleTargets)
  let outerEntries: TarWriteEntry[] = [
    TarWriteEntry { name: "bundle-index.json", data: indexData },
  ]
  for member of members {
    outerEntries.push(TarWriteEntry { name: member.memberPath, data: member.data })
  }
  archive := writeTarBlob(outerEntries.cloneReadonly())
  return Success(StdlibBundle {
    data: archive,
    packageCount: packages.length,
    moduleCount,
    nativePackageCount,
    sourceBytes,
    bundleDigest,
  })
}

function main(args: string[]): int {
  if args.length != 3 {
    println("usage: stdlib-bundle STDLIB_ROOT OUTPUT_TAR TARGETS")
    return 2
  }
  if exists(args[1]) {
    println("Refusing to overwrite existing output: " + args[1])
    return 1
  }
  let requestedTargets: string[] = []
  for target of args[2].split(",") { requestedTargets.push(target) }
  bundle := buildStdlibBundle(args[0], 9, requestedTargets) else error {
    println(error)
    return 1
  }
  _ := writeBlob(args[1], bundle.data) else {
    println("Could not write bundle: " + args[1])
    return 1
  }
  println(
    "Wrote " + string(bundle.packageCount) + " packages, " + string(bundle.moduleCount) +
    " modules, and " + string(bundle.nativePackageCount) + " native/resource blobs to " + args[1] +
    " (" + string(bundle.sourceBytes) + " source bytes; " + string(bundle.data.length) + " archive bytes; digest " +
    bundle.bundleDigest + ")",
  )
  return 0
}
