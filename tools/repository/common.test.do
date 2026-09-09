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
  temp := try! TemporaryDirectory()
  source := path(temp.root, "source"); staged := path(temp.root, "staged")
  try! write(path(source, "doof.json"), "{\"version\":\"0.1.0\"}")
  try! write(path(source, "tools/debugger/doof.json"), "{\"version\":\"0.1.0\"}")
  try! write(path(source, "src/version.do"), "export readonly compilerVersion = \"0.1.0-dev.unstamped\"\nexport readonly compilerVersionStamped = false\n")
  first := try! developmentVersion(source); second := try! developmentVersion(source)
  Assert.isTrue(first != second)
  Assert.isTrue(first.startsWith("0.1.0-dev."))
  try! stamp(source, staged, first)
  Assert.stringContains(try! read(path(staged, "src/version.do")), "export readonly compilerVersionStamped = true")
  Assert.equal(try! jsonString(try! jsonFile(path(staged, "doof.json")), "version"), first)
  Assert.equal(try! jsonString(try! jsonFile(path(source, "doof.json")), "version"), "0.1.0")
  try! stamp(source, staged, "2.0.0")
  Assert.equal(try! jsonString(try! jsonFile(path(staged, "tools/debugger/doof.json")), "version"), "2.0.0")
  temp.close()
}
export function testRepositoryCleanInputDiagnostics(): none {
  temp := try! TemporaryDirectory()
  try! command("git", ["init", "-q", temp.root])
  try! write(path(temp.root, "uncommitted.do"), "function main(): none {}")
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
  actual := try! capture("sh", ["-c", "printf %s " + quote(value)])
  Assert.equal(actual, value)
}
