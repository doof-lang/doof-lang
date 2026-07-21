// Shared diagnostic severity queries.

import { Diagnostic } from "./semantic"

export function hasErrorDiagnostics(diagnostics: Diagnostic[]): bool {
  for diagnostic of diagnostics {
    if diagnostic.severity == "error" { return true }
  }
  return false
}
