// Invalid: postfix `!` requires a nullable or Result operand.
// expect-error: 4:14 Postfix '!' requires a nullable or Result operand, got int
function main(): none {
    value := 1!
    println(value)
}
