import { SemanticTypeIdentities } from "./semantic-type-identities"
// Exact foreign declaration selection for one generated C++ translation unit.
//
// This is a transient lowering plan. It consumes checker decorations and never
// persists or reconstructs module semantics.

import {
  ClassDeclaration, ConstDeclaration, EnumDeclaration, ExportDeclaration, Expression, FunctionDeclaration,
  ImmutableBinding, InterfaceDeclaration, Program, ReadonlyDeclaration, Statement, TypeAliasDeclaration,
} from "./ast"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import { InstantiationPlan } from "./emitter-monomorphize"
import { collectStatementExpressions } from "./ast-walk"
import { Symbol, ResolvedType } from "./semantic"
import {
  DependencyBuilder, DependencySummary, SymbolDependency, InterfaceDependency,
  collectDependencySurface, collectDependencyExpression, collectDependencyType,
  dependencyForSymbol, summarizeDeclaration,
} from "./emitter-dependencies"

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

// One index belongs to a checked graph. Declaration summaries are frozen before
// any consumer runs; checked AST/module references still require serial use.
// Selection and traversal visitation live exclusively in WorldviewIndex.
export class WorldviewGraphIndex {
  identityPreparation: SemanticTypeIdentities | none = none
  modules: Map<string, ModuleInfo> = {}
  declarations: Map<string, Statement> = {}
  symbols: Map<string, Symbol> = {}
  readonly summaries: readonly Map<string, DependencySummary> = {}
}

class WorldviewIndex {
  // Opaque native surfaces expand once per consumer, including recursive cycles.
  expandedNativeHeaders: Set<string> = []
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
  dependencies := DependencyBuilder { identities: index.graph.identityPreparation }
  for statement of root!.program.statements {
    collectDependencySurface(statement, dependencies, false)
    let expressions: Expression[] = []
    collectStatementExpressions(statement, expressions)
    for expression of expressions { collectDependencyExpression(expression, dependencies) }
  }
  replayDependencies(dependencies.finish(), rootPath, index)
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
    // Generic bodies are emitted in their defining module. Their concrete
    // arguments can come from callers with no import edge back to that module.
    for function_ of instantiations!.functions {
      if function_.modulePath != rootPath { continue }
      for argument of function_.substitution.arguments { collectArgumentDependencies(argument, rootPath, index) }
    }
    for class_ of instantiations!.classes {
      if class_.modulePath != rootPath { continue }
      for argument of class_.substitution.arguments { collectArgumentDependencies(argument, rootPath, index) }
    }
    for method of instantiations!.methods {
      if method.modulePath != rootPath { continue }
      for argument of method.substitution.arguments { collectArgumentDependencies(argument, rootPath, index) }
    }
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

function collectSymbol(
  symbol: Symbol,
  rootPath: string,
  index: WorldviewIndex,
): none {
  collectSymbolDependency(dependencyForSymbol(symbol), rootPath, index)
}

function collectArgumentDependencies(type_: ResolvedType, rootPath: string, index: WorldviewIndex): none {
  builder := DependencyBuilder { identities: index.graph.identityPreparation }
  collectDependencyType(type_, builder)
  replayDependencies(builder.finish(), rootPath, index)
}

function replayDependencies(summary: DependencySummary, rootPath: string, index: WorldviewIndex): none {
  for event of summary.events {
    case event {
      symbol: SymbolDependency -> { collectSymbolDependency(symbol, rootPath, index) }
      interface_: InterfaceDependency -> { addInterfaceKey(index, interface_.key) }
    }
  }
}

function collectSymbolDependency(symbol: SymbolDependency, rootPath: string, index: WorldviewIndex): none {
  if symbol.modulePath == "" || index.selectedKeys.has(symbol.key) { return }
  index.selectedKeys.add(symbol.key)
  if symbol.modulePath == rootPath {
    collectNativeHeaderClosure(symbol, rootPath, index)
    return
  }
  declaration := declarationFor(index, symbol.modulePath, symbol.name)
  if declaration == none { return }
  selection := selectionFor(index, symbol.modulePath)
  selection.statements.push(declaration!)
  summary := try! index.graph.summaries.get(declarationKey(symbol.modulePath, symbol.name))
  replayDependencies(summary, rootPath, index)
  collectNativeHeaderClosure(symbol, rootPath, index)
}

function collectNativeHeaderClosure(
  symbol: SymbolDependency,
  rootPath: string,
  index: WorldviewIndex,
): none {
  if symbol.nativeHeader != "" {
    // Length-prefix the module so arbitrary path/header strings cannot collide.
    key := string(symbol.modulePath.length) + ":" + symbol.modulePath + symbol.nativeHeader
    if index.expandedNativeHeaders.has(key) { return }
    index.expandedNativeHeaders.add(key)
    module := findModule(index, symbol.modulePath)
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

export function indexWorldviewGraph(result: AnalysisResult, identities: SemanticTypeIdentities | none = none): WorldviewGraphIndex {
  modules: Map<string, ModuleInfo> := {}
  declarations: Map<string, Statement> := {}
  symbols: Map<string, Symbol> := {}
  summaries: Map<string, DependencySummary> := {}
  for module of result.modules {
    if !modules.has(module.path) { modules.set(module.path, module) }
    for statement of module.program.statements {
      name := statementName(statement)
      key := declarationKey(module.path, name)
      if name != "" && !declarations.has(key) {
        declarations.set(key, statement)
        summaries.set(key, summarizeDeclaration(statement, identities))
      }
    }
    for symbol of module.symbols {
      name := if symbol.originalName == "" then symbol.name else symbol.originalName
      key := declarationKey(module.path, name)
      if !symbols.has(key) { symbols.set(key, symbol) }
    }
  }
  return WorldviewGraphIndex { identityPreparation: identities, modules, declarations, symbols, summaries: summaries.drainToReadonly() }
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
