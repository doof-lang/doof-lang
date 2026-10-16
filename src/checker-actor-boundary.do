// Actor-call boundary validation for the Doof checker.
//
// Validation is deliberately performed at call sites after generic
// substitution. The same method may be called locally without crossing an
// actor domain, while an Actor<T> receiver requires deeply immutable payloads or
// synchronized runtime handles (actors, promises, and actor-affine callbacks).

import { AnalysisResult } from "./analyzer"
import {
  ActorType, ArrayResolvedType, ClassType, Diagnostic, EnumType, FunctionType, InterfaceType,
  SerialValueResolvedType, MapResolvedType, NoneType, PrimitiveType, PromiseType,
  ResolvedType, ResultResolvedType, SuccessResolvedType, FailureResolvedType, SetResolvedType, StreamResolvedType, TupleResolvedType,
  TypeParameterType, UnionResolvedType, UnknownType, WeakResolvedType,
} from "./semantic"
import { CallExpression, ClassDeclaration, Expression, InterfaceDeclaration, MemberExpression } from "./ast"
import { classType, substituteTypeParams, typeName } from "./checker-types"
import { fieldDisplayName, findClassDeclaration, findInterfaceDeclaration } from "./checker-symbols"
import { pushDiagnostic } from "./checker-validation"

export class ActorBoundaryViolation {
  reason: string
}

export function findActorBoundaryViolation(result: AnalysisResult, type_: ResolvedType): ActorBoundaryViolation | none {
  return findViolation(result, type_, [])
}

export function validateDeepReadonlyFields(result: AnalysisResult): Diagnostic[] {
  let diagnostics: Diagnostic[] = []
  for module of result.modules {
    for raw of module.program.statements {
      case raw {
        class_: ClassDeclaration -> {
          for field of class_.fields {
            if !field.readonly_ || field.resolvedType == none { continue }
            violation := findViolation(result, field.resolvedType!, [])
            if violation == none { continue }
            name := fieldDisplayName(field)
            pushDiagnostic(diagnostics, module.path, field.span, "Readonly field \"" + class_.name + "." + name + "\" must be deeply immutable: " + violation!.reason)
          }
        }
        interface_: InterfaceDeclaration -> {
          for field of interface_.fields {
            if !field.readonly_ || field.resolvedType == none { continue }
            violation := findViolation(result, field.resolvedType!, [])
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

function findViolation(result: AnalysisResult, type_: ResolvedType, seen: string[]): ActorBoundaryViolation | none {
  case type_ {
    _: PrimitiveType -> { return none }
    _: EnumType -> { return none }
    _: NoneType -> { return none }
    _: UnknownType -> { return none }
    _: TypeParameterType -> { return none }
    _: SerialValueResolvedType -> { return none }
    // Actor and promise handles are synchronized runtime handles: actor state
    // stays behind messages, and a promise result has a single runtime-claimed
    // consumer, so neither shares mutable state across domains.
    _: ActorType -> { return none }
    _: PromiseType -> { return none }
    weak_: WeakResolvedType -> { return findViolation(result, weak_.inner, seen) }
    array: ArrayResolvedType -> {
      if !array.readonly_ { return ActorBoundaryViolation { reason: "array type \"" + typeName(type_) + "\" is mutable" } }
      return findViolation(result, array.elementType, seen)
    }
    map: MapResolvedType -> {
      if !map.readonly_ { return ActorBoundaryViolation { reason: "map type \"" + typeName(type_) + "\" is mutable" } }
      keyViolation := findViolation(result, map.keyType, seen)
      if keyViolation != none { return keyViolation }
      return findViolation(result, map.valueType, seen)
    }
    set_: SetResolvedType -> {
      if !set_.readonly_ { return ActorBoundaryViolation { reason: "set type \"" + typeName(type_) + "\" is mutable" } }
      return findViolation(result, set_.elementType, seen)
    }
    stream: StreamResolvedType -> { return ActorBoundaryViolation { reason: "stream type \"" + typeName(stream) + "\" is mutable" } }
    result_: ResultResolvedType -> {
      valueViolation := findViolation(result, result_.valueType, seen)
      if valueViolation != none { return valueViolation }
      return findViolation(result, result_.errorType, seen)
    }
    success: SuccessResolvedType -> { return findViolation(result, success.valueType, seen) }
    failure: FailureResolvedType -> { return findViolation(result, failure.errorType, seen) }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        violation := findViolation(result, element, seen)
        if violation != none { return violation }
      }
      return none
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        violation := findViolation(result, member, seen)
        if violation != none { return violation }
      }
      return none
    }
    function_: FunctionType -> {
      for parameter of function_.params {
        violation := findViolation(result, parameter.type_, seen)
        if violation != none {
          return ActorBoundaryViolation { reason: "callback parameter \"" + parameter.name + "\" cannot cross actor boundaries: " + violation!.reason }
        }
      }
      return findViolation(result, function_.returnType, seen)
    }
    class_: ClassType -> { return findClassViolation(result, class_, seen) }
    interface_: InterfaceType -> { return findInterfaceViolation(result, interface_, seen) }
  }
  return none
}

function findClassViolation(result: AnalysisResult, type_: ClassType, seen: string[]): ActorBoundaryViolation | none {
  key := "class:" + type_.symbol.module + ":" + typeName(type_)
  if seen.contains(key) { return none }
  let nextSeen: string[] = []
  for item of seen { nextSeen.push(item) }
  nextSeen.push(key)
  declaration := findClassDeclaration(result, type_.symbol.module, type_.symbol.name)
  if declaration == none { return none }
  for field of declaration!.fields {
    if field.static_ { continue }
    if field.let_ {
      name := fieldDisplayName(field)
      return ActorBoundaryViolation { reason: "field \"" + name + "\" is mutable" }
    }
    fieldType := field.resolvedType
    if fieldType == none { continue }
    effective := substituteTypeParams(fieldType!, declaration!.typeParams, type_.typeArgs)
    violation := findViolation(result, effective, nextSeen)
    if violation != none {
      name := fieldDisplayName(field)
      return ActorBoundaryViolation { reason: "field \"" + name + "\" cannot cross actor boundaries: " + violation!.reason }
    }
  }
  return none
}

function findInterfaceViolation(result: AnalysisResult, type_: InterfaceType, seen: string[]): ActorBoundaryViolation | none {
  key := "interface:" + type_.symbol.module + ":" + typeName(type_)
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
    violation := findViolation(result, effective, nextSeen)
    if violation != none {
      return ActorBoundaryViolation { reason: "field \"" + field.name + "\" cannot cross actor boundaries: " + violation!.reason }
    }
  }
  if declaration!.resolvedSymbol != none {
    for implementation of declaration!.resolvedSymbol!.implementations {
      implementationType := classType(implementation.name, implementation)
      violation := findClassViolation(result, implementationType, nextSeen)
      if violation != none {
        return ActorBoundaryViolation {
          reason: "implementation \"" + implementation.name + "\" cannot cross actor boundaries: " + violation!.reason,
        }
      }
    }
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
