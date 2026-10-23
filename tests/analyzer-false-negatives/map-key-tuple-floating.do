// Invalid: Map key validation recurses into tuples, so a floating-point member is rejected.
// expect-error: 4:17 Map key type "(int, double)" is not supported (contains "double"); Map keys and Set elements may be byte, string, int, long, char, bool, enums, class or interface references, or tuples, unions, and structs of those
function main(): none {
    lookup: Map<Tuple<int, double>, string> := {}
    println(lookup.size)
}
