import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { FunctionDeclaration } from "./ast"
import { SourceFile } from "./semantic"
import { resolveProvisionalAnnotation } from "./checker-annotations"
import { typeName } from "./checker-types"

export function testSecondConsolidationProvisionalAnnotationsDoNotCommit(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function legacy(): void {}" }]).analyze("/main.do")
  module := analysis.modules[0]
  case module.program.statements[0] {
    fn: FunctionDeclaration -> {
      Assert.equal(typeName(resolveProvisionalAnnotation(fn.returnType!, module, analysis)), "none")
      Assert.equal(fn.returnType!.resolvedType, none)
    }
    _ -> { panic("expected function") }
  }
  checked := createChecker(analysis, "/main.do").check("/main.do")
  let warnings = 0
  for diagnostic of checked.diagnostics { if diagnostic.severity == "warning" { warnings = warnings + 1 } }
  Assert.equal(warnings, 1)
}

export function testSecondConsolidationProvisionalArityMatchesChecking(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function bad(): Map<string, int, bool> => {}" }]).analyze("/main.do")
  module := analysis.modules[0]
  case module.program.statements[0] {
    fn: FunctionDeclaration -> { Assert.equal(typeName(resolveProvisionalAnnotation(fn.returnType!, module, analysis)), "unknown") }
    _ -> { panic("expected function") }
  }
  checked := createChecker(analysis, "/main.do").check("/main.do")
  let found = false
  for diagnostic of checked.diagnostics {
    if diagnostic.message.contains("Map requires two type arguments") {
      Assert.equal(diagnostic.span.start.line, 1)
      found = true
    }
  }
  Assert.isTrue(found)
}

export function testUnionMutabilityAnnotations(): none {
  for annotation of [
    "int[] | readonly int[]",
    "readonly int[] | int[]",
    "Map<string, int> | ReadonlyMap<string, int>",
    "Set<int> | ReadonlySet<int>",
    "Map<string, int[]> | Map<string, readonly int[]>",
    "Tuple<int[]> | Tuple<readonly int[]>",
    "Promise<int[]> | Promise<readonly int[]>",
  ] {
    source := "function bad(value: " + annotation + "): none {}"
    analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
    for diagnostic of analysis.diagnostics { println(source + ": " + diagnostic.message) }
    Assert.equal(analysis.diagnostics.length, 0)
    checked := createChecker(analysis, "/main.do").check("/main.do")
    Assert.isTrue(checked.diagnostics.length > 0)
    Assert.stringContains(checked.diagnostics[0].message, "differ only in collection mutability")
    Assert.stringContains(checked.diagnostics[0].message, "use a single mutability or distinct wrapper types")
    Assert.equal(checked.diagnostics[0].span.start.line, 1)
  }
  for source of [
    "type Mutable = int[]\ntype Frozen = readonly int[]\nfunction bad(value: Mutable | Frozen): none {}",
    "type Choice<T, U> = T | U\nfunction bad(value: Choice<int[], readonly int[]>): none {}",
  ] {
    analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
    for diagnostic of analysis.diagnostics { println(source + ": " + diagnostic.message) }
    Assert.equal(analysis.diagnostics.length, 0)
    checked := createChecker(analysis, "/main.do").check("/main.do")
    Assert.isTrue(checked.diagnostics.length > 0)
    Assert.stringContains(checked.diagnostics[0].message, "differ only in collection mutability")
  }
  for annotation of ["int[] | int[]", "int[] | none", "readonly int[] | none", "int[] | readonly string[]"] {
    analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function good(value: " + annotation + "): none {}" }]).analyze("/main.do")
    Assert.equal(analysis.diagnostics.length, 0)
    Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  }
}

export function testEditorCheckerAnnotationsRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}
