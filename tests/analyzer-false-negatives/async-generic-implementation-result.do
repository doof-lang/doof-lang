// Invalid: an async block may yield an owned mutable graph, but not a callback.
// Widening Generic<() => int> to Holder hides the callback behind an
// unconstrained implementation type parameter.
// expect-error: 15:16 Async block result type "Holder" cannot cross from the worker: implementation "Generic" cannot cross the async boundary: field "payload" cannot cross the async boundary: unbound type parameter "T" may hold callbacks, weak references, or streams
interface Holder {
    describe(): string
}

class Generic<T> implements Holder {
    readonly payload: T
    describe(): string => "generic"
}

function main(): none {
    promise := async {
        let holder: Holder = Generic { payload: (): int => 1 }
        yield holder
    }
    println(promise.get()!.describe())
}
