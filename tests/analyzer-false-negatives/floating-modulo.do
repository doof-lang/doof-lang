// Invalid: `%` requires integer operands.
// expect-error: 4:18 Operator '%' requires integer operands, got double and double
function main(): none {
    remainder := 7.0 % 2.0
    println(remainder)
}
