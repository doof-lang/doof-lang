import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
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

export function testReadonlyEmissionGenericNamesUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction identity<T>(value: T): T => value\nfunction build(): Item => identity<Item>(Item {})" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "identity__mapped__types_Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}

import { discoverInstantiations } from "./checked-instantiations"
import { nameInstantiations } from "./emitter-monomorphize"
import { prepareModuleNames } from "./emitter-names"

export function testInstantiationDiscoveryNamingDoesNotMutateSemanticDemand(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "class Value {}\nfunction identity<T>(value: T): T => value\nfunction main(): none { identity<Value>(Value {}) }" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  checked := discoverInstantiations(analysis)
  key := checked.functions[0].key
  first := nameInstantiations(checked, prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/main.do", packageName: "first" }]))
  second := nameInstantiations(checked, prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/main.do", packageName: "second" }]))
  Assert.equal(checked.functions[0].key, key)
  Assert.equal(first.functions[0].key, second.functions[0].key)
  Assert.isFalse(first.functions[0].emittedName == second.functions[0].emittedName)
}

export function testInstantiationDiscoveryNamingPreservesCollisionOrder(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/left.do", source: "export class Item {}" },
    SourceFile { path: "/right.do", source: "export class Item {}" },
    SourceFile { path: "/main.do", source:
      "import { Item as Left } from \"./left\"\nimport { Item as Right } from \"./right\"\n" +
      "function identity<T>(value: T): T => value\nfunction main(): none { identity<Left>(Left {})\nidentity<Right>(Right {}) }" },
  ]).analyze("/main.do")
  checker := createChecker(analysis, "/main.do")
  for i of 0..<analysis.modules.length {
    Assert.equal(checker.check(analysis.modules[analysis.modules.length - 1 - i].path).diagnostics.length, 0)
  }
  checked := discoverInstantiations(analysis)
  plan := nameInstantiations(checked, prepareModuleNames([
    ModuleNamespaceMapping { logicalPrefix: "/left.do", packageName: "same" },
    ModuleNamespaceMapping { logicalPrefix: "/right.do", packageName: "same" },
  ]))
  Assert.equal(plan.functions.length, 2)
  Assert.isFalse(plan.functions[0].key == plan.functions[1].key)
  Assert.equal(plan.functions[1].emittedName, plan.functions[0].emittedName + "_2")
}
