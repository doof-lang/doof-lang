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
            const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
#line 15 "/src/emitter-expr-actor.do"
            if (!doof::is_null(expression->resolvedConstructor)) {
#line 16 "/src/emitter-expr-actor.do"
                const auto factory = emitActorConstructorFactory(className, doof::unwrap_optional(expression->resolvedConstructor), expression, context);
#line 17 "/src/emitter-expr-actor.do"
                return ((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + factory) + std::string(")"));
            }
#line 19 "/src/emitter-expr-actor.do"
            auto args = std::string("");
#line 20 "/src/emitter-expr-actor.do"
            const auto declaration = actorClassDeclaration(actor->innerClass->symbol->module, actor->innerClass->symbol->name, context);
#line 21 "/src/emitter-expr-actor.do"
            if (doof::is_null(declaration)) {
#line 21 "/src/emitter-expr-actor.do"
                doof::panic((std::string("Actor construction is missing class declaration ") + actor->innerClass->name));
            }
#line 22 "/src/emitter-expr-actor.do"
            auto argumentIndex = 0;
#line 23 "/src/emitter-expr-actor.do"
            const auto& _iterable_2 = declaration->fields;
            for (const auto& field : *_iterable_2) {
#line 24 "/src/emitter-expr-actor.do"
                if (field->static_ || field->const_) {
#line 24 "/src/emitter-expr-actor.do"
                    continue;
                }
#line 25 "/src/emitter-expr-actor.do"
                const auto& _iterable_4 = field->names;
                for (const auto& name : *_iterable_4) {
#line 26 "/src/emitter-expr-actor.do"
                    if (args != std::string("")) {
#line 26 "/src/emitter-expr-actor.do"
                        (args = (args + std::string(", ")));
                    }
#line 27 "/src/emitter-expr-actor.do"
                    if (argumentIndex < static_cast<int32_t>((expression->args)->size())) {
#line 28 "/src/emitter-expr-actor.do"
                        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, argumentIndex, "src/emitter-expr-actor", 28), context, field->resolvedType)));
                    } else {
#line 30 "/src/emitter-expr-actor.do"
                        if (doof::is_null(field->defaultValue)) {
#line 30 "/src/emitter-expr-actor.do"
                            doof::panic((std::string("Actor constructor is missing argument ") + name));
                        }
#line 31 "/src/emitter-expr-actor.do"
                        const auto previous = context->sourceLocationSpanOverride;
#line 32 "/src/emitter-expr-actor.do"
                        (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(expression->span));
#line 33 "/src/emitter-expr-actor.do"
                        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType)));
#line 34 "/src/emitter-expr-actor.do"
                        (context->sourceLocationSpanOverride = previous);
                    }
#line 36 "/src/emitter-expr-actor.do"
                    (argumentIndex = (argumentIndex + 1));
                }
            }
#line 39 "/src/emitter-expr-actor.do"
            return ((((((std::string("std::make_shared<doof::Actor<") + className) + std::string(">>(")) + className) + std::string("{")) + args) + std::string("})"));
    }
    else {
#line 41 "/src/emitter-expr-actor.do"
            doof::panic(std::string("Actor creation does not have Actor<T> type"));
    }
    }
    doof::unreachable();
#line 43 "/src/emitter-expr-actor.do"
    return std::string("");
}
#line 46 "/src/emitter-expr-actor.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> actorClassDeclaration(const std::string& modulePath, const std::string& name, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 47 "/src/emitter-expr-actor.do"
    const auto& _iterable_6 = context->allPrograms;
    for (const auto& program : *_iterable_6) {
#line 48 "/src/emitter-expr-actor.do"
        const auto& _iterable_8 = program->statements;
        for (const auto& statement : *_iterable_8) {
#line 49 "/src/emitter-expr-actor.do"
            const auto declaration = actorClassFromStatement(statement);
#line 50 "/src/emitter-expr-actor.do"
            if ((((!doof::is_null(declaration)) && (declaration->name == name)) && (!doof::is_null(declaration->resolvedSymbol))) && (declaration->resolvedSymbol->module == modulePath)) {
#line 50 "/src/emitter-expr-actor.do"
                return declaration;
            }
        }
    }
#line 53 "/src/emitter-expr-actor.do"
    return nullptr;
}
#line 56 "/src/emitter-expr-actor.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> actorClassFromStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 57 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 58 "/src/emitter-expr-actor.do"
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 60 "/src/emitter-expr-actor.do"
            {
                auto _case_subject = export_->declaration;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 61 "/src/emitter-expr-actor.do"
                    return class_;
            }
            else {
            }
            }
    }
    else {
    }
    }
#line 67 "/src/emitter-expr-actor.do"
    return nullptr;
}
#line 70 "/src/emitter-expr-actor.do"
std::string emitActorConstructorFactory(const std::string& className, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructor, const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 71 "/src/emitter-expr-actor.do"
    auto result = (className + std::string("::constructor("));
#line 72 "/src/emitter-expr-actor.do"
    for (int32_t i = 0; i < static_cast<int32_t>((constructor->params)->size()); ++i) {
#line 73 "/src/emitter-expr-actor.do"
        if (i > 0) {
#line 73 "/src/emitter-expr-actor.do"
            (result = (result + std::string(", ")));
        }
#line 74 "/src/emitter-expr-actor.do"
        const auto parameter = doof::array_at(constructor->params, i, "src/emitter-expr-actor", 74);
#line 75 "/src/emitter-expr-actor.do"
        if (i < static_cast<int32_t>((expression->args)->size())) {
#line 75 "/src/emitter-expr-actor.do"
            (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 75), context, parameter->resolvedType)));
        } else {
#line 77 "/src/emitter-expr-actor.do"
            if (doof::is_null(parameter->defaultValue)) {
#line 77 "/src/emitter-expr-actor.do"
                doof::panic((std::string("Actor constructor is missing argument ") + parameter->name));
            }
#line 78 "/src/emitter-expr-actor.do"
            const auto previous = context->sourceLocationSpanOverride;
#line 79 "/src/emitter-expr-actor.do"
            (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(expression->span));
#line 80 "/src/emitter-expr-actor.do"
            (result = (result + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType)));
#line 81 "/src/emitter-expr-actor.do"
            (context->sourceLocationSpanOverride = previous);
        }
    }
#line 84 "/src/emitter-expr-actor.do"
    return (result + std::string(")"));
}
#line 87 "/src/emitter-expr-actor.do"
std::string emitAsyncExpression(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 88 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = expression->expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 89 "/src/emitter-expr-actor.do"
            return emitAsyncBlock(expression, block, context);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 91 "/src/emitter-expr-actor.do"
            {
                auto _case_subject = inner;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                    const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 93 "/src/emitter-expr-actor.do"
                    {
                        auto _case_subject = call->callee;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 95 "/src/emitter-expr-actor.do"
                            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 96 "/src/emitter-expr-actor.do"
                                {
                                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                                        const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 97 "/src/emitter-expr-actor.do"
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
#line 104 "/src/emitter-expr-actor.do"
                    if (!doof::is_null(call->resolvedFunction)) {
#line 104 "/src/emitter-expr-actor.do"
                        return emitIsolatedFunctionCall(expression, call, context);
                    }
            }
            else {
            }
            }
    }
    }
#line 110 "/src/emitter-expr-actor.do"
    doof::panic(std::string("Cannot emit async expression without an actor method or isolated function call"));
#line 111 "/src/emitter-expr-actor.do"
    return std::string("");
}
#line 114 "/src/emitter-expr-actor.do"
std::string emitIsolatedFunctionCall(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 115 "/src/emitter-expr-actor.do"
    if (doof::is_null(expression->resolvedType)) {
#line 115 "/src/emitter-expr-actor.do"
        doof::panic(std::string("Async call is missing its resolved Promise type"));
    }
#line 116 "/src/emitter-expr-actor.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = std::monostate{};
#line 117 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 118 "/src/emitter-expr-actor.do"
            (valueType = doof::optional_value(promise->valueType));
    }
    else {
#line 119 "/src/emitter-expr-actor.do"
            doof::panic(std::string("Async call does not have Promise<T> type"));
    }
    }
#line 121 "/src/emitter-expr-actor.do"
    if (doof::is_null(valueType)) {
#line 121 "/src/emitter-expr-actor.do"
        return std::string("");
    }
#line 122 "/src/emitter-expr-actor.do"
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(valueType), context);
#line 123 "/src/emitter-expr-actor.do"
    const auto invocation = ::app_src_emitter_expr_::emitExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(call), context, std::monostate{});
#line 124 "/src/emitter-expr-actor.do"
    if (cppReturn == std::string("void")) {
#line 125 "/src/emitter-expr-actor.do"
        return ((std::string("doof::submit_async<void>([=]() { ") + invocation) + std::string("; })"));
    }
#line 127 "/src/emitter-expr-actor.do"
    return ((((((std::string("doof::submit_async<") + cppReturn) + std::string(">([=]() -> ")) + cppReturn) + std::string(" { return ")) + invocation) + std::string("; })"));
}
#line 130 "/src/emitter-expr-actor.do"
std::string emitAsyncBlock(const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 131 "/src/emitter-expr-actor.do"
    if (doof::is_null(expression->resolvedType)) {
#line 131 "/src/emitter-expr-actor.do"
        doof::panic(std::string("Async block is missing its resolved Promise type"));
    }
#line 132 "/src/emitter-expr-actor.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = std::monostate{};
#line 133 "/src/emitter-expr-actor.do"
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 134 "/src/emitter-expr-actor.do"
            (valueType = doof::optional_value(promise->valueType));
    }
    else {
#line 135 "/src/emitter-expr-actor.do"
            doof::panic(std::string("Async block does not have Promise<T> type"));
    }
    }
#line 137 "/src/emitter-expr-actor.do"
    if (doof::is_null(valueType)) {
#line 137 "/src/emitter-expr-actor.do"
        return std::string("");
    }
#line 138 "/src/emitter-expr-actor.do"
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(valueType), context);
#line 139 "/src/emitter-expr-actor.do"
    auto captures = std::string("");
#line 140 "/src/emitter-expr-actor.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->resolvedCaptureNames)->size()); ++i) {
#line 141 "/src/emitter-expr-actor.do"
        if (i > 0) {
#line 141 "/src/emitter-expr-actor.do"
            (captures = (captures + std::string(", ")));
        }
#line 142 "/src/emitter-expr-actor.do"
        (captures = (captures + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(expression->resolvedCaptureNames, i, "src/emitter-expr-actor", 142))));
    }
#line 144 "/src/emitter-expr-actor.do"
    const auto previousYieldState = context->inValueYieldBlock;
#line 145 "/src/emitter-expr-actor.do"
    const auto previousVoidState = context->valueYieldReturnsVoid;
#line 146 "/src/emitter-expr-actor.do"
    (context->inValueYieldBlock = true);
#line 147 "/src/emitter-expr-actor.do"
    (context->valueYieldReturnsVoid = (cppReturn == std::string("void")));
#line 148 "/src/emitter-expr-actor.do"
    const auto body = ::app_src_emitter_stmt_::emitBlock(block, 1, context);
#line 149 "/src/emitter-expr-actor.do"
    (context->inValueYieldBlock = previousYieldState);
#line 150 "/src/emitter-expr-actor.do"
    (context->valueYieldReturnsVoid = previousVoidState);
#line 151 "/src/emitter-expr-actor.do"
    return ((((((((std::string("doof::submit_async<") + cppReturn) + std::string(">([")) + captures) + std::string("]() -> ")) + cppReturn) + std::string(" {\n")) + body) + std::string("})"));
}
#line 154 "/src/emitter-expr-actor.do"
std::string emitRetireActor(const std::shared_ptr<::app_src_ast_::RetireExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 155 "/src/emitter-expr-actor.do"
    return (::app_src_emitter_expr_::emitExpression(expression->actor, context, std::monostate{}) + std::string("->retire()"));
}
#line 158 "/src/emitter-expr-actor.do"
std::string emitSyncActorCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_semantic_::ActorType>& actor, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 159 "/src/emitter-expr-actor.do"
    return emitActorMethodCall(expression, member, actor, false, context);
}
#line 162 "/src/emitter-expr-actor.do"
std::string emitActorMethodCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_semantic_::ActorType>& actor, bool async_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 163 "/src/emitter-expr-actor.do"
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 164 "/src/emitter-expr-actor.do"
    const auto className = ::app_src_emitter_types_::emitClassInnerType(actor->innerClass, context->modulePath);
#line 165 "/src/emitter-expr-actor.do"
    std::shared_ptr<::app_src_semantic_::FunctionType> methodType = nullptr;
#line 166 "/src/emitter-expr-actor.do"
    if (!doof::is_null(member->resolvedType)) {
#line 167 "/src/emitter-expr-actor.do"
        {
            auto _case_subject = doof::unwrap_optional(member->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 168 "/src/emitter-expr-actor.do"
                (methodType = function_);
        }
        else {
        }
        }
    }
#line 172 "/src/emitter-expr-actor.do"
    const auto args = emitActorMethodArguments(expression, methodType, context);
#line 173 "/src/emitter-expr-actor.do"
    const auto returnType = expression->resolvedType;
#line 174 "/src/emitter-expr-actor.do"
    if (doof::is_null(returnType)) {
#line 174 "/src/emitter-expr-actor.do"
        doof::panic(std::string("Actor method call is missing its resolved return type"));
    }
#line 178 "/src/emitter-expr-actor.do"
    const auto cppReturn = ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(returnType), context);
#line 179 "/src/emitter-expr-actor.do"
    const auto callName = (async_ ? std::string("call_async") : std::string("call_sync"));
#line 180 "/src/emitter-expr-actor.do"
    const auto capture = ((args == std::string("")) ? std::string("[]") : (async_ ? std::string("[=]") : std::string("[&]")));
#line 181 "/src/emitter-expr-actor.do"
    auto lambda = (((capture + std::string("(")) + className) + std::string("& _self)"));
#line 182 "/src/emitter-expr-actor.do"
    if (cppReturn == std::string("void")) {
#line 183 "/src/emitter-expr-actor.do"
        (lambda = (((((lambda + std::string(" { _self.")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }")));
    } else {
#line 185 "/src/emitter-expr-actor.do"
        (lambda = (((((((lambda + std::string(" -> ")) + cppReturn) + std::string(" { return _self.")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }")));
    }
#line 187 "/src/emitter-expr-actor.do"
    return (((((((object + std::string("->template ")) + callName) + std::string("<")) + cppReturn) + std::string(">(")) + lambda) + std::string(")"));
}
#line 190 "/src/emitter-expr-actor.do"
std::string emitActorMethodArguments(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_semantic_::FunctionType>& methodType, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 191 "/src/emitter-expr-actor.do"
    auto result = std::string("");
#line 192 "/src/emitter-expr-actor.do"
    auto named = false;
#line 193 "/src/emitter-expr-actor.do"
    const auto& _iterable_12 = expression->args;
    for (const auto& argument : *_iterable_12) {
#line 193 "/src/emitter-expr-actor.do"
        if (!doof::is_null(argument->name)) {
#line 193 "/src/emitter-expr-actor.do"
            (named = true);
        }
    }
#line 194 "/src/emitter-expr-actor.do"
    if (!doof::is_null(expression->resolvedFunction)) {
#line 195 "/src/emitter-expr-actor.do"
        const auto declaration = doof::unwrap_optional(expression->resolvedFunction);
#line 196 "/src/emitter-expr-actor.do"
        for (int32_t i = 0; i < static_cast<int32_t>((declaration->params)->size()); ++i) {
#line 197 "/src/emitter-expr-actor.do"
            const auto parameter = doof::array_at(declaration->params, i, "src/emitter-expr-actor", 197);
#line 198 "/src/emitter-expr-actor.do"
            auto argumentIndex = i;
#line 199 "/src/emitter-expr-actor.do"
            if (named) {
#line 200 "/src/emitter-expr-actor.do"
                (argumentIndex = static_cast<int32_t>((expression->args)->size()));
#line 201 "/src/emitter-expr-actor.do"
                for (int32_t candidateIndex = 0; candidateIndex < static_cast<int32_t>((expression->args)->size()); ++candidateIndex) {
#line 202 "/src/emitter-expr-actor.do"
                    if (doof::array_at(expression->args, candidateIndex, "src/emitter-expr-actor", 202)->name == parameter->name) {
#line 202 "/src/emitter-expr-actor.do"
                        (argumentIndex = candidateIndex);
                    }
                }
            }
#line 205 "/src/emitter-expr-actor.do"
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = parameter->resolvedType;
#line 206 "/src/emitter-expr-actor.do"
            if ((!doof::is_null(methodType)) && (i < static_cast<int32_t>((methodType->params)->size()))) {
#line 206 "/src/emitter-expr-actor.do"
                (expected = doof::optional_value(doof::array_at(methodType->params, i, "src/emitter-expr-actor", 206)->type_));
            }
#line 207 "/src/emitter-expr-actor.do"
            if (argumentIndex < static_cast<int32_t>((expression->args)->size())) {
#line 208 "/src/emitter-expr-actor.do"
                if (result != std::string("")) {
#line 208 "/src/emitter-expr-actor.do"
                    (result = (result + std::string(", ")));
                }
#line 209 "/src/emitter-expr-actor.do"
                (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, argumentIndex, "src/emitter-expr-actor", 209)->value, context, expected)));
            } else if (!doof::is_null(parameter->defaultValue)) {
#line 211 "/src/emitter-expr-actor.do"
                if (result != std::string("")) {
#line 211 "/src/emitter-expr-actor.do"
                    (result = (result + std::string(", ")));
                }
#line 212 "/src/emitter-expr-actor.do"
                const auto previous = context->sourceLocationSpanOverride;
#line 213 "/src/emitter-expr-actor.do"
                (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(expression->span));
#line 214 "/src/emitter-expr-actor.do"
                (result = (result + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(parameter->defaultValue), context, expected)));
#line 215 "/src/emitter-expr-actor.do"
                (context->sourceLocationSpanOverride = previous);
            }
        }
#line 218 "/src/emitter-expr-actor.do"
        return result;
    }
#line 220 "/src/emitter-expr-actor.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 221 "/src/emitter-expr-actor.do"
        if (i > 0) {
#line 221 "/src/emitter-expr-actor.do"
            (result = (result + std::string(", ")));
        }
#line 222 "/src/emitter-expr-actor.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
#line 223 "/src/emitter-expr-actor.do"
        if ((!doof::is_null(methodType)) && (i < static_cast<int32_t>((methodType->params)->size()))) {
#line 223 "/src/emitter-expr-actor.do"
            (expected = doof::optional_value(doof::array_at(methodType->params, i, "src/emitter-expr-actor", 223)->type_));
        }
#line 224 "/src/emitter-expr-actor.do"
        (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-actor", 224)->value, context, expected)));
    }
#line 226 "/src/emitter-expr-actor.do"
    return result;
}
#line 1 "<doof-generated>"
}
