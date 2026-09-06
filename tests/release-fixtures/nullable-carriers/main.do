import { Assert } from "std/assert"

class Item { value: int }
struct Value { value: int }
class Rows<T> {
  rows: T[]
  rowAt(index: int): T | none {
    if index < 0 || index >= rows.length { return none }
    return rows[index]
  }
  hasRow(index: int): bool {
    row := rowAt(index) as T else { return false }
    return true
  }
}

function load<T>(value: T, ok: bool): Result<T, string> {
  if ok { return Success { value: value } }
  return Failure { error: "missing" }
}

function optional<T>(value: T, ok: bool): T | none {
  return try? load(value, ok)
}

function fail<E>(error: E, ok: bool): Result<int, E> {
  if ok { return Success { value: 7 } }
  return Failure { error: error }
}

function capture<E>(error: E, ok: bool): E | none {
  return catch { try value := fail(error, ok) }
}

function unitTuple(): Tuple<none, int> => (none, 7)

class Effect {
  rerollScope: int
  readonly rerollScopes: int[]
}

function firstScope(effect: Effect): int {
  readonly scopes: int[] = if effect.rerollScopes.length == 0 then [effect.rerollScope] else effect.rerollScopes
  return scopes[0]
}

function main(): none {
  item := Item { value: 7 }
  rows := Rows<Item> { rows: [item] }
  Assert.isTrue(rows.rowAt(-1) == none)
  Assert.equal(rows.rowAt(0)!.value, 7)
  Assert.isTrue(rows.rowAt(1) == none)
  Assert.isTrue(rows.hasRow(0))
  Assert.isFalse(rows.hasRow(1))
  integers := Rows<int> { rows: [7] }
  Assert.equal(integers.rowAt(0)!, 7)
  Assert.isTrue(integers.rowAt(1) == none)
  Assert.isTrue(integers.hasRow(0))
  Assert.isFalse(integers.hasRow(1))
  values := Rows<Value> { rows: [Value { value: 7 }] }
  Assert.equal(values.rowAt(0)!.value, 7)
  Assert.isTrue(values.rowAt(-1) == none)
  nested := Rows<Item | none> { rows: [item, none] }
  Assert.equal(nested.rowAt(0)!.value, 7)
  Assert.isTrue(nested.rowAt(1) == none)
  Assert.isTrue(nested.rowAt(2) == none)
  optionalValues: (int | none)[] := [none, 7]
  Assert.isTrue(optionalValues[0] == none)
  Assert.equal(optionalValues[1]!, 7)
  units: none[] := [none]
  Assert.equal(units.length, 1)
  Assert.equal(unitTuple()._2, 7)
  Assert.equal(firstScope(Effect { rerollScope: 7, rerollScopes: [] }), 7)
  Assert.equal(firstScope(Effect { rerollScope: 7, rerollScopes: [9] }), 9)
  Assert.isTrue(optional(item, false) == none)
  Assert.equal(optional(item, true)!.value, 7)
  Assert.isTrue(optional(7, false) == none)
  Assert.equal(optional(7, true)!, 7)
  Assert.isTrue(capture(item, true) == none)
  Assert.equal(capture(item, false)!.value, 7)
  Assert.isTrue(capture(7, true) == none)
  Assert.equal(capture(7, false)!, 7)
  println("nullable carriers passed")
}
