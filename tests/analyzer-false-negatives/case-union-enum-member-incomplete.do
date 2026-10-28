// Invalid: inside a union, enum values cover only the enum they name.
// expect-error: 6:47 Case expression must be exhaustive
enum Color { Red, Green }
enum Tone { Red, Dark }

function name(value: Color | Tone): string => case value {
    Color.Red -> "red",
    Color.Green -> "green",
    Tone.Red -> "tone red"
}

function main(): none {
    println(name(Tone.Dark))
}
