// Invalid: a Stream<T> value may hold any class converted to it, so iterating
// one calls every matching class stream's next() and value() methods.
// expect-error: 32:5 Actor method "sum" is not isolated: calls non-isolated function "next"
let counter: int[] = []

class Counter implements Stream<int> {
    let current: int
    let latest: int = 0

    next(): bool {
        counter.push(current)
        if current >= 3 { return false }
        latest = current
        current += 1
        return true
    }

    value(): int => latest
}

class Worker {
    sum(): int {
        values: Stream<int> := Counter(0)
        let total = 0
        for v of values { total += v }
        return total
    }
}

function main(): none {
    worker := Actor<Worker>()
    worker.sum()
}
