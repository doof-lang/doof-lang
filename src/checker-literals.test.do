import { hasErrorDiagnostics } from "./diagnostics"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testCheckerConsolidationMapShorthandDecorated(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function make(value: int): Map<string, int> => { value }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
}

export function testCheckerConsolidationDuplicateContextualFields(): none {
  for value of ["C { value: 1, value: 2 }", "{ value: 1, value: 2 }"] {
    result := compile([SourceFile { path: "/main.do", source: "class C { value: int }\nfunction make(): C => " + value }], "/main.do")
    Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
    Assert.stringContains(result.diagnostics[0].message, "Duplicate field 'value'")
  }
}

export function testSecondConsolidationContextualObjectKeepsFieldConstruction(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Box { value: int\nstatic constructor(value: int): Box => Box { value: value + 1 } }\nfunction make(): Box => { value: 3 }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source, "std::make_shared<Box>(3)")
}

export function testNullableMapContextTypesMapLiterals(): none {
  valid := compile([SourceFile { path: "/main.do", source:
    "function make(present: bool): Map<string, int> | none { let scores: Map<string, int> | none = { \"k\": 7 }\nreturn if present then scores else none }",
  }], "/main.do")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  Assert.isTrue(valid.emission != none)
  invalid := compile([SourceFile { path: "/main.do", source: "function make(): none { let scores: Map<string, int> | none = { \"k\": \"seven\" } }" }], "/main.do")
  Assert.isTrue(hasErrorDiagnostics(invalid.diagnostics))
  Assert.stringContains(invalid.diagnostics[0].message, "Cannot assign string to int")
}
