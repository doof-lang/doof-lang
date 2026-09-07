import { prepareModuleNames, ModuleNamespaceMapping } from "./emitter-names"
import { exprModuleNamespaceFor } from "./emitter-expr-utils"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"
import { Assert } from "std/assert"
import { AstLocation, Identifier, ObjectProperty, SourceSpan } from "./ast"
import { NoneType, PrimitiveType, UnionResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitPropertyValue } from "./emitter-expr-utils"

export function testNoneCarrierSharedShorthandMatchesExpanded(): none {
  location := AstLocation { line: 1, column: 1, offset: 0 }
  span := SourceSpan { start: location, end: location }
  unit := NoneType {}
  target := UnionResolvedType { types: [PrimitiveType { name: "int" }, unit] }
  shorthand := ObjectProperty { name: "value", value: none, resolvedType: unit, span }
  expanded := ObjectProperty { name: "value", value: Identifier { kind: "identifier", name: "value", resolvedType: unit, span }, resolvedType: unit, span }
  context := EmitContext {}
  Assert.equal(emitPropertyValue(shorthand, context, target), "(static_cast<void>(value), std::nullopt)")
  Assert.equal(emitPropertyValue(shorthand, context, target), emitPropertyValue(expanded, context, target))
}

export function testWiderNonePromotionPreservesNullableCarriers(): none {
  for type_ of ["int", "Item"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class Item {}\nfunction widen(value: " + type_ + " | none): " + type_ + " | string | none { return value }",
    }], "/main.do")
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    source := result.emission!.modules[0].source
    Assert.stringContains(source, "if (doof::is_null(_nullable_value)) return std::monostate{};")
    Assert.stringContains(source, "doof::unwrap_optional(_nullable_value)")
  }
}

export function testReadonlyEmissionExpressionNamespacesAreExplicit(): none {
  names := prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "first" }])
  Assert.equal(exprModuleNamespaceFor("/vendor/item.do", names), "first::item")
  Assert.equal(exprModuleNamespaceFor("/vendor/item.do"), "app_vendor_item_")
}
