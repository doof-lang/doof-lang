import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { discardDiagnosticsSince, typeArgumentArityMessage, typeError } from "./checker-common"
import { CheckerState } from "./checker-state"
import { SourceFile } from "./semantic"

export function testEditorCheckerCommonRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}

export function testTypeArgumentArityMessagePluralizesExpectedCount(): none {
  Assert.equal(typeArgumentArityMessage("Box", 1, 2), "Box requires 1 type argument; received 2")
  Assert.equal(typeArgumentArityMessage("Generic call", 2, 0), "Generic call requires 2 type arguments; received 0")
  Assert.equal(typeArgumentArityMessage("Pair", 0, 1), "Pair requires 0 type arguments; received 1")
}

export function testDiscardDiagnosticsSinceKeepsEarlierDiagnostics(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function main(): none {}" }]).analyze("/main.do")
  state := CheckerState { result: analysis, info: analysis.modules[0] }
  span := analysis.modules[0].program.span
  typeError(state, "kept", span)
  mark := state.diagnostics.length
  typeError(state, "speculative one", span)
  typeError(state, "speculative two", span)
  discardDiagnosticsSince(state, mark)
  Assert.equal(state.diagnostics.length, 1)
  Assert.equal(state.diagnostics[0].message, "kept")
  // A mark at or past the end leaves the list untouched.
  discardDiagnosticsSince(state, 5)
  Assert.equal(state.diagnostics.length, 1)
}
