// Invalid: a destructor runs in the domain that releases the object, so an
// actor method that creates and drops an object whose destructor mutates
// module state is not isolated.
// expect-error: 23:5 Actor method "poke" is not isolated: accesses mutable module binding "counter"
let counter: int[] = []

class Noisy {
    let uses: int = 0

    destructor {
        counter.push(uses)
    }
}

class Worker {
    poke(): none {
        noisy := Noisy {}
    }
}

function main(): none {
    worker := Actor<Worker>()
    worker.poke()
}
