import { Assert as EditorAssert } from "std/assert"
import { Parser as EditorParser } from "./parser"

export function testEditorStatementRecoveryKeepsLaterDeclarations(): none {
  parser := EditorParser { source: "function main(): int {\nlet broken = ;\nreturn 42\n}", editorMode: true }
  program := parser.parse()
  EditorAssert.equal(program.statements.length, 1)
  EditorAssert.equal(parser.issues.length, 1)
}
