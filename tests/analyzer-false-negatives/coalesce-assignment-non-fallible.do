// Invalid: `??=` requires a nullable or Result assignment target.
// expect-error: 5:5 Operator '??=' requires a nullable or Result assignment target, got int
function main(): none {
    let value = 1
    value ??= 2
    println(value)
}
