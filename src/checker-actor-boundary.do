// Actor-call boundary validation for the Doof checker.
//
// Validation is deliberately performed at call sites after generic
// substitution. The same method may be called locally without crossing an
// actor domain, while an Actor<T> receiver requires deeply immutable payloads or
// synchronized runtime handles (actors, promises, actor-affine callbacks, and
// `import isolated class` native handles).

import { AnalysisResult } from "./analyzer"
import {
  ActorType, ArrayResolvedType, ClassType, Diagnostic, EnumType, FunctionType, InterfaceType,
  SerialValueResolvedType, MapResolvedType, NoneType, PrimitiveType, PromiseType,
  ResolvedType, ResultResolvedType, SuccessResolvedType, FailureResolvedType, SetResolvedType, StreamResolvedType, TupleResolvedType,
  Symbol, TypeParameterType, UnionResolvedType, UnknownType, WeakResolvedType,
} from "./semantic"
import { ArrayType, AstFunctionType, CallExpression, ClassDeclaration, Expression, InterfaceDeclaration, MemberExpression, NamedType, TypeAnnotation, UnionType, WeakType } from "./ast"
import { classType, substituteTypeParams, typeName, typeParameter } from "./checker-types"
import { fieldDisplayName, findClassDeclaration, findInterfaceDeclaration } from "./checker-symbols"
import { pushDiagnostic } from "./checker-validation"

export class ActorBoundaryViolation {
  reason: string
}

export function findActorBoundaryViolation(result: AnalysisResult, type_: ResolvedType): ActorBoundaryViolation | none {
  return findViolation(result, type_, [], false)
}

export function validateDeepReadonlyFields(result: AnalysisResult): Diagnostic[] {
  let diagnostics: Diagnostic[] = []
  for module of result.modules {
    for raw of module.program.statements {
      case raw {
        class_: ClassDeclaration -> {
          for field of class_.fields {
            if !field.readonly_ || field.resolvedType == none { continue }
            violation := findViolation(result, field.resolvedType!, [], false)
            if violation == none { continue }
            name := fieldDisplayName(field)
            pushDiagnostic(diagnostics, module.path, field.span, "Readonly field \"" + class_.name + "." + name + "\" must be deeply immutable: " + violation!.reason)
          }
        }
        interface_: InterfaceDeclaration -> {
          for field of interface_.fields {
            if !field.readonly_ || field.resolvedType == none { continue }
            violation := findViolation(result, field.resolvedType!, [], false)
            if violation == none { continue }
            pushDiagnostic(diagnostics, module.path, field.span, "Readonly field \"" + interface_.name + "." + field.name + "\" must be deeply immutable: " + violation!.reason)
          }
        }
        _ -> { }
      }
    }
  }
  return diagnostics
}

// `unbound` is set while walking interface implementations whose type arguments
// the widened value no longer records. Their unbound type parameters may hold
// any instantiation, so only a boundary-safe constraint makes them safe.
function findViolation(result: AnalysisResult, type_: ResolvedType, seen: string[], unbound: bool): ActorBoundaryViolation | none {
  case type_ {
    _: PrimitiveType -> { return none }
    _: EnumType -> { return none }
    _: NoneType -> { return none }
    _: UnknownType -> { return none }
    parameter: TypeParameterType -> {
      if !unbound { return none }
      if parameter.constraint != none && parameter.constraint!.kind != "unknown" { return findViolation(result, parameter.constraint!, seen, unbound) }
      return ActorBoundaryViolation { reason: "unbound type parameter \"" + parameter.name + "\" may hold mutable values" }
    }
    _: SerialValueResolvedType -> { return none }
    // Actor and promise handles are synchronized runtime handles: actor state
    // stays behind messages, and a promise result has a single runtime-claimed
    // consumer, so neither shares mutable state across domains.
    _: ActorType -> { return none }
    _: PromiseType -> { return none }
    weak_: WeakResolvedType -> { return findViolation(result, weak_.inner, seen, unbound) }
    array: ArrayResolvedType -> {
      if !array.readonly_ { return ActorBoundaryViolation { reason: "array type \"" + typeName(type_) + "\" is mutable" } }
      return findViolation(result, array.elementType, seen, unbound)
    }
    map: MapResolvedType -> {
      if !map.readonly_ { return ActorBoundaryViolation { reason: "map type \"" + typeName(type_) + "\" is mutable" } }
      keyViolation := findViolation(result, map.keyType, seen, unbound)
      if keyViolation != none { return keyViolation }
      return findViolation(result, map.valueType, seen, unbound)
    }
    set_: SetResolvedType -> {
      if !set_.readonly_ { return ActorBoundaryViolation { reason: "set type \"" + typeName(type_) + "\" is mutable" } }
      return findViolation(result, set_.elementType, seen, unbound)
    }
    stream: StreamResolvedType -> { return ActorBoundaryViolation { reason: "stream type \"" + typeName(stream) + "\" is mutable" } }
    result_: ResultResolvedType -> {
      valueViolation := findViolation(result, result_.valueType, seen, unbound)
      if valueViolation != none { return valueViolation }
      return findViolation(result, result_.errorType, seen, unbound)
    }
    success: SuccessResolvedType -> { return findViolation(result, success.valueType, seen, unbound) }
    failure: FailureResolvedType -> { return findViolation(result, failure.errorType, seen, unbound) }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        violation := findViolation(result, element, seen, unbound)
        if violation != none { return violation }
      }
      return none
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        violation := findViolation(result, member, seen, unbound)
        if violation != none { return violation }
      }
      return none
    }
    function_: FunctionType -> {
      for parameter of function_.params {
        violation := findViolation(result, parameter.type_, seen, unbound)
        if violation != none {
          return ActorBoundaryViolation { reason: "callback parameter \"" + parameter.name + "\" cannot cross actor boundaries: " + violation!.reason }
        }
      }
      return findViolation(result, function_.returnType, seen, unbound)
    }
    class_: ClassType -> { return findClassViolation(result, class_, seen, unbound) }
    interface_: InterfaceType -> { return findInterfaceViolation(result, interface_, seen, unbound) }
  }
  return none
}

function findClassViolation(result: AnalysisResult, type_: ClassType, seen: string[], unbound: bool): ActorBoundaryViolation | none {
  key := (if unbound then "unbound-" else "") + "class:" + type_.symbol.module + ":" + typeName(type_)
  if seen.contains(key) { return none }
  let nextSeen: string[] = []
  for item of seen { nextSeen.push(item) }
  nextSeen.push(key)
  declaration := findClassDeclaration(result, type_.symbol.module, type_.symbol.name)
  if declaration == none { return none }
  // Native state is invisible to the checker, so only an explicit
  // `import isolated class` contract makes a native handle shareable.
  if declaration!.native_ && !declaration!.nativeIsolated {
    return ActorBoundaryViolation { reason: "native class \"" + declaration!.name + "\" is not declared \"import isolated class\"" }
  }
  for field of declaration!.fields {
    if field.static_ { continue }
    if field.let_ {
      name := fieldDisplayName(field)
      return ActorBoundaryViolation { reason: "field \"" + name + "\" is mutable" }
    }
    fieldType := field.resolvedType
    if fieldType == none { continue }
    effective := substituteTypeParams(fieldType!, declaration!.typeParams, type_.typeArgs)
    violation := findViolation(result, effective, nextSeen, unbound)
    if violation != none {
      name := fieldDisplayName(field)
      return ActorBoundaryViolation { reason: "field \"" + name + "\" cannot cross actor boundaries: " + violation!.reason }
    }
  }
  // Native code may carry a type argument that no field mentions (a channel's
  // message type), so every type argument must be boundary-safe itself.
  for index of 0..<type_.typeArgs.length {
    violation := findViolation(result, type_.typeArgs[index], nextSeen, unbound)
    if violation != none {
      parameterName := if index < declaration!.typeParams.length then declaration!.typeParams[index] else typeName(type_.typeArgs[index])
      return ActorBoundaryViolation { reason: "type argument \"" + parameterName + "\" cannot cross actor boundaries: " + violation!.reason }
    }
  }
  return none
}

function findInterfaceViolation(result: AnalysisResult, type_: InterfaceType, seen: string[], unbound: bool): ActorBoundaryViolation | none {
  key := (if unbound then "unbound-" else "") + "interface:" + type_.symbol.module + ":" + typeName(type_)
  if seen.contains(key) { return none }
  let nextSeen: string[] = []
  for item of seen { nextSeen.push(item) }
  nextSeen.push(key)
  declaration := findInterfaceDeclaration(result, type_.symbol.module, type_.symbol.name)
  if declaration == none { return none }
  for field of declaration!.fields {
    if field.let_ { return ActorBoundaryViolation { reason: "field \"" + field.name + "\" is mutable" } }
    if field.resolvedType == none { continue }
    effective := substituteTypeParams(field.resolvedType!, declaration!.typeParams, type_.typeArgs)
    violation := findViolation(result, effective, nextSeen, unbound)
    if violation != none {
      return ActorBoundaryViolation { reason: "field \"" + field.name + "\" cannot cross actor boundaries: " + violation!.reason }
    }
  }
  if declaration!.resolvedSymbol != none {
    for implementation of declaration!.resolvedSymbol!.implementations {
      violation := findClassViolation(result, implementationType(result, type_, implementation), nextSeen, true)
      if violation != none {
        return ActorBoundaryViolation {
          reason: "implementation \"" + implementation.name + "\" cannot cross actor boundaries: " + violation!.reason,
        }
      }
    }
  }
  return none
}

/** The implementation type reachable from a widened interface value. Type
 * parameters forwarded directly to this interface's arguments are bound; the
 * rest stay unbound type parameters carrying their declared constraints. */
export function implementationType(result: AnalysisResult, interface_: InterfaceType, implementation: Symbol): ClassType {
  declaration := findClassDeclaration(result, implementation.module, implementation.name)
  if declaration == none || declaration!.typeParams.length == 0 { return classType(implementation.name, implementation) }
  let typeArgs: ResolvedType[] = []
  for index of 0..<declaration!.typeParams.length {
    let constraint: ResolvedType | none = none
    if index < declaration!.typeParamConstraints.length && declaration!.typeParamConstraints[index].type_ != none {
      constraint = annotationType(declaration!.typeParamConstraints[index].type_!)
    }
    typeArgs.push(typeParameter(declaration!.typeParams[index], "", constraint))
  }
  for reference of declaration!.implements_ {
    if reference.resolvedType == none { continue }
    case reference.resolvedType! {
      implemented: InterfaceType -> {
        if implemented.symbol.module != interface_.symbol.module || implemented.symbol.name != interface_.symbol.name { continue }
        for index of 0..<implemented.typeArgs.length {
          if index >= interface_.typeArgs.length { break }
          case implemented.typeArgs[index] {
            parameter: TypeParameterType -> {
              for position of 0..<declaration!.typeParams.length {
                if declaration!.typeParams[position] == parameter.name { typeArgs[position] = interface_.typeArgs[index] }
              }
            }
            _ -> { }
          }
        }
      }
      _ -> { }
    }
  }
  return classType(implementation.name, implementation, typeArgs)
}

function annotationType(annotation: TypeAnnotation): ResolvedType | none {
  case annotation {
    named: NamedType -> { return named.resolvedType }
    array: ArrayType -> { return array.resolvedType }
    union_: UnionType -> { return union_.resolvedType }
    function_: AstFunctionType -> { return function_.resolvedType }
    weak_: WeakType -> { return weak_.resolvedType }
  }
  return none
}

/** Whether `expression` calls a method through an `Actor<T>` receiver. */
export function isActorMethodCall(expression: Expression): bool {
  case expression {
    call: CallExpression -> {
      case call.callee {
        member: MemberExpression -> {
          if member.object.resolvedType == none { return false }
          case member.object.resolvedType! {
            _: ActorType -> { return true }
            _ -> { return false }
          }
        }
        _ -> { return false }
      }
    }
    _ -> { return false }
  }
  return false
}
