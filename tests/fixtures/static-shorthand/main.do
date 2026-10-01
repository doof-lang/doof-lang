enum Mode { Fast, Slow }
class Matrix {
  value: int
  static zero = Matrix { value: 0 }
  static readonly missing: Matrix | none = none
  static identity(): Matrix => Matrix { value: 1 }
  static scaled(by: int): Matrix => Matrix { value: by }
  static parse(text: string): Matrix | none => if text == "one" then Matrix { value: 1 } else none
}
struct Vec {
  x: int
  static unit(): Vec => Vec { x: 1 }
}
class Holder {
  a: Matrix = .zero
  b: Matrix = .identity()
  c: Matrix | none = .scaled(7)
  d: Matrix | none = .missing
  v: Vec = .unit()
  mode: Mode | none = .Slow
}
function sum(m: Matrix = .identity(), n: Matrix = .scaled(3), z: Matrix = .zero): int => m.value + n.value + z.value
function optional(m: Matrix | none = .parse("one")): int => m?.value ?? -1
function main(): int {
  m: Matrix := .identity()
  parsed: Matrix | none := .parse("one")
  absent: Matrix | none := .parse("two")
  widened: Matrix | none := .scaled(4)
  h := Holder {}
  if sum() != 4 || sum(.scaled(5)) != 8 || m.value != 1 { return 1 }
  if (parsed?.value ?? 0) != 1 || absent != none || (widened?.value ?? 0) != 4 { return 2 }
  if h.a.value != 0 || h.b.value != 1 || (h.c?.value ?? 0) != 7 || h.d != none || h.v.x != 1 || h.mode != .Slow { return 3 }
  if optional() != 1 || optional(.parse("two")) != -1 { return 4 }
  return 0
}
