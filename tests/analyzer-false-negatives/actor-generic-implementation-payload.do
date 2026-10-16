// Invalid: widening Generic<int[]> to Holder forgets the type argument, so an
// implementation field typed by an unconstrained type parameter may carry a
// mutable graph across the actor boundary.
// expect-error: 21:5 Actor method parameter "holder" of type "Holder" cannot cross actor boundary for "Actor<Worker>": implementation "Generic" cannot cross actor boundaries: field "payload" cannot cross actor boundaries: unbound type parameter "T" may hold mutable values
interface Holder {
    describe(): string
}

class Generic<T> implements Holder {
    readonly payload: T
    describe(): string => "generic"
}

class Worker {
    take(holder: Holder): none { }
}

function main(): none {
    values := [1]
    worker := Actor<Worker>()
    worker.take(Generic<int[]> { payload: values })
}
