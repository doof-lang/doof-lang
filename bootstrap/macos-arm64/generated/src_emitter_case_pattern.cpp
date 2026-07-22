#include "src_emitter_case_pattern.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_case_pattern_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_types_;

doof::JsonObject CaseTypePatternEmission::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["condition"] = doof::json_value(this->condition);
    (*_json)["binding"] = doof::json_value(this->binding);
    return _json;
}
doof::Result<std::shared_ptr<CaseTypePatternEmission>, std::string> CaseTypePatternEmission::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_condition = _object->find("condition");
    if (_iterator_condition == _object->end()) { return doof::Failure<std::string>{"Missing required field \"condition\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_condition->second) : doof::json_is_string(_iterator_condition->second)))) { return doof::Failure<std::string>{"Field \"condition\" expected string but got " + std::string(doof::json_type_name(_iterator_condition->second))}; }
    auto _field_condition = (_lenient ? doof::json_as_string_lenient(_iterator_condition->second) : doof::json_as_string(_iterator_condition->second));
    auto _iterator_binding = _object->find("binding");
    if (_iterator_binding == _object->end()) { return doof::Failure<std::string>{"Missing required field \"binding\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_binding->second) : doof::json_is_string(_iterator_binding->second)))) { return doof::Failure<std::string>{"Field \"binding\" expected string but got " + std::string(doof::json_type_name(_iterator_binding->second))}; }
    auto _field_binding = (_lenient ? doof::json_as_string_lenient(_iterator_binding->second) : doof::json_as_string(_iterator_binding->second));
    return doof::Success<std::shared_ptr<CaseTypePatternEmission>>{std::make_shared<CaseTypePatternEmission>(_field_condition, _field_binding)};
}
std::shared_ptr<CaseTypePatternEmission> emitCaseTypePattern(std::shared_ptr<::app_src_ast_::TypePattern> pattern, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> subjectType, std::string subject, std::string bindingName, std::string currentModulePath) {
    if (doof::is_null(pattern->resolvedType)) {
        doof::panic(std::string("Case pattern has no resolved type"));
    }
    const auto patternType = doof::unwrap_optional(pattern->resolvedType);
    {
        auto _case_subject = subjectType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return emitResultPattern(pattern, result, subject, bindingName, currentModulePath);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return emitJsonValuePattern(patternType, subject, bindingName);
    }
    else {
    }
    }
    if (::app_src_emitter_types_::usesVariantRepresentation(subjectType)) {
        const auto patternCpp = ::app_src_emitter_types_::emitType(patternType, currentModulePath);
        if (::app_src_emitter_types_::usesVariantRepresentation(patternType)) {
            return std::make_shared<CaseTypePatternEmission>(((((std::string("doof::variant_is<") + patternCpp) + std::string(">(")) + subject) + std::string(")")), ((bindingName == std::string("")) ? std::string("") : ((((((std::string("const auto ") + bindingName) + std::string(" = doof::variant_narrow<")) + patternCpp) + std::string(">(")) + subject) + std::string(");\n"))));
        }
        return std::make_shared<CaseTypePatternEmission>(((((std::string("std::holds_alternative<") + patternCpp) + std::string(">(")) + subject) + std::string(")")), ((bindingName == std::string("")) ? std::string("") : ((((((std::string("const auto& ") + bindingName) + std::string(" = std::get<")) + patternCpp) + std::string(">(")) + subject) + std::string(");\n"))));
    }
    const auto nullable = ::app_src_emitter_types_::usesNullableSingleValueRepresentation(subjectType);
    const auto value = (nullable ? ((std::string("doof::unwrap_optional(") + subject) + std::string(")")) : subject);
    return std::make_shared<CaseTypePatternEmission>((nullable ? ((std::string("!doof::is_null(") + subject) + std::string(")")) : std::string("true")), ((bindingName == std::string("")) ? std::string("") : ((((std::string("const auto ") + bindingName) + std::string(" = ")) + value) + std::string(";\n"))));
}
std::shared_ptr<CaseTypePatternEmission> emitResultPattern(std::shared_ptr<::app_src_ast_::TypePattern> pattern, std::shared_ptr<::app_src_semantic_::ResultResolvedType> result, std::string subject, std::string bindingName, std::string currentModulePath) {
    auto armType = std::string("");
    {
        auto _case_subject = pattern->type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (named->name == std::string("Success")) {
                (armType = ((std::string("doof::Success<") + ::app_src_emitter_types_::emitResultPayloadType(result->valueType, currentModulePath)) + std::string(">")));
            }
            if (named->name == std::string("Failure")) {
                (armType = ((std::string("doof::Failure<") + ::app_src_emitter_types_::emitResultPayloadType(result->errorType, currentModulePath)) + std::string(">")));
            }
    }
    else {
    }
    }
    if (armType == std::string("")) {
        doof::panic(std::string("Result case pattern must be Success or Failure"));
    }
    return std::make_shared<CaseTypePatternEmission>(((((std::string("std::holds_alternative<") + armType) + std::string(">(")) + subject) + std::string(")")), ((bindingName == std::string("")) ? std::string("") : ((((((std::string("const auto& ") + bindingName) + std::string(" = std::get<")) + armType) + std::string(">(")) + subject) + std::string(");\n"))));
}
std::shared_ptr<CaseTypePatternEmission> emitJsonValuePattern(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> patternType, std::string subject, std::string bindingName) {
    auto condition = std::string("true");
    auto value = subject;
    {
        auto _case_subject = patternType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            if (primitive->name == std::string("bool")) {
                (condition = ((std::string("doof::json_is_boolean(") + subject) + std::string(")")));
                (value = ((std::string("doof::json_as_bool(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("string")) {
                (condition = ((std::string("doof::json_is_string(") + subject) + std::string(")")));
                (value = ((std::string("doof::json_as_string(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("int")) {
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
                (value = ((std::string("doof::json_as_int(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("long")) {
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
                (value = ((std::string("doof::json_as_long(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("float")) {
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
                (value = ((std::string("doof::json_as_float(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("double")) {
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
                (value = ((std::string("doof::json_as_double(") + subject) + std::string(")")));
            } else {
                doof::panic((std::string("Unsupported primitive JsonValue case pattern ") + primitive->name));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            (condition = ((std::string("doof::json_is_array(") + subject) + std::string(")")));
            (value = ((std::string("std::get<doof::JsonArray>(doof::json_storage(") + subject) + std::string("))")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            (condition = ((std::string("doof::json_is_object(") + subject) + std::string(")")));
            (value = ((std::string("doof::json_object(") + subject) + std::string(")")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            (condition = ((std::string("doof::json_is_null(") + subject) + std::string(")")));
            (value = std::string("nullptr"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
    }
    else {
            doof::panic(std::string("Unsupported JsonValue case pattern"));
    }
    }
    return std::make_shared<CaseTypePatternEmission>(condition, ((bindingName == std::string("")) ? std::string("") : ((((std::string("const auto ") + bindingName) + std::string(" = ")) + value) + std::string(";\n"))));
}
}
