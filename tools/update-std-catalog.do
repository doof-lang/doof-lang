// Regenerates the immutable standard-package catalog from exact package Git
// checkouts. This replaces the retired Node maintenance script.

import { canonicalDependencyUrl } from "../src/std-catalog"
import { BlobReader } from "std/blob"
import { sha256HexString } from "std/crypto"
import { EntryKind, exists, isDirectory, readDir, readText, writeText } from "std/fs"
import { formatJsonValue, parseJsonValue } from "std/json"
import { ExecOptions, run } from "std/os"
import { join } from "std/path"

class CatalogPackage {
  name: string
  url: string
  ref: string
  version: string
  commit: string
}

function path(directory: string, name: string): string => join([directory, name])

function command(program: string, arguments: string[]): Result<string, string> {
  result := run(program, arguments, ExecOptions {
    withStdin: false,
    mergeStderrIntoStdout: true,
  }) else error {
    return Failure(program + ": " + error)
  }
  output := BlobReader(result.stdout).readString(long(result.stdout.length)).trim()
  if result.exitCode != 0 { return Failure(program + " failed: " + output) }
  return Success(output)
}

function manifestString(object: JsonObject, name: string, fallback: string = ""): Result<string, string> {
  value := object.get(name) else { return Success(fallback) }
  text := value as string else { return Failure("Manifest field " + name + " must be a string") }
  return Success(text)
}

function insertPackage(packages: CatalogPackage[], package_: CatalogPackage): none {
  packages.push(package_)
  let index = packages.length - 1
  while index > 0 && packages[index].name < packages[index - 1].name {
    previous := packages[index - 1]
    packages[index - 1] = packages[index]
    packages[index] = previous
    index -= 1
  }
}

function packageJson(package_: CatalogPackage): JsonObject {
  let value: JsonObject = {}
  value.set("name", package_.name)
  value.set("url", package_.url)
  value.set("ref", package_.ref)
  value.set("version", package_.version)
  value.set("commit", package_.commit)
  return value
}

function renderCatalog(compilerVersion: string, packages: CatalogPackage[]): string {
  let values: JsonValue[] = []
  for package_ of packages { values.push(packageJson(package_)) }

  let unsignedCatalog: JsonObject = {}
  unsignedCatalog.set("schemaVersion", 1)
  unsignedCatalog.set("compilerVersion", compilerVersion)
  unsignedCatalog.set("packages", values)
  canonical := formatJsonValue(unsignedCatalog) + "\n"

  let catalog: JsonObject = {}
  catalog.set("schemaVersion", 1)
  catalog.set("compilerVersion", compilerVersion)
  catalog.set("digest", sha256HexString(canonical))
  catalog.set("packages", values)
  return formatJsonValue(catalog) + "\n"
}

function generate(stdlibRoot: string, compilerVersion: string): Result<string, string> {
  entries := readDir(stdlibRoot) else { return Failure("Could not read " + stdlibRoot) }
  let packages: CatalogPackage[] = []

  for entry of entries {
    if entry.kind != .Directory { continue }
    packageRoot := path(stdlibRoot, entry.name)
    manifestPath := path(packageRoot, "doof.json")
    if !exists(manifestPath) { continue }

    source := readText(manifestPath) else { return Failure("Could not read " + manifestPath) }
    parsed := parseJsonValue(source) else error { return Failure("Invalid " + manifestPath + ": " + error) }
    manifest := parsed as JsonObject else { return Failure("Invalid " + manifestPath + ": root must be an object") }
    try name := manifestString(manifest, "name")
    if !name.startsWith("std/") { continue }
    expectedName := "std/" + entry.name
    if name != expectedName { return Failure(manifestPath + " declares " + name + "; expected " + expectedName) }
    if !isDirectory(path(packageRoot, ".git")) { return Failure("Standard package is not a Git checkout: " + packageRoot) }

    try dirty := command("git", ["-C", packageRoot, "status", "--porcelain"])
    if dirty != "" { return Failure("Standard package checkout is dirty: " + packageRoot) }
    try url := command("git", ["-C", packageRoot, "remote", "get-url", "origin"])
    try commit := command("git", ["-C", packageRoot, "rev-parse", "HEAD"])
    try ref := command("git", ["-C", packageRoot, "describe", "--tags", "--always"])
    try version := manifestString(manifest, "version", "")
    insertPackage(packages, CatalogPackage {
      name,
      url: canonicalDependencyUrl(url),
      ref,
      version,
      commit: commit.toLowerCase(),
    })
  }

  return Success(renderCatalog(compilerVersion, packages))
}

function main(args: string[]): int {
  if args.length != 3 {
    println("usage: update-std-catalog STDLIB_ROOT OUTPUT_PATH COMPILER_VERSION")
    return 2
  }
  catalog := generate(args[0], args[2]) else error {
    println(error)
    return 1
  }
  _ := writeText(args[1], catalog) else {
    println("Could not write " + args[1])
    return 1
  }
  println("Wrote standard package catalog to " + args[1])
  return 0
}
