// Invalid: an async call runs on a worker, so its target must be isolated.
// expect-error: 11:22 Async call is not isolated: calls non-isolated function "bump"
let calls = 0

function bump(): int {
    calls += 1
    return calls
}

function main(): none {
    pending := async bump()
    println(pending.get())
}
