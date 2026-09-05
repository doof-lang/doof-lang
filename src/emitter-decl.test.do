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

export function testEmitsStructFieldEqualityWithoutStaticFields(): none {
  result := emit("struct Color { red: int\nstatic let count: int = 0 }\nstruct Empty {}\nclass Node { value: int }")
  Assert.stringContains(result.header, "(this->red == _doof_other.red)")
  Assert.stringNotContains(result.header, "this->count ==")
  Assert.stringContains(result.header, "bool operator!=(const _DoofOther& _doof_other) const { return !(*this == _doof_other); }")
  Assert.stringContains(result.header, "_DoofOther = Empty>")
  Assert.stringNotContains(result.header, "_DoofOther = Node>")
}

struct EqualityColor { red: int }
struct EqualityNested { color: EqualityColor
  label: string }
struct EqualityEmpty {}
class EqualityNode { value: int }
struct EqualityReference { node: EqualityNode }
struct EqualityGeneric<T> { value: T }

export function testStructFieldEqualityRuntimePaths(): none {
  Assert.equal(EqualityColor { red: 7 }, EqualityColor { red: 7 })
  Assert.isTrue(EqualityColor { red: 7 } != EqualityColor { red: 8 })
  Assert.equal(EqualityNested { color: EqualityColor { red: 7 }, label: "red" }, EqualityNested { color: EqualityColor { red: 7 }, label: "red" })
  Assert.isTrue(EqualityNested { color: EqualityColor { red: 7 }, label: "red" } != EqualityNested { color: EqualityColor { red: 7 }, label: "blue" })
  Assert.equal(EqualityEmpty {}, EqualityEmpty {})
  node := EqualityNode { value: 1 }
  Assert.equal(EqualityReference { node }, EqualityReference { node })
  Assert.isTrue(EqualityReference { node } != EqualityReference { node: EqualityNode { value: 1 } })
  Assert.equal(EqualityGeneric<int> { value: 3 }, EqualityGeneric<int> { value: 3 })
}

export function testRejectsEqualityAcrossNominalStructTypes(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "struct Left { value: int }\nstruct Right { value: int }\n" +
    "function main(): bool => Left { value: 1 } == Right { value: 1 }",
  }], "/main.do")
  Assert.isTrue(hasErrorDiagnostics(result.diagnostics))
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("Operator '==' is not defined for Left and Right") { found = true }
  }
  Assert.isTrue(found)
}
