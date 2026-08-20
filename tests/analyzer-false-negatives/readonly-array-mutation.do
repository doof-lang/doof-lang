// Invalid: deeply readonly arrays do not expose mutating methods.
function main(): none {
    readonly values = [1, 2]
    values.push(3)
}
