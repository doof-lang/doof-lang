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

export function testNoneCarrierJsonPatternBindsUnit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function take(value: none): none {}\n" +
    "function main(): none { let value: JsonValue = none\n" +
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
