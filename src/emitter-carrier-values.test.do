import { Assert } from "std/assert"
import { EmitContext } from "./emitter-context"
import { emitCarrierAbsence, emitCarrierConversion } from "./emitter-carrier-values"
import { ClassType, FailureResolvedType, InterfaceType, NoneType, PrimitiveType, ResultResolvedType, SuccessResolvedType, Symbol, UnionResolvedType, WeakResolvedType } from "./semantic"

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

export function testStrongInterfaceValuesWeakPromoteIntoOptionalWeakVariants(): none {
  context := EmitContext { modulePath: "/main.do" }
  shape := InterfaceType { name: "Shape", symbol: Symbol { kind: "interface", name: "Shape", module: "/main.do", exported: false } }
  target := WeakResolvedType { inner: UnionResolvedType { types: [shape, NoneType {}] } }
  Assert.equal(emitCarrierConversion("shape", shape, target, context), "doof::weak_promote<std::optional<doof::union_t<doof::weak_arms<Shape>>>>(shape)")
  Assert.equal(emitCarrierConversion("held", target, target, context), "held")
}

export function testWeakReferencesWidenThroughTheirWeakCarriers(): none {
  context := EmitContext { modulePath: "/main.do" }
  shape := InterfaceType { name: "Shape", symbol: Symbol { kind: "interface", name: "Shape", module: "/main.do", exported: false } }
  circle := ClassType { name: "Circle", symbol: Symbol { kind: "class", name: "Circle", module: "/main.do", exported: false } }
  label := ClassType { name: "Label", symbol: Symbol { kind: "class", name: "Label", module: "/main.do", exported: false } }
  optionalShape := WeakResolvedType { inner: UnionResolvedType { types: [shape, NoneType {}] } }
  wider := WeakResolvedType { inner: UnionResolvedType { types: [shape, label, NoneType {}] } }
  Assert.equal(emitCarrierConversion("held", optionalShape, wider, context), "doof::weak_promote<std::optional<doof::union_t<doof::weak_arms<Shape>, std::weak_ptr<Label>>>>(held)")
  Assert.equal(emitCarrierConversion("held", WeakResolvedType { inner: circle }, WeakResolvedType { inner: shape }, context), "doof::variant_promote<doof::union_t<doof::weak_arms<Shape>>>(held)")
}
