import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { SourceFile } from "./semantic"
import { PhaseTimings } from "./phase-timings"

export function testEditorIncrementalExposesFrontendTimings(): none {
  timings := PhaseTimings { enabled: true }
  result := analyzeEditor([SourceFile { path: "/main.do", source: "function main(): none {}" }], "/main.do", none, [], timings)
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(timings.render(), "analysis.load-parse-discover")
  Assert.stringContains(timings.render(), "checking.modules")
}

export function testEditorIncrementalReusesUnaffectedDependency(): none {
  dependency := SourceFile { path: "/dep.do", source: "export function value(): int => 42" }
  first := analyzeEditor([SourceFile { path: "/main.do", source: "import { value } from \"./dep\"\nfunction main(): int => value()" }, dependency], "/main.do")
  second := analyzeEditor([SourceFile { path: "/main.do", source: "import { value } from \"./dep\"\nfunction main(): int => value() + 1" }, dependency], "/main.do", first)
  Assert.equal(second.diagnostics.length, 0)
  Assert.equal(second.reusedModules.length, 1)
  Assert.equal(second.reusedModules[0], "/dep.do")
}

export function testEditorIncrementalInvalidatesImporters(): none {
  main := SourceFile { path: "/main.do", source: "import { value } from \"./dep\"\nfunction main(): int => value()" }
  first := analyzeEditor([main, SourceFile { path: "/dep.do", source: "export function value(): int => 42" }], "/main.do")
  second := analyzeEditor([main, SourceFile { path: "/dep.do", source: "export function value(): string => \"changed\"" }], "/main.do", first)
  Assert.equal(second.reusedModules.length, 0)
  Assert.isTrue(second.diagnostics.length > 0)
}

export function testEditorIncrementalInvalidatesChangedMockDirectives(): none {
  firstTest := "mock import for \"../package\" { \"./dep\" => \"./first.mock\" }\nimport { value } from \"../package\"\nexport function testValue(): none { ignored := value() }"
  let sources = [
    SourceFile { path: "/tests/value.test.do", source: firstTest },
    SourceFile { path: "/package/index.do", source: "import { number } from \"./dep\"\nexport function value(): int => number" },
    SourceFile { path: "/package/dep.do", source: "export readonly number = 1" },
    SourceFile { path: "/tests/first.mock.do", source: "export readonly number = 2" },
    SourceFile { path: "/tests/second.mock.do", source: "export readonly number = \"wrong\"" },
  ]
  first := analyzeEditor(sources, "/tests/value.test.do")
  Assert.equal(first.diagnostics.length, 0)
  sources[0] = SourceFile { path: "/tests/value.test.do", source: firstTest.replaceAll("first.mock", "second.mock") }
  changed := analyzeEditor(sources, "/tests/value.test.do", first)
  Assert.isTrue(changed.diagnostics.length > 0)
  Assert.equal(changed.reusedModules.length, 0)
}

export function testEditorIncrementalRetainsIsolationEffectsFromReusedDependency(): none {
  dependency := SourceFile { path: "/dep.do", source: "let counter = 0\nexport function value(): int => counter" }
  prefix := "import { value } from \"./dep\"\n"
  first := analyzeEditor([SourceFile { path: "/main.do", source: prefix + "function main(): int => value()" }, dependency], "/main.do")
  Assert.equal(first.diagnostics.length, 0)
  second := analyzeEditor([SourceFile { path: "/main.do", source: prefix + "isolated function main(): int => value()" }, dependency], "/main.do", first)
  Assert.equal(second.reusedModules.length, 1)
  Assert.isTrue(second.diagnostics.length > 0)
  clean := analyzeEditor([SourceFile { path: "/main.do", source: prefix + "isolated function main(): int => value()" }, dependency], "/main.do")
  Assert.equal(second.diagnostics.length, clean.diagnostics.length)
  Assert.equal(second.diagnostics[0].message, clean.diagnostics[0].message)
  repaired := analyzeEditor([SourceFile { path: "/main.do", source: prefix + "function main(): int => value() + 1" }, dependency], "/main.do", second)
  Assert.equal(repaired.reusedModules.length, 1)
  Assert.equal(repaired.diagnostics.length, 0)
}

export function testEditorIncrementalKeepsErrorsInUnchangedDependency(): none {
  dependency := SourceFile { path: "/dep.do", source: "export function value(): int => missing" }
  prefix := "import { value } from \"./dep\"\nfunction main(): int => value()"
  first := analyzeEditor([SourceFile { path: "/main.do", source: prefix }, dependency], "/main.do")
  second := analyzeEditor([SourceFile { path: "/main.do", source: prefix + " + 1" }, dependency], "/main.do", first)
  Assert.equal(second.reusedModules.length, 0)
  Assert.isTrue(second.diagnostics.length > 0)
  let found = false
  for diagnostic of second.diagnostics { if diagnostic.module == "/dep.do" && diagnostic.message.contains("missing") { found = true } }
  Assert.isTrue(found)
}
