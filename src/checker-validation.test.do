import { compile } from "./compiler"
import { arrayType, primitive, unionType } from "./checker-types"
import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { validateCheckedTypes, validateResolved } from "./checker-validation"
import { CallExpression, FunctionDeclaration, MemberExpression } from "./ast"
import { Diagnostic, SourceFile } from "./semantic"

export function testCheckerConsolidationRequiresMemberTargetDecoration(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "class C { read(value: int = 9): int => value }\nfunction call(value: weak C): int => value!.read()",
  }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(checked.diagnostics.length, 0)
  Assert.equal(validateCheckedTypes(analysis).length, 0)
  let removed = false
  for module of analysis.modules {
    for statement of module.program.statements {
      case statement {
        fn: FunctionDeclaration -> {
          case fn.body {
            call: CallExpression -> {
              case call.callee {
                member: MemberExpression -> { member.resolvedMember = none; removed = true }
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
  Assert.isTrue(removed)
  diagnostics := validateCheckedTypes(analysis)
  Assert.equal(diagnostics.length, 1)
  Assert.stringContains(diagnostics[0].message, "has no checked member selection")
  Assert.equal(diagnostics[0].span.start.line, 2)
}

export function testSecondConsolidationRequiresConstructionPlan(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "class C { value: int }\nfunction make(): C => C(3)" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    fn: FunctionDeclaration -> { case fn.body {
      call: CallExpression -> { call.resolvedConstruction = none }
      _ -> { panic("expected call") }
    } }
    _ -> { panic("expected function") }
  }
  diagnostics := validateCheckedTypes(analysis)
  Assert.equal(diagnostics.length, 1)
  Assert.stringContains(diagnostics[0].message, "no checked plan")
  Assert.equal(diagnostics[0].span.start.line, 2)
}

export function testUnionMutabilityValidation(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function good(value: int[] | readonly string[]): none {}" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  Assert.equal(validateCheckedTypes(analysis).length, 0)
  let diagnostics: Diagnostic[] = []
  validateResolved(arrayType(unionType([arrayType(primitive("int")), arrayType(primitive("int"), true)])), analysis.modules[0].program.statements[0].span, "/main.do", "substituted type", diagnostics)
  Assert.equal(diagnostics.length, 1)
  Assert.stringContains(diagnostics[0].message, "cannot be distinguished at runtime")
  Assert.equal(diagnostics[0].span.start.line, 1)
}

export function testUnionMutabilityInferredMember(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Mutable { values: int[] }\nclass Frozen { values: readonly int[] }\nfunction read(value: Mutable | Frozen): none { items := value.values }\nfunction main(): none {}",
  }], "/main.do")
  Assert.equal(result.emission, none)
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("differ only in collection mutability") {
      Assert.equal(diagnostic.span.start.line, 3)
      found = true
    }
  }
  Assert.isTrue(found)
}
