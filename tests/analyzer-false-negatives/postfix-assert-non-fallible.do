// Invalid: postfix `!` requires a nullable or Result operand.
function main(): none {
    value := 1!
    println(value)
}
