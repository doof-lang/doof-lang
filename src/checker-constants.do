// Compile-time evaluation of constant int expressions.

import { BinaryExpression, Expression, IntLiteral, UnaryExpression } from "./ast"

/** Evaluates literal int arithmetic; none when not constant or outside the int range. */
export function constantInt(expression: Expression): long | none {
  case expression {
    literal: IntLiteral -> { return long(literal.value) }
    unary: UnaryExpression -> {
      if !unary.prefix || (unary.operator != "+" && unary.operator != "-") { return none }
      operand := constantInt(unary.operand)
      if operand == none { return none }
      result := if unary.operator == "-" then -operand! else operand!
      if result < -2147483648L || result > 2147483647L { return none }
      return result
    }
    binary: BinaryExpression -> {
      left := constantInt(binary.left)
      right := constantInt(binary.right)
      if left == none || right == none { return none }
      let result = 0L
      if binary.operator == "+" { result = left! + right! }
      else if binary.operator == "-" { result = left! - right! }
      else if binary.operator == "*" { result = left! * right! }
      else if binary.operator == "\\" {
        if right! == 0L { return none }
        result = left! \ right!
      } else if binary.operator == "%" {
        if right! == 0L { return none }
        result = left! % right!
      } else { return none }
      if result < -2147483648L || result > 2147483647L { return none }
      return result
    }
    _ -> { return none }
  }
  return none
}
