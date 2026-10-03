import { Assert } from "std/assert"
import { AnalysisResult, createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"
import { asyncResultViolation } from "./checker-async"
import { arrayType, mapType, primitive, promiseType, resultType, tupleType, weakType } from "./checker-types"

// Fails on parse or analysis diagnostics so a malformed fixture cannot pass
// unnoticed through a test that only inspects checker output.
function analyzed(source: string): AnalysisResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  return analysis
}

export function testSecondConsolidationAsyncNestedResultPolicy(): none {
  nested := arrayType(mapType(primitive("string"), resultType(tupleType([primitive("int"), promiseType(primitive("int"))]), primitive("string"))))
  Assert.equal(asyncResultViolation(createAnalyzer([]).analyze("/main.do"), nested), "Promise<T> values are asynchronous handles")
  safe := arrayType(mapType(primitive("string"), primitive("int")))
  Assert.equal(asyncResultViolation(createAnalyzer([]).analyze("/main.do"), safe), none)
}

export function testSecondConsolidationAsyncCaptureHandleDirection(): none {
  analysis := analyzed("class Worker { value: int\nread(): int => value }\nfunction use(worker: Actor<Worker>): Promise<int> => async { yield worker.read() }")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  for diagnostic of checked.diagnostics { println(diagnostic.message) }
  Assert.equal(checked.diagnostics.length, 0)
}
