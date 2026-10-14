// Positional literals construct the class or struct their context expects.
class Point { x, y: float }
struct Vec { x: int; y: int }
class Config { host: string; port: int = 8080; timeout: int = 30 }
class Line { start: Point; end: Point }
class Counter { count: int
  static constructor(initial: int, step: int): Counter { return Counter { count: initial + step } } }
class Box<T> { value: T; label: string }
class Pair<A, B> { first: A; second: B }

readonly ORIGIN: Point = (0.0, 0.0)

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function draw(p: Point): float => p.x + p.y
function make(): Point { return (3.0, 4.0) }
function maybe(flag: bool): Vec | none => if flag then (1, 2) else none

// The enclosing function's own type parameters are fixed inside its body.
function plain<T>(value: T): Pair<T, int> => (value, 1)
function boxed<T>(value: T): Pair<Box<T>, int> => (Box<T> { value, label: "boxed" }, 2)
function listed<T>(value: T): Pair<T[], int> => ([value], 3)
function optional<T>(value: T): Pair<T | none, int> => (value, 4)
function keyed<T>(value: T): Pair<Map<string, T>, int> => ({ "key": value }, 5)

function main(): int {
  check(draw((1.0, 2.0)) == 3.0f, "argument context")
  let p: Point = (1.0, 2.0)
  check(p.y == 2.0f, "annotation context")
  check(make().x == 3.0f, "return context")
  points: Point[] := [(1.0, 2.0), (3.0, 4.0)]
  check(points[1].x == 3.0f, "array element context")
  let verts: Point[] = []
  verts.push((5.0, 6.0))
  check(verts[0].y == 6.0f, "push context")
  let v: Vec = (5, 6)
  let copy = v
  check(copy.x + copy.y == 11, "struct construction")
  check((maybe(true)!).y == 2 && maybe(false) == none, "nullable struct context")
  let config: Config = ("localhost", 9000)
  check(config.port == 9000 && config.timeout == 30, "trailing defaults")
  let line = Line ((0.0, 0.0), (1.0, 1.0))
  check(line.end.x == 1.0f, "nested positional literals")
  let counter: Counter = (10, 5)
  check(counter.count == 15, "custom constructor")
  let box: Box<int> = (7, "seven")
  check(box.value == 7 && box.label == "seven", "generic class")
  check(plain("p").first == "p" && plain("p").second == 1, "enclosing type parameter")
  check(boxed(8).first.value == 8 && boxed(8).first.label == "boxed", "nested enclosing type parameter")
  check(listed("l").first[0] == "l" && listed("l").second == 3, "array of enclosing type parameter")
  check(optional(9).first == 9 && optional(9).second == 4, "nullable enclosing type parameter")
  check(keyed("k").first.get("key")! == "k" && keyed("k").second == 5, "map of enclosing type parameter")
  check(ORIGIN.x == 0.0f, "module initializer")
  pair := (1, "tuple")
  check(pair._2 == "tuple", "uncontextual literal stays a tuple")
  let typed: Tuple<float, float> = (1.0f, 2.0f)
  check(typed._1 == 1.0f, "tuple context stays a tuple")
  println("ok")
  return 0
}
