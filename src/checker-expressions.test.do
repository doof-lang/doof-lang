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

export function testInterfaceBoundTypeReceiver(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction invalid<T: Reader<int>>(value: T): int => T.read()")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("Instance member") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundReservedNames(): none {
  result := checked("interface View { metadata: string\nfromJsonValue(): int }\nclass Value { metadata: string\nfromJsonValue(): int => 1 }\nfunction read<T: View>(value: T): string => value.metadata\nfunction call<T: View>(value: T): int => value.fromJsonValue()")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(result.diagnostics.length > 0)
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
