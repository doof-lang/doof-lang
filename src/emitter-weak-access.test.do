import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

class WeakAccessCounter {
  let count: int = 0
  bump(): none { count += 1 }
  read(): int => count
}
class WeakAccessHolder { weak counter: WeakAccessCounter | none = none }

function weakAccessExpired(): WeakAccessHolder => WeakAccessHolder { counter: WeakAccessCounter {} }
function weakAccessBumpForced(counter: weak WeakAccessCounter): none { counter!.bump() }
function weakAccessBumpOptional(holder: WeakAccessHolder): none { holder.counter?.bump() }
function weakAccessReadOptional(holder: WeakAccessHolder): int | none => holder.counter?.read()
function weakAccessCountOptional(holder: WeakAccessHolder): int | none => holder.counter?.count

export function testWeakAccessRunsAgainstLiveReferent(): none {
  counter := WeakAccessCounter {}
  holder := WeakAccessHolder { counter }
  weakAccessBumpForced(counter)
  weakAccessBumpOptional(holder)
  Assert.equal(counter.count, 2)
  Assert.equal(weakAccessReadOptional(holder) ?? -1, 2)
  Assert.equal(weakAccessCountOptional(holder) ?? -1, 2)
}

export function testOptionalWeakAccessIsAbsentWhenNoneOrExpired(): none {
  holders: WeakAccessHolder[] := [WeakAccessHolder {}, weakAccessExpired()]
  for holder of holders {
    weakAccessBumpOptional(holder)
    Assert.isTrue(weakAccessReadOptional(holder) == none)
    Assert.isTrue(weakAccessCountOptional(holder) == none)
  }
}

export function testUnitWeakCallsEmitStatementBodies(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Node { touch(): none { } }\nclass Holder { weak node: Node | none = none }\n" +
    "function forced(node: weak Node): none { node!.touch() }\nfunction optional(holder: Holder): none { holder.node?.touch() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "[&]() -> void { auto _weak_storage_")
  Assert.stringContains(source, "if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\");")
  // An absent optional receiver and an expired reference both skip the call.
  Assert.stringContains(source, ".has_value()) return; auto _weak_locked")
  Assert.stringContains(source, "if (!_weak_locked.has_value()) return; auto _weak_value_")
  Assert.stringNotContains(source, "return _weak_value_")
}
