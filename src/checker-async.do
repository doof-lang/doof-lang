// Async-block capture decoration and cross-thread result validation.

import { AnalysisResult } from "./analyzer"
import { ActorType, ArrayResolvedType, ClassType, Diagnostic, FunctionType, InterfaceType, MapResolvedType, PromiseType, ResolvedType, ResultResolvedType, SemanticLocation, SemanticSpan, SetResolvedType, StreamResolvedType, TupleResolvedType, UnionResolvedType, WeakResolvedType } from "./semantic"
import { AsyncExpression, Block, ClassDeclaration, Expression, Identifier, InterfaceDeclaration, SourceSpan, ThisExpression } from "./ast"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { collectBlockExpressions, collectExpressionTree } from "./ast-walk"
import { declarationFor } from "./checker-symbols"
import { substituteTypeParams, typeName } from "./checker-types"

class AsyncBoundaryViolation {
  reason: string
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
    reason = findAsyncViolation(result, binding.type_, [], [], false)
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
  return findAsyncViolation(result, type_, [], [], true)
}

// One recursive walk; capture and result policies differ only at handle leaves.
function findAsyncViolation(result: AnalysisResult, type_: ResolvedType, seen: string[], safe: string[], resultMode: bool): string | none {
  case type_ {
    _: ActorType -> { if resultMode { return "Actor<T> references are persistent domains" } }
    _: PromiseType -> { if resultMode { return "Promise<T> values are asynchronous handles" } }
    _: FunctionType -> { return if resultMode then "actor-affine callbacks cannot be transferred from async blocks" else "actor-affine callbacks cannot cross into async blocks" }
    _: WeakResolvedType -> { return if resultMode then "weak references cannot be transferred from async blocks" else "weak references cannot cross into async blocks" }
    _: StreamResolvedType -> { return if resultMode then "streams cannot be transferred from async blocks" else "streams cannot cross into async blocks" }
    array: ArrayResolvedType -> { return findAsyncViolation(result, array.elementType, seen, safe, resultMode) }
    map: MapResolvedType -> {
      violation := findAsyncViolation(result, map.keyType, seen, safe, resultMode)
      if violation != none { return violation }
      return findAsyncViolation(result, map.valueType, seen, safe, resultMode)
    }
    set_: SetResolvedType -> { return findAsyncViolation(result, set_.elementType, seen, safe, resultMode) }
    result_: ResultResolvedType -> {
      violation := findAsyncViolation(result, result_.valueType, seen, safe, resultMode)
      if violation != none { return violation }
      return findAsyncViolation(result, result_.errorType, seen, safe, resultMode)
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        violation := findAsyncViolation(result, element, seen, safe, resultMode)
        if violation != none { return violation }
      }
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        violation := findAsyncViolation(result, member, seen, safe, resultMode)
        if violation != none { return violation }
      }
    }
    class_: ClassType -> {
      violation := findClassAsyncViolation(result, class_, seen, resultMode, safe)
      if violation != none { return violation.reason }
    }
    interface_: InterfaceType -> {
      violation := findInterfaceAsyncViolation(result, interface_, seen, resultMode, safe)
      if violation != none { return violation.reason }
    }
    _ -> { }
  }
  return none
}

function findClassAsyncViolation(result: AnalysisResult, type_: ClassType, seen: string[], resultMode: bool, safe: string[]): AsyncBoundaryViolation | none {
  key := "class:" + type_.symbol.module + ":" + typeName(type_)
  if contains(safe, key) { return none }
  if contains(seen, key) { return none }
  next := appended(seen, key)
  declaration := declarationFor(result, type_.symbol)
  if declaration == none { return none }
  case declaration! {
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if field.resolvedType == none { continue }
        effective := substituteTypeParams(field.resolvedType!, class_.typeParams, type_.typeArgs)
        reason := findAsyncViolation(result, effective, next, safe, resultMode)
        if reason != none {
          name := if field.names.length == 0 then "<field>" else field.names[0]
          return AsyncBoundaryViolation { reason: "field \"" + name + "\" cannot cross the async boundary: " + reason! }
        }
      }
    }
    _ -> { }
  }
  safe.push(key)
  return none
}

function findInterfaceAsyncViolation(result: AnalysisResult, type_: InterfaceType, seen: string[], resultMode: bool, safe: string[]): AsyncBoundaryViolation | none {
  key := "interface:" + type_.symbol.module + ":" + typeName(type_)
  if contains(safe, key) { return none }
  if contains(seen, key) { return none }
  next := appended(seen, key)
  declaration := declarationFor(result, type_.symbol)
  if declaration == none { return none }
  case declaration! {
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields {
        if field.resolvedType == none { continue }
        effective := substituteTypeParams(field.resolvedType!, interface_.typeParams, type_.typeArgs)
        reason := findAsyncViolation(result, effective, next, safe, resultMode)
        if reason != none { return AsyncBoundaryViolation { reason: "field \"" + field.name + "\" cannot cross the async boundary: " + reason! } }
      }
      if interface_.resolvedSymbol != none {
        for implementation of interface_.resolvedSymbol!.implementations {
          violation := findClassAsyncViolation(result, ClassType { name: implementation.name, symbol: implementation }, next, resultMode, safe)
          if violation != none { return AsyncBoundaryViolation { reason: "implementation \"" + implementation.name + "\" cannot cross the async boundary: " + violation!.reason } }
        }
      }
    }
    _ -> { }
  }
  safe.push(key)
  return none
}

function contains(values: string[], value: string): bool {
  for item of values { if item == value { return true } }
  return false
}

function appended(values: string[], value: string): string[] {
  let result: string[] = []
  for item of values { result.push(item) }
  result.push(value)
  return result
}

function semanticSpan(span: SourceSpan): SemanticSpan {
  return SemanticSpan {
    start: SemanticLocation { line: span.start.line, column: span.start.column, offset: span.start.offset },
    end: SemanticLocation { line: span.end.line, column: span.end.column, offset: span.end.offset },
  }
}

function pushDiagnostic(diagnostics: Diagnostic[], module: string, span: SourceSpan, message: string): none {
  diagnostics.push(Diagnostic { severity: "error", message, span: semanticSpan(span), module })
}
