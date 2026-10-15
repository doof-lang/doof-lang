// Map key and Set element validation for the Doof checker.
//
// Hash collections key by Doof `==`: scalars, strings, and enums by value;
// class and interface references by identity; tuples, unions, and structs by
// their members. Floating-point values are excluded because exact equality and
// NaN make poor keys. Arrays, collections, callbacks, actors, and weak
// references are rejected rather than silently keyed by reference.

import { AnalysisResult } from "./analyzer"
import { ClassDeclaration, SourceSpan } from "./ast"
import { typeError } from "./checker-common"
import { CheckerState } from "./checker-state"
import { declarationFor } from "./checker-symbols"
import { substituteTypeParams, typeName } from "./checker-types"
import { ClassType, PrimitiveType, ResolvedType, TupleResolvedType, UnionResolvedType } from "./semantic"

export readonly HASH_KEY_RULE = "Map keys and Set elements may be byte, string, int, long, char, bool, enums, class or interface references, or tuples, unions, and structs of those"

/** Reports an unsupported Map key or Set element type at its source span. */
export function reportUnsupportedHashKey(state: CheckerState, type_: ResolvedType, role: string, span: SourceSpan): none {
  message := hashKeyDiagnostic(state.result, type_, role)
  if message != none { typeError(state, message!, span) }
}

/**
 * Returns the diagnostic for a hash-collection key type, or none when it is
 * supported. `role` names the position, such as "Map key" or "Set element".
 * Type parameters are accepted here and validated per concrete instantiation,
 * which passes the generic key type and its bindings, such as "T = double".
 */
export function hashKeyDiagnostic(result: AnalysisResult, type_: ResolvedType, role: string, generic: ResolvedType | none = none, bindings: string = ""): string | none {
  let visited: string[] = []
  blocker := hashKeyBlocker(result, type_, visited)
  if blocker == none { return none }
  detail := if blocker! == "" then "" else " (" + blocker! + ")"
  shown := if generic == none then typeName(type_) else typeName(generic!)
  condition := if bindings == "" then "" else " when " + bindings
  return role + " type \"" + shown + "\" is not supported" + condition + detail + "; " + HASH_KEY_RULE
}

// "" marks the type itself as unsupported; other text names the nested part.
function hashKeyBlocker(result: AnalysisResult, type_: ResolvedType, visited: string[]): string | none {
  case type_ {
    primitive_: PrimitiveType -> {
      if primitive_.name == "float" || primitive_.name == "double" { return "" }
      return none
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        inner := hashKeyBlocker(result, element, visited)
        if inner != none { return nested(element, inner!) }
      }
      return none
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        if member.kind == "none" { continue }
        inner := hashKeyBlocker(result, member, visited)
        if inner != none { return nested(member, inner!) }
      }
      return none
    }
    class_: ClassType -> { return structBlocker(result, class_, visited) }
    _ -> { }
  }
  case type_.kind {
    "enum" | "interface" | "type-parameter" | "unknown" -> { return none }
    _ -> { return "" }
  }
  return ""
}

function nested(part: ResolvedType, blocker: string): string {
  return if blocker == "" then "contains \"" + typeName(part) + "\"" else blocker
}

// Classes key by identity. Structs key by the fields their equality compares.
function structBlocker(result: AnalysisResult, class_: ClassType, visited: string[]): string | none {
  if class_.symbol.kind != "struct" { return none }
  if class_.symbol.native_ { return "native struct \"" + typeName(class_) + "\" has no generated hash" }
  key := class_.symbol.module + ":" + class_.symbol.name
  for item of visited { if item == key { return none } }
  visited.push(key)
  declaration := declarationFor(result, class_.symbol)
  if declaration == none { return none }
  case declaration! {
    struct_: ClassDeclaration -> {
      for field of struct_.fields {
        if field.static_ || field.resolvedType == none { continue }
        fieldType := if struct_.typeParams.length == 0 then field.resolvedType! else substituteTypeParams(field.resolvedType!, struct_.typeParams, class_.typeArgs)
        inner := hashKeyBlocker(result, fieldType, visited)
        if inner != none {
          return if inner! == "" then "field \"" + field.names[0] + "\" of \"" + typeName(class_) + "\" has type \"" + typeName(fieldType) + "\"" else inner!
        }
      }
    }
    _ -> { }
  }
  return none
}
