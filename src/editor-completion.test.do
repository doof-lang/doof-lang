import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { createEditorIndex } from "./editor-index"
import { contextualCompletion, importSpecifier, builtinMemberCandidates } from "./editor-completion"
import { EditorItem } from "./editor-model"
import { SourceFile } from "./semantic"
import { Lexer, TokenType, tokenValue } from "./lexer"
import { readText } from "std/fs"

export function testEditorCompletionUsesLivePrefixBeforeReanalysis(): none {
  source := "function main(): none {\n  title := \"Doof\"\n}\n"
  index := createEditorIndex(analyzeEditor([SourceFile { path: "/main.do", source }], "/main.do"))
  let items: EditorItem[] = []
  Assert.isTrue(contextualCompletion(index, "/main.do", source.indexOf("}\n"), source.substring(0, source.indexOf("}\n")) + "  title.", items))
  let found = false
  for item of items { if item.label == "substring" { found = true; Assert.stringContains(item.detail, "int") } }
  Assert.isTrue(found)
  Assert.equal(importSpecifier("/src/main.do", "/std/math/index.do"), "std/math")
  Assert.equal(importSpecifier("/src/main.do", "/lib/value.do"), "../lib/value")
}

export function testEditorCompletionBuiltinCatalogTracksResolver(): none {
  source := try! readText("src/checker-resolution.do")
  tokens := Lexer { source }.tokenize()
  candidates := builtinMemberCandidates()
  for i of 0..<tokens.length - 2 {
    if tokenValue(tokens[i], source) != "property" || tokenValue(tokens[i + 1], source) != "==" || tokens[i + 2].kind != TokenType.StringLiteral { continue }
    name := tokenValue(tokens[i + 2], source)
    let found = false
    for candidate of candidates { if candidate == name { found = true } }
    Assert.isTrue(found, "Missing completion candidate: " + name)
  }
}
