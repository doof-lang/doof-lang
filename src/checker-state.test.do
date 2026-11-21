import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { FunctionDeclaration } from "./ast"
import { ProvisionalSignatures } from "./checker-state"
import { primitive, typeName } from "./checker-types"

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

export function testProvisionalSignaturesKeyByDeclarationAndModule(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function one(): int => 1\nfunction two(): int => 2" }], "/main.do")
  statements := result.analysis.modules[0].program.statements
  one := statements[0] as FunctionDeclaration else { panic("expected function") }
  two := statements[1] as FunctionDeclaration else { panic("expected function") }
  signatures := ProvisionalSignatures {}
  EditorAssert.isTrue(signatures.lookup(one, "/main.do") == none)
  signatures.store(one, "/main.do", primitive("int"))
  signatures.store(one, "/other.do", primitive("string"))
  EditorAssert.equal(typeName(signatures.lookup(one, "/main.do")!), "int")
  EditorAssert.equal(typeName(signatures.lookup(one, "/other.do")!), "string")
  EditorAssert.isTrue(signatures.lookup(two, "/main.do") == none)
}
