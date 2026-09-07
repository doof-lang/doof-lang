import { Assert } from "std/assert"
import { structuredTestResult } from "./driver"

export function testEditorDriverReportsExactIdentityAndExitStatus(): none {
  value := structuredTestResult("example.test.do::testOne", 7, "failure\n")
  Assert.equal(try! value.get("id"), "example.test.do::testOne")
  Assert.equal(try! value.get("exitCode"), 7)
  Assert.equal(try! value.get("output"), "failure\n")
}

import { frontendEmissionCacheSupported } from "./driver"
export function testBatchSelectionCacheTargetBoundaries(): none {
  Assert.isTrue(frontendEmissionCacheSupported("native"))
  Assert.isFalse(frontendEmissionCacheSupported("wasm"))
  Assert.isFalse(frontendEmissionCacheSupported("ios-app"))
}
