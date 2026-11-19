import { hasErrorDiagnostics } from "./diagnostics"
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

export function testInterfaceBoundForwarding(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction keep<T: Reader<int>>(value: T): T => value\nfunction forward<U: Reader<int>>(value: U): U => keep(value)\nfunction main(): int => forward(IntReader {}).read()")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInterfaceBoundForwardingMismatch(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction keep<T: Reader<int>>(value: T): T => value\nfunction invalid<U: Reader<string>>(value: U): U => keep(value)")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(result.diagnostics.some(=> it.message.contains("does not satisfy constraint")))
}


export function testInterfaceBoundPreservesIsolationEffects(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "shared := [0]\ninterface Job { run(): none }\nclass Unsafe { run(): none { shared.push(1) } }\n" +
    "isolated function execute<T: Job>(job: T): none { job.run() }\nfunction main(): none {}",
  }], "/main.do")
  Assert.isTrue(result.diagnostics.some(=> it.message.contains("isolated")))
}

export function testCheckerConsolidationFieldInferenceSkipsConstants(): none {
  result := compile([SourceFile { path: "/main.do", source: "class Box<T> { kind: \"box\"\nvalue: T }\nfunction main(): int => Box(3).value" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(result.diagnostics), false)
  Assert.isTrue(result.emission != none)
}

export function testInterfaceBoundSubstitutesMethodParameters(): none {
  result := checked("interface Cmp<V> { less(other: V): bool }\nclass N { v: int\nless(other: int): bool => v < other }\nfunction lessN<T: Cmp<int>>(a: T, b: int): bool => a.less(b)\nfunction main(): bool => lessN(N { v: 1 }, 2)")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testConstrainedTypeParameterFlowsThroughOptionalSelf(): none {
  result := checked(`interface HasScore { score(): int }
class P { v: int; score(): int => v }
function best<T: HasScore>(items: T[]): T | none {
    let found: T | none = none
    for item of items {
        current := found else { found = item; continue }
        if item.score() > current.score() { found = item }
    }
    return found
}
function only<T: HasScore>(item: T): T | none => item
function main(): int => (best([P { v: 3 }, P { v: 9 }]) ?? P { v: 0 }).v + (only(P { v: 1 })?.v ?? 0)`)
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testConstrainedTypeParameterStillRejectsUnrelatedTarget(): none {
  result := checked("interface HasScore { score(): int }\nfunction bad<T: HasScore>(item: T): int | none => item")
  Assert.isTrue(result.diagnostics.some(=> it.message.contains("Cannot return T")))
}
