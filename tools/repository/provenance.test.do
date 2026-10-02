import { Assert } from "std/assert"
import { formatJsonValue } from "std/json"
import { stdlibRevisions } from "./provenance"
import { TemporaryDirectory } from "./test-support"
import { path, write, command, capture, jsonString } from "./common"

function commit(directory: string): string {
  command("git", ["init", "-q", directory])!
  command("git", ["-C", directory, "add", "-A"])!
  command("git", ["-C", directory, "-c", "user.name=Doof Test", "-c", "user.email=test@localhost", "commit", "-qm", "fixture"])!
  return capture("git", ["-C", directory, "rev-parse", "HEAD"])!
}
export function testRepositoryStdlibRecordsPackageRevisions(): none {
  temp := TemporaryDirectory()!
  package := path(temp.root, "json")
  write(path(package, "doof.json"), "{\"name\":\"std/json\"}")!
  revision := commit(package)
  write(path(temp.root, "example/doof.json"), "{\"name\":\"example\"}")!
  revisions := stdlibRevisions(temp.root)!
  Assert.equal(jsonString(revisions, "std/json")!, revision)
  Assert.isFalse(formatJsonValue(revisions).contains("example"))
  write(path(package, "changed.do"), "function main(): none {}")!
  let rejected = false
  case stdlibRevisions(temp.root) {
    failure: Failure -> { rejected = failure.error.contains("clean checkout") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
  temp.close()
}
export function testRepositoryStdlibSupportsSingleCheckout(): none {
  temp := TemporaryDirectory()!
  write(path(temp.root, "json/doof.json"), "{\"name\":\"std/json\"}")!
  let rejected = false
  case stdlibRevisions(temp.root) {
    failure: Failure -> { rejected = failure.error.contains("Git checkout") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
  revision := commit(temp.root)
  revisions := stdlibRevisions(temp.root)!
  Assert.equal(jsonString(revisions, ".")!, revision)
  temp.close()
}
