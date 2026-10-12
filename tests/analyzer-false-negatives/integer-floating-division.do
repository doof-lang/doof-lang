// Invalid: `/` requires at least one float or double operand.
// expect-error: 4:17 Operator '/' requires at least one floating-point operand for every allowed type
function main(): none {
    quotient := 7 / 2
    println(quotient)
}
