import { AnalysisResult } from "./analyzer"
import { ClassDeclaration, FunctionDeclaration } from "./ast"
import { ResolvedType, TypeSubstitution, ClassType, InterfaceType, ArrayResolvedType, MapResolvedType, SetResolvedType, StreamResolvedType, ResultResolvedType, ActorType, PromiseType, TupleResolvedType, UnionResolvedType, WeakResolvedType, FunctionType } from "./semantic"
import { ModuleNames, moduleNamespace } from "./emitter-names"
import { typeName } from "./checker-types"
import { CheckedInstantiations, DiscoveredFunction, DiscoveredClass, DiscoveredInterface, DiscoveredMethod, discoverInstantiations, collectJsonDemand } from "./checked-instantiations"
export { functionInstantiationKey, classInstantiationKey, interfaceInstantiationKey, methodInstantiationKey } from "./checked-instantiations"

export class FunctionInstantiation {
  key: string
  modulePath: string
  declaration: FunctionDeclaration
  substitution: TypeSubstitution
  emittedName: string
  trace: string[] = []
}

export class ClassInstantiation {
  key: string
  modulePath: string
  declaration: ClassDeclaration
  substitution: TypeSubstitution
  emittedName: string
  trace: string[] = []
}

export class InterfaceInstantiation {
  key: string
  modulePath: string
  name: string
  substitution: TypeSubstitution
  emittedName: string
  implementations: ImplementationRef[] = []
}

export class ImplementationRef {
  modulePath: string
  typeName: string
}

export class MethodInstantiation {
  key: string
  modulePath: string
  ownerKey: string
  owner: ClassDeclaration
  declaration: FunctionDeclaration
  substitution: TypeSubstitution
  ownerEmittedName: string
  emittedName: string
  trace: string[] = []
}

export class InstantiationPlan {
  readonly moduleNames: ModuleNames = ModuleNames {}
  functions: FunctionInstantiation[] = []
  classes: ClassInstantiation[] = []
  interfaces: InterfaceInstantiation[] = []
  methods: MethodInstantiation[] = []
  let overflow: bool = false
  overflowTrace: string[] = []
  let currentTrace: string[] = []
  jsonSerializationKeys: string[] = []
  jsonDeserializationKeys: string[] = []
  concreteNameScopes: string[] = []
  concreteNames: string[] = []
}

export function buildInstantiationPlan(result: AnalysisResult, moduleNames: ModuleNames = ModuleNames {}): InstantiationPlan {
  return nameInstantiations(discoverInstantiations(result), moduleNames)
}

export function nameInstantiations(checked: CheckedInstantiations, moduleNames: ModuleNames = ModuleNames {}): InstantiationPlan {
  plan := InstantiationPlan { moduleNames, overflow: checked.overflow }
  for item of checked.overflowTrace { plan.overflowTrace.push(item) }
  for key of checked.jsonSerializationKeys { plan.jsonSerializationKeys.push(key) }
  for key of checked.jsonDeserializationKeys { plan.jsonDeserializationKeys.push(key) }
  classNames: Map<string, string> := {}
  // Preserve cross-kind discovery order: colliding C++ spellings share a scope.
  for entry of checked.entries {
    case entry {
      item: DiscoveredFunction -> {
        emittedName := allocateConcreteName(plan, "module:" + item.modulePath, concreteName(item.declaration.name, item.substitution.arguments, moduleNames))
        plan.functions.push(FunctionInstantiation { key: item.key, modulePath: item.modulePath, declaration: item.declaration, substitution: item.substitution, emittedName, trace: item.trace })
      }
      item: DiscoveredClass -> {
        emittedName := allocateConcreteName(plan, "module:" + item.modulePath, concreteName(item.declaration.name, item.substitution.arguments, moduleNames))
        classNames.set(item.key, emittedName)
        plan.classes.push(ClassInstantiation { key: item.key, modulePath: item.modulePath, declaration: item.declaration, substitution: item.substitution, emittedName, trace: item.trace })
      }
      item: DiscoveredInterface -> {
        emittedName := allocateConcreteName(plan, "module:" + item.modulePath, concreteName(item.name, item.substitution.arguments, moduleNames))
        plan.interfaces.push(InterfaceInstantiation { key: item.key, modulePath: item.modulePath, name: item.name, substitution: item.substitution, emittedName })
      }
      item: DiscoveredMethod -> {
        let ownerEmittedName = item.owner.name
        if item.owner.typeParams.length > 0 {
          found := try? classNames.get(item.ownerKey)
          if found != none { ownerEmittedName = found! }
        }
        arguments: ResolvedType[] := []
        for i of item.owner.typeParams.length..<item.substitution.arguments.length { arguments.push(item.substitution.arguments[i]) }
        emittedName := allocateConcreteName(plan, "owner:" + item.ownerKey, concreteName(item.declaration.name, arguments, moduleNames))
        plan.methods.push(MethodInstantiation { key: item.key, modulePath: item.modulePath, ownerKey: item.ownerKey, owner: item.owner, declaration: item.declaration, substitution: item.substitution, ownerEmittedName, emittedName, trace: item.trace })
      }
    }
  }
  for i of 0..<checked.interfaces.length {
    for implementation of checked.interfaces[i].implementations {
      typeName_ := if implementation.specializationKey == "" then implementation.typeName else try! classNames.get(implementation.specializationKey)
      plan.interfaces[i].implementations.push(ImplementationRef { modulePath: implementation.modulePath, typeName: typeName_ })
    }
  }
  return plan
}

export function concreteName(name: string, typeArgs: ResolvedType[], moduleNames: ModuleNames = ModuleNames {}): string {
  let result = name
  for argument of typeArgs { result = result + "__" + mangleType(argument, moduleNames) }
  return result
}

function allocateConcreteName(plan: InstantiationPlan, scope: string, base: string): string {
  let candidate = base
  let suffix = 2
  while concreteNameAllocated(plan, scope, candidate) {
    candidate = base + "_" + string(suffix)
    suffix = suffix + 1
  }
  plan.concreteNameScopes.push(scope)
  plan.concreteNames.push(candidate)
  return candidate
}

function concreteNameAllocated(plan: InstantiationPlan, scope: string, name: string): bool {
  for index of 0..<plan.concreteNames.length {
    if plan.concreteNameScopes[index] == scope && plan.concreteNames[index] == name { return true }
  }
  return false
}

function mangleType(type_: ResolvedType, moduleNames: ModuleNames): string {
  case type_ {
    class_: ClassType -> { return sanitize(moduleNamespace(class_.symbol.module, moduleNames) + "_" + class_.name + "_" + concreteTypeListMangle(class_.typeArgs, moduleNames)) }
    interface_: InterfaceType -> { return sanitize(moduleNamespace(interface_.symbol.module, moduleNames) + "_" + interface_.name + "_" + concreteTypeListMangle(interface_.typeArgs, moduleNames)) }
    array: ArrayResolvedType -> { return (if array.readonly_ then "readonly_array_" else "array_") + mangleType(array.elementType, moduleNames) }
    map: MapResolvedType -> { return (if map.readonly_ then "readonly_map_" else "map_") + mangleType(map.keyType, moduleNames) + "_" + mangleType(map.valueType, moduleNames) }
    set_: SetResolvedType -> { return (if set_.readonly_ then "readonly_set_" else "set_") + mangleType(set_.elementType, moduleNames) }
    stream: StreamResolvedType -> { return "stream_" + mangleType(stream.elementType, moduleNames) }
    result: ResultResolvedType -> { return "result_" + mangleType(result.valueType, moduleNames) + "_" + mangleType(result.errorType, moduleNames) }
    actor: ActorType -> { return "actor_" + mangleType(actor.innerClass, moduleNames) }
    promise: PromiseType -> { return "promise_" + mangleType(promise.valueType, moduleNames) }
    tuple: TupleResolvedType -> { return "tuple_" + concreteTypeListMangle(tuple.elements, moduleNames) }
    union_: UnionResolvedType -> { return "union_" + concreteTypeListMangle(union_.types, moduleNames) }
    weak_: WeakResolvedType -> { return "weak_" + mangleType(weak_.inner, moduleNames) }
    function_: FunctionType -> {
      let parameters: ResolvedType[] = []
      for parameter of function_.params { parameters.push(parameter.type_) }
      return "function_" + string(parameters.length) + "_" + concreteTypeListMangle(parameters, moduleNames) + "_returns_" + mangleType(function_.returnType, moduleNames)
    }
    _ -> { return sanitize(typeName(type_)) }
  }
  return "type"
}

function concreteTypeListMangle(types: ResolvedType[], moduleNames: ModuleNames): string {
  let result = ""
  for type_ of types {
    if result != "" { result = result + "_" }
    result = result + mangleType(type_, moduleNames)
  }
  return result
}

function sanitize(value: string): string {
  return value.replaceAll("/", "_").replaceAll(".", "_").replaceAll("<", "_").replaceAll(">", "_")
    .replaceAll(",", "_").replaceAll(" ", "_").replaceAll("|", "_").replaceAll("[", "_").replaceAll("]", "_")
    .replaceAll(":", "_").replaceAll("(", "_").replaceAll(")", "_")
}

// Backend entry points can request additional JSON adapters after discovery.
export function addJsonSerializationDemand(plan: InstantiationPlan, type_: ResolvedType, analysis: AnalysisResult): none {
  collectJsonDemand(plan.jsonSerializationKeys, type_, analysis)
}
export function addJsonDeserializationDemand(plan: InstantiationPlan, type_: ResolvedType, analysis: AnalysisResult): none {
  collectJsonDemand(plan.jsonDeserializationKeys, type_, analysis)
}
