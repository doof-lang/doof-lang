// Invalid: an async block's captures may be released in the worker, so their
// destructors must be isolated.
// expect-error: 14:15 Async block capture "token" may be released in the worker, but the destructor of class "Token" accesses mutable module binding "counter"
let counter: int[] = []

class Token {
    id: int
    destructor { counter.push(this.id) }
}

function main(): none {
    token := Token { id: 2 }
    pending := async {
        yield token.id
    }
    println(pending.get())
}
