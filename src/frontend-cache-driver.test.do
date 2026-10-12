import { Assert } from "std/assert"
import { compilerCacheIdentity, frontendCachePath, frontendEmissionCacheSupported } from "./frontend-cache-driver"
import { compilerVersion, compilerVersionStamped } from "./version"

export function testDriverUsesStampedCompilerIdentity(): none {
  Assert.equal(compilerCacheIdentity(), if compilerVersionStamped then compilerVersion else "")
}

export function testBatchSelectionCacheTargetBoundaries(): none {
  Assert.isTrue(frontendEmissionCacheSupported("native"))
  Assert.isFalse(frontendEmissionCacheSupported("wasm"))
  Assert.isFalse(frontendEmissionCacheSupported("ios-app"))
}

export function testFrontendCacheStateLivesInVersionedBuildDirectory(): none {
  Assert.equal(frontendCachePath("/tmp/app/build", "emission"), "/tmp/app/build/.doof-cache/v1/emission.json")
  Assert.equal(frontendCachePath("/tmp/app/build/", "check"), "/tmp/app/build/.doof-cache/v1/check.json")
}
