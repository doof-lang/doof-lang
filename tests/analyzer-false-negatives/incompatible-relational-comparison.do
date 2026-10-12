// Invalid: ordering is not defined between int and string.
// expect-error: 4:16 Operator '<' is not defined for int and string
function main(): none {
    ordered := 1 < "two"
    println(ordered)
}
