// Optional, caller-owned wall-clock measurements. No clocks are read when disabled.
import { MonotonicInstant } from "std/time"

export class PhaseTiming {
  name: string
  let nanos: long = 0L
  let count: int = 0
}

export class PhaseTimings {
  enabled: bool = false
  entries: PhaseTiming[] = []

  start(): MonotonicInstant | none {
    return if enabled then MonotonicInstant.now() else none
  }

  finish(name: string, started: MonotonicInstant | none): none {
    if !enabled || started == none { return }
    record(name, started!.durationUntil(MonotonicInstant.now()).toNanos())
  }

  record(name: string, nanos: long): none {
    if !enabled { return }
    for entry of entries {
      if entry.name == name {
        entry.nanos += nanos
        entry.count += 1
        return
      }
    }
    entries.push(PhaseTiming { name, nanos, count: 1 })
  }

  render(): string {
    if !enabled { return "" }
    let output = "[timings] wall milliseconds; parent phases include their children\n"
    for entry of entries {
      output = output + "[timings] " + entry.name + " ms=" +
        string(double(entry.nanos) / 1000000.0) + " count=" + string(entry.count) + "\n"
    }
    return output
  }
}
