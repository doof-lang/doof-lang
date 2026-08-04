// Versioned state for executable resources copied beside native programs.
// The driver owns filesystem traversal; this module keeps the persisted shape
// and exact metadata comparison independently testable.

import { formatJsonValue, parseJsonValue } from "std/json"

export readonly RESOURCE_STATE_VERSION = 1

export class MaterializedResource {
  sourcePath: string
  outputPath: string
  sourceSize: long
  sourceModifiedNanos: long
  outputSize: long
  outputModifiedNanos: long
}

export class ResourceState {
  version: int = 1
  files: MaterializedResource[] = []
}

export function parseResourceState(source: string): ResourceState | none {
  value := parseJsonValue(source) else { return none }
  state := ResourceState.fromJsonValue(value, true) else { return none }
  if state.version != RESOURCE_STATE_VERSION { return none }
  return state
}

export function renderResourceState(state: ResourceState): string {
  return formatJsonValue(state.toJsonObject()) + "\n"
}

export function findMaterializedResource(
  state: ResourceState,
  sourcePath: string,
  outputPath: string,
): MaterializedResource | none {
  for file of state.files {
    if file.sourcePath == sourcePath && file.outputPath == outputPath { return file }
  }
  return none
}

export function materializedResourceIsCurrent(
  previous: MaterializedResource | none,
  sourceSize: long,
  sourceModifiedNanos: long,
  outputSize: long,
  outputModifiedNanos: long,
): bool {
  if previous == none { return false }
  return previous!.sourceSize == sourceSize && previous!.sourceModifiedNanos == sourceModifiedNanos &&
    previous!.outputSize == outputSize && previous!.outputModifiedNanos == outputModifiedNanos
}
