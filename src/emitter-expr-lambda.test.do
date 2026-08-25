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
