#include "src_emitter_expr_actor.hpp"

namespace app_src_emitter_expr_actor_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_types_;
#line 10 "/src/emitter-expr-actor.do"
std::string emitActorCreation(const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 11 "/src/emitter-expr-actor.do"
    if (doof::is_null(expression->resolvedType)) {
#line 11 "/src/emitter-expr-actor.do"
        doof::panic(std::string("Actor creation is missing its resolved type"));
    }
#line 12 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 14 "/src/emitter-expr-actor.do"
            auto args = std::string("");
#line 15 "/src/emitter-expr-actor.do"
            for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 16 "/src/emitter-expr-actor.do"
                if (i > 0) {
#line 16 "/src/emitter-expr-actor.do"
                    (args = (args + std::string(", ")));
                }
#line 17 "/src/emitter-expr-actor.do"
                (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 17), context, std::monostate{})));
            }
#line 19 "/src/emitter-expr-actor.do"
            const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
#line 20 "/src/emitter-expr-actor.do"
            if (!doof::is_null(expression->resolvedConstructor)) {
#line 21 "/src/emitter-expr-actor.do"
                const auto factory = emitActorConstructorFactory(className, doof::unwrap_optional(expression->resolvedConstructor), expression, context);
#line 22 "/src/emitter-expr-actor.do"
                return ((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + factory) + std::string(")"));
            }
#line 24 "/src/emitter-expr-actor.do"
            return ((((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + className) + std::string("{")) + args) + std::string("})"));
    }
    else {
#line 26 "/src/emitter-expr-actor.do"
            doof::panic(std::string("Actor creation does not have Actor<T> type"));
    }
    }
    doof::unreachable();
#line 28 "/src/emitter-expr-actor.do"
    return std::string("");
}
#line 31 "/src/emitter-expr-actor.do"
std::string emitActorConstructorFactory(const std::string& className, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructor, const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 32 "/src/emitter-expr-actor.do"
    auto result = (className + std::string("::constructor("));
#line 33 "/src/emitter-expr-actor.do"
    for (int32_t i = 0; i < static_cast<int32_t>((constructor->params)->size()); ++i) {
#line 34 "/src/emitter-expr-actor.do"
        if (i > 0) {
#line 34 "/src/emitter-expr-actor.do"
            (result = (result + std::string(", ")));
        }
#line 35 "/src/emitter-expr-actor.do"
        const auto parameter = doof::array_at(constructor->params, i, "src/emitter-expr-actor", 35);
#line 36 "/src/emitter-expr-actor.do"
        if (i < static_cast<int32_t>((expression->args)->size())) {
#line 36 "/src/emitter-expr-actor.do"
            (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 36), context, parameter->resolvedType)));
        } else {
#line 38 "/src/emitter-expr-actor.do"
            if (doof::is_null(parameter->defaultValue)) {
#line 38 "/src/emitter-expr-actor.do"
                doof::panic((std::string("Actor constructor is missing argument ") + parameter->name));
            }
#line 39 "/src/emitter-expr-actor.do"
            const auto previous = context->sourceLocationSpanOverride;
#line 40 "/src/emitter-expr-actor.do"
            (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(expression->span));
#line 41 "/src/emitter-expr-actor.do"
            (result = (result + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType)));
#line 42 "/src/emitter-expr-actor.do"
            (context->sourceLocationSpanOverride = previous);
        }
    }
#line 45 "/src/emitter-expr-actor.do"
    return (result + std::string(")"));
}
#line 48 "/src/emitter-expr-actor.do"
std::string emitAsyncExpression(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 49 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = expression->expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 50 "/src/emitter-expr-actor.do"
            return emitAsyncBlock(expression, block, context);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 52 "/src/emitter-expr-actor.do"
            {
                auto _case_subject = inner;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                    const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 54 "/src/emitter-expr-actor.do"
                    {
                        auto _case_subject = call->callee;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 56 "/src/emitter-expr-actor.do"
                            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 57 "/src/emitter-expr-actor.do"
                                {
                                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                                        const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 58 "/src/emitter-expr-actor.do"
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
#line 65 "/src/emitter-expr-actor.do"
                    if (!doof::is_null(call->resolvedFunction)) {
#line 65 "/src/emitter-expr-actor.do"
                        return emitIsolatedFunctionCall(expression, call, context);
                    }
            }
            else {
            }
            }
    }
    }
#line 71 "/src/emitter-expr-actor.do"
    doof::panic(std::string("Cannot emit async expression without an actor method or isolated function call"));
#line 72 "/src/emitter-expr-actor.do"
    return std::string("");
}
#line 75 "/src/emitter-expr-actor.do"
std::string emitIsolatedFunctionCall(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 76 "/src/emitter-expr-actor.do"
    if (doof::is_null(expression->resolvedType)) {
#line 76 "/src/emitter-expr-actor.do"
        doof::panic(std::string("Async call is missing its resolved Promise type"));
    }
#line 77 "/src/emitter-expr-actor.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = std::monostate{};
#line 78 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 79 "/src/emitter-expr-actor.do"
            (valueType = doof::optional_value(promise->valueType));
    }
    else {
#line 80 "/src/emitter-expr-actor.do"
            doof::panic(std::string("Async call does not have Promise<T> type"));
    }
    }
#line 82 "/src/emitter-expr-actor.do"
    if (doof::is_null(valueType)) {
#line 82 "/src/emitter-expr-actor.do"
        return std::string("");
    }
#line 83 "/src/emitter-expr-actor.do"
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(valueType), context);
#line 84 "/src/emitter-expr-actor.do"
    const auto invocation = ::app_src_emitter_expr_::emitExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(call), context, std::monostate{});
#line 85 "/src/emitter-expr-actor.do"
    if (cppReturn == std::string("void")) {
#line 86 "/src/emitter-expr-actor.do"
        return ((std::string("doof::submit_async<void>([=]() { ") + invocation) + std::string("; })"));
    }
#line 88 "/src/emitter-expr-actor.do"
    return ((((((std::string("doof::submit_async<") + cppReturn) + std::string(">([=]() -> ")) + cppReturn) + std::string(" { return ")) + invocation) + std::string("; })"));
}
#line 91 "/src/emitter-expr-actor.do"
std::string emitAsyncBlock(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 92 "/src/emitter-expr-actor.do"
    if (doof::is_null(expression->resolvedType)) {
#line 92 "/src/emitter-expr-actor.do"
        doof::panic(std::string("Async block is missing its resolved Promise type"));
    }
#line 93 "/src/emitter-expr-actor.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = std::monostate{};
#line 94 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 95 "/src/emitter-expr-actor.do"
            (valueType = doof::optional_value(promise->valueType));
    }
    else {
#line 96 "/src/emitter-expr-actor.do"
            doof::panic(std::string("Async block does not have Promise<T> type"));
    }
    }
#line 98 "/src/emitter-expr-actor.do"
    if (doof::is_null(valueType)) {
#line 98 "/src/emitter-expr-actor.do"
        return std::string("");
    }
#line 99 "/src/emitter-expr-actor.do"
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(valueType), context);
#line 100 "/src/emitter-expr-actor.do"
    auto captures = std::string("");
#line 101 "/src/emitter-expr-actor.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->resolvedCaptureNames)->size()); ++i) {
#line 102 "/src/emitter-expr-actor.do"
        if (i > 0) {
#line 102 "/src/emitter-expr-actor.do"
            (captures = (captures + std::string(", ")));
        }
#line 103 "/src/emitter-expr-actor.do"
        (captures = (captures + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(expression->resolvedCaptureNames, i, "src/emitter-expr-actor", 103))));
    }
#line 105 "/src/emitter-expr-actor.do"
    const auto previousYieldState = context->inValueYieldBlock;
#line 106 "/src/emitter-expr-actor.do"
    const auto previousVoidState = context->valueYieldReturnsVoid;
#line 107 "/src/emitter-expr-actor.do"
    (context->inValueYieldBlock = true);
#line 108 "/src/emitter-expr-actor.do"
    (context->valueYieldReturnsVoid = (cppReturn == std::string("void")));
#line 109 "/src/emitter-expr-actor.do"
    const auto body = ::app_src_emitter_stmt_::emitBlock(block, 1, context);
#line 110 "/src/emitter-expr-actor.do"
    (context->inValueYieldBlock = previousYieldState);
#line 111 "/src/emitter-expr-actor.do"
    (context->valueYieldReturnsVoid = previousVoidState);
#line 112 "/src/emitter-expr-actor.do"
    return ((((((((std::string("doof::submit_async<") + cppReturn) + std::string(">([")) + captures) + std::string("]() -> ")) + cppReturn) + std::string(" {\n")) + body) + std::string("})"));
}
#line 115 "/src/emitter-expr-actor.do"
std::string emitRetireActor(const std::shared_ptr<::app_src_ast_::RetireExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 116 "/src/emitter-expr-actor.do"
    return (::app_src_emitter_expr_::emitExpression(expression->actor, context, std::monostate{}) + std::string("->retire()"));
}
#line 119 "/src/emitter-expr-actor.do"
std::string emitSyncActorCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_semantic_::ActorType>& actor, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 120 "/src/emitter-expr-actor.do"
    return emitActorMethodCall(expression, member, actor, false, context);
}
#line 123 "/src/emitter-expr-actor.do"
std::string emitActorMethodCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_semantic_::ActorType>& actor, bool async_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 124 "/src/emitter-expr-actor.do"
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 125 "/src/emitter-expr-actor.do"
    const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
#line 126 "/src/emitter-expr-actor.do"
    std::shared_ptr<::app_src_semantic_::FunctionType> methodType = nullptr;
#line 127 "/src/emitter-expr-actor.do"
    if (!doof::is_null(member->resolvedType)) {
#line 128 "/src/emitter-expr-actor.do"
        {
            auto _case_subject = doof::unwrap_optional(member->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 129 "/src/emitter-expr-actor.do"
                (methodType = function_);
        }
        else {
        }
        }
    }
#line 133 "/src/emitter-expr-actor.do"
    auto args = std::string("");
#line 134 "/src/emitter-expr-actor.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 135 "/src/emitter-expr-actor.do"
        if (i > 0) {
#line 135 "/src/emitter-expr-actor.do"
            (args = (args + std::string(", ")));
        }
#line 136 "/src/emitter-expr-actor.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
#line 137 "/src/emitter-expr-actor.do"
        if ((!doof::is_null(methodType)) && (i < static_cast<int32_t>((methodType->params)->size()))) {
#line 137 "/src/emitter-expr-actor.do"
            (expected = doof::optional_value(doof::array_at(methodType->params, i, "src/emitter-expr-actor", 137)->type_));
        }
#line 138 "/src/emitter-expr-actor.do"
        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 138)->value, context, expected)));
    }
#line 140 "/src/emitter-expr-actor.do"
    const auto returnType = expression->resolvedType;
#line 141 "/src/emitter-expr-actor.do"
    if (doof::is_null(returnType)) {
#line 141 "/src/emitter-expr-actor.do"
        doof::panic(std::string("Actor method call is missing its resolved return type"));
    }
#line 145 "/src/emitter-expr-actor.do"
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(returnType), context);
#line 146 "/src/emitter-expr-actor.do"
    const auto callName = (async_ ? std::string("call_async") : std::string("call_sync"));
#line 147 "/src/emitter-expr-actor.do"
    const auto capture = ((args == std::string("")) ? std::string("[]") : (async_ ? std::string("[=]") : std::string("[&]")));
#line 148 "/src/emitter-expr-actor.do"
    auto lambda = (((capture + std::string("(")) + className) + std::string("& _self)"));
#line 149 "/src/emitter-expr-actor.do"
    if (cppReturn == std::string("void")) {
#line 150 "/src/emitter-expr-actor.do"
        (lambda = (((((lambda + std::string(" { _self.")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }")));
    } else {
#line 152 "/src/emitter-expr-actor.do"
        (lambda = (((((((lambda + std::string(" -> ")) + cppReturn) + std::string(" { return _self.")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }")));
    }
#line 154 "/src/emitter-expr-actor.do"
    return (((((((object + std::string("->template ")) + callName) + std::string("<")) + cppReturn) + std::string(">(")) + lambda) + std::string(")"));
}
#line 1 "<doof-generated>"
}
