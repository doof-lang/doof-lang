// Optional chaining ('?.' and '?[]') over nullable receivers.
//
// The checker lowers a Result receiver through postfix '?', records the receiver
// with its none arm removed, and records the value before it is widened with
// none. Lowering evaluates the receiver once, returns early when it is absent,
// and otherwise emits the ordinary access through a synthetic receiver of the
// unwrapped type, so field, method, variant, struct, and builtin access paths
// are shared with plain member and index expressions. A Result-valued access
// keeps its Failure and receives the none in its success channel.

import { CallExpression, Expression, Identifier, IndexExpression, MemberExpression, SourceSpan } from "./ast"
import { ResolvedType, ResultResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { emitCarrierConversion } from "./emitter-carrier-values"
import { emitNoneLiteral } from "./emitter-expr-literals"
import { requireExpressionType } from "./emitter-expr-utils"
import { emitContextType, emitResultPayloadType } from "./emitter-types"
import { cppIdentifier } from "./emitter-names"

export function emitOptionalMember(expression: MemberExpression, context: EmitContext): string {
  valueType := expression.resolvedOptionalValue!
  return lowerOptional(expression.object, expression.resolvedOptionalReceiver!, valueType, requireExpressionType(expression, "optional member access"), expression.span, context,
    (receiver: Expression): Expression => unwrappedMember(expression, receiver, valueType))
}

export function emitOptionalCall(expression: CallExpression, member: MemberExpression, context: EmitContext): string {
  valueType := expression.resolvedOptionalValue!
  return lowerOptional(member.object, member.resolvedOptionalReceiver!, valueType, requireExpressionType(expression, "optional method call"), expression.span, context, (receiver: Expression): Expression => {
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
  return lowerOptional(expression.object, expression.resolvedOptionalReceiver!, valueType, requireExpressionType(expression, "optional index"), expression.span, context, (receiver: Expression): Expression => {
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

// The checker lowers a Result receiver through postfix `?`, so the receiver
// here is always nullable.
function lowerOptional(
  object: Expression,
  receiverType: ResolvedType,
  valueType: ResolvedType,
  resultType: ResolvedType,
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
  unwrap := "auto&& " + cppIdentifier(receiverName) + " = doof::unwrap_optional(" + sourceName + "); "
  if resultType.kind == "none" {
    return "[&]() -> void { " + prefix + "if (doof::is_null(" + sourceName + ")) return; " + unwrap + inner + "; }()"
  }
  return "[&]() -> " + emitContextType(resultType, context) + " { " + prefix + "if (doof::is_null(" + sourceName + ")) return " + emitOptionalAbsent(resultType, context) + "; " + unwrap + "return " + emitOptionalPresent(inner, valueType, resultType, suffix, context) + "; }()"
}

/** The value of an optional access whose receiver is absent. */
export function emitOptionalAbsent(resultType: ResolvedType, context: EmitContext): string {
  case resultType {
    out: ResultResolvedType -> { return successOf(emitNoneLiteral(out.valueType, context), out, context) }
    _ -> { }
  }
  return emitNoneLiteral(resultType, context)
}

/**
 * Widens a present access value to the optional access type. A Result value
 * keeps its Failure and widens its success value with none.
 */
export function emitOptionalPresent(inner: string, valueType: ResolvedType, resultType: ResolvedType, suffix: string, context: EmitContext): string {
  case resultType {
    out: ResultResolvedType -> {
      case valueType {
        nested: ResultResolvedType -> {
          nestedName := "_optional_result_" + suffix
          let body = "auto&& " + nestedName + " = " + inner + "; "
          body = body + "if (doof::is_failure(" + nestedName + ")) return " + failureOf(nestedName, out, context) + "; "
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
    _ -> { }
  }
  return emitCarrierConversion(inner, valueType, resultType, context)
}

function successOf(value: string, out: ResultResolvedType, context: EmitContext): string {
  payload := emitResultPayloadType(out.valueType, context.modulePath, context.names)
  if payload == "void" { return "doof::Success<void>{}" }
  return "doof::Success<" + payload + ">{" + value + "}"
}

function failureOf(sourceName: string, out: ResultResolvedType, context: EmitContext): string {
  errorCpp := emitResultPayloadType(out.errorType, context.modulePath, context.names)
  if errorCpp == "void" { return "doof::Failure<void>{}" }
  return "doof::Failure<" + errorCpp + ">{doof::failure_error(" + sourceName + ")}"
}
