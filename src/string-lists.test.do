import { Assert } from "std/assert"

import { addAllUnique, addUnique } from "./string-lists"

function joined(values: string[]): string {
  let text = ""
  for value of values { text = text + value + ";" }
  return text
}

export function testAddUniqueKeepsFirstSeenOrder(): none {
  let values: string[] = []
  addUnique(values, "b")
  addUnique(values, "a")
  addUnique(values, "b")
  Assert.equal(joined(values), "b;a;")
}

export function testAddUniqueAcceptsEmptyString(): none {
  let values: string[] = []
  addUnique(values, "")
  addUnique(values, "")
  Assert.equal(values.length, 1)
}

export function testAddAllUniqueSkipsExistingAndRepeatedValues(): none {
  let values: string[] = ["x"]
  addAllUnique(values, ["y", "x", "y", "z"])
  Assert.equal(joined(values), "x;y;z;")
}

export function testAddAllUniqueWithNoAdditionsLeavesListUnchanged(): none {
  let values: string[] = ["x"]
  addAllUnique(values, [])
  Assert.equal(joined(values), "x;")
}
