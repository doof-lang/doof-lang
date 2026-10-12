// Invalid: string range bounds cannot match an int subject.
// expect-error: 5:5 Range pattern bounds must be integers; got "string"
// expect-error: 5:10 Range pattern bounds must be integers; got "string"
function describe(value: int): string => case value {
    "a".."z" -> "letter"
    _ -> "number"
}

function main(): none {
    println(describe(0))
}
