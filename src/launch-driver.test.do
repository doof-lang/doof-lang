import { Assert } from "std/assert"
import { nativeBuildOutputModeForCommand, takeObserveUrlFile } from "./launch-driver"
import { exists, writeText } from "std/fs"

export function testObserveAndRunSuppressSuccessfulNativeBuildProgress(): none {
  Assert.equal(nativeBuildOutputModeForCommand("run"), .Silent)
  Assert.equal(nativeBuildOutputModeForCommand("observe"), .Silent)
  Assert.equal(nativeBuildOutputModeForCommand("build"), .Progress)
}

export function testDetachedObservedAppUrlFileIsConsumed(): none {
  path := "/tmp/doof-observe-url-driver-test"
  writeText(path, "http://127.0.0.1:4317/token/\n")!
  Assert.equal(takeObserveUrlFile(path, 1), "http://127.0.0.1:4317/token/")
  Assert.isFalse(exists(path))
  Assert.equal(takeObserveUrlFile(path, 0), "")
}
