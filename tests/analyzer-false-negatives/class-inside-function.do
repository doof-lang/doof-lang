// Invalid: type declarations are module-level declarations.
// expect-error: 4:5 Class declarations are only valid at module level
function main(): none {
    class Local { x: int }
}
