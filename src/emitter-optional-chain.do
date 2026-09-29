// Optional chaining ('?.' and '?[]') over nullable and Result receivers.
//
// The checker records the receiver with its none arm removed and the value
// before it is widened with none. Lowering evaluates the receiver once, returns
// early when it is absent (or, for a Result receiver, when it is a Failure),
// and otherwise emits the ordinary access through a synthetic receiver of the
// unwrapped type, so field, method, variant, struct, and builtin access paths
// are shared with plain member and index expressions.

import { CallExpression, Expression, Identifier, IndexExpression, MemberExpression, SourceSpan } from "./ast"
import { ResolvedType, ResultResolvedType, UnionResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { emitCarrierConversion } from "./emitter-carrier-values"
import { emitNoneLiteral } from "./emitter-expr-literals"
import { requireExpressionType } from "./emitter-expr-utils"
import { emitContextType, emitResultPayloadType } from "./emitter-types"
import { cppIdentifier } from "./emitter-names"

export function emitOptionalMember(expression: MemberExpression, context: EmitContext): string {
  valueType := expression.resolvedOptionalValue!
  return lowerOptional(expression.object, expression.resolvedOptionalReceiver!, valueType, requireExpressionType(expression, "optional member access"), false, expression.span, context,
    (receiver: Expression): Expression => unwrappedMember(expression, receiver, valueType))
}

export function emitOptionalCall(expression: CallExpression, member: MemberExpression, context: EmitContext): string {
  valueType := expression.resolvedOptionalValue!
  return lowerOptional(member.object, member.resolvedOptionalReceiver!, valueType, requireExpressionType(expression, "optional method call"), true, expression.span, context, (receiver: Expression): Expression => {
    callee := unwrappedMember(member, receiver, requireExpressionType(member, "optional callee"))
    call := CallExpression { kind: expression.kind, callee, args: expression.args, typeArgs: expression.typeArgs, span: expression.span }
    call.resolvedConstruction = expression.resolvedConstruction
    call.resolvedGenericTypeArgs = expression.resolvedGenericTypeArgs
    call.resolvedFunction = expression.resolvedFunction
    call.resolvedFunctionModule = expression.resolvedFunctionModule
    call.resolvedConstructor = expression.resolvedConstructor
    call.resolvedClass = expression.resolvedClass
    call.resolvedType = valueType
    return call
  })
}

export function emitOptionalIndex(expression: IndexExpression, context: EmitContext): string {
  valueType := expression.resolvedOptionalValue!
  return lowerOptional(expression.object, expression.resolvedOptionalReceiver!, valueType, requireExpressionType(expression, "optional index"), false, expression.span, context, (receiver: Expression): Expression => {
    index := IndexExpression { kind: expression.kind, object: receiver, index: expression.index, optional: false, span: expression.span }
    index.resolvedType = valueType
    return index
  })
}

function unwrappedMember(member: MemberExpression, receiver: Expression, valueType: ResolvedType): MemberExpression {
  access := MemberExpression { kind: member.kind, object: receiver, property: member.property, optional: false, force: false, span: member.span }
  access.resolvedStaticOwner = member.resolvedStaticOwner
  access.resolvedMember = member.resolvedMember
  access.resolvedCallableField = member.resolvedCallableField
  access.resolvedType = valueType
  return access
}

// `flattensResult` is set for calls: over a Result receiver, a
// Result-returning method's channels are merged into the chain's Result.
function lowerOptional(
  object: Expression,
  receiverType: ResolvedType,
  valueType: ResolvedType,
  resultType: ResolvedType,
  flattensResult: bool,
  span: SourceSpan,
  context: EmitContext,
  access: (receiver: Expression): Expression,
): string {
  source := emitExpression(object, context)
  context.tryCounter = context.tryCounter + 1
  suffix := string(context.tryCounter)
  sourceName := "_optional_source_" + suffix
  receiverName := "_optional_receiver_" + suffix
  receiver := Identifier { kind: "identifier", name: receiverName, span }
  receiver.resolvedType = receiverType
  inner := emitExpression(access(receiver), context)
  // Bind by reference so an lvalue receiver is not copied; prvalues are
  // lifetime-extended for the duration of the access.
  prefix := "auto&& " + sourceName + " = " + source + "; "
  case requireExpressionType(object, "optional receiver") {
    chained: ResultResolvedType -> {
      case resultType {
        out: ResultResolvedType -> {
          return lowerResultReceiver(prefix, sourceName, cppIdentifier(receiverName), suffix, inner, chained, valueType, out, flattensResult, context)
        }
        _ -> { panic("Optional chaining over a Result must resolve to Result") }
      }
    }
    _ -> { }
  }
  unwrap := "auto&& " + cppIdentifier(receiverName) + " = doof::unwrap_optional(" + sourceName + "); "
  if resultType.kind == "none" {
    return "[&]() -> void { " + prefix + "if (doof::is_null(" + sourceName + ")) return; " + unwrap + inner + "; }()"
  }
  value := emitCarrierConversion(inner, valueType, resultType, context)
  return "[&]() -> " + emitContextType(resultType, context) + " { " + prefix + "if (doof::is_null(" + sourceName + ")) return " + emitNoneLiteral(resultType, context) + "; " + unwrap + "return " + value + "; }()"
}

function lowerResultReceiver(
  prefix: string,
  sourceName: string,
  receiverCpp: string,
  suffix: string,
  inner: string,
  receiverResult: ResultResolvedType,
  valueType: ResolvedType,
  out: ResultResolvedType,
  flattensResult: bool,
  context: EmitContext,
): string {
  successName := "_optional_success_" + suffix
  let body = prefix + "if (doof::is_failure(" + sourceName + ")) return " + failure(sourceName, receiverResult, out, context) + "; "
  body = body + "auto&& " + successName + " = doof::success_value(" + sourceName + "); "
  if allowsNone(receiverResult.valueType) {
    body = body + "if (doof::is_null(" + successName + ")) return " + successOf(emitNoneLiteral(out.valueType, context), out, context) + "; "
    body = body + "auto&& " + receiverCpp + " = doof::unwrap_optional(" + successName + "); "
  } else {
    body = body + "auto&& " + receiverCpp + " = " + successName + "; "
  }
  if flattensResult {
    case valueType {
      nested: ResultResolvedType -> {
        nestedName := "_optional_result_" + suffix
        body = body + "auto&& " + nestedName + " = " + inner + "; "
        body = body + "if (doof::is_failure(" + nestedName + ")) return " + failure(nestedName, nested, out, context) + "; "
        if nested.valueType.kind == "none" {
          body = body + "return " + successOf("", out, context) + ";"
        } else {
          body = body + "return " + successOf(emitCarrierConversion("doof::success_value(" + nestedName + ")", nested.valueType, out.valueType, context), out, context) + ";"
        }
        return "[&]() -> " + emitContextType(out, context) + " { " + body + " }()"
      }
      _ -> { }
    }
  }
  if valueType.kind == "none" {
    body = body + inner + "; return " + successOf("", out, context) + ";"
  } else {
    body = body + "return " + successOf(emitCarrierConversion(inner, valueType, out.valueType, context), out, context) + ";"
  }
  return "[&]() -> " + emitContextType(out, context) + " { " + body + " }()"
}

function successOf(value: string, out: ResultResolvedType, context: EmitContext): string {
  payload := emitResultPayloadType(out.valueType, context.modulePath, context.names)
  if payload == "void" { return "doof::Success<void>{}" }
  return "doof::Success<" + payload + ">{" + value + "}"
}

// Promotes a source Failure into the chain's (possibly wider) error channel.
function failure(sourceName: string, source: ResultResolvedType, out: ResultResolvedType, context: EmitContext): string {
  errorCpp := emitResultPayloadType(out.errorType, context.modulePath, context.names)
  if errorCpp == "void" { return "doof::Failure<void>{}" }
  if emitResultPayloadType(source.errorType, context.modulePath, context.names) == "void" {
    return "doof::Failure<" + errorCpp + ">{" + errorCpp + "{}}"
  }
  return "doof::Failure<" + errorCpp + ">{doof::variant_promote<" + errorCpp + ">(doof::failure_error(" + sourceName + "))}"
}

function allowsNone(type_: ResolvedType): bool {
  if type_.kind == "none" { return true }
  case type_ {
    union_: UnionResolvedType -> {
      for member of union_.types { if member.kind == "none" { return true } }
    }
    _ -> { }
  }
  return false
}
