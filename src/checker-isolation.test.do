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

export function testValuesCrossingDomainsNeedIsolatedDestructors(): none {
  prefix := "let counter: int[] = []\nclass Token {\nid: int\ndestructor { counter.push(id) } }\nclass Holder { token: Token }\n"
  worker := "class Worker { take(holder: Holder): int => holder.token.id\nhold(token: Token): int => token.id }\n"
  Assert.isTrue(hasMessage(prefix + worker + "function main(): none { worker := Actor<Worker>()\nprintln(worker.take(Holder { token: Token { id: 1 } })) }",
    "Value passed to actor method \"take\" may be released there, but the destructor of class \"Token\" accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "class Keeper { token: Token }\nfunction main(): none { keeper := Actor<Keeper>(Token { id: 1 }) }",
    "Value passed to Actor<Keeper> construction may be released there"))
  Assert.isTrue(hasMessage(prefix + "isolated function read(token: Token): int => token.id\nfunction main(): none { pending := async read(Token { id: 1 })\nprintln(pending.get()) }",
    "Value passed to an async call may be released there"))
  Assert.isTrue(hasMessage(prefix + "function main(): none { token := Token { id: 1 }\npending := async { yield token.id }\nprintln(pending.get()) }",
    "Async block capture \"token\" may be released in the worker"))
  // Root-domain code may release such objects, and isolated destructors may cross.
  Assert.equal(errorCount(prefix + "function main(): none { token := Token { id: 1 }\nprintln(token.id) }"), 0)
  Assert.equal(errorCount("class Token {\nid: int\ndestructor { println(id) } }\nclass Worker { hold(token: Token): int => token.id }\n" +
    "function main(): none { worker := Actor<Worker>()\nprintln(worker.hold(Token { id: 1 })) }"), 0)
}

export function testCrossingDestructorsReachInterfaceImplementations(): none {
  source := "let counter: int[] = []\ninterface Named { name: string }\nclass Token implements Named {\nname: string\ndestructor { counter.push(1) } }\n" +
    "class Worker { hold(named: Named): string => named.name }\nfunction main(): none { worker := Actor<Worker>()\nnamed: Named := Token { name: \"a\" }\nprintln(worker.hold(named)) }"
  Assert.isTrue(hasMessage(source, "the destructor of class \"Token\" accesses mutable module binding \"counter\""))
}

export function testDecodingCountsAsConstruction(): none {
  prefix := "let counter: int[] = []\nclass Tracked {\nuses: int\ndestructor { counter.push(uses) } }\nclass Defaulted { n: int = counter.length }\n"
  Assert.isTrue(hasMessage(prefix + "isolated function load(): int {\nt := Tracked.fromSerialValue({ uses: 1 }) else { return 0 }\nreturn t.uses }", "accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "class Box { items: Tracked[] }\nisolated function load(): bool => Box.fromSerialValue({ items: [] }).isSuccess()", "accesses mutable module binding \"counter\""))
  Assert.isTrue(hasMessage(prefix + "isolated function load(): bool => Defaulted.fromSerialValue({}).isSuccess()", "accesses mutable module binding \"counter\""))
  Assert.equal(errorCount("class Plain { n: int }\nisolated function load(): bool => Plain.fromSerialValue({ n: 1 }).isSuccess()"), 0)
}

export function testUncrossedDestructorsMayTouchModuleState(): none {
  Assert.equal(errorCount("let depth = 0\nclass Guard { destructor { depth -= 1 } }\nfunction enter(): Guard {\ndepth += 1\nreturn Guard {} }\nfunction main(): none { guard := enter() }"), 0)
}

function errorMessages(files: SourceFile[]): string[] {
  result := compile(files, "/main.do")
  let messages: string[] = []
  for diagnostic of result.diagnostics { if diagnostic.severity == "error" { messages.push(diagnostic.message) } }
  return messages
}

// Callers are declared before callees so a node-order sweep would resolve only
// one link per pass.
function callChain(length: int, mutates: bool): string {
  let source = "let shared = 0\nisolated function top(): int => f0()\n"
  for position of 0..<length - 1 { source += "function f" + string(position) + "(): int => f" + string(position + 1) + "()\n" }
  last := "f" + string(length - 1)
  source += if mutates then "function " + last + "(): int { shared += 1\nreturn shared }\n" else "function " + last + "(): int => 1\n"
  return source
}

export function testLongCallChainsPropagateToTheIsolatedRoot(): none {
  messages := errorMessages([SourceFile { path: "/main.do", source: callChain(300, true) }])
  Assert.equal(messages.length, 1)
  Assert.equal(messages[0], "Isolated function \"top\" cannot call non-isolated function \"f0\"")
  Assert.equal(errorCount(callChain(300, false)), 0)
}

export function testRecursiveCyclesReachDirectReasons(): none {
  cycle := "function a(n: int): int => if n == 0 then b(n) else a(n - 1)\nfunction b(n: int): int => if n > 1 then a(n - 1) else c()\n"
  Assert.isTrue(hasMessage("let shared = 0\n" + cycle + "function c(): int { shared += 1\nreturn shared }\nisolated function top(): int => a(3)",
    "Isolated function \"top\" cannot call non-isolated function \"a\""))
  Assert.equal(errorCount(cycle + "function c(): int => 1\nisolated function top(): int => a(3)"), 0)
}

export function testCallReasonsNameTheNearestNonIsolatedCallee(): none {
  // `relay` is non-isolated only through `direct`, so `top` reports `direct`
  // even though it calls `relay` first.
  messages := errorMessages([SourceFile { path: "/main.do", source:
    "let shared = 0\nisolated function top(): int => relay() + direct()\nfunction relay(): int => direct()\nfunction direct(): int { shared += 1\nreturn shared }",
  }])
  Assert.equal(messages.length, 1)
  Assert.equal(messages[0], "Isolated function \"top\" cannot call non-isolated function \"direct\"")
}

export function testInterfaceCallsReachImplementationsInOtherModules(): none {
  shape := SourceFile { path: "/shape.do", source: "export interface Shape { area(): int }" }
  main := SourceFile { path: "/main.do", source:
    "import { Shape } from \"./shape\"\nimport { Square } from \"./square\"\nisolated function measure(s: Shape): int => s.area()\nfunction main(): none { println(measure(Square {})) }",
  }
  noisy := SourceFile { path: "/square.do", source:
    "import { Shape } from \"./shape\"\nlet calls = 0\nexport class Square implements Shape { area(): int { calls += 1\nreturn calls } }",
  }
  quiet := SourceFile { path: "/square.do", source: "import { Shape } from \"./shape\"\nexport class Square implements Shape { area(): int => 4 }" }
  messages := errorMessages([main, shape, noisy])
  Assert.equal(messages.length, 1)
  Assert.equal(messages[0], "Isolated function \"measure\" cannot call non-isolated function \"area\"")
  Assert.equal(errorMessages([main, shape, quiet]).length, 0)
}
