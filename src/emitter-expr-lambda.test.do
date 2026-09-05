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

export function testCapturedStructMethodsUseOwnedMutableClosureCopies(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "struct Roll { value: int\nread(): int => value }\n" +
    "function make<T>(value: T): (): T => (): T => value\n" +
    "function main(): int { roll := Roll { value: 7 }\n" +
    "outer := (): int => { inner := (): int => roll.read()\nreturn inner() }\n" +
    "copy := make<Roll>(roll)\nreturn outer() + copy().read() }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "[roll = roll]() mutable -> int32_t")
  Assert.stringContains(source, "[value = value]() mutable -> Roll")
  Assert.stringNotContains(source, "[roll]() ->")
}

struct CapturedRoll {
  let value: int
  copyRolls(): int[] => [value]
  advance(): int { value += 1
    return value }
}

function retainedRollReader(): (): int {
  roll := CapturedRoll { value: 7 }
  outer := (): (): int => (): int => roll.copyRolls()[0]
  return outer()
}

export function testCapturedStructMethodsRunInEscapingNestedCallbacks(): none {
  read := retainedRollReader()
  Assert.equal(read(), 7)
  Assert.equal(read(), 7)
  roll := CapturedRoll { value: 10 }
  first := (): int => roll.advance()
  second := (): int => roll.advance()
  Assert.equal(first(), 11)
  Assert.equal(first(), 12)
  Assert.equal(second(), 11)
  Assert.equal(roll.value, 10)
  let shared = CapturedRoll { value: 20 }
  advance := (): int => shared.advance()
  Assert.equal(advance(), 21)
  Assert.equal(shared.value, 21)
  shared = CapturedRoll { value: 30 }
  Assert.equal(advance(), 31)
}

export function testCapturedStructBindingsStillRejectReassignment(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "struct Roll { value: int }\nfunction main(): none { roll := Roll { value: 1 }\n" +
    "callback := (): none => { roll = Roll { value: 2 } } }",
  }], "/main.do")
  let rejected = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("immutable") { rejected = true }
  }
  Assert.isTrue(rejected)
}
