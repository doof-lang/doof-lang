// Numeric generic capabilities and promotion, independent of expression checking.

import { PrimitiveType, ResolvedType, TypeParameterType, UnionResolvedType } from "./semantic"
import { isNumeric, numericResult, primitive, sameType, unionType, unknownType } from "./checker-types"

/** A numeric bound lists exact primitive alternatives, not runtime union values. */
export function isNumericConstraint(type_: ResolvedType): bool {
  if isNumeric(type_) { return true }
  case type_ {
    parameter: TypeParameterType -> { return parameter.constraint != none && isNumericConstraint(parameter.constraint!) }
    union_: UnionResolvedType -> {
      if union_.types.length == 0 { return false }
      for member of union_.types { if !isNumericConstraint(member) { return false } }
      return true
    }
    _ -> { return false }
  }
}

export function isNumericOperand(type_: ResolvedType): bool {
  if isNumeric(type_) { return true }
  case type_ {
    parameter: TypeParameterType -> { return parameter.constraint != none && isNumericConstraint(parameter.constraint!) }
    _ -> { return false }
  }
}

function alternatives(type_: ResolvedType): ResolvedType[] {
  case type_ {
    parameter: TypeParameterType -> { if parameter.constraint != none { return alternatives(parameter.constraint!) } }
    union_: UnionResolvedType -> {
      let members: ResolvedType[] = []
      for member of union_.types { for candidate of alternatives(member) { members.push(candidate) } }
      return members
    }
    _ -> { return [type_] }
  }
  return []
}

export function satisfiesNumericConstraint(value: ResolvedType, constraint: ResolvedType): bool {
  if !isNumericOperand(value) { return false }
  allowed := alternatives(constraint)
  for candidate of alternatives(value) {
    let found = false
    for member of allowed { if sameType(candidate, member) { found = true } }
    if !found { return false }
  }
  return true
}

export function isIntegerOperand(type_: ResolvedType): bool {
  if !isNumericOperand(type_) { return false }
  for member of alternatives(type_) {
    case member {
      numeric: PrimitiveType -> { if numeric.name != "byte" && numeric.name != "int" && numeric.name != "long" { return false } }
      _ -> { return false }
    }
  }
  return true
}

export function numericOperatorAllowed(operator: string, left: ResolvedType, right: ResolvedType): bool {
  integerOnly := operator == "\\" || operator == "%" || operator == "&" || operator == "|" || operator == "^" || operator == "<<" || operator == ">>" || operator == ">>>"
  if integerOnly { return isIntegerOperand(left) && isIntegerOperand(right) }
  if operator != "/" { return true }
  for a of alternatives(left) {
    for b of alternatives(right) {
      if sameType(left, right) && left.kind == "type-parameter" && !sameType(a, b) { continue }
      if isIntegerOperand(a) && isIntegerOperand(b) { return false }
    }
  }
  return true
}

/** Preserve T only if promotion returns its concrete alternative in every case. */
export function numericOperationType(left: ResolvedType, right: ResolvedType, operator: string = "+"): ResolvedType {
  let results: ResolvedType[] = []
  let preservesLeft = left.kind == "type-parameter"
  let preservesRight = right.kind == "type-parameter"
  for a of alternatives(left) {
    for b of alternatives(right) {
      if sameType(left, right) && left.kind == "type-parameter" && !sameType(a, b) { continue }
      let promoted = numericResult(a, b)
      if operator == "<<" || operator == ">>" || operator == ">>>" { promoted = numericResult(a, a) }
      if operator == "**" && (isIntegerOperand(a) || isIntegerOperand(b)) { promoted = primitive("double") }
      results.push(promoted)
      if !sameType(promoted, a) { preservesLeft = false }
      if !sameType(promoted, b) { preservesRight = false }
    }
  }
  if results.length == 0 { return unknownType() }
  if preservesLeft { return left }
  if preservesRight { return right }
  return unionType(results)
}
