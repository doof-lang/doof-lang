import { Assert } from "std/assert"
import { NativeBuildPlan, NativeVendorBuild, PackageManifest } from "./package-manifest"
import {
  driverRootLogicalPath, driverRootLogicalPrefix, sourceLoaderForRequest, stdlibPackageAcquisitionRoot,
  stdlibPackageNameForLogicalPath,
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

function vendorRoot(name: string): PackageManifest {
  return PackageManifest {
    name, manifestPath: "/work/demo/doof.json", rootDirectory: "/work/demo",
    nativeBuild: NativeBuildPlan { vendorBuilds: [NativeVendorBuild { key: "demo-1", directory: "/work/demo/vendor" }] },
  }
}

export function testVendorBuildsAreLimitedToStandardPackages(): none {
  rejected := sourceLoaderForRequest("/work/demo/main.do", "/work/stdlib", [], vendorRoot("demo"), "/work/demo/build", "linux")
  _ := rejected else error {
    Assert.equal(error, "build.native.vendor is only allowed in standard packages")
    // A standard package checkout is the root while its own tests run.
    _ := sourceLoaderForRequest("/work/demo/main.do", "/work/stdlib", [], vendorRoot("std/demo"), "/work/demo/build", "linux")!
    return
  }
  panic("expected a non-standard vendor build to be rejected")
}
