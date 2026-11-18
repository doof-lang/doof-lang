// Invalid: a binding clause cannot appear under ||.
// expect-error: 6:23 A binding clause cannot appear under "||"; parenthesize the initializer if the operator belongs to it, or bind the value before the condition
function find(): string | none => none

function greet(fallback: bool): none {
    if user := find() || fallback { println("hello") }
}
