import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testWiderNoneJsonDecodesUnitAndContainers(): none {
  for type_ of ["none", "none[]", "Map<string, none>", "Tuple<none, int>"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class Data { value: " + type_ + " }\nfunction decode(input: JsonValue): Result<Data, string> => Data.fromJsonValue(input)",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, "throw doof::JsonDecodeError(\"Expected null\")")
    Assert.stringContains(source, "-> std::monostate")
    if type_ == "none" { Assert.stringContains(source, "expected null but got") }
  }
}

export function testCombinationNoneJsonNestedContainerGuards(): none {
  types := ["none[][]", "Map<string, none>[]", "Tuple<none, int>[]"]
  checks := ["if (_array == nullptr)", "if (_object_value == nullptr)", "if (_tuple == nullptr)"]
  for index of 0..<types.length {
    result := compile([SourceFile { path: "/main.do", source:
      "class Data { values: " + types[index] + " }\nfunction decode(input: JsonValue): Result<Data, string> => Data.fromJsonValue(input)",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, checks[index] + " throw doof::JsonDecodeError")
    if index == 2 { Assert.stringContains(source, "if (_tuple->size() != 2)") }
  }
}

export function testReadonlyEmissionJsonUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction decode(value: JsonValue): Result<Item, string> => Item.fromJsonValue(value)" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}
