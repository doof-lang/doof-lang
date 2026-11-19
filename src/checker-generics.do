// Generic type-argument inference from checked argument types.

import { ArrayResolvedType, ClassType, InterfaceType, FunctionType, MapResolvedType, ResolvedType, ResultResolvedType, SuccessResolvedType, FailureResolvedType, SetResolvedType, StreamResolvedType, TupleResolvedType, TypeParameterType, WeakResolvedType } from "./semantic"

export function inferTypeArgument(pattern: ResolvedType, actual: ResolvedType, name: string): ResolvedType | none {
  case pattern {
    parameter: TypeParameterType -> { if parameter.name == name { return actual } }
    array: ArrayResolvedType -> {
      if concrete := actual as ArrayResolvedType { return inferTypeArgument(array.elementType, concrete.elementType, name) }
    }
    map: MapResolvedType -> {
      if concrete := actual as MapResolvedType {
        if key := inferTypeArgument(map.keyType, concrete.keyType, name) { return key }
        return inferTypeArgument(map.valueType, concrete.valueType, name)
      }
    }
    set_: SetResolvedType -> {
      if concrete := actual as SetResolvedType { return inferTypeArgument(set_.elementType, concrete.elementType, name) }
    }
    stream: StreamResolvedType -> {
      if concrete := actual as StreamResolvedType { return inferTypeArgument(stream.elementType, concrete.elementType, name) }
    }
    class_: ClassType -> {
      if concrete := actual as ClassType {
        if class_.symbol.module != concrete.symbol.module || class_.symbol.name != concrete.symbol.name { return none }
        for i of 0..<class_.typeArgs.length {
          if i < concrete.typeArgs.length {
            if candidate := inferTypeArgument(class_.typeArgs[i], concrete.typeArgs[i], name) { return candidate }
          }
        }
      }
    }
    interface_: InterfaceType -> {
      if concrete := actual as InterfaceType {
        for i of 0..<interface_.typeArgs.length {
          if i < concrete.typeArgs.length {
            if candidate := inferTypeArgument(interface_.typeArgs[i], concrete.typeArgs[i], name) { return candidate }
          }
        }
      }
    }
    function_: FunctionType -> {
      if concrete := actual as FunctionType {
        for i of 0..<function_.params.length {
          if i < concrete.params.length {
            if candidate := inferTypeArgument(function_.params[i].type_, concrete.params[i].type_, name) { return candidate }
          }
        }
        return inferTypeArgument(function_.returnType, concrete.returnType, name)
      }
    }
    result_: ResultResolvedType -> {
      if concrete := actual as ResultResolvedType {
        if value := inferTypeArgument(result_.valueType, concrete.valueType, name) { return value }
        return inferTypeArgument(result_.errorType, concrete.errorType, name)
      }
    }
    success: SuccessResolvedType -> {
      if concrete := actual as SuccessResolvedType { return inferTypeArgument(success.valueType, concrete.valueType, name) }
    }
    failure: FailureResolvedType -> {
      if concrete := actual as FailureResolvedType { return inferTypeArgument(failure.errorType, concrete.errorType, name) }
    }
    tuple: TupleResolvedType -> {
      if concrete := actual as TupleResolvedType {
        for i of 0..<tuple.elements.length {
          if i < concrete.elements.length {
            if candidate := inferTypeArgument(tuple.elements[i], concrete.elements[i], name) { return candidate }
          }
        }
      }
    }
    weak_: WeakResolvedType -> {
      if concrete := actual as WeakResolvedType { return inferTypeArgument(weak_.inner, concrete.inner, name) }
    }
    _ -> { }
  }
  return none
}
