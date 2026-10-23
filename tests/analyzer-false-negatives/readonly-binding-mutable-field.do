// Invalid: a readonly binding must be deeply immutable, including the fields of its class.
// expect-error: 8:5 Readonly binding "counter" must be deeply immutable: field "count" is mutable
class Counter {
    let count: int = 0
}

function main(): none {
    readonly counter = Counter {}
    println(counter.count)
}
