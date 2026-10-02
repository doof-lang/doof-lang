// Native tests compile the current source emitter's output, never a stale
// installed compiler. Their build directory is separate from shared test builds.
import { Assert } from "std/assert"
import { BlobReader } from "std/blob"
import { exists, isDirectory, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { ExecOptions, env, run } from "std/os"
import { join, tempDirectory } from "std/path"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testCarrierModelNativeMatrix(): none {
  runNativeFixture("none-carriers")
}

export function testEmissionFailuresSubstringNative(): none {
  runNativeFixture("substring-default")
}

export function testEmissionFailuresCatchPanicNative(): none {
  runNativeFixture("catch-panic-never")
}

export function testBlockLambdaNative(): none {
  runNativeFixture("block-lambda-returns")
}

export function testArrayCallbacksNative(): none {
  runNativeFixture("array-callbacks")
}

export function testStaticShorthandNative(): none {
  runNativeFixture("static-shorthand")
}

export function testExponentLiteralsNative(): none {
  runNativeFixture("exponent-literals")
}

export function testInterfacesWithoutImplementationsNative(): none {
  runNativeFixture("interface-no-implementations")
}

export function testResultUnwrappingNative(): none {
  runNativeFixture("result-unwrapping")
}

function runNativeFixture(fixture: string): none {
  root := join([tempDirectory(), "doof-native-" + fixture])
  clearNativeMatrix(root)
  mkdir(root)!
  source := readText("tests/fixtures/" + fixture + "/main.do")!
  compiled := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of compiled.diagnostics { println(diagnostic.message) }
  Assert.equal(compiled.diagnostics.length, 0)
  Assert.isTrue(compiled.emission != none)
  writeText(join([root, "doof_runtime.hpp"]), readText("runtime/doof_runtime.hpp")!)!
  executable := join([root, "matrix"])
  let args = ["-std=c++17", "-O0", "-pthread", "-o", executable]
  for module of compiled.emission!.modules {
    writeText(join([root, module.headerName]), module.header)!
    path := join([root, module.sourceName])
    writeText(path, module.source)!
    args.push(path)
  }
  compiler := env("CXX") ?? "c++"
  built := run(compiler, args, ExecOptions { withStdin: false, mergeStderrIntoStdout: true })!
  if built.exitCode != 0 { println(BlobReader(built.stdout).readString(long(built.stdout.length))) }
  Assert.equal(built.exitCode, 0)
  executed := run(executable, [], ExecOptions { withStdin: false, mergeStderrIntoStdout: true })!
  if executed.exitCode != 0 { println(BlobReader(executed.stdout).readString(long(executed.stdout.length))) }
  Assert.equal(executed.exitCode, 0)
  clearNativeMatrix(root)
}

function clearNativeMatrix(path: string): none {
  if !exists(path) { return }
  if isDirectory(path) { for entry of readDir(path)! { clearNativeMatrix(join([path, entry.name])) } }
  remove(path)!
}

export function testNeverReviewNative(): none {
  runNativeFixture("never-review")
}

export function testCallbackEqualityNative(): none {
  runNativeFixture("callback-equality")
}

export function testOptionalChainingNative(): none {
  runNativeFixture("optional-chaining")
}

export function testAbsenceLayersNative(): none {
  runNativeFixture("absence-layers")
}

export function testLoopThenAndCoalescingNative(): none {
  runNativeFixture("loop-then-and-coalescing")
}

export function testLiteralFieldDiscriminatorsNative(): none {
  runNativeFixture("literal-field-discriminators")
}

export function testJsonAliasAndGenericDecodeNative(): none {
  runNativeFixture("json-alias-and-generic-decode")
}

export function testPositionalClassLiteralsNative(): none {
  runNativeFixture("positional-class-literals")
}
