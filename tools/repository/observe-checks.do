// Release-gate check of an observed Doof target and a reconnecting SSE client.
import { exists } from "std/fs"
import { Exec, ExecOptions } from "std/os"
import { Duration, Thread } from "std/time"
import { execute, makeDirectory, path, read, require, text } from "./common"

export function observedUrl(output: string): Result<string, string> {
  prefix := "DOOF_OBSERVE_URL="
  for line of output.split("\n") {
    if line.startsWith(prefix) && line.length > prefix.length {
      return Success(line.substring(prefix.length, line.length))
    }
  }
  return Failure("Observed target did not publish a session URL")
}

export function lastSseId(stream: string): Result<string, string> {
  let last = ""
  for line of stream.split("\n") {
    if line.startsWith("id: ") && line.length > 4 {
      last = line.substring(4, line.length)
    }
  }
  if last == "" { return Failure("SSE stream did not contain a retained event ID") }
  return Success(last)
}

class ObservedChild {
  readonly process: Exec
  destructor {
    if process.isRunning() { _ := process.terminate(9) else {} }
    _ := process.wait() else {}
  }
}

function awaitOutput(log: string, marker: string, process: Exec): Result<string, string> {
  for _ of 0..<1200 {
    if exists(log) {
      try content := read(log)
      if content.contains(marker) { return Success(content) }
    }
    if !process.isRunning() { break }
    Thread.sleep(Duration.ofMillis(50L))
  }
  content := read(log) else { return Failure("Observed target ended before " + marker) }
  return Failure("Timed out waiting for " + marker + ": " + content)
}

function sseWindow(url: string, lastId: string): Result<string, string> {
  try result := execute("curl", ["-sS", "-N", "--noproxy", "*", "--max-time", "1", "-H", "Last-Event-ID: " + lastId, url + "api/v1/events"])
  try require(result.exitCode == 0 || result.exitCode == 28,
    "SSE client failed with status " + string(result.exitCode) + ": " + text(result.stdout))
  return Success(text(result.stdout))
}

export function observedReconnectCheck(compiler: string, fixture: string, output: string, stdlib: string): Result<none, string> {
  try makeDirectory(output)
  log := path(output, "stream-target.log")
  args := ["-c", "log=$1; shift; exec \"$@\" >\"$log\" 2>&1", "sh", log,
    compiler, "observe", fixture, "--no-open", "--retain-events", "2", "-o", output, "--", "--stream"]
  try process := Exec.spawn("sh", args, ExecOptions {
    env: { DOOF_STDLIB_ROOT: stdlib, DOOF_OBSERVE_NO_OPEN: "1" },
    withStdin: false,
    timeout: Duration.ofSeconds(90L),
  })
  child := ObservedChild { process }
  try initialOutput := awaitOutput(log, "OBSERVE_STREAM_FIRST_READY", child.process)
  try url := observedUrl(initialOutput)
  try first := sseWindow(url, "0")
  try require(first.contains("event: hello") && first.contains("event: log"),
    "Initial SSE subscription missed greeting or structured logs: " + first)
  try cursor := lastSseId(first)
  try awaitOutput(log, "OBSERVE_STREAM_BURST_READY", child.process)
  try replay := sseWindow(url, cursor)
  try require(replay.contains("event: gap") && replay.contains("event: log") && replay.contains("stream event 7"),
    "Reconnected SSE client missed retention gap or latest log: " + replay)
  try snapshot := execute("curl", ["-fsS", "--noproxy", "*", url + "api/v1/snapshot"])
  try require(snapshot.exitCode == 0 && text(snapshot.stdout).contains("\"name\":\"requests_total\",\"value\":11") &&
    text(snapshot.stdout).contains("stream event 7"),
    "Observed snapshot did not recover the final metrics and structured log")
  try status := child.process.wait()
  return require(status == 0, "Observed streaming fixture exited with status " + string(status))
}
