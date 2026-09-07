import { Assert } from "std/assert"
import { CppTypeRegistry } from "./cpp-type"
import { CppDeclarationBuilder, renderDeclaration } from "./cpp-declaration"

export function testStructuredDeclarationKeepsTextOpaque(): none {
  registry := CppTypeRegistry {}
  type_ := registry.templateType("std::variant", [registry.templateType("std::shared_ptr", [registry.atom("A")])])
  builder := CppDeclarationBuilder {}
  builder.text("// std::variant<std::shared_ptr<A>>\n")
  builder.type_(type_)
  builder.text(" value; const char* text = \"std::variant<std::shared_ptr<A>>\";\n")
  declaration := builder.finish()
  rendered := renderDeclaration(declaration, "", { type_.id: "Choice" })
  Assert.stringContains(rendered, "Choice value;")
  Assert.stringContains(rendered, "// std::variant<std::shared_ptr<A>>")
  Assert.stringContains(rendered, "\"std::variant<std::shared_ptr<A>>\"")
  Assert.equal(rendered, renderDeclaration(declaration, "", { type_.id: "Choice" }))
}

export function testStructuredRenderCachesDoNotLeakAliasChoices(): none {
  registry := CppTypeRegistry {}
  type_ := registry.templateType("std::variant", [registry.templateType("std::shared_ptr", [registry.atom("A")])])
  builder := CppDeclarationBuilder {}
  builder.type_(type_)
  declaration := builder.finish()
  firstRendered: Map<int, string> := {}
  secondRendered: Map<int, string> := {}
  Assert.equal(renderDeclaration(declaration, "", { type_.id: "First" }, registry, firstRendered), "First")
  Assert.equal(renderDeclaration(declaration, "", { type_.id: "Second" }, registry, secondRendered), "Second")
  Assert.equal(renderDeclaration(declaration, "", {}, registry), "std::variant<std::shared_ptr<A>>")
}
