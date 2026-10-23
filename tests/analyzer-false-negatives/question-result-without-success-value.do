// Invalid: Result<none, E> has no success payload, so postfix '?' has nothing to produce.
// expect-error: 6:14 Postfix '?' requires a Result with a success value, got Result<none, string>
function save(): Result<none, string> => Success()

function run(): Result<int, string> {
    saved := save()?
    return Success(1)
}
