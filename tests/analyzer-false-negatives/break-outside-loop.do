// Invalid: break is only valid inside a loop.
// expect-error: 4:5 Break is only valid inside a loop
function main(): none {
    break
}
