import { compile } from "./compiler"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { CheckResult, SourceFile } from "./semantic"

function checked(source: string): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  return createChecker(analysis, "/main.do").check("/main.do")
}

export function testCheckerReviewNonassignableMembers(): none {
  for source of ["function bad(): none { xs := [1]\nxs.length = 2 }", "function bad(): none { s := \"x\"\ns.length += 1 }", "class Value { read(): int => 1 }\nfunction bad(): none { value := Value {}\nvalue.read = (): int => 2 }"] {
    result := checked(source)
    let found = false
    for diagnostic of result.diagnostics { if diagnostic.message.contains("not an assignable field") { found = true } }
    Assert.isTrue(found)
  }
  valid := checked("class Value { let count: int\nlet callback: (): int }\nfunction good(): none { value := Value { count: 1, callback: (): int => 1 }\nvalue.count += 1\nvalue.callback = (): int => 2 }")
  Assert.equal(valid.diagnostics.length, 0)
}

export function testInterfaceBoundImmutableField(): none {
  result := checked("interface View { value: int }\nclass Counter { let value: int }\nfunction update<T: View>(value: T): none { value.value = 1 }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("immutable") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundMutableField(): none {
  result := checked("interface View { let value: int }\nclass Counter { let value: int }\nfunction update<T: View>(value: T): int { value.value += 1\nreturn value.value }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testActorFieldAccessWritesRejectedOnce(): none {
  for update of ["actor.value = 8", "actor.value += 1", "actor.value -= 1"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class State { let value: int = 7 }\nfunction bad(actor: Actor<State>): none { " + update + " }",
    }], "/main.do")
    let errors = 0
    for diagnostic of result.diagnostics {
      if diagnostic.severity != "error" { continue }
      errors = errors + 1
      Assert.stringContains(diagnostic.message, "Cannot access actor field 'value' directly")
      Assert.equal(diagnostic.span.start.line, 2)
    }
    Assert.equal(errors, 1)
    Assert.equal(result.emission, none)
  }
}

