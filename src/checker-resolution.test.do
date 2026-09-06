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

export function testInterfaceBoundMembers(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction readOne<T: Reader<int>>(reader: T): int => reader.read()\nfunction main(): int => readOne(IntReader {})")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
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

export function testInterfaceBoundDoesNotGrantJsonIntrinsic(): none {
  result := checked("interface Reader<V> { read(): V }\nfunction bad<T: Reader<int>>(value: T): none { T.fromJsonValue(value) }")
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
