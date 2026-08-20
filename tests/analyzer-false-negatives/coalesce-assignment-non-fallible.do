// Invalid: `??=` requires a nullable or Result assignment target.
function main(): none {
    let value = 1
    value ??= 2
    println(value)
}
