import { sha256Hex } from "std/crypto"
import { exists, File, readBlob, writeBlob } from "std/fs"
import { formatJsonValue, parseJsonObject } from "std/json"
import { architecture, platform, Exec, ExecOptions } from "std/os"
import { basename, dirname } from "std/path"
import { Duration, Thread } from "std/time"
import { BlobBuilder } from "std/blob"
import { connect, SshClient, SshConnectOptions } from "std/ssh"
import { wakeOnLan } from "std/wol"
import { buildToolchain, prepare } from "./build"
import { capture, cleanRevision, command, copyInputs, copyTree, erase, execute, files, jsonFile, jsonString, makeDirectory, path, read, require, resolveSeed, setting, stableVersion, stamp, stdlibDirectory, write } from "./common"
import { createSnapshot, isMachO } from "./snapshot"
import { debuggerChecks, releaseVerification, testRepository } from "./verify"
import { stdlibRevisions } from "./provenance"
import { windowsBuildConfig, windowsBuildEnabled, windowsBuildScript, windowsProjectFile, windowsReleaseArchiveName, windowsVisualStudioCommand, windowsVisualStudioScript } from "./windows-build"
import { LinuxReleaseTarget, linuxBuildScript, linuxContainerArguments, linuxMakefile, linuxReleaseArchiveName, linuxReleaseTargets } from "./linux-build"

export function signingPreflight(identity: string, profile: string): Result<none, string> {
  try require(platform() == "darwin" && architecture() == "arm64", "Releases require macOS arm64")
  try require(identity != "", "DOOF_SIGN_IDENTITY is required for signed releases")
  try require(profile != "", "DOOF_NOTARY_PROFILE is required for signed releases")
  for tool of ["em++", "xcrun", "codesign", "ditto", "rsync", "curl", "container"] { try capture("sh", ["-c", "command -v \"$1\"", "sh", tool]) }
  try capture("container", ["system", "status"])
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

function emitWindowsInputs(compiler: string, source: string, stdlib: string, emitted: string): Result<none, string> {
  environment: Map<string, string> := {
    DOOF_STDLIB_ROOT: stdlib,
    DOOF_RUNTIME_HEADER: path(source, "runtime/doof_runtime.hpp"),
  }
  return command(compiler, ["emit", source, "--native-platform", "windows", "-o", emitted], environment)
}

function emitLinuxInputs(compiler: string, source: string, stdlib: string, emitted: string): Result<none, string> {
  environment: Map<string, string> := {
    DOOF_STDLIB_ROOT: stdlib,
    DOOF_RUNTIME_HEADER: path(source, "runtime/doof_runtime.hpp"),
  }
  return command(compiler, ["emit", source, "--native-platform", "linux", "-o", emitted], environment)
}

function buildLinuxReleaseArtifact(compiler: string, source: string, stdlib: string, stdlibBundle: string, work: string, pending: string, version: string, target: LinuxReleaseTarget): Result<none, string> {
  linux := path(work, "linux-" + target.name)
  emitted := path(linux, "emitted")
  resources := path(linux, "resources")
  try erase(linux); try makeDirectory(resources)
  try emitLinuxInputs(compiler, source, stdlib, emitted)
  try emittedFiles := files(emitted)
  try write(path(linux, "Makefile"), linuxMakefile(emittedFiles))
  try write(path(linux, "build.sh"), linuxBuildScript(target))
  try command("chmod", ["+x", path(linux, "build.sh")])
  for name of ["doof_runtime.hpp", "doof_observer.hpp", "doof_observer_platform.hpp", "doof_wasm_test_runner_apple.swift"] {
    try command("cp", [path(source, "runtime/" + name), path(resources, name)])
  }
  try copyTree(path(source, "observer-ui"), path(resources, "observer-ui"))
  try command("cp", [stdlibBundle, path(resources, "doof-stdlib.tar")])
  image := setting("DOOF_LINUX_CONTAINER_IMAGE", "docker.io/library/alpine:3.22.1")
  cpus := setting("DOOF_LINUX_CONTAINER_CPUS", "8")
  memory := setting("DOOF_LINUX_CONTAINER_MEMORY", "8G")
  jobs := setting("DOOF_LINUX_BUILD_JOBS", "4")
  try command("container", linuxContainerArguments(work, image, version, target, cpus, memory, jobs))
  archive := path(pending, linuxReleaseArchiveName(version, target))
  try require(exists(archive), "Linux container did not produce release archive")
  println("Verified Linux " + target.name + " musl release asset: " + archive)
  return Success()
}

function buildWindowsReleaseArtifact(compiler: string, source: string, stdlib: string, stdlibBundle: string, work: string, pending: string, version: string): Result<none, string> {
  try config := windowsBuildConfig()
  emitted := path(work, "windows-emitted")
  emittedArchive := path(work, "windows-emitted.zip")
  try erase(emitted)
  try emitWindowsInputs(compiler, source, stdlib, emitted)
  for name of ["doof_observer.hpp", "doof_observer_platform.hpp", "doof_wasm_test_runner_apple.swift"] {
    try command("cp", [path(source, "runtime/" + name), path(emitted, name)])
  }
  try copyTree(path(source, "observer-ui"), path(emitted, "observer-ui"))
  try command("ditto", ["-c", "-k", "--norsrc", emitted, emittedArchive])
  try emittedFiles := files(emitted)
  projectPath := path(work, "doof.vcxproj")
  try write(projectPath, windowsProjectFile(emittedFiles))
  if config.mac != none && config.broadcast != none {
    try wakeOnLan(config.mac!, config.broadcast!)
  }
  try client := connect(SshConnectOptions {
    host: config.host,
    username: config.username,
    password: config.password,
    knownHostsPath: config.knownHostsPath,
    wait: Duration.ofSeconds(60L),
    timeoutMs: 30000,
  })
  remoteRoot := "doof-release-" + version
  _ := try! client.run("powershell.exe -NoProfile -NonInteractive -Command \"$root = Join-Path $env:USERPROFILE 'doof-release-" + version + "'; Remove-Item -LiteralPath $root -Recurse -Force -ErrorAction SilentlyContinue; New-Item -ItemType Directory -Force -Path $root | Out-Null\"")
  try sftp := client.sftp()
  emittedBytes := readBlob(emittedArchive) else { return Failure("Cannot read emitted Windows archive") }
  bundleBytes := readBlob(stdlibBundle) else { return Failure("Cannot read Windows stdlib bundle") }
  projectBytes := readBlob(projectPath) else { return Failure("Cannot read Windows project") }
  try sftp.writeFile(remoteRoot + "/emitted.zip", emittedBytes)
  try sftp.writeFile(remoteRoot + "/doof-stdlib.tar", bundleBytes)
  try sftp.writeFile(remoteRoot + "/doof.vcxproj", projectBytes)
  scriptBuilder := BlobBuilder(); scriptBuilder.writeString(windowsBuildScript(version))
  try sftp.writeFile(remoteRoot + "/build.ps1", scriptBuilder.build())
  commandBuilder := BlobBuilder(); commandBuilder.writeString(windowsVisualStudioScript(version))
  try sftp.writeFile(remoteRoot + "/build.cmd", commandBuilder.build())
  sftp.close()
  try result := client.run(windowsVisualStudioCommand(version), 1800000)
  if result.exitStatus != 0 {
    client.close()
    return Failure("Windows build failed: " + result.stderr + result.stdout)
  }
  try downloaded := sftpRead(client, remoteRoot + "/" + windowsReleaseArchiveName(version))
  client.close()
  archive := path(pending, windowsReleaseArchiveName(version))
  _ := writeBlob(archive, downloaded) else { return Failure("Cannot write Windows release archive") }
  try erase(emittedArchive)
  println("Verified Windows release asset: " + archive)
  return Success()
}

function sftpRead(client: SshClient, remotePath: string): Result<readonly byte[], string> {
  try sftp := client.sftp()
  try bytes := sftp.readFile(remotePath)
  sftp.close()
  return Success(bytes)
}

/** Runs the remote Windows release workflow without signing or publishing. */
export function windowsEndToEnd(root: string, version: string): Result<none, string> {
  try require(stableVersion(version), "Windows test version must be stable MAJOR.MINOR.PATCH")
  work := path(root, "build/windows-e2e/" + version)
  source := path(work, "source")
  pending := path(work, "artifacts")
  try erase(work)
  try makeDirectory(work)
  try stamp(root, source, version)
  try liveStdlib := stdlibDirectory(root)
  stdlib := path(work, "stdlib")
  try copyInputs(liveStdlib, stdlib)
  try makeDirectory(pending)
  try compiler := resolveSeed(root, "DOOF_DEV_COMPILER")
  bundle := path(work, "doof-stdlib.tar")
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib, DOOF_RUNTIME_HEADER: path(source, "runtime/doof_runtime.hpp") }
  try command(compiler, ["run", path(source, "tools/stdlib-bundle.do"), "-o", path(work, "stdlib-bundle-tool"), "--", stdlib, bundle, "windows"], environment)
  return buildWindowsReleaseArtifact(compiler, source, stdlib, bundle, work, pending, version)
}

/** Runs the local Apple Container Linux workflow without signing or publishing. */
export function linuxEndToEnd(root: string, version: string): Result<none, string> {
  try require(stableVersion(version), "Linux test version must be stable MAJOR.MINOR.PATCH")
  work := path(root, "build/linux-e2e/" + version)
  source := path(work, "source")
  pending := path(work, "pending")
  try erase(work)
  try makeDirectory(work)
  try stamp(root, source, version)
  try liveStdlib := stdlibDirectory(root)
  stdlib := path(work, "stdlib")
  try copyInputs(liveStdlib, stdlib)
  try makeDirectory(pending)
  try compiler := resolveSeed(root, "DOOF_DEV_COMPILER")
  bundle := path(work, "doof-stdlib.tar")
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib, DOOF_RUNTIME_HEADER: path(source, "runtime/doof_runtime.hpp") }
  try command(compiler, ["run", path(source, "tools/stdlib-bundle.do"), "-o", path(work, "stdlib-bundle-tool"), "--", stdlib, bundle, "linux"], environment)
  for target of linuxReleaseTargets() { try buildLinuxReleaseArtifact(compiler, source, stdlib, bundle, work, pending, version, target) }
  return Success()
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
  for target of linuxReleaseTargets() { try buildLinuxReleaseArtifact(path(built.artifacts, "doof"), inputs.source, inputs.stdlib, path(built.artifacts, "doof-stdlib.tar"), work, pending, version, target) }
  if windowsBuildEnabled() { try buildWindowsReleaseArtifact(path(built.artifacts, "doof"), inputs.source, inputs.stdlib, path(built.artifacts, "doof-stdlib.tar"), work, pending, version) }
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
  try containerVersion := capture("container", ["--version"])
  linuxContainerImage := setting("DOOF_LINUX_CONTAINER_IMAGE", "docker.io/library/alpine:3.22.1")
  try linuxArm64Toolchain := read(path(work, "linux-arm64/toolchain.txt"))
  try linuxX64Toolchain := read(path(work, "linux-x64/toolchain.txt"))
  linuxToolchains: SerialObject := { arm64: linuxArm64Toolchain, x64: linuxX64Toolchain }
  let verified: SerialValue[] = ["compiler-tests", "release-fixtures", "source-rebuild", "relocation", "signatures", "notarization", "quarantine-assessment", "debugger-startup", "debugger-integration", "linux-arm64-musl-container-build", "linux-x64-musl-container-build"]
  if windowsBuildEnabled() { verified.push("windows-msvc-remote-build") }
  metadata: SerialObject := { version, tag: "v" + version, compilerRevision, stdlibRevisions: stdlibRevision, seedVersion, seedSha256, fixedPointGeneration: built.generation, clang, swift, emscripten, sdkVersion, macos, containerVersion, linuxContainerImage, linuxToolchains, notarizationId: submission, verified: verified.cloneReadonly() }
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
