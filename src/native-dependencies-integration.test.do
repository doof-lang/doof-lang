// Real native probes with hermetic pkg-config metadata; no shared test outputs.
import { Assert } from "std/assert"
import { BlobReader } from "std/blob"
import { exists, isDirectory, readDir, readText, mkdir, remove, writeText } from "std/fs"
import { platform, run } from "std/os"
import { tempDirectory, join } from "std/path"
import { uuidV4 } from "std/crypto"
import { OptionalPkgConfigPackage } from "./native-dependency-config"
import { NativeBuildPlan } from "./package-manifest"
import { resolveOptionalNativeDependencies } from "./native-dependencies"
import { ProjectEmission } from "./emitter-project"
import { buildNativeProject } from "./native-build-driver"

function erase(path: string): none {
  if !exists(path) { return }
  if isDirectory(path) { for entry of readDir(path)! { erase(join([path, entry.name])) } }
  remove(path)!
}

function fixture(): string {
  root := join([tempDirectory(), "doof-optional-native-" + uuidV4()])
  mkdir(root)!
  mkdir(root + "/empty")!
  mkdir(root + "/include")!
  writeText(root + "/pkg-config", readText("tests/fixtures/optional-native/pkg-config.sh")!)!
  Assert.equal(run("chmod", ["+x", root + "/pkg-config"])!.exitCode, 0)
  writeText(root + "/include/dependency.hpp", "inline int dependency_api() { return 0; }\n")!
  writeText(root + "/probe.cpp", "#include <dependency.hpp>\nint main() { return dependency_api(); }\n")!
  writeText(root + "/metadata-present", "yes")!
  return root
}

function native(name: string): NativeBuildPlan {
  return NativeBuildPlan { optionalPkgConfigPackages: [OptionalPkgConfigPackage {
    name, define: "OPTIONAL_FEATURE", probeSource: "probe.cpp", minimumVersion: "3.0",
  }] }
}

export function testOptionalNativeIntegrationDetectsMissingOrIncompatibleInputs(): none {
  if platform() == "windows" { return }
  root := fixture()
  for name of ["fixture", "absent", "old-version", "missing-header", "wrong-library"] {
    inputs := native(name)
    resolveOptionalNativeDependencies(inputs, "c++", root, "linux", false, root + "/pkg-config")!
    Assert.equal(inputs.defines.contains("OPTIONAL_FEATURE=1"), name == "fixture")
    Assert.equal(inputs.defines.contains("OPTIONAL_FEATURE=0"), name != "fixture")
    if name != "fixture" { Assert.equal(inputs.includePaths.length, 0); Assert.equal(inputs.linkLibraries.length, 0) }
  }
  missingTool := native("fixture")
  resolveOptionalNativeDependencies(missingTool, "c++", root, "linux", false, root + "/nonexistent-pkg-config")!
  Assert.equal(missingTool.defines[0], "OPTIONAL_FEATURE=0")
  brokenCompiler := resolveOptionalNativeDependencies(native("fixture"), root + "/no-c++", root, "linux", false, root + "/pkg-config")
  _ := brokenCompiler else error { Assert.stringContains(error, "target compiler"); erase(root); return }
  panic("expected missing compiler failure")
}

export function testOptionalNativeIntegrationRejectsIncompatibleProbeAndMissingSource(): none {
  if platform() == "windows" { return }
  root := fixture()
  writeText(root + "/probe.cpp", "#include <dependency.hpp>\nint main() { return nonexistent_api(); }\n")!
  inputs := native("fixture")
  resolveOptionalNativeDependencies(inputs, "c++", root, "linux", false, root + "/pkg-config")!
  Assert.equal(inputs.defines[0], "OPTIONAL_FEATURE=0")
  remove(root + "/probe.cpp")!
  missing := resolveOptionalNativeDependencies(native("absent"), "c++", root, "linux", false, root + "/pkg-config")
  _ := missing else error { Assert.stringContains(error, "probe source is missing"); erase(root); return }
  panic("expected missing packaged probe failure")
}

export function testOptionalNativeDriverIntegrationInvalidatesAvailabilityTransitions(): none {
  if platform() == "windows" { return }
  root := fixture()
  writeText(root + "/main.cpp", `#include <cstdio>
int main() { std::printf("%d", OPTIONAL_FEATURE); }
`)!
  for expected of [1, 0, 1] {
    if expected == 0 { remove(root + "/metadata-present")! }
    else if !exists(root + "/metadata-present") { writeText(root + "/metadata-present", "yes")! }
    inputs := native("fixture")
    inputs.sourceFiles.push("main.cpp")
    project := ProjectEmission { nativeBuild: inputs }
    Assert.equal(buildNativeProject("c++", root, root + "/app", project, .Debug, "linux", .Silent, false, root + "/pkg-config"), 0)
    result := run(root + "/app", [])!
    Assert.equal(BlobReader(result.stdout).readString(long(result.stdout.length)), string(expected))
  }
  // Successful dependency detection must not hide subsequent application errors.
  writeText(root + "/main.cpp", "#error deliberate_application_failure\n")!
  inputs := native("fixture")
  inputs.sourceFiles.push("main.cpp")
  project := ProjectEmission { nativeBuild: inputs }
  Assert.equal(buildNativeProject("c++", root, root + "/app", project, .Debug, "linux", .Silent, false, root + "/pkg-config") != 0, true)
  Assert.equal(inputs.defines.contains("OPTIONAL_FEATURE=1"), true)
  erase(root)
}
