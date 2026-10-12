import { Assert } from "std/assert"
import { silentTestFailureMessage, structuredTestResult } from "./test-driver"

export function testEditorDriverReportsExactIdentityAndExitStatus(): none {
  value := structuredTestResult("example.test.do::testOne", 7, "failure\n")
  Assert.equal(value.get("id")!, "example.test.do::testOne")
  Assert.equal(value.get("exitCode")!, 7)
  Assert.equal(value.get("output")!, "failure\n")
}

export function testDescribesSilentTestCrashSignal(): none {
  Assert.equal(silentTestFailureMessage(139), "test process terminated by signal 11 (SIGSEGV) without output")
  Assert.equal(silentTestFailureMessage(134), "test process terminated by signal 6 (SIGABRT) without output")
  Assert.equal(silentTestFailureMessage(159), "test process terminated by signal 31 without output")
}

export function testDescribesSilentTestExitCode(): none {
  Assert.equal(silentTestFailureMessage(1), "test process exited with code 1 without output")
  Assert.equal(silentTestFailureMessage(128), "test process exited with code 128 without output")
  Assert.equal(silentTestFailureMessage(-1), "test process exited with code -1 without output")
}
