import { Assert } from "std/assert"
import { PrimitiveType, UnionResolvedType } from "./semantic"
import { SemanticTypeIdentities } from "./semantic-type-identities"

export function testTypeLoweringIdentitiesAreObjectAndGraphLocal(): none {
  first := PrimitiveType { name: "int" }
  equivalent := PrimitiveType { name: "int" }
  Assert.equal(first.emissionIdentity, none)
  graph := SemanticTypeIdentities {}
  id := graph.identify(first)
  Assert.equal(graph.identify(first), id)
  Assert.isTrue(graph.identify(equivalent) != id)
  other := SemanticTypeIdentities {}
  Assert.equal(other.identify(first), 0)
  // Re-entering the first graph after restamping must never alias another type.
  Assert.isTrue(graph.identify(first) != graph.identify(equivalent))
  union_ := UnionResolvedType { types: [first, equivalent] }
  Assert.isTrue(graph.identify(union_) != graph.identify(first))
  Assert.equal(union_.types.length, 2)
}

export function testReadonlyEmissionIdentitySnapshotNeverStampsMisses(): none {
  child := PrimitiveType { name: "int" }
  parent := UnionResolvedType { types: [child] }
  preparation := SemanticTypeIdentities {}
  preparation.identify(parent)
  preparation.prepare(parent)
  snapshot := preparation.snapshot()
  saved := child.emissionIdentity
  Assert.isTrue(snapshot.identify(child) >= 0)
  Assert.equal(child.emissionIdentity, saved)
  first := PrimitiveType { name: "string" }
  second := PrimitiveType { name: "bool" }
  Assert.equal(snapshot.identify(first), -1)
  Assert.equal(snapshot.identify(second), -1)
  Assert.equal(first.emissionIdentity, none)
  Assert.equal(second.emissionIdentity, none)
  other := SemanticTypeIdentities {}
  other.prepare(child)
  Assert.equal(snapshot.identify(child), -1)
  Assert.isTrue(other.snapshot().identify(child) >= 0)
}
