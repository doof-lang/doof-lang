import { Assert } from "std/assert"

let invocationCount = 0

function assertFreshWasmInstance(): none {
  invocationCount += 1
  Assert.equal(invocationCount, 1)
}

export function testFirstFreshInstance(): none {
  assertFreshWasmInstance()
}

export function testSecondFreshInstance(): none {
  assertFreshWasmInstance()
}
