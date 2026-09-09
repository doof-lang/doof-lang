import { Assert } from "std/assert"
import { exists } from "std/fs"
import { TemporaryDirectory } from "./test-support"
import { command, path, read, write, makeDirectory } from "./common"
import { canonicalText, exportGraph, NativeCommand, relocateArgument } from "./snapshot"

export function testRepositorySnapshotReplaysCapturedGraph(): none {
  temp := try! TemporaryDirectory()
  graph := path(temp.root, "generated"); target := path(temp.root, "snapshot")
  try! write(path(graph, "one.cpp"), "#line 1 \"/Users/dev/source/a.do\"\nint main() {return 0;}\n")
  try! write(path(graph, "unused.cpp"), "not compiled\n")
  try! write(path(graph, "one.o"), "binary")
  object := path(graph, ".doof-objects/one.o")
  records := [
    NativeCommand { compiler: "clang++", arguments: ["-std=c++17", "-I", graph, "-include-pch", path(graph, "runtime.hpp.pch"), "-MMD", "-MF", object + ".d", "-c", path(graph, "one.cpp"), "-o", object] },
    NativeCommand { compiler: "clang++", arguments: [object, "-o", path(temp.root, "artifacts/doof")] },
  ]
  try! exportGraph(graph, target, "/Users/dev/source", records)
  script := try! read(path(target, "build.sh"))
  Assert.isFalse(script.contains(temp.root))
  Assert.isFalse(script.contains("unused.cpp"))
  Assert.isFalse(script.contains("-include-pch"))
  Assert.isFalse((try! read(path(target, "sources/one.cpp"))).contains("#line"))
  Assert.isFalse(exists(path(target, "sources/one.o")))
  try! command("sh", ["-n", path(target, "build.sh")])
  temp.close()
}
export function testRepositorySnapshotRejectsUnknownNativePaths(): none {
  let rejected = false
  case relocateArgument("/Users/other/private.h", "/build", "/source", {}) {
    failure: Failure -> { rejected = true }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
  Assert.equal(canonicalText("#line 1 \"/Users/dev/source/main.do\"\nUsers_dev_source_main", "/Users/dev/source"), "doof_source_main")
}
