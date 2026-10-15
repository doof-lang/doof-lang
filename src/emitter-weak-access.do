// Member access and method calls through a weak reference.
//
// The receiver is evaluated once and locked once; the access then runs against
// the locked strong value. Forced access panics when the reference is none or
// has expired, while `?.` access yields the absent value of its result type.

import { ResolvedType, WeakResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { weakTargetAllowsNone } from "./emitter-carriers"
import { emitOptionalAbsent, emitOptionalPresent } from "./emitter-optional-chain"
import { emitContextType, emitType } from "./emitter-types"

/** The generated locals of one weak access. `value` names the locked strong reference. */
export class WeakAccessNames {
  id: string
  storage: string
  value: string
}

export function weakAccessNames(context: EmitContext): WeakAccessNames {
  id := string(context.nextTemporaryId())
  return WeakAccessNames { id, storage: "_weak_storage_" + id, value: "_weak_value_" + id }
}

/**
 * Wraps `access`, written against `names.value`, in a lambda that stores
 * `object` (of checked type `weakType`) and locks it first. A `none` result
 * type emits `access` as a statement.
 */
export function emitWeakAccess(
  object: string,
  weakType: ResolvedType,
  names: WeakAccessNames,
  access: string,
  force: bool,
  resultType: ResolvedType,
  optionalValue: ResolvedType | none,
  context: EmitContext,
): string {
  let nullable = false
  case weakType {
    weak_: WeakResolvedType -> { nullable = weakTargetAllowsNone(weak_.inner) }
    _ -> { }
  }
  storage := names.storage
  weakValue := if nullable then storage + ".value()" else storage
  returnsVoid := resultType.kind == "none"
  stored := "auto " + storage + " = " + object + "; "
  lock := "auto _weak_locked = doof::lock_weak(" + weakValue + "); "
  locked := "auto " + names.value + " = std::move(_weak_locked.value()); "
  if force {
    noneCheck := if nullable then "if (!" + storage + ".has_value()) doof::panic(\"Weak reference is none\"); " else ""
    returnType := if returnsVoid then "void" else emitType(resultType, context.modulePath, context.names)
    body := if returnsVoid then access + "; " else "return " + access + "; "
    return "[&]() -> " + returnType + " { " + stored + noneCheck + lock + "if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); " + locked + body + "}()"
  }
  if returnsVoid {
    noneReturn := if nullable then "if (!" + storage + ".has_value()) return; " else ""
    return "[&]() -> void { " + stored + noneReturn + lock + "if (!_weak_locked.has_value()) return; " + locked + access + "; }()"
  }
  if optionalValue == none { panic("Optional weak access has no resolved value type") }
  absent := emitOptionalAbsent(resultType, context)
  absentReturn := if nullable then "if (!" + storage + ".has_value()) return " + absent + "; " else ""
  present := emitOptionalPresent(access, optionalValue!, resultType, names.id, context)
  return "[&]() -> " + emitContextType(resultType, context) + " { " + stored + absentReturn + lock + "if (!_weak_locked.has_value()) return " + absent + "; " + locked + "return " + present + "; }()"
}
