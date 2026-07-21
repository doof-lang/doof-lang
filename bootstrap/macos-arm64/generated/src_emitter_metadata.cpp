#include "src_emitter_metadata.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_types.hpp"
#include "src_emitter_json.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_metadata_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_json_;
std::string emitMetadataDeclaration(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner) {
    if (!owner->needsMetadata) {
        return std::string("");
    }
    return ((std::string("    static const doof::ClassMetadata<") + owner->name) + std::string("> _metadata;\n"));
}
std::string emitMetadataDefinition(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (!owner->needsMetadata) {
        return std::string("");
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>{});
    const auto& _iterable_1 = owner->methods;
    for (const auto& method : *_iterable_1) {
        if (!method->private_ && !method->static_) {
            methods->push_back(method);
        }
    }
    auto result = ((((std::string("inline const doof::ClassMetadata<") + owner->name) + std::string("> ")) + owner->name) + std::string("::_metadata = {\n"));
    (result = (((result + std::string("    \"")) + escapeCpp(owner->name)) + std::string("\",\n")));
    (result = (((result + std::string("    \"")) + escapeCpp(owner->description)) + std::string("\",\n")));
    (result = (((((result + std::string("    std::make_shared<std::vector<doof::MethodReflection<")) + owner->name) + std::string(">>>(std::vector<doof::MethodReflection<")) + owner->name) + std::string(">>{\n")));
    for (int32_t index = 0; index < static_cast<int32_t>((methods)->size()); ++index) {
        const auto method = (*methods)[index];
        (result = (result + emitMethodReflection(owner, method, context)));
        if ((index + 1) < static_cast<int32_t>((methods)->size())) {
            (result = (result + std::string(",")));
        }
        (result = (result + std::string("\n")));
    }
    (result = (result + std::string("    }),\n")));
    const auto defs = emitDefinitions(methods, context);
    (result = (((result + std::string("    ")) + ((defs == std::string("")) ? std::string("std::nullopt") : ((std::string("std::optional<doof::JsonValue>{") + defs) + std::string("}")))) + std::string("\n")));
    return (result + std::string("};\n"));
}
std::string emitMethodReflection(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_ast_::FunctionDeclaration> method, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto inputSchema = emitMethodInputSchema(method, context);
    const auto outputSchema = emitTypeSchema(methodSuccessType(method), context);
    auto result = ((std::string("        doof::MethodReflection<") + owner->name) + std::string(">{\n"));
    (result = (((result + std::string("            \"")) + escapeCpp(method->name)) + std::string("\",\n")));
    (result = (((result + std::string("            \"")) + escapeCpp(method->description)) + std::string("\",\n")));
    (result = (((result + std::string("            ")) + inputSchema) + std::string(",\n")));
    (result = (((result + std::string("            ")) + outputSchema) + std::string(",\n")));
    (result = (((result + std::string("            []( ")) + owner->name) + std::string("& _instance, const doof::JsonValue& _params) -> doof::Result<doof::JsonValue, doof::JsonValue> {\n")));
    (result = (result + std::string("                const bool _lenient = false;\n")));
    (result = (result + std::string("                const auto* _p = doof::json_as_object(_params);\n")));
    (result = (((result + std::string("                if (_p == nullptr) { return ")) + metadataFailure(400, std::string("std::string(\"Invalid JSON params: expected object\")"))) + std::string("; }\n")));
    const auto& _iterable_2 = method->params;
    for (const auto& parameter : *_iterable_2) {
        const auto type_ = doof::unwrap_optional(parameter->resolvedType);
        const auto safeName = ::app_src_emitter_expr_::cppIdentifier(parameter->name);
        const auto iterator = (std::string("_it_") + safeName);
        if (!doof::is_null(parameter->defaultValue)) {
            (result = (((((result + std::string("                ")) + ::app_src_emitter_types_::emitContextType(type_, context)) + std::string(" ")) + safeName) + std::string(";\n")));
            (result = (((((((result + std::string("                if (auto ")) + iterator) + std::string(" = _p->find(\"")) + escapeCpp(parameter->name)) + std::string("\"); ")) + iterator) + std::string(" != _p->end()) {\n")));
            (result = (result + emitParameterValidation(parameter->name, (iterator + std::string("->second")), type_, std::string("                    "))));
            (result = (((((result + std::string("                    ")) + safeName) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n")));
            (result = (((((result + std::string("                } else { ")) + safeName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, doof::optional_value(type_))) + std::string("; }\n")));
        } else {
            (result = (((((result + std::string("                auto ")) + iterator) + std::string(" = _p->find(\"")) + escapeCpp(parameter->name)) + std::string("\");\n")));
            (result = (((((result + std::string("                if (")) + iterator) + std::string(" == _p->end()) { return ")) + metadataFailure(400, ((std::string("std::string(\"Missing required parameter \\\"") + escapeCpp(parameter->name)) + std::string("\\\"\")")))) + std::string("; }\n")));
            (result = (result + emitParameterValidation(parameter->name, (iterator + std::string("->second")), type_, std::string("                "))));
            (result = (((((result + std::string("                auto ")) + safeName) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n")));
        }
    }
    auto arguments = std::string("");
    const auto& _iterable_3 = method->params;
    for (const auto& parameter : *_iterable_3) {
        if (arguments != std::string("")) {
            (arguments = (arguments + std::string(", ")));
        }
        (arguments = (arguments + ::app_src_emitter_expr_::cppIdentifier(parameter->name)));
    }
    const auto returnType = methodReturnType(method);
    {
        auto _case_subject = returnType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            (result = (((((result + std::string("                _instance.")) + ::app_src_emitter_expr_::cppIdentifier(method->name)) + std::string("(")) + arguments) + std::string(");\n")));
            (result = (((result + std::string("                return ")) + metadataSuccess(std::string("doof::json_value(nullptr)"))) + std::string(";\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& resultType = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            (result = (((((result + std::string("                auto _result = _instance.")) + ::app_src_emitter_expr_::cppIdentifier(method->name)) + std::string("(")) + arguments) + std::string(");\n")));
            (result = (result + std::string("                if (doof::is_failure(_result)) {\n")));
            if (doof::kind(resultType->errorType) == std::string("json-value")) {
                (result = (result + std::string("                    return doof::Failure<doof::JsonValue>{doof::failure_error(_result)};\n")));
            } else {
                (result = (((result + std::string("                    return ")) + metadataFailure(500, std::string("\"An error occurred\""))) + std::string(";\n")));
            }
            (result = (result + std::string("                }\n")));
            if (doof::kind(resultType->valueType) == std::string("none")) {
                (result = (((result + std::string("                return ")) + metadataSuccess(std::string("doof::json_value(nullptr)"))) + std::string(";\n")));
            } else {
                (result = (result + std::string("                auto _success = doof::success_value(_result);\n")));
                (result = (((result + std::string("                return ")) + metadataSuccess(::app_src_emitter_json_::emitJsonField(std::string("_success"), resultType->valueType, context))) + std::string(";\n")));
            }
    }
    else {
            (result = (((((result + std::string("                auto _result = _instance.")) + ::app_src_emitter_expr_::cppIdentifier(method->name)) + std::string("(")) + arguments) + std::string(");\n")));
            (result = (((result + std::string("                return ")) + metadataSuccess(::app_src_emitter_json_::emitJsonField(std::string("_result"), returnType, context))) + std::string(";\n")));
    }
    }
    return (result + std::string("            }\n        }"));
}
std::string emitParameterValidation(std::string name, std::string value, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::string indent) {
    return (((((indent + std::string("if (!(")) + ::app_src_emitter_json_::emitJsonTypeCheck(value, type_)) + std::string(")) { return ")) + metadataFailure(400, ((((((std::string("std::string(\"Parameter \\\"") + escapeCpp(name)) + std::string("\\\" expected ")) + ::app_src_emitter_json_::jsonTypeName(type_)) + std::string(" but got \") + doof::json_type_name(")) + value) + std::string(")")))) + std::string("; }\n"));
}
std::string metadataFailure(int32_t code, std::string message) {
    return ((((std::string("doof::Failure<doof::JsonValue>{doof::json_error(") + doof::to_string(code)) + std::string(", ")) + message) + std::string(")}"));
}
std::string metadataSuccess(std::string value) {
    return ((std::string("doof::Success<doof::JsonValue>{") + value) + std::string("}"));
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> methodReturnType(std::shared_ptr<::app_src_ast_::FunctionDeclaration> method) {
    {
        auto _case_subject = doof::unwrap_optional(method->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            return function_->returnType;
    }
    else {
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none")));
    }
    }
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none")));
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> methodSuccessType(std::shared_ptr<::app_src_ast_::FunctionDeclaration> method) {
    const auto result = methodReturnType(method);
    {
        auto _case_subject = result;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return result_->valueType;
    }
    else {
            return result;
    }
    }
    return result;
}
std::string emitMethodInputSchema(std::shared_ptr<::app_src_ast_::FunctionDeclaration> method, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    std::shared_ptr<std::vector<std::string>> properties = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> required = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_4 = method->params;
    for (const auto& parameter : *_iterable_4) {
        const auto schema = emitTypeSchemaWithDescription(doof::unwrap_optional(parameter->resolvedType), parameter->description, context);
        properties->push_back(jsonEntry(parameter->name, schema));
        if (doof::is_null(parameter->defaultValue)) {
            required->push_back(jsonString(parameter->name));
        }
    }
    std::shared_ptr<std::vector<std::string>> entries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("object"))), jsonEntry(std::string("properties"), jsonObject(properties))});
    if (static_cast<int32_t>((required)->size()) > 0) {
        entries->push_back(jsonEntry(std::string("required"), jsonArray(required)));
    }
    return jsonObject(entries);
}
std::string emitTypeSchemaWithDescription(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::string description, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto schema = emitTypeSchemaEntries(type_, context);
    if (description != std::string("")) {
        schema->push_back(jsonEntry(std::string("description"), jsonString(description)));
    }
    return jsonObject(schema);
}
std::string emitTypeSchema(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return jsonObject(emitTypeSchemaEntries(type_, context));
}
std::shared_ptr<std::vector<std::string>> emitTypeSchemaEntries(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            if (primitive->name == std::string("byte")) {
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("integer"))), jsonEntry(std::string("minimum"), jsonInt(0)), jsonEntry(std::string("maximum"), jsonInt(255))});
            }
            if (primitive->name == std::string("int")) {
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("integer"))), jsonEntry(std::string("format"), jsonString(std::string("int32")))});
            }
            if (primitive->name == std::string("long")) {
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("integer"))), jsonEntry(std::string("format"), jsonString(std::string("int64")))});
            }
            if ((primitive->name == std::string("float")) || (primitive->name == std::string("double"))) {
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("number")))});
            }
            if ((primitive->name == std::string("string")) || (primitive->name == std::string("char"))) {
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("string")))});
            }
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("boolean")))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("null")))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("$ref"), jsonString((std::string("#/$defs/") + class_->name)))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("array"))), jsonEntry(std::string("items"), emitTypeSchema(array->elementType, context))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            std::shared_ptr<std::vector<std::string>> items = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
            const auto& _iterable_5 = tuple->elements;
            for (const auto& element : *_iterable_5) {
                items->push_back(emitTypeSchema(element, context));
            }
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("array"))), jsonEntry(std::string("prefixItems"), jsonArray(items)), jsonEntry(std::string("minItems"), jsonInt(static_cast<int32_t>((tuple->elements)->size()))), jsonEntry(std::string("maxItems"), jsonInt(static_cast<int32_t>((tuple->elements)->size())))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            std::shared_ptr<std::vector<std::string>> values = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
            const auto declaration = findEnum(context, enum_->symbol->module, enum_->name);
            if (!doof::is_null(declaration)) {
                const auto& _iterable_6 = declaration->variants;
                for (const auto& variant : *_iterable_6) {
                    values->push_back(jsonString(variant->name));
                }
            }
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("enum"), jsonArray(values))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            std::shared_ptr<std::vector<std::string>> members = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
            const auto& _iterable_7 = union_->types;
            for (const auto& member : *_iterable_7) {
                members->push_back(emitTypeSchema(member, context));
            }
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("anyOf"), jsonArray(members))});
    }
    else {
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    }
    return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
}
std::string emitDefinitions(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> methods, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>> classes = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>{});
    const auto& _iterable_8 = methods;
    for (const auto& method : *_iterable_8) {
        const auto& _iterable_9 = method->params;
        for (const auto& parameter : *_iterable_9) {
            collectSchemaClasses(doof::unwrap_optional(parameter->resolvedType), context, classes);
        }
        collectSchemaClasses(methodSuccessType(method), context, classes);
    }
    if (static_cast<int32_t>((classes)->size()) == 0) {
        return std::string("");
    }
    std::shared_ptr<std::vector<std::string>> entries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_10 = classes;
    for (const auto& class_ : *_iterable_10) {
        entries->push_back(jsonEntry(class_->name, emitClassSchema(class_, context)));
    }
    return jsonObject(entries);
}
void collectSchemaClasses(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>> classes) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& classType = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto declaration = findClass(context, classType->symbol->module, classType->name);
            if (doof::is_null(declaration) || containsClass(classes, doof::unwrap_optional(declaration))) {
                return;
            }
            classes->push_back(doof::unwrap_optional(declaration));
            const auto& _iterable_11 = declaration->fields;
            for (const auto& field : *_iterable_11) {
                if (!field->static_) {
                    collectSchemaClasses(doof::unwrap_optional(field->resolvedType), context, classes);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            collectSchemaClasses(array->elementType, context, classes);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_12 = tuple->elements;
            for (const auto& element : *_iterable_12) {
                collectSchemaClasses(element, context, classes);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_13 = union_->types;
            for (const auto& member : *_iterable_13) {
                collectSchemaClasses(member, context, classes);
            }
    }
    else {
    }
    }
}
std::string emitClassSchema(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    std::shared_ptr<std::vector<std::string>> properties = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> required = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_14 = owner->fields;
    for (const auto& field : *_iterable_14) {
        if (field->static_ || field->private_) {
            continue;
        }
        for (int32_t index = 0; index < static_cast<int32_t>((field->names)->size()); ++index) {
            const auto description = ((index < static_cast<int32_t>((field->descriptions)->size())) ? (*field->descriptions)[index] : std::string(""));
            properties->push_back(jsonEntry((*field->names)[index], emitTypeSchemaWithDescription(doof::unwrap_optional(field->resolvedType), description, context)));
            if (doof::is_null(field->defaultValue)) {
                required->push_back(jsonString((*field->names)[index]));
            }
        }
    }
    std::shared_ptr<std::vector<std::string>> entries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("object"))), jsonEntry(std::string("properties"), jsonObject(properties))});
    if (static_cast<int32_t>((required)->size()) > 0) {
        entries->push_back(jsonEntry(std::string("required"), jsonArray(required)));
    }
    if (owner->description != std::string("")) {
        entries->push_back(jsonEntry(std::string("description"), jsonString(owner->description)));
    }
    return jsonObject(entries);
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> findClass(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string modulePath, std::string name) {
    const auto& _iterable_15 = context->allPrograms;
    for (const auto& program : *_iterable_15) {
        const auto& _iterable_16 = program->statements;
        for (const auto& statement : *_iterable_16) {
            const auto declaration = statementClass(statement);
            if ((((!doof::is_null(declaration)) && (declaration->name == name)) && (!doof::is_null(declaration->resolvedSymbol))) && (declaration->resolvedSymbol->module == modulePath)) {
                return declaration;
            }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::EnumDeclaration> findEnum(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string modulePath, std::string name) {
    const auto& _iterable_17 = context->allPrograms;
    for (const auto& program : *_iterable_17) {
        const auto& _iterable_18 = program->statements;
        for (const auto& statement : *_iterable_18) {
            {
                auto _case_subject = statement;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                    const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
                    if (enum_->name == name) {
                        return enum_;
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                    const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
                    {
                        auto _case_subject = export_->declaration;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
                            if (enum_->name == name) {
                                return enum_;
                            }
                    }
                    else {
                    }
                    }
            }
            else {
            }
            }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> statementClass(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return statementClass(export_->declaration);
    }
    else {
            return nullptr;
    }
    }
    return nullptr;
}
bool containsClass(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>> classes, std::shared_ptr<::app_src_ast_::ClassDeclaration> candidate) {
    const auto& _iterable_19 = classes;
    for (const auto& class_ : *_iterable_19) {
        if ((class_->resolvedSymbol->module == candidate->resolvedSymbol->module) && (class_->name == candidate->name)) {
            return true;
        }
    }
    return false;
}
std::string jsonEntry(std::string key, std::string value) {
    return ((((std::string("{\"") + escapeCpp(key)) + std::string("\", ")) + value) + std::string("}"));
}
std::string jsonString(std::string value) {
    return ((std::string("doof::json_value(\"") + escapeCpp(value)) + std::string("\")"));
}
std::string jsonInt(int32_t value) {
    return ((std::string("doof::json_value(static_cast<int32_t>(") + doof::to_string(value)) + std::string("))"));
}
std::string jsonArray(std::shared_ptr<std::vector<std::string>> values) {
    return ((std::string("doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{") + joinStrings(values)) + std::string("}))"));
}
std::string jsonObject(std::shared_ptr<std::vector<std::string>> entries) {
    return ((std::string("doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(doof::ordered_map<std::string, doof::JsonValue>{") + joinStrings(entries)) + std::string("}))"));
}
std::string joinStrings(std::shared_ptr<std::vector<std::string>> values) {
    auto result = std::string("");
    const auto& _iterable_20 = values;
    for (const auto& value : *_iterable_20) {
        if (result != std::string("")) {
            (result = (result + std::string(", ")));
        }
        (result = (result + value));
    }
    return result;
}
std::string escapeCpp(std::string value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\n"), std::string("\\n"));
}
}
