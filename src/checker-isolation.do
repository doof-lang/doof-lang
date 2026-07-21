// Transitive mutable-global effect analysis for isolated and actor-dispatched code.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  ActorType, Binding, Diagnostic, InterfaceType, ResolvedType, SemanticLocation, SemanticSpan,
} from "./semantic"
import {
  ActorCreationExpression, Block, CallExpression, ClassDeclaration, ConstDeclaration,
  ExportDeclaration, Expression, FunctionDeclaration, Identifier, ImmutableBinding,
  InterfaceDeclaration, MemberExpression, ReadonlyDeclaration, SourceSpan, Statement,
} from "./ast"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import {
  collectBlockExpressions, collectNestedExpressions, collectStatementExpressions,
} from "./checker-actor-lifecycle"
import { declarationFor } from "./checker-symbols"

export class IsolationReason {
  kind: string
  name: string
  span: SourceSpan
}

class IsolationCall {
  declaration: FunctionDeclaration
  span: SourceSpan
}

class IsolationNode {
  declaration: FunctionDeclaration
  module: string
  owner: string = ""
  calls: IsolationCall[] = []
  directReason: IsolationReason | none = none
  reason: IsolationReason | none = none
}

class IsolationGraph {
  nodes: IsolationNode[] = []
}

function unwrapExport(statement: Statement): Statement {
  case statement {
    export_: ExportDeclaration -> { return export_.declaration }
    _ -> { return statement }
  }
}

function collectGraph(result: AnalysisResult): IsolationGraph {
  graph := IsolationGraph {}
  for module of result.modules {
    for raw of module.program.statements {
      case unwrapExport(raw) {
        fn: FunctionDeclaration -> { graph.nodes.push(IsolationNode { declaration: fn, module: module.path }) }
        class_: ClassDeclaration -> {
          for method of class_.methods {
            graph.nodes.push(IsolationNode { declaration: method, module: module.path, owner: class_.name })
          }
        }
        _ -> { }
      }
    }
  }
  return graph
}

function findModule(result: AnalysisResult, path: string): ModuleInfo | none {
  for module of result.modules { if module.path == path { return module } }
  return none
}

function sameSpan(left: SourceSpan, right: SemanticSpan): bool {
  return left.start.offset == right.start.offset && left.end.offset == right.end.offset
}

function moduleValueDeclaration(result: AnalysisResult, binding: Binding): Statement | none {
  if binding.symbol != none && (binding.symbol!.kind == "const" || binding.symbol!.kind == "readonly") {
    return declarationFor(result, binding.symbol!)
  }
  module := findModule(result, binding.module)
  if module == none { return none }
  for raw of module!.program.statements {
    statement := unwrapExport(raw)
    case statement {
      value: ConstDeclaration -> { if sameSpan(value.span, binding.span) { return value } }
      value: ReadonlyDeclaration -> { if sameSpan(value.span, binding.span) { return value } }
      value: ImmutableBinding -> { if sameSpan(value.span, binding.span) { return value } }
      _ -> { }
    }
  }
  return none
}

function mutableModuleReason(result: AnalysisResult, expression: Expression): IsolationReason | none {
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding == none { return none }
      declaration := moduleValueDeclaration(result, identifier.resolvedBinding!)
      if declaration == none { return none }
      case declaration! {
        _: ReadonlyDeclaration -> { return none }
        _: ConstDeclaration -> { }
        _: ImmutableBinding -> { }
        _ -> { return none }
      }
      violation := findActorBoundaryViolation(result, identifier.resolvedBinding!.type_)
      if violation != none {
        return IsolationReason { kind: "module", name: identifier.name, span: identifier.span }
      }
    }
    _ -> { }
  }
  return none
}

function mutableStaticReason(expression: Expression): IsolationReason | none {
  case expression {
    member: MemberExpression -> {
      if member.resolvedStaticOwner == none { return none }
      for field of member.resolvedStaticOwner!.fields {
        if !field.static_ || field.readonly_ { continue }
        for name of field.names {
          if name == member.property {
            return IsolationReason {
              kind: "static",
              name: member.resolvedStaticOwner!.name + "." + member.property,
              span: member.span,
            }
          }
        }
      }
    }
    _ -> { }
  }
  return none
}

function allExpressions(roots: Expression[]): Expression[] {
  let result: Expression[] = []
  for root of roots { collectExpressionTree(root, result) }
  return result
}

function collectExpressionTree(expression: Expression, result: Expression[]): none {
  result.push(expression)
  let nested: Expression[] = []
  collectNestedExpressions(expression, nested)
  for child of nested { collectExpressionTree(child, result) }
}

function functionExpressions(fn: FunctionDeclaration): Expression[] {
  let roots: Expression[] = []
  for parameter of fn.params { if parameter.defaultValue != none { roots.push(parameter.defaultValue!) } }
  case fn.body {
    block: Block -> { collectBlockExpressions(block, roots) }
    expression: Expression -> { roots.push(expression) }
  }
  return allExpressions(roots)
}

function nodeForDeclaration(graph: IsolationGraph, declaration: FunctionDeclaration): IsolationNode | none {
  for node of graph.nodes { if node.declaration == declaration { return node } }
  return none
}

function nodesForDeclaration(result: AnalysisResult, graph: IsolationGraph, declaration: FunctionDeclaration): IsolationNode[] {
  direct := nodeForDeclaration(graph, declaration)
  if direct != none { return [direct!] }
  let targets: IsolationNode[] = []
  for module of result.modules {
    for raw of module.program.statements {
      case unwrapExport(raw) {
        interface_: InterfaceDeclaration -> {
          let ownsMethod = false
          for method of interface_.methods {
            if method.name == declaration.name && method.span.start.offset == declaration.span.start.offset && method.span.end.offset == declaration.span.end.offset {
              ownsMethod = true
            }
          }
          if !ownsMethod || interface_.resolvedSymbol == none { continue }
          for implementation of interface_.resolvedSymbol!.implementations {
            candidate := declarationFor(result, implementation)
            if candidate == none { continue }
            case candidate! {
              class_: ClassDeclaration -> {
                for method of class_.methods {
                  if method.name == declaration.name && method.static_ == declaration.static_ {
                    node := nodeForDeclaration(graph, method)
                    if node != none { targets.push(node!) }
                  }
                }
              }
              _ -> { }
            }
          }
        }
        _ -> { }
      }
    }
  }
  return targets
}

function callDeclaration(result: AnalysisResult, call: CallExpression): FunctionDeclaration | none {
  if call.resolvedFunction != none { return call.resolvedFunction }
  case call.callee {
    member: MemberExpression -> {
      if member.object.resolvedType == none { return none }
      case member.object.resolvedType! {
        interface_: InterfaceType -> {
          declaration := declarationFor(result, interface_.symbol)
          if declaration == none { return none }
          case declaration! {
            interfaceDeclaration: InterfaceDeclaration -> {
              for method of interfaceDeclaration.methods { if method.name == member.property { return method } }
            }
            _ -> { }
          }
        }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}

function analyzeNode(result: AnalysisResult, graph: IsolationGraph, node: IsolationNode): none {
  if node.declaration.bodyless && !node.declaration.isolated_ {
    node.directReason = IsolationReason { kind: "bodyless", name: node.declaration.name, span: node.declaration.span }
    return
  }
  for expression of functionExpressions(node.declaration) {
    if node.directReason == none {
      node.directReason = mutableModuleReason(result, expression)
      if node.directReason == none { node.directReason = mutableStaticReason(expression) }
    }
    case expression {
      call: CallExpression -> {
        declaration := callDeclaration(result, call)
        if declaration != none {
          node.calls.push(IsolationCall { declaration: declaration!, span: call.span })
        }
      }
      _ -> { }
    }
  }
}

function inferIsolation(result: AnalysisResult, graph: IsolationGraph): none {
  for node of graph.nodes {
    analyzeNode(result, graph, node)
    node.reason = node.directReason
  }
  let changed = true
  while changed {
    changed = false
    for node of graph.nodes {
      if node.reason != none { continue }
      for call of node.calls {
        for target of nodesForDeclaration(result, graph, call.declaration) {
          if target.reason != none {
            node.reason = IsolationReason { kind: "call", name: target.declaration.name, span: call.span }
            changed = true
            break
          }
        }
        if node.reason != none { break }
      }
    }
  }
  for node of graph.nodes { node.declaration.resolvedIsolated = node.reason == none }
}

function reasonText(reason: IsolationReason): string {
  if reason.kind == "module" { return "accesses mutable module binding \"" + reason.name + "\"" }
  if reason.kind == "static" { return "accesses mutable static field \"" + reason.name + "\"" }
  if reason.kind == "call" { return "calls non-isolated function \"" + reason.name + "\"" }
  return "uses bodyless function \"" + reason.name + "\" without an isolated contract"
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

function probeReason(result: AnalysisResult, graph: IsolationGraph, expression: Expression): IsolationReason | none {
  for nested of allExpressions([expression]) {
    let reason = mutableModuleReason(result, nested)
    if reason == none { reason = mutableStaticReason(nested) }
    if reason != none { return reason }
    case nested {
      call: CallExpression -> {
        declaration := callDeclaration(result, call)
        if declaration != none {
          for target of nodesForDeclaration(result, graph, declaration!) {
            if target.reason != none {
              return IsolationReason { kind: "call", name: target.declaration.name, span: call.span }
            }
          }
        }
      }
      _ -> { }
    }
  }
  return none
}

function actorConstructionReason(result: AnalysisResult, graph: IsolationGraph, actor: ActorCreationExpression): IsolationReason | none {
  if actor.resolvedType == none { return none }
  let class_: ClassDeclaration | none = none
  case actor.resolvedType! {
    actorType_: ActorType -> {
      declaration := declarationFor(result, actorType_.innerClass.symbol)
      if declaration != none {
        case declaration! {
          resolved: ClassDeclaration -> { class_ = resolved }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  if class_ == none { return none }
  for method of class_!.methods {
    if method.static_ && method.name == "constructor" {
      node := nodeForDeclaration(graph, method)
      if node != none && node!.reason != none {
        return IsolationReason { kind: "call", name: method.name, span: actor.span }
      }
      return none
    }
  }
  let positionalIndex = 0
  for field of class_!.fields {
    if field.static_ { continue }
    if positionalIndex >= actor.args.length && field.defaultValue != none {
      reason := probeReason(result, graph, field.defaultValue!)
      if reason != none { return reason }
    }
    positionalIndex = positionalIndex + 1
  }
  return none
}

function moduleExpressions(module: ModuleInfo): Expression[] {
  let roots: Expression[] = []
  for raw of module.program.statements {
    statement := unwrapExport(raw)
    case statement {
      fn: FunctionDeclaration -> {
        for expression of functionExpressions(fn) { roots.push(expression) }
      }
      class_: ClassDeclaration -> {
        for field of class_.fields { if field.defaultValue != none { roots.push(field.defaultValue!) } }
        for method of class_.methods {
          for expression of functionExpressions(method) { roots.push(expression) }
        }
      }
      _ -> { collectStatementExpressions(statement, roots) }
    }
  }
  return allExpressions(roots)
}

export function validateIsolationEffects(result: AnalysisResult, module: ModuleInfo, diagnostics: Diagnostic[]): none {
  graph := collectGraph(result)
  inferIsolation(result, graph)

  for node of graph.nodes {
    if node.module != module.path || !node.declaration.isolated_ || node.reason == none { continue }
    owner := if node.owner == "" then "function \"" + node.declaration.name + "\"" else "method \"" + node.owner + "." + node.declaration.name + "\""
    message := if node.reason!.kind == "call"
      then "Isolated " + owner + " cannot call non-isolated function \"" + node.reason!.name + "\""
      else "Isolated " + owner + " is not isolated: " + reasonText(node.reason!)
    pushDiagnostic(diagnostics, module.path, node.reason!.span, message)
  }

  for expression of moduleExpressions(module) {
    case expression {
      call: CallExpression -> {
        case call.callee {
          member: MemberExpression -> {
            if member.object.resolvedType != none {
              case member.object.resolvedType! {
                _: ActorType -> {
                  if call.resolvedFunction != none {
                    target := nodeForDeclaration(graph, call.resolvedFunction!)
                    if target != none && target!.reason != none {
                      pushDiagnostic(diagnostics, module.path, call.span,
                        "Actor method \"" + target!.declaration.name + "\" is not isolated: " + reasonText(target!.reason!))
                    }
                  }
                }
                _ -> { }
              }
            }
          }
          _ -> { }
        }
      }
      actor: ActorCreationExpression -> {
        reason := actorConstructionReason(result, graph, actor)
        if reason != none {
          pushDiagnostic(diagnostics, module.path, actor.span,
            "Actor<" + actor.className + "> construction is not isolated: " + reasonText(reason!))
        }
      }
      _ -> { }
    }
  }
}
