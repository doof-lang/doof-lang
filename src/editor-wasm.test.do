import { Assert } from "std/assert"
import { diagnostics } from "./editor-wasm"
import { SourceFile } from "./semantic"

export function testEditorWasmDiagnosticsUsesSharedFrontend(): none {
  Assert.equal(diagnostics([SourceFile { path: "/main.do", source: "function main(): int => 42" }], "/main.do").length, 0)
  errors := diagnostics([SourceFile { path: "/main.do", source: "function main(): int => \"wrong\"" }], "/main.do")
  Assert.isTrue(errors.length > 0)
  Assert.equal(errors[0].severity, "error")
}
