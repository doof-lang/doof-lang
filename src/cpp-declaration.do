// Immutable declaration fragments keep typed slots separate from C++ text.
// Comments, literals and opaque native/expression text are never reparsed.
import { CppType, CppTypeRegistry, renderCppType } from "./cpp-type"
import { StringBuilder } from "./string-builder"

export class CppDeclarationPart {
  readonly text: string = ""
  readonly type_: CppType | none = none
}

export class CppDeclaration {
  readonly parts: readonly CppDeclarationPart[]
}

export class CppDeclarationBuilder {
  private parts: CppDeclarationPart[] = []

  text(value: string): none {
    if value != "" { parts.push(CppDeclarationPart { text: value }) }
  }
  type_(value: CppType): none { parts.push(CppDeclarationPart { type_: value }) }
  declaration(value: CppDeclaration): none { for part of value.parts { parts.push(part) } }
  finish(): CppDeclaration => CppDeclaration { parts: parts.drainToReadonly() }
}

export function textDeclaration(value: string): CppDeclaration {
  return CppDeclaration { parts: [CppDeclarationPart { text: value }] }
}

export function renderDeclaration(declaration: CppDeclaration, namespace: string = "", aliases: Map<int, string> = {}, registry: CppTypeRegistry | none = none, rendered: Map<int, string> | none = none): string {
  result := StringBuilder()
  for part of declaration.parts {
    if part.type_ != none {
      result.append(if registry != none && aliases.size == 0 then registry!.render(part.type_!, namespace) else renderCppType(part.type_!, namespace, aliases, rendered))
    }
    else { result.append(part.text) }
  }
  return result.drainToString()
}
