// Invalid: Result<none, E> has no present value to bind; only `_` tests it.
// expect-error: 6:17 Cannot bind a none success value; use a discard binding '_ := expr' to test for success
function save(): Result<none, string> => Success()

function run(): none {
    if saved := save() { println("saved") }
}
