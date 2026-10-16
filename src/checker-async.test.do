import { Assert } from "std/assert"
import { AnalysisResult, createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"
import { asyncResultViolation } from "./checker-async"
import { arrayType, mapType, primitive, promiseType, resultType, tupleType, weakType } from "./checker-types"

// Fails on parse or analysis diagnostics so a malformed fixture cannot pass
// unnoticed through a test that only inspects checker output.
function analyzed(source: string): AnalysisResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  return analysis
}

export function testSecondConsolidationAsyncNestedResultPolicy(): none {
  nested := arrayType(mapType(primitive("string"), resultType(tupleType([primitive("int"), promiseType(primitive("int"))]), primitive("string"))))
  Assert.equal(asyncResultViolation(createAnalyzer([]).analyze("/main.do"), nested), none)
  weakNested := arrayType(tupleType([primitive("int"), weakType(arrayType(primitive("int")))]))
  Assert.equal(asyncResultViolation(createAnalyzer([]).analyze("/main.do"), weakNested), "weak references cannot be transferred from async blocks")
  safe := arrayType(mapType(primitive("string"), primitive("int")))
  Assert.equal(asyncResultViolation(createAnalyzer([]).analyze("/main.do"), safe), none)
}

export function testSecondConsolidationAsyncCaptureHandleDirection(): none {
  analysis := analyzed("class Worker { value: int\nread(): int => value }\nfunction use(worker: Actor<Worker>): Promise<int> => async { yield worker.read() }")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  for diagnostic of checked.diagnostics { println(diagnostic.message) }
  Assert.equal(checked.diagnostics.length, 0)
}

function asyncErrors(source: string): string[] {
  checked := createChecker(analyzed(source), "/main.do").check("/main.do")
  let messages: string[] = []
  for diagnostic of checked.diagnostics { if diagnostic.severity == "error" { messages.push(diagnostic.message) } }
  return messages
}

export function testAsyncExpressionsRequireYieldingBlocksOrIsolatedCalls(): none {
  Assert.equal(asyncErrors("function compute(): int => 4\nfunction run(): Promise<int> => async compute()").length, 0)
  Assert.equal(asyncErrors("function run(): Promise<int> => async { yield 4 }").length, 0)
  missing := asyncErrors("function run(flag: bool): Promise<int> => async { if flag { yield 4 } }")
  Assert.equal(missing.length, 1)
  Assert.stringContains(missing[0], "Async blocks must yield a value on every path")
  notCall := asyncErrors("function run(): Promise<int> => async 4")
  Assert.equal(notCall.length, 1)
  Assert.stringContains(notCall[0], "`async` requires an actor method call or an inferrably isolated function call")
}

export function testAsyncThisCaptureReportsAtThis(): none {
  // Async capture is validated by the graph-wide isolation phase, not per-module checking.
  errors := compile([SourceFile { path: "/main.do", source: "class Worker { value: int = 1\nrun(): Promise<int> => async {\nyield this.value } }" }], "/main.do").diagnostics
  let found = false
  for diagnostic of errors {
    if diagnostic.message.contains("Async blocks cannot capture 'this'") {
      found = true
      Assert.equal(diagnostic.span.start.line, 3)
      Assert.equal(diagnostic.span.start.column, 7)
    }
  }
  for diagnostic of errors { println(diagnostic.message) }
  Assert.isTrue(found)
}

export function testAsyncResultsRejectUnboundImplementationTypeParameters(): none {
  prefix := "interface Holder { describe(): string }\nclass Generic<T> implements Holder { readonly payload: T\ndescribe(): string => \"g\" }\n"
  rejected := asyncErrors(prefix + "function run(): Promise<Holder> => async {\nlet holder: Holder = Generic { payload: (): int => 1 }\nyield holder }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "unbound type parameter \"T\" may hold callbacks, weak references, or streams")
  Assert.equal(asyncErrors("function relay<T>(value: T): Promise<T> => async { yield value }").length, 0)
}

import { asyncBlockCaptures } from "./checker-async"
import { AsyncExpression, Block, Expression, FunctionDeclaration } from "./ast"
import { collectBlockExpressions, collectExpressionTree } from "./ast-walk"

export function testAsyncBlockCapturesListOuterLocalsOnce(): none {
  result := analyzed("function main(): none {\nouter := 1\nother := 2\npending := async {\ninner := outer + other + outer\nyield inner + outer }\nprintln(pending.get()) }")
  checked := createChecker(result, "/main.do").check("/main.do")
  Assert.equal(checked.diagnostics.length, 0)
  let names: string[] = []
  for module of result.modules {
    for statement of module.program.statements {
      case statement {
        fn: FunctionDeclaration -> {
          case fn.body {
            body: Block -> {
              let roots: Expression[] = []
              collectBlockExpressions(body, roots)
              let all: Expression[] = []
              for root of roots { collectExpressionTree(root, all) }
              for expression of all {
                case expression {
                  async_: AsyncExpression -> {
                    case async_.expression {
                      block: Block -> { for capture of asyncBlockCaptures(block) { names.push(capture.name) } }
                      _ -> { }
                    }
                  }
                  _ -> { }
                }
              }
            }
            _ -> { }
          }
        }
        _ -> { }
      }
    }
  }
  Assert.equal(names.length, 2)
  Assert.equal(names[0], "outer")
  Assert.equal(names[1], "other")
}
