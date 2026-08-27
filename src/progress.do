// Deterministic progress rendering shared by long-running CLI operations.

/** Renders a fixed-width completed/total bar with clamped inputs. */
export function renderProgressBar(completed: int, total: int, width: int = 24): string {
  barWidth := if width < 1 then 1 else width
  safeTotal := if total < 0 then 0 else total
  safeCompleted := if completed < 0 then 0 else if completed > safeTotal then safeTotal else completed
  filled := if safeTotal == 0 then barWidth else (safeCompleted * barWidth) \ total
  return "[" + "#".repeat(filled) + "-".repeat(barWidth - filled) + "] " +
    string(safeCompleted) + "/" + string(safeTotal)
}

/** Chooses a positive bounded worker count without creating idle workers. */
export function boundedWorkerCount(itemCount: int, maximumWorkers: int = 4): int {
  if itemCount <= 0 || maximumWorkers <= 0 { return 0 }
  return if itemCount < maximumWorkers then itemCount else maximumWorkers
}
