// Literal, array, object, tuple, and string expression lowering.

import { emitCarrierAbsence } from "./emitter-carrier-values"
import { emitClassObject } from "./emitter-construction"
import { ArrayLiteral, ObjectLiteral, StringLiteral, TupleLiteral } from "./ast"
import { ArrayResolvedType, ClassType, JsonValueResolvedType, MapResolvedType, ResolvedType, ResultResolvedType, SetResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { emitPropertyValue, findProperty } from "./emitter-expr-utils"
import { emitContextReturnType, emitContextType } from "./emitter-types"

export function emitNoneLiteral(expected: ResolvedType | none, context: EmitContext): string {
  if expected == none { panic("None literal has no checked type in " + context.modulePath) }
  return emitCarrierAbsence(expected!, context)
}

export function emitChar(value: char): string {
  if value == '\0' { return "U'\\0'" }
  if value == '\\' { return "U'\\\\'" }
  if value == '\'' { return "U'\\''" }
  if value == '\n' { return "U'\\n'" }
  if value == '\r' { return "U'\\r'" }
  if value == '\t' { return "U'\\t'" }
  code := int(value)
  if code <= 65535 {
    return "U'\\u" + hexDigit(code \ 4096) + hexDigit((code \ 256) % 16) + hexDigit((code \ 16) % 16) + hexDigit(code % 16) + "'"
  }
  return "U'\\U" + hexDigit((code \ 268435456) % 16) + hexDigit((code \ 16777216) % 16) + hexDigit((code \ 1048576) % 16) + hexDigit((code \ 65536) % 16) + hexDigit((code \ 4096) % 16) + hexDigit((code \ 256) % 16) + hexDigit((code \ 16) % 16) + hexDigit(code % 16) + "'"
}

function hexDigit(value: int): string {
  digits := "0123456789ABCDEF"
  return digits.substring(value, value + 1)
}

export function emitArray(expression: ArrayLiteral, context: EmitContext, expected: ResolvedType | none): string {
  arrayType := expression.resolvedType
  if arrayType != none {
    case arrayType! {
      array: ArrayResolvedType -> {
        elementType := emitContextType(array.elementType, context)
        let values = ""
        for i of 0..<expression.elements.length {
          if i > 0 { values = values + ", " }
          values = values + emitExpression(expression.elements[i], context, array.elementType)
        }
        return "std::make_shared<std::vector<" + elementType + ">>(std::vector<" + elementType + ">{" + values + "})"
      }
      set_: SetResolvedType -> {
        elementType := emitContextType(set_.elementType, context)
        let values = ""
        for i of 0..<expression.elements.length {
          if i > 0 { values = values + ", " }
          values = values + emitExpression(expression.elements[i], context)
        }
        return "std::make_shared<doof::ordered_set<" + elementType + ">>(doof::ordered_set<" + elementType + ">{" + values + "})"
      }
      _: JsonValueResolvedType -> {
        let values = ""
        for i of 0..<expression.elements.length {
          if i > 0 { values = values + ", " }
          values = values + "doof::json_value(" + emitExpression(expression.elements[i], context) + ")"
        }
        return "doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::initializer_list<doof::JsonValue>{" + values + "}))"
      }
      _ -> { }
    }
  }
  panic("Array literal has no checked array type in " + context.modulePath + "::" + context.currentFunctionName)
  return "nullptr"
}

export function emitObject(expression: ObjectLiteral, context: EmitContext, expected: ResolvedType | none): string {
  if expression.resolvedType != none {
    case expression.resolvedType! {
      class_: ClassType -> { return emitClassObject(expression, context, class_) }
      _ -> { }
    }
  }
  if expected != none {
    case expected! {
      result: ResultResolvedType -> {
        value := findProperty(expression.properties, "value")
        error := findProperty(expression.properties, "error")
        if value != none {
          emitted := emitPropertyValue(value!, context, result.valueType)
          return "doof::Success<" + emitContextReturnType(result.valueType, context) + ">{ " + emitted + " }"
        }
        if error != none {
          emitted := emitPropertyValue(error!, context, result.errorType)
          return "doof::Failure<" + emitContextReturnType(result.errorType, context) + ">{ " + emitted + " }"
        }
      }
      class_: ClassType -> { return emitClassObject(expression, context, class_) }
      _ -> { }
    }
  }
  if expected != none {
    case expected! {
      map: MapResolvedType -> { return emitMapObject(expression, context, map) }
      _ -> { }
    }
  }
  let values = ""
  let first = true
  for property of expression.properties {
    if !first { values = values + ", " }
    first = false
    key := quote(property.name)
    value := "doof::json_value(" + emitPropertyValue(property, context) + ")"
    values = values + "{" + key + ", " + value + "}"
  }
  return "doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{" + values + "}))"
}

function emitMapObject(expression: ObjectLiteral, context: EmitContext, map: MapResolvedType): string {
  let values = ""
  for i of 0..<expression.properties.length {
    if i > 0 { values = values + ", " }
    property := expression.properties[i]
    value := emitPropertyValue(property, context, map.valueType)
    key := if property.key == none then quote(property.name) else emitExpression(property.key!, context, map.keyType)
    values = values + "{" + key + ", " + value + "}"
  }
  keyType := emitContextType(map.keyType, context)
  valueType := emitContextType(map.valueType, context)
  return "std::make_shared<doof::ordered_map<" + keyType + ", " + valueType + ">>(std::initializer_list<std::pair<" + keyType + ", " + valueType + ">>{" + values + "})"
}

export function emitTuple(expression: TupleLiteral, context: EmitContext): string {
  let values = ""
  for i of 0..<expression.elements.length {
    if i > 0 { values = values + ", " }
    values = values + emitExpression(expression.elements[i], context)
  }
  return "std::make_tuple(" + values + ")"
}

export function emitString(expression: StringLiteral, context: EmitContext): string {
  if expression.interpolations.length == 0 { return emitStringConstant(expression.parts[0]) }
  let result = "([&]() -> std::string { std::string _interpolation = " + emitInterpolationPart(expression.parts[0]) + "; "
  for i of 0..<expression.interpolations.length {
    result = result + "_interpolation += doof::to_string(" + emitExpression(expression.interpolations[i], context) + "); "
    partIndex := i * 2 + 2
    if partIndex < expression.parts.length { result = result + "_interpolation += " + emitInterpolationPart(expression.parts[partIndex]) + "; " }
  }
  return result + "return _interpolation; }())"
}

function emitInterpolationPart(value: string): string {
  if value.contains(string('\0')) { return emitStringConstant(value) }
  return quote(value)
}

export function emitStringConstant(value: string): string {
  literal := quote(value)
  nul := string('\0')
  if value.contains(nul) { return "std::string(" + literal + ", " + string(value.length) + ")" }
  return "std::string(" + literal + ")"
}

export function quote(value: string): string {
  nul := string('\0')
  escaped := value.replaceAll("\\", "\\\\").replaceAll("\"", "\\\"").replaceAll("?", "\\?")
    .replaceAll("\n", "\\n").replaceAll("\r", "\\r").replaceAll("\t", "\\t").replaceAll(nul, "\\000")
  return "\"" + escaped + "\""
}
