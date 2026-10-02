// Absence rules shared by the `?` and `!` operator families and
// declaration-else.
//
// `none` and a `Failure` are both absent (see absence-types). Postfix `?`,
// `?.`, and `?[]` collapse absence to `none`; postfix `!` and `!.` panic on it;
// `??` and declaration-else replace it. None of them propagates a Failure.
//
// A receiver with a Result layer is lowered through a postfix `?` or `!` node,
// so member, index, and coalescing lowering only see nullable values.

import { Expression, UnaryExpression } from "./ast"
import { ResolvedType, ResultResolvedType } from "./semantic"
import { noneType, resultType, unionType } from "./checker-types"
import { finish } from "./checker-common"
import { CheckerState } from "./checker-state"
import { presentType } from "./absence-types"

/** Type of `x?`: the present value, or none. */
export function optionalType(type_: ResolvedType): ResolvedType {
  return unionType([presentType(type_), noneType()])
}

/**
 * Type of an optional access whose access value is `value`: a Result keeps its
 * own Failure and receives the none in its success channel.
 */
export function optionalAccessType(value: ResolvedType): ResolvedType {
  case value {
    result: ResultResolvedType -> { return resultType(unionType([result.valueType, noneType()]), result.errorType) }
    _ -> { }
  }
  return unionType([value, noneType()])
}

/** `operand?` over a checked operand whose present value exists. */
export function optionalConversion(state: CheckerState, operand: Expression, type_: ResolvedType): Expression {
  converted := UnaryExpression { kind: "optional-conversion", operator: "?", operand, prefix: false, span: operand.span }
  finish(state, converted, optionalType(type_))
  return converted
}

/** `operand!` over a checked operand whose present value exists. */
export function forcedValue(state: CheckerState, operand: Expression, type_: ResolvedType): Expression {
  forced := UnaryExpression { kind: "non-null-assertion", operator: "!", operand, prefix: false, span: operand.span }
  finish(state, forced, presentType(type_))
  return forced
}
