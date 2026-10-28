// Invalid: an interface value can hold only classes that implement it.
// expect-error: 7:54 Cannot narrow "Shape" to "Text" with "as"
interface Shape { area(): double }
class Square { side: double; area(): double => side * side }
class Text { body: string }

function body(shape: Shape): Result<Text, string> => shape as Text

function main(): none {
    println(body(Square { side: 1.0 }).isFailure())
}
