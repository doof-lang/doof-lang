// Invalid: try can only propagate a failure whose error type matches the enclosing Result.
// expect-error: 6:5 Cannot propagate error string from function returning Result<int, int>
function load(): Result<int, string> => Success(1)

function run(): Result<int, int> {
    try value := load()
    return Success(value)
}
