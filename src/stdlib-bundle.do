// Seekable bundled-standard-library intake and workspace-local materialization.
// The driver continues to consume ordinary disk-backed ModuleAcquisition roots;
// this module owns the archive boundary and its validation.

import { TarEntry, TarEntryKind, readTarBlob, readTarEntry, scanTarFile } from "std/archive"
import { BlobReader } from "std/blob"
import { sha256Hex, sha256HexString } from "std/crypto"
import { EntryKind, exists, isDirectory, mkdir, readDir, readText, remove, rename, writeBlob, writeText } from "std/fs"
import { formatJsonValue, parseJsonValue } from "std/json"
import { ExecOptions, pid, platform, run } from "std/os"
import { dirname, join } from "std/path"
import { zstdDecompress } from "std/zstd"
readonly STDLIB_BUNDLE_SCHEMA_VERSION = 4
readonly STDLIB_BUNDLE_FORMAT = "doof-stdlib-tar-of-tar-zst"
readonly STDLIB_BUNDLE_RECEIPT = ".doof-stdlib-bundle.json"

export class StdlibBundleMember {
  kind: string
  packageName: string
  path: string
  member: string
  sourceBytes: long
  compressedBytes: long
  sha256: string
}

export class StdlibBundleLicenseFile {
  packageName: string
  path: string
  member: string
}

export class StdlibBundleIndex {
  schemaVersion: int
  format: string
  bundleDigest: string
  zstdLevel: int
  targets: string[]
  packages: string[]
  members: StdlibBundleMember[]
  licenseFiles: StdlibBundleLicenseFile[]
}

export class StdlibBundleProvider {
  path: string
  index: StdlibBundleIndex
  archiveEntries: readonly TarEntry[]
}

export class MaterializedStdlibPackage {
  rootDirectory: string
  bundleDigest: string
}

function bundlePath(directory: string, name: string): string => join([directory, name])

function safeRelativePath(value: string): bool {
  if value == "" || value.startsWith("/") || value.contains("\\") { return false }
  for segment of value.split("/") {
    if segment == "" || segment == "." || segment == ".." { return false }
  }
  return true
}

function packageShortName(packageName: string): string => packageName.substring(4, packageName.length)

function memberArchiveEntry(provider: StdlibBundleProvider, name: string): TarEntry | none {
  for entry of provider.archiveEntries { if entry.name == name { return entry } }
  return none
}

function canonicalBundleDigest(index: StdlibBundleIndex): string {
  let canonical = "schema=4\n"
  for target of index.targets { canonical += "target=" + target + "\n" }
  for packageName of index.packages { canonical += "package=" + packageName + "\n" }
  for member of index.members {
    canonical += "member=" + member.kind + "\u0000" + member.packageName + "\u0000" + member.path +
      "\u0000" + member.member + "\u0000" + string(member.sourceBytes) + "\u0000" +
      string(member.compressedBytes) + "\u0000" + member.sha256 + "\n"
  }
  for license of index.licenseFiles {
    canonical += "license=" + license.packageName + "\u0000" + license.path + "\u0000" + license.member + "\n"
  }
  return sha256HexString(canonical)
}

function validateMemberShape(member: StdlibBundleMember, packages: string[]): Result<none, string> {
  if !packages.contains(member.packageName) { return Failure("Stdlib bundle member names unknown package " + member.packageName) }
  if member.sha256.length != 64 { return Failure("Stdlib bundle member has invalid SHA-256: " + member.member) }
  if member.sourceBytes < 0L || member.compressedBytes < 0L {
    return Failure("Stdlib bundle member has invalid size: " + member.member)
  }
  shortName := packageShortName(member.packageName)
  if member.kind == "manifest" {
    if member.path != "doof.json" || member.member != "manifests/" + shortName + ".tar.zst" {
      return Failure("Stdlib bundle has invalid manifest member for " + member.packageName)
    }
  } else if member.kind == "module" {
    if !safeRelativePath(member.path) || !member.path.endsWith(".do") ||
      member.member != "modules/" + shortName + "/" + member.path + ".tar.zst" {
      return Failure("Stdlib bundle has invalid module member for " + member.packageName + ": " + member.member)
    }
  } else if member.kind == "native" {
    if member.path != "" || member.member != "native/" + shortName + ".tar.zst" {
      return Failure("Stdlib bundle has invalid native member for " + member.packageName)
    }
  } else {
    return Failure("Stdlib bundle has unsupported member kind " + member.kind)
  }
  return Success()
}

function validateBundleIndex(
  index: StdlibBundleIndex,
  entries: readonly TarEntry[],
): Result<none, string> {
  if index.schemaVersion != STDLIB_BUNDLE_SCHEMA_VERSION {
    return Failure("Unsupported stdlib bundle schema " + string(index.schemaVersion))
  }
  if index.format != STDLIB_BUNDLE_FORMAT { return Failure("Unsupported stdlib bundle format " + index.format) }
  if index.targets.length == 0 { return Failure("Stdlib bundle must support at least one target") }
  let previousTarget = ""
  let supportedTargets = ["ios-device", "ios-simulator", "linux", "macos", "wasm", "windows"]
  for target of index.targets {
    if !supportedTargets.contains(target) || (previousTarget != "" && target <= previousTarget) {
      return Failure("Stdlib bundle target list must contain sorted unique supported targets")
    }
    previousTarget = target
  }
  if index.bundleDigest.length != 64 || canonicalBundleDigest(index) != index.bundleDigest {
    return Failure("Stdlib bundle digest is invalid")
  }
  let previousPackage = ""
  for packageName of index.packages {
    if !packageName.startsWith("std/") || packageName.substring(4, packageName.length).contains("/") ||
      (previousPackage != "" && packageName <= previousPackage) {
      return Failure("Stdlib bundle package list must contain sorted unique std package names")
    }
    previousPackage = packageName
  }

  let seenOuter: string[] = []
  for entry of entries {
    if entry.kind != TarEntryKind.File { return Failure("Stdlib bundle outer archive may contain files only") }
    if seenOuter.contains(entry.name) { return Failure("Stdlib bundle has duplicate outer member " + entry.name) }
    seenOuter.push(entry.name)
  }
  if entries.length != index.members.length + 1 || entries.length == 0 || entries[0].name != "bundle-index.json" {
    return Failure("Stdlib bundle outer archive does not match its index")
  }

  let seenMembers: string[] = []
  for packageName of index.packages {
    let manifestCount = 0
    for member of index.members {
      if member.packageName == packageName && member.kind == "manifest" { manifestCount += 1 }
    }
    if manifestCount != 1 { return Failure("Stdlib bundle requires one manifest for " + packageName) }
  }
  for member of index.members {
    try validateMemberShape(member, index.packages)
    if seenMembers.contains(member.member) { return Failure("Stdlib bundle index duplicates member " + member.member) }
    seenMembers.push(member.member)
    entry := memberArchiveEntry(StdlibBundleProvider { path: "", index, archiveEntries: entries }, member.member)
    if entry == none || entry!.size != member.compressedBytes {
      return Failure("Stdlib bundle member is missing or has the wrong size: " + member.member)
    }
  }
  let seenLicenses: string[] = []
  for license of index.licenseFiles {
    if !index.packages.contains(license.packageName) || !safeRelativePath(license.path) ||
      license.member != "native/" + packageShortName(license.packageName) + ".tar.zst" {
      return Failure("Stdlib bundle has invalid license entry for " + license.packageName)
    }
    licenseKey := license.packageName + "\u0000" + license.path
    if seenLicenses.contains(licenseKey) { return Failure("Stdlib bundle duplicates required license " + license.path) }
    seenLicenses.push(licenseKey)
    let hasNativeMember = false
    for member of index.members {
      if member.packageName == license.packageName && member.kind == "native" && member.member == license.member {
        hasNativeMember = true
      }
    }
    if !hasNativeMember { return Failure("Stdlib bundle license member is missing for " + license.packageName) }
  }
  return Success()
}

export function openStdlibBundle(path: string): Result<StdlibBundleProvider, string> {
  entries := scanTarFile(path) else error { return Failure("Could not scan bundled stdlib: " + error) }
  if entries.length == 0 || entries[0].name != "bundle-index.json" {
    return Failure("Bundled stdlib is missing bundle-index.json")
  }
  indexData := readTarEntry(path, entries[0]) else error {
    return Failure("Could not read bundled stdlib index: " + error)
  }
  indexText := BlobReader(indexData).readString(long(indexData.length))
  parsed := parseJsonValue(indexText) else error { return Failure("Invalid bundled stdlib index: " + error) }
  index := StdlibBundleIndex.fromJsonValue(parsed, true) else error {
    return Failure("Invalid bundled stdlib index: " + error)
  }
  try validateBundleIndex(index, entries)
  return Success(StdlibBundleProvider { path, index, archiveEntries: entries })
}

function ensureDirectory(path: string): Result<none, string> {
  if path == "" || exists(path) { return Success() }
  parent := dirname(path)
  if parent != path { try ensureDirectory(parent) }
  _ := mkdir(path) else { return Failure("Could not create stdlib bundle directory " + path) }
  return Success()
}

function removeTree(path: string): Result<none, string> {
  if !exists(path) { return Success() }
  if isDirectory(path) {
    entries := readDir(path) else { return Failure("Could not read " + path) }
    for entry of entries { try removeTree(bundlePath(path, entry.name)) }
  }
  _ := remove(path) else { return Failure("Could not remove " + path) }
  return Success()
}

function permissionText(mode: int): string | none {
  if mode == 420 { return "644" }
  if mode == 493 { return "755" }
  return none
}

function applyMode(path: string, mode: int): Result<none, string> {
  if platform() == "windows" { return Success() }
  text := permissionText(mode)
  if text == none { return Failure("Bundled stdlib entry has unsupported file mode " + string(mode) + ": " + path) }
  result := run("chmod", [text!, path], ExecOptions { withStdin: false, mergeStderrIntoStdout: true }) else error {
    return Failure("Could not set bundled stdlib permissions for " + path + ": " + error)
  }
  if result.exitCode != 0 { return Failure("Could not set bundled stdlib permissions for " + path) }
  return Success()
}

function receiptMatches(path: string, provider: StdlibBundleProvider, packageName: string): bool {
  source := readText(path) else { return false }
  parsed := parseJsonValue(source) else { return false }
  object := parsed as JsonObject else { return false }
  digestValue := object.get("bundleDigest") else { return false }
  digest := digestValue as string else { return false }
  packageValue := object.get("packageName") else { return false }
  recordedPackage := packageValue as string else { return false }
  return digest == provider.index.bundleDigest && recordedPackage == packageName
}

function receiptSource(provider: StdlibBundleProvider, packageName: string): string {
  let value: JsonObject = {}
  value.set("schemaVersion", 1)
  value.set("bundleDigest", provider.index.bundleDigest)
  value.set("packageName", packageName)
  return formatJsonValue(value) + "\n"
}

function readCompressedMember(provider: StdlibBundleProvider, member: StdlibBundleMember): Result<readonly byte[], string> {
  entry := memberArchiveEntry(provider, member.member)
  if entry == none { return Failure("Bundled stdlib member is missing: " + member.member) }
  data := readTarEntry(provider.path, entry!) else error {
    return Failure("Could not read bundled stdlib member " + member.member + ": " + error)
  }
  if sha256Hex(data) != member.sha256 { return Failure("Bundled stdlib member failed SHA-256 validation: " + member.member) }
  return Success(data)
}

function materializeInnerArchive(
  provider: StdlibBundleProvider,
  member: StdlibBundleMember,
  staging: string,
  writtenPaths: string[],
): Result<none, string> {
  try compressed := readCompressedMember(provider, member)
  innerData := zstdDecompress(compressed) else error {
    return Failure("Could not decompress bundled stdlib member " + member.member + ": " + error)
  }
  archive := readTarBlob(innerData) else error {
    return Failure("Could not read bundled stdlib member " + member.member + ": " + error)
  }
  if member.kind != "native" && archive.entries.length != 1 {
    return Failure("Bundled stdlib " + member.kind + " member must contain exactly one file: " + member.member)
  }
  let sourceBytes = 0L
  for entry of archive.entries {
    if entry.kind != TarEntryKind.File || !safeRelativePath(entry.name) {
      return Failure("Bundled stdlib inner archive contains an unsafe entry: " + entry.name)
    }
    if member.kind != "native" && entry.name != member.path {
      return Failure("Bundled stdlib member path does not match its index: " + member.member)
    }
    if writtenPaths.contains(entry.name) { return Failure("Bundled stdlib package duplicates path " + entry.name) }
    sourceBytes += entry.size
    writtenPaths.push(entry.name)
    outputPath := bundlePath(staging, entry.name)
    try ensureDirectory(dirname(outputPath))
    _ := writeBlob(outputPath, archive.entryData(entry)) else {
      return Failure("Could not write bundled stdlib file " + outputPath)
    }
    try applyMode(outputPath, entry.mode)
  }
  if sourceBytes != member.sourceBytes {
    return Failure("Bundled stdlib member source size does not match its index: " + member.member)
  }
  return Success()
}

function packageCacheRoot(
  packagesRoot: string,
  provider: StdlibBundleProvider,
  targetKey: string,
  packageName: string,
): string {
  return bundlePath(
    bundlePath(bundlePath(bundlePath(packagesRoot, "stdlib-bundles"), provider.index.bundleDigest), targetKey),
    packageShortName(packageName),
  )
}

export function materializeStdlibBundlePackage(
  provider: StdlibBundleProvider,
  packageName: string,
  packagesRoot: string,
  targetKey: string,
  nativeTarget: string,
): Result<MaterializedStdlibPackage, string> {
  if !provider.index.packages.contains(packageName) { return Failure("Unknown standard package " + packageName) }
  if !provider.index.targets.contains(nativeTarget) {
    return Failure("Bundled standard library does not support target " + nativeTarget)
  }
  if targetKey.length != 64 { return Failure("Invalid stdlib bundle target key") }
  root := packageCacheRoot(packagesRoot, provider, targetKey, packageName)
  receiptPath := bundlePath(root, STDLIB_BUNDLE_RECEIPT)
  if isDirectory(root) && receiptMatches(receiptPath, provider, packageName) {
    return Success(MaterializedStdlibPackage {
      rootDirectory: root, bundleDigest: provider.index.bundleDigest,
    })
  }

  try ensureDirectory(dirname(root))
  if exists(root) {
    // Never remove a cache root in place: another compiler may already have
    // opened files from it. Move an incomplete root aside atomically first.
    if isDirectory(root) && receiptMatches(receiptPath, provider, packageName) {
      return Success(MaterializedStdlibPackage {
        rootDirectory: root, bundleDigest: provider.index.bundleDigest,
      })
    }
    displaced := root + ".invalid-" + string(pid())
    if exists(displaced) { try removeTree(displaced) }
    _ := rename(root, displaced) else {
      if isDirectory(root) && receiptMatches(receiptPath, provider, packageName) {
        return Success(MaterializedStdlibPackage {
          rootDirectory: root, bundleDigest: provider.index.bundleDigest,
        })
      }
      return Failure("Could not replace incomplete bundled stdlib package " + packageName)
    }
    try removeTree(displaced)
  }
  staging := root + ".staging-" + string(pid())
  if exists(staging) { try removeTree(staging) }
  try ensureDirectory(staging)
  let writtenPaths: string[] = []
  let selectedMembers = 0
  for member of provider.index.members {
    if member.packageName != packageName { continue }
    selectedMembers += 1
    _ := materializeInnerArchive(provider, member, staging, writtenPaths) else error {
      try removeTree(staging)
      return Failure(error)
    }
  }
  if selectedMembers == 0 || !writtenPaths.contains("doof.json") {
    try removeTree(staging)
    return Failure("Bundled stdlib has no materializable package " + packageName)
  }
  for license of provider.index.licenseFiles {
    if license.packageName == packageName && !writtenPaths.contains(license.path) {
      try removeTree(staging)
      return Failure("Bundled stdlib package is missing required license " + license.path)
    }
  }
  _ := writeText(bundlePath(staging, STDLIB_BUNDLE_RECEIPT), receiptSource(provider, packageName)) else {
    try removeTree(staging)
    return Failure("Could not write bundled stdlib receipt for " + packageName)
  }
  _ := rename(staging, root) else {
    if isDirectory(root) && receiptMatches(receiptPath, provider, packageName) {
      try removeTree(staging)
    } else {
      try removeTree(staging)
      return Failure("Could not finalize bundled stdlib package " + packageName)
    }
  }
  return Success(MaterializedStdlibPackage {
    rootDirectory: root, bundleDigest: provider.index.bundleDigest,
  })
}

export function stdlibBundleTargetKey(
  nativeTarget: string,
  sdkPath: string,
  targetTriple: string,
  configureHost: string,
): string {
  return sha256HexString(
    "schema=1\ntarget=" + nativeTarget + "\nsdk=" + sdkPath + "\ntriple=" + targetTriple + "\nhost=" + configureHost + "\n",
  )
}
