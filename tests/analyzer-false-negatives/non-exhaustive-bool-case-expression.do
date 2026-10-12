// Invalid: value-producing case expressions must cover both bool values.
// expect-error: 3:43 Case expression must be exhaustive
function describe(value: bool): string => case value {
    true -> "yes"
}

function main(): none {
    println(describe(false))
}
