// Invalid: actor-dispatched methods run in the actor's domain and cannot reach mutable module state.
// expect-error: 14:13 Actor method "add" is not isolated: accesses mutable module binding "total"
let total = 0

class Accumulator {
    add(value: int): int {
        total += value
        return total
    }
}

function main(): none {
    accumulator := Actor<Accumulator>()
    println(accumulator.add(1))
}
