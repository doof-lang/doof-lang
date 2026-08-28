import { Assert } from "std/assert"
import { planAppleWasmTestRun, planAppleWasmTestRunnerBuild } from "./wasm-test-runner"

export function testPlansAppleJavaScriptCoreRunnerBuild(): none {
  plan := planAppleWasmTestRunnerBuild("/tmp/runner.swift", "/tmp/runner")
  Assert.equal(plan.command, "xcrun")
  Assert.equal(plan.arguments.length, 6)
  Assert.equal(plan.arguments[0], "swiftc")
  Assert.equal(plan.arguments[1], "/tmp/runner.swift")
  Assert.equal(plan.arguments[2], "-framework")
  Assert.equal(plan.arguments[3], "JavaScriptCore")
  Assert.equal(plan.arguments[4], "-o")
  Assert.equal(plan.arguments[5], "/tmp/runner")
}

export function testPlansFreshAppleWasmTestInvocation(): none {
  plan := planAppleWasmTestRun(
    "/tmp/doof-wasm-test-runner",
    "/tmp/doof-tests.wasm",
    "math.test.do::testAdds",
  )
  Assert.equal(plan.command, "/tmp/doof-wasm-test-runner")
  Assert.equal(plan.arguments.length, 2)
  Assert.equal(plan.arguments[0], "/tmp/doof-tests.wasm")
  Assert.equal(plan.arguments[1], "math.test.do::testAdds")
}
