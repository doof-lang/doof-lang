// Invalid: static members cannot be accessed through an instance with `.`.
class Counter {
    static count: int = 0
}

function main(): none {
    counter := Counter {}
    println(counter.count)
}
