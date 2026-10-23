// Invalid: classes have no implicit string representation, so they cannot be interpolated.
// expect-error: 9:22 Type "Point" cannot be used in string interpolation
class Point {
    x: int = 0
}

function main(): none {
    point := Point {}
    println(`point=${point}`)
}
