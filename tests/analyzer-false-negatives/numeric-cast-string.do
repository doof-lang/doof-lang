// Invalid: numeric casts require numeric operands, except int(char).
// expect-error: 4:18 Argument 1 has type string; expected byte | int | long | float | double | char
function main(): none {
    value := int("42")
    println(value)
}
