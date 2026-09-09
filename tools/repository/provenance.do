import { EntryKind, exists, readDir } from "std/fs"
import { cleanRevision, jsonFile, jsonString, path, require, sorted } from "./common"

// A stdlib workspace may be one checkout or a directory of std/* checkouts.
export function stdlibRevisions(root: string): Result<JsonObject, string> {
  result: JsonObject := {}
  if exists(path(root, ".git")) {
    try revision := cleanRevision(root)
    result.set(".", revision)
    return Success(result)
  }
  entries := readDir(root) else { return Failure("Cannot read stdlib workspace: " + root) }
  names: string[] := []
  for entry of entries { if entry.kind == EntryKind.Directory { names.push(entry.name) } }
  let count = 0
  for name of sorted(names) {
    directory := path(root, name)
    manifestPath := path(directory, "doof.json")
    if !exists(manifestPath) { continue }
    try manifest := jsonFile(manifestPath)
    try packageName := jsonString(manifest, "name")
    if !packageName.startsWith("std/") { continue }
    try require(packageName == "std/" + name, "Standard package directory/name mismatch: " + directory)
    try require(exists(path(directory, ".git")), "Standard package must be a Git checkout: " + directory)
    try revision := cleanRevision(directory)
    result.set(packageName, revision)
    count += 1
  }
  try require(count > 0, "No standard package checkouts found: " + root)
  return Success(result)
}
