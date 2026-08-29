// State-aware diagnostics and expression decoration helpers.

import {
  Binding, Diagnostic, NeverType, ResolvedType,
} from "./semantic"
import { Expression, FunctionDeclaration, SourceSpan } from "./ast"
import { typeName } from "./checker-types"
import { CheckerState } from "./checker-state"
import { optionalResolvedType } from "./checker-symbols"
import { checkerSemanticSpan } from "./checker-validation"

export function finish(state: CheckerState, expression: Expression, resolvedType: ResolvedType): ResolvedType { expression.resolvedType = optionalResolvedType(resolvedType); return resolvedType }
export function typeError(state: CheckerState, message: string, span: SourceSpan): none { state.diagnostics.push(Diagnostic { severity: "error", message, span: checkerSemanticSpan(span), module: state.info!.path }) }
export function deprecatedNoneAlias(state: CheckerState, spelling: string, span: SourceSpan, module: string = ""): none {
  state.diagnostics.push(Diagnostic {
    severity: "warning",
    message: "'" + spelling + "' is deprecated; replace it with 'none'",
    span: checkerSemanticSpan(span),
    module: if module == "" then state.info!.path else module,
    replacement: "none",
  })
}
export function deprecatedBuildReadonly(state: CheckerState, span: SourceSpan): none {
  state.diagnostics.push(Diagnostic {
    severity: "warning",
    message: "'buildReadonly' is deprecated; replace it with 'drainToReadonly'",
    span: checkerSemanticSpan(span),
    module: state.info!.path,
    replacement: "drainToReadonly",
  })
}
export function deprecatedClassMethodFunction(state: CheckerState, fn: FunctionDeclaration): none {
  if fn.legacyMethodFunctionSpan == none { return }
  state.diagnostics.push(Diagnostic {
    severity: "warning",
    message: "'function' on class methods is deprecated; declare '" + fn.name + "(...)' without the keyword",
    span: checkerSemanticSpan(fn.legacyMethodFunctionSpan!),
    module: state.info!.path,
    replacement: fn.name,
  })
}
export function validateAssignmentBinding(state: CheckerState, binding: Binding, span: SourceSpan): none {
  if binding.kind != "field" {
    if !binding.mutable { typeError(state, "Cannot assign to immutable binding '" + binding.name + "'", span) }
    return
  }
  if binding.mutable { return }
  let suffix = ""
  if binding.fieldMode == "implicit" { suffix = "; declare it with 'let' to allow reassignment" }
  typeError(state, "Cannot assign to immutable field '" + binding.fieldOwner + "." + binding.name + "'" + suffix, span)
}
export function requireBool(state: CheckerState, resolvedType: ResolvedType, span: SourceSpan): none {
  case resolvedType {
    _: NeverType -> { return }
    _ -> { }
  }
  if typeName(resolvedType) != "bool" && typeName(resolvedType) != "unknown" { typeError(state, "Expected bool, got " + typeName(resolvedType), span) }
}
