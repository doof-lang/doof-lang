function check(value: bool): none { if !value { panic("emission consolidation check failed") } }
class Box { const kind = "box"
  value: int = 7
  source: SourceLocation = @caller }
struct Row<T> { value: T
  rest: T[] = [] }
class Factory { value: int
  static constructor(value: int = 9): Factory => Factory { value } }
class A { callback: (value: int | none): int }
class B { callback: (value: int | none): int }
class Stopper {
  stop(): never => panic("method")
  block(): never { panic("block") }
  generic<T>(value: T): never => panic("generic")
  make(): (): int { let count = 0
    return (): int => { count += 1
      return count } }
}
function stop(): never => panic("function")
function count(value: int | none): int => if value == none then 1 else 0
function dispatch(value: A | B): int { absent := none
  return value.callback(absent) }
function contextual(): Box => {}
function main(): int {
  a := Box()
  b := Box {}
  c := contextual()
  check(a.value == 7 && b.value == 7 && c.value == 7)
  check(c.kind == "box" && c.source.line == 23)
  check(c.source.functionName == "contextual")
  check(Row<int>(3).rest.length == 0)
  check(Row<int> { value: 3 }.rest.length == 0)
  row: Row<int> := { value: 3 }
  check(row.value == 3 && row.rest.length == 0)
  check(Factory().value == 9 && Factory {}.value == 9)
  copy := Box { ...a, value: 8 }
  check(copy.value == 8 && copy.source == a.source)
  check(dispatch(A { callback: count }) == 1)
  stopper := Stopper {}
  next := stopper.make()
  check(next() == 1 && next() == 2)
  check(catchPanic((): none => { stop() }).isFailure())
  check(catchPanic((): none => { stopper.stop() }).isFailure())
  check(catchPanic((): none => { stopper.block() }).isFailure())
  check(catchPanic((): none => { stopper.generic(3) }).isFailure())
  check(genericDefault(3) == 0 && genericDefault{value: 4} == 0)
  selected: Left | Right := { kind: "left", value: 4 }
  case selected { left: Left -> { check(left.value == 4) } _ -> { panic("wrong class") } }
  return 0
}
function genericDefault<T>(value: T, rest: T[] = []): int => rest.length
class Left { const kind = "left"
  value: int }
class Right { const kind = "right"
  other: string }

