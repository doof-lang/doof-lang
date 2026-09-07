import { prepareModuleNames, ModuleNamespaceMapping, moduleNamespace } from "./emitter-names"
import { CppTypeRegistry } from "./cpp-type"
import { Assert } from "std/assert"
import { EmitContext } from "./emitter-context"
import { primitive, noneType, unionType, sameType } from "./checker-types"

export function testRestrictedYieldCarrierContext(): none {
  context := EmitContext {}
  Assert.isTrue(context.valueYieldType == none)
  optional := unionType([primitive("int"), noneType()])
  context.valueYieldType = optional
  Assert.isTrue(sameType(context.valueYieldType!, optional))
  Assert.isFalse(context.valueYieldReturnsVoid)
}

export function testStructuredContextsCanShareTypeRegistry(): none {
  registry := CppTypeRegistry {}
  first := EmitContext { cppTypes: registry }
  second := EmitContext { cppTypes: registry }
  Assert.equal(first.cppTypes.atom("Node", "first").id, second.cppTypes.atom("Node", "first").id)
  Assert.isTrue(first.cppTypes.atom("Node", "first").id != second.cppTypes.atom("Node", "second").id)
}

export function testTypeLoweringContextDefaultsToUncached(): none {
  context := EmitContext {}
  Assert.equal(context.typeLowering, none)
}

export function testReadonlyEmissionContextsCarryIndependentNames(): none {
  first := EmitContext { names: prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "one" }]) }
  second := EmitContext { names: prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "two" }]) }
  Assert.equal(moduleNamespace("/vendor/item.do", first.names), "one::item")
  Assert.equal(moduleNamespace("/vendor/item.do", second.names), "two::item")
}
