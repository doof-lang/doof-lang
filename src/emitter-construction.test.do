import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
// Native tests compile the current source emitter's output, never a stale
// installed compiler. Their build directory is separate from shared test builds.
import { Assert } from "std/assert"
import { BlobReader } from "std/blob"
import { exists, isDirectory, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { ExecOptions, env, run } from "std/os"
import { join, tempDirectory } from "std/path"
import { hasErrorDiagnostics } from "./diagnostics"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testEmissionCleanupNativeConstructionAndNeverMatrix(): none {
  root := join([tempDirectory(), "doof-native-emission-consolidation"])
  clearNativeMatrix(root)
  try! mkdir(root)
  source := try! readText("tests/fixtures/emission-consolidation/main.do")
  compiled := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of compiled.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(compiled.diagnostics), false)
  Assert.isTrue(compiled.emission != none)
  try! writeText(join([root, "doof_runtime.hpp"]), try! readText("runtime/doof_runtime.h"))
  executable := join([root, "matrix"])
  let args = ["-std=c++17", "-O0", "-pthread", "-o", executable]
  for module of compiled.emission!.modules {
    try! writeText(join([root, module.headerName]), module.header)
    path := join([root, module.sourceName])
    try! writeText(path, module.source)
    args.push(path)
  }
  compiler := env("CXX") ?? "c++"
  built := try! run(compiler, args, ExecOptions { withStdin: false, mergeStderrIntoStdout: true })
  if built.exitCode != 0 { println(BlobReader(built.stdout).readString(long(built.stdout.length))) }
  Assert.equal(built.exitCode, 0)
  executed := try! run(executable, [], ExecOptions { withStdin: false, mergeStderrIntoStdout: true })
  if executed.exitCode != 0 { println(BlobReader(executed.stdout).readString(long(executed.stdout.length))) }
  Assert.equal(executed.exitCode, 0)
  clearNativeMatrix(root)
}

function clearNativeMatrix(path: string): none {
  if !exists(path) { return }
  if isDirectory(path) { for entry of try! readDir(path) { clearNativeMatrix(join([path, entry.name])) } }
  try! remove(path)
}

export function testEmissionCleanupRejectsMissingConstructionFields(): none {
  for expression of ["Box()", "Box {}", "{}"] {
    compiled := compile([SourceFile { path: "/main.do", source:
      "class Box { value: int }\nfunction make(): Box => " + expression,
    }], "/main.do")
    Assert.isTrue(hasErrorDiagnostics(compiled.diagnostics))
    let actionable = false
    for diagnostic of compiled.diagnostics {
      if diagnostic.message.contains("value") || diagnostic.message.contains("argument") { actionable = true }
    }
    Assert.isTrue(actionable)
  }
}

export function testSecondConsolidationGenericStoredDefaults(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Box<T> { values: T[] = [] }\nfunction positional(): Box<int> => Box<int>()\nfunction named(): Box<int> => Box<int> {}\nfunction contextual(): Box<int> => {}",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "std::make_shared<Box__int>(std::make_shared<std::vector<int32_t>>" )
  Assert.equal(source.contains("std::vector<T>"), false)
}

export function testReadonlyEmissionConstructionUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction build(): Item => Item {}" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}

export function testUnitResultPayloadPreservesEffectsInObjects(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none { println(\"effect\") }\n" +
    "function success(): Result<none, string> => Success { value: effect() }\n" +
    "function failure(): Result<int, none> => Failure { error: none }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "doof::Success<void>{})")
  Assert.stringContains(source, "effect()")
  Assert.stringContains(source, "doof::Failure<void>{})")
}
