// Invalid: the field default is string, but the field type is int.
class Counter {
    count: int = "zero"
}

function main(): none {
    counter := Counter {}
    println(counter.count)
}
