import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"
import { discoverInstantiations } from "./checked-instantiations"

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
