import { Assert as EditorAssert } from "std/assert"
import { editorTypeName } from "./editor-model"
import { FunctionType, FunctionParamType, PrimitiveType } from "./semantic"

export function testEditorSignatureContainsParameterNamesAndReturnType(): none {
  type_ := FunctionType { params: [FunctionParamType { name: "value", type_: PrimitiveType { name: "int" }, hasDefault: false }], returnType: PrimitiveType { name: "string" } }
  EditorAssert.equal(editorTypeName(type_), "(value: int): string")
}
