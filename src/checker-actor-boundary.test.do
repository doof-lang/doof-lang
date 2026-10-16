import { Assert } from "std/assert"
import { AnalysisResult, createAnalyzer } from "./analyzer"
import { AsyncExpression, Block, Expression, FunctionDeclaration } from "./ast"
import { isActorMethodCall } from "./checker-actor-boundary"
import { createChecker } from "./checker"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testMutableReadonlyFieldReportsAtTheField(): none {
  result := compile([SourceFile { path: "/main.do", source: "class MutablePoint { let x: int }\nclass Container {\nreadonly point: MutablePoint }" }], "/main.do")
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("Readonly field \"Container.point\" must be deeply immutable") {
      found = true
      Assert.stringContains(diagnostic.message, "field \"x\" is mutable")
      Assert.equal(diagnostic.module, "/main.do")
      Assert.equal(diagnostic.span.start.line, 3)
    }
  }
  Assert.isTrue(found)
}

function functionBody(analysis: AnalysisResult, index: int): Expression {
  case analysis.modules[0].program.statements[index] {
    fn: FunctionDeclaration -> {
      case fn.body {
        expression: Expression -> { return expression }
        _: Block -> { panic("expected expression body") }
      }
    }
    _ -> { panic("expected function") }
  }
  panic("unreachable")
}

export function testActorMethodCallRequiresAnActorReceiver(): none {
  analysis := createAnalyzer([SourceFile {
    path: "/main.do",
    source: "class Counter { bump(): int => 1 }\nfunction remote(counter: Actor<Counter>): Promise<int> => async counter.bump()\nfunction local(counter: Counter): int => counter.bump()\nfunction value(counter: Actor<Counter>): Actor<Counter> => counter",
  }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(checked.diagnostics.length, 0)
  case functionBody(analysis, 1) {
    async_: AsyncExpression -> {
      case async_.expression {
        inner: Expression -> { Assert.isTrue(isActorMethodCall(inner)) }
        _: Block -> { panic("expected async call") }
      }
    }
    _ -> { panic("expected async expression") }
  }
  Assert.isFalse(isActorMethodCall(functionBody(analysis, 2)))
  Assert.isFalse(isActorMethodCall(functionBody(analysis, 3)))
}
