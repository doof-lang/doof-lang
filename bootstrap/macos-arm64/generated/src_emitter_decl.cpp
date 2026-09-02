#include "src_emitter_decl.hpp"

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
std::string emitFunctionSignature(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& name, const std::string& modulePath, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams) {
    auto functionType = checkedFunctionType(fn);
    if (!doof::is_null(context)) {
        {
            auto _case_subject = ::app_src_emitter_types_::specializeEmitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(functionType), doof::unwrap_optional(context));
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
    const auto& _iterable_2 = ownerTypeParams;
    for (const auto& typeParam : *_iterable_2) {
        genericParams->push_back(typeParam);
    }
    const auto& _iterable_4 = fn->typeParams;
    for (const auto& typeParam : *_iterable_4) {
        genericParams->push_back(typeParam);
    }
    const auto returnType = (doof::is_null(context) ? ::app_src_emitter_types_::emitReturnType(functionType->returnType, modulePath) : ::app_src_emitter_types_::emitContextReturnType(functionType->returnType, doof::unwrap_optional(context)));
    ensureKnown(functionType->returnType, (fn->name + std::string(" return type")));
    auto result = ((((((std::visit([](auto&& _obj) { return _obj->kind; }, functionType->returnType) == std::string("never")) ? std::string("[[noreturn]] ") : std::string("")) + returnType) + std::string(" ")) + functionName) + std::string("("));
    for (int32_t i = 0; i < static_cast<int32_t>((fn->params)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        const auto parameterType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_5 = doof::array_at(fn->params, i, "src/emitter-decl", 41)->resolvedType; if (doof::is_null(_coalesce_5)) return doof::array_at(functionType->params, i, "src/emitter-decl", 41)->type_; return doof::unwrap_optional(_coalesce_5); }();
        const auto parameterText = (doof::is_null(context) ? ::app_src_emitter_types_::emitParameterType(parameterType, modulePath) : ::app_src_emitter_types_::borrowParameterType(parameterType, ::app_src_emitter_types_::emitContextType(parameterType, doof::unwrap_optional(context))));
        ensureKnown(parameterType, ((fn->name + std::string(" parameter ")) + doof::array_at(fn->params, i, "src/emitter-decl", 45)->name));
        (result = (((result + parameterText) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(fn->params, i, "src/emitter-decl", 46)->name)));
    }
    return (result + std::string(")"));
}
std::string emitFunctionDefinition(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& name) {
    if (fn->bodyless) {
        return std::string("");
    }
    if ((static_cast<int32_t>((fn->typeParams)->size()) > 0) && doof::is_null(context->substitution)) {
        doof::panic(((std::string("Generic function ") + fn->name) + std::string(" reached emission without a concrete instantiation")));
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
    auto result = (((::app_src_emitter_context_::sourceLineDirective(fn->span, context) + emitCallableDescription(fn, std::string(""))) + emitFunctionSignature(fn, name, context->modulePath, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(" {\n"));
    {
        auto _case_subject = fn->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (result = (result + emitExpressionCoverageMark(expression, context)));
            const auto returnType = functionReturnType(fn);
            if ((!doof::is_null(returnType)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(returnType)) == std::string("none"))) {
                (result = (((result + std::string("    ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n")));
            } else if ((!doof::is_null(returnType)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(returnType)) == std::string("never"))) {
                (result = (((result + std::string("    ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n    doof::panic(\"never function returned\");\n")));
            } else {
                (result = (((result + std::string("    return ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (result = (result + ::app_src_emitter_stmt_::emitBlock(block, 1, context)));
            const auto returnType = functionReturnType(fn);
            if ((!doof::is_null(returnType)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(returnType)) == std::string("never"))) {
                (result = (result + std::string("    doof::panic(\"never function returned\");\n")));
            }
    }
    }
    (context->currentReturnErrorType = previousReturnErrorType);
    (context->currentFunctionName = previousFunctionName);
    (context->capturedMutables = previousCapturedMutables);
    return (result + std::string("}\n"));
}
std::string emitFunctionDeclaration(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& name, const std::string& modulePath, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if ((static_cast<int32_t>((fn->typeParams)->size()) > 0) && (doof::is_null(context) || doof::is_null(context->substitution))) {
        doof::panic(((std::string("Generic function ") + fn->name) + std::string(" reached declaration emission without a concrete instantiation")));
    }
    return ((emitCallableDescription(fn, std::string("")) + emitFunctionSignature(fn, name, modulePath, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(";\n"));
}
std::string emitNativeFunctionAdapterDefinition(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& emittedName, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto signature = emitFunctionSignature(fn, emittedName, context->modulePath, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto nativeName = ((fn->nativeCppName == std::string("")) ? fn->name : fn->nativeCppName);
    auto call = ((std::string("::") + nativeName) + std::string("("));
    for (int32_t i = 0; i < static_cast<int32_t>((fn->params)->size()); ++i) {
        if (i > 0) {
            (call = (call + std::string(", ")));
        }
        (call = (call + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(fn->params, i, "src/emitter-decl", 112)->name)));
    }
    (call = (call + std::string(")")));
    const auto returnType = ::app_src_emitter_types_::specializeEmitType(checkedFunctionType(fn)->returnType, context);
    if (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) == std::string("none")) {
        return (((signature + std::string(" {\n    ")) + call) + std::string(";\n}\n"));
    }
    if (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) == std::string("never")) {
        return (((signature + std::string(" {\n    ")) + call) + std::string(";\n    doof::panic(\"native never function returned\");\n}\n"));
    }
    return (((signature + std::string(" {\n    return ")) + call) + std::string(";\n}\n"));
}
std::string emitModuleValueStorage(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& initializer) {
    auto name = std::string("");
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_ = std::monostate{};
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            (name = value->name);
            (type_ = value->resolvedType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            (name = value->name);
            (type_ = value->resolvedType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            (name = value->name);
            (type_ = value->resolvedType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            (name = value->name);
            (type_ = value->resolvedType);
    }
    }
    if (((name == std::string("")) || (name == std::string("_"))) || doof::is_null(type_)) {
        return std::string("");
    }
    return ((((::app_src_emitter_types_::emitContextType(doof::unwrap_optional(type_), context) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + ((initializer == std::string("")) ? std::string("") : (std::string(" = ") + initializer))) + std::string(";\n"));
}
std::shared_ptr<::app_src_semantic_::FunctionType> checkedFunctionType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
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
    doof::unreachable();
    return std::make_shared<::app_src_semantic_::FunctionType>(std::string("function"), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> functionReturnType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
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
    doof::unreachable();
    return std::monostate{};
}
void ensureKnown(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::string& owner) {
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
                ensureKnown(doof::array_at(tuple->elements, i, "src/emitter-decl", 162), (owner + std::string(" tuple element")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_10 = union_->types;
            for (const auto& member : *_iterable_10) {
                ensureKnown(member, (owner + std::string(" union member")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_12 = function_->params;
            for (const auto& parameter : *_iterable_12) {
                ensureKnown(parameter->type_, (owner + std::string(" callback parameter")));
            }
            ensureKnown(function_->returnType, (owner + std::string(" callback return")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            ensureKnown(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), (owner + std::string(" actor state")));
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
std::string emitClassDeclaration(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& decl, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedName, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& concreteMethods) {
    if (decl->native_) {
        return std::string("");
    }
    if ((static_cast<int32_t>((decl->typeParams)->size()) > 0) && doof::is_null(context->substitution)) {
        doof::panic(((std::string("Generic class ") + decl->name) + std::string(" reached emission without a concrete instantiation")));
    }
    const auto className = ((emittedName == std::string("")) ? decl->name : emittedName);
    auto inheritance = (decl->struct_ ? std::string("") : ((std::string(" : public std::enable_shared_from_this<") + className) + std::string(">")));
    auto result = ((((emitDescriptionComment(decl->description, std::string("")) + std::string("struct ")) + className) + inheritance) + std::string(" {\n"));
    const auto& _iterable_15 = decl->fields;
    for (const auto& field : *_iterable_15) {
        for (int32_t index = 0; index < static_cast<int32_t>((field->names)->size()); ++index) {
            const auto name = doof::array_at(field->names, index, "src/emitter-decl", 188);
            const auto description = ((index < static_cast<int32_t>((field->descriptions)->size())) ? doof::array_at(field->descriptions, index, "src/emitter-decl", 189) : std::string(""));
            const auto effectiveType = fieldTypeForEmission(field);
            const auto fieldType = fieldTypeTextForEmission(field, effectiveType, context);
            ensureKnown(effectiveType, ((decl->name + std::string(".")) + name));
            (result = (result + emitDescriptionComment(description, std::string("    "))));
            (result = (((((result + std::string("    ")) + (field->static_ ? std::string("static ") : ((field->const_ && !decl->struct_) ? std::string("const ") : std::string("")))) + fieldType) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)));
            if (((!doof::is_null(field->defaultValue)) && !field->static_) && field->const_) {
                const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(effectiveType));
                (result = ((result + std::string(" = ")) + defaultText));
            }
            (result = (result + std::string(";\n")));
        }
    }
    if (hasInstanceFields(decl)) {
        (result = (((result + std::string("    ")) + className) + std::string("(")));
        auto firstParameter = true;
        const auto& _iterable_19 = decl->fields;
        for (const auto& field : *_iterable_19) {
            if (field->static_ || field->const_) {
                continue;
            }
            const auto& _iterable_17 = field->names;
            for (const auto& name : *_iterable_17) {
                if (!firstParameter) {
                    (result = (result + std::string(", ")));
                }
                (firstParameter = false);
                const auto effectiveType = fieldTypeForEmission(field);
                const auto fieldType = fieldTypeTextForEmission(field, effectiveType, context);
                (result = (((result + fieldType) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)));
            }
        }
        (result = (result + std::string(") : ")));
        auto firstInitializer = true;
        const auto& _iterable_23 = decl->fields;
        for (const auto& field : *_iterable_23) {
            if (field->static_ || field->const_) {
                continue;
            }
            const auto& _iterable_21 = field->names;
            for (const auto& name : *_iterable_21) {
                if (!firstInitializer) {
                    (result = (result + std::string(", ")));
                }
                (firstInitializer = false);
                (result = ((((result + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string("(")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(")")));
            }
        }
        (result = (result + std::string(" {}\n")));
        if (decl->struct_) {
            (result = (((result + std::string("    ")) + className) + std::string("() {}\n")));
        }
    } else if (!decl->struct_) {
        (result = (((result + std::string("    ")) + className) + std::string("() {}\n")));
    }
    const auto& _iterable_27 = decl->methods;
    for (const auto& method : *_iterable_27) {
        if (static_cast<int32_t>((method->typeParams)->size()) > 0) {
            const auto& _iterable_25 = concreteMethods;
            for (const auto& instantiation : *_iterable_25) {
                if (instantiation->declaration->name != method->name) {
                    continue;
                }
                const auto previousSubstitution = context->substitution;
                (context->substitution = instantiation->substitution);
                const auto staticPrefix = (method->static_ ? std::string("static ") : std::string(""));
                (result = (((((result + emitCallableDescription(method, std::string("    "))) + std::string("    ")) + staticPrefix) + emitFunctionSignature(method, instantiation->emittedName, context->modulePath, context, decl->typeParams)) + std::string(";\n")));
                (context->substitution = previousSubstitution);
            }
        } else {
            const auto staticPrefix = (method->static_ ? std::string("static ") : std::string(""));
            (result = (((((result + emitCallableDescription(method, std::string("    "))) + std::string("    ")) + staticPrefix) + emitFunctionSignature(method, std::string(""), context->modulePath, context, decl->typeParams)) + std::string(";\n")));
        }
    }
    if (!doof::is_null(decl->destructor_)) {
        (result = (((result + std::string("    ~")) + className) + std::string("();\n")));
    }
    (result = (result + ::app_src_emitter_json_::emitGeneratedJsonDeclarations(decl, context)));
    (result = (result + ::app_src_emitter_metadata_::emitMetadataDeclaration(decl)));
    return (result + std::string("};\n"));
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> fieldTypeForEmission(const std::shared_ptr<::app_src_ast_::ClassField>& field) {
    if (doof::is_null(field->resolvedType)) {
        doof::panic(std::string("Class field was not resolved before emission"));
    }
    return doof::unwrap_optional(field->resolvedType);
}
std::string fieldTypeTextForEmission(const std::shared_ptr<::app_src_ast_::ClassField>& field, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (field->weak_) {
        const auto specialized = ::app_src_emitter_types_::specializeEmitType(resolvedType, context);
        {
            auto _case_subject = specialized;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
                return ::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(weak_), context);
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                return ((std::string("std::weak_ptr<") + ::app_src_emitter_types_::emitClassInnerType(class_, context->modulePath)) + std::string(">"));
        }
        else {
                return ((std::string("std::weak_ptr<") + ::app_src_emitter_types_::emitContextType(specialized, context)) + std::string(">"));
        }
        }
        doof::unreachable();
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
bool hasInstanceFields(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& decl) {
    const auto& _iterable_29 = decl->fields;
    for (const auto& field : *_iterable_29) {
        if (!field->static_ && !field->const_) {
            return true;
        }
    }
    return false;
}
std::string emitStaticClassFieldDefinitions(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedOwnerName) {
    if (owner->native_ || ((static_cast<int32_t>((owner->typeParams)->size()) > 0) && doof::is_null(context->substitution))) {
        return std::string("");
    }
    const auto ownerName = ((emittedOwnerName == std::string("")) ? owner->name : emittedOwnerName);
    auto result = std::string("");
    const auto& _iterable_33 = owner->fields;
    for (const auto& field : *_iterable_33) {
        if (!field->static_ || doof::is_null(field->defaultValue)) {
            continue;
        }
        const auto& _iterable_31 = field->names;
        for (const auto& name : *_iterable_31) {
            const auto resolvedType = fieldTypeForEmission(field);
            (result = ((((((result + fieldTypeTextForEmission(field, resolvedType, context)) + std::string(" ")) + ownerName) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(";\n")));
        }
    }
    return result;
}
std::string emitDescriptionComment(const std::string& description, const std::string& indent) {
    if (description == std::string("")) {
        return std::string("");
    }
    return (((indent + std::string("// ")) + doof::string_replaceAll(description, std::string("\n"), ((std::string("\n") + indent) + std::string("// ")))) + std::string("\n"));
}
std::string emitCallableDescription(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& indent) {
    auto result = emitDescriptionComment(fn->description, indent);
    const auto& _iterable_35 = fn->params;
    for (const auto& parameter : *_iterable_35) {
        if (parameter->description != std::string("")) {
            (result = ((((((result + indent) + std::string("// @param ")) + parameter->name) + std::string(" ")) + doof::string_replaceAll(parameter->description, std::string("\n"), std::string(" "))) + std::string("\n")));
        }
    }
    return result;
}
std::string emitInterfaceAlias(const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& decl, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(decl->resolvedSymbol)) {
        doof::panic(((std::string("Interface ") + decl->name) + std::string(" was not analyzed")));
    }
    const auto implementations = decl->resolvedSymbol->implementations;
    if (static_cast<int32_t>((implementations)->size()) == 0) {
        doof::panic(((std::string("Interface ") + decl->name) + std::string(" has no implementing classes")));
    }
    auto result = (((emitDescriptionComment(decl->description, std::string("")) + std::string("using ")) + decl->name) + std::string(" = std::variant<"));
    auto first = true;
    const auto& _iterable_37 = implementations;
    for (const auto& symbol : *_iterable_37) {
        if (!first) {
            (result = (result + std::string(", ")));
        }
        (first = false);
        const auto className = (symbol->native_ ? (std::string("::") + ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName)) : ownedClassName(symbol, context->modulePath));
        (result = (((result + std::string("std::shared_ptr<")) + className) + std::string(">")));
    }
    return (result + std::string(">;\n"));
}
std::string ownedClassName(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& currentModulePath) {
    if ((symbol->module == currentModulePath) || (currentModulePath == std::string(""))) {
        return ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
    }
    return (((std::string("::") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName));
}
std::string emitClassMethodDefinition(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedOwnerName, const std::string& emittedMethodName) {
    if (method->bodyless || ((static_cast<int32_t>((method->typeParams)->size()) > 0) && doof::is_null(context->substitution))) {
        return std::string("");
    }
    const auto previous = context->currentClass;
    const auto previousNative = context->currentClassNative;
    const auto previousStruct = context->currentClassStruct;
    const auto previousReturnErrorType = context->currentReturnErrorType;
    const auto previousFunctionName = context->currentFunctionName;
    const auto previousFunctionStatic = context->currentFunctionStatic;
    const auto previousCapturedMutables = context->capturedMutables;
    (context->currentClass = owner->name);
    (context->currentClassNative = owner->native_);
    (context->currentClassStruct = owner->struct_);
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
    const auto ownerName = ((emittedOwnerName != std::string("")) ? emittedOwnerName : (owner->native_ ? ((owner->nativeCppName == std::string("")) ? owner->name : owner->nativeCppName) : owner->name));
    const auto methodName = ((emittedMethodName == std::string("")) ? ::app_src_emitter_expr_::cppIdentifier(method->name) : emittedMethodName);
    auto result = ((::app_src_emitter_context_::sourceLineDirective(method->span, context) + emitFunctionSignature(method, ((ownerName + std::string("::")) + methodName), context->modulePath, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(" {\n"));
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
    (context->currentClassStruct = previousStruct);
    (context->currentReturnErrorType = previousReturnErrorType);
    (context->currentFunctionName = previousFunctionName);
    (context->currentFunctionStatic = previousFunctionStatic);
    (context->capturedMutables = previousCapturedMutables);
    return (result + std::string("}\n"));
}
std::string emitClassDestructorDefinition(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedOwnerName) {
    if (doof::is_null(owner->destructor_) || owner->native_) {
        return std::string("");
    }
    const auto ownerName = ((emittedOwnerName == std::string("")) ? owner->name : emittedOwnerName);
    const auto previous = context->currentClass;
    const auto previousNative = context->currentClassNative;
    const auto previousStruct = context->currentClassStruct;
    (context->currentClass = owner->name);
    (context->currentClassNative = false);
    (context->currentClassStruct = owner->struct_);
    const auto result = (((((ownerName + std::string("::~")) + ownerName) + std::string("() {\n")) + ::app_src_emitter_stmt_::emitBlock(doof::unwrap_optional(owner->destructor_), 1, context)) + std::string("}\n"));
    (context->currentClass = previous);
    (context->currentClassNative = previousNative);
    (context->currentClassStruct = previousStruct);
    return result;
}
std::string emitExpressionCoverageMark(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (!context->coverageEnabled || (context->coverageModuleId < 0)) {
        return std::string("");
    }
    const auto line = std::visit([](auto&& _obj) { return _obj->span; }, expression).start.line;
    ::app_src_emitter_context_::recordCoverageLine(context, line);
    return ((((std::string("    doof::coverage::cov_mark(") + doof::to_string(context->coverageModuleId)) + std::string(", ")) + doof::to_string(line)) + std::string(");\n"));
}
}
