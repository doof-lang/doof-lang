import { Assert } from "std/assert"
import { parse } from "./parser"
import { Block, CallExpression, Expression, FunctionDeclaration, IfStatement, MemberExpression, TypeAliasDeclaration } from "./ast"
import { collectBlockExpressions, collectNestedExpressions, conditionClauses, hasBindingClause, releaseCheckedReferences } from "./ast-walk"

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

export function testReleasingCheckedReferencesClearsJsonAliases(): none {
  program := parse("type Shape = int\nfunction main(): none { Shape.fromSerialValue(1) }")
  case program.statements[1] {
    fn: FunctionDeclaration -> {
      case fn.body {
        block: Block -> {
          let expressions: Expression[] = []
          collectBlockExpressions(block, expressions)
          case program.statements[0] {
            alias: TypeAliasDeclaration -> {
              for expression of expressions {
                case expression { member: MemberExpression -> { member.resolvedJsonAlias = alias } _ -> { } }
              }
            }
            _ -> { panic("expected alias") }
          }
          releaseCheckedReferences(block.statements)
          for expression of expressions {
            case expression { member: MemberExpression -> { Assert.isTrue(member.resolvedJsonAlias == none) } _ -> { } }
          }
        }
        _ -> { panic("expected function block") }
      }
    }
    _ -> { panic("expected function") }
  }
}

import { ForOfStatement, Statement } from "./ast"

export function testStatementSinkRecordsNestedStatements(): none {
  program := parse("function main(): none { if ready() { for v of items() { } }\nf := (): none => { for w of more() { } } }")
  let expressions: Expression[] = []
  let statements: Statement[] = []
  case program.statements[0] {
    fn: FunctionDeclaration -> { case fn.body {
      block: Block -> { collectBlockExpressions(block, expressions, statements) }
      _ -> { panic("expected function block") }
    } }
    _ -> { panic("expected function") }
  }
  let nested: Expression[] = []
  for expression of expressions { collectExpressionTree(expression, nested, statements) }
  let loops = 0
  for statement of statements { case statement { _: ForOfStatement -> { loops += 1 } _ -> { } } }
  Assert.equal(loops, 2)
}

export function testConditionClausesSplitOnlyBindingAndChains(): none {
  program := parse("if ready && user := find() && user.ok { }\nif user := find() && (a && b) { }\nif a && b { }")
  first := program.statements[0] as IfStatement else { panic("expected if statement") }
  Assert.equal(conditionClauses(first.condition).length, 3)
  // A parenthesized `&&` without bindings stays one clause.
  second := program.statements[1] as IfStatement else { panic("expected if statement") }
  Assert.isTrue(hasBindingClause(second.condition))
  clauses := conditionClauses(second.condition)
  Assert.equal(clauses.length, 2)
  Assert.equal(clauses[0].kind, "binding-condition")
  Assert.equal(clauses[1].kind, "binary-expression")
  third := program.statements[2] as IfStatement else { panic("expected if statement") }
  Assert.isTrue(!hasBindingClause(third.condition))
  Assert.equal(conditionClauses(third.condition).length, 1)
  // A binding clause's initializer is a direct child for every walker.
  let children: Expression[] = []
  collectNestedExpressions(clauses[0], children)
  Assert.equal(children.length, 1)
  Assert.equal(children[0].kind, "call-expression")
}
