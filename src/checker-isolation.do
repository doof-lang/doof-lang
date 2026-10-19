// Transitive mutable-global effect analysis for isolated and actor-dispatched code.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import { ActorType, ArrayResolvedType, Binding, ClassType, Diagnostic, FailureResolvedType, InterfaceType, MapResolvedType, ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, SuccessResolvedType, Symbol, TupleResolvedType, TypeParameterType, UnionResolvedType } from "./semantic"
import { ActorCreationExpression, AsyncExpression, Block, CallArgument, CallExpression, CheckedConstruction, ClassDeclaration, ConstructExpression, ConstDeclaration, Expression, ForOfStatement, FunctionDeclaration, Identifier, ImmutableBinding, InterfaceDeclaration, LetDeclaration, MemberExpression, ObjectLiteral, ObjectProperty, ReadonlyDeclaration, SourceSpan, Statement, TupleLiteral } from "./ast"
import { findActorBoundaryViolation, implementationType, isActorMethodCall } from "./checker-actor-boundary"
import { asyncBlockCaptures, validateAsyncBlock } from "./checker-async"
import { collectExpressionTree, collectBlockExpressions, collectStatementExpressions } from "./ast-walk"
import { declaredSymbolName, symbolName } from "./checker-symbols"
import { classType, containsTypeParameter, isAssignable, substituteTypeParams, typeName } from "./checker-types"
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
  // Uncached nodes that may call this one, filled while inferring isolation.
  callers: IsolationNode[] = []
  let queued: bool = false
}

export class IsolationGraph {
  nodes: IsolationNode[] = []
}

// Lookups built once per validation so inference and effect collection never
// rescan module statements or graph nodes.
class IsolationIndex {
  result: AnalysisResult
  graph: IsolationGraph
  nodes: Map<FunctionDeclaration, IsolationNode> = {}
  // Graph nodes grouped by module path, in graph order.
  moduleNodes: Map<string, IsolationNode[]> = {}
  // Interface method (by `methodKey`) to the implementing class methods' nodes.
  implementations: Map<string, IsolationNode[]> = {}
  // Keyed by `declarationKey`, holding the first statement with that symbol name.
  declarations: Map<string, Statement> = {}
  classes: Map<string, ClassDeclaration> = {}
  // Top-level value declarations keyed by `spanKey`.
  values: Map<string, Statement> = {}
  // Classes convertible to some Stream<T>.
  streamClasses: ClassDeclaration[] = []
}

function declarationKey(modulePath: string, name: string): string {
  return modulePath + "\n" + name
}

function spanKey(modulePath: string, start: int, end: int): string {
  return modulePath + "\n" + string(start) + ":" + string(end)
}

function methodKey(method: FunctionDeclaration): string {
  return method.name + "\n" + string(method.span.start.offset) + ":" + string(method.span.end.offset)
}

function indexIsolation(result: AnalysisResult, graph: IsolationGraph): IsolationIndex {
  index := IsolationIndex { result, graph }
  for node of graph.nodes {
    if !index.nodes.has(node.declaration) { index.nodes.set(node.declaration, node) }
    if !index.moduleNodes.has(node.module) { index.moduleNodes.set(node.module, []) }
    index.moduleNodes[node.module].push(node)
  }
  for module of result.modules {
    for statement of module.program.statements {
      if statement.kind == "export-list" { continue }
      name := symbolName(statement)
      if name != "" && !index.declarations.has(declarationKey(module.path, name)) {
        index.declarations.set(declarationKey(module.path, name), statement)
      }
      case statement {
        class_: ClassDeclaration -> {
          if !index.classes.has(declarationKey(module.path, class_.name)) { index.classes.set(declarationKey(module.path, class_.name), class_) }
          if class_.resolvedSymbol != none && class_.resolvedSymbol!.streamElementTypes.length > 0 { index.streamClasses.push(class_) }
        }
        value: ConstDeclaration -> { indexValue(index, module.path, value.span, value) }
        value: ReadonlyDeclaration -> { indexValue(index, module.path, value.span, value) }
        value: ImmutableBinding -> { indexValue(index, module.path, value.span, value) }
        value: LetDeclaration -> { indexValue(index, module.path, value.span, value) }
        _ -> { }
      }
    }
  }
  for module of result.modules {
    for statement of module.program.statements {
      case statement {
        interface_: InterfaceDeclaration -> { indexImplementations(index, interface_) }
        _ -> { }
      }
    }
  }
  return index
}

function indexValue(index: IsolationIndex, modulePath: string, span: SourceSpan, statement: Statement): none {
  key := spanKey(modulePath, span.start.offset, span.end.offset)
  if !index.values.has(key) { index.values.set(key, statement) }
}

function indexImplementations(index: IsolationIndex, interface_: InterfaceDeclaration): none {
  if interface_.resolvedSymbol == none { return }
  for method of interface_.methods {
    let targets: IsolationNode[] = []
    for implementation of interface_.resolvedSymbol!.implementations {
      candidate := indexedDeclaration(index, implementation)
      if candidate == none { continue }
      case candidate! {
        class_: ClassDeclaration -> {
          for classMethod of class_.methods {
            if classMethod.name != method.name || classMethod.static_ != method.static_ { continue }
            node := index.nodes.get(classMethod) else { continue }
            targets.push(node)
          }
        }
        _ -> { }
      }
    }
    key := methodKey(method)
    existing := index.implementations.get(key) else {
      index.implementations.set(key, targets)
      continue
    }
    for target of targets { existing.push(target) }
  }
}

function indexedDeclaration(index: IsolationIndex, symbol: Symbol): Statement | none {
  statement := index.declarations.get(declarationKey(symbol.module, declaredSymbolName(symbol))) else { return none }
  return statement
}

function indexedClass(index: IsolationIndex, modulePath: string, name: string): ClassDeclaration | none {
  class_ := index.classes.get(declarationKey(modulePath, name)) else { return none }
  return class_
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
    let oldNodes: Map<FunctionDeclaration, IsolationNode> = {}
    for node of previous!.nodes { if !oldNodes.has(node.declaration) { oldNodes.set(node.declaration, node) } }
    reused: Set<string> := []
    for path of reusedModules { reused.add(path) }
    for node of graph.nodes {
      if !reused.has(node.module) { continue }
      old := oldNodes.get(node.declaration) else { continue }
      for call of old.calls { node.calls.push(call) }
      node.directReason = old.directReason
      node.reason = old.reason
      node.cached = true
    }
  }
  return graph
}


function moduleValueDeclaration(index: IsolationIndex, binding: Binding): Statement | none {
  if binding.symbol != none && (binding.symbol!.kind == "const" || binding.symbol!.kind == "readonly") {
    return indexedDeclaration(index, binding.symbol!)
  }
  statement := index.values.get(spanKey(binding.module, binding.span.start.offset, binding.span.end.offset)) else { return none }
  return statement
}

function mutableModuleReason(index: IsolationIndex, expression: Expression): IsolationReason | none {
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding == none { return none }
      declaration := moduleValueDeclaration(index, identifier.resolvedBinding!)
      if declaration == none { return none }
      case declaration! {
        _: ReadonlyDeclaration -> { return none }
        _: LetDeclaration -> { return IsolationReason { kind: "module", name: identifier.name, span: identifier.span } }
        _: ConstDeclaration -> { }
        _: ImmutableBinding -> { }
        _ -> { return none }
      }
      violation := findActorBoundaryViolation(index.result, identifier.resolvedBinding!.type_)
      if violation != none {
        return IsolationReason { kind: "module", name: identifier.name, span: identifier.span }
      }
    }
    _ -> { }
  }
  return none
}

function mutableStaticReason(index: IsolationIndex, expression: Expression): IsolationReason | none {
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding == none || identifier.resolvedBinding!.kind != "field" { return none }
      binding := identifier.resolvedBinding!
      owner := indexedClass(index, binding.module, binding.fieldOwner)
      if owner == none { return none }
      return staticFieldReason(index, owner!, identifier.name, identifier.span)
    }
    member: MemberExpression -> {
      if member.resolvedStaticOwner == none { return none }
      return staticFieldReason(index, member.resolvedStaticOwner!, member.property, member.span)
    }
    _ -> { }
  }
  return none
}

function staticFieldReason(index: IsolationIndex, owner: ClassDeclaration, property: string, span: SourceSpan): IsolationReason | none {
  for field of owner.fields {
    if !field.static_ || field.const_ { continue }
    for name of field.names {
      if name != property { continue }
      let mutable = field.let_ || field.resolvedType == none
      if !mutable { mutable = findActorBoundaryViolation(index.result, field.resolvedType!) != none }
      if !mutable { return none }
      return IsolationReason { kind: "static", name: owner.name + "." + property, span }
    }
  }
  return none
}

function allExpressions(roots: Expression[], statements: Statement[] | none = none): Expression[] {
  let result: Expression[] = []
  for root of roots { collectExpressionTree(root, result, statements) }
  return result
}

function functionExpressionRoots(fn: FunctionDeclaration, statements: Statement[] | none = none): Expression[] {
  let roots: Expression[] = []
  for parameter of fn.params { if parameter.defaultValue != none { roots.push(parameter.defaultValue!) } }
  case fn.body {
    block: Block -> { collectBlockExpressions(block, roots, statements) }
    expression: Expression -> { roots.push(expression) }
  }
  return roots
}

function nodeForDeclaration(index: IsolationIndex, declaration: FunctionDeclaration): IsolationNode | none {
  node := index.nodes.get(declaration) else { return none }
  return node
}

/** The declaration's own node, or for an interface method every implementing
 * class method's node. */
function nodesForDeclaration(index: IsolationIndex, declaration: FunctionDeclaration): IsolationNode[] {
  direct := index.nodes.get(declaration) else {
    targets := index.implementations.get(methodKey(declaration)) else { return [] }
    return targets
  }
  return [direct]
}

// Every method a member call may dispatch to. Union receivers contribute each
// member's method; interface methods expand to implementations later through
// nodesForDeclaration.
function receiverMethods(index: IsolationIndex, receiver: ResolvedType, property: string, targets: FunctionDeclaration[]): none {
  case receiver {
    class_: ClassType -> {
      declaration := indexedClass(index, class_.symbol.module, class_.symbol.name)
      if declaration == none { return }
      for method of declaration!.methods {
        if method.name == property && !method.static_ && !targets.contains(method) { targets.push(method) }
      }
    }
    interface_: InterfaceType -> {
      declaration := indexedDeclaration(index, interface_.symbol)
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
    union_: UnionResolvedType -> { for member of union_.types { receiverMethods(index, member, property, targets) } }
    parameter: TypeParameterType -> {
      if parameter.constraint != none { receiverMethods(index, parameter.constraint!, property, targets) }
    }
    stream: StreamResolvedType -> {
      for class_ of streamClasses(index, stream) {
        for method of class_.methods {
          if method.name == property && !method.static_ && !targets.contains(method) { targets.push(method) }
        }
      }
    }
    _ -> { }
  }
}

// A Stream<T> value holds any class instance converted to it, like the closed
// variant the emitter generates. Generic classes and element types that still
// mention type parameters match conservatively.
function streamClasses(index: IsolationIndex, stream: StreamResolvedType): ClassDeclaration[] {
  let classes: ClassDeclaration[] = []
  open := containsTypeParameter(stream.elementType)
  for class_ of index.streamClasses {
    if open || class_.typeParams.length > 0 || isAssignable(classType(class_.name, class_.resolvedSymbol!), stream) { classes.push(class_) }
  }
  return classes
}

// A for-of loop over a class or Stream<T> calls next() and value() on it.
function iterationMethods(index: IsolationIndex, iterable: ResolvedType): FunctionDeclaration[] {
  let targets: FunctionDeclaration[] = []
  case iterable {
    _: ActorType -> { return targets }
    _ -> { }
  }
  receiverMethods(index, iterable, "next", targets)
  receiverMethods(index, iterable, "value", targets)
  return targets
}

function callDeclarations(index: IsolationIndex, call: CallExpression): FunctionDeclaration[] {
  if call.resolvedFunction != none { return [call.resolvedFunction!] }
  let targets: FunctionDeclaration[] = []
  if call.resolvedConstructor != none { targets.push(call.resolvedConstructor!) }
  case call.callee {
    member: MemberExpression -> {
      if member.object.resolvedType != none && member.resolvedStaticOwner == none {
        case member.object.resolvedType! {
          // Actor calls run in the actor's domain and are validated separately.
          _: ActorType -> { }
          _ -> { receiverMethods(index, member.object.resolvedType!, member.property, targets) }
        }
      }
    }
    _ -> { }
  }
  return targets
}

// Direct mutable-state accesses and call edges reachable from a set of
// expressions, in source order. Construction contributes the checked plan's
// static factory or the omitted field defaults it evaluates, and the class
// destructor, which runs in the domain that releases the object; reasons found
// inside a default or destructor are attributed to the construction expression.
// For-of loops over class or Stream<T> iterables call next() and value().
class IsolationEffects {
  let direct: IsolationReason | none = none
  // Number of calls collected before the first direct reason.
  let callsBeforeDirect: int = 0
  calls: IsolationCall[] = []
  visitedDefaults: Expression[] = []
  visitedDestructors: Block[] = []
}

// `statements` holds statements already visited while building `roots`, such
// as a function body's; nested ones are collected here.
function collectEffects(index: IsolationIndex, roots: Expression[], effects: IsolationEffects, via: SourceSpan | none = none, statements: Statement[] = []): none {
  expressions := allExpressions(roots, statements)
  let loops: ForOfStatement[] = []
  for statement of statements {
    case statement {
      forOf: ForOfStatement -> { loops.push(forOf) }
      _ -> { }
    }
  }
  for expression of expressions {
    if effects.direct == none {
      let reason = mutableModuleReason(index, expression)
      if reason == none { reason = mutableStaticReason(index, expression) }
      if reason != none {
        effects.direct = if via == none then reason else IsolationReason { kind: reason!.kind, name: reason!.name, span: via! }
        effects.callsBeforeDirect = effects.calls.length
      }
    }
    case expression {
      call: CallExpression -> {
        span := via ?? call.span
        for declaration of callDeclarations(index, call) { effects.calls.push(IsolationCall { declaration, span }) }
        collectConstructionEffects(index, call.resolvedConstruction, suppliedArguments(call.args), span, effects)
        collectDecodeEffects(index, call, span, effects)
      }
      object: ObjectLiteral -> { collectConstructionEffects(index, object.resolvedConstruction, suppliedProperties(object.properties, []), via ?? object.span, effects) }
      tuple: TupleLiteral -> { collectConstructionEffects(index, tuple.resolvedConstruction, suppliedPositions(tuple.elements.length), via ?? tuple.span, effects) }
      construct: ConstructExpression -> { collectConstructionEffects(index, construct.resolvedConstruction, suppliedProperties(construct.args, construct.spreadFields), via ?? construct.span, effects) }
      actor: ActorCreationExpression -> { collectConstructionEffects(index, actor.resolvedConstruction, suppliedPositions(actor.args.length), via ?? actor.span, effects) }
      _ -> { }
    }
    // The loop advances the iterable after evaluating it and before its body.
    for loop_ of loops {
      if loop_.iterable != expression || expression.resolvedType == none { continue }
      for declaration of iterationMethods(index, expression.resolvedType!) {
        effects.calls.push(IsolationCall { declaration, span: via ?? expression.span })
      }
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

function collectConstructionEffects(index: IsolationIndex, plan: CheckedConstruction | none, supplied: SuppliedArguments, span: SourceSpan, effects: IsolationEffects): none {
  if plan == none { return }
  if plan!.declaration != none { collectDestructorEffects(index, plan!.declaration!, span, effects) }
  if plan!.factory != none {
    // Factory parameter defaults belong to the factory's own isolation node.
    effects.calls.push(IsolationCall { declaration: plan!.factory!, span })
    return
  }
  for position of 0..<plan!.signature.params.length {
    if position >= plan!.defaults.length || plan!.defaults[position].value == none { continue }
    name := plan!.signature.params[position].name
    if position < supplied.positional || supplied.names.contains(name) { continue }
    default_ := plan!.defaults[position].value!
    if effects.visitedDefaults.contains(default_) { continue }
    effects.visitedDefaults.push(default_)
    collectEffects(index, [default_], effects, span)
  }
}

// An object is released in the domain that drops its last reference. Objects
// stay in the domain that creates them unless they cross a boundary, which
// validateModuleIsolationEffects checks, so creation commits to the destructor.
function collectDestructorEffects(index: IsolationIndex, class_: ClassDeclaration, span: SourceSpan | none, effects: IsolationEffects): none {
  if class_.destructor_ == none { return }
  releaser := class_.destructor_!
  if effects.visitedDestructors.contains(releaser) { return }
  effects.visitedDestructors.push(releaser)
  let roots: Expression[] = []
  let statements: Statement[] = []
  collectBlockExpressions(releaser, roots, statements)
  collectEffects(index, roots, effects, span, statements)
}

// `T.fromSerialValue(json)` builds every object the decoded value can hold
// without a construction expression, evaluating omitted field defaults.
function collectDecodeEffects(index: IsolationIndex, call: CallExpression, span: SourceSpan, effects: IsolationEffects): none {
  if call.resolvedFunction != none || call.resolvedType == none { return }
  case call.callee {
    member: MemberExpression -> { if member.property != "fromSerialValue" { return } }
    _ -> { return }
  }
  case call.resolvedType! {
    decoded: ResultResolvedType -> {
      for class_ of reachableClasses(index, decoded.valueType) {
        for field of class_.fields {
          if field.static_ || field.defaultValue == none || effects.visitedDefaults.contains(field.defaultValue!) { continue }
          effects.visitedDefaults.push(field.defaultValue!)
          collectEffects(index, [field.defaultValue!], effects, span)
        }
        collectDestructorEffects(index, class_, span, effects)
      }
    }
    _ -> { }
  }
}

/** Every class whose instances a value of this type can own, through instance
 * fields, containers, unions, and interface implementations. */
function reachableClasses(index: IsolationIndex, type_: ResolvedType): ClassDeclaration[] {
  let classes: ClassDeclaration[] = []
  let seen: string[] = []
  collectReachableClasses(index, type_, classes, seen)
  return classes
}

function collectReachableClasses(index: IsolationIndex, type_: ResolvedType, classes: ClassDeclaration[], seen: string[]): none {
  case type_ {
    class_: ClassType -> {
      key := class_.symbol.module + ":" + typeName(class_)
      if seen.contains(key) { return }
      seen.push(key)
      declaration := indexedClass(index, class_.symbol.module, class_.symbol.name)
      if declaration == none { return }
      if !classes.contains(declaration!) { classes.push(declaration!) }
      for field of declaration!.fields {
        if field.static_ || field.resolvedType == none { continue }
        collectReachableClasses(index, substituteTypeParams(field.resolvedType!, declaration!.typeParams, class_.typeArgs), classes, seen)
      }
    }
    interface_: InterfaceType -> {
      key := interface_.symbol.module + ":" + typeName(interface_)
      if seen.contains(key) { return }
      seen.push(key)
      for implementation of interface_.symbol.implementations {
        collectReachableClasses(index, implementationType(index.result, interface_, implementation), classes, seen)
      }
    }
    array: ArrayResolvedType -> { collectReachableClasses(index, array.elementType, classes, seen) }
    map: MapResolvedType -> {
      collectReachableClasses(index, map.keyType, classes, seen)
      collectReachableClasses(index, map.valueType, classes, seen)
    }
    set_: SetResolvedType -> { collectReachableClasses(index, set_.elementType, classes, seen) }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectReachableClasses(index, element, classes, seen) } }
    union_: UnionResolvedType -> { for member of union_.types { collectReachableClasses(index, member, classes, seen) } }
    result_: ResultResolvedType -> {
      collectReachableClasses(index, result_.valueType, classes, seen)
      collectReachableClasses(index, result_.errorType, classes, seen)
    }
    success: SuccessResolvedType -> { collectReachableClasses(index, success.valueType, classes, seen) }
    failure: FailureResolvedType -> { collectReachableClasses(index, failure.errorType, classes, seen) }
    stream: StreamResolvedType -> {
      for class_ of streamClasses(index, stream) {
        if class_.resolvedSymbol != none { collectReachableClasses(index, classType(class_.name, class_.resolvedSymbol!), classes, seen) }
      }
    }
    parameter: TypeParameterType -> {
      if parameter.constraint != none { collectReachableClasses(index, parameter.constraint!, classes, seen) }
    }
    // Actor state stays behind messages; weak references never release their
    // target; a promise's value is created in the domain that completes it.
    _ -> { }
  }
}

function analyzeNode(index: IsolationIndex, node: IsolationNode): none {
  if node.declaration.bodyless && !node.declaration.isolated_ {
    node.directReason = IsolationReason { kind: "bodyless", name: node.declaration.name, span: node.declaration.span }
    return
  }
  effects := IsolationEffects {}
  let statements: Statement[] = []
  roots := functionExpressionRoots(node.declaration, statements)
  collectEffects(index, roots, effects, none, statements)
  node.directReason = effects.direct
  for call of effects.calls { node.calls.push(call) }
}

// The first call, in source order, to a node that already has a reason.
function callReason(index: IsolationIndex, node: IsolationNode): IsolationReason | none {
  for call of node.calls {
    for target of nodesForDeclaration(index, call.declaration) {
      if target.reason != none { return IsolationReason { kind: "call", name: target.declaration.name, span: call.span } }
    }
  }
  return none
}

/** Propagates reasons breadth-first along reverse call edges, visiting each
 * edge a bounded number of times. Every caller of a level's nodes takes its
 * reason from callees resolved at earlier levels, so explanations follow a
 * shortest path to a direct reason and never cycle. */
function inferIsolation(index: IsolationIndex): none {
  graph := index.graph
  for node of graph.nodes {
    if node.cached { continue }
    analyzeNode(index, node)
    node.reason = node.directReason
  }
  let frontier: IsolationNode[] = []
  for node of graph.nodes {
    if node.reason != none {
      frontier.push(node)
      continue
    }
    if node.cached { continue }
    for call of node.calls {
      for target of nodesForDeclaration(index, call.declaration) { target.callers.push(node) }
    }
  }
  while frontier.length > 0 {
    let level: IsolationNode[] = []
    for target of frontier {
      for caller of target.callers {
        if caller.reason != none || caller.queued { continue }
        caller.queued = true
        level.push(caller)
      }
    }
    let reasons: IsolationReason[] = []
    for node of level { reasons.push(callReason(index, node)!) }
    for position of 0..<level.length { level[position].reason = reasons[position] }
    frontier = level
  }
  for node of graph.nodes { node.declaration.resolvedIsolated = node.reason == none }
}

function reasonText(reason: IsolationReason): string {
  if reason.kind == "module" { return "accesses mutable module binding \"" + reason.name + "\"" }
  if reason.kind == "static" { return "accesses mutable static field \"" + reason.name + "\"" }
  if reason.kind == "call" { return "calls non-isolated function \"" + reason.name + "\"" }
  return "uses bodyless function \"" + reason.name + "\" without an isolated contract"
}

function effectsReason(index: IsolationIndex, effects: IsolationEffects): IsolationReason | none {
  for position of 0..<effects.calls.length {
    if effects.direct != none && position == effects.callsBeforeDirect { return effects.direct }
    call := effects.calls[position]
    for target of nodesForDeclaration(index, call.declaration) {
      if target.reason != none {
        return IsolationReason { kind: "call", name: target.declaration.name, span: call.span }
      }
    }
  }
  return effects.direct
}

function probeReason(index: IsolationIndex, expression: Expression): IsolationReason | none {
  effects := IsolationEffects {}
  collectEffects(index, [expression], effects)
  return effectsReason(index, effects)
}

/** The constructor factory or omitted field defaults run to build actor state;
 * arguments are evaluated in the creating domain and are checked there. */
function actorConstructionReason(index: IsolationIndex, actor: ActorCreationExpression): IsolationReason | none {
  effects := IsolationEffects {}
  collectConstructionEffects(index, actor.resolvedConstruction, suppliedPositions(actor.args.length), actor.span, effects)
  return effectsReason(index, effects)
}

class ReleaseReason {
  className: string
  reason: IsolationReason
}

/** A value that crosses into another domain may be released there, running the
 * destructor of any class it can own, so each such destructor must be isolated. */
function crossingReleaseReason(index: IsolationIndex, type_: ResolvedType): ReleaseReason | none {
  // Values that cannot cross at all are already rejected at the boundary.
  if findActorBoundaryViolation(index.result, type_) != none { return none }
  for class_ of reachableClasses(index, type_) {
    if class_.destructor_ == none { continue }
    effects := IsolationEffects {}
    collectDestructorEffects(index, class_, none, effects)
    reason := effectsReason(index, effects)
    if reason != none { return ReleaseReason { className: class_.name, reason: reason! } }
  }
  return none
}

function validateCrossingValue(index: IsolationIndex, module: ModuleInfo, value: Expression, destination: string, diagnostics: Diagnostic[]): none {
  if value.resolvedType == none { return }
  release := crossingReleaseReason(index, value.resolvedType!)
  if release == none { return }
  pushDiagnostic(diagnostics, module.path, value.span,
    "Value passed to " + destination + " may be released there, but the destructor of class \"" + release!.className + "\" " + reasonText(release!.reason))
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
        if class_.destructor_ != none { collectBlockExpressions(class_.destructor_!, roots) }
      }
      _ -> { collectStatementExpressions(statement, roots) }
    }
  }
  return allExpressions(roots)
}

function validateModuleIsolationEffects(index: IsolationIndex, module: ModuleInfo, diagnostics: Diagnostic[]): none {
  let moduleNodes: IsolationNode[] = []
  if index.moduleNodes.has(module.path) { moduleNodes = index.moduleNodes[module.path] }
  for node of moduleNodes {
    if !node.declaration.isolated_ || node.reason == none { continue }
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
          block: Block -> {
            validateAsyncBlock(index.result, async_, module.path, diagnostics)
            for capture of asyncBlockCaptures(block) {
              release := crossingReleaseReason(index, capture.resolvedBinding!.type_)
              if release != none {
                pushDiagnostic(diagnostics, module.path, capture.span,
                  "Async block capture \"" + capture.name + "\" may be released in the worker, but the destructor of class \"" + release!.className + "\" " + reasonText(release!.reason))
              }
            }
            reason := probeReason(index, async_)
            if reason != none {
              pushDiagnostic(diagnostics, module.path, reason!.span,
                "Async block is not isolated: " + reasonText(reason!))
            }
          }
          inner: Expression -> {
            if !isActorMethodCall(inner) {
              case inner {
                call: CallExpression -> {
                  for argument of call.args { validateCrossingValue(index, module, argument.value, "an async call", diagnostics) }
                }
                _ -> { }
              }
              reason := probeReason(index, inner)
              if reason != none {
                pushDiagnostic(diagnostics, module.path, reason!.span,
                  "Async call is not isolated: " + reasonText(reason!))
              }
            }
          }
        }
      }
      call: CallExpression -> {
        if isActorMethodCall(call) {
          name := case call.callee { member: MemberExpression -> member.property, _ -> "" }
          for argument of call.args { validateCrossingValue(index, module, argument.value, "actor method \"" + name + "\"", diagnostics) }
        }
        if isActorMethodCall(call) && call.resolvedFunction != none {
          target := nodeForDeclaration(index, call.resolvedFunction!)
          if target != none && target!.reason != none {
            pushDiagnostic(diagnostics, module.path, call.span,
              "Actor method \"" + target!.declaration.name + "\" is not isolated: " + reasonText(target!.reason!))
          }
        }
      }
      actor: ActorCreationExpression -> {
        for argument of actor.args { validateCrossingValue(index, module, argument, "Actor<" + actor.className + "> construction", diagnostics) }
        reason := actorConstructionReason(index, actor)
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
  index := indexIsolation(result, graph)
  inferIsolation(index)
  reused: Set<string> := []
  if previous != none { for path of reusedModules { reused.add(path) } }
  for module of result.modules {
    if reused.has(module.path) { continue }
    validateModuleIsolationEffects(index, module, diagnostics)
  }
  return graph
}
