// Invalid: an inferred type argument must satisfy the type parameter's constraint.
// expect-error: 6:13 Type "double" does not satisfy constraint "int | string" for type parameter "T"
function identity<T: int | string>(value: T): T => value

function main(): none {
    println(identity(1.5))
}
