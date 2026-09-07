import { Assert } from "std/assert"
import {
  phaseTimingsEnabled, compilerCacheIdentity, driverRootLogicalPath, driverRootLogicalPrefix, frontendEmissionCacheSupported, frontendStateMatches, materializeGeneratedText,
  nativeBuildOutputModeForCommand, nativeBuildOutputName, parseDependencyManifestForTarget,
  stdlibPackageNameForLogicalPath, synchronizeExecutableResources,
} from "./driver"
import { NativeBuildOutputMode } from "./native-build-driver"
import { PackageResource } from "./package-manifest"
import { FrontendCacheState } from "./frontend-cache"
import { noSourceLoader } from "./resolver"
import { readProjectSpec } from "./project"
import { projectBuildLockPath } from "./project-build-lock"
import { exists, isDirectory, metadata, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { join, tempDirectory } from "std/path"

export function testProjectBuildLockUsesSameRootForBuildAndTest(): none {
  root := join([tempDirectory(), "doof-driver-project-lock-test"])
  removeDriverTestTree(root)
  try! mkdir(root)
  try! mkdir(join([root, "src"]))
  try! writeText(join([root, "doof.json"]), "{\"name\":\"lock-test\",\"build\":{\"entry\":\"src/main.do\",\"buildDir\":\"artifacts\"}}")
  try! writeText(join([root, "src/main.do"]), "function main(): none {}")
  try! writeText(join([root, "src/main.test.do"]), "export function testOne(): none {}")
  build := readProjectSpec(root)
  test := readProjectSpec(join([root, "src/main.test.do"]))
  Assert.equal(projectBuildLockPath(build.rootDirectory, build.buildDirectory), join([root, "artifacts/.doof.lock"]))
  Assert.equal(projectBuildLockPath(test.rootDirectory, test.buildDirectory), projectBuildLockPath(build.rootDirectory, build.buildDirectory))
  removeDriverTestTree(root)
}

export function testCompilerCacheIdentityTracksReplacementBytes(): none {
  root := join([tempDirectory(), "doof-compiler-identity-test"])
  removeDriverTestTree(root)
  try! mkdir(root)
  first := join([root, "doof"])
  copy := join([root, "renamed-doof"])
  try! writeText(first, "compiler-a")
  try! writeText(copy, "compiler-a")
  identity := compilerCacheIdentity(first)
  Assert.isTrue(identity != "")
  Assert.equal(compilerCacheIdentity(copy), identity)
  try! writeText(first, "compiler-b")
  Assert.isTrue(compilerCacheIdentity(first) != identity)
  Assert.equal(compilerCacheIdentity(join([root, "missing"])), "")
  removeDriverTestTree(root)
}

export function testCompilerCacheIdentityControlsFrontendReuse(): none {
  state := FrontendCacheState { configurationFingerprint: "compiler-a" }
  Assert.isTrue(frontendStateMatches(state, "compiler-a", noSourceLoader))
  Assert.isFalse(frontendStateMatches(state, "compiler-b", noSourceLoader))
  Assert.isFalse(frontendStateMatches(none, "compiler-a", noSourceLoader))
  unreadable := FrontendCacheState { configurationFingerprint: "" }
  Assert.isFalse(frontendStateMatches(unreadable, "", noSourceLoader))
}

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

export function testMapsStandardImportProbeShapesToCatalogPackages(): none {
  Assert.equal(stdlibPackageNameForLogicalPath("/std/fs.do"), "std/fs")
  Assert.equal(stdlibPackageNameForLogicalPath("/std/fs/index.do"), "std/fs")
  Assert.equal(stdlibPackageNameForLogicalPath("/std/not-a-package.do"), "std/not-a-package")
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

import { writeCoverageHtml } from "./driver"
import { CoverageReport, CoverageFileReport, coverageFileRelativePath } from "./test-runner"

export function testQuarkFixCoverageWritesInsideOutputDirectory(): none {
  root := join([tempDirectory(), "doof-coverage-containment-test"])
  removeDriverTestTree(root)
  try! mkdir(root)
  sourceRoot := join([root, "source"])
  try! mkdir(sourceRoot)
  absoluteSource := join([sourceRoot, "readers.do"])
  try! writeText(absoluteSource, "function read(): int => 7")
  report := CoverageReport { files: [CoverageFileReport {
    path: absoluteSource, covered: 1, total: 1, percentTenths: 1000, hitLines: [1],
  }] }
  jsonPath := join([root, "output/compiler.json"])
  index := writeCoverageHtml(report, jsonPath, sourceRoot)
  page := coverageFileRelativePath(absoluteSource)
  expectedPage := join([root, "output/compiler_files", page])
  Assert.isTrue(expectedPage.startsWith(join([root, "output/compiler_files"]) + "/"))
  Assert.isTrue(exists(expectedPage))
  Assert.equal(exists(absoluteSource + ".html"), false)
  Assert.stringContains(try! readText(index), "compiler_files/" + page)
  Assert.stringContains(try! readText(expectedPage), "function read(): int")
  let depth = 1
  for i of 0..<page.length { if page[i] == '/' { depth += 1 } }
  Assert.stringContains(try! readText(expectedPage), "../".repeat(depth) + "compiler.html")
  removeDriverTestTree(root)
}

export function testQuarkFixEmptyCoverageCreatesIndexDirectory(): none {
  root := join([tempDirectory(), "doof-empty-coverage-test"])
  removeDriverTestTree(root)
  index := writeCoverageHtml(CoverageReport {}, join([root, "nested/coverage.json"]), root)
  Assert.isTrue(exists(index))
  removeDriverTestTree(root)
}

export function testPhaseTimingsDriverRequiresExplicitOptIn(): none {
  Assert.isTrue(phaseTimingsEnabled("emit", "1"))
  Assert.isTrue(phaseTimingsEnabled("check", "1"))
  for value of ["", "0", "true"] { Assert.isFalse(phaseTimingsEnabled("emit", value)) }
  for command of ["run", "build", "profile", "test", "package"] {
    Assert.isFalse(phaseTimingsEnabled(command, "1"))
  }
}
