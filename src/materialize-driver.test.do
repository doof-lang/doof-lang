import { Assert } from "std/assert"
import { driverOutputPath, ensureOutputDirectory, materializeGeneratedText } from "./materialize-driver"
import { exists, isDirectory, metadata, readText } from "std/fs"
import { Instant } from "std/time"

export function testOutputPathsJoinWithSingleSeparator(): none {
  Assert.equal(driverOutputPath("/tmp/out", "a.hpp"), "/tmp/out/a.hpp")
  Assert.equal(driverOutputPath("/tmp/out/", "a.hpp"), "/tmp/out/a.hpp")
}

export function testGeneratedTextCreatesParentsAndPreservesUnchangedFiles(): none {
  root := "/tmp/doof-materialize-driver-test-" + string(Instant.now().toEpochMillis())
  path := root + "/nested/dir/module.cpp"
  materializeGeneratedText(path, "int x;\n")
  Assert.equal(readText(path)!, "int x;\n")
  before := metadata(path)!.modifiedAt.toEpochNanos()
  materializeGeneratedText(path, "int x;\n")
  Assert.equal(metadata(path)!.modifiedAt.toEpochNanos(), before)
  materializeGeneratedText(path, "int y;\n")
  Assert.equal(readText(path)!, "int y;\n")
}

export function testEnsureOutputDirectoryIsIdempotent(): none {
  root := "/tmp/doof-materialize-driver-dirs-" + string(Instant.now().toEpochMillis()) + "/a/b"
  ensureOutputDirectory(root)
  ensureOutputDirectory(root)
  Assert.isTrue(exists(root))
  Assert.isTrue(isDirectory(root))
}
