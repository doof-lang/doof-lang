// Actor, Promise, async-call, and retirement lowering.

import { ActorCreationExpression, AsyncExpression, Block, CallExpression, Expression, MemberExpression, RetireExpression } from "./ast"
import { ActorType, FunctionType, PromiseType, ResolvedType, NoneType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitBlock } from "./emitter-stmt"
import { emitClassInnerType, emitContextReturnType } from "./emitter-types"

export function emitActorCreation(expression: ActorCreationExpression, context: EmitContext): string {
  if expression.resolvedType == none { panic("Actor creation is missing its resolved type") }
  case expression.resolvedType! {
    actor: ActorType -> {
      let args = ""
      for i of 0..<expression.args.length {
        if i > 0 { args = args + ", " }
        args = args + emitExpression(expression.args[i], context)
      }
      className := emitClassInnerType(actor.innerClass, context.modulePath)
      return "std::make_shared<doof::Actor<" + className + ">>(" + className + "{" + args + "})"
    }
    _ -> { panic("Actor creation does not have Actor<T> type") }
  }
  return ""
}

export function emitAsyncExpression(expression: AsyncExpression, context: EmitContext): string {
  case expression.expression {
    block: Block -> { return emitAsyncBlock(expression, block, context) }
    inner: Expression -> {
      case inner {
        call: CallExpression -> {
          case call.callee {
            member: MemberExpression -> {
              if member.object.resolvedType != none {
                case member.object.resolvedType! {
                  actor: ActorType -> { return emitActorMethodCall(call, member, actor, true, context) }
                  _ -> { }
                }
              }
            }
            _ -> { }
          }
          if call.resolvedFunction != none { return emitIsolatedFunctionCall(expression, call, context) }
        }
        _ -> { }
      }
    }
  }
  panic("Cannot emit async expression without an actor method or isolated function call")
  return ""
}

function emitIsolatedFunctionCall(expression: AsyncExpression, call: CallExpression, context: EmitContext): string {
  if expression.resolvedType == none { panic("Async call is missing its resolved Promise type") }
  let valueType: ResolvedType | none = none
  case expression.resolvedType! {
    promise: PromiseType -> { valueType = promise.valueType }
    _ -> { panic("Async call does not have Promise<T> type") }
  }
  if valueType == none { return "" }
  cppReturn := emitContextReturnType(valueType!, context)
  invocation := emitExpression(call, context)
  if cppReturn == "void" {
    return "doof::submit_async<void>([=]() { " + invocation + "; })"
  }
  return "doof::submit_async<" + cppReturn + ">([=]() -> " + cppReturn + " { return " + invocation + "; })"
}

function emitAsyncBlock(expression: AsyncExpression, block: Block, context: EmitContext): string {
  if expression.resolvedType == none { panic("Async block is missing its resolved Promise type") }
  let valueType: ResolvedType | none = none
  case expression.resolvedType! {
    promise: PromiseType -> { valueType = promise.valueType }
    _ -> { panic("Async block does not have Promise<T> type") }
  }
  if valueType == none { return "" }
  cppReturn := emitContextReturnType(valueType!, context)
  let captures = ""
  for i of 0..<expression.resolvedCaptureNames.length {
    if i > 0 { captures = captures + ", " }
    captures = captures + cppIdentifier(expression.resolvedCaptureNames[i])
  }
  previousYieldState := context.inValueYieldBlock
  previousVoidState := context.valueYieldReturnsVoid
  context.inValueYieldBlock = true
  context.valueYieldReturnsVoid = cppReturn == "void"
  body := emitBlock(block, 1, context)
  context.inValueYieldBlock = previousYieldState
  context.valueYieldReturnsVoid = previousVoidState
  return "doof::submit_async<" + cppReturn + ">([" + captures + "]() -> " + cppReturn + " {\n" + body + "})"
}

export function emitRetireActor(expression: RetireExpression, context: EmitContext): string {
  return emitExpression(expression.actor, context) + "->retire()"
}

export function emitSyncActorCall(expression: CallExpression, member: MemberExpression, actor: ActorType, context: EmitContext): string {
  return emitActorMethodCall(expression, member, actor, false, context)
}

function emitActorMethodCall(expression: CallExpression, member: MemberExpression, actor: ActorType, async_: bool, context: EmitContext): string {
  object := emitExpression(member.object, context)
  className := emitClassInnerType(actor.innerClass, context.modulePath)
  let methodType: FunctionType | none = none
  if member.resolvedType != none {
    case member.resolvedType! {
      function_: FunctionType -> { methodType = function_ }
      _ -> { }
    }
  }
  let args = ""
  for i of 0..<expression.args.length {
    if i > 0 { args = args + ", " }
    let expected: ResolvedType | none = none
    if methodType != none && i < methodType!.params.length { expected = methodType!.params[i].type_ }
    args = args + emitExpression(expression.args[i].value, context, expected)
  }
  returnType := expression.resolvedType
  if returnType == none { panic("Actor method call is missing its resolved return type") }
  // Actor calls may return compound types containing reached generic nominals.
  // Lower those through the whole-program concrete-type registry just like
  // declarations do, or the lambda signature can reintroduce C++ templates.
  cppReturn := emitContextReturnType(returnType!, context)
  callName := if async_ then "call_async" else "call_sync"
  capture := if args == "" then "[]" else if async_ then "[=]" else "[&]"
  let lambda = capture + "(" + className + "& _self)"
  if cppReturn == "void" {
    lambda = lambda + " { _self." + cppIdentifier(member.property) + "(" + args + "); }"
  } else {
    lambda = lambda + " -> " + cppReturn + " { return _self." + cppIdentifier(member.property) + "(" + args + "); }"
  }
  return object + "->template " + callName + "<" + cppReturn + ">(" + lambda + ")"
}
