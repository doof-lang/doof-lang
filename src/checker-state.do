// Mutable state shared by the Doof checker phases.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import { Diagnostic, Scope } from "./semantic"

export class CheckerState {
  result: AnalysisResult
  entry: string = ""
  entryMode: string = "executable"
  diagnostics: Diagnostic[] = []
  info: ModuleInfo | none = none
  moduleScope: Scope | none = none
}
