// Single annotation resolver for provisional signatures and checked annotations.

import { memberType } from "./checker-resolution"
import { ClassType, FunctionParamType, ResolvedType, Scope, Symbol, TypeParameterType, ResolvedTypeConstraint } from "./semantic"
import { AnalysisResult, ModuleInfo, unknownTypeMessage } from "./analyzer"
import { ArrayType, ClassDeclaration, AstFunctionType, InterfaceDeclaration, NamedType, SourceSpan, TypeAliasDeclaration, TypeAnnotation, UnionType, WeakType, TypeParameterConstraint } from "./ast"
import { actorType, arrayType, classType, containsTypeParameters, enumType, failureType, functionType, successType, interfaceType, jsonObjectType, mixedWeakUnionMessage, jsonValueType, mapType, resultType, setType, streamType, neverType, noneType, primitive, promiseType, rangeType, tupleType, typeName, unionMutabilityConflict, unionType, isWeakReferenceTarget, substituteTypeParams, typeParameter, unknownType, weakReferenceErrorType, weakType } from "./checker-types"

import { CheckerState } from "./checker-state"
import { reportUnsupportedHashKey } from "./checker-hash-keys"
import { isNumericConstraint, satisfiesNumericConstraint } from "./checker-numeric"
import { deprecatedNoneAlias, typeArgumentArityMessage, typeError } from "./checker-common"
import { builtinSourceLocationType, declaredSymbolName, hasTypeParam, typeParamConstraintName, typeParamConstraint, symbolFor, declarationFor } from "./checker-symbols"
import { registerConcreteInterfaceImplementations, classModuleFor, isAssignableWithInterfaces, satisfiesInterfaceBound, satisfiesInterfaceInstanceBound } from "./checker-interfaces"

class AnnotationResolution {
  state: CheckerState
  commit: bool
  let aliases: string[] = []
}

export function resolveType(state: CheckerState, annotation: TypeAnnotation, module: ModuleInfo, scope: Scope, validateConstraints: bool = true): ResolvedType {
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
    if resolution.state.editorMode { resolution.state.info!.editorAnnotations.push(annotation) }
    conflict := unionMutabilityConflict(type_)
    if conflict != none { typeError(resolution.state, conflict!, annotation.span) }
    annotation.resolvedType = type_
  }
  return type_
}

function resolveAnnotationType(resolution: AnnotationResolution, annotation: TypeAnnotation, module: ModuleInfo, scope: Scope, validateConstraints: bool = true): ResolvedType {
  state := resolution.state
  case annotation {
    named: NamedType -> {
      fixed := fixedBuiltinType(named.name)
      if fixed != none {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        if (named.name == "void" || named.name == "null") && named.resolvedType == none { deprecatedNoneAlias(state, named.name, named.span, module.path) }
        return finishAnnotation(resolution, annotation, fixed!)
      }
      if hasTypeParam(scope, named.name) {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, typeParameter(named.name, typeParamConstraintName(scope, named.name), typeParamConstraint(scope, named.name)))
      }
      builtinArity := case named.name {
        "Tuple" -> -1,
        "Map" | "ReadonlyMap" | "Result" -> 2,
        "Set" | "ReadonlySet" | "Stream" | "Actor" | "Promise" | "Success" | "Failure" -> 1,
        _ -> 0
      }
      if builtinArity != 0 {
        if builtinArity > 0 && named.typeArgs.length != builtinArity {
          typeError(state, named.name + " requires " + (if builtinArity == 1 then "one type argument" else "two type arguments"), named.span)
          return finishAnnotation(resolution, annotation, unknownType())
        }
        return finishAnnotation(resolution, annotation, genericBuiltinType(state, named, resolveTypeArgumentAnnotations(resolution, named, module, scope, validateConstraints)))
      }
      let symbol: Symbol | none = named.resolvedSymbol
      if symbol == none { symbol = symbolFor(module, named.name) }
      if symbol == none {
        typeError(state, unknownTypeMessage(named.name), named.span)
        return finishAnnotation(resolution, annotation, unknownType())
      }
      // Types reached only while checking expressions (for example case-arm
      // patterns) skip the analyzer's declaration-type traversal. Preserve the
      // checker selection so editor consumers see the same symbol either way.
      if resolution.commit { named.resolvedSymbol = symbol }
      if symbol!.kind == "type-alias" {
        declaration := declarationFor(state.result, symbol!)
        if declaration == none { return finishAnnotation(resolution, annotation, unknownType()) }
        case declaration! {
          alias: TypeAliasDeclaration -> {
            if named.typeArgs.length != alias.typeParams.length {
              typeError(state, typeArgumentArityMessage(alias.name, alias.typeParams.length, named.typeArgs.length), named.span)
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
            resolvedAlias := resolveAnnotationType(resolution, alias.type_, classModuleFor(state.result, symbol!), aliasScope, false)
            ignoredAlias := resolution.aliases.pop()!
            typeArgs := resolveTypeArgumentAnnotations(resolution, named, module, scope, validateConstraints)
            if validateConstraints { validateTypeArgumentConstraints(state, alias.typeParams, alias.typeParamConstraints, typeArgs, named.span, classModuleFor(state.result, symbol!), scope) }
            return finishAnnotation(resolution, annotation, substituteTypeParams(resolvedAlias, alias.typeParams, typeArgs))
          }
          _ -> { return finishAnnotation(resolution, annotation, unknownType()) }
        }
      }
      if symbol!.kind == "enum" {
        if rejectUnexpectedTypeArguments(resolution, named, module, scope, validateConstraints) { return finishAnnotation(resolution, annotation, unknownType()) }
        return finishAnnotation(resolution, annotation, enumType(declaredSymbolName(symbol!), symbol!))
      }
      isInterface := symbol!.kind == "interface"
      typeArgs := resolveTypeArgumentAnnotations(resolution, named, module, scope, validateConstraints)
      declaration := declarationFor(state.result, symbol!)
      let valid = true
      if declaration != none {
        declarationModule := classModuleFor(state.result, symbol!)
        case declaration! {
          interface_: InterfaceDeclaration -> { valid = validateNominalTypeArguments(state, interface_.name, interface_.typeParams, interface_.typeParamConstraints, typeArgs, named.span, declarationModule, scope, validateConstraints) }
          class_: ClassDeclaration -> { valid = validateNominalTypeArguments(state, class_.name, class_.typeParams, class_.typeParamConstraints, typeArgs, named.span, declarationModule, scope, validateConstraints) }
          _ -> {
            if !isInterface {
              typeError(state, "Symbol '" + named.name + "' is not a type", named.span)
              valid = false
            }
          }
        }
      } else if !isInterface && symbol!.kind != "class" && symbol!.kind != "struct" {
        typeError(state, "Symbol '" + named.name + "' is not a type", named.span)
        valid = false
      }
      if !valid { return finishAnnotation(resolution, annotation, unknownType()) }
      if isInterface {
        concreteInterface := interfaceType(declaredSymbolName(symbol!), symbol!, typeArgs)
        if resolution.commit && !containsTypeParameters(typeArgs) { registerConcreteInterfaceImplementations(state.result, concreteInterface) }
        return finishAnnotation(resolution, annotation, concreteInterface)
      }
      return finishAnnotation(resolution, annotation, classType(declaredSymbolName(symbol!), symbol!, typeArgs))
    }
    array: ArrayType -> { return finishAnnotation(resolution, annotation, arrayType(resolveAnnotationType(resolution, array.elementType, module, scope, validateConstraints), array.readonly_)) }
    union: UnionType -> {
      let members: ResolvedType[] = []
      for item of union.types { members.push(resolveAnnotationType(resolution, item, module, scope, validateConstraints)) }
      resolved := unionType(members)
      mixedWeak := mixedWeakUnionMessage(resolved)
      if resolution.commit && mixedWeak != none { typeError(state, mixedWeak!, union.span) }
      return finishAnnotation(resolution, annotation, resolved)
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

// Built-in names that denote one fixed type and accept no type arguments.
function fixedBuiltinType(name: string): ResolvedType | none {
  return case name {
    "none" | "void" | "null" -> noneType(),
    "never" -> neverType(),
    "SerialValue" -> jsonValueType(),
    "SerialObject" -> jsonObjectType(),
    "SourceLocation" -> builtinSourceLocationType(),
    "WeakReferenceError" -> weakReferenceErrorType(),
    "Range" -> rangeType(),
    "byte" | "int" | "long" | "float" | "double" | "string" | "char" | "bool" -> primitive(name),
    _ -> none
  }
}

/** Builds a generic built-in type whose argument count was already validated. */
function genericBuiltinType(state: CheckerState, named: NamedType, args: ResolvedType[]): ResolvedType {
  case named.name {
    "Tuple" -> { return tupleType(args) }
    "Map" | "ReadonlyMap" -> {
      reportUnsupportedHashKey(state, args[0], "Map key", named.typeArgs[0].span)
      return mapType(args[0], args[1], named.name == "ReadonlyMap")
    }
    "Set" | "ReadonlySet" -> {
      reportUnsupportedHashKey(state, args[0], "Set element", named.typeArgs[0].span)
      return setType(args[0], named.name == "ReadonlySet")
    }
    "Stream" -> { return streamType(args[0]) }
    "Actor" -> {
      case args[0] {
        class_: ClassType -> { return actorType(class_) }
        _ -> { typeError(state, "Actor requires a class type", named.span) }
      }
    }
    "Promise" -> { return promiseType(args[0]) }
    "Result" -> { return resultType(args[0], args[1]) }
    "Success" -> { return successType(args[0]) }
    "Failure" -> { return failureType(args[0]) }
    _ -> { }
  }
  return unknownType()
}

function resolveTypeArgumentAnnotations(resolution: AnnotationResolution, named: NamedType, module: ModuleInfo, scope: Scope, validateConstraints: bool): ResolvedType[] {
  let resolved: ResolvedType[] = []
  for argument of named.typeArgs { resolved.push(resolveAnnotationType(resolution, argument, module, scope, validateConstraints)) }
  return resolved
}

/** Resolves explicit type arguments written in checked source, such as `f<int>(...)` or `Box<string>.make()`. */
export function resolveTypeArguments(state: CheckerState, annotations: TypeAnnotation[], scope: Scope): ResolvedType[] {
  let resolved: ResolvedType[] = []
  for annotation of annotations { resolved.push(resolveType(state, annotation, state.info!, scope)) }
  return resolved
}

function rejectUnexpectedTypeArguments(resolution: AnnotationResolution, named: NamedType, module: ModuleInfo, scope: Scope, validateConstraints: bool): bool {
  if named.typeArgs.length == 0 { return false }
  resolveTypeArgumentAnnotations(resolution, named, module, scope, validateConstraints)
  typeError(resolution.state, named.name + " does not accept type arguments", named.span)
  return true
}

function validateNominalTypeArguments(state: CheckerState, name: string, typeParams: string[], constraints: TypeParameterConstraint[], typeArgs: ResolvedType[], span: SourceSpan, module: ModuleInfo, scope: Scope, validateConstraints: bool): bool {
  if typeParams.length != typeArgs.length {
    typeError(state, typeArgumentArityMessage(name, typeParams.length, typeArgs.length), span)
    return false
  }
  if validateConstraints { validateTypeArgumentConstraints(state, typeParams, constraints, typeArgs, span, module, scope) }
  return true
}

/** Validates concrete arguments against substituted declaration constraints. */
export function validateTypeArgumentConstraints(state: CheckerState, names: string[], constraints: TypeParameterConstraint[], arguments: ResolvedType[], span: SourceSpan, module: ModuleInfo, outer: Scope, ownerNames: string[] = [], ownerArguments: ResolvedType[] = []): none {
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
        if named.typeArgs.length == 0 && (named.name == "Reflectable" || named.name == "Serializable") {
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
        if named.typeArgs.length == 0 && named.name == "Serializable" {
          result := memberType(state, arguments[index], "fromSerialValue", span)
          if result.kind == "unknown" { reportConstraintViolation(state, names[index], arguments[index], named.name, span) }
          continue
        }
      }
      _ -> { }
    }
    resolvedConstraint := resolveType(state, annotation, module, constraintScope, false)
    substitutedConstraint := substituteTypeParams(substituteTypeParams(resolvedConstraint, ownerNames, ownerArguments), names, arguments)
    if isNumericConstraint(substitutedConstraint) {
      if !satisfiesNumericConstraint(arguments[index], substitutedConstraint) { reportConstraintViolation(state, names[index], arguments[index], typeName(substitutedConstraint), span) }
    } else if !satisfiesInterfaceBound(state.result, arguments[index], substitutedConstraint) {
      let detail = ""
      if satisfiesInterfaceInstanceBound(state.result, arguments[index], substitutedConstraint) {
        detail = "; it must be a class or struct providing the interface's static members as non-private, read-only fields and matching methods"
      }
      reportConstraintViolation(state, names[index], arguments[index], typeName(substitutedConstraint), span, detail)
    }
  }
}

function reportConstraintViolation(state: CheckerState, typeParam: string, argument: ResolvedType, constraint: string, span: SourceSpan, detail: string = ""): none {
  typeError(state, "Type \"" + typeName(argument) + "\" does not satisfy constraint \"" + constraint + "\" for type parameter \"" + typeParam + "\"" + detail, span)
}
