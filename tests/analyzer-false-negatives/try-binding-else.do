// Invalid: a try binding propagates failure, so it cannot also handle it with else.
// expect-error: 6:25 A 'try' binding cannot have an 'else' block; use 'try' to propagate the failure or 'name := expr else { ... }' to handle it
function load(): Result<int, string> => Success(1)

function run(): Result<int, string> {
    try value := load() else { return Success(0) }
    return Success(value)
}
