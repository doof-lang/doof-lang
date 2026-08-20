// Invalid: Dog is not a possible type of the Cat subject.
class Cat {}
class Dog {}

function describe(value: Cat): string => case value {
    dog: Dog -> "dog"
    _ -> "cat"
}

function main(): none {
    println(describe(Cat {}))
}
