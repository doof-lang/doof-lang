import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitNoneLiteral } from "./emitter-expr-literals"
import { ClassType, JsonValueResolvedType, NoneType, PrimitiveType, ResolvedType, Symbol, UnionResolvedType, WeakResolvedType } from "./semantic"

export function testGenericNoneLiteralUsesSpecializedCarrier(): none {
  types := ["Item", "int", "Value", "Item | none", "int | none", "Item | Value"]
  values := ["Item { value: 7 }", "7", "Value { value: 7 }", "Item { value: 7 }", "7", "Item { value: 7 }"]
  carriers := ["nullptr", "std::nullopt", "std::nullopt", "nullptr", "std::nullopt", "std::monostate{}"]
  for index of 0..<types.length {
    result := compile([SourceFile { path: "/main.do", source:
      "class Item { value: int }\nstruct Value { value: int }\n" +
      "class Rows<T> { rows: T[]\n" +
      "rowAt(index: int): T | none {\n" +
      "if index < 0 || index >= rows.length { return none }\n" +
      "return rows[index]\n} }\n" +
      "function absent<T>(value: T): T | none { return none }\n" +
      "function main(): none {\n" +
      "rows := Rows<" + types[index] + "> { rows: [" + values[index] + "] }\n" +
      "rows.rowAt(-1)\nrows.rowAt(0)\nrows.rowAt(1)\n" +
      "absent<" + types[index] + ">(" + values[index] + ")\n}",
    }], "/main.do")
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    let source = ""
    for module of result.emission!.modules { source = source + module.source }
    Assert.stringContains(source, "return " + carriers[index] + ";")
    if index < 5 { Assert.stringNotContains(source, "return std::monostate{};") }
  }
}

export function testGenericNoneLiteralWeakAndUnitCarriers(): none {
  context := EmitContext {}
  item := ClassType { name: "Item", symbol: Symbol { kind: "class", name: "Item", module: "", exported: false } }
  weakItem := WeakResolvedType { inner: item }
  optionalWeak := WeakResolvedType { inner: UnionResolvedType { types: [item, NoneType {}] } }
  let types: ResolvedType[] = [NoneType {}, JsonValueResolvedType {}, weakItem, optionalWeak,
    UnionResolvedType { types: [weakItem, NoneType {}] },
    UnionResolvedType { types: [UnionResolvedType { types: [PrimitiveType { name: "int" }, NoneType {}] }, NoneType {}] }]
  values := ["std::monostate{}", "doof::json_value(nullptr)", "std::weak_ptr<Item>{}",
    "std::optional<std::weak_ptr<Item>>{}", "std::weak_ptr<Item>{}", "std::nullopt"]
  for index of 0..<types.length { Assert.equal(emitNoneLiteral(types[index], context), values[index]) }
}

export function testGenericNoneLiteralCollectionElementsUseCheckedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function optionalArray(): (int | none)[] => [none, 7]\n" +
    "function unitArray(): none[] => [none]\n" +
    "function main(): none { optionalArray()\nunitArray() }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "std::vector<std::optional<int32_t>>{std::nullopt, 7}")
  Assert.stringContains(source, "std::vector<std::monostate>{std::monostate{}}")
}

export function testGenericNoneLiteralResultPayloadUsesSpecializedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Item {}\n" +
    "function load<T>(value: T): Result<T, string> { return Success { value: value } }\n" +
    "function fail<E>(error: E): Result<int, E> { return Failure { error: error } }\n" +
    "function main(): none { try? load(Item {})\ntry? fail(Item {}) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "doof::Success<std::shared_ptr<Item>>{ value }")
  Assert.stringContains(source, "doof::Failure<std::shared_ptr<Item>>{ error }")
  Assert.stringNotContains(source, "doof::Success<T>")
  Assert.stringNotContains(source, "doof::Failure<E>")
}
