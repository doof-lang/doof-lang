import { Assert } from "std/assert"
import { File, IoError, exists, mkdir, remove, writeText } from "std/fs"
import { join, tempDirectory } from "std/path"
import { acquireProjectBuildLock, projectBuildLockPath } from "./project-build-lock"

export function testProjectBuildLockExcludesAndReleases(): none {
  root := join([tempDirectory(), "doof-project-lock-test"])
  handle := acquireProjectBuildLock(root, "build/nested")!
  path := projectBuildLockPath(root, "build/nested")
  Assert.isTrue(exists(path))
  let blocked = false
  case File { path, mode: .ReadWrite, lock: .Exclusive, waitForLock: false } {
    failure: Failure -> { blocked = failure.error == IoError.WouldBlock }
    success: Success -> { success.value.close()! }
  }
  Assert.isTrue(blocked)
  other := acquireProjectBuildLock(root, "independent")!
  other.close()!
  handle.close()!
  // A leftover file is harmless: ownership is in the OS, not file existence.
  Assert.isTrue(exists(path))
  next := acquireProjectBuildLock(root, "build/nested")!
  next.close()!
  remove(path)!
  remove(join([root, "build/nested"]))!
  remove(join([root, "build"]))!
  remove(projectBuildLockPath(root, "independent"))!
  remove(join([root, "independent"]))!
  remove(root)!
}

export function testProjectBuildLockReportsFilesystemFailure(): none {
  root := join([tempDirectory(), "doof-project-lock-invalid-test"])
  if !exists(root) { mkdir(root)! }
  blocker := join([root, "file"])
  writeText(blocker, "not a directory")!
  let reported = false
  case acquireProjectBuildLock(root, "file/nested") {
    failure: Failure -> { reported = failure.error.contains("Could not create project build directory:") && failure.error.contains(blocker) }
    success: Success -> { success.value.close()! }
  }
  Assert.isTrue(reported)
  remove(blocker)!
  remove(root)!
}
