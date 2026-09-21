// Deterministic progress rendering shared by long-running CLI operations.

import isolated function hardwareConcurrency(): int from "doof_runtime.hpp" as doof::hardware_concurrency

/** Renders a fixed-width completed/total bar with clamped inputs. */
export function renderProgressBar(completed: int, total: int, width: int = 24): string {
  barWidth := if width < 1 then 1 else width
  safeTotal := if total < 0 then 0 else total
  safeCompleted := if completed < 0 then 0 else if completed > safeTotal then safeTotal else completed
  filled := if safeTotal == 0 then barWidth else (safeCompleted * barWidth) \ total
  return "[" + "#".repeat(filled) + "-".repeat(barWidth - filled) + "] " +
    string(safeCompleted) + "/" + string(safeTotal)
}

/** Chooses a positive hardware-bounded worker count without idle workers. */
export function boundedWorkerCount(itemCount: int, maximumWorkers: int = -1): int {
  workers := if maximumWorkers < 0 then hardwareConcurrency() else maximumWorkers
  if itemCount <= 0 || workers <= 0 { return 0 }
  return if itemCount < workers then itemCount else workers
}
