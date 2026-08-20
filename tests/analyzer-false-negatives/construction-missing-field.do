// Invalid: named construction must provide every non-defaulted instance field.
class Point {
    x: int
    y: int
}

function main(): none {
    point := Point { x: 1 }
    println(point.x)
}
