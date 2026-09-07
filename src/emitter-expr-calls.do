// Call target selection and runtime-specific member dispatch.

import { emitClassCall } from "./emitter-construction"

import { emitCallArguments, emitDispatchCallArguments } from "./emitter-call-arguments"
import { weakTargetAllowsNone, weakTargetUsesVariant } from "./emitter-carriers"
import { CallExpression, Expression, Identifier, MemberExpression } from "./ast"
import { ActorType, ArrayResolvedType, ClassType, EnumType, FunctionType, InterfaceType, MapResolvedType, NoneType, ResultResolvedType, ResolvedType, SetResolvedType, StreamResolvedType, TypeParameterType, UnionResolvedType, WeakResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { substituteTypeParams } from "./checker-types"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { decoratedExpressionType, exprModuleNamespaceFor, variantVisitValue } from "./emitter-expr-utils"
import { emitContextReturnType, emitContextType, emitResultPayloadType, emitType, naturalNullableUnionMember, specializeEmitType, usesVariantRepresentation } from "./emitter-types"
import { classInstantiationKey, functionInstantiationKey, methodInstantiationKey } from "./emitter-monomorphize"
import { emitSyncActorCall } from "./emitter-expr-actor"

export function emitCall(expression: CallExpression, context: EmitContext, expected: ResolvedType | none = none): string {
  case expression.callee {
    member: MemberExpression -> {
      if member.object.resolvedType != none {
        case member.object.resolvedType! {
          _: WeakResolvedType -> {
            if member.optional || member.force { return emitWeakMemberCall(expression, member, context) }
          }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  case expression.callee {
    identifier: Identifier -> {
      if isBuiltinIdentifier(identifier, "catchPanic") && expression.args.length == 1 {
        case expression.resolvedType! {
          result: ResultResolvedType -> {
            callback := emitExpression(expression.args[0].value, context)
            successType := emitResultPayloadType(result.valueType, context.modulePath, context.names)
            if result.valueType.kind == "none" {
              return "[&]() -> doof::Result<void, std::string> { try { " + callback + ".call(); return doof::Success<void>{}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"
            }
            return "[&]() -> doof::Result<" + successType + ", std::string> { try { return doof::Success<" + successType + ">{" + callback + ".call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"
          }
          _ -> { panic("catchPanic has no Result type") }
        }
      }
    }
    _ -> { }
  }
  case expression.callee {
    identifier: Identifier -> {
      if (identifier.name == "Success" || identifier.name == "Failure") && isBuiltinIdentifier(identifier, identifier.name) {
        let resultType: ResolvedType | none = none
        if expected != none { resultType = expected! }
        else if expression.resolvedType != none { resultType = expression.resolvedType! }
        if resultType == none { panic(identifier.name + " has no expected Result type") }
        case resultType! {
          result: ResultResolvedType -> {
            if expression.args.length == 0 { return "doof::" + identifier.name + "<" + emitContextReturnType(if identifier.name == "Success" then result.valueType else result.errorType, context) + ">{}" }
            valueType := if identifier.name == "Success" then result.valueType else result.errorType
            value := emitExpression(expression.args[0].value, context, valueType)
            payloadType := emitContextReturnType(valueType, context)
            return "doof::" + identifier.name + "<" + payloadType + ">{ " + value + " }"
          }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  case expression.callee {
    member: MemberExpression -> {
      if member.object.resolvedType != none {
        case member.object.resolvedType! {
          actor: ActorType -> { return emitSyncActorCall(expression, member, actor, context) }
          resultType: ResultResolvedType -> {
            if member.property == "isSuccess" { return "doof::is_success(" + emitExpression(member.object, context) + ")" }
            if member.property == "isFailure" { return "doof::is_failure(" + emitExpression(member.object, context) + ")" }
            if member.property == "unwrapOr" && expression.args.length == 1 {
              temporaryName := "_result_unwrap_" + string(context.tryCounter)
              context.tryCounter += 1
              object := emitExpression(member.object, context)
              fallback := emitExpression(expression.args[0].value, context, resultType.valueType)
              return "[&]() -> " + emitType(resultType.valueType, context.modulePath, context.names) + " { auto " + temporaryName + " = " + object + "; if (doof::is_failure(" + temporaryName + ")) return " + fallback + "; return std::move(doof::success_value(" + temporaryName + ")); }()"
            }
          }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  construction := emitClassCall(expression, context)
  if construction != none { return construction! }
  case expression.callee {
    member: MemberExpression -> {
      let arrayObjectType = decoratedExpressionType(member.object)
      if arrayObjectType != none {
        arrayObjectType = specializeEmitType(arrayObjectType!, context)
        if member.force {
          forcedType := naturalNullableUnionMember(arrayObjectType!)
          if forcedType != none { arrayObjectType = forcedType }
        }
      }
      let nominalReceiver = false
      if arrayObjectType != none {
        case arrayObjectType! {
          _: ClassType -> { nominalReceiver = true }
          _ -> { }
        }
      }
      if member.property == "length" {
        if arrayObjectType != none {
          case arrayObjectType! {
            class_: ClassType -> { return emitExpression(member.object, context) + (if class_.symbol.kind == "struct" then "." else "->") + "length()" }
            _ -> { }
          }
        }
      }
      if arrayObjectType != none {
        case arrayObjectType! {
          _: InterfaceType -> {
            if member.property == "fromJsonValue" && expression.resolvedFunction == none && !member.resolvedCallableField { return emitInterfaceJsonCall(member, expression, context) }
            return emitVariantMemberCall(member, expression, context)
          }
          _: StreamResolvedType -> { return emitInterfaceCall(member, expression, context) }
          union_: UnionResolvedType -> { if usesVariantRepresentation(union_) { return emitVariantMemberCall(member, expression, context) } }
          _: ArrayResolvedType -> {
            if member.property == "takeFirstCompleted" { return "doof::promise_take_first_completed(" + emitExpression(member.object, context) + ")" }
            if member.property == "buildReadonly" || member.property == "drainToReadonly" { return "doof::array_drainToReadonly(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "cloneReadonly" { return "doof::array_cloneReadonly(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "cloneMutable" { return "doof::array_cloneMutable(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "contains" { return "doof::array_contains(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
            if member.property == "indexOf" { return "doof::array_indexOf(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
            if member.property == "some" { return "doof::array_some(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
            if member.property == "every" { return "doof::array_every(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
            if member.property == "filter" { return "doof::array_filter(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
            if member.property == "map" { return "doof::array_map(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
          }
          map: MapResolvedType -> {
            if member.property == "has" {
              context.tryCounter = context.tryCounter + 1
              temporary := "_map_has_" + string(context.tryCounter)
              return "[&]() -> bool { auto " + temporary + " = " + emitExpression(member.object, context) + "; return " + temporary + "->find(" + emitExpression(expression.args[0].value, context) + ") != " + temporary + "->end(); }()"
            }
            if member.property == "set" { return "doof::map_set<" + emitContextType(map.keyType, context) + ", " + emitContextType(map.valueType, context) + ">(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context, map.keyType) + ", " + emitExpression(expression.args[1].value, context, map.valueType) + ", \"\", 0)" }
            if member.property == "get" && expression.args.length > 0 { return "doof::map_get(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
            if member.property == "keys" { return "doof::map_keys(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "values" { return "doof::map_values(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "buildReadonly" || member.property == "drainToReadonly" { return "doof::map_drainToReadonly(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "cloneReadonly" { return "doof::map_cloneReadonly(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "cloneMutable" { return "doof::map_cloneMutable(" + emitExpression(member.object, context) + ", \"\", 0)" }
          }
          _: SetResolvedType -> {
            if member.property == "has" { return "(" + emitExpression(member.object, context) + "->count(" + emitExpression(expression.args[0].value, context) + ") > 0)" }
            if member.property == "add" { return emitExpression(member.object, context) + "->insert(" + emitExpression(expression.args[0].value, context) + ")" }
            if member.property == "delete" { return emitExpression(member.object, context) + "->erase(" + emitExpression(expression.args[0].value, context) + ")" }
            if member.property == "values" { return "doof::set_values(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "buildReadonly" || member.property == "drainToReadonly" { return "doof::set_drainToReadonly(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "cloneReadonly" { return "doof::set_cloneReadonly(" + emitExpression(member.object, context) + ", \"\", 0)" }
            if member.property == "cloneMutable" { return "doof::set_cloneMutable(" + emitExpression(member.object, context) + ", \"\", 0)" }
          }
          enum_: EnumType -> {
            if member.property == "fromName" || member.property == "fromValue" {
              args := if expression.args.length == 0 then "" else emitExpression(expression.args[0].value, context)
              return emitContextType(enum_, context) + "_" + member.property + "(" + args + ")"
            }
            if member.property == "values" { return emitContextType(enum_, context) + "_values()" }
            if member.property == "toJsonValue" {
              let receiver = emitExpression(member.object, context)
              if member.force { receiver = "doof::unwrap_optional(" + receiver + ")" }
              return emitContextType(enum_, context) + "_toJsonValue(" + receiver + ")"
            }
            if member.property == "fromJsonValue" {
              let args = ""
              for i of 0..<expression.args.length {
                if i > 0 { args = args + ", " }
                args = args + emitExpression(expression.args[i].value, context)
              }
              if expression.args.length == 1 { args = args + ", false" }
              return emitContextType(enum_, context) + "_fromJsonValue(" + args + ")"
            }
          }
          _ -> { }
        }
      }
      if !nominalReceiver && member.property == "startsWith" { return emitBuiltinCall("doof::string_startsWith", member.object, expression, context) }
      if !nominalReceiver && member.property == "endsWith" { return emitBuiltinCall("doof::string_endsWith", member.object, expression, context) }
      if !nominalReceiver && member.property == "substring" { return emitBuiltinCall("doof::string_substring", member.object, expression, context) }
      if !nominalReceiver && member.property == "replaceAll" { return emitBuiltinCall("doof::string_replaceAll", member.object, expression, context) }
      if !nominalReceiver && member.property == "contains" { return emitBuiltinCall("doof::string_contains", member.object, expression, context) }
      if !nominalReceiver && member.property == "indexOf" { return emitBuiltinCall("doof::string_indexOf", member.object, expression, context) }
      objectType := decoratedExpressionType(member.object)
      if objectType != none {
        case objectType! {
          _: ArrayResolvedType -> {
            if member.property == "slice" && expression.args.length == 2 {
              return "doof::array_slice(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", " + emitExpression(expression.args[1].value, context) + ", \"\", 0)"
            }
          }
          _ -> { }
        }
      }
      if !nominalReceiver && member.property == "trim" && expression.args.length == 0 { return "doof::string_trim(" + emitExpression(member.object, context) + ")" }
      if !nominalReceiver && member.property == "trimStart" && expression.args.length == 0 { return "doof::string_trimStart(" + emitExpression(member.object, context) + ")" }
      if !nominalReceiver && member.property == "repeat" && expression.args.length == 1 { return "doof::string_repeat(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ")" }
      if !nominalReceiver && member.property == "slice" { return "doof::string_slice(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ")" }
      if !nominalReceiver && member.property == "charAt" { return "doof::string_at(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", \"\", 0)" }
      if !nominalReceiver && member.property == "padStart" {
        fill := if expression.args.length > 1 then emitExpression(expression.args[1].value, context) else "U' '"
        return "doof::string_padStart(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", " + fill + ")"
      }
      if !nominalReceiver && member.property == "padEnd" {
        fill := if expression.args.length > 1 then emitExpression(expression.args[1].value, context) else "U' '"
        return "doof::string_padEnd(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ", " + fill + ")"
      }
      if !nominalReceiver && member.property == "trimEnd" && expression.args.length == 0 { return "doof::string_trimEnd(" + emitExpression(member.object, context) + ")" }
      if !nominalReceiver && member.property == "trimEnd" && expression.args.length == 1 { return "doof::string_trimEnd(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ")" }
      if !nominalReceiver && member.property == "toLowerCase" { return "doof::string_toLowerCase(" + emitExpression(member.object, context) + ")" }
      if !nominalReceiver && member.property == "toUpperCase" { return "doof::string_toUpperCase(" + emitExpression(member.object, context) + ")" }
      if !nominalReceiver && member.property == "split" { return "doof::string_split(" + emitExpression(member.object, context) + ", " + emitExpression(expression.args[0].value, context) + ")" }
      if !nominalReceiver && member.property == "pop" && expression.args.length == 0 { return "doof::array_pop(" + emitExpression(member.object, context) + ")" }
      if member.property == "toJsonObject" && expression.args.length == 0 {
        object := emitExpression(member.object, context)
        objectType := decoratedExpressionType(member.object)
        if objectType != none {
          case objectType! {
            class_: ClassType -> { if class_.symbol.kind == "struct" { return object + ".toJsonObject()" } }
            _ -> { }
          }
        }
        return object + "->toJsonObject()"
      }
      if member.property == "fromJsonValue" && (!nominalReceiver || member.resolvedStaticOwner != none) {
        object := emitExpression(member.object, context)
        let args = ""
        for i of 0..<expression.args.length {
          if i > 0 { args = args + ", " }
          args = args + emitExpression(expression.args[i].value, context)
        }
        if expression.args.length == 1 { args = args + ", false" }
        objectType := decoratedExpressionType(member.object)
        if objectType != none {
          case objectType! {
            _: InterfaceType -> { return object + "_fromJsonValue(" + args + ")" }
            _ -> { }
          }
        }
        return object + "::fromJsonValue(" + args + ")"
      }
    }
    _ -> { }
  }
  let callee = emitExpression(expression.callee, context)
  if expression.callee.kind == "identifier" {
    case expression.callee {
      identifier: Identifier -> {
        if identifier.resolvedBinding != none && identifier.resolvedBinding!.kind == "builtin" && isBuiltinName(identifier.name) { callee = builtinName(identifier.name) }
      }
      _ -> { }
    }
  }
  let functionType: FunctionType | none = none
  if expression.callee.resolvedType != none {
    case expression.callee.resolvedType! {
      resolved: FunctionType -> { functionType = resolved }
      _ -> { }
    }
  }
  let concreteGenericArgs: ResolvedType[] = []
  for argument of expression.resolvedGenericTypeArgs { concreteGenericArgs.push(specializeEmitType(argument, context)) }
  if functionType != none && concreteGenericArgs.length > 0 {
    substituted := substituteTypeParams(functionType!, functionType!.typeParams, concreteGenericArgs)
    case substituted {
      specialized: FunctionType -> { functionType = specialized }
      _ -> { }
    }
  }
  functionDeclaration := expression.resolvedFunction
  let usesConcreteInstantiation = false
  if functionDeclaration != none && functionDeclaration!.typeParams.length > 0 {
    let targetModule = expression.resolvedFunctionModule
    let concreteMethodName = ""
    case expression.callee {
      identifier: Identifier -> {
        if identifier.resolvedBinding != none {
          if identifier.resolvedBinding!.kind == "method" && identifier.resolvedBinding!.symbol != none {
            symbol := identifier.resolvedBinding!.symbol!
            let ownerArgs: ResolvedType[] = []
            for typeParam of symbol.typeParams {
              ownerArgs.push(specializeEmitType(TypeParameterType { name: typeParam }, context))
            }
            ownerKey := classInstantiationKey(symbol.module, symbol.name, ownerArgs)
            methodKey := methodInstantiationKey(ownerKey, functionDeclaration!.name, concreteGenericArgs)
            concreteMethodName = concreteMethodNameFor(context, methodKey)
          } else if identifier.resolvedBinding!.symbol != none { targetModule = identifier.resolvedBinding!.symbol!.module }
          else if identifier.resolvedBinding!.module != "" { targetModule = identifier.resolvedBinding!.module }
        }
      }
      member: MemberExpression -> {
        if member.object.resolvedType != none {
          case specializeEmitType(member.object.resolvedType!, context) {
            class_: ClassType -> {
              targetModule = class_.symbol.module
              ownerKey := classInstantiationKey(class_.symbol.module, class_.name, class_.typeArgs)
              methodKey := methodInstantiationKey(ownerKey, functionDeclaration!.name, concreteGenericArgs)
              concreteMethodName = concreteMethodNameFor(context, methodKey)
            }
            _ -> { }
          }
        }
      }
      _ -> { }
    }
    if concreteMethodName != "" {
      usesConcreteInstantiation = true
      case expression.callee {
        _: Identifier -> { callee = concreteMethodName }
        member: MemberExpression -> { callee = callee.substring(0, callee.length - member.property.length) + concreteMethodName }
        _ -> { }
      }
    } else {
      key := functionInstantiationKey(targetModule, functionDeclaration!.name, concreteGenericArgs)
      concreteName := concreteFunctionName(context, key)
      if concreteName != "" {
        usesConcreteInstantiation = true
        callee = if targetModule != "" && targetModule != context.modulePath then "::" + exprModuleNamespaceFor(targetModule, context.names) + "::" + concreteName else concreteName
      }
    }
  }
  if concreteGenericArgs.length > 0 && functionDeclaration != none && functionDeclaration!.typeParams.length > 0 && !usesConcreteInstantiation {
    panic(
      "Missing concrete generic instantiation for " + context.modulePath + "::" + functionDeclaration!.name +
      " at line " + string(expression.span.start.line) + ":" + string(expression.span.start.column),
    )
  }
  let invokesCallback = false
  case expression.callee {
    identifier: Identifier -> {
      invokesCallback = !(identifier.resolvedBinding != none && identifier.resolvedBinding!.kind == "builtin" && isBuiltinName(identifier.name)) && functionType != none && functionDeclaration == none
    }
    member: MemberExpression -> { invokesCallback = member.resolvedCallableField && functionType != none }
    _ -> { invokesCallback = functionType != none && functionDeclaration == none }
  }
  callPrefix := if invokesCallback then callee + ".call(" else callee + "("
  return callPrefix + emitCallArguments(expression, context, functionType) + ")"
}

function emitWeakMemberCall(expression: CallExpression, member: MemberExpression, context: EmitContext): string {
  context.tryCounter = context.tryCounter + 1
  storage := "_weak_storage_" + string(context.tryCounter)
  temporary := "_weak_value_" + string(context.tryCounter)
  object := emitExpression(member.object, context)
  let nullable = false
  case member.object.resolvedType! {
    weak_: WeakResolvedType -> { nullable = weakTargetAllowsNone(weak_.inner) }
    _ -> { }
  }
  weakValue := if nullable then storage + ".value()" else storage
  let originalReturn: ResolvedType | none = none
  if member.resolvedType != none {
    case member.resolvedType! { function_: FunctionType -> { originalReturn = function_.returnType } _ -> { } }
  }
  arguments := emitDispatchCallArguments(expression, context)
  let call = temporary + "->" + cppIdentifier(member.property) + "(" + arguments + ")"
  case member.object.resolvedType! {
    weak_: WeakResolvedType -> {
      if weakTargetUsesVariant(weak_.inner) {
        if originalReturn == none { panic("Weak union method call has no resolved return type") }
        call = "std::visit([&](auto&& _weak_item) -> " + emitContextReturnType(originalReturn!, context) + " { return _weak_item->" + cppIdentifier(member.property) + "(" + arguments + "); }, " + temporary + ")"
      }
    }
    _ -> { }
  }
  if member.force {
    resultType := expression.resolvedType!
    noneCheck := if nullable then "if (!" + storage + ".has_value()) doof::panic(\"Weak reference is none\"); " else ""
    case resultType {
      _: NoneType -> { return "[&]() -> void { auto " + storage + " = " + object + "; " + noneCheck + "auto _weak_locked = doof::lock_weak(" + weakValue + "); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto " + temporary + " = std::move(_weak_locked.value()); " + call + "; }()" }
      _ -> { return "[&]() -> " + emitType(resultType, context.modulePath, context.names) + " { auto " + storage + " = " + object + "; " + noneCheck + "auto _weak_locked = doof::lock_weak(" + weakValue + "); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto " + temporary + " = std::move(_weak_locked.value()); return " + call + "; }()" }
    }
  }
  case expression.resolvedType! {
    result: ResultResolvedType -> {
      resultCpp := emitType(result, context.modulePath, context.names)
      payloadCpp := emitResultPayloadType(result.valueType, context.modulePath, context.names)
      errorCpp := emitResultPayloadType(result.errorType, context.modulePath, context.names)
      failure := if result.errorType.kind == "union" then errorCpp + "{::doof::WeakReferenceError{}}" else "::doof::WeakReferenceError{}"
      noneReturn := if nullable then "if (!" + storage + ".has_value()) return doof::Success<" + payloadCpp + ">{" + payloadCpp + "{}}; " else ""
      prefix := "[&]() -> " + resultCpp + " { auto " + storage + " = " + object + "; " + noneReturn + "auto _weak_locked = doof::lock_weak(" + weakValue + "); if (!_weak_locked.has_value()) return doof::Failure<" + errorCpp + ">{" + failure + "}; auto " + temporary + " = std::move(_weak_locked.value()); "
      if originalReturn != none {
        case originalReturn! {
          nested: ResultResolvedType -> {
            nestedErrorCpp := emitResultPayloadType(nested.errorType, context.modulePath, context.names)
            promotedError := if result.errorType.kind == "union" then errorCpp + "{doof::failure_error(_weak_result)}" else "doof::failure_error(_weak_result)"
            if nested.valueType.kind == "none" {
              return prefix + "auto _weak_result = " + call + "; if (doof::is_failure(_weak_result)) return doof::Failure<" + errorCpp + ">{" + promotedError + "}; return doof::Success<void>{}; }()"
            }
            return prefix + "auto _weak_result = " + call + "; if (doof::is_failure(_weak_result)) return doof::Failure<" + errorCpp + ">{" + promotedError + "}; return doof::Success<" + payloadCpp + ">{" + payloadCpp + "{doof::success_value(_weak_result)}}; }()"
          }
          _: NoneType -> { return prefix + call + "; return doof::Success<void>{}; }()" }
          _ -> { }
        }
      }
      return prefix + "return doof::Success<" + payloadCpp + ">{" + payloadCpp + "{" + call + "}}; }()"
    }
    _ -> { panic("Optional weak method call must resolve to Result") }
  }
  return ""
}

function isBuiltinIdentifier(identifier: Identifier, name: string): bool {
  return identifier.name == name && identifier.resolvedBinding != none && identifier.resolvedBinding!.kind == "builtin"
}

function emitBuiltinCall(name: string, object: Expression, expression: CallExpression, context: EmitContext): string {
  let result = name + "(" + emitExpression(object, context)
  for argument of expression.args { result = result + ", " + emitExpression(argument.value, context) }
  return result + ")"
}

function emitInterfaceCall(member: MemberExpression, call: CallExpression, context: EmitContext): string {
  object := emitExpression(member.object, context)
  let args = ""
  for i of 0..<call.args.length {
    if i > 0 { args = args + ", " }
    args = args + emitExpression(call.args[i].value, context)
  }
  return "std::visit([&](auto&& _obj) { return _obj->" + cppIdentifier(member.property) + "(" + args + "); }, " + object + ")"
}

function emitVariantMemberCall(member: MemberExpression, call: CallExpression, context: EmitContext): string {
  object := emitExpression(member.object, context)
  objectType := decoratedExpressionType(member.object)
  if objectType == none { panic("Variant member call has no resolved object type") }
  if call.resolvedType == none { panic("Variant member call has no resolved return type") }
  args := emitDispatchCallArguments(call, context)
  invocation := if member.resolvedCallableField then ".call(" else "("
  return "std::visit([&](auto&& _obj) -> " + emitContextReturnType(call.resolvedType!, context) + " { return _obj->" + cppIdentifier(member.property) + invocation + args + "); }, " + variantVisitValue(object, objectType!) + ")"
}

function emitInterfaceJsonCall(member: MemberExpression, call: CallExpression, context: EmitContext): string {
  let args = ""
  for i of 0..<call.args.length {
    if i > 0 { args = args + ", " }
    args = args + emitExpression(call.args[i].value, context)
  }
  if call.args.length == 1 { args = args + ", false" }
  return emitExpression(member.object, context) + "_fromJsonValue(" + args + ")"
}

function builtinName(name: string): string {
  if name == "println" { return "doof::println" }
  if name == "panic" { return "doof::panic" }
  if name == "assert" { return "doof::assert_" }
  if name == "string" { return "doof::to_string" }
  if name == "byte" { return "static_cast<uint8_t>" }
  if name == "int" { return "static_cast<int32_t>" }
  if name == "long" { return "static_cast<int64_t>" }
  if name == "float" { return "static_cast<float>" }
  if name == "double" { return "static_cast<double>" }
  if name == "char" { return "static_cast<char32_t>" }
  if name == "bool" { return "static_cast<bool>" }
  return name
}

function isBuiltinName(name: string): bool {
  return name == "println" || name == "panic" || name == "assert" || name == "catchPanic" || name == "string" || name == "byte" || name == "int" || name == "long" || name == "float" || name == "double" || name == "char" || name == "bool"
}

function concreteFunctionName(context: EmitContext, key: string): string {
  for i of 0..<context.concreteFunctionKeys.length {
    if context.concreteFunctionKeys[i] == key { return context.concreteFunctionNames[i] }
  }
  return ""
}

function concreteMethodNameFor(context: EmitContext, key: string): string {
  for i of 0..<context.concreteMethodKeys.length {
    if context.concreteMethodKeys[i] == key { return context.concreteMethodNames[i] }
  }
  return ""
}
