#include "src_emitter_metadata.hpp"

namespace app_src_emitter_metadata_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_json_;
#line 14 "/src/emitter-metadata.do"
std::string emitMetadataDeclaration(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner) {
#line 15 "/src/emitter-metadata.do"
    if (!owner->needsMetadata) {
#line 15 "/src/emitter-metadata.do"
        return std::string("");
    }
#line 16 "/src/emitter-metadata.do"
    return ((std::string("    static const doof::ClassMetadata<") + owner->name) + std::string("> _metadata;\n"));
}
#line 20 "/src/emitter-metadata.do"
std::string emitMetadataDefinition(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 21 "/src/emitter-metadata.do"
    if (!owner->needsMetadata) {
#line 21 "/src/emitter-metadata.do"
        return std::string("");
    }
#line 22 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>{});
#line 23 "/src/emitter-metadata.do"
    const auto& _iterable_2 = owner->methods;
    for (const auto& method : *_iterable_2) {
#line 23 "/src/emitter-metadata.do"
        if (!method->private_ && !method->static_) {
#line 23 "/src/emitter-metadata.do"
            methods->push_back(method);
        }
    }
#line 25 "/src/emitter-metadata.do"
    auto result = ((((std::string("inline const doof::ClassMetadata<") + owner->name) + std::string("> ")) + owner->name) + std::string("::_metadata = {\n"));
#line 26 "/src/emitter-metadata.do"
    (result = (((result + std::string("    \"")) + escapeCpp(owner->name)) + std::string("\",\n")));
#line 27 "/src/emitter-metadata.do"
    (result = (((result + std::string("    \"")) + escapeCpp(owner->description)) + std::string("\",\n")));
#line 28 "/src/emitter-metadata.do"
    (result = (((((result + std::string("    std::make_shared<std::vector<doof::MethodReflection<")) + owner->name) + std::string(">>>(std::vector<doof::MethodReflection<")) + owner->name) + std::string(">>{\n")));
#line 29 "/src/emitter-metadata.do"
    for (int32_t index = 0; index < static_cast<int32_t>((methods)->size()); ++index) {
#line 30 "/src/emitter-metadata.do"
        const auto method = doof::array_at(methods, index, "src/emitter-metadata", 30);
#line 31 "/src/emitter-metadata.do"
        (result = (result + emitMethodReflection(owner, method, context)));
#line 32 "/src/emitter-metadata.do"
        if ((index + 1) < static_cast<int32_t>((methods)->size())) {
#line 32 "/src/emitter-metadata.do"
            (result = (result + std::string(",")));
        }
#line 33 "/src/emitter-metadata.do"
        (result = (result + std::string("\n")));
    }
#line 35 "/src/emitter-metadata.do"
    (result = (result + std::string("    }),\n")));
#line 36 "/src/emitter-metadata.do"
    const auto defs = emitDefinitions(methods, context);
#line 37 "/src/emitter-metadata.do"
    (result = (((result + std::string("    ")) + ((defs == std::string("")) ? std::string("std::nullopt") : ((std::string("std::optional<doof::JsonValue>{") + defs) + std::string("}")))) + std::string("\n")));
#line 38 "/src/emitter-metadata.do"
    return (result + std::string("};\n"));
}
#line 41 "/src/emitter-metadata.do"
std::string emitMethodReflection(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 42 "/src/emitter-metadata.do"
    const auto inputSchema = emitMethodInputSchema(method, context);
#line 43 "/src/emitter-metadata.do"
    const auto outputSchema = emitTypeSchema(methodSuccessType(method), context);
#line 44 "/src/emitter-metadata.do"
    auto result = ((std::string("        doof::MethodReflection<") + owner->name) + std::string(">{\n"));
#line 45 "/src/emitter-metadata.do"
    (result = (((result + std::string("            \"")) + escapeCpp(method->name)) + std::string("\",\n")));
#line 46 "/src/emitter-metadata.do"
    (result = (((result + std::string("            \"")) + escapeCpp(method->description)) + std::string("\",\n")));
#line 47 "/src/emitter-metadata.do"
    (result = (((result + std::string("            ")) + inputSchema) + std::string(",\n")));
#line 48 "/src/emitter-metadata.do"
    (result = (((result + std::string("            ")) + outputSchema) + std::string(",\n")));
#line 49 "/src/emitter-metadata.do"
    (result = (((result + std::string("            []( ")) + owner->name) + std::string("& _instance, const doof::JsonValue& _params) -> doof::Result<doof::JsonValue, doof::JsonValue> {\n")));
#line 50 "/src/emitter-metadata.do"
    (result = (result + std::string("                const bool _lenient = false;\n")));
#line 51 "/src/emitter-metadata.do"
    (result = (result + std::string("                const auto* _p = doof::json_as_object(_params);\n")));
#line 52 "/src/emitter-metadata.do"
    (result = (((result + std::string("                if (_p == nullptr) { return ")) + metadataFailure(400, std::string("std::string(\"Invalid JSON params: expected object\")"))) + std::string("; }\n")));
#line 53 "/src/emitter-metadata.do"
    const auto& _iterable_5 = method->params;
    for (const auto& parameter : *_iterable_5) {
#line 54 "/src/emitter-metadata.do"
        const auto type_ = doof::unwrap_optional(parameter->resolvedType);
#line 55 "/src/emitter-metadata.do"
        const auto safeName = ::app_src_emitter_expr_::cppIdentifier(parameter->name);
#line 56 "/src/emitter-metadata.do"
        const auto iterator = (std::string("_it_") + safeName);
#line 57 "/src/emitter-metadata.do"
        if (!doof::is_null(parameter->defaultValue)) {
#line 58 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                ")) + ::app_src_emitter_types_::emitContextType(type_, context)) + std::string(" ")) + safeName) + std::string(";\n")));
#line 59 "/src/emitter-metadata.do"
            (result = (((((((result + std::string("                if (auto ")) + iterator) + std::string(" = _p->find(\"")) + escapeCpp(parameter->name)) + std::string("\"); ")) + iterator) + std::string(" != _p->end()) {\n")));
#line 60 "/src/emitter-metadata.do"
            (result = (result + emitParameterValidation(parameter->name, (iterator + std::string("->second")), type_, std::string("                    "))));
#line 61 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                    ")) + safeName) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n")));
#line 62 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                } else { ")) + safeName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, doof::optional_value(type_))) + std::string("; }\n")));
        } else {
#line 64 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                auto ")) + iterator) + std::string(" = _p->find(\"")) + escapeCpp(parameter->name)) + std::string("\");\n")));
#line 65 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                if (")) + iterator) + std::string(" == _p->end()) { return ")) + metadataFailure(400, ((std::string("std::string(\"Missing required parameter \\\"") + escapeCpp(parameter->name)) + std::string("\\\"\")")))) + std::string("; }\n")));
#line 66 "/src/emitter-metadata.do"
            (result = (result + emitParameterValidation(parameter->name, (iterator + std::string("->second")), type_, std::string("                "))));
#line 67 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                auto ")) + safeName) + std::string(" = ")) + ::app_src_emitter_json_::emitJsonRead((iterator + std::string("->second")), type_, context)) + std::string(";\n")));
        }
    }
#line 70 "/src/emitter-metadata.do"
    auto arguments = std::string("");
#line 71 "/src/emitter-metadata.do"
    const auto& _iterable_7 = method->params;
    for (const auto& parameter : *_iterable_7) {
#line 72 "/src/emitter-metadata.do"
        if (arguments != std::string("")) {
#line 72 "/src/emitter-metadata.do"
            (arguments = (arguments + std::string(", ")));
        }
#line 73 "/src/emitter-metadata.do"
        (arguments = (arguments + ::app_src_emitter_expr_::cppIdentifier(parameter->name)));
    }
#line 75 "/src/emitter-metadata.do"
    const auto returnType = methodReturnType(method);
#line 76 "/src/emitter-metadata.do"
    {
        auto _case_subject = returnType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 78 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                _instance.")) + ::app_src_emitter_expr_::cppIdentifier(method->name)) + std::string("(")) + arguments) + std::string(");\n")));
#line 79 "/src/emitter-metadata.do"
            (result = (((result + std::string("                return ")) + metadataSuccess(std::string("doof::json_value(nullptr)"))) + std::string(";\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& resultType = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 82 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                auto _result = _instance.")) + ::app_src_emitter_expr_::cppIdentifier(method->name)) + std::string("(")) + arguments) + std::string(");\n")));
#line 83 "/src/emitter-metadata.do"
            (result = (result + std::string("                if (doof::is_failure(_result)) {\n")));
#line 84 "/src/emitter-metadata.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, resultType->errorType) == std::string("json-value")) {
#line 85 "/src/emitter-metadata.do"
                (result = (result + std::string("                    return doof::Failure<doof::JsonValue>{doof::failure_error(_result)};\n")));
            } else {
#line 87 "/src/emitter-metadata.do"
                (result = (((result + std::string("                    return ")) + metadataFailure(500, std::string("\"An error occurred\""))) + std::string(";\n")));
            }
#line 89 "/src/emitter-metadata.do"
            (result = (result + std::string("                }\n")));
#line 90 "/src/emitter-metadata.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, resultType->valueType) == std::string("none")) {
#line 91 "/src/emitter-metadata.do"
                (result = (((result + std::string("                return ")) + metadataSuccess(std::string("doof::json_value(nullptr)"))) + std::string(";\n")));
            } else {
#line 93 "/src/emitter-metadata.do"
                (result = (result + std::string("                auto _success = doof::success_value(_result);\n")));
#line 94 "/src/emitter-metadata.do"
                (result = (((result + std::string("                return ")) + metadataSuccess(::app_src_emitter_json_::emitJsonField(std::string("_success"), resultType->valueType, context))) + std::string(";\n")));
            }
    }
    else {
#line 98 "/src/emitter-metadata.do"
            (result = (((((result + std::string("                auto _result = _instance.")) + ::app_src_emitter_expr_::cppIdentifier(method->name)) + std::string("(")) + arguments) + std::string(");\n")));
#line 99 "/src/emitter-metadata.do"
            (result = (((result + std::string("                return ")) + metadataSuccess(::app_src_emitter_json_::emitJsonField(std::string("_result"), returnType, context))) + std::string(";\n")));
    }
    }
#line 102 "/src/emitter-metadata.do"
    return (result + std::string("            }\n        }"));
}
#line 105 "/src/emitter-metadata.do"
std::string emitParameterValidation(const std::string& name, const std::string& value, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& indent) {
#line 106 "/src/emitter-metadata.do"
    return (((((indent + std::string("if (!(")) + ::app_src_emitter_json_::emitJsonTypeCheck(value, type_)) + std::string(")) { return ")) + metadataFailure(400, ((((((std::string("std::string(\"Parameter \\\"") + escapeCpp(name)) + std::string("\\\" expected ")) + ::app_src_emitter_json_::jsonTypeName(type_)) + std::string(" but got \") + doof::json_type_name(")) + value) + std::string(")")))) + std::string("; }\n"));
}
#line 109 "/src/emitter-metadata.do"
std::string metadataFailure(int32_t code, const std::string& message) {
#line 110 "/src/emitter-metadata.do"
    return ((((std::string("doof::Failure<doof::JsonValue>{doof::json_error(") + doof::to_string(code)) + std::string(", ")) + message) + std::string(")}"));
}
#line 113 "/src/emitter-metadata.do"
std::string metadataSuccess(const std::string& value) {
#line 114 "/src/emitter-metadata.do"
    return ((std::string("doof::Success<doof::JsonValue>{") + value) + std::string("}"));
}
#line 117 "/src/emitter-metadata.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> methodReturnType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method) {
#line 118 "/src/emitter-metadata.do"
    {
        auto _case_subject = doof::unwrap_optional(method->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 119 "/src/emitter-metadata.do"
            return function_->returnType;
    }
    else {
#line 120 "/src/emitter-metadata.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none")));
    }
    }
    doof::unreachable();
#line 122 "/src/emitter-metadata.do"
    return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none")));
}
#line 125 "/src/emitter-metadata.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> methodSuccessType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method) {
#line 126 "/src/emitter-metadata.do"
    const auto result = methodReturnType(method);
#line 127 "/src/emitter-metadata.do"
    {
        auto _case_subject = result;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 128 "/src/emitter-metadata.do"
            return result_->valueType;
    }
    else {
#line 129 "/src/emitter-metadata.do"
            return result;
    }
    }
    doof::unreachable();
#line 131 "/src/emitter-metadata.do"
    return result;
}
#line 134 "/src/emitter-metadata.do"
std::string emitMethodInputSchema(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 135 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::string>> properties = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 136 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::string>> required = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 137 "/src/emitter-metadata.do"
    const auto& _iterable_9 = method->params;
    for (const auto& parameter : *_iterable_9) {
#line 138 "/src/emitter-metadata.do"
        const auto schema = emitTypeSchemaWithDescription(doof::unwrap_optional(parameter->resolvedType), parameter->description, context);
#line 139 "/src/emitter-metadata.do"
        properties->push_back(jsonEntry(parameter->name, schema));
#line 140 "/src/emitter-metadata.do"
        if (doof::is_null(parameter->defaultValue)) {
#line 140 "/src/emitter-metadata.do"
            required->push_back(jsonString(parameter->name));
        }
    }
#line 142 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::string>> entries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("object"))), jsonEntry(std::string("properties"), jsonObject(properties))});
#line 143 "/src/emitter-metadata.do"
    if (static_cast<int32_t>((required)->size()) > 0) {
#line 143 "/src/emitter-metadata.do"
        entries->push_back(jsonEntry(std::string("required"), jsonArray(required)));
    }
#line 144 "/src/emitter-metadata.do"
    return jsonObject(entries);
}
#line 147 "/src/emitter-metadata.do"
std::string emitTypeSchemaWithDescription(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& description, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 148 "/src/emitter-metadata.do"
    const auto schema = emitTypeSchemaEntries(type_, context);
#line 149 "/src/emitter-metadata.do"
    if (description != std::string("")) {
#line 149 "/src/emitter-metadata.do"
        schema->push_back(jsonEntry(std::string("description"), jsonString(description)));
    }
#line 150 "/src/emitter-metadata.do"
    return jsonObject(schema);
}
#line 153 "/src/emitter-metadata.do"
std::string emitTypeSchema(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 153 "/src/emitter-metadata.do"
    return jsonObject(emitTypeSchemaEntries(type_, context));
}
#line 155 "/src/emitter-metadata.do"
std::shared_ptr<std::vector<std::string>> emitTypeSchemaEntries(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 156 "/src/emitter-metadata.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 158 "/src/emitter-metadata.do"
            if (primitive->name == std::string("byte")) {
#line 158 "/src/emitter-metadata.do"
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("integer"))), jsonEntry(std::string("minimum"), jsonInt(0)), jsonEntry(std::string("maximum"), jsonInt(255))});
            }
#line 159 "/src/emitter-metadata.do"
            if (primitive->name == std::string("int")) {
#line 159 "/src/emitter-metadata.do"
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("integer"))), jsonEntry(std::string("format"), jsonString(std::string("int32")))});
            }
#line 160 "/src/emitter-metadata.do"
            if (primitive->name == std::string("long")) {
#line 160 "/src/emitter-metadata.do"
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("integer"))), jsonEntry(std::string("format"), jsonString(std::string("int64")))});
            }
#line 161 "/src/emitter-metadata.do"
            if ((primitive->name == std::string("float")) || (primitive->name == std::string("double"))) {
#line 161 "/src/emitter-metadata.do"
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("number")))});
            }
#line 162 "/src/emitter-metadata.do"
            if ((primitive->name == std::string("string")) || (primitive->name == std::string("char"))) {
#line 162 "/src/emitter-metadata.do"
                return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("string")))});
            }
#line 163 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("boolean")))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 165 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 166 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("null")))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 167 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("$ref"), jsonString((std::string("#/$defs/") + class_->name)))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 168 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("array"))), jsonEntry(std::string("items"), emitTypeSchema(array->elementType, context))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 170 "/src/emitter-metadata.do"
            std::shared_ptr<std::vector<std::string>> items = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 171 "/src/emitter-metadata.do"
            const auto& _iterable_11 = tuple->elements;
            for (const auto& element : *_iterable_11) {
#line 171 "/src/emitter-metadata.do"
                items->push_back(emitTypeSchema(element, context));
            }
#line 172 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("array"))), jsonEntry(std::string("prefixItems"), jsonArray(items)), jsonEntry(std::string("minItems"), jsonInt(static_cast<int32_t>((tuple->elements)->size()))), jsonEntry(std::string("maxItems"), jsonInt(static_cast<int32_t>((tuple->elements)->size())))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 175 "/src/emitter-metadata.do"
            std::shared_ptr<std::vector<std::string>> values = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 176 "/src/emitter-metadata.do"
            const auto declaration = findEnum(context, enum_->symbol->module, enum_->name);
#line 177 "/src/emitter-metadata.do"
            if (!doof::is_null(declaration)) {
#line 177 "/src/emitter-metadata.do"
                const auto& _iterable_13 = declaration->variants;
                for (const auto& variant : *_iterable_13) {
#line 177 "/src/emitter-metadata.do"
                    values->push_back(jsonString(variant->name));
                }
            }
#line 178 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("enum"), jsonArray(values))});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 181 "/src/emitter-metadata.do"
            std::shared_ptr<std::vector<std::string>> members = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 182 "/src/emitter-metadata.do"
            const auto& _iterable_15 = union_->types;
            for (const auto& member : *_iterable_15) {
#line 182 "/src/emitter-metadata.do"
                members->push_back(emitTypeSchema(member, context));
            }
#line 183 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("anyOf"), jsonArray(members))});
    }
    else {
#line 185 "/src/emitter-metadata.do"
            return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    }
    doof::unreachable();
#line 187 "/src/emitter-metadata.do"
    return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
}
#line 190 "/src/emitter-metadata.do"
std::string emitDefinitions(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>& methods, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 191 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>> classes = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>{});
#line 192 "/src/emitter-metadata.do"
    const auto& _iterable_17 = methods;
    for (const auto& method : *_iterable_17) {
#line 193 "/src/emitter-metadata.do"
        const auto& _iterable_19 = method->params;
        for (const auto& parameter : *_iterable_19) {
#line 193 "/src/emitter-metadata.do"
            collectSchemaClasses(doof::unwrap_optional(parameter->resolvedType), context, classes);
        }
#line 194 "/src/emitter-metadata.do"
        collectSchemaClasses(methodSuccessType(method), context, classes);
    }
#line 196 "/src/emitter-metadata.do"
    if (static_cast<int32_t>((classes)->size()) == 0) {
#line 196 "/src/emitter-metadata.do"
        return std::string("");
    }
#line 197 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::string>> entries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 198 "/src/emitter-metadata.do"
    const auto& _iterable_21 = classes;
    for (const auto& class_ : *_iterable_21) {
#line 198 "/src/emitter-metadata.do"
        entries->push_back(jsonEntry(class_->name, emitClassSchema(class_, context)));
    }
#line 199 "/src/emitter-metadata.do"
    return jsonObject(entries);
}
#line 202 "/src/emitter-metadata.do"
void collectSchemaClasses(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>>& classes) {
#line 203 "/src/emitter-metadata.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& classType = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 205 "/src/emitter-metadata.do"
            const auto declaration = findClass(context, classType->symbol->module, classType->name);
#line 206 "/src/emitter-metadata.do"
            if (doof::is_null(declaration) || containsClass(classes, doof::unwrap_optional(declaration))) {
#line 206 "/src/emitter-metadata.do"
                return;
            }
#line 207 "/src/emitter-metadata.do"
            classes->push_back(doof::unwrap_optional(declaration));
#line 208 "/src/emitter-metadata.do"
            const auto& _iterable_23 = declaration->fields;
            for (const auto& field : *_iterable_23) {
#line 208 "/src/emitter-metadata.do"
                if (!field->static_) {
#line 208 "/src/emitter-metadata.do"
                    collectSchemaClasses(doof::unwrap_optional(field->resolvedType), context, classes);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 210 "/src/emitter-metadata.do"
            collectSchemaClasses(array->elementType, context, classes);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 211 "/src/emitter-metadata.do"
            const auto& _iterable_25 = tuple->elements;
            for (const auto& element : *_iterable_25) {
#line 211 "/src/emitter-metadata.do"
                collectSchemaClasses(element, context, classes);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 212 "/src/emitter-metadata.do"
            const auto& _iterable_27 = union_->types;
            for (const auto& member : *_iterable_27) {
#line 212 "/src/emitter-metadata.do"
                collectSchemaClasses(member, context, classes);
            }
    }
    else {
    }
    }
}
#line 217 "/src/emitter-metadata.do"
std::string emitClassSchema(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 218 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::string>> properties = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 219 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::string>> required = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 220 "/src/emitter-metadata.do"
    const auto& _iterable_29 = owner->fields;
    for (const auto& field : *_iterable_29) {
#line 221 "/src/emitter-metadata.do"
        if (field->static_ || field->private_) {
#line 221 "/src/emitter-metadata.do"
            continue;
        }
#line 222 "/src/emitter-metadata.do"
        for (int32_t index = 0; index < static_cast<int32_t>((field->names)->size()); ++index) {
#line 223 "/src/emitter-metadata.do"
            const auto description = ((index < static_cast<int32_t>((field->descriptions)->size())) ? doof::array_at(field->descriptions, index, "src/emitter-metadata", 223) : std::string(""));
#line 224 "/src/emitter-metadata.do"
            properties->push_back(jsonEntry(doof::array_at(field->names, index, "src/emitter-metadata", 224), emitTypeSchemaWithDescription(doof::unwrap_optional(field->resolvedType), description, context)));
#line 225 "/src/emitter-metadata.do"
            if (doof::is_null(field->defaultValue)) {
#line 225 "/src/emitter-metadata.do"
                required->push_back(jsonString(doof::array_at(field->names, index, "src/emitter-metadata", 225)));
            }
        }
    }
#line 228 "/src/emitter-metadata.do"
    std::shared_ptr<std::vector<std::string>> entries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{jsonEntry(std::string("type"), jsonString(std::string("object"))), jsonEntry(std::string("properties"), jsonObject(properties))});
#line 229 "/src/emitter-metadata.do"
    if (static_cast<int32_t>((required)->size()) > 0) {
#line 229 "/src/emitter-metadata.do"
        entries->push_back(jsonEntry(std::string("required"), jsonArray(required)));
    }
#line 230 "/src/emitter-metadata.do"
    if (owner->description != std::string("")) {
#line 230 "/src/emitter-metadata.do"
        entries->push_back(jsonEntry(std::string("description"), jsonString(owner->description)));
    }
#line 231 "/src/emitter-metadata.do"
    return jsonObject(entries);
}
#line 234 "/src/emitter-metadata.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> findClass(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& modulePath, const std::string& name) {
#line 235 "/src/emitter-metadata.do"
    const auto& _iterable_32 = context->allPrograms;
    for (const auto& program : *_iterable_32) {
#line 235 "/src/emitter-metadata.do"
        const auto& _iterable_34 = program->statements;
        for (const auto& statement : *_iterable_34) {
#line 236 "/src/emitter-metadata.do"
            const auto declaration = statementClass(statement);
#line 237 "/src/emitter-metadata.do"
            if ((((!doof::is_null(declaration)) && (declaration->name == name)) && (!doof::is_null(declaration->resolvedSymbol))) && (declaration->resolvedSymbol->module == modulePath)) {
#line 237 "/src/emitter-metadata.do"
                return declaration;
            }
        }
    }
#line 239 "/src/emitter-metadata.do"
    return nullptr;
}
#line 242 "/src/emitter-metadata.do"
std::shared_ptr<::app_src_ast_::EnumDeclaration> findEnum(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& modulePath, const std::string& name) {
#line 243 "/src/emitter-metadata.do"
    const auto& _iterable_36 = context->allPrograms;
    for (const auto& program : *_iterable_36) {
#line 243 "/src/emitter-metadata.do"
        const auto& _iterable_38 = program->statements;
        for (const auto& statement : *_iterable_38) {
#line 244 "/src/emitter-metadata.do"
            {
                auto _case_subject = statement;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                    const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 245 "/src/emitter-metadata.do"
                    if (enum_->name == name) {
#line 245 "/src/emitter-metadata.do"
                        return enum_;
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                    const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 247 "/src/emitter-metadata.do"
                    {
                        auto _case_subject = export_->declaration;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 248 "/src/emitter-metadata.do"
                            if (enum_->name == name) {
#line 248 "/src/emitter-metadata.do"
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
#line 255 "/src/emitter-metadata.do"
    return nullptr;
}
#line 258 "/src/emitter-metadata.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> statementClass(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 259 "/src/emitter-metadata.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 260 "/src/emitter-metadata.do"
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 261 "/src/emitter-metadata.do"
            return statementClass(export_->declaration);
    }
    else {
#line 262 "/src/emitter-metadata.do"
            return nullptr;
    }
    }
    doof::unreachable();
#line 264 "/src/emitter-metadata.do"
    return nullptr;
}
#line 267 "/src/emitter-metadata.do"
bool containsClass(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>>& classes, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& candidate) {
#line 268 "/src/emitter-metadata.do"
    const auto& _iterable_40 = classes;
    for (const auto& class_ : *_iterable_40) {
#line 268 "/src/emitter-metadata.do"
        if ((class_->resolvedSymbol->module == candidate->resolvedSymbol->module) && (class_->name == candidate->name)) {
#line 268 "/src/emitter-metadata.do"
            return true;
        }
    }
#line 269 "/src/emitter-metadata.do"
    return false;
}
#line 272 "/src/emitter-metadata.do"
std::string jsonEntry(const std::string& key, const std::string& value) {
#line 272 "/src/emitter-metadata.do"
    return ((((std::string("{\"") + escapeCpp(key)) + std::string("\", ")) + value) + std::string("}"));
}
#line 273 "/src/emitter-metadata.do"
std::string jsonString(const std::string& value) {
#line 273 "/src/emitter-metadata.do"
    return ((std::string("doof::json_value(\"") + escapeCpp(value)) + std::string("\")"));
}
#line 274 "/src/emitter-metadata.do"
std::string jsonInt(int32_t value) {
#line 274 "/src/emitter-metadata.do"
    return ((std::string("doof::json_value(static_cast<int32_t>(") + doof::to_string(value)) + std::string("))"));
}
#line 275 "/src/emitter-metadata.do"
std::string jsonArray(const std::shared_ptr<std::vector<std::string>>& values) {
#line 275 "/src/emitter-metadata.do"
    return ((std::string("doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{") + joinStrings(values)) + std::string("}))"));
}
#line 276 "/src/emitter-metadata.do"
std::string jsonObject(const std::shared_ptr<std::vector<std::string>>& entries) {
#line 276 "/src/emitter-metadata.do"
    return ((std::string("doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(doof::ordered_map<std::string, doof::JsonValue>{") + joinStrings(entries)) + std::string("}))"));
}
#line 278 "/src/emitter-metadata.do"
std::string joinStrings(const std::shared_ptr<std::vector<std::string>>& values) {
#line 279 "/src/emitter-metadata.do"
    auto result = std::string("");
#line 280 "/src/emitter-metadata.do"
    const auto& _iterable_42 = values;
    for (const auto& value : *_iterable_42) {
#line 281 "/src/emitter-metadata.do"
        if (result != std::string("")) {
#line 281 "/src/emitter-metadata.do"
            (result = (result + std::string(", ")));
        }
#line 282 "/src/emitter-metadata.do"
        (result = (result + value));
    }
#line 284 "/src/emitter-metadata.do"
    return result;
}
#line 287 "/src/emitter-metadata.do"
std::string escapeCpp(const std::string& value) {
#line 288 "/src/emitter-metadata.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\?"), std::string("\\\?")), std::string("\n"), std::string("\\n"));
}
#line 1 "<doof-generated>"
}
