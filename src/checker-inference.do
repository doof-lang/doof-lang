// Joining independently checked value paths; explicit unions remain semantic types.
import { ResolvedType, UnionResolvedType } from "./semantic"
import { SourceSpan } from "./ast"
import { CheckerState } from "./checker-state"
import { typeError } from "./checker-common"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { neverType, typeName, unionType } from "./checker-types"

export function pathType(state: CheckerState, left: ResolvedType, right: ResolvedType, expected: ResolvedType | none, span: SourceSpan): ResolvedType {
  if left.kind == "never" && right.kind == "never" { return left }
  if expected != none && expected!.kind != "unknown" {
    for actual of [left, right] {
      if !isAssignableWithInterfaces(state.result, actual, expected!) {
        typeError(state, "Cannot use " + typeName(actual) + " in expression expecting " + typeName(expected!), span)
      }
    }
    return expected!
  }
  if left.kind == "unknown" || left.kind == "never" { return right }
  if right.kind == "unknown" || right.kind == "never" { return left }
  if isAssignableWithInterfaces(state.result, left, right) { return right }
  if isAssignableWithInterfaces(state.result, right, left) { return left }
  // Strip absence before comparing: none must not prevent ordinary widening.
  leftValue := presentType(left)
  rightValue := presentType(right)
  if isAssignableWithInterfaces(state.result, leftValue, rightValue) { return unionType([right, absenceType(left)]) }
  if isAssignableWithInterfaces(state.result, rightValue, leftValue) { return unionType([left, absenceType(right)]) }
  typeError(state, "Cannot infer a common type for " + typeName(left) + " and " + typeName(right) + "; provide an explicit type annotation (only T | none unions are inferred)", span)
  return left
}

function presentType(type_: ResolvedType): ResolvedType {
  if type_.kind == "none" { return neverType() }
  case type_ {
    union_: UnionResolvedType -> {
      let members: ResolvedType[] = []
      for member of union_.types { if member.kind != "none" { members.push(member) } }
      return unionType(members)
    }
    _ -> { return type_ }
  }
}

function absenceType(type_: ResolvedType): ResolvedType {
  if type_.kind == "none" { return type_ }
  case type_ {
    union_: UnionResolvedType -> { for member of union_.types { if member.kind == "none" { return member } } }
    _ -> { }
  }
  return neverType()
}
