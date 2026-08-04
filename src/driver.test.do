import { Assert } from "std/assert"
import { driverRootLogicalPath, driverRootLogicalPrefix, nativeBuildOutputName } from "./driver"

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
