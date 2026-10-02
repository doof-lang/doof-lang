import { Assert } from "std/assert"
import { signingPreflight, validateReleaseStatus, smokeDebuggerApplication } from "./release"
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
