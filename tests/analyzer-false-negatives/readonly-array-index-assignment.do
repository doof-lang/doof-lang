// Invalid: element assignment is a mutation, so it is rejected through a readonly array.
// expect-error: 5:5 Cannot assign through readonly array
function main(): none {
    readonly values = [1, 2]
    values[0] = 3
}
