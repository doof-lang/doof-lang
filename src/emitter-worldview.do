import { SemanticTypeIdentities } from "./semantic-type-identities"
// Exact foreign declaration selection for one generated C++ translation unit.
//
// This is a transient lowering plan. It consumes checker decorations and never
// persists or reconstructs module semantics.

import { ClassDeclaration, Expression, Program, Statement } from "./ast"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  DeclarationIndex, declarationKey, declarationName, indexDeclarations, indexedClass, indexedDeclaration, indexedModule,
} from "./emitter-declarations"
import { InstantiationPlan } from "./emitter-monomorphize"
import { collectStatementExpressions } from "./ast-walk"
import { Symbol, ResolvedType } from "./semantic"
import {
  DependencyBuilder, DependencySummary, SymbolDependency, InterfaceDependency,
  collectDependencySurface, collectDependencyExpression, collectDependencyType, collectCompleteDependencyType,
  dependencyForSymbol, summarizeDeclaration,
} from "./emitter-dependencies"

export class WorldviewModule {
  path: string
  program: Program
  forwardClassNames: string[] = []
}

export class WorldviewPlan {
  modules: WorldviewModule[] = []
  let interfaceKeys: string[] = []
}

class WorldviewSelection {
  statements: Statement[] = []
  forwardClassNames: string[] = []
}

// One index belongs to a checked graph. Declaration summaries are frozen before
// any consumer runs; checked AST/module references still require serial use.
// Selection and traversal visitation live exclusively in WorldviewIndex.
export class WorldviewGraphIndex {
  identityPreparation: SemanticTypeIdentities | none = none
  declarations: DeclarationIndex = DeclarationIndex {}
  symbols: Map<string, Symbol> = {}
  readonly summaries: readonly Map<string, DependencySummary> = {}
}

class WorldviewIndex {
  // Opaque native surfaces expand once per consumer, including recursive cycles.
  expandedNativeHeaders: Set<string> = []
  // Explicit named type imports are part of a module's intentional generated
  // surface. Expand them once so generated consumers can use complete nominal
  // declarations even when the handwritten signature only needs a pointer.
  expandedExplicitTypeImports: Set<string> = []
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

  // An explicit type import is stronger than an inferred signature dependency:
  // generated code may inspect or serialize the imported value after the
  // handwritten AST has been projected. Keep this rule independent of any
  // particular generated consumer such as the wasm JSON adapter.
  collectExplicitTypeImports(root!, rootPath, index)

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
  // Generated JSON methods are emitted in the owning module's source, but
  // their field operations are not present in its handwritten AST. They call
  // through every field's concrete type, so select those definitions before
  // projecting the owner header rather than leaving a forward declaration in
  // the generated translation unit.
  if instantiations != none {
    collectGeneratedJsonDependencies(root!.program, rootPath, instantiations!, index)
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
  if path != rootPath && (selection == none || (selection!.statements.length == 0 && selection!.forwardClassNames.length == 0)) { return }
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
      forwardClassNames: forwardNamesWithoutDefinitions(selection!),
    })
  }
}

function forwardNamesWithoutDefinitions(selection: WorldviewSelection): string[] {
  let result: string[] = []
  for name of selection.forwardClassNames {
    let defined = false
    for statement of selection.statements {
      if declarationName(statement) == name { defined = true; break }
    }
    if !defined { result.push(name) }
  }
  return result
}

function addInterfaceKey(index: WorldviewIndex, value: string): none {
  if index.interfaceKeySet.has(value) { return }
  index.interfaceKeySet.add(value)
  index.interfaceKeys.push(value)
}

function orderedSelectionStatements(info: ModuleInfo, selection: WorldviewSelection): Statement[] {
  let ordered: Statement[] = []
  let selectedNames: Set<string> = []
  for selected of selection.statements { selectedNames.add(declarationName(selected)) }
  for candidate of info.program.statements {
    name := declarationName(candidate)
    if name != "" && selectedNames.has(name) { ordered.push(candidate) }
  }
  return ordered
}

function collectSymbol(
  symbol: Symbol,
  rootPath: string,
  index: WorldviewIndex,
  forceTransitiveDefinitions: bool = false,
): none {
  collectSymbolDependency(dependencyForSymbol(symbol), rootPath, index, forceTransitiveDefinitions)
}

function collectArgumentDependencies(type_: ResolvedType, rootPath: string, index: WorldviewIndex): none {
  builder := DependencyBuilder { identities: index.graph.identityPreparation }
  collectDependencyType(type_, builder)
  replayDependencies(builder.finish(), rootPath, index)
}

function collectGeneratedJsonDependencies(program: Program, rootPath: string, instantiations: InstantiationPlan, index: WorldviewIndex): none {
  for statement of program.statements {
    collectGeneratedJsonDeclarationDependencies(statement, rootPath, instantiations, index)
  }
}

function collectGeneratedJsonDeclarationDependencies(statement: Statement, rootPath: string, instantiations: InstantiationPlan, index: WorldviewIndex): none {
  case statement {
    class_: ClassDeclaration -> {
      key := rootPath + "::" + class_.name
      if !instantiations.jsonSerializationKeys.contains(key) && !instantiations.jsonDeserializationKeys.contains(key) { return }
      dependencies := DependencyBuilder { identities: index.graph.identityPreparation }
      for field of class_.fields {
        if !field.static_ && field.resolvedType != none { collectCompleteDependencyType(field.resolvedType!, dependencies) }
      }
      replayDependencies(dependencies.finish(), rootPath, index, true)
    }
    _ -> { }
  }
}

function replayDependencies(summary: DependencySummary, rootPath: string, index: WorldviewIndex, forceDefinitions: bool = false): none {
  for event of summary.events {
    case event {
      symbol: SymbolDependency -> { collectSymbolDependency(symbol, rootPath, index, forceDefinitions) }
      interface_: InterfaceDependency -> { addInterfaceKey(index, interface_.key) }
    }
  }
}

function collectSymbolDependency(
  symbol: SymbolDependency,
  rootPath: string,
  index: WorldviewIndex,
  forceTransitiveDefinitions: bool = false,
): none {
  if symbol.modulePath == "" { return }
  if symbol.forwardOnly && !forceTransitiveDefinitions {
    if index.selectedKeys.has(symbol.key) { return }
    if indexedClass(index.graph.declarations, symbol.modulePath, symbol.name) == none { return }
    selection := selectionFor(index, symbol.modulePath)
    if !selection.forwardClassNames.contains(symbol.name) { selection.forwardClassNames.push(symbol.name) }
    return
  }
  if index.selectedKeys.has(symbol.key) { return }
  index.selectedKeys.add(symbol.key)
  if symbol.modulePath == rootPath {
    collectNativeHeaderClosure(symbol, rootPath, index)
    return
  }
  declaration := declarationFor(index, symbol.modulePath, symbol.name)
  if declaration == none { return }
  selection := selectionFor(index, symbol.modulePath)
  selection.statements.push(declaration!)
  collectExplicitTypeImports(findModule(index, symbol.modulePath)!, rootPath, index)
  summary := index.graph.summaries.get(declarationKey(symbol.modulePath, symbol.name))!
  replayDependencies(summary, rootPath, index, forceTransitiveDefinitions)
  collectNativeHeaderClosure(symbol, rootPath, index)
}

function collectExplicitTypeImports(info: ModuleInfo, rootPath: string, index: WorldviewIndex): none {
  if index.expandedExplicitTypeImports.has(info.path) { return }
  index.expandedExplicitTypeImports.add(info.path)
  for imported of info.imports {
    if imported.symbol == none || !isNominalSurfaceSymbol(imported.symbol!) { continue }
    collectSymbol(imported.symbol!, rootPath, index)
  }
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
          collectSymbol(sibling, rootPath, index, true)
        }
      }
      // Native headers are intentionally opaque. Their supported Doof-facing
      // surface is the nominal imports/exports of their defining module, so
      // project those declarations completely before including the header.
      for imported of module!.imports {
        if imported.symbol != none && isNominalSurfaceSymbol(imported.symbol!) {
          collectSymbol(imported.symbol!, rootPath, index, true)
        }
      }
      for exported of module!.exports {
        if isNominalSurfaceSymbol(exported) { collectSymbol(exported, rootPath, index, true) }
      }
      for reExportPath of module!.reExports {
        reExported := findModule(index, reExportPath)
        if reExported == none { continue }
        for exported of reExported!.exports {
          if isNominalSurfaceSymbol(exported) { collectSymbol(exported, rootPath, index, true) }
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
  return indexedDeclaration(index.graph.declarations, modulePath, name)
}

export function indexWorldviewGraph(
  result: AnalysisResult,
  identities: SemanticTypeIdentities | none = none,
  declarations: DeclarationIndex | none = none,
): WorldviewGraphIndex {
  graph := declarations ?? indexDeclarations(result)
  symbols: Map<string, Symbol> := {}
  summaries: Map<string, DependencySummary> := {}
  for module of result.modules {
    for symbol of module.symbols {
      name := if symbol.originalName == "" then symbol.name else symbol.originalName
      key := declarationKey(module.path, name)
      if !symbols.has(key) { symbols.set(key, symbol) }
    }
  }
  for key, statement of graph.declarations { summaries.set(key, summarizeDeclaration(statement, identities)) }
  return WorldviewGraphIndex { identityPreparation: identities, declarations: graph, symbols, summaries: summaries.drainToReadonly() }
}

function findModule(index: WorldviewIndex, path: string): ModuleInfo | none {
  return indexedModule(index.graph.declarations, path)
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
