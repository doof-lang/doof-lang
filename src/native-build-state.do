// Persistent, versioned state for the native incremental build executor.
// Filesystem signatures are captured by the native driver; this module keeps
// JSON encoding and dependency-file parsing pure and independently testable.

import { formatJsonValue, parseJsonValue } from "std/json"

export readonly NATIVE_BUILD_STATE_VERSION = 1

export class NativeInputSignature {
  path: string
  let signature: string
  contentHash: bool = true
}

export class NativeTaskState {
  id: string
  fingerprint: string
  outputPath: string
  outputSize: long
  outputModifiedNanos: long
  inputs: NativeInputSignature[] = []
}

export class NativeBuildState {
  version: int = 1
  tasks: NativeTaskState[] = []
  managedOutputs: string[] = []
}

export function parseNativeBuildState(source: string): NativeBuildState | none {
  value := parseJsonValue(source) else { return none }
  state := NativeBuildState.fromJsonValue(value, true) else { return none }
  if state.version != NATIVE_BUILD_STATE_VERSION { return none }
  return state
}

export function renderNativeBuildState(state: NativeBuildState): string {
  return formatJsonValue(state.toJsonObject()) + "\n"
}

export function findNativeTaskState(state: NativeBuildState, id: string): NativeTaskState | none {
  for task of state.tasks { if task.id == id { return task } }
  return none
}

/** Parses the portable subset of Make dependency files emitted by GCC/Clang. */
export function parseMakeDependencies(source: string): string[] {
  flattened := source.replaceAll("\\\r\n", " ").replaceAll("\\\n", " ")
  let colon = -1
  let escaped = false
  for index of 0..<flattened.length {
    char := flattened[index]
    if !escaped && char == ':' { colon = index; break }
    if char == '\\' && !escaped { escaped = true } else { escaped = false }
  }
  if colon < 0 { return [] }
  let result: string[] = []
  let current = ""
  escaped = false
  for index of colon + 1..<flattened.length {
    char := flattened[index]
    if escaped {
      current = current + string(char)
      escaped = false
      continue
    }
    if char == '\\' {
      escaped = true
      continue
    }
    if char == ' ' || char == '\t' || char == '\r' || char == '\n' {
      if current != "" { appendUnique(result, current); current = "" }
      continue
    }
    current = current + string(char)
  }
  if escaped { current = current + "\\" }
  if current != "" { appendUnique(result, current) }
  return result
}

function appendUnique(values: string[], value: string): none {
  for existing of values { if existing == value { return } }
  values.push(value)
}
