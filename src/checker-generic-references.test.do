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

function messages(result: CheckResult): string {
  let all = ""
  for diagnostic of result.diagnostics { all = all + diagnostic.message + "\n" }
  return all
}

readonly prelude = "function identity<T>(value: T): T => value\n" +
  "function second<A, B>(a: A, b: B): B => b\n" +
  "function apply(g: (value: int): int): int => g(4)\n" +
  "class Box { wrap<T>(value: T): T[] => [value]\nstatic make<T>(value: T): T[] => [value] }\n"

export function testGenericReferencesInstantiateFromTheExpectedFunctionType(): none {
  result := checked(prelude +
    "function main(): none {\n" +
    "  a := apply(identity)\n" +
    "  let h: (value: string): string = identity\n" +
    "  let p: (a: int, b: string): string = second\n" +
    "  b := Box {}\n" +
    "  let w: (value: int): int[] = b.wrap\n" +
    "  let m: (value: bool): bool[] = Box.make\n" +
    "  opt: ((value: int): int) | none := identity\n" +
    "  direct := identity(3)\n" +
    "}")
  Assert.equal(messages(result), "")
}

export function testGenericReferencesWithoutContextAreRejected(): none {
  result := checked(prelude + "function main(): none { f := identity }")
  Assert.stringContains(messages(result), "Generic function 'identity' can only be used as a value where a function type is expected")
}

export function testGenericReferenceReportsUninferredTypeArguments(): none {
  result := checked("function fresh<T>(): none { }\nfunction main(): none { let f: (): none = fresh }")
  Assert.stringContains(messages(result), "Cannot infer type argument 'T' of generic function 'fresh' from expected type (): none")
}

export function testGenericReferenceChecksConstraints(): none {
  result := checked("interface Named { name: string }\nfunction label<T: Named>(value: T): string => value.name\n" +
    "function main(): none { let f: (value: int): string = label }")
  Assert.stringContains(messages(result), "does not satisfy constraint \"Named\"")
}

export function testOptionalReceiverMethodValuesAreOptional(): none {
  source := "class Sq { name(scale: int): string => \"s\" }\n"
  result := checked(source + "function main(): none { s: Sq | none := Sq {}\nlet m: (scale: int): string = s?.name }")
  Assert.stringContains(messages(result), "Cannot assign")
  allowed := checked(source + "function main(): none { s: Sq | none := Sq {}\nw: weak Sq := Sq {}\n" +
    "let m: ((scale: int): string) | none = s?.name\nlet k: ((scale: int): string) | none = w?.name\nlet f: (scale: int): string = w!.name\n" +
    "text: string | none := s?.name(2) }")
  Assert.equal(messages(allowed), "")
}

export function testGenericReferencesInstantiateInsideGenericCalls(): none {
  result := checked(prelude + "function applyGeneric<V>(g: (value: V): V, v: V): V => g(v)\n" +
    "function main(): none { items := [1, 2]\nmapped := items.map(identity)\nlet first: int = mapped[0]\nlet chosen: int = applyGeneric(identity, 9) }")
  Assert.equal(messages(result), "")
}
