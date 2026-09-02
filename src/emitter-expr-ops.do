// Assignment, identifier, operator, member, and index lowering.

import { AsExpression, AssignmentExpression, BinaryExpression, Expression, Identifier, IndexExpression, MemberExpression, StringLiteral, ThisExpression, UnaryExpression } from "./ast"
import { ArrayResolvedType, ClassMetadataResolvedType, ClassType, EnumType, FunctionType, InterfaceType, JsonValueResolvedType, MapResolvedType, MethodReflectionResolvedType, NoneType, PrimitiveType, PromiseType, RangeResolvedType, ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, TypeParameterType, UnionResolvedType, WeakResolvedType } from "./semantic"
import { EmitContext, isCapturedMutable } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { emitNoneLiteral, emitStringConstant, quote } from "./emitter-expr-literals"
import { decoratedExpressionType, emittedSymbolName, emitNullableVariantPromotion, exprModuleNamespaceFor, hasSinglePrimitiveMember, isNullableVariantType, needsNullableVariantPromotion, requireExpressionType, variantVisitValue } from "./emitter-expr-utils"
import { emitResultPayloadType, emitType, naturalNullableUnionMember, specializeEmitType, usesVariantRepresentation } from "./emitter-types"
import { moduleDiagnosticPath } from "./emitter-names"
import { isNumeric, sameType } from "./checker-types"

/** Lowers checked `as` conversion to a Result without evaluating its source twice. */
export function emitAs(expression: AsExpression, context: EmitContext): string {
  sourceType := requireExpressionType(expression.expression, "as source")
  resultType := requireExpressionType(expression, "as expression")
  case resultType {
    result: ResultResolvedType -> {
      target := result.valueType
      resultCpp := emitType(result, context.modulePath)
      targetCpp := emitType(target, context.modulePath)
      success := "doof::Success<" + targetCpp + ">"
      failure := "doof::Failure<" + emitType(result.errorType, context.modulePath) + ">"
      source := emitExpression(expression.expression, context)
      if sameType(sourceType, target) { return resultCpp + "{" + success + "{" + source + "}}" }
      case sourceType {
        sourceResult: ResultResolvedType -> {
          let narrowed = ""
          case sourceResult.valueType {
            _: JsonValueResolvedType -> { narrowed = emitJsonAs("doof::success_value(_as_source)", target, resultCpp, success, failure) }
            _ -> { }
          }
          if narrowed != "" {
            errorValue := emitAsFailureValue(sourceResult, result, context)
            return "[&]() -> " + resultCpp + " { auto _as_source = " + source + "; if (doof::is_failure(_as_source)) return " + failure + "{" + errorValue + "}; return " + narrowed + "; }()"
          }
          if isNumeric(sourceResult.valueType) && isNumeric(target) {
            errorValue := emitAsFailureValue(sourceResult, result, context)
            return "[&]() -> " + resultCpp + " { auto _as_source = " + source + "; if (doof::is_failure(_as_source)) return " + failure + "{" + errorValue + "}; auto _as_checked = doof::checked_numeric_as<" + targetCpp + ">(doof::success_value(_as_source)); if (_as_checked.has_value()) return " + success + "{_as_checked.value()}; return " + failure + "{\"Numeric narrowing failed\"}; }()"
          }
        }
        _ -> { }
      }
      if isNumeric(sourceType) && isNumeric(target) {
        return "[&]() -> " + resultCpp + " { auto _as_checked = doof::checked_numeric_as<" + targetCpp + ">(" + source + "); if (_as_checked.has_value()) return " + success + "{_as_checked.value()}; return " + failure + "{\"Numeric narrowing failed\"}; }()"
      }
      case sourceType {
        _: JsonValueResolvedType -> { return emitJsonAs(source, target, resultCpp, success, failure) }
        interface_: InterfaceType -> {
          case target {
            _: ClassType -> {
              return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (std::holds_alternative<" + targetCpp + ">(_as_value)) return " + success + "{std::get<" + targetCpp + ">(_as_value)}; return " + failure + "{\"Interface narrowing failed\"}; }()"
            }
            _ -> { }
          }
        }
        union_: UnionResolvedType -> {
          if unionContainsJsonValue(union_) {
            narrowedJson := "std::get<doof::JsonValue>(_as_nullable)"
            jsonNarrowing := emitJsonAs(narrowedJson, target, resultCpp, success, failure)
            return "[&]() -> " + resultCpp + " { auto _as_nullable = " + source + "; if (doof::is_null(_as_nullable)) return " + failure + "{\"JsonValue narrowing failed\"}; return " + jsonNarrowing + "; }()"
          }
          member := naturalNullableUnionMember(union_)
          if member != none {
            if sameType(member!, target) {
              case target {
                class_: ClassType -> {
                  if class_.symbol.kind == "struct" {
                    return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (_as_value.has_value()) return " + success + "{_as_value.value()}; return " + failure + "{\"Nullable narrowing failed\"}; }()"
                  }
                  return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (_as_value) return " + success + "{_as_value}; return " + failure + "{\"Nullable narrowing failed\"}; }()"
                }
                _: ArrayResolvedType -> {
                  return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (_as_value) return " + success + "{_as_value}; return " + failure + "{\"Nullable narrowing failed\"}; }()"
                }
                _: PrimitiveType -> {
                  return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (_as_value.has_value()) return " + success + "{_as_value.value()}; return " + failure + "{\"Nullable narrowing failed\"}; }()"
                }
                _: EnumType -> {
                  return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (_as_value.has_value()) return " + success + "{_as_value.value()}; return " + failure + "{\"Nullable narrowing failed\"}; }()"
                }
                _ -> { }
              }
            }
            if isNumeric(member!) && isNumeric(target) {
              return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (!_as_value.has_value()) return " + failure + "{\"Nullable narrowing failed\"}; auto _as_checked = doof::checked_numeric_as<" + targetCpp + ">(_as_value.value()); if (_as_checked.has_value()) return " + success + "{_as_checked.value()}; return " + failure + "{\"Numeric narrowing failed\"}; }()"
            }
          }
          if isNumeric(target) && unionHasNumericMember(union_) {
            return emitNumericUnionAs(source, union_, targetCpp, resultCpp, success, failure, context)
          }
          return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (doof::variant_is<" + targetCpp + ">(_as_value)) return " + success + "{doof::variant_narrow<" + targetCpp + ">(_as_value)}; return " + failure + "{\"Union narrowing failed\"}; }()"
        }
        _ -> { }
      }
      return failure + "{\"Unsupported narrowing\"}"
    }
    _ -> { panic("as expression must resolve to Result") }
  }
  return ""
}

function emitAsFailureValue(source: ResultResolvedType, target: ResultResolvedType, context: EmitContext): string {
  errorValue := "doof::failure_error(_as_source)"
  if !sameType(source.errorType, target.errorType) {
    return "doof::variant_promote<" + emitType(target.errorType, context.modulePath) + ">(" + errorValue + ")"
  }
  return errorValue
}

function unionHasNumericMember(union_: UnionResolvedType): bool {
  for member of union_.types { if isNumeric(member) { return true } }
  return false
}

function emitNumericUnionAs(source: string, union_: UnionResolvedType, targetCpp: string, resultCpp: string, success: string, failure: string, context: EmitContext): string {
  let numericItem = ""
  for member of union_.types {
    if isNumeric(member) {
      if numericItem != "" { numericItem = numericItem + " || " }
      numericItem = numericItem + "std::is_same_v<_AsItem, " + emitType(member, context.modulePath) + ">"
    }
  }
  return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; auto _as_checked = std::visit([](const auto& _as_item) -> std::optional<" + targetCpp + "> { using _AsItem = std::decay_t<decltype(_as_item)>; if constexpr (" + numericItem + ") return doof::checked_numeric_as<" + targetCpp + ">(_as_item); return std::nullopt; }, _as_value); if (_as_checked.has_value()) return " + success + "{_as_checked.value()}; return " + failure + "{\"Numeric narrowing failed\"}; }()"
}

function unionContainsJsonValue(union_: UnionResolvedType): bool {
  for member of union_.types {
    case member {
      _: JsonValueResolvedType -> { return true }
      _ -> { }
    }
  }
  return false
}

function emitJsonAs(source: string, target: ResolvedType, resultCpp: string, success: string, failure: string): string {
  let condition = "true"
  let value = source
  case target {
    primitive: PrimitiveType -> {
      if primitive.name == "bool" { condition = "doof::json_is_boolean(_as_value)"; value = "doof::json_as_bool(_as_value)" }
      else if primitive.name == "string" { condition = "doof::json_is_string(_as_value)"; value = "doof::json_as_string(_as_value)" }
      else if primitive.name == "int" { condition = "doof::json_is_number(_as_value)"; value = "doof::json_as_int(_as_value)" }
      else if primitive.name == "long" { condition = "doof::json_is_number(_as_value)"; value = "doof::json_as_long(_as_value)" }
      else if primitive.name == "float" { condition = "doof::json_is_number(_as_value)"; value = "doof::json_as_float(_as_value)" }
      else if primitive.name == "double" { condition = "doof::json_is_number(_as_value)"; value = "doof::json_as_double(_as_value)" }
    }
    _: ArrayResolvedType -> { condition = "doof::json_is_array(_as_value)"; value = "std::get<doof::JsonArray>(doof::json_storage(_as_value))" }
    _: MapResolvedType -> { condition = "doof::json_is_object(_as_value)"; value = "doof::json_object(_as_value)" }
    _: JsonValueResolvedType -> { value = "_as_value" }
    _ -> { }
  }
  return "[&]() -> " + resultCpp + " { auto _as_value = " + source + "; if (" + condition + ") return " + success + "{" + value + "}; return " + failure + "{\"JsonValue narrowing failed\"}; }()"
}

export function emitAssignment(expression: AssignmentExpression, context: EmitContext): string {
  operator := if expression.operator == "\\=" then "/=" else expression.operator
  targetType := expression.target.resolvedType
  value := emitExpression(expression.value, context, targetType)
  return "(" + emitAssignmentTarget(expression.target, context) + " " + operator + " " + value + ")"
}

function emitAssignmentTarget(target: Expression, context: EmitContext): string {
  case target {
    index: IndexExpression -> {
      objectType := decoratedExpressionType(index.object)
      if objectType != none {
        case objectType! {
          _: MapResolvedType -> {
            return "doof::map_index(" + emitExpression(index.object, context) + ", " + emitExpression(index.index, context) + ", " + quote(moduleDiagnosticPath(context.modulePath, true)) + ", " + string(index.span.start.line) + ")"
          }
          _ -> { }
        }
      }
    }
    member: MemberExpression -> {
      objectType := decoratedExpressionType(member.object)
      if objectType != none && isVariantCarrier(objectType!) {
        object := emitExpression(member.object, context)
        return "std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->" + cppIdentifier(member.property) + "); }, " + variantVisitValue(object, objectType!) + ")"
      }
    }
    _ -> { }
  }
  return emitExpression(target, context)
}

function isVariantCarrier(resolvedType: ResolvedType): bool {
  case resolvedType {
    _: InterfaceType -> { return true }
    union_: UnionResolvedType -> {
      let nonNull = 0
      for member of union_.types { if member.kind != "none" { nonNull = nonNull + 1 } }
      return nonNull > 1
    }
    _ -> { }
  }
  return false
}

export function emitIdentifier(expression: Identifier, context: EmitContext): string {
  if expression.resolvedBinding != none && expression.resolvedBinding!.kind == "script-global" {
    return "__doof_script_get_" + cppIdentifier(expression.name) + "()"
  }
  if expression.resolvedBinding != none && expression.resolvedBinding!.kind == "field" && !context.currentFunctionStatic {
    return "this->" + cppIdentifier(expression.name)
  }
  for imported of context.imports {
    if imported.localName == expression.name && imported.symbol != none {
      if imported.symbol!.native_ {
        return "::" + (if imported.symbol!.nativeCppName == "" then imported.symbol!.name else imported.symbol!.nativeCppName)
      }
      return "::" + exprModuleNamespaceFor(imported.symbol!.module) + "::" + cppIdentifier(emittedSymbolName(imported.symbol!))
    }
  }
  if expression.resolvedBinding != none && expression.resolvedBinding!.symbol != none {
    symbol := expression.resolvedBinding!.symbol!
    if symbol.native_ {
      return "::" + (if symbol.nativeCppName == "" then symbol.name else symbol.nativeCppName)
    }
    if context.modulePath != "" && symbol.module != "" && symbol.module != context.modulePath {
      return "::" + exprModuleNamespaceFor(symbol.module) + "::" + cppIdentifier(emittedSymbolName(symbol))
    }
  }
  if expression.resolvedBinding != none && expression.resolvedBinding!.kind == "import" {
    for imported of context.imports {
      if imported.localName == expression.name && imported.symbol != none {
        return "::" + exprModuleNamespaceFor(imported.symbol!.module) + "::" + cppIdentifier(emittedSymbolName(imported.symbol!))
      }
    }
  }
  if expression.resolvedBinding != none && expression.resolvedBinding!.mutable && isCapturedMutable(context, expression.name) {
    return "(*" + cppIdentifier(expression.name) + ")"
  }
  return cppIdentifier(expression.name)
}

export function cppIdentifier(name: string): string {
  if isCppKeyword(name) { return name + "_" }
  if name == "stdin" { return "stdin_" }
  if name == "stdout" { return "stdout_" }
  if name == "stderr" { return "stderr_" }
  return name
}

function isCppKeyword(name: string): bool {
  return name == "alignas" || name == "alignof" || name == "and" || name == "and_eq" || name == "asm" || name == "auto" ||
    name == "bitand" || name == "bitor" || name == "bool" || name == "break" || name == "case" || name == "catch" ||
    name == "char" || name == "char8_t" || name == "char16_t" || name == "char32_t" || name == "class" || name == "compl" ||
    name == "concept" || name == "const" || name == "consteval" || name == "constexpr" || name == "constinit" || name == "const_cast" ||
    name == "continue" || name == "co_await" || name == "co_return" || name == "co_yield" || name == "decltype" || name == "default" ||
    name == "delete" || name == "do" || name == "double" || name == "dynamic_cast" || name == "else" || name == "enum" ||
    name == "explicit" || name == "export" || name == "extern" || name == "false" || name == "float" || name == "for" ||
    name == "friend" || name == "goto" || name == "if" || name == "inline" || name == "int" || name == "long" ||
    name == "mutable" || name == "namespace" || name == "new" || name == "noexcept" || name == "not" || name == "not_eq" ||
    name == "nullptr" || name == "operator" || name == "or" || name == "or_eq" || name == "private" || name == "protected" ||
    name == "public" || name == "register" || name == "reinterpret_cast" || name == "requires" || name == "return" || name == "short" ||
    name == "signed" || name == "sizeof" || name == "static" || name == "static_assert" || name == "struct" || name == "switch" ||
    name == "template" || name == "this" || name == "thread_local" || name == "throw" || name == "true" || name == "try" ||
    name == "typedef" || name == "typeid" || name == "typename" || name == "union" || name == "unsigned" || name == "using" ||
    name == "virtual" || name == "void" || name == "volatile" || name == "wchar_t" || name == "while" || name == "xor" || name == "xor_eq"
}

export function emitUnary(expression: UnaryExpression, context: EmitContext): string {
  if expression.operator == "try!" || expression.operator == "try?" {
    operand := emitExpression(expression.operand, context)
    operandType := requireExpressionType(expression.operand, expression.operator + " operand")
    case operandType {
      result: ResultResolvedType -> {
        valueType := emitType(result.valueType, context.modulePath)
        if expression.operator == "try?" {
          expressionType := requireExpressionType(expression, "try? expression")
          expressionCpp := emitType(expressionType, context.modulePath)
          let successValue = "std::move(doof::success_value(_try_value))"
          if needsNullableVariantPromotion(result.valueType, expressionType) {
            successValue = emitNullableVariantPromotion(successValue, result.valueType, expressionType, context.modulePath)
          }
          noneValue := emitNoneLiteral(expressionType, context)
          return "[&]() -> " + expressionCpp + " { auto _try_value = " + operand + "; if (doof::is_failure(_try_value)) return " + noneValue + "; return " + successValue + "; }()"
        }
        let failureMessage = "std::string(\"" + expression.operator + " failed\")"
        case result.errorType {
          primitive: PrimitiveType -> {
            if primitive.name == "string" {
              failureMessage = failureMessage + " + std::string(\": \") + doof::failure_error(_try_value)"
            }
          }
          _ -> { }
        }
        sourcePath := moduleDiagnosticPath(context.modulePath, true)
        body := "auto _try_value = " + operand + "; if (doof::is_failure(_try_value)) doof::panic_at(" + quote(sourcePath) + ", " + string(expression.span.start.line) + ", " + failureMessage + "); "
        case result.valueType {
          _: NoneType -> { return "[&]() -> void { " + body + " }()" }
          _ -> { }
        }
        return "[&]() -> " + valueType + " { " + body + "return std::move(doof::success_value(_try_value)); }()"
      }
      _ -> { panic(expression.operator + " operand is not a Result") }
    }
  }
  operand := emitExpression(expression.operand, context)
  if !expression.prefix && expression.operator == "!" {
    operandType := decoratedExpressionType(expression.operand)
    if operandType != none {
      case operandType! {
        result: ResultResolvedType -> {
          valueType := emitType(result.valueType, context.modulePath)
          body := "auto _assert_value = " + operand + "; if (doof::is_failure(_assert_value)) doof::panic(\"! failed\"); "
          case result.valueType {
            _: NoneType -> { return "[&]() -> void { " + body + "}()" }
            _ -> { }
          }
          return "[&]() -> " + valueType + " { " + body + "return std::move(doof::success_value(_assert_value)); }()"
        }
        _ -> { }
      }
    }
    if operandType != none {
      case expression.operand {
        _: MemberExpression -> {
          case operandType! {
            union_: UnionResolvedType -> {
              if usesVariantRepresentation(union_) {
                let nonNullMembers: ResolvedType[] = []
                for member of union_.types { if member.kind != "none" { nonNullMembers.push(member) } }
                if nonNullMembers.length == 1 { return "std::get<" + emitType(nonNullMembers[0], context.modulePath) + ">(" + operand + ")" }
              }
            }
            _ -> { }
          }
          return "doof::unwrap_optional(" + operand + ")"
        }
        _ -> { }
      }
      case operandType! {
        union_: UnionResolvedType -> {
          if hasSinglePrimitiveMember(union_) { return operand + ".value()" }
          if usesVariantRepresentation(union_) {
            let nonNullMembers: ResolvedType[] = []
            for member of union_.types { if member.kind != "none" { nonNullMembers.push(member) } }
            if nonNullMembers.length == 1 { return "std::get<" + emitType(nonNullMembers[0], context.modulePath) + ">(" + operand + ")" }
          }
          if isNullableVariantType(operandType) { return "doof::unwrap_optional(" + operand + ")" }
        }
        _ -> { }
      }
    }
    return "doof::unwrap_optional(" + operand + ")"
  }
  return binaryOperator(expression.operator) + operand
}

function binaryOperator(operator: string): string {
  return if operator == "!" then "!" else if operator == "-" then "-" else if operator == "+" then "+" else "~"
}

export function emitBinary(expression: BinaryExpression, context: EmitContext): string {
  if expression.operator == "+" {
    let literalParts: string[] = []
    if appendConstantStringParts(expression, literalParts) {
      let value = ""
      for part of literalParts { value = value + part }
      return emitStringConstant(value)
    }
  }
  if expression.operator == ".." {
    return "doof::range(" + emitExpression(expression.left, context) + ", " + emitExpression(expression.right, context) + ")"
  }
  if expression.operator == "..<" {
    return "doof::range_exclusive(" + emitExpression(expression.left, context) + ", " + emitExpression(expression.right, context) + ")"
  }
  if expression.operator == "??" {
    left := emitExpression(expression.left, context)
    leftType := requireExpressionType(expression.left, "coalescing source")
    resultType := requireExpressionType(expression, "coalescing expression")
    rightType := requireExpressionType(expression.right, "coalescing fallback")
    right := emitExpression(expression.right, context, resultType)
    fallback := if rightType.kind == "never" then "{ " + right + "; }" else "return " + right + ";"
    context.tryCounter = context.tryCounter + 1
    temporary := "_coalesce_" + string(context.tryCounter)
    case leftType {
      _: ResultResolvedType -> {
        return "[&]() -> " + emitType(resultType, context.modulePath) + " { auto " + temporary + " = " + left + "; if (doof::is_failure(" + temporary + ")) " + fallback + " return std::move(doof::success_value(" + temporary + ")); }()"
      }
      _ -> {
        return "[&]() -> " + emitType(resultType, context.modulePath) + " { auto " + temporary + " = " + left + "; if (doof::is_null(" + temporary + ")) " + fallback + " return doof::unwrap_optional(" + temporary + "); }()"
      }
    }
  }
  if (expression.operator == "==" || expression.operator == "!=") && expression.right.kind == "none-literal" {
    let test = "doof::is_null(" + emitExpression(expression.left, context) + ")"
    return if expression.operator == "==" then test else "(!" + test + ")"
  }
  if (expression.operator == "==" || expression.operator == "!=") && expression.left.kind == "none-literal" {
    let test = "doof::is_null(" + emitExpression(expression.right, context) + ")"
    return if expression.operator == "==" then test else "(!" + test + ")"
  }
  if expression.operator == "**" {
    return "std::pow(" + emitExpression(expression.left, context) + ", " + emitExpression(expression.right, context) + ")"
  }
  operator := if expression.operator == "\\" then "/" else expression.operator
  return "(" + emitExpression(expression.left, context) + " " + operator + " " + emitExpression(expression.right, context) + ")"
}

function appendConstantStringParts(expression: Expression, parts: string[]): bool {
  case expression {
    string_: StringLiteral -> {
      if string_.interpolations.length > 0 { return false }
      parts.push(string_.value)
      return true
    }
    binary: BinaryExpression -> {
      if binary.operator != "+" { return false }
      return appendConstantStringParts(binary.left, parts) && appendConstantStringParts(binary.right, parts)
    }
    _ -> { return false }
  }
}

export function emitMember(expression: MemberExpression, context: EmitContext): string {
  object := emitExpression(expression.object, context)
  let objectType = decoratedExpressionType(expression.object)
  if objectType != none {
    case objectType! {
      _: WeakResolvedType -> {
        if expression.optional || expression.force { return emitWeakFieldAccess(expression, object, context) }
      }
      _ -> { }
    }
    if expression.force {
      inner := naturalNullableUnionMember(objectType!)
      if inner != none {
        case inner! {
          enum_: EnumType -> {
            unwrapped := "doof::unwrap_optional(" + object + ")"
            if expression.property == "value" { return emitType(enum_, context.modulePath) + "_value(" + unwrapped + ")" }
            if expression.property == "name" { return emitType(enum_, context.modulePath) + "_name(" + unwrapped + ")" }
          }
          _ -> { }
        }
      }
    }
  }
  case expression.object {
    this_: ThisExpression -> {
      let nativeOwner = false
      if this_.resolvedType != none {
        case this_.resolvedType! {
          class_: ClassType -> { nativeOwner = class_.symbol.native_ }
          _ -> { }
        }
      }
      return "this->" + (if nativeOwner then expression.property else cppIdentifier(expression.property))
    }
    _ -> { }
  }
  case expression.object {
    identifier: Identifier -> {
      if identifier.resolvedBinding != none && identifier.resolvedBinding!.casePattern != "" && (expression.property == "value" || expression.property == "error") {
        return object + "." + cppIdentifier(expression.property)
      }
    }
    _ -> { }
  }
  case expression.object {
    identifier: Identifier -> {
      for namespace of context.namespaceImports {
        if namespace.localName == identifier.name {
          return "::" + exprModuleNamespaceFor(namespace.sourceModule) + "::" + cppIdentifier(expression.property)
        }
      }
    }
    _ -> { }
  }
  staticObjectType := decoratedExpressionType(expression.object)
  if staticObjectType != none {
    case staticObjectType! {
      parameter: TypeParameterType -> {
        specialized := specializeEmitType(parameter, context)
        if expression.property == "metadata" { return "doof::metadata_for_type<" + emitType(specialized, context.modulePath) + ">()" }
        if expression.property == "fromJsonValue" {
          case specialized {
            concrete: ClassType -> { return emitType(concrete, context.modulePath) + "::element_type::fromJsonValue" }
            unresolved: TypeParameterType -> { return cppIdentifier(unresolved.name) + "::element_type::fromJsonValue" }
            _ -> { }
          }
        }
      }
      class_: ClassType -> {
        if expression.resolvedStaticOwner != none {
          owner := expression.resolvedStaticOwner!
          let ownerName = owner.name
          if owner.native_ {
            ownerName = "::" + (if owner.nativeCppName == "" then owner.name else owner.nativeCppName)
          } else if owner.resolvedSymbol != none && owner.resolvedSymbol!.module != context.modulePath && context.modulePath != "" {
            ownerName = "::" + exprModuleNamespaceFor(owner.resolvedSymbol!.module) + "::" + owner.name
          }
          return ownerName + "::" + (if expression.property == "metadata" then "_metadata" else if owner.native_ then expression.property else cppIdentifier(expression.property))
        }
      }
      _ -> { }
    }
  }
  // Nominal fields and methods take precedence over builtin and aggregate
  // pseudo-members. This keeps ordinary members named length, kind,
  // resolvedType, span, push, or value from being rewritten as accessors.
  if staticObjectType != none {
    case staticObjectType! {
      class_: ClassType -> {
        memberName := if class_.symbol.native_ then expression.property else cppIdentifier(expression.property)
        return object + (if class_.symbol.kind == "struct" then "." else "->") + memberName
      }
      _ -> { }
    }
  }
  let callableMember = false
  if expression.resolvedType != none {
    case expression.resolvedType! {
      _: FunctionType -> { callableMember = true }
      _ -> { }
    }
  }
  if !callableMember && staticObjectType != none && usesVariantRepresentation(staticObjectType!) {
    return "std::visit([](auto&& _obj) { return _obj->" + cppIdentifier(expression.property) + "; }, " + variantVisitValue(object, staticObjectType!) + ")"
  }
  if expression.property == "push" { return object + "->push_back" }
  objectType = decoratedExpressionType(expression.object)
  if objectType != none {
    case objectType! {
      function_: FunctionType -> { return object + "." + cppIdentifier(expression.property) }
      _: PromiseType -> { return object + "." + cppIdentifier(expression.property) }
      _: InterfaceType -> { return "std::visit([](auto&& _obj) { return _obj->" + cppIdentifier(expression.property) + "; }, " + object + ")" }
      _: StreamResolvedType -> { return "std::visit([](auto&& _obj) { return _obj->" + cppIdentifier(expression.property) + "; }, " + object + ")" }
      _: ArrayResolvedType -> { if expression.property == "length" { return "static_cast<int32_t>((" + object + ")->size())" } }
      _: MapResolvedType -> { if expression.property == "size" { return object + "->size()" } }
      _: SetResolvedType -> { if expression.property == "size" { return object + "->size()" } }
      _: RangeResolvedType -> {
        if expression.property == "lowerBound" || expression.property == "upperBound" { return object + "." + expression.property }
      }
      primitive: PrimitiveType -> {
        if primitive.name == "string" && expression.property == "length" { return "static_cast<int32_t>(" + object + ".size())" }
        if primitive.name == "string" && expression.property == "toLowerCase" { return "doof::string_toLowerCase" }
        if primitive.name == "string" && expression.property == "toUpperCase" { return "doof::string_toUpperCase" }
      }
      result: ResultResolvedType -> {
        if expression.property == "value" { return "doof::success_value(" + object + ")" }
        if expression.property == "error" { return "doof::failure_error(" + object + ")" }
      }
      _: ClassMetadataResolvedType -> { return object + "." + cppIdentifier(expression.property) }
      _: MethodReflectionResolvedType -> { return object + "." + cppIdentifier(expression.property) }
      enum_: EnumType -> {
        if expression.property == "value" { return emitType(enum_, context.modulePath) + "_value(" + object + ")" }
        if expression.property == "name" { return emitType(enum_, context.modulePath) + "_name(" + object + ")" }
        return object + "::" + cppIdentifier(expression.property)
      }
      _ -> { }
    }
  }
  return object + "->" + cppIdentifier(expression.property)
}

function emitWeakFieldAccess(expression: MemberExpression, object: string, context: EmitContext): string {
  context.tryCounter = context.tryCounter + 1
  storage := "_weak_storage_" + string(context.tryCounter)
  temporary := "_weak_value_" + string(context.tryCounter)
  let nullable = false
  case decoratedExpressionType(expression.object)! {
    weak_: WeakResolvedType -> { nullable = weakTargetAllowsNone(weak_.inner) }
    _ -> { }
  }
  weakValue := if nullable then storage + ".value()" else storage
  let access = temporary + "->" + cppIdentifier(expression.property)
  case decoratedExpressionType(expression.object)! {
    weak_: WeakResolvedType -> {
      if weakTargetUsesVariant(weak_.inner) {
        access = "std::visit([](auto&& _weak_item) { return _weak_item->" + cppIdentifier(expression.property) + "; }, " + temporary + ")"
      }
    }
    _ -> { }
  }
  if expression.force {
    resultType := emitType(expression.resolvedType!, context.modulePath)
    noneCheck := if nullable then "if (!" + storage + ".has_value()) doof::panic(\"Weak reference is none\"); " else ""
    return "[&]() -> " + resultType + " { auto " + storage + " = " + object + "; " + noneCheck + "auto _weak_locked = doof::lock_weak(" + weakValue + "); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto " + temporary + " = std::move(_weak_locked.value()); return " + access + "; }()"
  }
  case expression.resolvedType! {
    result: ResultResolvedType -> {
      resultCpp := emitType(result, context.modulePath)
      payloadCpp := emitResultPayloadType(result.valueType, context.modulePath)
      errorCpp := emitResultPayloadType(result.errorType, context.modulePath)
      failure := weakFailureValue(result.errorType, errorCpp, context)
      noneReturn := if nullable then "if (!" + storage + ".has_value()) return doof::Success<" + payloadCpp + ">{" + payloadCpp + "{}}; " else ""
      return "[&]() -> " + resultCpp + " { auto " + storage + " = " + object + "; " + noneReturn + "auto _weak_locked = doof::lock_weak(" + weakValue + "); if (!_weak_locked.has_value()) return doof::Failure<" + errorCpp + ">{" + failure + "}; auto " + temporary + " = std::move(_weak_locked.value()); return doof::Success<" + payloadCpp + ">{" + payloadCpp + "{" + access + "}}; }()"
    }
    _ -> { panic("Optional weak field access must resolve to Result") }
  }
  return ""
}

function weakTargetAllowsNone(type_: ResolvedType): bool {
  case type_ {
    union_: UnionResolvedType -> { for member of union_.types { if member.kind == "none" { return true } } }
    _ -> { }
  }
  return false
}

function weakTargetUsesVariant(type_: ResolvedType): bool {
  case type_ {
    union_: UnionResolvedType -> {
      let present = 0
      for member of union_.types { if member.kind != "none" { present = present + 1 } }
      return present > 1
    }
    _ -> { }
  }
  return false
}

function weakFailureValue(errorType: ResolvedType, errorCpp: string, context: EmitContext): string {
  case errorType {
    _: UnionResolvedType -> { return errorCpp + "{::doof::WeakReferenceError{}}" }
    _ -> { }
  }
  return "::doof::WeakReferenceError{}"
}

export function emitIndex(expression: IndexExpression, context: EmitContext): string {
  object := emitExpression(expression.object, context)
  index := emitExpression(expression.index, context)
  sourcePath := quote(moduleDiagnosticPath(context.modulePath, true))
  sourceLine := string(expression.span.start.line)
  objectType := decoratedExpressionType(expression.object)
  if objectType != none {
    case objectType! {
      _: ArrayResolvedType -> { return "doof::array_at(" + object + ", " + index + ", " + sourcePath + ", " + sourceLine + ")" }
      _: MapResolvedType -> { return "doof::map_at(" + object + ", " + index + ", " + sourcePath + ", " + sourceLine + ")" }
      primitive: PrimitiveType -> {
        if primitive.name == "string" { return "doof::string_at(" + object + ", " + index + ", " + sourcePath + ", " + sourceLine + ")" }
      }
      _ -> { }
    }
  }
  return object + "[" + index + "]"
}
