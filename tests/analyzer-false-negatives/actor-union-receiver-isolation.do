// Invalid: a call through a union receiver may dispatch to any member's method,
// so an actor method reaching a member that mutates module state is not isolated.
// expect-error: 22:5 Actor method "run" is not isolated: calls non-isolated function "poke"
let counter: int[] = []

class Touches {
    touch(): none { counter.push(1) }
}

class Quiet {
    touch(): none { }
}

function poke(target: Touches | Quiet): none { target.touch() }

class Worker {
    run(): none { poke(Touches {}) }
}

function main(): none {
    worker := Actor<Worker>()
    worker.run()
}
