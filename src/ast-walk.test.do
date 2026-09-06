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

import { collectExpressionTree } from "./ast-walk"

export function testSecondConsolidationPreorderTraversal(): none {
  program := parse("function main(): none => outer(inner())")
  let expressions: Expression[] = []
  case program.statements[0] {
    fn: FunctionDeclaration -> { case fn.body {
      expression: Expression -> { collectExpressionTree(expression, expressions) }
      _ -> { panic("expected expression") }
    } }
    _ -> { panic("expected function") }
  }
  Assert.equal(expressions.length, 4)
  case expressions[0] { _: CallExpression -> {} _ -> { panic("expected outer call first") } }
  case expressions[2] { _: CallExpression -> {} _ -> { panic("expected inner call after outer callee") } }
}
