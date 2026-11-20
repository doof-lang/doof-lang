import { Assert } from "std/assert"
import { AnalysisResult, createAnalyzer } from "./analyzer"
import { SourceFile } from "./semantic"
import { ClassDeclaration } from "./ast"

function analyzed(source: string): AnalysisResult {
  return createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
}

function classNamed(result: AnalysisResult, path: string, name: string): ClassDeclaration {
  for module of result.modules {
    if module.path != path { continue }
    for statement of module.program.statements {
      if class_ := statement as ClassDeclaration && class_.name == name { return class_ }
    }
  }
  panic("missing class: " + name)
}

function fieldNames(class_: ClassDeclaration): string {
  let names: string[] = []
  for field of class_.fields { for name of field.names { names.push(name) } }
  return joined(names, ",")
}

function messages(result: AnalysisResult): string[] {
  return result.diagnostics.map(=> "${it.span.start.line}:${it.span.start.column} ${it.message}")
}

export function testExpandsInclusionsAtTheirPositionInSourceOrder(): none {
  result := analyzed("struct Pos { line, column: int }\nclass Token {\ntext: string\n...Pos\nlet trivia: string = \"\"\n}")
  Assert.equal(messages(result).length, 0)
  token := classNamed(result, "/main.do", "Token")
  Assert.equal(fieldNames(token), "text,line,column,trivia")
  included := token.fields[1]
  origin := included.includedFrom else { panic("expected an included field") }
  Assert.equal(origin.source.name, "Pos")
  Assert.equal(included.span.start.line, 4)
  Assert.equal(included.type_ == none, true)
  Assert.equal(token.inclusions[0].resolvedSource?.name ?? "", "Pos")
}

export function testCopiesModifiersDefaultsAndDescriptionsButNotStatics(): none {
  result := analyzed("class Base {\nlet count \"How many.\": int = 1\nreadonly name: string\nweak owner: Base | none = none\nkind: \"base\"\nstatic shared: int = 0\nlabel(): string => name\n}\nclass Copy { ...Base }")
  Assert.equal(messages(result).length, 0)
  base := classNamed(result, "/main.do", "Base")
  copy := classNamed(result, "/main.do", "Copy")
  Assert.equal(fieldNames(copy), "count,name,owner,kind")
  Assert.equal(copy.methods.length, 0)
  Assert.equal(copy.fields[0].let_, true)
  Assert.equal(copy.fields[0].descriptions[0], "How many.")
  Assert.equal(copy.fields[0].defaultValue == base.fields[0].defaultValue, true)
  Assert.equal(copy.fields[1].readonly_, true)
  Assert.equal(copy.fields[2].weak_, true)
  Assert.equal(copy.fields[3].const_, true)
}

export function testExpandsTransitivelyAcrossModules(): none {
  result := createAnalyzer([
    SourceFile { path: "/main.do", source: "import { Node } from \"./node\"\nclass Leaf { ...Node\nvalue: int }" },
    SourceFile { path: "/node.do", source: "struct Span { start: int }\nexport class Node { ...Span\nlet resolved: bool = false }" },
  ]).analyze("/main.do")
  Assert.equal(messages(result).length, 0)
  Assert.equal(fieldNames(classNamed(result, "/main.do", "Leaf")), "start,resolved,value")
}

export function testExpansionIsIdempotentForReusedSyntax(): none {
  sources := [SourceFile { path: "/main.do", source: "struct Pos { line: int }\nclass Token { ...Pos\ntext: string }" }]
  first := createAnalyzer(sources)
  first.serialParsing = true
  first.editorMode = true
  previous := first.analyze("/main.do")
  second := createAnalyzer(sources)
  second.serialParsing = true
  second.editorMode = true
  second.reusableModules = previous.modules
  result := second.analyze("/main.do")
  Assert.equal(messages(result).length, 0)
  Assert.equal(result.modules[0].program == previous.modules[0].program, true)
  Assert.equal(fieldNames(classNamed(result, "/main.do", "Token")), "line,text")
}

export function testRejectsConflictingFieldNames(): none {
  result := analyzed("struct A { id: int }\nstruct B { id: int }\nclass C {\n...A\n...B\n}\nclass D {\nid: int\n...A\n}\nclass E {\n...A\nid: string\n}")
  Assert.equal(joined(messages(result), "\n"), joined([
    "5:1 Field \"id\" is already included from \"A\" (line 4); remove one inclusion or rename the field",
    "9:1 Field \"id\" from \"A\" is already declared on line 8; remove the inclusion or rename the field",
    "12:1 Field \"id\" from \"A\" is already declared on line 13; remove the inclusion or rename the field",
  ], "\n"))
  Assert.equal(fieldNames(classNamed(result, "/main.do", "C")), "id")
  Assert.equal(fieldNames(classNamed(result, "/main.do", "E")), "id")
}

export function testRejectsInadmissibleSources(): none {
  result := analyzed(joined([
    "interface I { x: int }",
    "class FromInterface { ...I }",
    "enum Color { Red }",
    "class FromEnum { ...Color }",
    "struct A { id: int }",
    "type Alias = A",
    "class FromAlias { ...Alias }",
    "import class Native from \"native.hpp\" { value: int }",
    "class FromNative { ...Native }",
    "class FromMissing { ...Missing }",
  ], "\n"))
  Assert.equal(joined(messages(result), "\n"), joined([
    "10:24 Unknown type 'Missing'",
    "2:26 Cannot include \"I\": only class and struct fields can be included",
    "4:21 Cannot include \"Color\": only class and struct fields can be included",
    "7:22 Cannot include \"Alias\": include the class or struct directly rather than a type alias",
    "9:23 Cannot include \"Native\": an extern class has no Doof-owned fields",
  ], "\n"))
}

export function testRejectsSourcesWithPrivateInstanceFields(): none {
  result := analyzed("class Session {\nid: int\nprivate secret: string = \"\"\n}\nclass Copy { ...Session }\nclass Counter { private static next: int = 0\nvalue: int }\nclass Counted { ...Counter }")
  Assert.equal(joined(messages(result), "\n"), "5:14 Cannot include \"Session\": it declares private field \"secret\"")
  Assert.equal(fieldNames(classNamed(result, "/main.do", "Counted")), "value")
}

export function testRejectsInclusionCycles(): none {
  result := analyzed("struct Self { ...Self }\nstruct Token { ...Pos }\nstruct Pos { ...Token\nline: int }")
  Assert.equal(joined(messages(result), "\n"), joined([
    "1:15 Inclusion cycle: \"Self\" includes \"Self\"",
    "3:14 Inclusion cycle: \"Token\" includes \"Pos\", which includes \"Token\"",
  ], "\n"))
  Assert.equal(fieldNames(classNamed(result, "/main.do", "Token")), "line")
}

function joined(values: string[], separator: string): string {
  let result = ""
  for index of 0..<values.length {
    if index > 0 { result += separator }
    result += values[index]
  }
  return result
}
