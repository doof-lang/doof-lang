// Invalid: a for-of loop over a class stream calls its next() and value()
// methods, so an actor method iterating a stream that mutates module state is
// not isolated.
// expect-error: 34:5 Actor method "sum" is not isolated: calls non-isolated function "next"
let counter: int[] = []

class Counter {
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
        let total = 0
        for v of Counter(0) {
            total += v
        }
        return total
    }
}

function main(): none {
    worker := Actor<Worker>()
    worker.sum()
}
