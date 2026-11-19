import { ModuleNames } from "./emitter-names"
// Shared expression-emission helpers.
//
// These helpers carry decorated-type and contextual-promotion logic so the
// expression dispatcher and its focused lowering modules stay small.

import { carrierOf } from "./emitter-carriers"
import { Expression, Identifier, ObjectProperty } from "./ast"
import { ClassType, ResolvedType, Symbol, UnionResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { cppIdentifier, moduleNamespace } from "./emitter-names"
import { emitContextReturnType, specializeEmitType } from "./emitter-types"

/** Shorthand and expanded fields share binding-aware contextual emission. */
export function emitPropertyValue(property: ObjectProperty, context: EmitContext, expected: ResolvedType | none = none): string {
  if value := property.value { return emitExpression(value, context, expected) }
  return emitExpression(Identifier {
    kind: "identifier", name: property.name, span: property.span,
    resolvedType: property.resolvedType, resolvedBinding: property.resolvedBinding,
  }, context, expected)
}

/** Native returns preserve the checked unit and nonreturning boundaries. */
export function emitExpressionReturn(expression: Expression, context: EmitContext, expected: ResolvedType | none): string {
  if actual := decoratedExpressionType(expression) && specializeEmitType(actual, context).kind == "never" {
    // A diverging return expression produces no value to convert, even when
    // other paths give the callable an inhabited return type.
    return emitExpression(expression, context) + "; doof::panic(\"never function returned\");"
  }
  value := emitExpression(expression, context, expected)
  if expectedType := expected && specializeEmitType(expectedType, context).kind == "never" {
    return value + "; doof::panic(\"never function returned\");"
  }
  if expectedType := expected && carrierOf(specializeEmitType(expectedType, context), .Return).kind == .Void {
    return "return static_cast<void>(" + value + ");"
  }
  return "return " + value + ";"
}

export function decoratedExpressionType(expression: Expression): ResolvedType | none {
  case expression {
    identifier: Identifier -> {
      if resolvedBinding := identifier.resolvedBinding { return resolvedBinding.type_ }
    }
    _ -> { }
  }
  if expression.resolvedType != none { return expression.resolvedType }
  return none
}

export function optionalExpectedType(value: ResolvedType): ResolvedType | none { return value }

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

// Class arms of a union carrier are shared_ptr alternatives, while struct arms
// are held by value. A visitor over a union with any struct arm reaches the
// member through doof::variant_member so every alternative compiles. Calls use
// doof::variant_receiver, which copies an immutable struct arm.
export function variantMember(visited: string, resolvedType: ResolvedType | none, call: bool = false): string {
  case resolvedType {
    union_: UnionResolvedType -> {
      for member of union_.types {
        case member {
          class_: ClassType -> { if class_.symbol.kind == "struct" { return (if call then "doof::variant_receiver(" else "doof::variant_member(") + visited + ")." } }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  return visited + "->"
}

// Reads one field from whichever arm a variant carrier holds. Union arms and
// interface implementations may declare the field with different types (the
// checker joins them, and a read-only interface field is covariant), so the
// visitor returns the checked field type when it is known.
export function emitVariantFieldRead(source: string, carrierType: ResolvedType | none, field: string, fieldType: ResolvedType | none, context: EmitContext): string {
  returnType := if fieldType == none then "" else " -> " + emitContextReturnType(fieldType!, context)
  return "std::visit([](auto&& _obj)" + returnType + " { return " + variantMember("_obj", carrierType) + cppIdentifier(field) + "; }, " + source + ")"
}

export function requireExpressionType(expression: Expression, description: string): ResolvedType {
  if expression.resolvedType == none {
    panic("Missing resolved type for " + description + " at line " + string(expression.span.start.line) + ":" + string(expression.span.start.column))
  }
  return expression.resolvedType!
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
