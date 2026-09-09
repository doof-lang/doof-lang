import { sha256Hex } from "std/crypto"
import { exists, File, readBlob } from "std/fs"
import { formatJsonValue, parseJsonObject } from "std/json"
import { architecture, platform, Exec, ExecOptions } from "std/os"
import { basename, dirname } from "std/path"
import { Duration, Thread } from "std/time"
import { buildToolchain, prepare } from "./build"
import { capture, cleanRevision, command, copyTree, erase, execute, files, jsonFile, jsonString, makeDirectory, path, read, require, resolveSeed, setting, stableVersion, stdlibDirectory, write } from "./common"
import { createSnapshot, isMachO } from "./snapshot"
import { debuggerChecks, releaseVerification, testRepository } from "./verify"
import { stdlibRevisions } from "./provenance"

export function signingPreflight(identity: string, profile: string): Result<none, string> {
  try require(platform() == "darwin" && architecture() == "arm64", "Releases require macOS arm64")
  try require(identity != "", "DOOF_SIGN_IDENTITY is required for signed releases")
  try require(profile != "", "DOOF_NOTARY_PROFILE is required for signed releases")
  for tool of ["em++", "xcrun", "codesign", "ditto", "rsync", "curl"] { try capture("sh", ["-c", "command -v \"$1\"", "sh", tool]) }
  try identities := capture("security", ["find-identity", "-v", "-p", "codesigning"])
  let matches = 0
  for line of identities.split("\n") { if line.contains(identity) && line.contains("Developer ID Application:") { matches += 1 } }
  try require(matches == 1, "DOOF_SIGN_IDENTITY must select exactly one valid Developer ID Application certificate")
  for tool of ["swiftc", "clang++", "notarytool", "stapler"] { try capture("xcrun", ["--find", tool]) }
  // Query profile validity without reading or printing stored credentials.
  try capture("xcrun", ["notarytool", "history", "--keychain-profile", profile, "--output-format", "json"])
  return Success()
}
export function validateReleaseStatus(status: string): Result<none, string> {
  return require(status == "404", "Release already exists or could not be checked (HTTP " + status + "); published versions are immutable")
}
function rejectExistingRelease(version: string): Result<none, string> {
  try status := capture("curl", ["--proto", "=https", "--proto-redir", "=https", "-sSL", "-o", "/dev/null", "-w", "%{http_code}", "https://github.com/doof-lang/doof-lang/releases/tag/v" + version])
  return validateReleaseStatus(status)
}
function zipArtifacts(artifacts: string, archive: string): Result<none, string> {
  try erase(archive)
  return command("ditto", ["-c", "-k", "--norsrc", artifacts, archive])
}
export function smokeToolchain(artifacts: string, work: string, version: string): Result<none, string> {
  compiler := path(artifacts, "doof")
  try actual := capture(compiler, ["--version"])
  try require(actual == "doof " + version, "Relocated compiler version mismatch")
  try makeDirectory(work)
  try write(path(work, "doof.json"), "{\"name\":\"doof-release-smoke\",\"build\":{\"entry\":\"smoke.do\"}}\n")
  sample := path(work, "smoke.do")
  try write(sample, "import { parseJsonValue } from \"std/json\"\nfunction main(): int { value := try! parseJsonValue(\"{}\")\nreturn 0 }\n")
  return command("env", ["-u", "DOOF_STDLIB_ROOT", "-u", "DOOF_RUNTIME_HEADER", "-u", "CXX", compiler, "run", sample, "-o", path(work, "output")], {}, work)
}
export function smokeDebuggerApplication(artifacts: string): Result<none, string> {
  // Exercise the distributed app's hardened-runtime startup, not a test binary.
  try application := Exec.spawn(path(artifacts, "Doof Debugger.app/Contents/MacOS/DoofDebugger"), [], ExecOptions { withStdin: false })
  Thread.sleep(Duration.ofSeconds(2L))
  running := application.isRunning()
  if running { try application.terminate(15) }
  try application.wait()
  return require(running, "Distributed debugger exited during application startup")
}
export function signAndNotarize(artifacts: string, work: string, archive: string, identity: string, profile: string): Result<string, string> {
  app := path(artifacts, "Doof Debugger.app")
  try names := files(artifacts)
  for name of names {
    file := path(artifacts, name)
    try native := isMachO(file)
    if native { try command("codesign", ["--force", "--sign", identity, "--options", "runtime", "--timestamp", file]) }
  }
  entitlements := path(work, "debugger-entitlements.plist")
  try write(entitlements, "<?xml version=\"1.0\"?><plist version=\"1.0\"><dict><key>com.apple.security.cs.debugger</key><true/></dict></plist>\n")
  try command("codesign", ["--force", "--sign", identity, "--options", "runtime", "--timestamp", "--entitlements", entitlements, app])
  for file of [path(artifacts, "doof"), app] { try command("codesign", ["--verify", "--deep", "--strict", file]) }
  try zipArtifacts(artifacts, archive)
  try response := capture("xcrun", ["notarytool", "submit", archive, "--keychain-profile", profile, "--wait", "--output-format", "json"])
  try write(path(work, "notarization.json"), response)
  try result := parseJsonObject(response)
  try status := jsonString(result, "status")
  try require(status == "Accepted", "Notarization failed; see " + path(work, "notarization.json"))
  try command("xcrun", ["stapler", "staple", app])
  try command("xcrun", ["stapler", "validate", app])
  try zipArtifacts(artifacts, archive)
  return jsonString(result, "id")
}
export function prepareRelease(root: string, version: string): Result<none, string> {
  try require(stableVersion(version), "Release version must be stable MAJOR.MINOR.PATCH without a v prefix")
  try makeDirectory(path(root, "build"))
  lock := File { path: path(root, "build/toolchain.lock"), mode: .ReadWrite, create: true, lock: .Exclusive, waitForLock: false } else { return Failure("Another toolchain operation is running or build lock is inaccessible") }
  try liveStdlib := stdlibDirectory(root)
  try compilerRevision := cleanRevision(root)
  try stdlibRevision := stdlibRevisions(liveStdlib)
  final := path(root, "dist/releases/" + version)
  try require(!exists(final), "Release assets already exist: " + final + "; use a new version for changed contents")
  identity := setting("DOOF_SIGN_IDENTITY"); profile := setting("DOOF_NOTARY_PROFILE")
  try signingPreflight(identity, profile)
  try rejectExistingRelease(version)
  try seed := resolveSeed(root, "DOOF_SEED_COMPILER")
  try seedVersion := capture(seed, ["--version"])
  seedBytes := readBlob(seed) else { return Failure("Cannot fingerprint the release seed") }
  seedSha256 := sha256Hex(seedBytes)
  work := path(root, "build/releases/" + version)
  try erase(work)
  try inputs := prepare(root, work, seed, version)
  try currentCompiler := cleanRevision(root); try currentStdlib := stdlibRevisions(liveStdlib)
  try require(currentCompiler == compilerRevision && formatJsonValue(currentStdlib) == formatJsonValue(stdlibRevision), "Release inputs changed during staging")
  try built := buildToolchain(inputs, true, true)
  try copyTree(built.artifacts, path(inputs.source, "dist"))
  try testRepository(inputs.source, path(built.artifacts, "doof"), inputs.stdlib)
  try releaseVerification(inputs.source, path(built.artifacts, "doof"), inputs.stdlib)
  pending := path(work, "pending")
  try makeDirectory(pending)
  snapshot := path(work, "doof-" + version + "-source")
  try createSnapshot(work, inputs.source, built.artifacts, snapshot, version)
  sourceArchive := path(pending, "doof-" + version + "-source.tar.gz")
  try command("tar", ["-czf", sourceArchive, "-C", work, basename(snapshot)])
  // A different path with spaces catches absolute paths and shell quoting errors.
  extracted := path(work, "source verification")
  try makeDirectory(extracted)
  try command("tar", ["-xzf", sourceArchive, "-C", extracted])
  rebuilt := path(extracted, basename(snapshot))
  try command("env", ["-u", "DOOF_STDLIB_ROOT", "-u", "DOOF_RUNTIME_HEADER", "-u", "CXX", path(rebuilt, "build.sh")])
  try smokeToolchain(path(rebuilt, "dist"), path(extracted, "smoke"), version)
  binaryArchive := path(pending, "doof-" + version + "-macos-arm64.zip")
  try submission := signAndNotarize(built.artifacts, work, binaryArchive, identity, profile)
  relocated := path(work, "downloaded toolchain")
  try command("ditto", ["-x", "-k", binaryArchive, relocated])
  try command("xattr", ["-r", "-w", "com.apple.quarantine", "0083;00000000;DoofRelease;", relocated])
  for file of [path(relocated, "doof"), path(relocated, "Doof Debugger.app")] {
    try command("codesign", ["--verify", "--deep", "--strict", file])
  }
  // spctl's application assessment rejects bare Mach-O tools as non-app-like.
  try command("codesign", ["-vvvv", "-R=notarized", "--check-notarization", path(relocated, "doof")])
  try command("spctl", ["--assess", "--type", "execute", "--verbose=2", path(relocated, "Doof Debugger.app")])
  try smokeToolchain(relocated, path(work, "signed-smoke"), version)
  try smokeDebuggerApplication(relocated)
  try debuggerChecks(inputs.source, path(relocated, "doof"), inputs.stdlib)
  try clang := capture("xcrun", ["clang++", "--version"])
  try swift := capture("xcrun", ["swiftc", "--version"])
  try emscripten := capture("em++", ["--version"])
  try sdkVersion := capture("xcrun", ["--show-sdk-version"])
  try macos := capture("sw_vers", ["-productVersion"])
  metadata: JsonObject := { version, tag: "v" + version, compilerRevision, stdlibRevisions: stdlibRevision, seedVersion, seedSha256, fixedPointGeneration: built.generation, clang, swift, emscripten, sdkVersion, macos, notarizationId: submission, verified: ["compiler-tests", "release-fixtures", "source-rebuild", "relocation", "signatures", "notarization", "quarantine-assessment", "debugger-startup", "debugger-integration"] }
  try write(path(pending, "release.json"), formatJsonValue(metadata) + "\n")
  try assets := files(pending)
  let checksums = ""
  for name of assets {
    bytes := readBlob(path(pending, name)) else { return Failure("Cannot checksum " + name) }
    checksums += sha256Hex(bytes) + "  " + name + "\n"
  }
  try write(path(pending, "SHA256SUMS"), checksums)
  try makeDirectory(dirname(final))
  try command("mv", [pending, final])
  println("Verified release assets ready: " + final)
  println("Manually publish tag v" + version + " at compiler revision " + compilerRevision + ". No GitHub changes were made.")
  _ := lock.close() else { return Failure("Could not close toolchain lock") }
  return Success()
}

// Verify the exact captured graph from build.sh without signing or publication.
export function checkSourceSnapshot(root: string): Result<none, string> {
  work := path(root, "build/toolchain-verify")
  source := path(work, "source"); artifacts := path(work, "artifacts")
  try manifest := jsonFile(path(source, "doof.json"))
  try version := jsonString(manifest, "version")
  check := path(work, "source-check")
  try erase(check); try makeDirectory(check)
  snapshot := path(check, "doof-source")
  try createSnapshot(work, source, artifacts, snapshot, version)
  archive := path(check, "source.tar.gz")
  try command("tar", ["-czf", archive, "-C", check, "doof-source"])
  extracted := path(check, "relocated source")
  try makeDirectory(extracted)
  try command("tar", ["-xzf", archive, "-C", extracted])
  try command("env", ["-u", "DOOF_STDLIB_ROOT", "-u", "DOOF_RUNTIME_HEADER", "-u", "CXX", path(extracted, "doof-source/build.sh")])
  try smokeToolchain(path(extracted, "doof-source/dist"), path(check, "smoke"), version)
  println("Standalone source snapshot rebuilt and verified: " + archive)
  return Success()
}
