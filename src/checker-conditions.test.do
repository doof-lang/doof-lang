import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker, validateCheckedTypes } from "./checker"
import { CheckResult, SourceFile } from "./semantic"

function checked(source: string): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  result := createChecker(analysis, "/main.do").check("/main.do")
  if result.diagnostics.length == 0 { Assert.equal(validateCheckedTypes(analysis).length, 0) }
  return result
}

function accepts(source: string): none {
  result := checked(source)
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

// The only diagnostic must contain `message`: rejections must not cascade.
function rejects(source: string, message: string): none {
  result := checked(source)
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, message)
}

readonly declarations = "class User { name: string; owner: int }\n" +
  "struct Point { x: int; y: int }\n" +
  "function find(): User | none => none\n" +
  "function load(): Result<int, string> => Success(1)\n" +
  "function deep(): Result<int | none, string> | none => none\n" +
  "function save(): Result<none, string> => Success()\n"

export function testBindingClausesBindEveryPresentShape(): none {
  accepts(declarations + "function run(): none {\n" +
    "  if user := find() { u: User := user }\n" +
    "  if value := load() { v: int := value }\n" +
    "  if value := deep() { v: int := value }\n" +
    "  if typed: int | string := load() { println(typed) }\n" +
    "  if _ := find() { println(\"present\") }\n" +
    "}")
}

export function testBindingsReachLaterClausesAndBodyOnly(): none {
  accepts(declarations + "function run(owner: int): int {\n" +
    "  if user := find() && user.owner == owner && value := load() && value > user.owner { return value }\n" +
    "  return 0\n" +
    "}")
  // A binding is unbound in the else branch and in later else-if conditions.
  rejects(declarations + "function run(): none { if user := find() { } else { println(user.name) } }", "\"user\" is not in scope here")
  rejects(declarations + "function run(): none { if user := find() { } else if user.owner > 0 { } }", "\"user\" is not in scope here")
  rejects(declarations + "function run(): none { if user := find() { }\nprintln(user.name) }", "Unknown identifier 'user'")
  // An else-if condition may bind its own value under the same name.
  accepts(declarations + "function run(other: User | none): none { if user := find() { } else if user := other { println(user.name) } }")
}

export function testConditionScopeAllowsShadowingAnOuterName(): none {
  accepts(declarations + "function run(user: User | none): string {\n" +
    "  if user := user { return user.name }\n" +
    "  return \"\"\n" +
    "}")
  rejects(declarations + "function run(): none { if user := find() && user := find() { } }", "Binding 'user' is already declared in this condition")
}

export function testBindingsAreImmutable(): none {
  rejects(declarations + "function run(): none { if user := find() { user = User { name: \"x\", owner: 1 } } }", "user")
}

export function testBindingClausesRejectSubjectsWithoutAPresentValue(): none {
  rejects(declarations + "function run(count: int): none { if value := count { } }", "Binding condition requires a nullable or Result value; \"count\" has type \"int\"")
  rejects(declarations + "function run(flag: bool): none { if value := flag { } }", "\"flag\" has type \"bool\"")
  rejects(declarations + "function run(value: int | string): none { if text := value { } }", "requires a nullable or Result value")
  rejects(declarations + "function run(): none { if saved := save() { } }", "Cannot bind a none success value; use a discard binding '_ := expr'")
  // A discard tests for success, with or without capturing the failure.
  accepts(declarations + "function run(): none { if _ := save() { println(\"saved\") } else error { println(error) } }")
  rejects(declarations + "function run(): none { if name: string := load() { } }", "Cannot assign int to string")
}

export function testAsSubjectsNarrowThroughTheirResult(): none {
  accepts("interface Shape { area(): int }\n" +
    "class Circle implements Shape { radius: int; area(): int => radius }\n" +
    "class Square implements Shape { side: int; area(): int => side }\n" +
    "function run(shape: Shape, value: int | string, raw: SerialValue): int {\n" +
    "  if circle := shape as Circle { return circle.radius }\n" +
    "  if count := value as int && count > 0 { return count }\n" +
    "  if small := 300 as byte { return int(small) }\n" +
    "  if number := raw as int { return number }\n" +
    "  return 0\n" +
    "}")
}

export function testFailureCaptureNeedsOneResultClause(): none {
  accepts(declarations + "function run(): none { if value := load() { println(value) } else error { e: string := error } }")
  // A subject that is also nullable captures `E | none`.
  accepts(declarations + "function run(): none { if value := deep() { } else error { e: string | none := error } }")
  // The capture belongs to the last condition in an else-if chain.
  accepts(declarations + "function run(ready: bool): none { if ready { } else if value := load() { } else error { println(error) } }")
  accepts(declarations + "function run(): none { if value := load() { } else _ { } }")
  rejects(declarations + "function run(): none { if value := load() && value > 0 { } else error { println(error) } }", "Failure capture requires a condition that is a single Result binding clause")
  rejects(declarations + "function run(): none { if user := find() { } else error { println(error) } }", "Failure capture requires a Result binding clause; \"User | none\" can only be absent as none")
  rejects(declarations + "function run(ready: bool): none { if ready { } else error { println(error) } }", "Failure capture requires a condition that is a single Result binding clause")
  // Without a capture, the Failure payload is discarded.
  accepts(declarations + "function run(): none { if value := load() { println(value) } else { println(\"failed\") } }")
}

export function testWhileBindingsAreFreshPerIterationAndScopedToTheBody(): none {
  accepts(declarations + "function run(): int {\n" +
    "  let total = 0\n" +
    "  while value := load() && value < 10 { total = total + value\nif total > 5 { break } } then { total = total + 1 }\n" +
    "  return total\n" +
    "}")
  rejects(declarations + "function run(): none { while value := load() { } then { println(value) } }", "Unknown identifier 'value'")
}

export function testIfExpressionsBindInTheirThenBranch(): none {
  accepts(declarations + "function run(): string => if user := find() then user.name else \"guest\"")
  rejects(declarations + "function run(): string => if user := find() then \"x\" else user.name", "\"user\" is not in scope here")
}

export function testWhileBindingConditionsCompleteNormally(): none {
  // Unlike `while true`, a binding condition can end the loop, so code after
  // it is reachable and a value-returning function still needs a return.
  rejects(declarations + "function run(): int { while value := load() { } }", "return")
}
