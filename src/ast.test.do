import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile, FunctionType } from "./semantic"
import { CallExpression, FunctionDeclaration, MemberExpression } from "./ast"
import { Assert } from "std/assert"
import { AstLocation, Block, BoolLiteral, CatchExpression, Expression, SourceSpan } from "./ast"
import { primitive, typeName } from "./checker-types"

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
