// Invalid: equality is not defined between unrelated int and string values.
// expect-error: 4:14 Operator '==' is not defined for int and string
function main(): none {
    equal := 1 == "1"
    println(equal)
}
