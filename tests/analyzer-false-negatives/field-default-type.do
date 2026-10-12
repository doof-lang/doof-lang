// Invalid: the field default is string, but the field type is int.
// expect-error: 4:18 Cannot use default value of type string for field of type int
class Counter {
    count: int = "zero"
}

function main(): none {
    counter := Counter {}
    println(counter.count)
}
