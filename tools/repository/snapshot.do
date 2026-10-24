import { join as joinStrings } from "std/string"
// Source snapshots replay native commands captured from the final compiler.
import { sha256HexString } from "std/crypto"
import { exists, isDirectory, readBlob, readDir } from "std/fs"
import { formatJsonValue, parseJsonValue } from "std/json"
import { dirname } from "std/path"
import { command, capture, copyTree, erase, execute, files, makeDirectory, path, quote, read, require, setting, sorted, write } from "./common"

export class NativeCommand {
  compiler: string
  arguments: string[]
}
export function captureEnvironment(work: string, tool: string, environment: Map<string, string>): Result<none, string> {
  directory := path(work, "native-tools")
  records := path(work, "native-commands")
  try makeDirectory(directory); try erase(records); try makeDirectory(records)
  for name of ["clang", "clang++"] {
    wrapper := path(directory, name)
    try write(wrapper, "#!/bin/sh\nexec " + quote(tool) + " capture " + quote(name) + " \"$@\"\n")
    try command("chmod", ["+x", wrapper])
  }
  environment.set("CXX", path(directory, "clang++"))
  environment.set("DOOF_NATIVE_COMMANDS", records)
  return Success()
}
export function captureNative(arguments: string[]): Result<int, string> {
  try require(arguments.length > 0, "capture requires a native compiler")
  compiler := arguments[0]
  try require(compiler == "clang" || compiler == "clang++", "Unsupported capture compiler")
  rest: string[] := []
  for i of 1..<arguments.length { rest.push(arguments[i]) }
  for i of 0..<rest.length {
    if rest[i] == "-o" && i + 1 < rest.length {
      record := NativeCommand { compiler, arguments: rest }
      try write(path(setting("DOOF_NATIVE_COMMANDS"), sha256HexString(rest[i + 1]) + ".json"), formatJsonValue(record.toSerialObject()))
    }
  }
  nativeArgs := [compiler]
  for argument of rest { nativeArgs.push(argument) }
  try result := execute("xcrun", nativeArgs, {}, "", true)
  return Success(result.exitCode)
}
export function sourceFile(name: string): bool {
  for suffix of [".c", ".cc", ".cpp", ".h", ".hh", ".hpp", ".m", ".mm", ".inc", ".inl", ".def", ".S"] { if name.endsWith(suffix) { return true } }
  return false
}
export function canonicalText(value: string, root: string): string {
  let encoded = ""
  for i of 0..<root.length {
    c := root[i]
    encoded += if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_' then string(c) else "_"
  }
  while encoded.startsWith("_") { encoded = encoded.substring(1, encoded.length) }
  lines: string[] := []
  for line of value.split("\n") { if !line.startsWith("#line ") { lines.push(line) } }
  return joinStrings(lines.cloneReadonly(), "\n").replaceAll(encoded, "doof_source").replaceAll(root, "doof-source")
}
// Mirrors the compiler's .doof-vendor build receipt.
class VendorReceipt {
  schemaVersion: int
  packageName: string
  key: string
  fingerprint: string
  source: string
  script: string
  environment: Map<string, string>
}
export function vendorScript(name: string): bool => name.endsWith("/vendor/build.sh")
/**
 * Replays the compiler's recorded vendor builds into the same graph-relative
 * directories, before the captured compiles that include their headers.
 */
export function vendorReplayLines(graph: string, source: string): Result<string[], string> {
  lines: string[] := []
  root := path(graph, ".doof-vendor")
  if !isDirectory(root) { return Success(lines) }
  entries := readDir(root) else { return Failure("Could not list " + root) }
  names: string[] := []
  for entry of entries { names.push(entry.name) }
  for name of sorted(names) {
    receiptPath := path(root, name + "/.doof-vendor-build.json")
    if !exists(receiptPath) { continue }
    try content := read(receiptPath)
    try value := parseJsonValue(content)
    try receipt := VendorReceipt.fromSerialValue(value, true)
    target := "\"$root\"/" + quote("sources/.doof-vendor/" + name)
    lines.push("rm -rf " + target + " && mkdir -p " + target)
    lines.push("cp -R \"$root\"/" + quote("sources/" + canonicalText(receipt.source, source) + "/.") + " " + target + "/")
    if receipt.script == "" { continue }
    keys: string[] := []
    for key, _ of receipt.environment { keys.push(key) }
    let assignments = ""
    for key of sorted(keys) {
      try assigned := vendorEnvironmentValue(key, receipt.environment.get(key)!, graph, source)
      assignments += " " + key + "=" + assigned
    }
    lines.push("(cd " + target + " && env" + assignments + " sh " + quote(receipt.script) + ")")
  }
  return Success(lines)
}
export function vendorEnvironmentValue(key: string, value: string, graph: string, source: string): Result<string, string> {
  if key == "DOOF_JOBS" { return Success("\"$jobs\"") }
  if key == "CC" || key == "CXX" || key == "AR" || key == "RANLIB" {
    let name = value
    for segment of value.split("/") { name = segment }
    if name == "clang" || name == "clang++" || name == "ar" || name == "ranlib" { return Success(quote("xcrun " + name)) }
    return Failure("Unhandled vendor tool for " + key + ": " + value)
  }
  if value.contains(graph) || value.contains(source) || value.contains("/Users/") || value.contains("/private/") {
    return Failure("Nonrelocatable vendor environment " + key + ": " + value)
  }
  return Success(quote(value))
}
function outputOf(record: NativeCommand): string {
  for i of 0..<record.arguments.length { if record.arguments[i] == "-o" && i + 1 < record.arguments.length { return record.arguments[i + 1] } }
  return ""
}
export function relocateArgument(argument: string, graph: string, source: string, mapping: Map<string, string>): Result<string, string> {
  mapped := mapping.get(argument) else {
    if argument == graph { return Success("\"$root/sources\"") }
    if argument.startsWith(graph + "/") { return Success("\"$root\"/" + quote("sources/" + canonicalText(argument.substring(graph.length + 1, argument.length), source))) }
    if argument.startsWith("/") && !argument.startsWith("/System/") { return Failure("Unhandled absolute native argument: " + argument) }
    if argument.startsWith("@") || argument.contains(source) || argument.contains("/Users/") || argument.contains("/private/") { return Failure("Nonrelocatable native argument: " + argument) }
    return Success(quote(argument))
  }
  return Success("\"$root\"/" + quote(mapped))
}
export function exportGraph(graph: string, target: string, source: string, records: NativeCommand[]): Result<none, string> {
  try makeDirectory(target)
  mapping: Map<string, string> := {}
  try discovered := files(graph)
  for name of discovered {
    if name.startsWith(".") || name.contains("/.") || name.contains(".app/") { continue }
    if !sourceFile(name) && !vendorScript(name) && !name.toUpperCase().contains("LICENSE") && !name.toUpperCase().contains("COPYING") && !name.toUpperCase().contains("NOTICE") { continue }
    try original := read(path(graph, name))
    relative := canonicalText(name, source)
    content := canonicalText(original, source)
    try require(!content.contains("/Users/") && !content.contains("/home/") && !content.contains("/private/var/") && !content.contains("/private/tmp/"), "Nonrelocatable source: " + name)
    try write(path(target, "sources/" + relative), content)
    mapping.set(path(graph, name), "sources/" + relative)
  }
  compiles: Map<string, NativeCommand> := {}
  let link: NativeCommand | none = none
  for record of records {
    if record.arguments.contains("c++-header") { continue }
    let belongs = false
    for argument of record.arguments {
      if argument.startsWith(path(graph, ".doof-objects") + "/") { belongs = true }
    }
    if !belongs { continue }
    if record.arguments.contains("-c") { compiles.set(outputOf(record), record) }
    else { try require(link == none, "Multiple native link commands for " + graph); link = record }
  }
  try require(compiles.size > 0 && link != none, "Incomplete native command capture for " + graph)
  outputs: string[] := []
  for key, _ of compiles { outputs.push(key) }
  ordered := sorted(outputs)
  commands: NativeCommand[] := []
  for i of 0..<ordered.length {
    mapping.set(ordered[i], "build/" + string(i) + ".o")
    commands.push(compiles.get(ordered[i])!)
  }
  mapping.set(outputOf(link!), "build/program")
  commands.push(link!)
  lines := ["#!/bin/sh", "set -eu", "root=$(CDPATH= cd -- \"$(dirname -- \"$0\")\" && pwd)", "mkdir -p \"$root/build\""]
  lines.push("jobs=\"\${DOOF_BUILD_JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}\"")
  lines.push("case \"$jobs\" in ''|*[!0-9]*|0) echo 'DOOF_BUILD_JOBS must be positive' >&2; exit 1 ;; esac")
  lines.push("pids=''; active=0")
  lines.push("wait_batch() { status=0; for job in $pids; do wait \"$job\" || status=1; done; pids=''; active=0; [ \"$status\" -eq 0 ]; }")
  lines.push("trap 'for job in $pids; do kill \"$job\" 2>/dev/null || :; done; exit 130' HUP INT TERM")
  try vendorLines := vendorReplayLines(graph, source)
  for line of vendorLines { lines.push(line) }
  for record of commands {
    arguments: string[] := []
    let i = 0
    while i < record.arguments.length {
      argument := record.arguments[i]; i += 1
      if argument == "-MF" || argument == "-include-pch" { i += 1; continue }
      if argument == "-MMD" || argument == "-g" { continue }
      try relocated := relocateArgument(argument, graph, source, mapping)
      arguments.push(relocated)
    }
    nativeCommand := "xcrun " + quote(record.compiler) + " " + joinStrings(arguments.cloneReadonly(), " ")
    if record.arguments.contains("-c") {
      lines.push(nativeCommand + " &")
      lines.push("pids=\"$pids $!\"; active=$((active + 1)); if [ \"$active\" -ge \"$jobs\" ]; then wait_batch; fi")
    } else { lines.push("wait_batch"); lines.push(nativeCommand) }
  }
  try write(path(target, "build.sh"), joinStrings(lines.cloneReadonly(), "\n") + "\n")
  return command("chmod", ["+x", path(target, "build.sh")])
}
export function isMachO(file: string): Result<bool, string> {
  bytes := readBlob(file) else { return Failure("Could not inspect " + file) }
  if bytes.length < 4 { return Success(false) }
  return Success((bytes[0] == 207 && bytes[1] == 250 && bytes[2] == 237 && bytes[3] == 254) || (bytes[0] == 254 && bytes[1] == 237 && bytes[2] == 250 && bytes[3] == 207) || (bytes[0] == 202 && bytes[1] == 254 && bytes[2] == 186 && bytes[3] == 190))
}
export function createSnapshot(work: string, source: string, artifacts: string, destination: string, version: string): Result<none, string> {
  records: NativeCommand[] := []
  recordRoot := path(work, "native-commands")
  try names := files(recordRoot)
  for name of names {
    try content := read(path(recordRoot, name))
    try value := parseJsonValue(content)
    try record := NativeCommand.fromSerialValue(value, true)
    records.push(record)
  }
  try exportGraph(path(work, "compiler/release"), path(destination, "compiler"), source, records)
  try exportGraph(path(source, "build/debugger-app"), path(destination, "debugger"), source, records)
  resources := path(destination, "resources")
  try makeDirectory(resources)
  for name of ["doof_runtime.hpp", "doof_observer.hpp", "doof_observer_platform.hpp", "doof_wasm_test_runner_apple.swift", "doof-stdlib.tar"] { try command("cp", [path(artifacts, name), path(resources, name)]) }
  try copyTree(path(artifacts, "observer-ui"), path(resources, "observer-ui"))
  app := path(resources, "Doof Debugger.app")
  try copyTree(path(artifacts, "Doof Debugger.app"), app)
  try erase(path(app, "Contents/MacOS")); try erase(path(app, "Contents/_CodeSignature"))
  try resourceFiles := files(resources)
  for name of resourceFiles { try native := isMachO(path(resources, name)); try require(!native, "Binary in source resource tree: " + name) }
  try command("cp", [path(source, "LICENSE"), path(destination, "LICENSE")])
  try write(path(destination, "VERSION"), version + "\n")
  try write(path(destination, "README.md"), "Build on macOS arm64 with Xcode Command Line Tools: ./build.sh\nThe ad-hoc signed toolchain is written to dist/. No installed Doof, Python, Node or stdlib checkout is needed.\nThe bundled stdlib includes its authenticated package licenses.\n")
  try template := read(path(source, "tools/repository/source-build.sh.in"))
  try write(path(destination, "build.sh"), template)
  return command("chmod", ["+x", path(destination, "build.sh")])
}
