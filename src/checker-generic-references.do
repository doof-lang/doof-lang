// Generic functions and methods named as values.
//
// A call instantiates a generic callee from its arguments. A reference that is
// not called has no arguments, so its type arguments come from the expected
// function type alone, such as a typed parameter or an annotated binding. The
// instantiation is recorded on the reference for discovery and lowering.

import { Expression, GenericReference, Identifier, MemberExpression } from "./ast"
import { FunctionType, ResolvedType, Scope, UnionResolvedType } from "./semantic"
import { CheckerState } from "./checker-state"
import { typeError } from "./checker-common"
import { displayTypeName, functionType, substituteTypeParams, unknownType } from "./checker-types"
import { inferTypeArgument } from "./checker-generics"
import { resolveCalleeTarget } from "./checker-resolution"
import { applyTypeArgumentConstraints } from "./checker-calls"

/** Instantiates a generic function or method reference used as a value; other types pass through. */
export function instantiateGenericReference(state: CheckerState, expression: Expression, referenceType: ResolvedType, expected: ResolvedType | none, scope: Scope, calleePosition: bool): ResolvedType {
  clearGenericReference(expression)
  if calleePosition { return referenceType }
  let generic: FunctionType | none = none
  case referenceType {
    function_: FunctionType -> { if function_.typeParams.length > 0 { generic = function_ } }
    _ -> { }
  }
  if generic == none { return referenceType }
  target := resolveCalleeTarget(state, expression, referenceType)
  if target.function_ == none || target.function_!.typeParams.length == 0 { return referenceType }
  name := referenceName(expression)
  contextual := expectedFunction(expected)
  if contextual == none {
    typeError(state, "Generic function '" + name + "' can only be used as a value where a function type is expected, such as a typed parameter or an annotated binding", expression.span)
    // The uninstantiated signature still reports the reference's arity.
    return referenceType
  }
  let typeArgs: ResolvedType[] = []
  for typeParam of generic!.typeParams {
    inferred := inferFromSignature(generic!, contextual!, typeParam)
    if inferred == none {
      typeError(state, "Cannot infer type argument '" + typeParam + "' of generic function '" + name + "' from expected type " + displayTypeName(contextual!), expression.span)
      return unknownType()
    }
    typeArgs.push(inferred!)
  }
  applyTypeArgumentConstraints(state, target.function_, typeArgs, expression.span, scope, target.modulePath, expression)
  let instantiated: ResolvedType = unknownType()
  case substituteTypeParams(generic!, generic!.typeParams, typeArgs) {
    function_: FunctionType -> { instantiated = functionType(function_.params, function_.returnType) }
    _ -> { return unknownType() }
  }
  reference := GenericReference { function_: target.function_!, modulePath: target.modulePath, typeArgs }
  case expression {
    identifier: Identifier -> { identifier.resolvedGenericReference = reference }
    member: MemberExpression -> { member.resolvedGenericReference = reference }
    _ -> { }
  }
  return instantiated
}

// Each parameter and the result may fix a type parameter. Call inference can
// supply a partial expected type whose open parts are unknown; those are
// skipped so the remaining positions still decide.
function inferFromSignature(generic: FunctionType, expected: FunctionType, typeParam: string): ResolvedType | none {
  for i of 0..<generic.params.length {
    if i >= expected.params.length { break }
    candidate := inferTypeArgument(generic.params[i].type_, expected.params[i].type_, typeParam)
    if candidate != none && candidate!.kind != "unknown" { return candidate }
  }
  candidate := inferTypeArgument(generic.returnType, expected.returnType, typeParam)
  if candidate != none && candidate!.kind != "unknown" { return candidate }
  return none
}

// Expressions may be rechecked (speculative call inference), so a stale
// instantiation from an earlier pass must not survive.
function clearGenericReference(expression: Expression): none {
  case expression {
    identifier: Identifier -> { identifier.resolvedGenericReference = none }
    member: MemberExpression -> { member.resolvedGenericReference = none }
    _ -> { }
  }
}

function referenceName(expression: Expression): string {
  case expression {
    identifier: Identifier -> { return identifier.name }
    member: MemberExpression -> { return member.property }
    _ -> { return "" }
  }
}

// An optional function type (`F | none`) still fixes the instantiation.
function expectedFunction(expected: ResolvedType | none): FunctionType | none {
  if expected == none { return none }
  case expected! {
    function_: FunctionType -> { return if function_.typeParams.length == 0 then function_ else none }
    union_: UnionResolvedType -> {
      let found: FunctionType | none = none
      for member of union_.types {
        case member {
          function_: FunctionType -> {
            if found != none || function_.typeParams.length > 0 { return none }
            found = function_
          }
          _ -> { }
        }
      }
      return found
    }
    _ -> { }
  }
  return none
}
