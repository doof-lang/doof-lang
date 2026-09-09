import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker, validateCheckedTypes } from "./checker"
import { CheckResult, SourceFile } from "./semantic"

function checked(source: string): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  result := createChecker(analysis, "/main.do").check("/main.do")
  if result.diagnostics.length == 0 { Assert.equal(validateCheckedTypes(analysis).length, 0) }
  return result
}

function rejects(source: string, message: string): none {
  result := checked(source)
  for diagnostic of result.diagnostics { if diagnostic.message.contains(message) { return } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  panic("Expected diagnostic: " + message)
}

export function testCheckerReviewTryPropagation(): none {
  load := "function load(): Result<int, string> => Failure { error: \"bad\" }\n"
  rejects(load + "function bad(): int { try x := load()\nreturn x }", "requires a Result-returning function")
  rejects(load + "function bad(): Result<int, int> { try x := load()\nreturn Success { value: x } }", "Cannot propagate error string")
  valid := checked(load + "function good(): Result<int, string | int> { try x := load()\nreturn Success { value: x } }")
  Assert.equal(valid.diagnostics.length, 0)
  script := checked(load + "try x := load()\nprintln(x)")
  Assert.equal(script.diagnostics.length, 0)
  caught := checked(load + "function good(): none { error := catch { try load() } }")
  Assert.equal(caught.diagnostics.length, 0)
}

export function testCheckerReviewTryScopeBoundaries(): none {
  load := "function load(): Result<int, string> => Failure { error: \"bad\" }\n"
  rejects(load + "function outer(): none { error := catch { function inner(): none { try load() } } }", "requires a Result-returning function")
  rejects(load + "error := catch { callback: (): none := () => { try load() } }", "requires a Result-returning function")
  rejects(load + "function outer(): none { error := catch { x <- { try load()\nyield 1 } } }", "value-producing block")
}

export function testCheckerReviewTryReadonly(): none {
  load := "function load(): Result<int[], string> => Success { value: [1] }\n"
  rejects(load + "function bad(): Result<int, string> { try readonly xs = load()\nxs.push(2)\nreturn Success { value: 1 } }", "readonly")
  rejects(load + "function bad(): Result<int, string> { try readonly xs = load()\nxs[0] = 2\nreturn Success { value: 1 } }", "readonly")
  valid := checked(load + "function good(): Result<int, string> { try readonly xs: int[] = load()\nreturn Success { value: xs.length } }")
  Assert.equal(valid.diagnostics.length, 0)
  mutable := checked(load + "function good(): Result<int, string> { try let xs = load()\nxs.push(2)\nreturn Success { value: xs.length } }")
  Assert.equal(mutable.diagnostics.length, 0)
}

export function testCheckerReviewTryDeclarations(): none {
  load := "function load(): Result<int, string> => Success { value: 1 }\n"
  for kind of ["let", "readonly", "const"] {
    rejects(load + "function bad(): Result<int, string> { try " + kind + " x: string = load()\nreturn Success { value: 1 } }", "Cannot assign int to string")
    valid := checked(load + "function good(): Result<long, string> { try " + kind + " x: long = load()\nreturn Success { value: x } }")
    Assert.equal(valid.diagnostics.length, 0)
  }
  save := "function save(): Result<none, string> => Success()\n"
  rejects(save + "function bad(): Result<int, string> { try x := save()\nreturn Success { value: 1 } }", "Cannot bind a none success value")
  valid := checked(save + "function good(): Result<none, string> { try save()\nreturn Success() }")
  Assert.equal(valid.diagnostics.length, 0)
}

export function testNeverReviewTryCompletion(): none {
  load := "function load(): Result<never, string> => Failure { error: \"bad\" }\n"
  for statement of ["try load()", "try x := load()", "try x: int := load()", "try let x: int = load()", "try readonly x: int = load()"] {
    result := checked(load + "function good(): Result<int, string> { " + statement + " }")
    Assert.equal(result.diagnostics.length, 0)
  }
  rejects(load + "function bad(): Result<int, int> { try load() }", "Cannot propagate error string")
  rejects(load + "function bad(): int { try load() }", "requires a Result-returning function")
  rejects("function load(): Result<int, string> => Failure { error: \"bad\" }\nfunction bad(): Result<int, string> { try load() }", "may complete")
}
