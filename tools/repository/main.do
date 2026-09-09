import { buildExtension, buildEditorService, verifyEditorArtifacts } from "./extension"
import { developmentBuild } from "./build"
import { captureNative } from "./snapshot"
import { testRepository, releaseVerification, debuggerChecks } from "./verify"
import { prepareRelease, checkSourceSnapshot, signingPreflight } from "./release"
import { cacheChecks, projectLockChecks, nativeEditorChecks } from "./process-checks"
import { path, stdlibDirectory, setting } from "./common"
import { require } from "./common"
function dispatch(arguments: string[]): Result<int, string> {
  try require(arguments.length >= 1, "usage: repository <root> <dev|build|test|release> [version]")
  if arguments[0] == "capture" {
    rest: string[] := []
    for i of 1..<arguments.length { rest.push(arguments[i]) }
    return captureNative(rest)
  }
  try require(arguments.length >= 2, "repository command is required")
  if arguments[1] != "release" && arguments[1] != "cache-test" { try require(arguments.length == 2, "Unexpected repository command arguments") }
  if arguments[1] == "dev" || arguments[1] == "build" { try developmentBuild(arguments[0], arguments[1] == "build") }
  else if arguments[1] == "preflight" { try signingPreflight(setting("DOOF_SIGN_IDENTITY"), setting("DOOF_NOTARY_PROFILE")) }
  else if arguments[1] == "snapshot-test" { try checkSourceSnapshot(arguments[0]) }
  else if arguments[1] == "release" { try require(arguments.length == 3, "release requires a version"); try prepareRelease(arguments[0], arguments[2]) }
  else if arguments[1] == "test" || arguments[1] == "verify" || arguments[1] == "debugger-test" || arguments[1] == "process-test" {
    try stdlib := stdlibDirectory(arguments[0])
    compiler := path(arguments[0], "dist/doof")
    if arguments[1] == "test" { try testRepository(arguments[0], compiler, stdlib) }
    else if arguments[1] == "verify" { try releaseVerification(arguments[0], compiler, stdlib) }
    else if arguments[1] == "process-test" { try projectLockChecks(arguments[0], compiler, stdlib) }
    else { try debuggerChecks(arguments[0], compiler, stdlib) }
  }
  else if arguments[1] == "extension-native" { try nativeEditorChecks(arguments[0], path(arguments[0], "dist/doof")) }
  else if arguments[1] == "extension-build" { try buildExtension(arguments[0]) }
  else if arguments[1] == "extension-service" { try buildEditorService(arguments[0]) }
  else if arguments[1] == "extension-verify" { try verifyEditorArtifacts(arguments[0]) }
  else if arguments[1] == "cache-test" {
    try require(arguments.length == 4, "cache-test requires two stamped compilers")
    try stdlib := stdlibDirectory(arguments[0]); try cacheChecks(arguments[0], arguments[2], arguments[3], stdlib)
  }
  else { return Failure("Unknown repository command: " + arguments[1]) }
  return Success(0)
}
function main(arguments: string[]): int {
  result := dispatch(arguments) else error { println("error: " + error); return 1 }
  return result
}
