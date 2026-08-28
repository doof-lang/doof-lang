// Host-side planning for executing Wasm test commands.
//
// The Apple implementation is a small JavaScriptCore executable materialized
// by driver.do. Keeping invocation and compilation planning pure here avoids
// teaching the general native command runner about JavaScriptCore or WASI.

export class WasmTestRunnerPlan {
  command: string
  arguments: string[] = []
}

/** Plans compilation of the bundled Swift JavaScriptCore host. */
export function planAppleWasmTestRunnerBuild(sourcePath: string, outputPath: string): WasmTestRunnerPlan {
  return WasmTestRunnerPlan {
    command: "xcrun",
    arguments: ["swiftc", sourcePath, "-framework", "JavaScriptCore", "-o", outputPath],
  }
}

/** Plans one fresh JavaScriptCore process and Wasm instance for a test id. */
export function planAppleWasmTestRun(
  runnerPath: string,
  modulePath: string,
  testId: string,
): WasmTestRunnerPlan {
  return WasmTestRunnerPlan { command: runnerPath, arguments: [modulePath, testId] }
}
