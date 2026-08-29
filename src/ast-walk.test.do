import { Assert } from "std/assert"
import { parse } from "./parser"
import { Block, CallExpression, Expression, FunctionDeclaration } from "./ast"
import { collectBlockExpressions, collectNestedExpressions } from "./ast-walk"

export function testWalksNestedStatementAndExpressionTrees(): none {
  program := parse("function main(): none { if ready() { println(format(\"ok\")) } }")
  let expressions: Expression[] = []
  case program.statements[0] {
    fn: FunctionDeclaration -> { case fn.body {
      block: Block -> { collectBlockExpressions(block, expressions) }
      _ -> { panic("expected function block") }
    } }
    _ -> { panic("expected function") }
  }

  let cursor = 0
  let calls = 0
  while cursor < expressions.length {
    expression := expressions[cursor]
    cursor = cursor + 1
    case expression { _: CallExpression -> { calls = calls + 1 } _ -> { } }
    collectNestedExpressions(expression, expressions)
  }
  Assert.equal(calls, 3)
}
