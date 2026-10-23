// Invalid: a readonly array cannot be passed where a mutable array is expected.
// expect-error: 7:12 Argument 1 has type readonly int[]; expected int[]
function append(values: int[]): none { values.push(1) }

function main(): none {
    readonly values = [1, 2]
    append(values)
}
