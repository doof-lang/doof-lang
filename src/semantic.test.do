import { Assert } from "std/assert"
import { Scope } from "./semantic"
import { primitive, sameType } from "./checker-types"

export function testYieldExpectationSeparateFromInference(): none {
  scope := Scope { parent: none }
  scope.yieldType = primitive("int")
  Assert.isTrue(scope.yieldExpectedType == none)
  scope.yieldExpectedType = primitive("long")
  Assert.isTrue(sameType(scope.yieldType!, primitive("int")))
}
