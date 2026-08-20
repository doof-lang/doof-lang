// Invalid: numeric casts require numeric operands, except int(char).
function main(): none {
    value := int("42")
    println(value)
}
