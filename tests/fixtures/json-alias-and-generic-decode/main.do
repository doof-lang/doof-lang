// Named class-union aliases and Serializable type parameters decode JSON.
class Circle { kind: "circle"; radius: double }
class Rect { kind: "rect"; width, height: double }
type Shape = Circle | Rect
class User { name: string; age: int = 0 }
struct Point { x: int; y: int }
enum Color { Red, Green }
enum Wire { Small = "small" }

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function area(shape: Shape): double => case shape {
  c: Circle -> c.radius,
  r: Rect -> r.width * r.height
}

function decode<T: Serializable>(json: SerialValue): Result<T, string> { return T.fromSerialValue(json) }
function decodeLenient<T: Serializable>(json: SerialValue): Result<T, string> { return T.fromSerialValue(json, true) }

function main(): int {
  check(area(Shape.fromSerialValue({ kind: "circle", radius: 5.0 })!) == 5.0, "alias decodes the circle arm")
  check(area(Shape.fromSerialValue({ kind: "rect", width: 2.0, height: 3.0 })!) == 6.0, "alias decodes the rect arm")
  unknown := Shape.fromSerialValue({ kind: "triangle" })
  check(case unknown { _: Success -> "", f: Failure -> f.error } == "Unknown kind: \"triangle\"", "unknown discriminator fails")
  missing := Shape.fromSerialValue({ radius: 1.0 })
  check(case missing { _: Success -> "", f: Failure -> f.error } == "Missing or invalid discriminator field \"kind\"", "missing discriminator fails")

  check((decode<User>({ name: "Ada", age: 36 })!).age == 36, "generic class decode")
  check((decode<Point>({ x: 1, y: 2 })!).y == 2, "generic struct decode")
  check(decode<User>({ name: "Ada", age: "36" }).isFailure(), "strict generic decode rejects a string number")
  check((decodeLenient<User>({ name: "Ada", age: true })!).age == 1, "lenient generic decode coerces")
  check((decode<Color>(1)!) == Color.Green, "generic int enum decode")
  check((decode<Wire>("small")!) == Wire.Small, "generic string enum decode")
  check(decode<Color>(7).isFailure(), "unknown enum value fails")
  println("ok")
  return 0
}
