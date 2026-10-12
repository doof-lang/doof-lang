// Invalid: `??` requires a nullable or Result value on its left side.
// expect-error: 4:14 Operator '??' requires a nullable or Result left operand, got int
function main(): none {
    value := 1 ?? 2
    println(value)
}
