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
  mkdir(root)!
  source := readText("tests/fixtures/checker-consolidation/main.do")!
  compiled := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of compiled.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(compiled.diagnostics), false)
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

export function testSecondConsolidationNamedFactoryResultOwner(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Box<T> { value: T\nstatic constructor(value: T): Result<Box<T>, string> => Success { value: Box<T> { value } } }\nfunction make(): Result<Box<int>, string> => Box<int> { value: 3 }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source, "Box__int::constructor(3)")
}

export function testPositionalLiteralsConstructExpectedClasses(): none {
  valid := compile([SourceFile { path: "/main.do", source:
    "class Point { x, y: float }\nstruct Vec { x: int\ny: int }\nclass Config { host: string\nport: int = 8080 }\n" +
    "class Counter { count: int\nstatic constructor(initial: int, step: int): Counter { return Counter { count: initial + step } } }\n" +
    "function draw(p: Point): float => p.x\nfunction make(): Point { return (3.0, 4.0) }\nfunction maybe(): Vec | none => (1, 2)\n" +
    "function main(): none { let p: Point = (1.0, 2.0)\npoints: Point[] := [(1.0, 2.0)]\n" +
    "let short: Config = (\"localhost\", 80)\nlet counter: Counter = (10, 5)\nprintln(draw((1.0, 2.0)))\npair := (1, \"one\")\nlet tuple: Tuple<int, int> = (1, 2) }",
  }], "/main.do")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)

  tooMany := compile([SourceFile { path: "/main.do", source: "class Point { x, y: float }\nfunction main(): none { let p: Point = (1.0, 2.0, 3.0) }" }], "/main.do")
  Assert.equal(tooMany.diagnostics.length, 1)
  Assert.stringContains(tooMany.diagnostics[0].message, "Class \"Point\" expects 2 constructor argument(s) but got 3")
  wrongType := compile([SourceFile { path: "/main.do", source: "class Point { x, y: float }\nfunction main(): none { let p: Point = (\"a\", 2.0) }" }], "/main.do")
  Assert.equal(wrongType.diagnostics.length, 1)
  Assert.stringContains(wrongType.diagnostics[0].message, "Argument 1 has type string; expected float")
  // Several class arms give no single target, so the literal stays a Tuple.
  ambiguous := compile([SourceFile { path: "/main.do", source: "class A { x: int\ny: int }\nclass B { x: int\ny: int }\ntype AB = A | B\nfunction main(): none { let value: AB = (1, 2) }" }], "/main.do")
  Assert.equal(ambiguous.diagnostics.length, 1)
  Assert.stringContains(ambiguous.diagnostics[0].message, "Cannot assign (int, int) to A | B")
}

function constructionErrors(source: string): string[] {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  let messages: string[] = []
  for diagnostic of result.diagnostics { if diagnostic.severity == "error" { messages.push(diagnostic.message) } }
  return messages
}

export function testInfersGenericClassArgumentsFromNamedConstruction(): none {
  channel := "function onString(value: string): none {}\nclass Channel<T> { handler: (value: T): none\nstatic constructor(handler: (value: T): none): Channel<T> => Channel<T> { handler } }\n"
  Assert.equal(constructionErrors(channel + "function main(): none { c := Channel { handler: onString }\nc.handler(\"x\") }").length, 0)
  Assert.equal(constructionErrors(channel + "function main(): none { handler := onString\nc := Channel { handler }\nc.handler(\"x\") }").length, 0)

  box := "class Box<T> { value: T }\n"
  Assert.equal(constructionErrors(box + "function main(): none { b := Box { value: 42 }\nlet n: int = b.value }").length, 0)
  Assert.equal(constructionErrors(box + "function main(): none { b := Box(\"s\")\nlet n: string = b.value }").length, 0)
  Assert.equal(constructionErrors(box + "function wrap<T>(x: T): T { b := Box { value: x }\nreturn b.value }").length, 0)
  Assert.equal(constructionErrors(box + "function main(): none { let b: Box<long> = Box { value: 1 } }").length, 0)

  mismatch := constructionErrors(box + "function main(): none { b := Box { value: 42 }\nlet s: string = b.value }")
  Assert.equal(mismatch.length, 1)
  Assert.stringContains(mismatch[0], "Cannot assign int to string")
}

export function testReportsUninferableGenericConstructionOnce(): none {
  container := "class Container<T, E> { result: Result<T, E> }\n"
  named := constructionErrors(container + "function main(): none { c := Container { result: Success { value: 42 } }\ncase c.result { s: Success -> println(s.value), f: Failure -> println(f.error) } }")
  Assert.equal(named.length, 1)
  Assert.equal(named[0], "Cannot infer type arguments for generic class 'Container'; provide them explicitly as Container<T, E>")

  called := constructionErrors("class Empty<T> { items: T[] = [] }\nfunction main(): none { e := Empty() }")
  Assert.equal(called.length, 1)
  Assert.stringContains(called[0], "provide them explicitly as Empty<T>")

  explicit := constructionErrors(container + "function main(): none { c := Container<int, string> { result: Success { value: 42 } } }")
  Assert.equal(explicit.length, 0)
}
