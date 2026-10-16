// Invalid: a value sent to an actor may be released in the actor's domain,
// running the destructor of every object it owns there.
// expect-error: 20:25 Value passed to actor method "take" may be released there, but the destructor of class "Token" accesses mutable module binding "counter"
let counter: int[] = []

class Token {
    id: int
    destructor { counter.push(this.id) }
}

class Holder { token: Token }

class Worker {
    take(holder: Holder): int => holder.token.id
}

function main(): none {
    worker := Actor<Worker>()
    holder := Holder { token: Token { id: 1 } }
    println(worker.take(holder))
}
