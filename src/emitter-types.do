import { ModuleNames } from "./emitter-names"
import { TypeLoweringGraph } from "./emitter-type-cache"
// C++ type lowering for the Doof emitter.
//
// This module owns representation choices only.  It deliberately does not
// inspect declarations or expressions; those concerns belong to the other
// emitter modules.

import { CppType, CppTypeRegistry, renderCppType } from "./cpp-type"
import { carrierOf, flattenCarrierMembers, naturalCarrierMember } from "./emitter-carriers"
import {
  ActorType, ArrayResolvedType, ClassMetadataResolvedType, ClassType, EnumType, FunctionParamType, FunctionType, InterfaceType, JsonValueResolvedType, MapResolvedType, MethodReflectionResolvedType, PrimitiveType, PromiseType, RangeResolvedType, ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, Symbol,
  NeverType, NoneType, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType, WeakResolvedType,
} from "./semantic"
import { moduleNamespace } from "./emitter-names"
import { substituteTypeParams } from "./checker-types"
import { EmitContext } from "./emitter-context"
import { classInstantiationKey, concreteName, interfaceInstantiationKey } from "./emitter-monomorphize"

export function specializeEmitType(resolvedType: ResolvedType, context: EmitContext): ResolvedType {
  if context.substitution == none { return resolvedType }
  return substituteTypeParams(resolvedType, context.substitution!.names, context.substitution!.arguments)
}

export function lowerContextCppType(resolvedType: ResolvedType, context: EmitContext): CppType {
  return lowerContextPosition(resolvedType, context, false)
}

export function lowerContextCppReturnType(resolvedType: ResolvedType, context: EmitContext): CppType {
  return lowerContextPosition(resolvedType, context, true)
}

function lowerContextPosition(resolvedType: ResolvedType, context: EmitContext, return_: bool): CppType {
  session := context.typeLowering
  let id = -1
  if session != none {
    session!.select(context.substitution)
    id = session!.graph.identities.identify(resolvedType)
    if id >= 0 {
      cached := if return_ then try? session!.returns.get(id) else try? session!.values.get(id)
      if cached != none { return cached! }
    }
  }
  specialized := lowerRegisteredTypes(specializeEmitType(resolvedType, context), context)
  result := if return_ && carrierOf(specialized, .Return).kind == .Void then context.cppTypes.atom("void")
    else lowerCppType(specialized, context.cppTypes, if session != none then session!.graph else none)
  if session != none && id >= 0 {
    if return_ { session!.returns.set(id, result) } else { session!.values.set(id, result) }
  }
  return result
}

export function emitContextType(resolvedType: ResolvedType, context: EmitContext): string {
  return context.cppTypes.render(lowerContextCppType(resolvedType, context), typeNamespace(context.modulePath, context.names))
}

export function emitContextReturnType(resolvedType: ResolvedType, context: EmitContext): string {
  return context.cppTypes.render(lowerContextCppReturnType(resolvedType, context), typeNamespace(context.modulePath, context.names))
}

export function typeNamespace(modulePath: string, names: ModuleNames = ModuleNames {}): string => if modulePath == "" then "" else moduleNamespace(modulePath, names)

export function emitContextClassInnerType(class_: ClassType, context: EmitContext): string {
  specialized := specializeEmitType(class_, context)
  lowered := lowerRegisteredTypes(specialized, context)
  case lowered {
    concrete: ClassType -> { return context.cppTypes.render(lowerCppClassInnerType(concrete, context.cppTypes), typeNamespace(context.modulePath, context.names)) }
    _ -> { panic("Class type did not remain nominal after contextual specialization") }
  }
  return ""
}

export function emitReturnType(resolvedType: ResolvedType, currentModulePath: string = "", names: ModuleNames = ModuleNames {}): string {
  if carrierOf(resolvedType, .Return).kind == .Void { return "void" }
  return emitType(resolvedType, currentModulePath, names)
}

export function emitResultPayloadType(resolvedType: ResolvedType, currentModulePath: string = "", names: ModuleNames = ModuleNames {}): string {
  if carrierOf(resolvedType, .Payload).kind == .Void { return "void" }
  return emitType(resolvedType, currentModulePath, names)
}

// Replace reached Doof generic nominals throughout a compound type before
// ordinary representation lowering. This keeps tuples, callbacks, Results,
// unions, and collections from accidentally reintroducing C++ templates.
function lowerRegisteredTypes(type_: ResolvedType, context: EmitContext): ResolvedType {
  session := context.typeLowering
  if session == none { return lowerRegisteredTypeUncached(type_, context) }
  session!.select(context.substitution)
  id := session!.graph.identities.identify(type_)
  if id < 0 { return lowerRegisteredTypeUncached(type_, context) }
  cached := try? session!.registered.get(id)
  if cached != none { return cached! }
  result := lowerRegisteredTypeUncached(type_, context)
  session!.registered.set(id, result)
  return result
}

function lowerRegisteredTypeUncached(type_: ResolvedType, context: EmitContext): ResolvedType {
  case type_ {
    class_: ClassType -> {
      if class_.typeArgs.length > 0 && !class_.symbol.native_ {
        key := classInstantiationKey(class_.symbol.module, class_.name, class_.typeArgs)
        for i of 0..<context.concreteClassKeys.length {
          if context.concreteClassKeys[i] == key {
            return ClassType { name: context.concreteClassNames[i], symbol: class_.symbol }
          }
        }
        panic("Missing concrete class instantiation for " + key)
      }
      let arguments: ResolvedType[] = []
      for argument of class_.typeArgs { arguments.push(lowerRegisteredTypes(argument, context)) }
      return ClassType { name: class_.name, symbol: class_.symbol, typeArgs: arguments }
    }
    interface_: InterfaceType -> {
      if interface_.typeArgs.length > 0 {
        key := interfaceInstantiationKey(interface_.symbol.module, interface_.name, interface_.typeArgs)
        registeredName := concreteInterfaceName(context, key)
        if registeredName == "" { panic("Missing concrete interface instantiation for " + key) }
        return InterfaceType { name: registeredName, symbol: interface_.symbol }
      }
      return interface_
    }
    array: ArrayResolvedType -> { return ArrayResolvedType { elementType: lowerRegisteredTypes(array.elementType, context), readonly_: array.readonly_ } }
    map: MapResolvedType -> { return MapResolvedType { keyType: lowerRegisteredTypes(map.keyType, context), valueType: lowerRegisteredTypes(map.valueType, context), readonly_: map.readonly_ } }
    set_: SetResolvedType -> { return SetResolvedType { elementType: lowerRegisteredTypes(set_.elementType, context), readonly_: set_.readonly_ } }
    stream: StreamResolvedType -> {
      key := interfaceInstantiationKey("", "Stream", [stream.elementType])
      registeredName := concreteInterfaceName(context, key)
      if registeredName != "" {
        return InterfaceType {
          name: registeredName,
          symbol: Symbol { kind: "interface", name: registeredName, module: context.modulePath, exported: false },
        }
      }
      return StreamResolvedType { elementType: lowerRegisteredTypes(stream.elementType, context) }
    }
    result_: ResultResolvedType -> { return ResultResolvedType { valueType: lowerRegisteredTypes(result_.valueType, context), errorType: lowerRegisteredTypes(result_.errorType, context) } }
    weak_: WeakResolvedType -> { return WeakResolvedType { inner: lowerRegisteredTypes(weak_.inner, context) } }
    actor: ActorType -> {
      lowered := lowerRegisteredTypes(actor.innerClass, context)
      case lowered {
        class_: ClassType -> { return ActorType { innerClass: class_ } }
        _ -> { return actor }
      }
    }
    promise: PromiseType -> { return PromiseType { valueType: lowerRegisteredTypes(promise.valueType, context) } }
    tuple: TupleResolvedType -> {
      let elements: ResolvedType[] = []
      for element of tuple.elements { elements.push(lowerRegisteredTypes(element, context)) }
      return TupleResolvedType { elements }
    }
    union_: UnionResolvedType -> {
      let members: ResolvedType[] = []
      for member of union_.types { members.push(lowerRegisteredTypes(member, context)) }
      return UnionResolvedType { types: members }
    }
    function_: FunctionType -> {
      let parameters: FunctionParamType[] = []
      for parameter of function_.params {
        parameters.push(FunctionParamType { name: parameter.name, type_: lowerRegisteredTypes(parameter.type_, context), hasDefault: parameter.hasDefault })
      }
      return FunctionType { params: parameters, returnType: lowerRegisteredTypes(function_.returnType, context), typeParams: function_.typeParams }
    }
    _ -> { return type_ }
  }
  return type_
}

function concreteInterfaceName(context: EmitContext, key: string): string {
  for i of 0..<context.concreteInterfaceKeys.length {
    if context.concreteInterfaceKeys[i] == key { return context.concreteInterfaceNames[i] }
  }
  return ""
}

export function emitType(resolvedType: ResolvedType, currentModulePath: string = "", names: ModuleNames = ModuleNames {}): string {
  return renderCppType(lowerCppType(resolvedType, CppTypeRegistry { names }), typeNamespace(currentModulePath, names))
}

export function lowerCppType(type_: ResolvedType, registry: CppTypeRegistry, cache: TypeLoweringGraph | none = none): CppType {
  if cache == none { return lowerCppTypeUncached(type_, registry, cache) }
  id := cache!.identities.identify(type_)
  if id < 0 { return lowerCppTypeUncached(type_, registry, cache) }
  cached := try? cache!.lowered.get(id)
  if cached != none { return cached! }
  result := lowerCppTypeUncached(type_, registry, cache)
  cache!.lowered.set(id, result)
  return result
}

function lowerCppTypeUncached(type_: ResolvedType, registry: CppTypeRegistry, cache: TypeLoweringGraph | none): CppType {
  case type_ {
    primitive: PrimitiveType -> { return registry.atom(emitPrimitive(primitive.name)) }
    class_: ClassType -> {
      inner := lowerCppClassInnerType(class_, registry, cache)
      return if class_.symbol.kind == "struct" then inner else registry.templateType("std::shared_ptr", [inner])
    }
    enum_: EnumType -> {
      return if enum_.symbol.native_ then registry.atom(nativeCppName(enum_.symbol)) else registry.atom(enum_.name, typeNamespace(enum_.symbol.module, registry.names))
    }
    interface_: InterfaceType -> {
      name := if interface_.typeArgs.length == 0 then interface_.name else concreteName(interface_.name, interface_.typeArgs, registry.names)
      return registry.atom(name, typeNamespace(interface_.symbol.module, registry.names))
    }
    function_: FunctionType -> {
      let arguments = [if carrierOf(function_.returnType, .Return).kind == .Void then registry.atom("void") else lowerCppType(function_.returnType, registry, cache)]
      for parameter of function_.params { arguments.push(lowerCppType(parameter.type_, registry, cache)) }
      return registry.intern("callback", "", arguments)
    }
    array: ArrayResolvedType -> { return registry.templateType("std::shared_ptr", [registry.templateType("std::vector", [lowerCppType(array.elementType, registry, cache)])]) }
    map: MapResolvedType -> { return registry.templateType("std::shared_ptr", [registry.templateType("doof::ordered_map", [lowerCppType(map.keyType, registry, cache), lowerCppType(map.valueType, registry, cache)])]) }
    set_: SetResolvedType -> { return registry.templateType("std::shared_ptr", [registry.templateType("doof::ordered_set", [lowerCppType(set_.elementType, registry, cache)])]) }
    stream: StreamResolvedType -> { return registry.atom(concreteName("Stream", [stream.elementType], registry.names)) }
    _: RangeResolvedType -> { return registry.atom("doof::Range") }
    _: JsonValueResolvedType -> { return registry.atom("doof::JsonValue") }
    result: ResultResolvedType -> { return registry.templateType("doof::Result", [lowerCppPayload(result.valueType, registry, cache), lowerCppPayload(result.errorType, registry, cache)]) }
    actor: ActorType -> { return registry.templateType("std::shared_ptr", [registry.templateType("doof::Actor", [lowerCppClassInnerType(actor.innerClass, registry, cache)])]) }
    promise: PromiseType -> { return registry.templateType("doof::Promise", [lowerCppPayload(promise.valueType, registry, cache)]) }
    tuple: TupleResolvedType -> {
      let arguments: CppType[] = []
      for element of tuple.elements { arguments.push(lowerCppType(element, registry, cache)) }
      return registry.templateType("std::tuple", arguments)
    }
    union_: UnionResolvedType -> {
      if union_.types.length == 0 { panic("Cannot emit empty resolved union") }
      carrier := carrierOf(union_)
      if carrier.naturalNullable {
        member := lowerCppType(carrier.member!, registry, cache)
        return if carrier.wrapsOptional then registry.templateType("std::optional", [member]) else member
      }
      let arguments: CppType[] = []
      if carrier.hasNone { arguments.push(registry.atom("std::monostate")) }
      for member of flattenCarrierMembers(union_.types) { if member.kind != "none" { arguments.push(lowerCppType(member, registry, cache)) } }
      return registry.templateType("std::variant", arguments)
    }
    weak_: WeakResolvedType -> { return lowerCppWeakType(weak_.inner, registry, cache) }
    _: NoneType -> { return registry.atom("std::monostate") }
    _: NeverType -> { return registry.atom("doof::Never") }
    _: UnknownType -> { panic("Cannot emit unresolved unknown type") }
    parameter: TypeParameterType -> { return registry.atom(parameter.name) }
    metadata: ClassMetadataResolvedType -> { return registry.templateType("doof::ClassMetadata", [lowerCppMetadataInnerType(metadata.classType, registry, cache)]) }
    reflection: MethodReflectionResolvedType -> { return registry.templateType("doof::MethodReflection", [lowerCppMetadataInnerType(reflection.classType, registry, cache)]) }
  }
  return registry.atom("void")
}

function lowerCppPayload(type_: ResolvedType, registry: CppTypeRegistry, cache: TypeLoweringGraph | none = none): CppType {
  return if carrierOf(type_, .Payload).kind == .Void then registry.atom("void") else lowerCppType(type_, registry, cache)
}

function lowerCppWeakType(inner: ResolvedType, registry: CppTypeRegistry, cache: TypeLoweringGraph | none = none): CppType {
  case inner {
    class_: ClassType -> { return registry.templateType("std::weak_ptr", [lowerCppClassInnerType(class_, registry, cache)]) }
    array: ArrayResolvedType -> { return registry.templateType("std::weak_ptr", [registry.templateType("std::vector", [lowerCppType(array.elementType, registry, cache)])]) }
    map: MapResolvedType -> { return registry.templateType("std::weak_ptr", [registry.templateType("doof::ordered_map", [lowerCppType(map.keyType, registry, cache), lowerCppType(map.valueType, registry, cache)])]) }
    set_: SetResolvedType -> { return registry.templateType("std::weak_ptr", [registry.templateType("doof::ordered_set", [lowerCppType(set_.elementType, registry, cache)])]) }
    union_: UnionResolvedType -> {
      let arguments: CppType[] = []
      for member of flattenCarrierMembers(union_.types) { if member.kind != "none" { arguments.push(lowerCppWeakType(member, registry, cache)) } }
      type_ := if arguments.length == 1 then arguments[0] else registry.templateType("std::variant", arguments)
      return if carrierOf(union_).hasNone then registry.templateType("std::optional", [type_]) else type_
    }
    _ -> { return registry.templateType("std::weak_ptr", [lowerCppType(inner, registry, cache)]) }
  }
  return registry.templateType("std::weak_ptr", [registry.atom("void")])
}

function lowerCppMetadataInnerType(owner: ResolvedType, registry: CppTypeRegistry, cache: TypeLoweringGraph | none = none): CppType {
  case owner {
    class_: ClassType -> { return lowerCppClassInnerType(class_, registry, cache) }
    parameter: TypeParameterType -> { return registry.templateType("doof::metadata_inner_t", [registry.atom(parameter.name)]) }
    _ -> { panic("Metadata owner must be a class or Reflectable type parameter") }
  }
  return registry.atom("void")
}

export function lowerCppClassInnerType(class_: ClassType, registry: CppTypeRegistry, cache: TypeLoweringGraph | none = none): CppType {
  if class_.typeArgs.length == 0 {
    return if class_.symbol.native_ then registry.atom(nativeCppName(class_.symbol)) else registry.atom(class_.name, typeNamespace(class_.symbol.module, registry.names))
  }
  if !class_.symbol.native_ { panic("Non-native generic class reached C++ type emission before monomorphization: " + class_.symbol.module + "::" + class_.name) }
  let arguments: CppType[] = []
  for argument of class_.typeArgs { arguments.push(lowerCppType(argument, registry, cache)) }
  return registry.templateType(nativeCppName(class_.symbol), arguments)
}

/** Borrows immutable parameters whose C++ carriers do not require Doof value-copy semantics. */
export function emitParameterType(resolvedType: ResolvedType, currentModulePath: string = "", names: ModuleNames = ModuleNames {}): string {
  emitted := emitType(resolvedType, currentModulePath, names)
  return if canBorrowParameter(resolvedType) then "const " + emitted + "&" else emitted
}

/** Applies parameter borrowing after contextual generic specialization selected the emitted carrier. */
export function borrowParameterType(resolvedType: ResolvedType, emittedType: string): string {
  return if canBorrowParameter(resolvedType) then "const " + emittedType + "&" else emittedType
}

export function canBorrowParameter(resolvedType: ResolvedType): bool {
  case resolvedType {
    primitive: PrimitiveType -> { return primitive.name == "string" }
    class_: ClassType -> { return class_.symbol.kind != "struct" }
    _: InterfaceType -> { return true }
    _: FunctionType -> { return true }
    _: ActorType -> { return true }
    _: PromiseType -> { return true }
    _: ArrayResolvedType -> { return true }
    _: MapResolvedType -> { return true }
    _: SetResolvedType -> { return true }
    _: StreamResolvedType -> { return true }
    _: JsonValueResolvedType -> { return true }
    result: ResultResolvedType -> {
      return !requiresParameterValueSemantics(result.valueType) && !requiresParameterValueSemantics(result.errorType)
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements { if requiresParameterValueSemantics(element) { return false } }
      return true
    }
    union_: UnionResolvedType -> {
      for member of union_.types { if requiresParameterValueSemantics(member) { return false } }
      return true
    }
    _: WeakResolvedType -> { return true }
    _: ClassMetadataResolvedType -> { return true }
    _: MethodReflectionResolvedType -> { return true }
    _ -> { return false }
  }
  return false
}

// Structs are direct C++ values whose mutable fields belong to the parameter's
// local copy. Generic parameters may specialize to structs, so retain their
// existing by-value ABI as well.
function requiresParameterValueSemantics(resolvedType: ResolvedType): bool {
  case resolvedType {
    class_: ClassType -> { return class_.symbol.kind == "struct" }
    _: TypeParameterType -> { return true }
    result: ResultResolvedType -> {
      return requiresParameterValueSemantics(result.valueType) || requiresParameterValueSemantics(result.errorType)
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements { if requiresParameterValueSemantics(element) { return true } }
      return false
    }
    union_: UnionResolvedType -> {
      for member of union_.types { if requiresParameterValueSemantics(member) { return true } }
      return false
    }
    _ -> { return false }
  }
  return false
}

export function emitClassInnerType(class_: ClassType, currentModulePath: string = "", names: ModuleNames = ModuleNames {}): string {
  return renderCppType(lowerCppClassInnerType(class_, CppTypeRegistry { names }), typeNamespace(currentModulePath, names))
}

function nativeCppName(symbol: Symbol): string {
  return "::" + (if symbol.nativeCppName == "" then symbol.name else symbol.nativeCppName)
}

function emitPrimitive(name: string): string {
  if name == "byte" { return "uint8_t" }
  if name == "int" { return "int32_t" }
  if name == "long" { return "int64_t" }
  if name == "float" { return "float" }
  if name == "double" { return "double" }
  if name == "string" { return "std::string" }
  if name == "char" { return "char32_t" }
  if name == "bool" { return "bool" }
  panic("Cannot emit unknown primitive type " + name)
  return "void"
}

/** Whether a checked union/interface dispatches through native variant arms. */
export function usesVariantRepresentation(type_: ResolvedType): bool {
  carrier := carrierOf(type_)
  return carrier.kind == .Variant && carrier.unionLike && !carrier.naturalNullable
}

/** Whether a union uses a natural nullable/optional carrier instead of variant. */
export function usesNullableSingleValueRepresentation(type_: ResolvedType): bool {
  return naturalNullableUnionMember(type_) != none
}

/** Compatibility query backed by the representation model. */
export function naturalNullableUnionMember(type_: ResolvedType): ResolvedType | none {
  return naturalCarrierMember(type_)
}
