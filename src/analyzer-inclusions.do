// Declaration field inclusion: expands `...Source` class and struct members
// into copies of the source's instance fields.
//
// Expansion runs graph-wide once named types are decorated, before any checker
// pass reads `fields`. Every later phase consumes the expanded field list. The
// expansion is idempotent so editor analyses may reuse unchanged syntax trees.

import { Diagnostic, SemanticLocation, SemanticSpan } from "./semantic"
import { ClassDeclaration, ClassField, FieldInclusion, IncludedField } from "./ast"
import type { SourceSpan } from "./ast"
import type { ModuleInfo } from "./analyzer"

/** A field name already present in the expanded declaration. */
class ClaimedField {
  name: string
  // The including source's name, or "" for a hand-written field.
  source: string
  line: int
}

class InclusionExpansion {
  modules: ModuleInfo[]
  let expanded: ClassDeclaration[] = []
  let active: ClassDeclaration[] = []
  let diagnostics: Diagnostic[] = []

  expand(class_: ClassDeclaration, modulePath: string): none {
    if expanded.some(=> it == class_) { return }
    handWritten := class_.fields.filter(=> it.includedFrom == none)
    if class_.inclusions.length == 0 {
      class_.fields = handWritten
      expanded.push(class_)
      return
    }
    active.push(class_)
    let claimed: ClaimedField[] = []
    for field of handWritten {
      for name of field.names { claimed.push(ClaimedField { name, source: "", line: field.span.start.line }) }
    }
    let fields: ClassField[] = []
    let next = 0
    for inclusion of class_.inclusions {
      while next < inclusion.position && next < handWritten.length {
        fields.push(handWritten[next])
        next += 1
      }
      // Reused syntax may carry a source decided by an earlier analysis.
      inclusion.resolvedSource = none
      source := admissibleSource(inclusion, modulePath) else { continue }
      if active.some(=> it == source) {
        reportCycle(inclusion, source, modulePath)
        continue
      }
      expand(source, source.resolvedSymbol?.module ?? modulePath)
      if private_ := source.fields.find(=> !it.static_ && it.private_) {
        name := if private_.names.length > 0 then private_.names[0] else ""
        error(modulePath, "Cannot include \"${source.name}\": it declares private field \"${name}\"", inclusion.span)
        continue
      }
      inclusion.resolvedSource = source
      for field of source.fields {
        if field.static_ { continue }
        if copied := copyField(field, source, inclusion, claimed, modulePath) { fields.push(copied) }
      }
    }
    while next < handWritten.length {
      fields.push(handWritten[next])
      next += 1
    }
    class_.fields = fields
    ignored := active.pop()!
    expanded.push(class_)
  }

  private admissibleSource(inclusion: FieldInclusion, modulePath: string): ClassDeclaration | none {
    named := inclusion.type_
    // An unresolved name was already reported by named-type decoration.
    symbol := named.resolvedSymbol else { return none }
    if symbol.kind == "type-alias" {
      error(modulePath, "Cannot include \"${named.name}\": include the class or struct directly rather than a type alias", named.span)
      return none
    }
    if symbol.kind != "class" && symbol.kind != "struct" {
      error(modulePath, "Cannot include \"${named.name}\": only class and struct fields can be included", named.span)
      return none
    }
    source := findClass(symbol.module, if symbol.originalName == "" then symbol.name else symbol.originalName) else { return none }
    if source.native_ {
      error(modulePath, "Cannot include \"${named.name}\": an extern class has no Doof-owned fields", named.span)
      return none
    }
    return source
  }

  private findClass(modulePath: string, name: string): ClassDeclaration | none {
    module := modules.find(=> it.path == modulePath) else { return none }
    for statement of module.program.statements {
      if class_ := statement as ClassDeclaration && class_.name == name { return class_ }
    }
    return none
  }

  private copyField(field: ClassField, source: ClassDeclaration, inclusion: FieldInclusion, claimed: ClaimedField[], modulePath: string): ClassField | none {
    let names: string[] = []
    let descriptions: string[] = []
    for index of 0..<field.names.length {
      name := field.names[index]
      if existing := claimed.find(=> it.name == name) {
        error(modulePath, conflictMessage(name, source.name, existing), inclusion.span)
        continue
      }
      claimed.push(ClaimedField { name, source: source.name, line: inclusion.span.start.line })
      names.push(name)
      if index < field.descriptions.length { descriptions.push(field.descriptions[index]) }
    }
    if names.length == 0 { return none }
    return ClassField {
      kind: "class-field",
      names,
      descriptions,
      type_: none,
      defaultValue: field.defaultValue,
      static_: false,
      const_: field.const_,
      let_: field.let_,
      readonly_: field.readonly_,
      weak_: field.weak_,
      private_: false,
      includedFrom: IncludedField { inclusion, source, sourceField: field },
      span: inclusion.span,
    }
  }

  private reportCycle(inclusion: FieldInclusion, source: ClassDeclaration, modulePath: string): none {
    let start = 0
    for index of 0..<active.length { if active[index] == source { start = index } }
    let chain = "\"${active[start].name}\" includes "
    for index of start + 1..<active.length { chain += "\"${active[index].name}\", which includes " }
    error(modulePath, "Inclusion cycle: ${chain}\"${source.name}\"", inclusion.span)
  }

  private error(modulePath: string, message: string, span: SourceSpan): none {
    diagnostics.push(Diagnostic { severity: "error", message, span: semanticSpan(span), module: modulePath })
  }
}

function conflictMessage(name: string, source: string, existing: ClaimedField): string {
  if existing.source == "" {
    return "Field \"${name}\" from \"${source}\" is already declared on line ${existing.line}; remove the inclusion or rename the field"
  }
  return "Field \"${name}\" is already included from \"${existing.source}\" (line ${existing.line}); remove one inclusion or rename the field"
}

function semanticSpan(span: SourceSpan): SemanticSpan {
  return SemanticSpan {
    start: SemanticLocation { line: span.start.line, column: span.start.column, offset: span.start.offset },
    end: SemanticLocation { line: span.end.line, column: span.end.column, offset: span.end.offset },
  }
}

/** Expands every class and struct inclusion in the module graph. */
export function expandFieldInclusions(modules: ModuleInfo[]): Diagnostic[] {
  expansion := InclusionExpansion { modules }
  for module of modules {
    for statement of module.program.statements {
      if class_ := statement as ClassDeclaration { expansion.expand(class_, module.path) }
    }
  }
  return expansion.diagnostics
}
