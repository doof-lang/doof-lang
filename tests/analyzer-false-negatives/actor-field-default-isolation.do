// Invalid: constructing a class evaluates its omitted field defaults, so an
// actor method that relies on a default reading module state is not isolated.
// expect-error: 16:13 Actor method "make" is not isolated: accesses mutable module binding "counter"
let counter: int[] = []

class Thing {
    n: int = counter.length
}

class Worker {
    make(): int => Thing {}.n
}

function main(): none {
    worker := Actor<Worker>()
    println(worker.make())
}
