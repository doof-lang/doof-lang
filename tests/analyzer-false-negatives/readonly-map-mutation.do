// Invalid: deeply readonly maps do not expose mutating methods.
function main(): none {
    readonly values: Map<string, int> = { "one": 1 }
    values.set("two", 2)
}
