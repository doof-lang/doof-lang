// Invalid: case-expression arms cannot affect outer control flow, so try is rejected in them.
// expect-error: 8:13 'try' cannot be used inside a value-producing block; handle the Result outside the block
function load(): Result<int, string> => Success(1)

function run(useLoad: bool): Result<int, string> {
    value := case useLoad {
        true -> {
            try loaded := load()
            yield loaded
        },
        false -> 0
    }
    return Success(value)
}
