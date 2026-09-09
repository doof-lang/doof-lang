import { DebugRow } from "./model"
import { textField } from "./protocol"

// Filter only known compiler temporaries, never all underscore-prefixed names.
// Source identifiers win over naming conventions. Raw data stays in the session.
export function isInternalVariable(name: string, identifiers: Set<string>): bool {
  if identifiers.has(name) { return false }
  if ["_case_subject", "_item", "_nullable_value", "_as_value", "_obj", "_weak_item", "_weak_locked", "_doof_captured_self"].contains(name) { return true }
  for prefix of ["_iterable_", "_discard_", "_discard_parameter_", "_destructure_", "_binding_value_", "_try_value_", "_result_unwrap_", "_coalesce_", "_construct_spread_", "_map_has_", "_weak_storage_", "_weak_value_", "_with_discard_"] {
    if !name.startsWith(prefix) { continue }
    suffix := name.substring(prefix.length, name.length)
    if suffix.length == 0 { continue }
    let generated = true
    for i of 0..<suffix.length { ch := suffix[i]; if (ch < '0' || ch > '9') && ch != '_' { generated = false } }
    if generated { return true }
  }
  return false
}

export function visibleVariables(rows: DebugRow[], identifiers: Set<string>, showInternals: bool, globals: bool = false): DebugRow[] {
  if showInternals { return rows }
  let visible: DebugRow[] = []
  for row of rows {
    name := textField(row.data, "name")
    if !isInternalVariable(name, identifiers) && (!globals || !isSystemGlobal(name)) { visible.push(row) }
  }
  return visible
}

export function visibleScopes(rows: DebugRow[], showInternals: bool, identifiers: Set<string> = []): DebugRow[] {
  if showInternals { return rows }
  let visible: DebugRow[] = []
  for row of rows {
    if isGlobalScope(row) && row.loaded && visibleVariables(row.children, identifiers, false, true).length == 0 { continue }
    if textField(row.data, "presentationHint") != "registers" && textField(row.data, "name") != "Registers" { visible.push(row) }
  }
  return visible
}

export function isGlobalScope(row: DebugRow): bool {
  return row.key.startsWith("scope/") && row.key.split("/").length == 2 &&
    (textField(row.data, "presentationHint") == "globals" || textField(row.data, "name") == "Globals")
}

export function isSystemGlobal(name: string): bool {
  qualified := if name.startsWith("::") then name.substring(2, name.length) else name
  // Match namespace boundaries, not variable types or similarly named projects.
  for prefix of ["std::", "doof::", "__gnu_cxx::", "__cxxabiv1::"] {
    if qualified.startsWith(prefix) { return true }
  }
  return false
}
