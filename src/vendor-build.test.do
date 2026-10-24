import { Assert } from "std/assert"
import { NativeVendorToolchain } from "./native-build"
import { NativeVendorBuild } from "./package-manifest"
import {
  missingVendorOutputs, nativeBuildModeName, vendorBuildDirectory, vendorBuildEnvironment,
  vendorBuildFingerprint, vendorScriptCommand, vendorScriptName,
} from "./vendor-build"

function toolchain(): NativeVendorToolchain {
  return NativeVendorToolchain { cc: "cc", cxx: "c++", ar: "ar", cflags: ["-O2", "-flto"], cxxflags: ["-std=c++17", "-O2", "-flto"] }
}

function build(key: string = "demo-1"): NativeVendorBuild {
  return NativeVendorBuild { packageName: "std/demo", key, directory: "std/demo/vendor", staticLibraries: ["libdemo.a"] }
}

export function testVendorEnvironmentCarriesToolchainAndTarget(): none {
  environment := vendorBuildEnvironment(toolchain(), "linux", .Release, 0)
  Assert.equal(environment.get("CC")!, "cc")
  Assert.equal(environment.get("CXX")!, "c++")
  Assert.equal(environment.get("AR")!, "ar")
  Assert.equal(environment.get("CFLAGS")!, "-O2 -flto")
  Assert.equal(environment.get("CXXFLAGS")!, "-std=c++17 -O2 -flto")
  Assert.equal(environment.get("DOOF_PLATFORM")!, "linux")
  Assert.equal(environment.get("DOOF_MODE")!, "release")
  // A non-positive job count still lets scripts run serially.
  Assert.equal(environment.get("DOOF_JOBS")!, "1")
  Assert.equal(nativeBuildModeName(.InteractiveDebug), "interactive-debug")
}

export function testVendorFingerprintTracksKeyTargetCompilerAndScript(): none {
  environment := vendorBuildEnvironment(toolchain(), "linux", .Debug, 4)
  base := vendorBuildFingerprint(build(), environment, "clang 18", "make lib")
  Assert.equal(vendorBuildFingerprint(build(), environment, "clang 18", "make lib"), base)
  Assert.notEqual(vendorBuildFingerprint(build("demo-2"), environment, "clang 18", "make lib"), base)
  Assert.notEqual(vendorBuildFingerprint(build(), vendorBuildEnvironment(toolchain(), "linux", .Release, 4), "clang 18", "make lib"), base)
  Assert.notEqual(vendorBuildFingerprint(build(), environment, "clang 19", "make lib"), base)
  Assert.notEqual(vendorBuildFingerprint(build(), environment, "clang 18", "make lib -j"), base)
  Assert.equal(vendorBuildFingerprint(build(), vendorBuildEnvironment(toolchain(), "linux", .Debug, 64), "clang 18", "make lib"), base)
}

export function testVendorDirectoriesAreGroupedByPackage(): none {
  directory := vendorBuildDirectory("std/demo", "0123456789abcdef0123")
  Assert.equal(directory, ".doof-vendor/std-demo-0123456789abcdef")
}

export function testSelectsVendorScriptByPlatform(): none {
  Assert.equal(vendorScriptName("windows"), "build.ps1")
  Assert.equal(vendorScriptName("macos"), "build.sh")
  Assert.equal(vendorScriptCommand("linux").program, "sh")
  windows := vendorScriptCommand("windows")
  Assert.equal(windows.program, "powershell.exe")
  Assert.equal(windows.arguments[windows.arguments.length - 1], "build.ps1")
}

export function testReportsMissingDeclaredVendorOutputs(): none {
  declared := NativeVendorBuild {
    key: "k", directory: "vendor", staticLibraries: ["libdemo.a", "libother.a"], bundleLibraries: ["libshared.dylib"],
  }
  missing := missingVendorOutputs(declared, (relativePath: string): bool => relativePath == "lib/libdemo.a")
  Assert.equal(missing.length, 2)
  Assert.equal(missing[0], "lib/libother.a")
  Assert.equal(missing[1], "lib/libshared.dylib")
}
