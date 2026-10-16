// Top-level declarations of an analyzed module graph.
//
// Emitters resolve a checked nominal type back to its declaration by the
// declaring module path and name. The index is built once per graph so those
// lookups do not rescan every program, and so same-named declarations in
// different modules stay distinct.

import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  ClassDeclaration, ConstDeclaration, EnumDeclaration, FunctionDeclaration,
  ImmutableBinding, InterfaceDeclaration, Program, ReadonlyDeclaration, Statement, TypeAliasDeclaration,
} from "./ast"

export class DeclarationIndex {
  programs: Program[] = []
  modules: Map<string, ModuleInfo> = {}
  // Keyed by `declarationKey`. Holds the statement as written, so exported
  // declarations keep their `export` wrapper.
  declarations: Map<string, Statement> = {}
}

export function indexDeclarations(result: AnalysisResult): DeclarationIndex {
  let programs: Program[] = []
  modules: Map<string, ModuleInfo> := {}
  declarations: Map<string, Statement> := {}
  for module of result.modules {
    programs.push(module.program)
    if !modules.has(module.path) { modules.set(module.path, module) }
    for statement of module.program.statements {
      name := declarationName(statement)
      key := declarationKey(module.path, name)
      if name != "" && !declarations.has(key) { declarations.set(key, statement) }
    }
  }
  return DeclarationIndex { programs, modules, declarations }
}

export function declarationKey(modulePath: string, name: string): string {
  return modulePath + "\n" + name
}

export function indexedModule(index: DeclarationIndex, path: string): ModuleInfo | none {
  module := index.modules.get(path) else { return none }
  return module
}

/** The top-level statement declaring `name` in `modulePath`, including any `export` wrapper. */
export function indexedDeclaration(index: DeclarationIndex, modulePath: string, name: string): Statement | none {
  statement := index.declarations.get(declarationKey(modulePath, name)) else { return none }
  return statement
}

export function indexedClass(index: DeclarationIndex, modulePath: string, name: string): ClassDeclaration | none {
  statement := indexedDeclaration(index, modulePath, name) else { return none }
  case statement {
    class_: ClassDeclaration -> { return class_ }
    _ -> { return none }
  }
}

export function indexedEnum(index: DeclarationIndex, modulePath: string, name: string): EnumDeclaration | none {
  statement := indexedDeclaration(index, modulePath, name) else { return none }
  case statement {
    enum_: EnumDeclaration -> { return enum_ }
    _ -> { return none }
  }
}

export function indexedInterface(index: DeclarationIndex, modulePath: string, name: string): InterfaceDeclaration | none {
  statement := indexedDeclaration(index, modulePath, name) else { return none }
  case statement {
    interface_: InterfaceDeclaration -> { return interface_ }
    _ -> { return none }
  }
}

/** The name a top-level statement declares, or "" when it declares none. */
export function declarationName(statement: Statement): string {
  case statement {
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
}
