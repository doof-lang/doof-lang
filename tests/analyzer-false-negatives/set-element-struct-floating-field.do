// Invalid: Set element validation recurses into struct fields, so a floating-point field is rejected.
// expect-error: 8:17 Set element type "Point" is not supported (field "x" of "Point" has type "double"); Map keys and Set elements may be byte, string, int, long, char, bool, enums, class or interface references, or tuples, unions, and structs of those
struct Point {
    x: double
}

function main(): none {
    points: Set<Point> := []
    println(points.size)
}
