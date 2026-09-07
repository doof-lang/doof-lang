import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { createEditorIndex } from "./editor-index"
import { missingImportFix } from "./editor-actions"
import { SourceFile } from "./semantic"

export function testEditorMissingImportRequiresUniqueExport(): none {
  let sources = [SourceFile { path: "/main.do", source: "function main(): int => value()" }, SourceFile { path: "/dep.do", source: "export function value(): int => 42" }]
  index := createEditorIndex(analyzeEditor(sources, "/main.do"))
  fix := missingImportFix(index, "/main.do", "Unknown identifier 'value'")
  Assert.equal(fix.edits.length, 1)
  Assert.equal(fix.edits[0].text, "import { value } from \"./dep\"\n")
  sources.push(SourceFile { path: "/other.do", source: "export function value(): int => 17" })
  ambiguous := createEditorIndex(analyzeEditor(sources, "/main.do"))
  Assert.equal(missingImportFix(ambiguous, "/main.do", "Unknown identifier 'value'").edits.length, 0)
}
