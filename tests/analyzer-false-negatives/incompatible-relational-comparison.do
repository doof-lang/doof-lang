// Invalid: ordering is not defined between int and string.
function main(): none {
    ordered := 1 < "two"
    println(ordered)
}
