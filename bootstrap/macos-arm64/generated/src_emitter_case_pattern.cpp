#include "src_emitter_case_pattern.hpp"

namespace app_src_emitter_case_pattern_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_types_;

#line 16 "/src/emitter-case-pattern.do"
std::shared_ptr<CaseTypePatternEmission> emitCaseTypePattern(const std::shared_ptr<::app_src_ast_::TypePattern>& pattern, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& subjectType, const std::string& subject, const std::string& bindingName, const std::string& currentModulePath) {
#line 23 "/src/emitter-case-pattern.do"
    if (doof::is_null(pattern->resolvedType)) {
#line 23 "/src/emitter-case-pattern.do"
        doof::panic(std::string("Case pattern has no resolved type"));
    }
#line 24 "/src/emitter-case-pattern.do"
    const auto patternType = doof::unwrap_optional(pattern->resolvedType);
#line 25 "/src/emitter-case-pattern.do"
    {
        auto _case_subject = subjectType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 26 "/src/emitter-case-pattern.do"
            return emitResultPattern(pattern, result, subject, bindingName, currentModulePath);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 27 "/src/emitter-case-pattern.do"
            return emitJsonValuePattern(patternType, subject, bindingName);
    }
    else {
    }
    }
#line 30 "/src/emitter-case-pattern.do"
    if (::app_src_emitter_types_::usesVariantRepresentation(subjectType)) {
#line 31 "/src/emitter-case-pattern.do"
        const auto patternCpp = ::app_src_emitter_types_::emitType(patternType, currentModulePath);
#line 32 "/src/emitter-case-pattern.do"
        if (::app_src_emitter_types_::usesVariantRepresentation(patternType)) {
#line 33 "/src/emitter-case-pattern.do"
            return std::make_shared<CaseTypePatternEmission>(((((std::string("doof::variant_is<") + patternCpp) + std::string(">(")) + subject) + std::string(")")), ((bindingName == std::string("")) ? std::string("") : ((((((std::string("const auto ") + bindingName) + std::string(" = doof::variant_narrow<")) + patternCpp) + std::string(">(")) + subject) + std::string(");\n"))));
        }
#line 38 "/src/emitter-case-pattern.do"
        return std::make_shared<CaseTypePatternEmission>(((((std::string("std::holds_alternative<") + patternCpp) + std::string(">(")) + subject) + std::string(")")), ((bindingName == std::string("")) ? std::string("") : ((((((std::string("const auto& ") + bindingName) + std::string(" = std::get<")) + patternCpp) + std::string(">(")) + subject) + std::string(");\n"))));
    }
#line 43 "/src/emitter-case-pattern.do"
    const auto nullable = ::app_src_emitter_types_::usesNullableSingleValueRepresentation(subjectType);
#line 44 "/src/emitter-case-pattern.do"
    const auto value = (nullable ? ((std::string("doof::unwrap_optional(") + subject) + std::string(")")) : subject);
#line 45 "/src/emitter-case-pattern.do"
    return std::make_shared<CaseTypePatternEmission>((nullable ? ((std::string("!doof::is_null(") + subject) + std::string(")")) : std::string("true")), ((bindingName == std::string("")) ? std::string("") : ((((std::string("const auto ") + bindingName) + std::string(" = ")) + value) + std::string(";\n"))));
}
#line 51 "/src/emitter-case-pattern.do"
std::shared_ptr<CaseTypePatternEmission> emitResultPattern(const std::shared_ptr<::app_src_ast_::TypePattern>& pattern, const std::shared_ptr<::app_src_semantic_::ResultResolvedType>& result, const std::string& subject, const std::string& bindingName, const std::string& currentModulePath) {
#line 58 "/src/emitter-case-pattern.do"
    auto armType = std::string("");
#line 59 "/src/emitter-case-pattern.do"
    {
        auto _case_subject = pattern->type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 61 "/src/emitter-case-pattern.do"
            if (named->name == std::string("Success")) {
#line 61 "/src/emitter-case-pattern.do"
                (armType = ((std::string("doof::Success<") + ::app_src_emitter_types_::emitResultPayloadType(result->valueType, currentModulePath)) + std::string(">")));
            }
#line 62 "/src/emitter-case-pattern.do"
            if (named->name == std::string("Failure")) {
#line 62 "/src/emitter-case-pattern.do"
                (armType = ((std::string("doof::Failure<") + ::app_src_emitter_types_::emitResultPayloadType(result->errorType, currentModulePath)) + std::string(">")));
            }
    }
    else {
    }
    }
#line 66 "/src/emitter-case-pattern.do"
    if (armType == std::string("")) {
#line 66 "/src/emitter-case-pattern.do"
        doof::panic(std::string("Result case pattern must be Success or Failure"));
    }
#line 67 "/src/emitter-case-pattern.do"
    return std::make_shared<CaseTypePatternEmission>(((((std::string("std::holds_alternative<") + armType) + std::string(">(")) + subject) + std::string(")")), ((bindingName == std::string("")) ? std::string("") : ((((((std::string("const auto& ") + bindingName) + std::string(" = std::get<")) + armType) + std::string(">(")) + subject) + std::string(");\n"))));
}
#line 73 "/src/emitter-case-pattern.do"
std::shared_ptr<CaseTypePatternEmission> emitJsonValuePattern(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& patternType, const std::string& subject, const std::string& bindingName) {
#line 74 "/src/emitter-case-pattern.do"
    auto condition = std::string("true");
#line 75 "/src/emitter-case-pattern.do"
    auto value = subject;
#line 76 "/src/emitter-case-pattern.do"
    {
        auto _case_subject = patternType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 78 "/src/emitter-case-pattern.do"
            if (primitive->name == std::string("bool")) {
#line 78 "/src/emitter-case-pattern.do"
                (condition = ((std::string("doof::json_is_boolean(") + subject) + std::string(")")));
#line 78 "/src/emitter-case-pattern.do"
                (value = ((std::string("doof::json_as_bool(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("string")) {
#line 79 "/src/emitter-case-pattern.do"
                (condition = ((std::string("doof::json_is_string(") + subject) + std::string(")")));
#line 79 "/src/emitter-case-pattern.do"
                (value = ((std::string("doof::json_as_string(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("int")) {
#line 80 "/src/emitter-case-pattern.do"
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
#line 80 "/src/emitter-case-pattern.do"
                (value = ((std::string("doof::json_as_int(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("long")) {
#line 81 "/src/emitter-case-pattern.do"
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
#line 81 "/src/emitter-case-pattern.do"
                (value = ((std::string("doof::json_as_long(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("float")) {
#line 82 "/src/emitter-case-pattern.do"
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
#line 82 "/src/emitter-case-pattern.do"
                (value = ((std::string("doof::json_as_float(") + subject) + std::string(")")));
            } else if (primitive->name == std::string("double")) {
#line 83 "/src/emitter-case-pattern.do"
                (condition = ((std::string("doof::json_is_number(") + subject) + std::string(")")));
#line 83 "/src/emitter-case-pattern.do"
                (value = ((std::string("doof::json_as_double(") + subject) + std::string(")")));
            } else {
#line 84 "/src/emitter-case-pattern.do"
                doof::panic((std::string("Unsupported primitive JsonValue case pattern ") + primitive->name));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 86 "/src/emitter-case-pattern.do"
            (condition = ((std::string("doof::json_is_array(") + subject) + std::string(")")));
#line 86 "/src/emitter-case-pattern.do"
            (value = ((std::string("std::get<doof::JsonArray>(doof::json_storage(") + subject) + std::string("))")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 87 "/src/emitter-case-pattern.do"
            (condition = ((std::string("doof::json_is_object(") + subject) + std::string(")")));
#line 87 "/src/emitter-case-pattern.do"
            (value = ((std::string("doof::json_object(") + subject) + std::string(")")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 88 "/src/emitter-case-pattern.do"
            (condition = ((std::string("doof::json_is_null(") + subject) + std::string(")")));
#line 88 "/src/emitter-case-pattern.do"
            (value = std::string("nullptr"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
    }
    else {
#line 90 "/src/emitter-case-pattern.do"
            doof::panic(std::string("Unsupported JsonValue case pattern"));
    }
    }
#line 92 "/src/emitter-case-pattern.do"
    return std::make_shared<CaseTypePatternEmission>(condition, ((bindingName == std::string("")) ? std::string("") : ((((std::string("const auto ") + bindingName) + std::string(" = ")) + value) + std::string(";\n"))));
}
#line 1 "<doof-generated>"
}
