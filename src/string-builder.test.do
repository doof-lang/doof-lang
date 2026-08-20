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

export function testSupportsLinesLengthReserveAndClear(): none {
  builder := StringBuilder()
  builder.reserve(64)
  builder.appendLine("alpha")
  builder.appendLine()
  builder.append("omega")
  Assert.equal(builder.length(), 12)
  Assert.equal(builder.drainToString(), "alpha\n\nomega")
  Assert.equal(builder.length(), 0)

  builder.append("discarded")
  builder.clear()
  Assert.equal(builder.length(), 0)
  Assert.equal(builder.drainToString(), "")
}
