// Invalid: a generic Map key or Set element must be hashable for each concrete instantiation.
// expect-error: 6:31 Map key type "T" is not supported when T = double; Map keys and Set elements may be byte, string, int, long, char, bool, enums, class or interface references, or tuples, unions, and structs of those
// expect-error: 10:50 Set element type "(T, int)" is not supported when T = float (contains "float"); Map keys and Set elements may be byte, string, int, long, char, bool, enums, class or interface references, or tuples, unions, and structs of those

function index<T>(key: T): Map<T, int> {
    let values: Map<T, int> = {}
    values.set(key, 1)
    return values
}
function pairs<T>(key: T): Set<Tuple<T, int>> => [(key, 1)]

function main(): none {
    index(1.5)
    pairs(2.0f)
}
