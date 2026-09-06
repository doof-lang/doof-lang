// Type annotation, member, index, and callable-field resolution.

import { ActorType, ArrayResolvedType, Binding, ClassMetadataResolvedType, ClassType, EnumType, InterfaceType, FunctionParamType, FunctionType, MapResolvedType, MethodReflectionResolvedType, PrimitiveType, PromiseType, RangeResolvedType, ResolvedType, ResultResolvedType, Scope, SetResolvedType, Symbol, StreamResolvedType, TupleResolvedType, UnionResolvedType, TypeParameterType } from "./semantic"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import { CheckedMember, ClassDeclaration, EnumDeclaration, Expression, FunctionDeclaration, Identifier, InterfaceDeclaration, MemberExpression, Program, SourceSpan, TypeAnnotation, Parameter, TypeParameterConstraint } from "./ast"
import { interfaceBoundReceiver, applyDeepReadonly, arrayType, classMetadataType, classType, functionType, joinTypes, jsonObjectType, jsonValueType, mapType, resultType, setType, noneType, primitive, promiseType, sameType, typeName, unionType, methodReflectionType, substituteTypeParams, typeParameter, unknownType } from "./checker-types"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization, interfaceJsonDiscriminator, isGeneratedJsonType } from "./json-semantics"

import { CheckerState } from "./checker-state"

import { deprecatedBuildReadonly, typeError } from "./checker-common"
import { resolveAnnotation, methodSignature, declarationFor } from "./checker-symbols"
import { classModuleFor, isAssignableWithInterfaces } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"

import { resolveCheckedAnnotation, validateAnnotationConstraints, decorateAnnotationType } from "./checker-annotations"

export function resolveType(state: CheckerState, annotation: TypeAnnotation, module: ModuleInfo, scope: Scope, validateConstraints: bool = true): ResolvedType {
  return resolveCheckedAnnotation(state, annotation, module, scope, validateConstraints)
}

export function validateTypeArgumentConstraints(state: CheckerState, names: string[], constraints: TypeParameterConstraint[], arguments: ResolvedType[], span: SourceSpan, module: ModuleInfo, outer: Scope, ownerNames: string[] = [], ownerArguments: ResolvedType[] = []): none {
  validateAnnotationConstraints(state, names, constraints, arguments, span, module, outer, ownerNames, ownerArguments)
}

export function decorateType(state: CheckerState, annotation: TypeAnnotation, resolvedType: ResolvedType): ResolvedType {
  return decorateAnnotationType(state, annotation, resolvedType)
}

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

export function memberType(state: CheckerState, object: ResolvedType, property: string, span: SourceSpan, validateVisibility: bool = true, declaredOnly: bool = false): ResolvedType {
  return resolveMember(state, object, property, span, validateVisibility, declaredOnly).type_!
}

function resolveMemberType(state: CheckerState, object: ResolvedType, property: string, span: SourceSpan, validateVisibility: bool, declaredOnly: bool, selection: CheckedMember): ResolvedType {
  if typeName(object) == "string" {
    if property == "length" { return primitive("int") }
    if property == "startsWith" || property == "endsWith" || property == "contains" { return functionType([FunctionParamType { name: "value", type_: primitive("string"), hasDefault: false }], primitive("bool")) }
    if property == "indexOf" { return functionType([FunctionParamType { name: "value", type_: primitive("string"), hasDefault: false }], primitive("int")) }
    if property == "substring" { return functionType([FunctionParamType { name: "start", type_: primitive("int"), hasDefault: false }, FunctionParamType { name: "end", type_: primitive("int"), hasDefault: true }], primitive("string")) }
    if property == "replaceAll" { return functionType([FunctionParamType { name: "oldValue", type_: primitive("string"), hasDefault: false }, FunctionParamType { name: "newValue", type_: primitive("string"), hasDefault: false }], primitive("string")) }
    if property == "trim" { return functionType([], primitive("string")) }
    if property == "trimStart" { return functionType([], primitive("string")) }
    if property == "trimEnd" { return functionType([FunctionParamType { name: "suffix", type_: primitive("char"), hasDefault: true }], primitive("string")) }
    if property == "toLowerCase" || property == "toUpperCase" { return functionType([], primitive("string")) }
    if property == "repeat" { return functionType([FunctionParamType { name: "count", type_: primitive("int"), hasDefault: false }], primitive("string")) }
    if property == "slice" { return functionType([FunctionParamType { name: "start", type_: primitive("int"), hasDefault: false }], primitive("string")) }
    if property == "charAt" { return functionType([FunctionParamType { name: "index", type_: primitive("int"), hasDefault: false }], primitive("char")) }
    if property == "padStart" || property == "padEnd" { return functionType([FunctionParamType { name: "length", type_: primitive("int"), hasDefault: false }, FunctionParamType { name: "fill", type_: primitive("char"), hasDefault: true }], primitive("string")) }
    if property == "split" { return functionType([FunctionParamType { name: "separator", type_: primitive("string"), hasDefault: false }], arrayType(primitive("string"), true)) }
  }
  case object {
    function_: FunctionType -> {
      if property == "call" { return function_ }
      if property == "post" { return functionType(function_.params, promiseType(function_.returnType)) }
      if property == "dispatch" {
        if function_.returnType.kind != "none" { typeError(state, "Method \"dispatch\" is only available on none-returning callbacks", span); return unknownType() }
        return functionType(function_.params, noneType())
      }
      return unknownType()
    }
    union: UnionResolvedType -> {
      let resolved: ResolvedType | none = none
      let first = true
      for member of union.types {
        if member.kind == "none" { continue }
        arm := CheckedMember {}
        memberValue := resolveMemberType(state, member, property, span, validateVisibility, declaredOnly, arm)
        if first {
          recordMember(selection, member, arm.modulePath, arm.function_, arm.field, arm.staticOwner, arm.instance)
        } else {
          if selection.function_ != arm.function_ || selection.modulePath != arm.modulePath { selection.function_ = none; selection.modulePath = "" }
          selection.field = selection.field && arm.field
          selection.instance = selection.instance && arm.instance
          if selection.staticOwner != arm.staticOwner { selection.staticOwner = none }
        }
        first = false
        if memberValue.kind == "unknown" { return unknownType() }
        resolved = if resolved == none then memberValue else joinTypes(resolved!, memberValue)
      }
      if resolved != none { return resolved! }
      return unknownType()
    }
    array: ArrayResolvedType -> {
      if property == "length" { return primitive("int") }
      if array.readonly_ && (property == "push" || property == "reserve" || property == "pop" || property == "takeFirstCompleted") {
        typeError(state, "Method \"" + property + "\" is not available on readonly array", span)
        return unknownType()
      }
      if property == "push" { return functionType([FunctionParamType { name: "value", type_: array.elementType, hasDefault: false }], noneType()) }
      if property == "contains" { return functionType([FunctionParamType { name: "value", type_: array.elementType, hasDefault: false }], primitive("bool")) }
      if property == "indexOf" { return functionType([FunctionParamType { name: "value", type_: array.elementType, hasDefault: false }], primitive("int")) }
      if property == "reserve" { return functionType([FunctionParamType { name: "capacity", type_: primitive("int"), hasDefault: false }], noneType()) }
      if property == "pop" { return functionType([], resultType(array.elementType, primitive("string"))) }
      if property == "takeFirstCompleted" {
        case array.elementType {
          promise: PromiseType -> { return functionType([], resultType(promise.valueType, primitive("string"))) }
          _ -> { return unknownType() }
        }
      }
      if property == "some" || property == "every" {
        predicate := functionType([FunctionParamType { name: "it", type_: array.elementType, hasDefault: false }], primitive("bool"))
        return functionType([FunctionParamType { name: "predicate", type_: predicate, hasDefault: false }], primitive("bool"))
      }
      if property == "filter" {
        predicate := functionType([FunctionParamType { name: "it", type_: array.elementType, hasDefault: false }], primitive("bool"))
        return functionType([FunctionParamType { name: "predicate", type_: predicate, hasDefault: false }], arrayType(array.elementType, array.readonly_))
      }
      if property == "map" {
        mapped := typeParameter("U")
        mapper := functionType([FunctionParamType { name: "it", type_: array.elementType, hasDefault: false }], mapped)
        return functionType([FunctionParamType { name: "mapper", type_: mapper, hasDefault: false }], arrayType(mapped, array.readonly_), ["U"])
      }
      if property == "slice" { return functionType([FunctionParamType { name: "start", type_: primitive("int"), hasDefault: false }, FunctionParamType { name: "end", type_: primitive("int"), hasDefault: false }], arrayType(array.elementType, array.readonly_)) }
      if array.readonly_ && (property == "buildReadonly" || property == "drainToReadonly" || property == "cloneReadonly") {
        typeError(state, "Method \"" + property + "\" is not available on readonly array", span)
        return unknownType()
      }
      if property == "buildReadonly" { deprecatedBuildReadonly(state, span); return functionType([], arrayType(array.elementType, true)) }
      if property == "drainToReadonly" || property == "cloneReadonly" { return functionType([], arrayType(array.elementType, true)) }
      if property == "cloneMutable" { return functionType([], arrayType(array.elementType)) }
      return unknownType()
    }
    map: MapResolvedType -> {
      if property == "size" { return primitive("int") }
      if property == "has" { return functionType([FunctionParamType { name: "key", type_: map.keyType, hasDefault: false }], primitive("bool")) }
      if property == "get" { return functionType([FunctionParamType { name: "key", type_: map.keyType, hasDefault: false }], resultType(map.valueType, primitive("string"))) }
      if map.readonly_ && (property == "set" || property == "delete") {
        typeError(state, "Method \"" + property + "\" is not available on readonly map", span)
        return unknownType()
      }
      if property == "set" { return functionType([FunctionParamType { name: "key", type_: map.keyType, hasDefault: false }, FunctionParamType { name: "value", type_: map.valueType, hasDefault: false }], noneType()) }
      if property == "delete" { return functionType([FunctionParamType { name: "key", type_: map.keyType, hasDefault: false }], noneType()) }
      if property == "keys" { return functionType([], arrayType(map.keyType)) }
      if property == "values" { return functionType([], arrayType(map.valueType)) }
      if map.readonly_ && (property == "buildReadonly" || property == "drainToReadonly" || property == "cloneReadonly") {
        typeError(state, "Method \"" + property + "\" is not available on readonly map", span)
        return unknownType()
      }
      if property == "buildReadonly" { deprecatedBuildReadonly(state, span); return functionType([], mapType(map.keyType, map.valueType, true)) }
      if property == "drainToReadonly" || property == "cloneReadonly" { return functionType([], mapType(map.keyType, map.valueType, true)) }
      if property == "cloneMutable" { return functionType([], mapType(map.keyType, map.valueType)) }
      return unknownType()
    }
    set: SetResolvedType -> {
      if property == "size" { return primitive("int") }
      if property == "has" { return functionType([FunctionParamType { name: "value", type_: set.elementType, hasDefault: false }], primitive("bool")) }
      if set.readonly_ && property == "add" { typeError(state, "Method \"add\" is not available on readonly set", span); return unknownType() }
      if property == "add" { return functionType([FunctionParamType { name: "value", type_: set.elementType, hasDefault: false }], noneType()) }
      if set.readonly_ && property == "delete" { typeError(state, "Method \"delete\" is not available on readonly set", span); return unknownType() }
      if property == "delete" { return functionType([FunctionParamType { name: "value", type_: set.elementType, hasDefault: false }], noneType()) }
      if property == "values" { return functionType([], arrayType(set.elementType)) }
      if set.readonly_ && (property == "buildReadonly" || property == "drainToReadonly" || property == "cloneReadonly") {
        typeError(state, "Method \"" + property + "\" is not available on readonly set", span)
        return unknownType()
      }
      if property == "buildReadonly" { deprecatedBuildReadonly(state, span); return functionType([], setType(set.elementType, true)) }
      if property == "drainToReadonly" || property == "cloneReadonly" { return functionType([], setType(set.elementType, true)) }
      if property == "cloneMutable" { return functionType([], setType(set.elementType)) }
      return unknownType()
    }
    result: ResultResolvedType -> {
      if property == "value" { return result.valueType }
      if property == "error" { return result.errorType }
      if property == "isSuccess" || property == "isFailure" { return functionType([], primitive("bool")) }
      if property == "unwrapOr" {
        if result.valueType.kind == "none" {
          typeError(state, "Method \"unwrapOr\" is not available on Result<void, E>", span)
          return unknownType()
        }
        return functionType([
          FunctionParamType { name: "defaultValue", type_: result.valueType, hasDefault: false },
        ], result.valueType)
      }
      return unknownType()
    }
    stream: StreamResolvedType -> {
      if property == "next" { return functionType([], primitive("bool")) }
      if property == "value" { return functionType([], stream.elementType) }
      return unknownType()
    }
    tuple: TupleResolvedType -> {
      for i of 0..<tuple.elements.length {
        if property == "_" + string(i + 1) { return tuple.elements[i] }
      }
      return unknownType()
    }
    _: RangeResolvedType -> {
      if property == "lowerBound" || property == "upperBound" { return primitive("int") }
      return unknownType()
    }
    actor: ActorType -> {
      resolved := resolveMemberType(state, actor.innerClass, property, span, validateVisibility, declaredOnly, selection)
      if validateVisibility && selection.field && selection.instance {
        typeError(state, "Cannot access actor field '" + property + "' directly; use an actor method to read or update actor state", span)
        return unknownType()
      }
      return resolved
    }
    promise: PromiseType -> {
      if property == "get" { return functionType([], resultType(promise.valueType, primitive("string"))) }
      return unknownType()
    }
    parameter: TypeParameterType -> {
      bound := interfaceBoundReceiver(parameter)
      if bound.kind == "interface" { return resolveMemberType(state, bound, property, span, validateVisibility, true, selection) }
      if property == "metadata" {
        if parameter.constraintName != "Reflectable" {
          typeError(state, "Static member \"metadata\" requires type parameter \"" + parameter.name + "\" to be constrained by Reflectable", span)
          return unknownType()
        }
        return classMetadataType(parameter)
      }
      if property == "fromJsonValue" {
        if parameter.constraintName != "JsonSerializable" {
          typeError(state, "Static member \"fromJsonValue\" requires type parameter \"" + parameter.name + "\" to be constrained by JsonSerializable", span)
          return unknownType()
        }
        return functionType([
          FunctionParamType { name: "value", type_: jsonValueType(), hasDefault: false },
          FunctionParamType { name: "lenient", type_: primitive("bool"), hasDefault: true },
        ], resultType(parameter, primitive("string")))
      }
      return unknownType()
    }
    metadata: ClassMetadataResolvedType -> {
      if property == "name" || property == "description" { return primitive("string") }
      if property == "methods" { return arrayType(methodReflectionType(metadata.classType)) }
      if property == "defs" { return unionType([jsonValueType(), noneType()]) }
      if property == "invoke" {
        return functionType([
          FunctionParamType { name: "instance", type_: metadata.classType, hasDefault: false },
          FunctionParamType { name: "methodName", type_: primitive("string"), hasDefault: false },
          FunctionParamType { name: "params", type_: jsonValueType(), hasDefault: false },
        ], resultType(jsonValueType(), jsonValueType()))
      }
      return unknownType()
    }
    reflection: MethodReflectionResolvedType -> {
      if property == "name" || property == "description" { return primitive("string") }
      if property == "inputSchema" || property == "outputSchema" { return jsonValueType() }
      if property == "invoke" {
        return functionType([
          FunctionParamType { name: "instance", type_: reflection.classType, hasDefault: false },
          FunctionParamType { name: "params", type_: jsonValueType(), hasDefault: false },
        ], resultType(jsonValueType(), jsonValueType()))
      }
      return unknownType()
    }
    enum_: EnumType -> {
      declaration := declarationFor(state.result, enum_.symbol)
      let backingType: ResolvedType = primitive("int")
      if declaration != none {
        case declaration! {
          enumDeclaration: EnumDeclaration -> { if enumDeclaration.backingKind == "string" { backingType = primitive("string") } }
          _ -> { }
        }
      }
      if property == "name" { return primitive("string") }
      if property == "value" { return backingType }
      if property == "toJsonValue" { return functionType([], jsonValueType()) }
      if property == "values" { return functionType([], arrayType(enum_, true)) }
      if property == "fromName" {
        return functionType(
          [FunctionParamType { name: "value", type_: primitive("string"), hasDefault: false }],
          unionType([enum_, noneType()]),
        )
      }
      if property == "fromValue" {
        return functionType(
          [FunctionParamType { name: "value", type_: backingType, hasDefault: false }],
          unionType([enum_, noneType()]),
        )
      }
      if property == "fromJsonValue" {
        return functionType([
          FunctionParamType { name: "value", type_: jsonValueType(), hasDefault: false },
          FunctionParamType { name: "lenient", type_: primitive("bool"), hasDefault: true },
        ], resultType(enum_, primitive("string")))
      }
      if declaration != none {
        case declaration! {
          enumDeclaration: EnumDeclaration -> {
            for variant of enumDeclaration.variants { if variant.name == property { return enum_ } }
          }
          _ -> { }
        }
      }
      return unknownType()
    }
    class_: ClassType -> {
      if class_.name == "SourceLocation" && class_.symbol.module == "<builtin>" {
        if property == "fileName" || property == "functionName" { return primitive("string") }
        if property == "line" { return primitive("int") }
        return unknownType()
      }
      declaration := declarationFor(state.result, class_.symbol)
      if declaration == none { return unknownType() }
      case declaration! {
        classDeclaration: ClassDeclaration -> {
          if property == "metadata" {
            if classDeclaration.typeParams.length > 0 {
              typeError(state, "Metadata is not available on generic type \"" + classDeclaration.name + "\"", span)
              return unknownType()
            }
            if !canGenerateJsonSerialization(classDeclaration, jsonPrograms(state.result)) || !canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state.result)) {
              typeError(state, "Type \"" + classDeclaration.name + "\" is not eligible for metadata because it does not support automatic JSON generation", span)
              return unknownType()
            }
            let valid = true
            for method of classDeclaration.methods {
              if method.private_ || method.static_ { continue }
              for parameter of method.params {
                if parameter.resolvedType != none && !isGeneratedJsonType(parameter.resolvedType!, jsonPrograms(state.result)) {
                  typeError(state, "Parameter \"" + parameter.name + "\" of method \"" + method.name + "\" is not JSON-serializable", parameter.span)
                  valid = false
                }
              }
              if method.resolvedType != none {
                case method.resolvedType! {
                function_: FunctionType -> {
                  let successType = function_.returnType
                  case successType {
                    result: ResultResolvedType -> { successType = result.valueType }
                    _ -> { }
                  }
                  if successType.kind != "none" && !isGeneratedJsonType(successType, jsonPrograms(state.result)) {
                    typeError(state, "Return type of method \"" + method.name + "\" is not JSON-serializable", method.span)
                    valid = false
                  }
                }
                _ -> { }
                }
              }
            }
            if !valid { return unknownType() }
            classDeclaration.needsMetadata = true
            recordMember(selection, class_, class_.symbol.module, none, false, classDeclaration, false)
            return classMetadataType(class_)
          }
          if property == "toJsonObject" && canGenerateJsonSerialization(classDeclaration, jsonPrograms(state.result)) {
            return functionType([], jsonObjectType())
          }
          if property == "fromJsonValue" && canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state.result)) {
            recordMember(selection, class_, class_.symbol.module, none, false, classDeclaration, false)
            return functionType([
              FunctionParamType { name: "value", type_: jsonValueType(), hasDefault: false },
              FunctionParamType { name: "lenient", type_: primitive("bool"), hasDefault: true },
            ], resultType(object, primitive("string")))
          }
          if property == "toJsonObject" || property == "fromJsonValue" {
            typeError(state, "Type \"" + classDeclaration.name + "\" does not support automatic JSON " + (if property == "toJsonObject" then "serialization" else "deserialization"), span)
            return unknownType()
          }
          for field of classDeclaration.fields {
            for name of field.names {
              if name == property {
                recordMember(selection, class_, class_.symbol.module, none, true, if field.static_ then classDeclaration else none, !field.static_)
                fieldType := if field.resolvedType != none then field.resolvedType! else if field.type_ != none then resolveType(state, field.type_!, state.info!, state.moduleScope!) else unknownType()
                if validateVisibility && field.private_ && class_.symbol.module != state.info!.path {
                  typeError(state, "Field '" + property + "' is private to module '" + class_.symbol.module + "'", span)
                }
                return substituteTypeParams(fieldType, classDeclaration.typeParams, class_.typeArgs)
              }
            }
          }
          for method of classDeclaration.methods {
            if method.name == property {
              recordMember(selection, class_, class_.symbol.module, method, false, if method.static_ then classDeclaration else none, !method.static_)
              methodType := method.resolvedType ?? methodSignature(method, classModuleFor(state.result, class_.symbol), state.result, class_.symbol.typeParams)
              if validateVisibility && method.private_ && class_.symbol.module != state.info!.path {
                typeError(state, "Method '" + property + "' is private to module '" + class_.symbol.module + "'", span)
              }
              return substituteTypeParams(methodType, classDeclaration.typeParams, class_.typeArgs)
            }
          }
        }
        interface_: InterfaceDeclaration -> {
          for field of interface_.fields { if field.name == property { recordMember(selection, class_, class_.symbol.module, none, true); return field.resolvedType ?? resolveType(state, field.type_, state.info!, state.moduleScope!) } }
          for method of interface_.methods { if method.name == property { recordMember(selection, class_, class_.symbol.module, method); return method.resolvedType ?? methodSignature(method, classModuleFor(state.result, class_.symbol), state.result, class_.symbol.typeParams) } }
        }
        _ -> { }
      }
    }
    _: EnumType -> { return object }
    interfaceType_: InterfaceType -> {
      declaration := declarationFor(state.result, interfaceType_.symbol)
      if declaration == none { return unknownType() }
      case declaration! {
        interface_: InterfaceDeclaration -> {
          for field of interface_.fields {
            if field.name == property {
              recordMember(selection, interfaceType_, interfaceType_.symbol.module, none, true)
              fieldType := field.resolvedType ?? resolveAnnotation(field.type_, classModuleFor(state.result, interfaceType_.symbol), state.result, interface_.typeParams)
              return substituteTypeParams(if field.readonly_ then applyDeepReadonly(fieldType) else fieldType, interface_.typeParams, interfaceType_.typeArgs)
            }
          }
          for method of interface_.methods {
            if method.name == property {
              recordMember(selection, interfaceType_, interfaceType_.symbol.module, method, false, none, !method.static_)
              methodType := method.resolvedType ?? interfaceMethodSignature(state, method, interface_, interfaceType_.symbol)
              return substituteTypeParams(methodType, interface_.typeParams, interfaceType_.typeArgs)
            }
          }
          if declaredOnly { return unknownType() }
          if property == "fromJsonValue" {
            if interface_.typeParams.length > 0 {
              typeError(state, "Automatic JSON deserialization is not available on generic interface \"" + interface_.name + "\"", span)
              return unknownType()
            }
            if interfaceType_.symbol.implementations.length == 0 {
              typeError(state, "Cannot deserialize interface \"" + interface_.name + "\": no implementing classes found", span)
              return unknownType()
            }
            discriminator := interfaceJsonDiscriminator(interface_, jsonPrograms(state.result))
            if discriminator == none {
              typeError(state, "Cannot deserialize interface \"" + interface_.name + "\": all implementing classes must share a const string field with distinct values (e.g. const kind = \"variant\")", span)
              return unknownType()
            }
            interface_.needsJson = true
            return functionType([
              FunctionParamType { name: "value", type_: jsonValueType(), hasDefault: false },
              FunctionParamType { name: "lenient", type_: primitive("bool"), hasDefault: true },
            ], resultType(object, primitive("string")))
          }

        }
        _ -> { }
      }
    }
    _ -> { }
  }
  return unknownType()
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
              if name == property {
                return Binding {
                  name,
                  kind: "field",
                  type_: fieldType,
                  mutable: field.let_,
                  span: checkerSemanticSpan(field.span),
                  module: class_.symbol.module,
                  symbol: class_.symbol,
                  fieldMode: if field.readonly_ then "readonly" else if field.const_ then "const" else if field.let_ then "let" else "implicit",
                  fieldOwner: classDeclaration.name,
                }
              }
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

function jsonPrograms(result: AnalysisResult): Program[] {
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
    _: TupleResolvedType -> { return unknownType() }
    primitive_: PrimitiveType -> {
      if primitive_.name == "string" {
        if !isAssignableWithInterfaces(state.result, index, primitive("int")) && typeName(index) != "unknown" { typeError(state, "Index must be an int", span) }
        return primitive("char")
      }
    }
    _ -> { }
  }
  return unknownType()
}

function interfaceMethodSignature(state: CheckerState, method: FunctionDeclaration, owner: InterfaceDeclaration, symbol: Symbol): ResolvedType {
  return methodSignature(method, classModuleFor(state.result, symbol), state.result, owner.typeParams)
}
