// Shared expression-emission helpers.
//
// These helpers carry decorated-type and contextual-promotion logic so the
// expression dispatcher and its focused lowering modules stay small.

import { Expression, Identifier, ObjectProperty } from "./ast"
import { ClassType, InterfaceType, NoneType, PrimitiveType, ResolvedType, ResultResolvedType, Symbol, UnionResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { moduleNamespace } from "./emitter-names"
import { emitType } from "./emitter-types"
import { isAssignable, sameType } from "./checker-types"

export function decoratedExpressionType(expression: Expression): ResolvedType | none {
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding != none { return identifier.resolvedBinding!.type_ }
    }
    _ -> { }
  }
  if expression.resolvedType != none { return expression.resolvedType }
  return none
}

export function optionalExpectedType(value: ResolvedType): ResolvedType | none { return value }

export function emitExpectedExpression(expression: Expression, context: EmitContext, expected: ResolvedType | none): string {
  return emitExpression(expression, context, expected)
}

export function needsNullableVariantPromotion(source: ResolvedType | none, expected: ResolvedType | none): bool {
  if expected == none || !isNullableVariantType(expected) || source == none { return false }
  case source! {
    _: NoneType -> { return false }
    _ -> { }
  }
  return !hasNoneMember(source)
}

/** Promotes a non-null value into a nullable multi-arm union using its actual carrier. */
export function emitNullableVariantPromotion(value: string, source: ResolvedType | none, expected: ResolvedType | none, currentModulePath: string): string {
  if source == none || expected == none { panic("Nullable variant promotion requires checked source and target types") }
  if nullablePromotionSourceUsesVariant(source!) { return "doof::optional_value(" + value + ")" }
  return "doof::variant_promote<" + emitType(expected!, currentModulePath) + ">(" + value + ")"
}

function nullablePromotionSourceUsesVariant(source: ResolvedType): bool {
  case source {
    _: InterfaceType -> { return true }
    _: ResultResolvedType -> { return true }
    _: UnionResolvedType -> { return true }
    class_: ClassType -> { return isAstVariantClass(class_.name) }
    _ -> { return false }
  }
  return false
}

// C++ std::variant does not implicitly convert one variant into a wider
// variant, even when every source alternative exists in the target. Doof
// union assignability does allow that promotion, so emission must make it
// explicit at contextual boundaries such as returns and arguments.
export function needsVariantPromotion(source: ResolvedType | none, expected: ResolvedType | none): bool {
  if source == none || expected == none || sameType(source!, expected!) || hasNoneMember(expected) { return false }
  case expected! {
    _: UnionResolvedType -> { return isAssignable(source!, expected!) }
    _ -> { return false }
  }
  return false
}

export function isNullableVariantType(resolvedType: ResolvedType | none): bool {
  if resolvedType == none { return false }
  case resolvedType! {
    union_: UnionResolvedType -> {
      let hasNone = false
      let nonNoneCount = 0
      for member of union_.types {
        if member.kind == "none" { hasNone = true }
        else { nonNoneCount = nonNoneCount + 1 }
      }
      if !hasNone { return false }
      if nonNoneCount > 1 { return true }
      for member of union_.types {
        case member {
          class_: ClassType -> { return isAstVariantClass(class_.name) }
          _ -> { }
        }
      }
      return false
    }
    _ -> { return false }
  }
  return false
}

function isAstVariantClass(name: string): bool {
  return name == "Expression" || name == "Statement" || name == "TypeAnnotation"
}

export function hasNoneMember(resolvedType: ResolvedType | none): bool {
  if resolvedType == none { return false }
  case resolvedType! {
    _: NoneType -> { return true }
    union_: UnionResolvedType -> {
      for member of union_.types { if member.kind == "none" { return true } }
    }
    _ -> { }
  }
  return false
}

export function requireExpressionType(expression: Expression, description: string): ResolvedType {
  if expression.resolvedType == none {
    panic("Missing resolved type for " + description + " at line " + string(expression.span.start.line) + ":" + string(expression.span.start.column))
  }
  return expression.resolvedType!
}

export function hasSinglePrimitiveMember(union_: UnionResolvedType): bool {
  let count = 0
  for member of union_.types {
    if member.kind == "none" { continue }
    if member.kind != "primitive" { return false }
    count = count + 1
  }
  return count == 1
}

export function findProperty(properties: ObjectProperty[], name: string): ObjectProperty | none {
  for property of properties { if property.name == name { return property } }
  return none
}

export function exprModuleNamespaceFor(path: string): string {
  return moduleNamespace(path)
}

export function emittedSymbolName(symbol: Symbol): string {
  return if symbol.originalName == "" then symbol.name else symbol.originalName
}
