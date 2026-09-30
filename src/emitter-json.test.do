import { parseJsonValue } from "std/json"
import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testWiderNoneJsonDecodesUnitAndContainers(): none {
  for type_ of ["none", "none[]", "Map<string, none>", "Tuple<none, int>"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class Data { value: " + type_ + " }\nfunction decode(input: SerialValue): Result<Data, string> => Data.fromSerialValue(input)",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, "throw doof::JsonDecodeError(\"Expected null\")")
    Assert.stringContains(source, "-> std::monostate")
    if type_ == "none" { Assert.stringContains(source, "expected null but got") }
  }
}

export function testCombinationNoneJsonNestedContainerGuards(): none {
  types := ["none[][]", "Map<string, none>[]", "Tuple<none, int>[]"]
  checks := ["if (_array == nullptr)", "if (_object_value == nullptr)", "if (_tuple == nullptr)"]
  for index of 0..<types.length {
    result := compile([SourceFile { path: "/main.do", source:
      "class Data { values: " + types[index] + " }\nfunction decode(input: SerialValue): Result<Data, string> => Data.fromSerialValue(input)",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, checks[index] + " throw doof::JsonDecodeError")
    if index == 2 { Assert.stringContains(source, "if (_tuple->size() != 2)") }
  }
}

export function testReadonlyEmissionJsonUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction decode(value: SerialValue): Result<Item, string> => Item.fromSerialValue(value)" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}

export function testIntegralJsonFieldsValidateExactFit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Data { small: byte\ncount: int\ntotal: long\nratio: double }\nfunction decode(input: SerialValue): Result<Data, string> => Data.fromSerialValue(input)",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "doof::serial_fits_byte_lenient(")
  Assert.stringContains(source, "doof::serial_fits_int(")
  Assert.stringContains(source, "doof::serial_fits_long(")
  Assert.stringContains(source, "expected int but got")
  Assert.stringContains(source, "expected number but got")
}

class JsonExactBox { count: int }
class JsonExactWide { total: long }

function jsonExactCase(text: string): string {
  value := parseJsonValue(text) else { return "parse error" }
  return case value { n: int -> "int ${n}", l: long -> "long ${l}", d: double -> "double ${d}", _ -> "other" }
}
function jsonExactAs(text: string): string {
  value := parseJsonValue(text) else { return "parse error" }
  n := value as int else { return "not int" }
  return "int ${n}"
}
function jsonExactDecode(text: string): string {
  value := parseJsonValue(text) else { return "parse error" }
  box := JsonExactBox.fromSerialValue(value) else error { return error }
  return "count ${box.count}"
}
function jsonExactDecodeWide(text: string): string {
  value := parseJsonValue(text) else { return "parse error" }
  box := JsonExactWide.fromSerialValue(value) else error { return error }
  return "total ${box.total}"
}

export function testJsonIntegralNarrowingNeverTruncatesOrWraps(): none {
  Assert.equal(jsonExactCase("3"), "int 3")
  Assert.equal(jsonExactCase("3.0"), "int 3")
  Assert.equal(jsonExactCase("1.5"), "double 1.5")
  Assert.equal(jsonExactCase("5000000000"), "long 5000000000")
  Assert.equal(jsonExactAs("3.0"), "int 3")
  Assert.equal(jsonExactAs("1.5"), "not int")
  Assert.equal(jsonExactAs("5000000000"), "not int")
  Assert.equal(jsonExactDecode("{\"count\": 3.0}"), "count 3")
  Assert.equal(jsonExactDecode("{\"count\": 1.5}"), "Field \"count\" expected int but got number")
  Assert.equal(jsonExactDecode("{\"count\": 5000000000}"), "Field \"count\" expected int but got number")
  Assert.equal(jsonExactDecodeWide("{\"total\": 5000000000}"), "total 5000000000")
}

export function testLiteralFieldDecodingValidatesEnumsAndOtherLiterals(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "enum Kind { Circle, Square }\nenum Wire { Small = \"small\" }\n" +
    "class Shape { kind: Kind.Circle\nsize: Wire.Small\nversion: -2\nenabled: true\nradius: double }\n" +
    "function decode(input: SerialValue): Result<Shape, string> => Shape.fromSerialValue(input)",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "Field \\\"kind\\\" must be Kind.Circle")
  Assert.stringContains(source, "Field \\\"size\\\" must be Wire.Small")
  Assert.stringContains(source, "Field \\\"version\\\" must be -2")
  Assert.stringContains(source, "Field \\\"enabled\\\" must be true")
}

export function testUnionAliasDecoderDispatchesOnDiscriminator(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Circle { kind: \"circle\"\nradius: double }\nclass Rect { kind: \"rect\"\nwidth: double }\ntype Shape = Circle | Rect\n" +
    "function decode(input: SerialValue): Result<Shape, string> => Shape.fromSerialValue(input)",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  module := result.emission!.modules[0]
  Assert.stringContains(module.header, "doof::Result<Shape, std::string> Shape_fromSerialValue(const doof::SerialValue& _json, bool _lenient);")
  Assert.stringContains(module.source, "if (_discriminator == \"circle\")")
  Assert.stringContains(module.source, "Circle::fromSerialValue(_json, _lenient)")
  Assert.stringContains(module.source, "Shape_fromSerialValue(input, false)")
  unused := compile([SourceFile { path: "/main.do", source:
    "class Circle { kind: \"circle\"\nradius: double }\nclass Rect { kind: \"rect\"\nwidth: double }\ntype Shape = Circle | Rect",
  }], "/main.do")
  Assert.stringNotContains(unused.emission!.modules[0].header, "Shape_fromSerialValue")
}
