// Filesystem/process adapters shared by repository commands, not compiler code.
import { join as joinStrings } from "std/string"
import { BlobReader } from "std/blob"
import { uuidV4 } from "std/crypto"
import { EntryKind, File, exists, isDirectory, readText, readBlob, readDir, writeText, mkdir } from "std/fs"
import { formatJsonValue, parseJsonObject } from "std/json"
import { env, run, ExecOptions, ExecResult } from "std/os"
import { absolute, dirname, join, homeDirectory } from "std/path"

export function text(bytes: readonly byte[]): string => BlobReader(bytes).readString(long(bytes.length))
export function setting(name: string, fallback: string = ""): string {
  value := env(name) else { return fallback }
  return value
}
export function path(root: string, name: string): string => join([root, name])
export function quote(value: string): string => "'" + value.replaceAll("'", "'\"'\"'") + "'"
export function require(condition: bool, message: string): Result<none, string> {
  if !condition { return Failure(message) }
  return Success()
}
export function read(path_: string): Result<string, string> {
  value := readText(path_) else { return Failure("Could not read " + path_) }
  return Success(value)
}
export function makeDirectory(directory: string): Result<none, string> {
  if isDirectory(directory) { return Success() }
  parent := dirname(directory)
  if parent != directory { try makeDirectory(parent) }
  _ := mkdir(directory) else { if !isDirectory(directory) { return Failure("Could not create " + directory) } }
  return Success()
}
export function write(path_: string, content: string): Result<none, string> {
  try makeDirectory(dirname(path_))
  existing := readText(path_) else { return writeNew(path_, content) }
  if existing == content { return Success() }
  return writeNew(path_, content)
}
function writeNew(path_: string, content: string): Result<none, string> {
  _ := writeText(path_, content) else { return Failure("Could not write " + path_) }
  return Success()
}
export function execute(program: string, arguments: string[], environment: Map<string, string> = {}, cwd: string = "", visible: bool = false): Result<ExecResult, string> {
  return run(program, arguments, ExecOptions { env: environment.cloneReadonly(), cwd: if cwd == "" then none else cwd, inheritOutput: visible, mergeStderrIntoStdout: true, withStdin: false })
}
export function command(program: string, arguments: string[], environment: Map<string, string> = {}, cwd: string = ""): Result<none, string> {
  println("+ " + program + " " + joinStrings(arguments.cloneReadonly(), " "))
  try result := execute(program, arguments, environment, cwd, true)
  if result.exitCode != 0 { return Failure(program + " exited with status " + string(result.exitCode)) }
  return Success()
}
export function capture(program: string, arguments: string[], environment: Map<string, string> = {}, cwd: string = ""): Result<string, string> {
  try result := execute(program, arguments, environment, cwd)
  if result.exitCode != 0 { return Failure(program + " exited with status " + string(result.exitCode) + ": " + text(result.stdout)) }
  return Success(text(result.stdout).trim())
}
export function erase(directory: string): Result<none, string> {
  try require(directory != "" && directory != "/", "Refusing unsafe removal")
  return command("rm", ["-rf", "--", directory])
}
export function copyTree(source: string, destination: string): Result<none, string> {
  try makeDirectory(destination)
  return command("cp", ["-R", source + "/.", destination + "/"])
}
export function copyInputs(source: string, destination: string): Result<none, string> {
  try makeDirectory(destination)
  arguments := ["-a", "--delete"]
  for name of [".git", "build", "dist", ".doof", ".reckon", ".doof-tests", "node_modules", "__pycache__", ".DS_Store", "bootstrap"] {
    arguments.push("--exclude=" + name)
  }
  arguments.push(source + "/"); arguments.push(destination + "/")
  return command("rsync", arguments)
}
export function stableVersion(version: string): bool {
  parts := version.split(".")
  if parts.length != 3 { return false }
  for part of parts {
    if part == "" || (part.length > 1 && part[0] == '0') { return false }
    for i of 0..<part.length { if part[i] < '0' || part[i] > '9' { return false } }
  }
  return true
}
export function jsonFile(path_: string): Result<JsonObject, string> {
  try source := read(path_)
  return parseJsonObject(source)
}
export function jsonString(value: JsonObject, key: string): Result<string, string> {
  field := value.get(key) else { return Failure("Missing " + key) }
  result := field as string else { return Failure("Expected string for " + key) }
  return Success(result)
}
export function developmentVersion(root: string): Result<string, string> {
  try manifest := jsonFile(path(root, "doof.json"))
  try version := jsonString(manifest, "version")
  try require(stableVersion(version), "doof.json must contain a stable base version")
  try timestamp := capture("date", ["-u", "+%Y%m%d%H%M%S"])
  return Success(version + "-dev." + timestamp + "." + uuidV4().replaceAll("-", ""))
}
export function stamp(source: string, destination: string, version: string): Result<none, string> {
  try copyInputs(source, destination)
  for manifestPath of ["doof.json", "tools/debugger/doof.json"] {
    file := path(destination, manifestPath)
    try manifest := jsonFile(file)
    manifest.set("version", version)
    try write(file, formatJsonValue(manifest) + "\n")
  }
  file := path(destination, "src/version.do")
  try module := read(file)
  let lines: string[] = []
  let versions = 0; let stamps = 0
  for line of module.split("\n") {
    if line.startsWith("export readonly compilerVersion = ") { lines.push("export readonly compilerVersion = \"" + version + "\""); versions += 1 }
    else if line.startsWith("export readonly compilerVersionStamped = ") { lines.push("export readonly compilerVersionStamped = true"); stamps += 1 }
    else { lines.push(line) }
  }
  try require(versions == 1 && stamps == 1, "Version module must declare one version and stamp constant")
  return write(file, joinStrings(lines.cloneReadonly(), "\n"))
}
export function resolveSeed(root: string, variable: string): Result<string, string> {
  explicit := setting(variable)
  let candidate = explicit
  if candidate == "" {
    found := capture("sh", ["-c", "command -v doof"]) else { return resolveExecutable(path(root, "dist/doof")) }
    candidate = found
  }
  return resolveExecutable(candidate)
}
function resolveExecutable(candidate: string): Result<string, string> {
  try result := execute("sh", ["-c", "command -v \"$1\"", "sh", candidate])
  if result.exitCode != 0 { return Failure("No seed Doof compiler found; use install.sh or a release source snapshot") }
  return absolute(text(result.stdout).trim())
}
export function stdlibDirectory(root: string): Result<string, string> {
  try value := absolute(setting("DOOF_STDLIB_ROOT", path(dirname(root), "doof-stdlib")))
  try require(isDirectory(value), "Doof stdlib not found at " + value)
  return Success(value)
}
export function cleanRevision(root: string): Result<string, string> {
  try status := capture("git", ["-C", root, "status", "--porcelain", "--untracked-files=normal"])
  try require(status == "", "Release requires a clean checkout: " + root)
  return capture("git", ["-C", root, "rev-parse", "HEAD"])
}
export function sorted(values: string[]): string[] {
  result: string[] := []
  for value of values {
    result.push(value)
    let i = result.length - 1
    while i > 0 && result[i] < result[i - 1] { previous := result[i - 1]; result[i - 1] = result[i]; result[i] = previous; i -= 1 }
  }
  return result
}
export function files(root: string, relative: string = ""): Result<string[], string> {
  result: string[] := []
  entries := readDir(path(root, relative)) else { return Failure("Could not list " + path(root, relative)) }
  for entry of entries {
    child := if relative == "" then entry.name else relative + "/" + entry.name
    if entry.kind == .Directory {
      try children := files(root, child)
      for item of children { result.push(item) }
    } else if entry.kind == .File { result.push(child) }
    else { return Failure("Unexpected symlink or special file in build inputs: " + child) }
  }
  return Success(sorted(result))
}
export function installArtifacts(root: string, artifacts: string, home: string, version: string): Result<none, string> {
  // The pre-compiler installer owns the single transaction implementation.
  return command("sh", ["-c", "DOOF_INSTALL_LIBRARY_ONLY=1; . \"$1\"; install_artifacts \"$2\" \"$3\" \"$4\"", "sh", path(root, "install.sh"), artifacts, home, version])
}
