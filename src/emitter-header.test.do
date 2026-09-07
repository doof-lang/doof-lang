import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testStructuredHeadersKeepReadableVariantsAndComments(): none {
  source := "class Left {}\nclass Right {}\nclass Pair \"std::variant<std::shared_ptr<Left>, std::shared_ptr<Right>>\" { left: Left | Right\nright: Left | Right }"
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  header := result.emission!.modules[0].header
  Assert.stringContains(header, "using doof_header_type_1 = std::variant<std::shared_ptr<Left>, std::shared_ptr<Right>>;")
  Assert.stringContains(header, "// std::variant<std::shared_ptr<Left>, std::shared_ptr<Right>>")
  Assert.stringContains(header, "doof_header_type_1 left;")
}

export function testReadonlyEmissionNativeAliasesUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nimport class Native from \"native.hpp\" as vendor::Native { get(): Item }" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "using Item = ::mapped::types::Item;")
  Assert.stringNotContains(output, "app_vendor_types_")
}
