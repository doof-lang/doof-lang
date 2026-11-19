import { sha256Hex } from "std/crypto"
import { join as joinStrings } from "std/string"
import { exists, File, readBlob, writeBlob } from "std/fs"
import { formatJsonValue, parseJsonObject } from "std/json"
import { architecture, platform, Exec, ExecOptions } from "std/os"
import { basename, dirname, executablePath } from "std/path"
import { Duration, MonotonicInstant, Thread } from "std/time"
import { BlobBuilder, BlobReader } from "std/blob"
import { connect, SshClient, SshConnectOptions } from "std/ssh"
import { wakeOnLan } from "std/wol"
import { buildToolchain, prepare } from "./build"
import { capture, cleanRevision, command, copyInputs, copyTree, erase, execute, files, jsonFile, jsonString, makeDirectory, path, read, require, resolveSeed, setting, stableVersion, stamp, stdlibDirectory, write } from "./common"
import { createSnapshot, isMachO } from "./snapshot"
import { debuggerChecks, releaseTests, runtimeChecks } from "./verify"
import { stdlibRevisions } from "./provenance"
import { WindowsBuildConfig, windowsBuildConfig, windowsBuildEnabled, windowsBuildLogName, windowsBuildLogTail, windowsBuildScript, windowsProjectFile, windowsReleaseArchiveName, windowsVisualStudioCommand, windowsVisualStudioScript } from "./windows-build"
import { LinuxReleaseTarget, linuxBuildScript, linuxContainerArguments, linuxContainerName, linuxMakefile, linuxProbeSources, linuxReleaseArchiveName, linuxReleaseTargets } from "./linux-build"

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
  try write(sample, "import { parseJsonValue } from \"std/json\"\nfunction main(): int { value := parseJsonValue(\"{}\")!\nreturn 0 }\n")
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

readonly CODESIGN_ATTEMPTS = 4

// Apple's timestamp server intermittently fails to answer; codesign then
// reports a missing timestamp. Only that failure is retried, with backoff.
export function codesignTimestampUnavailable(output: string): bool {
  return output.contains("A timestamp was expected but was not found") ||
    output.contains("The timestamp service is not available")
}

function timestampedCodesign(arguments: string[]): Result<none, string> {
  for attempt of 1..CODESIGN_ATTEMPTS {
    println("+ codesign " + joinStrings(arguments.cloneReadonly(), " "))
    try result := execute("codesign", arguments)
    output := BlobReader(result.stdout).readString(long(result.stdout.length)).trim()
    if output != "" { println(output) }
    if result.exitCode == 0 { return Success() }
    if !codesignTimestampUnavailable(output) || attempt == CODESIGN_ATTEMPTS {
      return Failure("codesign exited with status " + string(result.exitCode) + ": " + output)
    }
    println("codesign could not reach the timestamp service (attempt " + string(attempt) + " of " + string(CODESIGN_ATTEMPTS) + "); retrying")
    Thread.sleep(Duration.ofSeconds(long(attempt * 15)))
  }
  return Failure("codesign did not run")
}

export function signAndNotarize(artifacts: string, work: string, archive: string, identity: string, profile: string): Result<string, string> {
  app := path(artifacts, "Doof Debugger.app")
  try names := files(artifacts)
  for name of names {
    file := path(artifacts, name)
    try native := isMachO(file)
    if native { try timestampedCodesign(["--force", "--sign", identity, "--options", "runtime", "--timestamp", file]) }
  }
  entitlements := path(work, "debugger-entitlements.plist")
  try write(entitlements, "<?xml version=\"1.0\"?><plist version=\"1.0\"><dict><key>com.apple.security.cs.debugger</key><true/></dict></plist>\n")
  try timestampedCodesign(["--force", "--sign", identity, "--options", "runtime", "--timestamp", "--entitlements", entitlements, app])
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

function linuxEmittedProbeSources(stdlib: string, emittedFiles: string[]): Result<string[], string> {
  let checked: string[] = []
  let result: string[] = []
  for name of emittedFiles {
    parts := name.split("/")
    if parts.length < 3 || parts[0] != "std" || checked.contains(parts[1]) { continue }
    checked.push(parts[1])
    manifest := path(stdlib, parts[1] + "/doof.json")
    if !exists(manifest) { continue }
    try parsed := jsonFile(manifest)
    for probe of linuxProbeSources("std/" + parts[1], parsed) { result.push(probe) }
  }
  return Success(result)
}

/** A release stage running in its own process, logging to its own file. */
class BackgroundStage {
  readonly label: string
  readonly log: string
  // A named Apple container to stop with the stage; empty for local processes.
  readonly container: string
  started: MonotonicInstant
  process: Exec
}

export function formatElapsed(seconds: long): string {
  if seconds < 60L { return `${seconds}s` }
  remainder := seconds % 60L
  padding := if remainder < 10L then "0" else ""
  return `${seconds \ 60L}m${padding}${remainder}s`
}

function elapsedSince(started: MonotonicInstant): string =>
  formatElapsed(MonotonicInstant.now().durationSince(started).toMillis() \ 1000L)

function startStage(label: string, log: string, program: string, arguments: string[], container: string = ""): Result<BackgroundStage, string> {
  try makeDirectory(dirname(log))
  shellArguments: string[] := ["-c", "exec \"$0\" \"$@\" > \"$DOOF_STAGE_LOG\" 2>&1", program]
  for argument of arguments { shellArguments.push(argument) }
  try process := Exec.spawn("sh", shellArguments, ExecOptions { env: { DOOF_STAGE_LOG: log }, withStdin: false })
  println(`Started ${label}; log: ${log}`)
  return Success(BackgroundStage { label, log, container, started: MonotonicInstant.now(), process })
}

function finishStage(stage: BackgroundStage): Result<none, string> {
  status := stage.process.wait() else error { return Failure(`Could not wait for ${stage.label}: ${error}`) }
  if status != 0 {
    log := read(stage.log) else { return Failure(`${stage.label} exited with status ${status}`) }
    return Failure(`${stage.label} exited with status ${status}; last lines of ${stage.log}:\n${windowsBuildLogTail(log, 60)}`)
  }
  println(`Finished ${stage.label} in ${elapsedSince(stage.started)}`)
  return Success()
}

function stopStages(stages: BackgroundStage[]): none {
  for stage of stages {
    if stage.process.isRunning() {
      println(`Stopping ${stage.label}`)
      // The container keeps running if only its client is signalled.
      if stage.container != "" { _ := execute("container", ["stop", stage.container]) else {} }
      if stage.process.isRunning() { _ := stage.process.terminate() else {} }
      _ := stage.process.wait() else {}
    }
  }
}

// Waits for every stage, reporting each as it finishes. The first failure
// stops the others, so a broken stage never waits behind a slow one.
function awaitStages(stages: BackgroundStage[]): Result<none, string> {
  let pending: BackgroundStage[] = []
  for stage of stages { pending.push(stage) }
  while pending.length > 0 {
    let running: BackgroundStage[] = []
    for stage of pending {
      if stage.process.isRunning() { running.push(stage); continue }
      _ := finishStage(stage) else error {
        stopStages(stages)
        return Failure(error)
      }
    }
    pending = running
    if pending.length > 0 { Thread.sleep(Duration.ofSeconds(1L)) }
  }
  return Success()
}

// Stages the target's inputs, then starts its container without waiting; the
// container needs only files under work, so builds for other targets and the
// rest of the release can proceed meanwhile.
function startLinuxReleaseBuild(compiler: string, source: string, stdlib: string, stdlibBundle: string, work: string, version: string, target: LinuxReleaseTarget): Result<BackgroundStage, string> {
  try stageLinuxReleaseInputs(compiler, source, stdlib, stdlibBundle, work, target)
  image := setting("DOOF_LINUX_CONTAINER_IMAGE", "docker.io/library/alpine:3.22.1")
  cpus := setting("DOOF_LINUX_CONTAINER_CPUS", "8")
  memory := setting("DOOF_LINUX_CONTAINER_MEMORY", "8G")
  jobs := setting("DOOF_LINUX_BUILD_JOBS", cpus)
  log := path(work, "linux-" + target.name + "/container.log")
  arguments := linuxContainerArguments(work, image, version, target, cpus, memory, jobs)
  return startStage(`Linux ${target.name} musl container build`, log, "container", arguments, linuxContainerName(version, target))
}

function startLinuxReleaseBuilds(compiler: string, source: string, stdlib: string, stdlibBundle: string, work: string, version: string, stages: BackgroundStage[]): Result<none, string> {
  for target of linuxReleaseTargets() {
    started := startLinuxReleaseBuild(compiler, source, stdlib, stdlibBundle, work, version, target) else error {
      stopStages(stages)
      return Failure(error)
    }
    stages.push(started)
  }
  return Success()
}

function verifyLinuxReleaseArchives(pending: string, version: string): Result<none, string> {
  for target of linuxReleaseTargets() {
    archive := path(pending, linuxReleaseArchiveName(version, target))
    try require(exists(archive), `Linux ${target.name} container did not produce release archive`)
    println(`Verified Linux ${target.name} musl release asset: ${archive}`)
  }
  return Success()
}

function stageLinuxReleaseInputs(compiler: string, source: string, stdlib: string, stdlibBundle: string, work: string, target: LinuxReleaseTarget): Result<none, string> {
  linux := path(work, "linux-" + target.name)
  emitted := path(linux, "emitted")
  resources := path(linux, "resources")
  try erase(linux); try makeDirectory(resources)
  try emitLinuxInputs(compiler, source, stdlib, emitted)
  try emittedFiles := files(emitted)
  try probes := linuxEmittedProbeSources(stdlib, emittedFiles)
  try write(path(linux, "Makefile"), linuxMakefile(emittedFiles, probes))
  try write(path(linux, "build.sh"), linuxBuildScript(target))
  try command("chmod", ["+x", path(linux, "build.sh")])
  for name of ["doof_runtime.hpp", "doof_observer.hpp", "doof_observer_platform.hpp", "doof_wasm_test_runner_apple.swift"] {
    try command("cp", [path(source, "runtime/" + name), path(resources, name)])
  }
  try copyTree(path(source, "observer-ui"), path(resources, "observer-ui"))
  try command("cp", [stdlibBundle, path(resources, "doof-stdlib.tar")])
  return Success()
}

readonly WINDOWS_BUILD_TIMEOUT_MS = 1800000

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
  started := MonotonicInstant.now()
  if config.mac != none && config.broadcast != none {
    windowsProgress(started, "Sending wake-on-LAN to " + config.mac!)
    try wakeOnLan(config.mac!, config.broadcast!)
  }
  windowsProgress(started, "Connecting to " + config.host)
  try client := connectWindowsHost(config)
  remoteRoot := "doof-release-" + version
  windowsProgress(started, "Resetting %USERPROFILE%\\" + remoteRoot)
  _ := client.run("powershell.exe -NoProfile -NonInteractive -Command \"$root = Join-Path $env:USERPROFILE 'doof-release-" + version + "'; Remove-Item -LiteralPath $root -Recurse -Force -ErrorAction SilentlyContinue; New-Item -ItemType Directory -Force -Path $root | Out-Null\"")!
  try sftp := client.sftp()
  emittedBytes := readBlob(emittedArchive) else { return Failure("Cannot read emitted Windows archive") }
  bundleBytes := readBlob(stdlibBundle) else { return Failure("Cannot read Windows stdlib bundle") }
  projectBytes := readBlob(projectPath) else { return Failure("Cannot read Windows project") }
  scriptBuilder := BlobBuilder(); scriptBuilder.writeString(windowsBuildScript(version))
  commandBuilder := BlobBuilder(); commandBuilder.writeString(windowsVisualStudioScript(version))
  uploads: Map<string, readonly byte[]> := {
    "emitted.zip": emittedBytes, "doof-stdlib.tar": bundleBytes, "doof.vcxproj": projectBytes,
    "build.ps1": scriptBuilder.build(), "build.cmd": commandBuilder.build(),
  }
  for name, bytes of uploads {
    windowsProgress(started, "Uploading " + name + " (" + string(bytes.length) + " bytes)")
    try sftp.writeFile(remoteRoot + "/" + name, bytes)
  }
  sftp.close()
  windowsProgress(started, "Running the MSVC build; inspect it with ./tools/run.sh windows-log " + version)
  result := client.run(windowsVisualStudioCommand(version), WINDOWS_BUILD_TIMEOUT_MS) else error {
    client.close()
    return Failure("Windows build did not finish: " + error + windowsLogSection(config, version))
  }
  if result.exitStatus != 0 {
    client.close()
    return Failure("Windows build failed with exit status " + string(result.exitStatus) + windowsLogSection(config, version))
  }
  windowsProgress(started, "Downloading " + windowsReleaseArchiveName(version))
  try downloaded := sftpRead(client, remoteRoot + "/" + windowsReleaseArchiveName(version))
  client.close()
  archive := path(pending, windowsReleaseArchiveName(version))
  _ := writeBlob(archive, downloaded) else { return Failure("Cannot write Windows release archive") }
  try erase(emittedArchive)
  windowsProgress(started, "Verified Windows release asset: " + archive)
  return Success()
}

function windowsProgress(started: MonotonicInstant, message: string): none {
  seconds := MonotonicInstant.now().durationSince(started).toMillis() \ 1000L
  println("[windows +" + string(seconds) + "s] " + message)
}

function connectWindowsHost(config: WindowsBuildConfig): Result<SshClient, string> {
  return connect(SshConnectOptions {
    host: config.host,
    username: config.username,
    password: config.password,
    knownHostsPath: config.knownHostsPath,
    wait: Duration.ofSeconds(60L),
    timeoutMs: 30000,
  })
}

function readWindowsBuildLog(config: WindowsBuildConfig, version: string): Result<string, string> {
  try client := connectWindowsHost(config)
  bytes := sftpRead(client, "doof-release-" + version + "/" + windowsBuildLogName) else error {
    client.close()
    return Failure(error)
  }
  client.close()
  return Success(BlobReader(bytes).readString(long(bytes.length)))
}

// A fresh connection reads the transcript, since the build's session may be
// the one that stopped responding.
function windowsLogSection(config: WindowsBuildConfig, version: string): string {
  log := readWindowsBuildLog(config, version) else error {
    return "\n(could not read the remote " + windowsBuildLogName + ": " + error + ")"
  }
  return "\nLast lines of the remote " + windowsBuildLogName + ":\n" + windowsBuildLogTail(log, 60)
}

/** Prints the remote build transcript, including while a build is still running. */
export function windowsBuildLog(version: string): Result<none, string> {
  try require(windowsBuildEnabled(), "DOOF_WINDOWS_HOST is not set")
  try config := windowsBuildConfig()
  try log := readWindowsBuildLog(config, version)
  println(log)
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
  let stages: BackgroundStage[] = []
  try startLinuxReleaseBuilds(compiler, source, stdlib, bundle, work, version, stages)
  try awaitStages(stages)
  return verifyLinuxReleaseArchives(pending, version)
}

/** The parallel release stages that run in their own repository-tool processes. */
export function releaseStageNames(windows: bool): string[] {
  names := ["tests", "runtime", "macos"]
  if windows { names.push("windows") }
  return names
}

export function releaseStageArguments(root: string, version: string, stage: string): string[] =>
  [root, "release-stage", version, stage]

function releaseStageLabel(stage: string): string {
  case stage {
    "tests" -> { return "compiler and release tests" }
    "runtime" -> { return "native runtime checks" }
    "macos" -> { return "macOS source rebuild, signing and notarization" }
    "windows" -> { return "Windows MSVC remote build" }
    _ -> { return stage }
  }
}

/**
 * Runs one release stage inside a child process started by prepareRelease,
 * which holds the toolchain lock. Every stage reads the staged release under
 * build/releases/<version> and writes only its own paths. The tests and
 * platform builds use the copy of the toolchain in source/dist, because the
 * macos stage signs the artifacts directory in place.
 */
export function runReleaseStage(root: string, version: string, stage: string): Result<none, string> {
  try require(stableVersion(version), "Release version must be stable MAJOR.MINOR.PATCH")
  work := path(root, "build/releases/" + version)
  source := path(work, "source"); stdlib := path(work, "stdlib")
  artifacts := path(work, "artifacts"); pending := path(work, "pending")
  compiler := path(source, "dist/doof")
  try require(exists(compiler) && exists(path(artifacts, "doof")), "Release stages need a built toolchain in " + work)
  case stage {
    "tests" -> { return releaseTests(source, compiler, stdlib) }
    "runtime" -> { return runtimeChecks(source) }
    "windows" -> { return buildWindowsReleaseArtifact(compiler, source, stdlib, path(source, "dist/doof-stdlib.tar"), work, pending, version) }
    "macos" -> {
      return verifyMacRelease(source, stdlib, artifacts, work, pending, version, setting("DOOF_SIGN_IDENTITY"), setting("DOOF_NOTARY_PROFILE"))
    }
    _ -> { return Failure("Unknown release stage: " + stage) }
  }
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
  releaseStarted := MonotonicInstant.now()
  try built := buildToolchain(inputs, true, true)
  println(`Built fixed-point toolchain in ${elapsedSince(releaseStarted)}`)
  try copyTree(built.artifacts, path(inputs.source, "dist"))
  pending := path(work, "pending")
  try makeDirectory(pending)
  // Every remaining stage only reads the finished toolchain and writes its own
  // directories, so all of them run at once: the Linux containers, the test
  // gates, the Windows remote build, and the macOS source rebuild, signing
  // and notarization. Platform builds emit with the source/dist copy because
  // the macos stage signs the artifacts directory in place.
  compiler := path(inputs.source, "dist/doof")
  let stages: BackgroundStage[] = []
  try startLinuxReleaseBuilds(compiler, inputs.source, inputs.stdlib, path(inputs.source, "dist/doof-stdlib.tar"), work, version, stages)
  tool := executablePath() else error {
    stopStages(stages)
    return Failure("Cannot locate the repository tool to start release stages: " + error)
  }
  for stage of releaseStageNames(windowsBuildEnabled()) {
    started := startStage(releaseStageLabel(stage), path(work, "logs/" + stage + ".log"), tool, releaseStageArguments(root, version, stage)) else error {
      stopStages(stages)
      return Failure(error)
    }
    stages.push(started)
  }
  try awaitStages(stages)
  try verifyLinuxReleaseArchives(pending, version)
  if windowsBuildEnabled() { try require(exists(path(pending, windowsReleaseArchiveName(version))), "Windows stage did not produce its release archive") }
  try notarization := jsonFile(path(work, "notarization.json"))
  try submission := jsonString(notarization, "id")
  println(`All release stages finished in ${elapsedSince(releaseStarted)}`)
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

// The macos release stage: the relocated source rebuild, signing,
// notarization, and the signed-toolchain checks. The snapshot is taken before
// signing modifies the artifacts. signAndNotarize records the submission in
// work/notarization.json for the release metadata.
function verifyMacRelease(source: string, stdlib: string, artifacts: string, work: string, pending: string, version: string, identity: string, profile: string): Result<none, string> {
  snapshot := path(work, "doof-" + version + "-source")
  try createSnapshot(work, source, artifacts, snapshot, version)
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
  try submission := signAndNotarize(artifacts, work, binaryArchive, identity, profile)
  println("Notarization accepted: " + submission)
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
  try debuggerChecks(source, path(relocated, "doof"), stdlib, path(work, "signed-debugger-integration"))
  return Success()
}
