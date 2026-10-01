// Built-in array member signatures and the callback conventions they share.
//
// Element callbacks receive `(it: T, index: int)`; accumulator callbacks
// receive `(acc: U, it: T, index: int)`. Lambdas bind those parameters by name
// (see checker-lambdas), while a named function value may omit the trailing
// `index`, which the runtime detects from the callback's arity.
import { ArrayResolvedType, FunctionParamType, FunctionType, PromiseType, ResolvedType } from "./semantic"
import { SourceSpan } from "./ast"
import { arrayType, functionType, noneType, primitive, resultType, typeParameter, unionType, unknownType } from "./checker-types"
import { CheckerState } from "./checker-state"
import { deprecatedBuildReadonly, typeError } from "./checker-common"

const mutatingMethods: string[] = ["push", "reserve", "pop", "takeFirstCompleted", "sort"]

export function arrayMemberType(state: CheckerState, array: ArrayResolvedType, property: string, span: SourceSpan): ResolvedType {
  element := array.elementType
  if property == "length" { return primitive("int") }
  if array.readonly_ && mutatingMethods.contains(property) {
    typeError(state, "Method \"" + property + "\" is not available on readonly array", span)
    return unknownType()
  }
  if property == "push" { return functionType([param("value", element)], noneType()) }
  if property == "contains" { return functionType([param("value", element)], primitive("bool")) }
  if property == "indexOf" { return functionType([param("value", element)], primitive("int")) }
  if property == "reserve" { return functionType([param("capacity", primitive("int"))], noneType()) }
  if property == "pop" { return functionType([], resultType(element, primitive("string"))) }
  if property == "takeFirstCompleted" {
    case element {
      promise: PromiseType -> { return functionType([], resultType(promise.valueType, primitive("string"))) }
      _ -> { return unknownType() }
    }
  }
  if property == "some" || property == "every" { return functionType([param("predicate", elementCallback(element, primitive("bool")))], primitive("bool")) }
  if property == "find" { return functionType([param("predicate", elementCallback(element, primitive("bool")))], unionType([element, noneType()])) }
  if property == "filter" { return functionType([param("predicate", elementCallback(element, primitive("bool")))], arrayType(element, array.readonly_)) }
  if property == "forEach" { return functionType([param("action", elementCallback(element, noneType()))], noneType()) }
  if property == "map" {
    mapped := typeParameter("U")
    return functionType([param("mapper", elementCallback(element, mapped))], arrayType(mapped, array.readonly_), ["U"])
  }
  if property == "reduce" || property == "reduceRight" {
    accumulator := typeParameter("U")
    reducer := functionType([param("acc", accumulator), param("it", element), param("index", primitive("int"))], accumulator)
    return functionType([param("initial", accumulator), param("reducer", reducer)], accumulator, ["U"])
  }
  if property == "sort" {
    comparer := functionType([param("a", element), param("b", element)], primitive("int"))
    return functionType([param("compare", comparer)], noneType())
  }
  if property == "slice" { return functionType([param("start", primitive("int")), param("end", primitive("int"))], arrayType(element, array.readonly_)) }
  if array.readonly_ && (property == "buildReadonly" || property == "drainToReadonly" || property == "cloneReadonly") {
    typeError(state, "Method \"" + property + "\" is not available on readonly array", span)
    return unknownType()
  }
  if property == "buildReadonly" { deprecatedBuildReadonly(state, span); return functionType([], arrayType(element, true)) }
  if property == "drainToReadonly" || property == "cloneReadonly" { return functionType([], arrayType(element, true)) }
  if property == "cloneMutable" { return functionType([], arrayType(element)) }
  return unknownType()
}

/**
 * Narrows an index-carrying callback parameter to a named function value's
 * shorter arity, so `items.map(format)` accepts `format(value: int)`.
 * Returns none when the signature has no such callback or the arity is not a
 * strict prefix that keeps every non-index parameter.
 */
export function withCallbackArity(signature: FunctionType, parameterIndex: int, arity: int): FunctionType | none {
  if parameterIndex < 0 || parameterIndex >= signature.params.length { return none }
  case signature.params[parameterIndex].type_ {
    callback: FunctionType -> {
      count := callback.params.length
      if count == 0 || callback.params[count - 1].name != "index" || arity != count - 1 { return none }
      let narrowedParams: FunctionParamType[] = []
      for i of 0..<arity { narrowedParams.push(callback.params[i]) }
      let params: FunctionParamType[] = []
      for i of 0..<signature.params.length {
        current := signature.params[i]
        params.push(if i == parameterIndex then param(current.name, functionType(narrowedParams, callback.returnType)) else current)
      }
      case functionType(params, signature.returnType, signature.typeParams) {
        narrowed: FunctionType -> { return narrowed }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}

function elementCallback(element: ResolvedType, returnType: ResolvedType): ResolvedType {
  return functionType([param("it", element), param("index", primitive("int"))], returnType)
}

function param(name: string, type_: ResolvedType): FunctionParamType {
  return FunctionParamType { name, type_, hasDefault: false }
}
