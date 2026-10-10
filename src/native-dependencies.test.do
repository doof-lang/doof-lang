import { Assert } from "std/assert"
import { NativeBuildPlan } from "./package-manifest"
import { OptionalPkgConfigPackage } from "./native-dependency-config"
import { PkgConfigCommandResult } from "./pkg-config"
import { nativePkgConfigProgram, optionalNativePath, optionalPkgConfigInputs,
  applyOptionalNativeSelection, optionalNativeProbePlan } from "./native-dependencies"

export function testOptionalNativeMetadataIsTransactional(): none {
  native := NativeBuildPlan { linkLibraries: ["base"] }
  for status of [-1, 1] {
    failed := optionalPkgConfigInputs(native, "libcrypto",
      PkgConfigCommandResult { exitCode: 0, output: "-I/leak -DLEAK" },
      PkgConfigCommandResult { exitCode: status })
    Assert.equal(failed == none, true)
    Assert.equal(native.includePaths.length, 0)
    Assert.equal(native.defines.length, 0)
  }
  selected := optionalPkgConfigInputs(native, "libcrypto",
    PkgConfigCommandResult { exitCode: 0, output: "-I/target/include" },
    PkgConfigCommandResult { exitCode: 0, output: "-L/target/lib -lcrypto" })!
  applyOptionalNativeSelection(native, "RSA_EVP", selected)!
  Assert.equal(native.includePaths[0], "/target/include")
  Assert.equal(native.linkLibraries[0], "base")
  Assert.equal(native.linkLibraries[1], "crypto")
  Assert.equal(native.defines[0], "RSA_EVP=1")
}

export function testOptionalNativeRejectsCapabilityDefineCollisions(): none {
  for define of ["RSA_EVP", "RSA_EVP=0", "RSA_EVP=1"] {
    result := applyOptionalNativeSelection(NativeBuildPlan { defines: [define] }, "RSA_EVP", none)
    _ := result else error { Assert.stringContains(error, "unique define"); continue }
    panic("expected capability define collision")
  }
  result := applyOptionalNativeSelection(NativeBuildPlan {}, "RSA_EVP", NativeBuildPlan { defines: ["RSA_EVP=1"] })
  _ := result else error { Assert.stringContains(error, "pkg-config must not supply"); return }
  panic("expected pkg-config define collision")
}

export function testOptionalNativeSelectionChangesTargetCompileAndLinkArguments(): none {
  dependency := OptionalPkgConfigPackage { name: "libcrypto", define: "RSA_EVP", probeSource: "std/crypto/probe.cpp" }
  native := NativeBuildPlan { includePaths: ["std/crypto"], libraryPaths: ["vendor"],
    compilerFlags: ["--sysroot=/target", "--target=aarch64-linux-gnu"], linkerFlags: ["--sysroot=/target"] }
  probe := optionalNativeProbePlan(native, dependency, "target-c++", "/output", "linux")
  Assert.equal(probe.compileTasks.length, 1)
  Assert.equal(probe.precompiledHeaderTask == none, true)
  Assert.equal(probe.compileTasks[0].compiler, "target-c++")
  Assert.equal(probe.compileTasks[0].sourcePath, "/output/std/crypto/probe.cpp")
  Assert.equal(probe.compileTasks[0].arguments.contains("--target=aarch64-linux-gnu"), true)
  Assert.equal(probe.compileTasks[0].arguments.contains("-DRSA_EVP=1"), true)
  Assert.equal(probe.compileTasks[0].arguments.contains("/output/std/crypto"), true)
  Assert.equal(probe.linkArguments.contains("--sysroot=/target"), true)
  Assert.equal(probe.linkArguments.contains("-L/output/vendor"), true)
  Assert.equal(native.defines.length, 0)
  Assert.equal(nativePkgConfigProgram(""), "pkg-config")
  Assert.equal(nativePkgConfigProgram("/target/pkg-config"), "/target/pkg-config")
  Assert.equal(optionalNativePath("/output", "C:/target/include"), "C:/target/include")
}

export function testOptionalNativeUnavailableDefinesStubExplicitly(): none {
  native := NativeBuildPlan {}
  applyOptionalNativeSelection(native, "RSA_EVP", none)!
  Assert.equal(native.defines[0], "RSA_EVP=0")
  Assert.equal(native.linkLibraries.length, 0)
}

export function testOptionalNativeProbeUsesWindowsOrWasmTargetPlanner(): none {
  dependency := OptionalPkgConfigPackage { name: "fixture", define: "HAVE_FIXTURE", probeSource: "probe.cpp" }
  windows := optionalNativeProbePlan(NativeBuildPlan {}, dependency, "cl.exe", "/output", "windows")
  Assert.equal(windows.linker, "link.exe")
  Assert.equal(windows.outputPath.endsWith(".exe"), true)
  Assert.equal(windows.compileTasks[0].arguments.contains("/DHAVE_FIXTURE=1"), true)
  wasm := optionalNativeProbePlan(NativeBuildPlan {}, dependency, "em++", "/output", "linux", true)
  Assert.equal(wasm.outputPath.endsWith(".wasm"), true)
  Assert.equal(wasm.linkArguments.contains("-sSTANDALONE_WASM=1"), true)
}
