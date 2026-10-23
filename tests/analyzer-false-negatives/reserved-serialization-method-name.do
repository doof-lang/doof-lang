// Invalid: toSerialObject is a reserved compiler-generated method name.
// expect-error: 5:5 Method name "toSerialObject" is reserved for compiler-generated reflection and JSON support
class Payload {
    value: int = 0
    toSerialObject(): int => this.value
}
