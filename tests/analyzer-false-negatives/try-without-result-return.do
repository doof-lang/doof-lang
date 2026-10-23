// Invalid: try needs a Result-returning function or catch block to propagate the failure into.
// expect-error: 6:5 'try' requires a Result-returning function, a catch block, or native entry-script scope
function load(): Result<int, string> => Success(1)

function main(): none {
    try value := load()
    println(value)
}
