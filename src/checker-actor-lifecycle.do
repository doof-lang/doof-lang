// Conservative straight-line use-after-retire diagnostics.
//
// Runtime aliases remain guarded by Actor<T>'s lifecycle state. This pass adds
// an earlier diagnostic when a later statement reuses the same resolved
// lexical binding after `retire binding`.

import { Expression, Identifier, RetireExpression, SourceSpan, Statement } from "./ast"
import { ActorType, Binding, Diagnostic, SemanticLocation, SemanticSpan } from "./semantic"
import { collectNestedExpressions, collectStatementExpressions } from "./ast-walk"

export function reportRetiredActorUses(statement: Statement, retired: Binding[], module: string, diagnostics: Diagnostic[]): none {
  if retired.length == 0 { return }
  let identifiers: Identifier[] = []
  collectStatementIdentifiers(statement, identifiers)
  for identifier of identifiers {
    if identifier.resolvedBinding == none { continue }
    for binding of retired {
      if sameBinding(identifier.resolvedBinding!, binding) {
        diagnostics.push(Diagnostic {
          severity: "error",
          message: "Cannot use actor binding \"" + identifier.name + "\" after it has been retired",
          span: semanticSpan(identifier.span),
          module,
        })
      }
    }
  }
}

export function collectRetiredActorBindings(statement: Statement, retired: Binding[]): none {
  let expressions: Expression[] = []
  collectStatementExpressions(statement, expressions)
  for expression of expressions {
    case expression {
      retire_: RetireExpression -> {
        case retire_.actor {
          identifier: Identifier -> {
            if identifier.resolvedBinding == none || identifier.resolvedType == none { continue }
            case identifier.resolvedType! {
              _: ActorType -> { addBinding(retired, identifier.resolvedBinding!) }
              _ -> { }
            }
          }
          _ -> { }
        }
      }
      _ -> { }
    }
  }
}

function collectStatementIdentifiers(statement: Statement, result: Identifier[]): none {
  let expressions: Expression[] = []
  collectStatementExpressions(statement, expressions)
  for expression of expressions { collectExpressionIdentifiers(expression, result) }
}

function collectExpressionIdentifiers(expression: Expression, result: Identifier[]): none {
  case expression {
    identifier: Identifier -> { result.push(identifier) }
    _ -> { }
  }
  let nested: Expression[] = []
  collectNestedExpressions(expression, nested)
  for child of nested { collectExpressionIdentifiers(child, result) }
}

function sameBinding(left: Binding, right: Binding): bool {
  return left.name == right.name && left.span.start.offset == right.span.start.offset && left.span.end.offset == right.span.end.offset
}

function addBinding(values: Binding[], value: Binding): none {
  for existing of values { if sameBinding(existing, value) { return } }
  values.push(value)
}

function semanticSpan(span: SourceSpan): SemanticSpan {
  return SemanticSpan {
    start: SemanticLocation { line: span.start.line, column: span.start.column, offset: span.start.offset },
    end: SemanticLocation { line: span.end.line, column: span.end.column, offset: span.end.offset },
  }
}
