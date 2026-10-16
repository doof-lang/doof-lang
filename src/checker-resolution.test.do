import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { CheckResult, FunctionType, SourceFile } from "./semantic"
import { serialDecodeType } from "./checker-resolution"
import { primitive, typeName } from "./checker-types"

function checked(source: string): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  return createChecker(analysis, "/main.do").check("/main.do")
}

export function testPromiseOnCompleteAcceptsTypedAndInferredCallbacks(): none {
  for source of [
    `function use(p: Promise<int>, callback: (result: Result<int, string>): none): none { p.onComplete(callback) }`,
    `function use(p: Promise<int>): none { p.onComplete((result) => { case result { value: Success -> println(value.value), error: Failure -> println(error.error) } }) }`,
    `function use(p: Promise<none>): none { p.onComplete((result) => { case result { _: Success -> println("done"), error: Failure -> println(error.error) } }) }`,
    `function use(p: Promise<int[]>): none { p.onComplete((result) => { values := result!; values.push(42) }) }`,
    `function use<T>(p: Promise<T>, callback: (result: Result<T, string>): none): none { p.onComplete(callback) }`,
  ] {
    result := checked(source)
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.isFalse(hasErrorDiagnostics(result.diagnostics))
  }
}

export function testPromiseOnCompleteRejectsInvalidCallbackSignatures(): none {
  for source of [
    `function use(p: Promise<int>): none { p.onComplete() }`,
    `function use(p: Promise<int>): none { p.onComplete(42) }`,
    `function use(p: Promise<int>, callback: (value: int): none): none { p.onComplete(callback) }`,
    `function use(p: Promise<int>, callback: (result: Result<int, bool>): none): none { p.onComplete(callback) }`,
    `function use(p: Promise<int>, callback: (result: Result<int, string>): int): none { p.onComplete(callback) }`,
    `function use(p: Promise<int>, callback: (): none): none { p.onComplete(callback) }`,
  ] {
    result := checked(source)
    Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
    for diagnostic of result.diagnostics {
      Assert.equal(diagnostic.module, "/main.do")
      Assert.isTrue(diagnostic.span.start.line > 0)
    }
  }
}

export function testCallbackTryPostReturnsPromiseResult(): none {
  for source of [
    `function use(callback: (value: int): int): Result<Promise<int>, string> => callback.tryPost(1)`,
    `function use(callback: (): none): none { case callback.tryPost() { s: Success -> s.value.onComplete((result) => { result! }), f: Failure -> println(f.error) } }`,
    `function use(callback: (value: int): int): int => callback.tryPost(1)!.get()!`,
  ] {
    result := checked(source)
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.isFalse(hasErrorDiagnostics(result.diagnostics))
  }
}

export function testCallbackTryPostChecksArgumentsAndResult(): none {
  for source of [
    `function use(callback: (value: int): int): none { callback.tryPost() }`,
    `function use(callback: (value: int): int): none { callback.tryPost("one") }`,
    `function use(callback: (value: int): int): Promise<int> => callback.tryPost(1)`,
    `function use(callback: (value: int): int): Result<Promise<string>, string> => callback.tryPost(1)`,
  ] {
    result := checked(source)
    Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
    for diagnostic of result.diagnostics {
      Assert.equal(diagnostic.module, "/main.do")
      Assert.isTrue(diagnostic.span.start.line > 0)
    }
  }
}

export function testInterfaceBoundMembers(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction readOne<T: Reader<int>>(reader: T): int => reader.read()\nfunction main(): int => readOne(IntReader {})")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testResultPayloadMembersRequireNarrowing(): none {
  for property of ["value", "error"] {
    result := checked("function inspect(result: Result<int, string>): int { " + property + " := result." + property + "\nreturn 0 }")
    Assert.equal(result.diagnostics.length, 1)
    Assert.equal(result.diagnostics[0].message, "Type \"Result<int, string>\" has no member \"" + property + "\"")
  }
  narrowed := checked("function inspect(result: Result<int, string>): int => case result { success: Success -> success.value, _: Failure -> 0 }")
  Assert.equal(narrowed.diagnostics.length, 0)
}

export function testPayloadlessResultArmsHaveNoPayloadMember(): none {
  success := checked("function inspect(result: Result<none, string>): none { case result { value: Success -> { value.value }, _: Failure -> { } } }")
  Assert.equal(success.diagnostics.length, 1)
  Assert.equal(success.diagnostics[0].message, "Type \"Success<none>\" has no member \"value\"")
  failure := checked("function inspect(result: Result<int, none>): none { case result { _: Success -> { }, error: Failure -> { error.error } } }")
  Assert.equal(failure.diagnostics.length, 1)
  Assert.equal(failure.diagnostics[0].message, "Type \"Failure<none>\" has no member \"error\"")
}

export function testInterfaceBoundMissingMember(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction readOne<T: Reader<int>>(reader: T): int => reader.missing()")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("has no member") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundWrongArgument(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nclass Wrong { read(): string => \"bad\" }\nfunction keep<T: Reader<int>>(value: T): T => value\nfunction main(): none { keep(Wrong {}) }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("does not satisfy constraint") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].span.start.line, 5)
  Assert.equal(result.diagnostics[0].module, "/main.do")
}

export function testInterfaceBoundDependentArguments(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction readOne<V, T: Reader<V>>(reader: T, fallback: V): V => reader.read()\nfunction main(): int => readOne(IntReader {}, 0)")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}


export function testInterfaceBoundReadonlyArray(): none {
  result := checked("interface View { readonly values: int[] }\nclass Value { readonly values: int[] = [1] }\nfunction bad<T: View>(value: T): none { value.values.push(2) }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("readonly") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundDoesNotGrantReflectionIntrinsic(): none {
  result := checked("interface Reader<V> { read(): V }\nfunction bad<T: Reader<int>>(value: T): none { T.metadata }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("has no member") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundNoConstraintOnlyInference(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 1 }\nfunction read<V, T: Reader<V>>(value: T): V => value.read()\nfunction main(): none { read(IntReader {}) }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("infer") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testInterfaceBoundDeclarationOrderSignature(): none {
  result := checked("function wrong<T: Reader<int>>(value: T): string => value.read()\ninterface Reader<V> { read(): V }")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("Cannot return") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testCheckerReviewExactNumericBounds(): none {
  prefix := "function add<T: float | double>(a: T, b: T): T => a + b\n"
  valid := checked(prefix + "function good(): double => add(1.0, 2.0)\nfunction forward<U: float | double>(a: U): U => add(a, a)")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  for suffix of ["function bad(): int => add(1, 2)", "function bad(a: float | double): float | double => add(a, a)"] {
    invalid := checked(prefix + suffix)
    let found = false
    for diagnostic of invalid.diagnostics { if diagnostic.message.contains("does not satisfy constraint") { found = true } }
    Assert.isTrue(found)
  }
}

export function testCheckerReviewUnionAssignmentBindings(): none {
  valid := checked("class A { let value: int }\nclass B { let value: int }\nfunction good(item: A | B): none { item.value = 1 }")
  Assert.equal(valid.diagnostics.length, 0)
  immutable := checked("class A { let value: int }\nclass B { value: int }\nfunction bad(item: A | B): none { item.value = 1 }")
  Assert.isTrue(immutable.diagnostics.length > 0)
  Assert.stringContains(immutable.diagnostics[0].message, "immutable field")
  incompatible := checked("class A { let value: int }\nclass B { let value: long }\nfunction bad(item: A | B): none { item.value = 2147483648L }")
  Assert.isTrue(incompatible.diagnostics.length > 0)
}

export function testCheckerConsolidationMemberContractDefaults(): none {
  result := compile([SourceFile { path: "/main.do", source: "interface Reader { read(value: int = 2): int }\nclass C { read(value: int = 9): int => value }\nfunction read<T: Reader>(value: T): int => value.read()\nfunction main(): int { value: Reader := C {}\nreturn read(value) }" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(result.diagnostics), false)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "_obj->read(2)")
}

export function testSecondConsolidationRecursiveAliasDiagnostic(): none {
  result := compile([SourceFile { path: "/main.do", source: "type First = Second\ntype Second = First\nfunction use(value: First): none {}" }], "/main.do")
  Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("Cyclic type alias") { found = true } }
  Assert.isTrue(found)
}

export function testActorFieldAccessReadsRejected(): none {
  for field of ["value", "fixed", "items", "callback"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class State { let value: int = 7\nreadonly fixed: int = 8\nlet items: int[] = []\ncallback: (): int = => 9 }\nfunction bad(actor: Actor<State>): none { actor." + field + " }",
    }], "/main.do")
    let errors = 0
    for diagnostic of result.diagnostics {
      if diagnostic.severity != "error" { continue }
      errors = errors + 1
      Assert.stringContains(diagnostic.message, "Cannot access actor field '" + field + "' directly")
      Assert.stringContains(diagnostic.message, "use an actor method")
      Assert.equal(diagnostic.span.start.line, 5)
      Assert.equal(diagnostic.module, "/main.do")
    }
    Assert.equal(errors, 1)
    Assert.equal(result.emission, none)
  }
}

export function testActorFieldAccessUnionAndCallableRejected(): none {
  for source of [
    "class Stored { value: int = 7 }\nfunction main(): int { actor := Actor<Stored>()\nreturn actor.value }",
    "class State { value: int = 7 }\nfunction bad(actor: Actor<State> | State): int => actor.value",
    "class State { callback: (): int = => 9 }\nfunction bad(actor: Actor<State>): int => actor.callback()",
  ] {
    result := compile([SourceFile { path: "/main.do", source }], "/main.do")
    let found = false
    for diagnostic of result.diagnostics { if diagnostic.message.contains("Cannot access actor field") { found = true } }
    Assert.isTrue(found)
    Assert.equal(result.emission, none)
  }
}

export function testIndexingReportsNonIndexableReceivers(): none {
  sources := [
    "function f(value: int): none { _ := value[0] }",
    "function f(items: int[] | none): none { _ := items[0] }",
    "function f(): none { pair := (1, \"a\")\n_ := pair[0] }",
  ]
  messages := [
    "Type \"int\" cannot be indexed",
    "Cannot index possibly-none value of type \"int[] | none\"; use '?[]' or narrow it first",
    "Tuples cannot be indexed; access elements with '._1', '._2', ...",
  ]
  for index of 0..<sources.length {
    result := checked(sources[index])
    Assert.equal(result.diagnostics.length, 1)
    Assert.equal(result.diagnostics[0].message, messages[index])
  }
}

export function testStringReplaceReturnsString(): none {
  valid := checked("function first(text: string): string => text.replace(\"a\", \"b\")")
  Assert.equal(valid.diagnostics.length, 0)

  wrongArgument := checked("function first(text: string): string => text.replace(1, \"b\")")
  Assert.isTrue(wrongArgument.diagnostics.length > 0)

  missingArgument := checked("function first(text: string): string => text.replace(\"a\")")
  Assert.isTrue(missingArgument.diagnostics.length > 0)
}

export function testInterfaceValuesExposeToSerialObject(): none {
  result := checked(
    "interface Shape { area(): int }\n" +
    "class Square implements Shape { kind: \"square\"\nside: int\narea(): int => side }\n" +
    "class Scene { shapes: Shape[]\nfocus: Shape | none = none }\n" +
    "function encode(shape: Shape): SerialObject => shape.toSerialObject()\n" +
    "function encodeScene(scene: Scene): SerialObject => scene.toSerialObject()\n" +
    "function decodeScene(json: SerialValue): Result<Scene, string> => Scene.fromSerialValue(json)",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isFalse(hasErrorDiagnostics(result.diagnostics))
}

export function testInterfaceSerializationNamesTheBlockingImplementation(): none {
  result := checked(
    "interface Pet { speak(): string }\n" +
    "class Dog implements Pet { name: string\nspeak(): string => name }\n" +
    "class Robot implements Pet { onSpeak: (): string\nspeak(): string => onSpeak() }\n" +
    "function encode(pet: Pet): SerialObject => pet.toSerialObject()",
  )
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Cannot serialize interface \"Pet\": implementing class \"Robot\" does not support automatic JSON serialization")
}

export function testInterfaceSerializationRejectsGenericInterfaces(): none {
  result := checked(
    "interface Box<T> { get(): T }\n" +
    "function encode(box: Box<int>): SerialObject => box.toSerialObject()",
  )
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Automatic JSON serialization is not available on generic interface \"Box\"")
}

export function testInterfaceFieldsDecodeOnlyWithADiscriminator(): none {
  result := checked(
    "interface Pet { speak(): string }\n" +
    "class Dog implements Pet { name: string\nspeak(): string => name }\n" +
    "class Cat implements Pet { lives: int\nspeak(): string => \"meow\" }\n" +
    "class Kennel { pets: Pet[] }\n" +
    "function encode(kennel: Kennel): SerialObject => kennel.toSerialObject()\n" +
    "function decode(json: SerialValue): Result<Kennel, string> => Kennel.fromSerialValue(json)",
  )
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Type \"Kennel\" does not support automatic JSON deserialization")
  Assert.equal(result.diagnostics[0].span.start.line, 8)
}

export function testObjectUnionFieldsExplainAMissingDiscriminator(): none {
  result := checked(
    "class Circle { radius: double }\n" +
    "class Note { text: string }\n" +
    "class Loose { pick: Circle | Note }\n" +
    "function encode(loose: Loose): SerialObject => loose.toSerialObject()\n" +
    "function decode(json: SerialValue): Result<Loose, string> => Loose.fromSerialValue(json)",
  )
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Type \"Loose\" does not support automatic JSON deserialization (field \"pick\" has union type \"Circle | Note\", whose member classes must be non-generic and share a literal-valued string field with distinct values)")
  Assert.equal(result.diagnostics[0].span.start.line, 5)
}

export function testAmbiguousPrimitiveUnionFieldsExplainTheirJsonKind(): none {
  result := checked(
    "class Reading { value: int | double }\n" +
    "function encode(reading: Reading): SerialObject => reading.toSerialObject()\n" +
    "function decode(json: SerialValue): Result<Reading, string> => Reading.fromSerialValue(json)",
  )
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Type \"Reading\" does not support automatic JSON deserialization (field \"value\" has union type \"int | double\", whose members int and double both decode from a JSON number)")
  Assert.equal(result.diagnostics[0].span.start.line, 3)
}

export function testSerialDecodeTypeWrapsTargetInResult(): none {
  decoder := serialDecodeType(primitive("int")) as FunctionType else { panic("expected decoder function") }
  Assert.equal(decoder.params.length, 2)
  Assert.equal(decoder.params[0].name, "value")
  Assert.equal(typeName(decoder.params[0].type_), "SerialValue")
  Assert.isFalse(decoder.params[0].hasDefault)
  Assert.equal(decoder.params[1].name, "lenient")
  Assert.equal(typeName(decoder.params[1].type_), "bool")
  Assert.isTrue(decoder.params[1].hasDefault)
  Assert.equal(typeName(decoder.returnType), "Result<int, string>")
}

export function testCompilerProvidedDecodersShareOneSignature(): none {
  result := checked(
    "enum Color { Red, Green }\nclass Point { x: int = 0 }\ninterface Shape { kind: string }\nclass Square implements Shape { kind: \"square\" }\n" +
    "function color(value: SerialValue): Result<Color, string> => Color.fromSerialValue(value, false)\n" +
    "function point(value: SerialValue): Result<Point, string> => Point.fromSerialValue(value)\n" +
    "function shape(value: SerialValue): Result<Shape, string> => Shape.fromSerialValue(value, true)\n" +
    "function generic<T: Serializable>(value: SerialValue): Result<T, string> => T.fromSerialValue(value)",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

function messages(result: CheckResult): string {
  let found = ""
  for diagnostic of result.diagnostics { found = found + diagnostic.message + "\n" }
  return found
}

export function testReadonlyCollectionsRejectOnlyTheirOwnMutators(): none {
  Assert.equal(messages(checked("function use(m: ReadonlyMap<string, int>, s: ReadonlySet<int>): none { m.set(\"a\", 1)\ns.add(1)\ns.cloneReadonly() }")),
    "Method \"set\" is not available on readonly map\n" +
    "Method \"add\" is not available on readonly set\n" +
    "Method \"cloneReadonly\" is not available on readonly set\n",
  )
  Assert.equal(checked("function use(m: ReadonlyMap<string, int>, s: ReadonlySet<int>): int { return m.size + s.size + m.keys().length + s.values().length }").diagnostics.length, 0)
}

export function testTypeParameterIntrinsicsNameTheirRequiredConstraint(): none {
  Assert.equal(messages(checked("function use<T>(value: T): none { value.toSerialObject()\nT.fromSerialValue(value)\nT.metadata }")),
    "Member \"toSerialObject\" requires type parameter \"T\" to be constrained by Serializable\n" +
    "Static member \"fromSerialValue\" requires type parameter \"T\" to be constrained by Serializable\n" +
    "Static member \"metadata\" requires type parameter \"T\" to be constrained by Reflectable\n",
  )
}

export function testEnumMembersFollowTheBackingKind(): none {
  result := checked("enum Code { Ok = \"ok\", Bad = \"bad\" }\nfunction use(): string { found := Code.fromValue(\"ok\")\nreturn Code.Bad.value + Code.Ok.name + string(Code.values().length) }")
  Assert.equal(result.diagnostics.length, 0)
}
