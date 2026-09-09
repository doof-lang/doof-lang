import { Assert } from "std/assert"
import { generatedGraph, graphsMatch } from "./build"
import { TemporaryDirectory } from "./test-support"
import { erase, makeDirectory, path, write } from "./common"

export function testRepositoryFixedPointComparesWholeGraph(): none {
  temp := try! TemporaryDirectory()
  left := path(temp.root, "generation-1"); right := path(temp.root, "generation-2")
  try! write(path(left, "a.cpp"), "int a = 1;\n")
  try! write(path(right, "a.cpp"), "int a = 1;\n")
  Assert.isTrue(graphsMatch(try! generatedGraph(left), try! generatedGraph(right)))
  try! write(path(right, "a.cpp"), "int a = 2;\n")
  Assert.isFalse(graphsMatch(try! generatedGraph(left), try! generatedGraph(right)))
  try! write(path(right, "a.cpp"), "int a = 1;\n")
  try! write(path(right, "extra.hpp"), "// extra\n")
  Assert.isFalse(graphsMatch(try! generatedGraph(left), try! generatedGraph(right)))
  try! erase(path(right, "extra.hpp"))
  try! write(path(right, ".doof-objects/ignored.cpp"), "cache\n")
  Assert.isTrue(graphsMatch(try! generatedGraph(left), try! generatedGraph(right)))
  temp.close()
}
export function testRepositoryRejectsEmptyFixedPoint(): none {
  temp := try! TemporaryDirectory()
  let failed = false
  case generatedGraph(temp.root) {
    failure: Failure -> { failed = failure.error.contains("no source files") }
    success: Success -> {}
  }
  Assert.isTrue(failed)
  temp.close()
}

import { BuildInputs, buildToolchain } from "./build"
import { capture, command, read } from "./common"
import { exists } from "std/fs"

function fakeSeed(root: string, converges: bool): string {
  seed := path(root, "seed")
  // A native-program fixture: Doof owns orchestration and assertions.
  script := "#!/bin/sh\nset -eu\ncase \"$1\" in\n--version) echo 'doof 1.2.3'; exit 0 ;;\nrun) while [ \"$1\" != -- ]; do shift; done; shift; mkdir -p \"$(dirname \"$2\")\"; echo bundle >\"$2\"; exit 0 ;;\nesac\ncommand=$1; input=$2; output=''; artifacts=''\nwhile [ \"$#\" -gt 0 ]; do\ncase \"$1\" in -o) output=$2; shift 2 ;; --distdir) artifacts=$2; shift 2 ;; *) shift ;; esac\ndone\nmkdir -p \"$output\"\ncase \"$input\" in */tools/debugger) mkdir -p \"$output/DoofDebugger.app/Contents/MacOS\"; cp \"$0\" \"$output/DoofDebugger.app/Contents/MacOS/DoofDebugger\"; exit 0 ;; esac\nif [ \"$command\" = package ]; then\nmkdir -p \"$artifacts\"; cp \"$0\" \"$artifacts/doof\"; echo runtime >\"$artifacts/doof_runtime.h\"; echo swift >\"$artifacts/doof_wasm_test_runner_apple.swift\"\nelse\ncp \"$0\" \"$output/doof\"\n" + (if converges then "echo stable" else "echo \"$output\"") + " >\"$output/graph.cpp\"\nfi\n"
  try! write(seed, script)
  try! command("chmod", ["+x", seed])
  return seed
}
export function testRepositoryBuildConvergesBeforePackaging(): none {
  temp := try! TemporaryDirectory()
  inputs := BuildInputs { root: temp.root, work: path(temp.root, "work"), source: path(temp.root, "source"), stdlib: path(temp.root, "stdlib"), seed: fakeSeed(temp.root, true), version: "1.2.3" }
  try! makeDirectory(inputs.source); try! makeDirectory(inputs.stdlib)
  result := try! buildToolchain(inputs, true)
  Assert.equal(result.generation, 2)
  Assert.equal(try! capture(path(result.artifacts, "doof"), ["--version"]), "doof 1.2.3")
  Assert.isTrue(exists(path(result.artifacts, "Doof Debugger.app/Contents/MacOS/DoofDebugger")))
  temp.close()
}
export function testRepositoryBuildStopsOnNonconvergence(): none {
  temp := try! TemporaryDirectory()
  inputs := BuildInputs { root: temp.root, work: path(temp.root, "work"), source: path(temp.root, "source"), stdlib: path(temp.root, "stdlib"), seed: fakeSeed(temp.root, false), version: "1.2.3" }
  try! makeDirectory(inputs.source); try! makeDirectory(inputs.stdlib)
  let failed = false
  case buildToolchain(inputs, true) {
    failure: Failure -> { failed = failure.error.contains("No generated-source fixed point") }
    success: Success -> {}
  }
  Assert.isTrue(failed)
  Assert.isFalse(exists(path(inputs.work, "artifacts")))
  temp.close()
}
