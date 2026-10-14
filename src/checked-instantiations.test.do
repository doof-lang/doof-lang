import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"
import { discoverInstantiations } from "./checked-instantiations"
import { containsTypeParameter } from "./checker-types"

export function testCallbackGenericSignaturesStayDistinct(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "function keep<T>(value: T): T => value\n" +
    "function main(): none {\n" +
    "a: ((x: int): int) | none := none\n" +
    "b: ((x: string): int) | none := none\n" +
    "c: ((x: int): string) | none := none\n" +
    "aa := keep(a)\nbb := keep(b)\ncc := keep(c)\nagain := keep(a)\n}" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  catalog := discoverInstantiations(analysis)
  Assert.equal(catalog.functions.length, 3)
  Assert.isTrue(catalog.functions[0].key != catalog.functions[1].key)
  Assert.isTrue(catalog.functions[0].key != catalog.functions[2].key)
}

export function testInstantiationDiscoveryClosesTransitiveCallsAndDeduplicates(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "function leaf<T>(value: T): T => value\n" +
    "function outer<T>(value: T): T => leaf<T>(value)\n" +
    "function main(): int => outer<int>(1) + outer<int>(2)" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  checked := discoverInstantiations(analysis)
  catalog := checked
  Assert.equal(catalog.overflow, false)
  Assert.equal(catalog.entries.length, 2)
  Assert.equal(catalog.functions[0].declaration.name, "outer")
  Assert.equal(catalog.functions[1].declaration.name, "leaf")
  Assert.stringContains(catalog.functions[1].key, "::leaf::[int]")
}

export function testInstantiationDiscoveryEmptyForNongenericProgram(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function main(): int => 1" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  catalog := discoverInstantiations(analysis)
  Assert.equal(catalog.entries.length, 0)
  Assert.equal(catalog.overflowTrace.length, 0)
}

export function testInstantiationDiscoveryBoundsExpandingDiscovery(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "function grow<T>(value: T): int => grow<T[]>([value])\nfunction main(): int => grow<int>(1)" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  catalog := discoverInstantiations(analysis)
  Assert.equal(catalog.overflow, true)
  Assert.isTrue(catalog.overflowTrace.length <= 12)
  Assert.stringContains(catalog.overflowTrace[0], "::function::grow::[array:")
}

export function testInterfaceJsonDemandReachesImplementationsByDirection(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "interface Shape { area(): int }\n" +
    "class Square implements Shape { kind: \"square\"\nside: int\narea(): int => side }\n" +
    "class Disc implements Shape { kind: \"disc\"\nradius: int\narea(): int => radius }\n" +
    "class Scene { shapes: Shape[] }\n" +
    "function encode(shape: Shape): SerialObject => shape.toSerialObject()\n" +
    "function decode(json: SerialValue): Result<Scene, string> => Scene.fromSerialValue(json)" }]).analyze("/main.do")
  diagnostics := createChecker(analysis, "/main.do").check("/main.do").diagnostics
  for diagnostic of diagnostics { println(diagnostic.message) }
  Assert.equal(diagnostics.length, 0)
  catalog := discoverInstantiations(analysis)
  Assert.equal(joined(catalog.jsonSerializationKeys), "/main.do::Shape,/main.do::Square,/main.do::Disc")
  Assert.equal(joined(catalog.jsonDeserializationKeys), "/main.do::Scene,/main.do::Shape,/main.do::Square,/main.do::Disc")
}

export function testImpliedInterfaceEncodingNamesTheBlockingImplementation(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "interface Pet { speak(): string }\n" +
    "class Dog implements Pet { name: string\nspeak(): string => name }\n" +
    "class Robot implements Pet { onSpeak: (): string\nspeak(): string => onSpeak() }\n" +
    "function encode<T: Pet>(value: T): SerialObject => value.toSerialObject()\n" +
    "function main(): none { pet: Pet := Dog { name: \"Rex\" }\nencode<Pet>(pet) }" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  catalog := discoverInstantiations(analysis)
  Assert.equal(catalog.jsonErrors.length, 1)
  Assert.equal(catalog.jsonErrors[0].message, "Type \"Pet\" does not support automatic JSON serialization (implementing class \"Robot\" does not support it), required by 'toSerialObject' on type parameter \"T\"")
  // The error points at the member access inside the generic body.
  Assert.equal(catalog.jsonErrors[0].span.start.line, 6)
  Assert.equal(catalog.jsonErrors[0].span.end.line, 6)
  Assert.isTrue(catalog.jsonErrors[0].span.end.offset > catalog.jsonErrors[0].span.start.offset)
}

function joined(values: string[]): string {
  let result = ""
  for value of values { result = if result == "" then value else result + "," + value }
  return result
}

export function testMetadataTypeArgumentsAreSpecializedPerCaller(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source:
    "class Point { x: int = 0 }\nclass Line { length: int = 0 }\n" +
    "function keep<V>(value: V): V => value\n" +
    "function describe<T: Reflectable>(): string => keep(T.metadata).name\n" +
    "function main(): none { a := describe<Point>()\nb := describe<Line>() }" }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  catalog := discoverInstantiations(analysis)
  let keys: string[] = []
  for function_ of catalog.functions {
    if function_.declaration.name == "keep" { keys.push(function_.key) }
    // No instantiation may still mention the caller's type parameter.
    for argument of function_.substitution.arguments {
      if containsTypeParameter(argument) { panic("unspecialized instantiation " + function_.key) }
    }
  }
  Assert.equal(keys.length, 2)
  Assert.stringContains(joined(keys), "Point")
  Assert.stringContains(joined(keys), "Line")
}
