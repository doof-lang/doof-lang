// Invalid: named construction cannot provide fields absent from the class.
class Point {
    x: int
    y: int
}

function main(): none {
    point := Point { x: 1, y: 2, z: 3 }
    println(point.x)
}
