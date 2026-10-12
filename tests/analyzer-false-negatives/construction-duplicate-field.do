// Invalid: a named construction field can only be supplied once.
// expect-error: 9:34 Duplicate field 'x' in Point construction
class Point {
    x: int
    y: int
}

function main(): none {
    point := Point { x: 1, y: 2, x: 3 }
    println(point.x)
}
