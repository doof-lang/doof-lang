// Public façade and token state for the Doof recursive-descent parser.
//
// Syntax-specific parsing lives in parser-declarations.do,
// parser-statements.do, parser-types.do, and parser-expressions.do.  Keeping
// token state here preserves the existing Parser { source }.parse() API while
// allowing each grammar area to stay independently focused.

import { Lexer, Token, TokenType, tokenValue } from "./lexer"
import {
  parseExport as parseExportImpl, parseConst as parseConstImpl,
  parseReadonly as parseReadonlyImpl, parseLet as parseLetImpl,
  parseFunction as parseFunctionImpl, parseClass as parseClassImpl,
  parseInterface as parseInterfaceImpl, parseEnum as parseEnumImpl,
  parseTypeAlias as parseTypeAliasImpl, parseImport as parseImportImpl,
  parseMockImport as parseMockImportImpl,
} from "./parser-declarations"
import {
  parseStatement as parseStatementImpl, parseBlock as parseBlockImpl,
  parseCaseExpression as parseCaseExpressionImpl,
  looksLikePattern as looksLikePatternImpl,
  parseDestructuring as parseDestructuringImpl,
  parseTryStatement as parseTryStatementImpl,
} from "./parser-statements"
import { parseOptionalType as parseOptionalTypeImpl, parseTypeAnnotation as parseTypeAnnotationImpl } from "./parser-types"
import { parseExpression as parseExpressionImpl, parseAdditive as parseAdditiveImpl, parseUnary as parseUnaryImpl } from "./parser-expressions"
import {
  Program, Block, ClassDeclaration, FunctionDeclaration, NamedType,
  Statement, Expression, TypeAnnotation, AstLocation, SourceSpan,
} from "./ast"

export class Parser {
  readonly source: string
  let tokens: Token[] = []
  let pos: int = 0
  let inForIterable: bool = false
  let inTagAttribute: bool = false
  let errorMessage: string = ""
  let errorLine: int = 0
  let errorColumn: int = 0
  let errorOffset: int = 0

  parse(): Program {
    errorMessage = ""
    errorLine = 0
    errorColumn = 0
    errorOffset = 0
    lexer := Lexer { source }
    tokens = lexer.tokenize()
    pos = 0
    start := location()
    let statements: Statement[] = []
    while !atEnd() { statements.push(parseStatement()) }
    return Program { kind: "program", statements, span: span(start) }
  }

  // Shared parser state operations are public to the focused parser modules;
  // callers should continue to use parse() or the top-level parse() function.
  current(): Token { return tokens[pos] }

  peek(offset: int = 0): Token {
    index := pos + offset
    if index >= tokens.length { return tokens[tokens.length - 1] }
    return tokens[index]
  }

  atEnd(): bool { return current().kind == TokenType.EndOfFile }

  advance(): Token {
    token := current()
    if !atEnd() { pos = pos + 1 }
    return token
  }

  check(kind: TokenType): bool { return current().kind == kind }

  match(kind: TokenType): bool {
    if !check(kind) { return false }
    advance()
    return true
  }

  expect(kind: TokenType, message: string = ""): Token {
    if check(kind) { return advance() }
    let expectedMessage = message
    if expectedMessage == "" { expectedMessage = "Expected " + expectedLabel(kind) + " before '" + currentText() + "'" }
    fail(expectedMessage)
    return current()
  }

  fail(message: string): none {
    token := current()
    errorMessage = message
    errorLine = token.line
    errorColumn = token.column
    errorOffset = token.offset
    panic("Parse error at " + string(token.line) + ":" + string(token.column) + ": " + message)
  }

  private expectedLabel(kind: TokenType): string {
    if kind == TokenType.Identifier { return "identifier" }
    if kind == TokenType.RightParen { return "')'" }
    if kind == TokenType.RightBrace { return "'}'" }
    if kind == TokenType.RightBracket { return "']'" }
    if kind == TokenType.Colon { return "':'" }
    if kind == TokenType.Equal { return "'='" }
    if kind == TokenType.Greater { return "'>'" }
    if kind == TokenType.Slash { return "'/'" }
    return "token"
  }

  text(token: Token): string { return tokenValue(token, source) }
  private currentText(): string { return text(current()) }

  location(): AstLocation {
    token := current()
    return AstLocation { line: token.line, column: token.column, offset: token.offset }
  }

  span(start: AstLocation): SourceSpan {
    previous := if pos > 0 then tokens[pos - 1] else current()
    return SourceSpan {
      start,
      end: AstLocation {
        line: previous.line,
        column: previous.column + previous.length,
        offset: previous.offset + previous.length,
      },
    }
  }

  sameLineAsPrevious(): bool {
    if pos == 0 { return false }
    return tokens[pos - 1].line == current().line
  }

  previousIs(kind: TokenType): bool {
    if pos == 0 { return false }
    return tokens[pos - 1].kind == kind
  }

  immediatelyAfterPrevious(): bool {
    if pos == 0 { return false }
    previous := tokens[pos - 1]
    return previous.offset + previous.length == current().offset
  }

  consumeSemicolon(): none { match(TokenType.Semicolon) }

  locationSpan(): SourceSpan { start := location(); return SourceSpan { start, end: start } }

  // --------------------------------------------------------------------------
  // Focused parser-module entry points
  // --------------------------------------------------------------------------

  parseStatement(): Statement { return parseStatementImpl(this) }
  parseExport(): Statement { return parseExportImpl(this) }
  parseConst(exported: bool): Statement { return parseConstImpl(this, exported) }
  parseReadonly(exported: bool): Statement { return parseReadonlyImpl(this, exported) }
  parseLet(): Statement { return parseLetImpl(this) }
  parseFunction(exported: bool, static_: bool, isolated_: bool, private_: bool, legacyMethod: bool = false): FunctionDeclaration {
    return parseFunctionImpl(this, exported, static_, isolated_, private_, legacyMethod)
  }
  parseClass(exported: bool, private_: bool): Statement { return parseClassImpl(this, exported, private_) }
  parseInterface(exported: bool): Statement { return parseInterfaceImpl(this, exported) }
  parseEnum(exported: bool): Statement { return parseEnumImpl(this, exported) }
  parseTypeAlias(exported: bool): Statement { return parseTypeAliasImpl(this, exported) }
  parseImport(): Statement { return parseImportImpl(this) }
  parseMockImport(): Statement { return parseMockImportImpl(this) }

  parseBlock(): Block { return parseBlockImpl(this) }
  parseCaseExpression(): Expression { return parseCaseExpressionImpl(this) }
  looksLikePattern(separator: TokenType): bool { return looksLikePatternImpl(this, separator) }
  parseDestructuring(shape: string, bindingKind: string, separator: TokenType): Statement {
    return parseDestructuringImpl(this, shape, bindingKind, separator)
  }
  parseTryStatement(): Statement { return parseTryStatementImpl(this) }

  parseOptionalType(): TypeAnnotation | none { return parseOptionalTypeImpl(this) }
  parseTypeAnnotation(): TypeAnnotation { return parseTypeAnnotationImpl(this) }

  parseExpression(): Expression { return parseExpressionImpl(this) }
  parseAdditive(): Expression { return parseAdditiveImpl(this) }
  parseUnary(): Expression { return parseUnaryImpl(this) }
}

export function parse(source: string): Program { return Parser { source }.parse() }
