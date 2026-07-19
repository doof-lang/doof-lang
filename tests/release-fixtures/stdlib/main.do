import { readText, writeText } from "std/fs"
import { formatJsonValue } from "std/json"
import { currentWorkingDirectory } from "std/path"
import { Instant } from "std/time"

function main(): int {
  cwd := try! currentWorkingDirectory()
  path := cwd + "/selfhost-release-stdlib.txt"
  try! writeText(path, "stdlib")
  if (try! readText(path)) != "stdlib" { return 1 }
  if formatJsonValue({ ok: true }).length == 0 { return 2 }
  if Instant.now().toEpochNanos() <= 0L { return 3 }
  return 0
}
