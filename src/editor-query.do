import { BUILTIN_TYPES } from "./analyzer"
import { editorSignature } from "./editor-signature"
import { workspaceEditorSymbols } from "./editor-symbols"
import { missingImportFix } from "./editor-actions"
import { scopeCompletions, memberCompletions, contextualCompletion, autoImportCompletions } from "./editor-completion"
import { editorScopeAt } from "./editor-index"
import { validateEditorRename, renameCoverageError } from "./editor-rename"
import { Symbol } from "./semantic"
// Interactive queries consume one checker-owned snapshot. This layer never
// infers identifier bindings or member types from spelling alone.
import { EditorIndex, EditorItem, EditorEdit, EditorResponse } from "./editor-model"
import { editorModule, editorSource, nameItem, bindingItem, symbolItem } from "./editor-index"
import { Scope, ResolvedType, ClassType, InterfaceType, EnumType, FunctionType } from "./semantic"
import { ClassDeclaration, InterfaceDeclaration, EnumDeclaration, FunctionDeclaration, ExportDeclaration, Statement, MemberExpression, CallExpression, Identifier, SourceSpan, AstLocation } from "./ast"
import { declarationFor, lookup } from "./checker-symbols"
import { editorTypeName } from "./editor-model"
import { CheckerState } from "./checker-state"
import { resolveMember } from "./checker-resolution"
import { Lexer, TokenType, tokenValue } from "./lexer"

export function editorItemAt(index: EditorIndex, module: string, offset: int): EditorItem | none {
  let found: EditorItem | none = none
  for item of index.occurrences {
    if item.module != module || offset < item.start || offset > item.end || item.end <= item.start { continue }
    if found == none || item.end - item.start < found!.end - found!.start { found = item }
  }
  return found
}


export function queryEditor(index: EditorIndex, operation: string, module: string, offset: int = 0, text: string = ""): EditorResponse {
  if operation == "workspaceSymbols" { return EditorResponse { items: workspaceEditorSymbols(index, text) } }
  if operation == "codeAction" { return missingImportFix(index, module, text) }
  response := EditorResponse {}
  if operation == "completion" {
    if text != "" && contextualCompletion(index, module, offset, text, response.items) { return response }
    if memberCompletions(index, module, offset, response.items) { return response }
    scope := editorScopeAt(index, module, offset)
    if scope != none { scopeCompletions(index, scope!, offset, response.items) }
    for name of BUILTIN_TYPES { response.items.push(EditorItem { label: name, kind: "type", module, start: offset, end: offset }) }
    autoImportCompletions(index, module, offset, text, response.items)
    return response
  }
  if operation == "symbols" || operation == "workspaceSymbols" || operation == "semanticTokens" {
    values := if operation == "semanticTokens" then index.occurrences else declarationItems(index)
    for item of values {
      if operation != "workspaceSymbols" && item.module != module { continue }
      if text != "" && !item.label.toLowerCase().contains(text.toLowerCase()) { continue }
      response.items.push(item)
    }
    return response
  }
  if operation == "signature" { return editorSignature(index, module, offset, text) }
  item := editorItemAt(index, module, offset) else { return response }
  if operation == "typeDefinition" {
    for binding of index.bindings {
      if binding.item.identity != item.identity || binding.type_ == none { continue }
      case binding.type_! {
        class_: ClassType -> { response.items.push(typeDefinitionItem(index, class_.symbol)); return response }
        interface_: InterfaceType -> { response.items.push(typeDefinitionItem(index, interface_.symbol)); return response }
        enum_: EnumType -> { response.items.push(typeDefinitionItem(index, enum_.symbol)); return response }
        _ -> { }
      }
    }
    return response
  }
  if operation == "hover" || operation == "definition" || operation == "prepareRename" { response.items.push(item); return response }
  if operation == "references" {
    for occurrence of index.occurrences { if occurrence.identity == item.identity { response.items.push(occurrence) } }
    return response
  }
  if operation == "rename" {
    if item.definitionModule.startsWith("/std/") { return EditorResponse { error: "Bundled standard-library declarations are read-only." } }
    tokens := Lexer { source: text }.tokenize()
    if tokens.length != 2 || tokens[0].kind != TokenType.Identifier || tokenValue(tokens[0], text) != text {
      return EditorResponse { error: "Choose a valid Doof identifier." }
    }
    if index.frontend.diagnostics.length > 0 { return EditorResponse { error: "Resolve project diagnostics before renaming so every reference can be validated." } }
    coverage := renameCoverageError(index, item)
    if coverage != "" { return EditorResponse { error: coverage } }
    for occurrence of index.occurrences {
      if (if occurrence.renameIdentity == "" then occurrence.identity else occurrence.renameIdentity) != (if item.renameIdentity == "" then item.identity else item.renameIdentity) { continue }
      scope := editorScopeAt(index, occurrence.module, occurrence.start)
      if scope != none && lookup(scope!, text) != none && text != item.label { return EditorResponse { error: "The new name conflicts with an existing binding." } }
      let duplicate = false
      for edit of response.edits { if edit.module == occurrence.module && edit.start == occurrence.start { duplicate = true } }
      if !duplicate { response.edits.push(EditorEdit { module: occurrence.module, start: occurrence.start, end: occurrence.end, text: if occurrence.kind == "field-shorthand" then text + ": " + occurrence.label else if occurrence.shorthand then occurrence.label + ": " + text else text }) }
    }
    return validateEditorRename(index, response)
  }
  return response
}

function declarationItems(index: EditorIndex): EditorItem[] {
  let items: EditorItem[] = []
  for binding of index.bindings { if binding.item.end > binding.item.start { items.push(binding.item) } }
  return items
}


function typeDefinitionItem(index: EditorIndex, symbol: Symbol): EditorItem {
  target := symbolItem(index, symbol)
  return EditorItem { label: target.label, module: target.module, start: target.start, end: target.end, definitionModule: target.module, definitionStart: target.start, definitionEnd: target.end }
}



