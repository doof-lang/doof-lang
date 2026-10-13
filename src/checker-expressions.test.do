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

export function testCheckerReviewByteLiteralBounds(): none {
  valid := checked("function low(): byte => 0\nfunction high(): byte => 255\nfunction consume(value: byte): none {}\nfunction good(): none { values: byte[] := [0, 255]\nconsume(255) }")
  Assert.equal(valid.diagnostics.length, 0)
  for source of ["function bad(): byte => 256", "function bad(): none { x: byte := 2147483647 }", "function bad(): none { xs: byte[] := [256] }"] {
    result := checked(source)
    Assert.isTrue(result.diagnostics.length > 0)
    Assert.stringContains(result.diagnostics[0].message, "Byte literal must be in the range")
  }
  negative := checked("function bad(): byte => -1")
  Assert.isTrue(negative.diagnostics.length > 0)
}

export function testRestrictedPathInference(): none {
  for body of [
    "x := if flag then 1 else \"text\"",
    "x := if flag then \"text\" else 1",
    "x := case flag { true -> 1, false -> \"text\" }",
    "x := if flag then [1] else readonly [2]",
    "x := (): int | string => if flag then true else 1",
    "x := () => if flag then 1 else \"text\"",
    "value: int | none := none\nx := value ?? \"text\"",
  ] {
    result := checked("function run(flag: bool): none { " + body + " }")
    Assert.isTrue(result.diagnostics.length > 0)
    Assert.isTrue(result.diagnostics[0].span.start.line > 0)
  }
  for body of [
    "x := if flag then 1 else none\ny: int | none := x",
    "x := if flag then none else 1\ny: int | none := x",
    "x := if flag then 1 else 2L\ny: long := x",
    "x := if flag then panic(\"stop\") else 1\ny: int := x",
    "x := case flag { true -> none, false -> 1 }\ny: int | none := x",
    "x: int | string := if flag then 1 else \"text\"",
    "x: int | string := case flag { true -> 1, false -> \"text\" }",
    "value: int | string := 1\nx := if flag then value else none",
    "value: int | none := none\nx: int | string := value ?? \"text\"",
    "value: int | none := none\nx := value ?? 2L\ny: long := x",
    "value: Result<int, string> := Success { value: 1 }\nx := value ?? 2\ny: int := x",
  ] {
    result := checked("function run(flag: bool): none { " + body + " }")
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.equal(result.diagnostics.length, 0)
  }
}

export function testRestrictedCatchInference(): none {
  prefix := "function one(): Result<int, string> => Failure { error: \"bad\" }\nfunction two(): Result<int, int> => Failure { error: 1 }\n"
  invalid := checked(prefix + "function run(): none { error := catch { try one()\ntry two() } }")
  Assert.isTrue(invalid.diagnostics.length > 0)
  Assert.stringContains(invalid.diagnostics[0].message, "provide an explicit type annotation")
  valid := checked(prefix + "function run(): none { error: string | int | none := catch { try one()\ntry two() }\nsingle := catch { try one() }\nx: string | none := single }")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
}

export function testEditorCheckerExpressionsRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}

