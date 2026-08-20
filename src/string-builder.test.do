import { Assert } from "std/assert"

import { StringBuilder } from "./string-builder"

export function testBuildsTextFromEmptyAndNonEmptyChunks(): none {
  builder := StringBuilder()
  builder.append("")
  builder.append("large")
  builder.append("-")
  builder.append("header")
  Assert.equal(builder.drainToString(), "large-header")
}

export function testCanBeReusedAfterDrainTransfersTheResult(): none {
  builder := StringBuilder()
  builder.append("first")
  Assert.equal(builder.drainToString(), "first")
  Assert.equal(builder.drainToString(), "")
  builder.append("second")
  Assert.equal(builder.drainToString(), "second")
}
