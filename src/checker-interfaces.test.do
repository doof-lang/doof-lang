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

export function testInterfaceBoundInterfaceArgument(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction readOne<T: Reader<int>>(value: T): int => value.read()\nfunction pass(value: Reader<int>): int => readOne(value)")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInterfaceBoundPrivateImplementation(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nclass Secret { private read(): int => 1 }\nfunction keep<T: Reader<int>>(value: T): T => value\nfunction main(): none { keep(Secret {}) }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("does not satisfy constraint") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}


export function testCheckerReviewInvariantWritableFields(): none {
  invalid := checked("interface Box { let value: long }\nclass IntBox { let value: int }\nclass LongBox { let value: long }\nfunction bad(): none { box: Box := IntBox { value: 1 }\nbox.value = 2147483648L }")
  let found = false
  for diagnostic of invalid.diagnostics { if diagnostic.message.contains("Cannot assign IntBox to Box") { found = true } }
  Assert.isTrue(found)
  valid := checked("interface Box { let value: long }\nclass LongBox { let value: long }\nfunction good(): none { box: Box := LongBox { value: 1L }\nbox.value = 2147483648L }")
  Assert.equal(valid.diagnostics.length, 0)
  readOnlyView := checked("interface View { value: long }\nclass IntBox { value: int }\nfunction read(): long { box: View := IntBox { value: 1 }\nreturn box.value }")
  Assert.equal(readOnlyView.diagnostics.length, 0)
}

export function testSecondConsolidationGenericInterfaceSignatureBeforeBodies(): none {
  result := checked("interface Reader<T> { read(): T }\nfunction use(reader: Reader<int>): int => reader.read()\nclass Box<T> { value: T\nread(): T => value }\nfunction main(): int => use(Box<int> { value: 3 })")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}
