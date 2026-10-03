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

export function testStructsDoNotStructurallySatisfyInterfaces(): none {
  result := checked("interface Named { name: string }\nstruct Tag { name: string }\nclass User { name: string }\nfunction main(): none { let named: Named = Tag { name: \"a\" } }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "Cannot assign Tag to Named")
  valid := checked("interface Named { name: string }\nstruct Tag { name: string }\nclass User { name: string }\nfunction main(): none { let named: Named = User { name: \"a\" } }")
  Assert.equal(valid.diagnostics.length, 0)
}

readonly shapeStatics = "interface Shape { static sides: int\nstatic readonly label: string\nstatic unit(scale: int = 2): string\narea(): int }\n"

function diagnosticMessages(result: CheckResult): string {
  let all = ""
  for diagnostic of result.diagnostics { all = all + diagnostic.message + "\n" }
  return all
}

export function testTypeParameterReachesBoundStaticMembers(): none {
  result := checked(shapeStatics +
    "class Square { static sides = 4\nstatic readonly label = \"square\"\nstatic unit(scale: int = 2): string => \"sq\"\nside: int\narea(): int => side }\n" +
    "struct Tri { static sides = 3\nstatic readonly label = \"tri\"\nstatic unit(scale: int = 2): string => \"tri\"\nbase: int\narea(): int => base }\n" +
    "function describe<T: Shape>(shape: T): string => T.label + string(T.sides) + T.unit() + T.unit{scale: 3}\n" +
    "function forward<U: Shape>(shape: U): string => describe(shape)\n" +
    "class Holder<T: Shape> { label(): string => T.label }\n" +
    "function main(): none { describe(Square { side: 1 })\ndescribe(Tri { base: 1 })\nforward(Square { side: 2 })\nHolder<Square> {}.label() }")
  Assert.equal(diagnosticMessages(result), "")
}

export function testBoundStaticMemberTypesAreSubstituted(): none {
  result := checked("interface Source<V> { static make(): V }\nclass Nums { static make(): int => 1 }\nfunction build<V, T: Source<V>>(seed: V): V => T.make()\nfunction main(): int => build<int, Nums>(0)")
  Assert.equal(diagnosticMessages(result), "")
  mismatch := checked("interface Source<V> { static make(): V }\nclass Nums { static make(): int => 1 }\nfunction build<V, T: Source<V>>(seed: V): V => T.make()\nfunction main(): string => build<string, Nums>(\"\")")
  Assert.stringContains(diagnosticMessages(mismatch), "does not satisfy constraint")
}

export function testStaticBoundRejectsArgumentsWithoutStatics(): none {
  prelude := shapeStatics + "function use<T: Shape>(value: T): int => value.area()\n"
  cases: string[] := [
    "class Missing { area(): int => 1 }\nfunction main(): int => use(Missing {})",
    "class Mutable { static let sides = 4\nstatic readonly label = \"m\"\nstatic unit(scale: int = 2): string => \"m\"\narea(): int => 1 }\nfunction main(): int => use(Mutable {})",
    "class Wrong { static sides = 4\nstatic readonly label = \"w\"\nstatic unit(scale: int = 2): int => 1\narea(): int => 1 }\nfunction main(): int => use(Wrong {})",
    "class Hidden { private static sides = 4\nstatic readonly label = \"w\"\nstatic unit(scale: int = 2): string => \"h\"\narea(): int => 1 }\nfunction main(): int => use(Hidden {})",
    "class Ok { static sides = 4\nstatic readonly label = \"w\"\nstatic unit(scale: int = 2): string => \"h\"\narea(): int => 1 }\nfunction main(): int { value: Shape := Ok {}\nreturn use(value) }",
  ]
  for source of cases {
    messages := diagnosticMessages(checked(prelude + source))
    Assert.stringContains(messages, "does not satisfy constraint \"Shape\"")
  }
  Assert.stringContains(diagnosticMessages(checked(prelude + cases[0])), "static members")
}

export function testStaticBoundErrorsForUnknownAndInstanceMembers(): none {
  unknown := checked(shapeStatics + "function bad<T: Shape>(value: T): int => T.nope\nfunction main(): none { }")
  Assert.stringContains(diagnosticMessages(unknown), "has no member \"nope\"")
  instanceThroughType := checked(shapeStatics + "function bad<T: Shape>(value: T): int => T.area()\nfunction main(): none { }")
  Assert.stringContains(diagnosticMessages(instanceThroughType), "Instance member 'area' cannot be accessed through a class")
  staticThroughValue := checked(shapeStatics + "function bad<T: Shape>(value: T): int => value.sides\nfunction main(): none { }")
  Assert.stringContains(diagnosticMessages(staticThroughValue), "has no member \"sides\"")
}

export function testInterfaceStaticMembersDoNotAffectValueMatching(): none {
  result := checked(shapeStatics + "class Plain { area(): int => 1 }\nfunction main(): int { value: Shape := Plain {}\nreturn value.area() }")
  Assert.equal(diagnosticMessages(result), "")
  duplicate := checked("interface Dup { static a: int\nstatic a(): int }\nfunction main(): none { }")
  Assert.stringContains(diagnosticMessages(duplicate), "Static member \"a\" is already declared")
}

export function testInterfaceBoundImpliesJsonMembers(): none {
  result := checked("interface Named { name: string }\nclass User { name: string }\n" +
    "function encode<T: Named>(value: T): SerialValue => value.toSerialObject()\n" +
    "function decode<T: Named>(json: SerialValue): Result<T, string> => T.fromSerialValue(json)\n" +
    "function main(): none { a := encode(User { name: \"a\" })\nb := decode<User>({ name: \"a\" }) }")
  Assert.equal(diagnosticMessages(result), "")
  nonSerialized := checked("interface Named { name: string }\nfunction bad<T: Named>(value: T): SerialValue => value.other()\nfunction main(): none { }")
  Assert.stringContains(diagnosticMessages(nonSerialized), "has no member \"other\"")
}
