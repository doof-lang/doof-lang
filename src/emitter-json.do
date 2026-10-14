// Automatic JSON method lowering for the Doof emitter.
//
// Eligibility and lowering deliberately share one recursive surface so the
// checker never advertises synthetic methods the emitter cannot define.

import { carrierOf } from "./emitter-carriers"
import { emitCarrierAbsence } from "./emitter-carrier-values"
import {
  BoolLiteral, CharLiteral, ClassDeclaration, ClassField, DoubleLiteral, EnumDeclaration, ExportDeclaration, Expression, FloatLiteral, Identifier,
  IntLiteral, InterfaceDeclaration, LongLiteral, MemberExpression, NoneLiteral, Statement, StringLiteral, TypeAliasDeclaration, UnaryExpression,
} from "./ast"
import { quote } from "./emitter-expr-literals"
import { emitNoImplementationsAccess, implementationlessInterface } from "./emitter-no-implementations"
import { jsonValueType } from "./checker-types"
import { ArrayResolvedType, ClassType, EnumType, InterfaceType, SerialValueResolvedType, MapResolvedType, NoneType, PrimitiveType, ResolvedType, TupleResolvedType, UnionResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitClassInnerType, emitContextType, usesVariantRepresentation } from "./emitter-types"
import { JsonDiscriminator, JsonUnionLayout, interfaceJsonDiscriminator, jsonInterfaceKey, jsonOwnerKey, jsonUnionClassMembers, jsonUnionLayout, nullableJsonMember, objectUnionJsonDiscriminator, unionAliasJsonDiscriminator } from "./json-semantics"

export function emitInterfaceJsonDeclaration(owner: InterfaceDeclaration, context: EmitContext): string {
  if !containsJsonDemand(context.jsonDeserializationKeys, jsonInterfaceKey(owner)) { return "" }
  return "doof::Result<" + owner.name + ", std::string> " + owner.name + "_fromSerialValue(const doof::SerialValue& _json, bool _lenient);\n"
}

export function emitInterfaceJsonDefinition(owner: InterfaceDeclaration, context: EmitContext): string {
  if !containsJsonDemand(context.jsonDeserializationKeys, jsonInterfaceKey(owner)) { return "" }
  if owner.resolvedSymbol != none && owner.resolvedSymbol!.implementations.length == 0 {
    return "\ndoof::Result<" + owner.name + ", std::string> " + owner.name + "_fromSerialValue(const doof::SerialValue&, bool) {\n" +
      "    return doof::Failure<std::string>{\"Interface " + owner.name + " has no implementing classes\"};\n}\n"
  }
  discriminator := interfaceJsonDiscriminator(owner, context.allPrograms, context.jsonEligibility)
  if discriminator == none { return "" }
  return emitDiscriminatedJsonDefinition(owner.name, discriminator!, context)
}

export function emitUnionAliasJsonDeclaration(alias: TypeAliasDeclaration): string {
  if !alias.needsJson { return "" }
  return "doof::Result<" + alias.name + ", std::string> " + alias.name + "_fromSerialValue(const doof::SerialValue& _json, bool _lenient);\n"
}

export function emitUnionAliasJsonDefinition(alias: TypeAliasDeclaration, context: EmitContext): string {
  if !alias.needsJson { return "" }
  discriminator := unionAliasJsonDiscriminator(alias, context.allPrograms, context.jsonEligibility)
  if discriminator == none { return "" }
  return emitDiscriminatedJsonDefinition(alias.name, discriminator!, context)
}

// Interfaces and class-union aliases both lower to variants of class pointers,
// so one discriminator dispatch serves both decoders.
function emitDiscriminatedJsonDefinition(ownerName: string, discriminator: JsonDiscriminator, context: EmitContext): string {
  failureType := "doof::Failure<std::string>"
  successType := "doof::Success<" + ownerName + ">"
  let result = "\ndoof::Result<" + ownerName + ", std::string> " + ownerName + "_fromSerialValue(const doof::SerialValue& _json, bool _lenient) {\n"
  result = result + "    const auto* _object = doof::serial_as_object(_json);\n"
  result = result + "    if (_object == nullptr) { return " + failureType + "{\"Expected JSON object\"}; }\n"
  result = result + "    auto _discriminator_iterator = _object->find(\"" + discriminator.fieldName + "\");\n"
  result = result + "    if (_discriminator_iterator == _object->end() || !doof::serial_is_string(_discriminator_iterator->second)) { return " + failureType + "{\"Missing or invalid discriminator field \\\"" + discriminator.fieldName + "\\\"\"}; }\n"
  result = result + "    auto _discriminator = doof::serial_as_string(_discriminator_iterator->second);\n"
  for i of 0..<discriminator.entries.length {
    entry := discriminator.entries[i]
    classType_ := ClassType { name: entry.declaration.name, symbol: entry.declaration.resolvedSymbol! }
    className := emitClassInnerType(classType_, context.modulePath, context.names)
    result = result + "    " + (if i == 0 then "if" else "else if") + " (_discriminator == \"" + entry.value + "\") {\n"
    result = result + "        auto _result = " + className + "::fromSerialValue(_json, _lenient);\n"
    result = result + "        if (doof::is_success(_result)) { return " + successType + "{" + ownerName + "{doof::success_value(_result)}}; }\n"
    result = result + "        return " + failureType + "{doof::failure_error(_result)};\n"
    result = result + "    }\n"
  }
  return result + "    return " + failureType + "{\"Unknown " + discriminator.fieldName + ": \\\"\" + _discriminator + \"\\\"\"};\n}\n"
}

/** Emits automatic JSON declarations owned by a concrete class or struct. */
export function emitGeneratedJsonDeclarations(owner: ClassDeclaration, context: EmitContext): string {
  key := jsonOwnerKey(owner)
  let result = ""
  if containsJsonDemand(context.jsonSerializationKeys, key) {
    result = result + "    doof::SerialObject toSerialObject() const;\n"
  }
  if containsJsonDemand(context.jsonDeserializationKeys, key) {
    valueType := jsonResultValueType(owner)
    result = result + "    static doof::Result<" + valueType + ", std::string> fromSerialValue(const doof::SerialValue& _json, bool _lenient);\n"
  }
  return result
}

/** Emits automatic JSON definitions after the owning class declaration. */
export function emitGeneratedJsonMethods(owner: ClassDeclaration, context: EmitContext): string {
  key := jsonOwnerKey(owner)
  let result = ""
  if containsJsonDemand(context.jsonSerializationKeys, key) { result = result + emitToJsonObject(owner, context) }
  if containsJsonDemand(context.jsonDeserializationKeys, key) { result = result + emitFromJsonValue(owner, context) }
  return result
}

function containsJsonDemand(keys: string[], key: string): bool {
  for existing of keys { if existing == key { return true } }
  return false
}

function emitToJsonObject(owner: ClassDeclaration, context: EmitContext): string {
  let result = "doof::SerialObject " + owner.name + "::toSerialObject() const {\n"
  result = result + "    auto _json = std::make_shared<doof::ordered_map<std::string, doof::SerialValue>>();\n"
  for field of owner.fields {
    if field.static_ { continue }
    for name of field.names {
      result = result + "    (*_json)[\"" + name + "\"] = " + emitJsonField("this->" + cppIdentifier(name), field.resolvedType!, context) + ";\n"
    }
  }
  return result + "    return _json;\n}\n"
}

function emitFromJsonValue(owner: ClassDeclaration, context: EmitContext): string {
  valueType := jsonResultValueType(owner)
  failureType := "doof::Failure<std::string>"
  let result = "doof::Result<" + valueType + ", std::string> " + owner.name + "::fromSerialValue(const doof::SerialValue& _json, bool _lenient) {\n"
  result = result + "    try {\n"
  result = result + "        const auto* _object = doof::serial_as_object(_json);\n"
  result = result + "        if (_object == nullptr) { return " + failureType + "{\"Expected JSON object\"}; }\n"
  for field of owner.fields {
    if field.static_ { continue }
    for name of field.names {
      if field.const_ { result = result + emitJsonConstFieldValidation(field, name, context, failureType) }
      else { result = result + emitJsonFieldRead(field, name, context, failureType) }
    }
  }
  let arguments = ""
  for field of owner.fields {
    if field.static_ || field.const_ { continue }
    for name of field.names {
      if arguments != "" { arguments = arguments + ", " }
      arguments = arguments + "_field_" + cppIdentifier(name)
      if field.defaultValue != none { arguments = arguments + ".value()" }
    }
  }
  let constructed = owner.name + "{" + arguments + "}"
  if !owner.struct_ { constructed = "std::make_shared<" + owner.name + ">(" + arguments + ")" }
  return result + "        return doof::Success<" + valueType + ">{" + constructed + "};\n" +
    "    } catch (const doof::JsonDecodeError& _error) {\n" +
    "        return " + failureType + "{_error.message()};\n" +
    "    }\n}\n"
}

function emitJsonConstFieldValidation(field: ClassField, name: string, context: EmitContext, failureType: string): string {
  if field.defaultValue == none { return "" }
  iterator := "_iterator_" + cppIdentifier(name)
  case field.defaultValue! {
    value: StringLiteral -> {
      let result = "    if (auto " + iterator + " = _object->find(\"" + name + "\"); " + iterator + " != _object->end()) {\n"
      result = result + "        if (!doof::serial_is_string(" + iterator + "->second) || doof::serial_as_string(" + iterator + "->second) != \"" + value.value + "\") { return " + failureType + "{\"Field \\\"" + name + "\\\" must be \\\"" + value.value + "\\\"\"}; }\n"
      return result + "    }\n"
    }
    value: IntLiteral -> {
      let result = "    if (auto " + iterator + " = _object->find(\"" + name + "\"); " + iterator + " != _object->end()) {\n"
      result = result + "        if (!doof::serial_fits_int(" + iterator + "->second) || doof::serial_as_int(" + iterator + "->second) != " + string(value.value) + ") { return " + failureType + "{\"Field \\\"" + name + "\\\" must be " + string(value.value) + "\"}; }\n"
      return result + "    }\n"
    }
    _ -> { }
  }
  // Remaining literal and enum-member values decode with the field's own type
  // and compare against the constant; a mismatch fails instead of being ignored.
  if field.resolvedType == none { return "" }
  type_ := field.resolvedType!
  if type_.kind != "primitive" && type_.kind != "enum" { return "" }
  json := iterator + "->second"
  message := quote("Field \"" + name + "\" must be " + constFieldDisplay(field.defaultValue!))
  let result = "    if (auto " + iterator + " = _object->find(\"" + name + "\"); " + iterator + " != _object->end()) {\n"
  result = result + "        if (!(" + emitJsonTypeCheck(json, type_, context) + ") || " + emitJsonRead(json, type_, context) + " != " + emitExpression(field.defaultValue!, context, type_) + ") { return " + failureType + "{" + message + "}; }\n"
  return result + "    }\n"
}

function constFieldDisplay(value: Expression): string {
  case value {
    member: MemberExpression -> { return constFieldDisplay(member.object) + "." + member.property }
    identifier: Identifier -> { return identifier.name }
    unary: UnaryExpression -> { return unary.operator + constFieldDisplay(unary.operand) }
    integer: IntLiteral -> { return string(integer.value) }
    long_: LongLiteral -> { return string(long_.value) }
    double_: DoubleLiteral -> { return double_.raw }
    float_: FloatLiteral -> { return float_.raw }
    bool_: BoolLiteral -> { return string(bool_.value) }
    char_: CharLiteral -> { return "'" + string(char_.value) + "'" }
    _ -> { return "its declared value" }
  }
}

function emitJsonFieldRead(field: ClassField, name: string, context: EmitContext, failureType: string): string {
  type_ := field.resolvedType!
  safeName := cppIdentifier(name)
  iterator := "_iterator_" + safeName
  value := "_field_" + safeName
  typeText := emitContextType(type_, context)
  let result = ""
  if field.defaultValue != none {
    result = result + "    std::optional<" + typeText + "> " + value + ";\n"
    result = result + "    if (auto " + iterator + " = _object->find(\"" + name + "\"); " + iterator + " != _object->end()) {\n"
    result = result + emitJsonValidation(iterator + "->second", type_, name, context, failureType, 2)
    read := emitJsonRead(iterator + "->second", type_, context)
    result = result + "        " + value + " = doof::serial_decode_at(\"Field \\\"" + name + "\\\"\", [&]() { return " + read + "; });\n"
    result = result + "    } else {\n"
    let defaultValue = emitExpression(field.defaultValue!, context, type_)
    // A nullable `null` default must engage optional<optional<T>> with an
    // empty inner optional rather than disengaging the outer presence marker.
    case field.defaultValue! {
      _: NoneLiteral -> { defaultValue = typeText + "{" + defaultValue + "}" }
      _ -> {}
    }
    result = result + "        " + value + " = " + defaultValue + ";\n"
    return result + "    }\n"
  }
  result = result + "    auto " + iterator + " = _object->find(\"" + name + "\");\n"
  result = result + "    if (" + iterator + " == _object->end()) { return " + failureType + "{\"Missing required field \\\"" + name + "\\\"\"}; }\n"
  result = result + emitJsonValidation(iterator + "->second", type_, name, context, failureType, 1)
  read := emitJsonRead(iterator + "->second", type_, context)
  return result + "    auto " + value + " = doof::serial_decode_at(\"Field \\\"" + name + "\\\"\", [&]() { return " + read + "; });\n"
}

function emitJsonValidation(json: string, type_: ResolvedType, name: string, context: EmitContext, failureType: string, indent: int): string {
  prefix := if indent == 2 then "            " else "        "
  check := emitJsonTypeCheck(json, type_, context)
  expected := jsonTypeName(type_, context)
  return prefix + "if (!(" + check + ")) { return " + failureType + "{\"Field \\\"" + name + "\\\" expected " + expected + " but got \" + std::string(doof::serial_type_name(" + json + "))}; }\n"
}

export function emitJsonTypeCheck(json: string, type_: ResolvedType, context: EmitContext | none = none): string {
  case type_ {
    primitive: PrimitiveType -> {
      if primitive.name == "bool" { return "(_lenient ? doof::serial_is_lenient_boolean(" + json + ") : doof::serial_is_boolean(" + json + "))" }
      if primitive.name == "char" { return "doof::serial_is_char(" + json + ", _lenient)" }
      if primitive.name == "string" { return "(_lenient ? doof::serial_is_lenient_string(" + json + ") : doof::serial_is_string(" + json + "))" }
      if primitive.name == "byte" || primitive.name == "int" || primitive.name == "long" {
        return "(_lenient ? doof::serial_fits_" + primitive.name + "_lenient(" + json + ") : doof::serial_fits_" + primitive.name + "(" + json + "))"
      }
      return "(_lenient ? doof::serial_is_lenient_number(" + json + ") : doof::serial_is_number(" + json + "))"
    }
    _: NoneType -> { return "doof::serial_is_null(" + json + ")" }
    _: SerialValueResolvedType -> { return "true" }
    _: ClassType -> { return "doof::serial_is_object(" + json + ")" }
    _: InterfaceType -> { return "doof::serial_is_object(" + json + ")" }
    enum_: EnumType -> {
      if context != none && enumBackingKind(enum_, context!) == "string" { return "doof::serial_is_string(" + json + ")" }
      return "doof::serial_fits_int(" + json + ")"
    }
    _: ArrayResolvedType -> { return "doof::serial_is_array(" + json + ")" }
    tuple: TupleResolvedType -> { return "doof::serial_is_array(" + json + ") && doof::serial_as_array(" + json + ")->size() == " + string(tuple.elements.length) }
    _: MapResolvedType -> { return "doof::serial_is_object(" + json + ")" }
    union_: UnionResolvedType -> {
      inner := nullableJsonMember(union_) else { return emitJsonUnionTypeCheck(json, union_, context) }
      return "doof::serial_is_null(" + json + ") || " + emitJsonTypeCheck(json, inner, context)
    }
    _ -> { return "false" }
  }
  return "false"
}

// Every nesting level validates its container before dereferencing it.
function emitJsonContainerRead(json: string, name: string, object_: bool): string {
  kind := if object_ then "object" else "array"
  return "const auto* " + name + " = doof::serial_as_" + kind + "(" + json + "); if (" + name + " == nullptr) throw doof::JsonDecodeError(\"Expected " + kind + "\"); "
}

export function emitJsonRead(json: string, type_: ResolvedType, context: EmitContext): string {
  case type_ {
    primitive: PrimitiveType -> { return emitPrimitiveJsonRead(json, primitive.name) }
    _: NoneType -> { return "[&]() -> std::monostate { if (!doof::serial_is_null(" + json + ")) throw doof::JsonDecodeError(\"Expected null\"); return {}; }()" }
    _: SerialValueResolvedType -> { return json }
    class_: ClassType -> {
      return "doof::serial_decode_value(" + emitClassInnerType(class_, context.modulePath, context.names) + "::fromSerialValue(" + json + ", _lenient))"
    }
    interface_: InterfaceType -> {
      return "doof::serial_decode_value(" + emitContextType(interface_, context) + "_fromSerialValue(" + json + ", _lenient))"
    }
    enum_: EnumType -> {
      return "doof::serial_decode_value(" + emitContextType(enum_, context) + "_fromSerialValue(" + json + ", false))"
    }
    array: ArrayResolvedType -> {
      elementType := emitContextType(array.elementType, context)
      elementValue := emitNestedJsonRead("_element", array.elementType, context)
      return "[&]() { " + emitJsonContainerRead(json, "_array", false) + "auto _values = std::make_shared<std::vector<" + elementType + ">>(); _values->reserve(_array->size()); for (size_t _index = 0; _index < _array->size(); ++_index) { const auto& _element = (*_array)[_index]; _values->push_back(doof::serial_decode_at(std::string(\"[\") + doof::to_string(_index) + \"]\", [&]() { return " + elementValue + "; })); } return _values; }()"
    }
    tuple: TupleResolvedType -> {
      let elements = ""
      for i of 0..<tuple.elements.length {
        if i > 0 { elements = elements + ", " }
        elements = elements + "doof::serial_decode_at(\"[" + string(i) + "]\", [&]() { return " + emitNestedJsonRead("(*_tuple)[" + string(i) + "]", tuple.elements[i], context) + "; })"
      }
      return "[&]() { " + emitJsonContainerRead(json, "_tuple", false) + "if (_tuple->size() != " + string(tuple.elements.length) + ") throw doof::JsonDecodeError(\"Expected tuple of length " + string(tuple.elements.length) + "\"); return std::make_tuple(" + elements + "); }()"
    }
    map: MapResolvedType -> {
      valueType := emitContextType(map.valueType, context)
      entryValue := emitNestedJsonRead("_entry.second", map.valueType, context)
      return "[&]() { " + emitJsonContainerRead(json, "_object_value", true) + "auto _values = std::make_shared<doof::ordered_map<std::string, " + valueType + ">>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = doof::serial_decode_at(std::string(\".\") + _entry.first, [&]() { return " + entryValue + "; }); } return _values; }()"
    }
    union_: UnionResolvedType -> {
      inner := nullableJsonMember(union_) else { return emitJsonUnionRead(json, union_, context) }
      if usesVariantRepresentation(type_) {
        optionalType := emitContextType(type_, context)
        // A decoded interface variant spreads into the flattened union's arms.
        read := emitJsonRead(json, inner, context)
        present := if usesVariantRepresentation(inner) then "doof::variant_promote<" + optionalType + ">(" + read + ")" else optionalType + "{" + read + "}"
        return "(doof::serial_is_null(" + json + ") ? " + optionalType + "{std::monostate{}} : " + present + ")"
      }
      if carrierOf(type_).kind == .SharedPointer {
        return "(doof::serial_is_null(" + json + ") ? " + emitCarrierAbsence(type_, context) + " : " + emitJsonRead(json, inner, context) + ")"
      }
      optionalType := emitContextType(type_, context)
      return "(doof::serial_is_null(" + json + ") ? " + optionalType + "{std::nullopt} : " + optionalType + "{" + emitJsonRead(json, inner, context) + "})"
    }
    _ -> { return "{}" }
  }
  return "{}"
}

function requiredJsonUnionLayout(union_: UnionResolvedType, context: EmitContext): JsonUnionLayout {
  layout := jsonUnionLayout(union_, context.allPrograms) else { panic("Union JSON coding has no layout for " + context.modulePath) }
  return layout
}

function jsonKindCheck(json: string, jsonKind: string): string {
  return "doof::serial_is_" + jsonKind + "(" + json + ")"
}

// A union accepts exactly the JSON kinds of its members, before any lenient
// conversion, matching the dispatch in emitJsonUnionRead.
function emitJsonUnionTypeCheck(json: string, union_: UnionResolvedType, context: EmitContext | none): string {
  layout := jsonUnionLayout(union_, if context == none then [] else context!.allPrograms) else { return "false" }
  let kinds: string[] = []
  if layout.hasNone { kinds.push("null") }
  for arm of layout.arms { if !kinds.contains(arm.jsonKind) { kinds.push(arm.jsonKind) } }
  if kinds.length == 1 { return jsonKindCheck(json, kinds[0]) }
  let check = ""
  for kind of kinds { check = check + (if check == "" then "" else " || ") + jsonKindCheck(json, kind) }
  return "(" + check + ")"
}

// Decodes a union by the JSON value's own kind, each kind having one member;
// several class members share the object kind through their discriminator.
// The decoded member is promoted into the union's variant; null is none.
function emitJsonUnionRead(json: string, union_: UnionResolvedType, context: EmitContext): string {
  layout := requiredJsonUnionLayout(union_, context)
  classMembers := jsonUnionClassMembers(layout)
  unionCpp := emitContextType(union_, context)
  let result = "[&]() -> " + unionCpp + " { "
  if layout.hasNone { result = result + "if (doof::serial_is_null(" + json + ")) return " + unionCpp + "{std::monostate{}}; " }
  let classesRead = false
  for arm of layout.arms {
    if classMembers.length > 1 && classMembers.contains(arm.member) {
      if classesRead { continue }
      classesRead = true
      result = result + "if (doof::serial_is_object(" + json + ")) { " + emitJsonUnionClassesRead(json, union_, unionCpp, context) + " } "
      continue
    }
    result = result + "if (" + jsonKindCheck(json, arm.jsonKind) + ") return doof::variant_promote<" + unionCpp + ">(" + emitNestedJsonRead(json, arm.member, context) + "); "
  }
  return result + "throw doof::JsonDecodeError(std::string(\"Expected " + jsonUnionTypeName(union_, context) + " but got \") + doof::serial_type_name(" + json + ")); }()"
}

function emitJsonUnionClassesRead(json: string, union_: UnionResolvedType, unionCpp: string, context: EmitContext): string {
  discriminator := objectUnionJsonDiscriminator(union_, context.allPrograms, context.jsonEligibility) else { panic("Union JSON decoding has no discriminator") }
  let result = emitJsonContainerRead(json, "_union_object", true)
  if discriminator.entries.length == 0 { return result + "throw doof::JsonDecodeError(\"Union has no member classes\");" }
  field := discriminator.fieldName
  result = result + "auto _union_field = _union_object->find(\"" + field + "\"); if (_union_field == _union_object->end() || !doof::serial_is_string(_union_field->second)) throw doof::JsonDecodeError(\"Missing or invalid discriminator field \\\"" + field + "\\\"\"); auto _union_discriminator = doof::serial_as_string(_union_field->second); "
  for entry of discriminator.entries {
    className := emitClassInnerType(ClassType { name: entry.declaration.name, symbol: entry.declaration.resolvedSymbol! }, context.modulePath, context.names)
    result = result + "if (_union_discriminator == \"" + entry.value + "\") return doof::variant_promote<" + unionCpp + ">(doof::serial_decode_value(" + className + "::fromSerialValue(" + json + ", _lenient))); "
  }
  return result + "throw doof::JsonDecodeError(\"Unknown " + field + ": \\\"\" + _union_discriminator + \"\\\"\");"
}

function jsonUnionTypeName(union_: UnionResolvedType, context: EmitContext | none): string {
  layout := jsonUnionLayout(union_, if context == none then [] else context!.allPrograms) else { return "value" }
  let names: string[] = []
  for arm of layout.arms {
    name := jsonTypeName(arm.member, context)
    if !names.contains(name) { names.push(name) }
  }
  if layout.hasNone { names.push("null") }
  let result = ""
  for name of names { result = result + (if result == "" then "" else " or ") + name }
  return result
}

// Class arms, including an interface's flattened implementors, encode through
// the runtime; every other arm encodes by its own Doof type.
function emitJsonUnionField(value: string, union_: UnionResolvedType, context: EmitContext): string {
  layout := requiredJsonUnionLayout(union_, context)
  classMembers := jsonUnionClassMembers(layout)
  if classMembers.length == layout.arms.length { return "doof::serial_union_value(" + value + ")" }
  let branches = ""
  for arm of layout.arms {
    if classMembers.contains(arm.member) { continue }
    branches = branches + "if constexpr (std::is_same_v<_Arm, " + emitContextType(arm.member, context) + ">) { return " + emitJsonField("_arm", arm.member, context) + "; } else "
  }
  return "std::visit([&](const auto& _arm) -> doof::SerialValue { using _Arm = std::decay_t<decltype(_arm)>; " + branches + "{ return doof::serial_union_arm(_arm); } }, " + value + ")"
}

// A field is validated before its read, but container elements and union
// arms are not: their primitives validate here so malformed input becomes a
// decode failure rather than a conversion panic.
function emitNestedJsonRead(json: string, type_: ResolvedType, context: EmitContext): string {
  primitive := type_ as PrimitiveType else { return emitJsonRead(json, type_, context) }
  return "[&]() { if (!(" + emitJsonTypeCheck(json, primitive, context) + ")) throw doof::JsonDecodeError(std::string(\"Expected " + jsonTypeName(primitive, context) + " but got \") + doof::serial_type_name(" + json + ")); return " + emitPrimitiveJsonRead(json, primitive.name) + "; }()"
}

function emitPrimitiveJsonRead(json: string, name: string): string {
  if name == "bool" { return "(_lenient ? doof::serial_as_bool_lenient(" + json + ") : doof::serial_as_bool(" + json + "))" }
  if name == "byte" { return "static_cast<uint8_t>(_lenient ? doof::serial_as_int_lenient(" + json + ") : doof::serial_as_int(" + json + "))" }
  if name == "int" { return "(_lenient ? doof::serial_as_int_lenient(" + json + ") : doof::serial_as_int(" + json + "))" }
  if name == "long" { return "(_lenient ? doof::serial_as_long_lenient(" + json + ") : doof::serial_as_long(" + json + "))" }
  if name == "float" { return "(_lenient ? doof::serial_as_float_lenient(" + json + ") : doof::serial_as_float(" + json + "))" }
  if name == "double" { return "(_lenient ? doof::serial_as_double_lenient(" + json + ") : doof::serial_as_double(" + json + "))" }
  if name == "char" { return "doof::serial_as_char(" + json + ", _lenient)" }
  return "(_lenient ? doof::serial_as_string_lenient(" + json + ") : doof::serial_as_string(" + json + "))"
}

export function jsonTypeName(type_: ResolvedType, context: EmitContext | none = none): string {
  case type_ {
    primitive: PrimitiveType -> {
      if primitive.name == "bool" { return "boolean" }
      if primitive.name == "string" || primitive.name == "char" { return "string" }
      if primitive.name == "byte" || primitive.name == "int" || primitive.name == "long" { return primitive.name }
      return "number"
    }
    _: NoneType -> { return "null" }
    _: SerialValueResolvedType -> { return "json" }
    _: ClassType -> { return "object" }
    _: InterfaceType -> { return "object" }
    enum_: EnumType -> {
      if context != none && enumBackingKind(enum_, context!) == "string" { return "string" }
      return "integer"
    }
    _: ArrayResolvedType -> { return "array" }
    _: TupleResolvedType -> { return "array" }
    _: MapResolvedType -> { return "object" }
    union_: UnionResolvedType -> {
      inner := nullableJsonMember(union_) else { return jsonUnionTypeName(union_, context) }
      return jsonTypeName(inner, context) + " or null"
    }
    _ -> { return "value" }
  }
  return "value"
}

export function emitJsonField(value: string, resolvedType: ResolvedType, context: EmitContext): string {
  case resolvedType {
    _: SerialValueResolvedType -> { return value }
    _: NoneType -> { return "doof::serial_value(nullptr)" }
    primitive: PrimitiveType -> {
      if primitive.name == "char" { return "doof::serial_value(doof::char_to_utf8(" + value + "))" }
      if primitive.name == "byte" { return "doof::serial_value(static_cast<int32_t>(" + value + "))" }
      return "doof::serial_value(" + value + ")"
    }
    class_: ClassType -> {
      if class_.symbol.kind == "struct" { return "doof::serial_value(" + value + ".toSerialObject())" }
      return "doof::serial_value(" + value + "->toSerialObject())"
    }
    interface_: InterfaceType -> {
      if implementationlessInterface(interface_, context) != none { return emitNoImplementationsAccess(value, interface_, jsonValueType(), context) }
      return "std::visit([&](auto&& _obj) -> doof::SerialValue { return doof::serial_value(_obj->toSerialObject()); }, " + value + ")"
    }
    enum_: EnumType -> {
      return emitContextType(enum_, context) + "_toSerialValue(" + value + ")"
    }
    union_: UnionResolvedType -> {
      inner := nullableJsonMember(union_) else { return emitJsonUnionField(value, union_, context) }
      if usesVariantRepresentation(resolvedType) {
        // An interface member's implementors are flattened beside none, so
        // removing none yields the interface variant rather than one arm.
        present := if usesVariantRepresentation(inner) then "doof::unwrap_optional(" + value + ")" else "std::get<" + emitContextType(inner, context) + ">(" + value + ")"
        return "(std::holds_alternative<std::monostate>(" + value + ") ? doof::serial_value(nullptr) : " + emitJsonField(present, inner, context) + ")"
      }
      if carrierOf(resolvedType).kind == .SharedPointer {
        return "(" + value + " ? " + emitJsonField(value, inner, context) + " : doof::serial_value(nullptr))"
      }
      return "(" + value + ".has_value() ? " + emitJsonField(value + ".value()", inner, context) + " : doof::serial_value(nullptr))"
    }
    array: ArrayResolvedType -> {
      if array.elementType.kind == "json-value" { return "doof::serial_value(" + value + ")" }
      element := emitJsonField("_element", array.elementType, context)
      return "[&]() { auto _array = std::make_shared<std::vector<doof::SerialValue>>(); _array->reserve(" + value + "->size()); for (const auto& _element : *" + value + ") { _array->push_back(" + element + "); } return doof::serial_value(_array); }()"
    }
    tuple: TupleResolvedType -> {
      let elements = ""
      for i of 0..<tuple.elements.length {
        if i > 0 { elements = elements + ", " }
        elements = elements + emitJsonField("std::get<" + string(i) + ">(" + value + ")", tuple.elements[i], context)
      }
      return "doof::serial_value(std::make_shared<std::vector<doof::SerialValue>>(std::initializer_list<doof::SerialValue>{" + elements + "}))"
    }
    map: MapResolvedType -> {
      if map.keyType.kind == "primitive" && map.valueType.kind == "json-value" { return "doof::serial_value(" + value + ")" }
      entryValue := emitJsonField("_entry.second", map.valueType, context)
      return "[&]() { auto _object_value = std::make_shared<doof::ordered_map<std::string, doof::SerialValue>>(); for (const auto& _entry : *" + value + ") { (*_object_value)[_entry.first] = " + entryValue + "; } return doof::serial_value(_object_value); }()"
    }
    _ -> { return "doof::serial_value(nullptr)" }
  }
  return "doof::serial_value(nullptr)"
}

function enumBackingKind(enum_: EnumType, context: EmitContext): string {
  declaration := findEnumDeclaration(context, enum_.symbol.module, enum_.name)
  if declaration == none { return "int" }
  return declaration!.backingKind
}

function findEnumDeclaration(context: EmitContext, modulePath: string, name: string): EnumDeclaration | none {
  for program of context.allPrograms {
    for statement of program.statements {
      declaration := enumStatementDeclaration(statement)
      if declaration != none && declaration!.name == name { return declaration }
    }
  }
  return none
}

function enumStatementDeclaration(statement: Statement): EnumDeclaration | none {
  case statement {
    enum_: EnumDeclaration -> { return enum_ }
    export_: ExportDeclaration -> {
      case export_.declaration {
        enum_: EnumDeclaration -> { return enum_ }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}

function jsonResultValueType(owner: ClassDeclaration): string {
  if owner.struct_ { return owner.name }
  return "std::shared_ptr<" + owner.name + ">"
}
