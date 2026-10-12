// Invalid: deeply readonly maps do not expose mutating methods.
// expect-error: 5:5 Method "set" is not available on readonly map
function main(): none {
    readonly values: Map<string, int> = { "one": 1 }
    values.set("two", 2)
}
