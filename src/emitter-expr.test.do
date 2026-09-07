import { compileWithLoader } from "./compiler"
import { noSourceLoader } from "./resolver"
import { ModuleNamespaceMapping } from "./emitter-names"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testDiscardedCallsSkipOnlyUnusedCarrierConversion(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction number(): int => 7\n" +
    "function main(): none { effect()\nnumber()\nvalue := effect() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "    effect();")
  Assert.stringContains(source, "    number();")
  Assert.stringContains(source, "value = (static_cast<void>(effect()), std::monostate{});")
  Assert.stringNotContains(source, "    (static_cast<void>(effect()), std::monostate{});")
}

export function testGenericNoneLiteralWithoutContextUsesUnitCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function unitTuple(): Tuple<none, int> => (none, 7)\n" +
    "function main(): none { unitTuple() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "std::make_tuple(std::monostate{}, 7)")
  Assert.stringNotContains(source, "std::make_tuple(nullptr, 7)")
}

export function testEmitterGapConditionalDispatchPreservesExpectedUnionOrder(): none {
  result := compile([SourceFile {
    path: "/conditional.do",
    source: "function choose(flag: bool): int | string => if flag then \"first\" else 2",
  }], "/conditional.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "[&]() -> std::variant<int32_t, std::string>")
  Assert.stringNotContains(source, "[&]() -> std::variant<std::string, int32_t>")
}

export function testNoneCarrierNamedValuesUseContextualAbsence(): none {
  types := ["int | none", "Item | none", "Value | none", "int[] | none", "int | string | none", "JsonValue", "none"]
  carriers := ["std::nullopt", "nullptr", "std::nullopt", "nullptr", "std::monostate{}", "doof::json_value(nullptr)", "value"]
  for index of 0..<types.length {
    result := compile([SourceFile { path: "/main.do", source:
      "class Item {}\nstruct Value { number: int }\n" +
      "function take(value: " + types[index] + "): none {}\n" +
      "function main(): none { value := none\ntake(value) }",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    expected := if index == 6 then "take(value)" else "take((static_cast<void>(value), " + carriers[index] + "))"
    Assert.stringContains(source, expected)
  }
}

export function testNoneCarrierReturnPreservesEvaluation(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none { println(7) }\n" +
    "function absent(): int | none { return effect() }\n" +
    "function main(): none { absent() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "return (static_cast<void>(effect()), std::nullopt);")
}

export function testNoneCarrierGenericAndAssignmentBoundaries(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Item {}\n" +
    "function absent<T>(sample: T): T | none { value := none\nreturn value }\n" +
    "function main(): none { value := none\nlet target: int | none = 7\ntarget = value\nabsent(Item {}) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "return (static_cast<void>(value), nullptr);")
  Assert.stringContains(source, "target = (static_cast<void>(value), std::nullopt)")
}

export function testNoneCarrierRejectsNonNullableDestination(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function absent(): int { value := none\nreturn value }",
  }], "/main.do")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "Cannot return none from function returning int")
}

export function testNoneCarrierCallArgumentMaterializesUnit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none { println(7) }\n" +
    "function take(value: none): none {}\n" +
    "function main(): none { take(effect()) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "take((static_cast<void>(effect()), std::monostate{}))")
}

export function testWiderNoneUnitValuesNeedNoExpectedType(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction pair(): Tuple<none, int> => (effect(), 1)\nfunction main(): none { pair() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "std::make_tuple((static_cast<void>(effect()), std::monostate{}), 1)")
}

export function testEmissionCleanupThisRetainsClassAndStructCarriers(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class C { self(): C => this }\nstruct S { self(): S => this }\n" +
    "import class Native from \"native.hpp\" { self(): Native => this }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "C::self() {\n    return this->shared_from_this();")
  Assert.stringContains(source, "S::self() {\n    return *this;")
  Assert.stringContains(source, "Native::self() {\n    return this->shared_from_this();")
}

export function testReadonlyEmissionCallerUsesSnapshotDiagnosticPath(): none {
  source := "function debug(source: SourceLocation = @caller): string => source.fileName\nfunction caller(): string => debug()"
  result := compileWithLoader([SourceFile { path: "/vendor/tests/caller.do", source }], "/vendor/tests/caller.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source, "std::string(\"tests/caller\")")
  Assert.stringNotContains(result.emission!.modules[0].source, "std::string(\"vendor/tests/caller\")")
}
