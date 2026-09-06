import { Assert } from "std/assert"
import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceFile } from "./semantic"

export function testCheckerConsolidationShorthandValidationParity(): none {
  for value of ["value", "value: value"] {
    for body of ["Box { " + value + " }", "{ " + value + " }"] {
      result := compile([SourceFile { path: "/main.do", source:
        "class Box { value: int }\nfunction make(value: string): Box => " + body,
      }], "/main.do")
      Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
      Assert.stringContains(result.diagnostics[0].message, "Cannot assign string to int")
      Assert.equal(result.diagnostics[0].span.start.line, 2)
    }
  }
}

export function testCheckerConsolidationUnknownShorthandAcrossShapes(): none {
  for type_ of ["Box", "Map<string, int>", "Result<int, string>"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class Box { value: int }\nfunction make(): " + type_ + " => { value }",
    }], "/main.do")
    Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
    Assert.stringContains(result.diagnostics[0].message, "Unknown shorthand property 'value'")
  }
}
