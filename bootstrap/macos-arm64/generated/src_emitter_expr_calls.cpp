#include "src_emitter_expr_calls.hpp"

namespace app_src_emitter_expr_calls_ {
using namespace ::app_src_emitter_construction_;
using namespace ::app_src_emitter_call_arguments_;
using namespace ::app_src_emitter_carriers_;
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_expr_actor_;
std::string emitCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                        if (member->optional || member->force) {
                            return emitWeakMemberCall(expression, member, context);
                        }
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (isBuiltinIdentifier(identifier, std::string("catchPanic")) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                {
                    auto _case_subject = doof::unwrap_optional(expression->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                        const auto callback = ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 36)->value, context, std::monostate{});
                        const auto successType = ::app_src_emitter_types_::emitResultPayloadType(result->valueType, context->modulePath);
                        if (std::visit([](auto&& _obj) { return _obj->kind; }, result->valueType) == std::string("none")) {
                            return ((std::string("[&]() -> doof::Result<void, std::string> { try { ") + callback) + std::string(".call(); return doof::Success<void>{}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"));
                        }
                        return ((((((std::string("[&]() -> doof::Result<") + successType) + std::string(", std::string> { try { return doof::Success<")) + successType) + std::string(">{")) + callback) + std::string(".call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"));
                }
                else {
                        doof::panic(std::string("catchPanic has no Result type"));
                }
                }
                doof::unreachable();
            }
    }
    else {
    }
    }
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (((identifier->name == std::string("Success")) || (identifier->name == std::string("Failure"))) && isBuiltinIdentifier(identifier, identifier->name)) {
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resultType = std::monostate{};
                if (!doof::is_null(expected)) {
                    static_cast<void>((resultType = doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(expected))));
                } else if (!doof::is_null(expression->resolvedType)) {
                    static_cast<void>((resultType = doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(expression->resolvedType))));
                }
                if (doof::is_null(resultType)) {
                    doof::panic((identifier->name + std::string(" has no expected Result type")));
                }
                {
                    auto _case_subject = doof::unwrap_optional(resultType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                        if (static_cast<int32_t>((expression->args)->size()) == 0) {
                            return ((((std::string("doof::") + identifier->name) + std::string("<")) + ::app_src_emitter_types_::emitContextReturnType([&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (identifier->name == std::string("Success")) { return result->valueType; } return result->errorType; }(), context)) + std::string(">{}"));
                        }
                        const auto valueType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (identifier->name == std::string("Success")) { return result->valueType; } return result->errorType; }();
                        const auto value = ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 60)->value, context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(valueType));
                        const auto payloadType = ::app_src_emitter_types_::emitContextReturnType(valueType, context);
                        return ((((((std::string("doof::") + identifier->name) + std::string("<")) + payloadType) + std::string(">{ ")) + value) + std::string(" }"));
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                        const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
                        return ::app_src_emitter_expr_actor_::emitSyncActorCall(expression, member, actor, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& resultType = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                        if (member->property == std::string("isSuccess")) {
                            return ((std::string("doof::is_success(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
                        if (member->property == std::string("isFailure")) {
                            return ((std::string("doof::is_failure(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
                        if ((member->property == std::string("unwrapOr")) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                            const auto temporaryName = (std::string("_result_unwrap_") + doof::to_string(context->tryCounter));
                            static_cast<void>((context->tryCounter += 1));
                            const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                            const auto fallback = ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 82)->value, context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(resultType->valueType));
                            return ((((((((((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(resultType->valueType, context->modulePath)) + std::string(" { auto ")) + temporaryName) + std::string(" = ")) + object) + std::string("; if (doof::is_failure(")) + temporaryName) + std::string(")) return ")) + fallback) + std::string("; return std::move(doof::success_value(")) + temporaryName) + std::string(")); }()"));
                        }
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
    const auto construction = ::app_src_emitter_construction_::emitClassCall(expression, context);
    if (!doof::is_null(construction)) {
        return construction.value();
    }
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            auto arrayObjectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
            if (!doof::is_null(arrayObjectType)) {
                static_cast<void>((arrayObjectType = doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_emitter_types_::specializeEmitType(doof::unwrap_optional(arrayObjectType), context))));
                if (member->force) {
                    const auto forcedType = ::app_src_emitter_types_::naturalNullableUnionMember(doof::unwrap_optional(arrayObjectType));
                    if (!doof::is_null(forcedType)) {
                        static_cast<void>((arrayObjectType = forcedType));
                    }
                }
            }
            auto nominalReceiver = false;
            if (!doof::is_null(arrayObjectType)) {
                {
                    auto _case_subject = doof::unwrap_optional(arrayObjectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        static_cast<void>((nominalReceiver = true));
                }
                else {
                }
                }
            }
            if (member->property == std::string("length")) {
                if (!doof::is_null(arrayObjectType)) {
                    {
                        auto _case_subject = doof::unwrap_optional(arrayObjectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            return ((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"))) + std::string("length()"));
                    }
                    else {
                    }
                    }
                }
            }
            if (!doof::is_null(arrayObjectType)) {
                {
                    auto _case_subject = doof::unwrap_optional(arrayObjectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                        if (((member->property == std::string("fromJsonValue")) && doof::is_null(expression->resolvedFunction)) && !member->resolvedCallableField) {
                            return emitInterfaceJsonCall(member, expression, context);
                        }
                        return emitVariantMemberCall(member, expression, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                        return emitInterfaceCall(member, expression, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                        const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                        if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
                            return emitVariantMemberCall(member, expression, context);
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                        if (member->property == std::string("takeFirstCompleted")) {
                            return ((std::string("doof::promise_take_first_completed(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
                        if ((member->property == std::string("buildReadonly")) || (member->property == std::string("drainToReadonly"))) {
                            return ((std::string("doof::array_drainToReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneReadonly")) {
                            return ((std::string("doof::array_cloneReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneMutable")) {
                            return ((std::string("doof::array_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("contains")) {
                            return ((((std::string("doof::array_contains(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 132)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("indexOf")) {
                            return ((((std::string("doof::array_indexOf(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 133)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("some")) {
                            return ((((std::string("doof::array_some(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 134)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("every")) {
                            return ((((std::string("doof::array_every(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 135)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("filter")) {
                            return ((((std::string("doof::array_filter(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 136)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("map")) {
                            return ((((std::string("doof::array_map(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 137)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                        const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
                        if (member->property == std::string("has")) {
                            static_cast<void>((context->tryCounter = (context->tryCounter + 1)));
                            const auto temporary = (std::string("_map_has_") + doof::to_string(context->tryCounter));
                            return ((((((((((std::string("[&]() -> bool { auto ") + temporary) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string("; return ")) + temporary) + std::string("->find(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 143)->value, context, std::monostate{})) + std::string(") != ")) + temporary) + std::string("->end(); }()"));
                        }
                        if (member->property == std::string("set")) {
                            return ((((((((((std::string("doof::map_set<") + ::app_src_emitter_types_::emitContextType(map->keyType, context)) + std::string(", ")) + ::app_src_emitter_types_::emitContextType(map->valueType, context)) + std::string(">(")) + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 145)->value, context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(map->keyType))) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 145)->value, context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(map->valueType))) + std::string(", \"\", 0)"));
                        }
                        if ((member->property == std::string("get")) && (static_cast<int32_t>((expression->args)->size()) > 0)) {
                            return ((((std::string("doof::map_get(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 146)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("keys")) {
                            return ((std::string("doof::map_keys(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("values")) {
                            return ((std::string("doof::map_values(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if ((member->property == std::string("buildReadonly")) || (member->property == std::string("drainToReadonly"))) {
                            return ((std::string("doof::map_drainToReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneReadonly")) {
                            return ((std::string("doof::map_cloneReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneMutable")) {
                            return ((std::string("doof::map_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                        if (member->property == std::string("has")) {
                            return ((((std::string("(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string("->count(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 154)->value, context, std::monostate{})) + std::string(") > 0)"));
                        }
                        if (member->property == std::string("add")) {
                            return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("->insert(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 155)->value, context, std::monostate{})) + std::string(")"));
                        }
                        if (member->property == std::string("delete")) {
                            return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("->erase(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 156)->value, context, std::monostate{})) + std::string(")"));
                        }
                        if (member->property == std::string("values")) {
                            return ((std::string("doof::set_values(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if ((member->property == std::string("buildReadonly")) || (member->property == std::string("drainToReadonly"))) {
                            return ((std::string("doof::set_drainToReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneReadonly")) {
                            return ((std::string("doof::set_cloneReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneMutable")) {
                            return ((std::string("doof::set_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
                        const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
                        if ((member->property == std::string("fromName")) || (member->property == std::string("fromValue"))) {
                            const auto args = ((static_cast<int32_t>((expression->args)->size()) == 0) ? std::string("") : ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 164)->value, context, std::monostate{}));
                            return (((((::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context) + std::string("_")) + member->property) + std::string("(")) + args) + std::string(")"));
                        }
                        if (member->property == std::string("values")) {
                            return (::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context) + std::string("_values()"));
                        }
                        if (member->property == std::string("toJsonValue")) {
                            auto receiver = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                            if (member->force) {
                                static_cast<void>((receiver = ((std::string("doof::unwrap_optional(") + receiver) + std::string(")"))));
                            }
                            return (((::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context) + std::string("_toJsonValue(")) + receiver) + std::string(")"));
                        }
                        if (member->property == std::string("fromJsonValue")) {
                            auto args = std::string("");
                            for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
                                if (i > 0) {
                                    static_cast<void>((args = (args + std::string(", "))));
                                }
                                static_cast<void>((args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-calls", 177)->value, context, std::monostate{}))));
                            }
                            if (static_cast<int32_t>((expression->args)->size()) == 1) {
                                static_cast<void>((args = (args + std::string(", false"))));
                            }
                            return (((::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context) + std::string("_fromJsonValue(")) + args) + std::string(")"));
                        }
                }
                else {
                }
                }
            }
            if (!nominalReceiver && (member->property == std::string("startsWith"))) {
                return emitBuiltinCall(std::string("doof::string_startsWith"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("endsWith"))) {
                return emitBuiltinCall(std::string("doof::string_endsWith"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("substring"))) {
                return emitBuiltinCall(std::string("doof::string_substring"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("replaceAll"))) {
                return emitBuiltinCall(std::string("doof::string_replaceAll"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("contains"))) {
                return emitBuiltinCall(std::string("doof::string_contains"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("indexOf"))) {
                return emitBuiltinCall(std::string("doof::string_indexOf"), member->object, expression, context);
            }
            const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
            if (!doof::is_null(objectType)) {
                {
                    auto _case_subject = doof::unwrap_optional(objectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                        if ((member->property == std::string("slice")) && (static_cast<int32_t>((expression->args)->size()) == 2)) {
                            return ((((((std::string("doof::array_slice(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 197)->value, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 197)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else {
                }
                }
            }
            if ((!nominalReceiver && (member->property == std::string("trim"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::string_trim(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("trimStart"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::string_trimStart(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("repeat"))) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                return ((((std::string("doof::string_repeat(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 205)->value, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("slice"))) {
                return ((((std::string("doof::string_slice(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 206)->value, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("charAt"))) {
                return ((((std::string("doof::string_at(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 207)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
            }
            if (!nominalReceiver && (member->property == std::string("padStart"))) {
                const auto fill = ((static_cast<int32_t>((expression->args)->size()) > 1) ? ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 209)->value, context, std::monostate{}) : std::string("U' '"));
                return ((((((std::string("doof::string_padStart(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 210)->value, context, std::monostate{})) + std::string(", ")) + fill) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("padEnd"))) {
                const auto fill = ((static_cast<int32_t>((expression->args)->size()) > 1) ? ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 213)->value, context, std::monostate{}) : std::string("U' '"));
                return ((((((std::string("doof::string_padEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 214)->value, context, std::monostate{})) + std::string(", ")) + fill) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("trimEnd"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::string_trimEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("trimEnd"))) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                return ((((std::string("doof::string_trimEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 217)->value, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("toLowerCase"))) {
                return ((std::string("doof::string_toLowerCase(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("toUpperCase"))) {
                return ((std::string("doof::string_toUpperCase(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("split"))) {
                return ((((std::string("doof::string_split(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 220)->value, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("pop"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::array_pop(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((member->property == std::string("toJsonObject")) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
                if (!doof::is_null(objectType)) {
                    {
                        auto _case_subject = doof::unwrap_optional(objectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            if (class_->symbol->kind == std::string("struct")) {
                                return (object + std::string(".toJsonObject()"));
                            }
                    }
                    else {
                    }
                    }
                }
                return (object + std::string("->toJsonObject()"));
            }
            if ((member->property == std::string("fromJsonValue")) && (!nominalReceiver || (!doof::is_null(member->resolvedStaticOwner)))) {
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                auto args = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
                    if (i > 0) {
                        static_cast<void>((args = (args + std::string(", "))));
                    }
                    static_cast<void>((args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-calls", 238)->value, context, std::monostate{}))));
                }
                if (static_cast<int32_t>((expression->args)->size()) == 1) {
                    static_cast<void>((args = (args + std::string(", false"))));
                }
                const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
                if (!doof::is_null(objectType)) {
                    {
                        auto _case_subject = doof::unwrap_optional(objectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                            return (((object + std::string("_fromJsonValue(")) + args) + std::string(")"));
                    }
                    else {
                    }
                    }
                }
                return (((object + std::string("::fromJsonValue(")) + args) + std::string(")"));
            }
    }
    else {
    }
    }
    auto callee = ::app_src_emitter_expr_::emitExpression(expression->callee, context, std::monostate{});
    if (std::visit([](auto&& _obj) { return _obj->kind; }, expression->callee) == std::string("identifier")) {
        {
            auto _case_subject = expression->callee;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
                if (((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->kind == std::string("builtin"))) && isBuiltinName(identifier->name)) {
                    static_cast<void>((callee = builtinName(identifier->name)));
                }
        }
        else {
        }
        }
    }
    std::shared_ptr<::app_src_semantic_::FunctionType> functionType = nullptr;
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee))) {
        {
            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                static_cast<void>((functionType = resolved));
        }
        else {
        }
        }
    }
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> concreteGenericArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    const auto& _iterable_4 = expression->resolvedGenericTypeArgs;
    for (const auto& argument : *_iterable_4) {
        concreteGenericArgs->push_back(::app_src_emitter_types_::specializeEmitType(argument, context));
    }
    if ((!doof::is_null(functionType)) && (static_cast<int32_t>((concreteGenericArgs)->size()) > 0)) {
        const auto substituted = ::app_src_checker_types_::substituteTypeParams(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(functionType)), functionType->typeParams, concreteGenericArgs);
        {
            auto _case_subject = substituted;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& specialized = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                static_cast<void>((functionType = specialized));
        }
        else {
        }
        }
    }
    const auto functionDeclaration = expression->resolvedFunction;
    auto usesConcreteInstantiation = false;
    if ((!doof::is_null(functionDeclaration)) && (static_cast<int32_t>((functionDeclaration->typeParams)->size()) > 0)) {
        auto targetModule = expression->resolvedFunctionModule;
        auto concreteMethodName = std::string("");
        {
            auto _case_subject = expression->callee;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
                if (!doof::is_null(identifier->resolvedBinding)) {
                    if ((identifier->resolvedBinding->kind == std::string("method")) && (!doof::is_null(identifier->resolvedBinding->symbol))) {
                        const auto symbol = doof::unwrap_optional(identifier->resolvedBinding->symbol);
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> ownerArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                        const auto& _iterable_6 = symbol->typeParams;
                        for (const auto& typeParam : *_iterable_6) {
                            ownerArgs->push_back(::app_src_emitter_types_::specializeEmitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::TypeParameterType>(std::string("type-parameter"), typeParam, std::string(""), std::monostate{})), context));
                        }
                        const auto ownerKey = ::app_src_emitter_monomorphize_::classInstantiationKey(symbol->module, symbol->name, ownerArgs);
                        const auto methodKey = ::app_src_emitter_monomorphize_::methodInstantiationKey(ownerKey, functionDeclaration->name, concreteGenericArgs);
                        static_cast<void>((concreteMethodName = concreteMethodNameFor(context, methodKey)));
                    } else if (!doof::is_null(identifier->resolvedBinding->symbol)) {
                        static_cast<void>((targetModule = identifier->resolvedBinding->symbol->module));
                    } else if (identifier->resolvedBinding->module != std::string("")) {
                        static_cast<void>((targetModule = identifier->resolvedBinding->module));
                    }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                    {
                        auto _case_subject = ::app_src_emitter_types_::specializeEmitType(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)), context);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            static_cast<void>((targetModule = class_->symbol->module));
                            const auto ownerKey = ::app_src_emitter_monomorphize_::classInstantiationKey(class_->symbol->module, class_->name, class_->typeArgs);
                            const auto methodKey = ::app_src_emitter_monomorphize_::methodInstantiationKey(ownerKey, functionDeclaration->name, concreteGenericArgs);
                            static_cast<void>((concreteMethodName = concreteMethodNameFor(context, methodKey)));
                    }
                    else {
                    }
                    }
                }
        }
        else {
        }
        }
        if (concreteMethodName != std::string("")) {
            static_cast<void>((usesConcreteInstantiation = true));
            {
                auto _case_subject = expression->callee;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                    static_cast<void>((callee = concreteMethodName));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                    const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                    static_cast<void>((callee = (doof::string_substring(callee, 0, (static_cast<int32_t>(callee.size()) - static_cast<int32_t>(member->property.size()))) + concreteMethodName)));
            }
            else {
            }
            }
        } else {
            const auto key = ::app_src_emitter_monomorphize_::functionInstantiationKey(targetModule, functionDeclaration->name, concreteGenericArgs);
            const auto concreteName = concreteFunctionName(context, key);
            if (concreteName != std::string("")) {
                static_cast<void>((usesConcreteInstantiation = true));
                static_cast<void>((callee = (((targetModule != std::string("")) && (targetModule != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(targetModule)) + std::string("::")) + concreteName) : concreteName)));
            }
        }
    }
    if ((((static_cast<int32_t>((concreteGenericArgs)->size()) > 0) && (!doof::is_null(functionDeclaration))) && (static_cast<int32_t>((functionDeclaration->typeParams)->size()) > 0)) && !usesConcreteInstantiation) {
        doof::panic((((((((std::string("Missing concrete generic instantiation for ") + context->modulePath) + std::string("::")) + functionDeclaration->name) + std::string(" at line ")) + doof::to_string(expression->span.start.line)) + std::string(":")) + doof::to_string(expression->span.start.column)));
    }
    auto invokesCallback = false;
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            static_cast<void>((invokesCallback = ((!(((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->kind == std::string("builtin"))) && isBuiltinName(identifier->name)) && (!doof::is_null(functionType))) && doof::is_null(functionDeclaration))));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            static_cast<void>((invokesCallback = (member->resolvedCallableField && (!doof::is_null(functionType)))));
    }
    else {
            static_cast<void>((invokesCallback = ((!doof::is_null(functionType)) && doof::is_null(functionDeclaration))));
    }
    }
    const auto callPrefix = (invokesCallback ? (callee + std::string(".call(")) : (callee + std::string("(")));
    return ((callPrefix + ::app_src_emitter_call_arguments_::emitCallArguments(expression, context, functionType)) + std::string(")"));
}
std::string emitWeakMemberCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    static_cast<void>((context->tryCounter = (context->tryCounter + 1)));
    const auto storage = (std::string("_weak_storage_") + doof::to_string(context->tryCounter));
    const auto temporary = (std::string("_weak_value_") + doof::to_string(context->tryCounter));
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
    auto nullable = false;
    {
        auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            static_cast<void>((nullable = ::app_src_emitter_carriers_::weakTargetAllowsNone(weak_->inner)));
    }
    else {
    }
    }
    const auto weakValue = (nullable ? (storage + std::string(".value()")) : storage);
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> originalReturn = std::monostate{};
    if (!doof::is_null(member->resolvedType)) {
        {
            auto _case_subject = doof::unwrap_optional(member->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                static_cast<void>((originalReturn = doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(function_->returnType)));
        }
        else {
        }
        }
    }
    const auto arguments = ::app_src_emitter_call_arguments_::emitDispatchCallArguments(expression, context);
    auto call = (((((temporary + std::string("->")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + arguments) + std::string(")"));
    {
        auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            if (::app_src_emitter_carriers_::weakTargetUsesVariant(weak_->inner)) {
                if (doof::is_null(originalReturn)) {
                    doof::panic(std::string("Weak union method call has no resolved return type"));
                }
                static_cast<void>((call = ((((((((std::string("std::visit([&](auto&& _weak_item) -> ") + ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(originalReturn), context)) + std::string(" { return _weak_item->")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + arguments) + std::string("); }, ")) + temporary) + std::string(")"))));
            }
    }
    else {
    }
    }
    if (member->force) {
        const auto resultType = doof::unwrap_optional(expression->resolvedType);
        const auto noneCheck = (nullable ? ((std::string("if (!") + storage) + std::string(".has_value()) doof::panic(\"Weak reference is none\"); ")) : std::string(""));
        {
            auto _case_subject = resultType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                return ((((((((((((std::string("[&]() -> void { auto ") + storage) + std::string(" = ")) + object) + std::string("; ")) + noneCheck) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); ")) + call) + std::string("; }()"));
        }
        else {
                return ((((((((((((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(resultType, context->modulePath)) + std::string(" { auto ")) + storage) + std::string(" = ")) + object) + std::string("; ")) + noneCheck) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); return ")) + call) + std::string("; }()"));
        }
        }
        doof::unreachable();
    }
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            const auto resultCpp = ::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result), context->modulePath);
            const auto payloadCpp = ::app_src_emitter_types_::emitResultPayloadType(result->valueType, context->modulePath);
            const auto errorCpp = ::app_src_emitter_types_::emitResultPayloadType(result->errorType, context->modulePath);
            const auto failure = ((std::visit([](auto&& _obj) { return _obj->kind; }, result->errorType) == std::string("union")) ? (errorCpp + std::string("{::doof::WeakReferenceError{}}")) : std::string("::doof::WeakReferenceError{}"));
            const auto noneReturn = (nullable ? ((((((std::string("if (!") + storage) + std::string(".has_value()) return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{}}; ")) : std::string(""));
            const auto prefix = ((((((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto ")) + storage) + std::string(" = ")) + object) + std::string("; ")) + noneReturn) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) return doof::Failure<")) + errorCpp) + std::string(">{")) + failure) + std::string("}; auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); "));
            if (!doof::is_null(originalReturn)) {
                {
                    auto _case_subject = doof::unwrap_optional(originalReturn);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& nested = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                        const auto nestedErrorCpp = ::app_src_emitter_types_::emitResultPayloadType(nested->errorType, context->modulePath);
                        const auto promotedError = ((std::visit([](auto&& _obj) { return _obj->kind; }, result->errorType) == std::string("union")) ? (errorCpp + std::string("{doof::failure_error(_weak_result)}")) : std::string("doof::failure_error(_weak_result)"));
                        if (std::visit([](auto&& _obj) { return _obj->kind; }, nested->valueType) == std::string("none")) {
                            return (((((((prefix + std::string("auto _weak_result = ")) + call) + std::string("; if (doof::is_failure(_weak_result)) return doof::Failure<")) + errorCpp) + std::string(">{")) + promotedError) + std::string("}; return doof::Success<void>{}; }()"));
                        }
                        return (((((((((((prefix + std::string("auto _weak_result = ")) + call) + std::string("; if (doof::is_failure(_weak_result)) return doof::Failure<")) + errorCpp) + std::string(">{")) + promotedError) + std::string("}; return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{doof::success_value(_weak_result)}}; }()"));
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
                        return ((prefix + call) + std::string("; return doof::Success<void>{}; }()"));
                }
                else {
                }
                }
            }
            return (((((((prefix + std::string("return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{")) + call) + std::string("}}; }()"));
    }
    else {
            doof::panic(std::string("Optional weak method call must resolve to Result"));
    }
    }
    doof::unreachable();
    return std::string("");
}
bool isBuiltinIdentifier(const std::shared_ptr<::app_src_ast_::Identifier>& identifier, const std::string& name) {
    return (((identifier->name == name) && (!doof::is_null(identifier->resolvedBinding))) && (identifier->resolvedBinding->kind == std::string("builtin")));
}
std::string emitBuiltinCall(const std::string& name, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& object, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto result = ((name + std::string("(")) + ::app_src_emitter_expr_::emitExpression(object, context, std::monostate{}));
    const auto& _iterable_8 = expression->args;
    for (const auto& argument : *_iterable_8) {
        static_cast<void>((result = ((result + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(argument->value, context, std::monostate{}))));
    }
    return (result + std::string(")"));
}
std::string emitInterfaceCall(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
    auto args = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
        if (i > 0) {
            static_cast<void>((args = (args + std::string(", "))));
        }
        static_cast<void>((args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(call->args, i, "src/emitter-expr-calls", 426)->value, context, std::monostate{}))));
    }
    return ((((((std::string("std::visit([&](auto&& _obj) { return _obj->") + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }, ")) + object) + std::string(")"));
}
std::string emitVariantMemberCall(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
    const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
    if (doof::is_null(objectType)) {
        doof::panic(std::string("Variant member call has no resolved object type"));
    }
    if (doof::is_null(call->resolvedType)) {
        doof::panic(std::string("Variant member call has no resolved return type"));
    }
    const auto args = ::app_src_emitter_call_arguments_::emitDispatchCallArguments(call, context);
    const auto invocation = (member->resolvedCallableField ? std::string(".call(") : std::string("("));
    return ((((((((std::string("std::visit([&](auto&& _obj) -> ") + ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(call->resolvedType), context)) + std::string(" { return _obj->")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + invocation) + args) + std::string("); }, ")) + ::app_src_emitter_expr_utils_::variantVisitValue(object, doof::unwrap_optional(objectType))) + std::string(")"));
}
std::string emitInterfaceJsonCall(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto args = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
        if (i > 0) {
            static_cast<void>((args = (args + std::string(", "))));
        }
        static_cast<void>((args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(call->args, i, "src/emitter-expr-calls", 445)->value, context, std::monostate{}))));
    }
    if (static_cast<int32_t>((call->args)->size()) == 1) {
        static_cast<void>((args = (args + std::string(", false"))));
    }
    return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("_fromJsonValue(")) + args) + std::string(")"));
}
std::string builtinName(const std::string& name) {
    if (name == std::string("println")) {
        return std::string("doof::println");
    }
    if (name == std::string("panic")) {
        return std::string("doof::panic");
    }
    if (name == std::string("assert")) {
        return std::string("doof::assert_");
    }
    if (name == std::string("string")) {
        return std::string("doof::to_string");
    }
    if (name == std::string("byte")) {
        return std::string("static_cast<uint8_t>");
    }
    if (name == std::string("int")) {
        return std::string("static_cast<int32_t>");
    }
    if (name == std::string("long")) {
        return std::string("static_cast<int64_t>");
    }
    if (name == std::string("float")) {
        return std::string("static_cast<float>");
    }
    if (name == std::string("double")) {
        return std::string("static_cast<double>");
    }
    if (name == std::string("char")) {
        return std::string("static_cast<char32_t>");
    }
    if (name == std::string("bool")) {
        return std::string("static_cast<bool>");
    }
    return name;
}
bool isBuiltinName(const std::string& name) {
    return ((((((((((((name == std::string("println")) || (name == std::string("panic"))) || (name == std::string("assert"))) || (name == std::string("catchPanic"))) || (name == std::string("string"))) || (name == std::string("byte"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double"))) || (name == std::string("char"))) || (name == std::string("bool")));
}
std::string concreteFunctionName(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& key) {
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteFunctionKeys)->size()); ++i) {
        if (doof::array_at(context->concreteFunctionKeys, i, "src/emitter-expr-calls", 472) == key) {
            return doof::array_at(context->concreteFunctionNames, i, "src/emitter-expr-calls", 472);
        }
    }
    return std::string("");
}
std::string concreteMethodNameFor(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& key) {
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteMethodKeys)->size()); ++i) {
        if (doof::array_at(context->concreteMethodKeys, i, "src/emitter-expr-calls", 479) == key) {
            return doof::array_at(context->concreteMethodNames, i, "src/emitter-expr-calls", 479);
        }
    }
    return std::string("");
}
}
