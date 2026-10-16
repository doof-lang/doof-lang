// Transitive mutable-global effect analysis for isolated and actor-dispatched code.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import { ActorType, Binding, ClassType, Diagnostic, InterfaceType, ResolvedType, SemanticSpan, TypeParameterType, UnionResolvedType } from "./semantic"
import { ActorCreationExpression, AsyncExpression, Block, CallArgument, CallExpression, CheckedConstruction, ClassDeclaration, ConstructExpression, ConstDeclaration, Expression, FunctionDeclaration, Identifier, ImmutableBinding, InterfaceDeclaration, LetDeclaration, MemberExpression, ObjectLiteral, ObjectProperty, ReadonlyDeclaration, SourceSpan, Statement, TupleLiteral } from "./ast"
import { findActorBoundaryViolation, isActorMethodCall } from "./checker-actor-boundary"
import { validateAsyncBlock } from "./checker-async"
import { collectExpressionTree, collectBlockExpressions, collectStatementExpressions } from "./ast-walk"
import { declarationFor, findClassDeclaration } from "./checker-symbols"
import { findModule } from "./checker-interfaces"
import { pushDiagnostic } from "./checker-validation"

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
  let directReason: IsolationReason | none = none
  let reason: IsolationReason | none = none
  let cached: bool = false
}

export class IsolationGraph {
  nodes: IsolationNode[] = []
}

function collectGraph(result: AnalysisResult, previous: IsolationGraph | none, reusedModules: string[]): IsolationGraph {
  graph := IsolationGraph {}
  for module of result.modules {
    for statement of module.program.statements {
      case statement {
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
  if previous != none {
    for node of graph.nodes {
      let reused = false
      for path of reusedModules { if path == node.module { reused = true } }
      if !reused { continue }
      old := nodeForDeclaration(previous!, node.declaration)
      if old == none { continue }
      for call of old!.calls { node.calls.push(call) }
      node.directReason = old!.directReason
      node.reason = old!.reason
      node.cached = true
    }
  }
  return graph
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
  for statement of module!.program.statements {
    case statement {
      value: ConstDeclaration -> { if sameSpan(value.span, binding.span) { return value } }
      value: ReadonlyDeclaration -> { if sameSpan(value.span, binding.span) { return value } }
      value: ImmutableBinding -> { if sameSpan(value.span, binding.span) { return value } }
      value: LetDeclaration -> { if sameSpan(value.span, binding.span) { return value } }
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
        _: LetDeclaration -> { return IsolationReason { kind: "module", name: identifier.name, span: identifier.span } }
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

function mutableStaticReason(result: AnalysisResult, expression: Expression): IsolationReason | none {
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding == none || identifier.resolvedBinding!.kind != "field" { return none }
      binding := identifier.resolvedBinding!
      owner := findClassDeclaration(result, binding.module, binding.fieldOwner)
      if owner == none { return none }
      return staticFieldReason(result, owner!, identifier.name, identifier.span)
    }
    member: MemberExpression -> {
      if member.resolvedStaticOwner == none { return none }
      return staticFieldReason(result, member.resolvedStaticOwner!, member.property, member.span)
    }
    _ -> { }
  }
  return none
}

function staticFieldReason(result: AnalysisResult, owner: ClassDeclaration, property: string, span: SourceSpan): IsolationReason | none {
  for field of owner.fields {
    if !field.static_ || field.const_ { continue }
    for name of field.names {
      if name != property { continue }
      let mutable = field.let_ || field.resolvedType == none
      if !mutable { mutable = findActorBoundaryViolation(result, field.resolvedType!) != none }
      if !mutable { return none }
      return IsolationReason { kind: "static", name: owner.name + "." + property, span }
    }
  }
  return none
}

function allExpressions(roots: Expression[]): Expression[] {
  let result: Expression[] = []
  for root of roots { collectExpressionTree(root, result) }
  return result
}

function functionExpressionRoots(fn: FunctionDeclaration): Expression[] {
  let roots: Expression[] = []
  for parameter of fn.params { if parameter.defaultValue != none { roots.push(parameter.defaultValue!) } }
  case fn.body {
    block: Block -> { collectBlockExpressions(block, roots) }
    expression: Expression -> { roots.push(expression) }
  }
  return roots
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
    for statement of module.program.statements {
      case statement {
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

// Every method a member call may dispatch to. Union receivers contribute each
// member's method; interface methods expand to implementations later through
// nodesForDeclaration.
function receiverMethods(result: AnalysisResult, receiver: ResolvedType, property: string, targets: FunctionDeclaration[]): none {
  case receiver {
    class_: ClassType -> {
      declaration := findClassDeclaration(result, class_.symbol.module, class_.symbol.name)
      if declaration == none { return }
      for method of declaration!.methods {
        if method.name == property && !method.static_ && !targets.contains(method) { targets.push(method) }
      }
    }
    interface_: InterfaceType -> {
      declaration := declarationFor(result, interface_.symbol)
      if declaration == none { return }
      case declaration! {
        interfaceDeclaration: InterfaceDeclaration -> {
          for method of interfaceDeclaration.methods {
            if method.name == property && !targets.contains(method) { targets.push(method) }
          }
        }
        _ -> { }
      }
    }
    union_: UnionResolvedType -> { for member of union_.types { receiverMethods(result, member, property, targets) } }
    parameter: TypeParameterType -> {
      if parameter.constraint != none { receiverMethods(result, parameter.constraint!, property, targets) }
    }
    _ -> { }
  }
}

function callDeclarations(result: AnalysisResult, call: CallExpression): FunctionDeclaration[] {
  if call.resolvedFunction != none { return [call.resolvedFunction!] }
  let targets: FunctionDeclaration[] = []
  if call.resolvedConstructor != none { targets.push(call.resolvedConstructor!) }
  case call.callee {
    member: MemberExpression -> {
      if member.object.resolvedType != none && member.resolvedStaticOwner == none {
        case member.object.resolvedType! {
          // Actor calls run in the actor's domain and are validated separately.
          _: ActorType -> { }
          _ -> { receiverMethods(result, member.object.resolvedType!, member.property, targets) }
        }
      }
    }
    _ -> { }
  }
  return targets
}

// Direct mutable-state accesses and call edges reachable from a set of
// expressions, in source order. Construction contributes the checked plan's
// static factory or the omitted field defaults it evaluates; reasons found inside
// a default are attributed to the construction expression that evaluates it.
class IsolationEffects {
  let direct: IsolationReason | none = none
  // Number of calls collected before the first direct reason.
  let callsBeforeDirect: int = 0
  calls: IsolationCall[] = []
  visitedDefaults: Expression[] = []
}

function collectEffects(result: AnalysisResult, roots: Expression[], effects: IsolationEffects, via: SourceSpan | none = none): none {
  for expression of allExpressions(roots) {
    if effects.direct == none {
      let reason = mutableModuleReason(result, expression)
      if reason == none { reason = mutableStaticReason(result, expression) }
      if reason != none {
        effects.direct = if via == none then reason else IsolationReason { kind: reason!.kind, name: reason!.name, span: via! }
        effects.callsBeforeDirect = effects.calls.length
      }
    }
    case expression {
      call: CallExpression -> {
        span := via ?? call.span
        for declaration of callDeclarations(result, call) { effects.calls.push(IsolationCall { declaration, span }) }
        collectConstructionEffects(result, call.resolvedConstruction, suppliedArguments(call.args), span, effects)
      }
      object: ObjectLiteral -> { collectConstructionEffects(result, object.resolvedConstruction, suppliedProperties(object.properties, []), via ?? object.span, effects) }
      tuple: TupleLiteral -> { collectConstructionEffects(result, tuple.resolvedConstruction, suppliedPositions(tuple.elements.length), via ?? tuple.span, effects) }
      construct: ConstructExpression -> { collectConstructionEffects(result, construct.resolvedConstruction, suppliedProperties(construct.args, construct.spreadFields), via ?? construct.span, effects) }
      actor: ActorCreationExpression -> { collectConstructionEffects(result, actor.resolvedConstruction, suppliedPositions(actor.args.length), via ?? actor.span, effects) }
      _ -> { }
    }
  }
}

class SuppliedArguments {
  names: string[] = []
  let positional: int = 0
}

function suppliedArguments(args: CallArgument[]): SuppliedArguments {
  supplied := SuppliedArguments {}
  for argument of args { if argument.name != none { supplied.names.push(argument.name!) } }
  if supplied.names.length == 0 { supplied.positional = args.length }
  return supplied
}

function suppliedProperties(properties: ObjectProperty[], spreadFields: string[]): SuppliedArguments {
  supplied := SuppliedArguments {}
  for property of properties { supplied.names.push(property.name) }
  for name of spreadFields { supplied.names.push(name) }
  return supplied
}

function suppliedPositions(count: int): SuppliedArguments {
  return SuppliedArguments { positional: count }
}

function collectConstructionEffects(result: AnalysisResult, plan: CheckedConstruction | none, supplied: SuppliedArguments, span: SourceSpan, effects: IsolationEffects): none {
  if plan == none { return }
  if plan!.factory != none {
    // Factory parameter defaults belong to the factory's own isolation node.
    effects.calls.push(IsolationCall { declaration: plan!.factory!, span })
    return
  }
  for index of 0..<plan!.signature.params.length {
    if index >= plan!.defaults.length || plan!.defaults[index].value == none { continue }
    name := plan!.signature.params[index].name
    if index < supplied.positional || supplied.names.contains(name) { continue }
    default_ := plan!.defaults[index].value!
    if effects.visitedDefaults.contains(default_) { continue }
    effects.visitedDefaults.push(default_)
    collectEffects(result, [default_], effects, span)
  }
}

function analyzeNode(result: AnalysisResult, graph: IsolationGraph, node: IsolationNode): none {
  if node.declaration.bodyless && !node.declaration.isolated_ {
    node.directReason = IsolationReason { kind: "bodyless", name: node.declaration.name, span: node.declaration.span }
    return
  }
  effects := IsolationEffects {}
  collectEffects(result, functionExpressionRoots(node.declaration), effects)
  node.directReason = effects.direct
  for call of effects.calls { node.calls.push(call) }
}

function inferIsolation(result: AnalysisResult, graph: IsolationGraph): none {
  for node of graph.nodes {
    if node.cached { continue }
    analyzeNode(result, graph, node)
    node.reason = node.directReason
  }
  let changed = true
  while changed {
    changed = false
    for node of graph.nodes {
      if node.cached || node.reason != none { continue }
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

function effectsReason(result: AnalysisResult, graph: IsolationGraph, effects: IsolationEffects): IsolationReason | none {
  for index of 0..<effects.calls.length {
    if effects.direct != none && index == effects.callsBeforeDirect { return effects.direct }
    call := effects.calls[index]
    for target of nodesForDeclaration(result, graph, call.declaration) {
      if target.reason != none {
        return IsolationReason { kind: "call", name: target.declaration.name, span: call.span }
      }
    }
  }
  return effects.direct
}

function probeReason(result: AnalysisResult, graph: IsolationGraph, expression: Expression): IsolationReason | none {
  effects := IsolationEffects {}
  collectEffects(result, [expression], effects)
  return effectsReason(result, graph, effects)
}

/** The constructor factory or omitted field defaults run to build actor state;
 * arguments are evaluated in the creating domain and are checked there. */
function actorConstructionReason(result: AnalysisResult, graph: IsolationGraph, actor: ActorCreationExpression): IsolationReason | none {
  effects := IsolationEffects {}
  collectConstructionEffects(result, actor.resolvedConstruction, suppliedPositions(actor.args.length), actor.span, effects)
  return effectsReason(result, graph, effects)
}

function moduleExpressions(module: ModuleInfo): Expression[] {
  let roots: Expression[] = []
  for statement of module.program.statements {
    case statement {
      fn: FunctionDeclaration -> {
        for expression of functionExpressionRoots(fn) { roots.push(expression) }
      }
      class_: ClassDeclaration -> {
        for field of class_.fields { if field.defaultValue != none { roots.push(field.defaultValue!) } }
        for method of class_.methods {
          for expression of functionExpressionRoots(method) { roots.push(expression) }
        }
      }
      _ -> { collectStatementExpressions(statement, roots) }
    }
  }
  return allExpressions(roots)
}

function validateModuleIsolationEffects(result: AnalysisResult, graph: IsolationGraph, module: ModuleInfo, diagnostics: Diagnostic[]): none {
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
      async_: AsyncExpression -> {
        case async_.expression {
          _: Block -> {
            validateAsyncBlock(result, async_, module.path, diagnostics)
            reason := probeReason(result, graph, async_)
            if reason != none {
              pushDiagnostic(diagnostics, module.path, reason!.span,
                "Async block is not isolated: " + reasonText(reason!))
            }
          }
          inner: Expression -> {
            if !isActorMethodCall(inner) {
              reason := probeReason(result, graph, inner)
              if reason != none {
                pushDiagnostic(diagnostics, module.path, reason!.span,
                  "Async call is not isolated: " + reasonText(reason!))
              }
            }
          }
        }
      }
      call: CallExpression -> {
        if isActorMethodCall(call) && call.resolvedFunction != none {
          target := nodeForDeclaration(graph, call.resolvedFunction!)
          if target != none && target!.reason != none {
            pushDiagnostic(diagnostics, module.path, call.span,
              "Actor method \"" + target!.declaration.name + "\" is not isolated: " + reasonText(target!.reason!))
          }
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

/** Reuses effects only for dependency-closed checked modules whose declarations
 * are unchanged. The editor invalidates nominal changes across the whole graph
 * and rechecks every module with diagnostics before permitting this reuse. */
export function validateIsolationEffects(result: AnalysisResult, diagnostics: Diagnostic[], previous: IsolationGraph | none = none, reusedModules: string[] = []): IsolationGraph {
  graph := collectGraph(result, previous, reusedModules)
  inferIsolation(result, graph)
  for module of result.modules {
    let reused = false
    for path of reusedModules { if path == module.path { reused = true } }
    if previous != none && reused { continue }
    validateModuleIsolationEffects(result, graph, module, diagnostics)
  }
  return graph
}
