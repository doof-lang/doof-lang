import { EditorIndex, EditorItem, EditorResponse, editorTypeName } from "./editor-model"
import { editorModule, editorScopeAt } from "./editor-index"
import { lookup } from "./checker-symbols"
import { resolveMember } from "./checker-resolution"
import { CheckerState } from "./checker-state"
import { FunctionType, ResolvedType } from "./semantic"
import { CallExpression, AstLocation, SourceSpan } from "./ast"
import { Lexer, TokenType, tokenValue } from "./lexer"

function signatureResponse(type_: ResolvedType, module: string, offset: int, active: int): EditorResponse {
  fn := type_ as FunctionType else { return EditorResponse {} }
  let parameters: string[] = []
  for parameter of fn.params { parameters.push(parameter.name + ": " + editorTypeName(parameter.type_)) }
  return EditorResponse { activeParameter: active, items: [EditorItem { label: editorTypeName(fn), parameters, kind: "function", module, start: offset, end: offset }] }
}

export function editorSignature(index: EditorIndex, module: string, offset: int, prefix: string): EditorResponse {
  info := editorModule(index, module) else { return EditorResponse {} }
  if prefix != "" {
    tokens := Lexer { source: prefix }.tokenize()
    let position = tokens.length - 2
    let depth = 0
    let active = 0
    while position >= 0 {
      kind := tokens[position].kind
      if kind == TokenType.RightParen || kind == TokenType.RightBrace || kind == TokenType.RightBracket { depth += 1 }
      if kind == TokenType.Comma && depth == 0 { active += 1 }
      if kind == TokenType.LeftParen || kind == TokenType.LeftBrace || kind == TokenType.LeftBracket {
        if depth == 0 {
          if position == 0 || tokens[position - 1].kind != TokenType.Identifier { break }
          scope := editorScopeAt(index, module, offset) else { break }
          name := tokenValue(tokens[position - 1], prefix)
          if position >= 3 && tokens[position - 2].kind == TokenType.Dot {
            receiver := lookup(scope, tokenValue(tokens[position - 3], prefix)) else { break }
            location := AstLocation { line: 1, column: 1, offset }
            state := CheckerState { result: index.frontend.analysis, info, moduleScope: scope }
            member := resolveMember(state, receiver.type_, name, SourceSpan { start: location, end: location })
            if member.type_ != none { return signatureResponse(member.type_!, module, offset, active) }
          }
          binding := lookup(scope, name) else { break }
          return signatureResponse(binding.type_, module, offset, active)
        }
        depth -= 1
      }
      position -= 1
    }
  }
  let best: CallExpression | none = none
  for expression of info.editorExpressions {
    call := expression as CallExpression else { continue }
    if call.callee.span.end.offset > offset || call.span.end.offset < offset { continue }
    if best == none || call.span.end.offset - call.span.start.offset < best!.span.end.offset - best!.span.start.offset { best = call }
  }
  if best != none && best!.callee.resolvedType != none {
    let active = 0
    for argument of best!.args { if argument.span.end.offset < offset { active += 1 } }
    return signatureResponse(best!.callee.resolvedType!, module, offset, active)
  }
  return EditorResponse {}
}
