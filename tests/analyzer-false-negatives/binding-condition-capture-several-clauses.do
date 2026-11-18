// Invalid: failure capture needs a condition that is one Result binding clause.
// expect-error: 6:67 Failure capture requires a condition that is a single Result binding clause
function load(): Result<int, string> => Success(1)

function run(): none {
    if value := load() && value > 0 { println(value) } else error { println(error) }
}
