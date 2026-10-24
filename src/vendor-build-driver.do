// Filesystem and process execution for standard-package vendor builds.
//
// Planning lives in vendor-build.do. This module copies each emitted vendor
// tree into its fingerprinted build directory, runs the package's script
// there, verifies the declared lib/ outputs, and records the include and
// link inputs the rest of the native build consumes.

import { NativeBuildMode, NativeVendorToolchain } from "./native-build"
import { NativeBuildPlan, NativeVendorBuild } from "./package-manifest"
import {
  VendorBuildReceipt, missingVendorOutputs, vendorBuildDirectory, vendorBuildEnvironment,
  vendorBuildFingerprint, vendorBuildPrefix, vendorBuildReceiptName, vendorBuildRoot,
  vendorScriptCommand, vendorScriptName,
} from "./vendor-build"
import { addUnique } from "./string-lists"
import { BlobReader } from "std/blob"
import { copy, copyPermissions, exists, isDirectory, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { formatJsonValue, parseJsonValue } from "std/json"
import { ExecOptions, run } from "std/os"

import isolated function hardwareConcurrency(): int from "doof_runtime.hpp" as doof::hardware_concurrency

readonly MAX_VENDOR_OUTPUT_BYTES = 1048576L

/**
 * Builds every vendor tree in the plan, or reuses a finished build with the
 * same fingerprint, then adds its include/ and lib/ outputs to the plan.
 */
export function prepareVendorBuilds(
  outputDirectory: string,
  native: NativeBuildPlan,
  toolchain: NativeVendorToolchain,
  compilerIdentity: string,
  platform: string,
  mode: NativeBuildMode,
  reportProgress: bool,
): Result<none, string> {
  environment := vendorBuildEnvironment(toolchain, platform, mode, hardwareConcurrency())
  scriptName := vendorScriptName(platform)
  for build of native.vendorBuilds {
    sourceDirectory := joinPath(outputDirectory, build.directory)
    if !isDirectory(sourceDirectory) {
      return Failure("Vendor directory for " + build.packageName + " is missing: " + sourceDirectory)
    }
    scriptPath := joinPath(sourceDirectory, scriptName)
    hasScript := exists(scriptPath)
    let scriptContent = ""
    if hasScript {
      content := readText(scriptPath) else { return Failure("Could not read " + scriptPath) }
      scriptContent = content
    }
    fingerprint := vendorBuildFingerprint(build, environment, compilerIdentity, scriptContent)
    relativeDirectory := vendorBuildDirectory(build.packageName, fingerprint)
    buildDirectory := joinPath(outputDirectory, relativeDirectory)
    if !receiptMatches(joinPath(buildDirectory, vendorBuildReceiptName), fingerprint) {
      if reportProgress { println("Building vendored " + build.packageName) }
      try runVendorBuild(build, sourceDirectory, buildDirectory, scriptName, hasScript, environment, platform)
      receipt := VendorBuildReceipt {
        schemaVersion: 1,
        packageName: build.packageName,
        key: build.key,
        fingerprint,
        source: build.directory,
        script: if hasScript then scriptName else "",
        environment,
      }
      _ := writeText(joinPath(buildDirectory, vendorBuildReceiptName), formatJsonValue(receipt.toSerialObject())) else {
        return Failure("Could not record the vendor build for " + build.packageName)
      }
    }
    try removeSiblingBuilds(outputDirectory, build.packageName, relativeDirectory)
    if isDirectory(joinPath(buildDirectory, "include")) {
      addUnique(native.includePaths, relativeDirectory + "/include")
    }
    for library of build.staticLibraries {
      addUnique(native.linkInputs, joinPath(buildDirectory, "lib/" + library))
    }
    for library of build.bundleLibraries {
      path := joinPath(buildDirectory, "lib/" + library)
      addUnique(native.linkInputs, path)
      addUnique(native.bundledLibraries, path)
    }
  }
  return Success()
}

function runVendorBuild(
  build: NativeVendorBuild,
  sourceDirectory: string,
  buildDirectory: string,
  scriptName: string,
  hasScript: bool,
  environment: Map<string, string>,
  platform: string,
): Result<none, string> {
  // A build without a receipt is incomplete; start again from the pristine tree.
  try removeTree(buildDirectory)
  try ensureDirectory(buildDirectory)
  try copyTree(sourceDirectory, buildDirectory)
  let output = ""
  if hasScript {
    command := vendorScriptCommand(platform)
    result := run(command.program, command.arguments, ExecOptions {
      cwd: buildDirectory, env: environment.cloneReadonly(), withStdin: false,
      mergeStderrIntoStdout: true, maxOutputBytes: MAX_VENDOR_OUTPUT_BYTES,
    }) else error {
      return Failure("Could not run " + scriptName + " for " + build.packageName + ": " + error)
    }
    output = BlobReader(result.stdout).readString(long(result.stdout.length)).trim()
    if result.exitCode != 0 {
      return Failure(
        "Vendor " + scriptName + " for " + build.packageName + " exited with code " + string(result.exitCode) +
          if output == "" then "" else ":\n" + output,
      )
    }
  }
  missing := missingVendorOutputs(build, (relativePath: string): bool => exists(joinPath(buildDirectory, relativePath)))
  if missing.length > 0 {
    let message = "Vendor build for " + build.packageName + " did not produce the outputs declared in build.native.vendor: "
    for index of 0..<missing.length { message += (if index == 0 then "" else ", ") + missing[index] }
    if !hasScript { message += " (the package has no vendor/" + scriptName + ")" }
    return Failure(if output == "" then message else message + "\n" + output)
  }
  return Success()
}

function receiptMatches(path: string, fingerprint: string): bool {
  if !exists(path) { return false }
  source := readText(path) else { return false }
  value := parseJsonValue(source) else { return false }
  receipt := VendorBuildReceipt.fromSerialValue(value, true) else { return false }
  return receipt.fingerprint == fingerprint
}

// Older fingerprints of the same package are unreachable once a new build
// exists; remove them so the output directory does not grow without bound.
function removeSiblingBuilds(outputDirectory: string, packageName: string, current: string): Result<none, string> {
  root := joinPath(outputDirectory, vendorBuildRoot)
  if !isDirectory(root) { return Success() }
  prefix := vendorBuildPrefix(packageName)
  entries := readDir(root) else { return Failure("Could not list " + root) }
  for entry of entries {
    relative := vendorBuildRoot + "/" + entry.name
    if entry.name.startsWith(prefix) && relative != current { try removeTree(joinPath(root, entry.name)) }
  }
  return Success()
}

function copyTree(sourcePath: string, destinationPath: string): Result<none, string> {
  if isDirectory(sourcePath) {
    try ensureDirectory(destinationPath)
    entries := readDir(sourcePath) else { return Failure("Could not list " + sourcePath) }
    for entry of entries {
      try copyTree(joinPath(sourcePath, entry.name), joinPath(destinationPath, entry.name))
    }
    return Success()
  }
  _ := copy(sourcePath, destinationPath) else { return Failure("Could not copy " + sourcePath) }
  _ := copyPermissions(sourcePath, destinationPath) else { return Failure("Could not copy permissions for " + sourcePath) }
  return Success()
}

function removeTree(path: string): Result<none, string> {
  if !exists(path) { return Success() }
  if isDirectory(path) {
    entries := readDir(path) else { return Failure("Could not list " + path) }
    for entry of entries { try removeTree(joinPath(path, entry.name)) }
  }
  _ := remove(path) else { return Failure("Could not remove " + path) }
  return Success()
}

function ensureDirectory(path: string): Result<none, string> {
  if path == "" || exists(path) { return Success() }
  parent := parentPath(path)
  if parent != path { try ensureDirectory(parent) }
  _ := mkdir(path) else { return Failure("Could not create " + path) }
  return Success()
}

function joinPath(directory: string, name: string): string {
  return if directory.endsWith("/") then directory + name else directory + "/" + name
}

function parentPath(path: string): string {
  let index = path.length - 1
  while index > 0 && path[index] != '/' { index -= 1 }
  return if index <= 0 then "/" else path.substring(0, index)
}
