// Build/distribution policy for the editor extension. JS-runtime tests remain
// in TypeScript because they exercise VS Code, LSP and Wasm runtime APIs.
import { readTarBlob } from "std/archive"
import { BlobBuilder } from "std/blob"
import { sha256Hex, sha256HexString } from "std/crypto"
import { readBlob } from "std/fs"
import { formatJsonValue, parseJsonValue } from "std/json"
import { zstdDecompress } from "std/zstd"
import { StdlibBundleIndex } from "../../src/stdlib-bundle"
import { capture, command, copyTree, erase, files, jsonFile, jsonString, makeDirectory, path, read, require, setting, text, write } from "./common"

class EditorSource {
  path: string
  source: string
  physicalPath: string = ""
}
export function safeModulePath(name: string): bool {
  if name == "" || name.startsWith("/") || name.contains("\\") || !name.endsWith(".do") { return false }
  for part of name.split("/") { if part == "" || part == "." || part == ".." { return false } }
  return true
}
function sourceIdentity(directory: string): Result<string, string> {
  try names := files(directory)
  builder := BlobBuilder()
  for name of names {
    if name.contains("/") || !name.endsWith(".do") || name.endsWith(".test.do") { continue }
    builder.writeString(name + "\u0000")
    bytes := readBlob(path(directory, name)) else { return Failure("Could not hash " + name) }
    builder.writeBytes(bytes)
  }
  return Success(sha256Hex(builder.build()))
}
export function buildExtension(root: string): Result<none, string> {
  extension := path(root, "extensions/vscode-doof")
  for name of ["extension", "server", "worker"] {
    format := if name == "worker" then "esm" else "cjs"
    suffix := if name == "worker" then "mjs" else "cjs"
    try command(path(extension, "node_modules/.bin/esbuild"), [path(extension, "src/" + name + ".ts"), "--outfile=" + path(extension, "out/" + name + "." + suffix), "--bundle", "--platform=node", "--format=" + format, "--target=node22", "--external:vscode", "--sourcemap"])
  }
  return Success()
}
export function buildEditorService(root: string): Result<none, string> {
  stage := path(root, "build/vscode-service-package")
  artifacts := path(root, "extensions/vscode-doof/artifacts")
  try erase(path(stage, "src")); try copyTree(path(root, "src"), path(stage, "src"))
  try names := files(path(stage, "src"))
  for name of names { if name.endsWith(".test.do") { try erase(path(stage, "src/" + name)) } }
  try makeDirectory(artifacts)
  manifest: JsonObject := { name: "doof-language-service", build: { entry: "src/editor-wasm.do", target: "wasm", native: { linkerFlags: ["-sALLOW_MEMORY_GROWTH=1", "-sMAXIMUM_MEMORY=1073741824", "-sSTACK_SIZE=1048576"] } } }
  try write(path(stage, "doof.json"), formatJsonValue(manifest))
  try command("env", ["-u", "DOOF_STDLIB_ROOT", path(root, "dist/doof"), "build", stage, "-o", path(root, "build/vscode-service")], {}, root)
  try command("cp", [path(root, "build/vscode-service/doof-language-service.wasm"), path(artifacts, "service.wasm")])
  try originalManifest := jsonFile(path(root, "doof.json"))
  try version := jsonString(originalManifest, "version")
  try revision := capture("git", ["-C", root, "rev-parse", "HEAD"])
  try status := capture("git", ["-C", root, "status", "--porcelain", "--", "src"])
  try compilerSourceSha256 := sourceIdentity(path(stage, "src"))
  wasm := readBlob(path(artifacts, "service.wasm")) else { return Failure("Missing service Wasm") }
  bundle := readBlob(path(root, "dist/doof-stdlib.tar")) else { return Failure("Missing bundled stdlib") }
  try archive := readTarBlob(bundle)
  let catalogSource = ""
  for entry of archive.entries { if entry.name == "bundle-index.json" { catalogSource = text(archive.entryData(entry)) } }
  try catalogValue := parseJsonValue(catalogSource)
  try catalog := StdlibBundleIndex.fromJsonValue(catalogValue, true)
  try require(catalog.schemaVersion == 4, "Unsupported stdlib bundle schema")
  sources: Map<string, EditorSource> := {}
  try erase(path(artifacts, "stdlib"))
  for member of catalog.members {
    if member.kind != "module" { continue }
    try require(member.packageName.startsWith("std/"), "Invalid standard package name")
    name := member.packageName.substring(4, member.packageName.length) + "/" + member.path
    try require(safeModulePath(name), "Invalid stdlib module path: " + name)
    let found = false
    for entry of archive.entries {
      if entry.name != member.member { continue }
      compressed := archive.entryData(entry)
      try require(sha256Hex(compressed) == member.sha256, "Stdlib member digest mismatch")
      try raw := zstdDecompress(compressed)
      try inner := readTarBlob(raw)
      for moduleEntry of inner.entries {
        if moduleEntry.name != member.path { continue }
        source := text(inner.entryData(moduleEntry))
        sources.set(name, EditorSource { path: "/std/" + name, source })
        try write(path(artifacts, "stdlib/" + name), source)
        found = true
      }
    }
    try require(found, "Missing stdlib module " + name)
  }
  ordered: string[] := []
  for name, _ of sources { ordered.push(name) }
  sortedNames := sortNames(ordered)
  sourceArray: JsonValue[] := []
  for name of sortedNames { try source := sources.get(name); sourceArray.push(source.toJsonObject()) }
  serialized := formatJsonValue(sourceArray)
  try write(path(artifacts, "stdlib.json"), serialized)
  metadata: JsonObject := { version, compilerSourceSha256, dirty: status != "", wasmSha256: sha256Hex(wasm), revision, stdlibBundleDigest: catalog.bundleDigest, stdlibSha256: sha256HexString(serialized) }
  return write(path(artifacts, "service-version.json"), formatJsonValue(metadata) + "\n")
}
import { sorted as sortNames } from "./common"
export function verifyEditorArtifacts(root: string): Result<none, string> {
  artifacts := path(root, "extensions/vscode-doof/artifacts")
  try metadata := jsonFile(path(artifacts, "service-version.json"))
  bytes := readBlob(path(artifacts, "service.wasm")) else { return Failure("Missing service.wasm") }
  try expectedWasm := jsonString(metadata, "wasmSha256")
  try require(sha256Hex(bytes) == expectedWasm, "Wasm identity mismatch; rebuild the service")
  try serialized := read(path(artifacts, "stdlib.json"))
  try expectedStdlib := jsonString(metadata, "stdlibSha256")
  try require(sha256HexString(serialized) == expectedStdlib, "Stdlib identity mismatch")
  try value := parseJsonValue(serialized)
  array := value as JsonValue[] else { return Failure("Invalid stdlib source list") }
  for item of array {
    try source := EditorSource.fromJsonValue(item, true)
    try require(source.path.startsWith("/std/"), "Invalid virtual stdlib path")
    name := source.path.substring(5, source.path.length)
    try require(safeModulePath(name), "Unsafe stdlib source path")
    try actual := read(path(artifacts, "stdlib/" + name))
    try require(actual == source.source, "Bundled source mismatch: " + name)
  }
  try identity := sourceIdentity(path(root, "src"))
  try expectedSource := jsonString(metadata, "compilerSourceSha256")
  try require(identity == expectedSource, "Compiler sources changed; rebuild the service")
  try manifest := jsonFile(path(root, "doof.json"))
  try currentVersion := jsonString(manifest, "version"); try expectedVersion := jsonString(metadata, "version")
  try require(currentVersion == expectedVersion, "Service version mismatch")
  println("Wasm, compiler sources and bundled stdlib identities verified")
  return Success()
}
