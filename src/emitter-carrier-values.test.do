import { Assert } from "std/assert"
import { EmitContext } from "./emitter-context"
import { emitCarrierAbsence, emitCarrierConversion } from "./emitter-carrier-values"
import { FailureResolvedType, NoneType, PrimitiveType, ResultResolvedType, SuccessResolvedType, UnionResolvedType } from "./semantic"

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

export function testCarrierModelRewrapsResultArmsForTheirTargetResult(): none {
  context := EmitContext {}
  integer := PrimitiveType { name: "int" }
  long_ := PrimitiveType { name: "long" }
  string_ := PrimitiveType { name: "string" }
  boolean := PrimitiveType { name: "bool" }
  success := emitCarrierConversion("success", SuccessResolvedType { valueType: integer }, ResultResolvedType { valueType: long_, errorType: boolean }, context)
  Assert.stringContains(success, "doof::Result<int64_t, bool>")
  Assert.stringContains(success, "doof::Success<int64_t>{_result_arm.value}")
  failure := emitCarrierConversion("failure", FailureResolvedType { errorType: string_ }, ResultResolvedType { valueType: boolean, errorType: string_ }, context)
  Assert.stringContains(failure, "doof::Result<bool, std::string>")
  Assert.stringContains(failure, "doof::Failure<std::string>{_result_arm.error}")
}
