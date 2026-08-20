// Invalid: `??` requires a nullable or Result value on its left side.
function main(): none {
    value := 1 ?? 2
    println(value)
}
