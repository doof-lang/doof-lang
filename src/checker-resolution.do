// Type annotation, member, index, and callable-field resolution.

import { ActorType, ArrayResolvedType, Binding, ClassMetadataResolvedType, ClassType, EnumType, InterfaceType, FunctionType, MapResolvedType, MethodReflectionResolvedType, PrimitiveType, PromiseType, RangeResolvedType, ResolvedType, ResultResolvedType, SuccessResolvedType, FailureResolvedType, SetResolvedType, Symbol, StreamResolvedType, TupleResolvedType, UnionResolvedType, TypeParameterType, NeverType, UnknownType } from "./semantic"
import { AnalysisResult } from "./analyzer"
import { CheckedMember, ClassDeclaration, DotShorthand, EnumDeclaration, Expression, FunctionDeclaration, Identifier, InterfaceDeclaration, MemberExpression, Program, SourceSpan } from "./ast"
import { interfaceBoundReceiver, applyDeepReadonly, arrayType, classMetadataType, classType, functionType, joinTypes, jsonObjectType, jsonValueType, mapType, param, resultType, setType, noneType, primitive, promiseType, sameType, typeName, unionType, methodReflectionType, substituteTypeParams, unknownType } from "./checker-types"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization, interfaceJsonDiscriminator, interfaceJsonSerializationBlocker, isGeneratedJsonType, jsonUnionFieldBlocker } from "./json-semantics"

import { CheckerState } from "./checker-state"

import { deprecatedBuildReadonly, typeError } from "./checker-common"
import { classFieldBinding, containsString, resolveAnnotation, methodSignature, declarationFor } from "./checker-symbols"
import { classModuleFor, isAssignableWithInterfaces } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"
import { arrayMemberType } from "./checker-array-methods"
import { resolveType } from "./checker-annotations"

// Some checker phases need a member's type without performing a source-level
// access (for example, when synthesizing constructor parameters). Keep that
// lookup distinct from an explicit access so declaration spans cannot be
// reported against the module currently being checked.
export function resolveMember(state: CheckerState, object: ResolvedType, property: string, span: SourceSpan, validateVisibility: bool = true, declaredOnly: bool = false): CheckedMember {
  resolved := CheckedMember {}
  resolved.type_ = resolveMemberType(state, object, property, span, validateVisibility, declaredOnly, resolved)
  return resolved
}

// Identifier bindings already select a symbol. Explicit member expressions
// retain the selection produced while checking that expression.
export function resolveCalleeTarget(state: CheckerState, callee: Expression, calleeType: ResolvedType): CheckedMember {
  case callee {
    member: MemberExpression -> {
      if member.resolvedMember != none { return member.resolvedMember! }
    }
    dot: DotShorthand -> {
      if dot.resolvedMember != none { return dot.resolvedMember! }
    }
    identifier: Identifier -> {
      if identifier.resolvedBinding != none && identifier.resolvedBinding!.symbol != none {
        symbol := identifier.resolvedBinding!.symbol!
        target := declarationFor(state.result, symbol)
        if target != none {
          case target! {
            fn: FunctionDeclaration -> { return CheckedMember { type_: calleeType, function_: fn, modulePath: symbol.module } }
            _: ClassDeclaration -> {
              resolved := resolveMember(state, classType(symbol.name, symbol), identifier.name, identifier.span, false)
              resolved.type_ = calleeType
              return resolved
            }
            _ -> { }
          }
        }
      }
    }
    _ -> { }
  }
  return CheckedMember { type_: calleeType }
}

function recordMember(resolved: CheckedMember, owner: ResolvedType, modulePath: string, function_: FunctionDeclaration | none = none, field: bool = false, staticOwner: ClassDeclaration | none = none, instance: bool = true): none {
  resolved.owner = owner
  resolved.modulePath = modulePath
  resolved.function_ = function_
  resolved.field = field
  resolved.staticOwner = staticOwner
  resolved.instance = instance
}

/**
 * Resolves `T.name` against the static members of the interface bounding type
 * parameter `T`. Instance members of the bound are reached through values.
 */
export function resolveBoundStaticMember(state: CheckerState, object: ResolvedType, property: string): CheckedMember | none {
  if object.kind != "type-parameter" { return none }
  case interfaceBoundReceiver(object) {
    interfaceType_: InterfaceType -> {
      declaration := declarationFor(state.result, interfaceType_.symbol)
      if declaration == none { return none }
      case declaration! {
        interface_: InterfaceDeclaration -> {
          module := classModuleFor(state.result, interfaceType_.symbol)
          for field of interface_.staticFields {
            if field.name != property { continue }
            base := field.resolvedType ?? resolveAnnotation(field.type_, module, state.result, interface_.typeParams)
            selected := CheckedMember {}
            recordMember(selected, object, interfaceType_.symbol.module, none, true, none, false)
            selected.type_ = substituteTypeParams(if field.readonly_ && field.resolvedType == none then applyDeepReadonly(base) else base, interface_.typeParams, interfaceType_.typeArgs)
            return selected
          }
          for method of interface_.staticMethods {
            if method.name != property { continue }
            selected := CheckedMember {}
            recordMember(selected, object, interfaceType_.symbol.module, method, false, none, false)
            selected.type_ = substituteTypeParams(method.resolvedType ?? interfaceMethodSignature(state, method, interface_, interfaceType_.symbol), interface_.typeParams, interfaceType_.typeArgs)
            return selected
          }
        }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}

/** Signature of the compiler-provided `fromSerialValue(value, lenient = true)` decoder for `target`. */
export function serialDecodeType(target: ResolvedType): ResolvedType {
  return functionType([param("value", jsonValueType()), param("lenient", primitive("bool"), true)], resultType(target, primitive("string")))
}

export function memberType(state: CheckerState, object: ResolvedType, property: string, span: SourceSpan, validateVisibility: bool = true, declaredOnly: bool = false): ResolvedType {
  return resolveMember(state, object, property, span, validateVisibility, declaredOnly).type_!
}

function resolveMemberType(state: CheckerState, object: ResolvedType, property: string, span: SourceSpan, validateVisibility: bool, declaredOnly: bool, selection: CheckedMember): ResolvedType {
  case object {
    primitive_: PrimitiveType -> { return if primitive_.name == "string" then stringMemberType(property) else unknownType() }
    function_: FunctionType -> {
      if property == "dispatch" && function_.returnType.kind != "none" {
        typeError(state, "Method \"dispatch\" is only available on none-returning callbacks", span)
        return unknownType()
      }
      return case property {
        "call" -> function_,
        "post" -> functionType(function_.params, promiseType(function_.returnType)),
        "dispatch" -> functionType(function_.params, noneType()),
        _ -> unknownType()
      }
    }
    union: UnionResolvedType -> { return unionMemberType(state, union, property, span, validateVisibility, declaredOnly, selection) }
    array: ArrayResolvedType -> { return arrayMemberType(state, array, property, span) }
    map: MapResolvedType -> { return mapMemberType(state, map, property, span) }
    set: SetResolvedType -> { return setMemberType(state, set, property, span) }
    result: ResultResolvedType -> {
      if property == "unwrapOr" && result.valueType.kind == "none" {
        typeError(state, "Method \"unwrapOr\" is not available on Result<void, E>", span)
        return unknownType()
      }
      return case property {
        "isSuccess" | "isFailure" -> functionType([], primitive("bool")),
        "unwrapOr" -> functionType([param("defaultValue", result.valueType)], result.valueType),
        _ -> unknownType()
      }
    }
    success: SuccessResolvedType -> { return if property == "value" && success.valueType.kind != "none" then success.valueType else unknownType() }
    failure: FailureResolvedType -> { return if property == "error" && failure.errorType.kind != "none" then failure.errorType else unknownType() }
    stream: StreamResolvedType -> {
      return case property {
        "next" -> functionType([], primitive("bool")),
        "value" -> functionType([], stream.elementType),
        _ -> unknownType()
      }
    }
    tuple: TupleResolvedType -> {
      for i of 0..<tuple.elements.length {
        if property == "_" + string(i + 1) { return tuple.elements[i] }
      }
      return unknownType()
    }
    _: RangeResolvedType -> { return if property == "lowerBound" || property == "upperBound" then primitive("int") else unknownType() }
    actor: ActorType -> {
      resolved := resolveMemberType(state, actor.innerClass, property, span, validateVisibility, declaredOnly, selection)
      if validateVisibility && selection.field && selection.instance {
        typeError(state, "Cannot access actor field '" + property + "' directly; use an actor method to read or update actor state", span)
        return unknownType()
      }
      return resolved
    }
    promise: PromiseType -> {
      settled := resultType(promise.valueType, primitive("string"))
      return case property {
        "get" -> functionType([], settled),
        "onComplete" -> functionType([param("callback", functionType([param("result", settled)], noneType()))], noneType()),
        _ -> unknownType()
      }
    }
    parameter: TypeParameterType -> { return typeParameterMemberType(state, parameter, property, span, validateVisibility, selection) }
    metadata: ClassMetadataResolvedType -> {
      return case property {
        "name" | "description" -> primitive("string"),
        "methods" -> arrayType(methodReflectionType(metadata.classType)),
        "defs" -> unionType([jsonValueType(), noneType()]),
        "invoke" -> functionType([param("instance", metadata.classType), param("methodName", primitive("string")), param("params", jsonValueType())], resultType(jsonValueType(), jsonValueType())),
        _ -> unknownType()
      }
    }
    reflection: MethodReflectionResolvedType -> {
      return case property {
        "name" | "description" -> primitive("string"),
        "inputSchema" | "outputSchema" -> jsonValueType(),
        "invoke" -> functionType([param("instance", reflection.classType), param("params", jsonValueType())], resultType(jsonValueType(), jsonValueType())),
        _ -> unknownType()
      }
    }
    enum_: EnumType -> { return enumMemberType(state, enum_, property) }
    class_: ClassType -> { return classMemberType(state, class_, property, span, validateVisibility, selection) }
    interfaceType_: InterfaceType -> { return interfaceMemberType(state, interfaceType_, property, span, declaredOnly, selection) }
    _ -> { }
  }
  return unknownType()
}

function stringMemberType(property: string): ResolvedType {
  string_ := primitive("string")
  int_ := primitive("int")
  return case property {
    "length" -> int_,
    "startsWith" | "endsWith" | "contains" -> functionType([param("value", string_)], primitive("bool")),
    "indexOf" -> functionType([param("value", string_)], int_),
    "substring" -> functionType([param("start", int_), param("end", int_, true)], string_),
    "replace" | "replaceAll" -> functionType([param("oldValue", string_), param("newValue", string_)], string_),
    "trim" | "trimStart" | "toLowerCase" | "toUpperCase" -> functionType([], string_),
    "trimEnd" -> functionType([param("suffix", primitive("char"), true)], string_),
    "repeat" -> functionType([param("count", int_)], string_),
    "slice" -> functionType([param("start", int_)], string_),
    "charAt" -> functionType([param("index", int_)], primitive("char")),
    "padStart" | "padEnd" -> functionType([param("length", int_), param("fill", primitive("char"), true)], string_),
    "split" -> functionType([param("separator", string_)], arrayType(string_, true)),
    _ -> unknownType()
  }
}

// A member of a union is available only when every non-none arm provides it;
// the selection keeps only the declaration facts all arms agree on.
function unionMemberType(state: CheckerState, union: UnionResolvedType, property: string, span: SourceSpan, validateVisibility: bool, declaredOnly: bool, selection: CheckedMember): ResolvedType {
  let resolved: ResolvedType | none = none
  for member of union.types {
    if member.kind == "none" { continue }
    arm := CheckedMember {}
    memberValue := resolveMemberType(state, member, property, span, validateVisibility, declaredOnly, arm)
    if resolved == none {
      recordMember(selection, member, arm.modulePath, arm.function_, arm.field, arm.staticOwner, arm.instance)
    } else {
      if selection.function_ != arm.function_ || selection.modulePath != arm.modulePath { selection.function_ = none; selection.modulePath = "" }
      selection.field = selection.field && arm.field
      selection.instance = selection.instance && arm.instance
      if selection.staticOwner != arm.staticOwner { selection.staticOwner = none }
    }
    if memberValue.kind == "unknown" { return unknownType() }
    resolved = if resolved == none then memberValue else joinTypes(resolved!, memberValue)
  }
  return resolved ?? unknownType()
}

// Readonly collections reject mutators and the conversions that consume or
// re-wrap a mutable collection.
function rejectReadonlyCollectionMember(state: CheckerState, readonly_: bool, kind: string, mutators: string[], property: string, span: SourceSpan): bool {
  if !readonly_ { return false }
  if !containsString(mutators, property) && property != "buildReadonly" && property != "drainToReadonly" && property != "cloneReadonly" { return false }
  typeError(state, "Method \"" + property + "\" is not available on readonly " + kind, span)
  return true
}

function mapMemberType(state: CheckerState, map: MapResolvedType, property: string, span: SourceSpan): ResolvedType {
  if rejectReadonlyCollectionMember(state, map.readonly_, "map", ["set", "delete"], property, span) { return unknownType() }
  if property == "buildReadonly" { deprecatedBuildReadonly(state, span) }
  key := map.keyType
  value := map.valueType
  return case property {
    "size" -> primitive("int"),
    "has" -> functionType([param("key", key)], primitive("bool")),
    "get" -> functionType([param("key", key)], resultType(value, primitive("string"))),
    "set" -> functionType([param("key", key), param("value", value)], noneType()),
    "delete" -> functionType([param("key", key)], noneType()),
    "keys" -> functionType([], arrayType(key)),
    "values" -> functionType([], arrayType(value)),
    "buildReadonly" | "drainToReadonly" | "cloneReadonly" -> functionType([], mapType(key, value, true)),
    "cloneMutable" -> functionType([], mapType(key, value)),
    _ -> unknownType()
  }
}

function setMemberType(state: CheckerState, set: SetResolvedType, property: string, span: SourceSpan): ResolvedType {
  if rejectReadonlyCollectionMember(state, set.readonly_, "set", ["add", "delete"], property, span) { return unknownType() }
  if property == "buildReadonly" { deprecatedBuildReadonly(state, span) }
  element := set.elementType
  return case property {
    "size" -> primitive("int"),
    "has" -> functionType([param("value", element)], primitive("bool")),
    "add" | "delete" -> functionType([param("value", element)], noneType()),
    "values" -> functionType([], arrayType(element)),
    "buildReadonly" | "drainToReadonly" | "cloneReadonly" -> functionType([], setType(element, true)),
    "cloneMutable" -> functionType([], setType(element)),
    _ -> unknownType()
  }
}

function typeParameterMemberType(state: CheckerState, parameter: TypeParameterType, property: string, span: SourceSpan, validateVisibility: bool, selection: CheckedMember): ResolvedType {
  bound := interfaceBoundReceiver(parameter)
  if bound.kind == "interface" {
    declared := resolveMemberType(state, bound, property, span, validateVisibility, true, selection)
    // JSON members are compiler-provided, so an interface bound implies
    // them without declaring them; instantiation validates the argument.
    if declared.kind != "unknown" { return declared }
    return case property {
      "toSerialObject" -> functionType([], jsonObjectType()),
      "fromSerialValue" -> serialDecodeType(parameter),
      _ -> declared
    }
  }
  required := case property {
    "metadata" -> "Reflectable",
    "toSerialObject" | "fromSerialValue" -> "Serializable",
    _ -> ""
  }
  if required == "" { return unknownType() }
  if parameter.constraintName != required {
    memberKind := if property == "toSerialObject" then "Member" else "Static member"
    typeError(state, memberKind + " \"" + property + "\" requires type parameter \"" + parameter.name + "\" to be constrained by " + required, span)
    return unknownType()
  }
  return case property {
    "metadata" -> classMetadataType(parameter),
    "toSerialObject" -> functionType([], jsonObjectType()),
    _ -> serialDecodeType(parameter)
  }
}

function enumMemberType(state: CheckerState, enum_: EnumType, property: string): ResolvedType {
  let declaration: EnumDeclaration | none = none
  found := declarationFor(state.result, enum_.symbol)
  if found != none {
    case found! {
      enumDeclaration: EnumDeclaration -> { declaration = enumDeclaration }
      _ -> { }
    }
  }
  backingType := if declaration != none && declaration!.backingKind == "string" then primitive("string") else primitive("int")
  let resolved: ResolvedType = case property {
    "name" -> primitive("string"),
    "value" -> backingType,
    "toSerialValue" -> functionType([], jsonValueType()),
    "values" -> functionType([], arrayType(enum_, true)),
    "fromName" -> functionType([param("value", primitive("string"))], unionType([enum_, noneType()])),
    "fromValue" -> functionType([param("value", backingType)], unionType([enum_, noneType()])),
    "fromSerialValue" -> serialDecodeType(enum_),
    _ -> unknownType()
  }
  if resolved.kind != "unknown" || declaration == none { return resolved }
  for variant of declaration!.variants { if variant.name == property { return enum_ } }
  return unknownType()
}

function isGeneratedMember(property: string): bool {
  return property == "metadata" || property == "toSerialObject" || property == "fromSerialValue"
}

function classMemberType(state: CheckerState, class_: ClassType, property: string, span: SourceSpan, validateVisibility: bool, selection: CheckedMember): ResolvedType {
  if class_.name == "SourceLocation" && class_.symbol.module == "<builtin>" {
    return case property {
      "fileName" | "functionName" -> primitive("string"),
      "line" -> primitive("int"),
      _ -> unknownType()
    }
  }
  declaration := declarationFor(state.result, class_.symbol)
  if declaration == none { return unknownType() }
  case declaration! {
    classDeclaration: ClassDeclaration -> {
      if isGeneratedMember(property) { return classGeneratedMemberType(state, class_, classDeclaration, property, span, selection) }
      for field of classDeclaration.fields {
        for name of field.names {
          if name != property { continue }
          recordMember(selection, class_, class_.symbol.module, none, true, if field.static_ then classDeclaration else none, !field.static_)
          fieldType := if field.resolvedType != none then field.resolvedType! else if field.type_ != none then resolveType(state, field.type_!, state.info!, state.moduleScope!) else unknownType()
          if validateVisibility && field.private_ && class_.symbol.module != state.info!.path {
            typeError(state, "Field '" + property + "' is private to module '" + class_.symbol.module + "'", span)
          }
          return substituteTypeParams(fieldType, classDeclaration.typeParams, class_.typeArgs)
        }
      }
      for method of classDeclaration.methods {
        if method.name != property { continue }
        recordMember(selection, class_, class_.symbol.module, method, false, if method.static_ then classDeclaration else none, !method.static_)
        methodType := method.resolvedType ?? methodSignature(method, classModuleFor(state.result, class_.symbol), state.result, class_.symbol.typeParams)
        if validateVisibility && method.private_ && class_.symbol.module != state.info!.path {
          typeError(state, "Method '" + property + "' is private to module '" + class_.symbol.module + "'", span)
        }
        return substituteTypeParams(methodType, classDeclaration.typeParams, class_.typeArgs)
      }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields { if field.name == property { recordMember(selection, class_, class_.symbol.module, none, true); return field.resolvedType ?? resolveType(state, field.type_, state.info!, state.moduleScope!) } }
      for method of interface_.methods { if method.name == property { recordMember(selection, class_, class_.symbol.module, method); return method.resolvedType ?? methodSignature(method, classModuleFor(state.result, class_.symbol), state.result, class_.symbol.typeParams) } }
    }
    _ -> { }
  }
  return unknownType()
}

/** Resolves the compiler-provided `metadata`, `toSerialObject`, and `fromSerialValue` members of a class. */
function classGeneratedMemberType(state: CheckerState, class_: ClassType, declaration: ClassDeclaration, property: string, span: SourceSpan, selection: CheckedMember): ResolvedType {
  programs := jsonPrograms(state.result)
  if property == "metadata" {
    if !validateClassMetadata(state, declaration, programs, span) { return unknownType() }
    declaration.needsMetadata = true
    recordMember(selection, class_, class_.symbol.module, none, false, declaration, false)
    return classMetadataType(class_)
  }
  deserialize := property == "fromSerialValue"
  if !deserialize && canGenerateJsonSerialization(declaration, programs) { return functionType([], jsonObjectType()) }
  if deserialize && canGenerateJsonDeserialization(declaration, programs) {
    recordMember(selection, class_, class_.symbol.module, none, false, declaration, false)
    return serialDecodeType(class_)
  }
  blocker := jsonUnionFieldBlocker(declaration, programs, deserialize)
  reason := if blocker == none then "" else " (" + blocker! + ")"
  typeError(state, "Type \"" + declaration.name + "\" does not support automatic JSON " + (if deserialize then "deserialization" else "serialization") + reason, span)
  return unknownType()
}

// Metadata exposes every public instance method through JSON invocation, so
// each parameter and success value must itself be JSON-serializable.
function validateClassMetadata(state: CheckerState, declaration: ClassDeclaration, programs: Program[], span: SourceSpan): bool {
  if declaration.typeParams.length > 0 {
    typeError(state, "Metadata is not available on generic type \"" + declaration.name + "\"", span)
    return false
  }
  if !canGenerateJsonSerialization(declaration, programs) || !canGenerateJsonDeserialization(declaration, programs) {
    typeError(state, "Type \"" + declaration.name + "\" is not eligible for metadata because it does not support automatic JSON generation", span)
    return false
  }
  let valid = true
  for method of declaration.methods {
    if method.private_ || method.static_ { continue }
    for parameter of method.params {
      if parameter.resolvedType != none && !isGeneratedJsonType(parameter.resolvedType!, programs) {
        typeError(state, "Parameter \"" + parameter.name + "\" of method \"" + method.name + "\" is not JSON-serializable", parameter.span)
        valid = false
      }
    }
    if method.resolvedType == none { continue }
    case method.resolvedType! {
      function_: FunctionType -> {
        let successType = function_.returnType
        case successType {
          result: ResultResolvedType -> { successType = result.valueType }
          _ -> { }
        }
        if successType.kind != "none" && !isGeneratedJsonType(successType, programs) {
          typeError(state, "Return type of method \"" + method.name + "\" is not JSON-serializable", method.span)
          valid = false
        }
      }
      _ -> { }
    }
  }
  return valid
}

function interfaceMemberType(state: CheckerState, interfaceType_: InterfaceType, property: string, span: SourceSpan, declaredOnly: bool, selection: CheckedMember): ResolvedType {
  declaration := declarationFor(state.result, interfaceType_.symbol)
  if declaration == none { return unknownType() }
  case declaration! {
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields {
        if field.name != property { continue }
        recordMember(selection, interfaceType_, interfaceType_.symbol.module, none, true)
        fieldType := field.resolvedType ?? resolveAnnotation(field.type_, classModuleFor(state.result, interfaceType_.symbol), state.result, interface_.typeParams)
        return substituteTypeParams(if field.readonly_ then applyDeepReadonly(fieldType) else fieldType, interface_.typeParams, interfaceType_.typeArgs)
      }
      for method of interface_.methods {
        if method.name != property { continue }
        recordMember(selection, interfaceType_, interfaceType_.symbol.module, method, false, none, !method.static_)
        methodType := method.resolvedType ?? interfaceMethodSignature(state, method, interface_, interfaceType_.symbol)
        return substituteTypeParams(methodType, interface_.typeParams, interfaceType_.typeArgs)
      }
      if declaredOnly || (property != "toSerialObject" && property != "fromSerialValue") { return unknownType() }
      return interfaceGeneratedMemberType(state, interfaceType_, interface_, property, span, selection)
    }
    _ -> { }
  }
  return unknownType()
}

/** Resolves the compiler-provided `toSerialObject` and `fromSerialValue` members of an interface. */
function interfaceGeneratedMemberType(state: CheckerState, interfaceType_: InterfaceType, interface_: InterfaceDeclaration, property: string, span: SourceSpan, selection: CheckedMember): ResolvedType {
  deserialize := property == "fromSerialValue"
  if interface_.typeParams.length > 0 {
    typeError(state, "Automatic JSON " + (if deserialize then "deserialization" else "serialization") + " is not available on generic interface \"" + interface_.name + "\"", span)
    return unknownType()
  }
  programs := jsonPrograms(state.result)
  if deserialize {
    // Without implementations no value can be decoded; the generated decoder
    // always fails, so library helpers still check on their own.
    if interfaceJsonDiscriminator(interface_, programs) == none && interfaceType_.symbol.implementations.length > 0 {
      typeError(state, "Cannot deserialize interface \"" + interface_.name + "\": all implementing classes must share a literal-valued string field with distinct values (e.g. kind: \"variant\")", span)
      return unknownType()
    }
    return serialDecodeType(interfaceType_)
  }
  blocker := interfaceJsonSerializationBlocker(interface_, programs)
  if blocker != none {
    typeError(state, "Cannot serialize interface \"" + interface_.name + "\": implementing class \"" + blocker! + "\" does not support automatic JSON serialization", span)
    return unknownType()
  }
  recordMember(selection, interfaceType_, interfaceType_.symbol.module, none, false, none, true)
  return functionType([], jsonObjectType())
}

export function fieldAssignmentBinding(state: CheckerState, object: ResolvedType, property: string, fieldType: ResolvedType, span: SourceSpan): Binding | none {
  case interfaceBoundReceiver(object) {
    union_: UnionResolvedType -> {
      let selected: Binding | none = none
      for member of union_.types {
        if member.kind == "none" { continue }
        concreteType := memberType(state, member, property, span, false)
        if !sameType(concreteType, fieldType) { return none }
        binding := fieldAssignmentBinding(state, member, property, concreteType, span)
        if binding == none { return none }
        if selected == none || !binding!.mutable { selected = binding }
      }
      return selected
    }
    actor: ActorType -> { return fieldAssignmentBinding(state, actor.innerClass, property, fieldType, span) }
    class_: ClassType -> {
      declaration := declarationFor(state.result, class_.symbol)
      if declaration == none { return none }
      case declaration! {
        classDeclaration: ClassDeclaration -> {
          for field of classDeclaration.fields {
            for name of field.names {
              if name == property { return classFieldBinding(field, name, classDeclaration, fieldType, class_.symbol.module, class_.symbol) }
            }
          }
        }
        _ -> { }
      }
    }
    interfaceType_: InterfaceType -> {
      declaration := declarationFor(state.result, interfaceType_.symbol)
      if declaration == none { return none }
      case declaration! {
        interface_: InterfaceDeclaration -> {
          for field of interface_.fields {
            if field.name == property {
              return Binding {
                name: property,
                kind: "field",
                type_: fieldType,
                mutable: field.let_,
                span: checkerSemanticSpan(field.span),
                module: interfaceType_.symbol.module,
                symbol: interfaceType_.symbol,
                fieldMode: if field.readonly_ then "readonly" else if field.let_ then "let" else "implicit",
                fieldOwner: interface_.name,
              }
            }
          }
        }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}

export function jsonPrograms(result: AnalysisResult): Program[] {
  let programs: Program[] = []
  for module of result.modules { programs.push(module.program) }
  return programs
}

export function indexType(state: CheckerState, object: ResolvedType, index: ResolvedType, span: SourceSpan): ResolvedType {
  case object {
    array: ArrayResolvedType -> {
      if !isAssignableWithInterfaces(state.result, index, primitive("int")) && typeName(index) != "unknown" { typeError(state, "Index must be an int", span) }
      return array.elementType
    }
    map: MapResolvedType -> {
      if !isAssignableWithInterfaces(state.result, index, map.keyType) && typeName(index) != "unknown" { typeError(state, "Invalid map key type", span) }
      return map.valueType
    }
    _: TupleResolvedType -> {
      typeError(state, "Tuples cannot be indexed; access elements with '._1', '._2', ...", span)
      return unknownType()
    }
    primitive_: PrimitiveType -> {
      if primitive_.name == "string" {
        if !isAssignableWithInterfaces(state.result, index, primitive("int")) && typeName(index) != "unknown" { typeError(state, "Index must be an int", span) }
        return primitive("char")
      }
    }
    union_: UnionResolvedType -> {
      for member of union_.types {
        if member.kind == "none" {
          typeError(state, "Cannot index possibly-none value of type \"" + typeName(object) + "\"; use '?[]' or narrow it first", span)
          return unknownType()
        }
      }
    }
    _: UnknownType -> { return unknownType() }
    _: NeverType -> { return unknownType() }
    _ -> { }
  }
  typeError(state, "Type \"" + typeName(object) + "\" cannot be indexed", span)
  return unknownType()
}

function interfaceMethodSignature(state: CheckerState, method: FunctionDeclaration, owner: InterfaceDeclaration, symbol: Symbol): ResolvedType {
  return methodSignature(method, classModuleFor(state.result, symbol), state.result, owner.typeParams)
}
