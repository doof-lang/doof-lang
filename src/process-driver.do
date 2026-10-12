// Native subprocess execution and bounded console reporting for the driver.

import { Diagnostic } from "./semantic"
import { BlobReader } from "std/blob"
import { ExecOptions, ProcessGroupMode, run, platform } from "std/os"

export readonly MAX_PRINTED_DIAGNOSTICS = 20
export readonly MAX_NATIVE_COMPILER_OUTPUT_BYTES = 262144L

export function hostPlatform(): string {
  value := platform()
  return if value == "darwin" then "macos" else value
}

export class NativeCommandResult {
  readonly exitCode: int
  readonly output: readonly byte[] = []
  readonly error: string = ""
  readonly truncated: bool
}

export isolated function runNativeCommand(
  command: string,
  arguments: string[],
  directory: string | none = none,
  inheritOutput: bool = false,
  processGroupMode: ProcessGroupMode = .Isolated,
  // Defaults are emitted in the generated prototype before module values.
  maxOutputBytes: long = 262144L,
  environment: Map<string, string> = {},
): NativeCommandResult {
  executed := run(command, arguments, ExecOptions {
    cwd: directory,
    withStdin: false,
    mergeStderrIntoStdout: true,
    inheritOutput,
    processGroupMode,
    maxOutputBytes,
    env: environment.cloneReadonly(),
  }) else error {
    return NativeCommandResult { exitCode: -1, error, truncated: false }
  }
  let output: readonly byte[] = []
  if !inheritOutput { output = executed.stdout }
  return NativeCommandResult {
    exitCode: executed.exitCode,
    output,
    truncated: executed.stdoutTruncated,
  }
}

export function printNativeCommandOutput(result: NativeCommandResult, remainingLines: int): int {
  let remaining = remainingLines
  output := if result.error != ""
    then result.error
    else BlobReader(result.output).readString(long(result.output.length))
  for line of output.split("\n") {
    if line == "" { continue }
    if remaining <= 0 { return 0 }
    println(line)
    remaining -= 1
  }
  return remaining
}

export function printDiagnostics(diagnostics: Diagnostic[]): none {
  displayCount := if diagnostics.length < MAX_PRINTED_DIAGNOSTICS then diagnostics.length else MAX_PRINTED_DIAGNOSTICS
  for index of 0..<displayCount {
    diagnostic := diagnostics[index]
    println(
      diagnostic.module + ":" + string(diagnostic.span.start.line) + ":" + string(diagnostic.span.start.column) +
      ": " + diagnostic.severity + ": " + diagnostic.message,
    )
  }
  if diagnostics.length > displayCount {
    println("... " + string(diagnostics.length - displayCount) + " more diagnostics omitted")
  }
}
