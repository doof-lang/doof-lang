import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"

export function testRetiredActorUseReportsTheIdentifierSpan(): none {
  source := "class Worker { value(): int => 1 }\nfunction run(): int { worker := Actor<Worker>()\nretire worker\nreturn worker.value() }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  diagnostics := createChecker(analysis, "/main.do").check("/main.do").diagnostics
  Assert.equal(diagnostics.length, 1)
  Assert.equal(diagnostics[0].message, "Cannot use actor binding \"worker\" after it has been retired")
  Assert.equal(diagnostics[0].module, "/main.do")
  Assert.equal(diagnostics[0].span.start.line, 4)
  Assert.equal(diagnostics[0].span.start.column, 8)
  Assert.equal(diagnostics[0].span.end.offset - diagnostics[0].span.start.offset, 6)
}
