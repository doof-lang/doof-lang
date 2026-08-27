// Actor, Promise, async-call, and retirement lowering.

import { ActorCreationExpression, AsyncExpression, Block, CallExpression, ClassDeclaration, ExportDeclaration, Expression, FunctionDeclaration, MemberExpression, RetireExpression, Statement } from "./ast"
import { ActorType, FunctionType, PromiseType, ResolvedType, NoneType } from "./semantic"
import { EmitContext, SourceLocationSpanOverride } from "./emitter-context"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitBlock } from "./emitter-stmt"
import { emitClassInnerType, emitContextReturnType } from "./emitter-types"

export function emitActorCreation(expression: ActorCreationExpression, context: EmitContext): string {
  if expression.resolvedType == none { panic("Actor creation is missing its resolved type") }
  case expression.resolvedType! {
    actor: ActorType -> {
      className := emitClassInnerType(actor.innerClass, context.modulePath)
      if expression.resolvedConstructor != none {
        factory := emitActorConstructorFactory(className, expression.resolvedConstructor!, expression, context)
        return "std::make_shared<doof::Actor<" + className + ">>(" + factory + ")"
      }
      let args = ""
      declaration := actorClassDeclaration(actor.innerClass.symbol.module, actor.innerClass.symbol.name, context)
      if declaration == none { panic("Actor construction is missing class declaration " + actor.innerClass.name) }
      let argumentIndex = 0
      for field of declaration!.fields {
        if field.static_ || field.const_ { continue }
        for name of field.names {
          if args != "" { args = args + ", " }
          if argumentIndex < expression.args.length {
            args = args + emitExpression(expression.args[argumentIndex], context, field.resolvedType)
          } else {
            if field.defaultValue == none { panic("Actor constructor is missing argument " + name) }
            previous := context.sourceLocationSpanOverride
            context.sourceLocationSpanOverride = SourceLocationSpanOverride { span: expression.span }
            args = args + emitExpression(field.defaultValue!, context, field.resolvedType)
            context.sourceLocationSpanOverride = previous
          }
          argumentIndex = argumentIndex + 1
        }
      }
      return "std::make_shared<doof::Actor<" + className + ">>(" + className + "{" + args + "})"
    }
    _ -> { panic("Actor creation does not have Actor<T> type") }
  }
  return ""
}

function actorClassDeclaration(modulePath: string, name: string, context: EmitContext): ClassDeclaration | none {
  for program of context.allPrograms {
    for statement of program.statements {
      declaration := actorClassFromStatement(statement)
      if declaration != none && declaration!.name == name && declaration!.resolvedSymbol != none && declaration!.resolvedSymbol!.module == modulePath { return declaration }
    }
  }
  return none
}

function actorClassFromStatement(statement: Statement): ClassDeclaration | none {
  case statement {
    class_: ClassDeclaration -> { return class_ }
    export_: ExportDeclaration -> {
      case export_.declaration {
        class_: ClassDeclaration -> { return class_ }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}

function emitActorConstructorFactory(className: string, constructor: FunctionDeclaration, expression: ActorCreationExpression, context: EmitContext): string {
  let result = className + "::constructor("
  for i of 0..<constructor.params.length {
    if i > 0 { result = result + ", " }
    parameter := constructor.params[i]
    if i < expression.args.length { result = result + emitExpression(expression.args[i], context, parameter.resolvedType) }
    else {
      if parameter.defaultValue == none { panic("Actor constructor is missing argument " + parameter.name) }
      previous := context.sourceLocationSpanOverride
      context.sourceLocationSpanOverride = SourceLocationSpanOverride { span: expression.span }
      result = result + emitExpression(parameter.defaultValue!, context, parameter.resolvedType)
      context.sourceLocationSpanOverride = previous
    }
  }
  return result + ")"
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
  args := emitActorMethodArguments(expression, methodType, context)
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

function emitActorMethodArguments(expression: CallExpression, methodType: FunctionType | none, context: EmitContext): string {
  let result = ""
  let named = false
  for argument of expression.args { if argument.name != none { named = true } }
  if expression.resolvedFunction != none {
    declaration := expression.resolvedFunction!
    for i of 0..<declaration.params.length {
      parameter := declaration.params[i]
      let argumentIndex = i
      if named {
        argumentIndex = expression.args.length
        for candidateIndex of 0..<expression.args.length {
          if expression.args[candidateIndex].name == parameter.name { argumentIndex = candidateIndex }
        }
      }
      let expected: ResolvedType | none = parameter.resolvedType
      if methodType != none && i < methodType!.params.length { expected = methodType!.params[i].type_ }
      if argumentIndex < expression.args.length {
        if result != "" { result = result + ", " }
        result = result + emitExpression(expression.args[argumentIndex].value, context, expected)
      } else if parameter.defaultValue != none {
        if result != "" { result = result + ", " }
        previous := context.sourceLocationSpanOverride
        context.sourceLocationSpanOverride = SourceLocationSpanOverride { span: expression.span }
        result = result + emitExpression(parameter.defaultValue!, context, expected)
        context.sourceLocationSpanOverride = previous
      }
    }
    return result
  }
  for i of 0..<expression.args.length {
    if i > 0 { result = result + ", " }
    let expected: ResolvedType | none = none
    if methodType != none && i < methodType!.params.length { expected = methodType!.params[i].type_ }
    result = result + emitExpression(expression.args[i].value, context, expected)
  }
  return result
}
