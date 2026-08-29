// Exact foreign declaration selection for one generated C++ translation unit.
//
// This is a transient lowering plan. It consumes checker decorations and never
// persists or reconstructs module semantics.

import {
  ArrayType, AstFunctionType, Block, ClassDeclaration, ConstDeclaration, EnumDeclaration, ExportDeclaration, Expression, FunctionDeclaration, Identifier,
  ImmutableBinding, InterfaceDeclaration, MemberExpression, NamedType, Program, ReadonlyDeclaration, Statement, TypeAliasDeclaration,
  TypeAnnotation, UnionType, WeakType,
} from "./ast"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import { InstantiationPlan, interfaceInstantiationKey } from "./emitter-monomorphize"
import {
  collectWorldviewBlockExpressions, collectWorldviewNestedExpressions, collectWorldviewStatementExpressions,
} from "./emitter-worldview-walk"
import {
  ActorType, ArrayResolvedType, ClassType, EnumType, FunctionType, InterfaceType, MapResolvedType, PromiseType,
  ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, Symbol, TupleResolvedType, UnionResolvedType, WeakResolvedType,
} from "./semantic"

export class WorldviewModule {
  path: string
  program: Program
}

export class WorldviewPlan {
  modules: WorldviewModule[] = []
  let interfaceKeys: string[] = []
}

class WorldviewSelection {
  statements: Statement[] = []
}

// One transient index serves a single worldview plan. Keeping it graph-scoped
// avoids global state while replacing repeated linear searches through the
// module graph, declaration lists, selections, and visited-key arrays.
export class WorldviewGraphIndex {
  modules: Map<string, ModuleInfo> = {}
  declarations: Map<string, Statement> = {}
  symbols: Map<string, Symbol> = {}
}

class WorldviewIndex {
  graph: WorldviewGraphIndex
  selections: Map<string, WorldviewSelection> = {}
  selectedKeys: Set<string> = []
  interfaceKeys: string[] = []
  interfaceKeySet: Set<string> = []
  visitingPaths: Set<string> = []
  visitedPaths: Set<string> = []
}

export function planWorldview(
  result: AnalysisResult,
  rootPath: string,
  instantiations: InstantiationPlan | none = none,
  graphIndex: WorldviewGraphIndex | none = none,
): WorldviewPlan {
  index := WorldviewIndex { graph: if graphIndex == none then indexWorldviewGraph(result) else graphIndex! }
  root := findModule(index, rootPath)
  if root == none { return WorldviewPlan {} }

  // The root owns every declaration it defines. Foreign declarations are
  // selected only from checked uses and their recursive declaration surface.
  for statement of root!.program.statements {
    collectStatementSurface(statement, rootPath, index, false)
    let expressions: Expression[] = []
    collectWorldviewStatementExpressions(statement, expressions)
    for expression of expressions { collectExpressionTree(expression, rootPath, index) }
  }
  // The root header owns all of its declarations, including every native
  // declaration it exposes. Seed each opaque native-header surface even though
  // resolving a root symbol does not add a foreign statement.
  for symbol of root!.symbols {
    if symbol.native_ && symbol.nativeHeader != "" {
      collectSymbol(symbol, rootPath, index)
    }
  }
  // Re-exported declarations are part of the root module's own public header
  // surface even when its implementation never references them.
  for symbol of root!.exports {
    if symbol.module != "" && symbol.module != rootPath {
      collectSymbol(symbol, rootPath, index)
    }
  }

  if instantiations != none {
    for interface_ of instantiations!.interfaces {
      if !index.interfaceKeySet.has(interface_.key) { continue }
      for implementation of interface_.implementations {
        let name = implementation.typeName
        for class_ of instantiations!.classes {
          if class_.modulePath == implementation.modulePath && class_.emittedName == implementation.typeName {
            name = class_.declaration.name
            break
          }
        }
        module := findModule(index, implementation.modulePath)
        if module == none { continue }
        symbol := findSymbol(index, implementation.modulePath, name)
        if symbol != none { collectSymbol(symbol!, rootPath, index) }
      }
    }
  }

  plan := WorldviewPlan {}
  plan.interfaceKeys = index.interfaceKeys
  // Concrete interface implementors can be selected against the import edge,
  // so visit every selected foreign module before the root. Each visit follows
  // ordinary imports/re-exports dependency-first.
  for info of result.modules {
    if info.path != rootPath && findSelection(index, info.path) != none {
      appendWorldviewModule(index, info.path, rootPath, plan)
    }
  }
  appendWorldviewModule(index, rootPath, rootPath, plan)
  return plan
}

function appendWorldviewModule(
  index: WorldviewIndex,
  path: string,
  rootPath: string,
  plan: WorldviewPlan,
): none {
  if index.visitedPaths.has(path) || index.visitingPaths.has(path) { return }
  info := findModule(index, path)
  if info == none { return }
  selection := findSelection(index, path)
  if path != rootPath && (selection == none || selection!.statements.length == 0) { return }
  index.visitingPaths.add(path)
  for imported of info!.imports {
    if imported.sourceModule != rootPath {
      appendWorldviewModule(index, imported.sourceModule, rootPath, plan)
    }
  }
  for reExport of info!.reExports {
    if reExport != rootPath { appendWorldviewModule(index, reExport, rootPath, plan) }
  }
  index.visitingPaths.delete(path)
  if index.visitedPaths.has(path) { return }
  index.visitedPaths.add(path)
  if path == rootPath {
    plan.modules.push(WorldviewModule { path, program: info!.program })
  } else {
    ordered := orderedSelectionStatements(info!, selection!)
    plan.modules.push(WorldviewModule {
      path,
      program: Program { kind: info!.program.kind, statements: ordered, span: info!.program.span },
    })
  }
}

function addInterfaceKey(index: WorldviewIndex, value: string): none {
  if index.interfaceKeySet.has(value) { return }
  index.interfaceKeySet.add(value)
  index.interfaceKeys.push(value)
}

function orderedSelectionStatements(info: ModuleInfo, selection: WorldviewSelection): Statement[] {
  let ordered: Statement[] = []
  let selectedNames: Set<string> = []
  for selected of selection.statements { selectedNames.add(statementName(selected)) }
  for candidate of info.program.statements {
    name := statementName(candidate)
    if name != "" && selectedNames.has(name) { ordered.push(candidate) }
  }
  return ordered
}

function collectExpressionTree(
  expression: Expression,
  rootPath: string,
  index: WorldviewIndex,
): none {
  // Reuse one growing worklist for the whole expression tree. The previous
  // recursive form allocated a temporary child array for every AST node,
  // which dominates worldview planning for expression-heavy modules.
  let expressions = [expression]
  let cursor = 0
  while cursor < expressions.length {
    current := expressions[cursor]
    cursor = cursor + 1
    if current.resolvedType != none { collectType(current.resolvedType!, rootPath, index) }
    case current {
      identifier: Identifier -> {
        if identifier.resolvedBinding != none && identifier.resolvedBinding!.symbol != none {
          collectSymbol(identifier.resolvedBinding!.symbol!, rootPath, index)
        }
      }
      member: MemberExpression -> {
        if member.resolvedNamespaceSymbol != none {
          collectSymbol(member.resolvedNamespaceSymbol!, rootPath, index)
        }
        if member.resolvedStaticOwner != none && member.resolvedStaticOwner!.resolvedSymbol != none {
          collectSymbol(member.resolvedStaticOwner!.resolvedSymbol!, rootPath, index)
        }
      }
      _ -> { }
    }
    collectWorldviewNestedExpressions(current, expressions)
  }
}

function collectType(
  type_: ResolvedType,
  rootPath: string,
  index: WorldviewIndex,
): none {
  case type_ {
    class_: ClassType -> {
      collectSymbol(class_.symbol, rootPath, index)
      for argument of class_.typeArgs { collectType(argument, rootPath, index) }
    }
    enum_: EnumType -> { collectSymbol(enum_.symbol, rootPath, index) }
    interface_: InterfaceType -> {
      collectSymbol(interface_.symbol, rootPath, index)
      if interface_.typeArgs.length > 0 {
        addInterfaceKey(index, interfaceInstantiationKey(interface_.symbol.module, interface_.name, interface_.typeArgs))
      }
      for implementation of interface_.symbol.implementations {
        collectSymbol(implementation, rootPath, index)
      }
      for argument of interface_.typeArgs { collectType(argument, rootPath, index) }
    }
    actor: ActorType -> { collectType(actor.innerClass, rootPath, index) }
    promise: PromiseType -> { collectType(promise.valueType, rootPath, index) }
    array: ArrayResolvedType -> { collectType(array.elementType, rootPath, index) }
    map: MapResolvedType -> {
      collectType(map.keyType, rootPath, index)
      collectType(map.valueType, rootPath, index)
    }
    set_: SetResolvedType -> { collectType(set_.elementType, rootPath, index) }
    stream: StreamResolvedType -> {
      addInterfaceKey(index, interfaceInstantiationKey("", "Stream", [stream.elementType]))
      collectType(stream.elementType, rootPath, index)
    }
    result_: ResultResolvedType -> {
      collectType(result_.valueType, rootPath, index)
      collectType(result_.errorType, rootPath, index)
    }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectType(element, rootPath, index) } }
    union_: UnionResolvedType -> { for member of union_.types { collectType(member, rootPath, index) } }
    weak_: WeakResolvedType -> { collectType(weak_.inner, rootPath, index) }
    function_: FunctionType -> {
      for parameter of function_.params { collectType(parameter.type_, rootPath, index) }
      collectType(function_.returnType, rootPath, index)
    }
    _ -> { }
  }
}

function collectSymbol(
  symbol: Symbol,
  rootPath: string,
  index: WorldviewIndex,
): none {
  if symbol.module == "" { return }
  name := if symbol.originalName == "" then symbol.name else symbol.originalName
  key := symbol.module + "::" + symbol.kind + "::" + name
  if index.selectedKeys.has(key) { return }
  index.selectedKeys.add(key)
  if symbol.module == rootPath {
    collectNativeHeaderClosure(symbol, rootPath, index)
    return
  }
  declaration := declarationFor(index, symbol.module, name)
  if declaration == none { return }
  selection := selectionFor(index, symbol.module)
  selection.statements.push(declaration!)
  collectStatementSurface(declaration!, rootPath, index, true)
  // A native header is an opaque C++ compilation unit from Doof's point of
  // view. Select every native declaration in the defining module that shares
  // it so the header receives the complete alias prelude it may require.
  collectNativeHeaderClosure(symbol, rootPath, index)
}

function collectNativeHeaderClosure(
  symbol: Symbol,
  rootPath: string,
  index: WorldviewIndex,
): none {
  if symbol.native_ && symbol.nativeHeader != "" {
    module := findModule(index, symbol.module)
    if module != none {
      for sibling of module!.symbols {
        if sibling.native_ && sibling.nativeHeader == symbol.nativeHeader {
          collectSymbol(sibling, rootPath, index)
        }
      }
      // Native headers are intentionally opaque. Their supported Doof-facing
      // surface is the nominal imports/exports of their defining module, so
      // project those declarations completely before including the header.
      for imported of module!.imports {
        if imported.symbol != none && isNominalSurfaceSymbol(imported.symbol!) {
          collectSymbol(imported.symbol!, rootPath, index)
        }
      }
      for exported of module!.exports {
        if isNominalSurfaceSymbol(exported) { collectSymbol(exported, rootPath, index) }
      }
      for reExportPath of module!.reExports {
        reExported := findModule(index, reExportPath)
        if reExported == none { continue }
        for exported of reExported!.exports {
          if isNominalSurfaceSymbol(exported) { collectSymbol(exported, rootPath, index) }
        }
      }
    }
  }
}

function isNominalSurfaceSymbol(symbol: Symbol): bool {
  return symbol.kind == "class" || symbol.kind == "struct" || symbol.kind == "enum"
    || symbol.kind == "interface" || symbol.kind == "type-alias"
}

function collectStatementSurface(
  statement: Statement,
  rootPath: string,
  index: WorldviewIndex,
  foreign: bool,
): none {
  case statement {
    export_: ExportDeclaration -> { collectStatementSurface(export_.declaration, rootPath, index, foreign) }
    fn: FunctionDeclaration -> {
      if fn.resolvedType != none { collectType(fn.resolvedType!, rootPath, index) }
      if fn.returnType != none { collectAnnotationAliases(fn.returnType!, rootPath, index) }
      for parameter of fn.params {
        if parameter.resolvedType != none { collectType(parameter.resolvedType!, rootPath, index) }
        if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, rootPath, index) }
        if parameter.defaultValue != none { collectExpressionTree(parameter.defaultValue!, rootPath, index) }
      }
      if !foreign { collectFunctionBody(fn, rootPath, index) }
    }
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if field.resolvedType != none { collectType(field.resolvedType!, rootPath, index) }
        if field.type_ != none { collectAnnotationAliases(field.type_!, rootPath, index) }
        if field.defaultValue != none { collectExpressionTree(field.defaultValue!, rootPath, index) }
      }
      for method of class_.methods {
        if method.resolvedType != none { collectType(method.resolvedType!, rootPath, index) }
        if method.returnType != none { collectAnnotationAliases(method.returnType!, rootPath, index) }
        for parameter of method.params {
          if parameter.resolvedType != none { collectType(parameter.resolvedType!, rootPath, index) }
          if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, rootPath, index) }
          if parameter.defaultValue != none { collectExpressionTree(parameter.defaultValue!, rootPath, index) }
        }
        if !foreign { collectFunctionBody(method, rootPath, index) }
      }
      if class_.resolvedSymbol != none {
        for implementation of class_.resolvedSymbol!.implementations {
          collectSymbol(implementation, rootPath, index)
        }
      }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields {
        if field.resolvedType != none { collectType(field.resolvedType!, rootPath, index) }
        collectAnnotationAliases(field.type_, rootPath, index)
      }
      for method of interface_.methods {
        if method.resolvedType != none { collectType(method.resolvedType!, rootPath, index) }
        if method.returnType != none { collectAnnotationAliases(method.returnType!, rootPath, index) }
        for parameter of method.params { if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, rootPath, index) } }
      }
      if interface_.resolvedSymbol != none {
        for implementation of interface_.resolvedSymbol!.implementations {
          collectSymbol(implementation, rootPath, index)
        }
      }
    }
    alias: TypeAliasDeclaration -> {
      if alias.resolvedType != none { collectType(alias.resolvedType!, rootPath, index) }
      collectAnnotationAliases(alias.type_, rootPath, index)
    }
    const_: ConstDeclaration -> {
      if const_.resolvedType != none { collectType(const_.resolvedType!, rootPath, index) }
      if const_.type_ != none { collectAnnotationAliases(const_.type_!, rootPath, index) }
    }
    readonly_: ReadonlyDeclaration -> {
      if readonly_.resolvedType != none { collectType(readonly_.resolvedType!, rootPath, index) }
      if readonly_.type_ != none { collectAnnotationAliases(readonly_.type_!, rootPath, index) }
    }
    binding: ImmutableBinding -> {
      if binding.resolvedType != none { collectType(binding.resolvedType!, rootPath, index) }
      if binding.type_ != none { collectAnnotationAliases(binding.type_!, rootPath, index) }
    }
    enum_: EnumDeclaration -> {
      for variant of enum_.variants { if variant.value != none { collectExpressionTree(variant.value!, rootPath, index) } }
    }
    _ -> { }
  }
}

function collectAnnotationAliases(
  annotation: TypeAnnotation,
  rootPath: string,
  index: WorldviewIndex,
): none {
  case annotation {
    named: NamedType -> {
      if named.resolvedSymbol != none && named.resolvedSymbol!.kind == "type-alias" {
        collectSymbol(named.resolvedSymbol!, rootPath, index)
      }
      for argument of named.typeArgs { collectAnnotationAliases(argument, rootPath, index) }
    }
    array: ArrayType -> { collectAnnotationAliases(array.elementType, rootPath, index) }
    union_: UnionType -> { for member of union_.types { collectAnnotationAliases(member, rootPath, index) } }
    function_: AstFunctionType -> {
      for parameter of function_.params { collectAnnotationAliases(parameter.type_, rootPath, index) }
      collectAnnotationAliases(function_.returnType, rootPath, index)
    }
    weak_: WeakType -> { collectAnnotationAliases(weak_.type_, rootPath, index) }
  }
}

function collectFunctionBody(
  fn: FunctionDeclaration,
  rootPath: string,
  index: WorldviewIndex,
): none {
  let expressions: Expression[] = []
  case fn.body {
    block: Block -> { collectWorldviewBlockExpressions(block, expressions) }
    expression: Expression -> { expressions.push(expression) }
  }
  for expression of expressions { collectExpressionTree(expression, rootPath, index) }
}

function declarationFor(index: WorldviewIndex, modulePath: string, name: string): Statement | none {
  declaration := index.graph.declarations.get(declarationKey(modulePath, name)) else { return none }
  return declaration
}

function statementName(statement: Statement): string {
  case statement {
    export_: ExportDeclaration -> { return statementName(export_.declaration) }
    class_: ClassDeclaration -> { return class_.name }
    fn: FunctionDeclaration -> { return fn.name }
    interface_: InterfaceDeclaration -> { return interface_.name }
    enum_: EnumDeclaration -> { return enum_.name }
    alias: TypeAliasDeclaration -> { return alias.name }
    const_: ConstDeclaration -> { return const_.name }
    readonly_: ReadonlyDeclaration -> { return readonly_.name }
    binding: ImmutableBinding -> { return binding.name }
    _ -> { return "" }
  }
  return ""
}

export function indexWorldviewGraph(result: AnalysisResult): WorldviewGraphIndex {
  index := WorldviewGraphIndex {}
  for module of result.modules {
    if !index.modules.has(module.path) { index.modules.set(module.path, module) }
    for statement of module.program.statements {
      name := statementName(statement)
      key := declarationKey(module.path, name)
      if name != "" && !index.declarations.has(key) { index.declarations.set(key, statement) }
    }
    for symbol of module.symbols {
      name := if symbol.originalName == "" then symbol.name else symbol.originalName
      key := declarationKey(module.path, name)
      if !index.symbols.has(key) { index.symbols.set(key, symbol) }
    }
  }
  return index
}

function declarationKey(modulePath: string, name: string): string {
  return modulePath + "\n" + name
}

function findModule(index: WorldviewIndex, path: string): ModuleInfo | none {
  module := index.graph.modules.get(path) else { return none }
  return module
}

function findSymbol(index: WorldviewIndex, modulePath: string, name: string): Symbol | none {
  symbol := index.graph.symbols.get(declarationKey(modulePath, name)) else { return none }
  return symbol
}

function selectionFor(index: WorldviewIndex, path: string): WorldviewSelection {
  existing := findSelection(index, path)
  if existing != none { return existing! }
  selection := WorldviewSelection {}
  index.selections.set(path, selection)
  return selection
}

function findSelection(index: WorldviewIndex, path: string): WorldviewSelection | none {
  selection := index.selections.get(path) else { return none }
  return selection
}
