import { Assert } from "std/assert"
import { Parser, parse } from "./parser"
import { Block, ClassDeclaration, ConstDeclaration, ExportList, ForStatement, FunctionDeclaration, ImportDeclaration, LetDeclaration, YieldBlockExpression } from "./ast"

function parseFailure(source: string): Parser {
  parser := Parser { source }
  case catchPanic(=> parser.parse()) {
    _: Failure<string> -> { }
    _ -> { panic("expected parse failure for: " + source) }
  }
  return parser
}

function onlyClass(source: string): ClassDeclaration {
  class_ := parse(source).statements[0] as ClassDeclaration else { panic("expected class declaration") }
  return class_
}

export function testFunctionsAndMethodsShareSignatureAndBodyParsing(): none {
  function_ := parse("function pick \"Picks.\"<T: Comparable>(value: T = 1): T => value").statements[0] as FunctionDeclaration else { panic("expected function") }
  Assert.equal(function_.description, "Picks.")
  Assert.equal(function_.typeParams.length, 1)
  Assert.equal(function_.typeParamConstraints[0].type_ != none, true)
  Assert.equal(function_.params[0].defaultValue != none, true)
  Assert.equal(function_.legacyMethodFunctionSpan == none, true)

  class_ := onlyClass("class Box {\nread \"Reads.\"<T>(value: T): T { return value }\nfunction legacy(): int => 1\n}")
  Assert.equal(class_.methods.length, 2)
  method := class_.methods[0]
  Assert.equal(method.description, "Reads.")
  Assert.equal(method.typeParams.length, 1)
  case method.body { _: Block -> { } _ -> { panic("expected block body") } }
  Assert.equal(method.legacyMethodFunctionSpan == none, true)
  legacy := class_.methods[1]
  case legacy.body { _: Block -> { panic("expected expression body") } _ -> { } }
  // The legacy span covers `function legacy` for the checker's migration hint.
  Assert.equal(legacy.legacyMethodFunctionSpan!.end.offset - legacy.legacyMethodFunctionSpan!.start.offset, "function legacy".length)
}

export function testIsolatedClassMemberModifiers(): none {
  class_ := onlyClass("class Worker {\nisolated run(): int => 1\nisolated static make(): int => 2\nprivate isolated hidden(): int => 3\nprivate isolated static function both(): int => 4\nprivate function secret(): int => 5\n}")
  Assert.equal(class_.methods.length, 5)
  for index of 0..<4 { Assert.equal(class_.methods[index].isolated_, true) }
  Assert.equal(class_.methods[0].static_, false)
  Assert.equal(class_.methods[1].static_, true)
  Assert.equal(class_.methods[2].private_, true)
  Assert.equal(class_.methods[3].private_ && class_.methods[3].static_, true)
  Assert.equal(class_.methods[4].private_ && !class_.methods[4].isolated_, true)

  Assert.equal(parseFailure("class Bad { isolated value: int }").errorMessage, "Expected class method after 'isolated'")
  Assert.equal(parseFailure("class Bad { private isolated value: int }").errorMessage, "Expected class method after 'private isolated'")
}

export function testStaticMembersAfterTheStaticKeyword(): none {
  class_ := onlyClass("class Counter { static count: int = 0\nstatic next(): int => 1 }")
  Assert.equal(class_.fields[0].static_, true)
  Assert.equal(class_.methods[0].static_, true)
}

export function testFieldModifierDiagnostics(): none {
  Assert.stringContains(parseFailure("class Bad { let static value: int }").errorMessage, "order without duplicates")
  Assert.equal(parseFailure("class Bad { readonly const value: int = 1 }").errorMessage, "Field declarations accept only one of 'let', 'readonly', or 'const'")
}

export function testNativeDeclarationsReadHeaderAndCppName(): none {
  program := parse("import class Clock from \"clock.hpp\" as sys::Clock {\nnow(): long\nstatic make(): Clock => Clock {}\n}\nimport function tick(): int from \"tick.hpp\" as sys::detail::tick")
  clock := program.statements[0] as ClassDeclaration else { panic("expected native class") }
  Assert.equal(clock.nativeHeader, "clock.hpp")
  Assert.equal(clock.nativeCppName, "sys::Clock")
  Assert.equal(clock.methods[0].bodyless, true)
  Assert.equal(clock.methods[1].bodyless, false)
  tick := program.statements[1] as FunctionDeclaration else { panic("expected native function") }
  Assert.equal(tick.nativeHeader, "tick.hpp")
  Assert.equal(tick.nativeCppName, "sys::detail::tick")
  Assert.equal(tick.bodyless, true)

  bare := parse("import function plain(): int").statements[0] as FunctionDeclaration else { panic("expected native function") }
  Assert.equal(bare.nativeHeader, "")
  Assert.equal(bare.nativeCppName, "")
}

export function testLetDeclaratorsAcrossStatementsAndForInitializers(): none {
  program := parse("let total: int = 0;\nlet cached <- { yield 1 }\nfor let i = 0, j = 10; i < j; i += 1 { }")
  total := program.statements[0] as LetDeclaration else { panic("expected let") }
  // A statement's span includes its terminator.
  Assert.equal(total.span.end.offset, "let total: int = 0;".length)
  cached := program.statements[1] as LetDeclaration else { panic("expected let") }
  case cached.value { _: YieldBlockExpression -> { } _ -> { panic("expected yield block initializer") } }
  loop := program.statements[2] as ForStatement else { panic("expected for") }
  Assert.equal(loop.init.length, 2)

  Assert.equal(parseFailure("for let i <- { yield 0 }; i < 1; i += 1 { }").errorMessage, "Expected '=' in declaration")
  Assert.equal(parseFailure("let missing").errorMessage, "Expected '=' or '<-' in declaration")
}

export function testConstDeclarationKeepsKeywordSpan(): none {
  declaration := parse("const limit = 3").statements[0] as ConstDeclaration else { panic("expected const") }
  Assert.equal(declaration.keywordSpan.end.offset, "const".length)
}

export function testImportAndExportSpecifiersShareAliasParsing(): none {
  import_ := parse("import { a, b as c } from \"./m\"").statements[0] as ImportDeclaration else { panic("expected import") }
  Assert.isTrue(import_.specifiers[0].alias == none)
  Assert.equal(import_.specifiers[1].alias!, "c")
  export_ := parse("export { d as e, f }").statements[0] as ExportList else { panic("expected export list") }
  Assert.equal(export_.specifiers[0].alias!, "e")
  Assert.isTrue(export_.specifiers[1].alias == none)
}

export function testNativeClassMethodModifiersAndOptionalBodies(): none {
  class_ := parse("import class Clock from \"clock.hpp\" {\nisolated static now(): long\nstatic zone(): string\nisolated tick(): none\nlabel(): string => \"clock\"\nrate: int\nstatic count: int\n}").statements[0] as ClassDeclaration else { panic("expected native class") }
  Assert.equal(class_.methods.length, 4)
  Assert.equal(class_.fields.length, 2)
  let shapes = ""
  for method of class_.methods {
    shapes = shapes + (if method.isolated_ then "i" else "-") + (if method.static_ then "s" else "-") + (if method.bodyless then "b" else "d") + ";"
  }
  Assert.equal(shapes, "isb;-sb;i-b;--d;")
}

export function testLiteralValuedFieldsAcceptNegativeNumbers(): none {
  class_ := onlyClass("class Point { kind: -1 }")
  Assert.isTrue(class_.fields[0].const_)
  Assert.equal(class_.fields[0].defaultValue!.kind, "unary-expression")
}
