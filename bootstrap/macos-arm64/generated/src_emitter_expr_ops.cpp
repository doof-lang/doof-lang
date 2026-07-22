#include "src_emitter_expr_ops.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_expr_utils.hpp"
#include "src_emitter_types.hpp"
#include "src_checker_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_expr_ops_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_checker_types_;
std::string emitAs(std::shared_ptr<::app_src_ast_::AsExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto sourceType = ::app_src_emitter_expr_utils_::requireExpressionType(expression->expression, std::string("as source"));
    const auto resultType = ::app_src_emitter_expr_utils_::requireExpressionType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), std::string("as expression"));
    {
        auto _case_subject = resultType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            const auto target = result->valueType;
            const auto resultCpp = ::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result), context->modulePath);
            const auto targetCpp = ::app_src_emitter_types_::emitType(target, context->modulePath);
            const auto success = ((std::string("doof::Success<") + targetCpp) + std::string(">"));
            const auto failure = ((std::string("doof::Failure<") + ::app_src_emitter_types_::emitType(result->errorType, context->modulePath)) + std::string(">"));
            const auto source = ::app_src_emitter_expr_::emitExpression(expression->expression, context, std::monostate{});
            if (::app_src_checker_types_::sameType(sourceType, target)) {
                return (((success + std::string("{")) + source) + std::string("}"));
            }
            {
                auto _case_subject = sourceType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& sourceResult = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                    auto narrowed = std::string("");
                    {
                        auto _case_subject = sourceResult->valueType;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                            (narrowed = emitJsonAs(std::string("doof::success_value(_as_source)"), target, resultCpp, success, failure));
                    }
                    else {
                    }
                    }
                    if (narrowed != std::string("")) {
                        auto errorValue = std::string("doof::failure_error(_as_source)");
                        if (!::app_src_checker_types_::sameType(sourceResult->errorType, result->errorType)) {
                            (errorValue = ((((std::string("doof::variant_promote<") + ::app_src_emitter_types_::emitType(result->errorType, context->modulePath)) + std::string(">(")) + errorValue) + std::string(")")));
                        }
                        return ((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_source = ")) + source) + std::string("; if (doof::is_failure(_as_source)) return ")) + failure) + std::string("{")) + errorValue) + std::string("}; return ")) + narrowed) + std::string("; }()"));
                    }
            }
            else {
            }
            }
            if (::app_src_checker_types_::isNumeric(sourceType) && ::app_src_checker_types_::isNumeric(target)) {
                return ((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_checked = doof::checked_numeric_as<")) + targetCpp) + std::string(">(")) + source) + std::string("); if (_as_checked.has_value()) return ")) + success) + std::string("{_as_checked.value()}; return ")) + failure) + std::string("{\"Numeric narrowing failed\"}; }()"));
            }
            {
                auto _case_subject = sourceType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                    return emitJsonAs(source, target, resultCpp, success, failure);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
                    {
                        auto _case_subject = target;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (std::holds_alternative<")) + targetCpp) + std::string(">(_as_value)) return ")) + success) + std::string("{std::get<")) + targetCpp) + std::string(">(_as_value)}; return ")) + failure) + std::string("{\"Interface narrowing failed\"}; }()"));
                    }
                    else {
                    }
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                    const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                    if (unionContainsJsonValue(union_)) {
                        const auto narrowedJson = std::string("std::get<doof::JsonValue>(_as_nullable)");
                        const auto jsonNarrowing = emitJsonAs(narrowedJson, target, resultCpp, success, failure);
                        return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_nullable = ")) + source) + std::string("; if (doof::is_null(_as_nullable)) return ")) + failure) + std::string("{\"JsonValue narrowing failed\"}; return ")) + jsonNarrowing) + std::string("; }()"));
                    }
                    const auto member = ::app_src_emitter_types_::naturalNullableUnionMember(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
                    if (!doof::is_null(member)) {
                        if (::app_src_checker_types_::sameType(doof::unwrap_optional(member), target)) {
                            {
                                auto _case_subject = target;
                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                                    return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (_as_value) return ")) + success) + std::string("{_as_value}; return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; }()"));
                            }
                            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                                    return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (_as_value) return ")) + success) + std::string("{_as_value}; return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; }()"));
                            }
                            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                                    return ((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (_as_value.has_value()) return ")) + success) + std::string("{_as_value.value()}; return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; }()"));
                            }
                            else {
                            }
                            }
                        }
                        if (::app_src_checker_types_::isNumeric(doof::unwrap_optional(member)) && ::app_src_checker_types_::isNumeric(target)) {
                            return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (!_as_value.has_value()) return ")) + failure) + std::string("{\"Nullable narrowing failed\"}; auto _as_checked = doof::checked_numeric_as<")) + targetCpp) + std::string(">(_as_value.value()); if (_as_checked.has_value()) return ")) + success) + std::string("{_as_checked.value()}; return ")) + failure) + std::string("{\"Numeric narrowing failed\"}; }()"));
                        }
                    }
                    return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (doof::variant_is<")) + targetCpp) + std::string(">(_as_value)) return ")) + success) + std::string("{doof::variant_narrow<")) + targetCpp) + std::string(">(_as_value)}; return ")) + failure) + std::string("{\"Union narrowing failed\"}; }()"));
            }
            else {
            }
            }
            return (failure + std::string("{\"Unsupported narrowing\"}"));
    }
    else {
            doof::panic(std::string("as expression must resolve to Result"));
    }
    }
    return std::string("");
}
bool unionContainsJsonValue(std::shared_ptr<::app_src_semantic_::UnionResolvedType> union_) {
    const auto& _iterable_1 = union_->types;
    for (const auto& member : *_iterable_1) {
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                return true;
        }
        else {
        }
        }
    }
    return false;
}
std::string emitJsonAs(std::string source, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> target, std::string resultCpp, std::string success, std::string failure) {
    auto condition = std::string("true");
    auto value = source;
    {
        auto _case_subject = target;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            if (primitive->name == std::string("bool")) {
                (condition = std::string("doof::json_is_boolean(_as_value)"));
                (value = std::string("doof::json_as_bool(_as_value)"));
            } else if (primitive->name == std::string("string")) {
                (condition = std::string("doof::json_is_string(_as_value)"));
                (value = std::string("doof::json_as_string(_as_value)"));
            } else if (primitive->name == std::string("int")) {
                (condition = std::string("doof::json_is_number(_as_value)"));
                (value = std::string("doof::json_as_int(_as_value)"));
            } else if (primitive->name == std::string("long")) {
                (condition = std::string("doof::json_is_number(_as_value)"));
                (value = std::string("doof::json_as_long(_as_value)"));
            } else if (primitive->name == std::string("float")) {
                (condition = std::string("doof::json_is_number(_as_value)"));
                (value = std::string("doof::json_as_float(_as_value)"));
            } else if (primitive->name == std::string("double")) {
                (condition = std::string("doof::json_is_number(_as_value)"));
                (value = std::string("doof::json_as_double(_as_value)"));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            (condition = std::string("doof::json_is_array(_as_value)"));
            (value = std::string("std::get<doof::JsonArray>(doof::json_storage(_as_value))"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            (condition = std::string("doof::json_is_object(_as_value)"));
            (value = std::string("doof::json_object(_as_value)"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            (value = std::string("_as_value"));
    }
    else {
    }
    }
    return ((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto _as_value = ")) + source) + std::string("; if (")) + condition) + std::string(") return ")) + success) + std::string("{")) + value) + std::string("}; return ")) + failure) + std::string("{\"JsonValue narrowing failed\"}; }()"));
}
std::string emitAssignment(std::shared_ptr<::app_src_ast_::AssignmentExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto operator_ = ((expression->operator_ == std::string("\\=")) ? std::string("/=") : expression->operator_);
    const auto targetType = std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->target);
    const auto value = ::app_src_emitter_expr_::emitExpression(expression->value, context, targetType);
    return ((((((std::string("(") + emitAssignmentTarget(expression->target, context)) + std::string(" ")) + operator_) + std::string(" ")) + value) + std::string(")"));
}
std::string emitAssignmentTarget(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> target, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = target;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
            if ((!doof::is_null(objectType)) && isVariantCarrier(doof::unwrap_optional(objectType))) {
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                return ((((std::string("std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->") + cppIdentifier(member->property)) + std::string("); }, ")) + ::app_src_emitter_expr_utils_::variantVisitValue(object, doof::unwrap_optional(objectType))) + std::string(")"));
            }
    }
    else {
    }
    }
    return ::app_src_emitter_expr_::emitExpression(target, context, std::monostate{});
}
bool isVariantCarrier(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType) {
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            auto nonNull = 0;
            const auto& _iterable_2 = union_->types;
            for (const auto& member : *_iterable_2) {
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
                    (nonNull = (nonNull + 1));
                }
            }
            return (nonNull > 1);
    }
    else {
    }
    }
    return false;
}
std::string emitIdentifier(std::shared_ptr<::app_src_ast_::Identifier> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (((!doof::is_null(expression->resolvedBinding)) && (expression->resolvedBinding->kind == std::string("field"))) && !context->currentFunctionStatic) {
        return (std::string("this->") + cppIdentifier(expression->name));
    }
    const auto& _iterable_3 = context->imports;
    for (const auto& imported : *_iterable_3) {
        if ((imported->localName == expression->name) && (!doof::is_null(imported->symbol))) {
            if (imported->symbol->native_) {
                return (std::string("::") + ((imported->symbol->nativeCppName == std::string("")) ? imported->symbol->name : imported->symbol->nativeCppName));
            }
            return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(imported->symbol->module)) + std::string("::")) + cppIdentifier(::app_src_emitter_expr_utils_::emittedSymbolName(doof::unwrap_optional(imported->symbol))));
        }
    }
    if ((!doof::is_null(expression->resolvedBinding)) && (!doof::is_null(expression->resolvedBinding->symbol))) {
        const auto symbol = doof::unwrap_optional(expression->resolvedBinding->symbol);
        if (symbol->native_) {
            return (std::string("::") + ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName));
        }
        if (((context->modulePath != std::string("")) && (symbol->module != std::string(""))) && (symbol->module != context->modulePath)) {
            return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(symbol->module)) + std::string("::")) + cppIdentifier(::app_src_emitter_expr_utils_::emittedSymbolName(symbol)));
        }
    }
    if ((!doof::is_null(expression->resolvedBinding)) && (expression->resolvedBinding->kind == std::string("import"))) {
        const auto& _iterable_4 = context->imports;
        for (const auto& imported : *_iterable_4) {
            if ((imported->localName == expression->name) && (!doof::is_null(imported->symbol))) {
                return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(imported->symbol->module)) + std::string("::")) + cppIdentifier(::app_src_emitter_expr_utils_::emittedSymbolName(doof::unwrap_optional(imported->symbol))));
            }
        }
    }
    if (((!doof::is_null(expression->resolvedBinding)) && expression->resolvedBinding->mutable_) && ::app_src_emitter_context_::isCapturedMutable(context, expression->name)) {
        return ((std::string("(*") + cppIdentifier(expression->name)) + std::string(")"));
    }
    return cppIdentifier(expression->name);
}
std::string cppIdentifier(std::string name) {
    if (name == std::string("operator")) {
        return std::string("operator_");
    }
    if (name == std::string("mutable")) {
        return std::string("mutable_");
    }
    if (name == std::string("class")) {
        return std::string("class_");
    }
    if (name == std::string("struct")) {
        return std::string("struct_");
    }
    if (name == std::string("namespace")) {
        return std::string("namespace_");
    }
    if (name == std::string("template")) {
        return std::string("template_");
    }
    if (name == std::string("typename")) {
        return std::string("typename_");
    }
    if (name == std::string("union")) {
        return std::string("union_");
    }
    if (name == std::string("char")) {
        return std::string("char_");
    }
    if (name == std::string("short")) {
        return std::string("short_");
    }
    if (name == std::string("delete")) {
        return std::string("delete_");
    }
    return name;
}
std::string emitUnary(std::shared_ptr<::app_src_ast_::UnaryExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if ((expression->operator_ == std::string("try!")) || (expression->operator_ == std::string("try?"))) {
        const auto operand = ::app_src_emitter_expr_::emitExpression(expression->operand, context, std::monostate{});
        const auto operandType = ::app_src_emitter_expr_utils_::requireExpressionType(expression->operand, (expression->operator_ + std::string(" operand")));
        {
            auto _case_subject = operandType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                const auto valueType = ::app_src_emitter_types_::emitType(result->valueType, context->modulePath);
                const auto body = ((((std::string("auto _try_value = ") + operand) + std::string("; if (doof::is_failure(_try_value)) doof::panic(\"")) + expression->operator_) + std::string(" failed\"); "));
                {
                    auto _case_subject = result->valueType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                        return ((std::string("[&]() -> void { ") + body) + std::string(" }()"));
                }
                else {
                }
                }
                if (expression->operator_ == std::string("try?")) {
                    return ((((std::string("[&]() -> std::optional<") + valueType) + std::string("> { ")) + body) + std::string("return std::move(doof::success_value(_try_value)); }()"));
                }
                return ((((std::string("[&]() -> ") + valueType) + std::string(" { ")) + body) + std::string("return std::move(doof::success_value(_try_value)); }()"));
        }
        else {
                doof::panic((expression->operator_ + std::string(" operand is not a Result")));
        }
        }
    }
    const auto operand = ::app_src_emitter_expr_::emitExpression(expression->operand, context, std::monostate{});
    if (!expression->prefix && (expression->operator_ == std::string("!"))) {
        const auto operandType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->operand);
        if (!doof::is_null(operandType)) {
            {
                auto _case_subject = doof::unwrap_optional(operandType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                    const auto valueType = ::app_src_emitter_types_::emitType(result->valueType, context->modulePath);
                    const auto body = ((std::string("auto _assert_value = ") + operand) + std::string("; if (doof::is_failure(_assert_value)) doof::panic(\"! failed\"); "));
                    {
                        auto _case_subject = result->valueType;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                            return ((std::string("[&]() -> void { ") + body) + std::string("}()"));
                    }
                    else {
                    }
                    }
                    return ((((std::string("[&]() -> ") + valueType) + std::string(" { ")) + body) + std::string("return std::move(doof::success_value(_assert_value)); }()"));
            }
            else {
            }
            }
        }
        {
            auto _case_subject = expression->operand;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                return ((std::string("doof::unwrap_optional(") + operand) + std::string(")"));
        }
        else {
        }
        }
        if (!doof::is_null(operandType)) {
            {
                auto _case_subject = doof::unwrap_optional(operandType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                    const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                    if (::app_src_emitter_expr_utils_::hasSinglePrimitiveMember(union_)) {
                        return (operand + std::string(".value()"));
                    }
                    if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> nonNullMembers = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                        const auto& _iterable_5 = union_->types;
                        for (const auto& member : *_iterable_5) {
                            if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
                                nonNullMembers->push_back(member);
                            }
                        }
                        if (static_cast<int32_t>((nonNullMembers)->size()) == 1) {
                            return ((((std::string("std::get<") + ::app_src_emitter_types_::emitType((*nonNullMembers)[0], context->modulePath)) + std::string(">(")) + operand) + std::string(")"));
                        }
                    }
                    if (::app_src_emitter_expr_utils_::isNullableVariantType(operandType)) {
                        return ((std::string("doof::unwrap_optional(") + operand) + std::string(")"));
                    }
            }
            else {
            }
            }
        }
        return ((std::string("doof::unwrap_optional(") + operand) + std::string(")"));
    }
    return (binaryOperator(expression->operator_) + operand);
}
std::string binaryOperator(std::string operator_) {
    return ((operator_ == std::string("!")) ? std::string("!") : ((operator_ == std::string("-")) ? std::string("-") : ((operator_ == std::string("+")) ? std::string("+") : std::string("~"))));
}
std::string emitBinary(std::shared_ptr<::app_src_ast_::BinaryExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (expression->operator_ == std::string("..")) {
        return ((((std::string("doof::range(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
    }
    if (expression->operator_ == std::string("..<")) {
        return ((((std::string("doof::range_exclusive(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
    }
    if (expression->operator_ == std::string("??")) {
        const auto left = ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{});
        const auto right = ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{});
        return ((((((std::string("(doof::is_null(") + left) + std::string(") ? ")) + right) + std::string(" : doof::unwrap_optional(")) + left) + std::string("))"));
    }
    if (((expression->operator_ == std::string("==")) || (expression->operator_ == std::string("!="))) && (std::visit([](auto&& _obj) { return _obj->kind; }, expression->right) == std::string("none-literal"))) {
        auto test = ((std::string("doof::is_null(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(")"));
        return ((expression->operator_ == std::string("==")) ? test : ((std::string("(!") + test) + std::string(")")));
    }
    if (((expression->operator_ == std::string("==")) || (expression->operator_ == std::string("!="))) && (std::visit([](auto&& _obj) { return _obj->kind; }, expression->left) == std::string("none-literal"))) {
        auto test = ((std::string("doof::is_null(") + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
        return ((expression->operator_ == std::string("==")) ? test : ((std::string("(!") + test) + std::string(")")));
    }
    if (expression->operator_ == std::string("**")) {
        return ((((std::string("std::pow(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
    }
    const auto operator_ = ((expression->operator_ == std::string("\\")) ? std::string("/") : expression->operator_);
    return ((((((std::string("(") + ::app_src_emitter_expr_::emitExpression(expression->left, context, std::monostate{})) + std::string(" ")) + operator_) + std::string(" ")) + ::app_src_emitter_expr_::emitExpression(expression->right, context, std::monostate{})) + std::string(")"));
}
std::string emitMember(std::shared_ptr<::app_src_ast_::MemberExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto object = ::app_src_emitter_expr_::emitExpression(expression->object, context, std::monostate{});
    {
        auto _case_subject = expression->object;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
            return (std::string("this->") + cppIdentifier(expression->property));
    }
    else {
    }
    }
    {
        auto _case_subject = expression->object;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->casePattern != std::string(""))) && ((expression->property == std::string("value")) || (expression->property == std::string("error")))) {
                return ((object + std::string(".")) + cppIdentifier(expression->property));
            }
    }
    else {
    }
    }
    {
        auto _case_subject = expression->object;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            const auto& _iterable_6 = context->namespaceImports;
            for (const auto& namespace_ : *_iterable_6) {
                if (namespace_->localName == identifier->name) {
                    return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(namespace_->sourceModule)) + std::string("::")) + cppIdentifier(expression->property));
                }
            }
    }
    else {
    }
    }
    const auto staticObjectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object);
    if (!doof::is_null(staticObjectType)) {
        {
            auto _case_subject = doof::unwrap_optional(staticObjectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
                const auto specialized = ::app_src_emitter_types_::specializeEmitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter), context);
                if (expression->property == std::string("metadata")) {
                    return ((std::string("doof::metadata_for_type<") + ::app_src_emitter_types_::emitType(specialized, context->modulePath)) + std::string(">()"));
                }
                if (expression->property == std::string("fromJsonValue")) {
                    {
                        auto _case_subject = specialized;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            return (::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(concrete), context->modulePath) + std::string("::element_type::fromJsonValue"));
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                            const auto& unresolved = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
                            return (cppIdentifier(unresolved->name) + std::string("::element_type::fromJsonValue"));
                    }
                    else {
                    }
                    }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                if (!doof::is_null(expression->resolvedStaticOwner)) {
                    const auto owner = doof::unwrap_optional(expression->resolvedStaticOwner);
                    auto ownerName = owner->name;
                    if (owner->native_) {
                        (ownerName = (std::string("::") + ((owner->nativeCppName == std::string("")) ? owner->name : owner->nativeCppName)));
                    } else if (((!doof::is_null(owner->resolvedSymbol)) && (owner->resolvedSymbol->module != context->modulePath)) && (context->modulePath != std::string(""))) {
                        (ownerName = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(owner->resolvedSymbol->module)) + std::string("::")) + owner->name));
                    }
                    return ((ownerName + std::string("::")) + ((expression->property == std::string("metadata")) ? std::string("_metadata") : cppIdentifier(expression->property)));
                }
        }
        else {
        }
        }
    }
    if (!doof::is_null(staticObjectType)) {
        {
            auto _case_subject = doof::unwrap_optional(staticObjectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                return ((object + ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"))) + cppIdentifier(expression->property));
        }
        else {
        }
        }
    }
    auto callableMember = false;
    if (!doof::is_null(expression->resolvedType)) {
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                (callableMember = true);
        }
        else {
        }
        }
    }
    if ((!callableMember && (!doof::is_null(staticObjectType))) && ::app_src_emitter_types_::usesVariantRepresentation(doof::unwrap_optional(staticObjectType))) {
        return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + cppIdentifier(expression->property)) + std::string("; }, ")) + ::app_src_emitter_expr_utils_::variantVisitValue(object, doof::unwrap_optional(staticObjectType))) + std::string(")"));
    }
    if (expression->property == std::string("push")) {
        return (object + std::string("->push_back"));
    }
    if ((expression->property == std::string("value")) && doof::string_contains(object, std::string("::"))) {
        return ((std::string("static_cast<int32_t>(") + object) + std::string(")"));
    }
    const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object);
    if (!doof::is_null(objectType)) {
        {
            auto _case_subject = doof::unwrap_optional(objectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + cppIdentifier(expression->property)) + std::string("; }, ")) + object) + std::string(")"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + cppIdentifier(expression->property)) + std::string("; }, ")) + object) + std::string(")"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                if (expression->property == std::string("length")) {
                    return ((std::string("static_cast<int32_t>((") + object) + std::string(")->size())"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                if (expression->property == std::string("size")) {
                    return (object + std::string("->size()"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                if (expression->property == std::string("size")) {
                    return (object + std::string("->size()"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
                if ((expression->property == std::string("lowerBound")) || (expression->property == std::string("upperBound"))) {
                    return ((object + std::string(".")) + expression->property);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
                if ((primitive->name == std::string("string")) && (expression->property == std::string("length"))) {
                    return ((std::string("static_cast<int32_t>(") + object) + std::string(".size())"));
                }
                if ((primitive->name == std::string("string")) && (expression->property == std::string("toLowerCase"))) {
                    return std::string("doof::string_toLowerCase");
                }
                if ((primitive->name == std::string("string")) && (expression->property == std::string("toUpperCase"))) {
                    return std::string("doof::string_toUpperCase");
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                if (expression->property == std::string("value")) {
                    return ((std::string("doof::success_value(") + object) + std::string(")"));
                }
                if (expression->property == std::string("error")) {
                    return ((std::string("doof::failure_error(") + object) + std::string(")"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>>(_case_subject)) {
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>(_case_subject)) {
                return ((object + std::string(".")) + cppIdentifier(expression->property));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
                const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
                if (expression->property == std::string("value")) {
                    return ((std::string("static_cast<int32_t>(") + object) + std::string(")"));
                }
                return ((object + std::string("::")) + cppIdentifier(expression->property));
        }
        else {
        }
        }
    }
    return ((object + std::string("->")) + cppIdentifier(expression->property));
}
std::string emitIndex(std::shared_ptr<::app_src_ast_::IndexExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto object = ::app_src_emitter_expr_::emitExpression(expression->object, context, std::monostate{});
    const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression->object);
    if (!doof::is_null(objectType)) {
        {
            auto _case_subject = doof::unwrap_optional(objectType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                return ((((std::string("(*") + object) + std::string(")[")) + ::app_src_emitter_expr_::emitExpression(expression->index, context, std::monostate{})) + std::string("]"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                return ((((std::string("(*") + object) + std::string(")[")) + ::app_src_emitter_expr_::emitExpression(expression->index, context, std::monostate{})) + std::string("]"));
        }
        else {
        }
        }
    }
    return (((object + std::string("[")) + ::app_src_emitter_expr_::emitExpression(expression->index, context, std::monostate{})) + std::string("]"));
}
}
