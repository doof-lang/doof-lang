import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testSecondConsolidationIsolationNestedCallTraversal(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "let shared = 0\nfunction unsafe(): int { shared = shared + 1\nreturn shared }\nisolated function nested(): int => 1 + unsafe()",
  }], "/main.do")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("non-isolated") || diagnostic.message.contains("mutable module") { found = true } }
  Assert.isTrue(found)
}

export function testIsolationDiagnosticsPointIntoTheIsolatedFunction(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "let shared = 0\nfunction unsafe(): int { shared = shared + 1\nreturn shared }\nisolated function nested(): int =>\n1 + unsafe()",
  }], "/main.do")
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("non-isolated") || diagnostic.message.contains("mutable module") {
      found = true
      Assert.equal(diagnostic.severity, "error")
      Assert.equal(diagnostic.module, "/main.do")
      Assert.isTrue(diagnostic.span.start.line >= 4)
    }
  }
  Assert.isTrue(found)
}

function hasMessage(source: string, text: string): bool {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of result.diagnostics { if diagnostic.message.contains(text) { return true } }
  return false
}

function errorCount(source: string): int {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  let count = 0
  for diagnostic of result.diagnostics { if diagnostic.severity == "error" { count += 1 } }
  return count
}

export function testUnionReceiverCallsReachEveryMemberMethod(): none {
  prefix := "let counter: int[] = []\nclass A { touch(): none { counter.push(1) } }\nclass B { touch(): none { } }\n"
  Assert.isTrue(hasMessage(prefix + "isolated function poke(x: A | B): none { x.touch() }", "cannot call non-isolated function \"touch\""))
  Assert.isTrue(hasMessage(prefix + "isolated function poke(x: B | A | none): none { x?.touch() }", "cannot call non-isolated function \"touch\""))
  Assert.equal(errorCount("class A { touch(): int => 1 }\nclass B { touch(): int => 2 }\nisolated function poke(x: A | B): int => x.touch()"), 0)
}

export function testConstrainedTypeParameterReceiversReachImplementations(): none {
  source := "let counter: int[] = []\ninterface Toucher { touch(): none }\nclass A implements Toucher { touch(): none { counter.push(1) } }\n" +
    "isolated function poke<T: Toucher>(x: T): none { x.touch() }"
  Assert.isTrue(hasMessage(source, "cannot call non-isolated function \"touch\""))
}

export function testOmittedFieldDefaultsAreConstructionEffects(): none {
  prefix := "let counter: int[] = []\nclass Thing { n: int = counter.length }\n"
  Assert.isTrue(hasMessage(prefix + "isolated function make(): int => Thing {}.n", "accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "isolated function make(): int => Thing().n", "accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "isolated function make(): Thing => {}", "accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "class Outer { inner: Thing = Thing {} }\nisolated function make(): Outer => Outer {}", "accesses mutable module binding \"counter\""))
  Assert.equal(errorCount(prefix + "isolated function make(): int => Thing { n: 3 }.n"), 0)
  Assert.equal(errorCount(prefix + "isolated function make(): int => Thing(3).n"), 0)
}

export function testFieldDefaultReasonsPointAtTheConstruction(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "let counter: int[] = []\nclass Thing { n: int = counter.length }\nisolated function make(): int =>\nThing {}.n",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].span.start.line, 4)
}

export function testStaticConstructorFactoriesAreConstructionEffects(): none {
  source := "let counter: int[] = []\nclass Maker {\nk: int\nstatic constructor(): Maker => Maker { k: counter.length } }\n" +
    "isolated function make(): int => Maker().k"
  Assert.isTrue(hasMessage(source, "cannot call non-isolated function \"constructor\""))
  Assert.equal(errorCount("class Maker {\nk: int\nstatic constructor(): Maker => Maker { k: 1 } }\nisolated function make(): int => Maker().k"), 0)
}

export function testActorMethodsReachFieldDefaultsThroughConstruction(): none {
  source := "let counter: int[] = []\nclass Thing { n: int = counter.length }\nclass Worker { make(): int => Thing {}.n }\n" +
    "function main(): none { worker := Actor<Worker>()\nprintln(worker.make()) }"
  Assert.isTrue(hasMessage(source, "Actor method \"make\" is not isolated: accesses mutable module binding \"counter\""))
}

export function testForOfOverClassStreamsCallsNextAndValue(): none {
  prefix := "let counter: int[] = []\n"
  stream := "class Counter {\nlet current: int\nnext(): bool { current += 1\nreturn current < 3 }\nvalue(): int => current }\n"
  noisyNext := "class Counter {\nlet current: int\nnext(): bool { counter.push(1)\nreturn false }\nvalue(): int => current }\n"
  noisyValue := "class Counter {\nlet current: int\nnext(): bool => false\nvalue(): int => counter.length }\n"
  loop := "isolated function total(): int {\nlet sum = 0\nfor v of Counter(0) { sum += v }\nreturn sum }"
  Assert.isTrue(hasMessage(prefix + noisyNext + loop, "cannot call non-isolated function \"next\""))
  Assert.isTrue(hasMessage(prefix + noisyValue + loop, "cannot call non-isolated function \"value\""))
  Assert.isTrue(hasMessage(prefix + noisyNext + "isolated function total(): int {\nf := (): int => { for v of Counter(0) { return v }\nreturn 0 }\nreturn f() }", "cannot call non-isolated function \"next\""))
  Assert.equal(errorCount(prefix + stream + loop), 0)
}

export function testStreamValuesReachEveryConvertibleClass(): none {
  prefix := "let counter: int[] = []\n"
  noisy := "class Noisy implements Stream<int> {\nnext(): bool { counter.push(1)\nreturn false }\nvalue(): int => 0 }\n"
  quiet := "class Quiet implements Stream<string> {\nnext(): bool { counter.push(1)\nreturn false }\nvalue(): string => \"\" }\n"
  Assert.isTrue(hasMessage(prefix + noisy + "isolated function drain(s: Stream<int>): none { for v of s { } }", "cannot call non-isolated function \"next\""))
  Assert.isTrue(hasMessage(prefix + noisy + "isolated function step(s: Stream<int>): bool => s.next()", "cannot call non-isolated function \"next\""))
  // Only classes convertible to the element type are reachable.
  Assert.equal(errorCount(prefix + quiet + "isolated function drain(s: Stream<int>): none { for v of s { } }"), 0)
}

export function testConstructionAddsDestructorEffects(): none {
  prefix := "let counter: int[] = []\nclass Noisy {\nlet uses: int = 0\ndestructor { counter.push(uses) } }\n"
  Assert.isTrue(hasMessage(prefix + "isolated function make(): none { noisy := Noisy {} }", "accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "isolated function make(): int => Noisy().uses", "accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "class Holder { inner: Noisy = Noisy {} }\nisolated function make(): Holder => Holder {}", "accesses mutable module binding \"counter\""))
  // Ordinary root-domain code may still release such objects.
  Assert.equal(errorCount(prefix + "function make(): none { noisy := Noisy {} }"), 0)
  Assert.equal(errorCount("class Quiet {\nlet uses: int = 0\ndestructor { uses += 1 } }\nisolated function make(): none { quiet := Quiet {} }"), 0)
}

export function testRecursiveDestructorConstructionTerminates(): none {
  source := "let counter: int[] = []\nclass Node {\nlet next: Node | none = none\ndestructor { spare := Node {}\ncounter.push(1) } }\nisolated function make(): none { node := Node {} }"
  Assert.isTrue(hasMessage(source, "accesses mutable module binding \"counter\""))
}

export function testImmutableClassDestructorsMustBeIsolated(): none {
  Assert.isTrue(hasMessage("let counter: int[] = []\nclass Noisy {\nid: int\ndestructor { counter.push(id) } }",
    "Destructor of immutable class \"Noisy\" must be isolated because its instances can cross domains: accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage("let counter: int[] = []\nfunction touch(): none { counter.push(1) }\nclass Noisy { destructor { touch() } }",
    "Destructor of immutable class \"Noisy\" must be isolated because its instances can cross domains: calls non-isolated function \"touch\""))
  // Mutable instances stay in their domain and are covered at construction.
  Assert.equal(errorCount("let counter: int[] = []\nclass Local {\nlet n: int = 0\ndestructor { counter.push(n) } }"), 0)
  Assert.equal(errorCount("class Plain {\nid: int\ndestructor { println(id) } }"), 0)
}
