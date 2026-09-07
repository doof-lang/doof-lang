import { Assert } from "std/assert"
import { CppTypeRegistry } from "./cpp-type"
import { CppDeclarationBuilder, textDeclaration } from "./cpp-declaration"
import { HeaderPlan } from "./emitter-header-plan"
import { HeaderAliasState, planHeaderAliases } from "./emitter-header-aliases"

export function testStructuredAliasesPreferNamesAndRespectCompleteness(): none {
  registry := CppTypeRegistry {}
  left := registry.templateType("std::shared_ptr", [registry.atom("Left")])
  right := registry.templateType("std::shared_ptr", [registry.atom("Right")])
  choice := registry.templateType("std::variant", [left, right])
  valueChoice := registry.templateType("std::variant", [left, registry.atom("int32_t")])
  builder := CppDeclarationBuilder {}
  for type_ of [choice, choice, valueChoice, valueChoice] { builder.type_(type_); builder.text(" field;\n") }
  declaration := builder.finish()
  named := HeaderPlan { classDefinitions: [declaration], preferredTypeAliasNames: ["Choice"], preferredTypeAliasTypes: [choice] }
  aliases := planHeaderAliases(named, "", HeaderAliasState {})
  Assert.equal(try! aliases.names.get(choice.id), "Choice")
  Assert.isFalse(aliases.names.has(valueChoice.id))
  Assert.isFalse(aliases.definitionNames.has(choice.id))
  Assert.equal(aliases.declarations.length, 0)
  anonymous := planHeaderAliases(HeaderPlan { classDefinitions: [declaration], reservedNamespaceNames: ["doof_header_type_1"] }, "", HeaderAliasState {})
  Assert.equal(try! anonymous.names.get(choice.id), "doof_header_type_2")
  Assert.equal(anonymous.declarations.length, 1)
  opaque := planHeaderAliases(HeaderPlan { classDefinitions: [textDeclaration("std::variant<std::shared_ptr<A>> a; std::variant<std::shared_ptr<A>> b;")] }, "", HeaderAliasState {})
  Assert.equal(opaque.declarations.length, 0)
}
