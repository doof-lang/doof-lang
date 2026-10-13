// Binary, unary, and 'as' operators, and the operand compatibility rules they share.

import { absenceLayers, canBeAbsent, hasFailureLayer, hasPresentValue, presentType } from "./absence-types"
import { AsExpression, BinaryExpression, DotShorthand, EnumDeclaration, SourceSpan, UnaryExpression } from "./ast"
import { optionalConversion, optionalType } from "./checker-absence"
import { finish, requireBool, typeError } from "./checker-common"
import { constantInt } from "./checker-constants"
import { checkExpression } from "./checker-expressions"
import { pathType } from "./checker-inference"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { isIntegerOperand, isNumericOperand, numericOperationType, numericOperatorAllowed } from "./checker-numeric"
import { resolveType } from "./checker-resolution"
import { CheckerState } from "./checker-state"
import { declarationFor, optionalResolvedType } from "./checker-symbols"
import { isJsonValueType, isNumeric, isSerialBytesType, neverType, primitive, rangeType, resultType, sameType, typeName, unionType, unknownType } from "./checker-types"
import { ArrayResolvedType, ClassType, EnumType, FailureResolvedType, InterfaceType, MapResolvedType, NoneType, PrimitiveType, ResolvedType, ResultResolvedType, Scope, SerialValueResolvedType, SuccessResolvedType, TypeParameterType, UnionResolvedType, UnknownType, WeakResolvedType } from "./semantic"

export function checkBinary(state: CheckerState, expression: BinaryExpression, scope: Scope, expected: ResolvedType | none = none): ResolvedType {
  let left: ResolvedType = unknownType()
  let right: ResolvedType = unknownType()
  case expression.left {
    _: DotShorthand -> {
      right = checkExpression(state, expression.right, scope, none)
      left = checkExpression(state, expression.left, scope, optionalResolvedType(right))
    }
    _ -> {
      case expression.right {
        _: DotShorthand -> {
          left = checkExpression(state, expression.left, scope, none)
          shorthandExpected := if expression.operator == "??" then nonNoneType(state, left) else left
          right = checkExpression(state, expression.right, scope, optionalResolvedType(shorthandExpected))
        }
        _ -> {
          left = checkExpression(state, expression.left, scope, none)
          right = checkExpression(state, expression.right, scope, if expression.operator == "??" then expected else none)
        }
      }
    }
  }
  operator := expression.operator
  if left.kind == "never" { return finish(state, expression, neverType()) }
  if operator == "&&" || operator == "||" {
    requireBool(state, left, expression.left.span); requireBool(state, right, expression.right.span)
    return finish(state, expression, primitive("bool"))
  }
  if operator == "??" {
    if left.kind == "none" { return finish(state, expression, pathType(state, unknownType(), right, expected, expression.span)) }
    layers := absenceLayers(left)
    if layers.length == 0 {
      typeError(state, "Operator '??' requires a nullable or Result left operand, got " + typeName(left), expression.left.span)
      return finish(state, expression, pathType(state, unknownType(), right, expected, expression.span))
    }
    // Every absent layer falls back: 'x ?? y' is 'x? ?? y' when x has more
    // than one layer.
    if layers.length > 1 && hasPresentValue(left) { expression.left = optionalConversion(state, expression.left, left) }
    return finish(state, expression, pathType(state, presentType(left), right, expected, expression.span))
  }
  if right.kind == "never" { return finish(state, expression, neverType()) }
  if operator == "..<" || operator == ".." {
    validateRangeOperand(state, operator, "left", left, expression.left.span)
    validateRangeOperand(state, operator, "right", right, expression.right.span)
    if operator == ".." { rejectInclusiveRangeAtMaximumInt(state, expression) }
    return finish(state, expression, rangeType())
  }
  if operator == "==" || operator == "!=" {
    validateNoneComparison(state, operator, left, right, expression.span)
    if (isJsonValueType(left) && right.kind != "json-value" && right.kind != "none" && right.kind != "unknown" && right.kind != "never") || (isJsonValueType(right) && left.kind != "json-value" && left.kind != "none" && left.kind != "unknown" && left.kind != "never") {
      typeError(state, "Narrow SerialValue with 'as' or 'case' before comparing it with a typed value", expression.span)
      return finish(state, expression, primitive("bool"))
    }
    if left.kind != "none" && right.kind != "none" && !typesOverlap(state, left, right) {
      typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), expression.span)
    } else if left.kind != "none" && right.kind != "none" {
      expression.resolvedComparisonType = comparisonType(state, left, right)
    }
    return finish(state, expression, primitive("bool"))
  }
  if operator == "<" || operator == "<=" || operator == ">" || operator == ">=" {
    if !orderedTypes(state, left, right) { typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), expression.span) }
    return finish(state, expression, primitive("bool"))
  }
  if operator == "+" && typeName(left) == "string" && (typeName(right) == "string" || typeName(right) == "char" || typeName(right) == "unknown") { return finish(state, expression, primitive("string")) }
  if operator == "+" && typeName(right) == "string" && (typeName(left) == "char" || typeName(left) == "unknown") { return finish(state, expression, primitive("string")) }
  if isNumericOperand(left) && isNumericOperand(right) {
    validateNumericOperator(state, operator, left, right, expression.span)
    return finish(state, expression, numericOperationType(left, right, operator))
  }
  typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), expression.span)
  return finish(state, expression, unknownType())
}

function validateNoneComparison(state: CheckerState, operator: string, left: ResolvedType, right: ResolvedType, span: SourceSpan): none {
  if left.kind == "none" && !admitsNone(right) {
    typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), span)
  } else if right.kind == "none" && !admitsNone(left) {
    typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), span)
  }
}

function admitsNone(type_: ResolvedType): bool {
  case type_ {
    _: NoneType -> { return true }
    // An optional weak reference compares with none on absence, not expiry.
    weak_: WeakResolvedType -> { return admitsNone(weak_.inner) }
    _: UnknownType -> { return true }
    _: SerialValueResolvedType -> { return true }
    union_: UnionResolvedType -> {
      for member of union_.types { if member.kind == "none" { return true } }
    }
    _ -> { }
  }
  return false
}

// A Range stores an exclusive upper bound, which cannot represent one past
// the maximum int, so an inclusive range ending there is rejected.
function rejectInclusiveRangeAtMaximumInt(state: CheckerState, expression: BinaryExpression): none {
  end := constantInt(expression.right)
  if end == none || end! != 2147483647L { return }
  typeError(state, "Inclusive range \"..\" cannot end at the maximum int (2147483647); its exclusive upper bound would overflow", expression.right.span)
}

function validateRangeOperand(state: CheckerState, operator: string, side: string, operand: ResolvedType, span: SourceSpan): none {
  if operand.kind == "unknown" { return }
  case operand {
    primitive_: PrimitiveType -> {
      if primitive_.name != "byte" && primitive_.name != "int" && primitive_.name != "long" {
        typeError(state, "Range operator \"" + operator + "\" requires integer bounds, got " + side + " bound of type \"" + typeName(operand) + "\"", span)
      } else if primitive_.name == "long" {
        typeError(state, "Range operator \"" + operator + "\" currently requires int-compatible bounds, got " + side + " bound of type \"long\"", span)
      }
    }
    _ -> { typeError(state, "Range operator \"" + operator + "\" requires integer bounds, got " + side + " bound of type \"" + typeName(operand) + "\"", span) }
  }
}

export function checkUnary(state: CheckerState, expression: UnaryExpression, scope: Scope): ResolvedType {
  value := checkExpression(state, expression.operand, scope, none)
  // Keep the operand decoration explicit at this boundary.  The emitter
  // consumes the operand node later, and must not reconstruct its type from
  // the unary state.result (notably for postfix ! over imported Result functions).
        expression.operand.resolvedType = optionalResolvedType(value)
  if value.kind == "never" { return finish(state, expression, neverType()) }
  if expression.operator == "try" {
    // Bare `try` propagates by returning, so it only exists as a statement.
    typeError(state, "'try' is a statement, not an expression; write 'try name := value' to propagate, or use postfix 'value!' or 'value?' inside an expression", expression.span)
    case value {
      result: ResultResolvedType -> { return finish(state, expression, result.valueType) }
      _ -> { return finish(state, expression, unknownType()) }
    }
  }
  if expression.operator == "try!" || expression.operator == "try?" {
    // The prefix forms were replaced by postfix '!' and '?'; recover with the
    // postfix type so later diagnostics stay meaningful.
    postfix := expression.operator.substring(3, 4)
    typeError(state, "'" + expression.operator + " value' was removed; write 'value" + postfix + "'", expression.span)
    if !canBeAbsent(value) { return finish(state, expression, unknownType()) }
    return finish(state, expression, if postfix == "!" then presentType(value) else optionalType(value))
  }
  if !expression.prefix && (expression.operator == "!" || expression.operator == "?") {
    // Every absent layer (an outer none, a Failure, a none success value)
    // panics under '!' and becomes none under '?'.
    if !canBeAbsent(value) && value.kind != "none" {
      typeError(state, "Postfix '" + expression.operator + "' requires a nullable or Result operand, got " + typeName(value), expression.span)
      return finish(state, expression, unknownType())
    }
    if expression.operator == "!" {
      if value.kind == "none" { return finish(state, expression, unknownType()) }
      return finish(state, expression, presentType(value))
    }
    if !hasPresentValue(value) && hasFailureLayer(value) {
      typeError(state, "Postfix '?' requires a Result with a success value, got " + typeName(value), expression.span)
      return finish(state, expression, unknownType())
    }
    if value.kind == "none" { return finish(state, expression, value) }
    return finish(state, expression, optionalType(value))
  }
  if expression.operator == "!" { requireBool(state, value, expression.span); return finish(state, expression, primitive("bool")) }
  if expression.operator == "+" || expression.operator == "-" || expression.operator == "~" {
    if !isNumericOperand(value) { typeError(state, "Unary '" + expression.operator + "' requires a numeric operand", expression.span) }
    else {
      if expression.operator == "~" && !isIntegerOperand(value) { typeError(state, "Unary '~' requires an integer operand", expression.span) }
      return finish(state, expression, numericOperationType(value, value))
    }
    return finish(state, expression, value)
  }
  return finish(state, expression, value)
}

/** Validates checked narrowing and preserves its fallible Result shape. */
export function checkAs(state: CheckerState, expression: AsExpression, scope: Scope): ResolvedType {
  sourceType := checkExpression(state, expression.expression, scope, none)
  targetType := resolveType(state, expression.targetType, state.info!, scope)
  if sourceType.kind == "never" { return finish(state, expression, neverType()) }
  case sourceType {
    result: ResultResolvedType -> {
      if !isValidAsNarrow(state, result.valueType, targetType) {
        typeError(state, "Cannot narrow \"" + typeName(sourceType) + "\" to \"" + typeName(targetType) + "\" with \"as\"", expression.span)
        return finish(state, expression, unknownType())
      }
      return finish(state, expression, resultType(targetType, unionType([result.errorType, primitive("string")])))
    }
    _ -> { }
  }
  if !isValidAsNarrow(state, sourceType, targetType) {
    typeError(state, "Cannot narrow \"" + typeName(sourceType) + "\" to \"" + typeName(targetType) + "\" with \"as\"", expression.span)
    return finish(state, expression, unknownType())
  }
  return finish(state, expression, resultType(targetType, primitive("string")))
}

export function isValidAsNarrow(state: CheckerState, source: ResolvedType, target: ResolvedType): bool {
  if sameType(source, target) { return true }
  if isNumeric(source) && isNumeric(target) { return true }
  case source {
    _: SerialValueResolvedType -> { return isJsonAsTarget(state, target) }
    union_: UnionResolvedType -> {
      for member of union_.types { if isValidAsNarrow(state, member, target) { return true } }
    }
    _: InterfaceType -> {
      case target {
        _: ClassType -> { return true }
        _ -> { }
      }
    }
    _ -> { }
  }
  return false
}

export function isJsonAsTarget(state: CheckerState, target: ResolvedType): bool {
  case target {
    primitiveType: PrimitiveType -> {
      return primitiveType.name == "bool" || primitiveType.name == "string" || isNumeric(primitiveType)
    }
    array: ArrayResolvedType -> { return (array.readonly_ && isJsonValueType(array.elementType)) || isSerialBytesType(array) }
    map: MapResolvedType -> { return map.readonly_ && sameType(map.keyType, primitive("string")) && isJsonValueType(map.valueType) }
    _: SerialValueResolvedType -> { return true }
    _ -> { return false }
  }
  return false
}

export function nonNoneType(state: CheckerState, value: ResolvedType): ResolvedType {
  case value {
    union_: UnionResolvedType -> {
      let members: ResolvedType[] = []
      for member of union_.types { if member.kind != "none" { members.push(member) } }
      if members.length == 1 { return members[0] }
      if members.length > 1 { return unionType(members) }
      return unknownType()
    }
    _: NoneType -> { return unknownType() }
    _ -> { return value }
  }
  return unknownType()
}

export function hasNoneMember(state: CheckerState, value: UnionResolvedType): bool {
  for member of value.types { if member.kind == "none" { return true } }
  return false
}

export function binaryOperatorType(state: CheckerState, operator: string, left: ResolvedType, right: ResolvedType, span: SourceSpan): ResolvedType {
  if operator == "+" && typeName(left) == "string" && (typeName(right) == "string" || typeName(right) == "char") { return primitive("string") }
  if isNumericOperand(left) && isNumericOperand(right) {
    validateNumericOperator(state, operator, left, right, span)
    return numericOperationType(left, right, operator)
  }
  typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), span)
  return unknownType()
}

function validateNumericOperator(state: CheckerState, operator: string, left: ResolvedType, right: ResolvedType, span: SourceSpan): none {
  if numericOperatorAllowed(operator, left, right) { return }
  if operator == "/" { typeError(state, "Operator '/' requires at least one floating-point operand for every allowed type", span) }
  else { typeError(state, "Operator '" + operator + "' requires integer operands, got " + typeName(left) + " and " + typeName(right), span) }
}


function orderedTypes(state: CheckerState, left: ResolvedType, right: ResolvedType): bool {
  if left.kind == "unknown" || right.kind == "unknown" { return true }
  if isNumericOperand(left) && isNumericOperand(right) { return true }
  if sameType(left, right) {
    case left {
      primitive_: PrimitiveType -> { return primitive_.name == "string" || primitive_.name == "char" }
      enum_: EnumType -> {
        declaration := declarationFor(state.result, enum_.symbol)
        if declaration != none {
          case declaration! {
            owner: EnumDeclaration -> { return owner.backingKind == "int" }
            _ -> { }
          }
        }
        return true
      }
      _: TypeParameterType -> { return true }
      _ -> { }
    }
  }
  return false
}

// A union, Result, or interface compares with one of its members at the wider
// type, so the narrower operand is converted to it like any assignment.
function comparisonType(state: CheckerState, left: ResolvedType, right: ResolvedType): ResolvedType | none {
  if sameType(left, right) { return none }
  if isComparisonCarrier(right) && isAssignableWithInterfaces(state.result, left, right) { return right }
  if isComparisonCarrier(left) && isAssignableWithInterfaces(state.result, right, left) { return left }
  return none
}

function isComparisonCarrier(type_: ResolvedType): bool {
  case type_ {
    _: UnionResolvedType -> { return true }
    _: ResultResolvedType -> { return true }
    _: InterfaceType -> { return true }
    _ -> { return false }
  }
}

export function typesOverlap(state: CheckerState, left: ResolvedType, right: ResolvedType): bool {
  if left.kind == "unknown" || right.kind == "unknown" { return true }
  case left {
    union_: UnionResolvedType -> {
      for member of union_.types { if typesOverlap(state, member, right) { return true } }
      return false
    }
    _ -> { }
  }
  case right {
    union_: UnionResolvedType -> {
      for member of union_.types { if typesOverlap(state, left, member) { return true } }
      return false
    }
    _ -> { }
  }
  case left {
    result: ResultResolvedType -> { case right { success: SuccessResolvedType -> { return typesOverlap(state, result.valueType, success.valueType) } failure: FailureResolvedType -> { return typesOverlap(state, result.errorType, failure.errorType) } _ -> { } } }
    success: SuccessResolvedType -> { case right { result: ResultResolvedType -> { return typesOverlap(state, success.valueType, result.valueType) } _ -> { } } }
    failure: FailureResolvedType -> { case right { result: ResultResolvedType -> { return typesOverlap(state, failure.errorType, result.errorType) } _ -> { } } }
    _ -> { }
  }
  return isAssignableWithInterfaces(state.result, left, right) || isAssignableWithInterfaces(state.result, right, left) || (isNumericOperand(left) && isNumericOperand(right))
}
