import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { createEditorIndex } from "./editor-index"
import { queryEditor } from "./editor-query"

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
