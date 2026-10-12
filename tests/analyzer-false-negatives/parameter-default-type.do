// Invalid: the default value is string, but the parameter type is int.
// expect-error: 3:32 Cannot use default value of type string for parameter 'count' of type int
function useCount(count: int = "many"): none {
    println(count)
}

function main(): none {
    useCount()
}
