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
