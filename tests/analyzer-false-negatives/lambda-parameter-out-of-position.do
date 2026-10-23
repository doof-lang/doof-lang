// Invalid: a positional lambda parameter list cannot reuse a signature name at another position.
// expect-error: 5:27 Lambda parameter 'index' is parameter 2 of (it: int, index: int): int but is listed at position 1; name only signature parameters to bind them by name, or list them in order
function main(): none {
    values := [4, 5, 6]
    picked := values.map((index, value) => value)
    println(picked.length)
}
