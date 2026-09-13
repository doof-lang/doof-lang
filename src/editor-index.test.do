import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { createEditorIndex } from "./editor-index"
import { queryEditor } from "./editor-query"

export function testEditorIndexFocusKeepsImportedMemberCompletionAndDefinition(): none {
  source := "import { Tool } from \"./dep\"\nfunction main(): none { tool := Tool {}; tool.ru }"
  frontend := editorAnalysis([
    EditorSource { path: "/main.do", source },
    EditorSource { path: "/dep.do", source: "export class Tool { run(): string => \"done\" }" },
  ], "/main.do")
  index := createEditorIndex(frontend, ["/main.do"])
  for occurrence of index.occurrences { EditorAssert.equal(occurrence.module, "/main.do") }
  result := queryEditor(index, "completion", "/main.do", source.indexOf("tool.ru") + 7, source.substring(0, source.indexOf("tool.ru") + 7))
  let found = false
  for item of result.items { if item.label == "run" { found = true; EditorAssert.stringContains(item.detail, "string") } }
  EditorAssert.isTrue(found)
  definition := queryEditor(index, "definition", "/main.do", source.indexOf("Tool") + 1)
  EditorAssert.equal(definition.items.length, 1)
  EditorAssert.equal(definition.items[0].definitionModule, "/dep.do")
  EditorAssert.isTrue(definition.items[0].definitionEnd > definition.items[0].definitionStart)
}

export function testEditorIndexPreservesExplicitImportAliasDuringRename(): none {
  source := "import { value as local } from \"./dep\"\nfunction main(): int => local()"
  index := createEditorIndex(editorAnalysis([
    EditorSource { path: "/main.do", source },
    EditorSource { path: "/dep.do", source: "export function value(): int => 42" },
  ], "/main.do"))
  result := queryEditor(index, "rename", "/main.do", source.indexOf("local()") + 1, "renamed")
  EditorAssert.equal(result.error, "")
  EditorAssert.equal(result.edits.length, 2)
  for edit of result.edits { EditorAssert.equal(edit.module, "/main.do") }
}

export function testEditorIndexRenamesReexportAliasWithoutChangingOrigin(): none {
  source := "import { publicValue } from \"./barrel\"\nfunction main(): int => publicValue()"
  index := createEditorIndex(editorAnalysis([
    EditorSource { path: "/main.do", source },
    EditorSource { path: "/barrel.do", source: "export { value as publicValue } from \"./dep\"" },
    EditorSource { path: "/dep.do", source: "export function value(): int => 42" },
  ], "/main.do"))
  result := queryEditor(index, "rename", "/main.do", source.indexOf("publicValue()") + 1, "renamed")
  EditorAssert.equal(result.error, "")
  EditorAssert.equal(result.edits.length, 3)
  for edit of result.edits { EditorAssert.isTrue(edit.module != "/dep.do") }
}
