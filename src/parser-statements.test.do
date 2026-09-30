import { Assert as EditorAssert } from "std/assert"
import { Parser as EditorParser } from "./parser"
import { Block, CaseExpression, CaseStatement, FunctionDeclaration, ImmutableBinding, LambdaExpression, MemberExpression, NamedType, UnaryExpression, ValuePattern, RangePattern, DotShorthand } from "./ast"

export function testEditorStatementRecoveryKeepsLaterDeclarations(): none {
  parser := EditorParser { source: "function main(): int {\nlet broken = ;\nreturn 42\n}", editorMode: true }
  program := parser.parse()
  EditorAssert.equal(program.statements.length, 1)
  EditorAssert.equal(parser.issues.length, 1)
}

export function testNormalizesNestedNamedFunctionsToImmutableLambdas(): none {
  parser := EditorParser { source:
    "function main(): none {\n" +
    "function action(message: string): none { println(message) }\n" +
    "action(\"Lights, camera, action!\")\n" +
    "}",
  }
  program := parser.parse()
  case program.statements[0] {
    outer: FunctionDeclaration -> { case outer.body {
      body: Block -> {
        case body.statements[0] {
          binding: ImmutableBinding -> {
            EditorAssert.equal(binding.name, "action")
            case binding.value {
              lambda: LambdaExpression -> {
                EditorAssert.equal(lambda.params.length, 1)
                EditorAssert.equal(lambda.params[0].name, "message")
                case lambda.returnType! {
                  named: NamedType -> { EditorAssert.equal(named.name, "none") }
                  _ -> { panic("expected nested function return annotation") }
                }
              }
              _ -> { panic("expected nested function lambda") }
            }
          }
          _ -> { panic("expected nested function immutable binding") }
        }
      }
      _ -> { panic("expected outer function block") }
    } }
    _ -> { panic("expected outer function declaration") }
  }
}

export function testDefaultsOmittedNestedFunctionReturnToNone(): none {
  parser := EditorParser { source: "function main(): none { function action() {}\naction() }" }
  program := parser.parse()
  case program.statements[0] {
    outer: FunctionDeclaration -> { case outer.body {
      body: Block -> { case body.statements[0] {
        binding: ImmutableBinding -> { case binding.value {
          lambda: LambdaExpression -> { case lambda.returnType! {
            named: NamedType -> { EditorAssert.equal(named.name, "none") }
            _ -> { panic("expected synthesized none return") }
          } }
          _ -> { panic("expected nested function lambda") }
        } }
        _ -> { panic("expected nested function binding") }
      } }
      _ -> { panic("expected outer function block") }
    } }
    _ -> { panic("expected outer function declaration") }
  }
}

export function testDiagnosesNestedFunctionFeaturesWithoutLambdaSemantics(): none {
  genericParser := EditorParser { source: "function main(): none { function identity<T>(value: T): T => value }" }
  genericResult := catchPanic(=> genericParser.parse())
  case genericResult { _: Failure<string> -> { } _ -> { panic("expected nested generic function parse failure") } }
  EditorAssert.equal(genericParser.errorMessage, "Nested generic functions are not supported; use a non-generic local function or a top-level generic function")

  isolatedParser := EditorParser { source: "function main(): none { isolated function action(): none {} }" }
  isolatedResult := catchPanic(=> isolatedParser.parse())
  case isolatedResult { _: Failure<string> -> { } _ -> { panic("expected nested modified function parse failure") } }
  EditorAssert.equal(isolatedParser.errorMessage, "Nested function modifiers are not supported; local functions use lambda semantics")

  defaultParser := EditorParser { source: "function main(): none { function action(value: int = 1): none {} }" }
  defaultResult := catchPanic(=> defaultParser.parse())
  case defaultResult { _: Failure<string> -> { } _ -> { panic("expected nested default parameter parse failure") } }
  EditorAssert.equal(defaultParser.errorMessage, "Nested function default parameters are not supported; handle defaults inside the function body or use a top-level function")

  editorParser := EditorParser {
    source: "function main(): none { function identity<T>(value: T): T => value\nprintln(\"still parsing\") }",
    editorMode: true,
  }
  editorProgram := editorParser.parse()
  EditorAssert.equal(editorProgram.statements.length, 1)
  EditorAssert.equal(editorParser.issues.length, 1)
  EditorAssert.equal(editorParser.issues[0].message, "Nested generic functions are not supported; use a non-generic local function or a top-level generic function")
}

function parsedCaseExpression(source: string): CaseExpression {
  parser := EditorParser { source, editorMode: true }
  program := parser.parse()
  EditorAssert.equal(parser.issues.length, 0)
  case program.statements[0] {
    binding: ImmutableBinding -> { case binding.value {
      expression: CaseExpression -> { return expression }
      _ -> { panic("expected case expression") }
    } }
    _ -> { panic("expected immutable binding") }
  }
}

export function testLineSeparatedCaseArmsStartingWithOperatorTokens(): none {
  expression := parsedCaseExpression(
    "result := case value {\n" +
    "  0 -> \"zero\"\n" +
    "  -1 -> \"minus\"\n" +
    "  ..<0 -> \"negative\"\n" +
    "  .North -> \"north\"\n" +
    "  _ -> \"other\"\n" +
    "}")
  EditorAssert.equal(expression.arms.length, 5)
  case expression.arms[1].patterns[0] {
    value: ValuePattern -> { case value.value {
      _: UnaryExpression -> { }
      _ -> { panic("expected negative literal pattern") }
    } }
    _ -> { panic("expected value pattern") }
  }
  case expression.arms[2].patterns[0] {
    range: RangePattern -> { EditorAssert.equal(range.start == none, true) }
    _ -> { panic("expected open range pattern") }
  }
  case expression.arms[3].patterns[0] {
    value: ValuePattern -> { case value.value {
      _: DotShorthand -> { }
      _ -> { panic("expected dot-shorthand pattern") }
    } }
    _ -> { panic("expected value pattern") }
  }
}

export function testCaseArmBodyStillContinuesAcrossLines(): none {
  expression := parsedCaseExpression(
    "result := case value {\n" +
    "  0 -> items\n" +
    "    .first\n" +
    "  _ -> fallback(case other {\n" +
    "    1 -> 2\n" +
    "    _ -> 3\n" +
    "  })\n" +
    "}")
  EditorAssert.equal(expression.arms.length, 2)
  case expression.arms[0].body {
    member: MemberExpression -> { EditorAssert.equal(member.property, "first") }
    _ -> { panic("expected continued member access body") }
  }
}

export function testLineSeparatedCaseStatementArmsStartingWithDot(): none {
  parser := EditorParser { source: "case direction {\n  .North -> go(1)\n  .South -> go(2)\n  -1 -> go(3)\n}", editorMode: true }
  program := parser.parse()
  EditorAssert.equal(parser.issues.length, 0)
  case program.statements[0] {
    statement: CaseStatement -> { EditorAssert.equal(statement.arms.length, 3) }
    _ -> { panic("expected case statement") }
  }
}
