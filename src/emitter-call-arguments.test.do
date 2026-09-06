import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testEmissionCleanupContextualCallbackArgumentsAcrossDispatch(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class A { callback: (value: int | none): int }\nclass B { callback: (value: int | none): int }\n" +
    "function direct(callback: (value: int | none): int): int { absent := none\nreturn callback(absent) }\n" +
    "function dispatched(value: A | B): int { absent := none\nreturn value.callback(absent) }\n" +
    "function named(callback: (a: int, b: int): int): int => callback{b: 3, a: 2}",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "callback.call((static_cast<void>(absent), std::nullopt))")
  Assert.stringContains(source, "_obj->callback.call((static_cast<void>(absent), std::nullopt))")
  Assert.stringContains(source, "callback.call(2, 3)")
}

export function testEmissionCleanupGenericDefaultsAndBuiltinArguments(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function read<T>(value: T, rest: T[] = []): int => rest.length\n" +
    "function main(): int { println(3)\nreturn read(3) + read{value: 3} + int(4L) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "read__int(3, std::make_shared<std::vector<int32_t>>")
  Assert.stringContains(source, "doof::println(3)")
}

export function testCheckerConsolidationGenericOwnerDefaults(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class C<T> { size(values: T[] = []): int => values.length }\n" +
    "function direct(value: C<int>): int => value.size()\nfunction indirect(value: weak C<int>): int => value!.size()",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "->size(std::make_shared<std::vector<int32_t>>")
  Assert.stringNotContains(source, "std::vector<T>")
}
