import { Assert } from "std/assert"
import { planProfileCapture, planProfileOpen, planProfileSymbols } from "./profile-command"

export function testPlansProfileSymbolBundle(): none {
  plan := planProfileSymbols("/tmp/build/demo", "/tmp/build/demo.dSYM", "/tmp/project")
  Assert.equal(plan.command, "xcrun")
  expected := ["dsymutil", "/tmp/build/demo", "-o", "/tmp/build/demo.dSYM"]
  Assert.equal(plan.arguments.length, expected.length)
  for index of 0..<expected.length { Assert.equal(plan.arguments[index], expected[index]) }
  Assert.equal(plan.directory, "/tmp/project")
}

export function testPlansConsoleTimeProfileCapture(): none {
  plan := planProfileCapture(
    "/tmp/My Tool", ["--scenario", "large value"], "/tmp/project",
    "/tmp/project/build/profiles/demo.trace", "750ms",
  )
  Assert.equal(plan.command, "xcrun")
  Assert.equal(plan.directory, "/tmp/project")
  expected := [
    "xctrace", "record", "--template", "Time Profiler",
    "--output", "/tmp/project/build/profiles/demo.trace",
    "--time-limit", "750ms", "--target-stdin", "-", "--target-stdout", "-",
    "--launch", "--", "/tmp/My Tool", "--scenario", "large value",
  ]
  Assert.equal(plan.arguments.length, expected.length)
  for index of 0..<expected.length { Assert.equal(plan.arguments[index], expected[index]) }
}

export function testPlansMacOSAppCaptureWithoutConsoleRedirects(): none {
  plan := planProfileCapture("/tmp/Demo.app", ["--demo"], "/tmp/project", "/tmp/demo.trace", "", false)
  expected := [
    "xctrace", "record", "--template", "Time Profiler", "--output", "/tmp/demo.trace",
    "--launch", "--", "/tmp/Demo.app", "--demo",
  ]
  Assert.equal(plan.arguments.length, expected.length)
  for index of 0..<expected.length { Assert.equal(plan.arguments[index], expected[index]) }
}

export function testPlansOpeningCompletedProfile(): none {
  plan := planProfileOpen("/tmp/demo.trace", "/tmp/project")
  Assert.equal(plan.command, "open")
  Assert.equal(plan.arguments.length, 1)
  Assert.equal(plan.arguments[0], "/tmp/demo.trace")
  Assert.equal(plan.directory, "/tmp/project")
}
