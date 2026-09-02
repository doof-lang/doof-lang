// Expression and literal parsing for the Doof parser.

import type { Parser } from "./parser"
import { Token, TokenType, charTokenValue, tokenValue } from "./lexer"
import {
  Parameter, Identifier, CallArgument, ObjectProperty,
  SourceSpan, AstLocation, AssignmentExpression, BinaryExpression,
  UnaryExpression, MemberExpression, IndexExpression, CallExpression,
  IntLiteral, LongLiteral, FloatLiteral, DoubleLiteral, ArrayLiteral,
  StringLiteral, CharLiteral, BoolLiteral, NoneLiteral,
  ThisExpression, CallerExpression, IfExpression, LambdaExpression,
  TupleLiteral, ObjectLiteral, ConstructExpression, DotShorthand,
  AsyncExpression, RetireExpression, ActorCreationExpression,
  AsExpression, CatchExpression,
} from "./ast"
import type { Expression, TypeAnnotation } from "./ast"

export function parseExpression(parser: Parser): Expression { return parseAssignment(parser) }

function parseAssignment(parser: Parser): Expression {
  let left = parseNullCoalescing(parser)
  if isAssignmentOperator(parser, parser.current().kind) {
    start := left.span.start
    operator := operatorText(parser, parser.advance())
    right := parseAssignment(parser)
    return AssignmentExpression { kind: "assignment-expression", operator, target: left, value: right, span: SourceSpan { start, end: right.span.end } }
  }
  return left
}

function parseNullCoalescing(parser: Parser): Expression {
  left := parseLogicalOr(parser)
  if !parser.match(TokenType.QuestionQuestion) { return left }
  right := parseNullCoalescing(parser)
  return BinaryExpression {
    kind: "binary-expression", operator: "??", left, right,
    span: SourceSpan { start: left.span.start, end: right.span.end },
  }
}
function parseLogicalOr(parser: Parser): Expression { return parseBinaryLevel(parser, 1) }
function parseLogicalAnd(parser: Parser): Expression { return parseBinaryLevel(parser, 2) }
function parseBitwiseOr(parser: Parser): Expression { return parseBinaryLevel(parser, 3) }
function parseBitwiseXor(parser: Parser): Expression { return parseBinaryLevel(parser, 4) }
function parseBitwiseAnd(parser: Parser): Expression { return parseBinaryLevel(parser, 5) }
function parseEquality(parser: Parser): Expression { return parseBinaryLevel(parser, 6) }
function parseComparison(parser: Parser): Expression { return parseBinaryLevel(parser, 7) }

function parseShift(parser: Parser): Expression {
  let left = parseRange(parser)
  while parser.check(TokenType.LessLess) || parser.check(TokenType.GreaterGreater) || parser.check(TokenType.GreaterGreaterGreater) {
    operator := operatorText(parser, parser.advance())
    right := parseAdditive(parser)
    left = BinaryExpression { kind: "binary-expression", operator, left, right, span: SourceSpan { start: left.span.start, end: right.span.end } }
  }
  return left
}

export function parseAdditive(parser: Parser): Expression { return parseBinaryLevel(parser, 8) }
function parseMultiplicative(parser: Parser): Expression { return parseBinaryLevel(parser, 9) }

function parseRange(parser: Parser): Expression {
  let left = parseAdditive(parser)
  if parser.check(TokenType.DotDot) || parser.check(TokenType.DotDotLess) {
    operator := operatorText(parser, parser.advance())
    right := parseAdditive(parser)
    return BinaryExpression { kind: "binary-expression", operator, left, right, span: SourceSpan { start: left.span.start, end: right.span.end } }
  }
  return left
}

function parseExponentiation(parser: Parser): Expression {
  left := parseUnary(parser)
  if parser.match(TokenType.StarStar) {
    right := parseExponentiation(parser)
    return BinaryExpression { kind: "binary-expression", operator: "**", left, right, span: SourceSpan { start: left.span.start, end: right.span.end } }
  }
  return left
}

function parseBinaryLevel(parser: Parser, level: int): Expression {
  if level == 1 { return parseBinaryLoop(parser, parseLogicalAnd(parser), [TokenType.PipePipe], 1) }
  if level == 2 { return parseBinaryLoop(parser, parseBitwiseOr(parser), [TokenType.AmpersandAmpersand], 2) }
  if level == 3 { return parseBinaryLoop(parser, parseBitwiseXor(parser), [TokenType.Pipe], 3) }
  if level == 4 { return parseBinaryLoop(parser, parseBitwiseAnd(parser), [TokenType.Caret], 4) }
  if level == 5 { return parseBinaryLoop(parser, parseEquality(parser), [TokenType.Ampersand], 5) }
  if level == 6 { return parseBinaryLoop(parser, parseComparison(parser), [TokenType.EqualEqual, TokenType.BangEqual], 6) }
  if level == 7 { return parseBinaryLoop(parser, parseShift(parser), [TokenType.Less, TokenType.LessEqual, TokenType.Greater, TokenType.GreaterEqual], 7) }
  if level == 8 { return parseBinaryLoop(parser, parseMultiplicative(parser), [TokenType.Plus, TokenType.Minus], 8) }
  return parseBinaryLoop(parser, parseExponentiation(parser), [TokenType.Star, TokenType.Slash, TokenType.Backslash, TokenType.Percent], 9)
}

function parseBinaryLoop(parser: Parser, initial: Expression, kinds: TokenType[], level: int): Expression {
  let left = initial
  while contains(kinds, parser.current().kind) {
    if parser.inTagAttribute && parser.tagAttributeDelimiterDepth == 0
        && (parser.check(TokenType.Greater) || (parser.check(TokenType.Slash) && parser.peek(1).kind == TokenType.Greater)) {
      break
    }
    operator := operatorText(parser, parser.advance())
    right := if level == 1 then parseLogicalAnd(parser) else if level == 2 then parseBitwiseOr(parser) else if level == 3 then parseBitwiseXor(parser) else if level == 4 then parseBitwiseAnd(parser) else if level == 5 then parseEquality(parser) else if level == 6 then parseComparison(parser) else if level == 7 then parseShift(parser) else if level == 8 then parseMultiplicative(parser) else parseExponentiation(parser)
    left = BinaryExpression { kind: "binary-expression", operator, left, right, span: SourceSpan { start: left.span.start, end: right.span.end } }
  }
  return left
}

function contains(values: TokenType[], value: TokenType): bool {
  for item of values { if item == value { return true } }
  return false
}

export isolated function parseUnary(parser: Parser): Expression {
  // The positive magnitude of int.min is one greater than int.max, so parsing
  // it as an IntLiteral first would wrap before unary negation is represented.
  // Fold this boundary spelling while its magnitude can still be read as long.
  if parser.check(TokenType.Minus) && parser.peek(1).kind == TokenType.IntLiteral
      && parseLongValue(parser, parser.text(parser.peek(1))) == 2147483648L {
    start := parser.location()
    parser.advance()
    value := int(-parseLongValue(parser, parser.text(parser.advance())))
    return IntLiteral { kind: "int-literal", value, span: parser.span(start) }
  }
  if parser.check(TokenType.Identifier) && (parser.text(parser.current()) == "try!" || parser.text(parser.current()) == "try?") {
    start := parser.location()
    operator := parser.text(parser.advance())
    operand := parseUnary(parser)
    return UnaryExpression { kind: "unary-expression", operator, operand, prefix: true, span: SourceSpan { start, end: operand.span.end } }
  }
  if parser.check(TokenType.Try) {
    start := parser.location()
    parser.advance()
    let operator = "try"
    if parser.match(TokenType.Bang) {
      operator = "try!"
    } else if parser.check(TokenType.Identifier) && parser.text(parser.current()) == "?" {
      parser.advance()
      operator = "try?"
    }
    operand := parseUnary(parser)
    return UnaryExpression { kind: "unary-expression", operator, operand, prefix: true, span: SourceSpan { start, end: operand.span.end } }
  }
  if parser.check(TokenType.Bang) || parser.check(TokenType.Minus) || parser.check(TokenType.Plus) || parser.check(TokenType.Tilde) {
    start := parser.location()
    operator := operatorText(parser, parser.advance())
    operand := parseUnary(parser)
    return UnaryExpression { kind: "unary-expression", operator, operand, prefix: true, span: SourceSpan { start, end: operand.span.end } }
  }
  if parser.check(TokenType.Async) {
    start := parser.location()
    parser.advance()
    if parser.check(TokenType.LeftBrace) {
      block := parser.parseBlock()
      return AsyncExpression { kind: "async-expression", expression: block, span: SourceSpan { start, end: block.span.end } }
    }
    expression := parsePostfix(parser)
    return makeAsyncExpression(expression, start)
  }
  if parser.check(TokenType.Retire) {
    start := parser.location()
    parser.advance()
    actor := parseUnary(parser)
    return RetireExpression { kind: "retire-expression", actor, span: SourceSpan { start, end: actor.span.end } }
  }
  return parseAs(parser)
}

function parseAs(parser: Parser): Expression {
  let expression = parsePostfix(parser)
  while parser.check(TokenType.As) && parser.sameLineAsPrevious() {
    start := expression.span.start
    parser.advance()
    targetType := parser.parseTypeAnnotation()
    expression = AsExpression {
      kind: "as-expression", expression, targetType,
      span: SourceSpan { start, end: targetType.span.end },
    }
  }
  return expression
}

// Keep the Expression alias conversion at a typed function boundary so the
// generated C++ promotes its flattened variant into Expression | Block.
function makeAsyncExpression(expression: Expression, start: AstLocation): AsyncExpression {
  return AsyncExpression { kind: "async-expression", expression: expression, span: SourceSpan { start, end: expression.span.end } }
}

function parseIfExpression(parser: Parser): Expression {
  start := parser.location()
  parser.expect(TokenType.If)
  condition := parser.parseExpression()
  parser.expect(TokenType.Then)
  thenValue := parser.parseExpression()
  parser.expect(TokenType.Else)
  elseValue := parser.parseExpression()
  return IfExpression { kind: "if-expression", condition, then_: thenValue, else_: elseValue, span: parser.span(start) }
}

isolated function parsePostfix(parser: Parser): Expression {
  let expression = parsePrimary(parser)
  let typeArgs: TypeAnnotation[] = []
  while true {
    if parser.check(TokenType.Less) && looksLikeGenericTypeArguments(parser) {
      typeArgs = parseGenericCallTypeArguments(parser)
    } else if parser.check(TokenType.Dot) || parser.check(TokenType.QuestionDot) || parser.check(TokenType.BangDot) {
      optional := parser.check(TokenType.QuestionDot)
      force := parser.check(TokenType.BangDot)
      parser.advance()
      property := parser.text(parser.expect(TokenType.Identifier, "Expected member name"))
      expression = MemberExpression { kind: "member-expression", object: expression, property, optional, force, span: SourceSpan { start: expression.span.start, end: parser.previousEnd() } }
      typeArgs = []
    } else if (parser.check(TokenType.LeftBracket) || parser.check(TokenType.QuestionBracket)) && parser.sameLineAsPrevious() {
      optional := parser.check(TokenType.QuestionBracket)
      parser.advance()
      index := parser.parseExpression()
      parser.expect(TokenType.RightBracket)
      expression = IndexExpression { kind: "index-expression", object: expression, index, optional, span: SourceSpan { start: expression.span.start, end: parser.previousEnd() } }
    } else if parser.check(TokenType.LeftParen) && parser.sameLineAsPrevious() {
      expression = parseCall(parser, expression, typeArgs)
      typeArgs = []
    } else if parser.check(TokenType.LeftBrace) && parser.immediatelyAfterPrevious() {
      expression = parseNamedCall(parser, expression, typeArgs)
      typeArgs = []
    } else if parser.check(TokenType.Bang) && parser.sameLineAsPrevious() {
      parser.advance()
      expression = UnaryExpression { kind: "non-null-assertion", operator: "!", operand: expression, prefix: false, span: SourceSpan { start: expression.span.start, end: parser.previousEnd() } }
    } else {
      break
    }
  }
  return expression
}

function parseCall(parser: Parser, callee: Expression, typeArgs: TypeAnnotation[] = []): Expression {
  parser.expect(TokenType.LeftParen)
  let args: CallArgument[] = []
  while !parser.check(TokenType.RightParen) && !parser.atEnd() {
    start := parser.location()
    value := parser.parseExpression()
    args.push(CallArgument { name: none, value, span: parser.span(start) })
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(TokenType.RightParen)
  return CallExpression { kind: "call-expression", callee, args, typeArgs, span: SourceSpan { start: callee.span.start, end: parser.previousEnd() } }
}

function parseNamedCall(parser: Parser, callee: Expression, typeArgs: TypeAnnotation[] = []): Expression {
  parser.expect(TokenType.LeftBrace)
  let args: CallArgument[] = []
  while !parser.check(TokenType.RightBrace) && !parser.atEnd() {
    start := parser.location()
    name := parser.text(parser.expect(TokenType.Identifier))
    let value: Expression = Identifier { kind: "identifier", name, span: parser.span(start) }
    if parser.match(TokenType.Colon) { value = parser.parseExpression() }
    args.push(CallArgument { name, value, span: parser.span(start) })
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(TokenType.RightBrace)
  return CallExpression { kind: "call-expression", callee, args, typeArgs, span: SourceSpan { start: callee.span.start, end: parser.previousEnd() } }
}

isolated function parsePrimary(parser: Parser): Expression {
  start := parser.location()
  if parser.check(TokenType.IntLiteral) {
    value := parseIntValue(parser, parser.text(parser.advance()))
    return IntLiteral { kind: "int-literal", value, span: parser.span(start) }
  }
  if parser.check(TokenType.LongLiteral) {
    value := parseLongValue(parser, parser.text(parser.advance()))
    return LongLiteral { kind: "long-literal", value, span: parser.span(start) }
  }
  if parser.check(TokenType.FloatLiteral) {
    raw := parser.text(parser.advance()).replaceAll("f", "").replaceAll("F", "")
    value := float(parseDoubleValue(parser, raw))
    return FloatLiteral { kind: "float-literal", value, raw, span: parser.span(start) }
  }
  if parser.check(TokenType.DoubleLiteral) {
    raw := parser.text(parser.advance())
    value := parseDoubleValue(parser, raw)
    return DoubleLiteral { kind: "double-literal", value, raw, span: parser.span(start) }
  }
  if parser.check(TokenType.StringLiteral) || parser.check(TokenType.TemplateLiteralStart) {
    return parseStringLiteral(parser)
  }
  if parser.check(TokenType.CharLiteral) {
    token := parser.advance()
    value := charTokenValue(token, parser.source)
    return CharLiteral { kind: "char-literal", value, span: parser.span(start) }
  }
  if parser.match(TokenType.True) { return BoolLiteral { kind: "bool-literal", value: true, span: parser.span(start) } }
  if parser.match(TokenType.False) { return BoolLiteral { kind: "bool-literal", value: false, span: parser.span(start) } }
  if parser.match(TokenType.None) { return NoneLiteral { kind: "none-literal", sourceSpelling: "none", span: parser.span(start) } }
  if parser.match(TokenType.Null) { return NoneLiteral { kind: "none-literal", sourceSpelling: "null", span: parser.span(start) } }
  if parser.match(TokenType.This) { return ThisExpression { kind: "this-expression", span: parser.span(start) } }
  if parser.match(TokenType.CallerIntrinsic) { return CallerExpression { kind: "caller-expression", span: parser.span(start) } }
  if parser.check(TokenType.If) { return parseIfExpression(parser) }
  if parser.check(TokenType.Case) { return parser.parseCaseExpression() }
  if parser.check(TokenType.Catch) { return parseCatchExpression(parser) }
  if parser.check(TokenType.Arrow) { return parseParameterlessLambda(parser) }
  if parser.check(TokenType.Readonly) && parser.peek(1).kind == TokenType.LeftBracket {
    parser.advance()
    array := parseArrayLiteral(parser)
    array.readonly_ = true
    return array
  }
  if parser.check(TokenType.LeftBracket) { return parseArrayLiteral(parser) }
  if parser.check(TokenType.LeftParen) { return parseParenExpression(parser) }
  if parser.check(TokenType.LeftBrace) { return parseObjectLiteral(parser) }
  if parser.check(TokenType.TagOpen) { return parseTagCall(parser) }
  if parser.check(TokenType.Dot) && parser.peek(1).kind == TokenType.Identifier {
    parser.advance()
    return DotShorthand { kind: "dot-shorthand", name: parser.text(parser.expect(TokenType.Identifier)), span: parser.span(start) }
  }
  if parser.check(TokenType.Identifier) {
    name := parser.text(parser.advance())
    identifierSpan := parser.span(start)
    if name == "Actor" && parser.check(TokenType.Less) {
      parser.advance()
      className := parser.text(parser.expect(TokenType.Identifier, "Expected actor class name"))
      parser.expect(TokenType.Greater)
      parser.expect(TokenType.LeftParen)
      let args: Expression[] = []
      while !parser.check(TokenType.RightParen) && !parser.atEnd() {
        args.push(parser.parseExpression())
        if !parser.match(TokenType.Comma) { break }
      }
      parser.expect(TokenType.RightParen)
      return ActorCreationExpression { kind: "actor-creation-expression", className, args, span: parser.span(start) }
    }
    if parser.check(TokenType.Dot) {
      parser.advance()
      property := parser.text(parser.expect(TokenType.Identifier, "Expected member name"))
      return MemberExpression { kind: "member-expression", object: Identifier { kind: "identifier", name, span: identifierSpan }, property, optional: false, force: false, span: parser.span(start) }
    }
    let typeArgs: TypeAnnotation[] = []
    if startsWithUppercase(name) && parser.check(TokenType.Less) && looksLikeGenericTypeArguments(parser) {
      parser.advance()
      while !parser.check(TokenType.Greater) && !parser.atEnd() {
        typeArgs.push(parser.parseTypeAnnotation())
        if !parser.match(TokenType.Comma) { break }
      }
      parser.expect(TokenType.Greater)
    }
    if parser.check(TokenType.LeftBrace) && startsWithUppercase(name) && !parser.inForIterable && looksLikeConstruction(parser) {
      return parseConstruction(parser, start, name, typeArgs)
    }
    return Identifier { kind: "identifier", name, span: parser.span(start) }
  }
  parser.fail("Expected an expression")
  return NoneLiteral { kind: "none-literal", span: parser.span(start) }
}

function parseTagCall(parser: Parser): Expression {
  start := parser.location()
  parser.expect(TokenType.TagOpen)
  calleeStart := parser.location()
  firstName := parser.text(parser.expect(TokenType.Identifier, "Expected callable name after '<'"))
  let closingName = firstName
  let callee: Expression = Identifier { kind: "identifier", name: firstName, span: parser.span(calleeStart) }
  while parser.match(TokenType.Dot) {
    memberName := parser.text(parser.expect(TokenType.Identifier, "Expected member name in tag"))
    closingName = closingName + "." + memberName
    callee = MemberExpression { kind: "member-expression", object: callee, property: memberName, optional: false, force: false, span: SourceSpan { start: calleeStart, end: parser.previousEnd() } }
  }

  let typeArgs: TypeAnnotation[] = []
  if parser.check(TokenType.Less) { typeArgs = parseGenericCallTypeArguments(parser) }
  let args: CallArgument[] = []
  let attributeNames: string[] = []
  while !parser.check(TokenType.Greater) && !parser.check(TokenType.Slash) && !parser.atEnd() {
    attributeStart := parser.location()
    name := parser.text(parser.expect(TokenType.Identifier, "Expected tag attribute name"))
    if stringArrayContains(attributeNames, name) { parser.fail("Duplicate tag attribute '" + name + "'") }
    attributeNames.push(name)
    let value: Expression = NoneLiteral { kind: "none-literal", span: parser.locationSpan() }
    if parser.check(TokenType.Arrow) {
      previousInTagAttribute := parser.inTagAttribute
      previousTagAttributeDelimiterDepth := parser.tagAttributeDelimiterDepth
      parser.inTagAttribute = true
      parser.tagAttributeDelimiterDepth = 0
      value = parser.parseExpression()
      parser.inTagAttribute = previousInTagAttribute
      parser.tagAttributeDelimiterDepth = previousTagAttributeDelimiterDepth
    } else {
      parser.expect(TokenType.Equal, "Expected '=' or '=>' after tag attribute '" + name + "'")
      value = parseTagAttributeValue(parser, name)
    }
    args.push(CallArgument { name, value, span: parser.span(attributeStart) })
  }

  if parser.match(TokenType.Slash) {
    parser.expect(TokenType.Greater, "Expected '>' after '/' in self-closing tag")
    return CallExpression { kind: "call-expression", callee, args, typeArgs, span: parser.span(start) }
  }
  parser.expect(TokenType.Greater, "Expected '>' after tag attributes")

  let children: Expression[] = []
  while !(parser.check(TokenType.Less) && parser.peek(1).kind == TokenType.Slash) && !parser.atEnd() {
    if parser.check(TokenType.TagText) {
      textStart := parser.location()
      value := normalizeTagText(parser.text(parser.advance()))
      if value != "" { children.push(StringLiteral { kind: "string-literal", value, parts: [value], interpolations: [], span: parser.span(textStart) }) }
    } else if parser.match(TokenType.LeftBrace) {
      children.push(parser.parseExpression())
      parser.expect(TokenType.RightBrace, "Expected '}' after tag child expression")
    } else if parser.check(TokenType.TagOpen) {
      children.push(parseTagCall(parser))
    } else {
      parser.fail("Expected tag text, child expression, nested tag, or closing tag")
    }
  }
  if parser.atEnd() { parser.fail("Unterminated tag '<" + closingName + ">'") }
  parser.expect(TokenType.Less)
  parser.expect(TokenType.Slash)
  closeStart := parser.location()
  let actualClosingName = parser.text(parser.expect(TokenType.Identifier, "Expected closing tag name"))
  while parser.match(TokenType.Dot) {
    actualClosingName = actualClosingName + "." + parser.text(parser.expect(TokenType.Identifier, "Expected member name in closing tag"))
  }
  if actualClosingName != closingName { parser.fail("Closing tag '</" + actualClosingName + ">' does not match '<" + closingName + ">' ") }
  parser.expect(TokenType.Greater, "Expected '>' after closing tag")

  if children.length > 0 {
    if stringArrayContains(attributeNames, "children") { parser.fail("Tag cannot use both a 'children' attribute and nested content") }
    childrenValue := ArrayLiteral { kind: "array-literal", elements: children, readonly_: false, span: SourceSpan { start: closeStart, end: parser.previousEnd() } }
    args.push(CallArgument { name: "children", value: childrenValue, span: childrenValue.span })
  }
  return CallExpression { kind: "call-expression", callee, args, typeArgs, span: parser.span(start) }
}

function parseTagAttributeValue(parser: Parser, name: string): Expression {
  if parser.match(TokenType.LeftBrace) {
    value := parser.parseExpression()
    parser.expect(TokenType.RightBrace, "Expected '}' after tag attribute '" + name + "'")
    return value
  }
  if parser.check(TokenType.StringLiteral) || parser.check(TokenType.CharLiteral)
      || parser.check(TokenType.IntLiteral) || parser.check(TokenType.LongLiteral)
      || parser.check(TokenType.FloatLiteral) || parser.check(TokenType.DoubleLiteral)
      || parser.check(TokenType.True) || parser.check(TokenType.False)
      || parser.check(TokenType.None) || parser.check(TokenType.Null)
      || (parser.check(TokenType.Minus) && isNumericLiteralToken(parser.peek(1).kind)) {
    return parseUnary(parser)
  }
  parser.fail("Tag attribute '" + name + "' requires a scalar literal or '{expression}'")
  return NoneLiteral { kind: "none-literal", span: parser.locationSpan() }
}

function isNumericLiteralToken(kind: TokenType): bool {
  return kind == TokenType.IntLiteral || kind == TokenType.LongLiteral || kind == TokenType.FloatLiteral || kind == TokenType.DoubleLiteral
}

function stringArrayContains(values: string[], value: string): bool {
  for item of values { if item == value { return true } }
  return false
}

function normalizeTagText(raw: string): string {
  lines := raw.replaceAll("\r\n", "\n").replaceAll("\r", "\n").split("\n")
  let result = ""
  for i of 0..<lines.length {
    let line = lines[i]
    if i > 0 { line = line.trimStart() }
    if i + 1 < lines.length { line = line.trimEnd() }
    if line == "" { continue }
    if result != "" && i > 0 { result = result + " " }
    result = result + line
  }
  return result
}

function parseCatchExpression(parser: Parser): Expression {
  start := parser.location()
  parser.expect(TokenType.Catch)
  body := parser.parseBlock()
  return CatchExpression { body, span: parser.span(start) }
}

function parseGenericCallTypeArguments(parser: Parser): TypeAnnotation[] {
  let typeArgs: TypeAnnotation[] = []
  parser.expect(TokenType.Less)
  while !parser.check(TokenType.Greater) && !parser.atEnd() {
    typeArgs.push(parser.parseTypeAnnotation())
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(TokenType.Greater)
  return typeArgs
}

function parseStringLiteral(parser: Parser): Expression {
  start := parser.location()
  let parts: string[] = []
  let interpolations: Expression[] = []
  if parser.check(TokenType.StringLiteral) {
    value := tokenValue(parser.advance(), parser.source)
    parts.push(value)
    return StringLiteral { kind: "string-literal", value, parts, interpolations, span: parser.span(start) }
  }
  let value = ""
  raw := tokenValue(parser.expect(TokenType.TemplateLiteralStart), parser.source)
  parts.push(raw)
  value = value + raw
  expression := parser.parseExpression()
  interpolations.push(expression)
  parts.push("<expression>")
  value = value + "<expression>"
  while parser.check(TokenType.TemplateLiteralMiddle) {
    raw := tokenValue(parser.advance(), parser.source)
    parts.push(raw)
    value = value + raw
    expression := parser.parseExpression()
    interpolations.push(expression)
    parts.push("<expression>")
    value = value + "<expression>"
  }
  endRaw := tokenValue(parser.expect(TokenType.TemplateLiteralEnd, "Expected end of string interpolation"), parser.source)
  parts.push(endRaw)
  value = value + endRaw
  return StringLiteral { kind: "string-literal", value, parts, interpolations, span: parser.span(start) }
}

function parseArrayLiteral(parser: Parser): ArrayLiteral {
  start := parser.location()
  parser.expect(TokenType.LeftBracket)
  let elements: Expression[] = []
  while !parser.check(TokenType.RightBracket) && !parser.atEnd() {
    elements.push(parser.parseExpression())
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(TokenType.RightBracket)
  return ArrayLiteral { kind: "array-literal", elements, readonly_: false, span: parser.span(start) }
}

function parseParenExpression(parser: Parser): Expression {
  start := parser.location()
  if looksLikeParenthesizedLambda(parser) {
    parser.expect(TokenType.LeftParen)
    params := parseLambdaParameters(parser)
    parser.expect(TokenType.RightParen)
    return finishLambda(parser, params, start)
  }
  parser.expect(TokenType.LeftParen)
  if parser.check(TokenType.RightParen) {
    parser.advance()
    return TupleLiteral { kind: "tuple-literal", elements: [], span: parser.span(start) }
  }
  first := parser.parseExpression()
  if parser.match(TokenType.Comma) {
    let elements: Expression[] = [first]
    while !parser.check(TokenType.RightParen) && !parser.atEnd() {
      elements.push(parser.parseExpression())
      if !parser.match(TokenType.Comma) { break }
    }
    parser.expect(TokenType.RightParen)
    return TupleLiteral { kind: "tuple-literal", elements, span: parser.span(start) }
  }
  parser.expect(TokenType.RightParen)
  return first
}

// A colon inside the parameter list belongs to a lambda parameter, not to a
// parenthesized expression. Scan to the matching close before committing to
// either grammar so typed, untyped, and explicit-return lambdas share one path.
function looksLikeParenthesizedLambda(parser: Parser): bool {
  let depth = 0
  let offset = 0
  while true {
    token := parser.peek(offset)
    if token.kind == TokenType.EndOfFile { return false }
    if token.kind == TokenType.LeftParen {
      depth = depth + 1
    } else if token.kind == TokenType.RightParen {
      depth = depth - 1
      if depth == 0 {
        after := parser.peek(offset + 1).kind
        return after == TokenType.Arrow || after == TokenType.Colon
      }
    }
    offset = offset + 1
  }
}

function parseLambdaParameters(parser: Parser): Parameter[] {
  let params: Parameter[] = []
  while !parser.check(TokenType.RightParen) && !parser.atEnd() {
    start := parser.location()
    let name = "_"
    if parser.check(TokenType.Underscore) { parser.advance() }
    else { name = parser.text(parser.expect(TokenType.Identifier, "Expected lambda parameter name or '_'")) }
    type_ := parser.parseOptionalType()
    let defaultValue: Expression | none = none
    if parser.match(TokenType.Equal) { defaultValue = parser.parseExpression() }
    params.push(Parameter { name, type_, defaultValue, span: parser.span(start) })
    if !parser.match(TokenType.Comma) { break }
  }
  return params
}

function finishLambda(parser: Parser, params: Parameter[], start: AstLocation): Expression {
  returnType := parser.parseOptionalType()
  parser.expect(TokenType.Arrow)
  if parser.check(TokenType.LeftBrace) {
    body := parser.parseBlock()
    return LambdaExpression { kind: "lambda-expression", params, returnType, body, parameterless: params.length == 0, trailing: false, span: parser.span(start) }
  }
  body := parser.parseExpression()
  return LambdaExpression { kind: "lambda-expression", params, returnType, body, parameterless: params.length == 0, trailing: false, span: parser.span(start) }
}

function parseParameterlessLambda(parser: Parser): Expression {
  start := parser.location()
  parser.expect(TokenType.Arrow)
  if parser.check(TokenType.LeftBrace) {
    body := parser.parseBlock()
    return LambdaExpression { kind: "lambda-expression", params: [], returnType: none, body: body, parameterless: true, trailing: false, span: parser.span(start) }
  }
  body := parser.parseExpression()
  return LambdaExpression { kind: "lambda-expression", params: [], returnType: none, body: body, parameterless: true, trailing: false, span: parser.span(start) }
}

function parseObjectLiteral(parser: Parser): Expression {
  start := parser.location()
  parser.expect(TokenType.LeftBrace)
  let properties: ObjectProperty[] = []
  let spread: Expression | none = none
  while !parser.check(TokenType.RightBrace) && !parser.atEnd() {
    if parser.match(TokenType.Ellipsis) {
      spread = parser.parseExpression()
    } else {
      propertyStart := parser.location()
      let name = ""
      let key: Expression | none = none
      let value: Expression | none = none
      if parser.check(TokenType.StringLiteral) {
        name = tokenValue(parser.advance(), parser.source)
        parser.expect(TokenType.Colon, "Expected ':' after string map key")
        value = parser.parseExpression()
      } else if parser.check(TokenType.Dot) && parser.peek(1).kind == TokenType.Identifier && parser.peek(2).kind == TokenType.Colon {
        key = parser.parseExpression()
        parser.expect(TokenType.Colon, "Expected ':' after map key")
        value = parser.parseExpression()
      } else if looksLikeExpressionMapKey(parser) {
        key = parser.parseExpression()
        parser.expect(TokenType.Colon, "Expected ':' after map key")
        value = parser.parseExpression()
      } else {
        name = parser.text(parser.expect(TokenType.Identifier))
        if parser.match(TokenType.Colon) { value = parser.parseExpression() }
      }
      properties.push(ObjectProperty { name, key, value, span: parser.span(propertyStart) })
    }
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(TokenType.RightBrace)
  return ObjectLiteral { kind: "object-literal", properties, spread, span: parser.span(start) }
}

function looksLikeExpressionMapKey(parser: Parser): bool {
  kind := parser.peek(0).kind
  if (kind == TokenType.IntLiteral || kind == TokenType.LongLiteral
      || kind == TokenType.FloatLiteral || kind == TokenType.DoubleLiteral
      || kind == TokenType.CharLiteral || kind == TokenType.True || kind == TokenType.False)
      && parser.peek(1).kind == TokenType.Colon {
    return true
  }
  if kind == TokenType.Minus && isNumericLiteralToken(parser.peek(1).kind) && parser.peek(2).kind == TokenType.Colon {
    return true
  }
  return kind == TokenType.Identifier && parser.peek(1).kind == TokenType.Dot
      && parser.peek(2).kind == TokenType.Identifier && parser.peek(3).kind == TokenType.Colon
}

function parseConstruction(parser: Parser, start: AstLocation, name: string, typeArgs: TypeAnnotation[]): Expression {
  parser.expect(TokenType.LeftBrace)
  let properties: ObjectProperty[] = []
  let spread: Expression | none = none
  while !parser.check(TokenType.RightBrace) && !parser.atEnd() {
    if parser.match(TokenType.Ellipsis) {
      if spread != none { parser.fail("Named construction supports only one field spread") }
      spread = parser.parseExpression()
    } else {
      propertyStart := parser.location()
      propertyName := parser.text(parser.expect(TokenType.Identifier))
      let value: Expression | none = none
      if parser.match(TokenType.Colon) { value = parser.parseExpression() }
      properties.push(ObjectProperty { name: propertyName, value, span: parser.span(propertyStart) })
    }
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(TokenType.RightBrace)
  return ConstructExpression { kind: "construct-expression", type_: name, typeArgs, args: properties, spread, named: true, span: parser.span(start) }
}

// Uppercase identifiers can also name constants at the end of a control-flow
// condition. Only consume the following block when its opening tokens have the
// shape of named construction fields.
function looksLikeConstruction(parser: Parser): bool {
  if parser.peek(1).kind == TokenType.Identifier && parser.peek(2).kind == TokenType.Colon { return true }
  if parser.peek(1).kind == TokenType.Ellipsis { return true }
  if parser.peek(1).kind == TokenType.Identifier && (parser.peek(2).kind == TokenType.Comma || parser.peek(2).kind == TokenType.RightBrace) { return true }
  return parser.peek(1).kind == TokenType.RightBrace
}

function looksLikeGenericTypeArguments(parser: Parser): bool {
  let depth = 0
  let index = 0
  while index < 64 {
    token := parser.peek(index)
    if token.kind == TokenType.Less { depth = depth + 1 }
    if token.kind == TokenType.Greater {
      depth = depth - 1
      if depth == 0 {
        next := parser.peek(index + 1).kind
        return next == TokenType.LeftBrace || next == TokenType.LeftParen
      }
    }
    if token.kind == TokenType.EndOfFile || token.kind == TokenType.Semicolon || token.kind == TokenType.LeftBrace && depth == 0 { return false }
    index = index + 1
  }
  return false
}

function parseIntValue(parser: Parser, raw: string): int {
  let base = 10
  let index = 0
  if raw.length >= 2 && raw[0] == '0' && (raw[1] == 'x' || raw[1] == 'X') {
    base = 16
    index = 2
  } else if raw.length >= 2 && raw[0] == '0' && (raw[1] == 'b' || raw[1] == 'B') {
    base = 2
    index = 2
  }
  let result = 0
  while index < raw.length {
    ch := raw[index]
    if ch == '_' { index = index + 1; continue }
    digit := digitValue(ch)
    result = result * base + digit
    index = index + 1
  }
  return result
}

function parseLongValue(parser: Parser, raw: string): long {
  clean := raw.replaceAll("L", "").replaceAll("l", "")
  let base: long = 10L
  let index = 0
  if clean.length >= 2 && clean[0] == '0' && (clean[1] == 'x' || clean[1] == 'X') {
    base = 16L
    index = 2
  } else if clean.length >= 2 && clean[0] == '0' && (clean[1] == 'b' || clean[1] == 'B') {
    base = 2L
    index = 2
  }
  let result: long = 0L
  while index < clean.length {
    ch := clean[index]
    if ch == '_' { index = index + 1; continue }
    result = result * base + long(digitValue(ch))
    index = index + 1
  }
  return result
}

function digitValue(ch: char): int {
  if ch == '0' { return 0 }
  if ch == '1' { return 1 }
  if ch == '2' { return 2 }
  if ch == '3' { return 3 }
  if ch == '4' { return 4 }
  if ch == '5' { return 5 }
  if ch == '6' { return 6 }
  if ch == '7' { return 7 }
  if ch == '8' { return 8 }
  if ch == '9' { return 9 }
  if ch == 'a' || ch == 'A' { return 10 }
  if ch == 'b' || ch == 'B' { return 11 }
  if ch == 'c' || ch == 'C' { return 12 }
  if ch == 'd' || ch == 'D' { return 13 }
  if ch == 'e' || ch == 'E' { return 14 }
  return 15
}

function parseDoubleValue(parser: Parser, raw: string): double {
  let dot = -1
  for i of 0..<raw.length { if raw[i] == '.' { dot = i; break } }
  if dot < 0 { return double(parseLongValue(parser, raw)) }
  // The integral portion of a double can exceed int even when the final
  // floating-point value is valid (for example nanoseconds-per-day).
  whole := parseLongValue(parser, raw.substring(0, dot))
  fractionText := raw.substring(dot + 1, raw.length)
  let fraction = 0.0
  let divisor = 1.0
  for i of 0..<fractionText.length {
    fraction = fraction * 10.0 + double(digitValue(fractionText[i]))
    divisor = divisor * 10.0
  }
  return double(whole) + fraction / divisor
}

function isAssignmentOperator(parser: Parser, kind: TokenType): bool {
  return kind == TokenType.Equal || kind == TokenType.PlusEqual || kind == TokenType.MinusEqual ||
    kind == TokenType.StarEqual || kind == TokenType.SlashEqual || kind == TokenType.BackslashEqual ||
    kind == TokenType.PercentEqual || kind == TokenType.StarStarEqual || kind == TokenType.AmpersandEqual ||
    kind == TokenType.PipeEqual || kind == TokenType.CaretEqual || kind == TokenType.LessLessEqual ||
    kind == TokenType.GreaterGreaterEqual || kind == TokenType.QuestionQuestionEqual
}

function startsWithUppercase(name: string): bool {
  if name.length == 0 { return false }
  return name[0] >= 'A' && name[0] <= 'Z'
}

function operatorText(parser: Parser, token: Token): string { return parser.text(token) }
