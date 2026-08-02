// Mutable state shared by the Doof checker phases.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import { Diagnostic, Scope } from "./semantic"

export class CheckerState {
  result: AnalysisResult
  entry: string = ""
  entryMode: string = "executable"
  let diagnostics: Diagnostic[] = []
  let info: ModuleInfo | none = none
  let moduleScope: Scope | none = none
  warnedImplicitFieldDeclarations: string[] = []
}
