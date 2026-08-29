// Contextual array and object literal inference.

import {
  ActorType, ArrayResolvedType, Binding, CheckResult, ClassType, EnumType, InterfaceType,
  Diagnostic, FunctionParamType, FunctionType,
  JsonValueResolvedType, MapResolvedType, NoneType, PrimitiveType, PromiseType, ResolvedType, ResultResolvedType, Scope, SemanticLocation, SemanticSpan, SetResolvedType, Symbol,
  StreamResolvedType, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType,
} from "./semantic"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  ArrayLiteral, ArrayType, AsExpression, AssignmentExpression, AstLocation, BinaryExpression, Block,
  BoolLiteral, CallExpression, CallerExpression, CharLiteral, ClassDeclaration, ClassField, ConstructExpression,
  ConstDeclaration, ContinueStatement, DestructuringStatement, DoubleLiteral,
  DotShorthand, EnumDeclaration, ExportDeclaration, ExportList, Expression, ExpressionStatement,
  FloatLiteral, ForOfStatement, ForStatement, FunctionDeclaration, AstFunctionType,
  IfExpression, IfStatement, ImmutableBinding, Identifier, ImportDeclaration,
  IndexExpression, IntLiteral, InterfaceDeclaration, LetDeclaration,
  LambdaExpression, LongLiteral, MemberExpression, NamedType, NoneLiteral,
  NamedImport, NamespaceImport, ObjectLiteral, ObjectProperty, Program,
  ReadonlyDeclaration, ReturnStatement, SourceSpan, Statement, StringLiteral,
  ThisExpression, TupleLiteral, TypeAliasDeclaration, TypeAnnotation,
  UnaryExpression, UnionType, WhileStatement, WithBinding, WithStatement, BreakStatement,
  YieldStatement, CaseArm, CaseExpression, CasePattern, CaseStatement, TypePattern, ValuePattern, WildcardPattern,
  TryStatement,
  AsyncExpression, RetireExpression, ActorCreationExpression, Parameter,
} from "./ast"
import {
  actorType, applyDeepReadonly, arrayType, classType, enumType, functionType, interfaceType, isNumeric, joinTypes,
  isJsonValueType, isSupportedHashCollectionType, jsonObjectType, jsonValueType, mapType, resultType, setType, streamType,
  noneType, numericResult, primitive, promiseType, sameType, tupleType, typeName, unionType,
  substituteTypeParams, typeParameter, unknownType,
} from "./checker-types"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization } from "./json-semantics"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { collectRetiredActorBindings, reportRetiredActorUses } from "./checker-actor-lifecycle"


import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { memberType } from "./checker-resolution"
import { finish, typeError } from "./checker-common"
import { optionalResolvedType, hasObjectProperty, lookup, declarationFor } from "./checker-symbols"
import { findClassField, isAssignableWithInterfaces } from "./checker-interfaces"

// Bare Map/Set annotations are declaration-local inference requests. Keep the
// literal inspection here so contextual literal typing and collection
// finalization share one owner in the Doof checker.
export function checkOmittedCollectionLiteral(state: CheckerState, annotation: TypeAnnotation, expression: Expression, scope: Scope): ResolvedType | none {
  case annotation {
    named: NamedType -> {
      if named.typeArgs.length != 0 { return none }
      if named.name == "Set" || named.name == "ReadonlySet" {
        case expression {
          array: ArrayLiteral -> {
            if array.elements.length == 0 {
              typeError(state, "Cannot infer " + named.name + " element type from an empty set literal; provide a full " + named.name + "<T> annotation", array.span)
              return finish(state, expression, setType(unknownType(), named.name == "ReadonlySet"))
            }
            inferred := checkArray(state, array, scope, none)
            case inferred {
              arrayType_: ArrayResolvedType -> {
                let hasConcreteElement = true
                case arrayType_.elementType {
                  _: UnknownType -> { hasConcreteElement = false; typeError(state, "Cannot infer " + named.name + " element type from this set literal; provide a full " + named.name + "<T> annotation", array.span) }
                  _: UnionResolvedType -> { hasConcreteElement = false; typeError(state, "Cannot infer " + named.name + " element type from heterogeneous set elements; provide a full " + named.name + "<T> annotation", array.span) }
                  _ -> { }
                }
                if hasConcreteElement && !isSupportedHashCollectionType(arrayType_.elementType) {
                  typeError(state, "Set element type \"" + typeName(arrayType_.elementType) + "\" is not supported; set elements must be byte, string, int, long, char, bool, or enum", array.span)
                }
                return finish(state, expression, setType(arrayType_.elementType, named.name == "ReadonlySet"))
              }
              _ -> { return finish(state, expression, setType(unknownType(), named.name == "ReadonlySet")) }
            }
          }
          _ -> {
            checkExpression(state, expression, scope, none)
            typeError(state, "Omitted type arguments for " + named.name + " require a same-site non-empty set literal", expression.span)
            return setType(unknownType(), named.name == "ReadonlySet")
          }
        }
      }
      if named.name == "Map" || named.name == "ReadonlyMap" {
        case expression {
          object: ObjectLiteral -> {
            if object.properties.length == 0 {
              typeError(state, "Cannot infer " + named.name + " type arguments from an empty map literal; provide a full " + named.name + "<K, V> annotation", object.span)
              return finish(state, expression, mapType(unknownType(), unknownType(), named.name == "ReadonlyMap"))
            }
            let keyType = unknownType()
            let valueType = unknownType()
            for property of object.properties {
              propertyKeyType := if property.key == none then primitive("string") else checkExpression(state, property.key!, scope, none)
              keyType = joinTypes(keyType, propertyKeyType)
              let propertyType = unknownType()
              if property.value != none { propertyType = checkExpression(state, property.value!, scope, none) }
              else {
                binding := lookup(scope, property.name)
                if binding == none { typeError(state, "Unknown shorthand property '" + property.name + "'", property.span) }
                else { property.resolvedBinding = binding; propertyType = binding!.type_ }
              }
              property.resolvedType = optionalResolvedType(propertyType)
              valueType = joinTypes(valueType, propertyType)
            }
            case keyType {
              _: UnknownType -> { typeError(state, "Cannot infer " + named.name + " key type from this map literal; provide a full " + named.name + "<K, V> annotation", object.span) }
              _: UnionResolvedType -> { typeError(state, "Cannot infer " + named.name + " key type from heterogeneous map keys; provide a full " + named.name + "<K, V> annotation", object.span) }
              _ -> {
                if !isSupportedHashCollectionType(keyType) { typeError(state, "Map key type \"" + typeName(keyType) + "\" is not supported; map keys must be byte, string, int, long, char, bool, or enum", object.span) }
              }
            }
            case valueType {
              _: UnknownType -> { typeError(state, "Cannot infer " + named.name + " type arguments from this map literal; provide a full " + named.name + "<K, V> annotation", object.span) }
              _: UnionResolvedType -> { typeError(state, "Cannot infer " + named.name + " value type from heterogeneous map values; provide a full " + named.name + "<K, V> annotation", object.span) }
              _ -> { }
            }
            return finish(state, expression, mapType(keyType, valueType, named.name == "ReadonlyMap"))
          }
          _ -> {
            checkExpression(state, expression, scope, none)
            typeError(state, "Omitted type arguments for " + named.name + " require a same-site non-empty map literal", expression.span)
            return mapType(unknownType(), unknownType(), named.name == "ReadonlyMap")
          }
        }
      }
    }
    _ -> { }
  }
  return none
}

export function checkArray(state: CheckerState, expression: ArrayLiteral, scope: Scope, expected: ResolvedType | none): ResolvedType {
  if expected != none {
    case expected! {
      _: JsonValueResolvedType -> {
        for item of expression.elements {
          actual := checkExpression(state, item, scope, optionalResolvedType(jsonValueType()))
          if !isAssignableWithInterfaces(state.result, actual, jsonValueType()) { typeError(state, "Cannot assign " + typeName(actual) + " to JsonValue", item.span) }
        }
        return finish(state, expression, expected!)
      }
      union_: UnionResolvedType -> {
        if containsJsonValue(state, union_) {
          for item of expression.elements {
            actual := checkExpression(state, item, scope, optionalResolvedType(jsonValueType()))
            if !isAssignableWithInterfaces(state.result, actual, jsonValueType()) { typeError(state, "Cannot assign " + typeName(actual) + " to JsonValue", item.span) }
          }
          return finish(state, expression, jsonValueType())
        }
      }
      _ -> { }
    }
  }
  if expression.elements.length == 0 && expected != none {
    case expected! {
      _: ArrayResolvedType -> { return finish(state, expression, expected!) }
      _: SetResolvedType -> { return finish(state, expression, expected!) }
      _ -> { }
    }
  }
  let expectedElement: ResolvedType | none = none
  if expected != none {
    case expected! {
      array: ArrayResolvedType -> { expectedElement = array.elementType }
      set: SetResolvedType -> { expectedElement = set.elementType }
      _ -> { }
    }
  }
  if expectedElement != none {
    for item of expression.elements {
      actual := checkExpression(state, item, scope, optionalResolvedType(expectedElement!))
      if !isAssignableWithInterfaces(state.result, actual, expectedElement!) { typeError(state, "Cannot assign " + typeName(actual) + " to " + typeName(expectedElement!), item.span) }
    }
    case expected! {
      array: ArrayResolvedType -> { return finish(state, expression, arrayType(expectedElement!, array.readonly_)) }
      set: SetResolvedType -> { return finish(state, expression, setType(expectedElement!, set.readonly_)) }
      _ -> { }
    }
  }
  let element = unknownType()
  for item of expression.elements { element = joinTypes(element, checkExpression(state, item, scope, none)) }
  return finish(state, expression, arrayType(element, expression.readonly_))
}

export function checkObject(state: CheckerState, expression: ObjectLiteral, scope: Scope, expected: ResolvedType | none): ResolvedType {
  if expected != none {
    case expected! {
      result: ResultResolvedType -> {
        let recognized = 0
        let hasValue = false
        let hasError = false
        for property of expression.properties {
          let propertyExpected: ResolvedType | none = none
          if property.name == "value" { recognized = recognized + 1; hasValue = true; propertyExpected = result.valueType }
          else if property.name == "error" { recognized = recognized + 1; hasError = true; propertyExpected = result.errorType }
          if property.value != none {
            property.resolvedType = optionalResolvedType(checkExpression(state, property.value!, scope, propertyExpected))
          } else {
            binding := lookup(scope, property.name)
            if binding == none { typeError(state, "Unknown shorthand property '" + property.name + "'", property.span); property.resolvedType = optionalResolvedType(unknownType()) }
            else { property.resolvedBinding = binding; property.resolvedType = optionalResolvedType(binding!.type_) }
          }
          if propertyExpected != none && !isAssignableWithInterfaces(state.result, property.resolvedType!, propertyExpected!) {
            typeError(state, "Cannot assign " + typeName(property.resolvedType!) + " to " + typeName(propertyExpected!), property.span)
          }
        }
        if hasValue && hasError { typeError(state, "Result object literal must contain either a 'value' field or an 'error' field, but not both", expression.span) }
        else if !hasValue && !hasError { typeError(state, "Result object literal must contain a 'value' field or an 'error' field", expression.span) }
        else if recognized != expression.properties.length { typeError(state, "Result object literal only supports 'value' and 'error' fields", expression.span) }
        return finish(state, expression, result)
      }
      class_: ClassType -> {
        checkedClass := checkClassObject(state, expression, scope, class_, false)
        if checkedClass != none { return checkedClass! }
      }
      union_: UnionResolvedType -> {
        if supportsUnionObjectInference(union_) {
          return checkUnionObject(state, expression, scope, union_)
        }
      }
      _ -> { }
    }
  }
  let expectedValue: ResolvedType | none = none
  if expected != none {
    case expected! {
      _: JsonValueResolvedType -> { expectedValue = jsonValueType() }
      union_: UnionResolvedType -> {
        if containsJsonValue(state, union_) { expectedValue = jsonValueType() }
      }
      map: MapResolvedType -> {
        for property of expression.properties {
          if property.key != none {
            actualKey := checkExpression(state, property.key!, scope, optionalResolvedType(map.keyType))
            if !isAssignableWithInterfaces(state.result, actualKey, map.keyType) { typeError(state, "Cannot assign " + typeName(actualKey) + " to map key type " + typeName(map.keyType), property.span) }
          } else if !sameType(map.keyType, primitive("string")) {
            typeError(state, "Cannot assign string to map key type " + typeName(map.keyType), property.span)
          }
        }
        expectedValue = map.valueType
      }
      _ -> { }
    }
  }
  for property of expression.properties {
    if property.value != none {
      property.resolvedType = optionalResolvedType(checkExpression(state, property.value!, scope, expectedValue))
      if expectedValue != none && !isAssignableWithInterfaces(state.result, property.resolvedType!, expectedValue!) {
        typeError(state, "Cannot assign " + typeName(property.resolvedType!) + " to " + typeName(expectedValue!), property.span)
      }
    }
  }
  if expected != none {
    case expected! {
      _: JsonValueResolvedType -> { return finish(state, expression, expected!) }
      union_: UnionResolvedType -> { if containsJsonValue(state, union_) { return finish(state, expression, jsonValueType()) } }
      _: MapResolvedType -> { return finish(state, expression, expected!) }
      _ -> { }
    }
  }
  return finish(state, expression, mapType(primitive("string"), jsonValueType()))
}

function checkClassObject(state: CheckerState, expression: ObjectLiteral, scope: Scope, class_: ClassType, structural: bool): ResolvedType | none {
  declaration := declarationFor(state.result, class_.symbol)
  if declaration == none { return none }
  case declaration! {
    classDeclaration: ClassDeclaration -> {
      expression.resolvedClass = classDeclaration
      for property of expression.properties {
        field := findClassField(classDeclaration.fields, property.name)
        if field == none || field!.static_ || (!structural && field!.const_) {
          typeError(state, "Unknown field '" + property.name + "' for " + class_.name, property.span)
          decorateObjectProperty(state, property, scope, none)
          continue
        }
        fieldType := memberType(state, class_, property.name, property.span)
        decorateObjectProperty(state, property, scope, optionalResolvedType(fieldType))
        if !isAssignableWithInterfaces(state.result, property.resolvedType!, fieldType) { typeError(state, "Cannot assign " + typeName(property.resolvedType!) + " to " + typeName(fieldType), property.span) }
        if structural && field!.const_ {
          if property.value == none || field!.defaultValue == none || !sameFixedFieldValue(property.value!, field!.defaultValue!) {
            typeError(state, "Field '" + property.name + "' must match its literal-valued declaration", property.span)
          }
        }
      }
      for field of classDeclaration.fields {
        if field.static_ || (!structural && field.const_) { continue }
        for name of field.names {
          required := field.const_ || field.defaultValue == none
          if required && !hasObjectProperty(expression.properties, name) { typeError(state, "Missing required field '" + name + "'", expression.span) }
        }
      }
      return finish(state, expression, class_)
    }
    _ -> { }
  }
  return none
}

function supportsUnionObjectInference(union_: UnionResolvedType): bool {
  let hasNominal = false
  for member of union_.types {
    case member {
      _: JsonValueResolvedType -> { return false }
      _: MapResolvedType -> { return false }
      _: ClassType -> { hasNominal = true }
      _ -> { }
    }
  }
  return hasNominal
}

function checkUnionObject(state: CheckerState, expression: ObjectLiteral, scope: Scope, union_: UnionResolvedType): ResolvedType {
  if expression.spread != none {
    decorateUnresolvedObject(state, expression, scope)
    typeError(state, "Cannot infer a sum type member from an object literal with spread fields; use explicit Type { ... } construction", expression.span)
    return finish(state, expression, union_)
  }
  let matches: ClassType[] = []
  let nominalNames: string[] = []
  for member of union_.types {
    case member {
      class_: ClassType -> {
        nominalNames.push(class_.name)
        if objectShapeMatchesClass(state, expression, class_) { matches.push(class_) }
      }
      _ -> { }
    }
  }
  if matches.length == 1 {
    checked := checkClassObject(state, expression, scope, matches[0], true)
    if checked != none { return checked! }
  }
  decorateUnresolvedObject(state, expression, scope)
  if matches.length == 0 {
    typeError(state, "Object literal does not match any constructible member of " + typeName(union_) + "; candidates: " + joinNames(nominalNames) + ". Use explicit Type { ... } construction", expression.span)
  } else {
    let matchingNames: string[] = []
    for match of matches { matchingNames.push(match.name) }
    typeError(state, "Ambiguous object literal for " + typeName(union_) + "; matching members: " + joinNames(matchingNames) + ". Use explicit Type { ... } construction", expression.span)
  }
  return finish(state, expression, union_)
}

function objectShapeMatchesClass(state: CheckerState, expression: ObjectLiteral, class_: ClassType): bool {
  declaration := declarationFor(state.result, class_.symbol)
  if declaration == none { return false }
  case declaration! {
    classDeclaration: ClassDeclaration -> {
      for property of expression.properties {
        if property.key != none { return false }
        field := findClassField(classDeclaration.fields, property.name)
        if field == none || field!.static_ { return false }
      }
      for field of classDeclaration.fields {
        if field.static_ { continue }
        for name of field.names {
          if (field.const_ || field.defaultValue == none) && !hasObjectProperty(expression.properties, name) { return false }
        }
      }
      return true
    }
    _ -> { }
  }
  return false
}

function decorateObjectProperty(state: CheckerState, property: ObjectProperty, scope: Scope, expected: ResolvedType | none): none {
  if property.key != none { checkExpression(state, property.key!, scope, none) }
  if property.value != none { property.resolvedType = optionalResolvedType(checkExpression(state, property.value!, scope, expected)) }
  else {
    binding := lookup(scope, property.name)
    if binding == none { typeError(state, "Unknown shorthand property '" + property.name + "'", property.span); property.resolvedType = optionalResolvedType(unknownType()) }
    else { property.resolvedBinding = binding; property.resolvedType = optionalResolvedType(binding!.type_) }
  }
}

function decorateUnresolvedObject(state: CheckerState, expression: ObjectLiteral, scope: Scope): none {
  if expression.spread != none { checkExpression(state, expression.spread!, scope, none) }
  for property of expression.properties { decorateObjectProperty(state, property, scope, none) }
}

function sameFixedFieldValue(actual: Expression, expected: Expression): bool {
  case expected {
    expectedString: StringLiteral -> {
      case actual { actualString: StringLiteral -> { return actualString.value == expectedString.value } _ -> { return false } }
    }
    expectedInt: IntLiteral -> {
      case actual { actualInt: IntLiteral -> { return actualInt.value == expectedInt.value } _ -> { return false } }
    }
    expectedLong: LongLiteral -> {
      case actual { actualLong: LongLiteral -> { return actualLong.value == expectedLong.value } _ -> { return false } }
    }
    expectedFloat: FloatLiteral -> {
      case actual { actualFloat: FloatLiteral -> { return actualFloat.value == expectedFloat.value } _ -> { return false } }
    }
    expectedDouble: DoubleLiteral -> {
      case actual { actualDouble: DoubleLiteral -> { return actualDouble.value == expectedDouble.value } _ -> { return false } }
    }
    expectedChar: CharLiteral -> {
      case actual { actualChar: CharLiteral -> { return actualChar.value == expectedChar.value } _ -> { return false } }
    }
    expectedBool: BoolLiteral -> {
      case actual { actualBool: BoolLiteral -> { return actualBool.value == expectedBool.value } _ -> { return false } }
    }
    _: NoneLiteral -> {
      case actual { _: NoneLiteral -> { return true } _ -> { return false } }
    }
    expectedMember: MemberExpression -> {
      case actual {
        actualMember: MemberExpression -> { return actualMember.property == expectedMember.property }
        actualDot: DotShorthand -> { return actualDot.name == expectedMember.property }
        _ -> { return false }
      }
    }
    expectedDot: DotShorthand -> {
      case actual {
        actualMember: MemberExpression -> { return actualMember.property == expectedDot.name }
        actualDot: DotShorthand -> { return actualDot.name == expectedDot.name }
        _ -> { return false }
      }
    }
    expectedUnary: UnaryExpression -> {
      case actual {
        actualUnary: UnaryExpression -> { return actualUnary.operator == expectedUnary.operator && sameFixedFieldValue(actualUnary.operand, expectedUnary.operand) }
        _ -> { return false }
      }
    }
    _ -> { return false }
  }
  return false
}

function joinNames(names: string[]): string {
  let result = ""
  for i of 0..<names.length {
    if i > 0 { result = result + ", " }
    result = result + names[i]
  }
  return result
}

export function containsJsonValue(state: CheckerState, union_: UnionResolvedType): bool {
  for member of union_.types { if isJsonValueType(member) { return true } }
  return false
}
