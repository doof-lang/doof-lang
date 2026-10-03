// Lowering of built-in array member calls onto doof_runtime.hpp helpers.
//
// Callback arguments are emitted against the checked member signature, after
// generic substitution, so each lambda's C++ signature carries the parameters
// and return type the checker accepted. The runtime passes `index` only to
// callbacks whose arity includes it.
import { CallExpression, Expression, MemberExpression } from "./ast"
import { ArrayResolvedType, FunctionType, ResolvedType } from "./semantic"
import { substituteTypeParams } from "./checker-types"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { emitCarrierAbsence, emitCarrierConversion } from "./emitter-carrier-values"
import { emitContextType, specializeEmitType } from "./emitter-types"

/** Returns none for members without an array-specific lowering. */
export function emitArrayMethodCall(member: MemberExpression, expression: CallExpression, array: ArrayResolvedType, context: EmitContext): string | none {
  property := member.property
  if property == "takeFirstCompleted" { return "doof::promise_take_first_completed(" + emitExpression(member.object, context) + ")" }
  if property == "buildReadonly" || property == "drainToReadonly" { return runtimeCall("array_drainToReadonly", member, expression, context) }
  if property == "cloneReadonly" { return runtimeCall("array_cloneReadonly", member, expression, context) }
  if property == "cloneMutable" { return runtimeCall("array_cloneMutable", member, expression, context) }
  if property == "contains" || property == "indexOf" || property == "some" || property == "every" || property == "filter" || property == "map" || property == "forEach" || property == "sort" {
    return runtimeCall("array_" + property, member, expression, context)
  }
  if property == "reduce" || property == "reduceRight" { return runtimeCall("array_" + property, member, expression, context) }
  if property == "find" { return emitArrayFind(member, expression, array, context) }
  return none
}

function runtimeCall(helper: string, member: MemberExpression, expression: CallExpression, context: EmitContext): string {
  signature := checkedSignature(member, expression, context)
  let result = "doof::" + helper + "(" + emitExpression(member.object, context)
  for i of 0..<expression.args.length {
    let expected: ResolvedType | none = none
    if signature != none && i < signature!.params.length { expected = signature!.params[i].type_ }
    result = result + ", " + emitArgument(expression.args[i].value, expected, context)
  }
  return result + ", \"\", 0)"
}

// `find` yields the element in the checked `T | none` carrier, whose absence
// spelling depends on T, so the runtime reports only the matching index.
function emitArrayFind(member: MemberExpression, expression: CallExpression, array: ArrayResolvedType, context: EmitContext): string {
  signature := checkedSignature(member, expression, context)
  resultType := expression.resolvedType ?? signature!.returnType
  context.tryCounter = context.tryCounter + 1
  suffix := string(context.tryCounter)
  items := "_find_items_" + suffix
  index := "_find_index_" + suffix
  predicate := emitArgument(expression.args[0].value, signature!.params[0].type_, context)
  return "[&]() -> " + emitContextType(resultType, context) + " { auto " + items + " = " + emitExpression(member.object, context)
    + "; const int32_t " + index + " = doof::array_find_index(" + items + ", " + predicate + ", \"\", 0); if (" + index + " < 0) { return "
    + emitCarrierAbsence(resultType, context) + "; } return " + emitCarrierConversion("(*" + items + ")[static_cast<size_t>(" + index + ")]", array.elementType, resultType, context)
    + "; }()"
}

// Named functions and lambdas both lower to the callback carrier the runtime
// invokes (see emitter-function-refs).
function emitArgument(value: Expression, expected: ResolvedType | none, context: EmitContext): string {
  return emitExpression(value, context, expected)
}

function checkedSignature(member: MemberExpression, expression: CallExpression, context: EmitContext): FunctionType | none {
  if member.resolvedType == none { return none }
  case member.resolvedType! {
    signature: FunctionType -> {
      if expression.resolvedGenericTypeArgs.length == 0 { return signature }
      let concrete: ResolvedType[] = []
      for argument of expression.resolvedGenericTypeArgs { concrete.push(specializeEmitType(argument, context)) }
      case substituteTypeParams(signature, signature.typeParams, concrete) {
        specialized: FunctionType -> { return specialized }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}
