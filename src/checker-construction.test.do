import { join, tempDirectory } from "std/path"
import { ExecOptions, env, run } from "std/os"
import { exists, isDirectory, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { BlobReader } from "std/blob"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceFile } from "./semantic"

export function testCheckerConsolidationNamedGenericFactorySpread(): none {
  result := compile([SourceFile { path: "/main.do", source: "class Pair<T> { value: T\nstatic constructor(value: T, ignored: int = 2): Pair<T> => Pair<T> { value } }\nclass Input { value: int }\nfunction copy(input: Input): Pair<int> => Pair<int> { ...input }" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(result.diagnostics), false)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "Pair__int::constructor(_construct_spread_")
}

export function testCheckerConsolidationNativeMatrix(): none {
  root := join([tempDirectory(), "doof-native-checker-consolidation"])
  clearNativeMatrix(root)
  try! mkdir(root)
  source := try! readText("tests/fixtures/checker-consolidation/main.do")
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

export function testSecondConsolidationNamedFactoryResultOwner(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Box<T> { value: T\nstatic constructor(value: T): Result<Box<T>, string> => Success { value: Box<T> { value } } }\nfunction make(): Result<Box<int>, string> => Box<int> { value: 3 }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source, "Box__int::constructor(3)")
}
