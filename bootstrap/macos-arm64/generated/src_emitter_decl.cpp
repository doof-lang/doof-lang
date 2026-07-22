#include "src_emitter_decl.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_stmt.hpp"
#include "src_emitter_types.hpp"
#include "src_emitter_expr_lambda.hpp"
#include "src_emitter_names.hpp"
#include "src_emitter_monomorphize.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_metadata.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_decl_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_expr_lambda_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_metadata_;
std::string emitFunctionSignature(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string name, std::string modulePath, bool includeDefaults, std::shared_ptr<::app_src_emitter_context_::EmitContext> defaultContext, std::shared_ptr<std::vector<std::string>> ownerTypeParams) {
    auto functionType = checkedFunctionType(fn);
    if (!doof::is_null(defaultContext)) {
        {
            auto _case_subject = ::app_src_emitter_types_::specializeEmitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(functionType), doof::unwrap_optional(defaultContext));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& specialized = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                (functionType = specialized);
        }
        else {
        }
        }
    }
    const auto functionName = ::app_src_emitter_expr_::cppIdentifier(((name == std::string("")) ? fn->name : name));
    std::shared_ptr<std::vector<std::string>> genericParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_1 = ownerTypeParams;
    for (const auto& typeParam : *_iterable_1) {
        genericParams->push_back(typeParam);
    }
    const auto& _iterable_2 = fn->typeParams;
    for (const auto& typeParam : *_iterable_2) {
        genericParams->push_back(typeParam);
    }
    const auto returnType = (doof::is_null(defaultContext) ? ::app_src_emitter_types_::emitReturnType(functionType->returnType, modulePath) : ::app_src_emitter_types_::emitContextReturnType(functionType->returnType, doof::unwrap_optional(defaultContext)));
    ensureKnown(functionType->returnType, (fn->name + std::string(" return type")));
    auto result = (((returnType + std::string(" ")) + functionName) + std::string("("));
    for (int32_t i = 0; i < static_cast<int32_t>((fn->params)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        const auto parameterType = (doof::is_null((*fn->params)[i]->resolvedType) ? (*functionType->params)[i]->type_ : doof::unwrap_optional((*fn->params)[i]->resolvedType));
        const auto parameterText = (doof::is_null(defaultContext) ? ::app_src_emitter_types_::emitType(parameterType, modulePath) : ::app_src_emitter_types_::emitContextType(parameterType, doof::unwrap_optional(defaultContext)));
        ensureKnown(parameterType, ((fn->name + std::string(" parameter ")) + (*fn->params)[i]->name));
        (result = (((result + parameterText) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier((*fn->params)[i]->name)));
        if (includeDefaults && canEmitDefault(fn, i)) {
            if (doof::is_null(defaultContext)) {
                doof::panic(std::string("Default parameter emission requires an emit context"));
            }
            (result = ((result + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional((*fn->params)[i]->defaultValue), doof::unwrap_optional(defaultContext), doof::optional_value(parameterType))));
        }
    }
    return (result + std::string(")"));
}
std::string emitFunctionDefinition(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string name) {
    if (fn->bodyless) {
        return std::string("");
    }
    const auto previousReturnErrorType = context->currentReturnErrorType;
    const auto previousFunctionName = context->currentFunctionName;
    const auto previousCapturedMutables = context->capturedMutables;
    (context->currentFunctionName = fn->name);
    (context->capturedMutables = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    {
        auto _case_subject = fn->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInExpression(expression));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInBlock(block));
    }
    }
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                    (context->currentReturnErrorType = ::app_src_emitter_types_::emitContextType(result->errorType, context));
            }
            else {
                    (context->currentReturnErrorType = std::string(""));
            }
            }
    }
    else {
            (context->currentReturnErrorType = std::string(""));
    }
    }
    auto result = (((emitCallableDescription(fn, std::string("")) + (doof::is_null(context->substitution) ? templatePrefix(fn->typeParams) : std::string(""))) + emitFunctionSignature(fn, name, context->modulePath, false, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(" {\n"));
    {
        auto _case_subject = fn->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (result = (result + emitExpressionCoverageMark(expression, context)));
            const auto returnType = functionReturnType(fn);
            if ((!doof::is_null(returnType)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(returnType)) == std::string("none"))) {
                (result = (((result + std::string("    ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n")));
            } else {
                (result = (((result + std::string("    return ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (result = (result + ::app_src_emitter_stmt_::emitBlock(block, 1, context)));
    }
    }
    (context->currentReturnErrorType = previousReturnErrorType);
    (context->currentFunctionName = previousFunctionName);
    (context->capturedMutables = previousCapturedMutables);
    return (result + std::string("}\n"));
}
std::string emitFunctionDeclaration(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string name, std::string modulePath, std::shared_ptr<::app_src_emitter_context_::EmitContext> defaultContext) {
    const auto template_ = ((doof::is_null(defaultContext) || doof::is_null(defaultContext->substitution)) ? templatePrefix(fn->typeParams) : std::string(""));
    return (((emitCallableDescription(fn, std::string("")) + template_) + emitFunctionSignature(fn, name, modulePath, true, defaultContext, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(";\n"));
}
std::string emitNativeFunctionAdapterDefinition(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string emittedName, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto signature = emitFunctionSignature(fn, emittedName, context->modulePath, false, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto nativeName = ((fn->nativeCppName == std::string("")) ? fn->name : fn->nativeCppName);
    auto call = ((std::string("::") + nativeName) + std::string("("));
    for (int32_t i = 0; i < static_cast<int32_t>((fn->params)->size()); ++i) {
        if (i > 0) {
            (call = (call + std::string(", ")));
        }
        (call = (call + ::app_src_emitter_expr_::cppIdentifier((*fn->params)[i]->name)));
    }
    (call = (call + std::string(")")));
    const auto returnType = ::app_src_emitter_types_::specializeEmitType(checkedFunctionType(fn)->returnType, context);
    if (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) == std::string("none")) {
        return (((signature + std::string(" {\n    ")) + call) + std::string(";\n}\n"));
    }
    return (((signature + std::string(" {\n    return ")) + call) + std::string(";\n}\n"));
}
std::string emitValueDeclaration(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>> statement, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return ((((emitDescriptionComment(const_->description, std::string("")) + valuePrefix(const_->name, doof::unwrap_optional(const_->resolvedType), false, context)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(const_->value, context, const_->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return ((((emitDescriptionComment(readonly_->description, std::string("")) + valuePrefix(readonly_->name, doof::unwrap_optional(readonly_->resolvedType), false, context)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(readonly_->value, context, readonly_->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return (((valuePrefix(binding->name, doof::unwrap_optional(binding->resolvedType), false, context) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(binding->value, context, binding->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return (((valuePrefix(let_->name, doof::unwrap_optional(let_->resolvedType), true, context) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(let_->value, context, let_->resolvedType)) + std::string(";\n"));
    }
    }
    return std::string("");
}
std::string valuePrefix(std::string name, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, bool mutable_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            return ((((mutable_ ? std::string("") : std::string("const ")) + ::app_src_emitter_types_::emitContextType(resolvedType, context)) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            return ((((mutable_ ? std::string("") : std::string("const ")) + ::app_src_emitter_types_::emitContextType(resolvedType, context)) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name));
    }
    else {
            return ((mutable_ ? std::string("auto ") : std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(name));
    }
    }
    return (std::string("auto ") + ::app_src_emitter_expr_::cppIdentifier(name));
}
std::shared_ptr<::app_src_semantic_::FunctionType> checkedFunctionType(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn) {
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            return resolved;
    }
    else {
            doof::panic(((std::string("Function ") + fn->name) + std::string(" was not checked before emission")));
    }
    }
    return std::make_shared<::app_src_semantic_::FunctionType>(std::string("function"), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> functionReturnType(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn) {
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            return doof::optional_value(function_->returnType);
    }
    else {
            return std::monostate{};
    }
    }
    return std::monostate{};
}
bool canEmitDefault(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, int32_t index) {
    if (doof::is_null((*fn->params)[index]->defaultValue)) {
        return false;
    }
    for (int32_t i = (index + 1); i < static_cast<int32_t>((fn->params)->size()); ++i) {
        if (doof::is_null((*fn->params)[i]->defaultValue)) {
            return false;
        }
    }
    return true;
}
void ensureKnown(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, std::string owner) {
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
            doof::panic((std::string("Cannot emit unresolved type for ") + owner));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            ensureKnown(array->elementType, (owner + std::string(" element")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            ensureKnown(set_->elementType, (owner + std::string(" element")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
                ensureKnown((*tuple->elements)[i], (owner + std::string(" tuple element")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_3 = union_->types;
            for (const auto& member : *_iterable_3) {
                ensureKnown(member, (owner + std::string(" union member")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_4 = function_->params;
            for (const auto& parameter : *_iterable_4) {
                ensureKnown(parameter->type_, (owner + std::string(" callback parameter")));
            }
            ensureKnown(function_->returnType, (owner + std::string(" callback return")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            ensureKnown(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), (owner + std::string(" actor state")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            ensureKnown(promise->valueType, (owner + std::string(" promise value")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            ensureKnown(weak_->inner, (owner + std::string(" weak target")));
    }
    else {
    }
    }
}
std::string emitClassDeclaration(std::shared_ptr<::app_src_ast_::ClassDeclaration> decl, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string emittedName, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> concreteMethods) {
    if (decl->native_) {
        return std::string("");
    }
    const auto className = ((emittedName == std::string("")) ? decl->name : emittedName);
    auto ownershipName = className;
    if ((emittedName == std::string("")) && (static_cast<int32_t>((decl->typeParams)->size()) > 0)) {
        (ownershipName = (ownershipName + std::string("<")));
        for (int32_t index = 0; index < static_cast<int32_t>((decl->typeParams)->size()); ++index) {
            if (index > 0) {
                (ownershipName = (ownershipName + std::string(", ")));
            }
            (ownershipName = (ownershipName + (*decl->typeParams)[index]));
        }
        (ownershipName = (ownershipName + std::string(">")));
    }
    auto inheritance = (decl->struct_ ? std::string("") : ((std::string(" : public std::enable_shared_from_this<") + ownershipName) + std::string(">")));
    auto result = (((((emitDescriptionComment(decl->description, std::string("")) + (doof::is_null(context->substitution) ? templatePrefix(decl->typeParams) : std::string(""))) + std::string("struct ")) + className) + inheritance) + std::string(" {\n"));
    const auto& _iterable_5 = decl->fields;
    for (const auto& field : *_iterable_5) {
        for (int32_t index = 0; index < static_cast<int32_t>((field->names)->size()); ++index) {
            const auto name = (*field->names)[index];
            const auto description = ((index < static_cast<int32_t>((field->descriptions)->size())) ? (*field->descriptions)[index] : std::string(""));
            const auto effectiveType = fieldTypeForEmission(field);
            const auto fieldType = fieldTypeTextForEmission(field, effectiveType, context);
            ensureKnown(effectiveType, ((decl->name + std::string(".")) + name));
            (result = (result + emitDescriptionComment(description, std::string("    "))));
            (result = (((((result + std::string("    ")) + (field->static_ ? std::string("static ") : (field->const_ ? std::string("const ") : std::string("")))) + fieldType) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)));
            if ((!doof::is_null(field->defaultValue)) && !field->static_) {
                const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(effectiveType));
                if (!defaultNeedsImportedDefinition(defaultText, context)) {
                    (result = ((result + std::string(" = ")) + defaultText));
                }
            }
            (result = (result + std::string(";\n")));
        }
    }
    if (hasInstanceFields(decl)) {
        auto lastRequiredParameter = -1;
        auto parameterIndex = 0;
        const auto& _iterable_6 = decl->fields;
        for (const auto& field : *_iterable_6) {
            if (field->static_ || field->const_) {
                continue;
            }
            const auto& _iterable_7 = field->names;
            for (const auto& name : *_iterable_7) {
                if (doof::is_null(field->defaultValue)) {
                    (lastRequiredParameter = parameterIndex);
                }
                (parameterIndex = (parameterIndex + 1));
            }
        }
        auto suppressTrailingDefaults = false;
        (parameterIndex = 0);
        const auto& _iterable_8 = decl->fields;
        for (const auto& field : *_iterable_8) {
            if (field->static_ || field->const_) {
                continue;
            }
            const auto& _iterable_9 = field->names;
            for (const auto& name : *_iterable_9) {
                if ((parameterIndex > lastRequiredParameter) && (!doof::is_null(field->defaultValue))) {
                    const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(fieldTypeForEmission(field)));
                    if (defaultNeedsImportedDefinition(defaultText, context)) {
                        (suppressTrailingDefaults = true);
                    }
                }
                (parameterIndex = (parameterIndex + 1));
            }
        }
        (result = (((result + std::string("    ")) + className) + std::string("(")));
        auto firstParameter = true;
        (parameterIndex = 0);
        const auto& _iterable_10 = decl->fields;
        for (const auto& field : *_iterable_10) {
            if (field->static_ || field->const_) {
                continue;
            }
            const auto& _iterable_11 = field->names;
            for (const auto& name : *_iterable_11) {
                if (!firstParameter) {
                    (result = (result + std::string(", ")));
                }
                (firstParameter = false);
                const auto effectiveType = fieldTypeForEmission(field);
                const auto fieldType = fieldTypeTextForEmission(field, effectiveType, context);
                (result = (((result + fieldType) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)));
                if ((!suppressTrailingDefaults && (parameterIndex > lastRequiredParameter)) && (!doof::is_null(field->defaultValue))) {
                    const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(effectiveType));
                    if (!defaultNeedsImportedDefinition(defaultText, context)) {
                        (result = ((result + std::string(" = ")) + defaultText));
                    }
                }
                (parameterIndex = (parameterIndex + 1));
            }
        }
        (result = (result + std::string(") : ")));
        auto firstInitializer = true;
        const auto& _iterable_12 = decl->fields;
        for (const auto& field : *_iterable_12) {
            if (field->static_ || field->const_) {
                continue;
            }
            const auto& _iterable_13 = field->names;
            for (const auto& name : *_iterable_13) {
                if (!firstInitializer) {
                    (result = (result + std::string(", ")));
                }
                (firstInitializer = false);
                (result = ((((result + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string("(")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(")")));
            }
        }
        (result = (result + std::string(" {}\n")));
    } else if (!decl->struct_) {
        (result = (((result + std::string("    ")) + className) + std::string("() {}\n")));
    }
    const auto& _iterable_14 = decl->methods;
    for (const auto& method : *_iterable_14) {
        if (static_cast<int32_t>((method->typeParams)->size()) > 0) {
            if (static_cast<int32_t>((decl->typeParams)->size()) == 0) {
                (result = (result + emitInlineClassMethod(decl, method, context, std::string(""))));
            } else {
                const auto& _iterable_15 = concreteMethods;
                for (const auto& instantiation : *_iterable_15) {
                    if (instantiation->declaration->name != method->name) {
                        continue;
                    }
                    const auto previousSubstitution = context->substitution;
                    (context->substitution = instantiation->substitution);
                    (result = (result + emitInlineClassMethod(decl, method, context, instantiation->emittedName)));
                    (context->substitution = previousSubstitution);
                }
            }
        } else if ((static_cast<int32_t>((decl->typeParams)->size()) > 0) || (!doof::is_null(context->substitution))) {
            (result = (result + emitInlineClassMethod(decl, method, context, std::string(""))));
        } else {
            const auto staticPrefix = (method->static_ ? std::string("static ") : std::string(""));
            (result = ((((((result + emitCallableDescription(method, std::string("    "))) + std::string("    ")) + templatePrefix(method->typeParams)) + staticPrefix) + emitFunctionSignature(method, std::string(""), context->modulePath, true, context, decl->typeParams)) + std::string(";\n")));
        }
    }
    if (!doof::is_null(decl->destructor_)) {
        (result = (((result + std::string("    ~")) + className) + std::string("() {\n")));
        (result = (result + ::app_src_emitter_stmt_::emitBlock(doof::unwrap_optional(decl->destructor_), 2, context)));
        (result = (result + std::string("    }\n")));
    }
    (result = (result + ::app_src_emitter_json_::emitGeneratedJsonDeclarations(decl, context)));
    (result = (result + ::app_src_emitter_metadata_::emitMetadataDeclaration(decl)));
    return (result + std::string("};\n"));
}
bool defaultNeedsImportedDefinition(std::string defaultText, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto& _iterable_16 = context->imports;
    for (const auto& imported : *_iterable_16) {
        if (doof::string_contains(defaultText, ((std::string("::") + ::app_src_emitter_names_::moduleNamespace(imported->sourceModule)) + std::string("::")))) {
            return true;
        }
    }
    return false;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> fieldTypeForEmission(std::shared_ptr<::app_src_ast_::ClassField> field) {
    if (doof::is_null(field->resolvedType)) {
        doof::panic(std::string("Class field was not resolved before emission"));
    }
    return doof::unwrap_optional(field->resolvedType);
}
std::string fieldTypeTextForEmission(std::shared_ptr<::app_src_ast_::ClassField> field, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (field->weak_) {
        const auto specialized = ::app_src_emitter_types_::specializeEmitType(resolvedType, context);
        {
            auto _case_subject = specialized;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
                return ::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(weak_), context);
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                return ((std::string("std::weak_ptr<") + ::app_src_emitter_types_::emitClassInnerType(class_, context->modulePath)) + std::string(">"));
        }
        else {
                return ((std::string("std::weak_ptr<") + ::app_src_emitter_types_::emitContextType(specialized, context)) + std::string(">"));
        }
        }
    }
    const auto typeText = ::app_src_emitter_types_::emitContextType(resolvedType, context);
    if (doof::is_null(field->defaultValue)) {
        return typeText;
    }
    const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(resolvedType));
    if (((defaultText == std::string("std::monostate{}")) && doof::string_startsWith(typeText, std::string("std::variant<"))) && !doof::string_startsWith(typeText, std::string("std::variant<std::monostate"))) {
        return (std::string("std::variant<std::monostate, ") + doof::string_substring(typeText, 13, 1000000));
    }
    return typeText;
}
bool hasInstanceFields(std::shared_ptr<::app_src_ast_::ClassDeclaration> decl) {
    const auto& _iterable_17 = decl->fields;
    for (const auto& field : *_iterable_17) {
        if (!field->static_ && !field->const_) {
            return true;
        }
    }
    return false;
}
std::string emitStaticClassFieldDefinitions(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (owner->native_ || (static_cast<int32_t>((owner->typeParams)->size()) > 0)) {
        return std::string("");
    }
    auto result = std::string("");
    const auto& _iterable_18 = owner->fields;
    for (const auto& field : *_iterable_18) {
        if (!field->static_ || doof::is_null(field->defaultValue)) {
            continue;
        }
        const auto& _iterable_19 = field->names;
        for (const auto& name : *_iterable_19) {
            const auto resolvedType = fieldTypeForEmission(field);
            (result = ((((((((result + fieldTypeTextForEmission(field, resolvedType, context)) + std::string(" ")) + owner->name) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(resolvedType))) + std::string(";\n")));
        }
    }
    return result;
}
std::string emitInlineClassMethod(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_ast_::FunctionDeclaration> method, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string emittedName) {
    const auto previous = context->currentClass;
    const auto previousNative = context->currentClassNative;
    const auto previousFunctionName = context->currentFunctionName;
    const auto previousFunctionStatic = context->currentFunctionStatic;
    const auto previousGenericTypeParams = context->genericTypeParams;
    const auto previousCapturedMutables = context->capturedMutables;
    (context->currentClass = owner->name);
    (context->currentClassNative = owner->native_);
    (context->currentFunctionName = method->name);
    (context->currentFunctionStatic = method->static_);
    (context->genericTypeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    (context->capturedMutables = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInExpression(expression));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInBlock(block));
    }
    }
    const auto& _iterable_20 = owner->typeParams;
    for (const auto& typeParam : *_iterable_20) {
        context->genericTypeParams->push_back(typeParam);
    }
    const auto& _iterable_21 = method->typeParams;
    for (const auto& typeParam : *_iterable_21) {
        context->genericTypeParams->push_back(typeParam);
    }
    const auto staticPrefix = (method->static_ ? std::string("static ") : std::string(""));
    const auto template_ = (doof::is_null(context->substitution) ? templatePrefix(method->typeParams) : std::string(""));
    auto result = (((((emitCallableDescription(method, std::string("    ")) + std::string("    ")) + template_) + staticPrefix) + emitFunctionSignature(method, emittedName, context->modulePath, true, context, owner->typeParams)) + std::string(" {\n"));
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (result = (((result + std::string("        return ")) + ::app_src_emitter_expr_::emitExpression(expression, context, functionReturnType(method))) + std::string(";\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (result = (result + ::app_src_emitter_stmt_::emitBlock(block, 2, context)));
    }
    }
    (result = (result + std::string("    }\n")));
    (context->currentClass = previous);
    (context->currentClassNative = previousNative);
    (context->currentFunctionName = previousFunctionName);
    (context->currentFunctionStatic = previousFunctionStatic);
    (context->genericTypeParams = previousGenericTypeParams);
    (context->capturedMutables = previousCapturedMutables);
    return result;
}
std::string templatePrefix(std::shared_ptr<std::vector<std::string>> typeParams) {
    if (static_cast<int32_t>((typeParams)->size()) == 0) {
        return std::string("");
    }
    auto result = std::string("template <");
    for (int32_t i = 0; i < static_cast<int32_t>((typeParams)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        (result = ((result + std::string("typename ")) + (*typeParams)[i]));
    }
    return (result + std::string(">\n"));
}
std::string emitDescriptionComment(std::string description, std::string indent) {
    if (description == std::string("")) {
        return std::string("");
    }
    return (((indent + std::string("// ")) + doof::string_replaceAll(description, std::string("\n"), ((std::string("\n") + indent) + std::string("// ")))) + std::string("\n"));
}
std::string emitCallableDescription(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string indent) {
    auto result = emitDescriptionComment(fn->description, indent);
    const auto& _iterable_22 = fn->params;
    for (const auto& parameter : *_iterable_22) {
        if (parameter->description != std::string("")) {
            (result = ((((((result + indent) + std::string("// @param ")) + parameter->name) + std::string(" ")) + doof::string_replaceAll(parameter->description, std::string("\n"), std::string(" "))) + std::string("\n")));
        }
    }
    return result;
}
std::string emitInterfaceAlias(std::shared_ptr<::app_src_ast_::InterfaceDeclaration> decl, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (doof::is_null(decl->resolvedSymbol)) {
        doof::panic(((std::string("Interface ") + decl->name) + std::string(" was not analyzed")));
    }
    const auto implementations = decl->resolvedSymbol->implementations;
    if (static_cast<int32_t>((implementations)->size()) == 0) {
        doof::panic(((std::string("Interface ") + decl->name) + std::string(" has no implementing classes")));
    }
    auto result = (((emitDescriptionComment(decl->description, std::string("")) + std::string("using ")) + decl->name) + std::string(" = std::variant<"));
    auto first = true;
    const auto& _iterable_23 = implementations;
    for (const auto& symbol : *_iterable_23) {
        if (!first) {
            (result = (result + std::string(", ")));
        }
        (first = false);
        const auto className = (symbol->native_ ? (std::string("::") + ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName)) : ownedClassName(symbol, context->modulePath));
        (result = (((result + std::string("std::shared_ptr<")) + className) + std::string(">")));
    }
    return (result + std::string(">;\n"));
}
std::string ownedClassName(std::shared_ptr<::app_src_semantic_::Symbol> symbol, std::string currentModulePath) {
    if ((symbol->module == currentModulePath) || (currentModulePath == std::string(""))) {
        return ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
    }
    return (((std::string("::") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName));
}
std::string emitClassMethodDefinition(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_ast_::FunctionDeclaration> method, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (method->bodyless || (static_cast<int32_t>((method->typeParams)->size()) > 0)) {
        return std::string("");
    }
    const auto previous = context->currentClass;
    const auto previousNative = context->currentClassNative;
    const auto previousReturnErrorType = context->currentReturnErrorType;
    const auto previousFunctionName = context->currentFunctionName;
    const auto previousFunctionStatic = context->currentFunctionStatic;
    const auto previousCapturedMutables = context->capturedMutables;
    (context->currentClass = owner->name);
    (context->currentClassNative = owner->native_);
    (context->currentFunctionName = method->name);
    (context->currentFunctionStatic = method->static_);
    (context->capturedMutables = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInExpression(expression));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInBlock(block));
    }
    }
    {
        auto _case_subject = doof::unwrap_optional(method->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                    (context->currentReturnErrorType = ::app_src_emitter_types_::emitContextType(result->errorType, context));
            }
            else {
                    (context->currentReturnErrorType = std::string(""));
            }
            }
    }
    else {
            (context->currentReturnErrorType = std::string(""));
    }
    }
    const auto ownerName = (owner->native_ ? ((owner->nativeCppName == std::string("")) ? owner->name : owner->nativeCppName) : owner->name);
    auto result = (emitFunctionSignature(method, ((ownerName + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(method->name)), context->modulePath, false, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) + std::string(" {\n"));
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (result = (result + emitExpressionCoverageMark(expression, context)));
            (result = (((result + std::string("    return ")) + ::app_src_emitter_expr_::emitExpression(expression, context, functionReturnType(method))) + std::string(";\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (result = (result + ::app_src_emitter_stmt_::emitBlock(block, 1, context)));
    }
    }
    (context->currentClass = previous);
    (context->currentClassNative = previousNative);
    (context->currentReturnErrorType = previousReturnErrorType);
    (context->currentFunctionName = previousFunctionName);
    (context->currentFunctionStatic = previousFunctionStatic);
    (context->capturedMutables = previousCapturedMutables);
    return (result + std::string("}\n"));
}
std::string emitExpressionCoverageMark(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (!context->coverageEnabled || (context->coverageModuleId < 0)) {
        return std::string("");
    }
    const auto line = std::visit([](auto&& _obj) { return _obj->span; }, expression).start.line;
    ::app_src_emitter_context_::recordCoverageLine(context, line);
    return ((((std::string("    doof::coverage::cov_mark(") + doof::to_string(context->coverageModuleId)) + std::string(", ")) + doof::to_string(line)) + std::string(");\n"));
}
}
