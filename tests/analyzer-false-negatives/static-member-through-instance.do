// Invalid: static members cannot be accessed through an instance with `.`.
// expect-error: 9:13 Static member 'count' must be accessed through its class: use 'Counter.count'
class Counter {
    static count: int = 0
}

function main(): none {
    counter := Counter {}
    println(counter.count)
}
