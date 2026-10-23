// Invalid: async blocks cannot capture mutable collections shared with the caller.
// expect-error: 5:30 Async block capture "values" of type "int[]" cannot cross to the worker: array type "int[]" is mutable
function main(): none {
    values: int[] := [1, 2]
    pending := async { yield values.length }
    println(pending.get())
}
