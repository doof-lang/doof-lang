// Invalid: an interface value encodes through every implementing class.
// expect-error: 16:5 Cannot serialize interface "Pet": implementing class "Robot" does not support automatic JSON serialization
interface Pet {
    speak(): string
}
class Dog implements Pet {
    name: string
    speak(): string => "woof"
}
class Robot implements Pet {
    onSpeak: (): string
    speak(): string => onSpeak()
}
function main(): none {
    pet: Pet := Dog { name: "Rex" }
    pet.toSerialObject()
}
