// Call, construction, generic-call, and actor-boundary checking.

import { checkArguments, callArguments } from "./checker-arguments"
import { insideConstructorFactory, resolveConstructor, validateConstructorVisibility, validateFieldArguments } from "./checker-construction"

import { ActorType, Binding, ClassType, EnumType, FunctionParamType, FunctionType, PrimitiveType, ResolvedType, ResultResolvedType, Scope, UnionResolvedType, UnknownType, WeakResolvedType } from "./semantic"

import { CallExpression, ClassDeclaration, DotShorthand, Expression, FunctionDeclaration, Identifier, LambdaExpression, MemberExpression, SourceSpan, TypeParameterConstraint } from "./ast"
import { classType, functionType, resultArmExpectation, resultArmType, resultType, neverType, noneType, primitive, typeName, unionType, substituteTypeParams, unknownType, weakReferenceErrorType } from "./checker-types"

import { findActorBoundaryViolation } from "./checker-actor-boundary"

import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { resolveType, resolveCalleeTarget, validateTypeArgumentConstraints } from "./checker-resolution"
import { finish, typeError } from "./checker-common"
import { optionalResolvedType, functionParameterIndex, lookup, isBuiltinPrintlnCall, declarationFor } from "./checker-symbols"
import { inferTypeArgument } from "./checker-generics"
import { inferCallTypeArguments } from "./checker-call-inference"
import { withCallbackArity } from "./checker-array-methods"
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
        // A surrounding Result or matching arm types the payload; otherwise the
        // payload determines a standalone arm type.
        expectation := resultArmExpectation(identifier.name, expected)
        let valueType: ResolvedType = expectation.payload ?? noneType()
        if expression.args.length > 0 {
          valueType = checkExpression(state, expression.args[0].value, scope, expectation.payload)
          if expectation.payload != none && !isAssignableWithInterfaces(state.result, valueType, expectation.payload!) {
            channel := if identifier.name == "Success" then "success" else "failure"
            owner := expectation.result ?? resultArmType(identifier.name, expectation.payload!)
            typeError(state, "Cannot use " + typeName(valueType) + " as the " + channel + " value of " + typeName(owner), expression.args[0].span)
          }
          if expectation.payload != none { valueType = expectation.payload! }
        } else if valueType.kind != "none" && valueType.kind != "unknown" {
          typeError(state, identifier.name + "() needs a value for " + typeName(expectation.result ?? resultArmType(identifier.name, valueType)), expression.span)
        }
        produced: ResolvedType := expectation.result ?? resultArmType(identifier.name, valueType)
        callee := functionType([FunctionParamType { name: "value", type_: valueType, hasDefault: false }], produced)
        identifier.resolvedType = optionalResolvedType(callee)
        identifier.resolvedBinding = Binding { name: identifier.name, kind: "builtin", type_: callee, mutable: false, span: checkerSemanticSpan(identifier.span), module: state.info!.path }
        return finish(state, expression, produced)
      }
    }
    _ -> { }
  }
  // `.identity()` names a static method on the class the call must produce,
  // so a dot-shorthand callee resolves against the call's expected type.
  calleeType := checkExpression(state, expression.callee, scope, if expression.callee.kind == "dot-shorthand" then expected else none)
  target := resolveCalleeTarget(state, expression.callee, calleeType)
  expression.resolvedFunction = target.function_
  expression.resolvedFunctionModule = target.modulePath
  if calleeType.kind == "never" {
    for argument of expression.args { checkExpression(state, argument.value, scope, none) }
    return finish(state, expression, neverType())
  }
  case calleeType {
    declaredFunction: FunctionType -> {
      resolvedFunction := adaptArrayCallbackArity(state, expression, declaredFunction, scope)
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
        inferred := inferCallTypeArguments(state, expression.args, resolvedFunction, scope, expected)
        if inferred != none {
          expression.resolvedGenericTypeArgs = inferred!
          applyTypeArgumentConstraints(state, expression.resolvedFunction, inferred!, expression.span, scope, expression.resolvedFunctionModule, expression.callee)
          substituted := substituteTypeParams(resolvedFunction, resolvedFunction.typeParams, inferred!)
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

// A named function value passed to an array callback may omit the trailing
// `index` parameter. The narrowed signature is recorded on the callee so the
// emitter passes the argument with the arity the checker accepted.
function adaptArrayCallbackArity(state: CheckerState, expression: CallExpression, signature: FunctionType, scope: Scope): FunctionType {
  let member: MemberExpression | none = none
  case expression.callee { callee: MemberExpression -> { member = callee } _ -> { } }
  if member == none || member!.object.resolvedType == none || member!.object.resolvedType!.kind != "array" { return signature }
  let adapted = signature
  let changed = false
  for i of 0..<expression.args.length {
    argument := expression.args[i]
    case argument.value {
      _: LambdaExpression -> { continue }
      _: DotShorthand -> { continue }
      _ -> { }
    }
    parameterIndex := if argument.name == none then i else functionParameterIndex(adapted.params, argument.name!)
    if parameterIndex < 0 || parameterIndex >= adapted.params.length || adapted.params[parameterIndex].type_.kind != "function" { continue }
    diagnosticMark := state.diagnostics.length
    actual := checkExpression(state, argument.value, scope, none)
    while state.diagnostics.length > diagnosticMark { ignored := try! state.diagnostics.pop() }
    case actual {
      function_: FunctionType -> {
        narrowed := withCallbackArity(adapted, parameterIndex, function_.params.length)
        if narrowed != none { adapted = narrowed!; changed = true }
      }
      _ -> { }
    }
  }
  if changed { member!.resolvedType = adapted }
  return adapted
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
          receiver: ResultResolvedType -> {
            // '?.' over a Result keeps the receiver's Failure, adds none to the
            // success channel, and flattens a Result-returning method.
            if member.optional && member.resolvedOptionalReceiver != none {
              expression.resolvedOptionalValue = optionalResolvedType(returnType)
              case returnType {
                nested: ResultResolvedType -> {
                  return resultType(unionType([nested.valueType, noneType()]), unionType([receiver.errorType, nested.errorType]))
                }
                _ -> { return resultType(unionType([returnType, noneType()]), receiver.errorType) }
              }
            }
          }
          union_: UnionResolvedType -> {
            if member.optional {
              let includesNone = false
              for arm of union_.types { if arm.kind == "none" { includesNone = true } }
              if includesNone {
                expression.resolvedOptionalValue = optionalResolvedType(returnType)
                return unionType([returnType, noneType()])
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

export { checkLambda } from "./checker-lambdas"
