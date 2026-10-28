// Shared members of unions and interfaces whose arms disagree on the member's
// type or representation, and the narrowing and case forms over them.
enum Color { Red, Green, Blue }
interface Shape { area(): double }
class Square { side: double; area(): double => side * side }
class Circle { radius: double; area(): double => radius * 2.0 }
interface Named { readonly name: string }
interface Counter { let count: int }
class Tally { readonly name: string = "tally"; let count: int = 3 }
class Plain { readonly name: string = "plain" }
class Box<T> { value: T; get(): T => value }
class Num { value: int }
class Text { value: string }
interface Holder { readonly shape: Shape; readonly label: string }
class SquareHolder { readonly shape: Square; readonly label: string = "square" }
class CircleHolder { readonly shape: Circle; readonly label: string = "circle" }
class Copy { shape: Shape; label: string }
struct Wide { let x: int; y: int; total(): int => x + y }
struct Narrow { let x: int; total(): int => x }

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function text(value: int | string): string => case value { i: int -> "${i}", s: string -> s }

// No wildcard: every implementation, enum variant, bool, and Result arm is covered.
function shapeName(shape: Shape | none): string => case shape { _: Square -> "square", _: Circle -> "circle", none -> "none" }
function colorName(color: Color | none): string => case color { .Red -> "red", .Green -> "green", .Blue -> "blue", none -> "none" }
function flag(value: bool | none): string => case value { true -> "yes", false -> "no", none -> "unset" }
function outcome(result: Result<int, string> | none): string => case result { s: Success -> "${s.value}", f: Failure -> f.error, none -> "none" }
function boxed(box: Box<int> | Box<string>): string => case box { b: Box<int> -> "${b.value}", b: Box<string> -> b.value }
function tagged(value: Color | string): string => case value { .Green -> "green", s: string -> s, _ -> "other" }

function main(): int {
  // Field and method types joined across class arms.
  pair: Num | Text := Text { value: "text" }
  check(text(pair.value) == "text", "a field read returns the joined field type")
  generic: Box<int> | Box<string> := Box<int> { value: 4 }
  check(text(generic.get()) == "4", "a method call returns the joined return type")
  check(boxed(Box<string> { value: "s" }) == "s", "an explicit generic pattern selects its own member")

  // Struct arms are held by value.
  let measure: Wide | Narrow = Narrow { x: 4 }
  measure.x = 9
  check(measure.x == 9, "a struct arm field is assignable through the union")
  check(measure.total() == 9, "a struct arm method is callable through the union")
  fixed: Wide | Narrow := Wide { x: 1, y: 2 }
  check(fixed.total() == 3, "an immutable struct union calls the method on its arm")
  bound := fixed.total
  check(bound() == 3, "a bound method visits a struct arm")

  // Read-only interface fields narrowed by implementations.
  holders: Holder[] := [SquareHolder { shape: Square { side: 2.0 } }, CircleHolder { shape: Circle { radius: 1.0 } }]
  check(holders[0].shape.area() == 4.0, "an interface field read returns the interface field type")
  copied := Copy { ...holders[1] }
  check(copied.label == "circle" && copied.shape.area() == 2.0, "a spread reads covariant interface fields")
  { shape, label } := holders[0]
  check(label == "square" && shape.area() == 4.0, "destructuring reads covariant interface fields")

  // Interface narrowing to another interface.
  names: Named[] := [Tally {}, Plain {}]
  counted := names[0] as Counter
  check(case counted { s: Success -> s.value.count == 3, _: Failure -> false }, "as narrows to an overlapping interface")
  check(case names[1] as Counter { _: Success -> false, _: Failure -> true }, "as fails for a non-implementing arm")
  check(case names[0] { c: Counter -> c.count == 3, _ -> false }, "a case pattern names an overlapping interface")

  check(shapeName(Circle { radius: 1.0 }) == "circle" && shapeName(none) == "none", "interface members are exhaustive")
  check(colorName(.Blue) == "blue" && colorName(none) == "none", "enum members are exhaustive")
  check(flag(false) == "no" && flag(none) == "unset", "bool members are exhaustive")
  check(outcome(Success(2)) == "2" && outcome(Failure("bad")) == "bad" && outcome(none) == "none", "Result members are exhaustive")
  check(tagged(.Green) == "green" && tagged(Color.Red) == "other" && tagged("x") == "x", "shorthand names the enum arm")
  println("union member access ok")
  return 0
}
