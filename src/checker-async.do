// Async expression checking, async-block capture decoration, and cross-thread
// result validation.

import { AnalysisResult } from "./analyzer"
import { ActorType, ArrayResolvedType, ClassType, Diagnostic, FunctionType, InterfaceType, MapResolvedType, PromiseType, ResolvedType, ResultResolvedType, Scope, SuccessResolvedType, FailureResolvedType, SemanticSpan, SetResolvedType, StreamResolvedType, TupleResolvedType, TypeParameterType, UnionResolvedType, WeakResolvedType } from "./semantic"
import { AsyncExpression, Block, CallExpression, ClassDeclaration, Expression, Identifier, InterfaceDeclaration, MemberExpression, SourceSpan, ThisExpression } from "./ast"
import { findActorBoundaryViolation, implementationType, isActorMethodCall } from "./checker-actor-boundary"
import { collectBlockExpressions, collectExpressionTree } from "./ast-walk"
import { declarationFor, fieldDisplayName } from "./checker-symbols"
import { neverType, promiseType, substituteTypeParams, typeName, unknownType } from "./checker-types"
import { finish, typeError } from "./checker-common"
import { checkExpression } from "./checker-expressions"
import { CheckerState } from "./checker-state"
import { pushDiagnostic } from "./checker-validation"
import { checkBlock } from "./checker-statements"

class AsyncBoundaryViolation {
  reason: string
}

/** Checks 'async { ... }' blocks and 'async call(...)' worker dispatch. */
export function checkAsync(state: CheckerState, async_: AsyncExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  case async_.expression {
    block: Block -> {
      let expectedValue: ResolvedType | none = none
      if expected != none {
        case expected! {
          promise: PromiseType -> { expectedValue = promise.valueType }
          _ -> { }
        }
      }
      asyncScope := Scope {
        parent: scope,
        inValueYieldBlock: true,
        yieldExpectedType: expectedValue,
        yieldType: if expectedValue == none then unknownType() else expectedValue,
      }
      completes := checkBlock(state, block, asyncScope)
      if completes { typeError(state, "Async blocks must yield a value on every path", block.span) }
      let valueType = asyncScope.yieldType ?? unknownType()
      if !completes && valueType.kind == "unknown" { valueType = neverType() }
      violation := asyncResultViolation(state.result, valueType)
      if violation != none {
        typeError(state, "Async block result type \"" + typeName(valueType) + "\" cannot cross from the worker: " + violation!, async_.span)
      }
      return finish(state, async_, promiseType(valueType))
    }
    inner: Expression -> {
      innerType := checkExpression(state, inner, scope, none)
      actorCall := isActorMethodCall(inner)
      let isolatedCall = false
      case inner {
        call: CallExpression -> {
          isolatedCall = call.resolvedFunction != none
          if !actorCall && isolatedCall {
            for i of 0..<call.args.length {
              argumentType := call.args[i].value.resolvedType
              if argumentType == none { continue }
              violation := findActorBoundaryViolation(state.result, argumentType!)
              if violation != none {
                typeError(state,
                  "Async call argument " + string(i + 1) + " of type \"" + typeName(argumentType!) + "\" cannot cross to the worker: " + violation!.reason,
                  call.args[i].span,
                )
              }
            }
            case call.callee {
              member: MemberExpression -> {
                if member.resolvedStaticOwner == none && member.object.resolvedType != none {
                  receiverViolation := findActorBoundaryViolation(state.result, member.object.resolvedType!)
                  if receiverViolation != none {
                    typeError(state,
                      "Async call receiver of type \"" + typeName(member.object.resolvedType!) + "\" cannot cross to the worker: " + receiverViolation!.reason,
                      member.object.span,
                    )
                  }
                }
              }
              _ -> { }
            }
            resultViolation := asyncResultViolation(state.result, innerType)
            if resultViolation != none {
              typeError(state,
                "Async call result type \"" + typeName(innerType) + "\" cannot cross from the worker: " + resultViolation!,
                async_.span,
              )
            }
          }
        }
        _ -> { }
      }
      if !actorCall && !isolatedCall {
        typeError(state, "`async` requires an actor method call or an inferrably isolated function call", async_.span)
      }
      return finish(state, async_, promiseType(innerType))
    }
  }
  return unknownType()
}

export function validateAsyncBlock(result: AnalysisResult, expression: AsyncExpression, module: string, diagnostics: Diagnostic[]): none {
  case expression.expression {
    _: Expression -> { return }
    block: Block -> {
      expression.resolvedCaptureNames = []
      roots := blockExpressions(block)
      for nested of roots {
        case nested {
          identifier: Identifier -> { validateIdentifierCapture(result, expression, block, identifier, module, diagnostics) }
          this_: ThisExpression -> {
            pushDiagnostic(diagnostics, module, this_.span, "Async blocks cannot capture 'this'; copy deeply immutable values into local bindings first")
          }
          _ -> { }
        }
      }
    }
  }
}

function blockExpressions(block: Block): Expression[] {
  let roots: Expression[] = []
  collectBlockExpressions(block, roots)
  let result: Expression[] = []
  for root of roots { collectExpressionTree(root, result) }
  return result
}

function validateIdentifierCapture(result: AnalysisResult, async_: AsyncExpression, block: Block, identifier: Identifier, module: string, diagnostics: Diagnostic[]): none {
  if identifier.resolvedBinding == none { return }
  binding := identifier.resolvedBinding!
  if binding.kind == "field" || binding.kind == "method" {
    pushDiagnostic(diagnostics, module, identifier.span,
      "Async blocks cannot capture 'this' through \"" + identifier.name + "\"; copy deeply immutable values into local bindings first")
    return
  }
  if binding.symbol != none || binding.kind == "builtin" || binding.kind == "import" ||
      binding.kind == "script-global" || binding.kind == "script-arguments" { return }
  if inside(block.span, binding.span) { return }
  addCapture(async_.resolvedCaptureNames, binding.name)
  if binding.mutable {
    pushDiagnostic(diagnostics, module, identifier.span,
      "Async block capture \"" + identifier.name + "\" must come from an immutable binding")
    return
  }
  let reason: string | none = none
  boundaryViolation := findActorBoundaryViolation(result, binding.type_)
  if boundaryViolation != none { reason = boundaryViolation!.reason }
  if reason == none {
    reason = findAsyncViolation(result, binding.type_, [], [], false, false)
  }
  if reason != none {
    pushDiagnostic(diagnostics, module, identifier.span,
      "Async block capture \"" + identifier.name + "\" of type \"" + typeName(binding.type_) + "\" cannot cross to the worker: " + reason!)
  }
}

function inside(outer: SourceSpan, inner: SemanticSpan): bool {
  return inner.start.offset >= outer.start.offset && inner.end.offset <= outer.end.offset
}

function addCapture(names: string[], name: string): none {
  for existing of names { if existing == name { return } }
  names.push(name)
}

export function asyncResultViolation(result: AnalysisResult, type_: ResolvedType): string | none {
  return findAsyncViolation(result, type_, [], [], true, false)
}

// One recursive walk; capture and result policies differ only at handle leaves.
function findAsyncViolation(result: AnalysisResult, type_: ResolvedType, seen: string[], safe: string[], resultMode: bool, unbound: bool): string | none {
  case type_ {
    // Implementation walks lose the widened value's type arguments; see implementationType.
    parameter: TypeParameterType -> {
      if !unbound { return none }
      if parameter.constraint != none && parameter.constraint!.kind != "unknown" { return findAsyncViolation(result, parameter.constraint!, seen, safe, resultMode, unbound) }
      return "unbound type parameter \"" + parameter.name + "\" may hold callbacks, weak references, or streams"
    }
    // Actor and promise handles are synchronized and may be captured or yielded.
    _: ActorType -> { return none }
    _: PromiseType -> { return none }
    _: FunctionType -> { return if resultMode then "actor-affine callbacks cannot be transferred from async blocks" else "actor-affine callbacks cannot cross into async blocks" }
    _: WeakResolvedType -> { return if resultMode then "weak references cannot be transferred from async blocks" else "weak references cannot cross into async blocks" }
    _: StreamResolvedType -> { return if resultMode then "streams cannot be transferred from async blocks" else "streams cannot cross into async blocks" }
    array: ArrayResolvedType -> { return findAsyncViolation(result, array.elementType, seen, safe, resultMode, unbound) }
    map: MapResolvedType -> {
      violation := findAsyncViolation(result, map.keyType, seen, safe, resultMode, unbound)
      if violation != none { return violation }
      return findAsyncViolation(result, map.valueType, seen, safe, resultMode, unbound)
    }
    set_: SetResolvedType -> { return findAsyncViolation(result, set_.elementType, seen, safe, resultMode, unbound) }
    result_: ResultResolvedType -> {
      violation := findAsyncViolation(result, result_.valueType, seen, safe, resultMode, unbound)
      if violation != none { return violation }
      return findAsyncViolation(result, result_.errorType, seen, safe, resultMode, unbound)
    }
    success: SuccessResolvedType -> { return findAsyncViolation(result, success.valueType, seen, safe, resultMode, unbound) }
    failure: FailureResolvedType -> { return findAsyncViolation(result, failure.errorType, seen, safe, resultMode, unbound) }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        violation := findAsyncViolation(result, element, seen, safe, resultMode, unbound)
        if violation != none { return violation }
      }
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        violation := findAsyncViolation(result, member, seen, safe, resultMode, unbound)
        if violation != none { return violation }
      }
    }
    class_: ClassType -> {
      violation := findClassAsyncViolation(result, class_, seen, resultMode, safe, unbound)
      if violation != none { return violation!.reason }
    }
    interface_: InterfaceType -> {
      violation := findInterfaceAsyncViolation(result, interface_, seen, resultMode, safe, unbound)
      if violation != none { return violation!.reason }
    }
    _ -> { }
  }
  return none
}

function findClassAsyncViolation(result: AnalysisResult, type_: ClassType, seen: string[], resultMode: bool, safe: string[], unbound: bool): AsyncBoundaryViolation | none {
  key := (if unbound then "unbound-" else "") + "class:" + type_.symbol.module + ":" + typeName(type_)
  if safe.contains(key) { return none }
  if seen.contains(key) { return none }
  next := appended(seen, key)
  declaration := declarationFor(result, type_.symbol)
  if declaration == none { return none }
  case declaration! {
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if field.resolvedType == none { continue }
        effective := substituteTypeParams(field.resolvedType!, class_.typeParams, type_.typeArgs)
        reason := findAsyncViolation(result, effective, next, safe, resultMode, unbound)
        if reason != none {
          name := fieldDisplayName(field)
          return AsyncBoundaryViolation { reason: "field \"" + name + "\" cannot cross the async boundary: " + reason! }
        }
      }
    }
    _ -> { }
  }
  safe.push(key)
  return none
}

function findInterfaceAsyncViolation(result: AnalysisResult, type_: InterfaceType, seen: string[], resultMode: bool, safe: string[], unbound: bool): AsyncBoundaryViolation | none {
  key := (if unbound then "unbound-" else "") + "interface:" + type_.symbol.module + ":" + typeName(type_)
  if safe.contains(key) { return none }
  if seen.contains(key) { return none }
  next := appended(seen, key)
  declaration := declarationFor(result, type_.symbol)
  if declaration == none { return none }
  case declaration! {
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields {
        if field.resolvedType == none { continue }
        effective := substituteTypeParams(field.resolvedType!, interface_.typeParams, type_.typeArgs)
        reason := findAsyncViolation(result, effective, next, safe, resultMode, unbound)
        if reason != none { return AsyncBoundaryViolation { reason: "field \"" + field.name + "\" cannot cross the async boundary: " + reason! } }
      }
      if interface_.resolvedSymbol != none {
        for implementation of interface_.resolvedSymbol!.implementations {
          violation := findClassAsyncViolation(result, implementationType(result, type_, implementation), next, resultMode, safe, true)
          if violation != none { return AsyncBoundaryViolation { reason: "implementation \"" + implementation.name + "\" cannot cross the async boundary: " + violation!.reason } }
        }
      }
    }
    _ -> { }
  }
  safe.push(key)
  return none
}

function appended(values: string[], value: string): string[] {
  let result: string[] = []
  for item of values { result.push(item) }
  result.push(value)
  return result
}
