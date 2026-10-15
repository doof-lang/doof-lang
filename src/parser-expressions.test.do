import { Assert as EditorAssert } from "std/assert"
import { Parser as EditorParser } from "./parser"
import { Assert } from "std/assert"
import { BinaryExpression, CallExpression, ConstructExpression, ExpressionStatement, LetDeclaration, MemberExpression, ObjectLiteral, UnaryExpression } from "./ast"
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

export function testEditorPostfixRecoveryKeepsLiteralReceiver(): none {
  parser := EditorParser { source: "function main(): none {\n\"name\".\n}", editorMode: true }
  program := parser.parse()
  EditorAssert.equal(program.statements.length, 1)
  EditorAssert.equal(parser.issues.length, 1)
}

export function testPostfixQuestionConvertsTheOperand(): none {
  statement := parse("load()?").statements[0] as ExpressionStatement else { panic("expected statement") }
  conversion := statement.expression as UnaryExpression else { panic("expected postfix conversion") }
  Assert.equal(conversion.kind, "optional-conversion")
  Assert.equal(conversion.operator, "?")
  Assert.isFalse(conversion.prefix)
  Assert.equal(conversion.span.end.offset, 7)
  // Postfix binds tighter than '??', and '?.' stays one token.
  coalesce := parse("load()? ?? 1").statements[0] as ExpressionStatement else { panic("expected statement") }
  binary := coalesce.expression as BinaryExpression else { panic("expected coalescing") }
  Assert.equal(binary.operator, "??")
  Assert.equal(binary.left.kind, "optional-conversion")
  chained := parse("load()?!.name").statements[0] as ExpressionStatement else { panic("expected statement") }
  member := chained.expression as MemberExpression else { panic("expected member access") }
  Assert.isTrue(member.force)
  Assert.equal(member.object.kind, "optional-conversion")
}

export function testParenthesizedMapKeysAcceptAnyExpression(): none {
  program := parse("let m = { (1, \"a\"): 1, (node): 2, (Point { x: 1 }): 3, ((a)): 4 }")
  declaration := program.statements[0] as LetDeclaration else { panic("expected let declaration") }
  object := declaration.value as ObjectLiteral else { panic("expected map literal") }
  Assert.equal(object.properties.length, 4)
  let kinds = ""
  for property of object.properties {
    Assert.isTrue(property.key != none)
    Assert.isTrue(property.value != none)
    kinds = kinds + property.key!.kind + ";"
  }
  // The colon after the closing parenthesis starts the value, never a lambda return type.
  Assert.equal(kinds, "tuple-literal;identifier;construct-expression;identifier;")
}
