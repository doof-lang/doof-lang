import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testMutableReadonlyFieldReportsAtTheField(): none {
  result := compile([SourceFile { path: "/main.do", source: "class MutablePoint { let x: int }\nclass Container {\nreadonly point: MutablePoint }" }], "/main.do")
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("Readonly field \"Container.point\" must be deeply immutable") {
      found = true
      Assert.stringContains(diagnostic.message, "field \"x\" is mutable")
      Assert.equal(diagnostic.module, "/main.do")
      Assert.equal(diagnostic.span.start.line, 3)
    }
  }
  Assert.isTrue(found)
}
