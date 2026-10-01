import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

function emitted(body: string, prelude: string = ""): string {
  result := compile([SourceFile { path: "/main.do", source: prelude + "function main(): none {\nlet items = [1, 2, 3]\n" + body + "\n}" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  return result.emission!.modules[0].source
}

export function testCallbacksUseTheCheckedSignature(): none {
  // The lambda carries `index` and the explicit result type, so the runtime
  // deduces double[] rather than the body's int.
  source := emitted("r := items.map<double>(=> it + index)")
  Assert.stringContains(source, "doof::array_map(items, doof::callback<double(int32_t, int32_t)>([](int32_t it, int32_t index) -> double")
  declared := emitted("r := items.map((it): double => it)")
  Assert.stringContains(declared, "doof::callback<double(int32_t, int32_t)>")
}

export function testEachCallbackMethodLowersToItsRuntimeHelper(): none {
  for pair of [
    ["items.forEach(=> println(string(it)))", "doof::array_forEach(items, "],
    ["items.sort(=> a - b)", "doof::array_sort(items, "],
    ["t := items.reduce(0, => acc + it)", "doof::array_reduce(items, 0, "],
    ["t := items.reduceRight(0, => acc + it)", "doof::array_reduceRight(items, 0, "],
    ["t := items.some(=> it > index)", "doof::array_some(items, "],
    ["t := items.every(=> it > index)", "doof::array_every(items, "],
    ["t := items.filter(=> it > index)", "doof::array_filter(items, "],
    ["t := items.contains(2)", "doof::array_contains(items, 2, "],
  ] {
    Assert.stringContains(emitted(pair[0]), pair[1])
  }
}

export function testFindConvertsTheMatchIntoTheOptionalCarrier(): none {
  source := emitted("found := items.find(=> it > 1)")
  Assert.stringContains(source, "doof::array_find_index(_find_items_")
  Assert.stringContains(source, "return std::nullopt;")
}

export function testNamedFunctionsAreWrappedAtTheirOwnArity(): none {
  source := emitted("labels := items.map(label)", "function label(value: int): string => string(value)\n")
  Assert.stringContains(source, "doof::array_map(items, doof::callback<std::string(int32_t)>(label)")
}
