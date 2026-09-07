import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { createEditorIndex } from "./editor-index"
import { workspaceEditorSymbols } from "./editor-symbols"
import { SourceFile } from "./semantic"

export function testEditorWorkspaceSymbolsIncludeUnreachedDeclarations(): none {
  index := createEditorIndex(analyzeEditor([
    SourceFile { path: "/main.do", source: "function main(): int => 42" },
    SourceFile { path: "/unused.do", source: "export function other(): int => 17" },
  ], "/main.do"))
  found := workspaceEditorSymbols(index, "other")
  Assert.equal(found.length, 1)
  Assert.equal(found[0].module, "/unused.do")
  Assert.equal(workspaceEditorSymbols(index, "other").length, 1)
}
