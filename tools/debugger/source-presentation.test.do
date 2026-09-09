import { Assert } from "std/assert"
import { SourceStyle } from "std/appkit"
import { sourceHighlights, sourceIdentifiers } from "./source-presentation"

export function testSourceHighlightingUsesDoofTokensAndCommentTrivia(): none {
  source := "/* first\n second */\nfunction main(): none {\n  let message = \"工具🙂\"; let count = 41 // comment\n  println(message)\n}"
  lines := source.split("\n")
  let sawKeyword = false; let sawString = false; let sawNumber = false; let comments = 0; let sawCall = false
  for span of sourceHighlights(source) {
    text := lines[span.line-1].substring(span.start, span.start + span.length)
    if span.style == .Keyword && text == "function" { sawKeyword = true }
    if span.style == .String && text == "\"工具🙂\"" { sawString = true }
    if span.style == .Number && text == "41" { sawNumber = true }
    if span.style == .Comment { comments += 1 }
    if span.style == .Function && text == "println" { sawCall = true }
  }
  Assert.equal(sawKeyword && sawString && sawNumber && sawCall, true)
  Assert.equal(comments, 3)
}

export function testSourceHighlightingToleratesIncompleteSource(): none {
  Assert.equal(sourceHighlights("").length, 0)
  spans := sourceHighlights("let value = \"unfinished")
  Assert.equal(spans.length > 0, true)
  identifiers := sourceIdentifiers("let _count = 1 // _iterable_2\nlet text = \"_try_value_1\"")
  Assert.equal(identifiers.has("_count"), true)
  Assert.equal(identifiers.has("_iterable_2"), false)
  Assert.equal(identifiers.has("_try_value_1"), false)
}
