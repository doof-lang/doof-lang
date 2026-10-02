import { Assert } from "std/assert"
import { compile } from "./compiler"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceFile } from "./semantic"

function emitted(source: string): string {
  compilation := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of compilation.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(compilation.diagnostics), false)
  graph := compilation.emission else { panic("source graph was not emitted") }
  return graph.modules[0].source
}

export function testOptionalMemberShortCircuitsBeforeDereference(): none {
  source := emitted("class A { x: int\nread(): int => x }\nfunction field(a: A | none): int | none => a?.x\nfunction call(a: A | none): int | none => a?.read()")
  Assert.stringContains(source, "if (doof::is_null(_optional_source_")
  Assert.stringContains(source, "doof::unwrap_optional(_optional_source_")
  Assert.stringNotContains(source, "a->x")
  Assert.stringNotContains(source, "a->read()")
}

export function testOptionalNoneCallIsAStatementLambda(): none {
  source := emitted("class A { run(): none { } }\nfunction go(a: A | none): none { a?.run() }")
  Assert.stringContains(source, "[&]() -> void {")
  Assert.stringContains(source, "return; auto&&")
}

export function testOptionalIndexUsesCheckedElementAccess(): none {
  source := emitted("function first(items: int[] | none): int | none => items?[0]")
  Assert.stringContains(source, "doof::array_at(_optional_receiver_")
  Assert.stringContains(source, "if (doof::is_null(_optional_source_")
}

export function testOptionalChainOverResultCollapsesTheReceiverAndKeepsTheMemberFailure(): none {
  source := emitted(
    "enum LookupError { Missing }\nenum ProfileError { Private }\nclass Profile { bio: string }\n" +
    "class User { name: string\nprofile(): Result<Profile, ProfileError> => Success(Profile { bio: name }) }\n" +
    "function findUser(): Result<User, LookupError> => Success(User { name: \"ada\" })\n" +
    "function profile(): Result<Profile | none, ProfileError> => findUser()?.profile()",
  )
  // The receiver lowers through postfix '?', so a Failure becomes none.
  Assert.stringContains(source, "if (doof::is_failure(_optional_value)) return")
  Assert.stringContains(source, "if (doof::is_null(_optional_source_")
  // An absent receiver is a none success value; the member keeps its Failure.
  Assert.stringContains(source, "return doof::Success<")
  Assert.stringContains(source, "if (doof::is_failure(_optional_result_")
  Assert.stringNotContains(source, "doof::variant_promote<")
}
