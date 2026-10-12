// Invalid: Dog is not a possible type of the Cat subject.
// expect-error: 7:5 Case type pattern "Dog" cannot match subject type "Cat"
class Cat {}
class Dog {}

function describe(value: Cat): string => case value {
    dog: Dog -> "dog"
    _ -> "cat"
}

function main(): none {
    println(describe(Cat {}))
}
