import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testQuarkWeakCaseStatementEmission(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Item {}\nfunction read(item: weak Item): int { case item { _: Success -> { return 1 }\n_: Failure -> { return 0 } } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "doof::lock_weak(_case_weak)")
  Assert.stringContains(source, "std::holds_alternative<doof::Success<")
  Assert.stringContains(source, "std::holds_alternative<doof::Failure<")
}

export function testDiscardedExpressionValuesAreExplicit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\n" +
    "function main(): none { effect()\nnone\n42\nlet count = 0\ncount += 1\nvalue := effect() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "effect();")
  Assert.stringContains(source, "static_cast<void>(std::monostate{});")
  Assert.stringContains(source, "static_cast<void>(42);")
  Assert.stringContains(source, "static_cast<void>((count += 1));")
  Assert.stringContains(source, "value = (static_cast<void>(effect()), std::monostate{});")
}

export function testStandaloneDiscardBindingEmitsOnlyItsValue(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction main(): none { _ := effect() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "effect();")
  Assert.stringNotContains(source, "const auto _ =")
}

export function testUnitAsyncYieldExplicitlyDiscardsCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction main(): none { task := async { yield effect() } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source,
    "effect();\n    return;")
}

export function testLoopUpdatesExplicitlyDiscardEachValue(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction main(): none { for let i = 0; i < 2; effect(), i += 1 {} }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source,
    "effect(), static_cast<void>((i += 1))")
}

export function testCapturedOptionalGenericLocalUsesConcreteStorageType(): none {
  result := compile([
    SourceFile {
      path: "/event.do",
      source:
        "export class ChannelSender<T> { close(): none {} }\n" +
        "export function createChannel<T>(): ChannelSender<T> => ChannelSender<T> {}",
    },
    SourceFile {
      path: "/main.do",
      source:
        "import { ChannelSender, createChannel } from \"./event\"\n" +
        "class Message {}\n" +
        "function invoke(handler: (message: Message): none): none {}\n" +
        "function accept(sender: ChannelSender<Message>, message: Message): none { sender.close() }\n" +
        "function main(): none {\n" +
        "let channel: ChannelSender<Message> | none = none\n" +
        "sender := createChannel<Message>()\n" +
        "invoke((message: Message): none => accept(channel!, message))\n" +
        "channel = sender\n" +
        "}",
    },
  ], "/main.do")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { source = module.source } }
  Assert.stringContains(source, "std::make_shared<std::shared_ptr<::app_event_::ChannelSender__app_main__Message_>>(nullptr)")
  Assert.stringNotContains(source, "ChannelSender<std::shared_ptr<Message>>")
}

class DestructuredCounter { value: int }

function tupleCounter(): (): int {
  let (count, _) = (1, 0)
  return (): int => { count += 1
    return count }
}

function arrayCounter(): (): int {
  let [count, _] = [3, 0]
  return (): int => { count += 1
    return count }
}

function namedCounter(): (): int {
  let { value as count } = DestructuredCounter { value: 5 }
  return (): int => { count += 1
    return count }
}

export function testEmitterGapDestructuredMutablesShareEscapingStorage(): none {
  tuple := tupleCounter()
  array := arrayCounter()
  named := namedCounter()
  Assert.equal(tuple(), 2)
  Assert.equal(tuple(), 3)
  Assert.equal(array(), 4)
  Assert.equal(array(), 5)
  Assert.equal(named(), 6)
  Assert.equal(named(), 7)
  let (uncaptured, _) = (10, 0)
  uncaptured += 1
  Assert.equal(uncaptured, 11)
}

export function testDeclarationElseExtractsSingleCallbackVariant(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): none { let callback: ((): none) | none = (): none => {}\n" +
    "narrowed := callback else { panic(\"missing\") }\nnarrowed() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  for module of result.emission!.modules {
    if module.modulePath != "/main.do" { continue }
    Assert.stringContains(module.source, "std::get<doof::callback<void()>>(_binding_value_")
    Assert.stringContains(module.source, "narrowed.call()")
  }
}

export function testDeclarationElseCallbackRuntimePaths(): none {
  let count = 0
  let callback: ((): none) | none = (): none => { count = count + 1 }
  narrowed := callback else { panic("missing callback") }
  narrowed()
  Assert.equal(count, 1)
  Assert.equal(optionalCallbackValue(none), -1)
  Assert.equal(optionalCallbackValue((): int => 7), 7)
}

function optionalCallbackValue(callback: ((): int) | none): int {
  narrowed := callback else { return -1 }
  return narrowed()
}

export function testCheckerReviewTypedTryStorage(): none {
  result := compile([SourceFile { path: "/main.do", source: "function load(): Result<int, string> => Success { value: 1 }\nfunction good(): Result<long, string> { try let x: long = load()\nx += 2147483648L\nreturn Success { value: x } }\nfunction caught(): none { error := catch { try readonly x: long = load() } }\ntry value: long := load()\nprintln(value)" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "int64_t x = doof::variant_promote<int64_t>(doof::success_value(")
  Assert.stringContains(source, "const int64_t x = doof::variant_promote<int64_t>(doof::success_value(")
  Assert.stringContains(source, "const int64_t value = doof::variant_promote<int64_t>(doof::success_value(")
}

export function testRestrictedNestedYieldCarriers(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function run(flag: bool): int | none { let x <- { let inner: string | none <- { yield none }\nif flag { yield 1 } else { yield none } }\nreturn x }\nfunction main(): none { run(true) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "return std::nullopt;")
  Assert.stringNotContains(source, "return std::monostate{};")
}

export function testCombinationNoneGenericBlockReturn(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function identity<T>(value: T): T { return value }\nfunction main(): none { identity(none)\nidentity(7) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "return static_cast<void>(value);")
  Assert.stringContains(source, "return value;")
}

export function testReadonlyEmissionStatementsUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction build(): none { value := Item {} }" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}

export function testNeverReviewTryEmission(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function load(): Result<never, string> => Failure { error: \"bad\" }\n" +
    "function propagate(): Result<int, string> { try load() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source, "doof::unreachable();")
}

export function testLoopThenClausesRunOnlyOnNormalCompletion(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): none {\nfor item of [1, 2] { if item == 2 { break } } then { println(\"for-of\") }\n" +
    "let count = 0\nwhile count < 2 { count += 1 } then { println(\"while\") }\n" +
    "for let i = 0; i < 2; i += 1 { continue } then { println(\"for\") }\n" +
    "for item of [1] { for other of [2] { break } } then { println(\"outer\") } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "println(std::string(\"for-of\"))")
  Assert.stringContains(source, "println(std::string(\"while\"))")
  Assert.stringContains(source, "println(std::string(\"for\"))")
  Assert.stringContains(source, "println(std::string(\"outer\"))")
  // The break that exits a then-loop skips its clause; the inner loop's break stays local.
  Assert.stringContains(source, "goto _doof_break_")
  Assert.stringContains(source, "break;")
  Assert.stringContains(source, "continue;")
}

export function testLoopsWithoutThenKeepPlainBreaks(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): none { for item of [1, 2] { if item == 2 { break } } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "break;")
  Assert.stringNotContains(source, "_doof_break_")
}

export function testTryAssignmentStoresTheConvertedSuccessValue(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Box { let value: int = 0 }\nfunction name(): Result<string, string> => Success(\"a\")\nfunction count(): Result<int, string> => Success(1)\n" +
    "function run(box: Box): Result<int, string> { let wide: long | string = 0L\ntry wide = name()\ntry box.value = count()\nreturn Success(box.value) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "= name();")
  Assert.stringContains(source, "wide = doof::variant_promote<std::variant<int64_t, std::string>>(std::move(doof::success_value(_try_value_")
  Assert.stringContains(source, "box->value = std::move(doof::success_value(_try_value_")
}

export function testMultipleForInitializersAreHoistedIntoALoopBlock(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): none { for let i = 0, j = 10; i < j; i += 1, j -= 1 { println(i) } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "for (; i < j; ")
  Assert.isTrue(source.indexOf("j = 10") < source.indexOf("for (; "))

  single := compile([SourceFile { path: "/main.do", source:
    "function main(): none { for let i = 0; i < 2; i += 1 { println(i) } }",
  }], "/main.do")
  Assert.equal(single.diagnostics.length, 0)
  Assert.isFalse(single.emission!.modules[0].source.contains("for (; "))
}

export function testForOfOverReadonlyCollectionOwnsWithoutCopying(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): int { let values: readonly int[] = [1, 2]\nlet total = 0\nfor item of values { total = total + item }\nreturn total }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.equal(source.contains("iteration_snapshot"), false)
  Assert.stringContains(source, "const auto _iterable_")
  Assert.stringContains(source, "for (const auto& item : *_iterable_")
}

export function testForOfOverReadonlyMapAndSetOwnsWithoutCopying(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): int { scores: ReadonlyMap<string, int> := { \"a\": 1 }\nunique: ReadonlySet<int> := [1, 2]\nlet total = 0\nfor key, value of scores { total = total + value }\nfor n of unique { total = total + n }\nreturn total }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.equal(source.contains("iteration_snapshot"), false)
  Assert.stringContains(source, "for (const auto& [key, value] : *_iterable_")
  Assert.stringContains(source, "for (const auto& n : *_iterable_")
}

// These run through the compiled for-of lowering itself: each loop visits
// exactly the elements present at loop entry, whatever the body mutates.
// Elements are heap-allocated strings so that reading a freed or destroyed
// element fails visibly instead of returning stale inline values.
function label(n: int): string => "element-label-long-enough-to-allocate-" + string(n)

export function testForOfArrayIgnoresAppendsDuringIteration(): none {
  let items = [label(1), label(2), label(3)]
  let visited = ""
  for item of items {
    visited = visited + item + ","
    for i of 0..<8 { items.push(item + "-appended") }
  }
  Assert.equal(visited, label(1) + "," + label(2) + "," + label(3) + ",")
  Assert.equal(items.length, 27)
}

export function testForOfArrayVisitsOriginalElementsAfterShrinking(): none {
  let items = [label(1), label(2), label(3), label(4)]
  let visited = ""
  for item of items {
    visited = visited + item + ","
    ignored := items.pop()!
  }
  Assert.equal(visited, label(1) + "," + label(2) + "," + label(3) + "," + label(4) + ",")
  Assert.equal(items.length, 0)
}

export function testForOfArraySurvivesReassigningTheSource(): none {
  let items = [label(1), label(2), label(3)]
  let visited = ""
  for item of items {
    visited = visited + item + ","
    items = [label(9), label(9), label(9)]
  }
  Assert.equal(visited, label(1) + "," + label(2) + "," + label(3) + ",")
}

export function testForOfReadonlyArraySurvivesReassigningTheSource(): none {
  let items: readonly string[] = [label(1), label(2), label(3)]
  let visited = ""
  for item of items {
    visited = visited + item + ","
    items = [label(9), label(9), label(9)]
  }
  Assert.equal(visited, label(1) + "," + label(2) + "," + label(3) + ",")
}

export function testForOfReadonlyMapAndSetSurviveReassigningTheSource(): none {
  let scores: ReadonlyMap<string, int> = { "a": 1, "b": 2 }
  let unique: ReadonlySet<string> = [label(1), label(2)]
  let visited = ""
  for key, value of scores {
    visited = visited + key + string(value) + ","
    scores = { "z": 26 }
  }
  for value of unique {
    visited = visited + value + ","
    unique = [label(9)]
  }
  Assert.equal(visited, "a1,b2," + label(1) + "," + label(2) + ",")
}

export function testForOfMapVisitsEntriesPresentAtEntry(): none {
  scores: Map<string, int> := { "a": 1, "b": 2, "c": 3 }
  let visited = ""
  for key, value of scores {
    visited = visited + key + string(value) + ","
    scores.delete("b")
    scores.set("z", 26)
  }
  Assert.equal(visited, "a1,b2,c3,")
  Assert.equal(scores.has("b"), false)
}

export function testForOfMapSeesValuesAsTheyWereAtEntry(): none {
  scores: Map<string, int> := { "a": 1, "b": 2 }
  let visited = ""
  for key, value of scores {
    visited = visited + key + string(value) + ","
    scores.set("b", 99)
  }
  Assert.equal(visited, "a1,b2,")
  Assert.equal(scores.get("b")!, 99)
}

export function testForOfSetVisitsValuesPresentAtEntry(): none {
  unique: Set<int> := [1, 2, 3]
  let visited = ""
  for n of unique {
    visited = visited + string(n) + ","
    unique.delete(n + 1)
    unique.add(n + 100)
  }
  Assert.equal(visited, "1,2,3,")
}

export function testForOfRangeFixesItsEndAtEntry(): none {
  let items = [1, 2, 3]
  let visited = ""
  for i of 0..<items.length {
    visited = visited + string(i) + ","
    items.push(i)
  }
  Assert.equal(visited, "0,1,2,")
  let last = 2
  for i of 0..last {
    visited = visited + string(i) + ","
    last = 10
  }
  Assert.equal(visited, "0,1,2,0,1,2,")
}

let forOfRangeBoundCalls = 0
function forOfRangeBound(value: int): int {
  forOfRangeBoundCalls += 1
  return value
}

export function testForOfRangeEvaluatesEachBoundOnce(): none {
  forOfRangeBoundCalls = 0
  let total = 0
  for i of forOfRangeBound(1)..<forOfRangeBound(4) { total += i }
  for i of forOfRangeBound(1)..forOfRangeBound(4) { total += i }
  Assert.equal(total, 16)
  Assert.equal(forOfRangeBoundCalls, 4)
}

function forOfRangeMaxInt(): int => 2147483647

function forOfRangePanic(action: (): none): string => case catchPanic(action) {
  _: Success -> "no panic",
  failure: Failure -> failure.error,
}

export function testInclusiveRangeEndingAtMaximumIntPanics(): none {
  let visited = 0
  inline := forOfRangePanic(() => {
    for i of (forOfRangeMaxInt() - 2)..forOfRangeMaxInt() { visited += 1 }
  })
  Assert.stringContains(inline, "Inclusive range cannot end at the maximum int (2147483647)")
  Assert.equal(visited, 0)
  stored := forOfRangePanic(() => {
    values := 0..forOfRangeMaxInt()
    for i of values { visited += 1 }
  })
  Assert.stringContains(stored, "Inclusive range cannot end at the maximum int (2147483647)")
  Assert.equal(visited, 0)
}

export function testInclusiveRangeEndingBelowMaximumIntReachesItsEnd(): none {
  let last = 0
  for i of (forOfRangeMaxInt() - 3)..(forOfRangeMaxInt() - 1) { last = i }
  Assert.equal(last, 2147483646)
  values := (forOfRangeMaxInt() - 1)..(forOfRangeMaxInt() - 1)
  Assert.equal(values.upperBound, 2147483647)
  for i of values { last = i }
  Assert.equal(last, 2147483646)
}

export function testForOfRangeEmitsBoundsOnceInOrder(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(items: int[]): int { let total = 0\nfor i of 0..<items.length { total += i }\nfor j of 1..3 { total += j }\nr := 1..items.length\nreturn total }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "for (int32_t i = 0, _range_end_")
  Assert.stringContains(source, " = static_cast<int32_t>((items)->size()); i < _range_end_")
  Assert.stringContains(source, "for (int32_t j = 1, _range_end_")
  Assert.stringContains(source, " = doof::inclusive_range_end(3, \"/main.do\", 3); j <= _range_end_")
  Assert.stringContains(source, "doof::range(1, static_cast<int32_t>((items)->size()), ")
}

class ForOfCounter {
  let count: int
}

export function testForOfSnapshotIsShallow(): none {
  counters := [ForOfCounter { count: 1 }, ForOfCounter { count: 2 }]
  let visited = ""
  for counter of counters {
    visited = visited + string(counter.count) + ","
    counters[1].count = 20
  }
  Assert.equal(visited, "1,20,")
}

// A class stream iterated directly calls its own next()/value() methods
// instead of boxing the instance into a Stream<T> variant.
export function testForOfOverClassStreamCallsItsMethodsDirectly(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): int { let total = 0\nfor v of Ticks(0, 3) { total = total + v }\nreturn total }\n" +
    "class Ticks { let i: int\nend: int\nnext(): bool { i = i + 1\nreturn i <= end }\nvalue(): int => i }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "while (_iterable_")
  Assert.stringContains(source, "->next())")
  Assert.stringContains(source, "->value();")
  Assert.equal(source.contains("std::visit"), false)
}

class ForOfTicks implements Stream<int> {
  let current: int
  end: int
  next(): bool {
    current = current + 1
    return current <= end
  }
  value(): int => current
}

class ForOfRepeat<T> {
  item: T
  let times: int
  next(): bool {
    times = times - 1
    return times >= 0
  }
  value(): T => item
}

struct ForOfCountdown {
  let left: int
  next(): bool {
    left = left - 1
    return left >= 0
  }
  value(): int => left
}

export function testForOfIteratesClassStreamsDirectly(): none {
  let visited = ""
  for v of ForOfTicks(0, 3) { visited = visited + string(v) + "," }
  for s of ForOfRepeat<string>("x", 2) { visited = visited + s + "," }
  countdown := ForOfCountdown { left: 2 }
  for n of countdown { visited = visited + string(n) + "," }
  Assert.equal(visited, "1,2,3,x,x,1,0,")
}

export function testForOfClassStreamBreakSkipsThenAndCapturesEachValue(): none {
  ticks := ForOfTicks(0, 10)
  let total = 0
  let completed = false
  for v of ticks {
    if v == 3 { break }
    total = total + v
  } then { completed = true }
  Assert.equal(total, 3)
  Assert.isFalse(completed)
  // The loop advanced the shared instance, so iteration resumes after 3.
  Assert.equal(ticks.next(), true)
  Assert.equal(ticks.value(), 4)
}
