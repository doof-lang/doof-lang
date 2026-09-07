import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
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

export function testInterfaceBoundGenericOwners(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nclass Box<T: Reader<int>> { value: T\nread(): int => value.read()\nmap<U: Reader<int>>(other: U): int => other.read() }\nstruct Holder<T: Reader<int>> { value: T\nread(): int => value.read() }\ntype Alias<T: Reader<int>> = Box<T>\nfunction main(): int { box: Alias<IntReader> := Box(IntReader {})\nreturn box.map(IntReader {}) }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInterfaceBoundParameterOrder(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction readOne<T: U, U: Reader<int>>(value: T, other: U): int => value.read()")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInterfaceBoundCycle(): none {
  result := checked("function invalid<T: U, U: T>(value: T): T => value")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("Cyclic constraint") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundDeclarationOrder(): none {
  result := checked("function readOne<T: Reader<int>>(reader: T): int => reader.read()\ninterface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\n")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}


export function testInterfaceBoundConstrainedInterfaceAndAlias(): none {
  result := checked("interface Reader<V> { read(): V }\nclass R { read(): int => 1 }\ninterface Holder<T: Reader<int>> { item: T }\ntype Wrapped<T: Reader<int>> = Holder<T>\nfunction bad(value: Wrapped<string>): none {}")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("does not satisfy constraint") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundAliasUnconstrainedForward(): none {
  result := checked("interface Reader<V> { read(): V }\nclass Box<T: Reader<int>> { value: T }\ntype Bad<T> = Box<T>")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("does not satisfy constraint") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundAliasCycle(): none {
  result := checked("type Same<V> = V\nfunction invalid<T: Same<U>, U: T>(value: T): T => value")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("Cyclic constraint") { found = true } }
  Assert.isTrue(found)
}

export function testCheckerReviewWithCompletion(): none {
  valid := checked("function good(): int { with x := 1 { return x } }\nfunction stop(): never { with x := 1 { panic(\"stop\") } }")
  Assert.equal(valid.diagnostics.length, 0)
  invalid := checked("function bad(flag: bool): int { with x := 1 { if flag { return x } } }")
  Assert.equal(invalid.diagnostics.length, 1)
  Assert.stringContains(invalid.diagnostics[0].message, "may complete without returning int")
  unreachable := checked("function bad(): int { with x := 1 { return x }\nmissing() }")
  Assert.isTrue(unreachable.diagnostics.length > 0)
}

export function testRestrictedYieldInference(): none {
  for body of [
    "let x <- { if flag { yield 1 } else { yield none } }\ny: int | none := x",
    "let x <- { if flag { yield none } else { yield 1 } }\ny: int | none := x",
    "let x: int | string <- { if flag { yield 1 } else { yield \"text\" } }",
    "x := case flag { true -> { yield none }, false -> { yield 1 } }\ny: int | none := x",
    "x := async { if flag { yield 1 } else { yield none } }\ny: Promise<int | none> := x",
  ] {
    result := checked("function run(flag: bool): none { " + body + " }")
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.equal(result.diagnostics.length, 0)
  }
  for body of [
    "let x <- { if flag { yield 1 } else { yield \"text\" } }",
    "let x: int <- { if flag { yield 1 } else { yield 2L } }",
    "x := async { if flag { yield 1 } else { yield \"text\" } }",
  ] {
    result := checked("function run(flag: bool): none { " + body + " }")
    Assert.isTrue(result.diagnostics.length > 0)
  }
}

export function testEditorCheckerStatementsRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}
