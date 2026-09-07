import { Assert } from "std/assert"
import { analyzeWithLoader } from "./frontend"
import { createEditorIndex } from "./editor-index"
import { queryEditor } from "./editor-query"
import { SourceFile } from "./semantic"
import { noSourceLoader } from "./resolver"
import { PhaseTimings } from "./phase-timings"

export function testEditorQueriesUseLocalBindings(): none {
  source := "function main(): int {\n  answer := 42\n  return answer\n}"
  frontend := analyzeWithLoader([SourceFile { path: "/main.do", source }], "/main.do", noSourceLoader, "executable", PhaseTimings {}, true, true)
  Assert.equal(frontend.diagnostics.length, 0)
  index := createEditorIndex(frontend)
  offset := source.indexOf("return answer") + 8
  hover := queryEditor(index, "hover", "/main.do", offset)
  Assert.equal(hover.items.length, 1)
  Assert.equal(hover.items[0].detail, "int")
  Assert.equal(hover.items[0].definitionStart, source.indexOf("answer :="))
  references := queryEditor(index, "references", "/main.do", offset)
  Assert.equal(references.items.length, 2)
  rename := queryEditor(index, "rename", "/main.do", offset, "value")
  Assert.equal(rename.error, "")
  Assert.equal(rename.edits.length, 2)
}

export function testEditorCompletionRecoversTrailingDot(): none {
  source := "function main(): none {\n  name := \"Doof\"\n  name.\n}"
  index := createEditorIndex(analyzeWithLoader([SourceFile { path: "/main.do", source }], "/main.do", noSourceLoader, "executable", PhaseTimings {}, true, true))
  result := queryEditor(index, "completion", "/main.do", source.indexOf("name.") + 5)
  let found = false
  for item of result.items { if item.label == "substring" { found = true; Assert.stringContains(item.detail, "int") } }
  Assert.isTrue(found)
}
