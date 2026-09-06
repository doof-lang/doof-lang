// Project-wide serialization, independent of per-command output directories.
import { File, IoError, isDirectory, mkdir } from "std/fs"
import { dirname, join } from "std/path"

import isolated function printFlushed(value: string): none from "doof_runtime.hpp" as doof::print_flushed

export function projectBuildLockPath(root: string, buildDirectory: string): string {
  return join([root, buildDirectory, ".doof.lock"])
}

function ensureLockDirectory(directory: string): Result<none, string> {
  if isDirectory(directory) { return Success() }
  parent := dirname(directory)
  if parent != directory { try ensureLockDirectory(parent) }
  _ := mkdir(directory) else {
    // Another invocation may have created the directory concurrently.
    if !isDirectory(directory) { return Failure("Could not create project build directory: " + directory) }
  }
  return Success()
}

/** Keep the returned handle alive for the entire operation. Never unlink it. */
export function acquireProjectBuildLock(root: string, buildDirectory: string): Result<File, string> {
  directory := join([root, buildDirectory])
  try ensureLockDirectory(directory)
  path := projectBuildLockPath(root, buildDirectory)
  handle := File { path, mode: .ReadWrite, create: true, lock: .Exclusive, waitForLock: false } else error {
    if error != IoError.WouldBlock {
      return Failure("Could not acquire project build lock: " + path)
    }
    printFlushed("Waiting for project build lock: " + path + "\n")
    while true {
      waiting := File { path, mode: .ReadWrite, create: true, lock: .Exclusive, waitForLock: true } else waitError {
        if waitError == IoError.Interrupted { continue }
        return Failure("Could not acquire project build lock: " + path)
      }
      return Success(waiting)
    }
  }
  return Success(handle)
}
