import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testGenericNoneLiteralConstructPayloadUsesSpecializedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Item {}\n" +
    "function load<T>(value: T): Result<T, string> { return Success { value: value } }\n" +
    "function fail<E>(error: E): Result<int, E> { return Failure(error) }\n" +
    "function main(): none { try? load(Item {})\ntry? fail(Item {}) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "doof::Success<std::shared_ptr<Item>>")
  Assert.stringContains(source, "doof::Failure<std::shared_ptr<Item>>")
  Assert.stringNotContains(source, "doof::Success<T>")
  Assert.stringNotContains(source, "doof::Failure<E>")
}

export function testCoercesStructuralInterfaceMethodReturnsToDeclaredType(): none {
  result := compile([SourceFile {
    path: "/interface-return.do",
    source:
      "interface Dimensions { width(): double }\n" +
      "class PixelDimensions { width(): int => 16 }\n" +
      "class PreciseDimensions { width(): double => 16.5 }\n" +
      "function widthOf(value: Dimensions): double => value.width()\n" +
      "function main(): double => widthOf(PixelDimensions {}) + widthOf(PreciseDimensions {})",
  }], "/interface-return.do")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(
    result.emission!.modules[0].source,
    "std::visit([&](auto&& _obj) -> double { return _obj->width(); }, value)",
  )
}

export function testEmitsNamespaceGenericCallsAgainstResolvedOwner(): none {
  result := compile([
    SourceFile { path: "/main.do", source: "import * as tools from \"./tools\"\nfunction main(): int => tools.identity<int>(1)" },
    SourceFile { path: "/tools.do", source: "export function identity<T>(value: T): T => value" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  let mainSource = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { mainSource = module.source } }
  Assert.stringContains(mainSource, "::app_tools_::identity__int(1)")
}

export function testInterfaceBoundUsesContractDefaultsForVariantCalls(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "interface Reader<V> { read(first: int = 2, second: int = 3): V }\n" +
    "class C { read(first: int = 9, second: int = 9): int => first + second }\n" +
    "function readOne<T: Reader<int>>(value: T): int => value.read{second: 4}\n" +
    "function main(): int { value: Reader<int> := C {}\nreturn readOne(value) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source, "_obj->read(2, 4)")
}
