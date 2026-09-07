import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { createEditorIndex } from "./editor-index"
import { queryEditor } from "./editor-query"
import { autoImportEdits } from "./editor-autoimport"
import { SourceFile } from "./semantic"

export function testEditorAutoImportIncludesStdlibAndRechecksInsertedImport(): none {
  source := "function main(): int => clamp(42, 0, 100)"
  let sources = [SourceFile { path: "/main.do", source }, SourceFile { path: "/std/math/index.do", source: "export function clamp(value: int, low: int, high: int): int => value" }]
  index := createEditorIndex(analyzeEditor(sources, "/main.do"))
  offset := source.indexOf("clamp") + 3
  completion := queryEditor(index, "completion", "/main.do", offset, source.substring(0, offset))
  let found = false
  for item of completion.items { if item.label == "clamp" && item.importModule == "/std/math/index.do" { found = true } }
  Assert.isTrue(found)
  result := autoImportEdits(index, "/main.do", "/std/math/index.do", "clamp", source)
  Assert.equal(result.edits.length, 1)
  Assert.equal(result.edits[0].text, "import { clamp } from \"std/math\"\n")
  updated := result.edits[0].text + source
  Assert.equal(analyzeEditor([SourceFile { path: "/main.do", source: updated }, sources[1]], "/main.do").diagnostics.length, 0)
}

export function testEditorAutoImportMergesExistingImportAndAvoidsCollisions(): none {
  source := "import { first } from \"./dep\"\r\nfunction main(): int => second()"
  index := createEditorIndex(analyzeEditor([SourceFile { path: "/main.do", source }, SourceFile { path: "/dep.do", source: "export function first(): int => 1\nexport function second(): int => 2" }], "/main.do"))
  result := autoImportEdits(index, "/main.do", "/dep.do", "second", source)
  Assert.equal(result.edits.length, 1)
  Assert.equal(result.edits[0].start, source.indexOf("first") + 5)
  Assert.equal(result.edits[0].text, ", second")
  Assert.equal(autoImportEdits(index, "/main.do", "/dep.do", "first", source).edits.length, 0)
  collision := autoImportEdits(index, "/main.do", "/dep.do", "second", "function second(): int => 0")
  Assert.isTrue(collision.error != "")
}

export function testEditorAutoImportOffersAmbiguousSourcesAndPreservesShebang(): none {
  source := "#!/usr/bin/env doof\r\nfunction main(): int => value()"
  index := createEditorIndex(analyzeEditor([SourceFile { path: "/main.do", source }, SourceFile { path: "/one.do", source: "export function value(): int => 1" }, SourceFile { path: "/two.do", source: "export function value(): int => 2" }], "/main.do"))
  offset := source.indexOf("value()") + 3
  completion := queryEditor(index, "completion", "/main.do", offset, source.substring(0, offset))
  let choices = 0
  for item of completion.items { if item.label == "value" && item.importModule != "" { choices += 1 } }
  Assert.equal(choices, 2)
  edits := autoImportEdits(index, "/main.do", "/two.do", "value", source).edits
  Assert.equal(edits[0].start, source.indexOf("\n") + 1)
  Assert.equal(edits[0].text, "import { value } from \"./two\"\r\n")
}
