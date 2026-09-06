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
