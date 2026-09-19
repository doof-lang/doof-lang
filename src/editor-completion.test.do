import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { createEditorIndex } from "./editor-index"
import { contextualCompletion, memberCompletions, importSpecifier, builtinMemberCandidates } from "./editor-completion"
import { EditorItem } from "./editor-model"
import { SourceFile } from "./semantic"
import { Lexer, TokenType, tokenValue } from "./lexer"
import { readText } from "std/fs"

export function testEditorCompletionSeparatesStaticAndInstanceMembers(): none {
  declaration := "export class Example {\n static count: int = 1\n value: int = 2\n static create(): int => 1\n read(): int => 2\n}\n"
  for imported of [false, true] {
    header := if imported then "import { Example as Alias } from \"./example\"\n" else declaration
    name := if imported then "Alias" else "Example"
    for receiver of [name, "instance"] {
      source := header + "function main(): none {\n instance := ${name}()\n ${receiver}.\n}"
      offset := source.indexOf("${receiver}.\n") + receiver.length + 1
      index := createEditorIndex(analyzeEditor([
        SourceFile { path: "/main.do", source },
        SourceFile { path: "/example.do", source: declaration },
      ], "/main.do"))
      for contextual of [false, true] {
        let items: EditorItem[] = []
        if contextual { Assert.isTrue(contextualCompletion(index, "/main.do", offset, source.substring(0, offset), items)) }
        else { Assert.isTrue(memberCompletions(index, "/main.do", offset, items)) }
        let names: string[] = []
        for item of items { names.push(item.label) }
        readonly labels = names.cloneReadonly()
        if receiver == name {
          Assert.contains(labels, "create")
          Assert.contains(labels, "count")
          Assert.notContains(labels, "read")
          Assert.notContains(labels, "value")
          Assert.notContains(labels, "toSerialObject")
        } else {
          Assert.contains(labels, "read")
          Assert.contains(labels, "value")
          Assert.notContains(labels, "create")
          Assert.notContains(labels, "count")
          Assert.notContains(labels, "fromSerialValue")
        }
      }
    }
  }
}

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
