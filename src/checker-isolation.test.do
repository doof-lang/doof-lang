import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testSecondConsolidationIsolationNestedCallTraversal(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "let shared = 0\nfunction unsafe(): int { shared = shared + 1\nreturn shared }\nisolated function nested(): int => 1 + unsafe()",
  }], "/main.do")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("non-isolated") || diagnostic.message.contains("mutable module") { found = true } }
  Assert.isTrue(found)
}
