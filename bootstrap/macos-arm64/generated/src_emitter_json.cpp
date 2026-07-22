#include "src_emitter_json.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_types.hpp"
#include "src_json_semantics.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_json_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_json_semantics_;
std::string emitInterfaceJsonDeclaration(std::shared_ptr<::app_src_ast_::InterfaceDeclaration> owner) {
    if (!owner->needsJson) {
        return std::string("");
    }
    return ((((std::string("doof::Result<") + owner->name) + std::string(", std::string> ")) + owner->name) + std::string("_fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);\n"));
}
std::string emitInterfaceJsonDefinition(std::shared_ptr<::app_src_ast_::InterfaceDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (!owner->needsJson) {
        return std::string("");
    }
    const auto discriminator = ::app_src_json_semantics_::interfaceJsonDiscriminator(owner, context->allPrograms);
    if (doof::is_null(discriminator)) {
        return std::string("");
    }
    const auto failureType = std::string("doof::Failure<std::string>");
    const auto successType = ((std::string("doof::Success<") + owner->name) + std::string(">"));
    auto result = ((((std::string("\ndoof::Result<") + owner->name) + std::string(", std::string> ")) + owner->name) + std::string("_fromJsonValue(const doof::JsonValue& _json, bool _lenient) {\n"));
    (result = (result + std::string("    const auto* _object = doof::json_as_object(_json);\n")));
    (result = (((result + std::string("    if (_object == nullptr) { return ")) + failureType) + std::string("{\"Expected JSON object\"}; }\n")));
    (result = (((result + std::string("    auto _discriminator_iterator = _object->find(\"")) + discriminator->fieldName) + std::string("\");\n")));
    (result = (((((result + std::string("    if (_discriminator_iterator == _object->end() || !doof::json_is_string(_discriminator_iterator->second)) { return ")) + failureType) + std::string("{\"Missing or invalid discriminator field \\\"")) + discriminator->fieldName) + std::string("\\\"\"}; }\n")));
    (result = (result + std::string("    auto _discriminator = doof::json_as_string(_discriminator_iterator->second);\n")));
    for (int32_t i = 0; i < static_cast<int32_t>((discriminator->entries)->size()); ++i) {
        const auto entry = (*discriminator->entries)[i];
        const auto classType_ = std::make_shared<::app_src_semantic_::ClassType>(std::string("class"), entry->declaration->name, doof::unwrap_optional(entry->declaration->resolvedSymbol), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
        const auto className = ::app_src_emitter_types_::emitClassInnerType(classType_, context->modulePath);
        (result = (((((result + std::string("    ")) + ((i == 0) ? std::string("if") : std::string("else if"))) + std::string(" (_discriminator == \"")) + entry->value) + std::string("\") {\n")));
        (result = (((result + std::string("        auto _result = ")) + className) + std::string("::fromJsonValue(_json, _lenient);\n")));
        (result = (((((result + std::string("        if (doof::is_success(_result)) { return ")) + successType) + std::string("{")) + owner->name) + std::string("{doof::success_value(_result)}}; }\n")));
        (result = (((result + std::string("        return ")) + failureType) + std::string("{doof::failure_error(_result)};\n")));
        (result = (result + std::string("    }\n")));
    }
    return (((((result + std::string("    return ")) + failureType) + std::string("{\"Unknown ")) + discriminator->fieldName) + std::string(": \\\"\" + _discriminator + \"\\\"\"};\n}\n"));
}
std::string emitGeneratedJsonDeclarations(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (!::app_src_json_semantics_::canGenerateJsonSerialization(owner, context->allPrograms)) {
        return std::string("");
    }
    auto result = std::string("    doof::JsonObject toJsonObject() const;\n");
    if (::app_src_json_semantics_::canGenerateJsonDeserialization(owner, context->allPrograms)) {
        const auto valueType = jsonResultValueType(owner);
        (result = (((result + std::string("    static doof::Result<")) + valueType) + std::string(", std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);\n")));
    }
    return result;
}
std::string emitGeneratedJsonMethods(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (!::app_src_json_semantics_::canGenerateJsonSerialization(owner, context->allPrograms)) {
        return std::string("");
    }
    auto result = emitToJsonObject(owner, context);
    if (::app_src_json_semantics_::canGenerateJsonDeserialization(owner, context->allPrograms)) {
        (result = (result + emitFromJsonValue(owner, context)));
    }
    return result;
}
std::string emitToJsonObject(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto result = ((std::string("doof::JsonObject ") + owner->name) + std::string("::toJsonObject() const {\n"));
    (result = (result + std::string("    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();\n")));
    const auto& _iterable_1 = owner->fields;
    for (const auto& field : *_iterable_1) {
        if (field->static_) {
            continue;
        }
        const auto& _iterable_2 = field->names;
        for (const auto& name : *_iterable_2) {
            (result = (((((result + std::string("    (*_json)[\"")) + name) + std::string("\"] = ")) + emitJsonField((std::string("this->") + ::app_src_emitter_expr_::cppIdentifier(name)), doof::unwrap_optional(field->resolvedType), context)) + std::string(";\n")));
        }
    }
    return (result + std::string("    return _json;\n}\n"));
}
std::string emitFromJsonValue(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto valueType = jsonResultValueType(owner);
    const auto failureType = std::string("doof::Failure<std::string>");
    auto result = ((((std::string("doof::Result<") + valueType) + std::string(", std::string> ")) + owner->name) + std::string("::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {\n"));
    (result = (result + std::string("    const auto* _object = doof::json_as_object(_json);\n")));
    (result = (((result + std::string("    if (_object == nullptr) { return ")) + failureType) + std::string("{\"Expected JSON object\"}; }\n")));
    const auto& _iterable_3 = owner->fields;
    for (const auto& field : *_iterable_3) {
        if (field->static_) {
            continue;
        }
        const auto& _iterable_4 = field->names;
        for (const auto& name : *_iterable_4) {
            if (field->const_) {
                (result = (result + emitJsonConstFieldValidation(field, name, failureType)));
            } else {
                (result = (result + emitJsonFieldRead(field, name, context, failureType)));
            }
        }
    }
    auto arguments = std::string("");
    const auto& _iterable_5 = owner->fields;
    for (const auto& field : *_iterable_5) {
        if (field->static_ || field->const_) {
            continue;
        }
        const auto& _iterable_6 = field->names;
        for (const auto& name : *_iterable_6) {
            if (arguments != std::string("")) {
                (arguments = (arguments + std::string(", ")));
            }
            (arguments = ((arguments + std::string("_field_")) + ::app_src_emitter_expr_::cppIdentifier(name)));
            if (!doof::is_null(field->defaultValue)) {
                (arguments = (arguments + std::string(".value()")));
            }
        }
    }
    auto constructed = (((owner->name + std::string("{")) + arguments) + std::string("}"));
    if (!owner->struct_) {
        (constructed = ((((std::string("std::make_shared<") + owner->name) + std::string(">(")) + arguments) + std::string(")")));
    }
    return (((((result + std::string("    return doof::Success<")) + valueType) + std::string(">{")) + constructed) + std::string("};\n}\n"));
}
std::string emitJsonConstFieldValidation(std::shared_ptr<::app_src_ast_::ClassField> field, std::string name, std::string failureType) {
    if (doof::is_null(field->defaultValue)) {
        return std::string("");
    }
    const auto iterator = (std::string("_iterator_") + ::app_src_emitter_expr_::cppIdentifier(name));
    {
        auto _case_subject = doof::unwrap_optional(field->defaultValue);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
            auto result = ((((((std::string("    if (auto ") + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\"); ")) + iterator) + std::string(" != _object->end()) {\n"));
            (result = (((((((((((((result + std::string("        if (!doof::json_is_string(")) + iterator) + std::string("->second) || doof::json_as_string(")) + iterator) + std::string("->second) != \"")) + value->value) + std::string("\") { return ")) + failureType) + std::string("{\"Field \\\"")) + name) + std::string("\\\" must be \\\"")) + value->value) + std::string("\\\"\"}; }\n")));
            return (result + std::string("    }\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
            auto result = ((((((std::string("    if (auto ") + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\"); ")) + iterator) + std::string(" != _object->end()) {\n"));
            (result = (((((((((((((result + std::string("        if (!doof::json_is_number(")) + iterator) + std::string("->second) || doof::json_as_int(")) + iterator) + std::string("->second) != ")) + doof::to_string(value->value)) + std::string(") { return ")) + failureType) + std::string("{\"Field \\\"")) + name) + std::string("\\\" must be ")) + doof::to_string(value->value)) + std::string("\"}; }\n")));
            return (result + std::string("    }\n"));
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitJsonFieldRead(std::shared_ptr<::app_src_ast_::ClassField> field, std::string name, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string failureType) {
    const auto type_ = doof::unwrap_optional(field->resolvedType);
    const auto safeName = ::app_src_emitter_expr_::cppIdentifier(name);
    const auto iterator = (std::string("_iterator_") + safeName);
    const auto value = (std::string("_field_") + safeName);
    const auto typeText = ::app_src_emitter_types_::emitContextType(type_, context);
    auto result = std::string("");
    if (!doof::is_null(field->defaultValue)) {
        (result = (((((result + std::string("    std::optional<")) + typeText) + std::string("> ")) + value) + std::string(";\n")));
        (result = (((((((result + std::string("    if (auto ")) + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\"); ")) + iterator) + std::string(" != _object->end()) {\n")));
        (result = (result + emitJsonValidation((iterator + std::string("->second")), type_, name, failureType, 2)));
        (result = (((((result + std::string("        ")) + value) + std::string(" = ")) + emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n")));
        (result = (result + std::string("    } else {\n")));
        auto defaultValue = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(type_));
        {
            auto _case_subject = doof::unwrap_optional(field->defaultValue);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
                (defaultValue = (((typeText + std::string("{")) + defaultValue) + std::string("}")));
        }
        else {
        }
        }
        (result = (((((result + std::string("        ")) + value) + std::string(" = ")) + defaultValue) + std::string(";\n")));
        return (result + std::string("    }\n"));
    }
    (result = (((((result + std::string("    auto ")) + iterator) + std::string(" = _object->find(\"")) + name) + std::string("\");\n")));
    (result = (((((((result + std::string("    if (")) + iterator) + std::string(" == _object->end()) { return ")) + failureType) + std::string("{\"Missing required field \\\"")) + name) + std::string("\\\"\"}; }\n")));
    (result = (result + emitJsonValidation((iterator + std::string("->second")), type_, name, failureType, 1)));
    return (((((result + std::string("    auto ")) + value) + std::string(" = ")) + emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n"));
}
std::string emitJsonValidation(std::string json, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::string name, std::string failureType, int32_t indent) {
    const auto prefix = ((indent == 2) ? std::string("        ") : std::string("    "));
    const auto check = emitJsonTypeCheck(json, type_);
    const auto expected = jsonTypeName(type_);
    return (((((((((((prefix + std::string("if (!(")) + check) + std::string(")) { return ")) + failureType) + std::string("{\"Field \\\"")) + name) + std::string("\\\" expected ")) + expected) + std::string(" but got \" + std::string(doof::json_type_name(")) + json) + std::string("))}; }\n"));
}
std::string emitJsonTypeCheck(std::string json, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            if (primitive->name == std::string("bool")) {
                return ((((std::string("(_lenient ? doof::json_is_lenient_boolean(") + json) + std::string(") : doof::json_is_boolean(")) + json) + std::string("))"));
            }
            if ((primitive->name == std::string("string")) || (primitive->name == std::string("char"))) {
                return ((((std::string("(_lenient ? doof::json_is_lenient_string(") + json) + std::string(") : doof::json_is_string(")) + json) + std::string("))"));
            }
            return ((((std::string("(_lenient ? doof::json_is_lenient_number(") + json) + std::string(") : doof::json_is_number(")) + json) + std::string("))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return std::string("true");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            return ((std::string("doof::json_is_object(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return ((std::string("doof::json_is_string(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            return ((std::string("doof::json_is_array(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            return (((((std::string("doof::json_is_array(") + json) + std::string(") && doof::json_as_array(")) + json) + std::string(")->size() == ")) + doof::to_string(static_cast<int32_t>((tuple->elements)->size())));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            return ((std::string("doof::json_is_object(") + json) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto inner = doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)));
            return (((std::string("doof::json_is_null(") + json) + std::string(") || ")) + emitJsonTypeCheck(json, inner));
    }
    else {
            return std::string("false");
    }
    }
    doof::unreachable();
    return std::string("false");
}
std::string emitJsonRead(std::string json, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            return emitPrimitiveJsonRead(json, primitive->name);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return json;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            return ((((std::string("doof::success_value(") + ::app_src_emitter_types_::emitClassInnerType(class_, context->modulePath)) + std::string("::fromJsonValue(")) + json) + std::string(", _lenient))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            return (((::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context) + std::string("_fromName(doof::json_as_string(")) + json) + std::string(")).value()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            const auto elementType = ::app_src_emitter_types_::emitContextType(array->elementType, context);
            const auto elementValue = emitJsonRead(std::string("_element"), array->elementType, context);
            return ((((((std::string("[&]() { const auto* _array = doof::json_as_array(") + json) + std::string("); auto _values = std::make_shared<std::vector<")) + elementType) + std::string(">>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(")) + elementValue) + std::string("); } return _values; }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            auto elements = std::string("");
            for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
                if (i > 0) {
                    (elements = (elements + std::string(", ")));
                }
                (elements = (elements + emitJsonRead(((std::string("(*_tuple)[") + doof::to_string(i)) + std::string("]")), (*tuple->elements)[i], context)));
            }
            return ((((std::string("[&]() { const auto* _tuple = doof::json_as_array(") + json) + std::string("); return std::make_tuple(")) + elements) + std::string("); }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            const auto valueType = ::app_src_emitter_types_::emitContextType(map->valueType, context);
            const auto entryValue = emitJsonRead(std::string("_entry.second"), map->valueType, context);
            return ((((((std::string("[&]() { const auto* _object_value = doof::json_as_object(") + json) + std::string("); auto _values = std::make_shared<doof::ordered_map<std::string, ")) + valueType) + std::string(">>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = ")) + entryValue) + std::string("; } return _values; }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto inner = doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)));
            if (::app_src_emitter_types_::usesVariantRepresentation(type_)) {
                const auto optionalType = ::app_src_emitter_types_::emitContextType(type_, context);
                return ((((((((std::string("(doof::json_is_null(") + json) + std::string(") ? ")) + optionalType) + std::string("{std::monostate{}} : ")) + optionalType) + std::string("{")) + emitJsonRead(json, inner, context)) + std::string("})"));
            }
            {
                auto _case_subject = inner;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                    if (class_->symbol->kind != std::string("struct")) {
                        return ((((std::string("(doof::json_is_null(") + json) + std::string(") ? nullptr : ")) + emitJsonRead(json, inner, context)) + std::string(")"));
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    return ((((std::string("(doof::json_is_null(") + json) + std::string(") ? nullptr : ")) + emitJsonRead(json, inner, context)) + std::string(")"));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                    return ((((std::string("(doof::json_is_null(") + json) + std::string(") ? nullptr : ")) + emitJsonRead(json, inner, context)) + std::string(")"));
            }
            else {
            }
            }
            const auto optionalType = ::app_src_emitter_types_::emitContextType(type_, context);
            return ((((((((std::string("(doof::json_is_null(") + json) + std::string(") ? ")) + optionalType) + std::string("{std::nullopt} : ")) + optionalType) + std::string("{")) + emitJsonRead(json, inner, context)) + std::string("})"));
    }
    else {
            return std::string("{}");
    }
    }
    doof::unreachable();
    return std::string("{}");
}
std::string emitPrimitiveJsonRead(std::string json, std::string name) {
    if (name == std::string("bool")) {
        return ((((std::string("(_lenient ? doof::json_as_bool_lenient(") + json) + std::string(") : doof::json_as_bool(")) + json) + std::string("))"));
    }
    if (name == std::string("byte")) {
        return ((((std::string("static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(") + json) + std::string(") : doof::json_as_int(")) + json) + std::string("))"));
    }
    if (name == std::string("int")) {
        return ((((std::string("(_lenient ? doof::json_as_int_lenient(") + json) + std::string(") : doof::json_as_int(")) + json) + std::string("))"));
    }
    if (name == std::string("long")) {
        return ((((std::string("(_lenient ? doof::json_as_long_lenient(") + json) + std::string(") : doof::json_as_long(")) + json) + std::string("))"));
    }
    if (name == std::string("float")) {
        return ((((std::string("(_lenient ? doof::json_as_float_lenient(") + json) + std::string(") : doof::json_as_float(")) + json) + std::string("))"));
    }
    if (name == std::string("double")) {
        return ((((std::string("(_lenient ? doof::json_as_double_lenient(") + json) + std::string(") : doof::json_as_double(")) + json) + std::string("))"));
    }
    if (name == std::string("char")) {
        return ((std::string("static_cast<char32_t>(doof::json_as_string(") + json) + std::string(")[0])"));
    }
    return ((((std::string("(_lenient ? doof::json_as_string_lenient(") + json) + std::string(") : doof::json_as_string(")) + json) + std::string("))"));
}
std::string jsonTypeName(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            if (primitive->name == std::string("bool")) {
                return std::string("boolean");
            }
            if ((primitive->name == std::string("string")) || (primitive->name == std::string("char"))) {
                return std::string("string");
            }
            return std::string("number");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return std::string("json");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            return std::string("object");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return std::string("string");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            return std::string("array");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            return std::string("array");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            return std::string("object");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            return (jsonTypeName(doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)))) + std::string(" or null"));
    }
    else {
            return std::string("value");
    }
    }
    doof::unreachable();
    return std::string("value");
}
std::string emitJsonField(std::string value, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return value;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            return std::string("doof::json_value(nullptr)");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            if (primitive->name == std::string("char")) {
                return ((std::string("doof::json_value(std::string(1, static_cast<char>(") + value) + std::string(")))"));
            }
            if (primitive->name == std::string("byte")) {
                return ((std::string("doof::json_value(static_cast<int32_t>(") + value) + std::string("))"));
            }
            return ((std::string("doof::json_value(") + value) + std::string(")"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (class_->symbol->kind == std::string("struct")) {
                return ((std::string("doof::json_value(") + value) + std::string(".toJsonObject())"));
            }
            return ((std::string("doof::json_value(") + value) + std::string("->toJsonObject())"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            return ((((std::string("doof::json_value(") + ::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context)) + std::string("_name(")) + value) + std::string("))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto inner = doof::unwrap_optional(::app_src_json_semantics_::nullableJsonMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_)));
            if (::app_src_emitter_types_::usesVariantRepresentation(resolvedType)) {
                const auto innerType = ::app_src_emitter_types_::emitContextType(inner, context);
                return ((((std::string("(std::holds_alternative<std::monostate>(") + value) + std::string(") ? doof::json_value(nullptr) : ")) + emitJsonField(((((std::string("std::get<") + innerType) + std::string(">(")) + value) + std::string(")")), inner, context)) + std::string(")"));
            }
            {
                auto _case_subject = inner;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                    if (class_->symbol->kind == std::string("struct")) {
                        return ((((std::string("(") + value) + std::string(".has_value() ? ")) + emitJsonField((value + std::string(".value()")), inner, context)) + std::string(" : doof::json_value(nullptr))"));
                    }
                    return ((((std::string("(") + value) + std::string(" ? ")) + emitJsonField(value, inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    return ((((std::string("(") + value) + std::string(" ? ")) + emitJsonField(value, inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                    return ((((std::string("(") + value) + std::string(" ? ")) + emitJsonField(value, inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            else {
                    return ((((std::string("(") + value) + std::string(".has_value() ? ")) + emitJsonField((value + std::string(".value()")), inner, context)) + std::string(" : doof::json_value(nullptr))"));
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            if (std::visit([](auto&& _obj) { return _obj->kind; }, array->elementType) == std::string("json-value")) {
                return ((std::string("doof::json_value(") + value) + std::string(")"));
            }
            const auto element = emitJsonField(std::string("_element"), array->elementType, context);
            return ((((((std::string("[&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(") + value) + std::string("->size()); for (const auto& _element : *")) + value) + std::string(") { _array->push_back(")) + element) + std::string("); } return doof::json_value(_array); }()"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            auto elements = std::string("");
            for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
                if (i > 0) {
                    (elements = (elements + std::string(", ")));
                }
                (elements = (elements + emitJsonField(((((std::string("std::get<") + doof::to_string(i)) + std::string(">(")) + value) + std::string(")")), (*tuple->elements)[i], context)));
            }
            return ((std::string("doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::initializer_list<doof::JsonValue>{") + elements) + std::string("}))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            if ((std::visit([](auto&& _obj) { return _obj->kind; }, map->keyType) == std::string("primitive")) && (std::visit([](auto&& _obj) { return _obj->kind; }, map->valueType) == std::string("json-value"))) {
                return ((std::string("doof::json_value(") + value) + std::string(")"));
            }
            const auto entryValue = emitJsonField(std::string("_entry.second"), map->valueType, context);
            return ((((std::string("[&]() { auto _object_value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *") + value) + std::string(") { (*_object_value)[_entry.first] = ")) + entryValue) + std::string("; } return doof::json_value(_object_value); }()"));
    }
    else {
            return std::string("doof::json_value(nullptr)");
    }
    }
    doof::unreachable();
    return std::string("doof::json_value(nullptr)");
}
std::string jsonResultValueType(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner) {
    if (owner->struct_) {
        return owner->name;
    }
    return ((std::string("std::shared_ptr<") + owner->name) + std::string(">"));
}
}
