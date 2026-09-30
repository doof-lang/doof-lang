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
