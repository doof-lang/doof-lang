// Type annotation parsing for the Doof parser.

import type { Parser } from "./parser"
import { TokenType } from "./lexer"
import { AstFunctionType, ArrayType, AstLocation, FunctionTypeParam, NamedType, SourceSpan, UnionType, WeakType } from "./ast"
import type { TypeAnnotation } from "./ast"

// A `weak name: T` field qualifies its whole type, so `T` follows the same
// rules as the operand of a `weak` type prefix.
export function parseOptionalType(parser: Parser, weakField: bool = false): TypeAnnotation | none {
  if !parser.match(TokenType.Colon) { return none }
  if weakField { return parseUnionMembers(parser, true) }
  return parseTypeAnnotation(parser)
}

// `weak` prefixes a complete type and covers all of it: `weak A | none` is
// `weak (A | none)`. It cannot follow `|`, and a collection directly under it
// must be parenthesized to say which side is weak.
export function parseTypeAnnotation(parser: Parser): TypeAnnotation {
  start := parser.location()
  if !parser.match(TokenType.Weak) { return parseUnionMembers(parser, false) }
  if parser.check(TokenType.Weak) { parser.fail("'weak' qualifies a type at most once") }
  inner := parseUnionMembers(parser, true)
  return WeakType { type_: inner, span: SourceSpan { start, end: inner.span.end } }
}

function parseUnionMembers(parser: Parser, weakOperand: bool): TypeAnnotation {
  let operandStart: AstLocation | none = none
  if weakOperand { operandStart = parser.location() }
  first := parseTypeMember(parser, operandStart)
  let types: TypeAnnotation[] = [first]
  while parser.match(TokenType.Pipe) {
    if parser.check(TokenType.Weak) {
      parser.fail("'weak' must start the type and qualifies the whole union, as in 'weak (A | B)'")
    }
    types.push(parseTypeMember(parser, operandStart))
  }
  let result: TypeAnnotation = first
  if types.length > 1 { result = UnionType { kind: "union-type", types, span: SourceSpan { start: first.span.start, end: types[types.length - 1].span.end } } }
  return result
}

function parseTypeMember(parser: Parser, weakOperandStart: AstLocation | none): TypeAnnotation {
  memberStart := parser.location()
  parenthesized := parser.check(TokenType.LeftParen)
  if parser.check(TokenType.Readonly) && parser.peek(1).kind == TokenType.Weak {
    parser.fail("'readonly' cannot qualify a weak reference; write 'readonly (weak A)[]' for a readonly array of weak references")
  }
  let readonlyPrefix = parser.match(TokenType.Readonly)
  let result = parsePrimaryType(parser)
  let arraySuffix = false
  while parser.check(TokenType.LeftBracket) && parser.peek(1).kind == TokenType.RightBracket {
    start := result.span.start
    parser.advance()
    parser.advance()
    result = ArrayType { kind: "array-type", elementType: result, readonly_: readonlyPrefix, span: SourceSpan { start, end: parser.previousEnd() } }
    readonlyPrefix = false
    arraySuffix = true
  }
  if readonlyPrefix {
    case result {
      named: NamedType -> {
        if named.name == "Map" || named.name == "ReadonlyMap" {
          named.name = "ReadonlyMap"
          readonlyPrefix = false
        } else if named.name == "Set" || named.name == "ReadonlySet" {
          named.name = "ReadonlySet"
          readonlyPrefix = false
        }
      }
      _ -> { }
    }
  }
  if readonlyPrefix { parser.fail("Unexpected readonly type modifier; expected an array, Map<K, V>, or Set<T> type") }
  if weakOperandStart != none && (arraySuffix || !parenthesized) { rejectBareWeakCollection(parser, result, weakOperandStart!, memberStart) }
  return result
}

// `weak A[]` reads as either an array of weak references or a weak reference
// to an array, so a collection directly under `weak` must be parenthesized.
function rejectBareWeakCollection(parser: Parser, member: TypeAnnotation, operandStart: AstLocation, start: AstLocation): none {
  text := parser.source.substring(operandStart.offset, member.span.end.offset)
  case member {
    array: ArrayType -> {
      element := parser.source.substring(array.elementType.span.start.offset, array.elementType.span.end.offset)
      prefix := if array.readonly_ then "readonly " else ""
      parser.failAt(start, "'weak " + text + "' is ambiguous; write '" + prefix + "(weak " + element + ")[]' for an array of weak references or 'weak (" + text + ")' for a weak reference to the array")
    }
    named: NamedType -> {
      if named.name == "Map" || named.name == "ReadonlyMap" {
        parser.failAt(start, "'weak " + text + "' is ambiguous; write 'Map<K, weak V>' for weak values or 'weak (" + text + ")' for a weak reference to the map")
      } else if named.name == "Set" || named.name == "ReadonlySet" {
        parser.failAt(start, "'weak " + text + "' is ambiguous; write 'weak (" + text + ")' for a weak reference to the set")
      }
    }
    _ -> { }
  }
}

function parsePrimaryType(parser: Parser): TypeAnnotation {
  start := parser.location()
  if parser.check(TokenType.LeftParen) {
    if parser.peek(1).kind != TokenType.RightParen && !(parser.peek(1).kind == TokenType.Identifier && parser.peek(2).kind == TokenType.Colon) {
      parser.advance()
      inner := parseTypeAnnotation(parser)
      parser.expect(TokenType.RightParen)
      return inner
    }
    parser.advance()
    let params: FunctionTypeParam[] = []
    while !parser.check(TokenType.RightParen) && !parser.atEnd() {
      paramStart := parser.location()
      paramName := parser.text(parser.expect(TokenType.Identifier))
      parser.expect(TokenType.Colon)
      paramType := parseTypeAnnotation(parser)
      params.push(FunctionTypeParam { name: paramName, type_: paramType, span: parser.span(paramStart) })
      if !parser.match(TokenType.Comma) { break }
    }
    parser.expect(TokenType.RightParen)
    parser.expect(TokenType.Colon)
    returnType := parseTypeAnnotation(parser)
    return AstFunctionType { kind: "function-type", params, returnType, span: parser.span(start) }
  }
  kind := parser.current().kind
  if kind != TokenType.Identifier && kind != TokenType.None && kind != TokenType.Void && kind != TokenType.Null {
    parser.fail("Expected a type name")
  }
  name := parser.text(parser.advance())
  typeArgs: TypeAnnotation[] := if parser.check(TokenType.Less) then parseTypeArguments(parser) else []
  return NamedType { kind: "named-type", name, typeArgs, span: parser.span(start) }
}

// Parses a `<T, U>` argument list; the caller has checked for the opening `<`.
export function parseTypeArguments(parser: Parser): TypeAnnotation[] {
  parser.expect(TokenType.Less)
  let typeArgs: TypeAnnotation[] = []
  while !parser.check(TokenType.Greater) && !parser.atEnd() {
    typeArgs.push(parseTypeAnnotation(parser))
    if !parser.match(TokenType.Comma) { break }
  }
  parser.expect(TokenType.Greater)
  return typeArgs
}
