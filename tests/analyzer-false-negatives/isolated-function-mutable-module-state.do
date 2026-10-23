// Invalid: an explicitly isolated function cannot read mutable module state.
// expect-error: 5:37 Isolated function "current" is not isolated: accesses mutable module binding "counter"
let counter = 0

isolated function current(): int => counter
