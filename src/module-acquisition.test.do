import { Assert } from "std/assert"
import { ModuleAcquisition, acquiredManifestPath, acquiredModuleDiskPath, acquiredPackageForModule } from "./module-acquisition"

export function testMapsModulesFromAnUmbrellaRoot(): none {
  acquisitions := [ModuleAcquisition { logicalPrefix: "/std", diskRoot: "/opt/doof/stdlib" }]

  Assert.equal(acquiredModuleDiskPath("/std/time/index.do", acquisitions), "/opt/doof/stdlib/time/index.do")
}

export function testUsesTheMostSpecificAcquiredFolder(): none {
  acquisitions := [
    ModuleAcquisition { logicalPrefix: "/std", diskRoot: "/opt/doof/stdlib" },
    ModuleAcquisition { logicalPrefix: "/std/time", diskRoot: "/cache/time-v1" },
  ]

  Assert.equal(acquiredModuleDiskPath("/std/time/temporal.do", acquisitions), "/cache/time-v1/temporal.do")
  Assert.equal(acquiredModuleDiskPath("/std/fs/index.do", acquisitions), "/opt/doof/stdlib/fs/index.do")
}

export function testDoesNotMatchPartialPrefixSegments(): none {
  acquisitions := [ModuleAcquisition { logicalPrefix: "/std", diskRoot: "/opt/doof/stdlib" }]

  Assert.equal(acquiredModuleDiskPath("/stdlib/time.do", acquisitions), none)
}

export function testReturnsNullForAnUnacquiredModule(): none {
  acquisitions := [ModuleAcquisition { logicalPrefix: "/std", diskRoot: "/opt/doof/stdlib" }]

  Assert.equal(acquiredModuleDiskPath("/vendor/time.do", acquisitions), none)
}

export function testBuildsTheAcquiredPackageManifestPath(): none {
  acquisition := ModuleAcquisition { logicalPrefix: "/std/time", diskRoot: "/cache/time-v1/" }

  Assert.equal(acquiredManifestPath(acquisition), "/cache/time-v1/doof.json")
}

export function testIdentifiesThePackageReachedThroughAnUmbrellaRoot(): none {
  acquisitions := [ModuleAcquisition { logicalPrefix: "/std", diskRoot: "/opt/doof/stdlib" }]

  package := acquiredPackageForModule("/std/time/temporal.do", acquisitions)
  Assert.equal(package != none, true)
  Assert.equal(package!.logicalPrefix, "/std/time")
  Assert.equal(package!.diskRoot, "/opt/doof/stdlib/time")
}

export function testKeepsAPackageSpecificAcquisitionAsTheOwner(): none {
  acquisitions := [
    ModuleAcquisition { logicalPrefix: "/std", diskRoot: "/opt/doof/stdlib" },
    ModuleAcquisition { logicalPrefix: "/std/time", diskRoot: "/cache/time-v1" },
  ]

  package := acquiredPackageForModule("/std/time/index.do", acquisitions)
  Assert.equal(package != none, true)
  Assert.equal(package!.logicalPrefix, "/std/time")
  Assert.equal(package!.diskRoot, "/cache/time-v1")
}
