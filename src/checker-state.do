// Mutable state shared by the Doof checker phases.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import { Diagnostic, ResolvedType, Scope } from "./semantic"
import { FunctionDeclaration, ReturnStatement } from "./ast"

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

// Signatures of not-yet-checked functions, resolved provisionally while
// predeclaring module bindings. Graph-wide class-field preparation predeclares
// every module on each fixpoint pass, and each module check predeclares again,
// so resolve each signature once per declaration and resolving module. A
// checked function's own `resolvedType` always takes precedence over this.
export class ProvisionalSignatures {
  private let entries: Map<FunctionDeclaration, Map<string, ResolvedType>> = {}

  lookup(fn: FunctionDeclaration, modulePath: string): ResolvedType | none {
    byModule := this.entries.get(fn) else { return none }
    type_ := byModule.get(modulePath) else { return none }
    return type_
  }

  store(fn: FunctionDeclaration, modulePath: string, type_: ResolvedType): none {
    if byModule := this.entries.get(fn) {
      byModule.set(modulePath, type_)
      return
    }
    let byModule: Map<string, ResolvedType> = {}
    byModule.set(modulePath, type_)
    this.entries.set(fn, byModule)
  }
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
  provisionalSignatures: ProvisionalSignatures = ProvisionalSignatures {}
}
