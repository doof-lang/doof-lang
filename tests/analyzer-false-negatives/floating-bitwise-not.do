// Invalid: bitwise not requires an integer operand.
// expect-error: 4:14 Unary '~' requires an integer operand
function main(): none {
    value := ~1.0
    println(value)
}
