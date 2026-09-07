import { discoverInstantiations } from "./checked-instantiations"
// Self-hosted compiler orchestration.
//
// The compiler deliberately checks every analyzed module before emission.
// Emission consumes decorated ASTs, so allowing an unchecked dependency into
// the project emitter would turn a front-end omission into a C++ failure.

import { PhaseTimings } from "./phase-timings"
import { AnalysisResult, ModuleInfo, createAnalyzerWithLoader } from "./analyzer"
import { emitModuleGraph, ModuleEmissionCacheKey, ModuleGraphEmission } from "./emitter-module"
import { nameInstantiations } from "./emitter-monomorphize"
import { emitWasmSupport, WasmEmission } from "./emitter-wasm"
import { ModuleNamespaceMapping, prepareModuleNames } from "./emitter-names"
import { createChecker, ModuleChecker, validateCheckedTypes, validateDeepReadonlyFields, validateIsolationEffects } from "./checker"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceLoader, noSourceLoader } from "./resolver"
import { CheckResult, Diagnostic, SemanticLocation, SemanticSpan, SourceFile } from "./semantic"

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
  analyzer := createAnalyzerWithLoader(sources, loader)
  analysisStart := timings.start()
  analysis := analyzer.analyze(entry, timings)
  timings.finish("compiler.analysis", analysisStart)
  checkingStart := timings.start()
  let diagnostics: Diagnostic[] = []
  for diagnostic of analysis.diagnostics { diagnostics.push(diagnostic) }

  if !hasErrorDiagnostics(diagnostics) {
    moduleCheckStart := timings.start()
    checker := createChecker(analysis, entry, entryMode)
    let checkedPaths: string[] = []
    let visitingPaths: string[] = []
    for module of analysis.modules {
      checkModuleDependencies(module.path, analysis, checker, checkedPaths, visitingPaths, diagnostics)
    }
    timings.finish("checking.modules", moduleCheckStart)
    readonlyStart := timings.start()
    for diagnostic of validateDeepReadonlyFields(analysis) { diagnostics.push(diagnostic) }
    timings.finish("checking.deep-readonly", readonlyStart)
    isolationStart := timings.start()
    for diagnostic of validateIsolationEffects(analysis) { diagnostics.push(diagnostic) }
    timings.finish("checking.isolation", isolationStart)
  }

  timings.finish("compiler.checking", checkingStart)
  if hasErrorDiagnostics(diagnostics) {
    return Compilation { emission: none, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths }
  }
  validationStart := timings.start()
  for diagnostic of validateCheckedTypes(analysis) { diagnostics.push(diagnostic) }
  timings.finish("compiler.checked-type-validation", validationStart)
  if hasErrorDiagnostics(diagnostics) {
    return Compilation { emission: none, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths }
  }
  if !emit { return Compilation { emission: none, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths } }
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
    return Compilation { emission: none, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths }
  }
  let wasmEmission: WasmEmission | none = none
  if entryMode == "wasm" {
    wasmStart := timings.start()
    wasm := emitWasmSupport(analysis, entry, instantiations, names) else message {
      timings.finish("compiler.wasm", wasmStart)
      zero := SemanticLocation { line: 0, column: 0, offset: 0 }
      diagnostics.push(Diagnostic { severity: "error", message, span: SemanticSpan { start: zero, end: zero }, module: entry })
      return Compilation { emission: none, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths }
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
  return Compilation { emission, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths }
}

// Analyzer discovery order is driven by import syntax, not by a fixed source
// list.  Check dependencies first so imported class declarations are fully
// decorated before callers construct or inspect them.
function checkModuleDependencies(
  path: string,
  analysis: AnalysisResult,
  checker: ModuleChecker,
  checkedPaths: string[],
  visitingPaths: string[],
  diagnostics: Diagnostic[],
): none {
  if containsPath(checkedPaths, path) || containsPath(visitingPaths, path) { return }
  module := findAnalysisModule(analysis, path)
  if module == none { return }
  visitingPaths.push(path)
  for imported of module!.imports {
    checkModuleDependencies(imported.sourceModule, analysis, checker, checkedPaths, visitingPaths, diagnostics)
  }
  for reExport of module!.reExports {
    checkModuleDependencies(reExport, analysis, checker, checkedPaths, visitingPaths, diagnostics)
  }
  let ignored = try! visitingPaths.pop()
  checked := checker.check(path)
  for diagnostic of checked.diagnostics { diagnostics.push(diagnostic) }
  checkedPaths.push(path)
}

function containsPath(paths: string[], path: string): bool {
  for existing of paths { if existing == path { return true } }
  return false
}

function findAnalysisModule(result: AnalysisResult, path: string): ModuleInfo | none {
  for module of result.modules { if module.path == path { return module } }
  return none
}
