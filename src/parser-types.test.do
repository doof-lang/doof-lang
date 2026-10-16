import { Assert } from "std/assert"
import { Parser, parse } from "./parser"
import { ClassDeclaration, NamedType, TypeAliasDeclaration } from "./ast"

function parseFailure(source: string): Parser {
  parser := Parser { source }
  case catchPanic(=> parser.parse()) {
    _: Failure<string> -> { }
    _ -> { panic("expected parse failure for: " + source) }
  }
  return parser
}

export function testTypeArgumentsShareOneListParser(): none {
  alias := parse("type Lookup = Map<string, Box<int>>").statements[0] as TypeAliasDeclaration else { panic("expected alias") }
  lookup := alias.type_ as NamedType else { panic("expected named type") }
  Assert.equal(lookup.typeArgs.length, 2)
  box := lookup.typeArgs[1] as NamedType else { panic("expected nested named type") }
  Assert.equal(box.name, "Box")
  Assert.equal(box.typeArgs.length, 1)

  class_ := parse("class Store implements Reader<string>, Sink<Box<int>> { }").statements[0] as ClassDeclaration else { panic("expected class") }
  Assert.equal(class_.implements_.length, 2)
  Assert.equal(class_.implements_[1].typeArgs.length, 1)
}

export function testMissingTypeNameIsReportedAtTheOffendingToken(): none {
  parser := parseFailure("type Broken = 42")
  Assert.equal(parser.errorMessage, "Expected a type name")
  Assert.equal(parser.errorOffset, "type Broken = ".length)
}
