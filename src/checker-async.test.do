import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"
import { asyncResultViolation } from "./checker-async"
import { arrayType, mapType, primitive, promiseType, resultType, tupleType, weakType } from "./checker-types"

export function testSecondConsolidationAsyncNestedResultPolicy(): none {
  nested := arrayType(mapType(primitive("string"), resultType(tupleType([primitive("int"), promiseType(primitive("int"))]), primitive("string"))))
  Assert.equal(asyncResultViolation(createAnalyzer([]).analyze("/main.do"), nested), "Promise<T> values are asynchronous handles")
  safe := arrayType(mapType(primitive("string"), primitive("int")))
  Assert.equal(asyncResultViolation(createAnalyzer([]).analyze("/main.do"), safe), none)
}

export function testSecondConsolidationAsyncCaptureHandleDirection(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "class Worker { value: int\nread(): int => value }\nfunction use(worker: Actor<Worker>): Promise<int> => async { yield worker.read() }",
  }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  for diagnostic of checked.diagnostics { println(diagnostic.message) }
  Assert.equal(checked.diagnostics.length, 0)
}
