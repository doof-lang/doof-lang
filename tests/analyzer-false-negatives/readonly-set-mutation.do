// Invalid: readonly sets do not expose mutating methods.
// expect-error: 4:5 Method "add" is not available on readonly set
function record(seen: ReadonlySet<int>): none {
    seen.add(1)
}
