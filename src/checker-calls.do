// Call, lambda, construction, generic-call, and actor-boundary checking.

import { checkArguments, callArguments } from "./checker-arguments"
import { insideConstructorFactory, resolveConstructor, validateConstructorVisibility, validateFieldArguments } from "./checker-construction"

import { ActorType, Binding, ClassType, EnumType, FunctionParamType, FunctionType, PrimitiveType, ResolvedType, ResultResolvedType, Scope, UnionResolvedType, UnknownType, TypeParameterType, WeakResolvedType } from "./semantic"

import { Block, CallExpression, ClassDeclaration, DotShorthand, Expression, FunctionDeclaration, Identifier, LambdaExpression, MemberExpression, SourceSpan, TypeParameterConstraint, Parameter } from "./ast"
import { classType, functionType, resultType, neverType, noneType, primitive, sameType, typeName, unionType, substituteTypeParams, typeParameter, unknownType, weakReferenceErrorType } from "./checker-types"

import { findActorBoundaryViolation } from "./checker-actor-boundary"

import { CheckerState } from "./checker-state"
import { checkBlock } from "./checker-statements"
import { checkExpression } from "./checker-expressions"
import { resolveType, resolveCalleeTarget, validateTypeArgumentConstraints } from "./checker-resolution"
import { finish, typeError } from "./checker-common"
import { decorateAnnotationWithResolved, optionalResolvedType, functionParameterIndex, declare, lookup, isBuiltinPrintlnCall, declarationFor } from "./checker-symbols"
import { inferTypeArgument } from "./checker-generics"
import { classModuleFor, isAssignableWithInterfaces } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"

export function checkCall(state: CheckerState, expression: CallExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  case expression.callee {
    identifier: Identifier -> {
      if identifier.name == "string" && lookup(scope, identifier.name) == none {
        if expression.args.length != 1 {
          for argument of expression.args { checkExpression(state, argument.value, scope, none) }
          typeError(state, "string expects exactly one argument", expression.span)
          return finish(state, expression, primitive("string"))
        }
        actual := checkExpression(state, expression.args[0].value, scope, none)
        let supported = false
        case actual {
          _: PrimitiveType -> { supported = true }
          _: EnumType -> { supported = true }
          _: UnknownType -> { supported = true }
          _ -> { }
        }
        if !supported { typeError(state, "Argument 1 has type " + typeName(actual) + "; expected a primitive or enum", expression.args[0].span) }
        fn := functionType([FunctionParamType { name: "value", type_: actual, hasDefault: false }], primitive("string"))
        identifier.resolvedType = optionalResolvedType(fn)
        identifier.resolvedBinding = Binding { name: "string", kind: "builtin", type_: fn, mutable: false, span: checkerSemanticSpan(identifier.span), module: state.info!.path }
        return finish(state, expression, primitive("string"))
      }
      if (identifier.name == "Success" || identifier.name == "Failure") && lookup(scope, identifier.name) == none {
        let expectedResult: ResultResolvedType | none = none
        if expected != none {
          case expected! {
            result: ResultResolvedType -> { expectedResult = result }
            _ -> { }
          }
        }
        let valueType: ResolvedType = unknownType()
        if expression.args.length > 0 {
          let expectedValue: ResolvedType | none = none
          if expectedResult != none { expectedValue = if identifier.name == "Success" then expectedResult!.valueType else expectedResult!.errorType }
          valueType = checkExpression(state, expression.args[0].value, scope, expectedValue)
        }
        if expectedResult != none {
          valueType = if expression.args.length == 0 then (if identifier.name == "Success" then expectedResult!.valueType else expectedResult!.errorType) else valueType
          identifier.resolvedType = optionalResolvedType(functionType([FunctionParamType { name: "value", type_: valueType, hasDefault: false }], expectedResult!))
          identifier.resolvedBinding = Binding { name: identifier.name, kind: "builtin", type_: functionType([FunctionParamType { name: "value", type_: valueType, hasDefault: false }], expectedResult!), mutable: false, span: checkerSemanticSpan(identifier.span), module: state.info!.path }
          return finish(state, expression, expectedResult!)
        }
        typeError(state, identifier.name + " requires an expected Result type", identifier.span)
        if identifier.name == "Success" { return finish(state, expression, resultType(valueType, unknownType())) }
        return finish(state, expression, resultType(unknownType(), valueType))
      }
    }
    _ -> { }
  }
  calleeType := checkExpression(state, expression.callee, scope, none)
  target := resolveCalleeTarget(state, expression.callee, calleeType)
  expression.resolvedFunction = target.function_
  expression.resolvedFunctionModule = target.modulePath
  if calleeType.kind == "never" {
    for argument of expression.args { checkExpression(state, argument.value, scope, none) }
    return finish(state, expression, neverType())
  }
  case calleeType {
    resolvedFunction: FunctionType -> {
      let effectiveFunction: FunctionType = resolvedFunction
      let genericInferenceFailed = false
      if expression.typeArgs.length > 0 {
        if expression.typeArgs.length != resolvedFunction.typeParams.length {
          typeError(state, 
            "Generic call requires " + string(resolvedFunction.typeParams.length) + " type argument" + (if resolvedFunction.typeParams.length == 1 then "" else "s") + "; received " + string(expression.typeArgs.length),
            expression.span,
          )
        } else {
          let resolvedTypeArgs: ResolvedType[] = []
          for argument of expression.typeArgs { resolvedTypeArgs.push(resolveType(state, argument, state.info!, scope)) }
          expression.resolvedGenericTypeArgs = resolvedTypeArgs
          applyTypeArgumentConstraints(state, expression.resolvedFunction, resolvedTypeArgs, expression.span, scope, expression.resolvedFunctionModule, expression.callee)
          substituted := substituteTypeParams(resolvedFunction, resolvedFunction.typeParams, resolvedTypeArgs)
          case substituted {
            function_: FunctionType -> { effectiveFunction = function_ }
            _ -> { }
          }
        }
      } else if resolvedFunction.typeParams.length > 0 {
        let inferred: ResolvedType[] = []
        let complete = true
        for typeParam of resolvedFunction.typeParams {
          let inferredType: ResolvedType | none = none
          for i of 0..<expression.args.length {
            parameterIndex := if expression.args[i].name == none then i else functionParameterIndex(resolvedFunction.params, expression.args[i].name!)
            if parameterIndex < 0 || parameterIndex >= resolvedFunction.params.length { continue }
            parameterType := resolvedFunction.params[parameterIndex].type_
            // Unresolved type parameters still carry useful callback input
            // types, which are required to type shorthand lambda bindings.
            let inferenceExpected = genericInferenceExpected(parameterType, resolvedFunction.typeParams)
            case expression.args[i].value {
              _: LambdaExpression -> { inferenceExpected = parameterType }
              _: DotShorthand -> { if inferenceExpected == none { continue } }
              _ -> { }
            }
            actual := checkExpression(state, expression.args[i].value, scope, inferenceExpected)
            candidate := inferTypeArgument(parameterType, actual, typeParam)
            if candidate != none {
              let candidateIsSelf = false
              case candidate! { parameter: TypeParameterType -> { candidateIsSelf = parameter.name == typeParam } _ -> { } }
              let inferredIsSelf = false
              if inferredType != none { case inferredType! { parameter: TypeParameterType -> { inferredIsSelf = parameter.name == typeParam } _ -> { } } }
              if candidateIsSelf && inferredType != none { continue }
              if inferredType == none || (inferredIsSelf && !candidateIsSelf) { inferredType = candidate }
              else if sameType(inferredType!, candidate!) { }
              else if isAssignableWithInterfaces(state.result, candidate!, inferredType!) { }
              else if isAssignableWithInterfaces(state.result, inferredType!, candidate!) { inferredType = candidate }
              else { complete = false }
            }
          }
          if inferredType == none { complete = false; inferred.push(typeParameter(typeParam)) }
          else { inferred.push(inferredType!) }
        }
        if complete {
          expression.resolvedGenericTypeArgs = inferred
          applyTypeArgumentConstraints(state, expression.resolvedFunction, inferred, expression.span, scope, expression.resolvedFunctionModule, expression.callee)
          substituted := substituteTypeParams(resolvedFunction, resolvedFunction.typeParams, inferred)
          case substituted {
            function_: FunctionType -> { effectiveFunction = function_ }
            _ -> { }
          }
        } else {
          genericInferenceFailed = true
          typeError(state, "Cannot infer consistent type arguments for generic call; provide explicit type arguments", expression.span)
        }
      }
      checkArguments(state, callArguments(expression.args), effectiveFunction.params, scope, expression.span,
        "", "Argument", !genericInferenceFailed && !isBuiltinPrintlnCall(expression.callee), !genericInferenceFailed)
      validateActorMethodBoundary(state, expression, effectiveFunction)
      if callArgumentsDiverge(expression) { return finish(state, expression, neverType()) }
      return finish(state, expression, checkedMemberCallReturnType(expression, effectiveFunction.returnType))
    }
    class_: ClassType -> {
      let effectiveClass = class_
      declaration := declarationFor(state.result, class_.symbol)
      if expression.typeArgs.length > 0 {
        let declaredTypeParams: string[] = []
        let constraints: TypeParameterConstraint[] = if expression.resolvedClass == none then [] else expression.resolvedClass!.typeParamConstraints
        if declaration != none { case declaration! { classDeclaration: ClassDeclaration -> { declaredTypeParams = classDeclaration.typeParams; constraints = classDeclaration.typeParamConstraints } _ -> { } } }
        if expression.typeArgs.length != declaredTypeParams.length {
          typeError(state, "Generic construction requires " + string(declaredTypeParams.length) + " type argument" + (if declaredTypeParams.length == 1 then "" else "s") + "; received " + string(expression.typeArgs.length), expression.span)
        } else {
          let resolvedTypeArgs: ResolvedType[] = []
          for argument of expression.typeArgs { resolvedTypeArgs.push(resolveType(state, argument, state.info!, scope)) }
          expression.resolvedGenericTypeArgs = resolvedTypeArgs
          effectiveClass = classType(class_.name, class_.symbol, resolvedTypeArgs)
          validateTypeArgumentConstraints(state, declaredTypeParams, constraints, resolvedTypeArgs, expression.span, classModuleFor(state.result, class_.symbol), scope)
        }
      } else if declaration != none && class_.typeArgs.length == 0 {
        case declaration! {
          classDeclaration: ClassDeclaration -> {
            inferred := inferClassTypeArguments(state, expression, scope, class_, classDeclaration)
            if inferred.length == classDeclaration.typeParams.length && inferred.length > 0 {
              effectiveClass = classType(class_.name, class_.symbol, inferred)
              expression.resolvedGenericTypeArgs = inferred
              validateTypeArgumentConstraints(state, classDeclaration.typeParams, classDeclaration.typeParamConstraints, inferred, expression.span, classModuleFor(state.result, class_.symbol), scope)
            }
          }
          _ -> { }
        }
      }
      construction := resolveConstructor(state, effectiveClass, !insideConstructorFactory(scope, effectiveClass))
      expression.resolvedConstruction = construction
      expression.resolvedClass = construction.declaration
      expression.resolvedConstructor = construction.factory
      if construction.factory != none { validateConstructorVisibility(state, effectiveClass, construction.factory!, expression.span) }
      constructorParams := construction.signature.params
      validateFieldArguments(state, construction, effectiveClass, callArguments(expression.args))
      kind := if effectiveClass.symbol.kind == "struct" then "Struct" else "Class"
      checkArguments(state, callArguments(expression.args), constructorParams, scope, expression.span, kind + " \"" + effectiveClass.name + "\"")
      return finish(state, expression, construction.signature.returnType)
    }
    _: UnknownType -> {
      for argument of expression.args { checkExpression(state, argument.value, scope, none) }
      return finish(state, expression, unknownType())
    }
    _ -> { typeError(state, "Expression of type " + typeName(calleeType) + " is not callable", expression.span); return finish(state, expression, unknownType()) }
  }
  return finish(state, expression, unknownType())
}

// Concrete parts of a generic signature remain valid contextual types during
// inference. Expressions that depend on a type parameter are checked after
// substitution; a direct dot-shorthand can therefore learn that type from a
// sibling argument without producing an early no-context diagnostic.
function genericInferenceExpected(pattern: ResolvedType, typeParams: string[]): ResolvedType | none {
  let unknownArguments: ResolvedType[] = []
  for _ of typeParams { unknownArguments.push(unknownType()) }
  substituted := substituteTypeParams(pattern, typeParams, unknownArguments)
  if sameType(pattern, substituted) { return pattern }
  return none
}

function checkedMemberCallReturnType(expression: CallExpression, returnType: ResolvedType): ResolvedType {
  case expression.callee {
    member: MemberExpression -> {
      if member.object.resolvedType != none {
        case member.object.resolvedType! {
          _: WeakResolvedType -> {
            if member.optional {
              case returnType {
                result: ResultResolvedType -> {
                  return resultType(unionType([result.valueType, noneType()]), unionType([result.errorType, weakReferenceErrorType()]))
                }
                _ -> { return resultType(unionType([returnType, noneType()]), weakReferenceErrorType()) }
              }
            }
          }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  return returnType
}

function callArgumentsDiverge(expression: CallExpression): bool {
  for argument of expression.args {
    if argument.value.resolvedType != none && argument.value.resolvedType!.kind == "never" { return true }
  }
  return false
}

function inferClassTypeArguments(state: CheckerState, expression: CallExpression, scope: Scope, class_: ClassType, declaration: ClassDeclaration): ResolvedType[] {
  patterns := resolveConstructor(state, class_).signature.params
  let inferred: ResolvedType[] = []
  for typeParam of declaration.typeParams {
    let candidate: ResolvedType | none = none
    for index of 0..<expression.args.length {
      parameterIndex := if expression.args[index].name == none then index else functionParameterIndex(patterns, expression.args[index].name!)
      if parameterIndex < 0 || parameterIndex >= patterns.length { continue }
      actual := checkExpression(state, expression.args[index].value, scope, optionalResolvedType(patterns[parameterIndex].type_))
      next := inferTypeArgument(patterns[parameterIndex].type_, actual, typeParam)
      if next != none { candidate = next }
    }
    if candidate == none { return [] }
    inferred.push(candidate!)
  }
  return inferred
}

function applyTypeArgumentConstraints(state: CheckerState, declaration: FunctionDeclaration | none, arguments: ResolvedType[], span: SourceSpan, scope: Scope, modulePath: string, callee: Expression): none {
  if declaration == none { return }
  let module = state.info!
  for candidate of state.result.modules { if candidate.path == modulePath { module = candidate } }
  let ownerNames: string[] = []
  let ownerArguments: ResolvedType[] = []
  let receiver: ResolvedType | none = none
  case callee {
    member: MemberExpression -> { receiver = member.object.resolvedType }
    identifier: Identifier -> {
      if identifier.resolvedBinding != none && identifier.resolvedBinding!.kind == "method" {
        let current: Scope | none = scope
        while current != none {
          if current!.thisType != none && current!.thisType!.kind == "class" { receiver = current!.thisType; break }
          current = current!.parent
        }
      }
    }
    _ -> { }
  }
  if receiver != none {
    case receiver! {
      owner: ClassType -> {
        ownerDeclaration := declarationFor(state.result, owner.symbol)
        if ownerDeclaration != none {
          case ownerDeclaration! {
            class_: ClassDeclaration -> { ownerNames = class_.typeParams; ownerArguments = owner.typeArgs }
            _ -> { }
          }
        }
      }
      _ -> { }
    }
  }
  validateTypeArgumentConstraints(state, declaration!.typeParams, declaration!.typeParamConstraints, arguments, span, module, scope, ownerNames, ownerArguments)
}

// Positional class calls share function-call assignability rules, but report
// the nominal constructor range so invalid calls never reach C++ emission.
// Actor calls validate the effective method signature after generic
// substitution; ordinary calls on the same class remain local calls.
export function validateActorMethodBoundary(state: CheckerState, expression: CallExpression, method: FunctionType): none {
  let actor: ActorType | none = none
  case expression.callee {
    member: MemberExpression -> {
      if member.object.resolvedType != none {
        case member.object.resolvedType! {
          actorType_: ActorType -> { actor = actorType_ }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  if actor == none { return }
  for parameter of method.params {
    violation := findActorBoundaryViolation(state.result, parameter.type_)
    if violation != none {
      typeError(state, 
        "Actor method parameter \"" + parameter.name + "\" of type \"" + typeName(parameter.type_) + "\" cannot cross actor boundary for \"" + typeName(actor!) + "\": " + violation!.reason,
        expression.span,
      )
    }
  }
  returnViolation := findActorBoundaryViolation(state.result, method.returnType)
  if returnViolation != none {
    typeError(state, 
      "Actor method return type \"" + typeName(method.returnType) + "\" cannot cross actor boundary for \"" + typeName(actor!) + "\": " + returnViolation!.reason,
      expression.span,
    )
  }
}

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
    block: Block -> { checkBlock(state, block, lambdaScope) }
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
