// Pure native representation model. Inputs are checked, specialized types;
// this module never inspects AST syntax, emits C++, or decides assignability.

import { ArrayResolvedType, ClassType, EnumType, InterfaceType, JsonValueResolvedType, MapResolvedType, NoneType, PrimitiveType, ResolvedType, ResultResolvedType, SetResolvedType, UnionResolvedType, WeakResolvedType } from "./semantic"

export enum CarrierPosition { Value, Return, Payload }
export enum CarrierKind { Value, Unit, Void, SharedPointer, Optional, WeakPointer, Variant, Json }

export class NativeCarrier {
  kind: CarrierKind
  // Explicit semantic absence, not e.g. JSON null or an expired weak owner.
  hasNone: bool = false
  // A union's only present member, if any (including tuple/callback members).
  member: ResolvedType | none = none
  // Does this union add optional<T>, rather than reuse its member's carrier?
  wrapsOptional: bool = false
  naturalNullable: bool = false
  // Only semantic unions/interfaces permit arm-wise pattern/member dispatch.
  unionLike: bool = false
}

export function carrierOf(type_: ResolvedType, position: CarrierPosition = .Value): NativeCarrier {
  case type_ {
    _: NoneType -> { return NativeCarrier { kind: if position == .Value then .Unit else .Void, hasNone: true } }
    _: JsonValueResolvedType -> { return NativeCarrier { kind: .Json } }
    class_: ClassType -> { return NativeCarrier { kind: if class_.symbol.kind == "struct" then .Value else .SharedPointer } }
    _: ArrayResolvedType -> { return NativeCarrier { kind: .SharedPointer } }
    _: MapResolvedType -> { return NativeCarrier { kind: .SharedPointer } }
    _: SetResolvedType -> { return NativeCarrier { kind: .SharedPointer } }
    _: InterfaceType -> { return NativeCarrier { kind: .Variant, unionLike: true } }
    _: ResultResolvedType -> { return NativeCarrier { kind: .Variant } }
    weak_: WeakResolvedType -> {
      case weak_.inner {
        union_: UnionResolvedType -> {
          inner := carrierOf(union_)
          return NativeCarrier { kind: if inner.hasNone then .Optional else if weakTargetUsesVariant(union_) then .Variant else .WeakPointer }
        }
        _ -> { return NativeCarrier { kind: .WeakPointer } }
      }
    }
    union_: UnionResolvedType -> {
      let present: ResolvedType[] = []
      let hasNone = false
      for member of flattenCarrierMembers(union_.types) {
        if member.kind == "none" { hasNone = true } else { present.push(member) }
      }
      if hasNone && present.length == 1 {
        member := present[0]
        kind := carrierOf(member).kind
        if kind == .SharedPointer || kind == .WeakPointer || member.kind == "weak" {
          return NativeCarrier { kind, hasNone, member, naturalNullable: true }
        }
        case member {
          _: PrimitiveType -> { return NativeCarrier { kind: .Optional, hasNone, member, wrapsOptional: true, naturalNullable: true } }
          _: EnumType -> { return NativeCarrier { kind: .Optional, hasNone, member, wrapsOptional: true, naturalNullable: true } }
          class_: ClassType -> { if class_.symbol.kind == "struct" { return NativeCarrier { kind: .Optional, hasNone, member, wrapsOptional: true, naturalNullable: true } } }
          _ -> { }
        }
      }
      return NativeCarrier { kind: .Variant, hasNone, unionLike: true, member: if present.length == 1 then present[0] else none }
    }
    _ -> { return NativeCarrier { kind: .Value } }
  }
  return NativeCarrier { kind: .Value }
}

export function naturalCarrierMember(type_: ResolvedType): ResolvedType | none {
  carrier := carrierOf(type_)
  if carrier.naturalNullable { return carrier.member }
  return none
}

export function flattenCarrierMembers(types: ResolvedType[]): ResolvedType[] {
  let result: ResolvedType[] = []
  for member of types {
    case member {
      nested: UnionResolvedType -> { for child of flattenCarrierMembers(nested.types) { result.push(child) } }
      _ -> { result.push(member) }
    }
  }
  return result
}

// Weak targets omit the none arm before constructing their weak variant.
export function weakTargetAllowsNone(type_: ResolvedType): bool {
  return type_.kind == "union" && carrierOf(type_).hasNone
}

export function weakTargetUsesVariant(type_: ResolvedType): bool {
  case type_ {
    union_: UnionResolvedType -> {
      let present = 0
      for member of flattenCarrierMembers(union_.types) { if member.kind != "none" { present += 1 } }
      return present > 1
    }
    _ -> { return false }
  }
  return false
}
