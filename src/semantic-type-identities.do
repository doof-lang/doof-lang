// Compilation-local object identities. These do not canonicalize semantic types.
import { ActorType, ArrayResolvedType, ClassMetadataResolvedType, ClassType, FunctionType, InterfaceType, MapResolvedType, MethodReflectionResolvedType, PromiseType, ResultResolvedType, SetResolvedType, StreamResolvedType, TupleResolvedType, TypeParameterType, UnionResolvedType, WeakResolvedType, ResolvedType, SemanticTypeIdentity, SemanticTypeIdentityOwner } from "./semantic"

// Read-only lookup has no miss insertion path. Unknown/scratch types use -1 and
// must bypass all ID-keyed memo tables rather than alias one another.
export class SemanticTypeIdentitySnapshot {
  readonly owner: SemanticTypeIdentityOwner

  identify(type_: ResolvedType): int {
    existing := type_.emissionIdentity
    if existing != none && existing!.owner == owner { return existing!.id }
    return -1
  }
}

export class SemanticTypeIdentities {
  private prepared: Set<int> = []
  private owner: SemanticTypeIdentityOwner = SemanticTypeIdentityOwner {}
  private let nextId: int = 0

  identify(type_: ResolvedType): int {
    existing := type_.emissionIdentity
    if existing != none && existing!.owner == owner { return existing!.id }
    id := nextId
    nextId += 1
    type_.emissionIdentity = SemanticTypeIdentity { owner, id }
    return id
  }

  snapshot(): SemanticTypeIdentitySnapshot {
    return SemanticTypeIdentitySnapshot { owner }
  }

  // Preparation visits semantic children once, even if header lowering assigned
  // the outer object's ID earlier. Mark first to tolerate recursive constraints.
  prepare(type_: ResolvedType): none {
    id := identify(type_)
    if prepared.has(id) { return }
    prepared.add(id)
    case type_ {
      class_: ClassType -> { for argument of class_.typeArgs { prepare(argument) } }
      interface_: InterfaceType -> { for argument of interface_.typeArgs { prepare(argument) } }
      function_: FunctionType -> {
        for parameter of function_.params { prepare(parameter.type_) }
        prepare(function_.returnType)
      }
      actor: ActorType -> { prepare(actor.innerClass) }
      promise: PromiseType -> { prepare(promise.valueType) }
      array: ArrayResolvedType -> { prepare(array.elementType) }
      map: MapResolvedType -> { prepare(map.keyType); prepare(map.valueType) }
      set_: SetResolvedType -> { prepare(set_.elementType) }
      stream: StreamResolvedType -> { prepare(stream.elementType) }
      result_: ResultResolvedType -> { prepare(result_.valueType); prepare(result_.errorType) }
      tuple: TupleResolvedType -> { for element of tuple.elements { prepare(element) } }
      union_: UnionResolvedType -> { for member of union_.types { prepare(member) } }
      weak_: WeakResolvedType -> { prepare(weak_.inner) }
      parameter: TypeParameterType -> { if parameter.constraint != none { prepare(parameter.constraint!) } }
      metadata: ClassMetadataResolvedType -> { prepare(metadata.classType) }
      reflection: MethodReflectionResolvedType -> { prepare(reflection.classType) }
      _ -> { }
    }
  }

}
