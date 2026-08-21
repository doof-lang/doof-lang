import { Assert } from "std/assert"
import { compileWithLoader } from "./compiler"
import { noSourceLoader } from "./resolver"
import { SourceFile } from "./semantic"

export function testEmitsJsonAbiWrappersForExportedFunctions(): none {
  result := compileWithLoader([
    SourceFile {
      path: "/main.do",
      source: "export function add(a: int, b: int = 2): int => a + b\nfunction main(): int => 0",
    },
  ], "/main.do", noSourceLoader, [], "wasm")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.equal(result.emission != none, true)
  Assert.equal(result.emission!.wasmExportNames.length, 2)
  Assert.equal(result.emission!.wasmExportNames[0], "doof_initialize")
  Assert.equal(result.emission!.wasmExportNames[1], "doof_export_add")
  Assert.stringContains(result.emission!.wasmSupportSource, "extern \"C\" void doof_free(char* ptr)")
  Assert.stringContains(result.emission!.wasmSupportSource, "extern \"C\" char* doof_initialize()")
  Assert.stringContains(result.emission!.wasmSupportSource, "Call doof_initialize before invoking Doof exports")
  Assert.stringContains(result.emission!.wasmSupportSource, "extern \"C\" char* doof_export_add(const char* params_json)")
  Assert.stringContains(result.emission!.wasmSupportSource, "::app_main_::add(a, b)")
  Assert.equal(result.emission!.modules[0].source.contains("int main("), false)
}

export function testEmitsDirectionalNominalJsonSupportForWasmAbi(): none {
  result := compileWithLoader([
    SourceFile {
      path: "/main.do",
      source: "class Input { value: int }\nclass Output { label: string }\nexport function convert(input: Input): Output => Output { label: string(input.value) }",
    },
  ], "/main.do", noSourceLoader, [], "wasm")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "Input::fromJsonValue")
  Assert.stringNotContains(source, "Input::toJsonObject")
  Assert.stringContains(source, "Output::toJsonObject")
  Assert.stringNotContains(source, "Output::fromJsonValue")
}

export function testRejectsGenericWasmExports(): none {
  result := compileWithLoader([
    SourceFile { path: "/main.do", source: "export function identity<T>(value: T): T => value" },
  ], "/main.do", noSourceLoader, [], "wasm")

  Assert.equal(result.emission == none, true)
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "cannot be generic")
}

export function testRejectsUnsupportedWasmAbiTypes(): none {
  result := compileWithLoader([
    SourceFile { path: "/main.do", source: "export function count(values: Set<int>): int => values.size" },
  ], "/main.do", noSourceLoader, [], "wasm")

  Assert.equal(result.emission == none, true)
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "must be supported by the JSON ABI")
}

export function testIncludesFunctionsExportedByASeparateList(): none {
  result := compileWithLoader([
    SourceFile { path: "/main.do", source: "function add(a: int, b: int): int => a + b\nexport { add }" },
  ], "/main.do", noSourceLoader, [], "wasm")

  Assert.equal(result.diagnostics.length, 0)
  Assert.equal(result.emission!.wasmExportNames[1], "doof_export_add")
}
