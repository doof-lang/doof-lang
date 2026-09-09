// Shared, versioned launch contract. No filesystem or process operations here.
import { RunInvocation } from "./run-command"

export class DebugLaunch {
  version: int = 1
  executable: string
  source: string
  directory: string
  symbols: string
  arguments: string[] = []
}

export function debugTargetError(host: string, target: string): string {
  if host != "macos" { return "doof debug is supported only on macOS" }
  if target == "wasm" || target == "ios-app" {
    return "doof debug supports native console executables and macOS applications"
  }
  return ""
}

export function debugLaunchError(launch: DebugLaunch): string {
  if launch.version != 1 { return "Unsupported debugger launch version; reinstall the matching Doof toolchain" }
  for path of [launch.executable, launch.source, launch.directory, launch.symbols] {
    if !path.startsWith("/") { return "Debugger launch paths must be absolute" }
  }
  return ""
}

export function planDebuggerRun(app: string, descriptor: string, directory: string): RunInvocation {
  // Execute the bundle's binary directly so the user's environment is inherited.
  // NSApplication still owns a standalone native application and Dock entry.
  return RunInvocation {
    command: app + "/Contents/MacOS/DoofDebugger",
    arguments: [descriptor], directory,
  }
}
