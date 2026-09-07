import { Assert } from "std/assert"
import { PhaseTimings } from "./phase-timings"

export function testPhaseTimingsDisabledAndAggregated(): none {
  disabled := PhaseTimings {}
  Assert.equal(disabled.start(), none)
  disabled.record("ignored", 1L)
  Assert.equal(disabled.entries.length, 0)
  Assert.equal(disabled.render(), "")
  timings := PhaseTimings { enabled: true }
  timings.finish("absent", none)
  timings.record("first", 1000000L)
  timings.record("second", 0L)
  timings.record("first", 2500000L)
  Assert.equal(timings.entries.length, 2)
  Assert.equal(timings.entries[0].name, "first")
  Assert.equal(timings.entries[0].nanos, 3500000L)
  Assert.equal(timings.entries[0].count, 2)
  Assert.equal(timings.entries[1].nanos, 0L)
  Assert.stringContains(timings.render(), "first ms=3.5 count=2")
  started := timings.start()
  timings.finish("clock", started)
  Assert.equal(timings.entries[2].name, "clock")
  Assert.isTrue(timings.entries[2].nanos >= 0L)
}
