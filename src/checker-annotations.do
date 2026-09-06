// Single annotation resolver for provisional signatures and checked annotations.

import { memberType } from "./checker-resolution"
import { ClassType, FunctionParamType, ResolvedType, Scope, Symbol, TypeParameterType, ResolvedTypeConstraint } from "./semantic"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import { ArrayType, ClassDeclaration, AstFunctionType, InterfaceDeclaration, NamedType, SourceSpan, TypeAliasDeclaration, TypeAnnotation, UnionType, WeakType, TypeParameterConstraint } from "./ast"
import { actorType, arrayType, classType, enumType, functionType, interfaceType, isSupportedHashCollectionType, jsonObjectType, jsonValueType, mapType, resultType, setType, streamType, neverType, noneType, primitive, promiseType, rangeType, tupleType, typeName, unionMutabilityConflict, unionType, isWeakReferenceTarget, substituteTypeParams, typeParameter, unknownType, weakReferenceErrorType, weakType } from "./checker-types"

import { CheckerState } from "./checker-state"
import { isNumericConstraint, satisfiesNumericConstraint } from "./checker-numeric"
import { deprecatedNoneAlias, typeError } from "./checker-common"
import { builtinSourceLocationType, declaredSymbolName, optionalResolvedType, hasTypeParam, typeParamConstraintName, typeParamConstraint, symbolFor, declarationFor } from "./checker-symbols"
import { registerConcreteInterfaceImplementations, concreteTypes, classModuleFor, isAssignableWithInterfaces } from "./checker-interfaces"

class AnnotationResolution {
  state: CheckerState
  commit: bool
  let aliases: string[] = []
}

export function resolveCheckedAnnotation(state: CheckerState, annotation: TypeAnnotation, module: ModuleInfo, scope: Scope, validateConstraints: bool = true): ResolvedType {
  return resolveAnnotationType(AnnotationResolution { state, commit: true }, annotation, module, scope, validateConstraints)
}

// Predeclaration has no diagnostic or decoration ownership. It uses the same
// resolution rules; declaration checking later validates dependent constraints.
export function resolveProvisionalAnnotation(annotation: TypeAnnotation, info: ModuleInfo, result: AnalysisResult, typeParams: string[] = []): ResolvedType {
  state := CheckerState { result, info }
  scope := Scope { parent: none }
  for name of typeParams { scope.typeParams.push(name) }
  return resolveAnnotationType(AnnotationResolution { state, commit: false }, annotation, info, scope, false)
}

function finishAnnotation(resolution: AnnotationResolution, annotation: TypeAnnotation, type_: ResolvedType): ResolvedType {
  if resolution.commit {
    conflict := unionMutabilityConflict(type_)
    if conflict != none { typeError(resolution.state, conflict!, annotation.span) }
    annotation.resolvedType = optionalResolvedType(type_)
  }
  return type_
}

export function decorateAnnotationType(state: CheckerState, annotation: TypeAnnotation, resolvedType: ResolvedType): ResolvedType {
  annotation.resolvedType = optionalResolvedType(resolvedType)
  return resolvedType
}

function resolveAnnotationType(resolution: AnnotationResolution, annotation: TypeAnnotation, module: ModuleInfo, scope: Scope, validateConstraints: bool = true): ResolvedType {
  state := resolution.state
  case annotation {
    named: NamedType -> {
      if named.name == "none" || named.name == "void" || named.name == "null" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        if named.name != "none" && named.resolvedType == none { deprecatedNoneAlias(state, named.name, named.span, module.path) }
        return finishAnnotation(resolution, annotation, noneType())
      }
      if named.name == "never" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, neverType())
      }
      if named.name == "JsonValue" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, jsonValueType())
      }
      if named.name == "JsonObject" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, jsonObjectType())
      }
      if named.name == "SourceLocation" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, builtinSourceLocationType())
      }
      if named.name == "WeakReferenceError" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, weakReferenceErrorType())
      }
      if named.name == "Range" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, rangeType())
      }
      if hasTypeParam(scope, named.name) {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, typeParameter(named.name, typeParamConstraintName(scope, named.name), typeParamConstraint(scope, named.name)))
      }
      if named.name == "Tuple" {
        let elements: ResolvedType[] = []
        for argument of named.typeArgs { elements.push(resolveAnnotationType(resolution, argument, module, scope, validateConstraints)) }
        return finishAnnotation(resolution, annotation, tupleType(elements))
      }
      if named.name == "Map" || named.name == "ReadonlyMap" {
        if named.typeArgs.length != 2 { typeError(state, named.name + " requires two type arguments", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        key := resolveAnnotationType(resolution, named.typeArgs[0], module, scope, validateConstraints)
        value := resolveAnnotationType(resolution, named.typeArgs[1], module, scope, validateConstraints)
        return finishAnnotation(resolution, annotation, mapType(key, value, named.name == "ReadonlyMap"))
      }
      if named.name == "Set" || named.name == "ReadonlySet" {
        if named.typeArgs.length != 1 { typeError(state, named.name + " requires one type argument", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        element := resolveAnnotationType(resolution, named.typeArgs[0], module, scope, validateConstraints)
        if !isSupportedHashCollectionType(element) {
          typeError(state, "Set element type \"" + typeName(element) + "\" is not supported; set elements must be byte, string, int, long, char, bool, or enum", named.typeArgs[0].span)
        }
        return finishAnnotation(resolution, annotation, setType(element, named.name == "ReadonlySet"))
      }
      if named.name == "Stream" {
        if named.typeArgs.length != 1 { typeError(state, "Stream requires one type argument", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, streamType(resolveAnnotationType(resolution, named.typeArgs[0], module, scope, validateConstraints)))
      }
      if named.name == "Actor" {
        if named.typeArgs.length != 1 { typeError(state, "Actor requires one type argument", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        inner := resolveAnnotationType(resolution, named.typeArgs[0], module, scope, validateConstraints)
        case inner {
          class_: ClassType -> { return finishAnnotation(resolution, annotation, actorType(class_)) }
          _ -> { typeError(state, "Actor requires a class type", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        }
      }
      if named.name == "Promise" {
        if named.typeArgs.length != 1 { typeError(state, "Promise requires one type argument", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, promiseType(resolveAnnotationType(resolution, named.typeArgs[0], module, scope, validateConstraints)))
      }
      if named.name == "Result" {
        if named.typeArgs.length != 2 { typeError(state, "Result requires two type arguments", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, resultType(resolveAnnotationType(resolution, named.typeArgs[0], module, scope, validateConstraints), resolveAnnotationType(resolution, named.typeArgs[1], module, scope, validateConstraints)))
      }
      if named.name == "Success" || named.name == "Failure" {
        if named.typeArgs.length != 1 { typeError(state, named.name + " requires one type argument", named.span); return finishAnnotation(resolution, annotation, unknownType()) }
        payload := resolveAnnotationType(resolution, named.typeArgs[0], module, scope, validateConstraints)
        if named.name == "Success" { return finishAnnotation(resolution, annotation, resultType(payload, unknownType())) }
        return finishAnnotation(resolution, annotation, resultType(unknownType(), payload))
      }
      if named.name == "byte" || named.name == "int" || named.name == "long" || named.name == "float" || named.name == "double" || named.name == "string" || named.name == "char" || named.name == "bool" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, primitive(named.name))
      }
      let symbol: Symbol | none = named.resolvedSymbol
      if symbol == none { symbol = symbolFor(module, named.name) }
      if symbol == none {
        typeError(state, "Unknown type '" + named.name + "'", named.span)
        return finishAnnotation(resolution, annotation, unknownType())
      }
      if symbol!.kind == "type-alias" {
        declaration := declarationFor(state.result, symbol!)
        if declaration == none { return finishAnnotation(resolution, annotation, unknownType()) }
        case declaration! {
          alias: TypeAliasDeclaration -> {
            if named.typeArgs.length != alias.typeParams.length {
              typeError(state, alias.name + " requires " + string(alias.typeParams.length) + " type argument" + (if alias.typeParams.length == 1 then "" else "s"), named.span)
              return finishAnnotation(resolution, annotation, unknownType())
            }
            key := symbol!.module + ":" + alias.name
            for active of resolution.aliases {
              if active == key {
                typeError(state, "Cyclic type alias '" + alias.name + "'", named.span)
                return finishAnnotation(resolution, annotation, unknownType())
              }
            }
            resolution.aliases.push(key)
            aliasScope := Scope { parent: scope }
            for typeParam of alias.typeParams { aliasScope.typeParams.push(typeParam) }
            let resolvedAlias = resolveAnnotationType(resolution, alias.type_, classModuleFor(state.result, symbol!), aliasScope, false)
            ignoredAlias := try! resolution.aliases.pop()
            let typeArgs: ResolvedType[] = []
            for argument of named.typeArgs { typeArgs.push(resolveAnnotationType(resolution, argument, module, scope, validateConstraints)) }
            if validateConstraints { validateAnnotationConstraints(state, alias.typeParams, alias.typeParamConstraints, typeArgs, named.span, classModuleFor(state.result, symbol!), scope) }
            resolvedAlias = substituteTypeParams(resolvedAlias, alias.typeParams, typeArgs)
            return finishAnnotation(resolution, annotation, resolvedAlias)
          }
          _ -> { return finishAnnotation(resolution, annotation, unknownType()) }
        }
      }
      if symbol!.kind == "interface" {
        let typeArgs: ResolvedType[] = []
        for argument of named.typeArgs { typeArgs.push(resolveAnnotationType(resolution, argument, module, scope, validateConstraints)) }
        declaration := declarationFor(state.result, symbol!)
        if declaration != none {
          case declaration! {
            interfaceDeclaration: InterfaceDeclaration -> {
              if !validateNominalTypeArity(state, interfaceDeclaration.name, interfaceDeclaration.typeParams.length, typeArgs.length, named.span) {
                return finishAnnotation(resolution, annotation, unknownType())
              }
              if validateConstraints { validateAnnotationConstraints(state, interfaceDeclaration.typeParams, interfaceDeclaration.typeParamConstraints, typeArgs, named.span, classModuleFor(state.result, symbol!), scope) }
            }
            _ -> { }
          }
        }
        concreteInterface := interfaceType(declaredSymbolName(symbol!), symbol!, typeArgs)
        if resolution.commit && concreteTypes(typeArgs) { registerConcreteInterfaceImplementations(state.result, concreteInterface) }
        return finishAnnotation(resolution, annotation, concreteInterface)
      }
      if symbol!.kind == "enum" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, enumType(declaredSymbolName(symbol!), symbol!))
      }
      let typeArgs: ResolvedType[] = []
      for argument of named.typeArgs { typeArgs.push(resolveAnnotationType(resolution, argument, module, scope, validateConstraints)) }
      declaration := declarationFor(state.result, symbol!)
      if declaration != none {
        case declaration! {
          classDeclaration: ClassDeclaration -> {
            if !validateNominalTypeArity(state, classDeclaration.name, classDeclaration.typeParams.length, typeArgs.length, named.span) {
              return finishAnnotation(resolution, annotation, unknownType())
            }
            if validateConstraints { validateAnnotationConstraints(state, classDeclaration.typeParams, classDeclaration.typeParamConstraints, typeArgs, named.span, classModuleFor(state.result, symbol!), scope) }
          }
          _ -> {
            typeError(state, "Symbol '" + named.name + "' is not a type", named.span)
            return finishAnnotation(resolution, annotation, unknownType())
          }
        }
      } else if symbol!.kind != "class" && symbol!.kind != "struct" {
        typeError(state, "Symbol '" + named.name + "' is not a type", named.span)
        return finishAnnotation(resolution, annotation, unknownType())
      }
      return finishAnnotation(resolution, annotation, classType(declaredSymbolName(symbol!), symbol!, typeArgs))
    }
    array: ArrayType -> { return finishAnnotation(resolution, annotation, arrayType(resolveAnnotationType(resolution, array.elementType, module, scope, validateConstraints), array.readonly_)) }
    union: UnionType -> {
      let members: ResolvedType[] = []
      for item of union.types { members.push(resolveAnnotationType(resolution, item, module, scope, validateConstraints)) }
      return finishAnnotation(resolution, annotation, unionType(members))
    }
    function_: AstFunctionType -> {
      let params: FunctionParamType[] = []
      for parameter of function_.params { params.push(FunctionParamType { name: parameter.name, type_: resolveAnnotationType(resolution, parameter.type_, module, scope, validateConstraints), hasDefault: false }) }
      return finishAnnotation(resolution, annotation, functionType(params, resolveAnnotationType(resolution, function_.returnType, module, scope, validateConstraints)))
    }
    weak_: WeakType -> {
      inner := resolveAnnotationType(resolution, weak_.type_, module, scope, validateConstraints)
      if !isWeakReferenceTarget(inner) { typeError(state, "Type \"" + typeName(inner) + "\" is not a valid weak reference target", weak_.span) }
      return finishAnnotation(resolution, annotation, weakType(inner))
    }
  }
  return finishAnnotation(resolution, annotation, unknownType())
}

function rejectUnexpectedTypeArguments(resolution: AnnotationResolution, named: NamedType, module: ModuleInfo, scope: Scope, validateConstraints: bool): bool {
  state := resolution.state
  if named.typeArgs.length == 0 { return false }
  for argument of named.typeArgs { resolveAnnotationType(resolution, argument, module, scope, validateConstraints) }
  typeError(state, named.name + " does not accept type arguments", named.span)
  return true
}

function validateNominalTypeArity(state: CheckerState, name: string, expected: int, actual: int, span: SourceSpan): bool {
  if expected == actual { return true }
  typeError(state, name + " requires " + string(expected) + " type argument" + (if expected == 1 then "" else "s") + "; received " + string(actual), span)
  return false
}

/** Validates concrete arguments against substituted declaration constraints. */
export function validateAnnotationConstraints(state: CheckerState, names: string[], constraints: TypeParameterConstraint[], arguments: ResolvedType[], span: SourceSpan, module: ModuleInfo, outer: Scope, ownerNames: string[] = [], ownerArguments: ResolvedType[] = []): none {
  if names.length != arguments.length { return }
  constraintScope := Scope { parent: outer }
  for name of ownerNames { constraintScope.typeParams.push(name); constraintScope.typeParamConstraintNames.push(""); constraintScope.typeParamConstraints.push(ResolvedTypeConstraint {}) }
  for name of names {
    constraintScope.typeParams.push(name)
    constraintScope.typeParamConstraintNames.push("")
    constraintScope.typeParamConstraints.push(ResolvedTypeConstraint {})
  }
  for index of 0..<names.length {
    if index >= constraints.length || constraints[index].type_ == none { continue }
    annotation := constraints[index].type_!
    case annotation {
      named: NamedType -> {
        if named.typeArgs.length == 0 && (named.name == "Reflectable" || named.name == "JsonSerializable") {
          case arguments[index] {
            parameter: TypeParameterType -> { if parameter.constraintName == named.name { continue } }
            _ -> { }
          }
        }
        if named.typeArgs.length == 0 && named.name == "Reflectable" {
          case arguments[index] {
            _: ClassType -> { memberType(state, arguments[index], "metadata", span) }
            _ -> { reportConstraintViolation(state, names[index], arguments[index], "Reflectable", span) }
          }
          continue
        }
        if named.typeArgs.length == 0 && named.name == "JsonSerializable" {
          result := memberType(state, arguments[index], "fromJsonValue", span)
          if result.kind == "unknown" { reportConstraintViolation(state, names[index], arguments[index], "JsonSerializable", span) }
          continue
        }
      }
      _ -> { }
    }
    resolvedConstraint := resolveCheckedAnnotation(state, annotation, module, constraintScope, false)
    substitutedConstraint := substituteTypeParams(substituteTypeParams(resolvedConstraint, ownerNames, ownerArguments), names, arguments)
    if isNumericConstraint(substitutedConstraint) {
      if !satisfiesNumericConstraint(arguments[index], substitutedConstraint) { reportConstraintViolation(state, names[index], arguments[index], typeName(substitutedConstraint), span) }
    } else if !isAssignableWithInterfaces(state.result, arguments[index], substitutedConstraint) {
      reportConstraintViolation(state, names[index], arguments[index], typeName(substitutedConstraint), span)
    }
  }
}

function reportConstraintViolation(state: CheckerState, typeParam: string, argument: ResolvedType, constraint: string, span: SourceSpan): none {
  typeError(state, "Type \"" + typeName(argument) + "\" does not satisfy constraint \"" + constraint + "\" for type parameter \"" + typeParam + "\"", span)
}
