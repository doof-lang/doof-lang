import { Assert } from "std/assert"
import { CppTypeRegistry } from "./cpp-type"
import { CppDeclarationBuilder } from "./cpp-declaration"
import { HeaderPlan, HeaderSection } from "./emitter-header-plan"
import { HeaderRenderCache, renderProjectedHeader } from "./emitter-header-render"

function structuredPlan(registry: CppTypeRegistry, identity: string): HeaderPlan {
  type_ := registry.templateType("std::variant", [registry.templateType("std::shared_ptr", [registry.atom("Left", "later")]), registry.templateType("std::shared_ptr", [registry.atom("Right", "later")])])
  builder := CppDeclarationBuilder {}
  builder.text("struct Pair { ")
  builder.type_(type_)
  builder.text(" first; ")
  builder.type_(type_)
  builder.text(" second; };\n")
  return HeaderPlan { identity, classDefinitions: [builder.finish()] }
}

export function testStructuredRenderCacheIncludesAliasPositionAndNamespace(): none {
  registry := CppTypeRegistry {}
  plan := structuredPlan(registry, "pair")
  cache := HeaderRenderCache {}
  later := HeaderSection { namespaceName: "later", plan }
  before := HeaderSection { namespaceName: "before", plan }
  standalone := renderProjectedHeader([later], registry, cache)
  Assert.stringContains(standalone, "using doof_header_type_1 = std::variant<std::shared_ptr<Left>, std::shared_ptr<Right>>;")
  combined := renderProjectedHeader([before, later], registry, cache)
  Assert.stringContains(combined, "std::shared_ptr<::later::Left>")
  Assert.stringContains(combined, "using doof_header_type_2 =")
  Assert.equal(combined, renderProjectedHeader([before, later], registry, cache))
  Assert.equal(standalone, renderProjectedHeader([later], registry, cache))
  fresh := HeaderRenderCache {}
  Assert.equal(combined, renderProjectedHeader([before, later], registry, fresh))
}
