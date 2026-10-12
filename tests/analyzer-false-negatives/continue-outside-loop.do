// Invalid: continue is only valid inside a loop.
// expect-error: 4:5 Continue is only valid inside a loop
function main(): none {
    continue
}
