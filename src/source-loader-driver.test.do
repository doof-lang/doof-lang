import { Assert } from "std/assert"
import {
  driverRootLogicalPath, driverRootLogicalPrefix, stdlibPackageAcquisitionRoot, stdlibPackageNameForLogicalPath,
} from "./source-loader-driver"

export function testStandardPackageCacheFollowsSelectedBuildDirectory(): none {
  Assert.equal(stdlibPackageAcquisitionRoot("/tmp/jigsaw/build"), "/tmp/jigsaw/build/.doof/packages")
  Assert.equal(stdlibPackageAcquisitionRoot("/tmp/custom-output"), "/tmp/custom-output/.doof/packages")
}

export function testStandardPackageNameAcceptsDirectoryAndFileProbes(): none {
  Assert.equal(stdlibPackageNameForLogicalPath("/std/json/index.do"), "std/json")
  Assert.equal(stdlibPackageNameForLogicalPath("/std/json.do"), "std/json")
  Assert.equal(stdlibPackageNameForLogicalPath("/std/fs"), "std/fs")
}

export function testStandardPackageRootsUsePackageLogicalPrefix(): none {
  Assert.equal(driverRootLogicalPrefix("std/json", "/tmp/stdlib/json"), "/std/json")
  Assert.equal(driverRootLogicalPath("/tmp/stdlib/json/index.do", "/tmp/stdlib/json", "std/json"), "/std/json/index.do")
  Assert.equal(driverRootLogicalPath("/tmp/stdlib/json", "/tmp/stdlib/json", "std/json"), "/std/json")
}

export function testOrdinaryRootsKeepSourceSuffixLogicalPaths(): none {
  Assert.equal(driverRootLogicalPath("/tmp/app/src/main.do", "/tmp/app", "app"), "/src/main.do")
  Assert.equal(driverRootLogicalPath("/tmp/app/src/main", "/tmp/app", "app"), "/src/main.do")
}
