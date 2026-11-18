// Invalid: failure capture needs a Result subject; a nullable one has no failure.
// expect-error: 6:52 Failure capture requires a Result binding clause; "string | none" can only be absent as none
function find(): string | none => none

function run(): none {
    if user := find() { println(user) } else error { println("missing") }
}
