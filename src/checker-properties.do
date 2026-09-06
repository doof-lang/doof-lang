// One binding-aware property-value check for construction and contextual literals.
// Callers own key checking and shape selection; this owns value decoration.
import { ObjectProperty, Expression, StringLiteral, IntLiteral, LongLiteral, FloatLiteral, DoubleLiteral, CharLiteral, BoolLiteral, NoneLiteral, MemberExpression, DotShorthand, UnaryExpression } from "./ast"
import { ResolvedType, Scope } from "./semantic"
import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { lookup, optionalResolvedType } from "./checker-symbols"
import { typeName, unknownType } from "./checker-types"
import { typeError } from "./checker-common"
import { isAssignableWithInterfaces } from "./checker-interfaces"

export function checkPropertyValue(state: CheckerState, property: ObjectProperty, scope: Scope, expected: ResolvedType | none): ResolvedType {
  let actual: ResolvedType = unknownType()
  if property.value != none { actual = checkExpression(state, property.value!, scope, expected) }
  else {
    binding := lookup(scope, property.name)
    if binding == none { typeError(state, "Unknown shorthand property '" + property.name + "'", property.span) }
    else { property.resolvedBinding = binding; actual = binding!.type_ }
  }
  property.resolvedType = optionalResolvedType(actual)
  return actual
}

export function checkAssignableProperty(state: CheckerState, property: ObjectProperty, scope: Scope, expected: ResolvedType | none): ResolvedType {
  actual := checkPropertyValue(state, property, scope, expected)
  if expected != none && !isAssignableWithInterfaces(state.result, actual, expected!) {
    typeError(state, "Cannot assign " + typeName(actual) + " to " + typeName(expected!), property.span)
  }
  return actual
}

export function sameFixedFieldValue(actual: Expression, expected: Expression): bool {
  case expected {
    expectedString: StringLiteral -> {
      case actual { actualString: StringLiteral -> { return actualString.value == expectedString.value } _ -> { return false } }
    }
    expectedInt: IntLiteral -> {
      case actual { actualInt: IntLiteral -> { return actualInt.value == expectedInt.value } _ -> { return false } }
    }
    expectedLong: LongLiteral -> {
      case actual { actualLong: LongLiteral -> { return actualLong.value == expectedLong.value } _ -> { return false } }
    }
    expectedFloat: FloatLiteral -> {
      case actual { actualFloat: FloatLiteral -> { return actualFloat.value == expectedFloat.value } _ -> { return false } }
    }
    expectedDouble: DoubleLiteral -> {
      case actual { actualDouble: DoubleLiteral -> { return actualDouble.value == expectedDouble.value } _ -> { return false } }
    }
    expectedChar: CharLiteral -> {
      case actual { actualChar: CharLiteral -> { return actualChar.value == expectedChar.value } _ -> { return false } }
    }
    expectedBool: BoolLiteral -> {
      case actual { actualBool: BoolLiteral -> { return actualBool.value == expectedBool.value } _ -> { return false } }
    }
    _: NoneLiteral -> {
      case actual { _: NoneLiteral -> { return true } _ -> { return false } }
    }
    expectedMember: MemberExpression -> {
      case actual {
        actualMember: MemberExpression -> { return actualMember.property == expectedMember.property }
        actualDot: DotShorthand -> { return actualDot.name == expectedMember.property }
        _ -> { return false }
      }
    }
    expectedDot: DotShorthand -> {
      case actual {
        actualMember: MemberExpression -> { return actualMember.property == expectedDot.name }
        actualDot: DotShorthand -> { return actualDot.name == expectedDot.name }
        _ -> { return false }
      }
    }
    expectedUnary: UnaryExpression -> {
      case actual {
        actualUnary: UnaryExpression -> { return actualUnary.operator == expectedUnary.operator && sameFixedFieldValue(actualUnary.operand, expectedUnary.operand) }
        _ -> { return false }
      }
    }
    _ -> { return false }
  }
  return false
}
