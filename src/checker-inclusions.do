// Types of fields copied by declaration field inclusion.
//
// An included field is not re-checked in the includer: its type and default
// were decided while checking the source declaration. The includer only
// substitutes the type arguments written at the inclusion.

import { ModuleInfo } from "./analyzer"
import { ClassType, Scope } from "./semantic"
import type { ResolvedType } from "./semantic"
import { ClassDeclaration, IncludedField } from "./ast"
import { CheckerState } from "./checker-state"
import { resolveType } from "./checker-annotations"
import { substituteTypeParams, unknownType } from "./checker-types"

/** Resolves each admissible inclusion annotation once, reporting arity and constraint errors. */
export function resolveFieldInclusions(state: CheckerState, class_: ClassDeclaration, module: ModuleInfo, classScope: Scope): none {
  for inclusion of class_.inclusions {
    if inclusion.resolvedSource == none { continue }
    ignored := resolveType(state, inclusion.type_, module, classScope)
  }
}

/** The includer's view of a source field's checked type, or unknown until the source is prepared. */
export function includedFieldType(state: CheckerState, origin: IncludedField, module: ModuleInfo, classScope: Scope): ResolvedType {
  sourceType := origin.sourceField.resolvedType else { return unknownType() }
  if origin.source.typeParams.length == 0 { return sourceType }
  inclusionType := origin.inclusion.type_.resolvedType ?? resolveType(state, origin.inclusion.type_, module, classScope)
  included := inclusionType as ClassType else { return unknownType() }
  if included.typeArgs.length != origin.source.typeParams.length { return unknownType() }
  return substituteTypeParams(sourceType, origin.source.typeParams, included.typeArgs)
}
