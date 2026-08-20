// Invalid: value-producing case expressions must cover both bool values.
function describe(value: bool): string => case value {
    true -> "yes"
}

function main(): none {
    println(describe(false))
}
