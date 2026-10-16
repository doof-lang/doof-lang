import { Assert as EditorAssert } from "std/assert"
import { Parser as EditorParser } from "./parser"
import { Assert } from "std/assert"
import { ActorCreationExpression, ArrayLiteral, BinaryExpression, CallExpression, ConstructExpression, DoubleLiteral, ExpressionStatement, LambdaExpression, LetDeclaration, MemberExpression, ObjectLiteral, StringLiteral, TupleLiteral, UnaryExpression } from "./ast"
import type { Expression } from "./ast"
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

function expressionOf(source: string): Expression {
  statement := parse(source).statements[0] as ExpressionStatement else { panic("expected expression statement") }
  return statement.expression
}

export function testBinaryPrecedenceLevels(): none {
  // `||` < `&&` < `|` < `^` < `&` < equality < comparison < shift < range < additive < multiplicative < `**`.
  or_ := expressionOf("a || b && c | d ^ e & f == g < h << i + j * k ** l") as BinaryExpression else { panic("expected binary") }
  Assert.equal(or_.operator, "||")
  let node = or_.right
  for operator of ["&&", "|", "^", "&", "==", "<", "<<", "+", "*", "**"] {
    binary := node as BinaryExpression else { panic("expected " + operator) }
    Assert.equal(binary.operator, operator)
    node = binary.right
  }
  // Each level is left-associative except `**`.
  minus := expressionOf("a - b - c") as BinaryExpression else { panic("expected binary") }
  Assert.equal(minus.left.kind, "binary-expression")
  power := expressionOf("a ** b ** c") as BinaryExpression else { panic("expected binary") }
  Assert.equal(power.right.kind, "binary-expression")
}

export function testMemberAccessOnPlainIdentifiersGoesThroughPostfix(): none {
  member := expressionOf("Shape.Circle.radius") as MemberExpression else { panic("expected member") }
  Assert.equal(member.property, "radius")
  inner := member.object as MemberExpression else { panic("expected inner member") }
  Assert.equal(inner.property, "Circle")
  Assert.equal(inner.span.start.offset, 0)
  Assert.equal(inner.span.end.offset, "Shape.Circle".length)
  generic := expressionOf("Channel<string>.tag()") as CallExpression else { panic("expected call") }
  receiver := generic.callee as MemberExpression else { panic("expected static member") }
  Assert.equal(receiver.receiverTypeArgs.length, 1)
}

export function testParameterlessAndParenthesizedLambdasShareOneBuilder(): none {
  bare := expressionOf("=> 1") as LambdaExpression else { panic("expected lambda") }
  Assert.isTrue(bare.parameterless)
  Assert.isTrue(bare.returnType == none)
  empty := expressionOf("(): int => 1") as LambdaExpression else { panic("expected lambda") }
  Assert.isTrue(empty.parameterless)
  Assert.isTrue(empty.returnType != none)
}

export function testFloatingLiteralValuesIgnoreDigitSeparators(): none {
  for source of ["1.5_0", "1_0.2_5e0_1", "0.000_5"] {
    literal := expressionOf(source) as DoubleLiteral else { panic("expected double literal") }
    expected := if source == "1.5_0" then 1.5 else if source == "0.000_5" then 0.0005 else 102.5
    Assert.equal(literal.value, expected, source)
  }
  // Integral digits beyond long accumulate as a double instead of wrapping.
  huge := expressionOf("12345678901234567890123.0") as DoubleLiteral else { panic("expected double literal") }
  Assert.isTrue(huge.value > 1.2e22 && huge.value < 1.3e22)
}

function expressionFailure(source: string): EditorParser {
  parser := EditorParser { source }
  case catchPanic(=> parser.parse()) {
    _: Failure<string> -> { }
    _ -> { panic("expected parse failure for: " + source) }
  }
  return parser
}

export function testObjectLiteralsAndConstructionsAcceptOneSpread(): none {
  object := expressionOf("({ ...base, name: 1 })") as ObjectLiteral else { panic("expected object literal") }
  Assert.isTrue(object.spread != none)
  Assert.equal(object.properties.length, 1)
  // A second spread used to replace the first silently.
  objectFailure := expressionFailure("x := { ...a, ...b }")
  Assert.equal(objectFailure.errorMessage, "Object literals support only one field spread")
  Assert.equal(objectFailure.errorOffset, "x := { ...a, ".length)
  constructFailure := expressionFailure("x := Box { ...a, ...b }")
  Assert.equal(constructFailure.errorMessage, "Named construction supports only one field spread")
  Assert.equal(constructFailure.errorOffset, "x := Box { ...a, ".length)
}

export function testTemplateLiteralsAlternateTextAndInterpolations(): none {
  one := expressionOf("\"a\${x}b\"") as StringLiteral else { panic("expected string") }
  Assert.equal(joinedParts(one), "a|<expression>|b|")
  Assert.equal(one.interpolations.length, 1)
  three := expressionOf("\"\${x}-\${y}-\${z}\"") as StringLiteral else { panic("expected string") }
  Assert.equal(joinedParts(three), "|<expression>|-|<expression>|-|<expression>||")
  Assert.equal(three.value, "<expression>-<expression>-<expression>")
  Assert.equal(three.interpolations.length, 3)
}

function joinedParts(literal: StringLiteral): string {
  let result = ""
  for part of literal.parts { result = result + part + "|" }
  return result
}

export function testDelimitedExpressionListsAllowTrailingCommas(): none {
  array := expressionOf("[1, 2,]") as ArrayLiteral else { panic("expected array") }
  Assert.equal(array.elements.length, 2)
  tuple := expressionOf("(1, 2, 3,)") as TupleLiteral else { panic("expected tuple") }
  Assert.equal(tuple.elements.length, 3)
  actor := expressionOf("Actor<Worker>(1, \"a\",)") as ActorCreationExpression else { panic("expected actor creation") }
  Assert.equal(actor.className, "Worker")
  Assert.equal(actor.args.length, 2)
}

export function testScalarKeysAndTagAttributesShareLiteralRecognition(): none {
  map := expressionOf("({ -1: \"neg\", 2.5: \"half\", .Red: \"red\", Color.Blue: \"blue\" })") as ObjectLiteral else { panic("expected map literal") }
  let kinds = ""
  for property of map.properties { kinds = kinds + property.key!.kind + ";" }
  Assert.equal(kinds, "unary-expression;double-literal;dot-shorthand;member-expression;")
  tag := expressionOf("<Gauge min=-1 max=2.5 tone=.Warm />") as CallExpression else { panic("expected tag call") }
  let values = ""
  for argument of tag.args { values = values + argument.value.kind + ";" }
  Assert.equal(values, "unary-expression;double-literal;dot-shorthand;")
}
