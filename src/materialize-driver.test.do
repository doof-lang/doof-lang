import { Assert } from "std/assert"
import { ProjectEmission, ProjectNativeCopy } from "./emitter-project"
import {
  driverOutputPath, ensureOutputDirectory, materializeExecutableResources, materializeGeneratedText, materializeProject,
  synchronizeExecutableResources,
} from "./materialize-driver"
import { PackageResource } from "./package-manifest"
import { exists, isDirectory, metadata, readText, writeText } from "std/fs"
import { run } from "std/os"
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

export function testNativeCopiesKeepExecutePermissions(): none {
  root := "/tmp/doof-materialize-driver-modes-" + string(Instant.now().toEpochMillis())
  ensureOutputDirectory(root + "/package/vendor")
  writeText(root + "/package/vendor/configure", "#!/bin/sh\n")!
  writeText(root + "/package/vendor/README", "plain\n")!
  Assert.equal(run("chmod", ["755", root + "/package/vendor/configure"])!.exitCode, 0)
  project := ProjectEmission {
    nativeCopies: [ProjectNativeCopy { sourcePath: root + "/package/vendor", relativePath: "pkg/vendor" }],
  }
  materializeProject(root + "/out", project)!
  Assert.equal(run("test", ["-x", root + "/out/pkg/vendor/configure"])!.exitCode, 0)
  Assert.notEqual(run("test", ["-x", root + "/out/pkg/vendor/README"])!.exitCode, 0)
}

export function testMissingResourceDirectoryReportsSourcePath(): none {
  root := "/tmp/doof-materialize-driver-missing-resource-" + string(Instant.now().toEpochMillis())
  missing := root + "/package/assets"
  resources := [PackageResource { sourcePath: missing, destination: "assets" }]
  message := case synchronizeExecutableResources(resources, root + "/out", root + "/cache/resources") {
    _: Success -> "",
    failure: Failure -> failure.error,
  }
  Assert.isTrue(message.contains(missing), "expected missing resource path, got: " + message)
  Assert.isTrue(message.contains("resources in doof.json"), "expected manifest hint, got: " + message)
  Assert.isFalse(exists(root + "/cache/resources"), "resource state must not be written after a failure")
}

export function testMissingPackagedResourceReportsSourcePath(): none {
  root := "/tmp/doof-materialize-driver-missing-dist-resource-" + string(Instant.now().toEpochMillis())
  missing := root + "/package/config.json"
  resources := [PackageResource { sourcePath: missing, destination: "" }]
  message := case materializeExecutableResources(resources, root + "/dist") {
    _: Success -> "",
    failure: Failure -> failure.error,
  }
  Assert.isTrue(message.contains(missing), "expected missing resource path, got: " + message)
}

export function testExistingResourceDirectorySynchronizes(): none {
  root := "/tmp/doof-materialize-driver-resource-" + string(Instant.now().toEpochMillis())
  ensureOutputDirectory(root + "/package/assets")
  writeText(root + "/package/assets/data.txt", "data\n")!
  resources := [PackageResource { sourcePath: root + "/package/assets", destination: "assets" }]
  synchronizeExecutableResources(resources, root + "/out", root + "/cache/resources")!
  Assert.equal(readText(root + "/out/assets/data.txt")!, "data\n")
}

export function testStringFileResourceKeepsItsPackageRelativePath(): none {
  root := "/tmp/doof-materialize-driver-string-file-" + string(Instant.now().toEpochMillis())
  ensureOutputDirectory(root + "/package/config")
  writeText(root + "/package/config/defaults.json", "{}")!
  writeText(root + "/package/top.txt", "top")!
  resources := [
    PackageResource { sourcePath: root + "/package/config/defaults.json", destination: "config/defaults.json", preserveSourcePath: true },
    PackageResource { sourcePath: root + "/package/top.txt", destination: "top.txt", preserveSourcePath: true },
    PackageResource { sourcePath: root + "/package/top.txt", destination: "assets" },
  ]
  materializeExecutableResources(resources, root + "/dist")!
  Assert.equal(readText(root + "/dist/config/defaults.json")!, "{}")
  Assert.isFalse(isDirectory(root + "/dist/config/defaults.json"), "a string file entry must not become a directory")
  Assert.equal(readText(root + "/dist/top.txt")!, "top")
  Assert.equal(readText(root + "/dist/assets/top.txt")!, "top", "from/to file entries land inside their destination")

  synchronizeExecutableResources(resources, root + "/out", root + "/cache/resources")!
  Assert.equal(readText(root + "/out/config/defaults.json")!, "{}")
  Assert.equal(readText(root + "/out/top.txt")!, "top")
}
