// Call, construction, generic-call, and actor-boundary checking.

import { checkArguments, callArguments } from "./checker-arguments"
import { cannotInferConstruction, inferConstructionTypeArguments, insideConstructorFactory, resolveConstructor, validateConstructorVisibility, validateFieldArguments } from "./checker-construction"

import { ActorType, Binding, ClassType, EnumType, FunctionType, PrimitiveType, ResolvedType, Scope, UnionResolvedType, UnknownType, WeakResolvedType } from "./semantic"

import { CallExpression, ClassDeclaration, DotShorthand, Expression, FunctionDeclaration, Identifier, LambdaExpression, MemberExpression, SourceSpan, TypeParameterConstraint } from "./ast"
import { classType, functionType, param, resultArmExpectation, resultArmType, isStringInterpolatable, memberReceiverType, neverType, noneType, primitive, typeName, substituteTypeParams, unknownType } from "./checker-types"

import { findActorBoundaryViolation } from "./checker-actor-boundary"

import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { resolveCalleeTarget } from "./checker-resolution"
import { resolveTypeArguments, validateTypeArgumentConstraints } from "./checker-annotations"
import { discardDiagnosticsSince, finish, typeArgumentArityMessage, typeError } from "./checker-common"
import { builtinCallable, functionParameterIndex, lookup, isBuiltinPrintlnCall, declarationFor } from "./checker-symbols"
import { inferCallTypeArguments } from "./checker-call-inference"
import { withCallbackArity } from "./checker-array-methods"
import { classModuleFor, findModule, isAssignableWithInterfaces } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"
import { optionalAccessType } from "./checker-absence"

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
          union_: UnionResolvedType -> { supported = isStringConvertibleUnion(union_) }
          _ -> { }
        }
        if !supported { typeError(state, "Argument 1 has type ${typeName(actual)}; expected a primitive, enum, or union of them", expression.args[0].span) }
        fn := functionType([param("value", actual)], primitive("string"))
        identifier.resolvedType = fn
        identifier.resolvedBinding = Binding { name: "string", kind: "builtin", type_: fn, mutable: false, span: checkerSemanticSpan(identifier.span), module: state.info!.path }
        return finish(state, expression, primitive("string"))
      }
      if isNumericCastName(identifier.name) && expression.args.length == 1 && lookup(scope, identifier.name) == none {
        // The accepted-input union is an overload set, not a variant: the
        // argument keeps its own type so `byte(if c then 255 else 0)` casts
        // an int rather than a union the emitter cannot static_cast.
        target := primitive(identifier.name)
        accepted := numericCastInputs(identifier.name)
        actual := checkExpression(state, expression.args[0].value, scope, none)
        if !isNumericCastInput(actual, accepted) {
          typeError(state, "Argument 1 has type ${typeName(actual)}; expected ${typeName(accepted)}", expression.args[0].span)
        }
        fn := functionType([param("value", actual)], target)
        identifier.resolvedType = fn
        identifier.resolvedBinding = Binding { name: identifier.name, kind: "builtin", type_: fn, mutable: false, span: checkerSemanticSpan(identifier.span), module: state.info!.path }
        return finish(state, expression, target)
      }
      if (identifier.name == "Success" || identifier.name == "Failure") && lookup(scope, identifier.name) == none {
        // A surrounding Result or matching arm types the payload; otherwise the
        // payload determines a standalone arm type.
        expectation := resultArmExpectation(identifier.name, expected)
        let valueType: ResolvedType = expectation.payload ?? noneType()
        if expression.args.length > 0 {
          valueType = checkExpression(state, expression.args[0].value, scope, expectation.payload)
          if payload := expectation.payload && !isAssignableWithInterfaces(state.result, valueType, payload) {
            channel := if identifier.name == "Success" then "success" else "failure"
            owner := expectation.result ?? resultArmType(identifier.name, payload)
            typeError(state, "Cannot use ${typeName(valueType)} as the ${channel} value of ${typeName(owner)}", expression.args[0].span)
          }
          if payload := expectation.payload { valueType = payload }
        } else if valueType.kind != "none" && valueType.kind != "unknown" {
          typeError(state, "${identifier.name}() needs a value for ${typeName(expectation.result ?? resultArmType(identifier.name, valueType))}", expression.span)
        }
        produced: ResolvedType := expectation.result ?? resultArmType(identifier.name, valueType)
        callee := functionType([param("value", valueType)], produced)
        identifier.resolvedType = callee
        identifier.resolvedBinding = Binding { name: identifier.name, kind: "builtin", type_: callee, mutable: false, span: checkerSemanticSpan(identifier.span), module: state.info!.path }
        return finish(state, expression, produced)
      }
    }
    _ -> { }
  }
  // `.identity()` names a static method on the class the call must produce,
  // so a dot-shorthand callee resolves against the call's expected type.
  state.checkingCallee = true
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
      if staticOwner := genericStaticOwner(expression.callee) {
        // `Stack.empty<int>()` fixes the method's own parameters; the class's
        // are still inferred from the arguments.
        let signature = resolvedFunction
        let methodArgs: ResolvedType[] = []
        if expression.typeArgs.length > 0 {
          explicit := explicitCallTypeArguments(state, expression, resolvedFunction, scope)
          if explicit == none { genericInferenceFailed = true } else {
            methodArgs = explicit!
            substituted := substituteSignature(resolvedFunction, resolvedFunction.typeParams, methodArgs)
            signature = FunctionType { params: substituted.params, returnType: substituted.returnType }
          }
        }
        if !genericInferenceFailed {
          instantiated := instantiateGenericStaticCall(state, expression, staticOwner, signature, scope, expected)
          if instantiated == none {
            // The reported inference failure leaves the class open; its
            // parameters must not leak into the arguments or the result.
            for argument of expression.args { checkExpression(state, argument.value, scope, none) }
            return finish(state, expression, unknownType())
          }
          effectiveFunction = instantiated!
          if methodArgs.length > 0 { applyCallTypeArguments(state, expression, methodArgs, scope) }
        }
      } else if expression.typeArgs.length > 0 || resolvedFunction.typeParams.length > 0 {
        let typeArgs: ResolvedType[] | none = none
        if expression.typeArgs.length == 0 {
          typeArgs = inferCallTypeArguments(state, expression.args, resolvedFunction, scope, expected)
          if typeArgs == none {
            genericInferenceFailed = true
            typeError(state, "Cannot infer consistent type arguments for generic call; provide explicit type arguments", expression.span)
          }
        } else {
          typeArgs = explicitCallTypeArguments(state, expression, resolvedFunction, scope)
        }
        if explicitTypeArgs := typeArgs {
          applyCallTypeArguments(state, expression, explicitTypeArgs, scope)
          effectiveFunction = substituteSignature(resolvedFunction, resolvedFunction.typeParams, explicitTypeArgs)
        }
      }
      checkArguments(state, callArguments(expression.args), effectiveFunction.params, scope, expression.span,
        "", "Argument", !genericInferenceFailed && !isBuiltinPrintlnCall(expression.callee), !genericInferenceFailed && !isBuiltinPrintlnCall(expression.callee))
      if isBuiltinPrintlnCall(expression.callee) { checkPrintlnArguments(state, expression) }
      validateActorMethodBoundary(state, expression, effectiveFunction)
      if callArgumentsDiverge(expression) { return finish(state, expression, neverType()) }
      return finish(state, expression, checkedMemberCallReturnType(expression, effectiveFunction.returnType))
    }
    class_: ClassType -> {
      let effectiveClass = class_
      declaration := declarationFor(state.result, class_.symbol)
      if expression.typeArgs.length > 0 {
        let declaredTypeParams: string[] = []
        let constraints: TypeParameterConstraint[] = expression.resolvedClass?.typeParamConstraints ?? []
        if targetDeclaration := declaration { case targetDeclaration { classDeclaration: ClassDeclaration -> { declaredTypeParams = classDeclaration.typeParams; constraints = classDeclaration.typeParamConstraints } _ -> { } } }
        if expression.typeArgs.length != declaredTypeParams.length {
          typeError(state, typeArgumentArityMessage("Generic construction", declaredTypeParams.length, expression.typeArgs.length), expression.span)
        } else {
          resolvedTypeArgs := resolveTypeArguments(state, expression.typeArgs, scope)
          expression.resolvedGenericTypeArgs = resolvedTypeArgs
          effectiveClass = classType(class_.name, class_.symbol, resolvedTypeArgs)
          validateTypeArgumentConstraints(state, declaredTypeParams, constraints, resolvedTypeArgs, expression.span, classModuleFor(state.result, class_.symbol), scope)
        }
      } else if targetDeclaration := declaration && class_.typeArgs.length == 0 {
        case targetDeclaration {
          classDeclaration: ClassDeclaration -> {
            if classDeclaration.typeParams.length > 0 {
              if inferred := inferConstructionTypeArguments(state, expression.args, class_, classDeclaration, scope, expected) {
                effectiveClass = classType(class_.name, class_.symbol, inferred)
                expression.resolvedGenericTypeArgs = inferred
                validateTypeArgumentConstraints(state, classDeclaration.typeParams, classDeclaration.typeParamConstraints, inferred, expression.span, classModuleFor(state.result, class_.symbol), scope)
              } else {
                cannotInferConstruction(state, classDeclaration, expression.args, scope, expression.span)
                return finish(state, expression, unknownType())
              }
            }
          }
          _ -> { }
        }
      }
      construction := resolveConstructor(state, effectiveClass, !insideConstructorFactory(scope, effectiveClass))
      expression.resolvedConstruction = construction
      expression.resolvedClass = construction.declaration
      expression.resolvedConstructor = construction.factory
      if factory := construction.factory { validateConstructorVisibility(state, effectiveClass, factory, expression.span) }
      constructorParams := construction.signature.params
      validateFieldArguments(state, construction, effectiveClass, callArguments(expression.args))
      kind := if effectiveClass.symbol.kind == "struct" then "Struct" else "Class"
      checkArguments(state, callArguments(expression.args), constructorParams, scope, expression.span, "${kind} \"${effectiveClass.name}\"")
      return finish(state, expression, construction.signature.returnType)
    }
    _: UnknownType -> {
      for argument of expression.args { checkExpression(state, argument.value, scope, none) }
      return finish(state, expression, unknownType())
    }
    _ -> { typeError(state, "Expression of type ${typeName(calleeType)} is not callable", expression.span); return finish(state, expression, unknownType()) }
  }
  return finish(state, expression, unknownType())
}

function isNumericCastName(name: string): bool {
  return name == "byte" || name == "int" || name == "long" || name == "float" || name == "double"
}

function numericCastInputs(name: string): ResolvedType {
  case builtinCallable(name) {
    fn: FunctionType -> { return fn.params[0].type_ }
    _ -> { return unknownType() }
  }
}

// A cast lowers to static_cast, so its argument must be exactly one accepted
// primitive; a union value would need to be narrowed first.
function isNumericCastInput(actual: ResolvedType, accepted: ResolvedType): bool {
  case actual {
    _: UnknownType -> { return true }
    primitive_: PrimitiveType -> {
      case accepted {
        union_: UnionResolvedType -> {
          for member of union_.types { if typeName(member) == primitive_.name { return true } }
        }
        _ -> { }
      }
      return false
    }
    _ -> { return actual.kind == "never" }
  }
}

// string() accepts a union only when every member is itself convertible, so
// a nullable union still needs its none handled explicitly.
function isStringConvertibleUnion(union_: UnionResolvedType): bool {
  for member of union_.types {
    case member {
      _: PrimitiveType -> { }
      _: EnumType -> { }
      _ -> { return false }
    }
  }
  return true
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
    discardDiagnosticsSince(state, diagnosticMark)
    case actual {
      function_: FunctionType -> {
        if narrowed := withCallbackArity(adapted, parameterIndex, function_.params.length) { adapted = narrowed; changed = true }
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
      if resolvedType := member.object.resolvedType && member.optional {
        // A Result receiver was already lowered to '(r?)', so every '?.' call
        // short-circuits to none; a Result-returning method keeps its Failure.
        let absentReceiver = false
        case resolvedType {
          _: WeakResolvedType -> { absentReceiver = true }
          union_: UnionResolvedType -> { for arm of union_.types { if arm.kind == "none" { absentReceiver = true } } }
          _ -> { }
        }
        if absentReceiver {
          expression.resolvedOptionalValue = returnType
          return optionalAccessType(returnType)
        }
      }
    }
    _ -> { }
  }
  return returnType
}

// Explicit `f<A, B>(...)` arguments, or none after reporting an arity mismatch.
function explicitCallTypeArguments(state: CheckerState, expression: CallExpression, signature: FunctionType, scope: Scope): ResolvedType[] | none {
  if expression.typeArgs.length != signature.typeParams.length {
    typeError(state, typeArgumentArityMessage("Generic call", signature.typeParams.length, expression.typeArgs.length), expression.span)
    return none
  }
  return resolveTypeArguments(state, expression.typeArgs, scope)
}

function applyCallTypeArguments(state: CheckerState, expression: CallExpression, typeArgs: ResolvedType[], scope: Scope): none {
  expression.resolvedGenericTypeArgs = typeArgs
  applyTypeArgumentConstraints(state, expression.resolvedFunction, typeArgs, expression.span, scope, expression.resolvedFunctionModule, expression.callee)
}

function substituteSignature(signature: FunctionType, names: string[], typeArgs: ResolvedType[]): FunctionType {
  case substituteTypeParams(signature, names, typeArgs) {
    function_: FunctionType -> { return function_ }
    _ -> { }
  }
  return signature
}

/**
 * `Channel.constructor(handler)` reaches a static method through a generic
 * class written without type arguments. The class's type parameters are
 * inferred together with the method's own, and the receiver is decorated with
 * the concrete class it names. Returns none when inference fails.
 */
function instantiateGenericStaticCall(state: CheckerState, expression: CallExpression, owner: ClassDeclaration, signature: FunctionType, scope: Scope, expected: ResolvedType | none): FunctionType | none {
  member := staticReceiver(expression.callee)!
  let combinedParams: string[] = []
  for name of owner.typeParams { combinedParams.push(name) }
  for name of signature.typeParams { combinedParams.push(name) }
  combined := FunctionType { params: signature.params, returnType: signature.returnType, typeParams: combinedParams }
  inferred := inferCallTypeArguments(state, expression.args, combined, scope, expected)
  if inferred == none {
    let names = ""
    for i of 0..<owner.typeParams.length { names = names + (if i > 0 then ", " else "") + owner.typeParams[i] }
    typeError(state, "Cannot infer type arguments for generic class '${owner.name}' from this call to static method '${member.property}'; its arguments must determine ${names}, or write ${owner.name}<${names}>.${member.property}(...)", expression.span)
    return none
  }
  classArgs := inferred!.slice(0, owner.typeParams.length)
  methodArgs := inferred!.slice(owner.typeParams.length, inferred!.length)
  case member.object.resolvedType! {
    receiver: ClassType -> {
      validateTypeArgumentConstraints(state, owner.typeParams, owner.typeParamConstraints, classArgs, expression.span, classModuleFor(state.result, receiver.symbol), scope)
      member.resolvedStaticReceiver = ClassType { name: receiver.name, symbol: receiver.symbol, typeArgs: classArgs }
    }
    _ -> { }
  }
  if methodArgs.length > 0 { applyCallTypeArguments(state, expression, methodArgs, scope) }
  substituted := substituteSignature(combined, combinedParams, inferred!)
  instantiated := FunctionType { params: substituted.params, returnType: substituted.returnType }
  member.resolvedType = instantiated
  return instantiated
}

function staticReceiver(callee: Expression): MemberExpression | none {
  case callee {
    member: MemberExpression -> { if member.resolvedStaticOwner != none { return member } }
    _ -> { }
  }
  return none
}

/** The generic class named by a static call written without type arguments, such as `Channel.constructor`. */
function genericStaticOwner(callee: Expression): ClassDeclaration | none {
  member := staticReceiver(callee)
  if member == none || member!.resolvedStaticReceiver != none || member!.resolvedStaticOwner!.typeParams.length == 0 || member!.object.resolvedType == none { return none }
  case member!.object.resolvedType! {
    receiver: ClassType -> { if receiver.typeArgs.length == 0 { return member!.resolvedStaticOwner } }
    _ -> { }
  }
  return none
}

function callArgumentsDiverge(expression: CallExpression): bool {
  for argument of expression.args {
    if resolvedType := argument.value.resolvedType && resolvedType.kind == "never" { return true }
  }
  return false
}

export function applyTypeArgumentConstraints(state: CheckerState, declaration: FunctionDeclaration | none, arguments: ResolvedType[], span: SourceSpan, scope: Scope, modulePath: string, callee: Expression): none {
  if declaration == none { return }
  module := findModule(state.result, modulePath) ?? state.info!
  let ownerNames: string[] = []
  let ownerArguments: ResolvedType[] = []
  let receiver: ResolvedType | none = none
  case callee {
    member: MemberExpression -> { receiver = memberReceiverType(member) }
    identifier: Identifier -> {
      if resolvedBinding := identifier.resolvedBinding && resolvedBinding.kind == "method" {
        let current: Scope | none = scope
        while current != none {
          if thisType := current!.thisType && thisType.kind == "class" { receiver = current!.thisType; break }
          current = current!.parent
        }
      }
    }
    _ -> { }
  }
  if receiverType := receiver {
    case receiverType {
      owner: ClassType -> {
        if ownerDeclaration := declarationFor(state.result, owner.symbol) {
          case ownerDeclaration {
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
      if resolvedType := member.object.resolvedType {
        case resolvedType {
          actorType_: ActorType -> { actor = actorType_ }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  if actor == none { return }
  for parameter of method.params {
    if violation := findActorBoundaryViolation(state.result, parameter.type_) {
      typeError(state, 
        "Actor method parameter \"${parameter.name}\" of type \"${typeName(parameter.type_)}\" cannot cross actor boundary for \"${typeName(actor!)}\": ${violation.reason}",
        expression.span,
      )
    }
  }
  if returnViolation := findActorBoundaryViolation(state.result, method.returnType) {
    typeError(state, 
      "Actor method return type \"${typeName(method.returnType)}\" cannot cross actor boundary for \"${typeName(actor!)}\": ${returnViolation.reason}",
      expression.span,
    )
  }
}

export { checkLambda } from "./checker-lambdas"

// println accepts every type that string interpolation can format.
function checkPrintlnArguments(state: CheckerState, expression: CallExpression): none {
  for argument of expression.args {
    if actual := argument.value.resolvedType && !isStringInterpolatable(actual) {
      typeError(state, "Type \"${typeName(actual)}\" cannot be passed to println", argument.value.span)
    }
  }
}
