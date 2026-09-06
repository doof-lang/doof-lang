import { Assert } from "std/assert"
import { EmitContext } from "./emitter-context"
import { primitive, noneType, unionType, sameType } from "./checker-types"

export function testRestrictedYieldCarrierContext(): none {
  context := EmitContext {}
  Assert.isTrue(context.valueYieldType == none)
  optional := unionType([primitive("int"), noneType()])
  context.valueYieldType = optional
  Assert.isTrue(sameType(context.valueYieldType!, optional))
  Assert.isFalse(context.valueYieldReturnsVoid)
}
