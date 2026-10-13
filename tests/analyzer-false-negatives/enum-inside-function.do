// Invalid: type declarations are module-level declarations.
// expect-error: 4:5 Enum declarations are only valid at module level
function main(): none {
    enum Color { Red, Green }
}
