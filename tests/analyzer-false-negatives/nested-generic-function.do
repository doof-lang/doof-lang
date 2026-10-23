// Invalid: local functions cannot declare type parameters.
// expect-error: 5:5 Nested generic functions are not supported; use a non-generic local function or a top-level generic function
function main(): none {
    function identity<T>(value: T): T => value
    println(identity(1))
}
