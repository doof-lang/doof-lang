import { Assert } from "std/assert"
import { hasErrorDiagnostics } from "./diagnostics"
import { Diagnostic, SemanticLocation, SemanticSpan } from "./semantic"

function diagnostic(severity: string): Diagnostic {
  location := SemanticLocation { line: 1, column: 1, offset: 0 }
  return Diagnostic {
    severity,
    message: "message",
    span: SemanticSpan { start: location, end: location },
    module: "/main.do",
  }
}

export function testEmptyAndWarningOnlyDiagnosticsHaveNoErrors(): none {
  Assert.equal(hasErrorDiagnostics([]), false)
  Assert.equal(hasErrorDiagnostics([diagnostic("warning")]), false)
}

export function testFindsAnErrorAmongWarnings(): none {
  Assert.equal(hasErrorDiagnostics([
    diagnostic("warning"),
    diagnostic("error"),
    diagnostic("warning"),
  ]), true)
}
