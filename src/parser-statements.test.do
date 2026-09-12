import { Assert as EditorAssert } from "std/assert"
import { Parser as EditorParser } from "./parser"
import { Block, FunctionDeclaration, ImmutableBinding, LambdaExpression, NamedType } from "./ast"

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
