// Conservative formatter: canonical indentation without rewriting tokens,
// comments, literal contents, or line endings. Invalid source is never edited.
import { Parser } from "./parser"
import { Lexer, TokenType } from "./lexer"
import { EditorEdit, EditorResponse } from "./editor-model"

export function formatEditorSource(source: string, module: string, indentation: int = 2): EditorResponse {
  if indentation < 1 || indentation > 8 { return EditorResponse { error: "Indentation must be between 1 and 8 spaces." } }
  parser := Parser { source }
  parsed := catchPanic(=> parser.parse())
  program := parsed else { return EditorResponse { error: "Fix syntax errors before formatting." } }
  lexer := Lexer { source, retainTrivia: true }
  tokens := lexer.tokenize()
  if lexer.diagnostics.length > 0 { return EditorResponse { error: "Fix lexical errors before formatting." } }
  response := EditorResponse {}
  let start = 0
  let depth = 0
  let tokenIndex = 0
  while start < source.length {
    let end = start
    while end < source.length && source[end] != '\n' { end += 1 }
    let content = start
    while content < end && (source[content] == ' ' || source[content] == '\t') { content += 1 }
    let protected = false
    for trivia of lexer.trivia { if start > trivia.start && start < trivia.end { protected = true; break } }
    if tokenIndex > 0 && start < tokens[tokenIndex - 1].offset + tokens[tokenIndex - 1].length { protected = true }
    let lineDepth = depth
    if tokenIndex < tokens.length && tokens[tokenIndex].offset >= start && tokens[tokenIndex].offset < end {
      kind := tokens[tokenIndex].kind
      if kind == TokenType.RightBrace || kind == TokenType.RightBracket || kind == TokenType.RightParen { lineDepth -= 1 }
    }
    if lineDepth < 0 { lineDepth = 0 }
    if !protected && content < end && source[content] != '\r' {
      whitespace := " ".repeat(lineDepth * indentation)
      if whitespace != source.substring(start, content) { response.edits.push(EditorEdit { module, start, end: content, text: whitespace }) }
    }
    while tokenIndex < tokens.length && tokens[tokenIndex].offset < end {
      kind := tokens[tokenIndex].kind
      if kind == TokenType.LeftBrace || kind == TokenType.LeftBracket || kind == TokenType.LeftParen { depth += 1 }
      if kind == TokenType.RightBrace || kind == TokenType.RightBracket || kind == TokenType.RightParen { depth -= 1 }
      tokenIndex += 1
    }
    start = end + 1
  }
  return response
}
