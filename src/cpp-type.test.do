import { prepareModuleNames, ModuleNamespaceMapping, moduleNamespace } from "./emitter-names"
import { Assert } from "std/assert"
import { CppTypeRegistry, isReferenceVariant, renderCppType } from "./cpp-type"

export function testStructuredCppTypeIdentityAndVariantOrder(): none {
  registry := CppTypeRegistry {}
  left := registry.templateType("std::shared_ptr", [registry.atom("Node", "left")])
  right := registry.templateType("std::shared_ptr", [registry.atom("Node", "right")])
  union_ := registry.templateType("std::variant", [left, right])
  Assert.equal(union_.id, registry.templateType("std::variant", [left, right]).id)
  Assert.isTrue(left.id != right.id)
  Assert.isTrue(union_.id != registry.templateType("std::variant", [right, left]).id)
  Assert.equal(renderCppType(union_, "left"), "std::variant<std::shared_ptr<Node>, std::shared_ptr<::right::Node>>")
  Assert.isTrue(isReferenceVariant(union_))
  Assert.isFalse(isReferenceVariant(registry.templateType("std::variant", [left, registry.atom("int32_t")])))
  Assert.isTrue(isReferenceVariant(registry.templateType("std::variant", [registry.atom("std::monostate"), left])))
  nested := registry.templateType("std::vector", [union_])
  Assert.equal(renderCppType(nested, "left", { union_.id: "Nodes" }), "std::vector<Nodes>")
}

export function testStructuredCanonicalRenderCacheKeepsNamespacesSeparate(): none {
  registry := CppTypeRegistry {}
  node := registry.templateType("std::shared_ptr", [registry.atom("Node", "owner")])
  Assert.equal(registry.render(node, "owner"), "std::shared_ptr<Node>")
  Assert.equal(registry.render(node, "consumer"), "std::shared_ptr<::owner::Node>")
  Assert.equal(registry.render(node, "owner"), "std::shared_ptr<Node>")
}

export function testPreparedCppTypeForksKeepIdsAndRenderCachesIndependent(): none {
  preparation := CppTypeRegistry {}
  node := preparation.atom("Node", "owner")
  shared := preparation.templateType("std::shared_ptr", [node])
  Assert.equal(preparation.render(shared, "consumer"), "std::shared_ptr<::owner::Node>")
  snapshot := preparation.snapshot()
  left := CppTypeRegistry { base: snapshot }
  right := CppTypeRegistry { base: snapshot }
  Assert.equal(left.atom("Node", "owner"), node)
  Assert.equal(right.templateType("std::shared_ptr", [right.atom("Node", "owner")]), shared)
  first := left.atom("Left")
  second := right.atom("Right")
  // New IDs are local to a fork; equal integers do not imply shared identity.
  Assert.equal(first.id, second.id)
  Assert.isTrue(first.id > shared.id)
  Assert.equal(left.render(first, ""), "Left")
  Assert.equal(right.render(second, ""), "Right")
  Assert.equal(left.render(shared, "consumer"), "std::shared_ptr<::owner::Node>")
  Assert.equal(right.render(shared, "owner"), "std::shared_ptr<Node>")
  preparation.atom("Later")
  Assert.equal(snapshot.nodes.size, 2)
  nested := CppTypeRegistry { base: left.snapshot() }
  Assert.equal(nested.atom("Left"), first)
  Assert.isTrue(nested.atom("Next").id > first.id)
  Assert.equal(snapshot.nodes.size, 2)
}

export function testReadonlyEmissionCppSnapshotRetainsNamingInputs(): none {
  names := prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  registry := CppTypeRegistry { names }
  snapshot := registry.snapshot()
  Assert.equal(moduleNamespace("/vendor/item.do", snapshot.names), "mapped::item")
  Assert.equal(moduleNamespace("/vendor/item.do"), "app_vendor_item_")
}
