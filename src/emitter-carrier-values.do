// C++ operations on the pure carrier model. No AST inspection or assignability.
// Callers pass specialized checked types and the native source position.

import { ResolvedType } from "./semantic"
import { CarrierPosition, carrierOf } from "./emitter-carriers"
import { EmitContext } from "./emitter-context"
import { emitContextType, specializeEmitType } from "./emitter-types"

export function emitCarrierAbsence(type_: ResolvedType, context: EmitContext): string {
  concreteType := specializeEmitType(type_, context)
  carrier := carrierOf(concreteType)
  case carrier.kind {
    .Unit -> { return "std::monostate{}" }
    .SharedPointer -> { return "nullptr" }
    .Optional -> { return if concreteType.kind == "weak" then emitContextType(concreteType, context) + "{}" else "std::nullopt" }
    .WeakPointer -> { return emitContextType(concreteType, context) + "{}" }
    .Json -> { return "doof::json_value(nullptr)" }
    .Variant -> {
      if carrier.naturalNullable { return emitContextType(carrier.member!, context) + "{}" }
      if carrier.hasNone { return "std::monostate{}" }
    }
    _ -> { }
  }
  panic("No absence carrier for checked type " + concreteType.kind + " in " + context.modulePath)
}

export function emitCarrierNullTest(value: string): string { return "doof::is_null(" + value + ")" }
export function emitCarrierPresentValue(value: string): string { return "doof::unwrap_optional(" + value + ")" }

/** Convert an evaluated expression once, preserving the target's absence arm. */
export function emitCarrierConversion(value: string, source: ResolvedType, target: ResolvedType, context: EmitContext, position: CarrierPosition = .Value): string {
  fromType := specializeEmitType(source, context)
  toType := specializeEmitType(target, context)
  sourceCarrier := carrierOf(fromType, position)
  targetCarrier := carrierOf(toType)
  if sourceCarrier.kind == .Void || (sourceCarrier.kind == .Unit && targetCarrier.kind != .Unit) {
    return "(static_cast<void>(" + value + "), " + emitCarrierAbsence(toType, context) + ")"
  }
  if targetCarrier.kind == .Variant && !targetCarrier.naturalNullable {
    fromCpp := emitContextType(fromType, context)
    toCpp := emitContextType(toType, context)
    if fromCpp == toCpp { return value }
    if sourceCarrier.hasNone && sourceCarrier.naturalNullable {
      return "[&]() -> " + toCpp + " { const auto& _nullable_value = " + value + "; if (" + emitCarrierNullTest("_nullable_value") + ") return " + emitCarrierAbsence(toType, context) + "; return doof::variant_promote<" + toCpp + ">(" + emitCarrierPresentValue("_nullable_value") + "); }()"
    }
    return "doof::variant_promote<" + toCpp + ">(" + value + ")"
  }
  return value
}
