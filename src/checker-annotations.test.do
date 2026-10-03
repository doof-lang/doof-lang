import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { FunctionDeclaration, NamedType } from "./ast"
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

export function testEditorCheckedCasePatternRetainsResolvedTypeSymbol(): none {
  source := "class NamedType {}\nfunction inspect(annotation: NamedType | none): none { case annotation { named: NamedType -> {} _ -> {} } }"
  result := editorAnalysis([EditorSource { path: "/main.do", source }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  patternOffset := source.indexOf("named: NamedType") + 7
  let found = false
  for annotation of result.analysis.modules[0].editorAnnotations {
    case annotation {
      named: NamedType -> {
        if named.span.start.offset == patternOffset {
          EditorAssert.isTrue(named.resolvedSymbol != none)
          found = true
        }
      }
      _ -> { }
    }
  }
  EditorAssert.isTrue(found)
}

export function testStructsSatisfyInterfaceBoundsButNotInterfaceValues(): none {
  source := "interface Reader { read(): int }\nstruct Total { value: int\nread(): int => value }\nclass Fixed { read(): int => 1 }\n" +
    "function readOne<T: Reader>(reader: T): int => reader.read()\n"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: source + "function main(): int => readOne(Total { value: 3 })" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  asValue := createAnalyzer([SourceFile { path: "/main.do", source: source + "function main(): none { let reader: Reader = Total { value: 3 } }" }]).analyze("/main.do")
  diagnostics := createChecker(asValue, "/main.do").check("/main.do").diagnostics
  Assert.equal(diagnostics.length, 1)
  Assert.stringContains(diagnostics[0].message, "Cannot assign Total to Reader")
}

export function testResultArmAnnotationsResolveToArmTypes(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function f(a: Success<int>, b: Failure<none>, c: Success<int> | Failure<string>): none {}" }]).analyze("/main.do")
  result := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(result.diagnostics.length, 0)
  case analysis.modules[0].program.statements[0] {
    fn: FunctionDeclaration -> {
      Assert.equal(typeName(fn.params[0].resolvedType!), "Success<int>")
      Assert.equal(typeName(fn.params[1].resolvedType!), "Failure<none>")
      Assert.equal(typeName(fn.params[2].resolvedType!), "Result<int, string>")
    }
    _ -> { panic("expected function") }
  }
  arity := createChecker(createAnalyzer([SourceFile { path: "/main.do", source: "function f(a: Success<int, string>): none {}" }]).analyze("/main.do"), "/main.do").check("/main.do")
  Assert.equal(arity.diagnostics.length, 1)
  Assert.equal(arity.diagnostics[0].message, "Success requires one type argument")
}

function mapKeyErrors(source: string): string[] {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  let messages: string[] = []
  for diagnostic of checked.diagnostics {
    if diagnostic.message.contains("Map key type") { messages.push(diagnostic.message) }
  }
  return messages
}

export function testRejectsUnsupportedMapKeyAnnotations(): none {
  floating := mapKeyErrors("function main(): none { let m: Map<float, int> = {} }")
  Assert.equal(floating.length, 1)
  Assert.stringContains(floating[0], "Map key type \"float\" is not supported; map keys must be byte, string, int, long, char, bool, or enum")

  tuple := mapKeyErrors("function use(m: ReadonlyMap<Tuple<int, string>, int>): none {}")
  Assert.equal(tuple.length, 1)
  Assert.stringContains(tuple[0], "is not supported")

  nominal := mapKeyErrors("class Point { x: int }\nclass Holder { points: Map<Point, int> = {} }")
  Assert.equal(nominal.length, 1)
  Assert.stringContains(nominal[0], "Map key type \"Point\" is not supported")
}

export function testAcceptsSupportedMapKeyAnnotations(): none {
  Assert.equal(mapKeyErrors("enum Suit { Spades, Hearts }\nfunction use(a: Map<string, int>, b: Map<int, int>, c: Map<long, int>, d: Map<char, int>, e: Map<bool, int>, f: Map<byte, int>, g: Map<Suit, int>): none {}").length, 0)
  Assert.equal(mapKeyErrors("function count<K>(m: Map<K, int>): int => m.size").length, 0)
}

export function testReportsLocalSetElementAnnotationOnce(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "class Holder { s: Set<float> = [] }\nfunction main(): none { let s: Set<float> = [] }" }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  let count = 0
  for diagnostic of checked.diagnostics { if diagnostic.message.contains("Set element type \"float\"") { count += 1 } }
  Assert.equal(count, 2)
}
