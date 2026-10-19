// Invalid: a static interface method call dispatches to the implementing
// class's static method, which mutates module state, so the isolated caller
// is not isolated.
// expect-error: 18:45 Isolated function "build" cannot call non-isolated function "make"
let calls = 0

interface Maker {
    static make(): int
}

class Thing implements Maker {
    static make(): int {
        calls += 1
        return calls
    }
}

isolated function build<T: Maker>(): int => T.make()

function main(): none {
    println(build<Thing>())
}
