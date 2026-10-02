import { Assert } from "std/assert"
import { exists } from "std/fs"
import { formatJsonValue } from "std/json"
import { uuidV4 } from "std/crypto"
import { tempDirectory } from "std/path"
import { capture, cleanRevision, command, developmentVersion, erase, jsonFile, jsonString, makeDirectory, path, quote, read, stableVersion, stamp, write } from "./common"

import { TemporaryDirectory } from "./test-support"
export function testRepositoryStableVersionValidation(): none {
  for version of ["0.0.0", "1.2.3", "10.0.123"] { Assert.isTrue(stableVersion(version)) }
  for version of ["v1.2.3", "01.2.3", "1.2", "../1.2.3", "1.2.3-dev", "1.2.3\n", "1.2.3+local"] { Assert.isFalse(stableVersion(version)) }
}
export function testRepositoryStampIsolatedInputs(): none {
  temp := TemporaryDirectory()!
  source := path(temp.root, "source"); staged := path(temp.root, "staged")
  write(path(source, "doof.json"), "{\"version\":\"0.2.0\"}")!
  write(path(source, "tools/debugger/doof.json"), "{\"version\":\"0.2.0\"}")!
  write(path(source, "src/version.do"), "export readonly compilerVersion = \"0.2.0-dev.unstamped\"\nexport readonly compilerVersionStamped = false\n")!
  first := developmentVersion(source)!; second := developmentVersion(source)!
  Assert.isTrue(first != second)
  Assert.isTrue(first.startsWith("0.2.0-dev."))
  stamp(source, staged, first)!
  Assert.stringContains(read(path(staged, "src/version.do"))!, "export readonly compilerVersionStamped = true")
  Assert.equal(jsonString(jsonFile(path(staged, "doof.json"))!, "version")!, first)
  Assert.equal(jsonString(jsonFile(path(source, "doof.json"))!, "version")!, "0.2.0")
  stamp(source, staged, "2.0.0")!
  Assert.equal(jsonString(jsonFile(path(staged, "tools/debugger/doof.json"))!, "version")!, "2.0.0")
  temp.close()
}
export function testRepositoryCleanInputDiagnostics(): none {
  temp := TemporaryDirectory()!
  command("git", ["init", "-q", temp.root])!
  write(path(temp.root, "uncommitted.do"), "function main(): none {}")!
  let rejected = false
  case cleanRevision(temp.root) {
    failure: Failure -> { rejected = failure.error.contains("clean checkout") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
  temp.close()
}
export function testRepositoryShellQuoting(): none {
  value := "spaces 'quotes' $(not-executed) `literal`\nnext line"
  actual := capture("sh", ["-c", "printf %s " + quote(value)])!
  Assert.equal(actual, value)
}
