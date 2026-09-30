// Literal-valued fields, including enum members, discriminate unions and are
// validated when decoding JSON.
enum ShapeKind { Circle, Rectangle }
enum Wire { Small = "small", Large = "large" }
class CircleShape { kind: ShapeKind.Circle; radius: double }
class RectangleShape { kind: ShapeKind.Rectangle; width, height: double }
type Shape = CircleShape | RectangleShape
class Tagged { label: "tagged"; size: Wire.Large; version: -2; enabled: true }

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function area(shape: Shape): double => case shape {
  c: CircleShape -> c.radius,
  r: RectangleShape -> r.width * r.height
}

function failureOf<T>(result: Result<T, string>): string => case result {
  _: Success -> "",
  f: Failure -> f.error
}

function main(): int {
  let circle: Shape = { kind: .Circle, radius: 5.0 }
  let rectangle: Shape = { kind: ShapeKind.Rectangle, width: 2.0, height: 3.0 }
  check(area(circle) == 5.0, "enum discriminator selects CircleShape")
  check(area(rectangle) == 6.0, "enum discriminator selects RectangleShape")
  check(CircleShape { radius: 1.0 }.kind == ShapeKind.Circle, "construction fills the enum field")

  check(failureOf(CircleShape.fromSerialValue({ kind: 0, radius: 2.0 })) == "", "matching enum value decodes")
  check(failureOf(CircleShape.fromSerialValue({ radius: 2.0 })) == "", "absent literal field decodes")
  check(failureOf(CircleShape.fromSerialValue({ kind: 1, radius: 2.0 })) == "Field \"kind\" must be ShapeKind.Circle", "mismatched enum value fails")
  check(failureOf(Tagged.fromSerialValue({ label: "tagged", size: "large", version: -2, enabled: true })) == "", "matching literals decode")
  check(failureOf(Tagged.fromSerialValue({ size: "small" })) == "Field \"size\" must be Wire.Large", "string enum mismatch fails")
  check(failureOf(Tagged.fromSerialValue({ version: 3 })) == "Field \"version\" must be -2", "negative literal mismatch fails")
  check(failureOf(Tagged.fromSerialValue({ enabled: false })) == "Field \"enabled\" must be true", "bool literal mismatch fails")
  println("ok")
  return 0
}
