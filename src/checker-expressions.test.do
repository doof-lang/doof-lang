import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
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
  result := checked("interface View { metadata: string\nfromSerialValue(): int }\nclass Value { metadata: string\nfromSerialValue(): int => 1 }\nfunction read<T: View>(value: T): string => value.metadata\nfunction call<T: View>(value: T): int => value.fromSerialValue()")
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

export function testCheckerConsolidationActorConstructorDefaults(): none {
  result := compile([SourceFile { path: "/main.do", source: "class Worker { value: int\nstatic constructor(value: int = 4): Worker => Worker { value }\nread(): int => value }\nfunction main(): int { actor := Actor<Worker>()\nreturn actor.read() }" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(result.diagnostics), false)
  Assert.isTrue(result.emission != none)
}

export function testSecondConsolidationActorFactoryMustReturnDirectOwner(): none {
  result := checked("class Worker { value: int\nstatic constructor(value: int): Result<Worker, string> => Success { value: Worker { value } } }\nfunction make(): none { worker := Actor<Worker>(3) }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("must return Worker directly") { found = true } }
  Assert.isTrue(found)
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

export function testEditorCheckerExpressionsRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}

export function testPlainMemberAccessRejectsPossiblyNoneReceivers(): none {
  for access of ["s.length", "a.x", "a.read()"] {
    result := checked("class A { x: int\nread(): int => x }\nfunction f(s: string | none, a: A | none): none { _ := " + access + " }")
    Assert.equal(result.diagnostics.length, 1)
    Assert.stringContains(result.diagnostics[0].message, "on possibly-none value")
    Assert.stringContains(result.diagnostics[0].message, "use '?.', '!.', or narrow it first")
  }
  assigned := checked("class A { let x: int }\nfunction f(a: A | none): none { a.x = 3 }")
  Assert.isTrue(assigned.diagnostics.length > 0)
  Assert.stringContains(assigned.diagnostics[0].message, "on possibly-none value")
  explicit := checked("class A { x: int }\nfunction f(s: string | none, a: A | none): int { n := s?.length\nreturn a!.x + s!.length }")
  for diagnostic of explicit.diagnostics { println(diagnostic.message) }
  Assert.equal(explicit.diagnostics.length, 0)
}

export function testOptionalChainingTypesAndTargets(): none {
  typed := checked(
    "class A { x: int\nread(): string => \"a\"\nrun(): none { } }\n" +
    "function f(a: A | none, items: int[] | none): none {\n" +
    "let x: int | none = a?.x\nlet r: string | none = a?.read()\na?.run()\nlet first: int | none = items?[0] }",
  )
  for diagnostic of typed.diagnostics { println(diagnostic.message) }
  Assert.equal(typed.diagnostics.length, 0)
  narrowing := checked("function f(items: int[] | none): none { let first: int = items?[0] }")
  Assert.equal(narrowing.diagnostics.length, 1)
  Assert.equal(narrowing.diagnostics[0].message, "Cannot assign int | none to int")
  member := checked("class A { let x: int }\nfunction f(a: A | none): none { a?.x = 1 }")
  Assert.isTrue(member.diagnostics.length > 0)
  Assert.equal(member.diagnostics[0].message, "Optional chaining '?.' cannot be used as an assignment target")
  index := checked("function f(items: int[] | none): none { items?[0] = 1 }")
  Assert.isTrue(index.diagnostics.length > 0)
  Assert.equal(index.diagnostics[0].message, "Optional indexing '?[]' cannot be used as an assignment target")
}

export function testOptionalChainingOverResultReceivers(): none {
  prelude := "enum LookupError { Missing }\nenum ProfileError { Private }\nclass Profile { bio: string }\n" +
    "class User { name: string\nprofile(): Result<Profile, ProfileError> => Success(Profile { bio: name })\nshout(): string => name\nping(): none { } }\n" +
    "function findUser(): Result<User, LookupError> => Success(User { name: \"ada\" })\n" +
    "function maybeUser(): Result<User | none, LookupError> => Success(none)\n" +
    "function outerUser(): Result<User, LookupError> | none => none\n"
  // The receiver's Failure and none are both absent; a Result-returning
  // member keeps its own Failure and receives the none in its success value.
  typed := checked(prelude +
    "function f(): none {\n" +
    "let name: string | none = findUser()?.name\n" +
    "let profile: Result<Profile | none, ProfileError> = findUser()?.profile()\n" +
    "let bio: string | none = findUser()?.profile()?.bio\n" +
    "let shout: string | none = maybeUser()?.shout()\n" +
    "let outer: string | none = outerUser()?.name\n" +
    "let forced: string = maybeUser()!.name\n" +
    "findUser()?.ping() }")
  for diagnostic of typed.diagnostics { println(diagnostic.message) }
  Assert.equal(typed.diagnostics.length, 0)
  widened := checked(prelude + "function f(): none { let name: string = findUser()?.name }")
  Assert.equal(widened.diagnostics.length, 1)
  Assert.equal(widened.diagnostics[0].message, "Cannot assign string | none to string")
  plain := checked(prelude + "function f(): none { _ := findUser().name }")
  Assert.equal(plain.diagnostics.length, 1)
  Assert.stringContains(plain.diagnostics[0].message, "has no member \"name\"")
  noValue := checked(prelude + "function done(): Result<none, LookupError> => Success()\nfunction f(): none { _ := done()?.name }")
  Assert.equal(noValue.diagnostics.length, 1)
  Assert.stringContains(noValue.diagnostics[0].message, "the Result has no success value")
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

export function testUnionAliasesExposeJsonDecoders(): none {
  shapes := "class Circle { kind: \"circle\"\nradius: double }\nclass Rect { kind: \"rect\"\nwidth: double }\ntype Shape = Circle | Rect\n"
  valid := checked(shapes + "function decode(input: SerialValue): Result<Shape, string> => Shape.fromSerialValue(input)\nfunction lenient(input: SerialValue): Result<Shape, string> => Shape.fromSerialValue(input, true)")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  undiscriminated := checked("class A { name: string }\nclass B { name: string }\ntype AB = A | B\nfunction decode(input: SerialValue): Result<AB, string> => AB.fromSerialValue(input)")
  Assert.equal(undiscriminated.diagnostics.length, 1)
  Assert.stringContains(undiscriminated.diagnostics[0].message, "Cannot deserialize type alias \"AB\": it must be a union of classes")
  primitives := checked("type Num = int | string\nfunction decode(input: SerialValue): Result<Num, string> => Num.fromSerialValue(input)")
  Assert.equal(primitives.diagnostics.length, 1)
  Assert.stringContains(primitives.diagnostics[0].message, "Cannot deserialize type alias \"Num\"")
  // Only the decoder is available; the alias is still not a value.
  asValue := checked(shapes + "function main(): none { shape := Shape }")
  Assert.equal(asValue.diagnostics.length, 1)
  Assert.stringContains(asValue.diagnostics[0].message, "Type 'Shape' cannot be used as a value")
}

function shorthandMessages(declarations: string): string[] {
  prelude := "class Matrix {\nvalue: int\nstatic count = 3\nstatic readonly maybe: Matrix | none = none\nstatic zero = Matrix { value: 0 }\nstatic label(): string => \"m\"\nstatic identity(): Matrix => Matrix { value: 1 }\nstatic find(text: string): Matrix | none => none\n}\n"
  result := compile([SourceFile { path: "/main.do", source: prelude + declarations + "\nfunction main(): none {}" }], "/main.do")
  let found: string[] = []
  for diagnostic of result.diagnostics { found.push(diagnostic.message) }
  return found
}

export function testStaticShorthandResolvesFieldsAndFactories(): none {
  for declaration of [
    "function a(m: Matrix = .identity(), z: Matrix = .zero): none {}",
    "function b(m: Matrix | none = .find(\"x\"), n: Matrix | none = .maybe, o: Matrix | none = .identity()): none {}",
    "class Holder { m: Matrix = .identity()\nn: Matrix | none = .find(\"x\") }",
    "function c(): none { m: Matrix := .identity()\nn: Matrix | none := .find(\"x\") }",
    "function take(m: Matrix): none {}\nfunction d(): none { take(.identity()) }",
  ] {
    found := shorthandMessages(declaration)
    for message of found { println(declaration + ": " + message) }
    Assert.equal(found.length, 0)
  }
}

export function testStaticShorthandMustProduceTheExpectedClass(): none {
  for pair of [
    ["function a(m: Matrix = .label()): none {}", "Shorthand .label must name a static method returning Matrix; it returns string"],
    ["function a(m: Matrix = .find(\"x\")): none {}", "Shorthand .find must name a static method returning Matrix; it returns Matrix | none"],
    ["function a(m: Matrix | none = .label()): none {}", "Shorthand .label must name a static method returning Matrix or Matrix | none; it returns string"],
    ["function a(m: Matrix = .count): none {}", "Shorthand .count must name a static field of type Matrix; it has type int"],
    ["function a(m: Matrix = .maybe): none {}", "Shorthand .maybe must name a static field of type Matrix; it has type Matrix | none"],
    ["function a(m: Matrix = .missing()): none {}", "Type \"Matrix\" has no static member \"missing\""],
    ["function a(): none { x := .identity() }", "Cannot resolve shorthand .identity without an expected class or enum type"],
  ] {
    found := shorthandMessages(pair[0])
    for message of found { println(pair[0] + ": " + message) }
    Assert.equal(found.length, 1)
    Assert.equal(found[0], pair[1])
  }
}

export function testForceAccessUnwrapsResultReceivers(): none {
  prelude := "enum Color { Red }\nclass User { email: string\nemailOf(): string => email }\n" +
    "function load(): Result<User, string> => Success(User { email: \"a\" })\n" +
    "function maybe(): Result<User | none, string> => Success(none)\n" +
    "function color(): Result<Color, string> => Success(.Red)\n"
  typed := checked(prelude + "function f(): none {\nlet a: string = load()!.email\nlet b: string = load()!.emailOf()\nlet c: string = maybe()!.email\nlet d: string = color()!.name }")
  for diagnostic of typed.diagnostics { println(diagnostic.message) }
  Assert.equal(typed.diagnostics.length, 0)
  empty := checked("function save(): Result<none, string> => Success()\nfunction f(): none { _ := save()!.size }")
  Assert.equal(empty.diagnostics.length, 1)
  Assert.equal(empty.diagnostics[0].message, "Cannot access member \"size\" on Result<none, string>: the Result has no success value")
  helper := checked(prelude + "function f(): none { _ := load()!.isSuccess() }")
  Assert.equal(helper.diagnostics.length, 1)
  Assert.stringContains(helper.diagnostics[0].message, "has no member \"isSuccess\"")
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
