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

export function testStringReplaceNative(): none {
  runNativeFixture("string-replace")
}

export function testForMultipleInitializersNative(): none {
  runNativeFixture("for-multiple-initializers")
}

export function testGenericClassInferenceNative(): none {
  runNativeFixture("generic-class-inference")
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

export function testPromiseOnCompleteNative(): none {
  runNativeFixture("promise-on-complete", "onComplete delivered", 7)
}

export function testWeakPrecedenceNative(): none {
  runNativeFixture("weak-precedence", "weak precedence ok")
}

export function testWeakInterfaceNative(): none {
  runNativeFixture("weak-interface", "weak interface ok")
}

export function testInterfaceUnionsNative(): none {
  runNativeFixture("interface-unions", "interface unions ok")
}

export function testInterfaceUnionsAcrossModulesNative(): none {
  runNativeFixture("interface-unions-modules", "interface unions modules ok")
}

function runNativeFixture(fixture: string, expectedOutput: string = "", expectedExitCode: int = 0): none {
  root := join([tempDirectory(), "doof-native-" + fixture])
  clearNativeMatrix(root)
  mkdir(root)!
  // Every module in the fixture directory compiles together; main.do is the entry.
  directory := "tests/fixtures/" + fixture
  let sources: SourceFile[] = []
  for entry of readDir(directory)! {
    if entry.name.endsWith(".do") { sources.push(SourceFile { path: "/" + entry.name, source: readText(join([directory, entry.name]))! }) }
  }
  compiled := compile(sources, "/main.do")
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
  if executed.exitCode != expectedExitCode { println(BlobReader(executed.stdout).readString(long(executed.stdout.length))) }
  Assert.equal(executed.exitCode, expectedExitCode)
  if expectedOutput != "" { Assert.stringContains(BlobReader(executed.stdout).readString(long(executed.stdout.length)), expectedOutput) }
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

export function testInterfaceJsonNative(): none {
  runNativeFixture("interface-json")
}

export function testNullableInterfaceNative(): none {
  runNativeFixture("nullable-interface")
}

export function testPositionalClassLiteralsNative(): none {
  runNativeFixture("positional-class-literals")
}
