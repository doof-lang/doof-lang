// Invalid: a condition binding is not in scope in the else branch.
// expect-error: 6:56 "user" is not in scope here; it is bound only when its condition holds
function find(): string | none => none

function greet(): none {
    if user := find() { println(user) } else { println(user) }
}
