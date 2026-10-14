// Invalid: a decoded union needs one member per JSON kind; int and double are both JSON numbers.
// expect-error: 6:5 Type "Reading" does not support automatic JSON deserialization (field "value" has union type "int | double", whose members int and double both decode from a JSON number)
class Reading { value: int | double }

function decode(json: SerialValue): none {
    Reading.fromSerialValue(json)
}
