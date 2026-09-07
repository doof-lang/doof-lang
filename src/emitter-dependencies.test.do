import { SemanticTypeIdentities } from "./semantic-type-identities"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceFile, Symbol, ClassType, InterfaceType } from "./semantic"
import { DependencyBuilder, DependencySummary, SymbolDependency, InterfaceDependency, collectDependencyType, summarizeDeclaration } from "./emitter-dependencies"

export function testDependencySummaryKeepsAliasesAndDefaultsWithoutForeignBodies(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/types.do", source: "export class A {}\nexport class B {}\nexport class DefaultOnly {}" },
    SourceFile { path: "/body.do", source: "export function bodyOnly(): int => 1" },
    SourceFile { path: "/main.do", source: "import { A, B, DefaultOnly } from \"./types\"\nimport { bodyOnly } from \"./body\"\nexport type Choice = A | B\nexport function choose(value: Choice = A {}, extra: int = makeDefault(DefaultOnly {})): Choice { bodyOnly()\nreturn value }\nfunction makeDefault(value: DefaultOnly): int => 0" },
  ]).analyze("/main.do")
  checker := createChecker(analysis)
  for path of ["/types.do", "/body.do", "/main.do"] { Assert.equal(hasErrorDiagnostics(checker.check(path).diagnostics), false) }
  let found = false
  for module of analysis.modules {
    if module.path != "/main.do" { continue }
    for statement of module.program.statements {
      summary := summarizeDeclaration(statement)
      names := summaryNames(summary)
      if !names.contains("makeDefault,") { continue }
      found = true
      Assert.stringContains(names, "A,B,Choice,")
      Assert.stringContains(names, "DefaultOnly,")
      Assert.stringNotContains(names, "bodyOnly,")
    }
  }
  Assert.isTrue(found)
}

export function testDependencySummaryFreezesOrderedInterfaceAndSymbolEvents(): none {
  owner := Symbol { kind: "interface", name: "Reader", module: "/reader.do", exported: true }
  item := Symbol { kind: "class", name: "Item", module: "/item.do", exported: true }
  implementation := Symbol { kind: "class", name: "ReaderImpl", module: "/impl.do", exported: true }
  owner.implementations.push(implementation)
  type_ := InterfaceType { name: "Reader", symbol: owner, typeArgs: [ClassType { name: "Item", symbol: item }] }
  builder := DependencyBuilder {}
  collectDependencyType(type_, builder)
  collectDependencyType(type_, builder)
  summary := builder.finish()
  Assert.equal(summary.events.length, 4)
  Assert.equal(summaryNames(summary), "Reader,<interface>,ReaderImpl,Item,")
  // Published events contain scalar identities, with no live semantic links.
  owner.implementations.push(Symbol { kind: "class", name: "Later", module: "/later.do", exported: true })
  Assert.equal(summaryNames(summary), "Reader,<interface>,ReaderImpl,Item,")
  Assert.equal(builder.events.length, 0)
  fresh := DependencyBuilder {}
  collectDependencyType(type_, fresh)
  Assert.equal(summaryNames(fresh.finish()), "Reader,<interface>,ReaderImpl,Later,Item,")
  Assert.equal(DependencyBuilder {}.finish().events.length, 0)
}

function summaryNames(summary: DependencySummary): string {
  let result = ""
  for event of summary.events {
    case event {
      symbol: SymbolDependency -> { result = result + symbol.name + "," }
      interface_: InterfaceDependency -> { result = result + "<interface>," }
    }
  }
  return result
}

export function testReadonlyEmissionDependencyExtractionPreparesTypes(): none {
  identities := SemanticTypeIdentities {}
  symbol := Symbol { name: "Item", kind: "class", module: "/item.do", exported: true }
  type_ := ClassType { name: "Item", symbol }
  builder := DependencyBuilder { identities }
  collectDependencyType(type_, builder)
  Assert.isTrue(identities.snapshot().identify(type_) >= 0)
  Assert.equal(summaryNames(builder.finish()), "Item,")
}
