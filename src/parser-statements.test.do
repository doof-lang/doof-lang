import { Assert as EditorAssert } from "std/assert"
import { Parser as EditorParser, parse } from "./parser"
import {
  Block, BreakStatement, CaseExpression, CaseStatement, ContinueStatement, ForOfStatement, ForStatement, FunctionDeclaration, ImmutableBinding,
  LambdaExpression, MemberExpression, NamedType, TryStatement, UnaryExpression, ValuePattern, RangePattern, DotShorthand, WhileStatement,
} from "./ast"

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

export function testRejectsModuleDeclarationsInsideBlocks(): none {
  cases: string[][] := [
    ["import { Helper } from \"./helper\"", "Import declarations are only valid at module level"],
    ["import function cos(x: double): double from \"<cmath>\"", "Import declarations are only valid at module level"],
    ["mock import for \"./a\" { \"./b\" => \"./c\" }", "mock import directives are only valid at module level"],
    ["export { helper }", "Export declarations are only valid at module level"],
    ["class Local { x: int }", "Class declarations are only valid at module level"],
    ["private struct Point { x: int }", "Struct declarations are only valid at module level"],
    ["interface Shape { area(): double }", "Interface declarations are only valid at module level"],
    ["enum Color { Red, Green }", "Enum declarations are only valid at module level"],
    ["type Id = int", "Type alias declarations are only valid at module level"],
  ]
  for entry of cases {
    parser := EditorParser { source: "function main(): none {\n  if true {\n    " + entry[0] + "\n  }\n}" }
    result := catchPanic(=> parser.parse())
    case result { _: Failure<string> -> { } _ -> { panic("expected module directive parse failure: " + entry[0]) } }
    EditorAssert.equal(parser.errorMessage, entry[1])
    EditorAssert.equal(parser.errorLine, 3)
    EditorAssert.equal(parser.errorColumn, 5)
  }

  editorParser := EditorParser { source: "function main(): none {\nimport { Helper } from \"./helper\"\nprintln(\"still parsing\")\n}", editorMode: true }
  program := editorParser.parse()
  EditorAssert.equal(program.statements.length, 1)
  EditorAssert.equal(editorParser.issues.length, 1)
  EditorAssert.equal(editorParser.issues[0].message, "Import declarations are only valid at module level")
  EditorAssert.equal(editorParser.issues[0].span.start.line, 2)
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

function parseFailure(source: string): EditorParser {
  parser := EditorParser { source }
  case catchPanic(=> parser.parse()) {
    _: Failure<string> -> { }
    _ -> { panic("expected parse failure for: " + source) }
  }
  return parser
}

export function testImmutableBindingFormsShareElseCapture(): none {
  program := parse("value := load() else failure { return }\ntyped: int := load() else { return }\n_ := load() else { return }\nload() else problem { return }")
  let names = ""
  for statement of program.statements {
    binding := statement as ImmutableBinding else { panic("expected immutable binding") }
    EditorAssert.isTrue(binding.else_ != none)
    names = names + binding.name + "/" + (binding.failureName ?? "-") + ";"
  }
  EditorAssert.equal(names, "value/failure;typed/-;_/-;_/problem;")
  typed := program.statements[1] as ImmutableBinding else { panic("expected typed binding") }
  EditorAssert.isTrue(typed.type_ != none)
}

export function testTryBindingsCannotHandleFailureWithElse(): none {
  message := "A 'try' binding cannot have an 'else' block; use 'try' to propagate the failure or 'name := expr else { ... }' to handle it"
  for source of ["try value := load() else { return }", "try value: int := load() else failure { return }"] {
    parser := parseFailure(source)
    EditorAssert.equal(parser.errorMessage, message)
    EditorAssert.equal(parser.errorOffset, source.indexOf(" else") + 1)
  }
  for source of ["try value := load()", "try value: int := load()"] {
    statement := parse(source).statements[0] as TryStatement else { panic("expected try statement") }
    binding := statement.binding as ImmutableBinding else { panic("expected binding") }
    EditorAssert.equal(binding.name, "value")
    // The binding span starts at its name for typed and untyped forms alike.
    EditorAssert.equal(binding.span.start.offset, "try ".length)
  }
}

export function testDestructuringShapesForStatementsTryAndLet(): none {
  program := parse("[a, b] := pair\n(c, d) = pair\n{ name } := person\ntry [e, _] := load()\ntry (f, g) = load()\nlet { age as years } = person")
  let kinds = ""
  for statement of program.statements {
    case statement {
      try_: TryStatement -> { kinds = kinds + "try:" + try_.binding.kind + ";" }
      _ -> { kinds = kinds + statement.kind + ";" }
    }
  }
  EditorAssert.equal(kinds, "array-destructuring;positional-destructuring-assignment;named-destructuring;try:array-destructuring;try:positional-destructuring-assignment;named-destructuring;")
}

export function testLoopThenBlocksAndJumpLabels(): none {
  program := parse("outer: while true { break outer\n}\nfor x of items { continue\nlabel } then { }\nfor let i = 0; i < 3; i += 1 { } then { }")
  loop := program.statements[0] as WhileStatement else { panic("expected while") }
  EditorAssert.equal(loop.label!, "outer")
  EditorAssert.isTrue(loop.then_ == none)
  jump := loop.body.statements[0] as BreakStatement else { panic("expected break") }
  EditorAssert.equal(jump.label!, "outer")
  each := program.statements[1] as ForOfStatement else { panic("expected for-of") }
  EditorAssert.isTrue(each.then_ != none)
  // A label on the next line is a separate statement.
  next := each.body.statements[0] as ContinueStatement else { panic("expected continue") }
  EditorAssert.isTrue(next.label == none)
  EditorAssert.equal(each.body.statements.length, 2)
  counted := program.statements[2] as ForStatement else { panic("expected for") }
  EditorAssert.isTrue(counted.then_ != none)
}

export function testRangePatternForms(): none {
  statement := parse("case n { ..<0 -> a(), 0..9 -> b(), 10.. -> c(), 20..<30 -> d() }").statements[0] as CaseStatement else { panic("expected case") }
  let shapes = ""
  for arm of statement.arms {
    range := arm.patterns[0] as RangePattern else { panic("expected range pattern") }
    shapes = shapes + (if range.start == none then "_" else "s") + (if range.end == none then "_" else "e") + (if range.inclusive then "=" else "<") + ";"
  }
  EditorAssert.equal(shapes, "_e<;se=;s_=;se<;")
}
