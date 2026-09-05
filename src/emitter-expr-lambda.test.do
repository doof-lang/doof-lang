import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testModuleMutableBindingsRemainNamespaceStorageInLambda(): none {
  result := compile([SourceFile {
    path: "/module-callback.do",
    source:
      "let values: int[] = []\n" +
      "let count = 0\n" +
      "function invoke(handler: (): none): none { handler.call() }\n" +
      "export function start(): none { invoke((): none => { values.push(1)\ncount += 1 }) }",
  }], "/module-callback.do")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "doof::callback<void()>([]() -> void")
  Assert.stringContains(source, "values->push_back(1);")
  Assert.stringContains(source, "(count += 1);")
  Assert.stringNotContains(source, "[values, count]")
  Assert.stringNotContains(source, "(*values)")
  Assert.stringNotContains(source, "(*count)")
}

export function testAutomaticMutableBindingsStillUseSharedCaptureStorage(): none {
  result := compile([SourceFile {
    path: "/local-callback.do",
    source:
      "function makeCounter(): (): int {\n" +
      "let count = 0\n" +
      "return (): int => { count += 1\nreturn count }\n" +
      "}",
  }], "/local-callback.do")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "auto count = std::make_shared<int32_t>(0);")
  Assert.stringContains(source, "doof::callback<int32_t()>([count]() -> int32_t")
  Assert.stringContains(source, "(*count) += 1")
}

export function testClassLambdaRetainsCapturedThis(): none {
  result := compile([SourceFile {
    path: "/retained-this.do",
    source:
      "class Receiver {\n" +
      "  value: int = 1\n" +
      "  handler(): (): int => (): int => this.value\n" +
      "}\n",
  }], "/retained-this.do")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "[this, _doof_captured_self = this->shared_from_this()]() -> int32_t")
}

export function testStructLambdaKeepsValueTypeThisCapture(): none {
  result := compile([SourceFile {
    path: "/struct-this.do",
    source:
      "struct Receiver {\n" +
      "  value: int\n" +
      "  read(handler: (): int): int => handler() + value\n" +
      "  apply(): int => read((): int => this.value)\n" +
      "}\n",
  }], "/struct-this.do")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "doof::callback<int32_t()>([this]() -> int32_t")
  Assert.stringNotContains(source, "_doof_captured_self")
}

function destructuringReader(): (): int {
  values := [3]
  return (): int => { [value] := values
    return value }
}

function destructuringNestedCounter(): (): int {
  let count = 0
  [increment] := [(): int => { count += 1
    return count }]
  return increment
}

export function testEmitterGapDestructuringParticipatesInCaptureTraversal(): none {
  read := destructuringReader()
  Assert.equal(read(), 3)
  increment := destructuringNestedCounter()
  Assert.equal(increment(), 1)
  Assert.equal(increment(), 2)
}
