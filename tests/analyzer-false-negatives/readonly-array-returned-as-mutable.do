// Invalid: a readonly array cannot escape as a mutable array through a return.
// expect-error: 3:51 Cannot return readonly int[] from function returning int[]
function unlock(values: readonly int[]): int[] => values
