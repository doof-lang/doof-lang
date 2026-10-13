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

export function testQuarkJsonEqualityRequiresNarrowing(): none {
  for source of ["value == 4", "4 != value", "value == true", "value != \"four\""] {
    result := checked("function compare(value: SerialValue): bool => " + source)
    Assert.equal(result.diagnostics.length, 1)
    Assert.stringContains(result.diagnostics[0].message, "Narrow SerialValue")
  }
  for source of ["value == none", "none != value", "value == value", "(value as int)! == 4"] {
    Assert.equal(checked("function compare(value: SerialValue): bool => " + source).diagnostics.length, 0)
  }
}

export function testCheckerReviewNumericBoundOperators(): none {
  valid := checked("function add<T: float | double>(a: T, b: T): T => a + b\nfunction divide<T: float | double>(a: T, b: T): T => a / b\nfunction negate<T: int | long>(a: T): T => -a\nfunction invert<T: int | long>(a: T): T => ~a\nfunction less<T: float | double>(a: T, b: T): bool => a < b\nfunction increase<T: float | double>(a: T): T { let x = a\nx += 1\nreturn x }\nfunction single<T: double>(a: T, b: T): T => a * b")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  for source of ["function bad<T: float | double>(a: T, b: T): T => a % b", "function bad<T: int | long>(a: T, b: T): T => a / b", "function bad<T: byte | int>(a: T): T => a + a", "function bad<T: float | double>(a: T): T { let x = a\nx += 1.0\nreturn x }", "function bad<T>(a: T, b: T): T => a + b"] {
    invalid := checked(source)
    Assert.isTrue(invalid.diagnostics.length > 0)
  }
}

export function testCheckerReviewNumericOperatorPromotions(): none {
  valid := checked("function equal<T: int | long, U: float | double>(a: T, b: U): bool => a == b\nfunction shift<T: int | long>(a: T, count: long): T => a << count\nfunction power<T: int | long>(a: T): double => a ** a\nfunction floatingPower<T: float | double>(a: T): T => a ** a\nfunction compound(): long { let x = 1L\nreturn x += 2 }")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  invalid := checked("function bad<T: int | long>(a: T): T => a ** a")
  Assert.isTrue(invalid.diagnostics.length > 0)
}

export function testPostfixOperatorsCollapseEveryAbsentLayer(): none {
  prelude := "class Box { value: int\nitems: int[] = [] }\n" +
    "function plain(): Result<Box, string> => Success(Box { value: 1 })\n" +
    "function nested(): Result<Box | none, string> => Success(none)\n" +
    "function outer(): Result<Box, string> | none => none\n" +
    "function done(): Result<none, string> => Success()\n"
  typed := checked(prelude +
    "function f(maybe: Box | none): none {\n" +
    "let a: Box | none = plain()?\n" +
    "let b: Box | none = nested()?\n" +
    "let c: Box | none = outer()?\n" +
    "let d: Box | none = maybe?\n" +
    "let e: Box = nested()!\n" +
    "let g: Box = outer()!\n" +
    "let h: Box = nested() ?? Box { value: 2 }\n" +
    "let i: Box = outer() ?? Box { value: 3 }\n" +
    "let j: int | none = nested()?.items?[0]\n" +
    "let k: int = nested()!.items[0]\n" +
    "done()! }")
  for diagnostic of typed.diagnostics { println(diagnostic.message) }
  Assert.equal(typed.diagnostics.length, 0)
  plainValue := checked(prelude + "function f(): none { _ := 1? }")
  Assert.equal(plainValue.diagnostics.length, 1)
  Assert.equal(plainValue.diagnostics[0].message, "Postfix '?' requires a nullable or Result operand, got int")
  noValue := checked(prelude + "function f(): none { _ := done()? }")
  Assert.equal(noValue.diagnostics.length, 1)
  Assert.equal(noValue.diagnostics[0].message, "Postfix '?' requires a Result with a success value, got Result<none, string>")
}

export function testBareTryIsRejectedInExpressionPosition(): none {
  prefix := "function load(): Result<int, string> => Success(1)\n"
  for body of [
    "x := try load()\nreturn Success(x)",
    "return Success(1 + try load())",
    "x: int := case 1 { 0 -> 0, _ -> try load() }\nreturn Success(x)",
  ] {
    result := checked(prefix + "function run(): Result<int, string> {\n" + body + "\n}")
    Assert.isTrue(result.diagnostics.length > 0)
    Assert.stringContains(result.diagnostics[0].message, "'try' is a statement, not an expression; write 'try name := value'")
  }
  valid := checked(prefix + "function run(): Result<int, string> {\ntry x := load()\ny := load()!\nz := load()?\nreturn Success(x + y + (z ?? 0))\n}")
  Assert.equal(valid.diagnostics.length, 0)
}

export function testPrefixTryBangAndQuestionNameTheirPostfixForms(): none {
  prefix := "function load(): Result<int, string> => Success(1)\n"
  removed := checked(prefix + "function run(): int {\ny := try! load()\nz := try? load()\ntry! load()\nreturn y + (z ?? 0)\n}")
  Assert.equal(removed.diagnostics.length, 3)
  Assert.equal(removed.diagnostics[0].message, "'try! value' was removed; write 'value!'")
  Assert.equal(removed.diagnostics[1].message, "'try? value' was removed; write 'value?'")
  Assert.equal(removed.diagnostics[2].message, "'try! value' was removed; write 'value!'")
}

export function testEqualityComparesUnionsWithTheirMembers(): none {
  prelude := "struct P { x: int }\nfunction ok(): Result<int, string> => Success(1)\n"
  valid := checked(prelude + "function f(u: int | string, v: P | string): bool => u == 1 && v != P { x: 1 } && ok() == Success(1) && Failure(\"x\") != ok() && Success(1) == Success(1) && Failure() == Failure()")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  for comparison of ["Success(1) == Success(\"a\")", "Success(1) == Failure(1)", "ok() == Success(\"a\")"] {
    rejected := checked(prelude + "function f(): bool => " + comparison)
    Assert.equal(rejected.diagnostics.length, 1)
    Assert.stringContains(rejected.diagnostics[0].message, "Operator '==' is not defined for")
  }
}


export function testInclusiveRangeRejectsConstantMaximumIntEnd(): none {
  for source of ["0..2147483647", "1..2147483646 + 1", "-5..(2147483647)"] {
    result := checked("function make(): Range => " + source)
    Assert.equal(result.diagnostics.length, 1)
    Assert.stringContains(result.diagnostics[0].message, "Inclusive range \"..\" cannot end at the maximum int (2147483647)")
  }
  result := checked("function main(): none { for i of 0..2147483647 { } }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].span.start.column, 37)
}

export function testRangeAcceptsBoundsBelowOrExcludingMaximumInt(): none {
  for source of ["0..<2147483647", "0..2147483646", "2147483647..<2147483647", "0..limit"] {
    Assert.equal(checked("function make(limit: int): Range => " + source).diagnostics.length, 0)
  }
  Assert.equal(checked("function size(value: int): int => case value { 0..2147483647 -> 1, _ -> 0 }").diagnostics.length, 0)
}
