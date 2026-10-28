// Invalid: explicit method type arguments do not determine the class's own.
// expect-error: 9:14 Cannot infer type arguments for generic class 'Stack' from this call to static method 'empty'; its arguments must determine T, or write Stack<T>.empty(...)
class Stack<T> {
    let items: T[] = []
    static empty<U>(): Stack<U> => Stack<U> {}
}

function main(): none {
    stack := Stack.empty<int>()
    println(stack.items.length)
}
