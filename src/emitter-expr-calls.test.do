import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

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
