import { BlobReader } from "std/blob"
import { sha256Hex, uuidV4 } from "std/crypto"
import { EntryKind, copy, exists, isDirectory, mkdir, readBlob, readDir, readText, writeText } from "std/fs"
import { formatJsonValue, parseJsonObject, parseJsonValue } from "std/json"
import { absolute, dirname, join, tempDirectory } from "std/path"
import { ExecOptions, ExecResult, run } from "std/os"

class CopyRule {
  readonly source: string
  readonly destination: string
}

class VendorDependency {
  readonly name: string
  readonly kind: string
  readonly url: string
  readonly destination: string
  readonly ref: string = ""
  readonly commit: string = ""
  readonly sha256: string = ""
  readonly stripComponents: int = 0
  readonly copyFiles: readonly CopyRule[] = []
  readonly keep: readonly string[] = []
}

class VendorManifest {
  readonly schemaVersion: int
  readonly dependencies: readonly VendorDependency[]
}

function path(root: string, relative: string): string => join([root, relative])
function text(bytes: readonly byte[]): string => BlobReader(bytes).readString(long(bytes.length))

function fileText(file: string): Result<string, string> {
  value := readText(file) else { return Failure("could not read " + file) }
  return Success(value)
}

function fileBlob(file: string): Result<readonly byte[], string> {
  value := readBlob(file) else { return Failure("could not read " + file) }
  return Success(value)
}

function execute(program: string, arguments: string[], cwd: string = ""): Result<ExecResult, string> {
  result := run(program, arguments, ExecOptions {
    cwd: if cwd == "" then none else cwd,
    withStdin: false,
    mergeStderrIntoStdout: true,
  }) else error { return Failure(program + " failed to start: " + error) }
  return Success(result)
}

function command(program: string, arguments: string[], cwd: string = ""): Result<none, string> {
  try result := execute(program, arguments, cwd)
  if result.exitCode != 0 { return Failure(program + " failed with status " + string(result.exitCode) + ": " + text(result.stdout)) }
  return Success()
}

function capture(program: string, arguments: string[], cwd: string = ""): Result<string, string> {
  try result := execute(program, arguments, cwd)
  if result.exitCode != 0 { return Failure(program + " failed with status " + string(result.exitCode) + ": " + text(result.stdout)) }
  return Success(text(result.stdout).trim())
}

function makeDirectory(directory: string): Result<none, string> {
  if isDirectory(directory) { return Success() }
  parent := dirname(directory)
  if parent != directory { try makeDirectory(parent) }
  _ := mkdir(directory) else { if !isDirectory(directory) { return Failure("Could not create " + directory) } }
  return Success()
}

function require(condition: bool, message: string): Result<none, string> {
  if !condition { return Failure(message) }
  return Success()
}

function dependencyPath(root: string, dependency: VendorDependency): Result<string, string> {
  try require(dependency.destination.startsWith("vendor/"), "destination must be under vendor/: " + dependency.destination)
  try require(!dependency.destination.contains(".."), "destination must not contain ..: " + dependency.destination)
  return Success(path(root, dependency.destination))
}

function metadata(dependency: VendorDependency): Map<string, SerialValue> {
  let result: Map<string, SerialValue> = {}
  result.set("schemaVersion", 1)
  result.set("name", dependency.name)
  result.set("kind", dependency.kind)
  result.set("url", dependency.url)
  result.set("destination", dependency.destination)
  if dependency.kind == "git" {
    result.set("ref", dependency.ref)
    result.set("commit", dependency.commit)
  } else {
    result.set("sha256", dependency.sha256)
  }
  return result
}

function checkMetadata(dependency: VendorDependency, destination: string): Result<none, string> {
  metadataPath := path(destination, ".doof-external.json")
  try require(exists(metadataPath), dependency.name + ": missing " + metadataPath)
  object := parseJsonObject(try! fileText(metadataPath)) else error { return Failure(dependency.name + ": invalid metadata: " + error) }
  expected := if dependency.kind == "git" then dependency.commit else dependency.sha256
  key := if dependency.kind == "git" then "commit" else "sha256"
  actual := object.get(key) as string else { return Failure(dependency.name + ": metadata is missing " + key) }
  try require(actual == expected, dependency.name + ": expected " + key + " " + expected + ", found " + actual)
  for rule of dependency.copyFiles {
    try require(exists(path(destination, rule.destination)), dependency.name + ": missing copied file " + rule.destination)
  }
  return Success()
}

function applyCopies(dependency: VendorDependency, destination: string): Result<none, string> {
  for rule of dependency.copyFiles {
    source := path(destination, rule.source)
    target := path(destination, rule.destination)
    try require(exists(source), dependency.name + ": missing copy source " + rule.source)
    try makeDirectory(dirname(target))
    _ := copy(source, target) else { return Failure("could not copy " + source) }
  }
  return Success()
}

function isKept(relative: string, keep: readonly string[]): bool {
  for prefix of keep {
    if prefix == "." || relative == prefix || relative.startsWith(prefix + "/") { return true }
  }
  return false
}

function containsKept(relative: string, keep: readonly string[]): bool {
  for prefix of keep {
    if prefix.startsWith(relative + "/") { return true }
  }
  return false
}

function pruneDirectory(directory: string, relative: string, keep: readonly string[]): Result<none, string> {
  entries := readDir(directory) else { return Failure("could not list " + directory) }
  for entry of entries {
    childRelative := if relative == "" then entry.name else relative + "/" + entry.name
    child := path(directory, entry.name)
    if childRelative == ".doof-external.json" { continue }
    if entry.kind == EntryKind.Directory {
      if isKept(childRelative, keep) { continue }
      if containsKept(childRelative, keep) {
        try pruneDirectory(child, childRelative, keep)
      } else {
        try command("rm", ["-rf", "--", child])
      }
    } else if !isKept(childRelative, keep) {
      try command("rm", ["-f", "--", child])
    }
  }
  return Success()
}

function prune(dependency: VendorDependency, destination: string): Result<none, string> {
  if dependency.keep.length == 0 { return Success() }
  return pruneDirectory(destination, "", dependency.keep)
}

function materialize(root: string, dependency: VendorDependency, mode: string): Result<none, string> {
  try destination := dependencyPath(root, dependency)
  if mode == "check" {
    try require(isDirectory(destination), dependency.name + ": missing " + dependency.destination)
    return checkMetadata(dependency, destination)
  }
  if mode == "sync" && isDirectory(destination) { return Success() }
  try command("rm", ["-rf", "--", destination])
  try makeDirectory(path(root, "vendor"))
  if dependency.kind == "git" {
    try command("git", ["clone", "--quiet", "--depth", "1", "--branch", dependency.ref, dependency.url, destination])
    try actual := capture("git", ["rev-parse", "HEAD"], destination)
    try require(actual == dependency.commit, dependency.name + ": resolved " + actual + ", expected " + dependency.commit)
    try command("rm", ["-rf", "--", path(destination, ".git")])
  } else if dependency.kind == "archive" {
    temporaryRoot := tempDirectory()
    temporary := path(temporaryRoot, "doof-vendor-" + uuidV4())
    try makeDirectory(temporary)
    archive := path(temporary, "source")
    try command("curl", ["-fsSL", dependency.url, "-o", archive])
    actual := sha256Hex(try! fileBlob(archive))
    try require(actual == dependency.sha256, dependency.name + ": downloaded " + actual + ", expected " + dependency.sha256)
    try makeDirectory(destination)
    try command("tar", ["-xf", archive, "-C", destination, "--strip-components=" + string(dependency.stripComponents)])
    try command("rm", ["-rf", "--", temporary])
  } else {
    return Failure(dependency.name + ": unsupported kind " + dependency.kind)
  }
  _ := writeText(path(destination, ".doof-external.json"), formatJsonValue(metadata(dependency).cloneReadonly()) + "\n") else {
    return Failure("could not write metadata")
  }
  try applyCopies(dependency, destination)
  return prune(dependency, destination)
}

function manifest(root: string): Result<VendorManifest, string> {
  file := path(root, "doof-vendor.json")
  try require(exists(file), "missing " + file)
  try value := parseJsonValue(try! fileText(file))
  return VendorManifest.fromSerialValue(value)
}

function processRoot(root: string, mode: string): Result<none, string> {
  try manifest := manifest(root)
  for dependency of manifest.dependencies { try materialize(root, dependency, mode) }
  println("vendor " + mode + " complete: " + root)
  return Success()
}

function roots(input: string): Result<string[], string> {
  try full := absolute(input)
  if exists(path(full, "doof-vendor.json")) { return Success([full]) }
  entries := readDir(full) else { return Failure("could not list " + full) }
  let result: string[] = []
  for entry of entries {
    if entry.kind == EntryKind.Directory && exists(path(full, entry.name + "/doof-vendor.json")) {
      result.push(path(full, entry.name))
    }
  }
  try require(result.length > 0, "no doof-vendor.json found under " + full)
  return Success(result)
}

function main(arguments: string[]): int {
  if arguments.length < 1 || arguments.length > 2 {
    println("usage: vendor <module-or-stdlib-root> [sync|refresh|check]")
    return 2
  }
  mode := if arguments.length == 2 then arguments[1] else "sync"
  if mode != "sync" && mode != "refresh" && mode != "check" {
    println("unsupported vendor mode: " + mode)
    return 2
  }
  selectedRoots := roots(arguments[0]) else error { println("error: " + error); return 1 }
  for root of selectedRoots {
    _ := processRoot(root, mode) else error { println("error: " + error); return 1 }
  }
  return 0
}
