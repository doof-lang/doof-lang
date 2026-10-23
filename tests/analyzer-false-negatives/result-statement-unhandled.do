// Invalid: a Result returned by a bare call statement cannot be silently discarded.
// expect-error: 6:5 Result value must be handled
function save(): Result<int, string> => Success(1)

function main(): none {
    save()
}
