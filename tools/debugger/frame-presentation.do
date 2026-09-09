import { DebugRow } from "./model"
import { textField, intField, objectField } from "./protocol"
import { exists } from "std/fs"

export function frameName(name: string): string {
  // Drop argument signatures before namespaces (arguments themselves contain ::).
  signature := name.split("(")[0]
  parts := signature.split("::")
  short := parts[parts.length-1]
  return if short == "doof_main" then "main" else short
}

export function frameLabel(row: DebugRow): string {
  name := frameName(textField(row.data, "name"))
  line := intField(row.data, "line")
  return name + if line > 0 then " · " + string(line) else ""
}

export function hasDoofSource(row: DebugRow): bool {
  path := textField(objectField(row.data, "source"), "path")
  return path.endsWith(".do") && intField(row.data, "line") > 0 && exists(path)
}

export function sourceFrames(rows: DebugRow[]): DebugRow[] {
  let visible: DebugRow[] = []
  for row of rows { if hasDoofSource(row) { visible.push(row) } }
  return visible
}
