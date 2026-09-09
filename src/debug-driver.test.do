import { Assert } from "std/assert"
import { debugTargetError } from "./debug-command"

export function testDebugDriverRejectsUnsupportedTargetsBeforeLaunch(): none {
  Assert.equal(debugTargetError("macos", "executable"), "")
  Assert.equal(debugTargetError("macos", "ios-app") != "", true)
}

import { writeDebugLaunch } from "./debug-driver"
import { DebugLaunch } from "./debug-command"
import { tempDirectory, join } from "std/path"
import { pid } from "std/os"
import { exists, readText, remove } from "std/fs"
import { parseJsonValue } from "std/json"

export function testDebugDriverWritesExternalLaunch(): none {
  path := join([tempDirectory(), "doof-launch-" + string(pid()) + " 工具.json"])
  launch := DebugLaunch { executable: "/tmp/app space", source: "/tmp/main.do", directory: "/tmp", symbols: "/tmp/app space.dSYM", arguments: ["a b", "工具"] }
  Assert.equal(writeDebugLaunch(launch, path), 0)
  Assert.isTrue(exists(path))
  decoded := try! DebugLaunch.fromJsonValue(try! parseJsonValue(try! readText(path)))
  Assert.equal(decoded.arguments[1], "工具")
  Assert.equal(decoded.executable, launch.executable)
  try! remove(path)
  Assert.equal(writeDebugLaunch(launch, path + "/missing/file.json"), 1)
  invalid := DebugLaunch { executable: "relative", source: "/s", directory: "/d", symbols: "/x" }
  Assert.equal(writeDebugLaunch(invalid, path), 1)
  Assert.isFalse(exists(path))
}
