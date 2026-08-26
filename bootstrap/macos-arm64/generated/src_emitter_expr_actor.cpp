#include "src_emitter_expr_actor.hpp"

namespace app_src_emitter_expr_actor_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_types_;
std::string emitActorCreation(const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->resolvedType)) {
        doof::panic(std::string("Actor creation is missing its resolved type"));
    }
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            auto args = std::string("");
            for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
                if (i > 0) {
                    (args = (args + std::string(", ")));
                }
                (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 17), context, std::monostate{})));
            }
            const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
            if (!doof::is_null(expression->resolvedConstructor)) {
                const auto factory = emitActorConstructorFactory(className, doof::unwrap_optional(expression->resolvedConstructor), expression, context);
                return ((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + factory) + std::string(")"));
            }
            return ((((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + className) + std::string("{")) + args) + std::string("})"));
    }
    else {
            doof::panic(std::string("Actor creation does not have Actor<T> type"));
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitActorConstructorFactory(const std::string& className, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructor, const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto result = (className + std::string("::constructor("));
    for (int32_t i = 0; i < static_cast<int32_t>((constructor->params)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        const auto parameter = doof::array_at(constructor->params, i, "src/emitter-expr-actor", 35);
        if (i < static_cast<int32_t>((expression->args)->size())) {
            (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 36), context, parameter->resolvedType)));
        } else {
            if (doof::is_null(parameter->defaultValue)) {
                doof::panic((std::string("Actor constructor is missing argument ") + parameter->name));
            }
            const auto previous = context->sourceLocationSpanOverride;
            (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(expression->span));
            (result = (result + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType)));
            (context->sourceLocationSpanOverride = previous);
        }
    }
    return (result + std::string(")"));
}
std::string emitAsyncExpression(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = expression->expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            return emitAsyncBlock(expression, block, context);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            {
                auto _case_subject = inner;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                    const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
                    {
                        auto _case_subject = call->callee;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                                {
                                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                                        const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
                                        return emitActorMethodCall(call, member, actor, true, context);
                                }
                                else {
                                }
                                }
                            }
                    }
                    else {
                    }
                    }
                    if (!doof::is_null(call->resolvedFunction)) {
                        return emitIsolatedFunctionCall(expression, call, context);
                    }
            }
            else {
            }
            }
    }
    }
    doof::panic(std::string("Cannot emit async expression without an actor method or isolated function call"));
    return std::string("");
}
std::string emitIsolatedFunctionCall(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->resolvedType)) {
        doof::panic(std::string("Async call is missing its resolved Promise type"));
    }
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = std::monostate{};
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            (valueType = doof::optional_value(promise->valueType));
    }
    else {
            doof::panic(std::string("Async call does not have Promise<T> type"));
    }
    }
    if (doof::is_null(valueType)) {
        return std::string("");
    }
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(valueType), context);
    const auto invocation = ::app_src_emitter_expr_::emitExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(call), context, std::monostate{});
    if (cppReturn == std::string("void")) {
        return ((std::string("doof::submit_async<void>([=]() { ") + invocation) + std::string("; })"));
    }
    return ((((((std::string("doof::submit_async<") + cppReturn) + std::string(">([=]() -> ")) + cppReturn) + std::string(" { return ")) + invocation) + std::string("; })"));
}
std::string emitAsyncBlock(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->resolvedType)) {
        doof::panic(std::string("Async block is missing its resolved Promise type"));
    }
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = std::monostate{};
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            (valueType = doof::optional_value(promise->valueType));
    }
    else {
            doof::panic(std::string("Async block does not have Promise<T> type"));
    }
    }
    if (doof::is_null(valueType)) {
        return std::string("");
    }
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(valueType), context);
    auto captures = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((expression->resolvedCaptureNames)->size()); ++i) {
        if (i > 0) {
            (captures = (captures + std::string(", ")));
        }
        (captures = (captures + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(expression->resolvedCaptureNames, i, "src/emitter-expr-actor", 103))));
    }
    const auto previousYieldState = context->inValueYieldBlock;
    const auto previousVoidState = context->valueYieldReturnsVoid;
    (context->inValueYieldBlock = true);
    (context->valueYieldReturnsVoid = (cppReturn == std::string("void")));
    const auto body = ::app_src_emitter_stmt_::emitBlock(block, 1, context);
    (context->inValueYieldBlock = previousYieldState);
    (context->valueYieldReturnsVoid = previousVoidState);
    return ((((((((std::string("doof::submit_async<") + cppReturn) + std::string(">([")) + captures) + std::string("]() -> ")) + cppReturn) + std::string(" {\n")) + body) + std::string("})"));
}
std::string emitRetireActor(const std::shared_ptr<::app_src_ast_::RetireExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    return (::app_src_emitter_expr_::emitExpression(expression->actor, context, std::monostate{}) + std::string("->retire()"));
}
std::string emitSyncActorCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_semantic_::ActorType>& actor, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    return emitActorMethodCall(expression, member, actor, false, context);
}
std::string emitActorMethodCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_semantic_::ActorType>& actor, bool async_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
    const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
    std::shared_ptr<::app_src_semantic_::FunctionType> methodType = nullptr;
    if (!doof::is_null(member->resolvedType)) {
        {
            auto _case_subject = doof::unwrap_optional(member->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                (methodType = function_);
        }
        else {
        }
        }
    }
    auto args = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
        if (i > 0) {
            (args = (args + std::string(", ")));
        }
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
        if ((!doof::is_null(methodType)) && (i < static_cast<int32_t>((methodType->params)->size()))) {
            (expected = doof::optional_value(doof::array_at(methodType->params, i, "src/emitter-expr-actor", 137)->type_));
        }
        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 138)->value, context, expected)));
    }
    const auto returnType = expression->resolvedType;
    if (doof::is_null(returnType)) {
        doof::panic(std::string("Actor method call is missing its resolved return type"));
    }
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(returnType), context);
    const auto callName = (async_ ? std::string("call_async") : std::string("call_sync"));
    const auto capture = ((args == std::string("")) ? std::string("[]") : (async_ ? std::string("[=]") : std::string("[&]")));
    auto lambda = (((capture + std::string("(")) + className) + std::string("& _self)"));
    if (cppReturn == std::string("void")) {
        (lambda = (((((lambda + std::string(" { _self.")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }")));
    } else {
        (lambda = (((((((lambda + std::string(" -> ")) + cppReturn) + std::string(" { return _self.")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }")));
    }
    return (((((((object + std::string("->template ")) + callName) + std::string("<")) + cppReturn) + std::string(">(")) + lambda) + std::string(")"));
}
}
