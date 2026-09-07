import { SemanticTypeIdentities } from "./semantic-type-identities"
import { WorldviewPlan, indexWorldviewGraph } from "./emitter-worldview"
import { Statement, ExportDeclaration, ClassDeclaration, InterfaceDeclaration, FunctionDeclaration } from "./ast"
import { Assert } from "std/assert"

import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { hasErrorDiagnostics } from "./diagnostics"
import { buildInstantiationPlan } from "./emitter-monomorphize"
import { planWorldview } from "./emitter-worldview"
import { SourceFile } from "./semantic"

export function testPlansDenseRepeatedForeignUsesOnceInDeclarationOrder(): none {
  sources := [
    SourceFile {
      path: "/main.do",
      source: "import { makePair } from \"./factory\"\nfunction main(): int { first := makePair()\nsecond := makePair()\nreturn first.left.value + second.right.value }",
    },
    SourceFile {
      path: "/factory.do",
      source: "import { Left, Right } from \"./types\"\nexport class Pair { left: Left\nright: Right }\nexport function makePair(): Pair => Pair { left: Left { value: 1 }, right: Right { value: 2 } }",
    },
    SourceFile {
      path: "/types.do",
      source: "export class Unused { value: int }\nexport class Left { value: int }\nexport class Right { value: int }",
    },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checked := createChecker(analysis).check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)

  plan := planWorldview(analysis, "/main.do")
  Assert.equal(plan.modules.length, 3)
  Assert.equal(plan.modules[0].path, "/types.do")
  Assert.equal(plan.modules[0].program.statements.length, 2)
  Assert.equal(plan.modules[1].path, "/factory.do")
  Assert.equal(plan.modules[1].program.statements.length, 2)
  Assert.equal(plan.modules[2].path, "/main.do")
  Assert.equal(plan.modules[2].program.statements.length, 2)
}

export function testCollectsGenericInterfaceKeysDuringPrimaryWorldviewTraversal(): none {
  source := "interface Reader<T> { read(): T }\nclass IntReader { value: int\nread(): int => value }\nfunction makeReader(): Reader<int> => IntReader { value: 7 }\nfunction main(): int { reader := makeReader()\nreturn reader.read() }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  checked := createChecker(analysis).check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)

  plan := planWorldview(analysis, "/main.do", buildInstantiationPlan(analysis))
  Assert.equal(plan.interfaceKeys.length, 1)
}

export function testSelectsConcreteGenericArgumentDefinitionsInOwningModules(): none {
  sources := [
    SourceFile { path: "/main.do", source:
      "import { Color } from \"./color\"\nimport { identity, Box, Inspect } from \"./generic\"\n" +
      "function main(): int { value := Color { red: 7 }\n" +
      "box := Box<Color> { value }\nreturn Inspect.red<Color>(identity<Color>(box.value)) }" },
    SourceFile { path: "/color.do", source: "export struct Color { red: int }\nexport struct Unused { value: int }" },
    SourceFile { path: "/generic.do", source:
      "export function identity<T>(value: T): T => value\nexport class Box<T> { value: T }\n" +
      "export class Inspect { static red<T>(value: T): int => 7 }" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checked := createChecker(analysis).check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  plan := planWorldview(analysis, "/generic.do", buildInstantiationPlan(analysis))
  Assert.equal(plan.modules.length, 2)
  Assert.equal(plan.modules[0].path, "/color.do")
  Assert.equal(plan.modules[0].program.statements.length, 1)
  Assert.equal(plan.modules[1].path, "/generic.do")
}

export function testDependencyOptimizationKeepsOpaqueNativeClosuresAndOrdering(): none {
  sources := [
    SourceFile { path: "/main.do", source: "import { first } from \"./native\"\nimport { third } from \"./other\"\nfunction main(): int { value := first()\nreturn third() }" },
    SourceFile { path: "/native.do", source: "import { Token, Reader } from \"./types\"\nexport { Extra } from \"./extra\"\nexport import class First from \"first.hpp\" as vendor::First { next(): Second\nread(): Reader<int> }\nexport import class Second from \"second.hpp\" as vendor::Second { previous(): First\nvalue(): Token }\nexport import function first(): First from \"first.hpp\" as vendor::first\nexport import function hidden(): int from \"first.hpp\" as vendor::hidden\nexport import function secondOnly(): int from \"second.hpp\" as vendor::secondOnly" },
    SourceFile { path: "/other.do", source: "export import function third(): int from \"first.hpp\" as other::third\nexport import function sibling(): int from \"first.hpp\" as other::sibling" },
    SourceFile { path: "/types.do", source: "export class Token {}\nexport interface Reader<T> { read(): T }\nexport class IntReader { read(): int => 1 }" },
    SourceFile { path: "/extra.do", source: "export class Extra {}" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  Assert.equal(hasErrorDiagnostics(analysis.diagnostics), false)
  checker := createChecker(analysis)
  for path of ["/types.do", "/extra.do", "/native.do", "/other.do", "/main.do"] {
    Assert.equal(hasErrorDiagnostics(checker.check(path).diagnostics), false)
  }
  instantiations := buildInstantiationPlan(analysis)
  index := indexWorldviewGraph(analysis)
  plan := planWorldview(analysis, "/main.do", instantiations, index)
  Assert.equal(dependencyNames(plan, "/native.do"), "First,Second,first,hidden,secondOnly,")
  Assert.equal(dependencyNames(plan, "/other.do"), "third,sibling,")
  Assert.stringContains(dependencyNames(plan, "/types.do"), "Token,")
  Assert.stringContains(dependencyNames(plan, "/types.do"), "Reader,")
  Assert.equal(dependencyNames(plan, "/extra.do"), "Extra,")
  Assert.isTrue(plan.interfaceKeys.length > 0)
  repeated := planWorldview(analysis, "/main.do", instantiations, index)
  Assert.equal(repeated.modules.length, plan.modules.length)
  for i of 0..<plan.modules.length {
    Assert.equal(repeated.modules[i].path, plan.modules[i].path)
    Assert.equal(dependencyNames(repeated, plan.modules[i].path), dependencyNames(plan, plan.modules[i].path))
  }
  Assert.equal(repeated.interfaceKeys.length, plan.interfaceKeys.length)
  for i of 0..<plan.interfaceKeys.length { Assert.equal(repeated.interfaceKeys[i], plan.interfaceKeys[i]) }
  // The graph index is reusable; closure visitation belongs to each consumer.
  nativeRoot := planWorldview(analysis, "/native.do", instantiations, index)
  Assert.stringContains(dependencyNames(nativeRoot, "/types.do"), "Token,")
  Assert.equal(dependencyNames(nativeRoot, "/extra.do"), "Extra,")
}

function dependencyNames(plan: WorldviewPlan, path: string): string {
  let names = ""
  for module of plan.modules {
    if module.path != path { continue }
    for statement of module.program.statements { names = names + dependencyName(statement) }
  }
  return names
}

function dependencyName(statement: Statement): string {
  case statement {
    export_: ExportDeclaration -> { return dependencyName(export_.declaration) }
    class_: ClassDeclaration -> { return class_.name + "," }
    interface_: InterfaceDeclaration -> { return interface_.name + "," }
    function_: FunctionDeclaration -> { return function_.name + "," }
    _ -> { return "" }
  }
  return ""
}

export function testDependencySummaryReplayKeepsRootBodiesConsumerLocal(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/main.do", source: "import { choose } from \"./api\"\nfunction main(): int => choose()" },
    SourceFile { path: "/api.do", source: "import { bodyOnly } from \"./body\"\nexport function choose(): int => bodyOnly()" },
    SourceFile { path: "/body.do", source: "export function bodyOnly(): int => 1" },
  ]).analyze("/main.do")
  checker := createChecker(analysis)
  for path of ["/body.do", "/api.do", "/main.do"] { Assert.equal(hasErrorDiagnostics(checker.check(path).diagnostics), false) }
  graph := indexWorldviewGraph(analysis)
  first := planWorldview(analysis, "/main.do", none, graph)
  Assert.equal(dependencyNames(first, "/api.do"), "choose,")
  Assert.equal(dependencyNames(first, "/body.do"), "")
  owner := planWorldview(analysis, "/api.do", none, graph)
  Assert.equal(dependencyNames(owner, "/body.do"), "bodyOnly,")
  repeated := planWorldview(analysis, "/main.do", none, graph)
  Assert.equal(repeated.modules.length, first.modules.length)
  Assert.equal(dependencyNames(repeated, "/body.do"), "")
}

export function testReadonlyEmissionWorldviewPreparesRootTypes(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function identity(value: int): int => value" }]).analyze("/main.do")
  Assert.equal(hasErrorDiagnostics(createChecker(analysis).check("/main.do").diagnostics), false)
  identities := SemanticTypeIdentities {}
  index := indexWorldviewGraph(analysis, identities)
  plan := planWorldview(analysis, "/main.do", none, index)
  Assert.equal(plan.modules.length, 1)
  for statement of plan.modules[0].program.statements {
    case statement {
      function_: FunctionDeclaration -> {
        Assert.isTrue(identities.snapshot().identify(function_.params[0].resolvedType!) >= 0)
      }
      _ -> {}
    }
  }
}
