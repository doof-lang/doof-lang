import { Assert } from "std/assert"

function observedPair(counter: int[]): Tuple<int, string> {
  counter[0] = counter[0] + 1
  return (counter[0], "value")
}

function identity<T>(value: T): T => value

export function testTupleAritiesTypesAndNestedValues(): none {
  empty: Tuple<> := ()
  singleton: Tuple<int> := (7,)
  mixed := (42, "hello", true)
  nested := ((1, "one"), [2, 3])

  Assert.equal(empty, ())
  (only) := singleton
  (number, label, enabled) := mixed
  (inner, values) := nested
  (_, word) := inner
  Assert.equal(only, 7)
  Assert.equal(number, 42)
  Assert.equal(label, "hello")
  Assert.equal(enabled, true)
  Assert.equal(word, "one")
  Assert.equal(values[1], 3)
}

export function testTupleDestructuringPermutations(): none {
  mixed := (42, "hello", true)
  (number, _, enabled) := mixed
  Assert.equal(number, 42)
  Assert.equal(enabled, true)

  (partial, label) := mixed
  Assert.equal(partial, 42)
  Assert.equal(label, "hello")

  let mutableNumber = 0
  let mutableLabel = ""
  (mutableNumber, mutableLabel) = (7, "seven")
  Assert.equal(mutableNumber, 7)
  Assert.equal(mutableLabel, "seven")

  let (left, right) = (1, 2)
  left = left + right
  Assert.equal(left, 3)
}

export function testTupleNestingGenericsCollectionsAndReturns(): none {
  generic := identity<Tuple<int, string> >((9, "nine"))
  (genericNumber, genericWord) := generic
  Assert.equal(genericNumber, 9)
  Assert.equal(genericWord, "nine")

  let total = 0
  for number, word of [(1, "a"), (2, "bb"), (3, "ccc")] {
    total = total + number + word.length
  }
  Assert.equal(total, 12)

  (inner, values) := ((4, "four"), [5, 6])
  (innerNumber, innerWord) := inner
  Assert.equal(innerNumber + values[0], 9)
  Assert.equal(innerWord, "four")
}

export function testTupleDestructuringEvaluatesSourceOnce(): none {
  counter := [0]
  (number, label) := observedPair(counter)
  Assert.equal(counter[0], 1)
  Assert.equal(number, 1)
  Assert.equal(label, "value")
}
