// Type-argument inference for generic calls written without type arguments.
//
// Evidence is gathered in precedence order, and each stage only fills type
// parameters that earlier stages left open:
//
//   1. argument values other than lambdas;
//   2. lambdas with a declared return type, which state their result as
//      explicitly as a value does;
//   3. the call's contextual result type, such as `r: double[] := ...`;
//   4. the bodies of lambdas without a declared return type.
//
// A lambda checked after its result parameter is fixed converts its body to
// that type instead of redefining it, so explicit type arguments, declared
// lambda returns, and contextual result types all constrain a call the same
// way. Disagreement between two explicit sources is reported by the ordinary
// argument or assignment check.
//
// Arguments are checked speculatively here and rechecked against the
// substituted signature by the caller, so diagnostics from a successful
// inference are discarded rather than reported twice.
import { CallArgument, DotShorthand, Expression, LambdaExpression } from "./ast"
import { FunctionType, ResolvedType, Scope, TypeParameterType } from "./semantic"
import { functionType, sameType, substituteTypeParams, typeParameter, unknownType } from "./checker-types"
import { CheckerState } from "./checker-state"
import { typeError } from "./checker-common"
import { checkExpression } from "./checker-expressions"
import { functionParameterIndex } from "./checker-symbols"
import { inferTypeArgument } from "./checker-generics"
import { isAssignableWithInterfaces } from "./checker-interfaces"

class TypeArgumentEvidence {
  typeParams: string[]
  let found: (ResolvedType | none)[] = []
  let consistent: bool = true
}

/** Returns the inferred type arguments, or none when any stays open or conflicts. */
export function inferCallTypeArguments(state: CheckerState, args: CallArgument[], signature: FunctionType, scope: Scope, expected: ResolvedType | none): ResolvedType[] | none {
  diagnosticMark := state.diagnostics.length
  evidence := TypeArgumentEvidence { typeParams: signature.typeParams }
  for _ of signature.typeParams { evidence.found.push(none) }

  for stage of 1..4 {
    if stage == 3 {
      if expected != none { recordEvidence(state, evidence, signature.returnType, expected!, true) }
      continue
    }
    for i of 0..<args.length {
      parameterIndex := if args[i].name == none then i else functionParameterIndex(signature.params, args[i].name!)
      if parameterIndex < 0 || parameterIndex >= signature.params.length { continue }
      parameterType := signature.params[parameterIndex].type_
      let argumentExpected: ResolvedType | none = none
      case args[i].value {
        lambda: LambdaExpression -> {
          if stage != (if lambda.returnType == none then 4 else 2) { continue }
          argumentExpected = lambdaInferenceExpected(parameterType, evidence)
        }
        _: DotShorthand -> {
          if stage != 1 { continue }
          argumentExpected = genericInferenceExpected(parameterType, signature.typeParams)
          if argumentExpected == none { continue }
        }
        _ -> {
          if stage != 1 { continue }
          argumentExpected = genericInferenceExpected(parameterType, signature.typeParams)
          // A named function or method may itself be generic; like a lambda it
          // instantiates from the callback parameters known so far.
          if argumentExpected == none && parameterType.kind == "function" && namesCallable(args[i].value) {
            argumentExpected = lambdaInferenceExpected(parameterType, evidence)
          }
        }
      }
      actual := checkExpression(state, args[i].value, scope, argumentExpected)
      recordEvidence(state, evidence, parameterType, actual, false)
    }
  }

  let inferred: ResolvedType[] = []
  for found of evidence.found {
    if found == none { return none }
    inferred.push(found!)
  }
  if !evidence.consistent { return none }
  while state.diagnostics.length > diagnosticMark { ignored := state.diagnostics.pop()! }
  // Trailing lambdas are statement blocks for none-returning callbacks; one
  // cannot be what determines a generic callback's result.
  for i of 0..<args.length {
    case args[i].value {
      lambda: LambdaExpression -> {
        if lambda.trailing && callbackResultIsGeneric(signature, args, i) {
          typeError(state, "Trailing lambdas require a callback returning none; use an explicit lambda such as '=> ...' instead", lambda.span)
        }
      }
      _ -> { }
    }
  }
  return inferred
}

function namesCallable(expression: Expression): bool {
  return expression.kind == "identifier" || expression.kind == "member-expression"
}

function callbackResultIsGeneric(signature: FunctionType, args: CallArgument[], argumentIndex: int): bool {
  parameterIndex := if args[argumentIndex].name == none then argumentIndex else functionParameterIndex(signature.params, args[argumentIndex].name!)
  if parameterIndex < 0 || parameterIndex >= signature.params.length { return false }
  case signature.params[parameterIndex].type_ {
    callback: FunctionType -> { return genericInferenceExpected(callback.returnType, signature.typeParams) == none }
    _ -> { return false }
  }
}

/**
 * Concrete parts of a generic signature remain valid contextual types during
 * inference. Expressions that depend on a type parameter are checked after
 * substitution; a direct dot-shorthand can therefore learn that type from a
 * sibling argument without producing an early no-context diagnostic.
 */
export function genericInferenceExpected(pattern: ResolvedType, typeParams: string[]): ResolvedType | none {
  let unknownArguments: ResolvedType[] = []
  for _ of typeParams { unknownArguments.push(unknownType()) }
  substituted := substituteTypeParams(pattern, typeParams, unknownArguments)
  if sameType(pattern, substituted) { return pattern }
  return none
}

// A lambda sees the parameters inferred so far. A callback result that still
// depends on an open type parameter is left unknown so the body infers it.
function lambdaInferenceExpected(parameterType: ResolvedType, evidence: TypeArgumentEvidence): ResolvedType {
  let known: ResolvedType[] = []
  for i of 0..<evidence.typeParams.length { known.push(evidence.found[i] ?? typeParameter(evidence.typeParams[i])) }
  partial := substituteTypeParams(parameterType, evidence.typeParams, known)
  case partial {
    callback: FunctionType -> {
      if genericInferenceExpected(callback.returnType, openTypeParams(evidence)) == none {
        return functionType(callback.params, unknownType())
      }
    }
    _ -> { }
  }
  return partial
}

function openTypeParams(evidence: TypeArgumentEvidence): string[] {
  let result: string[] = []
  for i of 0..<evidence.typeParams.length { if evidence.found[i] == none { result.push(evidence.typeParams[i]) } }
  return result
}

// Contextual evidence only fills open parameters; argument evidence merges
// with earlier findings, widening to the more general of two compatible types.
function recordEvidence(state: CheckerState, evidence: TypeArgumentEvidence, pattern: ResolvedType, actual: ResolvedType, contextual: bool): none {
  for i of 0..<evidence.typeParams.length {
    name := evidence.typeParams[i]
    candidate := inferTypeArgument(pattern, actual, name)
    if candidate == none || (contextual && candidate!.kind == "unknown") { continue }
    current := evidence.found[i]
    if current == none { evidence.found[i] = candidate; continue }
    if contextual { continue }
    candidateIsSelf := isTypeParameterNamed(candidate!, name)
    if candidateIsSelf { continue }
    if isTypeParameterNamed(current!, name) { evidence.found[i] = candidate }
    else if sameType(current!, candidate!) || isAssignableWithInterfaces(state.result, candidate!, current!) { }
    else if isAssignableWithInterfaces(state.result, current!, candidate!) { evidence.found[i] = candidate }
    else { evidence.consistent = false }
  }
}

function isTypeParameterNamed(type_: ResolvedType, name: string): bool {
  case type_ {
    parameter: TypeParameterType -> { return parameter.name == name }
    _ -> { return false }
  }
}
