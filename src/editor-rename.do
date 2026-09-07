import { EditorIndex, EditorResponse } from "./editor-model"
import { SourceFile } from "./semantic"
import { analyzeWithLoader } from "./frontend"
import { noSourceLoader } from "./resolver"
import { PhaseTimings } from "./phase-timings"

/** Validate the complete proposed edit against a fresh strict semantic graph. */
export function validateEditorRename(index: EditorIndex, response: EditorResponse): EditorResponse {
  let sources: SourceFile[] = []
  for source of index.frontend.sourceFiles {
    let cursor = 0
    let output = ""
    let changed = false
    while true {
      let next = -1
      for i of 0..<response.edits.length {
        edit := response.edits[i]
        if edit.module != source.path || edit.start < cursor { continue }
        if next < 0 || edit.start < response.edits[next].start { next = i }
      }
      if next < 0 { break }
      edit := response.edits[next]
      if edit.end <= edit.start { return EditorResponse { error: "Cannot validate a zero-width rename target." } }
      output += source.source.substring(cursor, edit.start) + edit.text
      cursor = edit.end
      changed = true
    }
    sources.push(SourceFile { path: source.path, physicalPath: source.physicalPath, source: if changed then output + source.source.substring(cursor, source.source.length) else source.source })
  }
  checked := analyzeWithLoader(sources, index.frontend.entry, noSourceLoader, "executable", PhaseTimings {}, true, true, [], index.frontend.additionalEntries)
  for diagnostic of checked.diagnostics {
    if diagnostic.severity == "error" { return EditorResponse { error: "Rename would break the project: " + diagnostic.message } }
  }
  return response
}

import { EditorItem } from "./editor-model"
import { Parser } from "./parser"
import { ImportDeclaration, ExportList } from "./ast"
import { ModuleResolver } from "./resolver"

export function renameCoverageError(index: EditorIndex, item: EditorItem): string {
  if item.kind == "let" || item.kind == "immutable-binding" || item.kind == "parameter" { return "" }
  resolver := ModuleResolver { sources: index.frontend.sourceFiles, loader: noSourceLoader }
  for source of index.frontend.sourceFiles {
    if source.path.startsWith("/std/") { continue }
    let reached = false
    for module of index.frontend.analysis.modules { if module.path == source.path { reached = true } }
    if reached { continue }
    parser := Parser { source: source.source, editorMode: true }
    parsed := catchPanic(=> parser.parse())
    program := parsed else { return "Workspace analysis is incomplete; cannot prove this rename is safe." }
    for statement of program.statements {
      let specifier = ""
      case statement {
        import_: ImportDeclaration -> { specifier = import_.source }
        list: ExportList -> { specifier = list.source ?? "" }
        _ -> { }
      }
      if specifier != "" && resolver.resolve(source.path, specifier) == item.definitionModule {
        return "Open the dependent module " + source.path + " before renaming; its references have not been checked."
      }
    }
  }
  return ""
}
