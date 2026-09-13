import { ModuleNames } from "./emitter-names"
import { weakTargetAllowsNone, weakTargetUsesVariant } from "./emitter-carriers"
// Shared type-pattern lowering for statement and expression cases.

import { emitCarrierAbsence } from "./emitter-carrier-values"
import { EmitContext } from "./emitter-context"
import { NamedType, TypePattern } from "./ast"
import {
  ArrayResolvedType, JsonValueResolvedType, MapResolvedType, NoneType, PrimitiveType,
  ResolvedType, ResultResolvedType, WeakResolvedType,
} from "./semantic"
import { emitContextReturnType, emitContextType, emitResultPayloadType, emitType, usesNullableSingleValueRepresentation, usesVariantRepresentation } from "./emitter-types"

export class CaseTypePatternEmission {
  condition: string
  binding: string
}

/** Materializes the checker-owned weak read once, retaining a live referent. */
export function emitCaseSubjectValue(value: string, storageType: ResolvedType, subjectType: ResolvedType, context: EmitContext): string {
  case storageType {
    weak_: WeakResolvedType -> {
      result := subjectType as ResultResolvedType else { panic("Weak case subject must resolve to Result") }
      payload := emitContextType(result.valueType, context)
      error := emitContextType(result.errorType, context)
      nullable := weakTargetAllowsNone(weak_.inner)
      absent := if nullable then "if (!_case_weak.has_value()) return doof::Success<" + payload + ">{" + emitCarrierAbsence(result.valueType, context) + "}; " else ""
      weakValue := if nullable then "_case_weak.value()" else "_case_weak"
      lockedValue := if nullable && weakTargetUsesVariant(weak_.inner) then "doof::variant_promote<" + payload + ">(std::move(_case_locked.value()))" else payload + "{std::move(_case_locked.value())}"
      return "[&]() -> " + emitContextType(result, context) + " { auto _case_weak = " + value + "; " + absent +
        "auto _case_locked = doof::lock_weak(" + weakValue + "); if (!_case_locked.has_value()) return doof::Failure<" + error + ">{::doof::WeakReferenceError{}}; return doof::Success<" + payload + ">{" + lockedValue + "}; }()"
    }
    _ -> { return value }
  }
}

/** Lowers a checked type pattern from the subject's concrete C++ carrier. */
export function emitCaseTypePattern(
  pattern: TypePattern,
  subjectType: ResolvedType,
  subject: string,
  bindingName: string,
  currentModulePath: string,
  names: ModuleNames = ModuleNames {},
  context: EmitContext | none = none,
): CaseTypePatternEmission {
  if pattern.resolvedType == none { panic("Case pattern has no resolved type") }
  patternType := pattern.resolvedType!
  case subjectType {
    result: ResultResolvedType -> { return emitResultPattern(pattern, result, subject, bindingName, currentModulePath, names, context) }
    _: JsonValueResolvedType -> { return emitJsonValuePattern(patternType, subject, bindingName) }
    _ -> { }
  }
  if usesVariantRepresentation(subjectType) {
    patternCpp := if context == none then emitType(patternType, currentModulePath, names) else emitContextType(patternType, context!)
    if usesVariantRepresentation(patternType) {
      return CaseTypePatternEmission {
        condition: "doof::variant_is<" + patternCpp + ">(" + subject + ")",
        binding: if bindingName == "" then "" else "const auto " + bindingName + " = doof::variant_narrow<" + patternCpp + ">(" + subject + ");\n",
      }
    }
    return CaseTypePatternEmission {
      condition: "std::holds_alternative<" + patternCpp + ">(" + subject + ")",
      binding: if bindingName == "" then "" else "const auto& " + bindingName + " = std::get<" + patternCpp + ">(" + subject + ");\n",
    }
  }
  nullable := usesNullableSingleValueRepresentation(subjectType)
  if nullable && patternType.kind == "none" {
    return CaseTypePatternEmission {
      condition: "doof::is_null(" + subject + ")",
      binding: if bindingName == "" then "" else "const auto " + bindingName + " = " + emitCarrierAbsence(patternType, EmitContext { modulePath: currentModulePath, names }) + ";\n",
    }
  }
  value := if nullable then "doof::unwrap_optional(" + subject + ")" else subject
  return CaseTypePatternEmission {
    condition: if nullable then "!doof::is_null(" + subject + ")" else "true",
    binding: if bindingName == "" then "" else "const auto " + bindingName + " = " + value + ";\n",
  }
}

function emitResultPattern(
  pattern: TypePattern,
  result: ResultResolvedType,
  subject: string,
  bindingName: string,
  currentModulePath: string,
  names: ModuleNames = ModuleNames {},
  context: EmitContext | none = none,
): CaseTypePatternEmission {
  let armType = ""
  case pattern.type_ {
    named: NamedType -> {
      if named.name == "Success" { armType = "doof::Success<" + (if context == none then emitResultPayloadType(result.valueType, currentModulePath, names) else emitContextReturnType(result.valueType, context!)) + ">" }
      if named.name == "Failure" { armType = "doof::Failure<" + (if context == none then emitResultPayloadType(result.errorType, currentModulePath, names) else emitContextReturnType(result.errorType, context!)) + ">" }
    }
    _ -> { }
  }
  if armType == "" { panic("Result case pattern must be Success or Failure") }
  return CaseTypePatternEmission {
    condition: "std::holds_alternative<" + armType + ">(" + subject + ")",
    binding: if bindingName == "" then "" else "const auto& " + bindingName + " = std::get<" + armType + ">(" + subject + ");\n",
  }
}

function emitJsonValuePattern(patternType: ResolvedType, subject: string, bindingName: string): CaseTypePatternEmission {
  let condition = "true"
  let value = subject
  case patternType {
    primitive: PrimitiveType -> {
      if primitive.name == "bool" { condition = "doof::json_is_boolean(" + subject + ")"; value = "doof::json_as_bool(" + subject + ")" }
      else if primitive.name == "string" { condition = "doof::json_is_string(" + subject + ")"; value = "doof::json_as_string(" + subject + ")" }
      else if primitive.name == "int" { condition = "doof::json_is_number(" + subject + ")"; value = "doof::json_as_int(" + subject + ")" }
      else if primitive.name == "long" { condition = "doof::json_is_number(" + subject + ")"; value = "doof::json_as_long(" + subject + ")" }
      else if primitive.name == "float" { condition = "doof::json_is_number(" + subject + ")"; value = "doof::json_as_float(" + subject + ")" }
      else if primitive.name == "double" { condition = "doof::json_is_number(" + subject + ")"; value = "doof::json_as_double(" + subject + ")" }
      else { panic("Unsupported primitive JsonValue case pattern " + primitive.name) }
    }
    _: ArrayResolvedType -> { condition = "doof::json_is_array(" + subject + ")"; value = "std::get<doof::JsonArray>(doof::json_storage(" + subject + "))" }
    _: MapResolvedType -> { condition = "doof::json_is_object(" + subject + ")"; value = "doof::json_object(" + subject + ")" }
    _: NoneType -> { condition = "doof::json_is_null(" + subject + ")"; value = emitCarrierAbsence(patternType, EmitContext {}) }
    _: JsonValueResolvedType -> { }
    _ -> { panic("Unsupported JsonValue case pattern") }
  }
  return CaseTypePatternEmission {
    condition,
    binding: if bindingName == "" then "" else "const auto " + bindingName + " = " + value + ";\n",
  }
}
