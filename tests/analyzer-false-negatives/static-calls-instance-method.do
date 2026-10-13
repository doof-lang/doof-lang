// Invalid: a static method has no instance to call an instance method on.
// expect-error: 7:9 Cannot call instance method 'increment' from a static method
class Counter {
    let count = 0
    increment(): none { count += 1 }
    static bad(): none {
        increment()
    }
}
