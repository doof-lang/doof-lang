import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testAsyncUnitCallOmitsUnusedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "isolated function effect(): none {}\nfunction main(): none { task := async effect() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source,
    "doof::submit_async<void>([=]() { effect(); })")
}

export function testRestrictedAsyncYieldCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function run(flag: bool): Promise<int | none> => async { if flag { yield 1 } else { yield none } }\nfunction main(): none { run(true) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "return std::nullopt;")
}

export function testRestrictedAsyncYieldRuntime(): none {
  task := async { if true { yield none } else { yield 1 } }
  // A none success value is the yielded value, not an absent result.
  let value: int | none = 0
  case task.get() {
    s: Success -> { value = s.value }
    _: Failure -> { panic("async yield failed") }
  }
  Assert.isTrue(value == none)
}

export function testSecondConsolidationActorStoredAndFactoryDefaults(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Stored { kind: \"stored\"\nvalue: int = 7 }\nclass Factory { value: int\nstatic constructor(value: int = 9): Factory => Factory { value } }\nfunction make(): none { first := Actor<Stored>()\nsecond := Actor<Factory>() }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "Stored{7}")
  Assert.stringContains(source, "Factory::constructor(9)")
}

export function testReadonlyEmissionActorUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction build(): none { actor := Actor<Item>() }" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}

class HoistBox {
  let value: int = 0
  get(): int => this.value
  set(value: int): none { this.value = value }
  configure(first: int, second: int = 10, third: int = 100): int {
    this.value = first * 100 + second * 10 + third
    return this.value
  }
}

function hoistTake(values: int[]): int => values.pop()!

isolated function hoistTwice(value: int): int => value * 2

export function testActorCallArgumentsLowerBeforeDispatch(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Box { let value: int = 0\nget(): int => this.value\nset(value: int): none { this.value = value } }\nfunction main(): none { box := Actor<Box>()\nbox.set(box.get() + 1)\ntask := async box.set(2) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  // The receiver and argument are caller-side locals moved into the message,
  // so a queued message never refers to the caller's frame.
  Assert.stringContains(source, "auto _actor_arg_")
  Assert.stringContains(source, "->template call_sync<int32_t>([](Box& _self) -> int32_t { return _self.get(); })")
  Assert.stringContains(source, "->template call_sync<void>([=, _actor_arg_")
  Assert.stringContains(source, "->template call_async<void>([=, _actor_arg_")
  Assert.stringContains(source, " = std::move(_actor_arg_")
  Assert.isFalse(source.contains("[&](Box& _self)"))
}

export function testIsolatedAsyncCallArgumentsLowerBeforeSubmit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "isolated function twice(value: int): int => value * 2\nfunction main(): none { let values = [1, 2, 3]\ntask := async twice(values.pop()!) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "auto _async_arg_")
  Assert.stringContains(source, "doof::submit_async<int32_t>([=]() -> int32_t { return twice(_async_arg_")
}

export function testSyncActorCallArgumentReadsSameActor(): none {
  box := Actor<HoistBox>()
  // The argument call completes before `set` is queued, so this is not a
  // self-call from inside the actor.
  box.set(box.get() + 1)
  Assert.equal(box.get(), 1)
}

export function testActorCallArgumentUsesCallerCallback(): none {
  box := Actor<HoistBox>()
  double := (value: int): int => value * 2
  box.set(double(21))
  Assert.equal(box.get(), 42)
}

export function testAsyncActorCallArgumentRunsBeforeReturn(): none {
  box := Actor<HoistBox>()
  values := [1, 2, 3]
  task := async box.set(hoistTake(values))
  // The caller's array is popped before `async` returns, not on the actor.
  Assert.equal(values.length, 2)
  task.get()!
  Assert.equal(box.get(), 3)
}

export function testActorCallNamedArgumentsAndDefaults(): none {
  box := Actor<HoistBox>()
  Assert.equal(box.configure{ third: 3, first: 1 }, 203)
  Assert.equal(box.configure(2, 5), 350)
  task := async box.configure{ second: 4, first: 7 }
  Assert.equal(task.get()!, 840)
}

export function testIsolatedAsyncCallArgumentRunsBeforeReturn(): none {
  values := [1, 2, 3]
  task := async hoistTwice(hoistTake(values))
  Assert.equal(values.length, 2)
  Assert.equal(task.get()!, 6)
}

class SelfCallingPeer {
  let peer: Actor<SelfCallingPeer> | none = none
  let seen: string = "unset"
  attach(peer: Actor<SelfCallingPeer>): none { this.peer = peer }
  show(label: string, body: string): none { this.seen = label + ":" + string(body.length) }
  poke(): string {
    label := "label-" + string(42)
    let body = ""
    for i of 0..<512 { body = body + "x" }
    result := catchPanic(=> { this.peer!.show(label, body) })
    case result {
      _: Success -> { return "no panic" }
      failure: Failure -> { return failure.error }
    }
  }
  read(): string => this.seen
}

export function testDeadlockedSyncActorCallIsNeverQueued(): none {
  // The self-call panics before its message is queued, so the message cannot
  // later run against the caller's unwound operands.
  peer := Actor<SelfCallingPeer>()
  peer.attach(peer)
  Assert.stringContains(peer.poke(), "deadlock: blocking wait would never complete (synchronous actor call)")
  Assert.equal(peer.read(), "unset")
  state := retire peer
  Assert.equal(state.seen, "unset")
}
