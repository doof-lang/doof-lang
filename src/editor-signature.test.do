import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { createEditorIndex } from "./editor-index"
import { editorSignature } from "./editor-signature"
import { SourceFile } from "./semantic"

export function testEditorSignatureAcceptsUnfinishedLiveArguments(): none {
  source := "function add(left: int, right: int): int => left + right\nfunction main(): none {\n  println(add(1, 2))\n}"
  index := createEditorIndex(analyzeEditor([SourceFile { path: "/main.do", source }], "/main.do"))
  offset := source.indexOf("add(1")
  result := editorSignature(index, "/main.do", offset, source.substring(0, offset) + "add(1, ")
  Assert.equal(result.items.length, 1)
  Assert.equal(result.items[0].parameters.length, 2)
  Assert.equal(result.activeParameter, 1)
}
