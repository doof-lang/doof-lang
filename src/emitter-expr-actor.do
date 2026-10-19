// Actor, Promise, async-call, and retirement lowering.

import { emitActorConstruction } from "./emitter-construction"

import { ActorCreationExpression, AsyncExpression, Block, CallExpression, Expression, MemberExpression, RetireExpression } from "./ast"
import { ActorType, FunctionType, PromiseType, ResolvedType } from "./semantic"
import { EmitContext, HoistedOperand, SourceLocationSpanOverride } from "./emitter-context"
import { emitExpression, emitDiscardedExpression } from "./emitter-expr"
import { cppIdentifier } from "./emitter-names"
import { emitValueYieldBlock } from "./emitter-expr-control"
import { emitClassInnerType, emitContextReturnType } from "./emitter-types"

export function emitActorCreation(expression: ActorCreationExpression, context: EmitContext): string {
  return emitActorConstruction(expression, context)
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

// Operands are evaluated in the caller's domain before the call is queued.
// The lowered call itself is unchanged; emitExpression substitutes each
// operand with the caller-side temporary that holds its value.
function emitIsolatedFunctionCall(expression: AsyncExpression, call: CallExpression, context: EmitContext): string {
  if expression.resolvedType == none { panic("Async call is missing its resolved Promise type") }
  let valueType: ResolvedType | none = none
  case expression.resolvedType! {
    promise: PromiseType -> { valueType = promise.valueType }
    _ -> { panic("Async call does not have Promise<T> type") }
  }
  if valueType == none { return "" }
  cppReturn := emitContextReturnType(valueType!, context)
  let operands: HoistedOperand[] = []
  case call.callee {
    member: MemberExpression -> {
      if member.resolvedStaticOwner == none { operands.push(HoistedOperand { span: member.object.span, kind: member.object.kind }) }
    }
    _ -> { }
  }
  for argument of call.args { operands.push(HoistedOperand { span: argument.value.span, kind: argument.value.kind }) }
  previous := context.hoistedOperands
  context.hoistedOperands = operands
  let job = ""
  if cppReturn == "void" {
    job = "doof::submit_async<void>([=]() { " + emitDiscardedExpression(call, context) + "; })"
  } else {
    job = "doof::submit_async<" + cppReturn + ">([=]() -> " + cppReturn + " { return " + emitExpression(call, context) + "; })"
  }
  context.hoistedOperands = previous
  let prelude = ""
  for i of 0..<operands.length {
    operand := operands[i]
    if operand.temporary == "" {
      // A receiver the call lowering does not emit as a value (such as a
      // struct `this`) has nothing to hoist; every argument must be emitted.
      if i == 0 && operands.length > call.args.length { continue }
      panic("Async call argument was not lowered through its caller-side temporary")
    }
    prelude = prelude + "auto " + operand.temporary + " = " + operand.initializer + "; "
  }
  if prelude == "" { return job }
  return "[&]() { " + prelude + "return " + job + "; }()"
}

/** The caller-side temporary for `expression` when it is a hoisted operand. */
export function emitHoistedOperand(expression: Expression, context: EmitContext, expected: ResolvedType | none): string | none {
  for operand of context.hoistedOperands {
    if operand.kind != expression.kind || operand.span.start.offset != expression.span.start.offset || operand.span.end.offset != expression.span.end.offset { continue }
    if operand.temporary != "" { return operand.temporary }
    // Nested expressions, including checker wrappers sharing this span, lower
    // normally inside the initializer.
    previous := context.hoistedOperands
    context.hoistedOperands = []
    operand.initializer = emitExpression(expression, context, expected)
    context.hoistedOperands = previous
    operand.temporary = context.temporary("_async_arg_")
    return operand.temporary
  }
  return none
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
  body := emitValueYieldBlock(block, 1, valueType, cppReturn == "void", context)
  return "doof::submit_async<" + cppReturn + ">([" + captures + "]() -> " + cppReturn + " {\n" + body + "})"
}

export function emitRetireActor(expression: RetireExpression, context: EmitContext): string {
  return emitExpression(expression.actor, context) + "->retire()"
}

export function emitSyncActorCall(expression: CallExpression, member: MemberExpression, actor: ActorType, context: EmitContext): string {
  return emitActorMethodCall(expression, member, actor, false, context)
}

// The receiver and arguments are evaluated in the caller's domain, in source
// order, before the message is queued. Omitted parameters take their defaults
// inside the message, as they would in a local call on the actor's state.
function emitActorMethodCall(expression: CallExpression, member: MemberExpression, actor: ActorType, async_: bool, context: EmitContext): string {
  className := emitClassInnerType(actor.innerClass, context.modulePath, context.names)
  let methodType: FunctionType | none = none
  if member.resolvedType != none {
    case member.resolvedType! {
      function_: FunctionType -> { methodType = function_ }
      _ -> { }
    }
  }
  returnType := expression.resolvedType
  if returnType == none { panic("Actor method call is missing its resolved return type") }
  // Actor calls may return compound types containing reached generic nominals.
  // Lower those through the whole-program concrete-type registry just like
  // declarations do, or the lambda signature can reintroduce C++ templates.
  cppReturn := emitContextReturnType(returnType!, context)
  callName := if async_ then "call_async" else "call_sync"
  let object = emitExpression(member.object, context)
  let prelude = ""
  if expression.args.length > 0 {
    receiver := context.temporary("_actor_")
    prelude = "auto " + receiver + " = " + object + "; "
    object = receiver
  }
  let temporaries: string[] = []
  for i of 0..<expression.args.length {
    temporary := context.temporary("_actor_arg_")
    value := emitExpression(expression.args[i].value, context, actorArgumentType(expression, methodType, i))
    prelude = prelude + "auto " + temporary + " = " + value + "; "
    temporaries.push(temporary)
  }
  args := emitActorMethodArguments(expression, methodType, temporaries, context)
  // The message owns its operands: a queued message may outlive the caller's
  // frame, for example when the caller's wait panics or unwinds.
  let capture = "[]"
  if args != "" {
    capture = "[="
    for temporary of temporaries { capture = capture + ", " + temporary + " = std::move(" + temporary + ")" }
    capture = capture + "]"
  }
  let lambda = capture + "(" + className + "& _self)"
  if cppReturn == "void" {
    lambda = lambda + " { _self." + cppIdentifier(member.property) + "(" + args + "); }"
  } else {
    lambda = lambda + " -> " + cppReturn + " { return _self." + cppIdentifier(member.property) + "(" + args + "); }"
  }
  dispatch := object + "->template " + callName + "<" + cppReturn + ">(" + lambda + ")"
  if prelude == "" { return dispatch }
  return "[&]() { " + prelude + "return " + dispatch + "; }()"
}

function actorParameterIndex(expression: CallExpression, argumentIndex: int): int {
  name := expression.args[argumentIndex].name
  if name == none || expression.resolvedFunction == none { return argumentIndex }
  parameters := expression.resolvedFunction!.params
  for i of 0..<parameters.length { if parameters[i].name == name! { return i } }
  return argumentIndex
}

function actorArgumentType(expression: CallExpression, methodType: FunctionType | none, argumentIndex: int): ResolvedType | none {
  index := actorParameterIndex(expression, argumentIndex)
  if methodType != none && index < methodType!.params.length { return methodType!.params[index].type_ }
  if expression.resolvedFunction != none && index < expression.resolvedFunction!.params.length {
    return expression.resolvedFunction!.params[index].resolvedType
  }
  return none
}

/** Message-side argument list over the caller-side argument temporaries. */
function emitActorMethodArguments(expression: CallExpression, methodType: FunctionType | none, temporaries: string[], context: EmitContext): string {
  let result = ""
  if expression.resolvedFunction != none {
    declaration := expression.resolvedFunction!
    for i of 0..<declaration.params.length {
      parameter := declaration.params[i]
      let argumentIndex = expression.args.length
      for candidateIndex of 0..<expression.args.length {
        if actorParameterIndex(expression, candidateIndex) == i { argumentIndex = candidateIndex }
      }
      if argumentIndex < expression.args.length {
        if result != "" { result = result + ", " }
        result = result + temporaries[argumentIndex]
      } else if parameter.defaultValue != none {
        let expected: ResolvedType | none = parameter.resolvedType
        if methodType != none && i < methodType!.params.length { expected = methodType!.params[i].type_ }
        if result != "" { result = result + ", " }
        previous := context.sourceLocationSpanOverride
        context.sourceLocationSpanOverride = SourceLocationSpanOverride { span: expression.span }
        result = result + emitExpression(parameter.defaultValue!, context, expected)
        context.sourceLocationSpanOverride = previous
      }
    }
    return result
  }
  for temporary of temporaries {
    if result != "" { result = result + ", " }
    result = result + temporary
  }
  return result
}
