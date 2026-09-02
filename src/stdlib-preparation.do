// Bounded target preparation for reached standard packages.

import { PackageManifest, StdlibPreparationCommand } from "./package-manifest"
import { BlobReader } from "std/blob"
import { ExecOptions, run } from "std/os"
import { join } from "std/path"

readonly MAX_STDLIB_PREPARATION_OUTPUT_BYTES = 1048576L

export class StdlibPreparationTarget {
  nativeTarget: string
  sdkPath: string = ""
  targetTriple: string = ""
  configureHost: string = ""
  jobs: int = 1
}

export function applyStdlibPreparationSubstitutions(
  value: string,
  packageRoot: string,
  target: StdlibPreparationTarget,
): string {
  return value.replaceAll("\${packageRoot}", packageRoot)
    .replaceAll("\${jobs}", string(if target.jobs < 1 then 1 else target.jobs))
    .replaceAll("\${nativeTarget}", target.nativeTarget)
    .replaceAll("\${sdkPath}", target.sdkPath)
    .replaceAll("\${targetTriple}", target.targetTriple)
    .replaceAll("\${configureHost}", target.configureHost)
}

function withinPackage(path: string, packageRoot: string): bool {
  boundary := if packageRoot.endsWith("/") then packageRoot else packageRoot + "/"
  return path == packageRoot || path.startsWith(boundary)
}

function runPreparationCommand(
  command: StdlibPreparationCommand,
  index: int,
  manifest: PackageManifest,
  target: StdlibPreparationTarget,
): Result<none, string> {
  workingDirectory := if command.workingDirectory == ""
    then manifest.rootDirectory
    else join([manifest.rootDirectory, applyStdlibPreparationSubstitutions(command.workingDirectory, manifest.rootDirectory, target)])
  if !withinPackage(workingDirectory, manifest.rootDirectory) {
    return Failure("Standard package preparation workingDirectory must stay within " + manifest.rootDirectory)
  }
  let environment: Map<string, string> = {}
  for key, value of command.env {
    environment.set(key, applyStdlibPreparationSubstitutions(value, manifest.rootDirectory, target))
  }
  let arguments: string[] = []
  for argument of command.args {
    arguments.push(applyStdlibPreparationSubstitutions(argument, manifest.rootDirectory, target))
  }
  program := applyStdlibPreparationSubstitutions(command.program, manifest.rootDirectory, target)
  result := run(program, arguments, ExecOptions {
    cwd: workingDirectory, env: environment.drainToReadonly(), withStdin: false,
    mergeStderrIntoStdout: true, maxOutputBytes: MAX_STDLIB_PREPARATION_OUTPUT_BYTES,
  }) else error { return Failure(program + ": " + error) }
  output := BlobReader(result.stdout).readString(long(result.stdout.length)).trim()
  if result.exitCode != 0 {
    return Failure(
      "Standard package " + manifest.name + " preparation command " + string(index + 1) +
      " exited with code " + string(result.exitCode) + if output == "" then "" else ":\n" + output,
    )
  }
  return Success()
}

export function prepareStdlibPackage(
  manifest: PackageManifest,
  target: StdlibPreparationTarget,
): Result<none, string> {
  for index of 0..<manifest.stdlibPreparation.length {
    try runPreparationCommand(manifest.stdlibPreparation[index], index, manifest, target)
  }
  return Success()
}
