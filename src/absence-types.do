// Absence structure of a value type, shared by checking and lowering.
//
// `none` and a `Failure` are both absent. A value can be absent at up to three
// layers, outermost first: an outer none arm, one Result, and a none success
// value. `Result<T | none, E> | none` peels to `T`; a Result nested in a
// success value is a present value, not another layer.

import { ResolvedType, ResultResolvedType, UnionResolvedType } from "./semantic"
import { noneType, unionType } from "./checker-types"

export class AbsenceLayer {
  // A Result Failure; otherwise a none arm.
  failure: bool
  source: ResolvedType
  present: ResolvedType
}

export function absenceLayers(type_: ResolvedType): AbsenceLayer[] {
  let layers: AbsenceLayer[] = []
  let current = type_
  let resultSeen = false
  let more = true
  while more {
    more = false
    case current {
      union_: UnionResolvedType -> {
        let present: ResolvedType[] = []
        for member of union_.types { if member.kind != "none" { present.push(member) } }
        if present.length < union_.types.length && present.length > 0 {
          next := unionType(present)
          layers.push(AbsenceLayer { failure: false, source: current, present: next })
          current = next
          more = true
        }
      }
      result: ResultResolvedType -> {
        if !resultSeen {
          resultSeen = true
          layers.push(AbsenceLayer { failure: true, source: current, present: result.valueType })
          current = result.valueType
          more = result.valueType.kind != "none"
        }
      }
      _ -> { }
    }
  }
  return layers
}

/** Whether a value can be absent: nullable, a Result, or both. */
export function canBeAbsent(type_: ResolvedType): bool { return absenceLayers(type_).length > 0 }

export function hasFailureLayer(type_: ResolvedType): bool {
  for layer of absenceLayers(type_) { if layer.failure { return true } }
  return false
}

/** The value once every absent layer is removed; the type itself when none apply. */
export function presentType(type_: ResolvedType): ResolvedType {
  layers := absenceLayers(type_)
  if layers.length == 0 { return type_ }
  return layers[layers.length - 1].present
}

/** Whether every absent layer leaves a value: false for `Result<none, E>`. */
export function hasPresentValue(type_: ResolvedType): bool {
  return presentType(type_).kind != "none"
}

/**
 * The error a declaration-else handler captures: `E` when Failure is the only
 * absent layer, `E | none` when the value can also be absent as none, and
 * `none` when there is no Result layer.
 */
export function absenceErrorType(type_: ResolvedType): ResolvedType | none {
  layers := absenceLayers(type_)
  for layer of layers {
    if layer.failure {
      case layer.source {
        result: ResultResolvedType -> {
          if layers.length == 1 { return result.errorType }
          return unionType([result.errorType, noneType()])
        }
        _ -> { }
      }
    }
  }
  return none
}
