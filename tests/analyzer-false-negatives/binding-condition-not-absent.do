// Invalid: a binding condition needs a nullable or Result subject.
// expect-error: 4:17 Binding condition requires a nullable or Result value; "count" has type "int"
function report(count: int): none {
    if value := count { println(value) }
}
