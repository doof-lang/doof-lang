import { Assert } from "std/assert"
import { codesignTimestampUnavailable, formatElapsed, releaseStageArguments, releaseStageNames, runReleaseStage, signingPreflight, validateReleaseStatus, smokeDebuggerApplication } from "./release"
import { TemporaryDirectory } from "./test-support"
import { path, write, command } from "./common"
export function testRepositoryPublishedVersionsAreImmutable(): none {
  validateReleaseStatus("404")!
  for status of ["200", "403", "500"] {
    let rejected = false
    case validateReleaseStatus(status) {
      failure: Failure -> { rejected = failure.error.contains("immutable") }
      success: Success -> {}
    }
    Assert.isTrue(rejected)
  }
}
export function testRepositorySigningRequiresConfiguration(): none {
  let rejected = false
  case signingPreflight("", "") {
    failure: Failure -> { rejected = failure.error.contains("required") || failure.error.contains("require") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
}
export function testRepositoryDebuggerStartupRejectsEarlyExit(): none {
  temp := TemporaryDirectory()!
  executable := path(temp.root, "Doof Debugger.app/Contents/MacOS/DoofDebugger")
  write(executable, "#!/bin/sh\nexit 1\n")!
  command("chmod", ["+x", executable])!
  let rejected = false
  case smokeDebuggerApplication(temp.root) {
    failure: Failure -> { rejected = failure.error.contains("startup") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
  write(executable, "#!/bin/sh\nexec /bin/sleep 20\n")!
  smokeDebuggerApplication(temp.root)!
  temp.close()
}

export function testCodesignRetriesOnlyTimestampServiceFailures(): none {
  Assert.isTrue(codesignTimestampUnavailable("/tmp/doof: replacing existing signature\n/tmp/doof: A timestamp was expected but was not found."))
  Assert.isTrue(codesignTimestampUnavailable("/tmp/doof: The timestamp service is not available."))
  Assert.isFalse(codesignTimestampUnavailable("/tmp/doof: no identity found"))
}

export function testReleaseStageElapsedTimesAreReadable(): none {
  Assert.equal(formatElapsed(0L), "0s")
  Assert.equal(formatElapsed(59L), "59s")
  Assert.equal(formatElapsed(60L), "1m00s")
  Assert.equal(formatElapsed(605L), "10m05s")
}

export function testReleaseRunsWindowsStageOnlyWhenConfigured(): none {
  Assert.arrayEqual(releaseStageNames(false).cloneReadonly(), ["tests", "runtime", "macos"])
  Assert.arrayEqual(releaseStageNames(true).cloneReadonly(), ["tests", "runtime", "macos", "windows"])
}

export function testReleaseStagesReenterTheRepositoryTool(): none {
  Assert.arrayEqual(releaseStageArguments("/repo root", "1.2.3", "tests").cloneReadonly(), ["/repo root", "release-stage", "1.2.3", "tests"])
}

export function testReleaseStageRejectsUnknownStagesAndMissingToolchains(): none {
  temp := TemporaryDirectory()!
  let missing = false
  case runReleaseStage(temp.root, "1.2.3", "tests") {
    failure: Failure -> { missing = failure.error.contains("built toolchain") }
    success: Success -> {}
  }
  Assert.isTrue(missing)
  work := path(temp.root, "build/releases/1.2.3")
  write(path(work, "source/dist/doof"), "")!
  write(path(work, "artifacts/doof"), "")!
  let unknown = false
  case runReleaseStage(temp.root, "1.2.3", "publish") {
    failure: Failure -> { unknown = failure.error.contains("Unknown release stage: publish") }
    success: Success -> {}
  }
  Assert.isTrue(unknown)
  temp.close()
}
