import { prepareModuleNames, ModuleNamespaceMapping } from "./emitter-names"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import { ImportBinding, NamespaceBinding } from "./semantic"
import { parse } from "./parser"
import { InstantiationPlan } from "./emitter-monomorphize"
import { ModuleGraphEmission } from "./emitter-module"
import { compileWithLoader } from "./compiler"
import { noSourceLoader } from "./resolver"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { emitModuleGraph, ModuleEmissionCacheKey } from "./emitter-module"
import { PhaseTimings } from "./phase-timings"
import { SourceFile } from "./semantic"

export function testPhaseTimingsEmitterSeparatesRenderingAndReuse(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function main(): int => 1" }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(checked.diagnostics.length, 0)
  timings := PhaseTimings { enabled: true }
  first := emitModuleGraph(analysis, "/main.do", none, "executable", false, [], "", false, timings)
  for phase of ["module.prepare:/main.do", "module.render:/main.do", "emission.worldviews", "emission.header-planning", "emission.header-rendering", "emission.source-rendering"] {
    Assert.stringContains(timings.render(), phase + " ms=")
  }
  reusedTimings := PhaseTimings { enabled: true }
  keys := [ModuleEmissionCacheKey { modulePath: "/main.do", fingerprint: first.modules[0].fingerprint }]
  reused := emitModuleGraph(analysis, "/main.do", none, "executable", false, keys, "", false, reusedTimings)
  Assert.equal(reused.modules[0].reused, true)
  Assert.stringContains(reusedTimings.render(), "module.reuse:/main.do ms=")
  Assert.isFalse(reusedTimings.render().contains("module.render:"))
  Assert.stringContains(reusedTimings.render(), "emission.fingerprints ms=")
  Assert.isFalse(reusedTimings.render().contains("emission.source-rendering"))
}

export function testHeaderCacheReusesDependencyProjectionsWithinOneGraph(): none {
  sources := [
    SourceFile { path: "/types.do", source: "export class Left {}\nexport class Right {}\nexport class Pair { left: Left | Right\nright: Left | Right }\nexport class Unused {}" },
    SourceFile { path: "/left.do", source: "import { Pair } from \"./types\"\nexport function left(value: Pair): Pair => value" },
    SourceFile { path: "/right.do", source: "import { Pair } from \"./types\"\nexport function right(value: Pair): Pair => value" },
    SourceFile { path: "/main.do", source: "import { left } from \"./left\"\nimport { right } from \"./right\"\nfunction main(): int => 0" },
  ]
  timings := PhaseTimings { enabled: true }
  first := compileWithLoader(sources, "/main.do", noSourceLoader, [], "executable", false, [], "", false, timings)
  Assert.equal(first.diagnostics.length, 0)
  let lookups = 0
  let declarations = 0
  for timing of timings.entries {
    if timing.name == "header.cache-lookup-copy" { lookups = timing.count }
    if timing.name == "header.declarations" { declarations = timing.count }
  }
  Assert.isTrue(lookups > declarations)
  for module of first.emission!.modules {
    if module.modulePath == "/left.do" || module.modulePath == "/right.do" {
      Assert.stringContains(module.header, "doof_header_type_1 left;")
      Assert.stringNotContains(module.header, "struct Unused")
    }
  }
  sources[0] = SourceFile { path: "/types.do", source: sources[0].source.replaceAll("left:", "next:") }
  second := compileWithLoader(sources, "/main.do", noSourceLoader)
  Assert.equal(second.diagnostics.length, 0)
  for module of second.emission!.modules {
    if module.modulePath == "/left.do" || module.modulePath == "/right.do" {
      Assert.stringContains(module.header, "doof_header_type_1 next;")
      Assert.stringNotContains(module.header, "doof_header_type_1 left;")
    }
  }
}

export function testStructuredModuleHeadersShareTypesWithoutRewritingSources(): none {
  sources := [
    SourceFile { path: "/types.do", source: "export class Left {}\nexport class Right {}\nexport type Choice = Left | Right" },
    SourceFile { path: "/main.do", source: "import { Choice } from \"./types\"\nfunction choose(value: Choice): Choice => value\nfunction main(): int => 0" },
  ]
  result := compileWithLoader(sources, "/main.do", noSourceLoader)
  Assert.equal(result.diagnostics.length, 0)
  for module of result.emission!.modules {
    if module.modulePath == "/main.do" {
      Assert.stringContains(module.header, "std::variant<")
      Assert.stringContains(module.source, "std::variant<")
      Assert.stringNotContains(module.source, "doof_header_type_")
    }
  }
}

export function testTypeLoweringGraphCanEmitSameCheckedInputTwice(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "class Left {}\nclass Right {}\nfunction choose(value: Left | Right): Left | Right => value\nfunction main(): int => 0" }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(checked.diagnostics.length, 0)
  first := emitModuleGraph(analysis, "/main.do")
  second := emitModuleGraph(analysis, "/main.do")
  Assert.equal(first.modules.length, second.modules.length)
  for i of 0..<first.modules.length {
    Assert.equal(first.modules[i].header, second.modules[i].header)
    Assert.equal(first.modules[i].source, second.modules[i].source)
  }
}

export function testDependencyOptimizationPreservesFingerprintBytesAndClosure(): none {
  // All three edge kinds, including a cycle, contribute in analysis-module order.
  main := ModuleInfo { path: "/main.do", sourceHash: "main", program: parse(""), imports: [ImportBinding { localName: "x", sourceName: "x", sourceModule: "/bridge.do", typeOnly: true }], namespaceImports: [NamespaceBinding { localName: "leaf", sourceModule: "/leaf.do", typeOnly: true }] }
  bridge := ModuleInfo { path: "/bridge.do", sourceHash: "bridge", program: parse(""), reExports: ["/leaf.do"] }
  leaf := ModuleInfo { path: "/leaf.do", sourceHash: "leaf", program: parse(""), reExports: ["/main.do"] }
  unused := ModuleInfo { path: "/unused.do", sourceHash: "unused", program: parse("") }
  analysis := AnalysisResult { modules: [main, bridge, leaf, unused] }
  plan := InstantiationPlan {}
  before := emitModuleGraph(analysis, "/main.do", plan, "none", false, [], "test-config")
  fingerprint := dependencyFingerprint(before, "/main.do")
  Assert.equal(fingerprint, "d5ff08a51fdd9fe390a8a43cf60cc94efd6b84669149717508a18e342608fdb4")
  analysis.modules[3] = ModuleInfo { path: "/unused.do", sourceHash: "unrelated edit", program: parse("") }
  Assert.equal(dependencyFingerprint(emitModuleGraph(analysis, "/main.do", plan, "none", false, [], "test-config"), "/main.do"), fingerprint)
  analysis.modules[2] = ModuleInfo { path: "/leaf.do", sourceHash: "reachable edit", program: parse(""), reExports: ["/main.do"] }
  Assert.isTrue(dependencyFingerprint(emitModuleGraph(analysis, "/main.do", plan, "none", false, [], "test-config"), "/main.do") != fingerprint)
  analysis.modules[2] = leaf
  // Demand from elsewhere in the graph must still invalidate this module.
  plan.jsonSerializationKeys.push("new-closed-world-demand")
  Assert.isTrue(dependencyFingerprint(emitModuleGraph(analysis, "/main.do", plan, "none", false, [], "test-config"), "/main.do") != fingerprint)
}

function dependencyFingerprint(graph: ModuleGraphEmission, path: string): string {
  for module of graph.modules { if module.modulePath == path { return module.fingerprint } }
  panic("Expected emitted module " + path)
  return ""
}

export function testSerialEmissionPreservesMixedReuseAndModuleOrder(): none {
  sources := [
    SourceFile { path: "/types.do", source: "export class Left {}\nexport class Right {}\nexport type Choice = Left | Right" },
    SourceFile { path: "/main.do", source: "import { Choice } from \"./types\"\nfunction pass(value: Choice): Choice => value\nfunction main(): int => 0" },
  ]
  first := compileWithLoader(sources, "/main.do", noSourceLoader)
  Assert.equal(first.diagnostics.length, 0)
  let keys: ModuleEmissionCacheKey[] = []
  for module of first.emission!.modules {
    if module.modulePath == "/types.do" { keys.push(ModuleEmissionCacheKey { modulePath: module.modulePath, fingerprint: module.fingerprint }) }
  }
  Assert.equal(keys.length, 1)
  second := compileWithLoader(sources, "/main.do", noSourceLoader, [], "executable", false, keys, "", false, PhaseTimings {})
  Assert.equal(second.diagnostics.length, 0)
  Assert.equal(second.emission!.modules.length, first.emission!.modules.length)
  for i of 0..<first.emission!.modules.length {
    before := first.emission!.modules[i]
    after := second.emission!.modules[i]
    Assert.equal(after.modulePath, before.modulePath)
    Assert.equal(after.fingerprint, before.fingerprint)
    if after.modulePath == "/types.do" {
      Assert.isTrue(after.reused)
    } else {
      Assert.isFalse(after.reused)
      Assert.equal(after.header, before.header)
      Assert.equal(after.source, before.source)
      Assert.stringContains(after.source, "using namespace ::")
    }
  }
}

export function testReadonlyEmissionGraphNamesAreExplicit(): none {
  analysis := createAnalyzer([SourceFile { path: "/vendor/main.do", source: "function main(): int => 0" }]).analyze("/vendor/main.do")
  Assert.equal(createChecker(analysis).check("/vendor/main.do").diagnostics.length, 0)
  names := prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  named := emitModuleGraph{ result: analysis, entry: "/vendor/main.do", names }
  plain := emitModuleGraph(analysis, "/vendor/main.do")
  Assert.stringContains(named.modules[0].source, "namespace mapped::main_")
  Assert.stringContains(plain.modules[0].source, "namespace app_vendor_main_")
}
