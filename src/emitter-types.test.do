import { SemanticTypeIdentities } from "./semantic-type-identities"
import { TypeLoweringGraph, TypeLoweringSession } from "./emitter-type-cache"
import { ArrayResolvedType, TupleResolvedType, TypeParameterType, TypeSubstitution } from "./semantic"
import { emitContextReturnType } from "./emitter-types"
import { classInstantiationKey } from "./emitter-monomorphize"
import { CppTypeRegistry, renderCppType } from "./cpp-type"
import { lowerCppType } from "./emitter-types"
import { Assert } from "std/assert"
import { EmitContext } from "./emitter-context"
import { emitContextType, emitType, usesVariantRepresentation } from "./emitter-types"
import { ClassType, InterfaceType, NoneType, PrimitiveType, ResultResolvedType, Symbol, UnionResolvedType } from "./semantic"

export function testCarrierModelSeparatesResultStorageFromUnionDispatch(): none {
  integer := PrimitiveType { name: "int" }
  result := ResultResolvedType { valueType: integer, errorType: integer }
  Assert.isFalse(usesVariantRepresentation(result))
  Assert.isTrue(usesVariantRepresentation(UnionResolvedType { types: [result, NoneType {}] }))
  Assert.isFalse(usesVariantRepresentation(UnionResolvedType { types: [integer, NoneType {}] }))
}

export function testRejectsUnloweredNonNativeGenericClassTypes(): none {
  symbol := Symbol { kind: "class", name: "Box", module: "/box.do", exported: true }
  unresolved := ClassType {
    name: "Box",
    symbol,
    typeArgs: [PrimitiveType { name: "int" }],
  }

  result := catchPanic(=> emitType(unresolved, "/main.do"))
  case result {
    failure: Failure<string> -> {
      Assert.stringContains(failure.error, "before monomorphization: /box.do::Box")
    }
    _ -> { panic("expected unlowered non-native generic type emission to panic") }
  }
}

export function testKeepsNativeGenericClassTypesAtCppBoundary(): none {
  symbol := Symbol {
    kind: "class",
    name: "Box",
    module: "/native.do",
    exported: true,
    native_: true,
    nativeCppName: "native::Box",
  }
  native := ClassType {
    name: "Box",
    symbol,
    typeArgs: [PrimitiveType { name: "int" }],
  }

  Assert.equal(emitType(native, "/main.do"), "std::shared_ptr<::native::Box<int32_t>>")
}

export function testRequiresRegisteredConcreteClassNames(): none {
  symbol := Symbol { kind: "class", name: "Box", module: "/box.do", exported: true }
  unresolved := ClassType { name: "Box", symbol, typeArgs: [PrimitiveType { name: "int" }] }

  result := catchPanic(=> emitContextType(unresolved, EmitContext { modulePath: "/main.do" }))
  case result {
    failure: Failure<string> -> { Assert.stringContains(failure.error, "Missing concrete class instantiation") }
    _ -> { panic("expected a missing concrete class registration to panic") }
  }
}

export function testRequiresRegisteredConcreteInterfaceNames(): none {
  symbol := Symbol { kind: "interface", name: "Reader", module: "/reader.do", exported: true }
  unresolved := InterfaceType { name: "Reader", symbol, typeArgs: [PrimitiveType { name: "string" }] }

  result := catchPanic(=> emitContextType(unresolved, EmitContext { modulePath: "/main.do" }))
  case result {
    failure: Failure<string> -> { Assert.stringContains(failure.error, "Missing concrete interface instantiation") }
    _ -> { panic("expected a missing concrete interface registration to panic") }
  }
}

export function testStructuredTypeLoweringRetainsNativeTemplates(): none {
  registry := CppTypeRegistry {}
  type_ := ClassType { name: "Box", symbol: Symbol { kind: "class", name: "Box", module: "/foreign.do", exported: true, native_: true, nativeCppName: "vendor::Box" }, typeArgs: [PrimitiveType { name: "int" }] }
  Assert.equal(renderCppType(lowerCppType(type_, registry)), "std::shared_ptr<::vendor::Box<int32_t>>")
}

export function testTypeLoweringMemoizesCompoundChildrenAndCarrierPositions(): none {
  registry := CppTypeRegistry {}
  graph := TypeLoweringGraph { registry }
  session := TypeLoweringSession { graph }
  context := EmitContext { cppTypes: registry, typeLowering: session }
  integer := PrimitiveType { name: "int" }
  child := ArrayResolvedType { elementType: integer, readonly_: false }
  tuple := TupleResolvedType { elements: [child, child] }
  Assert.equal(emitContextType(tuple, context), "std::tuple<std::shared_ptr<std::vector<int32_t>>, std::shared_ptr<std::vector<int32_t>>>")
  size := graph.lowered.size
  Assert.equal(emitContextType(tuple, context), emitType(tuple))
  Assert.equal(graph.lowered.size, size)
  Assert.equal(session.values.size, 1)
  // A second parent reuses the already-registered and lowered child.
  other := TupleResolvedType { elements: [child] }
  emitContextType(other, context)
  Assert.equal(graph.lowered.size, size + 1)
  unit := NoneType {}
  Assert.equal(emitContextType(unit, context), "std::monostate")
  Assert.equal(emitContextReturnType(unit, context), "void")
  Assert.equal(emitContextType(ResultResolvedType { valueType: unit, errorType: integer }, context), "doof::Result<void, int32_t>")
}

export function testTypeLoweringMemoizationIsolatesSubstitutions(): none {
  registry := CppTypeRegistry {}
  graph := TypeLoweringGraph { registry }
  context := EmitContext { cppTypes: registry, typeLowering: TypeLoweringSession { graph } }
  parameter := TypeParameterType { name: "T" }
  array := ArrayResolvedType { elementType: parameter, readonly_: false }
  context.substitution = TypeSubstitution { names: ["T"], arguments: [PrimitiveType { name: "int" }] }
  Assert.equal(emitContextType(array, context), "std::shared_ptr<std::vector<int32_t>>")
  context.substitution = TypeSubstitution { names: ["T"], arguments: [PrimitiveType { name: "string" }] }
  Assert.equal(emitContextType(array, context), "std::shared_ptr<std::vector<std::string>>")
  context.substitution = none
  Assert.equal(emitContextType(array, context), "std::shared_ptr<std::vector<T>>")
}

export function testTypeLoweringMemoizationKeepsConcreteMappingsAndNamespacesLocal(): none {
  registry := CppTypeRegistry {}
  graph := TypeLoweringGraph { registry }
  integer := PrimitiveType { name: "int" }
  box := ClassType { name: "Box", symbol: Symbol { kind: "class", name: "Box", module: "/box.do", exported: true }, typeArgs: [integer] }
  key := classInstantiationKey("/box.do", "Box", [integer])
  first := EmitContext { modulePath: "/box.do", cppTypes: registry, concreteClassKeys: [key], concreteClassNames: ["First"], typeLowering: TypeLoweringSession { graph } }
  second := EmitContext { modulePath: "/box.do", cppTypes: registry, concreteClassKeys: [key], concreteClassNames: ["Second"], typeLowering: TypeLoweringSession { graph } }
  Assert.equal(emitContextType(box, first), "std::shared_ptr<First>")
  Assert.equal(emitContextType(box, second), "std::shared_ptr<Second>")
  Assert.equal(emitContextType(box, first), "std::shared_ptr<First>")
  missing := EmitContext { cppTypes: registry, typeLowering: TypeLoweringSession { graph } }
  failure := catchPanic(=> emitContextType(box, missing))
  case failure {
    error: Failure<string> -> { Assert.stringContains(error.error, "Missing concrete class instantiation") }
    _ -> { panic("Expected the missing context's registration diagnostic") }
  }
  left := ClassType { name: "Same", symbol: Symbol { kind: "class", name: "Same", module: "/left.do", exported: true } }
  right := ClassType { name: "Same", symbol: Symbol { kind: "class", name: "Same", module: "/right.do", exported: true } }
  union_ := UnionResolvedType { types: [left, right] }
  Assert.equal(emitContextType(union_, first), emitType(union_, first.modulePath))
  reverse := UnionResolvedType { types: [right, left] }
  Assert.isTrue(emitContextType(reverse, first) != emitContextType(union_, first))
}

export function testReadonlyEmissionCacheMissesCannotAliasOrMutateTypes(): none {
  preparation := SemanticTypeIdentities {}
  prepared := PrimitiveType { name: "int" }
  preparation.prepare(prepared)
  saved := prepared.emissionIdentity
  registry := CppTypeRegistry {}
  graph := TypeLoweringGraph { registry, identities: preparation.snapshot() }
  session := TypeLoweringSession { graph }
  context := EmitContext { cppTypes: registry, typeLowering: session }
  first := PrimitiveType { name: "string" }
  second := PrimitiveType { name: "bool" }
  Assert.equal(emitContextType(first, context), "std::string")
  Assert.equal(emitContextType(second, context), "bool")
  Assert.equal(session.values.size, 0)
  Assert.equal(graph.lowered.size, 0)
  Assert.equal(first.emissionIdentity, none)
  Assert.equal(second.emissionIdentity, none)
  Assert.equal(emitContextType(prepared, context), "int32_t")
  Assert.equal(emitContextType(prepared, context), "int32_t")
  Assert.equal(session.values.size, 1)
  Assert.equal(prepared.emissionIdentity, saved)
}
