import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"

export function testRestrictedJoinOptionalWidening(): none {
  for expression of ["if flag then a else b", "if flag then b else a", "case flag { true -> a, false -> b }"] {
    source := "function run(flag: bool, a: int | none, b: long): long | none { x := " + expression + "\nreturn x }"
    analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
    Assert.equal(analysis.diagnostics.length, 0)
    result := createChecker(analysis, "/main.do").check("/main.do")
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.equal(result.diagnostics.length, 0)
  }
}

export function testRestrictedJoinDiagnosticAndNever(): none {
  source := "function stop(flag: bool): never => if flag then panic(\"left\") else panic(\"right\")\nfunction run(flag: bool): none { x := if flag then none else if flag then 1 else \"text\" }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  result := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "only T | none unions are inferred")
}
