// Shared shallow AST traversal primitives.
//
// Statement collection descends through statement-owned blocks. Expression
// collection returns direct expression children; consumers choose whether to
// recurse, use a worklist, or stop at a semantic boundary.

import {
  ActorCreationExpression, ArrayLiteral, AssignmentExpression, AsyncExpression, BinaryExpression, Block, CallExpression,
  CaseExpression, CaseStatement, CatchExpression, ConstDeclaration, ConstructExpression, DestructuringStatement,
  ExportDeclaration, Expression, ExpressionStatement, ForOfStatement, ForStatement, IfExpression, IfStatement,
  ImmutableBinding, IndexExpression, LambdaExpression, LetDeclaration, MemberExpression, ObjectLiteral, RangePattern,
  ReadonlyDeclaration, RetireExpression, ReturnStatement, Statement, StringLiteral, TryStatement, TupleLiteral,
  UnaryExpression, ValuePattern, WhileStatement, WithStatement, YieldBlockAssignmentStatement, YieldBlockExpression,
  YieldStatement, AsExpression,
} from "./ast"

export function collectStatementExpressions(statement: Statement, result: Expression[]): none {
  case statement {
    value: ConstDeclaration -> { result.push(value.value) }
    value: ReadonlyDeclaration -> { result.push(value.value) }
    value: ImmutableBinding -> { result.push(value.value); if value.else_ != none { collectBlockExpressions(value.else_!, result) } }
    value: LetDeclaration -> { result.push(value.value) }
    expression: ExpressionStatement -> { result.push(expression.expression) }
    return_: ReturnStatement -> { if return_.value != none { result.push(return_.value!) } }
    yield_: YieldStatement -> { result.push(yield_.value) }
    if_: IfStatement -> {
      result.push(if_.condition)
      collectBlockExpressions(if_.body, result)
      for branch of if_.elseIfs { result.push(branch.condition); collectBlockExpressions(branch.body, result) }
      if if_.else_ != none { collectBlockExpressions(if_.else_!, result) }
    }
    while_: WhileStatement -> {
      result.push(while_.condition); collectBlockExpressions(while_.body, result)
      if while_.then_ != none { collectBlockExpressions(while_.then_!, result) }
    }
    for_: ForStatement -> {
      if for_.init != none { collectStatementExpressions(for_.init!, result) }
      if for_.condition != none { result.push(for_.condition!) }
      for update of for_.update { result.push(update) }
      collectBlockExpressions(for_.body, result)
      if for_.then_ != none { collectBlockExpressions(for_.then_!, result) }
    }
    forOf: ForOfStatement -> {
      result.push(forOf.iterable); collectBlockExpressions(forOf.body, result)
      if forOf.then_ != none { collectBlockExpressions(forOf.then_!, result) }
    }
    with_: WithStatement -> {
      for binding of with_.bindings { result.push(binding.value) }
      collectBlockExpressions(with_.body, result)
    }
    case_: CaseStatement -> {
      result.push(case_.subject)
      for arm of case_.arms {
        for pattern of arm.patterns {
          case pattern {
            value: ValuePattern -> { result.push(value.value) }
            range: RangePattern -> {
              if range.start != none { result.push(range.start!) }
              if range.end != none { result.push(range.end!) }
            }
            _ -> { }
          }
        }
        case arm.body {
          block: Block -> { collectBlockExpressions(block, result) }
          expression: Expression -> { result.push(expression) }
        }
      }
    }
    destructuring: DestructuringStatement -> { result.push(destructuring.value) }
    try_: TryStatement -> {
      case try_.binding {
        declaration: ConstDeclaration -> { collectStatementExpressions(declaration, result) }
        declaration: ReadonlyDeclaration -> { collectStatementExpressions(declaration, result) }
        binding: ImmutableBinding -> { collectStatementExpressions(binding, result) }
        declaration: LetDeclaration -> { collectStatementExpressions(declaration, result) }
        expression: ExpressionStatement -> { collectStatementExpressions(expression, result) }
        destructuring: DestructuringStatement -> { collectStatementExpressions(destructuring, result) }
      }
    }
    assignment: YieldBlockAssignmentStatement -> { result.push(assignment.value) }
    export_: ExportDeclaration -> { collectStatementExpressions(export_.declaration, result) }
    block: Block -> { collectBlockExpressions(block, result) }
    _ -> { }
  }
}

export function collectBlockExpressions(block: Block, result: Expression[]): none {
  for statement of block.statements { collectStatementExpressions(statement, result) }
}

export function collectNestedExpressions(expression: Expression, result: Expression[]): none {
  case expression {
    string_: StringLiteral -> { for interpolation of string_.interpolations { result.push(interpolation) } }
    binary: BinaryExpression -> { result.push(binary.left); result.push(binary.right) }
    unary: UnaryExpression -> { result.push(unary.operand) }
    assignment: AssignmentExpression -> { result.push(assignment.target); result.push(assignment.value) }
    member: MemberExpression -> { result.push(member.object) }
    index: IndexExpression -> { result.push(index.object); result.push(index.index) }
    call: CallExpression -> { result.push(call.callee); for argument of call.args { result.push(argument.value) } }
    array: ArrayLiteral -> { for element of array.elements { result.push(element) } }
    object: ObjectLiteral -> {
      if object.spread != none { result.push(object.spread!) }
      for property of object.properties {
        if property.key != none { result.push(property.key!) }
        if property.value != none { result.push(property.value!) }
      }
    }
    tuple: TupleLiteral -> { for element of tuple.elements { result.push(element) } }
    lambda: LambdaExpression -> {
      case lambda.body {
        block: Block -> { collectBlockExpressions(block, result) }
        body: Expression -> { result.push(body) }
      }
    }
    if_: IfExpression -> { result.push(if_.condition); result.push(if_.then_); result.push(if_.else_) }
    case_: CaseExpression -> {
      result.push(case_.subject)
      for arm of case_.arms {
        for pattern of arm.patterns {
          case pattern {
            value: ValuePattern -> { result.push(value.value) }
            range: RangePattern -> {
              if range.start != none { result.push(range.start!) }
              if range.end != none { result.push(range.end!) }
            }
            _ -> { }
          }
        }
        case arm.body {
          block: Block -> { collectBlockExpressions(block, result) }
          bodyExpression: Expression -> { result.push(bodyExpression) }
        }
      }
    }
    yieldBlock: YieldBlockExpression -> { collectBlockExpressions(yieldBlock.body, result) }
    catch_: CatchExpression -> { collectBlockExpressions(catch_.body, result) }
    async_: AsyncExpression -> {
      case async_.expression {
        block: Block -> { collectBlockExpressions(block, result) }
        inner: Expression -> { result.push(inner) }
      }
    }
    retire_: RetireExpression -> { result.push(retire_.actor) }
    actor: ActorCreationExpression -> { for argument of actor.args { result.push(argument) } }
    construct: ConstructExpression -> {
      if construct.spread != none { result.push(construct.spread!) }
      for property of construct.args { if property.value != none { result.push(property.value!) } }
    }
    as_: AsExpression -> { result.push(as_.expression) }
    _ -> { }
  }
}
