import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testNoneCarrierJsonPatternBindsUnit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function take(value: none): none {}\n" +
    "function main(): none { let value: JsonValue = none\n" +
    "case value { n: none -> { take(n) }\n_ -> {} } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "const auto n = std::monostate{};")
  Assert.stringContains(source, "take(n);")
  Assert.stringNotContains(source, "const auto n = nullptr;")
}

export function testNoneCarrierNaturalPatternTestsAbsence(): none {
  for type_ of ["int", "Item", "int[]"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class Item {}\nfunction take(value: none): none {}\n" +
      "function inspect(value: " + type_ + " | none): int {\n" +
      "case value { n: none -> { take(n)\nreturn 1 }\n_ -> { return 2 } } }",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, "if (doof::is_null(_case_subject))")
    Assert.stringContains(source, "const auto n = std::monostate{};")
    Assert.stringNotContains(source, "if (!doof::is_null(_case_subject))")
  }
}
