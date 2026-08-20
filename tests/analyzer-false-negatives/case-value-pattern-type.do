// Invalid: a string value pattern cannot match an int subject.
function describe(value: int): string => case value {
    "zero" -> "impossible"
    _ -> "number"
}

function main(): none {
    println(describe(0))
}
