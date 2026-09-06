import { Assert } from "std/assert"
import { carrierOf, CarrierKind, CarrierPosition, weakTargetAllowsNone, weakTargetUsesVariant } from "./emitter-carriers"
import { ArrayResolvedType, ClassType, FunctionType, JsonValueResolvedType, NoneType, PrimitiveType, ResolvedType, ResultResolvedType, Symbol, TupleResolvedType, UnionResolvedType, WeakResolvedType } from "./semantic"

export function testCarrierModelPositionsAndNullableFamilies(): none {
  unit := NoneType {}
  Assert.equal(carrierOf(unit).kind, CarrierKind.Unit)
  Assert.equal(carrierOf(unit, .Return).kind, CarrierKind.Void)
  Assert.equal(carrierOf(unit, .Payload).kind, CarrierKind.Void)
  item := ClassType { name: "Item", symbol: Symbol { kind: "class", name: "Item", module: "", exported: false } }
  point := ClassType { name: "Point", symbol: Symbol { kind: "struct", name: "Point", module: "", exported: false } }
  integer := PrimitiveType { name: "int" }
  resultCarrier := carrierOf(ResultResolvedType { valueType: integer, errorType: integer })
  Assert.equal(resultCarrier.kind, CarrierKind.Variant)
  Assert.isFalse(resultCarrier.unionLike)
  weakTarget := UnionResolvedType { types: [UnionResolvedType { types: [item, unit] }, ArrayResolvedType { elementType: integer, readonly_: false }] }
  Assert.isTrue(weakTargetAllowsNone(weakTarget))
  Assert.isTrue(weakTargetUsesVariant(weakTarget))
  Assert.isFalse(weakTargetUsesVariant(UnionResolvedType { types: [item, unit] }))
  Assert.equal(carrierOf(WeakResolvedType { inner: weakTarget }).kind, CarrierKind.Optional)
  types: ResolvedType[] := [integer, item, point, ArrayResolvedType { elementType: integer, readonly_: false }, WeakResolvedType { inner: item }, TupleResolvedType { elements: [integer] }, FunctionType { params: [], returnType: integer }, ResultResolvedType { valueType: integer, errorType: integer }, JsonValueResolvedType {}]
  kinds := [CarrierKind.Optional, CarrierKind.SharedPointer, CarrierKind.Optional, CarrierKind.SharedPointer, CarrierKind.WeakPointer, CarrierKind.Variant, CarrierKind.Variant, CarrierKind.Variant, CarrierKind.Variant]
  for index of 0..<types.length {
    carrier := carrierOf(UnionResolvedType { types: [UnionResolvedType { types: [types[index], unit] }, unit] })
    Assert.equal(carrier.kind, kinds[index])
    Assert.isTrue(carrier.hasNone)
    Assert.equal(carrier.naturalNullable, index < 5)
  }
}
