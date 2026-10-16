// Statement, control-flow, and case-pattern parsing for the Doof parser.

import type { Parser } from "./parser"
import { Token, TokenType } from "./lexer"
import {
  Block, IfBranch, WithBinding, CaseArm, CaseExpression, CaseExpressionArm, CaseStatement,
  CasePattern, RangePattern, TypePattern, ValuePattern, WildcardPattern,
  IfStatement, WhileStatement, ForOfStatement, ForStatement, WithStatement,
  BreakStatement, ContinueStatement, ReturnStatement, YieldStatement,
  ExpressionStatement, DestructuringStatement, DestructureBinding, ConstDeclaration, ReadonlyDeclaration, ImmutableBinding, TryStatement,
  LetDeclaration, LambdaExpression, CallExpression,
  CallArgument, AstLocation, SourceSpan, YieldBlockExpression, YieldBlockAssignmentStatement,
  FunctionDeclaration, NamedType,
} from "./ast"
import type { Statement, Expression, TypeAnnotation } from "./ast"

export isolated function parseStatement(parser: Parser): Statement {
  if parser.check(TokenType.Mock) { return parser.parseMockImport() }
  if parser.check(TokenType.Export) { return parser.parseExport() }
  if parser.check(TokenType.Import) { return parser.parseImport() }
  if parser.check(TokenType.Const) { return parser.parseConst(false) }
  if parser.check(TokenType.Readonly) && parser.peek(1).kind != TokenType.LeftBracket { return parser.parseReadonly(false) }
  if parser.check(TokenType.Let) { return parser.parseLet() }
  if parser.check(TokenType.Function) { return parser.parseFunction(false, false, false, false) }
  if parser.check(TokenType.Isolated) && parser.peek(1).kind == TokenType.Function {
    parser.advance()
    return parser.parseFunction(false, false, true, false)
  }
  if parser.check(TokenType.Class) || parser.check(TokenType.Struct) { return parser.parseClass(false, false) }
  if parser.check(TokenType.Private) {
    parser.advance()
    if parser.check(TokenType.Function) { return parser.parseFunction(false, false, false, true) }
    if parser.check(TokenType.Class) || parser.check(TokenType.Struct) { return parser.parseClass(false, true) }
    parser.fail("Expected function, class, or struct after private")
  }
  if parser.check(TokenType.Interface) { return parser.parseInterface(false) }
  if parser.check(TokenType.Enum) { return parser.parseEnum(false) }
  if parser.check(TokenType.Type) { return parser.parseTypeAlias(false) }
  if parser.check(TokenType.Return) { return parseReturn(parser) }
  if parser.check(TokenType.Yield) { return parseYield(parser) }
  if parser.check(TokenType.Try) { return parseTryStatement(parser) }
  if parser.check(TokenType.If) { return parseIfStatement(parser) }
  if parser.check(TokenType.Case) { return parseCaseStatement(parser) }
  if parser.check(TokenType.Identifier) && parser.peek(1).kind == TokenType.Colon
      && (parser.peek(2).kind == TokenType.While || parser.peek(2).kind == TokenType.For) {
    loopStart := parser.location()
    label := parser.text(parser.advance())
    parser.expect(TokenType.Colon)
    if parser.check(TokenType.While) { return parseWhile(parser, label, loopStart) }
    return parseFor(parser, label, loopStart)
  }
  if parser.check(TokenType.While) { return parseWhile(parser, none, parser.location()) }
  if parser.check(TokenType.For) { return parseFor(parser, none, parser.location()) }
  if parser.check(TokenType.With) { return parseWith(parser) }
  if parser.check(TokenType.Break) { return parseBreak(parser) }
  if parser.check(TokenType.Continue) { return parseContinue(parser) }

  if startsImmutableBinding(parser) { return parseImmutableBinding(parser, true) }
  destructuring := parseDestructuringStatement(parser)
  if destructuring != none { return destructuring! }
  if parser.check(TokenType.LeftBrace) { parser.fail("Bare block statements are not allowed") }

  return parseExpressionStatement(parser)
}

// `[a, b] := v`, `(a, b) = v`, `{ name } := v`, and their assignment forms.
function parseDestructuringStatement(parser: Parser): Statement | none {
  shape := destructuringShape(parser)
  if shape == "" { return none }
  if looksLikePattern(parser, TokenType.ColonEqual) { return parseDestructuring(parser, shape, "immutable", TokenType.ColonEqual) }
  if looksLikePattern(parser, TokenType.Equal) { return parseDestructuring(parser, shape, "assignment", TokenType.Equal) }
  return none
}

function parseReturn(parser: Parser): Statement {
  start := parser.location()
  parser.expect(TokenType.Return)
  if parser.check(TokenType.RightBrace) || parser.check(TokenType.EndOfFile) || parser.check(TokenType.Semicolon) {
    parser.consumeSemicolon()
    return ReturnStatement { kind: "return-statement", span: parser.span(start) }
  }
  value := parser.parseExpression()
  parser.consumeSemicolon()
  return ReturnStatement { kind: "return-statement", value: value, span: parser.span(start) }
}

function parseYield(parser: Parser): Statement {
  start := parser.location()
  parser.expect(TokenType.Yield)
  value := parser.parseExpression()
  parser.consumeSemicolon()
  return YieldStatement { kind: "yield-statement", value: value, span: parser.span(start) }
}

function parseIfStatement(parser: Parser): Statement {
  start := parser.location()
  parser.expect(TokenType.If)
  condition := parser.parseExpression()
  body := parseBlock(parser)
  let elseIfs: IfBranch[] = []
  let else_: Block | none = none
  while parser.match(TokenType.Else) {
    if parser.match(TokenType.If) {
      branchStart := parser.location()
      branchCondition := parser.parseExpression()
      branchBody := parseBlock(parser)
      elseIfs.push(IfBranch { condition: branchCondition, body: branchBody, span: parser.span(branchStart) })
    } else {
      else_ = parseBlock(parser)
      break
    }
  }
  return IfStatement { kind: "if-statement", condition, body, elseIfs, else_, span: parser.span(start) }
}

function parseCaseStatement(parser: Parser): Statement {
  start := parser.location()
  parser.expect(TokenType.Case)
  subject := parser.parseExpression()
  parser.expect(TokenType.LeftBrace)
  let arms: CaseArm[] = []
  while !parser.check(TokenType.RightBrace) && !parser.atEnd() {
    armStart := parser.location()
    patterns := parseCaseArmPatterns(parser)
    body := if parser.check(TokenType.LeftBrace) then parseBlock(parser) else parseBoundedCaseArm(parser)
    arms.push(CaseArm { kind: "case-arm", patterns, body, span: parser.span(armStart) })
    parser.match(TokenType.Comma)
  }
  parser.expect(TokenType.RightBrace)
  parser.consumeSemicolon()
  return CaseStatement { kind: "case-statement", subject, arms, span: parser.span(start) }
}

export function parseCaseExpression(parser: Parser): Expression {
  start := parser.location()
  parser.expect(TokenType.Case)
  subject := parser.parseExpression()
  parser.expect(TokenType.LeftBrace)
  let arms: CaseExpressionArm[] = []
  while !parser.check(TokenType.RightBrace) && !parser.atEnd() {
    armStart := parser.location()
    patterns := parseCaseArmPatterns(parser)
    body := parseCaseExpressionBody(parser)
    arms.push(CaseExpressionArm { kind: "case-expression-arm", patterns, body, span: parser.span(armStart) })
    parser.match(TokenType.Comma)
  }
  parser.expect(TokenType.RightBrace)
  return CaseExpression { kind: "case-expression", subject, arms, span: parser.span(start) }
}

// `pattern | pattern ->` at the start of a case arm.
function parseCaseArmPatterns(parser: Parser): CasePattern[] {
  let patterns: CasePattern[] = [parseCasePattern(parser)]
  while parser.match(TokenType.Pipe) { patterns.push(parseCasePattern(parser)) }
  parser.expect(TokenType.RightArrow)
  return patterns
}

// Keep the Expression/Block promotion at a typed boundary so generated C++
// does not try to represent this choice as a native conditional expression.
function parseCaseExpressionBody(parser: Parser): Expression | Block {
  if parser.check(TokenType.LeftBrace) { return parseBlock(parser) }
  previousBoundary := enterInlineCaseArm(parser)
  body := parser.parseExpression()
  parser.caseArmBoundary = previousBoundary
  return body
}

function parseBoundedCaseArm(parser: Parser): Block {
  previousBoundary := enterInlineCaseArm(parser)
  statement := parseStatement(parser)
  parser.caseArmBoundary = previousBoundary
  return Block { kind: "block", statements: [statement], span: statement.span }
}

// Bounds an inline arm body at the next arm; returns the boundary to restore.
function enterInlineCaseArm(parser: Parser): int {
  previousBoundary := parser.caseArmBoundary
  parser.caseArmBoundary = nextCaseArmBoundary(parser)
  return previousBoundary
}

// Inline arm bodies continue across lines like other expressions, so an arm
// beginning with `.`, `-`, or `..<` would otherwise extend the previous body.
// The next arm starts on the first later line whose depth-0 tokens reach `->`.
function nextCaseArmBoundary(parser: Parser): int {
  tokens := parser.tokens
  let depth = 0
  for index of parser.pos..<tokens.length {
    kind := tokens[index].kind
    if depth == 0 && index > parser.pos {
      if kind == TokenType.Comma || kind == TokenType.RightBrace || kind == TokenType.EndOfFile { return -1 }
      if tokens[index].line > tokens[index - 1].line && lineStartsCaseArm(tokens, index) { return index }
    }
    if kind == TokenType.LeftParen || kind == TokenType.LeftBracket || kind == TokenType.LeftBrace { depth += 1 }
    else if kind == TokenType.RightParen || kind == TokenType.RightBracket || kind == TokenType.RightBrace {
      if depth == 0 { return -1 }
      depth -= 1
    }
  }
  return -1
}

function lineStartsCaseArm(tokens: Token[], start: int): bool {
  line := tokens[start].line
  let depth = 0
  let index = start
  while index < tokens.length && tokens[index].line == line {
    kind := tokens[index].kind
    if depth == 0 && kind == TokenType.RightArrow { return true }
    if kind == TokenType.LeftParen || kind == TokenType.LeftBracket || kind == TokenType.LeftBrace { depth += 1 }
    else if kind == TokenType.RightParen || kind == TokenType.RightBracket || kind == TokenType.RightBrace {
      if depth == 0 { return false }
      depth -= 1
    }
    index += 1
  }
  return false
}

function parseCasePattern(parser: Parser): CasePattern {
  start := parser.location()
  if parser.match(TokenType.Underscore) {
    if parser.match(TokenType.Colon) {
      typeValue := parser.parseTypeAnnotation()
      return TypePattern { kind: "type-pattern", name: "_", type_: typeValue, span: parser.span(start) }
    }
    return WildcardPattern { kind: "wildcard-pattern", span: parser.span(start) }
  }
  if parser.match(TokenType.DotDotLess) { return rangePattern(parser, start, none, parser.parseAdditive(), false) }
  if parser.check(TokenType.Identifier) && parser.peek(1).kind == TokenType.Colon {
    name := parser.text(parser.advance())
    parser.advance()
    typeValue := parser.parseTypeAnnotation()
    return TypePattern { kind: "type-pattern", name, type_: typeValue, span: parser.span(start) }
  }
  // Pattern alternatives use `|` as a separator, so a value pattern must
  // stop before bitwise-or rather than consume the rest of the arm.
  value := parser.parseAdditive()
  if parser.match(TokenType.DotDot) {
    if parser.check(TokenType.RightArrow) || parser.check(TokenType.Pipe) || parser.check(TokenType.Comma) || parser.check(TokenType.RightBrace) || parser.atEnd() {
      return rangePattern(parser, start, value, none, true)
    }
    return rangePattern(parser, start, value, parser.parseAdditive(), true)
  }
  if parser.match(TokenType.DotDotLess) { return rangePattern(parser, start, value, parser.parseAdditive(), false) }
  return ValuePattern { kind: "value-pattern", value, span: parser.span(start) }
}

function rangePattern(parser: Parser, start: AstLocation, low: Expression | none, high: Expression | none, inclusive: bool): CasePattern {
  return RangePattern { kind: "range-pattern", start: low, end: high, inclusive, span: parser.span(start) }
}

function parseWhile(parser: Parser, label: string | none, start: AstLocation): Statement {
  parser.expect(TokenType.While)
  condition := parser.parseExpression()
  body := parseBlock(parser)
  then_ := parseLoopThen(parser)
  return WhileStatement { kind: "while-statement", condition, body, label, then_, span: parser.span(start) }
}

function parseFor(parser: Parser, label: string | none, start: AstLocation): Statement {
  parser.expect(TokenType.For)
  if discardableBindingToken(parser.current().kind) && (parser.peek(1).kind == TokenType.Of || parser.peek(1).kind == TokenType.Comma) {
    let bindings: string[] = [parseDiscardableBindingName(parser, "Expected loop binding name or '_'")]
    while parser.match(TokenType.Comma) { bindings.push(parseDiscardableBindingName(parser, "Expected loop binding name or '_'")) }
    parser.expect(TokenType.Of)
    parser.inForIterable = true
    iterable := parser.parseExpression()
    parser.inForIterable = false
    body := parseBlock(parser)
    then_ := parseLoopThen(parser)
    return ForOfStatement { kind: "for-of-statement", bindings, iterable, body, label, then_, span: parser.span(start) }
  }
  // One `let` covers every comma-separated declarator: `let i = 0, j = 10`.
  let init: Statement[] = []
  if !parser.check(TokenType.Semicolon) {
    if parser.check(TokenType.Let) {
      declaratorStart := parser.location()
      parser.expect(TokenType.Let)
      init.push(parser.parseLetDeclarator(declaratorStart, true))
      while parser.match(TokenType.Comma) { init.push(parser.parseLetDeclarator(parser.location(), true)) }
    } else {
      init.push(parseExpressionStatementNoSemicolon(parser))
      while parser.match(TokenType.Comma) { init.push(parseExpressionStatementNoSemicolon(parser)) }
    }
  }
  parser.expect(TokenType.Semicolon)
  let condition: Expression | none = none
  if !parser.check(TokenType.Semicolon) { condition = parser.parseExpression() }
  parser.expect(TokenType.Semicolon)
  let update: Expression[] = []
  while !parser.check(TokenType.LeftBrace) && !parser.atEnd() {
    update.push(parser.parseExpression())
    if !parser.match(TokenType.Comma) { break }
  }
  body := parseBlock(parser)
  then_ := parseLoopThen(parser)
  return ForStatement { kind: "for-statement", init, condition, update, body, label, then_, span: parser.span(start) }
}

// The optional `then { ... }` block that runs when a loop ends without `break`.
function parseLoopThen(parser: Parser): Block | none {
  if !parser.match(TokenType.Then) { return none }
  return parseBlock(parser)
}

function parseExpressionStatementNoSemicolon(parser: Parser): Statement {
  start := parser.location()
  value := parser.parseExpression()
  return ExpressionStatement { kind: "expression-statement", expression: value, span: parser.span(start) }
}

function parseWith(parser: Parser): Statement {
  start := parser.location()
  parser.expect(TokenType.With)
  let bindings: WithBinding[] = []
  while !parser.check(TokenType.LeftBrace) && !parser.atEnd() {
    bindingStart := parser.location()
    name := parseDiscardableBindingName(parser, "Expected scoped binding name or '_'")
    typeValue := parser.parseOptionalType()
    parser.expect(TokenType.ColonEqual)
    value := parser.parseExpression()
    bindings.push(WithBinding { name, type_: typeValue, value, span: parser.span(bindingStart) })
    if !parser.match(TokenType.Comma) { break }
  }
  body := parseBlock(parser)
  return WithStatement { kind: "with-statement", bindings, body, span: parser.span(start) }
}

function discardableBindingToken(kind: TokenType): bool {
  return kind == TokenType.Identifier || kind == TokenType.Underscore
}

function parseDiscardableBindingName(parser: Parser, message: string): string {
  if discardableBindingToken(parser.current().kind) { return parser.text(parser.advance()) }
  parser.fail(message)
  return "<error>"
}

function parseBreak(parser: Parser): Statement {
  start := parser.location()
  parser.expect(TokenType.Break)
  label := parseJumpLabel(parser)
  return BreakStatement { kind: "break-statement", label, span: parser.span(start) }
}

function parseContinue(parser: Parser): Statement {
  start := parser.location()
  parser.expect(TokenType.Continue)
  label := parseJumpLabel(parser)
  return ContinueStatement { kind: "continue-statement", label, span: parser.span(start) }
}

// A loop label must stay on the `break`/`continue` line; the statement ends there.
function parseJumpLabel(parser: Parser): string | none {
  let label: string | none = none
  if parser.check(TokenType.Identifier) && parser.sameLineAsPrevious() { label = parser.text(parser.advance()) }
  parser.consumeSemicolon()
  return label
}

// The `{ ... }` after a `<-` that has already been consumed.
export function parseYieldBlock(parser: Parser): YieldBlockExpression {
  start := parser.location()
  if !parser.check(TokenType.LeftBrace) { parser.fail("Expected block after '<-'") }
  body := parseBlock(parser)
  return YieldBlockExpression { body, span: parser.span(start) }
}

export function parseBlock(parser: Parser): Block {
  start := parser.location()
  parser.expect(TokenType.LeftBrace)
  let statements: Statement[] = []
  while !parser.check(TokenType.RightBrace) && !parser.atEnd() { parser.appendStatement(statements, true) }
  parser.expect(TokenType.RightBrace)
  return Block { kind: "block", statements, span: parser.span(start) }
}

// Statements inside a block. Module directives and type declarations are
// parsed in full before being rejected at their start, so editor recovery
// resumes after the declaration.
export function parseLocalStatement(parser: Parser): Statement {
  let directive = ""
  if parser.check(TokenType.Import) { directive = "Import declarations" }
  if parser.check(TokenType.Mock) { directive = "mock import directives" }
  if parser.check(TokenType.Export) { directive = "Export declarations" }
  modified := parser.check(TokenType.Private) || parser.check(TokenType.Isolated)
  declarationToken := if modified then parser.peek(1).kind else parser.current().kind
  if declarationToken == TokenType.Class { directive = "Class declarations" }
  if declarationToken == TokenType.Struct { directive = "Struct declarations" }
  if declarationToken == TokenType.Interface { directive = "Interface declarations" }
  if declarationToken == TokenType.Enum { directive = "Enum declarations" }
  if declarationToken == TokenType.Type { directive = "Type alias declarations" }
  start := parser.location()
  statement := parseStatement(parser)
  if directive != "" { parser.failAt(start, directive + " are only valid at module level") }
  return normalizeLocalFunction(parser, statement)
}

// Local named functions are syntax sugar for immutable lambda bindings. Keep
// this normalization at the parser boundary so checking, closure capture, and
// emission have exactly one representation for local callable values.
export function normalizeLocalFunction(parser: Parser, statement: Statement): Statement {
  case statement {
    fn: FunctionDeclaration -> {
      if fn.typeParams.length > 0 {
        parser.fail("Nested generic functions are not supported; use a non-generic local function or a top-level generic function")
      }
      if fn.isolated_ || fn.private_ || fn.static_ || fn.exported {
        parser.fail("Nested function modifiers are not supported; local functions use lambda semantics")
      }
      for parameter of fn.params {
        if parameter.defaultValue != none {
          parser.fail("Nested function default parameters are not supported; handle defaults inside the function body or use a top-level function")
        }
      }
      let returnType = fn.returnType
      if returnType == none {
        returnType = NamedType { kind: "named-type", name: "none", typeArgs: [], span: fn.span }
      }
      lambda := LambdaExpression {
        kind: "lambda-expression",
        params: fn.params,
        returnType,
        body: fn.body,
        parameterless: fn.params.length == 0,
        trailing: false,
        span: fn.span,
      }
      return ImmutableBinding {
        kind: "immutable-binding",
        name: fn.name,
        type_: none,
        value: lambda,
        exported: false,
        span: fn.span,
      }
    }
    _ -> { return statement }
  }
  return statement
}

export function looksLikePattern(parser: Parser, separator: TokenType): bool {
  let depth = 0
  let index = 0
  while index < 128 {
    token := parser.peek(index)
    if token.kind == TokenType.EndOfFile { return false }
    if token.kind == TokenType.LeftBracket || token.kind == TokenType.LeftParen || token.kind == TokenType.LeftBrace { depth = depth + 1 }
    if token.kind == TokenType.RightBracket || token.kind == TokenType.RightParen || token.kind == TokenType.RightBrace { depth = depth - 1 }
    if depth == 0 && token.kind == separator { return true }
    if depth == 0 && token.kind == TokenType.Equal { return separator == TokenType.Equal }
    index = index + 1
  }
  return false
}

// The destructuring shape a pattern opening at the current token would have,
// or "" when the token cannot open a pattern.
export function destructuringShape(parser: Parser): string {
  if parser.check(TokenType.LeftBracket) { return "array" }
  if parser.check(TokenType.LeftParen) { return "positional" }
  if parser.check(TokenType.LeftBrace) { return "named" }
  return ""
}

export function parseDestructuring(parser: Parser, shape: string, bindingKind: string, separator: TokenType): Statement {
  start := parser.location()
  let close = TokenType.RightParen
  let open = TokenType.LeftParen
  if shape == "array" { close = TokenType.RightBracket; open = TokenType.LeftBracket }
  if shape == "named" { close = TokenType.RightBrace; open = TokenType.LeftBrace }
  parser.expect(open)
  let bindings: string[] = []
  let namedBindings: DestructureBinding[] = []
  while !parser.check(close) && !parser.atEnd() {
    bindingStart := parser.location()
    if shape == "named" {
      name := parser.text(parser.expect(TokenType.Identifier))
      let alias: string | none = none
      if parser.match(TokenType.As) { alias = parser.text(parser.expect(TokenType.Identifier)) }
      namedBindings.push(DestructureBinding { name, alias, span: parser.span(bindingStart) })
    } else {
      bindings.push(parseDiscardableBindingName(parser, "Expected destructuring binding name or '_'"))
    }
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(close)
  parser.expect(separator)
  value := parser.parseExpression()
  parser.consumeSemicolon()
  let kind = if shape == "array" then "array-destructuring" else if shape == "named" then "named-destructuring" else "positional-destructuring"
  if bindingKind == "assignment" { kind = kind + "-assignment" }
  return DestructuringStatement { kind, bindings, namedBindings, bindingKind, value, span: parser.span(start) }
}

function parseExpressionStatement(parser: Parser): Statement {
  start := parser.location()
  if parser.check(TokenType.Identifier) && parser.peek(1).kind == TokenType.LeftArrow {
    name := parser.text(parser.advance())
    parser.advance()
    value := parseYieldBlock(parser)
    parser.consumeSemicolon()
    return YieldBlockAssignmentStatement { name, value, span: parser.span(start) }
  }
  let value = parser.parseExpression()
  // Statement-else: `expr else { ... }` binds the success value to nothing.
  if parser.check(TokenType.Else) { return finishImmutableBinding(parser, start, "_", none, value, true) }
  value = parseTrailingLambdaExpressionStatement(parser, value)
  parser.consumeSemicolon()
  return ExpressionStatement { kind: "expression-statement", expression: value, span: parser.span(start) }
}

// Trailing lambdas are statement-only syntax, so attach the block only after
// the ordinary expression parser has produced the complete call expression.
function parseTrailingLambdaExpressionStatement(parser: Parser, expression: Expression): Expression {
  if !parser.previousIs(TokenType.RightParen) || !parser.check(TokenType.LeftBrace) || !parser.sameLineAsPrevious() {
    return expression
  }
  case expression {
    call: CallExpression -> {
      block := parseBlock(parser)
      lambda := LambdaExpression {
        kind: "lambda-expression", params: [], returnType: none, body: block,
        parameterless: true, trailing: true, span: block.span,
      }
      call.args.push(CallArgument { name: none, value: lambda, span: block.span })
      call.span = SourceSpan { start: call.span.start, end: block.span.end }
      if parser.sameLineAsPrevious() && (
        parser.check(TokenType.Dot) || parser.check(TokenType.DoubleColon) ||
        parser.check(TokenType.QuestionDot) || parser.check(TokenType.BangDot) ||
        parser.check(TokenType.LeftParen) || parser.check(TokenType.LeftBracket) ||
        parser.check(TokenType.QuestionBracket) || parser.check(TokenType.Bang) || parser.check(TokenType.Question)
      ) {
        parser.fail("Chaining after a trailing lambda is not allowed; use an explicit lambda instead")
      }
      return call
    }
    _ -> { return expression }
  }
}

export isolated function parseTryStatement(parser: Parser): Statement {
  // The removed `try!`/`try?` prefixes are ordinary expressions so the checker
  // can report their postfix spelling wherever they appear.
  if parser.peek(1).kind == TokenType.Bang || parser.peek(1).kind == TokenType.Question { return parseExpressionStatement(parser) }
  start := parser.location()
  parser.expect(TokenType.Try)
  if parser.check(TokenType.Const) {
    case parser.parseConst(false) {
      binding: ConstDeclaration -> { return TryStatement { kind: "try-statement", binding, span: parser.span(start) } }
      _ -> { parser.fail("Expected const declaration after try") }
    }
  }
  if parser.check(TokenType.Readonly) {
    case parser.parseReadonly(false) {
      binding: ReadonlyDeclaration -> { return TryStatement { kind: "try-statement", binding, span: parser.span(start) } }
      _ -> { parser.fail("Expected readonly declaration after try") }
    }
  }
  if parser.check(TokenType.Let) {
    case parser.parseLet() {
      binding: LetDeclaration -> { return TryStatement { kind: "try-statement", binding, span: parser.span(start) } }
      binding: DestructuringStatement -> { return TryStatement { kind: "try-statement", binding, span: parser.span(start) } }
      _ -> { parser.fail("Expected named let declaration after try") }
    }
  }
  case parseDestructuringStatement(parser) {
    binding: DestructuringStatement -> { return TryStatement { kind: "try-statement", binding, span: parser.span(start) } }
    _ -> { }
  }
  if parser.check(TokenType.Identifier) && startsImmutableBinding(parser) {
    binding := parseImmutableBinding(parser, false)
    return TryStatement { kind: "try-statement", binding, span: parser.span(start) }
  }
  value := parser.parseExpression()
  parser.consumeSemicolon()
  return TryStatement {
    kind: "try-statement",
    binding: ExpressionStatement { kind: "expression-statement", expression: value, span: parser.span(start) },
    span: parser.span(start),
  }
}

// `name := value`, `name: Type := value`, or the discarding `_ := value`.
function startsImmutableBinding(parser: Parser): bool {
  next := parser.peek(1).kind
  if parser.check(TokenType.Underscore) { return next == TokenType.ColonEqual }
  if !parser.check(TokenType.Identifier) { return false }
  return next == TokenType.ColonEqual || (next == TokenType.Colon && looksLikeTypedImmutableBinding(parser))
}

function looksLikeTypedImmutableBinding(parser: Parser): bool {
  let index = 2
  while index < 64 {
    token := parser.peek(index)
    if token.kind == TokenType.EndOfFile || token.kind == TokenType.Semicolon || token.kind == TokenType.LeftBrace { return false }
    if token.kind == TokenType.ColonEqual { return true }
    index = index + 1
  }
  return false
}

// A `try` binding propagates failure, so it cannot also handle it with `else`.
function parseImmutableBinding(parser: Parser, allowElse: bool): ImmutableBinding {
  start := parser.location()
  name := parser.text(parser.advance())
  let typeValue: TypeAnnotation | none = none
  if parser.match(TokenType.Colon) { typeValue = parser.parseTypeAnnotation() }
  parser.expect(TokenType.ColonEqual)
  value := parser.parseExpression()
  return finishImmutableBinding(parser, start, name, typeValue, value, allowElse)
}

// Parses the optional `else [failure] { ... }` and terminator of a binding.
function finishImmutableBinding(parser: Parser, start: AstLocation, name: string, typeValue: TypeAnnotation | none, value: Expression, allowElse: bool): ImmutableBinding {
  let else_: Block | none = none
  let failureName: string | none = none
  if parser.check(TokenType.Else) {
    if !allowElse {
      parser.fail("A 'try' binding cannot have an 'else' block; use 'try' to propagate the failure or 'name := expr else { ... }' to handle it")
    }
    parser.advance()
    if parser.check(TokenType.Identifier) && parser.peek(1).kind == TokenType.LeftBrace {
      failureName = parser.text(parser.advance())
    }
    else_ = parseBlock(parser)
  }
  parser.consumeSemicolon()
  return ImmutableBinding { kind: "immutable-binding", name, type_: typeValue, value, exported: false, else_, failureName, span: parser.span(start) }
}
