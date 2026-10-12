// Invalid: the expression body is string, but the declared return type is int.
// expect-error: 3:36 Cannot return string from function returning int
function wrongReturnType(): int => "not an int"

function main(): none {
    println(wrongReturnType())
}
