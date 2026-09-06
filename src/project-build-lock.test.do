import { Assert } from "std/assert"
import { File, IoError, exists, mkdir, remove, writeText } from "std/fs"
import { join, tempDirectory } from "std/path"
import { acquireProjectBuildLock, projectBuildLockPath } from "./project-build-lock"

export function testProjectBuildLockExcludesAndReleases(): none {
  root := join([tempDirectory(), "doof-project-lock-test"])
  handle := try! acquireProjectBuildLock(root, "build/nested")
  path := projectBuildLockPath(root, "build/nested")
  Assert.isTrue(exists(path))
  let blocked = false
  case File { path, mode: .ReadWrite, lock: .Exclusive, waitForLock: false } {
    failure: Failure -> { blocked = failure.error == IoError.WouldBlock }
    success: Success -> { try! success.value.close() }
  }
  Assert.isTrue(blocked)
  other := try! acquireProjectBuildLock(root, "independent")
  try! other.close()
  try! handle.close()
  // A leftover file is harmless: ownership is in the OS, not file existence.
  Assert.isTrue(exists(path))
  next := try! acquireProjectBuildLock(root, "build/nested")
  try! next.close()
  try! remove(path)
  try! remove(join([root, "build/nested"]))
  try! remove(join([root, "build"]))
  try! remove(projectBuildLockPath(root, "independent"))
  try! remove(join([root, "independent"]))
  try! remove(root)
}

export function testProjectBuildLockReportsFilesystemFailure(): none {
  root := join([tempDirectory(), "doof-project-lock-invalid-test"])
  if !exists(root) { try! mkdir(root) }
  blocker := join([root, "file"])
  try! writeText(blocker, "not a directory")
  let reported = false
  case acquireProjectBuildLock(root, "file/nested") {
    failure: Failure -> { reported = failure.error.contains("Could not create project build directory:") && failure.error.contains(blocker) }
    success: Success -> { try! success.value.close() }
  }
  Assert.isTrue(reported)
  try! remove(blocker)
  try! remove(root)
}
