// Invalid: a string value pattern cannot match an int subject.
// expect-error: 4:5 Case value pattern of type "string" cannot match subject type "int"
function describe(value: int): string => case value {
    "zero" -> "impossible"
    _ -> "number"
}

function main(): none {
    println(describe(0))
}
