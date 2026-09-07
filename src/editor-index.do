import { prepareAutoImports } from "./editor-autoimport"
import { ModuleResolver, noSourceLoader } from "./resolver"
// Project editor index. Targets come from checker bindings and decorations;
// token lookup only narrows declaration spans to their actual name token.
import { ModuleInfo } from "./analyzer"
import { FrontendResult } from "./frontend"
import { EditorIndex, EditorItem, IndexedBinding, EditorTokens } from "./editor-model"
import { Binding, ResolvedType, Scope, Symbol, ClassType, InterfaceType } from "./semantic"
import { Lexer, TokenType, tokenValue } from "./lexer"
import { declarationFor, lookup } from "./checker-symbols"
import { editorTypeName } from "./editor-model"
import { Identifier, MemberExpression, FunctionDeclaration, ClassDeclaration, InterfaceDeclaration, NamedType, ExportDeclaration, Statement, ObjectLiteral, ConstructExpression, ObjectProperty, ImportDeclaration, NamedImport, ExportList } from "./ast"

export function editorModule(index: EditorIndex, path: string): ModuleInfo | none {
  for module of index.frontend.analysis.modules { if module.path == path { return module } }
  return none
}

export function editorSource(index: EditorIndex, path: string): string {
  for source of index.frontend.sourceFiles { if source.path == path { return source.source } }
  return ""
}

export function nameItem(index: EditorIndex, module: string, name: string, start: int, end: int, kind: string = "variable"): EditorItem {
  let cached: EditorTokens | none = none
  for entry of index.tokens { if entry.module == module { cached = entry; break } }
  if cached == none {
    source := editorSource(index, module)
    cached = EditorTokens { module, source, tokens: Lexer { source }.tokenize() }
    index.tokens.push(cached!)
  }
  source := cached!.source
  tokens := cached!.tokens
  let lower = 0
  let upper = tokens.length
  while lower < upper {
    middle := (lower + upper) >> 1
    if tokens[middle].offset < start { lower = middle + 1 } else { upper = middle }
  }
  for position of lower..<tokens.length {
    token := tokens[position]
    if token.offset >= end { break }
    if token.kind == TokenType.Identifier && tokenValue(token, source) == name {
      return EditorItem { label: name, module, start: token.offset, end: token.offset + token.length, kind }
    }
  }
  return EditorItem { label: name, module, start, end: start, kind }
}

export function symbolItem(index: EditorIndex, symbol: Symbol): EditorItem {
  declaration := declarationFor(index.frontend.analysis, symbol)
  name := if symbol.originalName == "" then symbol.name else symbol.originalName
  if declaration == none { return EditorItem { label: name, module: symbol.module, start: 0, end: 0, kind: symbol.kind } }
  item := nameItem(index, symbol.module, name, declaration!.span.start.offset, declaration!.span.end.offset, symbol.kind)
  return item
}

export function itemIdentity(item: EditorItem): string => item.module + ":" + string(item.start) + ":" + item.label

export function bindingItem(index: EditorIndex, binding: Binding): EditorItem {
  key := binding.module + ":" + string(binding.span.start.offset) + ":" + binding.name
  if index.bindingItems.has(key) { return try! index.bindingItems.get(key) }
  local := nameItem(index, binding.module, binding.name, binding.span.start.offset, binding.span.end.offset, binding.kind)
  let target = local
  if binding.symbol != none { target = symbolItem(index, binding.symbol!) }
  let renameIdentity = itemIdentity(target)
  if binding.kind == "import" {
    info := editorModule(index, binding.module)
    if info != none {
      for imported of info!.imports {
        if imported.localName == binding.name {
          alias := exportAliasItem(index, imported.sourceModule, imported.sourceName)
          if alias != none { renameIdentity = itemIdentity(alias!) }
        }
      }
      for statement of info!.program.statements {
        import_ := statement as ImportDeclaration else { continue }
        for specifier of import_.specifiers {
          named := specifier as NamedImport else { continue }
          if named.alias != none && named.alias! == binding.name { renameIdentity = itemIdentity(local) }
        }
      }
    }
  }
  item := EditorItem {
    documentation: if binding.symbol == none then "" else symbolDocumentation(index, binding.symbol!),
    renameIdentity, label: binding.name, detail: editorTypeName(binding.type_), kind: binding.kind,
    module: local.module, start: local.start, end: local.end,
    identity: itemIdentity(target), definitionModule: target.module,
    definitionStart: target.start, definitionEnd: target.end, declaration: true,
  }
  index.bindingItems[key] = item
  return item
}

function addBinding(index: EditorIndex, binding: Binding): none {
  item := bindingItem(index, binding)
  key := item.module + ":" + string(item.start) + ":" + item.label
  if index.indexedBindings.has(key) { return }
  index.indexedBindings.add(key)
  index.bindings.push(IndexedBinding { item, binding, type_: binding.type_ })
  if item.end > item.start { index.occurrences.push(item) }
}

function addScope(index: EditorIndex, scope: Scope): none {
  if scope.editorIndexed { return }
  scope.editorIndexed = true
  index.visitedScopes.push(scope)
  for binding of scope.bindings { addBinding(index, binding) }
  if scope.parent != none { addScope(index, scope.parent!) }
}

function occurrence(index: EditorIndex, binding: Binding, module: string, start: int, end: int, shorthand: bool = false): EditorItem {
  item := bindingItem(index, binding)
  return EditorItem {
    label: binding.name, detail: item.detail, documentation: item.documentation, kind: item.kind,
    module, start, end, identity: item.identity, renameIdentity: item.renameIdentity,
    definitionModule: item.definitionModule, definitionStart: item.definitionStart, definitionEnd: item.definitionEnd, shorthand,
  }
}

function addProperties(index: EditorIndex, properties: ObjectProperty[], module: string, owner: ResolvedType | none): none {
  for property of properties {
    target := fieldTarget(index, owner, property.name)
    if target != none {
      token := nameItem(index, module, property.name, property.span.start.offset, property.span.end.offset)
      index.occurrences.push(EditorItem { label: property.name, kind: if property.value == none then "field-shorthand" else "property", module, start: token.start, end: token.end, identity: itemIdentity(target!), definitionModule: target!.module, definitionStart: target!.start, definitionEnd: target!.end, shorthand: property.value == none })
    }
    if property.value == none && property.resolvedBinding != none {
      name := nameItem(index, module, property.name, property.span.start.offset, property.span.end.offset)
      index.occurrences.push(occurrence(index, property.resolvedBinding!, module, name.start, name.end, true))
    }
  }
}

export function createEditorIndex(frontend: FrontendResult): EditorIndex {
  index := EditorIndex { frontend }
  for module of frontend.analysis.modules {
    for region of module.editorScopes { addScope(index, region.scope) }
    for statement of module.program.statements { addMemberDeclarations(index, statement, module.path) }
    for statement of module.program.statements {
      case statement {
        list: ExportList -> {
          if list.source != none { addReexport(index, module, list) }
          for specifier of list.specifiers {
            if list.source != none { continue }
            for indexed of index.bindings {
              if indexed.binding == none || indexed.item.module != module.path || indexed.item.label != specifier.name { continue }
              token := nameItem(index, module.path, specifier.name, specifier.span.start.offset, specifier.span.end.offset)
              index.occurrences.push(occurrence(index, indexed.binding!, module.path, token.start, token.end))
              if specifier.alias != none {
                alias := nameItem(index, module.path, specifier.alias!, specifier.span.start.offset, specifier.span.end.offset, "export-alias")
                target := indexed.item
                index.occurrences.push(EditorItem { label: alias.label, kind: "export-alias", module: module.path, start: alias.start, end: alias.end, identity: target.identity, renameIdentity: itemIdentity(alias), definitionModule: target.definitionModule, definitionStart: target.definitionStart, definitionEnd: target.definitionEnd, declaration: true })
              }
              break
            }
          }
        }
        _ -> { }
      }
      import_ := statement as ImportDeclaration else { continue }
      for specifier of import_.specifiers {
        named := specifier as NamedImport else { continue }
        if named.alias == none { continue }
        for binding of module.imports {
          if binding.localName != named.alias! || binding.symbol == none { continue }
          target := symbolItem(index, binding.symbol!)
          token := nameItem(index, module.path, named.name, named.span.start.offset, named.span.end.offset, "import-source")
          alias := exportAliasItem(index, binding.sourceModule, binding.sourceName)
          index.occurrences.push(EditorItem { label: named.name, kind: "import-source", module: module.path, start: token.start, end: token.end, identity: itemIdentity(target), renameIdentity: if alias == none then itemIdentity(target) else itemIdentity(alias!), definitionModule: target.module, definitionStart: target.start, definitionEnd: target.end })
        }
      }
    }
    for expression of module.editorExpressions {
      case expression {
        identifier: Identifier -> {
          if identifier.resolvedBinding != none {
            index.occurrences.push(occurrence(index, identifier.resolvedBinding!, module.path, identifier.span.start.offset, identifier.span.end.offset))
          }
        }
        member: MemberExpression -> {
          let target: EditorItem | none = none
          if member.resolvedNamespaceSymbol != none { target = symbolItem(index, member.resolvedNamespaceSymbol!) }
          else if member.resolvedMember != none && member.resolvedMember!.function_ != none {
            fn := member.resolvedMember!.function_!
            target = nameItem(index, member.resolvedMember!.modulePath, fn.name, fn.span.start.offset, fn.span.end.offset, "method")
          }
          if target == none && member.resolvedMember != none { target = fieldTarget(index, member.resolvedMember!.owner, member.property) }
          if target != none {
            index.occurrences.push(EditorItem {
              label: member.property, detail: if member.resolvedType == none then "" else editorTypeName(member.resolvedType!), kind: target!.kind,
              module: module.path, start: member.span.end.offset - member.property.length, end: member.span.end.offset,
              identity: itemIdentity(target!), definitionModule: target!.module, definitionStart: target!.start, definitionEnd: target!.end,
            })
          }
        }
        object: ObjectLiteral -> { addProperties(index, object.properties, module.path, if object.resolvedConstruction == none then none else object.resolvedConstruction!.owner) }
        construct: ConstructExpression -> { addProperties(index, construct.args, module.path, construct.resolvedConstructedType) }
        _ -> { }
      }
    }
    for annotation of module.editorAnnotations {
      case annotation {
        named: NamedType -> {
          if named.resolvedSymbol != none {
            target := symbolItem(index, named.resolvedSymbol!)
            token := nameItem(index, module.path, named.name, named.span.start.offset, named.span.end.offset, "type")
            index.occurrences.push(EditorItem { label: named.name, detail: if named.resolvedType == none then "" else editorTypeName(named.resolvedType!), kind: "type", module: module.path, start: token.start, end: token.end, identity: itemIdentity(target), definitionModule: target.module, definitionStart: target.start, definitionEnd: target.end })
          }
        }
        _ -> { }
      }
    }
  }
  for scope of index.visitedScopes { scope.editorIndexed = false }
  prepareAutoImports(index)
  return index
}

function unwrapDeclaration(statement: Statement): Statement {
  case statement { export_: ExportDeclaration -> { return unwrapDeclaration(export_.declaration) } _ -> { return statement } }
}

function symbolDocumentation(index: EditorIndex, symbol: Symbol): string {
  declaration := declarationFor(index.frontend.analysis, symbol) else { return "" }
  case unwrapDeclaration(declaration) {
    fn: FunctionDeclaration -> { return fn.description }
    class_: ClassDeclaration -> { return class_.description }
    interface_: InterfaceDeclaration -> { return interface_.description }
    _ -> { return "" }
  }
}

function memberDeclaration(index: EditorIndex, module: string, name: string, start: int, end: int, kind: string, type_: ResolvedType | none, documentation: string = ""): none {
  token := nameItem(index, module, name, start, end, kind)
  if token.end <= token.start { return }
  item := EditorItem { label: name, detail: if type_ == none then "" else editorTypeName(type_!), documentation, kind, module, start: token.start, end: token.end, identity: itemIdentity(token), declaration: true, definitionModule: module, definitionStart: token.start, definitionEnd: token.end }
  index.bindings.push(IndexedBinding { item, type_ })
  index.occurrences.push(item)
}

function addMemberDeclarations(index: EditorIndex, statement: Statement, module: string): none {
  case unwrapDeclaration(statement) {
    class_: ClassDeclaration -> {
      for field of class_.fields { for name of field.names { memberDeclaration(index, module, name, field.span.start.offset, field.span.end.offset, "property", field.resolvedType) } }
      for method of class_.methods { memberDeclaration(index, module, method.name, method.span.start.offset, method.span.end.offset, "method", method.resolvedType, method.description) }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields { memberDeclaration(index, module, field.name, field.span.start.offset, field.span.end.offset, "property", field.resolvedType, field.description) }
      for method of interface_.methods { memberDeclaration(index, module, method.name, method.span.start.offset, method.span.end.offset, "method", method.resolvedType, method.description) }
    }
    _ -> { }
  }
}

function fieldTarget(index: EditorIndex, owner: ResolvedType | none, name: string): EditorItem | none {
  if owner == none { return none }
  let symbol: Symbol | none = none
  case owner! { class_: ClassType -> { symbol = class_.symbol } interface_: InterfaceType -> { symbol = interface_.symbol } _ -> { } }
  if symbol == none { return none }
  declaration := declarationFor(index.frontend.analysis, symbol!) else { return none }
  case unwrapDeclaration(declaration) {
    class_: ClassDeclaration -> {
      for field of class_.fields { for fieldName of field.names { if fieldName == name { return nameItem(index, symbol!.module, name, field.span.start.offset, field.span.end.offset, "property") } } }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields { if field.name == name { return nameItem(index, symbol!.module, name, field.span.start.offset, field.span.end.offset, "property") } }
    }
    _ -> { }
  }
  return none
}

function exportAliasItem(index: EditorIndex, module: string, name: string): EditorItem | none {
  info := editorModule(index, module) else { return none }
  for statement of info.program.statements {
    list := statement as ExportList else { continue }
    for specifier of list.specifiers {
      if specifier.alias != none && specifier.alias! == name { return nameItem(index, module, name, specifier.span.start.offset, specifier.span.end.offset, "export-alias") }
    }
  }
  return none
}

export function editorScopeAt(index: EditorIndex, module: string, offset: int): Scope | none {
  info := editorModule(index, module) else { return none }
  let found: Scope | none = none
  let width = 2147483647
  for region of info.editorScopes {
    if offset < region.span.start.offset || offset > region.span.end.offset { continue }
    size := region.span.end.offset - region.span.start.offset
    if size <= width { found = region.scope; width = size }
  }
  return found
}

function addReexport(index: EditorIndex, module: ModuleInfo, list: ExportList): none {
  resolver := ModuleResolver { sources: index.frontend.sourceFiles, loader: noSourceLoader }
  sourceModule := resolver.resolve(module.path, list.source!)
  source := editorModule(index, sourceModule) else { return }
  for specifier of list.specifiers {
    for symbol of source.exports {
      if symbol.name != specifier.name { continue }
      target := symbolItem(index, symbol)
      token := nameItem(index, module.path, specifier.name, specifier.span.start.offset, specifier.span.end.offset, "export-source")
      upstream := exportAliasItem(index, sourceModule, specifier.name)
      index.occurrences.push(EditorItem { label: specifier.name, kind: "export-source", module: module.path, start: token.start, end: token.end, identity: itemIdentity(target), renameIdentity: if upstream == none then itemIdentity(target) else itemIdentity(upstream!), definitionModule: target.module, definitionStart: target.start, definitionEnd: target.end })
      if specifier.alias != none {
        alias := nameItem(index, module.path, specifier.alias!, specifier.span.start.offset, specifier.span.end.offset, "export-alias")
        index.occurrences.push(EditorItem { label: alias.label, kind: "export-alias", module: module.path, start: alias.start, end: alias.end, identity: itemIdentity(target), renameIdentity: itemIdentity(alias), definitionModule: target.module, definitionStart: target.start, definitionEnd: target.end, declaration: true })
      }
    }
  }
}
