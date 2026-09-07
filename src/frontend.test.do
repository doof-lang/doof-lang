import { Assert } from "std/assert"
import { analyzeWithLoader } from "./frontend"
import { noSourceLoader } from "./resolver"
import { PhaseTimings } from "./phase-timings"
import { SourceFile } from "./semantic"

export function testFrontendSerialAndParallelAnalysisAgree(): none {
  sources := [
    SourceFile { path: "/main.do", source: "import { answer } from \"./answer\"\nfunction main(): int => answer()" },
    SourceFile { path: "/answer.do", source: "export function answer(): int => 42" },
  ]
  serial := analyzeWithLoader(sources, "/main.do", noSourceLoader, "executable", PhaseTimings {}, true)
  parallel := analyzeWithLoader(sources, "/main.do")
  Assert.equal(serial.diagnostics.length, 0)
  Assert.equal(parallel.diagnostics.length, 0)
  Assert.equal(serial.analysis.modules.length, 2)
  for index of 0..<serial.analysis.modules.length {
    Assert.equal(serial.analysis.modules[index].path, parallel.analysis.modules[index].path)
    Assert.equal(serial.analysis.modules[index].sourceHash, parallel.analysis.modules[index].sourceHash)
  }
}

export function testFrontendSerialReportsMalformedAndMissingSources(): none {
  malformed := analyzeWithLoader([SourceFile { path: "/main.do", source: "function main(: int {" }], "/main.do", noSourceLoader, "executable", PhaseTimings {}, true)
  Assert.isTrue(malformed.diagnostics.length > 0)
  Assert.equal(malformed.diagnostics[0].module, "/main.do")
  missing := analyzeWithLoader([], "/missing.do", noSourceLoader, "executable", PhaseTimings {}, true)
  Assert.equal(missing.diagnostics.length, 1)
  Assert.stringContains(missing.diagnostics[0].message, "Module not found")
}

export function testFrontendRetainsGraphForTypeDiagnostics(): none {
  result := analyzeWithLoader([SourceFile { path: "/main.do", source: "function main(): int => \"wrong\"" }], "/main.do", noSourceLoader, "executable", PhaseTimings {}, true)
  Assert.equal(result.analysis.modules.length, 1)
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.equal(result.diagnostics[0].module, "/main.do")
}

export function testEditorFrontendIncludesUnreachedOpenModules(): none {
  result := analyzeWithLoader([
    SourceFile { path: "/main.do", source: "function main(): int => 42" },
    SourceFile { path: "/other.do", source: "export function value(): int => \"wrong\"" },
  ], "/main.do", noSourceLoader, "executable", PhaseTimings {}, true, true, [], ["/other.do"])
  Assert.equal(result.analysis.modules.length, 2)
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.equal(result.diagnostics[0].module, "/other.do")
}
