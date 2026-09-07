import { Assert } from "std/assert"
import { analyzeEditor } from "./editor-incremental"
import { SourceFile } from "./semantic"

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
