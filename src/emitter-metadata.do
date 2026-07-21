// Structured reflection metadata, JSON Schema, and JSON invocation lowering.

import { ClassDeclaration, ClassField, EnumDeclaration, ExportDeclaration, FunctionDeclaration, Program, Statement } from "./ast"
import {
  ArrayResolvedType, ClassType, EnumType, FunctionType, JsonValueResolvedType, NoneType, PrimitiveType,
  ResolvedType, ResultResolvedType, TupleResolvedType, UnionResolvedType,
} from "./semantic"
import { EmitContext } from "./emitter-context"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitContextType } from "./emitter-types"
import { emitJsonField, emitJsonRead, emitJsonTypeCheck, jsonTypeName } from "./emitter-json"

/** Declares the runtime-owned reflection record on a metadata-demanded type. */
export function emitMetadataDeclaration(owner: ClassDeclaration): string {
  if !owner.needsMetadata { return "" }
  return "    static const doof::ClassMetadata<" + owner.name + "> _metadata;\n"
}

/** Defines reflection records after the owner is complete. */
export function emitMetadataDefinition(owner: ClassDeclaration, context: EmitContext): string {
  if !owner.needsMetadata { return "" }
  let methods: FunctionDeclaration[] = []
  for method of owner.methods { if !method.private_ && !method.static_ { methods.push(method) } }

  let result = "inline const doof::ClassMetadata<" + owner.name + "> " + owner.name + "::_metadata = {\n"
  result = result + "    \"" + escapeCpp(owner.name) + "\",\n"
  result = result + "    \"" + escapeCpp(owner.description) + "\",\n"
  result = result + "    std::make_shared<std::vector<doof::MethodReflection<" + owner.name + ">>>(std::vector<doof::MethodReflection<" + owner.name + ">>{\n"
  for index of 0..<methods.length {
    method := methods[index]
    result = result + emitMethodReflection(owner, method, context)
    if index + 1 < methods.length { result = result + "," }
    result = result + "\n"
  }
  result = result + "    }),\n"
  defs := emitDefinitions(methods, context)
  result = result + "    " + (if defs == "" then "std::nullopt" else "std::optional<doof::JsonValue>{" + defs + "}") + "\n"
  return result + "};\n"
}

function emitMethodReflection(owner: ClassDeclaration, method: FunctionDeclaration, context: EmitContext): string {
  inputSchema := emitMethodInputSchema(method, context)
  outputSchema := emitTypeSchema(methodSuccessType(method), context)
  let result = "        doof::MethodReflection<" + owner.name + ">{\n"
  result = result + "            \"" + escapeCpp(method.name) + "\",\n"
  result = result + "            \"" + escapeCpp(method.description) + "\",\n"
  result = result + "            " + inputSchema + ",\n"
  result = result + "            " + outputSchema + ",\n"
  result = result + "            []( " + owner.name + "& _instance, const doof::JsonValue& _params) -> doof::Result<doof::JsonValue, doof::JsonValue> {\n"
  result = result + "                const bool _lenient = false;\n"
  result = result + "                const auto* _p = doof::json_as_object(_params);\n"
  result = result + "                if (_p == nullptr) { return " + metadataFailure(400, "std::string(\"Invalid JSON params: expected object\")") + "; }\n"
  for parameter of method.params {
    type_ := parameter.resolvedType!
    safeName := cppIdentifier(parameter.name)
    iterator := "_it_" + safeName
    if parameter.defaultValue != none {
      result = result + "                " + emitContextType(type_, context) + " " + safeName + ";\n"
      result = result + "                if (auto " + iterator + " = _p->find(\"" + escapeCpp(parameter.name) + "\"); " + iterator + " != _p->end()) {\n"
      result = result + emitParameterValidation(parameter.name, iterator + "->second", type_, "                    ")
      result = result + "                    " + safeName + " = " + emitJsonRead(iterator + "->second", type_, context) + ";\n"
      result = result + "                } else { " + safeName + " = " + emitExpression(parameter.defaultValue!, context, type_) + "; }\n"
    } else {
      result = result + "                auto " + iterator + " = _p->find(\"" + escapeCpp(parameter.name) + "\");\n"
      result = result + "                if (" + iterator + " == _p->end()) { return " + metadataFailure(400, "std::string(\"Missing required parameter \\\"" + escapeCpp(parameter.name) + "\\\"\")") + "; }\n"
      result = result + emitParameterValidation(parameter.name, iterator + "->second", type_, "                ")
      result = result + "                auto " + safeName + " = " + emitJsonRead(iterator + "->second", type_, context) + ";\n"
    }
  }
  let arguments = ""
  for parameter of method.params {
    if arguments != "" { arguments = arguments + ", " }
    arguments = arguments + cppIdentifier(parameter.name)
  }
  returnType := methodReturnType(method)
  case returnType {
    _: NoneType -> {
      result = result + "                _instance." + cppIdentifier(method.name) + "(" + arguments + ");\n"
      result = result + "                return " + metadataSuccess("doof::json_value(nullptr)") + ";\n"
    }
    resultType: ResultResolvedType -> {
      result = result + "                auto _result = _instance." + cppIdentifier(method.name) + "(" + arguments + ");\n"
      result = result + "                if (doof::is_failure(_result)) {\n"
      if resultType.errorType.kind == "json-value" {
        result = result + "                    return doof::Failure<doof::JsonValue>{doof::failure_error(_result)};\n"
      } else {
        result = result + "                    return " + metadataFailure(500, "\"An error occurred\"") + ";\n"
      }
      result = result + "                }\n"
      if resultType.valueType.kind == "none" {
        result = result + "                return " + metadataSuccess("doof::json_value(nullptr)") + ";\n"
      } else {
        result = result + "                auto _success = doof::success_value(_result);\n"
        result = result + "                return " + metadataSuccess(emitJsonField("_success", resultType.valueType, context)) + ";\n"
      }
    }
    _ -> {
      result = result + "                auto _result = _instance." + cppIdentifier(method.name) + "(" + arguments + ");\n"
      result = result + "                return " + metadataSuccess(emitJsonField("_result", returnType, context)) + ";\n"
    }
  }
  return result + "            }\n        }"
}

function emitParameterValidation(name: string, value: string, type_: ResolvedType, indent: string): string {
  return indent + "if (!(" + emitJsonTypeCheck(value, type_) + ")) { return " + metadataFailure(400, "std::string(\"Parameter \\\"" + escapeCpp(name) + "\\\" expected " + jsonTypeName(type_) + " but got \") + doof::json_type_name(" + value + ")") + "; }\n"
}

function metadataFailure(code: int, message: string): string {
  return "doof::Failure<doof::JsonValue>{doof::json_error(" + string(code) + ", " + message + ")}"
}

function metadataSuccess(value: string): string {
  return "doof::Success<doof::JsonValue>{" + value + "}"
}

function methodReturnType(method: FunctionDeclaration): ResolvedType {
  case method.resolvedType! {
    function_: FunctionType -> { return function_.returnType }
    _ -> { return NoneType {} }
  }
  return NoneType {}
}

function methodSuccessType(method: FunctionDeclaration): ResolvedType {
  result := methodReturnType(method)
  case result {
    result_: ResultResolvedType -> { return result_.valueType }
    _ -> { return result }
  }
  return result
}

function emitMethodInputSchema(method: FunctionDeclaration, context: EmitContext): string {
  let properties: string[] = []
  let required: string[] = []
  for parameter of method.params {
    schema := emitTypeSchemaWithDescription(parameter.resolvedType!, parameter.description, context)
    properties.push(jsonEntry(parameter.name, schema))
    if parameter.defaultValue == none { required.push(jsonString(parameter.name)) }
  }
  let entries: string[] = [jsonEntry("type", jsonString("object")), jsonEntry("properties", jsonObject(properties))]
  if required.length > 0 { entries.push(jsonEntry("required", jsonArray(required))) }
  return jsonObject(entries)
}

function emitTypeSchemaWithDescription(type_: ResolvedType, description: string, context: EmitContext): string {
  schema := emitTypeSchemaEntries(type_, context)
  if description != "" { schema.push(jsonEntry("description", jsonString(description))) }
  return jsonObject(schema)
}

function emitTypeSchema(type_: ResolvedType, context: EmitContext): string { return jsonObject(emitTypeSchemaEntries(type_, context)) }

function emitTypeSchemaEntries(type_: ResolvedType, context: EmitContext): string[] {
  case type_ {
    primitive: PrimitiveType -> {
      if primitive.name == "byte" { return [jsonEntry("type", jsonString("integer")), jsonEntry("minimum", jsonInt(0)), jsonEntry("maximum", jsonInt(255))] }
      if primitive.name == "int" { return [jsonEntry("type", jsonString("integer")), jsonEntry("format", jsonString("int32"))] }
      if primitive.name == "long" { return [jsonEntry("type", jsonString("integer")), jsonEntry("format", jsonString("int64"))] }
      if primitive.name == "float" || primitive.name == "double" { return [jsonEntry("type", jsonString("number"))] }
      if primitive.name == "string" || primitive.name == "char" { return [jsonEntry("type", jsonString("string"))] }
      return [jsonEntry("type", jsonString("boolean"))]
    }
    _: JsonValueResolvedType -> { return [] }
    _: NoneType -> { return [jsonEntry("type", jsonString("null"))] }
    class_: ClassType -> { return [jsonEntry("$ref", jsonString("#/$defs/" + class_.name))] }
    array: ArrayResolvedType -> { return [jsonEntry("type", jsonString("array")), jsonEntry("items", emitTypeSchema(array.elementType, context))] }
    tuple: TupleResolvedType -> {
      let items: string[] = []
      for element of tuple.elements { items.push(emitTypeSchema(element, context)) }
      return [jsonEntry("type", jsonString("array")), jsonEntry("prefixItems", jsonArray(items)), jsonEntry("minItems", jsonInt(tuple.elements.length)), jsonEntry("maxItems", jsonInt(tuple.elements.length))]
    }
    enum_: EnumType -> {
      let values: string[] = []
      declaration := findEnum(context, enum_.symbol.module, enum_.name)
      if declaration != none { for variant of declaration!.variants { values.push(jsonString(variant.name)) } }
      return [jsonEntry("enum", jsonArray(values))]
    }
    union_: UnionResolvedType -> {
      let members: string[] = []
      for member of union_.types { members.push(emitTypeSchema(member, context)) }
      return [jsonEntry("anyOf", jsonArray(members))]
    }
    _ -> { return [] }
  }
  return []
}

function emitDefinitions(methods: FunctionDeclaration[], context: EmitContext): string {
  let classes: ClassDeclaration[] = []
  for method of methods {
    for parameter of method.params { collectSchemaClasses(parameter.resolvedType!, context, classes) }
    collectSchemaClasses(methodSuccessType(method), context, classes)
  }
  if classes.length == 0 { return "" }
  let entries: string[] = []
  for class_ of classes { entries.push(jsonEntry(class_.name, emitClassSchema(class_, context))) }
  return jsonObject(entries)
}

function collectSchemaClasses(type_: ResolvedType, context: EmitContext, classes: ClassDeclaration[]): none {
  case type_ {
    classType: ClassType -> {
      declaration := findClass(context, classType.symbol.module, classType.name)
      if declaration == none || containsClass(classes, declaration!) { return }
      classes.push(declaration!)
      for field of declaration!.fields { if !field.static_ { collectSchemaClasses(field.resolvedType!, context, classes) } }
    }
    array: ArrayResolvedType -> { collectSchemaClasses(array.elementType, context, classes) }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectSchemaClasses(element, context, classes) } }
    union_: UnionResolvedType -> { for member of union_.types { collectSchemaClasses(member, context, classes) } }
    _ -> { }
  }
}

function emitClassSchema(owner: ClassDeclaration, context: EmitContext): string {
  let properties: string[] = []
  let required: string[] = []
  for field of owner.fields {
    if field.static_ || field.private_ { continue }
    for index of 0..<field.names.length {
      description := if index < field.descriptions.length then field.descriptions[index] else ""
      properties.push(jsonEntry(field.names[index], emitTypeSchemaWithDescription(field.resolvedType!, description, context)))
      if field.defaultValue == none { required.push(jsonString(field.names[index])) }
    }
  }
  let entries: string[] = [jsonEntry("type", jsonString("object")), jsonEntry("properties", jsonObject(properties))]
  if required.length > 0 { entries.push(jsonEntry("required", jsonArray(required))) }
  if owner.description != "" { entries.push(jsonEntry("description", jsonString(owner.description))) }
  return jsonObject(entries)
}

function findClass(context: EmitContext, modulePath: string, name: string): ClassDeclaration | none {
  for program of context.allPrograms { for statement of program.statements {
    declaration := statementClass(statement)
    if declaration != none && declaration!.name == name && declaration!.resolvedSymbol != none && declaration!.resolvedSymbol!.module == modulePath { return declaration }
  } }
  return none
}

function findEnum(context: EmitContext, modulePath: string, name: string): EnumDeclaration | none {
  for program of context.allPrograms { for statement of program.statements {
    case statement {
      enum_: EnumDeclaration -> { if enum_.name == name { return enum_ } }
      export_: ExportDeclaration -> {
        case export_.declaration {
          enum_: EnumDeclaration -> { if enum_.name == name { return enum_ } }
          _ -> { }
        }
      }
      _ -> { }
    }
  } }
  return none
}

function statementClass(statement: Statement): ClassDeclaration | none {
  case statement {
    class_: ClassDeclaration -> { return class_ }
    export_: ExportDeclaration -> { return statementClass(export_.declaration) }
    _ -> { return none }
  }
  return none
}

function containsClass(classes: ClassDeclaration[], candidate: ClassDeclaration): bool {
  for class_ of classes { if class_.resolvedSymbol!.module == candidate.resolvedSymbol!.module && class_.name == candidate.name { return true } }
  return false
}

function jsonEntry(key: string, value: string): string { return "{\"" + escapeCpp(key) + "\", " + value + "}" }
function jsonString(value: string): string { return "doof::json_value(\"" + escapeCpp(value) + "\")" }
function jsonInt(value: int): string { return "doof::json_value(static_cast<int32_t>(" + string(value) + "))" }
function jsonArray(values: string[]): string { return "doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{" + joinStrings(values) + "}))" }
function jsonObject(entries: string[]): string { return "doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(doof::ordered_map<std::string, doof::JsonValue>{" + joinStrings(entries) + "}))" }

function joinStrings(values: string[]): string {
  let result = ""
  for value of values {
    if result != "" { result = result + ", " }
    result = result + value
  }
  return result
}

function escapeCpp(value: string): string {
  return value.replaceAll("\\", "\\\\").replaceAll("\"", "\\\"").replaceAll("\n", "\\n")
}
