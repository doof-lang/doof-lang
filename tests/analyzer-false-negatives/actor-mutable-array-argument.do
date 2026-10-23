// Invalid: a mutable array would be shared between the caller and the actor's domain.
// expect-error: 10:13 Actor method parameter "values" of type "int[]" cannot cross actor boundary for "Actor<Worker>": array type "int[]" is mutable
class Worker {
    count(values: int[]): int => values.length
}

function main(): none {
    worker := Actor<Worker>()
    values: int[] := [1, 2]
    println(worker.count(values))
}
