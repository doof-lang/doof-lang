// Invalid: a case expression over a nullable subject must handle none.
// expect-error: 3:43 Case expression must be exhaustive
function value(input: int | none): int => case input {
    present: int -> present
}
