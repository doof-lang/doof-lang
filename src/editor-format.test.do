import { Assert } from "std/assert"
import { formatEditorSource } from "./editor-format"

export function testEditorFormatterPreservesLiteralAndCommentContents(): none {
  source := "function main(): none {\nprintln(\"hello\") // keep this\n}"
  result := formatEditorSource(source, "/main.do")
  Assert.equal(result.error, "")
  Assert.equal(result.edits.length, 1)
  Assert.equal(result.edits[0].text, "  ")
  formatted := source.substring(0, result.edits[0].start) + result.edits[0].text + source.substring(result.edits[0].end, source.length)
  Assert.equal(formatEditorSource(formatted, "/main.do").edits.length, 0)
  Assert.equal(formatEditorSource("function main( {", "/main.do").edits.length, 0)
}
