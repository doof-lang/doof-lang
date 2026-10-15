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

export function testExplicitGenericStaticReceivers(): none {
  source := "class Channel<T> { static tag(): string => \"channel\"\nname(): string => \"c\" }\nclass Plain { static tag(): string => \"plain\" }\n"
  valid := checked(source + "function main(): none { println(Channel<string>.tag()) }")
  Assert.equal(valid.diagnostics.length, 0)

  arity := checked(source + "function main(): none { a := Channel<string, int>.tag() }")
  Assert.equal(arity.diagnostics.length, 1)
  Assert.equal(arity.diagnostics[0].message, "Generic class 'Channel' requires 1 type argument; received 2")

  plain := checked(source + "function main(): none { a := Plain<int>.tag() }")
  Assert.equal(plain.diagnostics.length, 1)
  Assert.equal(plain.diagnostics[0].message, "Class 'Plain' is not generic and takes no type arguments")

  instance := checked(source + "function main(): none { a := Channel<string>.name() }")
  Assert.equal(instance.diagnostics.length, 1)
  Assert.stringContains(instance.diagnostics[0].message, "Instance member 'name' cannot be accessed through a class")

  bounded := checked("interface Shape { area(): double }\nclass Drawer<T: Shape> { static tag(): string => \"drawer\" }\nfunction main(): none { a := Drawer<int>.tag() }")
  Assert.isTrue(bounded.diagnostics.length > 0)
}


export function testOptionalMemberValuesFollowReceiverAbsence(): none {
  valid := checked(
    "class A { x: int = 0\nread(): int => x }\n" +
    "function f(a: A | none, w: weak A): none {\n" +
    "let x: int | none = a?.x\nlet bound: ((): int) | none = a?.read\nlet wx: int | none = w?.x\n" +
    "let forced: int = w!.x\nlet direct: int = a!.x }",
  )
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  rejected := checked("class A { x: int = 0 }\nfunction f(a: A | none, w: weak A): none {\nlet x: int = a?.x\nlet wx: int = w?.x }")
  Assert.equal(rejected.diagnostics.length, 2)
  Assert.equal(rejected.diagnostics[0].message, "Cannot assign int | none to int")
  Assert.equal(rejected.diagnostics[1].message, "Cannot assign int | none to int")
}

export function testUnionAliasDecoderSignature(): none {
  result := checked(
    "class Cat { kind: \"cat\" }\nclass Dog { kind: \"dog\" }\ntype Pet = Cat | Dog\n" +
    "function load(value: SerialValue): Result<Pet, string> => Pet.fromSerialValue(value)\n" +
    "function strict(value: SerialValue): Result<Pet, string> => Pet.fromSerialValue(value, false)",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testMapIndexChecksKeysAgainstTheKeyType(): none {
  result := checked(
    "enum Suit { Spades, Hearts }\n" +
    "function main(): none {\nlet counts: Map<Suit, int> = {}\ncounts[.Spades] = 1\nprintln(counts[.Hearts])\n" +
    "let pairs: Map<Tuple<Suit, string | none>, int> = {}\npairs[(.Hearts, none)] = 2\nprintln(pairs[(.Hearts, \"x\")])\n" +
    "let flags: Map<int | string, bool> = {}\nprintln(flags[1])\n}",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  wrong := checked("function main(): none {\nlet counts: Map<string, int> = {}\nprintln(counts[1])\n}")
  Assert.equal(wrong.diagnostics.length, 1)
  Assert.equal(wrong.diagnostics[0].message, "Invalid map key type")
}
