import { Assert } from "std/assert"
import { sha256Hex } from "std/crypto"
import { exists, readBlob } from "std/fs"
import { Exec, ExecOptions } from "std/os"
import { currentWorkingDirectory, dirname } from "std/path"
import { TemporaryDirectory } from "./test-support"
import { capture, command, copyTree, erase, execute, makeDirectory, path, read, require, setting, text, write } from "./common"

class DownloadFixture {
  temporary: TemporaryDirectory
  repo: string
  home: string
  artifacts: string
  let archive: string
  let archiveName: string
  environment: Map<string, string>
}
function fixture(): DownloadFixture {
  temporary := try! TemporaryDirectory()
  cwd := try! currentWorkingDirectory()
  let discovered = cwd
  while !exists(path(discovered, "install.sh")) && dirname(discovered) != discovered { discovered = dirname(discovered) }
  repo := setting("DOOF_REPOSITORY_TEST_ROOT", discovered)
  root := temporary.root
  bin := path(root, "bin")
  artifacts := path(root, "artifacts")
  try! makeDirectory(bin)
  curl := "#!/bin/sh\nset -eu\n[ \"\${DOWNLOAD_FAIL:-}\" != 1 ] || exit 22\noutput=''\nurl=''\nwhile [ \"$#\" -gt 0 ]; do\ncase \"$1\" in\n-o) output=$2; shift 2 ;;\nhttps:*) url=$1; shift ;;\n*) shift ;;\nesac\ndone\ncase \"$url\" in\n*/latest) printf https://github.com/doof-lang/doof-lang/releases/tag/v1.2.3 ;;\n*/SHA256SUMS) cp \"$FIXTURE/SHA256SUMS\" \"$output\" ;;\n*/\"$FIXTURE_ARCHIVE\") cp \"$FIXTURE/$FIXTURE_ARCHIVE\" \"$output\" ;;\n*) exit 23 ;;\nesac\n"
  try! write(path(bin, "curl"), curl)
  try! write(path(bin, "uname"), "#!/bin/sh\ncase \"$1\" in -s) echo Darwin ;; -m) echo arm64 ;; esac\n")
  try! command("chmod", ["+x", path(bin, "curl"), path(bin, "uname")])
  archiveName := "doof-1.2.3-macos-arm64.zip"
  result := DownloadFixture { temporary, repo, home: path(root, "home"), artifacts, archive: path(root, archiveName), archiveName, environment: { DOOF_HOME: path(root, "home"), PATH: bin + ":" + setting("PATH"), FIXTURE: root, FIXTURE_ARCHIVE: archiveName } }
  payload(result)
  return result
}
function payload(f: DownloadFixture, version: string = "1.2.3"): none {
  try! erase(f.artifacts); try! makeDirectory(f.artifacts)
  try! write(path(f.artifacts, "doof"), "#!/bin/sh\ncase \"$1\" in --version) echo \"doof " + version + "\" ;; --help|emit) exit 0 ;; *) exit 64 ;; esac\n")
  for name of ["doof_runtime.hpp", "doof_observer.hpp", "doof_observer_platform.hpp", "doof_wasm_test_runner_apple.swift", "doof-stdlib.tar"] { try! write(path(f.artifacts, name), "fixture") }
  try! write(path(f.artifacts, "observer-ui/index.html"), "observer")
  debugger := path(f.artifacts, "Doof Debugger.app/Contents/MacOS/DoofDebugger")
  try! write(debugger, "#!/bin/sh\nexit 0\n")
  try! command("chmod", ["+x", path(f.artifacts, "doof"), debugger])
  archive(f)
}
function checksum(f: DownloadFixture): none {
  try! write(path(f.temporary.root, "SHA256SUMS"), sha256Hex(try! readBlob(f.archive)) + "  " + f.archiveName + "\n")
}
function archive(f: DownloadFixture): none {
  try! erase(f.archive)
  if f.archiveName.endsWith(".zip") {
    try! command("ditto", ["-c", "-k", "--norsrc", f.artifacts, f.archive])
  } else {
    try! command("tar", ["-czf", f.archive, "doof", "doof_runtime.hpp", "doof_observer.hpp", "doof_observer_platform.hpp", "doof_wasm_test_runner_apple.swift", "doof-stdlib.tar", "observer-ui"], {}, f.artifacts)
  }
  checksum(f)
}
function invoke(f: DownloadFixture, arguments: string[] = [], success: bool = false): string {
  args := ["-s", "--"]
  for argument of arguments { args.push(argument) }
  process := try! Exec.spawn("bash", args, ExecOptions { env: f.environment.cloneReadonly(), withStdin: true, mergeStderrIntoStdout: true })
  try! process.writeStdinText(try! read(path(f.repo, "install.sh")))
  try! process.closeStdin()
  let output = ""
  for chunk of process.stdoutStream() { output += text(chunk) }
  status := try! process.wait()
  assert((status == 0) == success, "Installer status " + string(status) + ": " + output)
  if !success { Assert.isFalse(exists(path(f.home, "current"))) }
  return output
}
export function testRepositoryDownloadLatestAndPinnedVersion(): none {
  f := fixture()
  invoke(f, [], true)
  Assert.equal(try! capture("readlink", [path(f.home, "current")]), "versions/1.2.3")
  Assert.equal(try! capture("readlink", [path(f.home, "bin/doof")]), "../current/doof")
  invoke(f, ["--version", "1.2.3"], true)
  Assert.isFalse(exists(path(f.home, ".install-lock")))
  f.temporary.close()
}
export function testRepositoryDownloadInstallsLinuxX64Tarball(): none {
  f := fixture()
  f.archiveName = "doof-1.2.3-linux-x64-musl.tar.gz"
  f.archive = path(f.temporary.root, f.archiveName)
  f.environment.set("FIXTURE_ARCHIVE", f.archiveName)
  try! write(path(f.temporary.root, "bin/uname"), "#!/bin/sh\ncase \"$1\" in -s) echo Linux ;; -m) echo x86_64 ;; esac\n")
  payload(f)
  invoke(f, [], true)
  Assert.equal(try! capture("readlink", [path(f.home, "current")]), "versions/1.2.3")
  Assert.isFalse(exists(path(f.home, "bin/Doof Debugger.app")))
  f.temporary.close()
}
export function testRepositoryReleaseTargetMapping(): none {
  f := fixture()
  helper := "DOOF_INSTALL_LIBRARY_ONLY=1; . \"$1\"; release_target \"$2\" \"$3\""
  Assert.equal(try! capture("sh", ["-c", helper, "sh", path(f.repo, "install.sh"), "Darwin", "arm64"]), "macos-arm64 zip")
  Assert.equal(try! capture("sh", ["-c", helper, "sh", path(f.repo, "install.sh"), "Linux", "aarch64"]), "linux-arm64-musl tar.gz")
  Assert.equal(try! capture("sh", ["-c", helper, "sh", path(f.repo, "install.sh"), "Linux", "x86_64"]), "linux-x64-musl tar.gz")
  unsupported := try! execute("sh", ["-c", helper, "sh", path(f.repo, "install.sh"), "Linux", "riscv64"])
  Assert.isTrue(unsupported.exitCode != 0)
  f.temporary.close()
}
export function testRepositoryDownloadRejectsInvalidInputs(): none {
  f := fixture()
  invoke(f, ["--version", "../1.2.3"])
  f.environment.set("DOWNLOAD_FAIL", "1")
  invoke(f)
  f.environment.set("DOWNLOAD_FAIL", "")
  try! write(path(f.temporary.root, "bin/uname"), "#!/bin/sh\necho Linux\n")
  invoke(f)
  f.temporary.close()
}
export function testRepositoryDownloadVerifiesChecksumAndVersion(): none {
  f := fixture()
  try! write(path(f.temporary.root, "SHA256SUMS"), "0000000000000000000000000000000000000000000000000000000000000000  doof-1.2.3-macos-arm64.zip\n")
  invoke(f)
  checksum(f)
  sums := try! read(path(f.temporary.root, "SHA256SUMS"))
  try! write(path(f.temporary.root, "SHA256SUMS"), sums + sums)
  invoke(f)
  payload(f, "1.2.4")
  invoke(f)
  payload(f)
  try! erase(path(f.artifacts, "doof_runtime.hpp")); archive(f)
  invoke(f)
  f.temporary.close()
}
export function testRepositoryDownloadRejectsLinksAndTraversal(): none {
  f := fixture()
  try! command("ln", ["-s", "/tmp", path(f.artifacts, "escape")])
  archive(f); invoke(f)
  try! erase(path(f.artifacts, "escape"))
  archive(f)
  try! write(path(f.temporary.root, "escaped"), "bad")
  try! command("zip", ["-q", f.archive, "../escaped"], {}, f.artifacts)
  checksum(f); invoke(f)
  f.temporary.close()
}
export function testRepositoryInstallationRollsBackActivationFailure(): none {
  f := fixture()
  helperArgs := ["-c", "DOOF_INSTALL_LIBRARY_ONLY=1; . \"$1\"; install_artifacts \"$2\" \"$3\" dev", "sh", path(f.repo, "install.sh"), f.artifacts, f.home]
  try! command("sh", helperArgs)
  try! write(path(f.home, "versions/1.0.0/marker"), "released")
  try! write(path(f.home, "packages/marker"), "cached")
  try! write(path(f.artifacts, "doof_runtime.hpp"), "replacement")
  bin := path(f.temporary.root, "failing-bin")
  try! write(path(bin, "ln"), "#!/bin/sh\nexit 77\n")
  try! command("chmod", ["+x", path(bin, "ln")])
  result := try! execute("sh", helperArgs, { PATH: bin + ":" + setting("PATH") })
  Assert.isTrue(result.exitCode != 0)
  Assert.equal(try! read(path(f.home, "versions/dev/doof_runtime.hpp")), "fixture")
  Assert.equal(try! capture("readlink", [path(f.home, "current")]), "versions/dev")
  Assert.equal(try! read(path(f.home, "versions/1.0.0/marker")), "released")
  Assert.equal(try! read(path(f.home, "packages/marker")), "cached")
  try! command("sh", helperArgs)
  Assert.equal(try! read(path(f.home, "versions/dev/doof_runtime.hpp")), "replacement")
  f.temporary.close()
}

export function testRepositoryInstallationRestoresCurrentAfterFailedSmoke(): none {
  f := fixture()
  helper := ["-c", "DOOF_INSTALL_LIBRARY_ONLY=1; . \"$1\"; install_artifacts \"$2\" \"$3\" \"$4\"", "sh", path(f.repo, "install.sh"), f.artifacts, f.home, "1.2.3"]
  try! command("sh", helper)
  try! write(path(f.artifacts, "doof"), "#!/bin/sh\ncase \"$0\" in */bin/doof) exit 76 ;; *) exit 0 ;; esac\n")
  helper[helper.length - 1] = "1.2.4"
  failed := try! execute("sh", helper)
  Assert.isTrue(failed.exitCode != 0)
  Assert.equal(try! capture("readlink", [path(f.home, "current")]), "versions/1.2.3")
  Assert.isFalse(exists(path(f.home, "versions/1.2.4")))
  Assert.equal(try! capture(path(f.home, "bin/doof"), ["--version"]), "doof 1.2.3")
  f.temporary.close()
}
export function testRepositoryInstalledCompilerResourceLinks(): none {
  root := setting("DOOF_REPOSITORY_TEST_ROOT"); compiler := setting("DOOF_REPOSITORY_TEST_COMPILER")
  if root == "" || compiler == "" { return }
  temp := try! TemporaryDirectory()
  home := path(temp.root, "home")
  helper := ["-c", "DOOF_INSTALL_LIBRARY_ONLY=1; . \"$1\"; install_artifacts \"$2\" \"$3\" dev", "sh", path(root, "install.sh"), path(root, "dist"), home]
  try! command("sh", helper)
  for name of ["doof", "doof_runtime.hpp", "doof_observer.hpp", "doof_observer_platform.hpp", "doof_wasm_test_runner_apple.swift", "doof-stdlib.tar", "observer-ui", "Doof Debugger.app"] {
    Assert.equal(try! capture("readlink", [path(home, "bin/" + name)]), "../current/" + name)
  }
  try! command("env", ["-u", "DOOF_STDLIB_ROOT", "-u", "DOOF_RUNTIME_HEADER", path(home, "bin/doof"), "emit", path(root, "tests/release-fixtures/runtime"), "-o", path(temp.root, "emitted")], {}, temp.root)
  Assert.equal(try! read(path(root, "dist/doof_runtime.hpp")), try! read(path(temp.root, "emitted/doof_runtime.hpp")))
  temp.close()
}
