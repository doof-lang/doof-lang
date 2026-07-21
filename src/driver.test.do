import { Assert } from "std/assert"
import { driverRootLogicalPath, driverRootLogicalPrefix } from "./driver"

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
