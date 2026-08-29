import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { hasErrorDiagnostics } from "./diagnostics"
import { emitModuleGraph, ModuleEmission } from "./emitter-module"
import { SourceFile } from "./semantic"

function emit(source: string): ModuleEmission {
  path := "/main.do"
  analysis := createAnalyzer([SourceFile { path, source }]).analyze(path)
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis, path).check(path)
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  graph := emitModuleGraph(analysis, path)
  for module of graph.modules { if module.modulePath == path { return module } }
  panic("entry module was not emitted")
}

export function testDiscoversGenericCallsInsideAsExpressions(): none {
  result := emit(
    "function identity<T>(value: T): T => value\n" +
    "function main(): Result<int, string> => identity<int>(1) as int",
  )

  Assert.stringContains(result.source, "identity__int(1)")
  Assert.stringContains(result.source, "int32_t identity__int")
}

export function testDiscoversGenericCallsInsideCasePatterns(): none {
  result := emit(
    "function identity<T>(value: T): T => value\n" +
    "function main(): int => case 1 { identity<int>(1) -> 1, identity<int>(0)..identity<int>(2) -> 2, _ -> 0 }",
  )

  Assert.stringContains(result.source, "_case_subject == identity__int(1)")
  Assert.stringContains(result.source, "_case_subject >= identity__int(0)")
  Assert.stringContains(result.source, "_case_subject <= identity__int(2)")
}
