import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testGenericNoneLiteralWithoutContextUsesUnitCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function unitTuple(): Tuple<none, int> => (none, 7)\n" +
    "function main(): none { unitTuple() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "std::make_tuple(std::monostate{}, 7)")
  Assert.stringNotContains(source, "std::make_tuple(nullptr, 7)")
}

export function testEmitterGapConditionalDispatchPreservesExpectedUnionOrder(): none {
  result := compile([SourceFile {
    path: "/conditional.do",
    source: "function choose(flag: bool): int | string => if flag then \"first\" else 2",
  }], "/conditional.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "[&]() -> std::variant<int32_t, std::string>")
  Assert.stringNotContains(source, "[&]() -> std::variant<std::string, int32_t>")
}
