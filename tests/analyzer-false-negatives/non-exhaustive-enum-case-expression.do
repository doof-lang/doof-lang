// Invalid: value-producing case expressions must cover every enum variant.
enum Direction { North, South }

function describe(value: Direction): string => case value {
    .North -> "north"
}

function main(): none {
    println(describe(.South))
}
