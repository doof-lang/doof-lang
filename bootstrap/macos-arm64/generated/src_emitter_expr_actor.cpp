#include "src_emitter_expr_actor.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_expr_actor_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_types_;
std::string emitActorCreation(std::shared_ptr<::app_src_ast_::ActorCreationExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
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
                (args = (args + ::app_src_emitter_expr_::emitExpression((*expression->args)[i], context, std::monostate{})));
            }
            const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
            return ((((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + className) + std::string("{")) + args) + std::string("})"));
    }
    else {
            doof::panic(std::string("Actor creation does not have Actor<T> type"));
    }
    }
    return std::string("");
}
std::string emitAsyncActorCall(std::shared_ptr<::app_src_ast_::AsyncExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = expression->expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            doof::panic(std::string("Cannot emit async block; async is only valid for actor method calls"));
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
                            if (!doof::is_null(doof::resolved_type(member->object))) {
                                {
                                    auto _case_subject = doof::unwrap_optional(doof::resolved_type(member->object));
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
            }
            else {
            }
            }
    }
    }
    doof::panic(std::string("Cannot emit non-actor async expression; async is only valid for actor method calls"));
    return std::string("");
}
std::string emitRetireActor(std::shared_ptr<::app_src_ast_::RetireExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return (::app_src_emitter_expr_::emitExpression(expression->actor, context, std::monostate{}) + std::string("->retire()"));
}
std::string emitSyncActorCall(std::shared_ptr<::app_src_ast_::CallExpression> expression, std::shared_ptr<::app_src_ast_::MemberExpression> member, std::shared_ptr<::app_src_semantic_::ActorType> actor, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return emitActorMethodCall(expression, member, actor, false, context);
}
std::string emitActorMethodCall(std::shared_ptr<::app_src_ast_::CallExpression> expression, std::shared_ptr<::app_src_ast_::MemberExpression> member, std::shared_ptr<::app_src_semantic_::ActorType> actor, bool async_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
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
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
        if ((!doof::is_null(methodType)) && (i < static_cast<int32_t>((methodType->params)->size()))) {
            (expected = doof::optional_value((*methodType->params)[i]->type_));
        }
        (args = (args + ::app_src_emitter_expr_::emitExpression((*expression->args)[i]->value, context, expected)));
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
