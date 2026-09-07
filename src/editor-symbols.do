// Workspace search includes declarations outside the current entry graph.
import { EditorIndex, EditorItem } from "./editor-model"
import { nameItem } from "./editor-index"
import { Parser } from "./parser"
import { Statement, ExportDeclaration, FunctionDeclaration, ClassDeclaration, InterfaceDeclaration, EnumDeclaration, TypeAliasDeclaration, ConstDeclaration, ReadonlyDeclaration, ImmutableBinding } from "./ast"

function declarationName(statement: Statement): string {
  case statement {
    export_: ExportDeclaration -> { return declarationName(export_.declaration) }
    fn: FunctionDeclaration -> { return fn.name }
    class_: ClassDeclaration -> { return class_.name }
    interface_: InterfaceDeclaration -> { return interface_.name }
    enum_: EnumDeclaration -> { return enum_.name }
    alias: TypeAliasDeclaration -> { return alias.name }
    const_: ConstDeclaration -> { return const_.name }
    readonly_: ReadonlyDeclaration -> { return readonly_.name }
    binding: ImmutableBinding -> { return binding.name }
    _ -> { return "" }
  }
}

export function workspaceEditorSymbols(index: EditorIndex, search: string): EditorItem[] {
  if !index.workspaceIndexed {
    for source of index.frontend.sourceFiles {
      if source.path.startsWith("/std/") { continue }
      parser := Parser { source: source.source, editorMode: true }
      parsed := catchPanic(=> parser.parse())
      program := parsed else { continue }
      for statement of program.statements {
        name := declarationName(statement)
        if name == "" { continue }
        index.workspaceDeclarations.push(nameItem(index, source.path, name, statement.span.start.offset, statement.span.end.offset))
      }
    }
    index.workspaceIndexed = true
  }
  let result: EditorItem[] = []
  for item of index.workspaceDeclarations { if item.label.toLowerCase().contains(search.toLowerCase()) { result.push(item) } }
  return result
}
