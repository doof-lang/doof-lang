import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testBlockLambdaInferredReturnPaths(): none {
  for body of [
    "{ return 42 }", "{ if flag { return 42 } else { return 7 } }",
    "{ if flag { return none }\nreturn 42 }",
    "{ if flag { panic(\"stop\") }\nreturn 42 }",
    "{ case flag { true -> { return 42 }\nfalse -> { return 7 } } }",
    "{ with value := 42 { return value } }",
    "{ while true {} }", "{ panic(\"stop\") }", "{ return panic(\"stop\") }",
    "{}", "{ return }",
  ] {
    result := compile([SourceFile { path: "/main.do", source: "function main(): none { fn := (flag: bool) => " + body + " }" }], "/main.do")
    for diagnostic of result.diagnostics { println(body + ": " + diagnostic.message) }
    Assert.equal(result.diagnostics.length, 0)
  }
}

export function testBlockLambdaCompletionDiagnostics(): none {
  for declaration of [
    "fn := (): never => {}",
    "fn := (flag: bool): never => { if flag { panic(\"stop\") } }",
    "fn := (): int => {}",
    "fn := (flag: bool) => { if flag { return 42 } }",
    "fn: (): never := => {}",
  ] {
    result := compile([SourceFile { path: "/main.do", source: "function main(): none { " + declaration + " }" }], "/main.do")
    Assert.isTrue(result.diagnostics.length > 0)
    Assert.stringContains(result.diagnostics[0].message, "may complete without returning")
    Assert.equal(result.diagnostics[0].span.start.line, 1)
  }
}

export function testBlockLambdaRejectsIncompatibleReturns(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): none { fn := (flag: bool) => { if flag { return 42 }\nreturn \"bad\" } }",
  }], "/main.do")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "provide an explicit type annotation")
  Assert.equal(result.diagnostics[0].span.start.line, 2)
  annotated := compile([SourceFile { path: "/main.do", source:
    "function main(): none { fn := (flag: bool): int | string => { if flag { return 42 }\nreturn \"ok\" } }",
  }], "/main.do")
  Assert.equal(annotated.diagnostics.length, 0)
}

export function testBlockLambdaBareReturnCannotOmitOptionalPayload(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): none { fn := (flag: bool) => { if flag { return }\nreturn 42 } }",
  }], "/main.do")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "Expected a return value")
}

export function testTrailingLambdasRequireNoneCallbacks(): none {
  valid := compile([SourceFile { path: "/main.do", source:
    "function each(xs: int[], f: (it: int): none): none { for x of xs { f(x) } }\n" +
    "function main(): none { each([1]) {\nnext := (x: int): int => { return x + 1 }\nprintln(next(it)) } }",
  }], "/main.do")
  Assert.equal(valid.diagnostics.length, 0)
  mapped := compile([SourceFile { path: "/main.do", source:
    "function main(): none { let items = [1]\nitems.map() { it * 2 } }",
  }], "/main.do")
  Assert.isTrue(mapped.diagnostics.length > 0)
  Assert.stringContains(mapped.diagnostics[0].message, "Trailing lambdas require a callback returning none")
  valued := compile([SourceFile { path: "/main.do", source:
    "function make(f: (): int): int => f()\nfunction main(): none { make() { println(1) } }",
  }], "/main.do")
  Assert.isTrue(valued.diagnostics.length > 0)
  Assert.stringContains(valued.diagnostics[0].message, "Trailing lambdas require a callback returning none")
}

function lambdaMessages(source: string): string[] {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  let found: string[] = []
  for diagnostic of result.diagnostics { found.push(diagnostic.message) }
  return found
}

export function testExpressionBodyKeepsDeclaredAndContextualReturnTypes(): none {
  // The declared return type is the lambda's signature, as for block bodies.
  Assert.equal(lambdaMessages("function main(): none { f := (x: int): double => x + 1\ny: (x: int): double := f }").length, 0)
  Assert.equal(lambdaMessages("function main(): none { f: (x: int): double := (x) => x + 1 }").length, 0)
  found := lambdaMessages("function main(): none { f := (x: int): string => x + 1 }")
  Assert.equal(found.length, 1)
  Assert.equal(found[0], "Cannot return int from lambda returning string")
}

export function testNoneCallbacksDiscardExpressionValues(): none {
  Assert.equal(lambdaMessages("function main(): none { let total = 0\nf: (x: int): none := (x) => total += x\ng: (x: int): none := (x) => x + 1 }").length, 0)
  found := lambdaMessages("function check(): Result<int, string> => Success(1)\nfunction main(): none { f: (x: int): none := (x) => check() }")
  Assert.equal(found.length, 1)
  Assert.equal(found[0], "Result value must be handled")
}

export function testParametersBindByNameOrByPosition(): none {
  prefix := "type Step = (acc: int, it: int, index: int): int\nfunction main(): none {\n"
  for lambda of [
    // Signature names bind by name: any subset, any order.
    "(index) => index", "(it, index) => it + index", "(index, acc) => acc - index", "(acc) => acc",
    // Other names bind by position and may omit trailing parameters.
    "(total, value) => total + value", "(total: int): int => total", "(acc, _, index) => acc + index",
    "(first, second, third) => first",
  ] {
    found := lambdaMessages(prefix + "step: Step := " + lambda + "\n}")
    for message of found { println(lambda + ": " + message) }
    Assert.equal(found.length, 0)
  }
  // By-name and positional binding give the parameters different meanings.
  Assert.equal(lambdaMessages("function main(): none { r: int[] := [5].map((index) => index) }").length, 0)
  Assert.equal(lambdaMessages("function main(): none { r: string[] := [5].map((label) => string(label)) }").length, 0)
}

export function testOutOfPlaceSignatureNameIsOneActionableError(): none {
  found := lambdaMessages("function main(): none { doubled := [1].map((index, value) => value * 2) }")
  Assert.equal(found.length, 1)
  Assert.equal(found[0], "Lambda parameter 'index' is parameter 2 of (it: int, index: int): int but is listed at position 1; name only signature parameters to bind them by name, or list them in order")
  generic := lambdaMessages("function main(): none { total := [1].reduce(0, (it, total) => total) }")
  Assert.equal(generic.length, 1)
  Assert.stringContains(generic[0], "Lambda parameter 'it' is parameter 2 of (acc: int, it: int, index: int): int")
  duplicate := lambdaMessages("type Pair = (a: int, b: int): int\nfunction main(): none { f: Pair := (a, a) => a }")
  Assert.equal(duplicate.length, 1)
  Assert.stringContains(duplicate[0], "already declared")
}
