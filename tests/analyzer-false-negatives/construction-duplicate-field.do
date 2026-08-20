// Invalid: a named construction field can only be supplied once.
class Point {
    x: int
    y: int
}

function main(): none {
    point := Point { x: 1, y: 2, x: 3 }
    println(point.x)
}
