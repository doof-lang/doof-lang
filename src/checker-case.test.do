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

export function testResultCaseArmCanChangeTheOppositeChannel(): none {
  result := checked(
    "function widenError(input: Result<int, string>): Result<long, bool> { return case input { success: Success -> success, _: Failure -> Failure { error: false } } }\n" +
    "function widenValue(input: Result<int, string>): Result<bool, string> { return case input { _: Success -> Success { value: false }, failure: Failure -> failure } }",
  )
  Assert.equal(result.diagnostics.length, 0)
}

export function testQuarkWeakCaseExpressionChecking(): none {
  prefix := "class Item { value: int }\n"
  valid := checked(prefix + "function read(item: weak Item): int => case item { value: Success -> value.value.value\n_: Failure -> -1 }")
  Assert.equal(valid.diagnostics.length, 0)
  missing := checked(prefix + "function read(item: weak Item): int => case item { _: Success -> 1 }")
  Assert.isTrue(missing.diagnostics.length > 0)
  Assert.stringContains(missing.diagnostics[0].message, "exhaustive")
  wrong := checked(prefix + "function read(item: weak Item): int => case item { _: Success<int> -> 1\n_: Failure -> -1 }")
  Assert.isTrue(wrong.diagnostics.length > 0)
  Assert.stringContains(wrong.diagnostics[0].message, "must be \"Success<Item>\"")
  wrongFailure := checked(prefix + "function read(item: weak Item): int => case item { _: Success -> 1\n_: Failure<string> -> -1 }")
  Assert.isTrue(wrongFailure.diagnostics.length > 0)
  Assert.stringContains(wrongFailure.diagnostics[0].message, "must be \"Failure<WeakReferenceError>\"")
  extra := checked(prefix + "function read(item: weak Item): int => case item { _: Success<Item, Item> -> 1\n_: Failure -> -1 }")
  Assert.isTrue(extra.diagnostics.length > 0)
  Assert.stringContains(extra.diagnostics[0].message, "Success requires one type argument")
}

function caseDiagnostics(subject: string, arms: string): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function f(n: " + subject + "): int => case n { " + arms + " }" }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  return createChecker(analysis, "/main.do").check("/main.do")
}

export function testIntegerRangeExhaustivenessUsesSubjectBounds(): none {
  complete := [
    ["byte", "0..127 -> 1, 128..255 -> 2"],
    ["byte", "0 -> 1, 1.. -> 2"],
    ["int", "..<0 -> 1, 0 -> 2, 1.. -> 3"],
    ["int", "-2147483648..-1 -> 1, 0..2147483647 -> 2"],
    ["long", "..<0L -> 1, 0L.. -> 2"],
    ["long", "..<5000000001L -> 1, 5000000001L.. -> 2"],
  ]
  for entry of complete {
    Assert.equal(caseDiagnostics(entry[0], entry[1]).diagnostics.length, 0)
  }
  incomplete := [
    ["byte", "0..127 -> 1, 129..255 -> 2"],
    ["byte", "1.. -> 1"],
    ["int", "..<0 -> 1, 1.. -> 2"],
    ["int", "..<2147483647 -> 1"],
    ["long", "..<0L -> 1, 1L.. -> 2"],
    ["long", "..<2147483648L -> 1, 2147483648L..5000000000L -> 2"],
  ]
  for entry of incomplete {
    result := caseDiagnostics(entry[0], entry[1])
    Assert.isTrue(result.diagnostics.length > 0)
    Assert.stringContains(result.diagnostics[0].message, "Case expression must be exhaustive")
  }
}

export function testBareGenericPatternsTakeTheSubjectMembersArguments(): none {
  prelude := "class Box<T> { value: T }\n"
  valid := checked(prelude +
    "function a(x: Success<int> | none): int => case x { s: Success -> s.value, _ -> 0 }\n" +
    "function b(x: Box<int> | string): int => case x { box: Box -> box.value, s: string -> s.length }\n" +
    "function c(r: Result<int, string>): int => case r { s: Success -> s.value, f: Failure -> f.error.length }\n" +
    "function d(r: Result<int, string>): int => case r { s: Success<int> -> s.value, f: Failure<string> -> 0 }\n" +
    "function e(r: Result<int, string>): int => case r { all: Result<int, string> -> all.unwrapOr(0) }")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  mismatch := checked("function f(r: Result<int, string>): int => case r { s: Success<long> -> 1, _ -> 0 }")
  Assert.equal(mismatch.diagnostics.length, 1)
  Assert.equal(mismatch.diagnostics[0].message, "Case type pattern \"Success<long>\" must be \"Success<int>\" to match subject type \"Result<int, string>\"")
  partial := checked("function f(r: Result<int, string>): int => case r { s: Success -> 1 }")
  Assert.equal(partial.diagnostics.length, 1)
  Assert.equal(partial.diagnostics[0].message, "Case expression must be exhaustive")
  ambiguous := checked(prelude + "function f(x: Box<int> | Box<string>): int => case x { b: Box -> 1, _ -> 0 }")
  Assert.isTrue(ambiguous.diagnostics.length > 0)
  Assert.stringContains(ambiguous.diagnostics[0].message, "Box requires 1 type argument")
}

export function testBareResultArmsOnUnknownSubjectDoNotCascade(): none {
  result := checked("function main(): none { case missing { s: Success -> println(s.value), f: Failure -> println(f.error) } }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "missing")
}

export function testRangePatternsRequireIntegerSubjectsAndBounds(): none {
  floating := caseDiagnostics("double", "90.0.. -> 1, 80.0..<90.0 -> 2, _ -> 3")
  Assert.equal(floating.diagnostics.length, 2)
  for diagnostic of floating.diagnostics {
    Assert.equal(diagnostic.message, "Range patterns require an integer subject (byte, int, or long); got \"double\"")
  }

  characters := caseDiagnostics("char", "'a'..'z' -> 1, _ -> 2")
  Assert.equal(characters.diagnostics.length, 1)
  Assert.stringContains(characters.diagnostics[0].message, "got \"char\"")

  fractionalBound := caseDiagnostics("int", "90.5.. -> 1, _ -> 2")
  Assert.equal(fractionalBound.diagnostics.length, 1)
  Assert.equal(fractionalBound.diagnostics[0].message, "Range pattern bounds must be integers; got \"double\"")

  for subject of ["byte", "int", "long"] {
    valid := caseDiagnostics(subject, "..<10 -> 1, 10..<20 -> 2, 20.. -> 3")
    Assert.equal(valid.diagnostics.length, 0)
  }
}

