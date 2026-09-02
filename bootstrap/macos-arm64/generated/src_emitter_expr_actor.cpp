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
            const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
            if (!doof::is_null(expression->resolvedConstructor)) {
                const auto factory = emitActorConstructorFactory(className, doof::unwrap_optional(expression->resolvedConstructor), expression, context);
                return ((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + factory) + std::string(")"));
            }
            auto args = std::string("");
            const auto declaration = actorClassDeclaration(actor->innerClass->symbol->module, actor->innerClass->symbol->name, context);
            if (doof::is_null(declaration)) {
                doof::panic((std::string("Actor construction is missing class declaration ") + actor->innerClass->name));
            }
            auto argumentIndex = 0;
            const auto& _iterable_4 = declaration->fields;
            for (const auto& field : *_iterable_4) {
                if (field->static_ || field->const_) {
                    continue;
                }
                const auto& _iterable_2 = field->names;
                for (const auto& name : *_iterable_2) {
                    if (args != std::string("")) {
                        (args = (args + std::string(", ")));
                    }
                    if (argumentIndex < static_cast<int32_t>((expression->args)->size())) {
                        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, argumentIndex, "src/emitter-expr-actor", 28), context, field->resolvedType)));
                    } else {
                        if (doof::is_null(field->defaultValue)) {
                            doof::panic((std::string("Actor constructor is missing argument ") + name));
                        }
                        const auto previous = context->sourceLocationSpanOverride;
                        (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(expression->span));
                        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType)));
                        (context->sourceLocationSpanOverride = previous);
                    }
                    (argumentIndex = (argumentIndex + 1));
                }
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
std::shared_ptr<::app_src_ast_::ClassDeclaration> actorClassDeclaration(const std::string& modulePath, const std::string& name, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto& _iterable_8 = context->allPrograms;
    for (const auto& program : *_iterable_8) {
        const auto& _iterable_6 = program->statements;
        for (const auto& statement : *_iterable_6) {
            const auto declaration = actorClassFromStatement(statement);
            if ((((!doof::is_null(declaration)) && (declaration->name == name)) && (!doof::is_null(declaration->resolvedSymbol))) && (declaration->resolvedSymbol->module == modulePath)) {
                return declaration;
            }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> actorClassFromStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            {
                auto _case_subject = export_->declaration;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                    return class_;
            }
            else {
            }
            }
    }
    else {
    }
    }
    return nullptr;
}
std::string emitActorConstructorFactory(const std::string& className, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructor, const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto result = (className + std::string("::constructor("));
    for (int32_t i = 0; i < static_cast<int32_t>((constructor->params)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        const auto parameter = doof::array_at(constructor->params, i, "src/emitter-expr-actor", 74);
        if (i < static_cast<int32_t>((expression->args)->size())) {
            (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 75), context, parameter->resolvedType)));
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
        (captures = (captures + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(expression->resolvedCaptureNames, i, "src/emitter-expr-actor", 142))));
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
    const auto args = emitActorMethodArguments(expression, methodType, context);
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
std::string emitActorMethodArguments(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_semantic_::FunctionType>& methodType, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto result = std::string("");
    auto named = false;
    const auto& _iterable_12 = expression->args;
    for (const auto& argument : *_iterable_12) {
        if (!doof::is_null(argument->name)) {
            (named = true);
        }
    }
    if (!doof::is_null(expression->resolvedFunction)) {
        const auto declaration = doof::unwrap_optional(expression->resolvedFunction);
        for (int32_t i = 0; i < static_cast<int32_t>((declaration->params)->size()); ++i) {
            const auto parameter = doof::array_at(declaration->params, i, "src/emitter-expr-actor", 197);
            auto argumentIndex = i;
            if (named) {
                (argumentIndex = static_cast<int32_t>((expression->args)->size()));
                for (int32_t candidateIndex = 0; candidateIndex < static_cast<int32_t>((expression->args)->size()); ++candidateIndex) {
                    if (doof::array_at(expression->args, candidateIndex, "src/emitter-expr-actor", 202)->name == parameter->name) {
                        (argumentIndex = candidateIndex);
                    }
                }
            }
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = parameter->resolvedType;
            if ((!doof::is_null(methodType)) && (i < static_cast<int32_t>((methodType->params)->size()))) {
                (expected = doof::optional_value(doof::array_at(methodType->params, i, "src/emitter-expr-actor", 206)->type_));
            }
            if (argumentIndex < static_cast<int32_t>((expression->args)->size())) {
                if (result != std::string("")) {
                    (result = (result + std::string(", ")));
                }
                (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, argumentIndex, "src/emitter-expr-actor", 209)->value, context, expected)));
            } else if (!doof::is_null(parameter->defaultValue)) {
                if (result != std::string("")) {
                    (result = (result + std::string(", ")));
                }
                const auto previous = context->sourceLocationSpanOverride;
                (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(expression->span));
                (result = (result + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, expected)));
                (context->sourceLocationSpanOverride = previous);
            }
        }
        return result;
    }
    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
        if ((!doof::is_null(methodType)) && (i < static_cast<int32_t>((methodType->params)->size()))) {
            (expected = doof::optional_value(doof::array_at(methodType->params, i, "src/emitter-expr-actor", 223)->type_));
        }
        (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 224)->value, context, expected)));
    }
    return result;
}
}
