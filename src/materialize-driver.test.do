import { Assert } from "std/assert"
import { ProjectEmission, ProjectNativeCopy } from "./emitter-project"
import { driverOutputPath, ensureOutputDirectory, materializeGeneratedText, materializeProject } from "./materialize-driver"
import { exists, isDirectory, metadata, readText, writeText } from "std/fs"
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

export function testNativeCopiesMaterializeNestedPackageInputs(): none {
  root := "/tmp/doof-materialize-driver-copy-" + string(Instant.now().toEpochMillis())
  ensureOutputDirectory(root + "/package/include")
  writeText(root + "/package/include/native.hpp", "// native\n")!
  project := ProjectEmission {
    nativeCopies: [ProjectNativeCopy { sourcePath: root + "/package/include", relativePath: "pkg/include" }],
  }
  materializeProject(root + "/out", project)!
  Assert.equal(readText(root + "/out/pkg/include/native.hpp")!, "// native\n")
}

export function testMissingNativeCopyReportsSourcePath(): none {
  root := "/tmp/doof-materialize-driver-missing-" + string(Instant.now().toEpochMillis())
  missing := root + "/package/native_test_support.hpp"
  project := ProjectEmission {
    nativeCopies: [ProjectNativeCopy { sourcePath: missing, relativePath: "pkg/native_test_support.hpp" }],
  }
  message := case materializeProject(root + "/out", project) {
    _: Success -> "",
    failure: Failure -> failure.error,
  }
  Assert.isTrue(message.contains(missing), "expected missing source path, got: " + message)
  Assert.isTrue(message.contains("build.native"), "expected manifest hint, got: " + message)
}
