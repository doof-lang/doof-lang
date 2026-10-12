// `doof test` workflow: discovery, per-group harness compilation, parallel test
// processes, structured results, and coverage reports.

import { formatJsonValue } from "std/json"
import { Compilation, compileWithLoader } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { CliRequest } from "./cli"
import { planProjectEmission } from "./emitter-project"
import { ModuleNamespaceMapping } from "./emitter-names"
import {
  cachedModuleGraph, frontendCachePath, frontendConfigurationFingerprint, frontendEmissionCacheSupported,
  frontendStateForCompilation, frontendStateMatches, readFrontendState, removeStaleFrontendOutputs, writeFrontendState,
} from "./frontend-cache-driver"
import { ensureOutputDirectory, materializeProject, materializeRuntimeHeader, writeTextIfChanged } from "./materialize-driver"
import { buildNativeProject } from "./native-build-driver"
import { Parser } from "./parser"
import {
  MAX_NATIVE_COMPILER_OUTPUT_BYTES, MAX_PRINTED_DIAGNOSTICS, NativeCommandResult, hostPlatform, printDiagnostics,
  printNativeCommandOutput, runNativeCommand,
} from "./process-driver"
import { environmentValue, fileName, joinPath, parentPath, readProjectSpec } from "./project"
import { acquireProjectBuildLock } from "./project-build-lock"
import {
  configuredSourceDiskPath, driverRootLogicalPath, driverRootLogicalPrefix, prepareReachedStdlibPackages,
  preparationTargetForRequest, projectNativePackages, sourceLoaderForRequest,
} from "./source-loader-driver"
import { StdlibPreparationTarget } from "./stdlib-preparation"
import {
  CoverageModuleMetadata, CoverageReport, DiscoveredTest, buildCoverageReport, discoverModuleTests,
  coverageFileRelativePath, selectTestsFromJson, filterDiscoveredTests, formatParseFailure, generateTestHarness, groupTestsForCompilation,
  mergeCoverageOutput, renderCoverageFileHtml, renderCoverageHtml, renderCoverageJson, selectedTestsForExecution,
  stripCoverageLines,
} from "./test-runner"
import { boundedWorkerCount, renderProgressBar } from "./progress"
import { planAppleWasmTestRun, planAppleWasmTestRunnerBuild } from "./wasm-test-runner"
import { BlobReader } from "std/blob"
import { sha256HexString } from "std/crypto"
import { EntryKind, File, exists, isDirectory, readDir, readText, readTextResource, writeText } from "std/fs"
import { absolute } from "std/path"

import isolated function printFlushed(value: string): none from "doof_runtime.hpp" as doof::print_flushed

readonly MAX_COVERAGE_OUTPUT_BYTES = 16777216L

class TestExecutionResult {
  readonly id: string
  readonly command: NativeCommandResult
}

class TestWorkerCompletion {
  readonly workerIndex: int
  readonly test: TestExecutionResult
}

class TestProcessWorker {
  readonly command: string
  readonly wasmModule: string = ""
  readonly directory: string
  readonly maxOutputBytes: long

  runTest(workerIndex: int, id: string): TestWorkerCompletion {
    let command = this.command
    let arguments = [id]
    if this.wasmModule != "" {
      invocation := planAppleWasmTestRun(this.command, this.wasmModule, id)
      command = invocation.command
      arguments = invocation.arguments
    }
    result := runNativeCommand(command, arguments, this.directory, false, .Isolated, this.maxOutputBytes)
    return TestWorkerCompletion { workerIndex, test: TestExecutionResult { id, command: result } }
  }
}

/**
 * Describes a failed test process that printed nothing. The process runner
 * reports a death by signal N as exit code 128 + N.
 */
export function silentTestFailureMessage(exitCode: int): string {
  if exitCode > 128 && exitCode < 160 {
    signal := exitCode - 128
    name := case signal {
      4 -> " (SIGILL)",
      6 -> " (SIGABRT)",
      8 -> " (SIGFPE)",
      9 -> " (SIGKILL)",
      11 -> " (SIGSEGV)",
      13 -> " (SIGPIPE)",
      15 -> " (SIGTERM)",
      _ -> ""
    }
    return "test process terminated by signal " + string(signal) + name + " without output"
  }
  return "test process exited with code " + string(exitCode) + " without output"
}

function buildAppleWasmTestRunner(buildRoot: string): Result<string, string> {
  runnerDirectory := joinPath(joinPath(buildRoot, ".doof-tests"), "apple-wasm-runner")
  ensureOutputDirectory(runnerDirectory)
  sourcePath := joinPath(runnerDirectory, "doof-wasm-test-runner.swift")
  runnerPath := joinPath(runnerDirectory, "doof-wasm-test-runner")
  fingerprintPath := joinPath(runnerDirectory, "source.sha256")
  source := readTextResource("doof_wasm_test_runner_apple.swift") else {
    return Failure("Could not read embedded doof_wasm_test_runner_apple.swift")
  }
  writeTextIfChanged(sourcePath, source)
  fingerprint := sha256HexString(source)
  if exists(runnerPath) && exists(fingerprintPath) {
    previousFingerprint := readText(fingerprintPath)!
    if previousFingerprint.trim() == fingerprint { return Success(runnerPath) }
  }
  plan := planAppleWasmTestRunnerBuild(sourcePath, runnerPath)
  built := runNativeCommand(plan.command, plan.arguments, runnerDirectory)
  if built.exitCode != 0 {
    output := if built.error != ""
      then built.error
      else BlobReader(built.output).readString(long(built.output.length)).trim()
    return Failure("Could not build the Apple JavaScriptCore Wasm test runner" + if output == "" then "" else ":\n" + output)
  }
  writeText(fingerprintPath, fingerprint + "\n")!
  return Success(runnerPath)
}

function collectTestFiles(path: string, results: string[], root: bool = true): none {
  if !isDirectory(path) {
    if path.endsWith(".do") { results.push(path) }
    return
  }
  if !root && exists(joinPath(path, "doof.json")) { return }
  entries := readDir(path)!
  for entry of entries {
    entryPath := joinPath(path, entry.name)
    if entry.kind == EntryKind.Directory {
      collectTestFiles(entryPath, results, false)
    } else if entry.kind == EntryKind.File && entry.name.endsWith(".test.do") {
      results.push(entryPath)
    }
  }
}

function sortedTestFiles(values: string[]): string[] {
  let result: string[] = []
  let last = ""
  for count of 0..<values.length {
    let candidate: string | none = none
    for value of values {
      if (result.length == 0 || value > last) && (candidate == none || value < candidate!) { candidate = value }
    }
    if candidate != none { result.push(candidate!); last = candidate! }
  }
  return result
}

function sortedDiscoveredTests(values: DiscoveredTest[]): DiscoveredTest[] {
  let result: DiscoveredTest[] = []
  let last = ""
  for count of 0..<values.length {
    let candidate: DiscoveredTest | none = none
    for value of values {
      if (result.length == 0 || value.id > last) && (candidate == none || value.id < candidate!.id) { candidate = value }
    }
    if candidate != none { result.push(candidate!); last = candidate!.id }
  }
  return result
}

function mergeCoverageGroup(
  groupModules: CoverageModuleMetadata[],
  groupHits: int[][],
  allModules: CoverageModuleMetadata[],
  allHits: int[][],
): none {
  for groupIndex of 0..<groupModules.length {
    groupModule := groupModules[groupIndex]
    diskPath := configuredSourceDiskPath(groupModule.modulePath)
    let targetIndex = -1
    for index of 0..<allModules.length {
      if allModules[index].modulePath == diskPath { targetIndex = index }
    }
    if targetIndex < 0 {
      let lines: int[] = []
      for line of groupModule.instrumentedLines { lines.push(line) }
      allModules.push(CoverageModuleMetadata {
        moduleId: allModules.length,
        modulePath: diskPath,
        instrumentedLines: lines,
      })
      allHits.push([])
      targetIndex = allModules.length - 1
    }
    if groupIndex < groupHits.length {
      for line of groupHits[groupIndex] {
        let found = false
        for existing of allHits[targetIndex] { if existing == line { found = true } }
        if !found { allHits[targetIndex].push(line) }
      }
    }
  }
}

function printCoverageSummary(report: CoverageReport): none {
  println("Coverage summary:")
  for file of report.files {
    percent := string(file.percentTenths \ 10) + "." + string(file.percentTenths % 10)
    println("  " + file.path + ": " + string(file.covered) + "/" + string(file.total) + " lines (" + percent + "%)")
  }
  overall := string(report.totalPercentTenths \ 10) + "." + string(report.totalPercentTenths % 10)
  println("Overall: " + string(report.totalCovered) + "/" + string(report.totalLines) + " lines (" + overall + "%)")
}

function coverageHtmlPath(jsonPath: string): string {
  if jsonPath.endsWith(".json") { return jsonPath.substring(0, jsonPath.length - 5) + ".html" }
  return jsonPath + ".html"
}

export function writeCoverageHtml(report: CoverageReport, jsonPath: string, rootDirectory: string): string {
  indexPath := coverageHtmlPath(jsonPath)
  ensureOutputDirectory(parentPath(indexPath))
  filesDirectory := indexPath.substring(0, indexPath.length - 5) + "_files"
  filesDirectoryName := fileName(filesDirectory)
  for file of report.files {
    relativePage := coverageFileRelativePath(file.path)
    pagePath := joinPath(filesDirectory, relativePage)
    ensureOutputDirectory(parentPath(pagePath))
    let depth = 1
    for index of 0..<relativePage.length { if relativePage[index] == '/' { depth += 1 } }
    indexHref := "../".repeat(depth) + fileName(indexPath)
    sourcePath := joinPath(rootDirectory, file.path)
    let source = ""
    if exists(sourcePath) { source = readText(sourcePath)! }
    writeText(pagePath, renderCoverageFileHtml(file, source, indexHref))!
  }
  writeText(indexPath, renderCoverageHtml(report, filesDirectoryName))!
  return indexPath
}

/** Runs the one-harness-per-module test convention. */
export function testRequest(request: CliRequest): int {
  target := absolute(request.entry)!
  if !exists(target) {
    println("error: File not found: " + target)
    return 1
  }
  rootDirectory := if isDirectory(target) then target else parentPath(target)
  let testFiles: string[] = []
  collectTestFiles(target, testFiles)
  testFiles = sortedTestFiles(testFiles)
  let discovered: DiscoveredTest[] = []
  for testFile of testFiles {
    source := readText(testFile) else {
      println("error: Could not read test file: " + testFile)
      return 1
    }
    parser := Parser { source }
    parsed := catchPanic(=> parser.parse())
    program := parsed else failure {
      if parser.errorMessage == "" { panic(failure) }
      println(formatParseFailure(testFile, source, parser.errorLine, parser.errorColumn, parser.errorMessage))
      return 1
    }
    discovery := discoverModuleTests(program, testFile, rootDirectory)
    for error of discovery.errors { println(error) }
    if discovery.errors.length > 0 { return 1 }
    for test of discovery.tests { discovered.push(test) }
  }
  discovered = sortedDiscoveredTests(discovered)
  let selected = filterDiscoveredTests(discovered, request.filter, request.exactFilter)
  if request.selectionJson != "" {
    selectionSource := readText(request.selectionJson) else {
      println("error: Could not read test selection: " + request.selectionJson)
      return 1
    }
    exactSelection := selectTestsFromJson(discovered, selectionSource) else error {
      println("error: " + error)
      return 1
    }
    selected = exactSelection
  }
  if request.listOnly && request.jsonOutput {
    let values: SerialValue[] = []
    for test of selected { values.push(test.toSerialObject()) }
    println(formatJsonValue(values.cloneReadonly()))
    return 0
  }
  if selected.length == 0 {
    suffix := if request.filter == "" then "" else " matching \"" + request.filter + "\""
    println("error: No tests found under " + target + suffix)
    return 1
  }
  if request.listOnly {
    for test of selected { println(test.id) }
    return 0
  }

  groups := groupTestsForCompilation(discovered)
  let lockDirectories: string[] = []
  for group of groups {
    if selectedTestsForExecution(group.tests, selected).length == 0 { continue }
    projectForLock := readProjectSpec(group.tests[0].modulePath, hostPlatform(), request.targetOverride)
    lockDirectories.push(joinPath(projectForLock.rootDirectory, projectForLock.buildDirectory))
  }
  // Sort and deduplicate before taking any locks, including for mock groups.
  let projectLocks: File[] = []
  for directory of sortedTestFiles(lockDirectories) {
    projectLock := acquireProjectBuildLock(directory, ".") else error {
      println("error: " + error)
      return 1
    }
    projectLocks.push(projectLock)
  }

  let resultValues: SerialValue[] = []
  let passed = 0
  let failed = 0
  let coverageModules: CoverageModuleMetadata[] = []
  let coverageHits: int[][] = []
  let appleWasmRunner = ""
  for group of groups {
    compilationTests := group.tests
    moduleTests := selectedTestsForExecution(compilationTests, selected)
    if moduleTests.length == 0 { continue }
    testFile := compilationTests[0].modulePath
    project := readProjectSpec(testFile, hostPlatform(), request.targetOverride)
    wasmTests := project.target == "wasm"
    if wasmTests && hostPlatform() != "macos" {
      println("error: doof test --target wasm currently requires macOS and JavaScriptCore")
      return 1
    }
    buildRoot := if request.outputDirectory == ""
      then joinPath(project.rootDirectory, project.buildDirectory)
      else absolute(request.outputDirectory)!
    coverageSuffix := if request.coverage then "-coverage" else ""
    targetSuffix := if wasmTests then "-wasm" else ""
    outputDirectory := joinPath(joinPath(buildRoot, ".doof-tests"), group.outputName + targetSuffix + coverageSuffix)
    harnessPath := joinPath(outputDirectory, "__doof_tests__.do")
    ensureOutputDirectory(outputDirectory)
    writeTextIfChanged(harnessPath, generateTestHarness(harnessPath, compilationTests))

    stdlibRoot := environmentValue("DOOF_STDLIB_ROOT")
    rootLogicalPrefix := driverRootLogicalPrefix(project.name, project.rootDirectory)
    let namespaceMappings: ModuleNamespaceMapping[] = [ModuleNamespaceMapping {
      logicalPrefix: rootLogicalPrefix,
      packageName: project.name,
      outputRoot: "",
    }]
    let testPreparationTarget = StdlibPreparationTarget { nativeTarget: hostPlatform() }
    if wasmTests {
      resolvedTarget := preparationTargetForRequest("wasm", hostPlatform(), "", "") else error {
        println("error: " + error)
        return 1
      }
      testPreparationTarget = resolvedTarget
    }
    loader := sourceLoaderForRequest(
      harnessPath, stdlibRoot, namespaceMappings, project.manifest, buildRoot, hostPlatform(), testPreparationTarget,
    ) else error {
      println("error: " + error)
      return 1
    }
    entry := driverRootLogicalPath(harnessPath, project.rootDirectory, project.name)
    configuration := frontendConfigurationFingerprint(entry, "executable", project.target, project.manifest, stdlibRoot, hostPlatform(), testPreparationTarget)
    cachePath := frontendCachePath(outputDirectory, "emission")
    previous := readFrontendState(cachePath)
    cacheAllowed := !request.coverage && frontendEmissionCacheSupported(project.target)
    cached := if cacheAllowed && previous != none && frontendStateMatches(previous, configuration, loader)
      then cachedModuleGraph(previous!, outputDirectory) else none
    result := if cached != none then Compilation { emission: cached!, diagnostics: [] }
      else compileWithLoader([], entry, loader, namespaceMappings, "executable", request.coverage)
    if cached != none { println("REUSE frontend " + group.outputName) }
    if result.diagnostics.length > 0 { printDiagnostics(result.diagnostics) }
    if hasErrorDiagnostics(result.diagnostics) { return 1 }
    if result.emission == none { panic("test compiler produced no emission") }
    rootManifest := project.manifest
    _ := prepareReachedStdlibPackages(testPreparationTarget) else error {
      println("error: " + error)
      return 1
    }
    emission := planProjectEmission(result.emission!, projectNativePackages(project.rootDirectory, rootManifest))
    if request.coverage { emission.nativeBuild.defines.push("DOOF_COVERAGE") }
    materializeProject(outputDirectory, emission)
    materializeRuntimeHeader(outputDirectory)
    if cacheAllowed && cached == none && result.diagnostics.length == 0 {
      next := frontendStateForCompilation(result, configuration, rootManifest)
      removeStaleFrontendOutputs(previous, next, outputDirectory)
      writeFrontendState(cachePath, next)
    }
    binary := joinPath(outputDirectory, if wasmTests then "doof-tests.wasm" else "doof-tests")
    println("BUILD " + group.outputName)
    buildExitCode := buildNativeProject(
      request.compiler, outputDirectory, binary, emission, .Debug, hostPlatform(), .Progress,
      wasmTests,
    )
    if buildExitCode != 0 { return buildExitCode }

    if wasmTests && appleWasmRunner == "" {
      builtRunner := buildAppleWasmTestRunner(buildRoot) else error {
        println("error: " + error)
        return 1
      }
      appleWasmRunner = builtRunner
    }

    println("Testing " + string(moduleTests.length) + if moduleTests.length == 1 then " test" else " tests")
    printFlushed(renderProgressBar(0, moduleTests.length))
    let testWorkers: Actor<TestProcessWorker>[] = []
    let pendingTests: Promise<TestWorkerCompletion>[] = []
    maxTestOutput := if request.coverage then MAX_COVERAGE_OUTPUT_BYTES else MAX_NATIVE_COMPILER_OUTPUT_BYTES
    let nextTestIndex = 0
    for workerIndex of 0..<boundedWorkerCount(moduleTests.length) {
      worker := Actor<TestProcessWorker>(
        if wasmTests then appleWasmRunner else binary,
        if wasmTests then binary else "",
        project.rootDirectory,
        maxTestOutput,
      )
      testWorkers.push(worker)
      test := moduleTests[nextTestIndex]
      pendingTests.push(async worker.runTest(workerIndex, test.id))
      nextTestIndex += 1
    }
    let completedTests = 0
    let executionResults: TestExecutionResult[] = []
    while pendingTests.length > 0 {
      workerResult := pendingTests.takeFirstCompleted() else error {
        for worker of testWorkers { ignoredWorker := retire worker }
        println("")
        println("error: test worker failed: " + error)
        return 1
      }
      executionResults.push(workerResult.test)
      completedTests += 1
      printFlushed("\r" + renderProgressBar(completedTests, moduleTests.length))
      if nextTestIndex < moduleTests.length {
        test := moduleTests[nextTestIndex]
        pendingTests.push(async testWorkers[workerResult.workerIndex].runTest(workerResult.workerIndex, test.id))
        nextTestIndex += 1
      }
    }
    for worker of testWorkers { retire worker }
    println("")

    for test of moduleTests {
      execution := findTestExecutionResult(executionResults, test.id)
      if execution == none { panic("test worker returned no result for " + test.id) }
      testResult := execution!.command
      if request.coverage {
        if testResult.truncated {
          println("error: coverage output exceeded " + string(MAX_COVERAGE_OUTPUT_BYTES) + " bytes for " + test.id)
          return 1
        }
        output := BlobReader(testResult.output).readString(long(testResult.output.length))
        let groupHits: int[][] = []
        for ignored of result.emission!.coverageModules { groupHits.push([]) }
        mergeCoverageOutput(output, result.emission!.coverageModules, groupHits)
        mergeCoverageGroup(result.emission!.coverageModules, groupHits, coverageModules, coverageHits)
        if testResult.exitCode != 0 {
          visibleOutput := stripCoverageLines(output)
          println(if visibleOutput != "" then visibleOutput else silentTestFailureMessage(testResult.exitCode))
        }
      } else if testResult.exitCode != 0 {
        remaining := printNativeCommandOutput(testResult, MAX_PRINTED_DIAGNOSTICS)
        if remaining == MAX_PRINTED_DIAGNOSTICS { println(silentTestFailureMessage(testResult.exitCode)) }
        if testResult.truncated { println("... test output capture truncated after " + string(MAX_NATIVE_COMPILER_OUTPUT_BYTES) + " bytes") }
      }
      exitCode := testResult.exitCode
      if request.reportJson != "" {
        value := structuredTestResult(test.id, exitCode, BlobReader(testResult.output).readString(long(testResult.output.length)))
        resultValues.push(value)
      }
      if exitCode == 0 {
        passed = passed + 1
      } else {
        failed = failed + 1
        println("FAIL " + test.id)
      }
    }
  }
  if request.reportJson != "" {
    _ := writeText(request.reportJson, formatJsonValue(resultValues.cloneReadonly())) else error {
      println("error: Could not write test report: " + request.reportJson)
      return 1
    }
  }
  println("Tests finished: " + string(passed) + " passed, " + string(failed) + " failed")
  if request.coverage && coverageModules.length > 0 {
    report := buildCoverageReport(coverageModules, coverageHits, rootDirectory)
    printCoverageSummary(report)
    outputPath := if request.coverageOutput == ""
      then joinPath(joinPath(rootDirectory, "build"), "coverage/doof-test-coverage.json")
      else absolute(request.coverageOutput)!
    ensureOutputDirectory(parentPath(outputPath))
    writeText(outputPath, renderCoverageJson(report))!
    println("Coverage report written to " + outputPath)
    htmlPath := writeCoverageHtml(report, outputPath, rootDirectory)
    println("Coverage HTML report written to " + htmlPath)
  }
  return if failed == 0 then 0 else 1
}

function findTestExecutionResult(results: TestExecutionResult[], id: string): TestExecutionResult | none {
  for result of results { if result.id == id { return result } }
  return none
}

export function structuredTestResult(id: string, exitCode: int, output: string): SerialObject => { "id": id, "exitCode": exitCode, "output": output }
