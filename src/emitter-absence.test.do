import { Assert } from "std/assert"
import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceFile } from "./semantic"

readonly PRELUDE = "class Box { value: int }\n" +
  "function nested(): Result<Box | none, string> => Success(none)\n" +
  "function outer(): Result<Box, string> | none => none\n"

function emitted(source: string): string {
  compilation := compile([SourceFile { path: "/main.do", source: PRELUDE + source }], "/main.do")
  for diagnostic of compilation.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(compilation.diagnostics), false)
  graph := compilation.emission else { panic("source graph was not emitted") }
  return graph.modules[0].source
}

export function testForcedPanicsAtEachLayerInOrder(): none {
  source := emitted("function f(): Box => nested()!")
  Assert.stringContains(source, "if (doof::is_failure(_forced_value)) doof::panic_at(")
  Assert.stringContains(source, "if (doof::is_null(doof::success_value(_forced_value))) doof::panic_at(")
  Assert.stringContains(source, "\"! failed: value is none\"")
}

export function testOptionalReturnsNoneAtEachLayer(): none {
  source := emitted("function f(): Box | none => outer()?")
  Assert.stringContains(source, "if (doof::is_null(_optional_value)) return")
  Assert.stringContains(source, "if (doof::is_failure(std::get<doof::Result<")
}

export function testDeclarationElseTestsLayersWithShortCircuit(): none {
  source := emitted("function f(): int { box := nested() else error { return 0 }\nreturn box.value }")
  Assert.stringContains(source, "if (doof::is_failure(_binding_value_")
  Assert.stringContains(source, ") || doof::is_null(doof::success_value(_binding_value_")
  // The error is the Failure's error, or none for a none success value.
  Assert.stringContains(source, "const auto error = [&]() -> ")
  Assert.stringContains(source, "return std::nullopt; }()")
}

export function testForcedNullableReferenceChecksForNone(): none {
  // A class reference has no checked unwrap of its own, so '!' and '!.' test it.
  source := emitted("function f(box: Box | none): int => box!.value\nfunction g(box: Box | none): Box => box!")
  Assert.stringContains(source, "auto _forced_value = box; if (doof::is_null(_forced_value)) doof::panic_at(")
  Assert.stringNotContains(source, "doof::unwrap_optional(box)->value")
}

export function testForceAccessRequiresAnAbsentReceiver(): none {
  compilation := compile([SourceFile { path: "/main.do", source: PRELUDE + "function f(box: Box): int => box!.value" }], "/main.do")
  Assert.equal(compilation.diagnostics.length, 1)
  Assert.equal(compilation.diagnostics[0].message, "Force access '!.' requires a nullable or Result receiver, got Box")
}
