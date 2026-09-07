import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { createEditorIndex } from "./editor-index"
import { validateEditorRename } from "./editor-rename"
import { EditorResponse, EditorEdit } from "./editor-model"
import { SourceFile } from "./semantic"

export function testEditorRenameRejectsEditsThatBreakReferences(): none {
  source := "function main(): int { answer := 42; return answer }"
  index := createEditorIndex(analyzeEditor([SourceFile { path: "/main.do", source }], "/main.do"))
  start := source.indexOf("answer :=")
  result := validateEditorRename(index, EditorResponse { edits: [EditorEdit { module: "/main.do", start, end: start + 6, text: "value" }] })
  Assert.stringContains(result.error, "Rename would break")
  Assert.equal(result.edits.length, 0)
}
