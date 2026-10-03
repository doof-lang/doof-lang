// Function and method references used as values.
//
// Doof function values lower to `doof::callback<R(Args...)>`. A bare C++
// function name, static member function, or member access does not deduce to
// that type (and `obj->method` is not a C++ value at all), so references that
// are not immediately called are wrapped here. Calls emit their callee through
// `emitCalleeExpression`, which keeps the direct C++ call form.

import { Expression, GenericReference, Identifier, MemberExpression } from "./ast"
import { ClassType, FunctionType, ResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { emitIdentifier, emitMember } from "./emitter-expr-ops"
import { cppIdentifier } from "./emitter-names"
import { variantVisitValue } from "./emitter-expr-utils"
import { emitContextReturnType, emitContextType, specializeEmitType, usesVariantRepresentation } from "./emitter-types"
import { implementationlessInterface } from "./emitter-no-implementations"
import { concreteGenericTarget } from "./emitter-expr-calls"

readonly forwardedArguments = "std::forward<decltype(_args)>(_args)..."

/** Emits a call's callee without wrapping a named function as a callback value. */
export function emitCalleeExpression(callee: Expression, context: EmitContext): string {
  case callee {
    identifier: Identifier -> { return emitIdentifier(identifier, context) }
    member: MemberExpression -> { return emitMember(member, context) }
    _ -> { return emitExpression(callee, context) }
  }
}

/** Wraps an identifier naming a function or method as a callback value. */
export function emitIdentifierValue(identifier: Identifier, emitted: string, context: EmitContext, expected: ResolvedType | none = none): string {
  let value = emitted
  if identifier.resolvedBinding == none { return value }
  binding := identifier.resolvedBinding!
  // A generic reference names its concrete instantiation instead.
  if identifier.resolvedGenericReference != none { value = concreteReferenceName(identifier, identifier.resolvedGenericReference!, context) }
  signature := referenceSignature(identifier.resolvedType, expected, context)
  if signature == none { return value }
  callbackType := emitContextType(signature!, context)
  if binding.kind == "function" || (binding.kind == "import" && binding.symbol != none && binding.symbol!.kind == "function") {
    return callbackType + "(" + value + ")"
  }
  if binding.kind != "method" { return value }
  // An implicit method reference inside a class. Static contexts can only name
  // static methods; elsewhere the receiver is captured, which also serves
  // static methods called through it.
  if context.currentFunctionStatic { return callbackType + "(" + value + ")" }
  structOwner := binding.symbol != none && binding.symbol!.kind == "struct"
  receiver := if structOwner then "*this" else "this->shared_from_this()"
  access := if structOwner then "_self." else "_self->"
  return boundCallback(callbackType, receiver, emitContextReturnType(signature!.returnType, context), access + value + "(" + forwardedArguments + ")", structOwner)
}

/** Wraps a member naming a static or bound instance method as a callback value. */
export function emitMemberValue(member: MemberExpression, value: string, context: EmitContext, expected: ResolvedType | none = none): string {
  if member.resolvedMember == none || member.resolvedCallableField || member.optional || member.force { return value }
  selected := member.resolvedMember!
  if selected.field { return value }
  // A union receiver's arms each declare the method, so no single declaration
  // is selected; it is still an instance method when every arm agrees.
  if selected.function_ == none && !(selected.instance && variantReceiver(member, context)) { return value }
  signature := referenceSignature(member.resolvedType, expected, context)
  if signature == none { return value }
  callbackType := emitContextType(signature!, context)
  let method = cppIdentifier(member.property)
  let staticValue = value
  if member.resolvedGenericReference != none {
    method = concreteReferenceName(member, member.resolvedGenericReference!, context)
    staticValue = value.substring(0, value.length - cppIdentifier(member.property).length) + method
  }
  if !selected.instance { return callbackType + "(" + staticValue + ")" }
  if member.object.resolvedType == none { return value }
  receiverType := specializeEmitType(member.object.resolvedType!, context)
  if !canBindMethod(receiverType, context) { return value }
  // The receiver is evaluated once, when the reference is taken.
  return boundMethod(callbackType, signature!, emitExpression(member.object, context), receiverType, method, context)
}

/**
 * A bound-method callback over an already-evaluated strong receiver, for
 * lowerings that obtain the receiver themselves (weak access). None when the
 * member is not an instance method used as a value.
 */
export function emitBoundMethodValue(member: MemberExpression, receiver: string, receiverType: ResolvedType, context: EmitContext): string | none {
  if member.resolvedMember == none || member.resolvedCallableField { return none }
  selected := member.resolvedMember!
  if selected.field || !selected.instance { return none }
  specialized := specializeEmitType(receiverType, context)
  if selected.function_ == none && !usesVariantRepresentation(specialized) { return none }
  referenceType := if member.resolvedOptionalValue != none then member.resolvedOptionalValue else member.resolvedType
  signature := referenceSignature(referenceType, none, context)
  if signature == none { return none }
  if !canBindMethod(specialized, context) { return none }
  method := if member.resolvedGenericReference == none then cppIdentifier(member.property) else concreteReferenceName(member, member.resolvedGenericReference!, context)
  return boundMethod(emitContextType(signature!, context), signature!, receiver, specialized, method, context)
}

function variantReceiver(member: MemberExpression, context: EmitContext): bool {
  if member.object.resolvedType == none { return false }
  return usesVariantRepresentation(specializeEmitType(member.object.resolvedType!, context))
}

function canBindMethod(receiverType: ResolvedType, context: EmitContext): bool {
  if implementationlessInterface(receiverType, context) != none { return false }
  if usesVariantRepresentation(receiverType) { return true }
  case receiverType {
    class_: ClassType -> { return !class_.symbol.native_ }
    _ -> { return false }
  }
  return false
}

function boundMethod(callbackType: string, signature: FunctionType, receiver: string, receiverType: ResolvedType, method: string, context: EmitContext): string {
  returnType := emitContextReturnType(signature.returnType, context)
  if usesVariantRepresentation(receiverType) {
    return boundCallback(callbackType, receiver, returnType, "std::visit([&](auto&& _obj) -> " + returnType + " { return _obj->" + method + "(" + forwardedArguments + "); }, " + variantVisitValue("_self", receiverType) + ")", false)
  }
  let structReceiver = false
  case receiverType {
    class_: ClassType -> { structReceiver = class_.symbol.kind == "struct" }
    _ -> { }
  }
  return boundCallback(callbackType, receiver, returnType, "_self" + (if structReceiver then "." else "->") + method + "(" + forwardedArguments + ")", structReceiver)
}

// Struct methods are not `const` in C++, so a captured struct receiver needs a
// `mutable` lambda; Doof still forbids the methods from changing it.
function boundCallback(callbackType: string, receiver: string, returnType: string, invocation: string, structReceiver: bool): string {
  return callbackType + "([_self = " + receiver + "](auto&&... _args) " + (if structReceiver then "mutable " else "") + "-> " + returnType + " { return " + invocation + "; })"
}

// The callback takes the expected function type when there is one, so the value
// needs no further callback-to-callback conversion.
function referenceSignature(type_: ResolvedType | none, expected: ResolvedType | none, context: EmitContext): FunctionType | none {
  if type_ == none { return none }
  if expected != none {
    case specializeEmitType(expected!, context) {
      target: FunctionType -> { if target.typeParams.length == 0 { return target } }
      _ -> { }
    }
  }
  case specializeEmitType(type_!, context) {
    function_: FunctionType -> { return if function_.typeParams.length > 0 then none else function_ }
    _ -> { return none }
  }
}

function concreteReferenceName(reference: Expression, generic: GenericReference, context: EmitContext): string {
  let concreteArgs: ResolvedType[] = []
  for argument of generic.typeArgs { concreteArgs.push(specializeEmitType(argument, context)) }
  target := concreteGenericTarget(reference, generic.function_, generic.modulePath, concreteArgs, context)
  if target == none {
    panic("Missing concrete generic instantiation for reference to " + generic.modulePath + "::" + generic.function_.name +
      " at line " + string(reference.span.start.line) + ":" + string(reference.span.start.column))
  }
  return target!.name
}
