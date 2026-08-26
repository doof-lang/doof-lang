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
#line 24 "/src/emitter-decl.do"
std::string emitFunctionSignature(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& name, const std::string& modulePath, bool includeDefaults, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& defaultContext, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams) {
#line 25 "/src/emitter-decl.do"
    auto functionType = checkedFunctionType(fn);
#line 26 "/src/emitter-decl.do"
    if (!doof::is_null(defaultContext)) {
#line 27 "/src/emitter-decl.do"
        {
            auto _case_subject = ::app_src_emitter_types_::specializeEmitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(functionType), doof::unwrap_optional(defaultContext));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& specialized = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 28 "/src/emitter-decl.do"
                (functionType = specialized);
        }
        else {
        }
        }
    }
#line 32 "/src/emitter-decl.do"
    const auto functionName = ::app_src_emitter_expr_::cppIdentifier(((name == std::string("")) ? fn->name : name));
#line 33 "/src/emitter-decl.do"
    std::shared_ptr<std::vector<std::string>> genericParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 34 "/src/emitter-decl.do"
    const auto& _iterable_2 = ownerTypeParams;
    for (const auto& typeParam : *_iterable_2) {
#line 34 "/src/emitter-decl.do"
        genericParams->push_back(typeParam);
    }
#line 35 "/src/emitter-decl.do"
    const auto& _iterable_4 = fn->typeParams;
    for (const auto& typeParam : *_iterable_4) {
#line 35 "/src/emitter-decl.do"
        genericParams->push_back(typeParam);
    }
#line 36 "/src/emitter-decl.do"
    const auto returnType = (doof::is_null(defaultContext) ? ::app_src_emitter_types_::emitReturnType(functionType->returnType, modulePath) : ::app_src_emitter_types_::emitContextReturnType(functionType->returnType, doof::unwrap_optional(defaultContext)));
#line 37 "/src/emitter-decl.do"
    ensureKnown(functionType->returnType, (fn->name + std::string(" return type")));
#line 38 "/src/emitter-decl.do"
    auto result = ((((((std::visit([](auto&& _obj) { return _obj->kind; }, functionType->returnType) == std::string("never")) ? std::string("[[noreturn]] ") : std::string("")) + returnType) + std::string(" ")) + functionName) + std::string("("));
#line 39 "/src/emitter-decl.do"
    for (int32_t i = 0; i < static_cast<int32_t>((fn->params)->size()); ++i) {
#line 40 "/src/emitter-decl.do"
        if (i > 0) {
#line 40 "/src/emitter-decl.do"
            (result = (result + std::string(", ")));
        }
#line 41 "/src/emitter-decl.do"
        const auto parameterType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_6 = doof::array_at(fn->params, i, "src/emitter-decl", 41)->resolvedType; if (doof::is_null(_coalesce_6)) return doof::array_at(functionType->params, i, "src/emitter-decl", 41)->type_; return doof::unwrap_optional(_coalesce_6); }();
#line 42 "/src/emitter-decl.do"
        const auto parameterText = (doof::is_null(defaultContext) ? ::app_src_emitter_types_::emitParameterType(parameterType, modulePath) : ::app_src_emitter_types_::borrowParameterType(parameterType, ::app_src_emitter_types_::emitContextType(parameterType, doof::unwrap_optional(defaultContext))));
#line 45 "/src/emitter-decl.do"
        ensureKnown(parameterType, ((fn->name + std::string(" parameter ")) + doof::array_at(fn->params, i, "src/emitter-decl", 45)->name));
#line 46 "/src/emitter-decl.do"
        (result = (((result + parameterText) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(fn->params, i, "src/emitter-decl", 46)->name)));
#line 47 "/src/emitter-decl.do"
        if (includeDefaults && canEmitDefault(fn, i)) {
#line 48 "/src/emitter-decl.do"
            if (doof::is_null(defaultContext)) {
#line 48 "/src/emitter-decl.do"
                doof::panic(std::string("Default parameter emission requires an emit context"));
            }
#line 49 "/src/emitter-decl.do"
            (result = ((result + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(doof::array_at(fn->params, i, "src/emitter-decl", 49)->defaultValue), doof::unwrap_optional(defaultContext), doof::optional_value(parameterType))));
        }
    }
#line 52 "/src/emitter-decl.do"
    return (result + std::string(")"));
}
#line 55 "/src/emitter-decl.do"
std::string emitFunctionDefinition(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& name) {
#line 56 "/src/emitter-decl.do"
    if (fn->bodyless) {
#line 56 "/src/emitter-decl.do"
        return std::string("");
    }
#line 57 "/src/emitter-decl.do"
    const auto previousReturnErrorType = context->currentReturnErrorType;
#line 58 "/src/emitter-decl.do"
    const auto previousFunctionName = context->currentFunctionName;
#line 59 "/src/emitter-decl.do"
    const auto previousCapturedMutables = context->capturedMutables;
#line 60 "/src/emitter-decl.do"
    (context->currentFunctionName = fn->name);
#line 61 "/src/emitter-decl.do"
    (context->capturedMutables = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 62 "/src/emitter-decl.do"
    {
        auto _case_subject = fn->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 63 "/src/emitter-decl.do"
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInExpression(expression));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 64 "/src/emitter-decl.do"
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInBlock(block));
    }
    }
#line 66 "/src/emitter-decl.do"
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 68 "/src/emitter-decl.do"
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 69 "/src/emitter-decl.do"
                    (context->currentReturnErrorType = ::app_src_emitter_types_::emitContextType(result->errorType, context));
            }
            else {
#line 70 "/src/emitter-decl.do"
                    (context->currentReturnErrorType = std::string(""));
            }
            }
    }
    else {
#line 73 "/src/emitter-decl.do"
            (context->currentReturnErrorType = std::string(""));
    }
    }
#line 75 "/src/emitter-decl.do"
    auto result = ((((::app_src_emitter_context_::sourceLineDirective(fn->span, context) + emitCallableDescription(fn, std::string(""))) + (doof::is_null(context->substitution) ? templatePrefix(fn->typeParams) : std::string(""))) + emitFunctionSignature(fn, name, context->modulePath, false, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(" {\n"));
#line 76 "/src/emitter-decl.do"
    {
        auto _case_subject = fn->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 78 "/src/emitter-decl.do"
            (result = (result + emitExpressionCoverageMark(expression, context)));
#line 79 "/src/emitter-decl.do"
            const auto returnType = functionReturnType(fn);
#line 80 "/src/emitter-decl.do"
            if ((!doof::is_null(returnType)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(returnType)) == std::string("none"))) {
#line 80 "/src/emitter-decl.do"
                (result = (((result + std::string("    ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n")));
            } else if ((!doof::is_null(returnType)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(returnType)) == std::string("never"))) {
#line 81 "/src/emitter-decl.do"
                (result = (((result + std::string("    ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n    doof::panic(\"never function returned\");\n")));
            } else {
#line 82 "/src/emitter-decl.do"
                (result = (((result + std::string("    return ")) + ::app_src_emitter_expr_::emitExpression(expression, context, returnType)) + std::string(";\n")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 85 "/src/emitter-decl.do"
            (result = (result + ::app_src_emitter_stmt_::emitBlock(block, 1, context)));
#line 86 "/src/emitter-decl.do"
            const auto returnType = functionReturnType(fn);
#line 87 "/src/emitter-decl.do"
            if ((!doof::is_null(returnType)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(returnType)) == std::string("never"))) {
#line 87 "/src/emitter-decl.do"
                (result = (result + std::string("    doof::panic(\"never function returned\");\n")));
            }
    }
    }
#line 90 "/src/emitter-decl.do"
    (context->currentReturnErrorType = previousReturnErrorType);
#line 91 "/src/emitter-decl.do"
    (context->currentFunctionName = previousFunctionName);
#line 92 "/src/emitter-decl.do"
    (context->capturedMutables = previousCapturedMutables);
#line 93 "/src/emitter-decl.do"
    return (result + std::string("}\n"));
}
#line 96 "/src/emitter-decl.do"
std::string emitFunctionDeclaration(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& name, const std::string& modulePath, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& defaultContext) {
#line 97 "/src/emitter-decl.do"
    const auto template_ = ((doof::is_null(defaultContext) || doof::is_null(defaultContext->substitution)) ? templatePrefix(fn->typeParams) : std::string(""));
#line 98 "/src/emitter-decl.do"
    return (((emitCallableDescription(fn, std::string("")) + template_) + emitFunctionSignature(fn, name, modulePath, true, defaultContext, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(";\n"));
}
#line 105 "/src/emitter-decl.do"
std::string emitNativeFunctionAdapterDefinition(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& emittedName, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 106 "/src/emitter-decl.do"
    const auto signature = emitFunctionSignature(fn, emittedName, context->modulePath, false, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 107 "/src/emitter-decl.do"
    const auto nativeName = ((fn->nativeCppName == std::string("")) ? fn->name : fn->nativeCppName);
#line 108 "/src/emitter-decl.do"
    auto call = ((std::string("::") + nativeName) + std::string("("));
#line 109 "/src/emitter-decl.do"
    for (int32_t i = 0; i < static_cast<int32_t>((fn->params)->size()); ++i) {
#line 110 "/src/emitter-decl.do"
        if (i > 0) {
#line 110 "/src/emitter-decl.do"
            (call = (call + std::string(", ")));
        }
#line 111 "/src/emitter-decl.do"
        (call = (call + ::app_src_emitter_expr_::cppIdentifier(doof::array_at(fn->params, i, "src/emitter-decl", 111)->name)));
    }
#line 113 "/src/emitter-decl.do"
    (call = (call + std::string(")")));
#line 114 "/src/emitter-decl.do"
    const auto returnType = ::app_src_emitter_types_::specializeEmitType(checkedFunctionType(fn)->returnType, context);
#line 115 "/src/emitter-decl.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) == std::string("none")) {
#line 115 "/src/emitter-decl.do"
        return (((signature + std::string(" {\n    ")) + call) + std::string(";\n}\n"));
    }
#line 116 "/src/emitter-decl.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) == std::string("never")) {
#line 116 "/src/emitter-decl.do"
        return (((signature + std::string(" {\n    ")) + call) + std::string(";\n    doof::panic(\"native never function returned\");\n}\n"));
    }
#line 117 "/src/emitter-decl.do"
    return (((signature + std::string(" {\n    return ")) + call) + std::string(";\n}\n"));
}
#line 120 "/src/emitter-decl.do"
std::string emitValueDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 121 "/src/emitter-decl.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 122 "/src/emitter-decl.do"
            return ((((emitDescriptionComment(const_->description, std::string("")) + valuePrefix(const_->name, doof::unwrap_optional(const_->resolvedType), false, context)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(const_->value, context, const_->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 123 "/src/emitter-decl.do"
            return ((((emitDescriptionComment(readonly_->description, std::string("")) + valuePrefix(readonly_->name, doof::unwrap_optional(readonly_->resolvedType), false, context)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(readonly_->value, context, readonly_->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 124 "/src/emitter-decl.do"
            return (((valuePrefix(binding->name, doof::unwrap_optional(binding->resolvedType), false, context) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(binding->value, context, binding->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 125 "/src/emitter-decl.do"
            return (((valuePrefix(let_->name, doof::unwrap_optional(let_->resolvedType), true, context) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(let_->value, context, let_->resolvedType)) + std::string(";\n"));
    }
    }
    doof::unreachable();
#line 127 "/src/emitter-decl.do"
    return std::string("");
}
#line 131 "/src/emitter-decl.do"
std::string emitModuleValueStorage(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& initializer) {
#line 136 "/src/emitter-decl.do"
    auto name = std::string("");
#line 137 "/src/emitter-decl.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_ = std::monostate{};
#line 138 "/src/emitter-decl.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 139 "/src/emitter-decl.do"
            (name = value->name);
#line 139 "/src/emitter-decl.do"
            (type_ = value->resolvedType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 140 "/src/emitter-decl.do"
            (name = value->name);
#line 140 "/src/emitter-decl.do"
            (type_ = value->resolvedType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 141 "/src/emitter-decl.do"
            (name = value->name);
#line 141 "/src/emitter-decl.do"
            (type_ = value->resolvedType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 142 "/src/emitter-decl.do"
            (name = value->name);
#line 142 "/src/emitter-decl.do"
            (type_ = value->resolvedType);
    }
    }
#line 144 "/src/emitter-decl.do"
    if (((name == std::string("")) || (name == std::string("_"))) || doof::is_null(type_)) {
#line 144 "/src/emitter-decl.do"
        return std::string("");
    }
#line 145 "/src/emitter-decl.do"
    return ((((::app_src_emitter_types_::emitContextType(doof::unwrap_optional(type_), context) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + ((initializer == std::string("")) ? std::string("") : (std::string(" = ") + initializer))) + std::string(";\n"));
}
#line 149 "/src/emitter-decl.do"
std::string valuePrefix(const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, bool mutable_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 150 "/src/emitter-decl.do"
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 151 "/src/emitter-decl.do"
            return ((((mutable_ ? std::string("") : std::string("const ")) + ::app_src_emitter_types_::emitContextType(resolvedType, context)) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
#line 152 "/src/emitter-decl.do"
            return ((((mutable_ ? std::string("") : std::string("const ")) + ::app_src_emitter_types_::emitContextType(resolvedType, context)) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name));
    }
    else {
#line 153 "/src/emitter-decl.do"
            return ((mutable_ ? std::string("auto ") : std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(name));
    }
    }
    doof::unreachable();
#line 155 "/src/emitter-decl.do"
    return (std::string("auto ") + ::app_src_emitter_expr_::cppIdentifier(name));
}
#line 158 "/src/emitter-decl.do"
std::shared_ptr<::app_src_semantic_::FunctionType> checkedFunctionType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 159 "/src/emitter-decl.do"
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 160 "/src/emitter-decl.do"
            return resolved;
    }
    else {
#line 161 "/src/emitter-decl.do"
            doof::panic(((std::string("Function ") + fn->name) + std::string(" was not checked before emission")));
    }
    }
    doof::unreachable();
#line 163 "/src/emitter-decl.do"
    return std::make_shared<::app_src_semantic_::FunctionType>(std::string("function"), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
#line 166 "/src/emitter-decl.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> functionReturnType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 167 "/src/emitter-decl.do"
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 168 "/src/emitter-decl.do"
            return doof::optional_value(function_->returnType);
    }
    else {
#line 169 "/src/emitter-decl.do"
            return std::monostate{};
    }
    }
    doof::unreachable();
#line 171 "/src/emitter-decl.do"
    return std::monostate{};
}
#line 174 "/src/emitter-decl.do"
bool canEmitDefault(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, int32_t index) {
#line 175 "/src/emitter-decl.do"
    if (doof::is_null(doof::array_at(fn->params, index, "src/emitter-decl", 175)->defaultValue)) {
#line 175 "/src/emitter-decl.do"
        return false;
    }
#line 176 "/src/emitter-decl.do"
    for (int32_t i = (index + 1); i < static_cast<int32_t>((fn->params)->size()); ++i) {
#line 177 "/src/emitter-decl.do"
        if (doof::is_null(doof::array_at(fn->params, i, "src/emitter-decl", 177)->defaultValue)) {
#line 177 "/src/emitter-decl.do"
            return false;
        }
    }
#line 179 "/src/emitter-decl.do"
    return true;
}
#line 182 "/src/emitter-decl.do"
void ensureKnown(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::string& owner) {
#line 183 "/src/emitter-decl.do"
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 184 "/src/emitter-decl.do"
            doof::panic((std::string("Cannot emit unresolved type for ") + owner));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 185 "/src/emitter-decl.do"
            ensureKnown(array->elementType, (owner + std::string(" element")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 186 "/src/emitter-decl.do"
            ensureKnown(set_->elementType, (owner + std::string(" element")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 188 "/src/emitter-decl.do"
            for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
#line 188 "/src/emitter-decl.do"
                ensureKnown(doof::array_at(tuple->elements, i, "src/emitter-decl", 188), (owner + std::string(" tuple element")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 191 "/src/emitter-decl.do"
            const auto& _iterable_11 = union_->types;
            for (const auto& member : *_iterable_11) {
#line 191 "/src/emitter-decl.do"
                ensureKnown(member, (owner + std::string(" union member")));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 194 "/src/emitter-decl.do"
            const auto& _iterable_13 = function_->params;
            for (const auto& parameter : *_iterable_13) {
#line 194 "/src/emitter-decl.do"
                ensureKnown(parameter->type_, (owner + std::string(" callback parameter")));
            }
#line 195 "/src/emitter-decl.do"
            ensureKnown(function_->returnType, (owner + std::string(" callback return")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 197 "/src/emitter-decl.do"
            ensureKnown(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), (owner + std::string(" actor state")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 198 "/src/emitter-decl.do"
            ensureKnown(promise->valueType, (owner + std::string(" promise value")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 199 "/src/emitter-decl.do"
            ensureKnown(weak_->inner, (owner + std::string(" weak target")));
    }
    else {
    }
    }
}
#line 204 "/src/emitter-decl.do"
std::string emitClassDeclaration(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& decl, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedName, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& concreteMethods) {
#line 205 "/src/emitter-decl.do"
    if (decl->native_) {
#line 205 "/src/emitter-decl.do"
        return std::string("");
    }
#line 206 "/src/emitter-decl.do"
    const auto className = ((emittedName == std::string("")) ? decl->name : emittedName);
#line 207 "/src/emitter-decl.do"
    auto ownershipName = className;
#line 208 "/src/emitter-decl.do"
    if ((emittedName == std::string("")) && (static_cast<int32_t>((decl->typeParams)->size()) > 0)) {
#line 209 "/src/emitter-decl.do"
        (ownershipName = (ownershipName + std::string("<")));
#line 210 "/src/emitter-decl.do"
        for (int32_t index = 0; index < static_cast<int32_t>((decl->typeParams)->size()); ++index) {
#line 211 "/src/emitter-decl.do"
            if (index > 0) {
#line 211 "/src/emitter-decl.do"
                (ownershipName = (ownershipName + std::string(", ")));
            }
#line 212 "/src/emitter-decl.do"
            (ownershipName = (ownershipName + doof::array_at(decl->typeParams, index, "src/emitter-decl", 212)));
        }
#line 214 "/src/emitter-decl.do"
        (ownershipName = (ownershipName + std::string(">")));
    }
#line 216 "/src/emitter-decl.do"
    auto inheritance = (decl->struct_ ? std::string("") : ((std::string(" : public std::enable_shared_from_this<") + ownershipName) + std::string(">")));
#line 217 "/src/emitter-decl.do"
    auto result = (((((emitDescriptionComment(decl->description, std::string("")) + (doof::is_null(context->substitution) ? templatePrefix(decl->typeParams) : std::string(""))) + std::string("struct ")) + className) + inheritance) + std::string(" {\n"));
#line 218 "/src/emitter-decl.do"
    const auto& _iterable_16 = decl->fields;
    for (const auto& field : *_iterable_16) {
#line 219 "/src/emitter-decl.do"
        for (int32_t index = 0; index < static_cast<int32_t>((field->names)->size()); ++index) {
#line 220 "/src/emitter-decl.do"
            const auto name = doof::array_at(field->names, index, "src/emitter-decl", 220);
#line 221 "/src/emitter-decl.do"
            const auto description = ((index < static_cast<int32_t>((field->descriptions)->size())) ? doof::array_at(field->descriptions, index, "src/emitter-decl", 221) : std::string(""));
#line 222 "/src/emitter-decl.do"
            const auto effectiveType = fieldTypeForEmission(field);
#line 223 "/src/emitter-decl.do"
            const auto fieldType = fieldTypeTextForEmission(field, effectiveType, context);
#line 224 "/src/emitter-decl.do"
            ensureKnown(effectiveType, ((decl->name + std::string(".")) + name));
#line 225 "/src/emitter-decl.do"
            (result = (result + emitDescriptionComment(description, std::string("    "))));
#line 229 "/src/emitter-decl.do"
            (result = (((((result + std::string("    ")) + (field->static_ ? std::string("static ") : ((field->const_ && !decl->struct_) ? std::string("const ") : std::string("")))) + fieldType) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)));
#line 230 "/src/emitter-decl.do"
            if ((!doof::is_null(field->defaultValue)) && !field->static_) {
#line 231 "/src/emitter-decl.do"
                const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(effectiveType));
#line 232 "/src/emitter-decl.do"
                if (!defaultNeedsImportedDefinition(defaultText, context)) {
#line 232 "/src/emitter-decl.do"
                    (result = ((result + std::string(" = ")) + defaultText));
                }
            }
#line 234 "/src/emitter-decl.do"
            (result = (result + std::string(";\n")));
        }
    }
#line 237 "/src/emitter-decl.do"
    if (hasInstanceFields(decl)) {
#line 241 "/src/emitter-decl.do"
        auto lastRequiredParameter = -1;
#line 242 "/src/emitter-decl.do"
        auto parameterIndex = 0;
#line 243 "/src/emitter-decl.do"
        const auto& _iterable_19 = decl->fields;
        for (const auto& field : *_iterable_19) {
#line 244 "/src/emitter-decl.do"
            if (field->static_ || field->const_) {
#line 244 "/src/emitter-decl.do"
                continue;
            }
#line 245 "/src/emitter-decl.do"
            const auto& _iterable_21 = field->names;
            for (const auto& name : *_iterable_21) {
#line 246 "/src/emitter-decl.do"
                if (doof::is_null(field->defaultValue)) {
#line 246 "/src/emitter-decl.do"
                    (lastRequiredParameter = parameterIndex);
                }
#line 247 "/src/emitter-decl.do"
                (parameterIndex = (parameterIndex + 1));
            }
        }
#line 250 "/src/emitter-decl.do"
        auto suppressTrailingDefaults = false;
#line 251 "/src/emitter-decl.do"
        (parameterIndex = 0);
#line 252 "/src/emitter-decl.do"
        const auto& _iterable_23 = decl->fields;
        for (const auto& field : *_iterable_23) {
#line 253 "/src/emitter-decl.do"
            if (field->static_ || field->const_) {
#line 253 "/src/emitter-decl.do"
                continue;
            }
#line 254 "/src/emitter-decl.do"
            const auto& _iterable_25 = field->names;
            for (const auto& name : *_iterable_25) {
#line 255 "/src/emitter-decl.do"
                if ((parameterIndex > lastRequiredParameter) && (!doof::is_null(field->defaultValue))) {
#line 256 "/src/emitter-decl.do"
                    const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(fieldTypeForEmission(field)));
#line 257 "/src/emitter-decl.do"
                    if (defaultNeedsImportedDefinition(defaultText, context)) {
#line 257 "/src/emitter-decl.do"
                        (suppressTrailingDefaults = true);
                    }
                }
#line 259 "/src/emitter-decl.do"
                (parameterIndex = (parameterIndex + 1));
            }
        }
#line 262 "/src/emitter-decl.do"
        (result = (((result + std::string("    ")) + className) + std::string("(")));
#line 263 "/src/emitter-decl.do"
        auto firstParameter = true;
#line 264 "/src/emitter-decl.do"
        (parameterIndex = 0);
#line 265 "/src/emitter-decl.do"
        const auto& _iterable_27 = decl->fields;
        for (const auto& field : *_iterable_27) {
#line 266 "/src/emitter-decl.do"
            if (field->static_ || field->const_) {
#line 266 "/src/emitter-decl.do"
                continue;
            }
#line 267 "/src/emitter-decl.do"
            const auto& _iterable_29 = field->names;
            for (const auto& name : *_iterable_29) {
#line 268 "/src/emitter-decl.do"
                if (!firstParameter) {
#line 268 "/src/emitter-decl.do"
                    (result = (result + std::string(", ")));
                }
#line 269 "/src/emitter-decl.do"
                (firstParameter = false);
#line 270 "/src/emitter-decl.do"
                const auto effectiveType = fieldTypeForEmission(field);
#line 271 "/src/emitter-decl.do"
                const auto fieldType = fieldTypeTextForEmission(field, effectiveType, context);
#line 272 "/src/emitter-decl.do"
                (result = (((result + fieldType) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)));
#line 273 "/src/emitter-decl.do"
                if ((!suppressTrailingDefaults && (parameterIndex > lastRequiredParameter)) && (!doof::is_null(field->defaultValue))) {
#line 274 "/src/emitter-decl.do"
                    const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(effectiveType));
#line 275 "/src/emitter-decl.do"
                    if (!defaultNeedsImportedDefinition(defaultText, context)) {
#line 275 "/src/emitter-decl.do"
                        (result = ((result + std::string(" = ")) + defaultText));
                    }
                }
#line 277 "/src/emitter-decl.do"
                (parameterIndex = (parameterIndex + 1));
            }
        }
#line 280 "/src/emitter-decl.do"
        (result = (result + std::string(") : ")));
#line 281 "/src/emitter-decl.do"
        auto firstInitializer = true;
#line 282 "/src/emitter-decl.do"
        const auto& _iterable_31 = decl->fields;
        for (const auto& field : *_iterable_31) {
#line 283 "/src/emitter-decl.do"
            if (field->static_ || field->const_) {
#line 283 "/src/emitter-decl.do"
                continue;
            }
#line 284 "/src/emitter-decl.do"
            const auto& _iterable_33 = field->names;
            for (const auto& name : *_iterable_33) {
#line 285 "/src/emitter-decl.do"
                if (!firstInitializer) {
#line 285 "/src/emitter-decl.do"
                    (result = (result + std::string(", ")));
                }
#line 286 "/src/emitter-decl.do"
                (firstInitializer = false);
#line 287 "/src/emitter-decl.do"
                (result = ((((result + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string("(")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(")")));
            }
        }
#line 290 "/src/emitter-decl.do"
        (result = (result + std::string(" {}\n")));
#line 291 "/src/emitter-decl.do"
        if (decl->struct_ && (lastRequiredParameter >= 0)) {
#line 292 "/src/emitter-decl.do"
            (result = (((result + std::string("    ")) + className) + std::string("() {}\n")));
        }
    } else if (!decl->struct_) {
#line 295 "/src/emitter-decl.do"
        (result = (((result + std::string("    ")) + className) + std::string("() {}\n")));
    }
#line 297 "/src/emitter-decl.do"
    const auto& _iterable_35 = decl->methods;
    for (const auto& method : *_iterable_35) {
#line 298 "/src/emitter-decl.do"
        if (static_cast<int32_t>((method->typeParams)->size()) > 0) {
#line 299 "/src/emitter-decl.do"
            if (static_cast<int32_t>((decl->typeParams)->size()) == 0) {
#line 300 "/src/emitter-decl.do"
                (result = (result + emitInlineClassMethod(decl, method, context, std::string(""))));
            } else {
#line 302 "/src/emitter-decl.do"
                const auto& _iterable_37 = concreteMethods;
                for (const auto& instantiation : *_iterable_37) {
#line 303 "/src/emitter-decl.do"
                    if (instantiation->declaration->name != method->name) {
#line 303 "/src/emitter-decl.do"
                        continue;
                    }
#line 304 "/src/emitter-decl.do"
                    const auto previousSubstitution = context->substitution;
#line 305 "/src/emitter-decl.do"
                    (context->substitution = instantiation->substitution);
#line 306 "/src/emitter-decl.do"
                    (result = (result + emitInlineClassMethod(decl, method, context, instantiation->emittedName)));
#line 307 "/src/emitter-decl.do"
                    (context->substitution = previousSubstitution);
                }
            }
        } else if ((static_cast<int32_t>((decl->typeParams)->size()) > 0) || (!doof::is_null(context->substitution))) {
#line 311 "/src/emitter-decl.do"
            (result = (result + emitInlineClassMethod(decl, method, context, std::string(""))));
        } else {
#line 313 "/src/emitter-decl.do"
            const auto staticPrefix = (method->static_ ? std::string("static ") : std::string(""));
#line 314 "/src/emitter-decl.do"
            (result = ((((((result + emitCallableDescription(method, std::string("    "))) + std::string("    ")) + templatePrefix(method->typeParams)) + staticPrefix) + emitFunctionSignature(method, std::string(""), context->modulePath, true, context, decl->typeParams)) + std::string(";\n")));
        }
    }
#line 317 "/src/emitter-decl.do"
    if (!doof::is_null(decl->destructor_)) {
#line 318 "/src/emitter-decl.do"
        (result = (((result + std::string("    ~")) + className) + std::string("() {\n")));
#line 319 "/src/emitter-decl.do"
        (result = (result + ::app_src_emitter_stmt_::emitBlock(doof::unwrap_optional(decl->destructor_), 2, context)));
#line 320 "/src/emitter-decl.do"
        (result = (result + std::string("    }\n")));
    }
#line 322 "/src/emitter-decl.do"
    (result = (result + ::app_src_emitter_json_::emitGeneratedJsonDeclarations(decl, context)));
#line 323 "/src/emitter-decl.do"
    (result = (result + ::app_src_emitter_metadata_::emitMetadataDeclaration(decl)));
#line 324 "/src/emitter-decl.do"
    return (result + std::string("};\n"));
}
#line 330 "/src/emitter-decl.do"
bool defaultNeedsImportedDefinition(const std::string& defaultText, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 331 "/src/emitter-decl.do"
    if (!context->importedDefinitionNeedlesReady) {
#line 332 "/src/emitter-decl.do"
        const auto& _iterable_39 = context->imports;
        for (const auto& imported : *_iterable_39) {
#line 333 "/src/emitter-decl.do"
            const auto needle = ((std::string("::") + ::app_src_emitter_names_::moduleNamespace(imported->sourceModule)) + std::string("::"));
#line 334 "/src/emitter-decl.do"
            auto retained = false;
#line 335 "/src/emitter-decl.do"
            const auto& _iterable_41 = context->importedDefinitionNeedles;
            for (const auto& existing : *_iterable_41) {
#line 335 "/src/emitter-decl.do"
                if (existing == needle) {
#line 335 "/src/emitter-decl.do"
                    (retained = true);
                }
            }
#line 336 "/src/emitter-decl.do"
            if (!retained) {
#line 336 "/src/emitter-decl.do"
                context->importedDefinitionNeedles->push_back(needle);
            }
        }
#line 338 "/src/emitter-decl.do"
        (context->importedDefinitionNeedlesReady = true);
    }
#line 340 "/src/emitter-decl.do"
    const auto& _iterable_43 = context->importedDefinitionNeedles;
    for (const auto& needle : *_iterable_43) {
#line 341 "/src/emitter-decl.do"
        if (doof::string_contains(defaultText, needle)) {
#line 341 "/src/emitter-decl.do"
            return true;
        }
    }
#line 343 "/src/emitter-decl.do"
    return false;
}
#line 346 "/src/emitter-decl.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> fieldTypeForEmission(const std::shared_ptr<::app_src_ast_::ClassField>& field) {
#line 347 "/src/emitter-decl.do"
    if (doof::is_null(field->resolvedType)) {
#line 347 "/src/emitter-decl.do"
        doof::panic(std::string("Class field was not resolved before emission"));
    }
#line 348 "/src/emitter-decl.do"
    return doof::unwrap_optional(field->resolvedType);
}
#line 351 "/src/emitter-decl.do"
std::string fieldTypeTextForEmission(const std::shared_ptr<::app_src_ast_::ClassField>& field, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 352 "/src/emitter-decl.do"
    if (field->weak_) {
#line 353 "/src/emitter-decl.do"
        const auto specialized = ::app_src_emitter_types_::specializeEmitType(resolvedType, context);
#line 354 "/src/emitter-decl.do"
        {
            auto _case_subject = specialized;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 355 "/src/emitter-decl.do"
                return ::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(weak_), context);
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 356 "/src/emitter-decl.do"
                return ((std::string("std::weak_ptr<") + ::app_src_emitter_types_::emitClassInnerType(class_, context->modulePath)) + std::string(">"));
        }
        else {
#line 357 "/src/emitter-decl.do"
                return ((std::string("std::weak_ptr<") + ::app_src_emitter_types_::emitContextType(specialized, context)) + std::string(">"));
        }
        }
        doof::unreachable();
    }
#line 360 "/src/emitter-decl.do"
    const auto typeText = ::app_src_emitter_types_::emitContextType(resolvedType, context);
#line 361 "/src/emitter-decl.do"
    if (doof::is_null(field->defaultValue)) {
#line 361 "/src/emitter-decl.do"
        return typeText;
    }
#line 362 "/src/emitter-decl.do"
    const auto defaultText = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, doof::optional_value(resolvedType));
#line 363 "/src/emitter-decl.do"
    if (((defaultText == std::string("std::monostate{}")) && doof::string_startsWith(typeText, std::string("std::variant<"))) && !doof::string_startsWith(typeText, std::string("std::variant<std::monostate"))) {
#line 364 "/src/emitter-decl.do"
        return (std::string("std::variant<std::monostate, ") + doof::string_substring(typeText, 13, 1000000));
    }
#line 366 "/src/emitter-decl.do"
    return typeText;
}
#line 369 "/src/emitter-decl.do"
bool hasInstanceFields(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& decl) {
#line 370 "/src/emitter-decl.do"
    const auto& _iterable_45 = decl->fields;
    for (const auto& field : *_iterable_45) {
#line 370 "/src/emitter-decl.do"
        if (!field->static_ && !field->const_) {
#line 370 "/src/emitter-decl.do"
            return true;
        }
    }
#line 371 "/src/emitter-decl.do"
    return false;
}
#line 374 "/src/emitter-decl.do"
std::string emitStaticClassFieldDefinitions(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 375 "/src/emitter-decl.do"
    if (owner->native_ || (static_cast<int32_t>((owner->typeParams)->size()) > 0)) {
#line 375 "/src/emitter-decl.do"
        return std::string("");
    }
#line 376 "/src/emitter-decl.do"
    auto result = std::string("");
#line 377 "/src/emitter-decl.do"
    const auto& _iterable_47 = owner->fields;
    for (const auto& field : *_iterable_47) {
#line 378 "/src/emitter-decl.do"
        if (!field->static_ || doof::is_null(field->defaultValue)) {
#line 378 "/src/emitter-decl.do"
            continue;
        }
#line 379 "/src/emitter-decl.do"
        const auto& _iterable_49 = field->names;
        for (const auto& name : *_iterable_49) {
#line 380 "/src/emitter-decl.do"
            const auto resolvedType = fieldTypeForEmission(field);
#line 381 "/src/emitter-decl.do"
            (result = ((((((result + fieldTypeTextForEmission(field, resolvedType, context)) + std::string(" ")) + owner->name) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(";\n")));
        }
    }
#line 384 "/src/emitter-decl.do"
    return result;
}
#line 387 "/src/emitter-decl.do"
std::string emitInlineClassMethod(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedName) {
#line 388 "/src/emitter-decl.do"
    const auto previous = context->currentClass;
#line 389 "/src/emitter-decl.do"
    const auto previousNative = context->currentClassNative;
#line 390 "/src/emitter-decl.do"
    const auto previousFunctionName = context->currentFunctionName;
#line 391 "/src/emitter-decl.do"
    const auto previousFunctionStatic = context->currentFunctionStatic;
#line 392 "/src/emitter-decl.do"
    const auto previousGenericTypeParams = context->genericTypeParams;
#line 393 "/src/emitter-decl.do"
    const auto previousCapturedMutables = context->capturedMutables;
#line 394 "/src/emitter-decl.do"
    (context->currentClass = owner->name);
#line 395 "/src/emitter-decl.do"
    (context->currentClassNative = owner->native_);
#line 396 "/src/emitter-decl.do"
    (context->currentFunctionName = method->name);
#line 397 "/src/emitter-decl.do"
    (context->currentFunctionStatic = method->static_);
#line 398 "/src/emitter-decl.do"
    (context->genericTypeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 399 "/src/emitter-decl.do"
    (context->capturedMutables = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 400 "/src/emitter-decl.do"
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 401 "/src/emitter-decl.do"
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInExpression(expression));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 402 "/src/emitter-decl.do"
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInBlock(block));
    }
    }
#line 404 "/src/emitter-decl.do"
    const auto& _iterable_51 = owner->typeParams;
    for (const auto& typeParam : *_iterable_51) {
#line 404 "/src/emitter-decl.do"
        context->genericTypeParams->push_back(typeParam);
    }
#line 405 "/src/emitter-decl.do"
    const auto& _iterable_53 = method->typeParams;
    for (const auto& typeParam : *_iterable_53) {
#line 405 "/src/emitter-decl.do"
        context->genericTypeParams->push_back(typeParam);
    }
#line 406 "/src/emitter-decl.do"
    const auto staticPrefix = (method->static_ ? std::string("static ") : std::string(""));
#line 407 "/src/emitter-decl.do"
    const auto template_ = (doof::is_null(context->substitution) ? templatePrefix(method->typeParams) : std::string(""));
#line 408 "/src/emitter-decl.do"
    auto result = ((((((::app_src_emitter_context_::sourceLineDirective(method->span, context) + emitCallableDescription(method, std::string("    "))) + std::string("    ")) + template_) + staticPrefix) + emitFunctionSignature(method, emittedName, context->modulePath, true, context, owner->typeParams)) + std::string(" {\n"));
#line 409 "/src/emitter-decl.do"
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 410 "/src/emitter-decl.do"
            (result = (((result + std::string("        return ")) + ::app_src_emitter_expr_::emitExpression(expression, context, functionReturnType(method))) + std::string(";\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 411 "/src/emitter-decl.do"
            (result = (result + ::app_src_emitter_stmt_::emitBlock(block, 2, context)));
    }
    }
#line 413 "/src/emitter-decl.do"
    (result = (result + std::string("    }\n")));
#line 414 "/src/emitter-decl.do"
    (context->currentClass = previous);
#line 415 "/src/emitter-decl.do"
    (context->currentClassNative = previousNative);
#line 416 "/src/emitter-decl.do"
    (context->currentFunctionName = previousFunctionName);
#line 417 "/src/emitter-decl.do"
    (context->currentFunctionStatic = previousFunctionStatic);
#line 418 "/src/emitter-decl.do"
    (context->genericTypeParams = previousGenericTypeParams);
#line 419 "/src/emitter-decl.do"
    (context->capturedMutables = previousCapturedMutables);
#line 420 "/src/emitter-decl.do"
    return result;
}
#line 423 "/src/emitter-decl.do"
std::string templatePrefix(const std::shared_ptr<std::vector<std::string>>& typeParams) {
#line 424 "/src/emitter-decl.do"
    if (static_cast<int32_t>((typeParams)->size()) == 0) {
#line 424 "/src/emitter-decl.do"
        return std::string("");
    }
#line 425 "/src/emitter-decl.do"
    auto result = std::string("template <");
#line 426 "/src/emitter-decl.do"
    for (int32_t i = 0; i < static_cast<int32_t>((typeParams)->size()); ++i) {
#line 427 "/src/emitter-decl.do"
        if (i > 0) {
#line 427 "/src/emitter-decl.do"
            (result = (result + std::string(", ")));
        }
#line 428 "/src/emitter-decl.do"
        (result = ((result + std::string("typename ")) + doof::array_at(typeParams, i, "src/emitter-decl", 428)));
    }
#line 430 "/src/emitter-decl.do"
    return (result + std::string(">\n"));
}
#line 434 "/src/emitter-decl.do"
std::string emitDescriptionComment(const std::string& description, const std::string& indent) {
#line 435 "/src/emitter-decl.do"
    if (description == std::string("")) {
#line 435 "/src/emitter-decl.do"
        return std::string("");
    }
#line 436 "/src/emitter-decl.do"
    return (((indent + std::string("// ")) + doof::string_replaceAll(description, std::string("\n"), ((std::string("\n") + indent) + std::string("// ")))) + std::string("\n"));
}
#line 439 "/src/emitter-decl.do"
std::string emitCallableDescription(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& indent) {
#line 440 "/src/emitter-decl.do"
    auto result = emitDescriptionComment(fn->description, indent);
#line 441 "/src/emitter-decl.do"
    const auto& _iterable_56 = fn->params;
    for (const auto& parameter : *_iterable_56) {
#line 442 "/src/emitter-decl.do"
        if (parameter->description != std::string("")) {
#line 443 "/src/emitter-decl.do"
            (result = ((((((result + indent) + std::string("// @param ")) + parameter->name) + std::string(" ")) + doof::string_replaceAll(parameter->description, std::string("\n"), std::string(" "))) + std::string("\n")));
        }
    }
#line 446 "/src/emitter-decl.do"
    return result;
}
#line 449 "/src/emitter-decl.do"
std::string emitInterfaceAlias(const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& decl, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 450 "/src/emitter-decl.do"
    if (doof::is_null(decl->resolvedSymbol)) {
#line 450 "/src/emitter-decl.do"
        doof::panic(((std::string("Interface ") + decl->name) + std::string(" was not analyzed")));
    }
#line 451 "/src/emitter-decl.do"
    const auto implementations = decl->resolvedSymbol->implementations;
#line 452 "/src/emitter-decl.do"
    if (static_cast<int32_t>((implementations)->size()) == 0) {
#line 452 "/src/emitter-decl.do"
        doof::panic(((std::string("Interface ") + decl->name) + std::string(" has no implementing classes")));
    }
#line 453 "/src/emitter-decl.do"
    auto result = (((emitDescriptionComment(decl->description, std::string("")) + std::string("using ")) + decl->name) + std::string(" = std::variant<"));
#line 454 "/src/emitter-decl.do"
    auto first = true;
#line 455 "/src/emitter-decl.do"
    const auto& _iterable_58 = implementations;
    for (const auto& symbol : *_iterable_58) {
#line 456 "/src/emitter-decl.do"
        if (!first) {
#line 456 "/src/emitter-decl.do"
            (result = (result + std::string(", ")));
        }
#line 457 "/src/emitter-decl.do"
        (first = false);
#line 458 "/src/emitter-decl.do"
        const auto className = (symbol->native_ ? (std::string("::") + ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName)) : ownedClassName(symbol, context->modulePath));
#line 459 "/src/emitter-decl.do"
        (result = (((result + std::string("std::shared_ptr<")) + className) + std::string(">")));
    }
#line 461 "/src/emitter-decl.do"
    return (result + std::string(">;\n"));
}
#line 464 "/src/emitter-decl.do"
std::string ownedClassName(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& currentModulePath) {
#line 465 "/src/emitter-decl.do"
    if ((symbol->module == currentModulePath) || (currentModulePath == std::string(""))) {
#line 465 "/src/emitter-decl.do"
        return ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
    }
#line 466 "/src/emitter-decl.do"
    return (((std::string("::") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName));
}
#line 469 "/src/emitter-decl.do"
std::string emitClassMethodDefinition(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 470 "/src/emitter-decl.do"
    if (method->bodyless || (static_cast<int32_t>((method->typeParams)->size()) > 0)) {
#line 470 "/src/emitter-decl.do"
        return std::string("");
    }
#line 471 "/src/emitter-decl.do"
    const auto previous = context->currentClass;
#line 472 "/src/emitter-decl.do"
    const auto previousNative = context->currentClassNative;
#line 473 "/src/emitter-decl.do"
    const auto previousReturnErrorType = context->currentReturnErrorType;
#line 474 "/src/emitter-decl.do"
    const auto previousFunctionName = context->currentFunctionName;
#line 475 "/src/emitter-decl.do"
    const auto previousFunctionStatic = context->currentFunctionStatic;
#line 476 "/src/emitter-decl.do"
    const auto previousCapturedMutables = context->capturedMutables;
#line 477 "/src/emitter-decl.do"
    (context->currentClass = owner->name);
#line 478 "/src/emitter-decl.do"
    (context->currentClassNative = owner->native_);
#line 479 "/src/emitter-decl.do"
    (context->currentFunctionName = method->name);
#line 480 "/src/emitter-decl.do"
    (context->currentFunctionStatic = method->static_);
#line 481 "/src/emitter-decl.do"
    (context->capturedMutables = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 482 "/src/emitter-decl.do"
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 483 "/src/emitter-decl.do"
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInExpression(expression));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 484 "/src/emitter-decl.do"
            (context->capturedMutables = ::app_src_emitter_expr_lambda_::scanCapturedMutablesInBlock(block));
    }
    }
#line 486 "/src/emitter-decl.do"
    {
        auto _case_subject = doof::unwrap_optional(method->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 488 "/src/emitter-decl.do"
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 489 "/src/emitter-decl.do"
                    (context->currentReturnErrorType = ::app_src_emitter_types_::emitContextType(result->errorType, context));
            }
            else {
#line 490 "/src/emitter-decl.do"
                    (context->currentReturnErrorType = std::string(""));
            }
            }
    }
    else {
#line 493 "/src/emitter-decl.do"
            (context->currentReturnErrorType = std::string(""));
    }
    }
#line 495 "/src/emitter-decl.do"
    const auto ownerName = (owner->native_ ? ((owner->nativeCppName == std::string("")) ? owner->name : owner->nativeCppName) : owner->name);
#line 496 "/src/emitter-decl.do"
    auto result = ((::app_src_emitter_context_::sourceLineDirective(method->span, context) + emitFunctionSignature(method, ((ownerName + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(method->name)), context->modulePath, false, context, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) + std::string(" {\n"));
#line 497 "/src/emitter-decl.do"
    {
        auto _case_subject = method->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 499 "/src/emitter-decl.do"
            (result = (result + emitExpressionCoverageMark(expression, context)));
#line 500 "/src/emitter-decl.do"
            (result = (((result + std::string("    return ")) + ::app_src_emitter_expr_::emitExpression(expression, context, functionReturnType(method))) + std::string(";\n")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 502 "/src/emitter-decl.do"
            (result = (result + ::app_src_emitter_stmt_::emitBlock(block, 1, context)));
    }
    }
#line 504 "/src/emitter-decl.do"
    (context->currentClass = previous);
#line 505 "/src/emitter-decl.do"
    (context->currentClassNative = previousNative);
#line 506 "/src/emitter-decl.do"
    (context->currentReturnErrorType = previousReturnErrorType);
#line 507 "/src/emitter-decl.do"
    (context->currentFunctionName = previousFunctionName);
#line 508 "/src/emitter-decl.do"
    (context->currentFunctionStatic = previousFunctionStatic);
#line 509 "/src/emitter-decl.do"
    (context->capturedMutables = previousCapturedMutables);
#line 510 "/src/emitter-decl.do"
    return (result + std::string("}\n"));
}
#line 513 "/src/emitter-decl.do"
std::string emitExpressionCoverageMark(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 514 "/src/emitter-decl.do"
    if (!context->coverageEnabled || (context->coverageModuleId < 0)) {
#line 514 "/src/emitter-decl.do"
        return std::string("");
    }
#line 515 "/src/emitter-decl.do"
    const auto line = std::visit([](auto&& _obj) { return _obj->span; }, expression).start.line;
#line 516 "/src/emitter-decl.do"
    ::app_src_emitter_context_::recordCoverageLine(context, line);
#line 517 "/src/emitter-decl.do"
    return ((((std::string("    doof::coverage::cov_mark(") + doof::to_string(context->coverageModuleId)) + std::string(", ")) + doof::to_string(line)) + std::string(");\n"));
}
#line 1 "<doof-generated>"
}
