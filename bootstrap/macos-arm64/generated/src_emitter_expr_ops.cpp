#include "src_emitter_expr_ops.hpp"

namespace app_src_emitter_expr_ops_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_literals_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_checker_types_;
#line 14 "/src/emitter-expr-ops.do"
std::string emitAs(const std::shared_ptr<::app_src_ast_::AsExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 15 "/src/emitter-expr-ops.do"
    const auto sourceType = ::app_src_emitter_expr_utils_::requireExpressionType(expression->expression, std::string("as source"));
#line 16 "/src/emitter-expr-ops.do"
    const auto resultType = ::app_src_emitter_expr_utils_::requireExpressionType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), std::string("as expression"));
#line 17 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = resultType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 19 "/src/emitter-expr-ops.do"
            const auto target = result->valueType;
#line 20 "/src/emitter-expr-ops.do"
            const auto resultCpp = ::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result), context->modulePath);
#line 21 "/src/emitter-expr-ops.do"
            const auto targetCpp = ::app_src_emitter_types_::emitType(target, context->modulePath);
#line 22 "/src/emitter-expr-ops.do"
            const auto success = ((std::string("doof::Success<") + targetCpp) + std::string(">"));
#line 23 "/src/emitter-expr-ops.do"
            const auto failure = ((std::string("doof::Failure<") + ::app_src_emitter_types_::emitType(result->errorType, context->modulePath)) + std::string(">"));
#line 24 "/src/emitter-expr-ops.do"
            const auto source = ::app_src_emitter_expr_::emitExpression(expression->expression, context, std::monostate{});
#line 25 "/src/emitter-expr-ops.do"
            if (::app_src_checker_types_::sameType(sourceType, target)) {
#line 25 "/src/emitter-expr-ops.do"
                return (((((resultCpp + std::string("{")) + success) + std::string("{")) + source) + std::string("}}"));
            }
#line 26 "/src/emitter-expr-ops.do"
            {
                auto _case_subject = sourceType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& sourceResult = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 28 "/src/emitter-expr-ops.do"
                    auto narrowed = std::string("");
#line 29 "/src/emitter-expr-ops.do"
                    {
                        auto _case_subject = sourceResult->valueType;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 30 "/src/emitter-expr-ops.do"
                            (narrowed = emitJsonAs(std::string("doof::success_value(_as_source)"), target, resultCpp, success, failure));
                    }
                    else {
                    }
                    }
#line 33 "/src/emitter-expr-ops.do"
                    if (narrowed != std::string("")) {
#line 34 "/src/emitter-expr-ops.do"
                        const auto errorValue = emitAsFailureValue(sourceResult, result, context);
#line 35 "/src/emitter-expr-ops.do"
                        return ((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_source = ")) + source) + std::string("; if (doof::is_failure(_as_source)) return ")) + failure) + std::string("{")) + errorValue) + std::string("}; return ")) + narrowed) + std::string("; }()"));
                    }
#line 37 "/src/emitter-expr-ops.do"
                    if (::app_src_checker_types_::isNumeric(sourceResult->valueType) && ::app_src_checker_types_::isNumeric(target)) {
#line 38 "/src/emitter-expr-ops.do"
                        const auto errorValue = emitAsFailureValue(sourceResult, result, context);
#line 39 "/src/emitter-expr-ops.do"
                        return ((((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_source = ")) + source) + std::string("; if (doof::is_failure(_as_source)) return ")) + failure) + std::string("{")) + errorValue) + std::string("}; auto _as_checked = doof::checked_numeric_as<")) + targetCpp) + std::string(">(doof::success_value(_as_source)); if (_as_checked.has_value()) return ")) + success) + std::string("{_as_checked.value()}; return ")) + failure) + std::string("{\"Numeric narrowing failed\"}; }()"));
                    }
            }
            else {
            }
            }
#line 44 "/src/emitter-expr-ops.do"
            if (::app_src_checker_types_::isNumeric(sourceType) && ::app_src_checker_types_::isNumeric(target)) {
#line 45 "/src/emitter-expr-ops.do"
                return ((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_checked = doof::checked_numeric_as<")) + targetCpp) + std::string(">(")) + source) + std::string("); if (_as_checked.has_value()) return ")) + success) + std::string("{_as_checked.value()}; return ")) + failure) + std::string("{\"Numeric narrowing failed\"}; }()"));
            }
#line 47 "/src/emitter-expr-ops.do"
            {
                auto _case_subject = sourceType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 48 "/src/emitter-expr-ops.do"
                    return emitJsonAs(source, target, resultCpp, success, failure);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 50 "/src/emitter-expr-ops.do"
                    {
                        auto _case_subject = target;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 52 "/src/emitter-expr-ops.do"
                            return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (std::holds_alternative<")) + targetCpp) + std::string(">(_as_value)) return ")) + success) + std::string("{std::get<")) + targetCpp) + std::string(">(_as_value)}; return ")) + failure) + std::string("{\"Interface narrowing failed\"}; }()"));
                    }
                    else {
                    }
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                    const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 58 "/src/emitter-expr-ops.do"
                    if (unionContainsJsonValue(union_)) {
#line 59 "/src/emitter-expr-ops.do"
                        const auto narrowedJson = std::string("std::get<doof::JsonValue>(_as_nullable)");
#line 60 "/src/emitter-expr-ops.do"
                        const auto jsonNarrowing = emitJsonAs(narrowedJson, target, resultCpp, success, failure);
#line 61 "/src/emitter-expr-ops.do"
                        return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_nullable = ")) + source) + std::string("; if (doof::is_null(_as_nullable)) return ")) + failure) + std::string("{\"JsonValue narrowing failed\"}; return ")) + jsonNarrowing) + std::string("; }()"));
                    }
#line 63 "/src/emitter-expr-ops.do"
                    const auto member = ::app_src_emitter_types_::naturalNullableUnionMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
#line 64 "/src/emitter-expr-ops.do"
                    if (!doof::is_null(member)) {
#line 65 "/src/emitter-expr-ops.do"
                        if (::app_src_checker_types_::sameType(doof::unwrap_optional(member), target)) {
#line 66 "/src/emitter-expr-ops.do"
                            {
                                auto _case_subject = target;
                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 68 "/src/emitter-expr-ops.do"
                                    if (class_->symbol->kind == std::string("struct")) {
#line 69 "/src/emitter-expr-ops.do"
                                        return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (_as_value.has_value()) return ")) + success) + std::string("{_as_value.value()}; return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; }()"));
                                    }
#line 71 "/src/emitter-expr-ops.do"
                                    return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (_as_value) return ")) + success) + std::string("{_as_value}; return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; }()"));
                            }
                            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 74 "/src/emitter-expr-ops.do"
                                    return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (_as_value) return ")) + success) + std::string("{_as_value}; return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; }()"));
                            }
                            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
#line 77 "/src/emitter-expr-ops.do"
                                    return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (_as_value.has_value()) return ")) + success) + std::string("{_as_value.value()}; return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; }()"));
                            }
                            else {
                            }
                            }
                        }
#line 82 "/src/emitter-expr-ops.do"
                        if (::app_src_checker_types_::isNumeric(doof::unwrap_optional(member)) && ::app_src_checker_types_::isNumeric(target)) {
#line 83 "/src/emitter-expr-ops.do"
                            return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (!_as_value.has_value()) return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; auto _as_checked = doof::checked_numeric_as<")) + targetCpp) + std::string(">(_as_value.value()); if (_as_checked.has_value()) return ")) + success) + std::string("{_as_checked.value()}; return ")) + failure) + std::string("{\"Numeric narrowing failed\"}; }()"));
                        }
                    }
#line 86 "/src/emitter-expr-ops.do"
                    if (::app_src_checker_types_::isNumeric(target) && unionHasNumericMember(union_)) {
#line 87 "/src/emitter-expr-ops.do"
                        return emitNumericUnionAs(source, union_, targetCpp, resultCpp, success, failure, context);
                    }
#line 89 "/src/emitter-expr-ops.do"
                    return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (doof::variant_is<")) + targetCpp) + std::string(">(_as_value)) return ")) + success) + std::string("{doof::variant_narrow<")) + targetCpp) + std::string(">(_as_value)}; return ")) + failure) + std::string("{\"Union narrowing failed\"}; }()"));
            }
            else {
            }
            }
#line 93 "/src/emitter-expr-ops.do"
            return (failure + std::string("{\"Unsupported narrowing\"}"));
    }
    else {
#line 95 "/src/emitter-expr-ops.do"
            doof::panic(std::string("as expression must resolve to Result"));
    }
    }
    doof::unreachable();
#line 97 "/src/emitter-expr-ops.do"
    return std::string("");
}
#line 100 "/src/emitter-expr-ops.do"
std::string emitAsFailureValue(const std::shared_ptr<::app_src_semantic_::ResultResolvedType>& source, const std::shared_ptr<::app_src_semantic_::ResultResolvedType>& target, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 101 "/src/emitter-expr-ops.do"
    const auto errorValue = std::string("doof::failure_error(_as_source)");
#line 102 "/src/emitter-expr-ops.do"
    if (!::app_src_checker_types_::sameType(source->errorType, target->errorType)) {
#line 103 "/src/emitter-expr-ops.do"
        return ((((std::string("doof::variant_promote<") + ::app_src_emitter_types_::emitType(target->errorType, context->modulePath)) + std::string(">(")) + errorValue) + std::string(")"));
    }
#line 105 "/src/emitter-expr-ops.do"
    return errorValue;
}
#line 108 "/src/emitter-expr-ops.do"
bool unionHasNumericMember(const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
#line 109 "/src/emitter-expr-ops.do"
    const auto& _iterable_2 = union_->types;
    for (const auto& member : *_iterable_2) {
#line 109 "/src/emitter-expr-ops.do"
        if (::app_src_checker_types_::isNumeric(member)) {
#line 109 "/src/emitter-expr-ops.do"
            return true;
        }
    }
#line 110 "/src/emitter-expr-ops.do"
    return false;
}
#line 113 "/src/emitter-expr-ops.do"
std::string emitNumericUnionAs(const std::string& source, const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_, const std::string& targetCpp, const std::string& resultCpp, const std::string& success, const std::string& failure, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 114 "/src/emitter-expr-ops.do"
    auto numericItem = std::string("");
#line 115 "/src/emitter-expr-ops.do"
    const auto& _iterable_4 = union_->types;
    for (const auto& member : *_iterable_4) {
#line 116 "/src/emitter-expr-ops.do"
        if (::app_src_checker_types_::isNumeric(member)) {
#line 117 "/src/emitter-expr-ops.do"
            if (numericItem != std::string("")) {
#line 117 "/src/emitter-expr-ops.do"
                (numericItem = (numericItem + std::string(" || ")));
            }
#line 118 "/src/emitter-expr-ops.do"
            (numericItem = (((numericItem + std::string("std::is_same_v<_AsItem, ")) + ::app_src_emitter_types_::emitType(member, context->modulePath)) + std::string(">")));
        }
    }
#line 121 "/src/emitter-expr-ops.do"
    return ((((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; auto _as_checked = std::visit([](const auto& _as_item) -> std::optional<")) + targetCpp) + std::string("> { using _AsItem = std::decay_t<decltype(_as_item)>; if constexpr (")) + numericItem) + std::string(") return doof::checked_numeric_as<")) + targetCpp) + std::string(">(_as_item); return std::nullopt; }, _as_value); if (_as_checked.has_value()) return ")) + success) + std::string("{_as_checked.value()}; return ")) + failure) + std::string("{\"Numeric narrowing failed\"}; }()"));
}
#line 124 "/src/emitter-expr-ops.do"
bool unionContainsJsonValue(const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
#line 125 "/src/emitter-expr-ops.do"
    const auto& _iterable_6 = union_->types;
    for (const auto& member : *_iterable_6) {
#line 126 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 127 "/src/emitter-expr-ops.do"
                return true;
        }
        else {
        }
        }
    }
#line 131 "/src/emitter-expr-ops.do"
    return false;
}
#line 134 "/src/emitter-expr-ops.do"
std::string emitJsonAs(const std::string& source, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& target, const std::string& resultCpp, const std::string& success, const std::string& failure) {
#line 135 "/src/emitter-expr-ops.do"
    auto condition = std::string("true");
#line 136 "/src/emitter-expr-ops.do"
    auto value = source;
#line 137 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = target;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 139 "/src/emitter-expr-ops.do"
            if (primitive->name == std::string("bool")) {
#line 139 "/src/emitter-expr-ops.do"
                (condition = std::string("doof::json_is_boolean(_as_value)"));
#line 139 "/src/emitter-expr-ops.do"
                (value = std::string("doof::json_as_bool(_as_value)"));
            } else if (primitive->name == std::string("string")) {
#line 140 "/src/emitter-expr-ops.do"
                (condition = std::string("doof::json_is_string(_as_value)"));
#line 140 "/src/emitter-expr-ops.do"
                (value = std::string("doof::json_as_string(_as_value)"));
            } else if (primitive->name == std::string("int")) {
#line 141 "/src/emitter-expr-ops.do"
                (condition = std::string("doof::json_is_number(_as_value)"));
#line 141 "/src/emitter-expr-ops.do"
                (value = std::string("doof::json_as_int(_as_value)"));
            } else if (primitive->name == std::string("long")) {
#line 142 "/src/emitter-expr-ops.do"
                (condition = std::string("doof::json_is_number(_as_value)"));
#line 142 "/src/emitter-expr-ops.do"
                (value = std::string("doof::json_as_long(_as_value)"));
            } else if (primitive->name == std::string("float")) {
#line 143 "/src/emitter-expr-ops.do"
                (condition = std::string("doof::json_is_number(_as_value)"));
#line 143 "/src/emitter-expr-ops.do"
                (value = std::string("doof::json_as_float(_as_value)"));
            } else if (primitive->name == std::string("double")) {
#line 144 "/src/emitter-expr-ops.do"
                (condition = std::string("doof::json_is_number(_as_value)"));
#line 144 "/src/emitter-expr-ops.do"
                (value = std::string("doof::json_as_double(_as_value)"));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 146 "/src/emitter-expr-ops.do"
            (condition = std::string("doof::json_is_array(_as_value)"));
#line 146 "/src/emitter-expr-ops.do"
            (value = std::string("std::get<doof::JsonArray>(doof::json_storage(_as_value))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 147 "/src/emitter-expr-ops.do"
            (condition = std::string("doof::json_is_object(_as_value)"));
#line 147 "/src/emitter-expr-ops.do"
            (value = std::string("doof::json_object(_as_value)"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 148 "/src/emitter-expr-ops.do"
            (value = std::string("_as_value"));
    }
    else {
    }
    }
#line 151 "/src/emitter-expr-ops.do"
    return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (")) + condition) + std::string(") return ")) + success) + std::string("{")) + value) + std::string("}; return ")) + failure) + std::string("{\"JsonValue narrowing failed\"}; }()"));
}
#line 154 "/src/emitter-expr-ops.do"
std::string emitAssignment(const std::shared_ptr<::app_src_ast_::AssignmentExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 155 "/src/emitter-expr-ops.do"
    const auto operator_ = ((expression->operator_ == std::string("\\=")) ? std::string("/=") : expression->operator_);
#line 156 "/src/emitter-expr-ops.do"
    const auto targetType = std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->target);
#line 157 "/src/emitter-expr-ops.do"
    const auto value = ::app_src_emitter_expr_::emitExpression(expression->value, context, targetType);
#line 158 "/src/emitter-expr-ops.do"
    return ((((((std::string("(") + emitAssignmentTarget(expression->target, context)) + std::string(" ")) + operator_) + std::string(" ")) + value) + std::string(")"));
}
#line 161 "/src/emitter-expr-ops.do"
std::string emitAssignmentTarget(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& target, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 162 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = target;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 164 "/src/emitter-expr-ops.do"
            const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(index->object);
#line 165 "/src/emitter-expr-ops.do"
            if (!doof::is_null(objectType)) {
#line 166 "/src/emitter-expr-ops.do"
                {
                    auto _case_subject = doof::unwrap_optional(objectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 168 "/src/emitter-expr-ops.do"
                        return ((((((((std::string("doof::map_index(") + ::app_src_emitter_expr_::emitExpression(index->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(index->index, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_literals_::quote(::app_src_emitter_names_::moduleDiagnosticPath(context->modulePath, true))) + std::string(", ")) + doof::to_string(index->span.start.line)) + std::string(")"));
                }
                else {
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 175 "/src/emitter-expr-ops.do"
            const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
#line 176 "/src/emitter-expr-ops.do"
            if ((!doof::is_null(objectType)) && isVariantCarrier(doof::unwrap_optional(objectType))) {
#line 177 "/src/emitter-expr-ops.do"
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 178 "/src/emitter-expr-ops.do"
                return ((((std::string("std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->") + cppIdentifier(member->property)) + std::string("); }, ")) + ::app_src_emitter_expr_utils_::variantVisitValue(object, doof::unwrap_optional(objectType))) + std::string(")"));
            }
    }
    else {
    }
    }
#line 183 "/src/emitter-expr-ops.do"
    return ::app_src_emitter_expr_::emitExpression(target, context, std::monostate{});
}
#line 186 "/src/emitter-expr-ops.do"
bool isVariantCarrier(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType) {
#line 187 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 188 "/src/emitter-expr-ops.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 190 "/src/emitter-expr-ops.do"
            auto nonNull = 0;
#line 191 "/src/emitter-expr-ops.do"
            const auto& _iterable_8 = union_->types;
            for (const auto& member : *_iterable_8) {
#line 191 "/src/emitter-expr-ops.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 191 "/src/emitter-expr-ops.do"
                    (nonNull = (nonNull + 1));
                }
            }
#line 192 "/src/emitter-expr-ops.do"
            return (nonNull > 1);
    }
    else {
    }
    }
#line 196 "/src/emitter-expr-ops.do"
    return false;
}
#line 199 "/src/emitter-expr-ops.do"
std::string emitIdentifier(const std::shared_ptr<::app_src_ast_::Identifier>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 200 "/src/emitter-expr-ops.do"
    if ((!doof::is_null(expression->resolvedBinding)) && (expression->resolvedBinding->kind == std::string("script-global"))) {
#line 201 "/src/emitter-expr-ops.do"
        return ((std::string("__doof_script_get_") + cppIdentifier(expression->name)) + std::string("()"));
    }
#line 203 "/src/emitter-expr-ops.do"
    if (((!doof::is_null(expression->resolvedBinding)) && (expression->resolvedBinding->kind == std::string("field"))) && !context->currentFunctionStatic) {
#line 204 "/src/emitter-expr-ops.do"
        return (std::string("this->") + cppIdentifier(expression->name));
    }
#line 206 "/src/emitter-expr-ops.do"
    const auto& _iterable_10 = context->imports;
    for (const auto& imported : *_iterable_10) {
#line 207 "/src/emitter-expr-ops.do"
        if ((imported->localName == expression->name) && (!doof::is_null(imported->symbol))) {
#line 208 "/src/emitter-expr-ops.do"
            if (imported->symbol->native_) {
#line 209 "/src/emitter-expr-ops.do"
                return (std::string("::") + ((imported->symbol->nativeCppName == std::string("")) ? imported->symbol->name : imported->symbol->nativeCppName));
            }
#line 211 "/src/emitter-expr-ops.do"
            return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(imported->symbol->module)) + std::string("::")) + cppIdentifier(::app_src_emitter_expr_utils_::emittedSymbolName(doof::unwrap_optional(imported->symbol))));
        }
    }
#line 214 "/src/emitter-expr-ops.do"
    if ((!doof::is_null(expression->resolvedBinding)) && (!doof::is_null(expression->resolvedBinding->symbol))) {
#line 215 "/src/emitter-expr-ops.do"
        const auto symbol = doof::unwrap_optional(expression->resolvedBinding->symbol);
#line 216 "/src/emitter-expr-ops.do"
        if (symbol->native_) {
#line 217 "/src/emitter-expr-ops.do"
            return (std::string("::") + ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName));
        }
#line 219 "/src/emitter-expr-ops.do"
        if (((context->modulePath != std::string("")) && (symbol->module != std::string(""))) && (symbol->module != context->modulePath)) {
#line 220 "/src/emitter-expr-ops.do"
            return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(symbol->module)) + std::string("::")) + cppIdentifier(::app_src_emitter_expr_utils_::emittedSymbolName(symbol)));
        }
    }
#line 223 "/src/emitter-expr-ops.do"
    if ((!doof::is_null(expression->resolvedBinding)) && (expression->resolvedBinding->kind == std::string("import"))) {
#line 224 "/src/emitter-expr-ops.do"
        const auto& _iterable_12 = context->imports;
        for (const auto& imported : *_iterable_12) {
#line 225 "/src/emitter-expr-ops.do"
            if ((imported->localName == expression->name) && (!doof::is_null(imported->symbol))) {
#line 226 "/src/emitter-expr-ops.do"
                return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(imported->symbol->module)) + std::string("::")) + cppIdentifier(::app_src_emitter_expr_utils_::emittedSymbolName(doof::unwrap_optional(imported->symbol))));
            }
        }
    }
#line 230 "/src/emitter-expr-ops.do"
    if (((!doof::is_null(expression->resolvedBinding)) && expression->resolvedBinding->mutable_) && ::app_src_emitter_context_::isCapturedMutable(context, expression->name)) {
#line 231 "/src/emitter-expr-ops.do"
        return ((std::string("(*") + cppIdentifier(expression->name)) + std::string(")"));
    }
#line 233 "/src/emitter-expr-ops.do"
    return cppIdentifier(expression->name);
}
#line 236 "/src/emitter-expr-ops.do"
std::string cppIdentifier(const std::string& name) {
#line 237 "/src/emitter-expr-ops.do"
    if (isCppKeyword(name)) {
#line 237 "/src/emitter-expr-ops.do"
        return (name + std::string("_"));
    }
#line 238 "/src/emitter-expr-ops.do"
    if (name == std::string("stdin")) {
#line 238 "/src/emitter-expr-ops.do"
        return std::string("stdin_");
    }
#line 239 "/src/emitter-expr-ops.do"
    if (name == std::string("stdout")) {
#line 239 "/src/emitter-expr-ops.do"
        return std::string("stdout_");
    }
#line 240 "/src/emitter-expr-ops.do"
    if (name == std::string("stderr")) {
#line 240 "/src/emitter-expr-ops.do"
        return std::string("stderr_");
    }
#line 241 "/src/emitter-expr-ops.do"
    return name;
}
#line 244 "/src/emitter-expr-ops.do"
bool isCppKeyword(const std::string& name) {
#line 245 "/src/emitter-expr-ops.do"
    return (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((name == std::string("alignas")) || (name == std::string("alignof"))) || (name == std::string("and"))) || (name == std::string("and_eq"))) || (name == std::string("asm"))) || (name == std::string("auto"))) || (name == std::string("bitand"))) || (name == std::string("bitor"))) || (name == std::string("bool"))) || (name == std::string("break"))) || (name == std::string("case"))) || (name == std::string("catch"))) || (name == std::string("char"))) || (name == std::string("char8_t"))) || (name == std::string("char16_t"))) || (name == std::string("char32_t"))) || (name == std::string("class"))) || (name == std::string("compl"))) || (name == std::string("concept"))) || (name == std::string("const"))) || (name == std::string("consteval"))) || (name == std::string("constexpr"))) || (name == std::string("constinit"))) || (name == std::string("const_cast"))) || (name == std::string("continue"))) || (name == std::string("co_await"))) || (name == std::string("co_return"))) || (name == std::string("co_yield"))) || (name == std::string("decltype"))) || (name == std::string("default"))) || (name == std::string("delete"))) || (name == std::string("do"))) || (name == std::string("double"))) || (name == std::string("dynamic_cast"))) || (name == std::string("else"))) || (name == std::string("enum"))) || (name == std::string("explicit"))) || (name == std::string("export"))) || (name == std::string("extern"))) || (name == std::string("false"))) || (name == std::string("float"))) || (name == std::string("for"))) || (name == std::string("friend"))) || (name == std::string("goto"))) || (name == std::string("if"))) || (name == std::string("inline"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("mutable"))) || (name == std::string("namespace"))) || (name == std::string("new"))) || (name == std::string("noexcept"))) || (name == std::string("not"))) || (name == std::string("not_eq"))) || (name == std::string("nullptr"))) || (name == std::string("operator"))) || (name == std::string("or"))) || (name == std::string("or_eq"))) || (name == std::string("private"))) || (name == std::string("protected"))) || (name == std::string("public"))) || (name == std::string("register"))) || (name == std::string("reinterpret_cast"))) || (name == std::string("requires"))) || (name == std::string("return"))) || (name == std::string("short"))) || (name == std::string("signed"))) || (name == std::string("sizeof"))) || (name == std::string("static"))) || (name == std::string("static_assert"))) || (name == std::string("struct"))) || (name == std::string("switch"))) || (name == std::string("template"))) || (name == std::string("this"))) || (name == std::string("thread_local"))) || (name == std::string("throw"))) || (name == std::string("true"))) || (name == std::string("try"))) || (name == std::string("typedef"))) || (name == std::string("typeid"))) || (name == std::string("typename"))) || (name == std::string("union"))) || (name == std::string("unsigned"))) || (name == std::string("using"))) || (name == std::string("virtual"))) || (name == std::string("void"))) || (name == std::string("volatile"))) || (name == std::string("wchar_t"))) || (name == std::string("while"))) || (name == std::string("xor"))) || (name == std::string("xor_eq")));
}
#line 262 "/src/emitter-expr-ops.do"
std::string emitUnary(const std::shared_ptr<::app_src_ast_::UnaryExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 263 "/src/emitter-expr-ops.do"
    if ((expression->operator_ == std::string("try!")) || (expression->operator_ == std::string("try\?"))) {
#line 264 "/src/emitter-expr-ops.do"
        const auto operand = ::app_src_emitter_expr_::emitExpression(expression->operand, context, std::monostate{});
#line 265 "/src/emitter-expr-ops.do"
        const auto operandType = ::app_src_emitter_expr_utils_::requireExpressionType(expression->operand, (expression->operator_ + std::string(" operand")));
#line 266 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = operandType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 268 "/src/emitter-expr-ops.do"
                const auto valueType = ::app_src_emitter_types_::emitType(result->valueType, context->modulePath);
#line 269 "/src/emitter-expr-ops.do"
                auto failureMessage = ((std::string("std::string(\"") + expression->operator_) + std::string(" failed\")"));
#line 270 "/src/emitter-expr-ops.do"
                {
                    auto _case_subject = result->errorType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                        const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 272 "/src/emitter-expr-ops.do"
                        if (primitive->name == std::string("string")) {
#line 273 "/src/emitter-expr-ops.do"
                            (failureMessage = (failureMessage + std::string(" + std::string(\": \") + doof::failure_error(_try_value)")));
                        }
                }
                else {
                }
                }
#line 278 "/src/emitter-expr-ops.do"
                const auto sourcePath = ::app_src_emitter_names_::moduleDiagnosticPath(context->modulePath, true);
#line 279 "/src/emitter-expr-ops.do"
                const auto body = ((((((((std::string("auto _try_value = ") + operand) + std::string("; if (doof::is_failure(_try_value)) doof::panic_at(")) + ::app_src_emitter_expr_literals_::quote(sourcePath)) + std::string(", ")) + doof::to_string(expression->span.start.line)) + std::string(", ")) + failureMessage) + std::string("); "));
#line 280 "/src/emitter-expr-ops.do"
                {
                    auto _case_subject = result->valueType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 281 "/src/emitter-expr-ops.do"
                        return ((std::string("[&]() -> void { ") + body) + std::string(" }()"));
                }
                else {
                }
                }
#line 284 "/src/emitter-expr-ops.do"
                if (expression->operator_ == std::string("try\?")) {
#line 285 "/src/emitter-expr-ops.do"
                    return ((((std::string("[&]() -> std::optional<") + valueType) + std::string("> { ")) + body) + std::string("return std::move(doof::success_value(_try_value)); }()"));
                }
#line 287 "/src/emitter-expr-ops.do"
                return ((((std::string("[&]() -> ") + valueType) + std::string(" { ")) + body) + std::string("return std::move(doof::success_value(_try_value)); }()"));
        }
        else {
#line 289 "/src/emitter-expr-ops.do"
                doof::panic((expression->operator_ + std::string(" operand is not a Result")));
        }
        }
        doof::unreachable();
    }
#line 292 "/src/emitter-expr-ops.do"
    const auto operand = ::app_src_emitter_expr_::emitExpression(expression->operand, context, std::monostate{});
#line 293 "/src/emitter-expr-ops.do"
    if (!expression->prefix && (expression->operator_ == std::string("!"))) {
#line 294 "/src/emitter-expr-ops.do"
        const auto operandType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->operand);
#line 295 "/src/emitter-expr-ops.do"
        if (!doof::is_null(operandType)) {
#line 296 "/src/emitter-expr-ops.do"
            {
                auto _case_subject = doof::unwrap_optional(operandType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 298 "/src/emitter-expr-ops.do"
                    const auto valueType = ::app_src_emitter_types_::emitType(result->valueType, context->modulePath);
#line 299 "/src/emitter-expr-ops.do"
                    const auto body = ((std::string("auto _assert_value = ") + operand) + std::string("; if (doof::is_failure(_assert_value)) doof::panic(\"! failed\"); "));
#line 300 "/src/emitter-expr-ops.do"
                    {
                        auto _case_subject = result->valueType;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 301 "/src/emitter-expr-ops.do"
                            return ((std::string("[&]() -> void { ") + body) + std::string("}()"));
                    }
                    else {
                    }
                    }
#line 304 "/src/emitter-expr-ops.do"
                    return ((((std::string("[&]() -> ") + valueType) + std::string(" { ")) + body) + std::string("return std::move(doof::success_value(_assert_value)); }()"));
            }
            else {
            }
            }
        }
#line 309 "/src/emitter-expr-ops.do"
        if (!doof::is_null(operandType)) {
#line 310 "/src/emitter-expr-ops.do"
            {
                auto _case_subject = expression->operand;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
#line 312 "/src/emitter-expr-ops.do"
                    {
                        auto _case_subject = doof::unwrap_optional(operandType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 314 "/src/emitter-expr-ops.do"
                            if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
#line 315 "/src/emitter-expr-ops.do"
                                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> nonNullMembers = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 316 "/src/emitter-expr-ops.do"
                                const auto& _iterable_14 = union_->types;
                                for (const auto& member : *_iterable_14) {
#line 316 "/src/emitter-expr-ops.do"
                                    if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 316 "/src/emitter-expr-ops.do"
                                        nonNullMembers->push_back(member);
                                    }
                                }
#line 317 "/src/emitter-expr-ops.do"
                                if (static_cast<int32_t>((nonNullMembers)->size()) == 1) {
#line 317 "/src/emitter-expr-ops.do"
                                    return ((((std::string("std::get<") + ::app_src_emitter_types_::emitType(doof::array_at(nonNullMembers, 0, "src/emitter-expr-ops", 317), context->modulePath)) + std::string(">(")) + operand) + std::string(")"));
                                }
                            }
                    }
                    else {
                    }
                    }
#line 322 "/src/emitter-expr-ops.do"
                    return ((std::string("doof::unwrap_optional(") + operand) + std::string(")"));
            }
            else {
            }
            }
#line 326 "/src/emitter-expr-ops.do"
            {
                auto _case_subject = doof::unwrap_optional(operandType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                    const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 328 "/src/emitter-expr-ops.do"
                    if (::app_src_emitter_expr_utils_::hasSinglePrimitiveMember(union_)) {
#line 328 "/src/emitter-expr-ops.do"
                        return (operand + std::string(".value()"));
                    }
#line 329 "/src/emitter-expr-ops.do"
                    if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
#line 330 "/src/emitter-expr-ops.do"
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> nonNullMembers = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 331 "/src/emitter-expr-ops.do"
                        const auto& _iterable_16 = union_->types;
                        for (const auto& member : *_iterable_16) {
#line 331 "/src/emitter-expr-ops.do"
                            if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 331 "/src/emitter-expr-ops.do"
                                nonNullMembers->push_back(member);
                            }
                        }
#line 332 "/src/emitter-expr-ops.do"
                        if (static_cast<int32_t>((nonNullMembers)->size()) == 1) {
#line 332 "/src/emitter-expr-ops.do"
                            return ((((std::string("std::get<") + ::app_src_emitter_types_::emitType(doof::array_at(nonNullMembers, 0, "src/emitter-expr-ops", 332), context->modulePath)) + std::string(">(")) + operand) + std::string(")"));
                        }
                    }
#line 334 "/src/emitter-expr-ops.do"
                    if (::app_src_emitter_expr_utils_::isNullableVariantType(operandType)) {
#line 334 "/src/emitter-expr-ops.do"
                        return ((std::string("doof::unwrap_optional(") + operand) + std::string(")"));
                    }
            }
            else {
            }
            }
        }
#line 339 "/src/emitter-expr-ops.do"
        return ((std::string("doof::unwrap_optional(") + operand) + std::string(")"));
    }
#line 341 "/src/emitter-expr-ops.do"
    return (binaryOperator(expression->operator_) + operand);
}
#line 344 "/src/emitter-expr-ops.do"
std::string binaryOperator(const std::string& operator_) {
#line 345 "/src/emitter-expr-ops.do"
    return ((operator_ == std::string("!")) ? std::string("!") : ((operator_ == std::string("-")) ? std::string("-") : ((operator_ == std::string("+")) ? std::string("+") : std::string("~"))));
}
#line 348 "/src/emitter-expr-ops.do"
std::string emitBinary(const std::shared_ptr<::app_src_ast_::BinaryExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 349 "/src/emitter-expr-ops.do"
    if (expression->operator_ == std::string("+")) {
#line 350 "/src/emitter-expr-ops.do"
        std::shared_ptr<std::vector<std::string>> literalParts = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 351 "/src/emitter-expr-ops.do"
        if (appendConstantStringParts(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), literalParts)) {
#line 352 "/src/emitter-expr-ops.do"
            auto value = std::string("");
#line 353 "/src/emitter-expr-ops.do"
            const auto& _iterable_18 = literalParts;
            for (const auto& part : *_iterable_18) {
#line 353 "/src/emitter-expr-ops.do"
                (value = (value + part));
            }
#line 354 "/src/emitter-expr-ops.do"
            return ((std::string("std::string(") + ::app_src_emitter_expr_literals_::quote(value)) + std::string(")"));
        }
    }
#line 357 "/src/emitter-expr-ops.do"
    if (expression->operator_ == std::string("..")) {
#line 358 "/src/emitter-expr-ops.do"
        return ((((std::string("doof::range(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
    }
#line 360 "/src/emitter-expr-ops.do"
    if (expression->operator_ == std::string("..<")) {
#line 361 "/src/emitter-expr-ops.do"
        return ((((std::string("doof::range_exclusive(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
    }
#line 363 "/src/emitter-expr-ops.do"
    if (expression->operator_ == std::string("\?\?")) {
#line 364 "/src/emitter-expr-ops.do"
        const auto left = ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{});
#line 365 "/src/emitter-expr-ops.do"
        const auto leftType = ::app_src_emitter_expr_utils_::requireExpressionType(expression->left, std::string("coalescing source"));
#line 366 "/src/emitter-expr-ops.do"
        const auto resultType = ::app_src_emitter_expr_utils_::requireExpressionType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), std::string("coalescing expression"));
#line 367 "/src/emitter-expr-ops.do"
        const auto rightType = ::app_src_emitter_expr_utils_::requireExpressionType(expression->right, std::string("coalescing fallback"));
#line 368 "/src/emitter-expr-ops.do"
        const auto right = ::app_src_emitter_expr_::emitExpression(expression->right, context, doof::optional_value(resultType));
#line 369 "/src/emitter-expr-ops.do"
        const auto fallback = ((std::visit([](auto&& _obj) { return _obj->kind; }, rightType) == std::string("never")) ? ((std::string("{ ") + right) + std::string("; }")) : ((std::string("return ") + right) + std::string(";")));
#line 370 "/src/emitter-expr-ops.do"
        (context->tryCounter = (context->tryCounter + 1));
#line 371 "/src/emitter-expr-ops.do"
        const auto temporary = (std::string("_coalesce_") + doof::to_string(context->tryCounter));
#line 372 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = leftType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
#line 374 "/src/emitter-expr-ops.do"
                return ((((((((((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(resultType, context->modulePath)) + std::string(" { auto ")) + temporary) + std::string(" = ")) + left) + std::string("; if (doof::is_failure(")) + temporary) + std::string(")) ")) + fallback) + std::string(" return std::move(doof::success_value(")) + temporary) + std::string(")); }()"));
        }
        else {
#line 377 "/src/emitter-expr-ops.do"
                return ((((((((((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(resultType, context->modulePath)) + std::string(" { auto ")) + temporary) + std::string(" = ")) + left) + std::string("; if (doof::is_null(")) + temporary) + std::string(")) ")) + fallback) + std::string(" return doof::unwrap_optional(")) + temporary) + std::string("); }()"));
        }
        }
        doof::unreachable();
    }
#line 381 "/src/emitter-expr-ops.do"
    if (((expression->operator_ == std::string("==")) || (expression->operator_ == std::string("!="))) && (std::visit([](auto&& _obj) { return _obj->kind; }, expression->right) == std::string("none-literal"))) {
#line 382 "/src/emitter-expr-ops.do"
        auto test = ((std::string("doof::is_null(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(")"));
#line 383 "/src/emitter-expr-ops.do"
        return ((expression->operator_ == std::string("==")) ? test : ((std::string("(!") + test) + std::string(")")));
    }
#line 385 "/src/emitter-expr-ops.do"
    if (((expression->operator_ == std::string("==")) || (expression->operator_ == std::string("!="))) && (std::visit([](auto&& _obj) { return _obj->kind; }, expression->left) == std::string("none-literal"))) {
#line 386 "/src/emitter-expr-ops.do"
        auto test = ((std::string("doof::is_null(") + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
#line 387 "/src/emitter-expr-ops.do"
        return ((expression->operator_ == std::string("==")) ? test : ((std::string("(!") + test) + std::string(")")));
    }
#line 389 "/src/emitter-expr-ops.do"
    if (expression->operator_ == std::string("**")) {
#line 390 "/src/emitter-expr-ops.do"
        return ((((std::string("std::pow(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
    }
#line 392 "/src/emitter-expr-ops.do"
    const auto operator_ = ((expression->operator_ == std::string("\\")) ? std::string("/") : expression->operator_);
#line 393 "/src/emitter-expr-ops.do"
    return ((((((std::string("(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(" ")) + operator_) + std::string(" ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
}
#line 396 "/src/emitter-expr-ops.do"
bool appendConstantStringParts(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<std::vector<std::string>>& parts) {
#line 397 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 399 "/src/emitter-expr-ops.do"
            if (static_cast<int32_t>((string_->interpolations)->size()) > 0) {
#line 399 "/src/emitter-expr-ops.do"
                return false;
            }
#line 400 "/src/emitter-expr-ops.do"
            parts->push_back(string_->value);
#line 401 "/src/emitter-expr-ops.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 404 "/src/emitter-expr-ops.do"
            if (binary->operator_ != std::string("+")) {
#line 404 "/src/emitter-expr-ops.do"
                return false;
            }
#line 405 "/src/emitter-expr-ops.do"
            return (appendConstantStringParts(binary->left, parts) && appendConstantStringParts(binary->right, parts));
    }
    else {
#line 407 "/src/emitter-expr-ops.do"
            return false;
    }
    }
    doof::unreachable();
}
#line 411 "/src/emitter-expr-ops.do"
std::string emitMember(const std::shared_ptr<::app_src_ast_::MemberExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 412 "/src/emitter-expr-ops.do"
    const auto object = ::app_src_emitter_expr_::emitExpression(expression->object, context, std::monostate{});
#line 413 "/src/emitter-expr-ops.do"
    auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object);
#line 414 "/src/emitter-expr-ops.do"
    if (!doof::is_null(objectType)) {
#line 415 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = doof::unwrap_optional(objectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
#line 417 "/src/emitter-expr-ops.do"
                if (expression->optional || expression->force) {
#line 417 "/src/emitter-expr-ops.do"
                    return emitWeakFieldAccess(expression, object, context);
                }
        }
        else {
        }
        }
    }
#line 422 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = expression->object;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
            const auto& this_ = std::get<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject);
#line 424 "/src/emitter-expr-ops.do"
            auto nativeOwner = false;
#line 425 "/src/emitter-expr-ops.do"
            if (!doof::is_null(this_->resolvedType)) {
#line 426 "/src/emitter-expr-ops.do"
                {
                    auto _case_subject = doof::unwrap_optional(this_->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 427 "/src/emitter-expr-ops.do"
                        (nativeOwner = class_->symbol->native_);
                }
                else {
                }
                }
            }
#line 431 "/src/emitter-expr-ops.do"
            return (std::string("this->") + (nativeOwner ? expression->property : cppIdentifier(expression->property)));
    }
    else {
    }
    }
#line 435 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = expression->object;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 437 "/src/emitter-expr-ops.do"
            if (((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->casePattern != std::string(""))) && ((expression->property == std::string("value")) || (expression->property == std::string("error")))) {
#line 438 "/src/emitter-expr-ops.do"
                return ((object + std::string(".")) + cppIdentifier(expression->property));
            }
    }
    else {
    }
    }
#line 443 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = expression->object;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 445 "/src/emitter-expr-ops.do"
            const auto& _iterable_20 = context->namespaceImports;
            for (const auto& namespace_ : *_iterable_20) {
#line 446 "/src/emitter-expr-ops.do"
                if (namespace_->localName == identifier->name) {
#line 447 "/src/emitter-expr-ops.do"
                    return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(namespace_->sourceModule)) + std::string("::")) + cppIdentifier(expression->property));
                }
            }
    }
    else {
    }
    }
#line 453 "/src/emitter-expr-ops.do"
    const auto staticObjectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object);
#line 454 "/src/emitter-expr-ops.do"
    if (!doof::is_null(staticObjectType)) {
#line 455 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = doof::unwrap_optional(staticObjectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 457 "/src/emitter-expr-ops.do"
                const auto specialized = ::app_src_emitter_types_::specializeEmitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter), context);
#line 458 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("metadata")) {
#line 458 "/src/emitter-expr-ops.do"
                    return ((std::string("doof::metadata_for_type<") + ::app_src_emitter_types_::emitType(specialized, context->modulePath)) + std::string(">()"));
                }
#line 459 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("fromJsonValue")) {
#line 460 "/src/emitter-expr-ops.do"
                    {
                        auto _case_subject = specialized;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 461 "/src/emitter-expr-ops.do"
                            return (::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(concrete), context->modulePath) + std::string("::element_type::fromJsonValue"));
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                            const auto& unresolved = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 462 "/src/emitter-expr-ops.do"
                            return (cppIdentifier(unresolved->name) + std::string("::element_type::fromJsonValue"));
                    }
                    else {
                    }
                    }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 468 "/src/emitter-expr-ops.do"
                if (!doof::is_null(expression->resolvedStaticOwner)) {
#line 469 "/src/emitter-expr-ops.do"
                    const auto owner = doof::unwrap_optional(expression->resolvedStaticOwner);
#line 470 "/src/emitter-expr-ops.do"
                    auto ownerName = owner->name;
#line 471 "/src/emitter-expr-ops.do"
                    if (owner->native_) {
#line 472 "/src/emitter-expr-ops.do"
                        (ownerName = (std::string("::") + ((owner->nativeCppName == std::string("")) ? owner->name : owner->nativeCppName)));
                    } else if (((!doof::is_null(owner->resolvedSymbol)) && (owner->resolvedSymbol->module != context->modulePath)) && (context->modulePath != std::string(""))) {
#line 474 "/src/emitter-expr-ops.do"
                        (ownerName = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(owner->resolvedSymbol->module)) + std::string("::")) + owner->name));
                    }
#line 476 "/src/emitter-expr-ops.do"
                    return ((ownerName + std::string("::")) + ((expression->property == std::string("metadata")) ? std::string("_metadata") : (owner->native_ ? expression->property : cppIdentifier(expression->property))));
                }
        }
        else {
        }
        }
    }
#line 485 "/src/emitter-expr-ops.do"
    if (!doof::is_null(staticObjectType)) {
#line 486 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = doof::unwrap_optional(staticObjectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 488 "/src/emitter-expr-ops.do"
                const auto memberName = (class_->symbol->native_ ? expression->property : cppIdentifier(expression->property));
#line 489 "/src/emitter-expr-ops.do"
                return ((object + ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"))) + memberName);
        }
        else {
        }
        }
    }
#line 494 "/src/emitter-expr-ops.do"
    auto callableMember = false;
#line 495 "/src/emitter-expr-ops.do"
    if (!doof::is_null(expression->resolvedType)) {
#line 496 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
#line 497 "/src/emitter-expr-ops.do"
                (callableMember = true);
        }
        else {
        }
        }
    }
#line 501 "/src/emitter-expr-ops.do"
    if ((!callableMember && (!doof::is_null(staticObjectType))) && ::app_src_emitter_types_::usesVariantRepresentation(doof::unwrap_optional(staticObjectType))) {
#line 502 "/src/emitter-expr-ops.do"
        return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + cppIdentifier(expression->property)) + std::string("; }, ")) + ::app_src_emitter_expr_utils_::variantVisitValue(object, doof::unwrap_optional(staticObjectType))) + std::string(")"));
    }
#line 504 "/src/emitter-expr-ops.do"
    if (expression->property == std::string("push")) {
#line 504 "/src/emitter-expr-ops.do"
        return (object + std::string("->push_back"));
    }
#line 505 "/src/emitter-expr-ops.do"
    if ((expression->property == std::string("value")) && doof::string_contains(object, std::string("::"))) {
#line 505 "/src/emitter-expr-ops.do"
        return ((std::string("static_cast<int32_t>(") + object) + std::string(")"));
    }
#line 506 "/src/emitter-expr-ops.do"
    (objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object));
#line 507 "/src/emitter-expr-ops.do"
    if (!doof::is_null(objectType)) {
#line 508 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = doof::unwrap_optional(objectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 509 "/src/emitter-expr-ops.do"
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
#line 510 "/src/emitter-expr-ops.do"
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 511 "/src/emitter-expr-ops.do"
                return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + cppIdentifier(expression->property)) + std::string("; }, ")) + object) + std::string(")"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
#line 512 "/src/emitter-expr-ops.do"
                return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + cppIdentifier(expression->property)) + std::string("; }, ")) + object) + std::string(")"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 513 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("length")) {
#line 513 "/src/emitter-expr-ops.do"
                    return ((std::string("static_cast<int32_t>((") + object) + std::string(")->size())"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 514 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("size")) {
#line 514 "/src/emitter-expr-ops.do"
                    return (object + std::string("->size()"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
#line 515 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("size")) {
#line 515 "/src/emitter-expr-ops.do"
                    return (object + std::string("->size()"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
#line 517 "/src/emitter-expr-ops.do"
                if ((expression->property == std::string("lowerBound")) || (expression->property == std::string("upperBound"))) {
#line 517 "/src/emitter-expr-ops.do"
                    return ((object + std::string(".")) + expression->property);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 520 "/src/emitter-expr-ops.do"
                if ((primitive->name == std::string("string")) && (expression->property == std::string("length"))) {
#line 520 "/src/emitter-expr-ops.do"
                    return ((std::string("static_cast<int32_t>(") + object) + std::string(".size())"));
                }
#line 521 "/src/emitter-expr-ops.do"
                if ((primitive->name == std::string("string")) && (expression->property == std::string("toLowerCase"))) {
#line 521 "/src/emitter-expr-ops.do"
                    return std::string("doof::string_toLowerCase");
                }
#line 522 "/src/emitter-expr-ops.do"
                if ((primitive->name == std::string("string")) && (expression->property == std::string("toUpperCase"))) {
#line 522 "/src/emitter-expr-ops.do"
                    return std::string("doof::string_toUpperCase");
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 525 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("value")) {
#line 525 "/src/emitter-expr-ops.do"
                    return ((std::string("doof::success_value(") + object) + std::string(")"));
                }
#line 526 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("error")) {
#line 526 "/src/emitter-expr-ops.do"
                    return ((std::string("doof::failure_error(") + object) + std::string(")"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>>(_case_subject)) {
#line 528 "/src/emitter-expr-ops.do"
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>(_case_subject)) {
#line 529 "/src/emitter-expr-ops.do"
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
                const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 531 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("value")) {
#line 531 "/src/emitter-expr-ops.do"
                    return ((std::string("static_cast<int32_t>(") + object) + std::string(")"));
                }
#line 532 "/src/emitter-expr-ops.do"
                if (expression->property == std::string("name")) {
#line 532 "/src/emitter-expr-ops.do"
                    return (((::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context->modulePath) + std::string("_name(")) + object) + std::string(")"));
                }
#line 533 "/src/emitter-expr-ops.do"
                return ((object + std::string("::")) + cppIdentifier(expression->property));
        }
        else {
        }
        }
    }
#line 538 "/src/emitter-expr-ops.do"
    return ((object + std::string("->")) + cppIdentifier(expression->property));
}
#line 541 "/src/emitter-expr-ops.do"
std::string emitWeakFieldAccess(const std::shared_ptr<::app_src_ast_::MemberExpression>& expression, const std::string& object, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 542 "/src/emitter-expr-ops.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 543 "/src/emitter-expr-ops.do"
    const auto storage = (std::string("_weak_storage_") + doof::to_string(context->tryCounter));
#line 544 "/src/emitter-expr-ops.do"
    const auto temporary = (std::string("_weak_value_") + doof::to_string(context->tryCounter));
#line 545 "/src/emitter-expr-ops.do"
    auto nullable = false;
#line 546 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = doof::unwrap_optional(::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object));
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 547 "/src/emitter-expr-ops.do"
            (nullable = weakTargetAllowsNone(weak_->inner));
    }
    else {
    }
    }
#line 550 "/src/emitter-expr-ops.do"
    const auto weakValue = (nullable ? (storage + std::string(".value()")) : storage);
#line 551 "/src/emitter-expr-ops.do"
    auto access = ((temporary + std::string("->")) + cppIdentifier(expression->property));
#line 552 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = doof::unwrap_optional(::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object));
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 554 "/src/emitter-expr-ops.do"
            if (weakTargetUsesVariant(weak_->inner)) {
#line 555 "/src/emitter-expr-ops.do"
                (access = ((((std::string("std::visit([](auto&& _weak_item) { return _weak_item->") + cppIdentifier(expression->property)) + std::string("; }, ")) + temporary) + std::string(")")));
            }
    }
    else {
    }
    }
#line 560 "/src/emitter-expr-ops.do"
    if (expression->force) {
#line 561 "/src/emitter-expr-ops.do"
        const auto resultType = ::app_src_emitter_types_::emitType(doof::unwrap_optional(expression->resolvedType), context->modulePath);
#line 562 "/src/emitter-expr-ops.do"
        const auto noneCheck = (nullable ? ((std::string("if (!") + storage) + std::string(".has_value()) doof::panic(\"Weak reference is none\"); ")) : std::string(""));
#line 563 "/src/emitter-expr-ops.do"
        return ((((((((((((((std::string("[&]() -> ") + resultType) + std::string(" { auto ")) + storage) + std::string(" = ")) + object) + std::string("; ")) + noneCheck) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); return ")) + access) + std::string("; }()"));
    }
#line 565 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 567 "/src/emitter-expr-ops.do"
            const auto resultCpp = ::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result), context->modulePath);
#line 568 "/src/emitter-expr-ops.do"
            const auto payloadCpp = ::app_src_emitter_types_::emitResultPayloadType(result->valueType, context->modulePath);
#line 569 "/src/emitter-expr-ops.do"
            const auto errorCpp = ::app_src_emitter_types_::emitResultPayloadType(result->errorType, context->modulePath);
#line 570 "/src/emitter-expr-ops.do"
            const auto failure = weakFailureValue(result->errorType, errorCpp, context);
#line 571 "/src/emitter-expr-ops.do"
            const auto noneReturn = (nullable ? ((((((std::string("if (!") + storage) + std::string(".has_value()) return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{}}; ")) : std::string(""));
#line 572 "/src/emitter-expr-ops.do"
            return ((((((((((((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto ")) + storage) + std::string(" = ")) + object) + std::string("; ")) + noneReturn) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) return doof::Failure<")) + errorCpp) + std::string(">{")) + failure) + std::string("}; auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{")) + access) + std::string("}}; }()"));
    }
    else {
#line 574 "/src/emitter-expr-ops.do"
            doof::panic(std::string("Optional weak field access must resolve to Result"));
    }
    }
    doof::unreachable();
#line 576 "/src/emitter-expr-ops.do"
    return std::string("");
}
#line 579 "/src/emitter-expr-ops.do"
bool weakTargetAllowsNone(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 580 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 581 "/src/emitter-expr-ops.do"
            const auto& _iterable_22 = union_->types;
            for (const auto& member : *_iterable_22) {
#line 581 "/src/emitter-expr-ops.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 581 "/src/emitter-expr-ops.do"
                    return true;
                }
            }
    }
    else {
    }
    }
#line 584 "/src/emitter-expr-ops.do"
    return false;
}
#line 587 "/src/emitter-expr-ops.do"
bool weakTargetUsesVariant(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 588 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 590 "/src/emitter-expr-ops.do"
            auto present = 0;
#line 591 "/src/emitter-expr-ops.do"
            const auto& _iterable_24 = union_->types;
            for (const auto& member : *_iterable_24) {
#line 591 "/src/emitter-expr-ops.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 591 "/src/emitter-expr-ops.do"
                    (present = (present + 1));
                }
            }
#line 592 "/src/emitter-expr-ops.do"
            return (present > 1);
    }
    else {
    }
    }
#line 596 "/src/emitter-expr-ops.do"
    return false;
}
#line 599 "/src/emitter-expr-ops.do"
std::string weakFailureValue(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& errorType, const std::string& errorCpp, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 600 "/src/emitter-expr-ops.do"
    {
        auto _case_subject = errorType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
#line 601 "/src/emitter-expr-ops.do"
            return (errorCpp + std::string("{::doof::WeakReferenceError{}}"));
    }
    else {
    }
    }
#line 604 "/src/emitter-expr-ops.do"
    return std::string("::doof::WeakReferenceError{}");
}
#line 607 "/src/emitter-expr-ops.do"
std::string emitIndex(const std::shared_ptr<::app_src_ast_::IndexExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 608 "/src/emitter-expr-ops.do"
    const auto object = ::app_src_emitter_expr_::emitExpression(expression->object, context, std::monostate{});
#line 609 "/src/emitter-expr-ops.do"
    const auto index = ::app_src_emitter_expr_::emitExpression(expression->index, context, std::monostate{});
#line 610 "/src/emitter-expr-ops.do"
    const auto sourcePath = ::app_src_emitter_expr_literals_::quote(::app_src_emitter_names_::moduleDiagnosticPath(context->modulePath, true));
#line 611 "/src/emitter-expr-ops.do"
    const auto sourceLine = doof::to_string(expression->span.start.line);
#line 612 "/src/emitter-expr-ops.do"
    const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object);
#line 613 "/src/emitter-expr-ops.do"
    if (!doof::is_null(objectType)) {
#line 614 "/src/emitter-expr-ops.do"
        {
            auto _case_subject = doof::unwrap_optional(objectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 615 "/src/emitter-expr-ops.do"
                return ((((((((std::string("doof::array_at(") + object) + std::string(", ")) + index) + std::string(", ")) + sourcePath) + std::string(", ")) + sourceLine) + std::string(")"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 616 "/src/emitter-expr-ops.do"
                return ((((((((std::string("doof::map_at(") + object) + std::string(", ")) + index) + std::string(", ")) + sourcePath) + std::string(", ")) + sourceLine) + std::string(")"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 618 "/src/emitter-expr-ops.do"
                if (primitive->name == std::string("string")) {
#line 618 "/src/emitter-expr-ops.do"
                    return ((((((((std::string("doof::string_at(") + object) + std::string(", ")) + index) + std::string(", ")) + sourcePath) + std::string(", ")) + sourceLine) + std::string(")"));
                }
        }
        else {
        }
        }
    }
#line 623 "/src/emitter-expr-ops.do"
    return (((object + std::string("[")) + index) + std::string("]"));
}
#line 1 "<doof-generated>"
}
