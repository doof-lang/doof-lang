import { Assert } from "std/assert"
import { CallExpression, ConstructExpression, ExpressionStatement } from "./ast"
import { parse } from "./parser"

export function testInterfaceBoundNestedExplicitCallClosers(): none {
  program := parse("function main(): none { use<Box<Reader<int>>>(value) }")
  Assert.equal(program.statements.length, 1)
}

export function testUppercaseNamedCallParsing(): none {
  for source of ["GroupBox{title: \"Account\"}", "GroupBox{}", "Factory<int>{value: 1}", "Factory<int>(1)"] {
    program := parse(source)
    statement := program.statements[0] as ExpressionStatement else { panic("expected expression statement") }
    call := statement.expression as CallExpression else { panic("expected named or positional call") }
    Assert.equal(call.typeArgs.length, if source.startsWith("Factory") then 1 else 0)
  }
}

export function testUppercaseSpacedConstructionParsing(): none {
  for source of ["View {}", "View { value: 1 }", "View { ...other }"] {
    statement := parse(source).statements[0] as ExpressionStatement else { panic("expected statement") }
    construction := statement.expression as ConstructExpression else { panic("expected construction") }
    Assert.equal(construction.type_, "View")
  }
}
