// Pure target validation and launch-environment planning for `doof observe`.

import { RunInvocation } from "./run-command"

export function observeTargetError(target: string, iosApp: bool): string {
  if target == "wasm" || iosApp {
    return "doof observe supports native console executables and macOS applications"
  }
  return ""
}

export function observeEnvironment(port: int, noOpen: bool, retainEvents: int, uiRoot: string = "", urlFile: string = ""): Map<string, string> {
  let environment: Map<string, string> = {
    DOOF_OBSERVE_PORT: string(port),
    DOOF_OBSERVE_NO_OPEN: if noOpen then "1" else "0",
    DOOF_OBSERVE_RETAIN_EVENTS: string(retainEvents),
  }
  if uiRoot != "" { environment.set("DOOF_OBSERVE_UI_ROOT", uiRoot) }
  if urlFile != "" { environment.set("DOOF_OBSERVE_URL_FILE", urlFile) }
  return environment
}

/** Converts environment overrides to macOS `open --env NAME=value` arguments. */
export function observeOpenEnvironmentArguments(environment: Map<string, string>): string[] {
  let arguments: string[] = []
  for name, value of environment {
    arguments.push("--env")
    arguments.push(name + "=" + value)
  }
  return arguments
}

/** Plans an observed macOS bundle launch with the runtime settings forwarded. */
export function planObservedMacOSAppRun(
  appPath: string,
  packageRoot: string,
  environment: Map<string, string>,
): RunInvocation {
  arguments := ["-n"]
  for argument of observeOpenEnvironmentArguments(environment) { arguments.push(argument) }
  arguments.push(appPath)
  return RunInvocation { command: "open", arguments, directory: packageRoot }
}
