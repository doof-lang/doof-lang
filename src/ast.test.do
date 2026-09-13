import { Assert as EditorAssert } from "std/assert"
import { analyzeEditor as editorAnalysis } from "./editor-incremental"
import { SourceFile as EditorSource } from "./semantic"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile, FunctionType } from "./semantic"
import { CallExpression, FunctionDeclaration, MemberExpression } from "./ast"
import { Assert } from "std/assert"
import { AstLocation, Block, BoolLiteral, CaseExpression, CaseStatement, CatchExpression, Expression, SourceSpan } from "./ast"
import { primitive, typeName } from "./checker-types"

export function testQuarkCaseSubjectDecorationIsSeparateFromStorage(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "class Item {}\n" +
    "function expression(item: weak Item): int => case item { _: Success -> 1\n_: Failure -> 0 }\n" +
    "function statement(item: weak Item): int { case item { _: Success -> { return 1 }\n_: Failure -> { return 0 } } }",
  }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  let inspected = 0
  for declaration of analysis.modules[0].program.statements {
    function_ := declaration as FunctionDeclaration else { continue }
    if function_.name == "expression" {
      expression := function_.body as CaseExpression else { panic("Expected case expression") }
      Assert.equal(typeName(expression.subject.resolvedType!), "weak Item")
      Assert.equal(typeName(expression.resolvedSubjectType!), "Result<Item, WeakReferenceError>")
      inspected += 1
    } else if function_.name == "statement" {
      block := function_.body as Block else { panic("Expected case block") }
      statement := block.statements[0] as CaseStatement else { panic("Expected case statement") }
      Assert.equal(typeName(statement.subject.resolvedType!), "weak Item")
      Assert.equal(typeName(statement.resolvedSubjectType!), "Result<Item, WeakReferenceError>")
      inspected += 1
    }
  }
  Assert.equal(inspected, 2)
}

export function testCheckerReviewMutableExpressionDecorations(): none {
  location := AstLocation { line: 1, column: 1, offset: 0 }
  span := SourceSpan { start: location, end: location }
  literal := BoolLiteral { kind: "bool-literal", value: true, span }
  caught := CatchExpression { body: Block { kind: "block", statements: [], span }, span }
  expressions: Expression[] := [literal, caught]
  for expression of expressions { expression.resolvedType = primitive("bool") }
  Assert.equal(typeName(literal.resolvedType!), "bool")
  Assert.equal(typeName(caught.resolvedType!), "bool")
}

export function testCheckerConsolidationMemberMetadataRetainsOwnerAndSignature(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "class Box<T> { read(value: T): T => value }\nfunction call(box: weak Box<int>): int => box!.read(3)",
  }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(checked.diagnostics.length, 0)
  let found = false
  for module of analysis.modules {
    for statement of module.program.statements {
      case statement {
        fn: FunctionDeclaration -> {
          case fn.body {
            call: CallExpression -> {
              case call.callee {
                member: MemberExpression -> {
                  selected := member.resolvedMember!
                  Assert.equal(selected.function_!.name, "read")
                  Assert.equal(selected.modulePath, "/main.do")
                  Assert.equal(typeName(selected.owner!), "Box<int>")
                  Assert.equal(call.resolvedFunction, selected.function_)
                  case selected.type_! { signature: FunctionType -> { Assert.equal(typeName(signature.params[0].type_), "int") } _ -> { panic("expected function") } }
                  found = true
                }
                _ -> { }
              }
            }
            _ -> { }
          }
        }
        _ -> { }
      }
    }
  }
  Assert.isTrue(found)
}

export function testSecondConsolidationConstructionPlanRetainsFactoryResult(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "class Box<T> { value: T\nstatic constructor(value: T): Result<Box<T>, string> => Success { value: Box<T> { value } } }\nfunction make(): Result<Box<int>, string> => Box<int>(3)",
  }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  for diagnostic of checked.diagnostics { println(diagnostic.message) }
  Assert.equal(checked.diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    fn: FunctionDeclaration -> { case fn.body {
      call: CallExpression -> {
        plan := call.resolvedConstruction!
        Assert.equal(typeName(plan.owner), "Box<int>")
        Assert.equal(typeName(plan.signature.params[0].type_), "int")
        Assert.equal(plan.signature.returnType.kind, "result")
        Assert.equal(plan.factory, call.resolvedConstructor)
        Assert.equal(plan.defaults.length, 1)
      }
      _ -> { panic("expected call") }
    } }
    _ -> { panic("expected function") }
  }
}

export function testEditorAstRetainsCheckedGraphWithScopes(): none {
  result := editorAnalysis([EditorSource { path: "/main.do", source: "function main(): int { value := 42; return value }" }], "/main.do")
  EditorAssert.equal(result.diagnostics.length, 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorScopes.length > 0)
  EditorAssert.isTrue(result.analysis.modules[0].editorExpressions.length > 0)
}
