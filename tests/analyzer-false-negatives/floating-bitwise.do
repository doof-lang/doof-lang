// Invalid: bitwise operators require integer operands.
// expect-error: 4:14 Operator '&' requires integer operands, got double and double
function main(): none {
    value := 1.0 & 2.0
    println(value)
}
