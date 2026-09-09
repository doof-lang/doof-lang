import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"

export function testEditorCheckerStateRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}

export function testBlockLambdaNestedReturnScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source:
    "function main(): none { outer := => { inner := => { return \"nested\" }\n" +
    "function named(): string { return \"named\" }\nreturn 42 }\n" +
    "other := => { return true } }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  EditorAssert.equal(result.diagnostics.length, 0)
}
