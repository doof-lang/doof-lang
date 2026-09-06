import { Assert } from "std/assert"
import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceFile } from "./semantic"

export function testCheckerConsolidationArgumentDiagnosticsAndSpans(): none {
  for invocation of ["read{unknown: 1}", "read{value: 1, value: 2}", "read()", "read(\"wrong\")"] {
    result := compile([SourceFile { path: "/main.do", source:
      "function read(value: int): int => value\nfunction main(): int => " + invocation,
    }], "/main.do")
    Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
    Assert.equal(result.diagnostics[0].span.start.line, 2)
    Assert.isTrue(result.diagnostics[0].message.contains("argument") || result.diagnostics[0].message.contains("Argument"))
  }
}

export function testCheckerConsolidationRequiredPositionalSlots(): none {
  for source of [
    "function read(first: int = 2, second: int): int => second\nfunction main(): int => read(3)",
    "class C { first: int = 2\nsecond: int }\nfunction main(): C => C(3)",
    "class C { first: int = 2\nsecond: int }\nfunction main(): Actor<C> => Actor<C>(3)",
  ] {
    result := compile([SourceFile { path: "/main.do", source }], "/main.do")
    Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
    Assert.stringContains(result.diagnostics[0].message, "2")
  }
}
