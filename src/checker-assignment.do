// Assignment targets and compound assignment operators.

import { canBeAbsent } from "./absence-types"
import { AssignmentExpression, Identifier, IndexExpression, MemberExpression, SourceSpan } from "./ast"
import { finish, typeError, validateAssignmentBinding } from "./checker-common"
import { checkExpression } from "./checker-expressions"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { binaryOperatorType } from "./checker-operators"
import { fieldAssignmentBinding } from "./checker-resolution"
import { CheckerState } from "./checker-state"
import { lookup, optionalResolvedType } from "./checker-symbols"
import { displayTypeName, neverType, primitive, typeName, unknownType } from "./checker-types"
import { ArrayResolvedType, MapResolvedType, ResolvedType, ResultResolvedType, Scope } from "./semantic"

// `tried` checks `try target = expr`: the value must be a Result, and the target
// is checked against its success type.
export function checkAssignment(state: CheckerState, expression: AssignmentExpression, scope: Scope, tried: bool = false): ResolvedType {
  case expression.target {
    member: MemberExpression -> {
      if member.optional { typeError(state, "Optional chaining '?.' cannot be used as an assignment target", expression.target.span) }
    }
    index: IndexExpression -> {
      if index.optional { typeError(state, "Optional indexing '?[]' cannot be used as an assignment target", expression.target.span) }
    }
    _ -> { }
  }
  targetType := checkExpression(state, expression.target, scope, none)
  // Assignment emission needs the target decoration to choose representation
  // conversions, especially when a member is a nullable AST union field.
  finish(state, expression.target, targetType)
  case expression.target {
    identifier: Identifier -> {
      binding := lookup(scope, identifier.name)
      if binding != none {
        identifier.resolvedBinding = binding
        identifier.resolvedType = optionalResolvedType(binding!.type_)
      }
    }
    _ -> { }
  }
  let value = checkExpression(state, expression.value, scope, if tried then none else optionalResolvedType(targetType))
  if tried {
    case value {
      result: ResultResolvedType -> {
        expression.resolvedTriedResult = result
        // A none success value is reported once by the try statement.
        value = if result.valueType.kind == "none" then unknownType() else result.valueType
      }
      _ -> {
        if value.kind != "unknown" { typeError(state, "try requires a Result expression", expression.value.span) }
        value = unknownType()
      }
    }
  }
  validateAssignmentOperator(state, expression.operator, targetType, value, expression.span)
  case expression.target {
    identifier: Identifier -> {
      target := lookup(scope, identifier.name)
      if target == none { typeError(state, "Unknown assignment target '" + identifier.name + "'", identifier.span) }
      else {
        validateAssignmentBinding(state, target!, identifier.span)
        if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, target!.type_) { typeError(state, "Cannot assign " + displayTypeName(value) + " to " + displayTypeName(target!.type_), expression.span) }
      }
    }
    index: IndexExpression -> {
      objectType := checkExpression(state, index.object, scope, none)
      case objectType {
        array: ArrayResolvedType -> {
          checkExpression(state, index.index, scope, optionalResolvedType(primitive("int")))
          if array.readonly_ { typeError(state, "Cannot assign through readonly array", expression.span) }
          if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, array.elementType) { typeError(state, "Cannot assign " + displayTypeName(value) + " to " + displayTypeName(array.elementType), expression.span) }
        }
        map: MapResolvedType -> {
          key := checkExpression(state, index.index, scope, optionalResolvedType(map.keyType))
          if !isAssignableWithInterfaces(state.result, key, map.keyType) { typeError(state, "Cannot use " + typeName(key) + " as map key " + typeName(map.keyType), index.index.span) }
          if map.readonly_ { typeError(state, "Cannot assign through readonly map", expression.span) }
          if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, map.valueType) { typeError(state, "Cannot assign " + displayTypeName(value) + " to " + displayTypeName(map.valueType), expression.span) }
        }
        _ -> { typeError(state, "Index assignment requires an array or map", expression.span) }
      }
    }
    member: MemberExpression -> {
      // The target was already checked above. In particular, do not resolve an
      // inaccessible actor field again or add assignment errors to that failure.
      if targetType.kind == "unknown" { return finish(state, expression, value) }
      objectType := member.object.resolvedType ?? unknownType()
      fieldBinding := fieldAssignmentBinding(state, objectType, member.property, targetType, member.span)
      if fieldBinding != none { validateAssignmentBinding(state, fieldBinding!, member.span) }
      else if objectType.kind != "unknown" && objectType.kind != "never" { typeError(state, "Member '" + member.property + "' is not an assignable field", member.span) }
      if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, targetType) { typeError(state, "Cannot assign " + displayTypeName(value) + " to " + displayTypeName(targetType), expression.span) }
    }
    _ -> { typeError(state, "Assignment target must be a binding", expression.target.span) }
  }
  if targetType.kind == "never" || value.kind == "never" { return finish(state, expression, neverType()) }
  return finish(state, expression, if expression.operator == "=" then value else targetType)
}

function validateAssignmentOperator(state: CheckerState, operator: string, target: ResolvedType, value: ResolvedType, span: SourceSpan): none {
  if operator == "=" || target.kind == "unknown" || value.kind == "unknown" { return }
  if operator == "??=" {
    if !canBeAbsent(target) && target.kind != "none" { typeError(state, "Operator '??=' requires a nullable or Result assignment target, got " + typeName(target), span); return }
    case target {
      result: ResultResolvedType -> {
        if !isAssignableWithInterfaces(state.result, value, target) && !isAssignableWithInterfaces(state.result, value, result.valueType) {
          typeError(state, "Cannot assign " + typeName(value) + " through ??= to " + typeName(target), span)
        }
      }
      _ -> { if !isAssignableWithInterfaces(state.result, value, target) { typeError(state, "Cannot assign " + typeName(value) + " through ??= to " + typeName(target), span) } }
    }
    return
  }
  base := operator.substring(0, operator.length - 1)
  result := binaryOperatorType(state, base, target, value, span)
  if !isAssignableWithInterfaces(state.result, result, target) { typeError(state, "Operator '" + operator + "' produces " + typeName(result) + ", which cannot be assigned to " + typeName(target), span) }
}
