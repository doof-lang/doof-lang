// Declarative module initialization validation.
//
// Module values are backed by direct C++ storage and assigned by an explicit
// graph runner. Keep the accepted initializer language structural until a
// future effect analysis can prove that executable expressions are safe.

import {
  ArrayLiteral, BinaryExpression, BoolLiteral, CallExpression, CharLiteral, ClassDeclaration, ClassField, ConstDeclaration,
  ConstructExpression, DotShorthand, DoubleLiteral, ExportDeclaration, Expression,
  FloatLiteral, Identifier, ImmutableBinding, IntLiteral, LetDeclaration, LongLiteral, NoneLiteral,
  ObjectLiteral, ObjectProperty, ReadonlyDeclaration, Statement, StringLiteral, TupleLiteral,
  UnaryExpression,
} from "./ast"
import { CheckerState } from "./checker-state"
import {
  ArrayResolvedType, ClassType, EnumType, InterfaceType, JsonValueResolvedType,
  MapResolvedType, NoneType, PrimitiveType, ResolvedType, SetResolvedType,
  TupleResolvedType, WeakResolvedType,
} from "./semantic"
import { typeError } from "./checker-common"
import { declarationFor } from "./checker-symbols"
import { typeName } from "./checker-types"

/** Validates every eager initializer owned by one declarative statement. */
export function validateModuleInitializerStatement(state: CheckerState, statement: Statement): none {
  case statement {
    value: ConstDeclaration -> { validateValue(state, value.name, value.value, value.resolvedType); value.moduleInitializerChecked = true }
    value: ReadonlyDeclaration -> { validateValue(state, value.name, value.value, value.resolvedType); value.moduleInitializerChecked = true }
    value: ImmutableBinding -> { validateValue(state, value.name, value.value, value.resolvedType); value.moduleInitializerChecked = true }
    value: LetDeclaration -> { validateValue(state, value.name, value.value, value.resolvedType); value.moduleInitializerChecked = true }
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if !field.static_ || field.defaultValue == none { continue }
        validateField(state, class_, field)
        field.moduleInitializerChecked = true
      }
    }
    export_: ExportDeclaration -> { validateModuleInitializerStatement(state, export_.declaration) }
    _ -> { }
  }
}

function validateValue(state: CheckerState, name: string, value: Expression, type_: ResolvedType | none): none {
  if !literalTree(state, value) {
    typeError(
      state,
      "Module initializer for '" + name + "' must be a literal tree; move executable initialization into main() or an explicitly called function",
      value.span,
    )
    return
  }
  if type_ != none && !supportsDirectStorage(type_!) {
    typeError(
      state,
      "Module initializer for '" + name + "' has type " + typeName(type_!) +
        ", which cannot use direct default-constructed assignable storage",
      value.span,
    )
  }
}

function validateField(state: CheckerState, owner: ClassDeclaration, field: ClassField): none {
  if !literalTree(state, field.defaultValue!) {
    typeError(
      state,
      "Static field initializer for '" + owner.name + "." + field.names[0] +
        "' must be a literal tree; move executable initialization into an explicitly called function",
      field.defaultValue!.span,
    )
    return
  }
  if field.resolvedType != none && !supportsDirectStorage(field.resolvedType!) {
    typeError(
      state,
      "Static field initializer for '" + owner.name + "." + field.names[0] + "' has type " +
        typeName(field.resolvedType!) + ", which cannot use direct default-constructed assignable storage",
      field.defaultValue!.span,
    )
  }
}

function literalTree(state: CheckerState, expression: Expression): bool {
  case expression {
    _: IntLiteral -> { return true }
    _: LongLiteral -> { return true }
    _: FloatLiteral -> { return true }
    _: DoubleLiteral -> { return true }
    _: CharLiteral -> { return true }
    _: BoolLiteral -> { return true }
    _: NoneLiteral -> { return true }
    string_: StringLiteral -> { return string_.interpolations.length == 0 }
    unary: UnaryExpression -> {
      return unary.prefix && (unary.operator == "-" || unary.operator == "+") &&
        numericLiteral(unary.operand)
    }
    binary: BinaryExpression -> {
      return constantBinaryOperator(binary.operator) &&
        literalTree(state, binary.left) && literalTree(state, binary.right)
    }
    identifier: Identifier -> { return directScalarConstantBinding(state, identifier) }
    array: ArrayLiteral -> {
      for element of array.elements { if !literalTree(state, element) { return false } }
      return true
    }
    tuple: TupleLiteral -> {
      for element of tuple.elements { if !literalTree(state, element) { return false } }
      return true
    }
    object: ObjectLiteral -> {
      if object.spread != none && !literalTree(state, object.spread!) { return false }
      for property of object.properties { if !literalProperty(state, property) { return false } }
      if object.resolvedClass != none && !literalClassDefaults(state, object.resolvedClass!, object.properties) { return false }
      return object.resolvedClass == none || !object.resolvedClass!.native_
    }
    construct: ConstructExpression -> {
      if construct.resolvedClass == none || construct.resolvedClass!.native_ || construct.resolvedConstructor != none { return false }
      if construct.spread != none && !literalTree(state, construct.spread!) { return false }
      for argument of construct.args { if !literalProperty(state, argument) { return false } }
      return literalClassDefaults(state, construct.resolvedClass!, construct.args)
    }
    call: CallExpression -> {
      if call.resolvedClass == none || call.resolvedClass!.native_ || call.resolvedConstructor != none { return false }
      for argument of call.args { if !literalTree(state, argument.value) { return false } }
      return literalPositionalClassDefaults(state, call.resolvedClass!, call.args.length)
    }
    dot: DotShorthand -> { return dot.resolvedShorthandOwnerKind == "enum" }
    _ -> { return false }
  }
  return false
}

function constantBinaryOperator(operator: string): bool {
  return operator == "+" || operator == "-" || operator == "*" ||
    operator == "/" || operator == "\\" || operator == "%"
}

function directScalarConstantBinding(state: CheckerState, identifier: Identifier): bool {
  if identifier.resolvedBinding == none || identifier.resolvedBinding!.mutable ||
      identifier.resolvedBinding!.symbol == none {
    return false
  }
  declaration := declarationFor(state.result, identifier.resolvedBinding!.symbol!)
  if declaration == none { return false }
  case declaration! {
    value: ConstDeclaration -> { return scalarConstantInitializer(value.value) }
    value: ReadonlyDeclaration -> { return scalarConstantInitializer(value.value) }
    value: ImmutableBinding -> { return scalarConstantInitializer(value.value) }
    _ -> { return false }
  }
  return false
}

function scalarConstantInitializer(expression: Expression): bool {
  case expression {
    _: IntLiteral -> { return true }
    _: LongLiteral -> { return true }
    _: FloatLiteral -> { return true }
    _: DoubleLiteral -> { return true }
    _: CharLiteral -> { return true }
    _: BoolLiteral -> { return true }
    dot: DotShorthand -> { return dot.resolvedShorthandOwnerKind == "enum" }
    _ -> { return false }
  }
  return false
}

function numericLiteral(expression: Expression): bool {
  case expression {
    _: IntLiteral -> { return true }
    _: LongLiteral -> { return true }
    _: FloatLiteral -> { return true }
    _: DoubleLiteral -> { return true }
    _ -> { return false }
  }
  return false
}

function literalProperty(state: CheckerState, property: ObjectProperty): bool {
  if property.key != none && !literalTree(state, property.key!) { return false }
  if property.value == none { return false }
  return literalTree(state, property.value!)
}

function literalPositionalClassDefaults(state: CheckerState, class_: ClassDeclaration, suppliedCount: int): bool {
  let position = 0
  for field of class_.fields {
    if field.static_ { continue }
    if field.const_ {
      if field.defaultValue != none && !literalTree(state, field.defaultValue!) { return false }
      continue
    }
    for name of field.names {
      if position >= suppliedCount && field.defaultValue != none && !literalTree(state, field.defaultValue!) {
        return false
      }
      position = position + 1
    }
  }
  return true
}

function literalClassDefaults(state: CheckerState, class_: ClassDeclaration, supplied: ObjectProperty[]): bool {
  for field of class_.fields {
    if field.static_ { continue }
    for name of field.names {
      if suppliedProperty(supplied, name) { continue }
      if field.const_ {
        if field.defaultValue != none && !literalTree(state, field.defaultValue!) { return false }
        continue
      }
      if field.defaultValue != none && !literalTree(state, field.defaultValue!) { return false }
    }
  }
  return true
}

function suppliedProperty(properties: ObjectProperty[], name: string): bool {
  for property of properties { if property.name == name { return true } }
  return false
}

// This is deliberately conservative. New representations must opt in only
// when their emitted C++ type is known to support both operations.
function supportsDirectStorage(type_: ResolvedType): bool {
  case type_ {
    _: PrimitiveType -> { return true }
    _: EnumType -> { return true }
    _: NoneType -> { return true }
    _: ClassType -> { return true }
    _: ArrayResolvedType -> { return true }
    _: MapResolvedType -> { return true }
    _: SetResolvedType -> { return true }
    _: InterfaceType -> { return true }
    _: JsonValueResolvedType -> { return true }
    weak_: WeakResolvedType -> { return supportsDirectStorage(weak_.inner) }
    tuple: TupleResolvedType -> {
      for element of tuple.elements { if !supportsDirectStorage(element) { return false } }
      return true
    }
    _ -> { return false }
  }
  return false
}
