// Invalid: return is forbidden inside a trailing lambda body.
// expect-error: 5:24 'return' cannot be used inside a trailing lambda; use an explicit lambda instead
function main(): none {
    values := [1, 2]
    values.forEach() { return }
}
