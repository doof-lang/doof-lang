// Invalid: equality is not defined between unrelated int and string values.
function main(): none {
    equal := 1 == "1"
    println(equal)
}
