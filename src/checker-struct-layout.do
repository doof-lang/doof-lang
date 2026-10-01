// Struct layout validation for the Doof checker.
//
// Structs lower to C++ value types, so a struct cannot contain itself by
// value. Optional, union, tuple, and Result wrappers embed their arms inline
// and therefore continue the containment chain; classes, collections,
// callbacks, and weak references are indirections and end it.

import { ClassDeclaration, ClassField } from "./ast"
import { ClassType, ResolvedType, ResultResolvedType, SuccessResolvedType, FailureResolvedType, Symbol, TupleResolvedType, UnionResolvedType } from "./semantic"
import { CheckerState } from "./checker-state"
import { typeError } from "./checker-common"
import { declarationFor } from "./checker-symbols"

export function validateStructLayout(state: CheckerState, class_: ClassDeclaration, symbol: Symbol): none {
  if !class_.struct_ { return }
  for field of class_.fields {
    if field.static_ || field.resolvedType == none { continue }
    let visited: string[] = []
    if embedsStruct(state, field.resolvedType!, symbol, visited) {
      typeError(state, "Struct \"" + class_.name + "\" cannot contain itself by value through field \"" + fieldName(field) + "\"; use a class or a collection to add indirection", field.span)
    }
  }
}

function embedsStruct(state: CheckerState, type_: ResolvedType, target: Symbol, visited: string[]): bool {
  case type_ {
    union_: UnionResolvedType -> {
      for member of union_.types { if embedsStruct(state, member, target, visited) { return true } }
      return false
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements { if embedsStruct(state, element, target, visited) { return true } }
      return false
    }
    result: ResultResolvedType -> {
      return embedsStruct(state, result.valueType, target, visited) || embedsStruct(state, result.errorType, target, visited)
    }
    success: SuccessResolvedType -> { return embedsStruct(state, success.valueType, target, visited) }
    failure: FailureResolvedType -> { return embedsStruct(state, failure.errorType, target, visited) }
    class_: ClassType -> {
      if class_.symbol.module == target.module && class_.symbol.name == target.name { return true }
      key := class_.symbol.module + ":" + class_.symbol.name
      for item of visited { if item == key { return false } }
      visited.push(key)
      declaration := declarationFor(state.result, class_.symbol)
      if declaration == none { return false }
      case declaration! {
        nested: ClassDeclaration -> {
          if !nested.struct_ { return false }
          for field of nested.fields {
            if field.static_ || field.resolvedType == none { continue }
            if embedsStruct(state, field.resolvedType!, target, visited) { return true }
          }
        }
        _ -> { }
      }
      return false
    }
    _ -> { return false }
  }
  return false
}

function fieldName(field: ClassField): string {
  return if field.names.length == 0 then "<field>" else field.names[0]
}
