// Binding conditions run here as compiled Doof, then their lowering is
// inspected for single evaluation and a single copy of each branch body.

import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

class ConditionUser { name: string; let owner: int }
struct ConditionPoint { let x: int; y: int }
class ConditionNode { value: int; next: ConditionNode | none = none }
class ConditionCounter { let calls: int = 0 }

function conditionUser(name: string): ConditionUser | none {
  return if name == "" then none else ConditionUser { name, owner: name.length }
}

function conditionParse(text: string): Result<int, string> {
  return if text == "1" then Success(1) else Failure("bad " + text)
}

function conditionDeep(text: string): Result<int | none, string> | none {
  if text == "" { return none }
  if text == "n" { return Success(none) }
  if text == "1" { return Success(1) }
  return Failure("bad " + text)
}

function conditionTick(counter: ConditionCounter, limit: int): int | none {
  counter.calls = counter.calls + 1
  return if counter.calls <= limit then counter.calls else none
}

export function testIfBindingsRunTheirBodyOnlyWhenEveryClauseHolds(): none {
  let seen = ""
  if user := conditionUser("ann") && user.owner == 3 { seen = user.name }
  Assert.equal(seen, "ann")
  if user := conditionUser("bob") && user.owner == 9 { seen = "wrong" } else { seen = "owner mismatch" }
  Assert.equal(seen, "owner mismatch")
  if user := conditionUser("") { seen = "wrong" } else { seen = "absent" }
  Assert.equal(seen, "absent")
  if _ := conditionUser("x") { seen = "present" }
  Assert.equal(seen, "present")
}

export function testIfBindingsUnwrapEveryAbsentLayer(): none {
  let results = ""
  for text of ["", "n", "1", "z"] {
    if value := conditionDeep(text) { results = results + "value " + string(value) + "|" } else error { results = results + "absent " + (error ?? "none") + "|" }
  }
  Assert.equal(results, "absent none|absent none|value 1|absent bad z|")
  let captured = ""
  if value := conditionParse("x") { captured = "wrong" } else error { captured = error }
  Assert.equal(captured, "bad x")
}

export function testElseIfChainsEvaluateEachBranchOnce(): none {
  let order = ""
  for text of ["1", "x", "y"] {
    if value := conditionParse(text) && value > 0 {
      order = order + "first|"
    } else if text == "x" {
      order = order + "second|"
    } else if user := conditionUser(text) {
      order = order + "third " + user.name + "|"
    } else {
      order = order + "else|"
    }
  }
  Assert.equal(order, "first|second|third y|")
}

export function testSubjectsAreEvaluatedOnceAndInOrder(): none {
  counter := ConditionCounter {}
  let pair = ""
  if a := conditionTick(counter, 5) && b := conditionTick(counter, 5) && a < b { pair = string(a) + "," + string(b) }
  Assert.equal(pair, "1,2")
  Assert.equal(counter.calls, 2)
  // A failed clause stops evaluation of later clauses.
  stopped := ConditionCounter { calls: 10 }
  if a := conditionTick(stopped, 5) && b := conditionTick(stopped, 5) { pair = "wrong" }
  Assert.equal(stopped.calls, 11)
}

export function testBindingsCopyStructsAndShareClasses(): none {
  let maybePoint: ConditionPoint | none = ConditionPoint { x: 1, y: 2 }
  if point := maybePoint {
    maybePoint = ConditionPoint { x: 5, y: 6 }
    Assert.equal(point.x, 1)
  }
  maybeUser := conditionUser("ann")
  if user := maybeUser { user.owner = 42 }
  Assert.equal(maybeUser!.owner, 42)
}

export function testWhileBindingsRebindEachIterationAndKeepLoopControl(): none {
  counter := ConditionCounter {}
  let total = 0
  while value := conditionTick(counter, 4) {
    if value == 2 { continue }
    total = total + value
  } then { total = total + 100 }
  Assert.equal(total, 108)
  head := ConditionNode { value: 1, next: ConditionNode { value: 200, next: ConditionNode { value: 3 } } }
  let sum = 0
  let cursor: ConditionNode | none = head
  outer: while node := cursor && node.value > 0 {
    sum = sum + node.value
    if sum > 100 { break outer }
    cursor = node.next
  } then { sum = sum + 1000 }
  Assert.equal(sum, 201)
}

export function testIfExpressionsBindInTheirThenValue(): none {
  maybeUser := conditionUser("ann")
  Assert.equal(if user := maybeUser then user.name else "guest", "ann")
  Assert.equal(if user := conditionUser("") then user.name else "guest", "guest")
  greeting := (name: string): string => if user := conditionUser(name) && user.owner > 1 then "hi " + user.name else "anon"
  Assert.equal(greeting("bo"), "hi bo")
  Assert.equal(greeting("b"), "anon")
}

export function testAnnotatedBindingsConvertToTheirDeclaredType(): none {
  if value: int | string := conditionParse("1") {
    case value {
      count: int -> { Assert.equal(count, 1) }
      _: string -> { panic("expected the int arm") }
    }
  } else {
    panic("expected a present value")
  }
}

function emittedSource(source: string): string {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let emitted = ""
  for module of result.emission!.modules { emitted = emitted + module.source }
  return emitted
}

export function testMultiClauseConditionsEmitTheElseBodyOnce(): none {
  source := emittedSource("function find(): int | none => 1\n" +
    "function run(): none { if value := find() && value > 0 { println(\"then-body\") } else { println(\"else-body\") } }")
  Assert.equal(source.split("else-body").length, 2)
  Assert.equal(source.split("find()").length, 2)
  Assert.stringContains(source, "_condition_held_")
}

export function testSingleClauseConditionsCaptureFromTheTestedValue(): none {
  source := emittedSource("function load(): Result<int, string> => Success(1)\n" +
    "function run(): none { if value := load() { println(value) } else problem { println(problem) } }")
  Assert.stringContains(source, "doof::failure_error(_condition_value_")
  Assert.stringNotContains(source, "_condition_held_")
}

export function testWhileBindingsLowerToAnInLoopHead(): none {
  source := emittedSource("function next(): int | none => none\n" +
    "function run(): none { while value := next() { println(value) } }")
  Assert.stringContains(source, "while (true)")
  Assert.stringContains(source, ") break;")
}

function conditionSave(ok: bool): Result<none, string> {
  return if ok then Success() else Failure("disk full")
}

export function testDiscardBindingsTestResultNoneForSuccess(): none {
  let log = ""
  for ok of [true, false] {
    if _ := conditionSave(ok) { log = log + "saved|" } else error { log = log + error + "|" }
  }
  Assert.equal(log, "saved|disk full|")
  let loops = 0
  while _ := conditionSave(loops < 2) { loops = loops + 1 }
  Assert.equal(loops, 2)
}
