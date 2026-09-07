// Export discovery and import edits are compiler-owned, including stdlib sources.
import { EditorIndex, EditorItem, EditorEdit, EditorResponse } from "./editor-model"
import { Parser } from "./parser"
import { ModuleResolver, noSourceLoader } from "./resolver"
import { FunctionDeclaration, ClassDeclaration, InterfaceDeclaration, EnumDeclaration, TypeAliasDeclaration, ConstDeclaration, ReadonlyDeclaration, ImmutableBinding, ExportDeclaration, ExportList, Statement, ImportDeclaration, NamedImport } from "./ast"

function declarationItem(statement: Statement, module: string, forced: bool = false): EditorItem | none {
  let name = ""
  let kind = "variable"
  let exported = forced
  let documentation = ""
  case statement {
    export_: ExportDeclaration -> { return declarationItem(export_.declaration, module, true) }
    fn: FunctionDeclaration -> { name = fn.name; kind = "function"; exported = exported || fn.exported; documentation = fn.description }
    class_: ClassDeclaration -> { name = class_.name; kind = "class"; exported = exported || class_.exported; documentation = class_.description }
    interface_: InterfaceDeclaration -> { name = interface_.name; kind = "interface"; exported = exported || interface_.exported; documentation = interface_.description }
    enum_: EnumDeclaration -> { name = enum_.name; kind = "enum"; exported = exported || enum_.exported }
    alias: TypeAliasDeclaration -> { name = alias.name; kind = "type"; exported = exported || alias.exported }
    const_: ConstDeclaration -> { name = const_.name; exported = exported || const_.exported }
    readonly_: ReadonlyDeclaration -> { name = readonly_.name; exported = exported || readonly_.exported }
    binding: ImmutableBinding -> { name = binding.name; exported = exported || binding.exported }
    _ -> { }
  }
  if name == "" || !exported { return none }
  return EditorItem { label: name, kind, documentation, module, start: statement.span.start.offset, end: statement.span.end.offset, importModule: module }
}

export function prepareAutoImports(index: EditorIndex): none {
  for source of index.frontend.sourceFiles {
    if source.path.endsWith(".test.do") { continue }
    let statements: Statement[] = []
    let reached = false
    for module of index.frontend.analysis.modules {
      if module.path == source.path { statements = module.program.statements; reached = true; break }
    }
    if !reached {
      parser := Parser { source: source.source, editorMode: true }
      parsed := catchPanic(=> parser.parse())
      program := parsed else { continue }
      statements = program.statements
    }
    for statement of statements {
      candidate := declarationItem(statement, source.path)
      if candidate != none { index.exportCandidates.push(candidate!) }
      case statement {
        list: ExportList -> {
          for specifier of list.specifiers { index.exportCandidates.push(EditorItem { label: specifier.alias ?? specifier.name, module: source.path, start: specifier.span.start.offset, end: specifier.span.end.offset, importModule: source.path }) }
        }
        _ -> { }
      }
    }
  }
}

export function autoImportEdits(index: EditorIndex, module: string, target: string, name: string, source: string): EditorResponse {
  if module == target { return EditorResponse { error: "The declaration is already in this module." } }
  let found = false
  for candidate of index.exportCandidates { if candidate.module == target && candidate.label == name { found = true } }
  if !found { return EditorResponse { error: "This export is no longer available." } }
  parser := Parser { source, editorMode: true }
  parsed := catchPanic(=> parser.parse())
  program := parsed else { return EditorResponse { error: "Cannot safely locate imports in this source." } }
  resolver := ModuleResolver { sources: index.frontend.sourceFiles, loader: noSourceLoader }
  let mergeOffset = -1
  for statement of program.statements {
    declared := declarationItem(statement, module, true)
    if declared != none && declared!.label == name { return EditorResponse { error: "A declaration already uses this name." } }
    import_ := statement as ImportDeclaration else { continue }
    let lastNamed = -1
    for specifier of import_.specifiers {
      named := specifier as NamedImport else { continue }
      if (named.alias ?? named.name) == name {
        if resolver.resolve(module, import_.source) == target && named.name == name { return EditorResponse {} }
        return EditorResponse { error: "An existing import already uses this name." }
      }
      lastNamed = named.span.end.offset
    }
    if resolver.resolve(module, import_.source) == target && lastNamed >= 0 {
      mergeOffset = lastNamed
    }
  }
  if mergeOffset >= 0 { return EditorResponse { edits: [EditorEdit { module, start: mergeOffset, end: mergeOffset, text: ", " + name }] } }
  let offset = 0
  if source.startsWith("#!") { offset = source.indexOf("\n") + 1; if offset == 0 { return EditorResponse { error: "Complete the shebang line before adding an import." } } }
  specifier := autoImportSpecifier(module, target).replaceAll("\\", "\\\\").replaceAll("\"", "\\\"")
  newline := if source.contains("\r\n") then "\r\n" else "\n"
  return EditorResponse { edits: [EditorEdit { module, start: offset, end: offset, text: "import { " + name + " } from \"" + specifier + "\"" + newline }] }
}

export function autoImportSpecifier(module: string, target: string): string {
  let value = target
  if value.endsWith(".do") { value = value.substring(0, value.length - 3) }
  if value.endsWith("/index") { value = value.substring(0, value.length - 6) }
  if value.startsWith("/std/") { return value.substring(1, value.length) }
  fromParts := module.split("/")
  to := value.split("/")
  let shared = 0
  while shared < fromParts.length - 1 && shared < to.length && fromParts[shared] == to[shared] { shared += 1 }
  let result = ""
  for ignored of shared..<fromParts.length - 1 { result += "../" }
  if result == "" { result = "./" }
  for i of shared..<to.length { if i > shared { result += "/" } result += to[i] }
  return result
}
