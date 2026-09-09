// Presentation of Doof's string[] carrier using LLDB's existing synthetic
// vector/string children. Never evaluate C++ expressions in the target.
import { DebugRow } from "./model"
import { textField } from "./protocol"

export function isStringArray(row: DebugRow): bool {
  typeName := textField(row.data, "type").replaceAll("std::__1::", "std::")
    .replaceAll("std::__cxx11::", "std::").replaceAll(" ", "").replaceAll("const", "")
  prefix := "std::shared_ptr<std::vector<"
  if !typeName.startsWith(prefix) { return false }
  element := typeName.substring(prefix.length, typeName.length)
  return element.startsWith("std::string>") || element.startsWith("std::string,") ||
    element.startsWith("std::basic_string<char>") || element.startsWith("std::basic_string<char,")
}

export function stringArrayStorage(row: DebugRow): DebugRow | none {
  if !isStringArray(row) { return none }
  for child of row.children {
    if textField(child.data, "name") == "pointer" { return child }
  }
  return none
}

export function collectionChildren(row: DebugRow, showInternals: bool): DebugRow[] {
  if showInternals || !isStringArray(row) { return row.children }
  storage := stringArrayStorage(row) else { return row.children }
  return storage.children
}

export function variableLabel(row: DebugRow, showInternals: bool): string {
  if showInternals || !isStringArray(row) { return row.label }
  let label = textField(row.data, "name") + " : string[]"
  summary := textField(row.data, "value")
  parts := summary.split("size=")
  if parts.length > 1 {
    let length = ""
    for i of 0..<parts[1].length {
      ch := parts[1][i]
      if ch < '0' || ch > '9' { break }
      length += string(ch)
    }
    if length != "" { label += " · " + length + if length == "1" then " item" else " items" }
  }
  return label
}
