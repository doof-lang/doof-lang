// Function and method references used as values.
//
// Doof function values lower to `doof::callback<R(Args...)>`. A bare C++
// function name, static member function, or member access does not deduce to
// that type (and `obj->method` is not a C++ value at all), so references that
// are not immediately called are wrapped here. Calls emit their callee through
// `emitCalleeExpression`, which keeps the direct C++ call form.

import { Expression, Identifier, MemberExpression } from "./ast"
import { ClassType, FunctionType, ResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { emitIdentifier, emitMember } from "./emitter-expr-ops"
import { cppIdentifier } from "./emitter-names"
import { variantVisitValue } from "./emitter-expr-utils"
import { emitContextReturnType, emitContextType, specializeEmitType, usesVariantRepresentation } from "./emitter-types"
import { implementationlessInterface } from "./emitter-no-implementations"

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
export function emitIdentifierValue(identifier: Identifier, value: string, context: EmitContext, expected: ResolvedType | none = none): string {
  if identifier.resolvedBinding == none { return value }
  binding := identifier.resolvedBinding!
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
  if selected.function_ == none || selected.field { return value }
  signature := referenceSignature(member.resolvedType, expected, context)
  if signature == none { return value }
  callbackType := emitContextType(signature!, context)
  if !selected.instance { return callbackType + "(" + value + ")" }
  if member.object.resolvedType == none { return value }
  receiverType := specializeEmitType(member.object.resolvedType!, context)
  if implementationlessInterface(receiverType, context) != none { return value }
  returnType := emitContextReturnType(signature!.returnType, context)
  method := cppIdentifier(member.property)
  let invocation = ""
  let structReceiver = false
  if usesVariantRepresentation(receiverType) {
    invocation = "std::visit([&](auto&& _obj) -> " + returnType + " { return _obj->" + method + "(" + forwardedArguments + "); }, " + variantVisitValue("_self", receiverType) + ")"
  } else {
    case receiverType {
      class_: ClassType -> {
        if class_.symbol.native_ { return value }
        structReceiver = class_.symbol.kind == "struct"
        invocation = "_self" + (if structReceiver then "." else "->") + method + "(" + forwardedArguments + ")"
      }
      _ -> { return value }
    }
  }
  // The receiver is evaluated once, when the reference is taken.
  return boundCallback(callbackType, emitExpression(member.object, context), returnType, invocation, structReceiver)
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
