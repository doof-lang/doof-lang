// Invalid: string range bounds cannot match an int subject.
function describe(value: int): string => case value {
    "a".."z" -> "letter"
    _ -> "number"
}

function main(): none {
    println(describe(0))
}
