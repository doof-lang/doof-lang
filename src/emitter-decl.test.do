import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { emitFunctionDeclaration } from "./emitter-decl"
import { ModuleEmission } from "./emitter-module"
import { FunctionDeclaration } from "./ast"
import { SourceFile } from "./semantic"

function emit(source: string): ModuleEmission {
  compilation := compile([SourceFile { path: "/main.do", source }], "/main.do")
  Assert.equal(hasErrorDiagnostics(compilation.diagnostics), false)
  graph := compilation.emission else { panic("source graph was not emitted") }
  for module of graph.modules { if module.modulePath == "/main.do" { return module } }
  panic("entry module was not emitted")
}

export function testBorrowsImmutableReferenceAndVariantParameters(): none {
  result := emit(
    "class Node { value: int }\n" +
    "function inspect(text: string, nodes: Node[], node: Node, value: Node | none): int => text.length + nodes.length + node.value + value!.value",
  )

  Assert.stringContains(result.header, "const std::string& text")
  Assert.stringContains(result.header, "const std::shared_ptr<std::vector<std::shared_ptr<Node>>>& nodes")
  Assert.stringContains(result.header, "const std::shared_ptr<Node>& node")
  Assert.stringContains(result.header, "const std::shared_ptr<Node>& value")
}

export function testRetainsValueSemanticsForCheapAndStructParameters(): none {
  result := emit(
    "struct Counter { let value: int }\n" +
    "function update(count: int, counter: Counter): int { counter.value = counter.value + count\nreturn counter.value }",
  )

  Assert.stringContains(result.header, "int32_t count")
  Assert.stringContains(result.header, "Counter counter")
  Assert.stringNotContains(result.header, "const Counter& counter")
}

export function testKeepsCallbackAbiOwningWhileBorrowingNamedFunctions(): none {
  result := emit(
    "function apply(callback: (value: string): int, value: string): int => callback(value)\n" +
    "function size(value: string): int => value.length\n" +
    "function main(): int => apply(size, \"hello\")",
  )

  Assert.stringContains(result.header, "const doof::callback<int32_t(std::string)>& callback")
  Assert.stringContains(result.header, "const std::string& value")
  Assert.stringContains(result.header, "doof::callback<int32_t(std::string)>")
}

export function testRejectsGenericDeclarationsWithoutConcreteInstantiation(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function identity<T>(value: T): T => value" }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  let declaration: FunctionDeclaration | none = none
  for module of analysis.modules {
    if module.path != "/main.do" { continue }
    case module.program.statements[0] {
      function_: FunctionDeclaration -> { declaration = function_ }
      _ -> { }
    }
  }
  Assert.isTrue(declaration != none)

  result := catchPanic(=> emitFunctionDeclaration(declaration!))
  case result {
    failure: Failure<string> -> { Assert.stringContains(failure.error, "without a concrete instantiation") }
    _ -> { panic("expected generic declaration emission to panic") }
  }
}
