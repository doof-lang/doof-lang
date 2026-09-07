// Diagnostic fixes share export discovery and import editing with completion.
import { EditorIndex, EditorResponse } from "./editor-model"
import { editorSource } from "./editor-index"
import { autoImportEdits } from "./editor-autoimport"

export function missingImportFix(index: EditorIndex, module: string, message: string): EditorResponse {
  prefix := "Unknown identifier '"
  if !message.startsWith(prefix) || !message.endsWith("'") { return EditorResponse {} }
  name := message.substring(prefix.length, message.length - 1)
  let candidate = ""
  for source of index.frontend.sourceFiles {
    if source.path == module { continue }
    for exported of index.exportCandidates {
      if exported.module != source.path || exported.label != name { continue }
      if candidate != "" && candidate != source.path { return EditorResponse {} }
      candidate = source.path
    }
  }
  if candidate == "" { return EditorResponse {} }
  return autoImportEdits(index, module, candidate, name, editorSource(index, module))
}
