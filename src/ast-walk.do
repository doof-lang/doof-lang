// Shared shallow AST traversal primitives.
//
// Statement collection descends through statement-owned blocks. Expression
// collection returns direct expression children; consumers choose whether to
// recurse, use a worklist, or stop at a semantic boundary.
//
// Shallow queries over checked AST decorations live here when both the checker
// and emitter need them.

import {
  ActorCreationExpression, ArrayLiteral, AssignmentExpression, AsyncExpression, BinaryExpression, Block, CallExpression,
  BindingCondition, CaseExpression, CaseStatement, CatchExpression, ConstDeclaration, ConstructExpression, DestructuringStatement,
  Expression, ExpressionStatement, ForOfStatement, ForStatement, IfExpression, IfStatement,
  ImmutableBinding, IndexExpression, LambdaExpression, LetDeclaration, MemberExpression, ObjectLiteral, RangePattern,
  ReadonlyDeclaration, RetireExpression, ReturnStatement, Statement, StringLiteral, TryStatement, TupleLiteral,
  UnaryExpression, ValuePattern, WhileStatement, WithStatement, YieldBlockAssignmentStatement, YieldBlockExpression,
  YieldStatement, AsExpression, ClassDeclaration, FunctionDeclaration, InterfaceDeclaration, Identifier,
} from "./ast"

/** Whether an expression names a type parameter itself (`T` in `T.zero()`), not a value of that type. */
export function isTypeParameterName(expression: Expression): bool {
  case expression {
    identifier: Identifier -> { return identifier.resolvedBinding != none && identifier.resolvedBinding!.kind == "type-parameter" }
    _ -> { return false }
  }
}

// When `statements` is given, every visited statement is also recorded there,
// including statements inside nested blocks and lambda bodies, so consumers can
// recover statement-level semantics (such as a for-of iterable) that the
// flattened expression list loses.
export function collectStatementExpressions(statement: Statement, result: Expression[], statements: Statement[] | none = none): none {
  statements?.push(statement)
  case statement {
    value: ConstDeclaration -> { result.push(value.value) }
    value: ReadonlyDeclaration -> { result.push(value.value) }
    value: ImmutableBinding -> { result.push(value.value); if else_ := value.else_ { collectBlockExpressions(else_, result, statements) } }
    value: LetDeclaration -> { result.push(value.value) }
    expression: ExpressionStatement -> { result.push(expression.expression) }
    return_: ReturnStatement -> { if value := return_.value { result.push(value) } }
    yield_: YieldStatement -> { result.push(yield_.value) }
    if_: IfStatement -> {
      result.push(if_.condition)
      collectBlockExpressions(if_.body, result, statements)
      for branch of if_.elseIfs { result.push(branch.condition); collectBlockExpressions(branch.body, result, statements) }
      if else_ := if_.else_ { collectBlockExpressions(else_, result, statements) }
    }
    while_: WhileStatement -> {
      result.push(while_.condition); collectBlockExpressions(while_.body, result, statements)
      if then_ := while_.then_ { collectBlockExpressions(then_, result, statements) }
    }
    for_: ForStatement -> {
      for init of for_.init { collectStatementExpressions(init, result, statements) }
      if condition := for_.condition { result.push(condition) }
      for update of for_.update { result.push(update) }
      collectBlockExpressions(for_.body, result, statements)
      if then_ := for_.then_ { collectBlockExpressions(then_, result, statements) }
    }
    forOf: ForOfStatement -> {
      result.push(forOf.iterable); collectBlockExpressions(forOf.body, result, statements)
      if then_ := forOf.then_ { collectBlockExpressions(then_, result, statements) }
    }
    with_: WithStatement -> {
      for binding of with_.bindings { result.push(binding.value) }
      collectBlockExpressions(with_.body, result, statements)
    }
    case_: CaseStatement -> {
      result.push(case_.subject)
      for arm of case_.arms {
        for pattern of arm.patterns {
          case pattern {
            value: ValuePattern -> { result.push(value.value) }
            range: RangePattern -> {
              if start := range.start { result.push(start) }
              if end := range.end { result.push(end) }
            }
            _ -> { }
          }
        }
        case arm.body {
          block: Block -> { collectBlockExpressions(block, result, statements) }
          expression: Expression -> { result.push(expression) }
        }
      }
    }
    destructuring: DestructuringStatement -> { result.push(destructuring.value) }
    try_: TryStatement -> {
      case try_.binding {
        declaration: ConstDeclaration -> { collectStatementExpressions(declaration, result, statements) }
        declaration: ReadonlyDeclaration -> { collectStatementExpressions(declaration, result, statements) }
        binding: ImmutableBinding -> { collectStatementExpressions(binding, result, statements) }
        declaration: LetDeclaration -> { collectStatementExpressions(declaration, result, statements) }
        expression: ExpressionStatement -> { collectStatementExpressions(expression, result, statements) }
        destructuring: DestructuringStatement -> { collectStatementExpressions(destructuring, result, statements) }
      }
    }
    assignment: YieldBlockAssignmentStatement -> { result.push(assignment.value) }
    block: Block -> { collectBlockExpressions(block, result, statements) }
    _ -> { }
  }
}

export function collectBlockExpressions(block: Block, result: Expression[], statements: Statement[] | none = none): none {
  for statement of block.statements { collectStatementExpressions(statement, result, statements) }
}

export function collectNestedExpressions(expression: Expression, result: Expression[], statements: Statement[] | none = none): none {
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
      if spread := object.spread { result.push(spread) }
      for property of object.properties {
        if key := property.key { result.push(key) }
        if value := property.value { result.push(value) }
      }
    }
    tuple: TupleLiteral -> { for element of tuple.elements { result.push(element) } }
    lambda: LambdaExpression -> {
      case lambda.body {
        block: Block -> { collectBlockExpressions(block, result, statements) }
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
              if start := range.start { result.push(start) }
              if end := range.end { result.push(end) }
            }
            _ -> { }
          }
        }
        case arm.body {
          block: Block -> { collectBlockExpressions(block, result, statements) }
          bodyExpression: Expression -> { result.push(bodyExpression) }
        }
      }
    }
    yieldBlock: YieldBlockExpression -> { collectBlockExpressions(yieldBlock.body, result, statements) }
    catch_: CatchExpression -> { collectBlockExpressions(catch_.body, result, statements) }
    binding: BindingCondition -> { result.push(binding.value) }
    async_: AsyncExpression -> {
      case async_.expression {
        block: Block -> { collectBlockExpressions(block, result, statements) }
        inner: Expression -> { result.push(inner) }
      }
    }
    retire_: RetireExpression -> { result.push(retire_.actor) }
    actor: ActorCreationExpression -> { for argument of actor.args { result.push(argument) } }
    construct: ConstructExpression -> {
      if spread := construct.spread { result.push(spread) }
      for property of construct.args { if value := property.value { result.push(value) } }
    }
    as_: AsExpression -> { result.push(as_.expression) }
    _ -> { }
  }
}

// Preorder traversal for analyses that deliberately include every expression.
export function collectExpressionTree(expression: Expression, result: Expression[], statements: Statement[] | none = none): none {
  result.push(expression)
  let nested: Expression[] = []
  collectNestedExpressions(expression, nested, statements)
  for child of nested { collectExpressionTree(child, result, statements) }
}

// Checked annotations point from uses back to declarations: a call to its
// function, a member to its method, a construction to its class. Any recursion
// then forms a reference cycle through the declaration's own body, so a
// reference-counted host never frees the checked program. Consumers that are
// finished with an analysis call this to drop those back-references; the
// syntax tree and resolved types remain intact.
export function releaseCheckedReferences(statements: Statement[]): none {
  let pending: Statement[] = []
  for statement of statements { pending.push(statement) }
  let expressions: Expression[] = []
  while pending.length > 0 {
    statement := pending.pop()!
    case statement {
      function_: FunctionDeclaration -> { releaseFunctionBody(function_, pending, expressions) }
      class_: ClassDeclaration -> {
        for method of class_.methods { releaseFunctionBody(method, pending, expressions) }
        for field of class_.fields { if defaultValue := field.defaultValue { expressions.push(defaultValue) } }
        if destructor_ := class_.destructor_ { for inner of destructor_.statements { pending.push(inner) } }
      }
      interface_: InterfaceDeclaration -> {
        for method of interface_.methods { releaseFunctionBody(method, pending, expressions) }
        for method of interface_.staticMethods { releaseFunctionBody(method, pending, expressions) }
      }
      block: Block -> { for inner of block.statements { pending.push(inner) } }
      _ -> { collectStatementExpressions(statement, expressions) }
    }
    while expressions.length > 0 {
      expression := expressions.pop()!
      releaseExpression(expression)
      collectNestedExpressions(expression, expressions)
    }
  }
}

function releaseFunctionBody(function_: FunctionDeclaration, pending: Statement[], expressions: Expression[]): none {
  for param of function_.params { if defaultValue := param.defaultValue { expressions.push(defaultValue) } }
  case function_.body {
    block: Block -> { for inner of block.statements { pending.push(inner) } }
    expression: Expression -> { expressions.push(expression) }
  }
}

function releaseExpression(expression: Expression): none {
  case expression {
    call: CallExpression -> {
      call.resolvedConstruction = none; call.resolvedFunction = none
      call.resolvedConstructor = none; call.resolvedClass = none
    }
    member: MemberExpression -> { member.resolvedMember = none; member.resolvedStaticOwner = none; member.resolvedJsonAlias = none }
    object: ObjectLiteral -> { object.resolvedConstruction = none; object.resolvedClass = none }
    tuple: TupleLiteral -> { tuple.resolvedConstruction = none; tuple.resolvedClass = none }
    construct: ConstructExpression -> {
      construct.resolvedConstruction = none; construct.resolvedClass = none; construct.resolvedConstructor = none
    }
    actor: ActorCreationExpression -> { actor.resolvedConstruction = none; actor.resolvedConstructor = none }
    _ -> { }
  }
}

/** Whether a condition has a binding clause among its top-level `&&` operands. */
export function hasBindingClause(condition: Expression): bool {
  case condition {
    _: BindingCondition -> { return true }
    binary: BinaryExpression -> { return binary.operator == "&&" && (hasBindingClause(binary.left) || hasBindingClause(binary.right)) }
    _ -> { return false }
  }
}

/**
 * The clauses of a condition with binding clauses, left to right: its
 * top-level `&&` operands. A `&&` subtree without bindings stays one clause.
 */
export function conditionClauses(condition: Expression): Expression[] {
  let clauses: Expression[] = []
  collectConditionClauses(condition, clauses)
  return clauses
}

function collectConditionClauses(condition: Expression, clauses: Expression[]): none {
  case condition {
    binary: BinaryExpression -> {
      if binary.operator == "&&" && hasBindingClause(binary) {
        collectConditionClauses(binary.left, clauses)
        collectConditionClauses(binary.right, clauses)
        return
      }
    }
    _ -> { }
  }
  clauses.push(condition)
}
