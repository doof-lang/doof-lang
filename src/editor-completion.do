import { autoImportSpecifier } from "./editor-autoimport"
// Completion candidates and context selection; member signatures come from the checker.
import { EditorIndex, EditorItem } from "./editor-model"
import { editorTypeName } from "./editor-model"
import { editorModule, editorScopeAt, bindingItem, symbolItem } from "./editor-index"
import { Scope, ResolvedType, ClassType, InterfaceType, EnumType, FunctionType } from "./semantic"
import { ClassDeclaration, InterfaceDeclaration, EnumDeclaration, ExportDeclaration, Statement, MemberExpression, Identifier, SourceSpan, AstLocation } from "./ast"
import { declarationFor, lookup } from "./checker-symbols"
import { CheckerState } from "./checker-state"
import { resolveMember } from "./checker-resolution"
import { Lexer, TokenType, tokenValue } from "./lexer"

function uniquePush(items: EditorItem[], item: EditorItem): none {
  for existing of items { if existing.label == item.label { return } }
  items.push(item)
}

export function scopeCompletions(index: EditorIndex, scope: Scope, offset: int, items: EditorItem[]): none {
  for binding of scope.bindings {
    if binding.span.start.offset > offset && (binding.kind == "let" || binding.kind == "immutable-binding" || binding.kind == "const" || binding.kind == "readonly") { continue }
    uniquePush(items, bindingItem(index, binding))
  }
  if scope.parent != none { scopeCompletions(index, scope.parent!, offset, items) }
}

function declarationMemberNames(statement: Statement, names: string[]): none {
  case statement {
    export_: ExportDeclaration -> { declarationMemberNames(export_.declaration, names) }
    class_: ClassDeclaration -> {
      for field of class_.fields { for name of field.names { names.push(name) } }
      for method of class_.methods { names.push(method.name) }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields { names.push(field.name) }
      for method of interface_.methods { names.push(method.name) }
    }
    enum_: EnumDeclaration -> { for variant of enum_.variants { names.push(variant.name) } }
    _ -> { }
  }
}

export function memberCompletions(index: EditorIndex, module: string, offset: int, items: EditorItem[]): bool {
  info := editorModule(index, module) else { return false }
  for expression of info.editorExpressions {
    member := expression as MemberExpression else { continue }
    if offset < member.object.span.end.offset || offset > member.span.end.offset { continue }
    // Namespace members are compiler-resolved exports, including re-exports.
    case member.object {
      identifier: Identifier -> {
        for namespace of info.namespaceImports {
          if namespace.localName != identifier.name { continue }
          target := editorModule(index, namespace.sourceModule) else { continue }
          for symbol of target.exports { uniquePush(items, symbolItem(index, symbol)) }
          return true
        }
      }
      _ -> { }
    }
    receiver := member.object.resolvedType else { return true }
    completeMembers(index, module, offset, receiver, member.span, items)
    return true
  }
  return false
}

export function builtinMemberCandidates(): string[] => ["_", "add", "buildReadonly", "call", "charAt", "cloneMutable", "cloneReadonly", "contains", "defs", "delete", "description", "dispatch", "drainToReadonly", "endsWith", "error", "every", "fileName", "filter", "fromJsonValue", "fromName", "fromValue", "functionName", "get", "has", "indexOf", "inputSchema", "invoke", "isFailure", "isSuccess", "keys", "length", "line", "lowerBound", "map", "metadata", "methods", "name", "next", "outputSchema", "padEnd", "padStart", "pop", "post", "push", "repeat", "replaceAll", "reserve", "set", "size", "slice", "some", "split", "startsWith", "substring", "takeFirstCompleted", "toJsonObject", "toJsonValue", "toLowerCase", "toUpperCase", "trim", "trimEnd", "trimStart", "unwrapOr", "upperBound", "value", "values"]

function completeMembers(index: EditorIndex, module: string, offset: int, receiver: ResolvedType, span: SourceSpan, items: EditorItem[]): none {
  info := editorModule(index, module) else { return }
  let names: string[] = []
    case receiver {
      class_: ClassType -> {
        declaration := declarationFor(index.frontend.analysis, class_.symbol)
        if declaration != none { declarationMemberNames(declaration!, names) }
      }
      interface_: InterfaceType -> {
        declaration := declarationFor(index.frontend.analysis, interface_.symbol)
        if declaration != none { declarationMemberNames(declaration!, names) }
      }
      enum_: EnumType -> {
        declaration := declarationFor(index.frontend.analysis, enum_.symbol)
        if declaration != none { declarationMemberNames(declaration!, names) }
      }
      _ -> { }
    }
    // Candidate spellings are checked against the core resolver by tests; resolveMember remains authoritative for availability and signatures.
    for name of builtinMemberCandidates() { names.push(name) }
    state := CheckerState { result: index.frontend.analysis, info, moduleScope: editorScopeAt(index, module, offset) }
    for name of names {
      state.diagnostics = []
      selected := resolveMember(state, receiver, name, span)
      if selected.type_ == none || selected.type_!.kind == "unknown" || state.diagnostics.length > 0 { continue }
      uniquePush(items, EditorItem { label: name, detail: editorTypeName(selected.type_!), kind: if selected.function_ == none then "property" else "method", module, start: offset, end: offset })
    }

}

export function contextualCompletion(index: EditorIndex, module: string, offset: int, prefix: string, items: EditorItem[]): bool {
  tokens := Lexer { source: prefix }.tokenize()
  if tokens.length < 2 { return false }
  last := tokens.length - 2
  if tokens[last].kind == TokenType.StringLiteral && last > 0 && tokens[last - 1].kind == TokenType.From {
    for source of index.frontend.sourceFiles {
      if source.path == module { continue }
      specifier := importSpecifier(module, source.path)
      uniquePush(items, EditorItem { label: specifier, kind: "module", module, start: tokens[last].valueOffset, end: prefix.length, insertText: specifier })
    }
    return true
  }
  let dot = last
  if tokens[last].kind == TokenType.Identifier && last > 0 { dot -= 1 }
  if dot > 0 && (tokens[dot].kind == TokenType.Dot || tokens[dot].kind == TokenType.QuestionDot || tokens[dot].kind == TokenType.BangDot) && tokens[dot - 1].kind == TokenType.Identifier {
    name := tokenValue(tokens[dot - 1], prefix)
    scope := editorScopeAt(index, module, offset) else { return true }
    binding := lookup(scope, name)
    if binding != none {
      location := AstLocation { line: 1, column: 1, offset }
      completeMembers(index, module, offset, binding!.type_, SourceSpan { start: location, end: location }, items)
    } else {
      info := editorModule(index, module) else { return true }
      for namespace of info.namespaceImports {
        if namespace.localName != name { continue }
        target := editorModule(index, namespace.sourceModule) else { continue }
        for symbol of target.exports { uniquePush(items, symbolItem(index, symbol)) }
      }
    }
    return true
  }
  // Parameter labels come from the checked callable signature.
  let depth = 0
  let position = last
  while position >= 0 {
    kind := tokens[position].kind
    if kind == TokenType.RightParen || kind == TokenType.RightBrace { depth += 1 }
    if kind == TokenType.LeftParen || kind == TokenType.LeftBrace {
      if depth == 0 {
        if position == 0 || tokens[position - 1].kind != TokenType.Identifier { return false }
        scope := editorScopeAt(index, module, offset) else { return false }
        binding := lookup(scope, tokenValue(tokens[position - 1], prefix)) else { return false }
        case binding.type_ {
          fn: FunctionType -> {
            for parameter of fn.params { uniquePush(items, EditorItem { label: parameter.name, detail: editorTypeName(parameter.type_), insertText: parameter.name + ": ", kind: "parameter", module, start: offset, end: offset }) }
            return false
          }
          _ -> { return false }
        }
      }
      depth -= 1
    }
    position -= 1
  }
  return false
}

export function importSpecifier(module: string, target: string): string => autoImportSpecifier(module, target)

export function autoImportCompletions(index: EditorIndex, module: string, offset: int, prefix: string, items: EditorItem[]): none {
  tokens := Lexer { source: prefix }.tokenize()
  if tokens.length < 2 || tokens[tokens.length - 2].kind != TokenType.Identifier { return }
  typed := tokenValue(tokens[tokens.length - 2], prefix).toLowerCase()
  scope := editorScopeAt(index, module, offset)
  for candidate of index.exportCandidates {
    if candidate.module == module || !candidate.label.toLowerCase().startsWith(typed) { continue }
    if scope != none && lookup(scope!, candidate.label) != none { continue }
    let visible = false
    for item of items { if item.label == candidate.label && item.importModule == "" { visible = true } }
    if visible { continue }
    specifier := autoImportSpecifier(module, candidate.module)
    items.push(EditorItem { label: candidate.label, documentation: candidate.documentation, kind: candidate.kind, detail: "Auto import from " + specifier, importModule: candidate.module, module, start: offset, end: offset })
  }
}
