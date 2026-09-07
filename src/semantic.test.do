import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { SemanticTypeIdentities } from "./semantic-type-identities"
import { Assert } from "std/assert"
import { Scope } from "./semantic"
import { primitive, sameType } from "./checker-types"

export function testYieldExpectationSeparateFromInference(): none {
  scope := Scope { parent: none }
  scope.yieldType = primitive("int")
  Assert.isTrue(scope.yieldExpectedType == none)
  scope.yieldExpectedType = primitive("long")
  Assert.isTrue(sameType(scope.yieldType!, primitive("int")))
}

export function testTypeLoweringMetadataDoesNotChangeSemanticEquality(): none {
  first := primitive("int")
  second := primitive("int")
  Assert.equal(first.emissionIdentity, none)
  // Metadata is outside the semantic equality contract.
  identities := SemanticTypeIdentities {}
  identities.identify(first)
  Assert.isTrue(sameType(first, second))
  Assert.equal(second.emissionIdentity, none)
}

export function testEditorSemanticRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}
