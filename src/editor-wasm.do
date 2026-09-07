import { discoverModuleTests, TestDiscovery } from "./test-discovery"
import { Parser } from "./parser"
import { formatEditorSource } from "./editor-format"
import { analyzeEditor } from "./editor-incremental"
// JSON ABI entry point. All semantic work stays in the shared Doof frontend.
import { analyzeWithLoader } from "./frontend"
import { SourceFile, Diagnostic } from "./semantic"
import { noSourceLoader } from "./resolver"
import { PhaseTimings } from "./phase-timings"

export function diagnostics(sources: SourceFile[], entry: string): Diagnostic[] {
  return analyzeWithLoader(sources, entry, noSourceLoader, "executable", PhaseTimings {}, true).diagnostics
}

import { EditorIndex, EditorResponse } from "./editor-model"
import { createEditorIndex } from "./editor-index"
import { queryEditor } from "./editor-query"

class EditorState { let current: EditorIndex | none = none }
state := EditorState {}

export function analyze(sources: SourceFile[], entry: string, additionalEntries: string[] = []): Diagnostic[] {
  previous := if state.current == none then none else state.current!.frontend
  frontend := analyzeEditor(sources, entry, previous, additionalEntries)
  state.current = createEditorIndex(frontend)
  return frontend.diagnostics
}

export function query(operation: string, module: string, offset: int = 0, text: string = ""): EditorResponse {
  snapshot := state.current else { return EditorResponse { error: "The project has not been analyzed yet." } }
  return queryEditor(snapshot, operation, module, offset, text)
}

export function format(source: string, module: string, indentation: int = 2): EditorResponse => formatEditorSource(source, module, indentation)

export function tests(source: string, module: string, root: string): TestDiscovery {
  parser := Parser { source }
  parsed := catchPanic(=> parser.parse())
  program := parsed else { return TestDiscovery { errors: [parser.errorMessage] } }
  return discoverModuleTests(program, module, root)
}

import { parsePackageSourceInputs, PackageSourceInputs } from "./package-manifest"
export function project(source: string, manifest: string, root: string): Result<PackageSourceInputs, string> => parsePackageSourceInputs(source, manifest, root)

import { autoImportEdits } from "./editor-autoimport"
export function autoImport(module: string, target: string, name: string, source: string): EditorResponse {
  index := state.current else { return EditorResponse { error: "The project has not been analyzed yet." } }
  return autoImportEdits(index, module, target, name, source)
}
