// Conservative module invalidation. Ownership of reusable checked modules is
// transferred to the next snapshot; callers must not query the old graph while
// analysis runs. Closed-world class/interface changes force a clean analysis.
import { FrontendResult, analyzeWithLoader } from "./frontend"
import { ModuleInfo } from "./analyzer"
import { SourceFile } from "./semantic"
import { Lexer, TokenType } from "./lexer"
import { noSourceLoader } from "./resolver"
import { PhaseTimings } from "./phase-timings"

function contains(paths: string[], path: string): bool {
  for value of paths { if value == path { return true } }
  return false
}

function requiresWholeGraph(source: string): bool {
  tokens := Lexer { source }.tokenize()
  for token of tokens {
    if token.kind == TokenType.Class || token.kind == TokenType.Struct || token.kind == TokenType.Interface || token.kind == TokenType.Mock { return true }
  }
  return false
}

export function reusableEditorModules(previous: FrontendResult, sources: SourceFile[]): ModuleInfo[] {
  if previous.diagnostics.length > 0 || previous.sourceFiles.length != sources.length { return [] }
  let dirty: string[] = []
  for old of previous.sourceFiles {
    let found = false
    for source of sources {
      if source.path != old.path { continue }
      found = true
      if source.source != old.source {
        if requiresWholeGraph(old.source) || requiresWholeGraph(source.source) || importsFingerprint(old.source) != importsFingerprint(source.source) { return [] }
        dirty.push(source.path)
      }
      break
    }
    if !found { return [] }
  }
  let changed = true
  while changed {
    changed = false
    for module of previous.analysis.modules {
      if contains(dirty, module.path) { continue }
      let depends = false
      for imported of module.imports { if contains(dirty, imported.sourceModule) { depends = true } }
      for imported of module.namespaceImports { if contains(dirty, imported.sourceModule) { depends = true } }
      for path of module.reExports { if contains(dirty, path) { depends = true } }
      if depends { dirty.push(module.path); changed = true }
    }
  }
  // Mock directives can replace dependency edges without changing import statements.
  // A changed alias/signature can affect a dependent nominal declaration and
  // its structural conformance even in modules that do not import that class.
  for source of sources { if contains(dirty, source.path) && requiresWholeGraph(source.source) { return [] } }
  let reusable: ModuleInfo[] = []
  for module of previous.analysis.modules { if !contains(dirty, module.path) { reusable.push(module) } }
  return reusable
}

export function analyzeEditor(sources: SourceFile[], entry: string, previous: FrontendResult | none = none, additionalEntries: string[] = []): FrontendResult {
  reusable: ModuleInfo[] := if previous == none || previous!.entry != entry || !sameEntries(previous!.additionalEntries, additionalEntries) then [] else reusableEditorModules(previous!, sources)
  // Keep the snapshot source list independent of subsequent caller edits.
  return analyzeWithLoader(sources.cloneMutable(), entry, noSourceLoader, "executable", PhaseTimings {}, true, true, reusable, additionalEntries)
}

function importsFingerprint(source: string): string {
  tokens := Lexer { source }.tokenize()
  let result = ""
  for index of 0..<tokens.length - 1 {
    if tokens[index].kind == TokenType.From {
      next := tokens[index + 1]
      result += source.substring(next.offset, next.offset + next.length) + "\n"
    }
  }
  return result
}

function sameEntries(left: string[], right: string[]): bool {
  if left.length != right.length { return false }
  for i of 0..<left.length { if left[i] != right[i] { return false } }
  return true
}
