// Lambda signatures, block-return inference, and callable completion checking.
import { Block, Expression, LambdaExpression, Parameter } from "./ast"
import { Binding, FunctionParamType, FunctionType, ResolvedType, Scope, UnionResolvedType } from "./semantic"
import { CheckerState, LambdaReturnInference } from "./checker-state"
import { displayTypeName, functionType, neverType, noneType, unknownType } from "./checker-types"
import { pathType } from "./checker-inference"
import { checkBlock } from "./checker-statements"
import { checkExpression } from "./checker-expressions"
import { resolveType } from "./checker-resolution"
import { finish, typeError } from "./checker-common"
import { decorateAnnotationWithResolved, functionParameterIndex, optionalResolvedType, declare } from "./checker-symbols"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"

export function checkLambda(state: CheckerState, expression: LambdaExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  expectedFunction := contextualFunctionType(expected)
  if expression.trailing && expectedFunction != none && expectedFunction!.returnType.kind != "none" {
    typeError(state, "Trailing lambdas require a callback returning none; use an explicit lambda such as '=> ...' instead", expression.span)
  }
  // `=> body` inherits the complete callback signature. Materializing those
  // parameters on the decorated AST keeps checking, generic inference,
  // capture analysis, and C++ emission aligned on the same representation.
  if expression.parameterless && expression.params.length == 0 && expectedFunction != none {
    for expectedParameter of expectedFunction!.params {
      expression.params.push(Parameter {
        name: expectedParameter.name,
        type_: none,
        defaultValue: none,
        resolvedType: expectedParameter.type_,
        span: expression.span,
      })
    }
  }
  parametersBound := expression.parameterless || expectedFunction == none || bindLambdaParameters(state, expression, expectedFunction!)
  lambdaScope := Scope { parent: scope, trailingLambda: expression.trailing }
  let params: FunctionParamType[] = []
  for i of 0..<expression.params.length {
    parameter := expression.params[i]
    parameterType := if parameter.type_ == none then if expectedFunction != none && i < expectedFunction!.params.length then expectedFunction!.params[i].type_ else unknownType() else resolveType(state, parameter.type_!, state.info!, lambdaScope)
    parameter.resolvedType = optionalResolvedType(parameterType)
    params.push(FunctionParamType { name: parameter.name, type_: parameterType, hasDefault: parameter.defaultValue != none })
    if parameter.name != "_" && !declare(lambdaScope, Binding { name: parameter.name, kind: "parameter", type_: parameterType, mutable: false, span: checkerSemanticSpan(parameter.span), module: state.info!.path }) {
      typeError(state, "Binding '" + parameter.name + "' is already declared in this scope", parameter.span)
    }
  }
  let returnType = if expectedFunction == none then unknownType() else expectedFunction!.returnType
  if expression.returnType != none {
    returnType = resolveType(state, expression.returnType!, state.info!, lambdaScope)
    decorateAnnotationWithResolved(expression.returnType!, returnType)
  }
  // A block lambda is its own return target. Without this scope boundary,
  // returns inside an escaping closure are checked against the enclosing
  // function's return type.
  lambdaScope.returnType = returnType
  case expression.body {
    block: Block -> {
      previousInference := state.lambdaReturns
      inference := LambdaReturnInference { scope: lambdaScope }
      state.lambdaReturns = if returnType.kind == "unknown" then inference else none
      completes := checkBlock(state, block, lambdaScope)
      state.lambdaReturns = previousInference
      if returnType.kind == "unknown" {
        returnType = neverType()
        for observation of inference.returns {
          if observation.reachable {
            returnType = pathType(state, returnType, observation.type_, none, observation.statement.span)
          }
        }
        if completes && returnType.kind == "never" { returnType = noneType() }
        lambdaScope.returnType = returnType
        // Return sites retain the final contextual carrier for the emitter,
        // including nullable and unit conversions. Do not recheck the body.
        for observation of inference.returns {
          observation.statement.resolvedExpectedType = optionalResolvedType(returnType)
          if observation.statement.value == none && returnType.kind != "none" && returnType.kind != "unknown" {
            typeError(state, "Expected a return value of type " + displayTypeName(returnType), observation.statement.span)
          } else if !isAssignableWithInterfaces(state.result, observation.type_, returnType) {
            typeError(state, "Cannot return " + displayTypeName(observation.type_) + " from lambda returning " + displayTypeName(returnType), observation.statement.span)
          }
        }
      }
      if completes && returnType.kind != "none" && returnType.kind != "unknown" {
        typeError(state, "Lambda may complete without returning " + displayTypeName(returnType), expression.span)
      }
    }
    expressionBody: Expression -> {
      // A declared or contextual return type is the lambda's signature, as it
      // is for block bodies; the body converts to it. Only an unknown return
      // type is inferred from the body.
      bodyType := checkExpression(state, expressionBody, lambdaScope, optionalResolvedType(returnType))
      if returnType.kind == "unknown" { returnType = bodyType }
      else if returnType.kind == "none" {
        // A none-returning body is an expression statement: its value is
        // discarded, except a Result, which must still be handled.
        if bodyType.kind == "result" && expressionBody.kind != "assignment-expression" { typeError(state, "Result value must be handled", expressionBody.span) }
      } else if !isAssignableWithInterfaces(state.result, bodyType, returnType) {
        typeError(state, "Cannot return " + displayTypeName(bodyType) + " from lambda returning " + displayTypeName(returnType), expressionBody.span)
      }
    }
  }
  if !parametersBound { return finish(state, expression, functionType(expectedFunction!.params, returnType)) }
  return finish(state, expression, functionType(params, returnType))
}

// Explicit parameter lists bind to the contextual signature in one of two
// ways. When every name belongs to the signature, parameters bind by name, so
// a lambda may list any subset in any order. Otherwise they bind by position,
// and a shorter list omits trailing parameters; this lets callers rename for
// clarity, as in `users.map((user) => user.name)`. Either way the list is
// rewritten into signature order, with discards for omitted positions, so the
// checker, capture analysis, and emitter all see one positional shape.
//
// A positional list that uses a signature name at another position is
// ambiguous and reported. The list is then left as written, so every recheck
// reports it again; the caller gives the lambda the expected signature so the
// error does not cascade into an argument mismatch.
function bindLambdaParameters(state: CheckerState, expression: LambdaExpression, expected: FunctionType): bool {
  params := expression.params
  if params.length == 0 || params.length > expected.params.length { return true }
  let slots: (Parameter | none)[] = []
  for _ of expected.params { slots.push(none) }
  let byName = true
  for parameter of params {
    index := if parameter.name == "_" then -1 else functionParameterIndex(expected.params, parameter.name)
    if index < 0 || slots[index] != none { byName = false; break }
    slots[index] = parameter
  }
  if !byName {
    let seen: string[] = []
    for i of 0..<params.length {
      name := params[i].name
      position := functionParameterIndex(expected.params, name)
      // Repeated names are reported as duplicate bindings when declared.
      if name != "_" && !seen.contains(name) && position >= 0 && position != i {
        typeError(state,
          "Lambda parameter '" + name + "' is parameter " + string(position + 1) + " of " + displayTypeName(expected) + " but is listed at position " + string(i + 1) + "; name only signature parameters to bind them by name, or list them in order",
          params[i].span,
        )
        return false
      }
      seen.push(name)
    }
    if params.length == expected.params.length { return true }
    for i of 0..<expected.params.length { slots[i] = if i < params.length then params[i] else none }
  }
  let bound: Parameter[] = []
  for i of 0..<slots.length {
    bound.push(slots[i] ?? Parameter { name: "_", type_: none, defaultValue: none, span: expression.span })
  }
  while params.length > 0 { ignored := try! params.pop() }
  for parameter of bound { params.push(parameter) }
  return true
}

// A lambda can use the single callable member of an optional or wider union as
// its contextual signature. More than one callable member is ambiguous, so in
// that case ordinary lambda checking reports the missing parameter context.
function contextualFunctionType(expected: ResolvedType | none): FunctionType | none {
  if expected == none { return none }
  case expected! {
    function_: FunctionType -> return function_,
    union_: UnionResolvedType -> {
      let found: FunctionType | none = none
      for member of union_.types {
        case member {
          function_: FunctionType -> {
            if found != none { return none }
            found = function_
          }
          _ -> { }
        }
      }
      return found
    }
    _ -> return none,
  }
}
