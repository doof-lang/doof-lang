import { Block, ExportList, FunctionDeclaration, MockImportDirective, NamedType, Program, Statement } from "./ast"

export class DiscoveredTest {
  id: string
  name: string
  modulePath: string
  moduleDisplayPath: string
  usesMocks: bool = false
  startOffset: int = 0
  endOffset: int = 0
}

export class TestDiscovery {
  tests: DiscoveredTest[] = []
  errors: string[] = []
}

/** Discovers locally defined exported test functions in source order. */
export function discoverModuleTests(
  program: Program,
  modulePath: string,
  rootDirectory: string,
): TestDiscovery {
  result := TestDiscovery {}
  let usesMocks = false
  for statement of program.statements {
    case statement {
      _: MockImportDirective -> { usesMocks = true }
      _ -> { }
    }
  }
  for statement of program.statements {
    case statement {
      fn: FunctionDeclaration -> {
        if fn.exported && fn.name.startsWith("test") {
          addDiscoveredTest(result, fn, fn.name, modulePath, rootDirectory, usesMocks)
        }
      }
      list: ExportList -> {
        if list.source != none { continue }
        for specifier of list.specifiers {
          exportedName := if specifier.alias == none then specifier.name else specifier.alias!
          if !exportedName.startsWith("test") { continue }
          declaration := findFunction(program.statements, specifier.name)
          if declaration != none {
            addDiscoveredTest(result, declaration!, exportedName, modulePath, rootDirectory, usesMocks)
          }
        }
      }
      _ -> { }
    }
  }
  return result
}

export function testDisplayPath(rootDirectory: string, modulePath: string): string {
  root := trimTrailingSlashes(rootDirectory.replaceAll("\\", "/"))
  module := modulePath.replaceAll("\\", "/")
  prefix := root + "/"
  if module.startsWith(prefix) { return module.substring(prefix.length, module.length) }
  return module
}

function addDiscoveredTest(
  result: TestDiscovery,
  declaration: FunctionDeclaration,
  exportedName: string,
  modulePath: string,
  rootDirectory: string,
  usesMocks: bool,
): none {
  location := modulePath + ":" + string(declaration.span.start.line) + ":" + string(declaration.span.start.column)
  if declaration.params.length > 0 {
    result.errors.push(location + ": error: test \"" + exportedName + "\" must not declare parameters")
    return
  }
  if declaration.typeParams.length > 0 {
    result.errors.push(location + ": error: test \"" + exportedName + "\" must not declare type parameters")
    return
  }
  if !returnsNone(declaration) {
    result.errors.push(location + ": error: test \"" + exportedName + "\" must return none")
    return
  }
  displayPath := testDisplayPath(rootDirectory, modulePath)
  result.tests.push(DiscoveredTest {
    id: displayPath + "::" + exportedName,
    name: exportedName,
    modulePath,
    moduleDisplayPath: displayPath,
    usesMocks,
    startOffset: declaration.span.start.offset,
    endOffset: declaration.span.end.offset,
  })
}

function returnsNone(declaration: FunctionDeclaration): bool {
  if declaration.returnType == none {
    case declaration.body {
      _: Block -> { return true }
      _ -> { return false }
    }
  }
  case declaration.returnType! {
    named: NamedType -> { return named.name == "none" || named.name == "void" }
    _ -> { return false }
  }
}

function findFunction(statements: Statement[], name: string): FunctionDeclaration | none {
  for statement of statements {
    case statement {
      fn: FunctionDeclaration -> { if fn.name == name { return fn } }
      _ -> { }
    }
  }
  return none
}

function trimTrailingSlashes(path: string): string {
  let end = path.length
  while end > 1 && path[end - 1] == '/' { end = end - 1 }
  return path.substring(0, end)
}

