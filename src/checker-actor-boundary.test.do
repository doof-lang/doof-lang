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

function boundaryMessages(source: string): string[] {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  let messages: string[] = []
  for diagnostic of result.diagnostics { if diagnostic.severity == "error" { messages.push(diagnostic.message) } }
  return messages
}

export function testUnboundImplementationTypeParametersAreUnsafe(): none {
  messages := boundaryMessages(
    "interface Holder { describe(): string }\nclass Generic<T> implements Holder { readonly payload: T\ndescribe(): string => \"g\" }\n" +
    "class Worker { take(h: Holder): none { } }\nfunction main(): none { values := [1]\nworker := Actor<Worker>()\nworker.take(Generic<int[]> { payload: values }) }")
  Assert.equal(messages.length, 1)
  Assert.stringContains(messages[0], "implementation \"Generic\" cannot cross actor boundaries")
  Assert.stringContains(messages[0], "unbound type parameter \"T\" may hold mutable values")
}

export function testImplementationTypeParametersBindThroughTheInterface(): none {
  prefix := "interface Box<T> { describe(): string }\nclass Forward<T> implements Box<T> { readonly value: T\ndescribe(): string => \"f\" }\n"
  Assert.equal(boundaryMessages(prefix + "class Worker { take(b: Box<int>): none { } }\nfunction main(): none { worker := Actor<Worker>()\nworker.take(Forward<int> { value: 1 }) }").length, 0)
  rejected := boundaryMessages(prefix + "class Worker { take(b: Box<int[]>): none { } }\nfunction main(): none { worker := Actor<Worker>()\nworker.take(Forward<int[]> { value: [1] }) }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "array type \"int[]\" is mutable")
}

export function testBoundaryConstraintsMakeImplementationTypeParametersSafe(): none {
  prefix := "interface Plain { readonly value: int }\nclass Fixed implements Plain { readonly value: int }\ninterface Holder { describe(): string }\n" +
    "class Worker { take(h: Holder): none { } }\n"
  Assert.equal(boundaryMessages(prefix + "class Bounded<T: Plain> implements Holder { readonly payload: T\ndescribe(): string => \"b\" }\n" +
    "function main(): none { worker := Actor<Worker>()\nworker.take(Bounded<Fixed> { payload: Fixed { value: 1 } }) }").length, 0)
  Assert.equal(boundaryMessages(prefix + "class Numeric<T: int | long> implements Holder { readonly payload: T\ndescribe(): string => \"n\" }\n" +
    "function main(): none { worker := Actor<Worker>()\nworker.take(Numeric<int> { payload: 1 }) }").length, 0)
}

export function testReadonlyTypeParameterFieldsAreCheckedPerInstantiation(): none {
  Assert.equal(boundaryMessages("class Generic<T> { readonly payload: T }\nclass Worker { take(g: Generic<int>): none { } }\n" +
    "function main(): none { worker := Actor<Worker>()\nworker.take(Generic<int> { payload: 1 }) }").length, 0)
  rejected := boundaryMessages("class Generic<T> { readonly payload: T }\nclass Worker { take(g: Generic<int[]>): none { } }\n" +
    "function main(): none { worker := Actor<Worker>()\nworker.take(Generic<int[]> { payload: [1] }) }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "field \"payload\" cannot cross actor boundaries")
}

readonly nativeHandles = "import class Builder from \"builder.hpp\" { isolated append(value: int): none }\n" +
  "import isolated class Channel from \"channel.hpp\" { isolated close(): bool }\n"

export function testNativeClassesCrossOnlyWhenDeclaredIsolated(): none {
  rejected := boundaryMessages(nativeHandles + "class Worker { take(builder: Builder): none { } }\n" +
    "function main(builder: Builder): none { worker := Actor<Worker>()\nworker.take(builder) }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "native class \"Builder\" is not declared \"import isolated class\"")
  Assert.equal(boundaryMessages(nativeHandles + "class Worker { take(channel: Channel): none { } }\n" +
    "function main(channel: Channel): none { worker := Actor<Worker>()\nworker.take(channel) }").length, 0)
}

export function testNativeHandlesInsideReadonlyFieldsMustBeIsolated(): none {
  rejected := boundaryMessages(nativeHandles + "class Wrapper { readonly builder: Builder }\nclass Shared { readonly channel: Channel }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "Readonly field \"Wrapper.builder\" must be deeply immutable: native class \"Builder\"")
  Assert.equal(boundaryMessages(nativeHandles + "class Wrapper { builder: Builder }").length, 0)
}

export function testIsolatedNativeClassFieldsAreStillChecked(): none {
  rejected := boundaryMessages("import isolated class Point from \"point.hpp\" { let x: int }\nclass Worker { take(point: Point): none { } }\n" +
    "function main(point: Point): none { worker := Actor<Worker>()\nworker.take(point) }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "field \"x\" is mutable")
}

export function testPhantomTypeArgumentsMustBeBoundarySafe(): none {
  prefix := nativeHandles + "class Sender<T> { private readonly native: Channel\nsend(value: T): none { } }\n"
  Assert.equal(boundaryMessages(prefix + "class Worker { take(sender: Sender<readonly int[]>): none { } }\n" +
    "function main(sender: Sender<readonly int[]>): none { worker := Actor<Worker>()\nworker.take(sender) }").length, 0)
  rejected := boundaryMessages(prefix + "class Worker { take(sender: Sender<int[]>): none { } }\n" +
    "function main(sender: Sender<int[]>): none { worker := Actor<Worker>()\nworker.take(sender) }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "type argument \"T\" cannot cross actor boundaries: array type \"int[]\" is mutable")
}

export function testAsyncCapturesRejectNonIsolatedNativeClasses(): none {
  rejected := boundaryMessages(nativeHandles + "function main(builder: Builder, channel: Channel): none {\n" +
    "first := async { builder.append(1)\nyield 1 }\nsecond := async { yield channel }\nprintln(first.get()! + 1)\nsecond.get()! }")
  Assert.equal(rejected.length, 1)
  Assert.stringContains(rejected[0], "Async block capture \"builder\"")
  Assert.stringContains(rejected[0], "native class \"Builder\"")
}
