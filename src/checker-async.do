// Async-block capture decoration and cross-thread result validation.

import { AnalysisResult } from "./analyzer"
import {
  ActorType, ArrayResolvedType, Binding, ClassType, Diagnostic, FunctionType, InterfaceType,
  MapResolvedType, PromiseType, ResolvedType, ResultResolvedType, SemanticLocation, SemanticSpan,
  SetResolvedType, StreamResolvedType, TupleResolvedType, UnionResolvedType, WeakResolvedType,
} from "./semantic"
import {
  AsyncExpression, Block, ClassDeclaration, ExportDeclaration, Expression, Identifier,
  InterfaceDeclaration, SourceSpan, Statement, ThisExpression,
} from "./ast"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { collectBlockExpressions, collectNestedExpressions } from "./checker-actor-lifecycle"
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
  for root of roots { collectTree(root, result) }
  return result
}

function collectTree(expression: Expression, result: Expression[]): none {
  result.push(expression)
  let nested: Expression[] = []
  collectNestedExpressions(expression, nested)
  for child of nested { collectTree(child, result) }
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
    affineViolation := findAsyncAffineViolation(result, binding.type_, [], [])
    if affineViolation != none { reason = affineViolation!.reason }
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

function findAsyncAffineViolation(result: AnalysisResult, type_: ResolvedType, seen: string[], safe: string[]): AsyncBoundaryViolation | none {
  case type_ {
    _: FunctionType -> { return AsyncBoundaryViolation { reason: "actor-affine callbacks cannot cross into async blocks" } }
    _: WeakResolvedType -> { return AsyncBoundaryViolation { reason: "weak references cannot cross into async blocks" } }
    _: StreamResolvedType -> { return AsyncBoundaryViolation { reason: "streams cannot cross into async blocks" } }
    array: ArrayResolvedType -> { return findAsyncAffineViolation(result, array.elementType, seen, safe) }
    map: MapResolvedType -> {
      violation := findAsyncAffineViolation(result, map.keyType, seen, safe)
      if violation != none { return violation }
      return findAsyncAffineViolation(result, map.valueType, seen, safe)
    }
    set_: SetResolvedType -> { return findAsyncAffineViolation(result, set_.elementType, seen, safe) }
    result_: ResultResolvedType -> {
      violation := findAsyncAffineViolation(result, result_.valueType, seen, safe)
      if violation != none { return violation }
      return findAsyncAffineViolation(result, result_.errorType, seen, safe)
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        violation := findAsyncAffineViolation(result, element, seen, safe)
        if violation != none { return violation }
      }
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        violation := findAsyncAffineViolation(result, member, seen, safe)
        if violation != none { return violation }
      }
    }
    class_: ClassType -> { return findClassAsyncViolation(result, class_, seen, false, safe) }
    interface_: InterfaceType -> { return findInterfaceAsyncViolation(result, interface_, seen, false, safe) }
    _ -> { }
  }
  return none
}

export function asyncResultViolation(result: AnalysisResult, type_: ResolvedType): string | none {
  return findAsyncResultViolation(result, type_, [], [])
}

function findAsyncResultViolation(result: AnalysisResult, type_: ResolvedType, seen: string[], safe: string[]): string | none {
  case type_ {
    _: ActorType -> { return "Actor<T> references are persistent domains" }
    _: PromiseType -> { return "Promise<T> values are asynchronous handles" }
    _: FunctionType -> { return "actor-affine callbacks cannot be transferred from async blocks" }
    _: WeakResolvedType -> { return "weak references cannot be transferred from async blocks" }
    _: StreamResolvedType -> { return "streams cannot be transferred from async blocks" }
    array: ArrayResolvedType -> { return findAsyncResultViolation(result, array.elementType, seen, safe) }
    map: MapResolvedType -> {
      violation := findAsyncResultViolation(result, map.keyType, seen, safe)
      if violation != none { return violation }
      return findAsyncResultViolation(result, map.valueType, seen, safe)
    }
    set_: SetResolvedType -> { return findAsyncResultViolation(result, set_.elementType, seen, safe) }
    result_: ResultResolvedType -> {
      violation := findAsyncResultViolation(result, result_.valueType, seen, safe)
      if violation != none { return violation }
      return findAsyncResultViolation(result, result_.errorType, seen, safe)
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        violation := findAsyncResultViolation(result, element, seen, safe)
        if violation != none { return violation }
      }
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        violation := findAsyncResultViolation(result, member, seen, safe)
        if violation != none { return violation }
      }
    }
    class_: ClassType -> {
      violation := findClassAsyncViolation(result, class_, seen, true, safe)
      if violation != none { return violation.reason }
    }
    interface_: InterfaceType -> {
      violation := findInterfaceAsyncViolation(result, interface_, seen, true, safe)
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
        let reason: string | none = none
        if resultMode { reason = findAsyncResultViolation(result, effective, next, safe) }
        else {
          violation := findAsyncAffineViolation(result, effective, next, safe)
          if violation != none { reason = violation!.reason }
        }
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
        let reason: string | none = none
        if resultMode { reason = findAsyncResultViolation(result, effective, next, safe) }
        else {
          violation := findAsyncAffineViolation(result, effective, next, safe)
          if violation != none { reason = violation!.reason }
        }
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
