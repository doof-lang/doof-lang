// Invalid: the expression body is string, but the declared return type is int.
function wrongReturnType(): int => "not an int"

function main(): none {
    println(wrongReturnType())
}
