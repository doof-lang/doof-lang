// Invalid: `\` requires integer operands.
// expect-error: 4:17 Operator '\' requires integer operands, got double and double
function main(): none {
    quotient := 7.0 \ 2.0
    println(quotient)
}
