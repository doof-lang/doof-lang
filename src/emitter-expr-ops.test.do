import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testGenericNoneLiteralNarrowingUsesSpecializedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Item {}\n" +
    "function present<T>(value: T | none): bool { item := value as T else { return false }\nreturn true }\n" +
    "function main(): none { present<Item>(Item {})\npresent<int>(7)\npresent<Item | none>(none) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "if (_as_value)")
  Assert.stringContains(source, "if (_as_value.has_value())")
  Assert.stringNotContains(source, "doof::variant_is<")
  Assert.stringNotContains(source, "doof::variant_narrow<")
}

export function testGenericNoneLiteralTryUsesSpecializedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Item {}\n" +
    "function optional<T>(value: T): T | none {\n" +
    "result: Result<T, string> := Success { value: value }\nreturn try? result }\n" +
    "function main(): none { optional(7)\noptional(Item {}) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "if (doof::is_failure(_try_value)) return std::nullopt;")
  Assert.stringContains(source, "if (doof::is_failure(_try_value)) return nullptr;")
  Assert.stringNotContains(source, "std::variant<std::monostate, T>")
}

export function testInterfaceBoundSpecializedStructAndVariantFields(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "interface Counter { let value: int }\nclass C { let value: int }\nstruct S { let value: int }\n" +
    "function bump<T: Counter>(counter: T): int { counter.value += 1\nreturn counter.value }\n" +
    "function main(): int { c: Counter := C(1)\nreturn bump(c) + bump(S(2)) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "counter.value")
  Assert.stringContains(source, "-> decltype(auto) { return (_obj->value);")
}

export function testCheckerReviewNumericSpecializedLowering(): none {
  result := compile([SourceFile { path: "/main.do", source: "function shift<T: int | long>(a: T): T => a >>> 1\nfunction square<T: float | double>(a: T): T { let x = a\nx **= a\nreturn x }\nfunction main(): none { shift(-1)\nshift(-1L)\nsquare(2.0f)\nsquare(2.0) }" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "std::make_unsigned_t<int32_t>")
  Assert.stringContains(source, "std::make_unsigned_t<int64_t>")
  Assert.stringContains(source, "std::pow(_assignment_target, _assignment_value)")
}

export function testWiderNoneNamedEqualityAndUnitUnwrap(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): Result<none, string> => Success {}\nfunction take(value: none): none {}\n" +
    "function main(): none { absent := none\nlet value: int | none = none\nprintln(value == absent)\nprintln(absent != value)\ntake(try! effect())\ntake(effect()!) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "return doof::is_null(_none_left);")
  Assert.stringContains(source, "return !doof::is_null(_none_right);")
  Assert.stringContains(source, "take([&]() -> std::monostate")
  Assert.stringNotContains(source, "take([&]() -> void")
}
