// Shared analysis/checking boundary. This module must not import emission or drivers.
import { IsolationGraph, validateIsolationEffects } from "./checker-isolation"
import { PhaseTimings } from "./phase-timings"
import { AnalysisResult, ModuleInfo, createAnalyzerWithLoader } from "./analyzer"
import { createChecker, ModuleChecker, validateCheckedTypes, validateDeepReadonlyFields } from "./checker"
import { hasErrorDiagnostics } from "./diagnostics"
import { SourceLoader, noSourceLoader } from "./resolver"
import { Diagnostic, SourceFile } from "./semantic"

export class FrontendResult {
  entry: string = ""
  analysis: AnalysisResult
  diagnostics: Diagnostic[]
  sourceFiles: SourceFile[]
  resolutionProbes: string[]
  reusedModules: string[] = []
  additionalEntries: string[] = []
  isolation: IsolationGraph | none = none
}

export function analyzeWithLoader(
  sources: SourceFile[],
  entry: string,
  loader: SourceLoader = noSourceLoader,
  entryMode: string = "executable",
  timings: PhaseTimings = PhaseTimings {},
  serialParsing: bool = false,
  editorMode: bool = false,
  reusableModules: ModuleInfo[] = [],
  additionalEntries: string[] = [],
  previousIsolation: IsolationGraph | none = none,
): FrontendResult {
  analyzer := createAnalyzerWithLoader(sources, loader)
  analyzer.serialParsing = serialParsing
  analyzer.editorMode = editorMode
  analyzer.reusableModules = reusableModules
  analyzer.additionalEntries = additionalEntries
  analysisStart := timings.start()
  analysis := analyzer.analyze(entry, timings)
  timings.finish("compiler.analysis", analysisStart)
  checkingStart := timings.start()
  let diagnostics: Diagnostic[] = []
  for diagnostic of analysis.diagnostics { diagnostics.push(diagnostic) }

  let isolation: IsolationGraph | none = none
  if editorMode || !hasErrorDiagnostics(diagnostics) {
    moduleCheckStart := timings.start()
    checker := createChecker(analysis, entry, entryMode)
    checker.state.editorMode = editorMode
    let checkedPaths: string[] = []
    for path of analyzer.reusedPaths { checkedPaths.push(path) }
    let visitingPaths: string[] = []
    for module of analysis.modules {
      checkModuleDependencies(module.path, analysis, checker, checkedPaths, visitingPaths, diagnostics)
    }
    timings.finish("checking.modules", moduleCheckStart)
    readonlyStart := timings.start()
    for diagnostic of validateDeepReadonlyFields(analysis) { diagnostics.push(diagnostic) }
    timings.finish("checking.deep-readonly", readonlyStart)
    isolationStart := timings.start()
    isolation = validateIsolationEffects(analysis, diagnostics, previousIsolation, analyzer.reusedPaths)
    timings.finish("checking.isolation", isolationStart)
  }

  timings.finish("compiler.checking", checkingStart)
  if editorMode || hasErrorDiagnostics(diagnostics) {
    return FrontendResult { entry, additionalEntries, isolation, analysis, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths, reusedModules: analyzer.reusedPaths }
  }
  validationStart := timings.start()
  for diagnostic of validateCheckedTypes(analysis) { diagnostics.push(diagnostic) }
  timings.finish("compiler.checked-type-validation", validationStart)
  if hasErrorDiagnostics(diagnostics) {
    return FrontendResult { entry, additionalEntries, isolation, analysis, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths, reusedModules: analyzer.reusedPaths }
  }
  return FrontendResult { entry, additionalEntries, isolation, analysis, diagnostics, sourceFiles: analyzer.resolver.sources, resolutionProbes: analyzer.resolver.loadedPaths, reusedModules: analyzer.reusedPaths }
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
  for imported of module!.namespaceImports {
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
