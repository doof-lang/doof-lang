// Invalid: numeric casts lower to static_cast, which cannot convert a variant.
// A union value must be narrowed with `case` before it is cast.
// expect-error: 5:17 Argument 1 has type int | float; expected byte | int | long | float | double
function narrow(value: int | float): byte {
    return byte(value)
}

function main(): none {
    println(narrow(3))
}
