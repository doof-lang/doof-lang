import { Assert } from "std/assert"
import {
  driverRootLogicalPath, driverRootLogicalPrefix, frontendEmissionCacheSupported, materializeGeneratedText,
  nativeBuildOutputModeForCommand, nativeBuildOutputName, parseDependencyManifestForTarget,
  synchronizeExecutableResources,
} from "./driver"
import { NativeBuildOutputMode } from "./native-build-driver"
import { PackageResource } from "./package-manifest"
import { exists, isDirectory, metadata, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { join, tempDirectory } from "std/path"

function removeDriverTestTree(path: string): none {
  if !exists(path) { return }
  if isDirectory(path) {
    for entry of try! readDir(path) { removeDriverTestTree(join([path, entry.name])) }
  }
  try! remove(path)
}

export function testCanonicalizesStandardPackageRoots(): none {
  Assert.equal(driverRootLogicalPrefix("std/path", "/workspace/doof-stdlib/path"), "/std/path")
  Assert.equal(
    driverRootLogicalPath(
      "/workspace/doof-stdlib/path/build/.doof-tests/path_test_do/__doof_tests__.do",
      "/workspace/doof-stdlib/path",
      "std/path",
    ),
    "/std/path/build/.doof-tests/path_test_do/__doof_tests__.do",
  )
}

export function testKeepsOrdinaryPackageRootsPathBased(): none {
  Assert.equal(
    driverRootLogicalPrefix("demo", "/workspace/demo"),
    "/workspace/demo",
  )
  Assert.equal(
    driverRootLogicalPath("/workspace/demo/src/main.do", "/workspace/demo", "demo"),
    "/src/main.do",
  )
}

export function testCanonicalizesWindowsCompilerSourcePaths(): none {
  Assert.equal(
    driverRootLogicalPrefix("doof", "C:/workspace/doof-lang"),
    "/C:/workspace/doof-lang",
  )
  Assert.equal(
    driverRootLogicalPath("C:/workspace/doof-lang/src/main.do", "C:/workspace/doof-lang", "doof"),
    "/src/main.do",
  )
}

export function testCanonicalizesWindowsOrdinaryPackagePaths(): none {
  Assert.equal(driverRootLogicalPrefix("demo", "C:/workspace/demo"), "/C:/workspace/demo")
  Assert.equal(
    driverRootLogicalPath("C:/workspace/demo/main.do", "C:/workspace/demo", "demo"),
    "/C:/workspace/demo/main.do",
  )
}

export function testPlansMsvcNativeExecutableSuffixOnWindows(): none {
  Assert.equal(nativeBuildOutputName("tools/doof", "windows"), "tools-doof.exe")
  Assert.equal(nativeBuildOutputName("doof.exe", "windows"), "doof.exe")
  Assert.equal(nativeBuildOutputName("doof", "macos"), "doof")
}

export function testSelectsCommandAwareNativeBuildOutput(): none {
  Assert.equal(nativeBuildOutputModeForCommand("run"), NativeBuildOutputMode.Silent)
  for command of ["build", "profile", "test", "package"] {
    Assert.equal(nativeBuildOutputModeForCommand(command), NativeBuildOutputMode.Progress)
  }
}

export function testFrontendEmissionCacheSupportsMacOSApps(): none {
  Assert.equal(frontendEmissionCacheSupported("macos-app"), true)
  Assert.equal(frontendEmissionCacheSupported(""), true)
  Assert.equal(frontendEmissionCacheSupported("wasm"), false)
  Assert.equal(frontendEmissionCacheSupported("ios-app"), false)
}

export function testSelectsDependencyNativeInputsForRootWasmTarget(): none {
  manifest := try! parseDependencyManifestForTarget(
    "{\"name\":\"std/http\",\"build\":{\"native\":{\"macos\":{\"sourceFiles\":[\"native_http_client_apple.mm\"],\"frameworks\":[\"Foundation\"]},\"wasm\":{\"sourceFiles\":[\"native_http_client_wasm.cpp\"]}}}}",
    "/stdlib/http/doof.json",
    "/stdlib/http",
    "macos",
    "wasm",
  )

  Assert.equal(manifest.nativeBuild.sourceFiles.length, 1)
  Assert.equal(manifest.nativeBuild.sourceFiles[0], "/stdlib/http/native_http_client_wasm.cpp")
  Assert.equal(manifest.nativeBuild.frameworks.length, 0)
}

export function testDoesNotParseDependencyAsRootMacOSApp(): none {
  manifest := try! parseDependencyManifestForTarget(
    "{\"name\":\"std/game\",\"build\":{\"native\":{\"macos\":{\"frameworks\":[\"Metal\"]}}}}",
    "/stdlib/game/doof.json",
    "/stdlib/game",
    "macos",
    "macos-app",
  )

  Assert.equal(manifest.target, "")
  Assert.equal(manifest.macosApp == none, true)
  Assert.equal(manifest.nativeBuild.frameworks.length, 1)
  Assert.equal(manifest.nativeBuild.frameworks[0], "Metal")
}

export function testPreservesGeneratedHeaderTimestampWhenProjectedContentIsUnchanged(): none {
  root := join([tempDirectory(), "doof-driver-generated-header"])
  removeDriverTestTree(root)
  try! mkdir(root)
  header := join([root, "consumer.hpp"])
  materializeGeneratedText(header, "projected worldview\n")
  before := try! metadata(header)
  materializeGeneratedText(header, "projected worldview\n")
  after := try! metadata(header)
  Assert.equal(after.modifiedAt.toEpochNanos(), before.modifiedAt.toEpochNanos())
  removeDriverTestTree(root)
}

export function testSynchronizesExecutableResourceEditsAdditionsAndRemovals(): none {
  root := join([tempDirectory(), "doof-driver-resource-sync"])
  removeDriverTestTree(root)
  try! mkdir(root)
  source := join([root, "source"])
  output := join([root, "output"])
  try! mkdir(source)
  try! mkdir(output)
  keepSource := join([source, "keep.txt"])
  removedSource := join([source, "removed.txt"])
  try! writeText(keepSource, "first")
  try! writeText(removedSource, "remove")
  resources := [PackageResource { sourcePath: source, destination: "assets" }]
  statePath := join([output, ".doof-cache/v1/resources.json"])

  synchronizeExecutableResources(resources, output, statePath)
  keepOutput := join([output, "assets/keep.txt"])
  removedOutput := join([output, "assets/removed.txt"])
  before := try! metadata(keepOutput)
  synchronizeExecutableResources(resources, output, statePath)
  after := try! metadata(keepOutput)
  Assert.equal(after.modifiedAt.toEpochNanos(), before.modifiedAt.toEpochNanos())

  try! writeText(keepSource, "second value")
  try! remove(removedSource)
  try! writeText(join([source, "added.txt"]), "added")
  synchronizeExecutableResources(resources, output, statePath)
  Assert.equal(try! readText(keepOutput), "second value")
  Assert.equal(try! readText(join([output, "assets/added.txt"])), "added")
  Assert.equal(exists(removedOutput), false)
  removeDriverTestTree(root)
}
