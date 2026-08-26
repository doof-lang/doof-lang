// Pure macOS Time Profiler invocation planning.
//
// The driver owns process execution and filesystem checks. Keeping argument
// construction here makes paths and program-argument forwarding deterministic.

import { RunInvocation } from "./run-command"

/** Plans creation of the dSYM bundle Instruments uses for source navigation. */
export function planProfileSymbols(binaryPath: string, symbolsPath: string, packageRoot: string): RunInvocation {
  return RunInvocation {
    command: "xcrun",
    arguments: ["dsymutil", binaryPath, "-o", symbolsPath],
    directory: packageRoot,
  }
}

/** Plans an xctrace Time Profiler launch for a console executable or .app bundle. */
export function planProfileCapture(
  targetPath: string,
  programArguments: string[],
  packageRoot: string,
  tracePath: string,
  timeLimit: string = "",
  consoleTarget: bool = true,
): RunInvocation {
  arguments := ["xctrace", "record", "--template", "Time Profiler", "--output", tracePath]
  if timeLimit != "" {
    arguments.push("--time-limit")
    arguments.push(timeLimit)
  }
  if consoleTarget {
    arguments.push("--target-stdin")
    arguments.push("-")
    arguments.push("--target-stdout")
    arguments.push("-")
  }
  arguments.push("--launch")
  arguments.push("--")
  arguments.push(targetPath)
  for argument of programArguments { arguments.push(argument) }
  return RunInvocation { command: "xcrun", arguments, directory: packageRoot }
}

/** Plans opening a completed trace with its registered macOS application. */
export function planProfileOpen(tracePath: string, packageRoot: string): RunInvocation {
  return RunInvocation { command: "open", arguments: [tracePath], directory: packageRoot }
}
