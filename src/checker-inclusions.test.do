import { Assert } from "std/assert"
import { AnalysisResult, createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"
import { ClassDeclaration } from "./ast"
import { typeName } from "./checker-types"

class Checked {
  analysis: AnalysisResult
  messages: string[]
}

function checkedSources(sources: SourceFile[]): Checked {
  analysis := createAnalyzer(sources).analyze(sources[0].path)
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  checker := createChecker(analysis, sources[0].path)
  let messages: string[] = []
  for module of analysis.modules {
    for diagnostic of checker.check(module.path).diagnostics {
      if diagnostic.severity == "error" { messages.push("${diagnostic.span.start.line}:${diagnostic.span.start.column} ${diagnostic.message}") }
    }
  }
  return Checked { analysis, messages }
}

function checked(source: string): Checked {
  return checkedSources([SourceFile { path: "/main.do", source }])
}

function fieldTypes(result: Checked, name: string): string {
  for statement of result.analysis.modules[0].program.statements {
    if class_ := statement as ClassDeclaration && class_.name == name {
      return joined(class_.fields.map(=> "${joined(it.names, ",")}: ${if resolved := it.resolvedType then typeName(resolved) else "?"}"), "; ")
    }
  }
  panic("missing class: " + name)
}

export function testIncludedFieldsKeepTheSourceTypesAndModifiers(): none {
  result := checked("class Node {}\nclass Base {\nlet count: int = 1\nreadonly names: string[]\nweak owner: Node | none = none\nkind: \"base\"\n}\nclass Copy { ...Base }")
  Assert.equal(result.messages.length, 0)
  Assert.equal(fieldTypes(result, "Copy"), fieldTypes(result, "Base"))
}

export function testSubstitutesInclusionTypeArguments(): none {
  result := checked(joined([
    "struct Timestamped<T> { value: T\nlet history: T[] = [] }",
    "class Setting<T> { ...Timestamped<T>\nkey: string }",
    "class Named { ...Timestamped<string> }",
    "class Nested { ...Setting<int> }",
  ], "\n"))
  Assert.equal(result.messages.length, 0)
  Assert.equal(fieldTypes(result, "Setting"), "value: T; history: T[]; key: string")
  Assert.equal(fieldTypes(result, "Named"), "value: string; history: string[]")
  Assert.equal(fieldTypes(result, "Nested"), "value: int; history: int[]; key: string")
}

export function testChecksInclusionTypeArguments(): none {
  result := checked("struct Box<T: int | string> { value: T }\nclass Bare { ...Box }\nclass Extra { ...Box<int, int> }\nclass Wrong { ...Box<bool> }")
  Assert.equal(joined(result.messages, "\n"), joined([
    "2:17 Box requires 1 type argument; received 0",
    "3:18 Box requires 1 type argument; received 2",
    "4:18 Type \"bool\" does not satisfy constraint \"int | string\" for type parameter \"T\"",
  ], "\n"))
}

export function testIncludedFieldsParticipateInConstructionAndInterfaces(): none {
  result := checked(joined([
    "struct Pos { line, column: int }",
    "interface Spanned { line: int }",
    "class Token implements Spanned { text: string\n...Pos\nlet trivia: string = \"\" }",
    "function startLine(node: Spanned): int => node.line",
    "function main(): none {",
    "  token := Token(\"if\", 3, 7)",
    "  named := Token { text: \"x\", line: 1, column: 2 }",
    "  spread := Token { ...Pos { line: 1, column: 2 }, text: \"y\" }",
    "  println(startLine(token) + named.column + spread.line)",
    "  wrong := Token { text: \"z\", line: \"one\", column: 2 }",
    "}",
  ], "\n"))
  Assert.equal(joined(result.messages, "\n"), "12:31 Cannot assign string to int")
}

export function testDefaultsAreCheckedInTheSourceScope(): none {
  result := checkedSources([
    SourceFile { path: "/main.do", source: "import { Base } from \"./base\"\nclass Copy { ...Base }\nfunction main(): none { println(Copy {}.tag) }" },
    SourceFile { path: "/base.do", source: "function defaultTag(): string => \"tag\"\nexport class Base { tag: string = defaultTag() }" },
  ])
  Assert.equal(result.messages.length, 0)
  Assert.equal(fieldTypes(result, "Copy"), "tag: string")
}

export function testIncludedFieldsConflictWithIncluderMethods(): none {
  result := checked("struct A { id: int }\nclass N {\n...A\nid(): int => 1\n}")
  Assert.equal(joined(result.messages, "\n"), "4:1 Member \"id\" is already declared in class \"N\"")
}

export function testStructIncludersRejectWeakAndSelfContainingFields(): none {
  result := checked("class Holder { weak owner: Holder | none = none }\nstruct Weakling { ...Holder }\nstruct Tree { ...Branch }\nstruct Branch { child: Tree }")
  Assert.equal(joined(result.messages, "\n"), joined([
    "2:19 Struct field \"owner\" cannot be weak",
    "3:15 Struct \"Tree\" cannot contain itself by value through field \"child\" included from \"Branch\"; use a class or a collection to add indirection",
  ], "\n"))
}

function joined(values: string[], separator: string): string {
  let result = ""
  for index of 0..<values.length {
    if index > 0 { result += separator }
    result += values[index]
  }
  return result
}
