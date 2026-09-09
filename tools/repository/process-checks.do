// Native process regressions formerly maintained as Python/shell programs.
import { exists, File } from "std/fs"
import { Exec, ExecOptions } from "std/os"
import { Duration, Thread } from "std/time"
import { command, capture, copyTree, erase, execute, files, makeDirectory, path, quote, read, require, text, write } from "./common"

export function commandOutputChecks(compiler: string, fixtures: string, work: string, stdlib: string): Result<none, string> {
  try erase(work); try makeDirectory(work)
  fixture := path(work, "program"); tests := path(work, "tests")
  try copyTree(path(fixtures, "command-output"), fixture)
  try copyTree(path(fixtures, "test-runner"), tests)
  try erase(path(tests, "build"))
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib }
  try runOutput := capture(compiler, ["run", fixture, "-o", path(work, "run-build")], environment)
  try require(runOutput == "program-output 7", "Successful run leaked compiler output: " + runOutput)
  try cold := capture(compiler, ["build", fixture, "-o", path(work, "build")], environment)
  try require(cold.contains("Compiling "), "Cold build omitted progress")
  try warm := capture(compiler, ["build", fixture, "-o", path(work, "build")], environment)
  try require(warm == "", "Warm build unexpectedly compiled: " + warm)
  try packaged := capture(compiler, ["package", fixture, "-o", path(work, "package")], environment)
  try require(packaged.contains("Compiling "), "Package omitted progress")
  try command("cp", [path(fixture, "native-failure.hpp"), path(fixture, "native.hpp")])
  try nativeFailure := execute(compiler, ["run", fixture, "-o", path(work, "run-build")], environment)
  nativeText := text(nativeFailure.stdout)
  try require(nativeFailure.exitCode != 0 && nativeText.contains("expected native compilation failure") && !nativeText.contains("program-output 7"), "Native failure launched stale program or hid diagnostics")
  try command("cp", [path(fixtures, "command-output/native.hpp"), path(fixture, "native.hpp")])
  try command("cp", [path(fixture, "main-frontend-failure.do.txt"), path(fixture, "main.do")])
  try frontendFailure := execute(compiler, ["run", fixture, "-o", path(work, "run-build")], environment)
  try require(frontendFailure.exitCode != 0 && text(frontendFailure.stdout).contains("missingName") && !text(frontendFailure.stdout).contains("program-output should not run"), "Frontend failure launched stale program or hid diagnostics")
  try firstTests := capture(compiler, ["test", tests], environment)
  try require(firstTests.contains("Compiling "), "Cold test build omitted progress")
  try warmTests := capture(compiler, ["test", tests], environment)
  try require(!warmTests.contains("Compiling "), "Warm test build recompiled")
  try filtered := capture(compiler, ["test", tests, "--filter", "testAddsValues"], environment)
  try require(!filtered.contains("Compiling ") && filtered.contains("Testing 1 test") && filtered.contains("Tests finished: 1 passed, 0 failed"), "Filtered test output changed")
  try command("cp", [path(tests, "math.test.changed"), path(tests, "math.test.do")])
  try changed := capture(compiler, ["test", tests], environment)
  try require(changed.contains("Compiling 1 file") && changed.contains("1/1") && !changed.contains("PASS "), "Changed-test progress contract failed")
  try command("cp", [path(tests, "math.test.failure"), path(tests, "math.test.do")])
  try failed := execute(compiler, ["test", tests], environment)
  try require(failed.exitCode != 0 && text(failed.stdout).contains("failure-context") && text(failed.stdout).contains("FAIL math.test.do::testReportsFailure") && !text(failed.stdout).contains("PASS "), "Failed test omitted useful context")
  return Success()
}

// `script` supplies the operating-system PTY; Doof owns input and assertions.
export function interactiveCheck(compiler: string, fixture: string, stdlib: string): Result<none, string> {
  try process := Exec.spawn("/usr/bin/script", ["-q", "/dev/null", compiler, "run", fixture], ExecOptions { cwd: fixture, env: { DOOF_STDLIB_ROOT: stdlib }, withStdin: true, mergeStderrIntoStdout: true, timeout: Duration.ofSeconds(60L) })
  // A concurrent deadline prevents a blocked stream read from hanging the gate.
  deadline := async {
    let completed = false
    for attempt of 0..<600 {
      if !process.isRunning() { completed = true; break }
      Thread.sleep(Duration.ofMillis(100L))
    }
    if !completed { _ := process.terminate(9) else {} }
    yield completed
  }
  let output = ""; let sent = false
  for chunk of process.stdoutStream() {
    output += text(chunk)
    if !sent && output.contains("Enter value:") { try process.writeStdinText("hello\n"); sent = true }
  }
  try completed := deadline.get()
  try status := process.wait()
  try require(completed && sent && status == 0 && output.contains("received: hello"), "Interactive prompt/input failed: " + output)
  return Success()
}

class Children {
  processes: Exec[] = []
  destructor {
    for child of processes {
      if child.isRunning() { _ := child.terminate(9) else {} }
      _ := child.wait() else {}
    }
  }
}
function start(children: Children, compiler: string, arguments: string[], log: string, stdlib: string): Result<Exec, string> {
  args := ["-c", "log=$1; shift; exec \"$@\" >\"$log\" 2>&1", "sh", log, compiler]
  for argument of arguments { args.push(argument) }
  try child := Exec.spawn("sh", args, ExecOptions { env: { DOOF_STDLIB_ROOT: stdlib }, withStdin: false, timeout: Duration.ofSeconds(120L) })
  children.processes.push(child)
  return Success(child)
}
function awaitFile(file: string, marker: string = ""): Result<none, string> {
  for _ of 0..<2400 {
    if exists(file) {
      try content := read(file)
      if marker == "" || content.contains(marker) { return Success() }
    }
    Thread.sleep(Duration.ofMillis(50L))
  }
  return Failure("Timed out waiting for " + file + " " + marker)
}
function passed(child: Exec, log: string): Result<none, string> {
  try status := child.wait()
  try output := read(log)
  return require(status == 0, "Child failed: " + output)
}
export function projectLockChecks(root: string, compiler: string, stdlib: string): Result<none, string> {
  work := path(root, "build/project-lock-integration")
  try erase(work)
  project := path(work, "project")
  try makeDirectory(path(project, "build"))
  try write(path(project, "doof.json"), "{\"name\":\"lock-test\",\"build\":{\"entry\":\"main.do\"}}")
  try write(path(project, "main.do"), "function main(): none {}\n")
  ready := path(project, "ready"); release := path(project, "release")
  worker := "import { exists, writeText } from \"std/fs\"\nimport { Duration, Thread } from \"std/time\"\nexport function testWait(): none {\ntry! writeText(\"" + ready + "\", \"ready\")\nfor attempt of 0..<3000 { if exists(\"" + release + "\") { return }\nThread.sleep(Duration.ofMillis(10L)) }\npanic(\"release timed out\")\n}\n"
  try write(path(project, "main.test.do"), worker)
  try write(release, "")
  children := Children()
  lockPath := path(project, "build/.doof.lock")
  lock := File { path: lockPath, mode: .ReadWrite, create: true, lock: .Exclusive } else { return Failure("Cannot acquire test build lock") }
  try building := start(children, compiler, ["build", project, "-o", path(work, "build-output")], path(work, "build.log"), stdlib)
  try testing := start(children, compiler, ["test", project, "-o", path(work, "test-output")], path(work, "test.log"), stdlib)
  try awaitFile(path(work, "build.log"), "Waiting for project build lock:")
  try awaitFile(path(work, "test.log"), "Waiting for project build lock:")
  try require(building.isRunning() && testing.isRunning() && !exists(path(work, "build-output")) && !exists(path(work, "test-output")), "Queued command emitted before acquiring project lock")
  try command(compiler, ["test", project, "--list"], { DOOF_STDLIB_ROOT: stdlib })
  try write(path(work, "other/main.do"), "function main(): none {}\n")
  try command(compiler, ["check", path(work, "other/main.do")], { DOOF_STDLIB_ROOT: stdlib })
  try building.terminate(); _ := building.wait() else {}
  _ := lock.close() else { return Failure("Cannot release test build lock") }
  try passed(testing, path(work, "test.log"))
  try erase(ready); try erase(release)
  try holding := start(children, compiler, ["test", project, "-o", path(work, "test-output")], path(work, "holding.log"), stdlib)
  try awaitFile(ready)
  try queued := start(children, compiler, ["build", project, "-o", path(work, "build-output")], path(work, "queued.log"), stdlib)
  try awaitFile(path(work, "queued.log"), "Waiting for project build lock:")
  try write(release, ""); try passed(holding, path(work, "holding.log")); try passed(queued, path(work, "queued.log"))
  try erase(ready); try erase(release)
  try write(path(project, "main.do"), worker.replaceAll("export function testWait()", "function main()"))
  try running := start(children, compiler, ["run", project, "-o", path(work, "build-output")], path(work, "run.log"), stdlib)
  try awaitFile(ready)
  try command(compiler, ["check", project], { DOOF_STDLIB_ROOT: stdlib })
  try require(running.isRunning(), "Program exited before lock-release assertion")
  try write(release, ""); try passed(running, path(work, "run.log"))
  handle := File { path: lockPath, mode: .ReadWrite, lock: .Exclusive, waitForLock: false } else { return Failure("Project lock leaked") }
  _ := handle.close() else { return Failure("Cannot close project test lock") }
  return Success()
}
export function cacheChecks(root: string, oldCompiler: string, newCompiler: string, stdlib: string): Result<none, string> {
  try oldVersion := capture(oldCompiler, ["--version"]); try newVersion := capture(newCompiler, ["--version"])
  try require(oldVersion != newVersion && !oldVersion.contains("unstamped") && !newVersion.contains("unstamped"), "Cache checks require two distinct stamped compiler versions")
  work := path(root, "build/compiler-cache-check")
  try erase(work); try makeDirectory(work)
  try write(path(work, "main.do"), "function main(): int => 7\n")
  compiler := path(work, "doof"); output := path(work, "output")
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib, DOOF_RUNTIME_HEADER: path(root, "runtime/doof_runtime.h") }
  try command("cp", [oldCompiler, compiler])
  try command(compiler, ["emit", path(work, "main.do"), "-o", output], environment)
  try oldCheck := read(path(output, ".doof-cache/v1/check.json"))
  try markCpp(output)
  try command(compiler, ["emit", path(work, "main.do"), "-o", output], environment)
  try warmMarker := hasMarker(output)
  try require(warmMarker, "Unchanged compiler did not reuse emission")
  try command("cp", [newCompiler, compiler])
  try command(compiler, ["check", path(work, "main.do"), "-o", output], environment)
  try newCheck := read(path(output, ".doof-cache/v1/check.json"))
  try require(oldCheck != newCheck, "New compiler reused checked state")
  try command(compiler, ["emit", path(work, "main.do"), "-o", output], environment)
  try staleMarker := hasMarker(output)
  try require(!staleMarker, "New compiler reused stale emission")
  try markCpp(output)
  try command("cp", [compiler, path(work, "renamed-doof")])
  try command(path(work, "renamed-doof"), ["emit", path(work, "main.do"), "-o", output], environment)
  try renamedMarker := hasMarker(output)
  return require(renamedMarker, "Compiler rename lost stable version identity")
}
function markCpp(root: string): Result<none, string> {
  try names := files(root)
  for name of names { if name.endsWith(".cpp") { try original := read(path(root, name)); try write(path(root, name), original + "\n// compiler-cache-retained-marker\n") } }
  return Success()
}
function hasMarker(root: string): Result<bool, string> {
  try names := files(root)
  for name of names { if name.endsWith(".cpp") { try source := read(path(root, name)); if source.contains("compiler-cache-retained-marker") { return Success(true) } } }
  return Success(false)
}

import { parseJsonValue, formatJsonValue } from "std/json"
class NativeTestResult {
  id: string
  exitCode: int
}
function testResults(file: string): Result<NativeTestResult[], string> {
  try content := read(file); try value := parseJsonValue(content)
  items := value as JsonValue[] else { return Failure("Expected structured result array") }
  result: NativeTestResult[] := []
  for item of items { try decoded := NativeTestResult.fromJsonValue(item); result.push(decoded) }
  return Success(result)
}
export function nativeEditorChecks(root: string, compiler: string): Result<none, string> {
  directory := path(root, "build/editor-native-check")
  try erase(directory); try makeDirectory(directory)
  try write(path(directory, "doof.json"), "{\"name\":\"native-editor-fixture\",\"build\":{\"entry\":\"main.do\"}}")
  try write(path(directory, "main.do"), "function main(): int => 0\n")
  tests := path(directory, "workflow.test.do")
  try write(tests, "export function testSelected(): none {}\nexport function testSelectedOther(): none { panic(\"Unselected test must not execute\") }\n")
  try discovered := capture(compiler, ["test", directory, "--list", "--json"])
  try listValue := parseJsonValue(discovered)
  listed := listValue as JsonValue[] else { return Failure("Expected JSON test discovery") }
  try require(listed.length == 2, "Wrong test discovery count")
  id := "workflow.test.do::testSelected"; report := path(directory, "results.json")
  try command(compiler, ["test", directory, "--exact-filter", id, "--report-json", report])
  try selected := testResults(report)
  try require(selected.length == 1 && selected[0].id == id && selected[0].exitCode == 0, "Exact test selection failed")
  selection := path(directory, "selected.json")
  try write(selection, formatJsonValue([id, "workflow.test.do::testSelectedOther"]))
  try batchOutput := execute(compiler, ["test", directory, "--selection-json", selection, "--report-json", report])
  try batch := testResults(report)
  try require(batchOutput.exitCode != 0 && batch.length == 2 && batch[0].exitCode == 0 && batch[1].exitCode != 0, "Batch selection lost structured failure")
  try require(text(batchOutput.stdout).contains("REUSE frontend shared"), "Selection change invalidated shared frontend")
  try write(tests, "export function testSelected(): none {}\nexport function testSelectedOther(): none {}\n")
  try changed := capture(compiler, ["test", directory, "--selection-json", selection, "--report-json", report])
  try require(!changed.contains("REUSE frontend"), "Source edit reused stale frontend")
  try results := testResults(report)
  for result of results { try require(result.exitCode == 0, "Changed test did not pass") }
  return Success()
}
