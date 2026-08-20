// Invalid: the default value is string, but the parameter type is int.
function useCount(count: int = "many"): none {
    println(count)
}

function main(): none {
    useCount()
}
