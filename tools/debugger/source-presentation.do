// Reuse the compiler's lexer so strings, interpolation and comments follow Doof.
import { Lexer, TokenType, tokenValue } from "../../src/lexer"
import { SourceHighlight, SourceStyle } from "std/appkit"

export function sourceHighlights(source: string): SourceHighlight[] {
  scanner := Lexer { source, retainTrivia: true }
  tokens := scanner.tokenize()
  let starts: int[] = [0]
  for i of 0..<source.length { if source[i] == '\n' { starts.push(i + 1) } }
  let result: SourceHighlight[] = []
  for index of 0..<tokens.length {
    token := tokens[index]
    let style = SourceStyle.Plain
    kind := token.kind
    if kind.value >= TokenType.Const.value && kind.value <= TokenType.Mock.value { style = .Keyword }
    if kind.value >= TokenType.IntLiteral.value && kind.value <= TokenType.DoubleLiteral.value { style = .Number }
    if kind.value >= TokenType.StringLiteral.value && kind.value <= TokenType.TemplateLiteralEnd.value { style = .String }
    if kind == .Identifier {
      name := tokenValue(token, source)
      if name.length > 0 && name[0] >= 'A' && name[0] <= 'Z' { style = .Type }
      if ["int", "long", "double", "float", "bool", "string", "char", "never"].contains(name) { style = .Type }
      if index + 1 < tokens.length && tokens[index + 1].kind == .LeftParen { style = .Function }
    }
    if style != .Plain { appendSpan(result, starts, source, token.offset, token.offset + token.length, style) }
  }
  for comment of scanner.trivia { appendSpan(result, starts, source, comment.start, comment.end, .Comment) }
  return result
}

function appendSpan(result: SourceHighlight[], starts: int[], source: string, start: int, end: int, style: SourceStyle): none {
  // Binary search the first line, then split multiline tokens at line boundaries.
  let low = 0
  let high = starts.length
  while low + 1 < high {
    middle := (low + high) \ 2
    if starts[middle] <= start { low = middle } else { high = middle }
  }
  let cursor = start
  let line = low
  while cursor < end && line < starts.length {
    limit := if line + 1 < starts.length then starts[line + 1] - 1 else source.length
    stop := if end < limit then end else limit
    if stop > cursor { result.push(SourceHighlight { line: line + 1, start: cursor - starts[line], length: stop - cursor, style }) }
    cursor = limit + 1
    line += 1
  }
}

export function sourceIdentifiers(source: string): Set<string> {
  scanner := Lexer { source }
  let result: Set<string> = []
  for token of scanner.tokenize() {
    if token.kind == .Identifier {
      name := tokenValue(token, source)
      result.add(name)
      result.add(name + "_") // C++ keyword escaping, e.g. explicit -> explicit_.
    }
  }
  return result
}
