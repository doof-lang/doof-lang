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
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("does not satisfy constraint") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}


export function testInterfaceBoundPreservesIsolationEffects(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "shared := [0]\ninterface Job { run(): none }\nclass Unsafe { run(): none { shared.push(1) } }\n" +
    "isolated function execute<T: Job>(job: T): none { job.run() }\nfunction main(): none {}",
  }], "/main.do")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("isolated") { found = true } }
  Assert.isTrue(found)
}
