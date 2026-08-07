// AST traversal owned by consumer-worldview planning.

import {
  ActorCreationExpression, ArrayLiteral, AssignmentExpression, AsyncExpression, BinaryExpression, Block, CallExpression,
  CaseExpression, CaseStatement, CatchExpression, ConstDeclaration, ConstructExpression, DestructuringStatement,
  ExportDeclaration, Expression, ExpressionStatement, ForOfStatement, ForStatement, IfExpression, IfStatement,
  ImmutableBinding, IndexExpression, LambdaExpression, LetDeclaration, MemberExpression, ObjectLiteral, RangePattern,
  ReadonlyDeclaration, RetireExpression, ReturnStatement, Statement, StringLiteral, TryStatement, TupleLiteral,
  UnaryExpression, ValuePattern, WhileStatement, WithStatement, YieldBlockAssignmentStatement, YieldBlockExpression,
  YieldStatement, AsExpression,
} from "./ast"

export function collectWorldviewStatementExpressions(statement: Statement, result: Expression[]): none {
  case statement {
    value: ConstDeclaration -> { result.push(value.value) }
    value: ReadonlyDeclaration -> { result.push(value.value) }
    value: ImmutableBinding -> { result.push(value.value); if value.else_ != none { collectWorldviewBlockExpressions(value.else_!, result) } }
    value: LetDeclaration -> { result.push(value.value) }
    expression: ExpressionStatement -> { result.push(expression.expression) }
    return_: ReturnStatement -> { if return_.value != none { result.push(return_.value!) } }
    yield_: YieldStatement -> { result.push(yield_.value) }
    if_: IfStatement -> {
      result.push(if_.condition)
      collectWorldviewBlockExpressions(if_.body, result)
      for branch of if_.elseIfs { result.push(branch.condition); collectWorldviewBlockExpressions(branch.body, result) }
      if if_.else_ != none { collectWorldviewBlockExpressions(if_.else_!, result) }
    }
    while_: WhileStatement -> {
      result.push(while_.condition); collectWorldviewBlockExpressions(while_.body, result)
      if while_.then_ != none { collectWorldviewBlockExpressions(while_.then_!, result) }
    }
    for_: ForStatement -> {
      if for_.init != none { collectWorldviewStatementExpressions(for_.init!, result) }
      if for_.condition != none { result.push(for_.condition!) }
      for update of for_.update { result.push(update) }
      collectWorldviewBlockExpressions(for_.body, result)
      if for_.then_ != none { collectWorldviewBlockExpressions(for_.then_!, result) }
    }
    forOf: ForOfStatement -> {
      result.push(forOf.iterable); collectWorldviewBlockExpressions(forOf.body, result)
      if forOf.then_ != none { collectWorldviewBlockExpressions(forOf.then_!, result) }
    }
    with_: WithStatement -> {
      for binding of with_.bindings { result.push(binding.value) }
      collectWorldviewBlockExpressions(with_.body, result)
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
          block: Block -> { collectWorldviewBlockExpressions(block, result) }
          expression: Expression -> { result.push(expression) }
        }
      }
    }
    destructuring: DestructuringStatement -> { result.push(destructuring.value) }
    try_: TryStatement -> {
      case try_.binding {
        declaration: ConstDeclaration -> { collectWorldviewStatementExpressions(declaration, result) }
        declaration: ReadonlyDeclaration -> { collectWorldviewStatementExpressions(declaration, result) }
        binding: ImmutableBinding -> { collectWorldviewStatementExpressions(binding, result) }
        declaration: LetDeclaration -> { collectWorldviewStatementExpressions(declaration, result) }
        expression: ExpressionStatement -> { collectWorldviewStatementExpressions(expression, result) }
        destructuring: DestructuringStatement -> { collectWorldviewStatementExpressions(destructuring, result) }
      }
    }
    assignment: YieldBlockAssignmentStatement -> { result.push(assignment.value) }
    export_: ExportDeclaration -> { collectWorldviewStatementExpressions(export_.declaration, result) }
    block: Block -> { collectWorldviewBlockExpressions(block, result) }
    _ -> { }
  }
}

export function collectWorldviewBlockExpressions(block: Block, result: Expression[]): none {
  for statement of block.statements { collectWorldviewStatementExpressions(statement, result) }
}

export function collectWorldviewNestedExpressions(expression: Expression, result: Expression[]): none {
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
        block: Block -> { collectWorldviewBlockExpressions(block, result) }
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
          block: Block -> { collectWorldviewBlockExpressions(block, result) }
          bodyExpression: Expression -> { result.push(bodyExpression) }
        }
      }
    }
    yieldBlock: YieldBlockExpression -> { collectWorldviewBlockExpressions(yieldBlock.body, result) }
    catch_: CatchExpression -> { collectWorldviewBlockExpressions(catch_.body, result) }
    async_: AsyncExpression -> {
      case async_.expression {
        block: Block -> { collectWorldviewBlockExpressions(block, result) }
        inner: Expression -> { result.push(inner) }
      }
    }
    retire_: RetireExpression -> { result.push(retire_.actor) }
    actor: ActorCreationExpression -> { for argument of actor.args { result.push(argument) } }
    construct: ConstructExpression -> {
      for property of construct.args { if property.value != none { result.push(property.value!) } }
    }
    as_: AsExpression -> { result.push(as_.expression) }
    _ -> { }
  }
}
