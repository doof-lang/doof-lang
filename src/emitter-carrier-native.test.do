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
  root := join([tempDirectory(), "doof-native-carrier-matrix"])
  clearNativeMatrix(root)
  try! mkdir(root)
  source := try! readText("tests/fixtures/none-carriers/main.do")
  compiled := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of compiled.diagnostics { println(diagnostic.message) }
  Assert.equal(compiled.diagnostics.length, 0)
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
