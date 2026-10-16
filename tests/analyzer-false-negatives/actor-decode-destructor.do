// Invalid: fromSerialValue builds objects without a construction expression,
// so decoding in an actor commits it to their destructors and field defaults.
// expect-error: 20:13 Actor method "load" is not isolated: accesses mutable module binding "counter"
let counter: int[] = []

class Tracked {
    let uses: int = 0
    destructor { counter.push(this.uses) }
}

class Worker {
    load(): int {
        tracked := Tracked.fromSerialValue({ uses: 1 }) else { return 0 }
        return tracked.uses
    }
}

function main(): none {
    worker := Actor<Worker>()
    println(worker.load())
}
