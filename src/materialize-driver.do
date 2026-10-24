// Content-preserving filesystem materialization of emitted projects, executable
// resources, and embedded runtime assets.

import { ProjectEmission } from "./emitter-project"
import { PackageResource } from "./package-manifest"
import { environmentValue, fileName, joinPath, parentPath } from "./project"
import {
  MaterializedResource, ResourceState, findMaterializedResource, materializedResourceIsCurrent,
  parseResourceState, renderResourceState,
} from "./resource-state"
import { copyPermissions, exists, isDirectory, metadata, mkdir, readBlob, readDir, readText, readTextResource, remove, rename, writeBlob, writeText } from "std/fs"

export function driverOutputPath(directory: string, name: string): string {
  if directory.endsWith("/") { return directory + name }
  return directory + "/" + name
}

export function ensureOutputDirectory(path: string): none {
  if path == "" || exists(path) { return }
  parent := parentPath(path)
  if parent != path { ensureOutputDirectory(parent) }
  mkdir(path)!
}

function materializeNativeCopy(sourcePath: string, outputPath: string): Result<none, string> {
  if !exists(sourcePath) {
    return Failure("Native package input " + sourcePath + " does not exist; check build.native paths in its doof.json")
  }
  if isDirectory(sourcePath) {
    ensureOutputDirectory(outputPath)
    entries := readDir(sourcePath) else { return Failure("Could not read native package directory " + sourcePath) }
    for entry of entries {
      try materializeNativeCopy(joinPath(sourcePath, entry.name), joinPath(outputPath, entry.name))
    }
    return Success()
  }
  ensureOutputDirectory(parentPath(outputPath))
  content := readBlob(sourcePath) else { return Failure("Could not read native package input " + sourcePath) }
  writeBlobIfChanged(outputPath, content)
  // Vendor build scripts and autoconf helpers run from the emitted graph.
  _ := copyPermissions(sourcePath, outputPath) else { return Failure("Could not copy permissions for " + sourcePath) }
  return Success()
}

export function writeTextIfChanged(path: string, content: string): none {
  if exists(path) {
    existing := readText(path)!
    if existing == content { return }
  }
  writeText(path, content)!
}

// Generated C++ materialization is content preserving so native dependency
// timestamps remain stable when conservative frontend invalidation reproduces
// the same projected worldview.
export function materializeGeneratedText(path: string, content: string): none {
  ensureOutputDirectory(parentPath(path))
  writeTextIfChanged(path, content)
}

function writeBlobIfChanged(path: string, content: readonly byte[]): none {
  if exists(path) {
    existing := readBlob(path)!
    if blobsEqual(existing, content) { return }
  }
  writeBlob(path, content)!
}

function blobsEqual(left: readonly byte[], right: readonly byte[]): bool {
  if left.length != right.length { return false }
  for index of 0..<left.length { if left[index] != right[index] { return false } }
  return true
}

export function materializeProject(outputDirectory: string, project: ProjectEmission): Result<none, string> {
  ensureOutputDirectory(outputDirectory)
  for module of project.modules {
    if module.reused { continue }
    materializeGeneratedText(driverOutputPath(outputDirectory, module.headerName), module.header)
    materializeGeneratedText(driverOutputPath(outputDirectory, module.sourceName), module.source)
  }
  for supportFile of project.supportFiles {
    outputPath := driverOutputPath(outputDirectory, supportFile.relativePath)
    ensureOutputDirectory(parentPath(outputPath))
    writeTextIfChanged(outputPath, supportFile.content)
  }
  for nativeCopy of project.nativeCopies {
    try materializeNativeCopy(
      nativeCopy.sourcePath,
      driverOutputPath(outputDirectory, nativeCopy.relativePath),
    )
  }
  return Success()
}

export function materializeExecutableResources(resources: PackageResource[], outputDirectory: string): none {
  for resource of resources {
    destinationRoot := driverOutputPath(outputDirectory, resource.destination)
    outputPath := if isDirectory(resource.sourcePath)
      then destinationRoot
      else driverOutputPath(destinationRoot, fileName(resource.sourcePath))
    materializeNativeCopy(resource.sourcePath, outputPath)!
  }
}

function readResourceState(path: string): ResourceState {
  if !exists(path) { return ResourceState {} }
  source := readText(path) else { return ResourceState {} }
  parsed := parseResourceState(source)
  return if parsed == none then ResourceState {} else parsed!
}

function materializeTrackedResource(
  sourcePath: string,
  outputPath: string,
  previous: ResourceState,
  next: ResourceState,
): none {
  if isDirectory(sourcePath) {
    ensureOutputDirectory(outputPath)
    for entry of readDir(sourcePath)! {
      materializeTrackedResource(joinPath(sourcePath, entry.name), joinPath(outputPath, entry.name), previous, next)
    }
    return
  }
  sourceInfo := metadata(sourcePath)!
  prior := findMaterializedResource(previous, sourcePath, outputPath)
  if exists(outputPath) && !isDirectory(outputPath) {
    outputInfo := metadata(outputPath)!
    if materializedResourceIsCurrent(
      prior,
      sourceInfo.size,
      sourceInfo.modifiedAt.toEpochNanos(),
      outputInfo.size,
      outputInfo.modifiedAt.toEpochNanos(),
    ) {
      next.files.push(prior!)
      return
    }
  }
  materializeNativeCopy(sourcePath, outputPath)!
  outputInfo := metadata(outputPath)!
  next.files.push(MaterializedResource {
    sourcePath,
    outputPath,
    sourceSize: sourceInfo.size,
    sourceModifiedNanos: sourceInfo.modifiedAt.toEpochNanos(),
    outputSize: outputInfo.size,
    outputModifiedNanos: outputInfo.modifiedAt.toEpochNanos(),
  })
}

function resourceOutputIsCurrent(files: MaterializedResource[], outputPath: string): bool {
  for file of files { if file.outputPath == outputPath { return true } }
  return false
}

export function synchronizeExecutableResources(
  resources: PackageResource[],
  outputDirectory: string,
  statePath: string,
): none {
  previous := readResourceState(statePath)
  next := ResourceState {}
  for resource of resources {
    destinationRoot := driverOutputPath(outputDirectory, resource.destination)
    outputPath := if isDirectory(resource.sourcePath)
      then destinationRoot
      else driverOutputPath(destinationRoot, fileName(resource.sourcePath))
    materializeTrackedResource(resource.sourcePath, outputPath, previous, next)
  }
  prefix := if outputDirectory.endsWith("/") then outputDirectory else outputDirectory + "/"
  for old of previous.files {
    if resourceOutputIsCurrent(next.files, old.outputPath) || !old.outputPath.startsWith(prefix) ||
      !exists(old.outputPath) || isDirectory(old.outputPath) { continue }
    remove(old.outputPath)!
  }
  ensureOutputDirectory(parentPath(statePath))
  temporaryPath := statePath + ".tmp"
  writeText(temporaryPath, renderResourceState(next))!
  rename(temporaryPath, statePath)!
}

export function materializeRuntimeHeader(outputDirectory: string): none {
  // Packaged compilers carry the canonical header as an executable resource.
  // The override remains useful when developing against an alternate runtime.
  let sourcePath = environmentValue("DOOF_RUNTIME_HEADER")
  runtimeSource := if sourcePath == ""
    then readTextResource("doof_runtime.hpp")
    else readText(sourcePath)
  writeTextIfChanged(driverOutputPath(outputDirectory, "doof_runtime.hpp"), runtimeSource!)
}

export function materializeObserverRuntime(outputDirectory: string): none {
  for name of ["doof_observer.hpp", "doof_observer_platform.hpp"] {
    content := readTextResource(name) else { panic("Could not read embedded observer runtime resource " + name) }
    writeTextIfChanged(driverOutputPath(outputDirectory, name), content)
  }
}

export function materializeObserverUi(outputDirectory: string): none {
  uiDirectory := driverOutputPath(outputDirectory, "observer-ui")
  ensureOutputDirectory(uiDirectory)
  for name of ["index.html", "app.css", "app.js"] {
    source := readTextResource("observer-ui/" + name) else {
      panic("Could not read embedded observer UI asset " + name)
    }
    writeTextIfChanged(driverOutputPath(uiDirectory, name), source)
  }
}
