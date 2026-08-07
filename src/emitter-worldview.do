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
  path: string
  statements: Statement[] = []
}

export function planWorldview(result: AnalysisResult, rootPath: string, instantiations: InstantiationPlan | none = none): WorldviewPlan {
  root := findModule(result, rootPath)
  if root == none { return WorldviewPlan {} }
  let selections: WorldviewSelection[] = []
  let selectedKeys: string[] = []

  // The root owns every declaration it defines. Foreign declarations are
  // selected only from checked uses and their recursive declaration surface.
  for statement of root!.program.statements {
    collectStatementSurface(statement, rootPath, result, selections, selectedKeys, false)
    let expressions: Expression[] = []
    collectWorldviewStatementExpressions(statement, expressions)
    for expression of expressions { collectExpressionTree(expression, rootPath, result, selections, selectedKeys) }
  }
  // The root header owns all of its declarations, including every native
  // declaration it exposes. Seed each opaque native-header surface even though
  // resolving a root symbol does not add a foreign statement.
  for symbol of root!.symbols {
    if symbol.native_ && symbol.nativeHeader != "" {
      collectSymbol(symbol, rootPath, result, selections, selectedKeys)
    }
  }
  // Re-exported declarations are part of the root module's own public header
  // surface even when its implementation never references them.
  for symbol of root!.exports {
    if symbol.module != "" && symbol.module != rootPath {
      collectSymbol(symbol, rootPath, result, selections, selectedKeys)
    }
  }

  let interfaceKeys: string[] = []
  collectProgramInterfaceKeys(root!.program, interfaceKeys)
  for selection of selections { for statement of selection.statements { collectStatementInterfaceKeys(statement, interfaceKeys) } }
  if instantiations != none {
    for interface_ of instantiations!.interfaces {
      if !containsString(interfaceKeys, interface_.key) { continue }
      for implementation of interface_.implementations {
        let name = implementation.typeName
        for class_ of instantiations!.classes {
          if class_.modulePath == implementation.modulePath && class_.emittedName == implementation.typeName {
            name = class_.declaration.name
            break
          }
        }
        module := findModule(result, implementation.modulePath)
        if module == none { continue }
        for symbol of module!.symbols {
          original := if symbol.originalName == "" then symbol.name else symbol.originalName
          if original == name { collectSymbol(symbol, rootPath, result, selections, selectedKeys); break }
        }
      }
    }
  }

  plan := WorldviewPlan {}
  plan.interfaceKeys = interfaceKeys
  let visitedPaths: string[] = []
  let visitingPaths: string[] = []
  // Concrete interface implementors can be selected against the import edge,
  // so visit every selected foreign module before the root. Each visit follows
  // ordinary imports/re-exports dependency-first.
  for info of result.modules {
    if info.path != rootPath && findSelection(selections, info.path) != none {
      appendWorldviewModule(result, info.path, rootPath, selections, plan, visitingPaths, visitedPaths)
    }
  }
  appendWorldviewModule(result, rootPath, rootPath, selections, plan, visitingPaths, visitedPaths)
  return plan
}

function appendWorldviewModule(
  result: AnalysisResult,
  path: string,
  rootPath: string,
  selections: WorldviewSelection[],
  plan: WorldviewPlan,
  visiting: string[],
  visited: string[],
): none {
  if containsString(visited, path) || containsString(visiting, path) { return }
  info := findModule(result, path)
  if info == none { return }
  selection := findSelection(selections, path)
  if path != rootPath && (selection == none || selection!.statements.length == 0) { return }
  visiting.push(path)
  for imported of info!.imports {
    if imported.sourceModule != rootPath {
      appendWorldviewModule(result, imported.sourceModule, rootPath, selections, plan, visiting, visited)
    }
  }
  for reExport of info!.reExports {
    if reExport != rootPath { appendWorldviewModule(result, reExport, rootPath, selections, plan, visiting, visited) }
  }
  ignored := try! visiting.pop()
  if containsString(visited, path) { return }
  visited.push(path)
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

function collectProgramInterfaceKeys(program: Program, keys: string[]): none {
  for statement of program.statements { collectStatementInterfaceKeys(statement, keys) }
}

function collectStatementInterfaceKeys(statement: Statement, keys: string[]): none {
  case statement {
    export_: ExportDeclaration -> { collectStatementInterfaceKeys(export_.declaration, keys) }
    fn: FunctionDeclaration -> {
      if fn.resolvedType != none { collectTypeInterfaceKeys(fn.resolvedType!, keys) }
      for parameter of fn.params {
        if parameter.resolvedType != none { collectTypeInterfaceKeys(parameter.resolvedType!, keys) }
        if parameter.defaultValue != none { collectExpressionInterfaceKeys(parameter.defaultValue!, keys) }
      }
      let expressions: Expression[] = []
      case fn.body {
        block: Block -> { collectWorldviewBlockExpressions(block, expressions) }
        expression: Expression -> { expressions.push(expression) }
      }
      for expression of expressions { collectExpressionInterfaceKeys(expression, keys) }
    }
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if field.resolvedType != none { collectTypeInterfaceKeys(field.resolvedType!, keys) }
        if field.defaultValue != none { collectExpressionInterfaceKeys(field.defaultValue!, keys) }
      }
      for method of class_.methods { collectStatementInterfaceKeys(method, keys) }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields { if field.resolvedType != none { collectTypeInterfaceKeys(field.resolvedType!, keys) } }
      for method of interface_.methods { collectStatementInterfaceKeys(method, keys) }
    }
    alias: TypeAliasDeclaration -> { if alias.resolvedType != none { collectTypeInterfaceKeys(alias.resolvedType!, keys) } }
    const_: ConstDeclaration -> { if const_.resolvedType != none { collectTypeInterfaceKeys(const_.resolvedType!, keys) } }
    readonly_: ReadonlyDeclaration -> { if readonly_.resolvedType != none { collectTypeInterfaceKeys(readonly_.resolvedType!, keys) } }
    binding: ImmutableBinding -> { if binding.resolvedType != none { collectTypeInterfaceKeys(binding.resolvedType!, keys) } }
    _ -> { }
  }
}

function collectExpressionInterfaceKeys(expression: Expression, keys: string[]): none {
  if expression.resolvedType != none { collectTypeInterfaceKeys(expression.resolvedType!, keys) }
  let nested: Expression[] = []
  collectWorldviewNestedExpressions(expression, nested)
  for child of nested { collectExpressionInterfaceKeys(child, keys) }
}

function collectTypeInterfaceKeys(type_: ResolvedType, keys: string[]): none {
  case type_ {
    interface_: InterfaceType -> {
      if interface_.typeArgs.length > 0 { addUniqueString(keys, interfaceInstantiationKey(interface_.symbol.module, interface_.name, interface_.typeArgs)) }
      for argument of interface_.typeArgs { collectTypeInterfaceKeys(argument, keys) }
    }
    stream: StreamResolvedType -> {
      addUniqueString(keys, interfaceInstantiationKey("", "Stream", [stream.elementType]))
      collectTypeInterfaceKeys(stream.elementType, keys)
    }
    class_: ClassType -> { for argument of class_.typeArgs { collectTypeInterfaceKeys(argument, keys) } }
    actor: ActorType -> { collectTypeInterfaceKeys(actor.innerClass, keys) }
    promise: PromiseType -> { collectTypeInterfaceKeys(promise.valueType, keys) }
    array: ArrayResolvedType -> { collectTypeInterfaceKeys(array.elementType, keys) }
    map: MapResolvedType -> { collectTypeInterfaceKeys(map.keyType, keys); collectTypeInterfaceKeys(map.valueType, keys) }
    set_: SetResolvedType -> { collectTypeInterfaceKeys(set_.elementType, keys) }
    result_: ResultResolvedType -> { collectTypeInterfaceKeys(result_.valueType, keys); collectTypeInterfaceKeys(result_.errorType, keys) }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectTypeInterfaceKeys(element, keys) } }
    union_: UnionResolvedType -> { for member of union_.types { collectTypeInterfaceKeys(member, keys) } }
    weak_: WeakResolvedType -> { collectTypeInterfaceKeys(weak_.inner, keys) }
    function_: FunctionType -> {
      for parameter of function_.params { collectTypeInterfaceKeys(parameter.type_, keys) }
      collectTypeInterfaceKeys(function_.returnType, keys)
    }
    _ -> { }
  }
}

function addUniqueString(values: string[], value: string): none {
  if !containsString(values, value) { values.push(value) }
}

function orderedSelectionStatements(info: ModuleInfo, selection: WorldviewSelection): Statement[] {
  let ordered: Statement[] = []
  for candidate of info.program.statements {
    name := statementName(candidate)
    if name == "" { continue }
    for selected of selection.statements {
      if statementName(selected) == name { ordered.push(candidate); break }
    }
  }
  return ordered
}

function collectExpressionTree(
  expression: Expression,
  rootPath: string,
  result: AnalysisResult,
  selections: WorldviewSelection[],
  selectedKeys: string[],
): none {
  if expression.resolvedType != none { collectType(expression.resolvedType!, rootPath, result, selections, selectedKeys) }
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding != none && identifier.resolvedBinding!.symbol != none {
        collectSymbol(identifier.resolvedBinding!.symbol!, rootPath, result, selections, selectedKeys)
      }
    }
    member: MemberExpression -> {
      if member.resolvedNamespaceSymbol != none {
        collectSymbol(member.resolvedNamespaceSymbol!, rootPath, result, selections, selectedKeys)
      }
      if member.resolvedStaticOwner != none && member.resolvedStaticOwner!.resolvedSymbol != none {
        collectSymbol(member.resolvedStaticOwner!.resolvedSymbol!, rootPath, result, selections, selectedKeys)
      }
    }
    _ -> { }
  }
  let nested: Expression[] = []
  collectWorldviewNestedExpressions(expression, nested)
  for child of nested { collectExpressionTree(child, rootPath, result, selections, selectedKeys) }
}

function collectType(
  type_: ResolvedType,
  rootPath: string,
  result: AnalysisResult,
  selections: WorldviewSelection[],
  selectedKeys: string[],
): none {
  case type_ {
    class_: ClassType -> {
      collectSymbol(class_.symbol, rootPath, result, selections, selectedKeys)
      for argument of class_.typeArgs { collectType(argument, rootPath, result, selections, selectedKeys) }
    }
    enum_: EnumType -> { collectSymbol(enum_.symbol, rootPath, result, selections, selectedKeys) }
    interface_: InterfaceType -> {
      collectSymbol(interface_.symbol, rootPath, result, selections, selectedKeys)
      for implementation of interface_.symbol.implementations {
        collectSymbol(implementation, rootPath, result, selections, selectedKeys)
      }
      for argument of interface_.typeArgs { collectType(argument, rootPath, result, selections, selectedKeys) }
    }
    actor: ActorType -> { collectType(actor.innerClass, rootPath, result, selections, selectedKeys) }
    promise: PromiseType -> { collectType(promise.valueType, rootPath, result, selections, selectedKeys) }
    array: ArrayResolvedType -> { collectType(array.elementType, rootPath, result, selections, selectedKeys) }
    map: MapResolvedType -> {
      collectType(map.keyType, rootPath, result, selections, selectedKeys)
      collectType(map.valueType, rootPath, result, selections, selectedKeys)
    }
    set_: SetResolvedType -> { collectType(set_.elementType, rootPath, result, selections, selectedKeys) }
    stream: StreamResolvedType -> { collectType(stream.elementType, rootPath, result, selections, selectedKeys) }
    result_: ResultResolvedType -> {
      collectType(result_.valueType, rootPath, result, selections, selectedKeys)
      collectType(result_.errorType, rootPath, result, selections, selectedKeys)
    }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectType(element, rootPath, result, selections, selectedKeys) } }
    union_: UnionResolvedType -> { for member of union_.types { collectType(member, rootPath, result, selections, selectedKeys) } }
    weak_: WeakResolvedType -> { collectType(weak_.inner, rootPath, result, selections, selectedKeys) }
    function_: FunctionType -> {
      for parameter of function_.params { collectType(parameter.type_, rootPath, result, selections, selectedKeys) }
      collectType(function_.returnType, rootPath, result, selections, selectedKeys)
    }
    _ -> { }
  }
}

function collectSymbol(
  symbol: Symbol,
  rootPath: string,
  result: AnalysisResult,
  selections: WorldviewSelection[],
  selectedKeys: string[],
): none {
  if symbol.module == "" { return }
  name := if symbol.originalName == "" then symbol.name else symbol.originalName
  key := symbol.module + "::" + symbol.kind + "::" + name
  if containsString(selectedKeys, key) { return }
  selectedKeys.push(key)
  if symbol.module == rootPath {
    collectNativeHeaderClosure(symbol, rootPath, result, selections, selectedKeys)
    return
  }
  declaration := declarationFor(result, symbol.module, name)
  if declaration == none { return }
  selection := selectionFor(selections, symbol.module)
  selection.statements.push(declaration!)
  collectStatementSurface(declaration!, rootPath, result, selections, selectedKeys, true)
  // A native header is an opaque C++ compilation unit from Doof's point of
  // view. Select every native declaration in the defining module that shares
  // it so the header receives the complete alias prelude it may require.
  collectNativeHeaderClosure(symbol, rootPath, result, selections, selectedKeys)
}

function collectNativeHeaderClosure(
  symbol: Symbol,
  rootPath: string,
  result: AnalysisResult,
  selections: WorldviewSelection[],
  selectedKeys: string[],
): none {
  if symbol.native_ && symbol.nativeHeader != "" {
    module := findModule(result, symbol.module)
    if module != none {
      for sibling of module!.symbols {
        if sibling.native_ && sibling.nativeHeader == symbol.nativeHeader {
          collectSymbol(sibling, rootPath, result, selections, selectedKeys)
        }
      }
      // Native headers are intentionally opaque. Their supported Doof-facing
      // surface is the nominal imports/exports of their defining module, so
      // project those declarations completely before including the header.
      for imported of module!.imports {
        if imported.symbol != none && isNominalSurfaceSymbol(imported.symbol!) {
          collectSymbol(imported.symbol!, rootPath, result, selections, selectedKeys)
        }
      }
      for exported of module!.exports {
        if isNominalSurfaceSymbol(exported) { collectSymbol(exported, rootPath, result, selections, selectedKeys) }
      }
      for reExportPath of module!.reExports {
        reExported := findModule(result, reExportPath)
        if reExported == none { continue }
        for exported of reExported!.exports {
          if isNominalSurfaceSymbol(exported) { collectSymbol(exported, rootPath, result, selections, selectedKeys) }
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
  result: AnalysisResult,
  selections: WorldviewSelection[],
  selectedKeys: string[],
  foreign: bool,
): none {
  case statement {
    export_: ExportDeclaration -> { collectStatementSurface(export_.declaration, rootPath, result, selections, selectedKeys, foreign) }
    fn: FunctionDeclaration -> {
      if fn.resolvedType != none { collectType(fn.resolvedType!, rootPath, result, selections, selectedKeys) }
      if fn.returnType != none { collectAnnotationAliases(fn.returnType!, rootPath, result, selections, selectedKeys) }
      for parameter of fn.params {
        if parameter.resolvedType != none { collectType(parameter.resolvedType!, rootPath, result, selections, selectedKeys) }
        if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, rootPath, result, selections, selectedKeys) }
        if parameter.defaultValue != none { collectExpressionTree(parameter.defaultValue!, rootPath, result, selections, selectedKeys) }
      }
      if !foreign { collectFunctionBody(fn, rootPath, result, selections, selectedKeys) }
    }
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if field.resolvedType != none { collectType(field.resolvedType!, rootPath, result, selections, selectedKeys) }
        if field.type_ != none { collectAnnotationAliases(field.type_!, rootPath, result, selections, selectedKeys) }
        if field.defaultValue != none { collectExpressionTree(field.defaultValue!, rootPath, result, selections, selectedKeys) }
      }
      for method of class_.methods {
        if method.resolvedType != none { collectType(method.resolvedType!, rootPath, result, selections, selectedKeys) }
        if method.returnType != none { collectAnnotationAliases(method.returnType!, rootPath, result, selections, selectedKeys) }
        for parameter of method.params {
          if parameter.resolvedType != none { collectType(parameter.resolvedType!, rootPath, result, selections, selectedKeys) }
          if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, rootPath, result, selections, selectedKeys) }
          if parameter.defaultValue != none { collectExpressionTree(parameter.defaultValue!, rootPath, result, selections, selectedKeys) }
        }
        if !foreign { collectFunctionBody(method, rootPath, result, selections, selectedKeys) }
      }
      if class_.resolvedSymbol != none {
        for implementation of class_.resolvedSymbol!.implementations {
          collectSymbol(implementation, rootPath, result, selections, selectedKeys)
        }
      }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields {
        if field.resolvedType != none { collectType(field.resolvedType!, rootPath, result, selections, selectedKeys) }
        collectAnnotationAliases(field.type_, rootPath, result, selections, selectedKeys)
      }
      for method of interface_.methods {
        if method.resolvedType != none { collectType(method.resolvedType!, rootPath, result, selections, selectedKeys) }
        if method.returnType != none { collectAnnotationAliases(method.returnType!, rootPath, result, selections, selectedKeys) }
        for parameter of method.params { if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, rootPath, result, selections, selectedKeys) } }
      }
      if interface_.resolvedSymbol != none {
        for implementation of interface_.resolvedSymbol!.implementations {
          collectSymbol(implementation, rootPath, result, selections, selectedKeys)
        }
      }
    }
    alias: TypeAliasDeclaration -> {
      if alias.resolvedType != none { collectType(alias.resolvedType!, rootPath, result, selections, selectedKeys) }
      collectAnnotationAliases(alias.type_, rootPath, result, selections, selectedKeys)
    }
    const_: ConstDeclaration -> {
      if const_.resolvedType != none { collectType(const_.resolvedType!, rootPath, result, selections, selectedKeys) }
      if const_.type_ != none { collectAnnotationAliases(const_.type_!, rootPath, result, selections, selectedKeys) }
    }
    readonly_: ReadonlyDeclaration -> {
      if readonly_.resolvedType != none { collectType(readonly_.resolvedType!, rootPath, result, selections, selectedKeys) }
      if readonly_.type_ != none { collectAnnotationAliases(readonly_.type_!, rootPath, result, selections, selectedKeys) }
    }
    binding: ImmutableBinding -> {
      if binding.resolvedType != none { collectType(binding.resolvedType!, rootPath, result, selections, selectedKeys) }
      if binding.type_ != none { collectAnnotationAliases(binding.type_!, rootPath, result, selections, selectedKeys) }
    }
    enum_: EnumDeclaration -> {
      for variant of enum_.variants { if variant.value != none { collectExpressionTree(variant.value!, rootPath, result, selections, selectedKeys) } }
    }
    _ -> { }
  }
}

function collectAnnotationAliases(
  annotation: TypeAnnotation,
  rootPath: string,
  result: AnalysisResult,
  selections: WorldviewSelection[],
  selectedKeys: string[],
): none {
  case annotation {
    named: NamedType -> {
      if named.resolvedSymbol != none && named.resolvedSymbol!.kind == "type-alias" {
        collectSymbol(named.resolvedSymbol!, rootPath, result, selections, selectedKeys)
      }
      for argument of named.typeArgs { collectAnnotationAliases(argument, rootPath, result, selections, selectedKeys) }
    }
    array: ArrayType -> { collectAnnotationAliases(array.elementType, rootPath, result, selections, selectedKeys) }
    union_: UnionType -> { for member of union_.types { collectAnnotationAliases(member, rootPath, result, selections, selectedKeys) } }
    function_: AstFunctionType -> {
      for parameter of function_.params { collectAnnotationAliases(parameter.type_, rootPath, result, selections, selectedKeys) }
      collectAnnotationAliases(function_.returnType, rootPath, result, selections, selectedKeys)
    }
    weak_: WeakType -> { collectAnnotationAliases(weak_.type_, rootPath, result, selections, selectedKeys) }
  }
}

function collectFunctionBody(
  fn: FunctionDeclaration,
  rootPath: string,
  result: AnalysisResult,
  selections: WorldviewSelection[],
  selectedKeys: string[],
): none {
  let expressions: Expression[] = []
  case fn.body {
    block: Block -> { collectWorldviewBlockExpressions(block, expressions) }
    expression: Expression -> { expressions.push(expression) }
  }
  for expression of expressions { collectExpressionTree(expression, rootPath, result, selections, selectedKeys) }
}

function declarationFor(result: AnalysisResult, modulePath: string, name: string): Statement | none {
  module := findModule(result, modulePath)
  if module == none { return none }
  for statement of module!.program.statements {
    if statementName(statement) == name { return statement }
  }
  return none
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

function findModule(result: AnalysisResult, path: string): ModuleInfo | none {
  for module of result.modules { if module.path == path { return module } }
  return none
}

function selectionFor(selections: WorldviewSelection[], path: string): WorldviewSelection {
  existing := findSelection(selections, path)
  if existing != none { return existing! }
  selection := WorldviewSelection { path }
  selections.push(selection)
  return selection
}

function findSelection(selections: WorldviewSelection[], path: string): WorldviewSelection | none {
  for selection of selections { if selection.path == path { return selection } }
  return none
}

function containsString(values: string[], value: string): bool {
  for existing of values { if existing == value { return true } }
  return false
}
