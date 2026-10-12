import { Assert } from "std/assert"
import { hostPlatform, runNativeCommand } from "./process-driver"

export function testHostPlatformUsesDoofPlatformNames(): none {
  Assert.notEqual(hostPlatform(), "darwin")
  Assert.notEqual(hostPlatform(), "")
}

export function testMissingCommandReportsLaunchError(): none {
  result := runNativeCommand("/nonexistent/doof-process-driver-test", [])
  Assert.equal(result.exitCode, -1)
  Assert.notEqual(result.error, "")
  Assert.isFalse(result.truncated)
}

export function testCapturedCommandOutputIsReturned(): none {
  result := runNativeCommand("/bin/echo", ["hello"])
  Assert.equal(result.exitCode, 0)
  Assert.equal(result.output.length, 6)
}
