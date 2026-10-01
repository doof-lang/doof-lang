// Interfaces nobody implements: every helper must still compile, and no value
// of the interface can exist at runtime.
interface Shape {
  name: string
  let scale: double
  area(): double
  describe(prefix: string): string
}

// Only generic implementers that are never instantiated.
interface Labelled { label(): string }
class Tagged<T> implements Labelled { value: T; label(): string => "tagged" }

class Canvas {
  shapes: Shape[] = []
  focus: Shape | none = none
}

function describe(shape: Shape): string => shape.describe("shape: ") + shape.name + " " + string(shape.area())
function rescale(shape: Shape): none { shape.scale = shape.scale * 2.0 }
function maybeName(shape: Shape | none): string => shape?.name ?? "none"
function total(shapes: Shape[]): double {
  let sum = 0.0
  for shape of shapes { sum += shape.area() }
  return sum
}
function same(a: Shape, b: Shape): bool => a == b
function firstName(shapes: Shape[]): string => shapes.map(=> it.name).find(=> it.length > 0) ?? ""
function label(item: Labelled): string => item.label()
function labelOrNone(item: Labelled | none): string => item?.label() ?? "none"
function identity<T>(value: T): T => value
function pick(shape: Shape): string {
  { name, scale } := shape
  return identity(name) + string(scale)
}

// A generic interface with no implementers, and one returned from another.
interface Reader<T> { read(): T }
interface Source { open(): Reader<int> }
function readAll(source: Source): int => source.open().read()

// A struct satisfies an interface only as a generic bound.
interface Sized { size(): int }
struct Block { width: int
size(): int => width }
function sizeOf<T: Sized>(value: T): int => value.size()

class Circle { radius: double }
function classify(value: Shape | Circle | none): string => case value {
  _: Circle -> "circle",
  _: Shape -> "shape",
  _ -> "none",
}
function asCircle(value: Shape | Circle): double {
  circle := value as Circle else { return -1.0 }
  return circle.radius
}

// Decoding can never produce a value, so it always fails.
function decode(value: SerialValue): Result<Shape, string> => Shape.fromSerialValue(value)

function main(): int {
  canvas := Canvas {}
  if total(canvas.shapes) != 0.0 || maybeName(canvas.focus) != "none" { return 1 }
  if firstName(canvas.shapes) != "" || labelOrNone(none) != "none" { return 2 }
  if sizeOf(Block { width: 3 }) != 3 { return 3 }
  if classify(Circle { radius: 1.0 }) != "circle" || classify(none) != "none" { return 4 }
  if asCircle(Circle { radius: 2.0 }) != 2.0 { return 5 }
  decoded := decode({ name: "x", scale: 1.0 })
  message := case decoded { _: Success -> "", failure: Failure -> failure.error }
  if message != "Interface Shape has no implementing classes" { return 6 }
  return 0
}
