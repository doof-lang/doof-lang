// Small persistent cache for exact, whole-graph frontend hits.
//
// This deliberately stores no AST or checker objects. Any changed input is a
// cache miss and runs the ordinary compiler pipeline.

import { formatJsonValue, parseJsonValue } from "std/json"

export readonly FRONTEND_CACHE_VERSION = 2
// Bump when checker or lowering semantics change without changing the JSON
// shape. Cache correctness must never depend on a stale compiler decision.
export readonly FRONTEND_SEMANTIC_ABI = 10

export class FrontendSourceProbe {
  logicalPath: string
  sourceHash: string = ""
  missing: bool = false
}

export class FrontendFileInput {
  path: string
  sourceHash: string
}

export class FrontendModuleOutput {
  modulePath: string
  headerName: string
  sourceName: string
  fingerprint: string = ""
}

export class FrontendCacheState {
  version: int = 2
  configurationFingerprint: string
  probes: FrontendSourceProbe[] = []
  fileInputs: FrontendFileInput[] = []
  modules: FrontendModuleOutput[] = []
}

export function parseFrontendCacheState(source: string): FrontendCacheState | none {
  value := parseJsonValue(source) else { return none }
  state := FrontendCacheState.fromJsonValue(value, true) else { return none }
  if state.version != FRONTEND_CACHE_VERSION { return none }
  return state
}

export function renderFrontendCacheState(state: FrontendCacheState): string {
  return formatJsonValue(state.toJsonObject()) + "\n"
}
