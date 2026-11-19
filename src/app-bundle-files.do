// Shared filesystem materialization for macOS and iOS app bundles.
//
// Both Apple app drivers copy executables and doof.json resources into a
// bundle tree and discover nested code to sign. Resource glob matching and
// destination checks live here so the platforms report the same diagnostics.

import { exists, isDirectory, mkdir, readBlob, readDir, remove, writeBlob } from "std/fs"
import { basename, dirname, join } from "std/path"

function outputPath(directory: string, name: string): string => join([directory, name])

export function ensureDirectory(path: string): none {
  if path == "" || exists(path) { return }
  parent := dirname(path)
  if parent != path { ensureDirectory(parent) }
  mkdir(path)!
}

export function copyPath(sourcePath: string, destinationPath: string): none {
  if isDirectory(sourcePath) {
    ensureDirectory(destinationPath)
    for entry of readDir(sourcePath)! {
      copyPath(outputPath(sourcePath, entry.name), outputPath(destinationPath, entry.name))
    }
    return
  }
  ensureDirectory(dirname(destinationPath))
  writeBlob(destinationPath, readBlob(sourcePath)!)!
}

export function removeTree(path: string): none {
  if !exists(path) { return }
  if isDirectory(path) {
    for entry of readDir(path)! { removeTree(outputPath(path, entry.name)) }
  }
  remove(path)!
}

/** Returns the directory a resource glob is rooted at: the path before its first wildcard segment. */
export function globBaseDirectory(pattern: string): string {
  let wildcard = pattern.length
  for index of 0..<pattern.length {
    if pattern.substring(index, index + 1) == "*" { wildcard = index; break }
  }
  if wildcard == pattern.length { return dirname(pattern) }
  let slash = wildcard
  while slash > 0 && pattern.substring(slash - 1, slash) != "/" { slash -= 1 }
  return if slash <= 1 then "/" else pattern.substring(0, slash - 1)
}

/** Matches `*` within one path segment and `**` across segments. */
export function globMatches(pattern: string, value: string, patternIndex: int = 0, valueIndex: int = 0): bool {
  if patternIndex == pattern.length { return valueIndex == value.length }
  current := pattern.substring(patternIndex, patternIndex + 1)
  if current != "*" {
    return valueIndex < value.length && current == value.substring(valueIndex, valueIndex + 1) &&
      globMatches(pattern, value, patternIndex + 1, valueIndex + 1)
  }
  doubleStar := patternIndex + 1 < pattern.length && pattern.substring(patternIndex + 1, patternIndex + 2) == "*"
  nextPattern := patternIndex + if doubleStar then 2 else 1
  if globMatches(pattern, value, nextPattern, valueIndex) { return true }
  if valueIndex >= value.length { return false }
  if !doubleStar && value.substring(valueIndex, valueIndex + 1) == "/" { return false }
  return globMatches(pattern, value, patternIndex, valueIndex + 1)
}

function collectResourceFiles(path: string, baseDirectory: string, pattern: string, results: string[]): none {
  if isDirectory(path) {
    for entry of readDir(path)! { collectResourceFiles(outputPath(path, entry.name), baseDirectory, pattern, results) }
    return
  }
  prefix := if baseDirectory.endsWith("/") then baseDirectory else baseDirectory + "/"
  relative := if path.startsWith(prefix) then path.substring(prefix.length, path.length) else basename(path)
  relativePattern := if pattern.startsWith(prefix) then pattern.substring(prefix.length, pattern.length) else basename(pattern)
  if globMatches(relativePattern, relative) { results.push(path) }
}

// The leading segments of a package-relative path before its last segment, or
// before the first wildcard segment of a glob.
function relativeParent(path: string): string {
  let slash = path.length
  while slash > 0 && path.substring(slash - 1, slash) != "/" { slash -= 1 }
  return if slash == 0 then "" else path.substring(0, slash - 1)
}

function relativeGlobBase(pattern: string): string {
  let wildcard = 0
  while wildcard < pattern.length && pattern.substring(wildcard, wildcard + 1) != "*" { wildcard += 1 }
  return relativeParent(pattern.substring(0, wildcard))
}

/**
 * Copies one resource (a file, directory, or glob) under bundleRoot. Every
 * copied path is recorded in destinations so later resources cannot overwrite it.
 * destination is a directory, or with preserveSourcePath (a string-form entry)
 * the source's own package-relative path or glob.
 */
export function copyBundleResource(
  sourcePath: string,
  destination: string,
  bundleRoot: string,
  destinations: string[],
  platformName: string,
  preserveSourcePath: bool = false,
): Result<none, string> {
  let files: string[] = []
  let baseDirectory = globBaseDirectory(sourcePath)
  let destinationDirectory = destination
  if sourcePath.contains("*") {
    if preserveSourcePath { destinationDirectory = relativeGlobBase(destination) }
    if exists(baseDirectory) { collectResourceFiles(baseDirectory, baseDirectory, sourcePath, files) }
  } else if isDirectory(sourcePath) {
    collectResourceFiles(sourcePath, sourcePath, "${sourcePath}/**", files)
    baseDirectory = sourcePath
  } else if exists(sourcePath) {
    files.push(sourcePath)
    baseDirectory = dirname(sourcePath)
    if preserveSourcePath { destinationDirectory = relativeParent(destination) }
  }
  if files.length == 0 { return Failure("No files matched resource pattern: ${sourcePath}") }
  prefix := if baseDirectory.endsWith("/") then baseDirectory else baseDirectory + "/"
  destinationRoot := if destinationDirectory == "" then bundleRoot else outputPath(bundleRoot, destinationDirectory)
  for file of files {
    relative := if file.startsWith(prefix) then file.substring(prefix.length, file.length) else basename(file)
    destinationPath := outputPath(destinationRoot, relative)
    if destinations.contains(destinationPath) {
      return Failure("Duplicate ${platformName} app resource destination: ${destinationPath}")
    }
    destinations.push(destinationPath)
    copyPath(file, destinationPath)
  }
  return Success()
}

/** Collects bundled code that must be signed before its enclosing bundle, innermost first. */
export function collectNestedCode(path: string, bundleExtensions: readonly string[], results: string[]): none {
  if !exists(path) { return }
  if isDirectory(path) {
    for entry of readDir(path)! { collectNestedCode(outputPath(path, entry.name), bundleExtensions, results) }
    for extension of bundleExtensions {
      if path.endsWith(extension) { results.push(path); return }
    }
    return
  }
  if path.endsWith(".dylib") || path.endsWith(".so") { results.push(path) }
}
