// Invalid: union arms that differ only in collection mutability cannot be distinguished at runtime.
// expect-error: 3:24 Union members int[] and readonly int[] differ only in collection mutability and cannot be distinguished at runtime; use a single mutability or distinct wrapper types
function total(values: int[] | readonly int[]): int => 0
