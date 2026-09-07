// Only enabled after checking and concrete-instantiation planning are complete.
// Semantic structure and registration tables stay fixed for this cache lifetime.
import { CppType, CppTypeRegistry } from "./cpp-type"
import { ResolvedType, TypeSubstitution } from "./semantic"
import { SemanticTypeIdentities, SemanticTypeIdentitySnapshot } from "./semantic-type-identities"

export class TypeLoweringGraph {
  registry: CppTypeRegistry
  identities: SemanticTypeIdentities | SemanticTypeIdentitySnapshot = SemanticTypeIdentities {}
  // These inputs are already specialized and concretely registered.
  lowered: Map<int, CppType> = {}
}

export class TypeLoweringSession {
  graph: TypeLoweringGraph
  // A session belongs to one module and fixed concrete registration tables.
  private let substitution: TypeSubstitution | none = none
  let values: Map<int, CppType> = {}
  let returns: Map<int, CppType> = {}
  let registered: Map<int, ResolvedType> = {}

  select(next: TypeSubstitution | none): none {
    if substitution == next { return }
    substitution = next
    values = {}
    returns = {}
    registered = {}
  }
}
