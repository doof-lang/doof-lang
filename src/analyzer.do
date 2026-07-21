// Module-level semantic analysis for the Doof compiler.
//
// The pass is intentionally phased: collect declarations, resolve imports,
// process export lists, then decorate named type annotations.  Keeping these
// responsibilities separate makes the later checker independent of parsing.

import { Parser } from "./parser"
import { ModuleResolver, SourceLoader, noSourceLoader } from "./resolver"
import {
  Diagnostic, ImportBinding, NamespaceBinding, SemanticLocation, SemanticSpan,
  SourceFile, Symbol,
} from "./semantic"
import {
  ArrayType, AstLocation, ClassDeclaration, ConstDeclaration, EnumDeclaration,
  Block, ExportDeclaration, ExportList, ForOfStatement, ForStatement, FunctionDeclaration,
  AstFunctionType, IfStatement, ImmutableBinding, InterfaceDeclaration, LetDeclaration,
  NamedImport, NamedType, NamespaceImport, ReadonlyDeclaration, ReturnStatement,
  YieldStatement, WhileStatement, WithStatement, BreakStatement, ContinueStatement,
  ExpressionStatement, DestructuringStatement, ImportDeclaration, TypeAliasDeclaration, UnionType,
  CaseStatement, MockImportDirective, WeakType, YieldBlockAssignmentStatement, TypeParameterConstraint,
} from "./ast"
import type { ImportDeclaration, Program, SourceSpan, Statement, TryStatement, TypeAnnotation } from "./ast"

export class ModuleInfo {
  path: string
  program: Program
  symbols: Symbol[] = []
  exports: Symbol[] = []
  imports: ImportBinding[] = []
  namespaceImports: NamespaceBinding[] = []
  reExports: string[] = []
  mockImportDirectives: MockImportDirective[] = []
  mockRootPath: string | none = none
  diagnostics: Diagnostic[] = []
}

export class AnalysisResult {
  modules: ModuleInfo[] = []
  diagnostics: Diagnostic[] = []
}

readonly BUILTIN_TYPES = ["byte", "int", "long", "float", "double", "string", "char", "bool", "none", "void", "null", "JsonValue", "JsonObject", "SourceLocation", "Map", "ReadonlyMap", "Set", "ReadonlySet", "Result", "Stream", "Range", "Tuple", "Actor", "Promise"]

export class ModuleAnalyzer {
  resolver: ModuleResolver
  modules: ModuleInfo[] = []
  diagnostics: Diagnostic[] = []
  inProgress: string[] = []

  function analyze(entry: string): AnalysisResult {
    modules = []
    diagnostics = []
    inProgress = []
    resolver.loadedPaths = []
    resolver.diagnostics = []
    resolver.failedPaths = []
    ignored := analyzeModule(if entry.endsWith(".do") then entry else entry + ".do", none)
    for diagnostic of resolver.diagnostics { diagnostics.push(diagnostic) }
    return AnalysisResult { modules, diagnostics }
  }

  private function analyzeModule(path: string, inheritedMockRootPath: string | none): ModuleInfo | none {
    existing := findModule(path)
    if existing != none { return existing }
    if contains(inProgress, path) { return none }

    source := resolver.find(path)
    if source == none {
      if !resolver.failed(path) {
        diagnostics.push(Diagnostic {
          severity: "error",
          message: "Module not found: " + path,
          span: emptySemanticSpan(),
          module: path,
        })
      }
      return none
    }

    inProgress.push(path)
    parser := Parser { source: source.source }
    parsed := catchPanic(=> parser.parse())
    program := parsed else failure {
      if parser.errorMessage == "" { panic(failure) }
      location := SemanticLocation { line: parser.errorLine, column: parser.errorColumn, offset: parser.errorOffset }
      diagnostics.push(Diagnostic {
        severity: "error",
        message: parser.errorMessage,
        span: SemanticSpan { start: location, end: location },
        module: path,
      })
      ignored := try! inProgress.pop()
      return none
    }
    mockImportDirectives := collectMockImportDirectives(program)
    let mockRootPath = inheritedMockRootPath
    if mockRootPath == none && mockImportDirectives.length > 0 && path.endsWith(".test.do") {
      mockRootPath = path
    }
    info := ModuleInfo { path, program, mockImportDirectives, mockRootPath }
    modules.push(info)
    validateMockImportDirectives(info, inheritedMockRootPath)
    collectSymbols(info)
    resolveImports(info)
    resolveExportLists(info)
    resolveNamedTypes(info)
    ignored := try! inProgress.pop()
    for item of info.diagnostics { diagnostics.push(item) }
    return info
  }

  private function collectSymbols(info: ModuleInfo): none {
    for statement of info.program.statements {
      symbol := symbolFor(statement, info.path)
      if symbol == none { continue }
      decorateDeclarationSymbol(statement, symbol!)
      info.symbols.push(symbol!)
      if symbol!.exported { info.exports.push(symbol!) }
    }
  }

  private function decorateDeclarationSymbol(statement: Statement, symbol: Symbol): none {
    case statement {
      class_: ClassDeclaration -> { class_.resolvedSymbol = symbol }
      interface_: InterfaceDeclaration -> { interface_.resolvedSymbol = symbol }
      _ -> { }
    }
  }

  private function symbolFor(statement: Statement, module: string): Symbol | none {
    case statement {
      value: ClassDeclaration -> {
        return Symbol {
          kind: if value.struct_ then "struct" else "class", name: value.name, module, exported: value.exported,
          native_: value.native_, nativeHeader: value.nativeHeader, nativeCppName: value.nativeCppName,
        }
      }
      value: InterfaceDeclaration -> {
        return Symbol { kind: "interface", name: value.name, module, exported: value.exported }
      }
      value: FunctionDeclaration -> {
        return Symbol {
          kind: "function", name: value.name, module, exported: value.exported,
          native_: value.native_, nativeHeader: value.nativeHeader, nativeCppName: value.nativeCppName,
        }
      }
      value: TypeAliasDeclaration -> {
        return Symbol { kind: "type-alias", name: value.name, module, exported: value.exported }
      }
      value: ConstDeclaration -> {
        return Symbol { kind: "const", name: value.name, module, exported: value.exported }
      }
      value: ReadonlyDeclaration -> {
        return Symbol { kind: "readonly", name: value.name, module, exported: value.exported }
      }
      value: ImmutableBinding -> {
        return Symbol { kind: "const", name: value.name, module, exported: value.exported }
      }
      value: EnumDeclaration -> {
        return Symbol { kind: "enum", name: value.name, module, exported: value.exported }
      }
      _ -> { return none }
    }
    return none
  }

  /** Retains declaration identity when an export list introduces a public name. */
  private function exportedSymbol(symbol: Symbol, exportedName: string): Symbol {
    return Symbol {
      kind: symbol.kind,
      name: exportedName,
      module: symbol.module,
      exported: true,
      originalName: if symbol.originalName == "" then symbol.name else symbol.originalName,
      native_: symbol.native_,
      nativeHeader: symbol.nativeHeader,
      nativeCppName: symbol.nativeCppName,
      implementations: symbol.implementations,
      implementedInterfaceTypes: symbol.implementedInterfaceTypes,
    }
  }

  private function resolveImports(info: ModuleInfo): none {
    for statement of info.program.statements {
      case statement {
        import_: ImportDeclaration -> {
          sourcePath := resolveImportPath(info, import_.source)
          if info.path.endsWith(".test.do") && info.mockRootPath == info.path && sourcePath.endsWith(".test.do") {
            addError(info, "Test file \"" + info.path + "\" cannot import another test file \"" + sourcePath + "\"", import_.span)
            continue
          }
          source := analyzeModule(sourcePath, info.mockRootPath)
          for specifier of import_.specifiers {
            case specifier {
              named: NamedImport -> {
                let imported: Symbol | none = none
                if source != none { imported = findExport(source!, named.name) }
                // A failed dependency already owns the actionable diagnostic.
                // Do not reinterpret its missing symbol table as missing exports.
                if source != none && imported == none {
                  addError(info, "Module '" + import_.source + "' does not export '" + named.name + "'", named.span)
                }
                localName := if named.alias == none then named.name else named.alias!
                if imported == none {
                  info.imports.push(ImportBinding {
                    localName, sourceName: named.name, sourceModule: sourcePath,
                    typeOnly: import_.typeOnly,
                  })
                } else {
                  info.imports.push(ImportBinding {
                    localName, sourceName: named.name, sourceModule: sourcePath,
                    typeOnly: import_.typeOnly, symbol: imported,
                  })
                }
              }
              namespace: NamespaceImport -> {
                info.namespaceImports.push(NamespaceBinding {
                  localName: namespace.alias,
                  sourceModule: sourcePath,
                  typeOnly: import_.typeOnly,
                })
              }
            }
          }
        }
        _ -> { }
      }
    }
  }

  private function resolveExportLists(info: ModuleInfo): none {
    for statement of info.program.statements {
      case statement {
        list: ExportList -> {
          if list.source != none {
            sourcePath := resolveImportPath(info, list.source!)
            source := analyzeModule(sourcePath, info.mockRootPath)
            info.reExports.push(sourcePath)
            for specifier of list.specifiers {
              let exported: Symbol | none = none
              if source != none { exported = findExport(source!, specifier.name) }
              if source != none && exported == none {
                addError(info, "Module '" + list.source! + "' does not export '" + specifier.name + "'", specifier.span)
              } else {
                if exported != none {
                  exportedName := if specifier.alias == none then specifier.name else specifier.alias!
                  info.exports.push(exportedSymbol(exported!, exportedName))
                }
              }
            }
            continue
          }
          for specifier of list.specifiers {
            local := findSymbol(info, specifier.name)
            if local != none {
              exportedName := if specifier.alias == none then specifier.name else specifier.alias!
              if findExport(info, exportedName) == none {
                info.exports.push(exportedSymbol(local!, exportedName))
              }
            } else {
              addError(info, "Cannot export unknown symbol '" + specifier.name + "'", specifier.span)
            }
          }
        }
        _ -> { }
      }
    }
  }

  private function resolveNamedTypes(info: ModuleInfo): none {
    for statement of info.program.statements { visitStatementTypes(statement, info) }
  }

  private function visitStatementTypes(statement: Statement, info: ModuleInfo): none {
    case statement {
      fn: FunctionDeclaration -> { visitFunctionTypes(fn, info) }
      class_: ClassDeclaration -> {
        visitTypeParameterConstraints(class_.typeParamConstraints, info, class_.typeParams)
        for annotation of class_.implements_ { visitType(annotation, info, class_.typeParams) }
        for field of class_.fields { if field.type_ != none { visitType(field.type_!, info, class_.typeParams) } }
        for method of class_.methods { visitFunctionTypes(method, info, class_.typeParams) }
      }
      interface_: InterfaceDeclaration -> {
        visitTypeParameterConstraints(interface_.typeParamConstraints, info, interface_.typeParams)
        for field of interface_.fields { visitType(field.type_, info, interface_.typeParams) }
        for method of interface_.methods { visitFunctionTypes(method, info, interface_.typeParams) }
      }
      alias: TypeAliasDeclaration -> { visitTypeParameterConstraints(alias.typeParamConstraints, info, alias.typeParams); visitType(alias.type_, info, alias.typeParams) }
      const_: ConstDeclaration -> { if const_.type_ != none { visitType(const_.type_!, info, []) } }
      readonly_: ReadonlyDeclaration -> { if readonly_.type_ != none { visitType(readonly_.type_!, info, []) } }
      binding: ImmutableBinding -> { if binding.type_ != none { visitType(binding.type_!, info, []) } }
      let_: LetDeclaration -> { if let_.type_ != none { visitType(let_.type_!, info, []) } }
      _ -> { }
    }
  }

  private function visitFunctionTypes(fn: FunctionDeclaration, info: ModuleInfo, ownerTypeParams: string[] = []): none {
    let typeParams: string[] = []
    for parameter of ownerTypeParams { typeParams.push(parameter) }
    for parameter of fn.typeParams { typeParams.push(parameter) }
    visitTypeParameterConstraints(fn.typeParamConstraints, info, typeParams)
    for parameter of fn.params { if parameter.type_ != none { visitType(parameter.type_!, info, typeParams) } }
    if fn.returnType != none { visitType(fn.returnType!, info, typeParams) }
  }

  private function visitTypeParameterConstraints(constraints: TypeParameterConstraint[], info: ModuleInfo, typeParams: string[]): none {
    for constraint of constraints { if constraint.type_ != none { visitType(constraint.type_!, info, typeParams) } }
  }

  private function visitType(annotation: TypeAnnotation, info: ModuleInfo, typeParams: string[] = []): none {
    case annotation {
      named: NamedType -> {
        if !isBuiltin(named.name) && !containsTypeParam(typeParams, named.name) {
          let symbol: Symbol | none = findSymbol(info, named.name)
          if symbol == none {
            for imported of info.imports {
              if imported.localName == named.name { symbol = imported.symbol; break }
            }
          }
          if symbol == none { symbol = findExport(info, named.name) }
          if symbol == none { addError(info, "Unknown type '" + named.name + "'", named.span) }
          named.resolvedSymbol = symbol
        }
        for argument of named.typeArgs { visitType(argument, info, typeParams) }
      }
      array: ArrayType -> { visitType(array.elementType, info, typeParams) }
      union: UnionType -> { for member of union.types { visitType(member, info, typeParams) } }
      function_: AstFunctionType -> {
        for parameter of function_.params { visitType(parameter.type_, info, typeParams) }
        visitType(function_.returnType, info, typeParams)
      }
      weak_: WeakType -> { visitType(weak_.type_, info, typeParams) }
    }
  }

  private function containsTypeParam(typeParams: string[], name: string): bool {
    for typeParam of typeParams { if typeParam == name { return true } }
    return false
  }

  private function findModule(path: string): ModuleInfo | none {
    for module of modules { if module.path == path { return module } }
    return none
  }

  // Keep the complete Statement union visible in this module's generated
  // header.  These forms are dispatched by shared Statement-typed helpers.
  private function keepStatementTypes(
    block: Block | none = none,
    export_: ExportDeclaration | none = none,
    import_: ImportDeclaration | none = none,
    mockImport: MockImportDirective | none = none,
    if_: IfStatement | none = none,
    case_: CaseStatement | none = none,
    while_: WhileStatement | none = none,
    for_: ForStatement | none = none,
    forOf: ForOfStatement | none = none,
    with_: WithStatement | none = none,
    return_: ReturnStatement | none = none,
    yield_: YieldStatement | none = none,
    break_: BreakStatement | none = none,
    continue_: ContinueStatement | none = none,
    expression: ExpressionStatement | none = none,
    destructuring: DestructuringStatement | none = none,
  ): none { }

  /** Applies the root test's mock environment before ordinary path resolution. */
  private function resolveImportPath(info: ModuleInfo, specifier: string): string {
    if info.mockRootPath == none { return resolver.resolve(info.path, specifier) }
    root := findModule(info.mockRootPath!)
    if root == none || root!.mockImportDirectives.length == 0 { return resolver.resolve(info.path, specifier) }
    sourceSpecifier := relativeModuleSpecifier(info.mockRootPath!, info.path)
    replacement := findMockReplacement(root!.mockImportDirectives, sourceSpecifier, specifier)
    if replacement == none { return resolver.resolve(info.path, specifier) }
    return resolver.resolve(info.mockRootPath!, replacement!)
  }

  private function validateMockImportDirectives(info: ModuleInfo, inheritedMockRootPath: string | none): none {
    if info.mockImportDirectives.length == 0 { return }
    if !info.path.endsWith(".test.do") {
      for directive of info.mockImportDirectives {
        addError(info, "mock import directives are only valid in .test.do files", directive.span)
      }
    }
    if inheritedMockRootPath != none && inheritedMockRootPath != info.path {
      for directive of info.mockImportDirectives {
        addError(info, "mock import directives are only valid in the root test file", directive.span)
      }
    }

    let sawOrdinaryStatement = false
    for statement of info.program.statements {
      case statement {
        directive: MockImportDirective -> {
          if sawOrdinaryStatement {
            addError(info, "mock import directives must appear at the top of the file before other statements", directive.span)
          }
        }
        _ -> { sawOrdinaryStatement = true }
      }
    }

    for directive of info.mockImportDirectives {
      for mapping of directive.mappings {
        if mapping.dependency == mapping.replacement {
          addError(info, "mock import cannot substitute \"" + mapping.dependency + "\" with itself", mapping.span)
        }
      }
    }
  }
}

function collectMockImportDirectives(program: Program): MockImportDirective[] {
  let directives: MockImportDirective[] = []
  for statement of program.statements {
    case statement {
      directive: MockImportDirective -> { directives.push(directive) }
      _ -> { }
    }
  }
  return directives
}

function relativeModuleSpecifier(fromModule: string, toModule: string): string {
  fromComponents := parentPathComponents(fromModule.replaceAll("\\", "/"))
  toComponents := moduleSpecifierPath(toModule.replaceAll("\\", "/")).split("/")
  let common = 0
  while common < fromComponents.length && common < toComponents.length && fromComponents[common] == toComponents[common] { common = common + 1 }
  let result = ""
  for ignored of common..<fromComponents.length { result = result + "../" }
  for index of common..<toComponents.length {
    if result != "" && !result.endsWith("/") { result = result + "/" }
    result = result + toComponents[index]
  }
  return if result.startsWith(".") then result else "./" + result
}

function parentPathComponents(path: string): string[] {
  components := path.split("/")
  if components.length > 0 { ignored := try! components.pop() }
  return components
}

function moduleSpecifierPath(path: string): string {
  if path.endsWith("/index.do") { return path.substring(0, path.length - 9) }
  if path.endsWith(".do") { return path.substring(0, path.length - 3) }
  return path
}

function findMockReplacement(
  directives: MockImportDirective[],
  sourceSpecifier: string,
  dependencySpecifier: string,
): string | none {
  for directive of directives {
    if directive.sourcePattern != sourceSpecifier { continue }
    for mapping of directive.mappings {
      if mapping.dependency == dependencySpecifier { return mapping.replacement }
    }
  }
  return none
}

export function createAnalyzer(sources: SourceFile[]): ModuleAnalyzer {
  return ModuleAnalyzer { resolver: ModuleResolver { sources, loader: noSourceLoader } }
}

export function createAnalyzerWithLoader(sources: SourceFile[], loader: SourceLoader): ModuleAnalyzer {
  return ModuleAnalyzer { resolver: ModuleResolver { sources, loader } }
}

function findSymbol(info: ModuleInfo, name: string): Symbol | none {
  for symbol of info.symbols { if symbol.name == name { return symbol } }
  return none
}

function findExport(info: ModuleInfo, name: string): Symbol | none {
  for symbol of info.exports { if symbol.name == name { return symbol } }
  return none
}

function isBuiltin(name: string): bool {
  if name == "JsonSerializable" || name == "Reflectable" { return true }
  for builtin of BUILTIN_TYPES { if builtin == name { return true } }
  return false
}

function contains(values: string[], value: string): bool {
  for item of values { if item == value { return true } }
  return false
}

function addError(info: ModuleInfo, message: string, span: SourceSpan): none {
  info.diagnostics.push(Diagnostic { severity: "error", message, span: semanticSpan(span), module: info.path })
}

function semanticSpan(span: SourceSpan): SemanticSpan {
  return SemanticSpan {
    start: SemanticLocation { line: span.start.line, column: span.start.column, offset: span.start.offset },
    end: SemanticLocation { line: span.end.line, column: span.end.column, offset: span.end.offset },
  }
}

function emptySemanticSpan(): SemanticSpan {
  zero := SemanticLocation { line: 0, column: 0, offset: 0 }
  return SemanticSpan { start: zero, end: zero }
}
