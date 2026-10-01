import { Assert } from "std/assert"
import { compile } from "./compiler"
import { FunctionParamType, FunctionType, SourceFile } from "./semantic"
import { displayTypeName, functionType, primitive } from "./checker-types"
import { withCallbackArity } from "./checker-array-methods"

function messages(body: string): string[] {
  result := compile([SourceFile { path: "/main.do", source: "function main(): none {\n" + body + "\n}" }], "/main.do")
  let found: string[] = []
  for diagnostic of result.diagnostics { found.push(diagnostic.message) }
  return found
}

function signature(callbackParams: string[], typeParams: string[] = []): FunctionType {
  let params: FunctionParamType[] = []
  for name of callbackParams { params.push(FunctionParamType { name, type_: primitive("int"), hasDefault: false }) }
  callback := functionType(params, primitive("bool"))
  case functionType([FunctionParamType { name: "predicate", type_: callback, hasDefault: false }], primitive("bool"), typeParams) {
    function_: FunctionType -> { return function_ }
    _ -> { panic("expected function") }
  }
}

export function testCallbackMethodsAcceptEveryCallbackForm(): none {
  for call of [
    "found: int | none := items.find(=> it > index)",
    "total: double := items.reduce(0.0, (acc, it) => acc + it)",
    "joined: string := items.reduceRight(\"\", (acc, index) => acc + string(index))",
    "items.forEach(=> println(string(it * index)))",
    "items.forEach() { println(string(it)) }",
    "items.sort(=> b - a)",
    "kept: int[] := items.filter((index) => index > 0)",
    "any: bool := items.some((index, it) => it == index)",
    "all: bool := items.every(=> it > 0)",
  ] {
    found := messages("let items = [1, 2, 3]\n" + call)
    for message of found { println(call + ": " + message) }
    Assert.equal(found.length, 0)
  }
}

export function testFindIsOptionalAndSortIsMutableOnly(): none {
  Assert.stringContains(messages("items := [1]\nvalue: int := items.find(=> it > 0)")[0], "Cannot assign int | none to int")
  sorted := messages("items: readonly int[] := [2, 1]\nitems.sort(=> a - b)")
  Assert.stringContains(sorted[0], "Method \"sort\" is not available on readonly array")
}

export function testReduceAccumulatorDiagnostics(): none {
  found := messages("items := [1, 2]\ntotal := items.reduce(0, => acc + it * 0.5)")
  Assert.equal(found.length, 1)
  Assert.stringContains(found[0], "Cannot return double from lambda returning int")
  widened := messages("items := [1, 2]\ntotal: double := items.reduce<double>(0, => acc + it * 0.5)")
  Assert.equal(widened.length, 0)
}

export function testNamedFunctionsMayOmitIndex(): none {
  for source of [
    "function label(value: int): string => string(value)\nfunction main(): none { labels: string[] := [1].map(label) }",
    "function add(acc: int, it: int): int => acc + it\nfunction main(): none { total: int := [1].reduce(0, add) }",
    "function both(it: int, index: int): bool => it > index\nfunction main(): none { kept := [1].filter(both) }",
  ] {
    result := compile([SourceFile { path: "/main.do", source }], "/main.do")
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.equal(result.diagnostics.length, 0)
  }
  result := compile([SourceFile { path: "/main.do", source: "function none0(): bool => true\nfunction main(): none { kept := [1].filter(none0) }" }], "/main.do")
  Assert.isTrue(result.diagnostics.length > 0)
}

export function testWithCallbackArityOnlyDropsTrailingIndex(): none {
  narrowed := withCallbackArity(signature(["it", "index"], ["U"]), 0, 1)
  Assert.isTrue(narrowed != none)
  Assert.equal(displayTypeName(narrowed!), "(predicate: (it: int): bool): bool")
  Assert.equal(narrowed!.typeParams.length, 1)
  Assert.isTrue(withCallbackArity(signature(["it", "index"]), 0, 2) == none)
  Assert.isTrue(withCallbackArity(signature(["it", "index"]), 0, 0) == none)
  Assert.isTrue(withCallbackArity(signature(["a", "b"]), 0, 1) == none)
  Assert.isTrue(withCallbackArity(signature(["it", "index"]), 1, 1) == none)
}
