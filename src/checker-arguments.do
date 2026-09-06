// Parameter mapping, contextual argument checks, and required/default validation.
// Syntax adapters preserve spans and shorthand properties; boundary rules stay
// with the caller and consume the decorated values after this check.
import { CallArgument, Expression, ObjectProperty, SourceSpan } from "./ast"
import { FunctionParamType, ResolvedType, Scope } from "./semantic"
import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { checkPropertyValue } from "./checker-properties"
import { containsString, functionParameterIndex } from "./checker-symbols"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { typeName } from "./checker-types"
import { typeError } from "./checker-common"

export class SuppliedArgument {
  name: string | none
  value: Expression | none = none
  property: ObjectProperty | none = none
  span: SourceSpan
}

export function callArguments(args: CallArgument[]): SuppliedArgument[] {
  let result: SuppliedArgument[] = []
  for argument of args { result.push(SuppliedArgument { name: argument.name, value: argument.value, span: argument.span }) }
  return result
}

export function propertyArguments(properties: ObjectProperty[]): SuppliedArgument[] {
  let result: SuppliedArgument[] = []
  for property of properties { result.push(SuppliedArgument { name: property.name, property, span: property.span }) }
  return result
}

export function positionalArguments(values: Expression[]): SuppliedArgument[] {
  let result: SuppliedArgument[] = []
  for value of values { result.push(SuppliedArgument { name: none, value, span: value.span }) }
  return result
}

export function checkArguments(
  state: CheckerState, args: SuppliedArgument[], params: FunctionParamType[], scope: Scope, span: SourceSpan,
  countSubject: string = "", argumentPrefix: string = "Argument", contextual: bool = true, validateTypes: bool = true,
  spread: FunctionParamType[] = [], spreadSpan: SourceSpan | none = none, namedSyntax: bool = false,
): none {
  let named = namedSyntax
  for argument of args { if argument.name != none { named = true } }
  let used: string[] = []
  if !named {
    let requiredCount = 0
    for i of 0..<params.length { if !params[i].hasDefault { requiredCount = i + 1 } }
    if args.length < requiredCount || args.length > params.length {
      range := if requiredCount == params.length then string(requiredCount) else string(requiredCount) + "-" + string(params.length)
      prefix := if countSubject == "" then "Expected " else countSubject + " expects "
      suffix := if countSubject == "" then " argument(s)" else " constructor argument(s)"
      typeError(state, prefix + range + suffix + " but got " + string(args.length), span)
    }
  }
  for i of 0..<args.length {
    argument := args[i]
    let index = i
    if named {
      if argument.name == none {
        typeError(state, if countSubject == "" then "Named calls cannot contain positional arguments" else "Named construction cannot contain positional arguments", argument.span)
        checkArgumentValue(state, argument, scope, none)
        continue
      }
      index = functionParameterIndex(params, argument.name!)
      if index < 0 {
        typeError(state, "Unknown named argument '" + argument.name! + "'", argument.span)
        checkArgumentValue(state, argument, scope, none)
        continue
      }
      if containsString(used, argument.name!) { typeError(state, "Duplicate named argument '" + argument.name! + "'", argument.span) }
      used.push(argument.name!)
    }
    let expected: ResolvedType | none = none
    if index < params.length { expected = params[index].type_ }
    actual := checkArgumentValue(state, argument, scope, if contextual then expected else none)
    if validateTypes && expected != none && !isAssignableWithInterfaces(state.result, actual, expected!) {
      label := if named then "'" + argument.name! + "'" else string(i + 1)
      typeError(state, argumentPrefix + " " + label + " has type " + typeName(actual) + "; expected " + typeName(expected!), argument.span)
    }
  }
  if named {
    for parameter of params {
      if containsString(used, parameter.name) { continue }
      spreadIndex := functionParameterIndex(spread, parameter.name)
      if spreadIndex >= 0 {
        actual := spread[spreadIndex].type_
        if !isAssignableWithInterfaces(state.result, actual, parameter.type_) {
          typeError(state, "Cannot assign spread field " + typeName(actual) + " to " + typeName(parameter.type_), spreadSpan ?? span)
        }
      } else if !parameter.hasDefault { typeError(state, "Missing required argument '" + parameter.name + "'", span) }
    }
  }
}

function checkArgumentValue(state: CheckerState, argument: SuppliedArgument, scope: Scope, expected: ResolvedType | none): ResolvedType {
  if argument.property != none { return checkPropertyValue(state, argument.property!, scope, expected) }
  return checkExpression(state, argument.value!, scope, expected)
}
