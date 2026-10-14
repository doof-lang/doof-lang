// Unions with interface members lower to one flat variant of implementing
// classes. Each section drives a different shape of interface union through
// C++ compilation and execution.
interface Shape { area(): double }
interface Named { name(): string }
interface Solo { solo(): int }
interface Plugin { run(): int }
interface Source<T> { pull(): T }

class Circle implements Shape { radius: double; area(): double => radius * 2.0 }
class Square implements Shape { side: double; area(): double => side * side }
class Tag implements Named { text: string; name(): string => text }
// Badge implements both interfaces, so unions of the two share its one arm.
class Badge implements Shape, Named { area(): double => 1.0; name(): string => "badge" }
class Only implements Solo { solo(): int => 7 }
class Counter implements Source<int> { let count: int = 0; pull(): int { count += 1; return count } }
class Label { text: string }

class Holder {
  let focus: Shape | none = none
}

struct Slot {
  shape: Shape | none
  weight: int
}

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

// Two interfaces and none in one union.
function describe(item: Shape | Named | none): string {
  return case item {
    badge: Badge -> "badge " + badge.name(),
    shape: Shape -> "shape " + string(shape.area()),
    named: Named -> "named " + named.name(),
    _ -> "none"
  }
}

// An interface beside an implementationless interface and a plain class.
function classify(item: Plugin | Label | Shape | none): string {
  return case item {
    _: Plugin -> "plugin",
    label: Label -> "label " + label.text,
    shape: Shape -> "shape " + string(shape.area()),
    _ -> "none"
  }
}

function soloValue(value: Solo | none): int => value?.solo() ?? -1

function pullTwice(source: Source<int> | none): int {
  first := source?.pull() ?? 0
  second := source?.pull() ?? 0
  return first + second
}

function first<T>(items: T[]): T | none {
  for item of items { return item }
  return none
}

function largest(shapes: (Shape | none)[]): double {
  let best = 0.0
  for shape of shapes {
    area := shape?.area() ?? 0.0
    if area > best { best = area }
  }
  return best
}

function load(present: bool): Result<Shape | none, string> {
  if present { return Success(Square { side: 2.0 }) }
  return Success(none)
}

function loadedArea(present: bool): Result<double, string> {
  try shape := load(present)
  return Success(shape?.area() ?? 0.0)
}

function areaOr(shape: Shape | none = none, fallback: double = -1.0): double => shape?.area() ?? fallback

function pair(shape: Shape | none, count: int): Tuple<Shape | none, int> => (shape, count)

function main(): int {
  circle := Circle { radius: 1.5 }
  square := Square { side: 3.0 }
  tag := Tag { text: "t" }
  badge := Badge {}

  // Several interfaces in one union, with a class implementing both.
  check(describe(circle) == "shape 3", "a Shape implementor matches the Shape arm")
  check(describe(tag) == "named t", "a Named implementor matches the Named arm")
  check(describe(badge) == "badge badge", "a class implementing both interfaces keeps one arm")
  check(describe(none) == "none", "none is the empty arm of a two-interface union")
  either: Shape | Named := badge
  check(describe(either) == "badge badge", "a two-interface union widens into its nullable form")

  // Implementationless interfaces stay unreachable beside real arms.
  check(classify(Label { text: "l" }) == "label l", "a class arm beside an implementationless interface")
  check(classify(square) == "shape 9", "an interface arm beside an implementationless interface")
  check(classify(none) == "none", "none beside an implementationless interface")

  // A single implementor and a generic interface.
  check(soloValue(Only {}) == 7 && soloValue(none) == -1, "a single-implementor interface union")
  check(pullTwice(Counter {}) == 3 && pullTwice(none) == 0, "a generic interface union keeps one mutable referent")

  // Stored in fields, structs, collections, tuples, and Results.
  holder := Holder {}
  holder.focus ??= circle
  holder.focus ??= square
  check(holder.focus!.area() == 3.0, "??= stores only into an absent interface field")
  maybeHolder: Holder | none := holder
  check(maybeHolder?.focus?.area() == 3.0, "optional chains pass through a nullable interface field")
  slot := Slot { shape: square, weight: 2 }
  check(slot.shape!.area() * double(slot.weight) == 18.0, "a struct field holds a nullable interface")
  check(largest([circle, none, square]) == 9.0, "an array of nullable interfaces")
  byName: Map<string, Shape | none> := { "c": circle, "n": none }
  storedNone := case byName.get("n") { s: Success -> s.value == none, _: Failure -> false }
  check(byName.get("c")!.area() == 3.0 && storedNone, "a map of nullable interfaces")
  (stored, count) := pair(square, 4)
  check(stored!.area() == 9.0 && count == 4, "a tuple element holds a nullable interface")
  check(loadedArea(true)! == 4.0 && loadedArea(false)! == 0.0, "a Result carries a nullable interface through try")
  check(areaOr() == -1.0 && areaOr(circle) == 3.0, "a default nullable interface parameter")

  // Generic code instantiated at an interface, and callbacks returning one.
  shapes: Shape[] := [square, circle]
  check(first(shapes)!.area() == 9.0, "a generic T | none instantiated at an interface")
  empty: Shape[] := []
  check(first(empty) == none, "an empty generic lookup yields none")
  pick := (big: bool): Shape | none => if big then square else none
  check(pick(true)?.area() == 9.0 && pick(false) == none, "a callback returns a nullable interface")

  // Checked narrowing and equality.
  item: Shape | Label | none := circle
  check((item as Circle)!.radius == 1.5, "as narrows a flattened union to an implementor")
  check((item as Shape)!.area() == 3.0, "as narrows a flattened union to its interface")
  check((item as Label).isFailure(), "as rejects an arm the value does not hold")
  check(item != none, "a present interface value is not none")
  println("interface unions ok")
  return 0
}
