import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

class QuarkWeakItem { value: int }
class QuarkWeakOther { value: int }
class QuarkWeakObserver { weak item: QuarkWeakItem }
class QuarkWeakOptional { weak item: QuarkWeakItem | none = none }
class QuarkWeakUnion { weak item: QuarkWeakItem | QuarkWeakOther }
class QuarkWeakOptionalUnion { weak item: QuarkWeakItem | QuarkWeakOther | none = none }
class QuarkWeakArray { weak items: int[] }
class QuarkWeakTracked {
  releases: int[]
  destructor { releases[0] += 1 }
}
class QuarkWeakTrackedObserver { weak item: QuarkWeakTracked }

function quarkExpiredObserver(): QuarkWeakObserver => QuarkWeakObserver { item: QuarkWeakItem { value: 7 } }
function quarkWeakRead(observer: QuarkWeakObserver): int => case observer.item {
  found: Success -> found.value.value
  _: Failure -> -1
}
function quarkWeakOptionalRead(observer: QuarkWeakOptional): int => case observer.item {
  found: Success -> { item := found.value as QuarkWeakItem else { yield 0 }
    yield item.value }
  _: Failure -> -1
}
function quarkExpiredOptional(): QuarkWeakOptional => QuarkWeakOptional { item: QuarkWeakItem { value: 9 } }

export function testQuarkWeakCaseRuntimeAliveExpiredAndAbsent(): none {
  item := QuarkWeakItem { value: 7 }
  Assert.equal(quarkWeakRead(QuarkWeakObserver { item }), 7)
  Assert.equal(quarkWeakRead(quarkExpiredObserver()), -1)
  Assert.equal(quarkWeakOptionalRead(QuarkWeakOptional {}), 0)
  Assert.equal(quarkWeakOptionalRead(QuarkWeakOptional { item }), 7)
  Assert.equal(quarkWeakOptionalRead(quarkExpiredOptional()), -1)
  array := [2, 3]
  observer := QuarkWeakArray { items: array }
  case observer.items {
    found: Success -> { Assert.equal(found.value.length, 2) }
    _: Failure -> { Assert.isTrue(false) }
  }
  other := QuarkWeakOther { value: 8 }
  union := QuarkWeakUnion { item: other }
  case union.item {
    found: Success -> { value := found.value as QuarkWeakOther else { panic("Wrong weak target") }
      Assert.equal(value.value, 8) }
    _: Failure -> { Assert.isTrue(false) }
  }
}

export function testQuarkWeakCaseRetainsReferentThroughArm(): none {
  releases := [0]
  let item: QuarkWeakTracked | none = QuarkWeakTracked { releases }
  observer := QuarkWeakTrackedObserver { item: item! }
  case observer.item {
    found: Success -> {
      item = none
      Assert.equal(releases[0], 0)
      Assert.equal(found.value.releases[0], 0)
    }
    _: Failure -> { Assert.isTrue(false) }
  }
  Assert.equal(releases[0], 1)
}

function quarkOptionalUnionRead(observer: QuarkWeakOptionalUnion): int => case observer.item {
  found: Success -> case found.value {
    item: QuarkWeakItem -> item.value
    other: QuarkWeakOther -> other.value
    _: none -> 0
  }
  _: Failure -> -1
}
function quarkExpiredOptionalUnion(): QuarkWeakOptionalUnion => QuarkWeakOptionalUnion { item: QuarkWeakOther { value: 8 } }

export function testQuarkWeakCaseNullableUnion(): none {
  item := QuarkWeakItem { value: 7 }
  other := QuarkWeakOther { value: 8 }
  Assert.equal(quarkOptionalUnionRead(QuarkWeakOptionalUnion {}), 0)
  Assert.equal(quarkOptionalUnionRead(QuarkWeakOptionalUnion { item }), 7)
  Assert.equal(quarkOptionalUnionRead(QuarkWeakOptionalUnion { item: other }), 8)
  Assert.equal(quarkOptionalUnionRead(quarkExpiredOptionalUnion()), -1)
}

class QuarkNoneValueItem { value: int }
function quarkNoneValueOptional(email: string | none): string => case email {
  none -> "missing",
  e: string -> e
}
function quarkNoneValuePointer(item: QuarkNoneValueItem | none): int => case item {
  none -> -1,
  found: QuarkNoneValueItem -> found.value
}
function quarkNoneValueVariant(value: int | string | none): string => case value {
  none -> "none",
  n: int -> "int " + string(n),
  s: string -> "string " + s
}
function quarkNoneValueStatement(email: string | none): int {
  case email {
    none -> { return 0 }
    "a" -> { return 1 }
    _ -> { return 2 }
  }
}

export function testNoneValuePatternRuntimeAcrossCarriers(): none {
  Assert.equal(quarkNoneValueOptional(none), "missing")
  Assert.equal(quarkNoneValueOptional("a@b.c"), "a@b.c")
  Assert.equal(quarkNoneValuePointer(none), -1)
  Assert.equal(quarkNoneValuePointer(QuarkNoneValueItem { value: 4 }), 4)
  Assert.equal(quarkNoneValueVariant(none), "none")
  Assert.equal(quarkNoneValueVariant(3), "int 3")
  Assert.equal(quarkNoneValueVariant("x"), "string x")
  Assert.equal(quarkNoneValueStatement(none), 0)
  Assert.equal(quarkNoneValueStatement("a"), 1)
  Assert.equal(quarkNoneValueStatement("b"), 2)
}

export function testNoneValuePatternTestsCarrierAbsence(): none {
  cases := [
    ["string", "doof::is_null(_case_subject)"],
    ["Item", "doof::is_null(_case_subject)"],
    ["int | string", "std::holds_alternative<std::monostate>(_case_subject)"],
  ]
  for entry of cases {
    result := compile([SourceFile { path: "/main.do", source:
      "class Item {}\n" +
      "function inspect(value: " + entry[0] + " | none): int => case value { none -> 1, _ -> 2 }\n" +
      "function run(value: " + entry[0] + " | none): int { case value { none -> { return 1 }\n_ -> { return 2 } } }",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, "if (" + entry[1] + ")")
    Assert.stringNotContains(source, "== std::monostate{}")
  }
}

function quarkValueVariant(value: int | string | none): string => case value {
  1 -> "one",
  "x" -> "x",
  none -> "none",
  _ -> "other"
}

export function testValuePatternOnVariantComparesMatchingAlternative(): none {
  Assert.equal(quarkValueVariant(1), "one")
  Assert.equal(quarkValueVariant(2), "other")
  Assert.equal(quarkValueVariant("x"), "x")
  Assert.equal(quarkValueVariant("y"), "other")
  Assert.equal(quarkValueVariant(none), "none")
  result := compile([SourceFile { path: "/main.do", source:
    "function inspect(value: int | string): int => case value { 1 -> 1, _ -> 2 }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "(std::holds_alternative<int32_t>(_case_subject) && std::get<int32_t>(_case_subject) == 1)")
}

export function testNoneValuePatternOnJsonTestsNull(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function inspect(value: SerialValue): int => case value { none -> 1, _ -> 2 }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "doof::serial_is_null(_case_subject)")
}

export function testNoneCarrierJsonPatternBindsUnit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function take(value: none): none {}\n" +
    "function main(): none { let value: SerialValue = none\n" +
    "case value { n: none -> { take(n) }\n_ -> {} } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "const auto n = std::monostate{};")
  Assert.stringContains(source, "take(n);")
  Assert.stringNotContains(source, "const auto n = nullptr;")
}

export function testNoneCarrierNaturalPatternTestsAbsence(): none {
  for type_ of ["int", "Item", "int[]"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class Item {}\nfunction take(value: none): none {}\n" +
      "function inspect(value: " + type_ + " | none): int {\n" +
      "case value { n: none -> { take(n)\nreturn 1 }\n_ -> { return 2 } } }",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, "if (doof::is_null(_case_subject))")
    Assert.stringContains(source, "const auto n = std::monostate{};")
    Assert.stringNotContains(source, "if (!doof::is_null(_case_subject))")
  }
}

export function testReadonlyEmissionPatternsUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction inspect(value: Item | Other): int { case value { item: Item -> { return item.value }\n_ -> { return 0 } } }" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "std::shared_ptr<::mapped::types::Item>")
  Assert.stringNotContains(output, "app_vendor_types_")
}

export function testSerialIntegralPatternsRequireExactFit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function inspect(value: SerialValue): int => case value { b: byte -> int(b), n: int -> n, l: long -> 2, d: double -> 3, _ -> 4 }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "doof::serial_fits_byte(_case_subject)")
  Assert.stringContains(source, "doof::serial_fits_int(_case_subject)")
  Assert.stringContains(source, "doof::serial_fits_long(_case_subject)")
  Assert.stringContains(source, "doof::serial_is_number(_case_subject)")
}

export function testResultArmPatternsUseTheCheckedArmTypes(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function a(r: Result<int, string>): int => case r { s: Success -> s.value, f: Failure<string> -> f.error.length }\n" +
    "function b(x: Success<int> | none): int => case x { s: Success -> s.value, _ -> 0 }\n" +
    "function c(r: Result<int, string>): int => case r { all: Result<int, string> -> all.unwrapOr(0) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "std::holds_alternative<doof::Success<int32_t>>(")
  Assert.stringContains(source, "std::holds_alternative<doof::Failure<std::string>>(")
  Assert.stringNotContains(source, "holds_alternative<doof::Result")
}
