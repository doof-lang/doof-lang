// Invalid: deeply readonly arrays do not expose mutating methods.
// expect-error: 5:5 Method "push" is not available on readonly array
function main(): none {
    readonly values = [1, 2]
    values.push(3)
}
