// Invalid: a callback posted from an actor carries its arguments to the
// owning domain, so every callback parameter must be boundary-safe. Otherwise
// the actor could post a mutable array to the root and keep mutating it.
// expect-error: 17:5 Actor method parameter "deliver" of type "function" cannot cross actor boundary for "Actor<Producer>": callback parameter "values" cannot cross actor boundaries: array type "int[]" is mutable
class Producer {
    start(deliver: (values: int[]): none): none {
        values := [1]
        _ := deliver.post(values)
        for index of 0..<100 {
            values.push(index)
        }
    }
}

function main(): none {
    producer := Actor<Producer>()
    producer.start((values: int[]): none => println(values.length))
}
