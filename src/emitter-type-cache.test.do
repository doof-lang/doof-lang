import { SemanticTypeIdentities } from "./semantic-type-identities"
import { Assert } from "std/assert"
import { CppTypeRegistry } from "./cpp-type"
import { PrimitiveType, TypeSubstitution } from "./semantic"
import { TypeLoweringGraph, TypeLoweringSession } from "./emitter-type-cache"

export function testTypeLoweringSessionInvalidatesEveryContextualStage(): none {
  registry := CppTypeRegistry {}
  graph := TypeLoweringGraph { registry }
  session := TypeLoweringSession { graph }
  type_ := PrimitiveType { name: "int" }
  id := graph.identities.identify(type_)
  cpp := registry.atom("int32_t")
  session.values.set(id, cpp)
  session.returns.set(id, cpp)
  session.registered.set(id, type_)
  graph.lowered.set(id, cpp)
  session.select(none)
  Assert.equal(session.values.size, 1)
  substitution := TypeSubstitution { names: ["T"], arguments: [type_] }
  session.select(substitution)
  Assert.equal(session.values.size, 0)
  Assert.equal(session.returns.size, 0)
  Assert.equal(session.registered.size, 0)
  Assert.equal(graph.lowered.size, 1)
  session.values.set(id, cpp)
  session.select(substitution)
  Assert.equal(session.values.size, 1)
  session.select(none)
  Assert.equal(session.values.size, 0)
}

export function testReadonlyEmissionSessionsShareLookupWithoutStamping(): none {
  preparation := SemanticTypeIdentities {}
  type_ := PrimitiveType { name: "int" }
  preparation.prepare(type_)
  snapshot := preparation.snapshot()
  first := TypeLoweringGraph { registry: CppTypeRegistry {}, identities: snapshot }
  second := TypeLoweringGraph { registry: CppTypeRegistry {}, identities: snapshot }
  Assert.equal(first.identities.identify(type_), second.identities.identify(type_))
  scratch := PrimitiveType { name: "bool" }
  Assert.equal(first.identities.identify(scratch), -1)
  Assert.equal(second.identities.identify(scratch), -1)
  Assert.equal(scratch.emissionIdentity, none)
}
