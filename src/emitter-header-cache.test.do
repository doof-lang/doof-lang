import { CppTypeRegistry } from "./cpp-type"
import { CppDeclarationBuilder } from "./cpp-declaration"
import { Assert } from "std/assert"
import { Program } from "./ast"
import { Parser } from "./parser"
import { HeaderPlan, HeaderSection, renderProjectedHeader } from "./emitter-header"
import { HeaderPlanCache, projectedHeaderKey } from "./emitter-header-cache"

export function testHeaderCacheKeysDistinguishSelectionsAndInterfaces(): none {
  program := Parser { source: "class Left {}\nclass Right {}" }.parse()
  left := Program { kind: program.kind, span: program.span, statements: [program.statements[0]] }
  right := Program { kind: program.kind, span: program.span, statements: [program.statements[1]] }
  reversed := Program { kind: program.kind, span: program.span, statements: [program.statements[1], program.statements[0]] }
  key := projectedHeaderKey("/types.do", left, [])
  Assert.isTrue(key != projectedHeaderKey("/other.do", left, []))
  Assert.isTrue(key != projectedHeaderKey("/types.do", right, []))
  Assert.isTrue(projectedHeaderKey("/types.do", program, []) != projectedHeaderKey("/types.do", reversed, []))
  Assert.isTrue(key != projectedHeaderKey("/types.do", left, ["Reader<int>"]))
  Assert.isTrue(projectedHeaderKey("/types.do", left, ["ab", "c"]) != projectedHeaderKey("/types.do", left, ["a", "bc"]))
  Assert.equal(key, projectedHeaderKey("/types.do", left, []))
}

function variantPlan(): HeaderPlan {
  registry := CppTypeRegistry {}
  variant := registry.templateType("std::variant", [registry.templateType("std::shared_ptr", [registry.atom("Left")]), registry.templateType("std::shared_ptr", [registry.atom("Right")])])
  declaration := CppDeclarationBuilder {}
  declaration.text("struct Pair { ")
  declaration.type_(variant)
  declaration.text(" first; ")
  declaration.type_(variant)
  declaration.text(" second; };\n")
  return HeaderPlan { classDefinitions: [declaration.finish()], hasMain: true, mainReturnsInt: true, mainAcceptsArgs: true }
}

export function testStructuredHeaderCacheSharesImmutableTemplates(): none {
  cache := HeaderPlanCache {}
  Assert.equal(cache.get("missing"), none)
  original := variantPlan()
  cache.store("pair", original)
  first := cache.get("pair")!
  Assert.isTrue(first.hasMain && first.mainReturnsInt && first.mainAcceptsArgs)
  combined := renderProjectedHeader([
    HeaderSection { namespaceName: "earlier", plan: variantPlan() },
    HeaderSection { namespaceName: "later", plan: first },
  ])
  Assert.stringContains(combined, "using doof_header_type_2 =")
  second := cache.get("pair")!
  standalone :=  renderProjectedHeader([HeaderSection { namespaceName: "later", plan: second }])
  Assert.stringContains(standalone, "using doof_header_type_1 =")
  Assert.stringNotContains(standalone, "doof_header_type_2")
  Assert.equal(standalone, renderProjectedHeader([HeaderSection { namespaceName: "later", plan: original }]))
  fresh := HeaderPlanCache {}
  Assert.equal(fresh.get("pair"), none)
}
