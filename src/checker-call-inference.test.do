import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

function messages(source: string): string[] {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  let found: string[] = []
  for diagnostic of result.diagnostics { found.push(diagnostic.message) }
  return found
}

function inMain(body: string): string[] => messages("function main(): none {\nitems := [1, 2]\n" + body + "\n}")

export function testResultTypeSourcesAgree(): none {
  // Explicit type arguments, declared lambda returns, and contextual result
  // types each fix the callback result; the body converts to it.
  for body of [
    "r := items.map<double>(=> it + 3)\ncheck: double[] := r",
    "r := items.map((it): double => it + 3)\ncheck: double[] := r",
    "r: double[] := items.map(=> it + 3)",
    "r: double[] := items.map<double>((it): double => it)",
    "r: double[] := items.map((it): double => it)",
    "r := items.map(=> it + 3)\ncheck: int[] := r",
  ] {
    found := inMain(body)
    for message of found { println(body + ": " + message) }
    Assert.equal(found.length, 0)
  }
}

export function testExplicitResultClashesAreReported(): none {
  Assert.equal(only(inMain("r := items.map<string>((it): double => it)")), "Argument 1 returns double; expected a callback returning string")
  Assert.equal(only(inMain("r: string[] := items.map((it): double => it)")), "Cannot assign double[] to string[]")
  Assert.equal(only(inMain("r := items.map<string>(=> it + 3)")), "Cannot return int from lambda returning string")
  Assert.equal(only(inMain("r: string[] := items.map(=> it + 3)")), "Cannot return int from lambda returning string")
}

export function testArgumentValuesOutrankContextAndLambdaBodies(): none {
  // T comes from the argument, so the result widens on assignment rather
  // than re-instantiating the call.
  Assert.equal(messages("function identity<T>(value: T): T => value\nfunction main(): none { x: double := identity(3) }").length, 0)
  Assert.equal(messages("function apply<T, U>(value: T, f: (it: T): U): U => f(value)\nfunction main(): none { x: double := apply(3, => it + 1) }").length, 0)
}

export function testLambdasSeeEarlierInferenceWithoutDuplicateDiagnostics(): none {
  found := messages("function apply<T, U>(value: T, f: (it: T): U): U => f(value)\nfunction main(): none { x := apply(3, => it + \"a\") }")
  Assert.equal(only(found), "Operator '+' is not defined for int and string")
}

export function testInconsistentEvidenceStillFails(): none {
  found := messages("function pair<T>(a: T, b: T): T => a\nfunction main(): none { x := pair(1, \"a\") }")
  Assert.stringContains(found[0], "Cannot infer consistent type arguments")
}

export function testTrailingLambdaCannotDetermineGenericResult(): none {
  found := inMain("items.map() { it * 2 }")
  Assert.equal(found.length, 1)
  Assert.stringContains(found[0], "Trailing lambdas require a callback returning none")
}

function only(found: string[]): string {
  for message of found { println(message) }
  Assert.equal(found.length, 1)
  return found[0]
}
