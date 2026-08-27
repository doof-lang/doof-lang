import { Assert } from "std/assert"
import { boundedWorkerCount, renderProgressBar } from "./progress"

export function testRendersDeterministicProgressWidth(): none {
  Assert.equal(renderProgressBar(0, 4, 8), "[--------] 0/4")
  Assert.equal(renderProgressBar(1, 4, 8), "[##------] 1/4")
  Assert.equal(renderProgressBar(4, 4, 8), "[########] 4/4")
}

export function testClampsProgressInputsAndWidth(): none {
  Assert.equal(renderProgressBar(-2, 4, 4), "[----] 0/4")
  Assert.equal(renderProgressBar(8, 4, 4), "[####] 4/4")
  Assert.equal(renderProgressBar(0, 0, 0), "[#] 0/0")
}

export function testBoundsWorkersToAvailableItems(): none {
  Assert.equal(boundedWorkerCount(10), 4)
  Assert.equal(boundedWorkerCount(2), 2)
  Assert.equal(boundedWorkerCount(0), 0)
  Assert.equal(boundedWorkerCount(3, 0), 0)
}
