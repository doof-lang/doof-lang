import { Assert } from "std/assert"
import { formatJsonValue } from "std/json"
import { stdlibRevisions } from "./provenance"
import { TemporaryDirectory } from "./test-support"
import { path, write, command, capture, jsonString } from "./common"

function commit(directory: string): string {
  try! command("git", ["init", "-q", directory])
  try! command("git", ["-C", directory, "add", "-A"])
  try! command("git", ["-C", directory, "-c", "user.name=Doof Test", "-c", "user.email=test@localhost", "commit", "-qm", "fixture"])
  return try! capture("git", ["-C", directory, "rev-parse", "HEAD"])
}
export function testRepositoryStdlibRecordsPackageRevisions(): none {
  temp := try! TemporaryDirectory()
  package := path(temp.root, "json")
  try! write(path(package, "doof.json"), "{\"name\":\"std/json\"}")
  revision := commit(package)
  try! write(path(temp.root, "example/doof.json"), "{\"name\":\"example\"}")
  revisions := try! stdlibRevisions(temp.root)
  Assert.equal(try! jsonString(revisions, "std/json"), revision)
  Assert.isFalse(formatJsonValue(revisions).contains("example"))
  try! write(path(package, "changed.do"), "function main(): none {}")
  let rejected = false
  case stdlibRevisions(temp.root) {
    failure: Failure -> { rejected = failure.error.contains("clean checkout") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
  temp.close()
}
export function testRepositoryStdlibSupportsSingleCheckout(): none {
  temp := try! TemporaryDirectory()
  try! write(path(temp.root, "json/doof.json"), "{\"name\":\"std/json\"}")
  let rejected = false
  case stdlibRevisions(temp.root) {
    failure: Failure -> { rejected = failure.error.contains("Git checkout") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
  revision := commit(temp.root)
  revisions := try! stdlibRevisions(temp.root)
  Assert.equal(try! jsonString(revisions, "."), revision)
  temp.close()
}
