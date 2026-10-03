// Mutable state shared by the Doof checker phases.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import { Diagnostic, ResolvedType, Scope } from "./semantic"
import { ReturnStatement } from "./ast"

export class LambdaReturnObservation {
  statement: ReturnStatement
  type_: ResolvedType
  reachable: bool
}

export class LambdaReturnInference {
  scope: Scope
  returns: LambdaReturnObservation[] = []
  let reachable: bool = true
}

export class CheckerState {
  let editorMode: bool = false
  result: AnalysisResult
  entry: string = ""
  entryMode: string = "executable"
  let diagnostics: Diagnostic[] = []
  let info: ModuleInfo | none = none
  let moduleScope: Scope | none = none
  let allowsCaller: bool = false
  let lambdaReturns: LambdaReturnInference | none = none
  // Set by call checking for exactly the next checked expression: its callee.
  // A generic callee is instantiated by the call, not as a function value.
  let checkingCallee: bool = false
}
