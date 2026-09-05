import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

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
