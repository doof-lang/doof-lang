import { Assert } from "std/assert"
import { EmitContext } from "./emitter-context"
import { emitCarrierAbsence, emitCarrierConversion } from "./emitter-carrier-values"
import { NoneType, PrimitiveType, UnionResolvedType } from "./semantic"

export function testCarrierModelValueConversionAndInvalidAbsence(): none {
  context := EmitContext {}
  unit := NoneType {}
  integer := PrimitiveType { name: "int" }
  optional := UnionResolvedType { types: [integer, unit] }
  wider := UnionResolvedType { types: [integer, PrimitiveType { name: "string" }, unit] }
  Assert.equal(emitCarrierConversion("effect()", unit, unit, context, .Return), "(static_cast<void>(effect()), std::monostate{})")
  Assert.equal(emitCarrierConversion("value", unit, optional, context), "(static_cast<void>(value), std::nullopt)")
  Assert.stringContains(emitCarrierConversion("source()", optional, wider, context), "const auto& _nullable_value = source(); if (doof::is_null(_nullable_value)) return std::monostate{};")
  failure := catchPanic(=> emitCarrierAbsence(integer, context))
  Assert.isTrue(failure.isFailure())
}
