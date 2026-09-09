// Lambda signatures, block-return inference, and callable completion checking.
import { Block, Expression, LambdaExpression, Parameter } from "./ast"
import { Binding, FunctionParamType, FunctionType, ResolvedType, Scope, UnionResolvedType } from "./semantic"
import { CheckerState, LambdaReturnInference } from "./checker-state"
import { functionType, neverType, noneType, typeName, unknownType } from "./checker-types"
import { pathType } from "./checker-inference"
import { checkBlock } from "./checker-statements"
import { checkExpression } from "./checker-expressions"
import { resolveType } from "./checker-resolution"
import { finish, typeError } from "./checker-common"
import { decorateAnnotationWithResolved, optionalResolvedType, declare } from "./checker-symbols"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"

export function checkLambda(state: CheckerState, expression: LambdaExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  expectedFunction := contextualFunctionType(expected)
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
  lambdaScope := Scope { parent: scope }
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
            typeError(state, "Expected a return value of type " + typeName(returnType), observation.statement.span)
          } else if !isAssignableWithInterfaces(state.result, observation.type_, returnType) {
            typeError(state, "Cannot return " + typeName(observation.type_) + " from lambda returning " + typeName(returnType), observation.statement.span)
          }
        }
      }
      if completes && returnType.kind != "none" && returnType.kind != "unknown" {
        typeError(state, "Lambda may complete without returning " + typeName(returnType), expression.span)
      }
    }
    expressionBody: Expression -> { returnType = checkExpression(state, expressionBody, lambdaScope, optionalResolvedType(returnType)) }
  }
  return finish(state, expression, functionType(params, returnType))
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
