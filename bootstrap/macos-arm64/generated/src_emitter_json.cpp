#include "src_emitter_json.hpp"

namespace app_src_emitter_json_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_json_semantics_;
#line 13 "/src/emitter-json.do"
std::string emitInterfaceJsonDeclaration(const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& owner) {
#line 14 "/src/emitter-json.do"
    if (!owner->needsJson) {
#line 14 "/src/emitter-json.do"
        return std::string("");
    }
#line 15 "/src/emitter-json.do"
    return ((((std::string("doof::Result<") + owner->name) + std::string(", std::string> ")) + owner->name) + std::string("_fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);\n"));
}
#line 18 "/src/emitter-json.do"
std::string emitInterfaceJsonDefinition(const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 19 "/src/emitter-json.do"
    if (!owner->needsJson) {
#line 19 "/src/emitter-json.do"
        return std::string("");
    }
#line 20 "/src/emitter-json.do"
    const auto discriminator = ::app_src_json_semantics_::interfaceJsonDiscriminator(owner, context->allPrograms, context->jsonEligibility);
#line 21 "/src/emitter-json.do"
    if (doof::is_null(discriminator)) {
#line 21 "/src/emitter-json.do"
        return std::string("");
    }
#line 22 "/src/emitter-json.do"
    const auto failureType = std::string("doof::Failure<std::string>");
#line 23 "/src/emitter-json.do"
    const auto successType = ((std::string("doof::Success<") + owner->name) + std::string(">"));
#line 24 "/src/emitter-json.do"
    auto result = ((((std::string("\ndoof::Result<") + owner->name) + std::string(", std::string> ")) + owner->name) + std::string("_fromJsonValue(const doof::JsonValue& _json, bool _lenient) {\n"));
#line 25 "/src/emitter-json.do"
    (result = (result + std::string("    const auto* _object = doof::json_as_object(_json);\n")));
#line 26 "/src/emitter-json.do"
    (result = (((result + std::string("    if (_object == nullptr) { return ")) + failureType) + std::string("{\"Expected JSON object\"}; }\n")));
#line 27 "/src/emitter-json.do"
    (result = (((result + std::string("    auto _discriminator_iterator = _object->find(\"")) + discriminator->fieldName) + std::string("\");\n")));
#line 28 "/src/emitter-json.do"
    (result = (((((result + std::string("    if (_discriminator_iterator == _object->end() || !doof::json_is_string(_discriminator_iterator->second)) { return ")) + failureType) + std::string("{\"Missing or invalid discriminator field \\\"")) + discriminator->fieldName) + std::string("\\\"\"}; }\n")));
#line 29 "/src/emitter-json.do"
    (result = (result + std::string("    auto _discriminator = doof::json_as_string(_discriminator_iterator->second);\n")));
#line 30 "/src/emitter-json.do"
    for (int32_t i = 0; i < static_cast<int32_t>((discriminator->entries)->size()); ++i) {
#line 31 "/src/emitter-json.do"
        const auto entry = doof::array_at(discriminator->entries, i, "src/emitter-json", 31);
#line 32 "/src/emitter-json.do"
        const auto classType_ = std::make_shared<::app_src_semantic_::ClassType>(std::string("class"), entry->declaration->name, doof::unwrap_optional(entry->declaration->resolvedSymbol), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
#line 33 "/src/emitter-json.do"
        const auto className = ::app_src_emitter_types_::emitClassInnerType(classType_, context->modulePath);
#line 34 "/src/emitter-json.do"
        (result = (((((result + std::string("    ")) + ((i == 0) ? std::string("if") : std::string("else if"))) + std::string(" (_discriminator == \"")) + entry->value) + std::string("\") {\n")));
#line 35 "/src/emitter-json.do"
        (result = (((result + std::string("        auto _result = ")) + className) + std::string("::fromJsonValue(_json, _lenient);\n")));
#line 36 "/src/emitter-json.do"
        (result = (((((result + std::string("        if (doof::is_success(_result)) { return ")) + successType) + std::string("{")) + owner->name) + std::string("{doof::success_value(_result)}}; }\n")));
#line 37 "/src/emitter-json.do"
        (result = (((result + std::string("        return ")) + failureType) + std::string("{doof::failure_error(_result)};\n")));
#line 38 "/src/emitter-json.do"
        (result = (result + std::string("    }\n")));
    }
#line 40 "/src/emitter-json.do"
    return (((((result + std::string("    return ")) + failureType) + std::string("{\"Unknown ")) + discriminator->fieldName) + std::string(": \\\"\" + _discriminator + \"\\\"\"};\n}\n"));
}
#line 44 "/src/emitter-json.do"
std::string emitGeneratedJsonDeclarations(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 45 "/src/emitter-json.do"
    const auto key = ::app_src_json_semantics_::jsonOwnerKey(owner);
#line 46 "/src/emitter-json.do"
    auto result = std::string("");
#line 47 "/src/emitter-json.do"
    if (containsJsonDemand(context->jsonSerializationKeys, key)) {
#line 48 "/src/emitter-json.do"
        (result = (result + std::string("    doof::JsonObject toJsonObject() const;\n")));
    }
#line 50 "/src/emitter-json.do"
    if (containsJsonDemand(context->jsonDeserializationKeys, key)) {
#line 51 "/src/emitter-json.do"
        const auto valueType = jsonResultValueType(owner);
#line 52 "/src/emitter-json.do"
        (result = (((result + std::string("    static doof::Result<")) + valueType) + std::string(", std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);\n")));
    }
#line 54 "/src/emitter-json.do"
    return result;
}
#line 58 "/src/emitter-json.do"
std::string emitGeneratedJsonMethods(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 59 "/src/emitter-json.do"
    const auto key = ::app_src_json_semantics_::jsonOwnerKey(owner);
#line 60 "/src/emitter-json.do"
    auto result = std::string("");
#line 61 "/src/emitter-json.do"
    if (containsJsonDemand(context->jsonSerializationKeys, key)) {
#line 61 "/src/emitter-json.do"
        (result = (result + emitToJsonObject(owner, context)));
    }
#line 62 "/src/emitter-json.do"
    if (containsJsonDemand(context->jsonDeserializationKeys, key)) {
#line 62 "/src/emitter-json.do"
        (result = (result + emitFromJsonValue(owner, context)));
    }
#line 63 "/src/emitter-json.do"
    return result;
}
#line 66 "/src/emitter-json.do"
bool containsJsonDemand(const std::shared_ptr<std::vector<std::string>>& keys, const std::string& key) {
#line 67 "/src/emitter-json.do"
    const auto& _iterable_3 = keys;
    for (const auto& existing : *_iterable_3) {
#line 67 "/src/emitter-json.do"
        if (existing == key) {
#line 67 "/src/emitter-json.do"
            return true;
        }
    }
#line 68 "/src/emitter-json.do"
    return false;
}
#line 71 "/src/emitter-json.do"
std::string emitToJsonObject(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 72 "/src/emitter-json.do"
    auto result = ((std::string("doof::JsonObject ") + owner->name) + std::string("::toJsonObject() const {\n"));
#line 73 "/src/emitter-json.do"
    (result = (result + std::string("    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();\n")));
#line 74 "/src/emitter-json.do"
    const auto& _iterable_5 = owner->fields;
    for (const auto& field : *_iterable_5) {
#line 75 "/src/emitter-json.do"
        if (field->static_) {
#line 75 "/src/emitter-json.do"
            continue;
        }
#line 76 "/src/emitter-json.do"
        const auto& _iterable_7 = field->names;
        for (const auto& name : *_iterable_7) {
#line 77 "/src/emitter-json.do"
            (result = (((((result + std::string("    (*_json)[\"")) + name) + std::string("\"] = ")) + emitJsonField((std::string("this->") + ::app_src_emitter_expr_::cppIdentifier(name)), doof::unwrap_optional(field->resolvedType), context)) + std::string(";\n")));
        }
    }
#line 80 "/src/emitter-json.do"
    return (result + std::string("    return _json;\n}\n"));
}
#line 83 "/src/emitter-json.do"
std::string emitFromJsonValue(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 84 "/src/emitter-json.do"
    const auto valueType = jsonResultValueType(owner);
#line 85 "/src/emitter-json.do"
    const auto failureType = std::string("doof::Failure<std::string>");
#line 86 "/src/emitter-json.do"
    auto result = ((((std::string("doof::Result<") + valueType) + std::string(", std::string> ")) + owner->name) + std::string("::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {\n"));
#line 87 "/src/emitter-json.do"
    (result = (result + std::string("    try {\n")));
#line 88 "/src/emitter-json.do"
    (result = (result + std::string("        const auto* _object = doof::json_as_object(_json);\n")));
#line 89 "/src/emitter-json.do"
    (result = (((result + std::string("        if (_object == nullptr) { return ")) + failureType) + std::string("{\"Expected JSON object\"}; }\n")));
#line 90 "/src/emitter-json.do"
    const auto& _iterable_9 = owner->fields;
    for (const auto& field : *_iterable_9) {
#line 91 "/src/emitter-json.do"
        if (field->static_) {
#line 91 "/src/emitter-json.do"
            continue;
        }
#line 92 "/src/emitter-json.do"
        const auto& _iterable_11 = field->names;
        for (const auto& name : *_iterable_11) {
#line 93 "/src/emitter-json.do"
            if (field->const_) {
#line 93 "/src/emitter-json.do"
                (result = (result + emitJsonConstFieldValidation(field, name, failureType)));
            } else {
#line 94 "/src/emitter-json.do"
                (result = (result + emitJsonFieldRead(field, name, context, failureType)));
            }
        }
    }
#line 97 "/src/emitter-json.do"
    auto arguments = std::string("");
#line 98 "/src/emitter-json.do"
    const auto& _iterable_13 = owner->fields;
    for (const auto& field : *_iterable_13) {
#line 99 "/src/emitter-json.do"
        if (field->static_ || field->const_) {
#line 99 "/src/emitter-json.do"
            continue;
        }
#line 100 "/src/emitter-json.do"
        const auto& _iterable_15 = field->names;
        for (const auto& name : *_iterable_15) {
#line 101 "/src/emitter-json.do"
            if (arguments != std::string("")) {
#line 101 "/src/emitter-json.do"
                (arguments = (arguments + std::string(", ")));
            }
#line 102 "/src/emitter-json.do"
            (arguments = ((arguments + std::string("_field_")) + ::app_src_emitter_expr_::cppIdentifier(name)));
#line 103 "/src/emitter-json.do"
            if (!doof::is_null(field->defaultValue)) {
#line 103 "/src/emitter-json.do"
                (arguments = (arguments + std::string(".value()")));
            }
        }
    }
#line 106 "/src/emitter-json.do"
    auto constructed = (((owner->name + std::string("{")) + arguments) + std::string("}"));
#line 107 "/src/emitter-json.do"
    if (!owner->struct_) {
#line 107 "/src/emitter-json.do"
        (constructed = ((((std::string("std::make_shared<") + owner->name) + std::string(">(")) + arguments) + std::string(")")));
    }
#line 108 "/src/emitter-json.do"
    return ((((((((((result + std::string("        return doof::Success<")) + valueType) + std::string(">{")) + constructed) + std::string("};\n")) + std::string("    } catch (const doof::JsonDecodeError& _error) {\n")) + std::string("        return ")) + failureType) + std::string("{_error.message()};\n")) + std::string("    }\n}\n"));
}
#line 114 "/src/emitter-json.do"
std::string emitJsonConstFieldValidation(const std::shared_ptr<::app_src_ast_::ClassField>& field, const std::string& name, const std::string& failureType) {
#line 115 "/src/emitter-json.do"
    if (doof::is_null(field->defaultValue)) {
#line 115 "/src/emitter-json.do"
        return std::string("");
    }
#line 116 "/src/emitter-json.do"
    const auto iterator = (std::string("_iterator_") + ::app_src_emitter_expr_::cppIdentifier(name));
#line 117 "/src/emitter-json.do"
    {
        auto _case_subject = doof::unwrap_optional(field->defaultValue);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 119 "/src/emitter-json.do"
            auto result = ((((((std::string("    if (auto ") + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\"); ")) + iterator) + std::string(" != _object->end()) {\n"));
#line 120 "/src/emitter-json.do"
            (result = (((((((((((((result + std::string("        if (!doof::json_is_string(")) + iterator) + std::string("->second) || doof::json_as_string(")) + iterator) + std::string("->second) != \"")) + value->value) + std::string("\") { return ")) + failureType) + std::string("{\"Field \\\"")) + name) + std::string("\\\" must be \\\"")) + value->value) + std::string("\\\"\"}; }\n")));
#line 121 "/src/emitter-json.do"
            return (result + std::string("    }\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
#line 124 "/src/emitter-json.do"
            auto result = ((((((std::string("    if (auto ") + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\"); ")) + iterator) + std::string(" != _object->end()) {\n"));
#line 125 "/src/emitter-json.do"
            (result = (((((((((((((result + std::string("        if (!doof::json_is_number(")) + iterator) + std::string("->second) || doof::json_as_int(")) + iterator) + std::string("->second) != ")) + doof::to_string(value->value)) + std::string(") { return ")) + failureType) + std::string("{\"Field \\\"")) + name) + std::string("\\\" must be ")) + doof::to_string(value->value)) + std::string("\"}; }\n")));
#line 126 "/src/emitter-json.do"
            return (result + std::string("    }\n"));
    }
    else {
#line 128 "/src/emitter-json.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 130 "/src/emitter-json.do"
    return std::string("");
}
#line 133 "/src/emitter-json.do"
std::string emitJsonFieldRead(const std::shared_ptr<::app_src_ast_::ClassField>& field, const std::string& name, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& failureType) {
#line 134 "/src/emitter-json.do"
    const auto type_ = doof::unwrap_optional(field->resolvedType);
#line 135 "/src/emitter-json.do"
    const auto safeName = ::app_src_emitter_expr_::cppIdentifier(name);
#line 136 "/src/emitter-json.do"
    const auto iterator = (std::string("_iterator_") + safeName);
#line 137 "/src/emitter-json.do"
    const auto value = (std::string("_field_") + safeName);
#line 138 "/src/emitter-json.do"
    const auto typeText = ::app_src_emitter_types_::emitContextType(type_, context);
#line 139 "/src/emitter-json.do"
    auto result = std::string("");
#line 140 "/src/emitter-json.do"
    if (!doof::is_null(field->defaultValue)) {
#line 141 "/src/emitter-json.do"
        (result = (((((result + std::string("    std::optional<")) + typeText) + std::string("> ")) + value) + std::string(";\n")));
#line 142 "/src/emitter-json.do"
        (result = (((((((result + std::string("    if (auto ")) + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\"); ")) + iterator) + std::string(" != _object->end()) {\n")));
#line 143 "/src/emitter-json.do"
        (result = (result + emitJsonValidation((iterator + std::string("->second")), type_, name, failureType, 2)));
#line 144 "/src/emitter-json.do"
        (result = (((((result + std::string("        ")) + value) + std::string(" = ")) + emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n")));
#line 145 "/src/emitter-json.do"
        (result = (result + std::string("    } else {\n")));
#line 146 "/src/emitter-json.do"
        auto defaultValue = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(type_));
#line 149 "/src/emitter-json.do"
        {
            auto _case_subject = doof::unwrap_optional(field->defaultValue);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
#line 150 "/src/emitter-json.do"
                (defaultValue = (((typeText + std::string("{")) + defaultValue) + std::string("}")));
        }
        else {
        }
        }
#line 153 "/src/emitter-json.do"
        (result = (((((result + std::string("        ")) + value) + std::string(" = ")) + defaultValue) + std::string(";\n")));
#line 154 "/src/emitter-json.do"
        return (result + std::string("    }\n"));
    }
#line 156 "/src/emitter-json.do"
    (result = (((((result + std::string("    auto ")) + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\");\n")));
#line 157 "/src/emitter-json.do"
    (result = (((((((result + std::string("    if (")) + iterator) + std::string(" == _object->end()) { return ")) + failureType) + std::string("{\"Missing required field \\\"")) + name) + std::string("\\\"\"}; }\n")));
#line 158 "/src/emitter-json.do"
    (result = (result + emitJsonValidation((iterator + std::string("->second")), type_, name, failureType, 1)));
#line 159 "/src/emitter-json.do"
    return (((((result + std::string("    auto ")) + value) + std::string(" = ")) + emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n"));
}
#line 162 "/src/emitter-json.do"
std::string emitJsonValidation(const std::string& json, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& name, const std::string& failureType, int32_t indent) {
#line 163 "/src/emitter-json.do"
    const auto prefix = ((indent == 2) ? std::string("            ") : std::string("        "));
#line 164 "/src/emitter-json.do"
    const auto check = emitJsonTypeCheck(json, type_);
#line 165 "/src/emitter-json.do"
    const auto expected = jsonTypeName(type_);
#line 166 "/src/emitter-json.do"
    return (((((((((((prefix + std::string("if (!(")) + check) + std::string(")) { return ")) + failureType) + std::string("{\"Field \\\"")) + name) + std::string("\\\" expected ")) + expected) + std::string(" but got \" + std::string(doof::json_type_name(")) + json) + std::string("))}; }\n"));
}
#line 169 "/src/emitter-json.do"
std::string emitJsonTypeCheck(const std::string& json, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 170 "/src/emitter-json.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 172 "/src/emitter-json.do"
            if (primitive->name == std::string("bool")) {
#line 172 "/src/emitter-json.do"
                return ((((std::string("(_lenient \? doof::json_is_lenient_boolean(") + json) + std::string(") : doof::json_is_boolean(")) + json) + std::string("))"));
            }
#line 173 "/src/emitter-json.do"
            if (primitive->name == std::string("char")) {
#line 173 "/src/emitter-json.do"
                return ((std::string("doof::json_is_char(") + json) + std::string(", _lenient)"));
            }
#line 174 "/src/emitter-json.do"
            if (primitive->name == std::string("string")) {
#line 174 "/src/emitter-json.do"
                return ((((std::string("(_lenient \? doof::json_is_lenient_string(") + json) + std::string(") : doof::json_is_string(")) + json) + std::string("))"));
            }
#line 175 "/src/emitter-json.do"
            return ((((std::string("(_lenient \? doof::json_is_lenient_number(") + json) + std::string(") : doof::json_is_number(")) + json) + std::string("))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 177 "/src/emitter-json.do"
            return std::string("true");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 178 "/src/emitter-json.do"
            return ((std::string("doof::json_is_object(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 179 "/src/emitter-json.do"
            return ((std::string("doof::json_is_string(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 180 "/src/emitter-json.do"
            return ((std::string("doof::json_is_array(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 181 "/src/emitter-json.do"
            return (((((std::string("doof::json_is_array(") + json) + std::string(") && doof::json_as_array(")) + json) + std::string(")->size() == ")) + doof::to_string(static_cast<int32_t>((tuple->elements)->size())));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 182 "/src/emitter-json.do"
            return ((std::string("doof::json_is_object(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 184 "/src/emitter-json.do"
            const auto inner = doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)));
#line 185 "/src/emitter-json.do"
            return (((std::string("doof::json_is_null(") + json) + std::string(") || ")) + emitJsonTypeCheck(json, inner));
    }
    else {
#line 187 "/src/emitter-json.do"
            return std::string("false");
    }
    }
    doof::unreachable();
#line 189 "/src/emitter-json.do"
    return std::string("false");
}
#line 192 "/src/emitter-json.do"
std::string emitJsonRead(const std::string& json, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 193 "/src/emitter-json.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 194 "/src/emitter-json.do"
            return emitPrimitiveJsonRead(json, primitive->name);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 195 "/src/emitter-json.do"
            return json;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 197 "/src/emitter-json.do"
            return ((((std::string("doof::json_decode_value(") + ::app_src_emitter_types_::emitClassInnerType(class_, context->modulePath)) + std::string("::fromJsonValue(")) + json) + std::string(", _lenient))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 200 "/src/emitter-json.do"
            return ((((((std::string("doof::json_decode_optional(") + ::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context)) + std::string("_fromName(doof::json_as_string(")) + json) + std::string(")), std::string(\"Unknown enum value: \") + doof::json_as_string(")) + json) + std::string("))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 203 "/src/emitter-json.do"
            const auto elementType = ::app_src_emitter_types_::emitContextType(array->elementType, context);
#line 204 "/src/emitter-json.do"
            const auto elementValue = emitJsonRead(std::string("_element"), array->elementType, context);
#line 205 "/src/emitter-json.do"
            return ((((((std::string("[&]() { const auto* _array = doof::json_as_array(") + json) + std::string("); auto _values = std::make_shared<std::vector<")) + elementType) + std::string(">>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(")) + elementValue) + std::string("); } return _values; }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 208 "/src/emitter-json.do"
            auto elements = std::string("");
#line 209 "/src/emitter-json.do"
            for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
#line 210 "/src/emitter-json.do"
                if (i > 0) {
#line 210 "/src/emitter-json.do"
                    (elements = (elements + std::string(", ")));
                }
#line 211 "/src/emitter-json.do"
                (elements = (elements + emitJsonRead(((std::string("(*_tuple)[") + doof::to_string(i)) + std::string("]")), doof::array_at(tuple->elements, i, "src/emitter-json", 211), context)));
            }
#line 213 "/src/emitter-json.do"
            return ((((std::string("[&]() { const auto* _tuple = doof::json_as_array(") + json) + std::string("); return std::make_tuple(")) + elements) + std::string("); }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 216 "/src/emitter-json.do"
            const auto valueType = ::app_src_emitter_types_::emitContextType(map->valueType, context);
#line 217 "/src/emitter-json.do"
            const auto entryValue = emitJsonRead(std::string("_entry.second"), map->valueType, context);
#line 218 "/src/emitter-json.do"
            return ((((((std::string("[&]() { const auto* _object_value = doof::json_as_object(") + json) + std::string("); auto _values = std::make_shared<doof::ordered_map<std::string, ")) + valueType) + std::string(">>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = ")) + entryValue) + std::string("; } return _values; }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 221 "/src/emitter-json.do"
            const auto inner = doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)));
#line 222 "/src/emitter-json.do"
            if (::app_src_emitter_types_::usesVariantRepresentation(type_)) {
#line 223 "/src/emitter-json.do"
                const auto optionalType = ::app_src_emitter_types_::emitContextType(type_, context);
#line 224 "/src/emitter-json.do"
                return ((((((((std::string("(doof::json_is_null(") + json) + std::string(") \? ")) + optionalType) + std::string("{std::monostate{}} : ")) + optionalType) + std::string("{")) + emitJsonRead(json, inner, context)) + std::string("})"));
            }
#line 226 "/src/emitter-json.do"
            {
                auto _case_subject = inner;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 228 "/src/emitter-json.do"
                    if (class_->symbol->kind != std::string("struct")) {
#line 228 "/src/emitter-json.do"
                        return ((((std::string("(doof::json_is_null(") + json) + std::string(") \? nullptr : ")) + emitJsonRead(json, inner, context)) + std::string(")"));
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 231 "/src/emitter-json.do"
                    return ((((std::string("(doof::json_is_null(") + json) + std::string(") \? nullptr : ")) + emitJsonRead(json, inner, context)) + std::string(")"));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 234 "/src/emitter-json.do"
                    return ((((std::string("(doof::json_is_null(") + json) + std::string(") \? nullptr : ")) + emitJsonRead(json, inner, context)) + std::string(")"));
            }
            else {
            }
            }
#line 238 "/src/emitter-json.do"
            const auto optionalType = ::app_src_emitter_types_::emitContextType(type_, context);
#line 239 "/src/emitter-json.do"
            return ((((((((std::string("(doof::json_is_null(") + json) + std::string(") \? ")) + optionalType) + std::string("{std::nullopt} : ")) + optionalType) + std::string("{")) + emitJsonRead(json, inner, context)) + std::string("})"));
    }
    else {
#line 241 "/src/emitter-json.do"
            return std::string("{}");
    }
    }
    doof::unreachable();
#line 243 "/src/emitter-json.do"
    return std::string("{}");
}
#line 246 "/src/emitter-json.do"
std::string emitPrimitiveJsonRead(const std::string& json, const std::string& name) {
#line 247 "/src/emitter-json.do"
    if (name == std::string("bool")) {
#line 247 "/src/emitter-json.do"
        return ((((std::string("(_lenient \? doof::json_as_bool_lenient(") + json) + std::string(") : doof::json_as_bool(")) + json) + std::string("))"));
    }
#line 248 "/src/emitter-json.do"
    if (name == std::string("byte")) {
#line 248 "/src/emitter-json.do"
        return ((((std::string("static_cast<uint8_t>(_lenient \? doof::json_as_int_lenient(") + json) + std::string(") : doof::json_as_int(")) + json) + std::string("))"));
    }
#line 249 "/src/emitter-json.do"
    if (name == std::string("int")) {
#line 249 "/src/emitter-json.do"
        return ((((std::string("(_lenient \? doof::json_as_int_lenient(") + json) + std::string(") : doof::json_as_int(")) + json) + std::string("))"));
    }
#line 250 "/src/emitter-json.do"
    if (name == std::string("long")) {
#line 250 "/src/emitter-json.do"
        return ((((std::string("(_lenient \? doof::json_as_long_lenient(") + json) + std::string(") : doof::json_as_long(")) + json) + std::string("))"));
    }
#line 251 "/src/emitter-json.do"
    if (name == std::string("float")) {
#line 251 "/src/emitter-json.do"
        return ((((std::string("(_lenient \? doof::json_as_float_lenient(") + json) + std::string(") : doof::json_as_float(")) + json) + std::string("))"));
    }
#line 252 "/src/emitter-json.do"
    if (name == std::string("double")) {
#line 252 "/src/emitter-json.do"
        return ((((std::string("(_lenient \? doof::json_as_double_lenient(") + json) + std::string(") : doof::json_as_double(")) + json) + std::string("))"));
    }
#line 253 "/src/emitter-json.do"
    if (name == std::string("char")) {
#line 253 "/src/emitter-json.do"
        return ((std::string("doof::json_as_char(") + json) + std::string(", _lenient)"));
    }
#line 254 "/src/emitter-json.do"
    return ((((std::string("(_lenient \? doof::json_as_string_lenient(") + json) + std::string(") : doof::json_as_string(")) + json) + std::string("))"));
}
#line 257 "/src/emitter-json.do"
std::string jsonTypeName(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 258 "/src/emitter-json.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 260 "/src/emitter-json.do"
            if (primitive->name == std::string("bool")) {
#line 260 "/src/emitter-json.do"
                return std::string("boolean");
            }
#line 261 "/src/emitter-json.do"
            if ((primitive->name == std::string("string")) || (primitive->name == std::string("char"))) {
#line 261 "/src/emitter-json.do"
                return std::string("string");
            }
#line 262 "/src/emitter-json.do"
            return std::string("number");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 264 "/src/emitter-json.do"
            return std::string("json");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 265 "/src/emitter-json.do"
            return std::string("object");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 266 "/src/emitter-json.do"
            return std::string("string");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 267 "/src/emitter-json.do"
            return std::string("array");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
#line 268 "/src/emitter-json.do"
            return std::string("array");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 269 "/src/emitter-json.do"
            return std::string("object");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 270 "/src/emitter-json.do"
            return (jsonTypeName(doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)))) + std::string(" or null"));
    }
    else {
#line 271 "/src/emitter-json.do"
            return std::string("value");
    }
    }
    doof::unreachable();
#line 273 "/src/emitter-json.do"
    return std::string("value");
}
#line 276 "/src/emitter-json.do"
std::string emitJsonField(const std::string& value, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 277 "/src/emitter-json.do"
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 278 "/src/emitter-json.do"
            return value;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 279 "/src/emitter-json.do"
            return std::string("doof::json_value(nullptr)");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 281 "/src/emitter-json.do"
            if (primitive->name == std::string("char")) {
#line 281 "/src/emitter-json.do"
                return ((std::string("doof::json_value(doof::char_to_utf8(") + value) + std::string("))"));
            }
#line 282 "/src/emitter-json.do"
            if (primitive->name == std::string("byte")) {
#line 282 "/src/emitter-json.do"
                return ((std::string("doof::json_value(static_cast<int32_t>(") + value) + std::string("))"));
            }
#line 283 "/src/emitter-json.do"
            return ((std::string("doof::json_value(") + value) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 286 "/src/emitter-json.do"
            if (class_->symbol->kind == std::string("struct")) {
#line 286 "/src/emitter-json.do"
                return ((std::string("doof::json_value(") + value) + std::string(".toJsonObject())"));
            }
#line 287 "/src/emitter-json.do"
            return ((std::string("doof::json_value(") + value) + std::string("->toJsonObject())"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 290 "/src/emitter-json.do"
            return ((((std::string("doof::json_value(") + ::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context)) + std::string("_name(")) + value) + std::string("))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 293 "/src/emitter-json.do"
            const auto inner = doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)));
#line 294 "/src/emitter-json.do"
            if (::app_src_emitter_types_::usesVariantRepresentation(resolvedType)) {
#line 295 "/src/emitter-json.do"
                const auto innerType = ::app_src_emitter_types_::emitContextType(inner, context);
#line 296 "/src/emitter-json.do"
                return ((((std::string("(std::holds_alternative<std::monostate>(") + value) + std::string(") \? doof::json_value(nullptr) : ")) + emitJsonField(((((std::string("std::get<") + innerType) + std::string(">(")) + value) + std::string(")")), inner, context)) + std::string(")"));
            }
#line 298 "/src/emitter-json.do"
            {
                auto _case_subject = inner;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 300 "/src/emitter-json.do"
                    if (class_->symbol->kind == std::string("struct")) {
#line 300 "/src/emitter-json.do"
                        return ((((std::string("(") + value) + std::string(".has_value() \? ")) + emitJsonField((value + std::string(".value()")), inner, context)) + std::string(" : doof::json_value(nullptr))"));
                    }
#line 301 "/src/emitter-json.do"
                    return ((((std::string("(") + value) + std::string(" \? ")) + emitJsonField(value, inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 303 "/src/emitter-json.do"
                    return ((((std::string("(") + value) + std::string(" \? ")) + emitJsonField(value, inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 304 "/src/emitter-json.do"
                    return ((((std::string("(") + value) + std::string(" \? ")) + emitJsonField(value, inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            else {
#line 305 "/src/emitter-json.do"
                    return ((((std::string("(") + value) + std::string(".has_value() \? ")) + emitJsonField((value + std::string(".value()")), inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 309 "/src/emitter-json.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, array->elementType) == std::string("json-value")) {
#line 309 "/src/emitter-json.do"
                return ((std::string("doof::json_value(") + value) + std::string(")"));
            }
#line 310 "/src/emitter-json.do"
            const auto element = emitJsonField(std::string("_element"), array->elementType, context);
#line 311 "/src/emitter-json.do"
            return ((((((std::string("[&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(") + value) + std::string("->size()); for (const auto& _element : *")) + value) + std::string(") { _array->push_back(")) + element) + std::string("); } return doof::json_value(_array); }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 314 "/src/emitter-json.do"
            auto elements = std::string("");
#line 315 "/src/emitter-json.do"
            for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
#line 316 "/src/emitter-json.do"
                if (i > 0) {
#line 316 "/src/emitter-json.do"
                    (elements = (elements + std::string(", ")));
                }
#line 317 "/src/emitter-json.do"
                (elements = (elements + emitJsonField(((((std::string("std::get<") + doof::to_string(i)) + std::string(">(")) + value) + std::string(")")), doof::array_at(tuple->elements, i, "src/emitter-json", 317), context)));
            }
#line 319 "/src/emitter-json.do"
            return ((std::string("doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::initializer_list<doof::JsonValue>{") + elements) + std::string("}))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 322 "/src/emitter-json.do"
            if ((std::visit([](auto&& _obj) { return _obj->kind; }, map->keyType) == std::string("primitive")) && (std::visit([](auto&& _obj) { return _obj->kind; }, map->valueType) == std::string("json-value"))) {
#line 322 "/src/emitter-json.do"
                return ((std::string("doof::json_value(") + value) + std::string(")"));
            }
#line 323 "/src/emitter-json.do"
            const auto entryValue = emitJsonField(std::string("_entry.second"), map->valueType, context);
#line 324 "/src/emitter-json.do"
            return ((((std::string("[&]() { auto _object_value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *") + value) + std::string(") { (*_object_value)[_entry.first] = ")) + entryValue) + std::string("; } return doof::json_value(_object_value); }()"));
    }
    else {
#line 326 "/src/emitter-json.do"
            return std::string("doof::json_value(nullptr)");
    }
    }
    doof::unreachable();
#line 328 "/src/emitter-json.do"
    return std::string("doof::json_value(nullptr)");
}
#line 331 "/src/emitter-json.do"
std::string jsonResultValueType(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner) {
#line 332 "/src/emitter-json.do"
    if (owner->struct_) {
#line 332 "/src/emitter-json.do"
        return owner->name;
    }
#line 333 "/src/emitter-json.do"
    return ((std::string("std::shared_ptr<") + owner->name) + std::string(">"));
}
#line 1 "<doof-generated>"
}
