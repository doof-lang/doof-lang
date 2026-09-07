import { Scope } from "./semantic"
import { typeName } from "./checker-types"
import { FunctionType } from "./semantic"
import { Token } from "./lexer"
// Serializable editor query results use compiler byte offsets. Hosts own URI
// mapping and conversion to their negotiated position encoding.
import { Binding, ResolvedType } from "./semantic"
import { FrontendResult } from "./frontend"

export class EditorItem {
  importModule: string = ""
  parameters: string[] = []
  label: string
  detail: string = ""
  insertText: string = ""
  documentation: string = ""
  kind: string = "variable"
  module: string
  start: int
  end: int
  identity: string = ""
  renameIdentity: string = ""
  definitionModule: string = ""
  definitionStart: int = 0
  definitionEnd: int = 0
  declaration: bool = false
  shorthand: bool = false
}

export class EditorEdit {
  module: string
  start: int
  end: int
  text: string
}

export class EditorResponse {
  activeParameter: int = 0
  items: EditorItem[] = []
  edits: EditorEdit[] = []
  error: string = ""
}

export class IndexedBinding {
  item: EditorItem
  binding: Binding | none = none
  type_: ResolvedType | none = none
}

export class EditorTokens {
  module: string
  source: string
  tokens: Token[]
}

export class EditorIndex {
  exportCandidates: EditorItem[] = []
  let workspaceIndexed: bool = false
  workspaceDeclarations: EditorItem[] = []
  visitedScopes: Scope[] = []
  bindingItems: Map<string, EditorItem> = {}
  indexedBindings: Set<string> = []
  tokens: EditorTokens[] = []
  frontend: FrontendResult
  bindings: IndexedBinding[] = []
  occurrences: EditorItem[] = []
}

export function editorTypeName(type_: ResolvedType): string {
  case type_ {
    function_: FunctionType -> {
      let signature = "("
      for index of 0..<function_.params.length {
        if index > 0 { signature += ", " }
        parameter := function_.params[index]
        signature += parameter.name + ": " + editorTypeName(parameter.type_)
        if parameter.hasDefault { signature += " = …" }
      }
      return signature + "): " + editorTypeName(function_.returnType)
    }
    _ -> { return typeName(type_) }
  }
}
