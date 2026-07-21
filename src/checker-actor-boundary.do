// Actor-call boundary validation for the Doof checker.
//
// Validation is deliberately performed at call sites after generic
// substitution. The same method may be called locally without crossing an
// actor domain, while an Actor<T> receiver requires deeply immutable payloads.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  ActorType, ArrayResolvedType, ClassType, EnumType, FunctionType, InterfaceType,
  JsonValueResolvedType, MapResolvedType, NoneType, PrimitiveType, PromiseType,
  ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, TupleResolvedType,
  TypeParameterType, UnionResolvedType, UnknownType, WeakResolvedType,
} from "./semantic"
import { ClassDeclaration, ExportDeclaration, InterfaceDeclaration, Statement } from "./ast"
import { classType, substituteTypeParams, typeName } from "./checker-types"

export class ActorBoundaryViolation {
  reason: string
}

export function findActorBoundaryViolation(result: AnalysisResult, type_: ResolvedType): ActorBoundaryViolation | none {
  return findViolation(result, type_, [])
}

function findViolation(result: AnalysisResult, type_: ResolvedType, seen: string[]): ActorBoundaryViolation | none {
  case type_ {
    _: PrimitiveType -> { return none }
    _: EnumType -> { return none }
    _: NoneType -> { return none }
    _: UnknownType -> { return none }
    _: TypeParameterType -> { return none }
    _: JsonValueResolvedType -> { return none }
    _: ActorType -> { return ActorBoundaryViolation { reason: "Actor<T> references cannot cross actor boundaries" } }
    _: PromiseType -> { return ActorBoundaryViolation { reason: "Promise<T> values cannot cross actor boundaries" } }
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
  if containsString(seen, key) { return none }
  let nextSeen: string[] = []
  for item of seen { nextSeen.push(item) }
  nextSeen.push(key)
  declaration := classDeclaration(result, type_.symbol.module, type_.symbol.name)
  if declaration == none { return none }
  for field of declaration!.fields {
    if !field.readonly_ {
      name := if field.names.length == 0 then "<field>" else field.names[0]
      return ActorBoundaryViolation { reason: "field \"" + name + "\" is mutable" }
    }
    fieldType := field.resolvedType
    if fieldType == none { continue }
    effective := substituteTypeParams(fieldType!, declaration!.typeParams, type_.typeArgs)
    violation := findViolation(result, effective, nextSeen)
    if violation != none {
      name := if field.names.length == 0 then "<field>" else field.names[0]
      return ActorBoundaryViolation { reason: "field \"" + name + "\" cannot cross actor boundaries: " + violation!.reason }
    }
  }
  return none
}

function findInterfaceViolation(result: AnalysisResult, type_: InterfaceType, seen: string[]): ActorBoundaryViolation | none {
  key := "interface:" + type_.symbol.module + ":" + typeName(type_)
  if containsString(seen, key) { return none }
  let nextSeen: string[] = []
  for item of seen { nextSeen.push(item) }
  nextSeen.push(key)
  declaration := interfaceDeclaration(result, type_.symbol.module, type_.symbol.name)
  if declaration == none { return none }
  for field of declaration!.fields {
    if !field.readonly_ { return ActorBoundaryViolation { reason: "field \"" + field.name + "\" is mutable" } }
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

function classDeclaration(result: AnalysisResult, modulePath: string, name: string): ClassDeclaration | none {
  module := findModule(result, modulePath)
  if module == none { return none }
  for statement of module!.program.statements {
    case unwrapExport(statement) {
      class_: ClassDeclaration -> { if class_.name == name { return class_ } }
      _ -> { }
    }
  }
  return none
}

function interfaceDeclaration(result: AnalysisResult, modulePath: string, name: string): InterfaceDeclaration | none {
  module := findModule(result, modulePath)
  if module == none { return none }
  for statement of module!.program.statements {
    case unwrapExport(statement) {
      interface_: InterfaceDeclaration -> { if interface_.name == name { return interface_ } }
      _ -> { }
    }
  }
  return none
}

function unwrapExport(statement: Statement): Statement {
  case statement {
    export_: ExportDeclaration -> { return export_.declaration }
    _ -> { return statement }
  }
}

function findModule(result: AnalysisResult, path: string): ModuleInfo | none {
  for module of result.modules { if module.path == path { return module } }
  return none
}

function containsString(values: string[], value: string): bool {
  for item of values { if item == value { return true } }
  return false
}
