import { discoverInstantiations } from "./checked-instantiations"
// Self-hosted compiler orchestration.
//
// The compiler deliberately checks every analyzed module before emission.
// Emission consumes decorated ASTs, so allowing an unchecked dependency into
// the project emitter would turn a front-end omission into a C++ failure.

import { PhaseTimings } from "./phase-timings"
import { analyzeWithLoader } from "./frontend"
import { emitModuleGraph, ModuleEmissionCacheKey, ModuleGraphEmission } from "./emitter-module"
import { nameInstantiations } from "./emitter-monomorphize"
import { emitWasmSupport, WasmEmission } from "./emitter-wasm"
import { ModuleNamespaceMapping, prepareModuleNames } from "./emitter-names"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceLoader, noSourceLoader } from "./resolver"
import { Diagnostic, SemanticLocation, SemanticSpan, SourceFile } from "./semantic"

export class Compilation {
  emission: ModuleGraphEmission | none
  diagnostics: Diagnostic[]
  sourceFiles: SourceFile[] = []
  resolutionProbes: string[] = []
}

export function compile(sources: SourceFile[], entry: string, coverage: bool = false): Compilation {
  return compileInternal(sources, entry, noSourceLoader, [], "executable", coverage)
}

export function compileWithLoader(
  sources: SourceFile[],
  entry: string,
  loader: SourceLoader,
  namespaceMappings: ModuleNamespaceMapping[] = [],
  entryMode: string = "executable",
  coverage: bool = false,
  reusableModules: ModuleEmissionCacheKey[] = [],
  emissionConfigurationFingerprint: string = "",
  physicalSourcePaths: bool = false,
  timings: PhaseTimings = PhaseTimings {},
): Compilation {
  return compileInternal(
    sources, entry, loader, namespaceMappings, entryMode, coverage, true,
    reusableModules, emissionConfigurationFingerprint, physicalSourcePaths, timings,
  )
}

/** Checks a source graph without running lowering or C++ emission. */
export function checkWithLoader(
  sources: SourceFile[],
  entry: string,
  loader: SourceLoader,
  entryMode: string = "executable",
  timings: PhaseTimings = PhaseTimings {},
): Compilation {
  return compileInternal(sources, entry, loader, [], entryMode, false, false, [], "", false, timings)
}

function compileInternal(
  sources: SourceFile[],
  entry: string,
  loader: SourceLoader,
  namespaceMappings: ModuleNamespaceMapping[],
  entryMode: string = "executable",
  coverage: bool = false,
  emit: bool = true,
  reusableModules: ModuleEmissionCacheKey[] = [],
  emissionConfigurationFingerprint: string = "",
  physicalSourcePaths: bool = false,
  timings: PhaseTimings = PhaseTimings {},
): Compilation {
  frontend := analyzeWithLoader(sources, entry, loader, entryMode, timings)
  analysis := frontend.analysis
  diagnostics := frontend.diagnostics
  if hasErrorDiagnostics(diagnostics) || !emit {
    return Compilation { emission: none, diagnostics, sourceFiles: frontend.sourceFiles, resolutionProbes: frontend.resolutionProbes }
  }
  paths: string[] := []
  for module of analysis.modules { paths.push(module.path) }
  names := prepareModuleNames(namespaceMappings, paths)
  instantiationStart := timings.start()
  discoveryStart := timings.start()
  checkedInstantiations := discoverInstantiations(analysis)
  timings.finish("compiler.instantiation-discovery", discoveryStart)
  namingStart := timings.start()
  instantiations := nameInstantiations(checkedInstantiations, names)
  timings.finish("compiler.instantiation-naming", namingStart)
  timings.finish("compiler.instantiations", instantiationStart)
  if instantiations.overflow {
    let trace = ""
    for item of instantiations.overflowTrace { trace = trace + (if trace == "" then "" else " -> ") + item }
    zero := SemanticLocation { line: 0, column: 0, offset: 0 }
    diagnostics.push(Diagnostic {
      severity: "error",
      message: "Generic instantiation did not converge after 256 concrete instantiations" + (if trace == "" then "" else ": " + trace),
      span: SemanticSpan { start: zero, end: zero },
      module: entry,
    })
    return Compilation { emission: none, diagnostics, sourceFiles: frontend.sourceFiles, resolutionProbes: frontend.resolutionProbes }
  }
  let wasmEmission: WasmEmission | none = none
  if entryMode == "wasm" {
    wasmStart := timings.start()
    wasm := emitWasmSupport(analysis, entry, instantiations, names) else message {
      timings.finish("compiler.wasm", wasmStart)
      zero := SemanticLocation { line: 0, column: 0, offset: 0 }
      diagnostics.push(Diagnostic { severity: "error", message, span: SemanticSpan { start: zero, end: zero }, module: entry })
      return Compilation { emission: none, diagnostics, sourceFiles: frontend.sourceFiles, resolutionProbes: frontend.resolutionProbes }
    }
    timings.finish("compiler.wasm", wasmStart)
    wasmEmission = wasm
  }
  emissionStart := timings.start()
  emission := emitModuleGraph(
    analysis, entry, instantiations, entryMode, coverage,
    reusableModules, emissionConfigurationFingerprint, physicalSourcePaths, timings, names,
  )
  timings.finish("compiler.emission", emissionStart)
  if wasmEmission != none {
    emission.wasmSupportSource = wasmEmission!.source
    emission.wasmExportNames = wasmEmission!.exportNames
  }
  return Compilation { emission, diagnostics, sourceFiles: frontend.sourceFiles, resolutionProbes: frontend.resolutionProbes }
}
