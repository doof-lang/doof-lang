// Invalid: a static method has no instance whose field it could read.
// expect-error: 6:9 Cannot access instance field 'count' from a static method
class Counter {
    let count = 0
    static reset(): none {
        count = 0
    }
}
