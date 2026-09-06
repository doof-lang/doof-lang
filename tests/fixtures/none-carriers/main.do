class Item { number: int = 7 }
class Arrays { values: none[][] }
class Maps { values: Map<string, none>[] }
class Tuples { values: Tuple<none, int>[] }
function identity<T>(value: T): T => value
function block<T>(value: T): T { return value }
function widen(value: (weak Item) | none): (weak Item) | string | none => value
function expired(): weak Item { item := Item {}
return item }
function main(): int {
 nativeMatrix()
 identity(none)
 block(none)
 if identity(7) != 7 || block(9) != 9 { return 1 }
 absent := none
 let ints: Map<string, int | none> = {}
 ints.set("a", absent)
 ints.set("b", none)
 ints.set("c", 7)
 if (try! ints.get("a")) != none || (try! ints.get("b")) != none { return 2 }
 if (try! ints.get("c")) == none { return 3 }
 let items: Map<string, Item | none> = {}
 items.set("a", none)
 items.set("b", absent)
 items.set("c", Item {})
 if (try! items.get("a")) != none || (try! items.get("b")) != none { return 4 }
 if (try! items.get("c")) == none { return 5 }
 if widen(none) != none || widen(expired()) == none { return 6 }
 item := Item {}
 let reference: (weak Item) | none = item
 if widen(reference) == none { return 7 }
 let bad: JsonValue = { values: [none] }
 arrayResult := Arrays.fromJsonValue(bad)
 case arrayResult { error: Failure -> { if !error.error.contains("[0]") || !error.error.contains("Expected array") { return 8 } }
_ -> { return 9 } }
 if Maps.fromJsonValue(bad).isSuccess() || Tuples.fromJsonValue(bad).isSuccess() { return 10 }
 let shortTuple: JsonValue = { values: [[none]] }
 let longTuple: JsonValue = { values: [[none, 7, 8]] }
 if Tuples.fromJsonValue(shortTuple).isSuccess() || Tuples.fromJsonValue(longTuple).isSuccess() { return 11 }
 let goodArray: JsonValue = { values: [[none]] }
 let goodMap: JsonValue = { values: [{ a: none }] }
 let goodTuple: JsonValue = { values: [[none, 7]] }
 if !Arrays.fromJsonValue(goodArray).isSuccess() || !Maps.fromJsonValue(goodMap).isSuccess() || !Tuples.fromJsonValue(goodTuple).isSuccess() { return 12 }
 return 0
}

class Marker {}
function absent<T>(sample: T): T | none => none
function wider<T>(value: T | none): T | Marker | none => value
function probe<T>(sample: T): none {
  n := none
  let slot: T | none = n
  if slot != n { panic("initial absence") }
  slot = sample
  if slot == n { panic("present assignment") }
  slot = absent(sample)
  if slot != n { panic("generic absence") }
  if wider<T>(slot) != none { panic("absent widening") }
  if wider<T>(sample) == none { panic("present widening") }
  values: (T | none)[] := [none, sample]
  values.push(n)
  if values[0] != n || values[1] == n || values[2] != n { panic("array carriers") }
  let map: Map<string, T | none> = {}
  map.set("absent", n)
  map.set("present", sample)
  if (try! map.get("absent")) != none || (try! map.get("present")) == none { panic("map carriers") }
}

enum Mode { First, Second }
struct Point { x: int }
let effects = 0
function unitEffect(): none { effects += 1 }
function unitResult(): Result<none, string> { effects += 1
return Success {} }
function consume(value: none): none { effects += 10 }
function unitPair(): Tuple<none, int> => (unitEffect(), 7)
function nativeMatrix(): none {
  probe(7)
  probe(7L)
  probe(1.5)
  probe(true)
  probe('a')
  probe("text")
  probe(Mode.First)
  probe(Point { x: 7 })
  probe(Item {})
  probe([1, 2])
  let map: Map<string, int> = { a: 7 }
  probe(map)
  let set: Set<int> = [1, 2]
  probe(set)
  probe((7, "value"))
  probe((): int => 7)
  let result: Result<int, string> = Success { value: 7 }
  probe(result)
  let wrapped: Result<int, string> | Marker | none = result
  case wrapped {
    payload: Result<int, string> -> { if (try! payload) != 7 { panic("nested result payload") } }
    _ -> { panic("nested result arm") }
  }
  let failed: Result<int, string> = Failure { error: "expected" }
  if failed.error != "expected" { panic("result error access") }
  consume(unitEffect())
  consume(try! unitResult())
  consume(unitResult()!)
  unitPair()
  callback := (): none => unitEffect()
  callback()
  if effects != 35 { panic("unit evaluation count") }
}
