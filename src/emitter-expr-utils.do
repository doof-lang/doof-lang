import { ModuleNames } from "./emitter-names"
// Shared expression-emission helpers.
//
// These helpers carry decorated-type and contextual-promotion logic so the
// expression dispatcher and its focused lowering modules stay small.

import { carrierOf } from "./emitter-carriers"
import { Expression, Identifier, ObjectProperty } from "./ast"
import { ResolvedType, Symbol, UnionResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { moduleNamespace } from "./emitter-names"
import { specializeEmitType } from "./emitter-types"

/** Shorthand and expanded fields share binding-aware contextual emission. */
export function emitPropertyValue(property: ObjectProperty, context: EmitContext, expected: ResolvedType | none = none): string {
  if property.value != none { return emitExpression(property.value!, context, expected) }
  return emitExpression(Identifier {
    kind: "identifier", name: property.name, span: property.span,
    resolvedType: property.resolvedType, resolvedBinding: property.resolvedBinding,
  }, context, expected)
}

/** Native returns preserve the checked unit and nonreturning boundaries. */
export function emitExpressionReturn(expression: Expression, context: EmitContext, expected: ResolvedType | none): string {
  actual := decoratedExpressionType(expression)
  if actual != none && specializeEmitType(actual!, context).kind == "never" {
    // A diverging return expression produces no value to convert, even when
    // other paths give the callable an inhabited return type.
    return emitExpression(expression, context) + "; doof::panic(\"never function returned\");"
  }
  value := emitExpression(expression, context, expected)
  if expected != none && specializeEmitType(expected!, context).kind == "never" {
    return value + "; doof::panic(\"never function returned\");"
  }
  if expected != none && carrierOf(specializeEmitType(expected!, context), .Return).kind == .Void {
    return "return static_cast<void>(" + value + ");"
  }
  return "return " + value + ";"
}

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

export function isNullableVariantType(type_: ResolvedType | none): bool {
  if type_ == none { return false }
  carrier := carrierOf(type_!)
  return carrier.kind == .Variant && carrier.hasNone && !carrier.naturalNullable
}

export function hasNoneMember(type_: ResolvedType | none): bool {
  return type_ != none && carrierOf(type_!).hasNone
}

// A nullable multi-arm union is represented as variant<monostate, ...>.
// Remove the absence arm before emitting a visitor whose checked member is
// only shared by the present alternatives. The runtime unwrap supplies the
// same failure boundary as other forced nullable access and keeps the visitor
// valid for every C++ alternative.
export function variantVisitValue(value: string, resolvedType: ResolvedType): string {
  if hasNoneMember(resolvedType) { return "doof::unwrap_optional(" + value + ")" }
  return value
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

export function exprModuleNamespaceFor(path: string, names: ModuleNames = ModuleNames {}): string {
  return moduleNamespace(path, names)
}

export function emittedSymbolName(symbol: Symbol): string {
  return if symbol.originalName == "" then symbol.name else symbol.originalName
}
