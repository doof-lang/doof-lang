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

function emitSources(sources: SourceFile[], entry: string): ModuleEmission[] {
  analysis := createAnalyzer(sources).analyze(entry)
  Assert.equal(analysis.diagnostics.length, 0)
  checker := createChecker(analysis, entry)
  for i of 0..<analysis.modules.length {
    module := analysis.modules[analysis.modules.length - 1 - i]
    Assert.equal(hasErrorDiagnostics(checker.check(module.path).diagnostics), false)
  }
  return emitModuleGraph(analysis, entry).modules
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

export function testUsesCheckerConformanceForConcreteInterfaceVariants(): none {
  result := emit(
    "interface Box<T> { readonly value: T\nread(): T }\n" +
    "class HiddenBox { readonly value: int\nprivate read(): int => value }\n" +
    "class MutableBox { value: int\nread(): int => value }\n" +
    "class IntBox { readonly value: int\nread(): int => value }\n" +
    "function read(box: Box<int>): int => box.read()\n" +
    "function main(): int => read(IntBox { value: 7 })",
  )

  Assert.stringContains(result.header, "using Box__int = std::variant<std::shared_ptr<IntBox>>;")
}

export function testMonomorphizesNamespaceGenericCallsInTheirDefiningModule(): none {
  modules := emitSources([
    SourceFile { path: "/main.do", source: "import * as tools from \"./tools\"\nfunction main(): int => tools.identity<int>(1)" },
    SourceFile { path: "/tools.do", source: "export function identity<T>(value: T): T => value" },
  ], "/main.do")
  let main: ModuleEmission | none = none
  let tools: ModuleEmission | none = none
  for module of modules {
    if module.modulePath == "/main.do" { main = module }
    if module.modulePath == "/tools.do" { tools = module }
  }
  Assert.equal(main != none, true)
  Assert.equal(tools != none, true)
  Assert.stringContains(main!.source, "::app_tools_::identity__int(1)")
  Assert.stringContains(tools!.source, "identity__int")
}

export function testIncludesGenericClassesInConcreteInterfaceVariants(): none {
  result := emit(
    "interface Reader<T> { read(): T }\n" +
    "class Box<T> { value: T\nread(): T => value }\n" +
    "function read(reader: Reader<int>): int => reader.read()\n" +
    "function main(): int => read(Box<int> { value: 7 })",
  )
  Assert.stringContains(result.header, "using Reader__int = std::variant<std::shared_ptr<Box__int>>;")
}
