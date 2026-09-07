import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
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

export function testReadonlyEmissionPatternsUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction inspect(value: Item | Other): int { case value { item: Item -> { return item.value }\n_ -> { return 0 } } }" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "std::shared_ptr<::mapped::types::Item>")
  Assert.stringNotContains(output, "app_vendor_types_")
}
