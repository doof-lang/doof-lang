// Generic type-argument inference from checked argument types.

import { ArrayResolvedType, ClassType, InterfaceType, FunctionType, MapResolvedType, ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, TupleResolvedType, TypeParameterType, WeakResolvedType } from "./semantic"

export function inferTypeArgument(pattern: ResolvedType, actual: ResolvedType, name: string): ResolvedType | none {
  case pattern {
    parameter: TypeParameterType -> { if parameter.name == name { return actual } }
    array: ArrayResolvedType -> {
      case actual {
        concrete: ArrayResolvedType -> { return inferTypeArgument(array.elementType, concrete.elementType, name) }
        _ -> { }
      }
    }
    map: MapResolvedType -> {
      case actual {
        concrete: MapResolvedType -> {
          key := inferTypeArgument(map.keyType, concrete.keyType, name)
          if key != none { return key }
          return inferTypeArgument(map.valueType, concrete.valueType, name)
        }
        _ -> { }
      }
    }
    set_: SetResolvedType -> {
      case actual {
        concrete: SetResolvedType -> { return inferTypeArgument(set_.elementType, concrete.elementType, name) }
        _ -> { }
      }
    }
    stream: StreamResolvedType -> {
      case actual {
        concrete: StreamResolvedType -> { return inferTypeArgument(stream.elementType, concrete.elementType, name) }
        _ -> { }
      }
    }
    class_: ClassType -> {
      case actual {
        concrete: ClassType -> {
          if class_.symbol.module != concrete.symbol.module || class_.symbol.name != concrete.symbol.name { return none }
          for i of 0..<class_.typeArgs.length {
            if i < concrete.typeArgs.length {
              candidate := inferTypeArgument(class_.typeArgs[i], concrete.typeArgs[i], name)
              if candidate != none { return candidate }
            }
          }
        }
        _ -> { }
      }
    }
    interface_: InterfaceType -> {
      case actual {
        concrete: InterfaceType -> {
          for i of 0..<interface_.typeArgs.length {
            if i < concrete.typeArgs.length {
              candidate := inferTypeArgument(interface_.typeArgs[i], concrete.typeArgs[i], name)
              if candidate != none { return candidate }
            }
          }
        }
        _ -> { }
      }
    }
    function_: FunctionType -> {
      case actual {
        concrete: FunctionType -> {
          for i of 0..<function_.params.length {
            if i < concrete.params.length {
              candidate := inferTypeArgument(function_.params[i].type_, concrete.params[i].type_, name)
              if candidate != none { return candidate }
            }
          }
          return inferTypeArgument(function_.returnType, concrete.returnType, name)
        }
        _ -> { }
      }
    }
    result_: ResultResolvedType -> {
      case actual {
        concrete: ResultResolvedType -> {
          value := inferTypeArgument(result_.valueType, concrete.valueType, name)
          if value != none { return value }
          return inferTypeArgument(result_.errorType, concrete.errorType, name)
        }
        _ -> { }
      }
    }
    tuple: TupleResolvedType -> {
      case actual {
        concrete: TupleResolvedType -> {
          for i of 0..<tuple.elements.length {
            if i < concrete.elements.length {
              candidate := inferTypeArgument(tuple.elements[i], concrete.elements[i], name)
              if candidate != none { return candidate }
            }
          }
        }
        _ -> { }
      }
    }
    weak_: WeakResolvedType -> {
      case actual {
        concrete: WeakResolvedType -> { return inferTypeArgument(weak_.inner, concrete.inner, name) }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}
