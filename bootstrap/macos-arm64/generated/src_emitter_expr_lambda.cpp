#include "src_emitter_expr_lambda.hpp"

namespace app_src_emitter_expr_lambda_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_types_;
#line 23 "/src/emitter-expr-lambda.do"
std::string emitLambdaExpression(const std::shared_ptr<::app_src_ast_::LambdaExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 24 "/src/emitter-expr-lambda.do"
    auto functionType = lambdaFunctionType(expression);
#line 25 "/src/emitter-expr-lambda.do"
    if (!doof::is_null(expected)) {
#line 26 "/src/emitter-expr-lambda.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& expectedFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 27 "/src/emitter-expr-lambda.do"
                (functionType = expectedFunction);
        }
        else {
        }
        }
    }
#line 31 "/src/emitter-expr-lambda.do"
    auto params = std::string("");
#line 32 "/src/emitter-expr-lambda.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->params)->size()); ++i) {
#line 33 "/src/emitter-expr-lambda.do"
        if (i > 0) {
#line 33 "/src/emitter-expr-lambda.do"
            (params = (params + std::string(", ")));
        }
#line 34 "/src/emitter-expr-lambda.do"
        const auto parameter = doof::array_at(expression->params, i, "src/emitter-expr-lambda", 34);
#line 35 "/src/emitter-expr-lambda.do"
        if (doof::is_null(parameter->resolvedType)) {
#line 35 "/src/emitter-expr-lambda.do"
            doof::panic(std::string("Lambda parameter was not resolved before emission"));
        }
#line 36 "/src/emitter-expr-lambda.do"
        const auto parameterName = ((parameter->name == std::string("_")) ? (std::string("_discard_parameter_") + doof::to_string(i)) : ::app_src_emitter_expr_::cppIdentifier(parameter->name));
#line 37 "/src/emitter-expr-lambda.do"
        (params = (((params + ::app_src_emitter_types_::emitType(doof::unwrap_optional(parameter->resolvedType), context->modulePath)) + std::string(" ")) + parameterName));
    }
#line 40 "/src/emitter-expr-lambda.do"
    const auto captureNames = lambdaCaptureNames(expression);
#line 41 "/src/emitter-expr-lambda.do"
    auto captures = std::string("");
#line 42 "/src/emitter-expr-lambda.do"
    if (static_cast<int32_t>((captureNames)->size()) > 0) {
#line 43 "/src/emitter-expr-lambda.do"
        (captures = std::string(""));
#line 44 "/src/emitter-expr-lambda.do"
        for (int32_t i = 0; i < static_cast<int32_t>((captureNames)->size()); ++i) {
#line 45 "/src/emitter-expr-lambda.do"
            if (i > 0) {
#line 45 "/src/emitter-expr-lambda.do"
                (captures = (captures + std::string(", ")));
            }
#line 46 "/src/emitter-expr-lambda.do"
            (captures = (captures + doof::array_at(captureNames, i, "src/emitter-expr-lambda", 46)));
        }
    }
#line 50 "/src/emitter-expr-lambda.do"
    const auto previousReturnErrorType = context->currentReturnErrorType;
#line 51 "/src/emitter-expr-lambda.do"
    const auto previousFunctionName = context->currentFunctionName;
#line 52 "/src/emitter-expr-lambda.do"
    const auto previousTryPanics = context->tryPanics;
#line 53 "/src/emitter-expr-lambda.do"
    (context->currentFunctionName = (previousFunctionName + std::string(".<lambda>")));
#line 54 "/src/emitter-expr-lambda.do"
    (context->tryPanics = false);
#line 55 "/src/emitter-expr-lambda.do"
    {
        auto _case_subject = functionType->returnType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 56 "/src/emitter-expr-lambda.do"
            (context->currentReturnErrorType = ::app_src_emitter_types_::emitType(result->errorType, context->modulePath));
    }
    else {
#line 57 "/src/emitter-expr-lambda.do"
            (context->currentReturnErrorType = std::string(""));
    }
    }
#line 60 "/src/emitter-expr-lambda.do"
    const auto returnType = ::app_src_emitter_types_::emitReturnType(functionType->returnType, context->modulePath);
#line 61 "/src/emitter-expr-lambda.do"
    auto lambda = ((((((std::string("[") + captures) + std::string("](")) + params) + std::string(") -> ")) + returnType) + std::string(" {"));
#line 62 "/src/emitter-expr-lambda.do"
    {
        auto _case_subject = expression->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 63 "/src/emitter-expr-lambda.do"
            (lambda = (((lambda + std::string("\n")) + ::app_src_emitter_stmt_::emitBlock(block, 1, context)) + std::string("}")));
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto body = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 64 "/src/emitter-expr-lambda.do"
            (lambda = (((lambda + std::string(" return ")) + ::app_src_emitter_expr_::emitExpression(body, context, doof::optional_value(functionType->returnType))) + std::string("; }")));
    }
    }
#line 67 "/src/emitter-expr-lambda.do"
    (context->currentReturnErrorType = previousReturnErrorType);
#line 68 "/src/emitter-expr-lambda.do"
    (context->currentFunctionName = previousFunctionName);
#line 69 "/src/emitter-expr-lambda.do"
    (context->tryPanics = previousTryPanics);
#line 70 "/src/emitter-expr-lambda.do"
    return (((::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(functionType), context->modulePath) + std::string("(")) + lambda) + std::string(")"));
}
#line 77 "/src/emitter-expr-lambda.do"
std::shared_ptr<std::vector<std::string>> scanCapturedMutablesInBlock(const std::shared_ptr<::app_src_ast_::Block>& body) {
#line 78 "/src/emitter-expr-lambda.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 79 "/src/emitter-expr-lambda.do"
    scanBlockForLambdas(body, result);
#line 80 "/src/emitter-expr-lambda.do"
    return result;
}
#line 83 "/src/emitter-expr-lambda.do"
std::shared_ptr<std::vector<std::string>> scanCapturedMutablesInExpression(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& body) {
#line 84 "/src/emitter-expr-lambda.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 85 "/src/emitter-expr-lambda.do"
    scanExpressionForLambdas(body, result);
#line 86 "/src/emitter-expr-lambda.do"
    return result;
}
#line 89 "/src/emitter-expr-lambda.do"
std::shared_ptr<::app_src_semantic_::FunctionType> lambdaFunctionType(const std::shared_ptr<::app_src_ast_::LambdaExpression>& expression) {
#line 90 "/src/emitter-expr-lambda.do"
    if (!doof::is_null(expression->resolvedType)) {
#line 91 "/src/emitter-expr-lambda.do"
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 92 "/src/emitter-expr-lambda.do"
                return function_;
        }
        else {
        }
        }
    }
#line 96 "/src/emitter-expr-lambda.do"
    doof::panic(std::string("Lambda has no resolved function type"));
#line 97 "/src/emitter-expr-lambda.do"
    return std::make_shared<::app_src_semantic_::FunctionType>(std::string("function"), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::NoneType>(std::string("none"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
#line 100 "/src/emitter-expr-lambda.do"
std::shared_ptr<std::vector<std::string>> lambdaCaptureNames(const std::shared_ptr<::app_src_ast_::LambdaExpression>& expression) {
#line 101 "/src/emitter-expr-lambda.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 102 "/src/emitter-expr-lambda.do"
    auto bodyStart = 0;
#line 103 "/src/emitter-expr-lambda.do"
    auto bodyEnd = 0;
#line 104 "/src/emitter-expr-lambda.do"
    {
        auto _case_subject = expression->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 106 "/src/emitter-expr-lambda.do"
            (bodyStart = block->span.start.offset);
#line 107 "/src/emitter-expr-lambda.do"
            (bodyEnd = block->span.end.offset);
#line 108 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(block, bodyStart, bodyEnd, result, false);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto body = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 111 "/src/emitter-expr-lambda.do"
            (bodyStart = std::visit([](auto&& _obj) { return _obj->span; }, body).start.offset);
#line 112 "/src/emitter-expr-lambda.do"
            (bodyEnd = std::visit([](auto&& _obj) { return _obj->span; }, body).end.offset);
#line 113 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(body, bodyStart, bodyEnd, result, false);
    }
    }
#line 116 "/src/emitter-expr-lambda.do"
    std::shared_ptr<std::vector<std::string>> captures = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 117 "/src/emitter-expr-lambda.do"
    const auto& _iterable_4 = result;
    for (const auto& name : *_iterable_4) {
#line 118 "/src/emitter-expr-lambda.do"
        auto parameter = false;
#line 119 "/src/emitter-expr-lambda.do"
        const auto& _iterable_6 = expression->params;
        for (const auto& item : *_iterable_6) {
#line 119 "/src/emitter-expr-lambda.do"
            if (::app_src_emitter_expr_::cppIdentifier(item->name) == name) {
#line 119 "/src/emitter-expr-lambda.do"
                (parameter = true);
            }
        }
#line 120 "/src/emitter-expr-lambda.do"
        if (!parameter) {
#line 120 "/src/emitter-expr-lambda.do"
            captures->push_back(name);
        }
    }
#line 122 "/src/emitter-expr-lambda.do"
    return captures;
}
#line 125 "/src/emitter-expr-lambda.do"
void scanBlockForLambdas(const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<std::vector<std::string>>& result) {
#line 126 "/src/emitter-expr-lambda.do"
    const auto& _iterable_8 = block->statements;
    for (const auto& statement : *_iterable_8) {
#line 126 "/src/emitter-expr-lambda.do"
        scanStatementForLambdas(statement, result);
    }
}
#line 129 "/src/emitter-expr-lambda.do"
void scanStatementForLambdas(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<std::vector<std::string>>& result) {
#line 130 "/src/emitter-expr-lambda.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 131 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(const_->value, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 132 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(readonly_->value, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 134 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(binding->value, result);
#line 135 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(binding->else_)) {
#line 135 "/src/emitter-expr-lambda.do"
                scanBlockForLambdas(doof::unwrap_optional(binding->else_), result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 137 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(let_->value, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 138 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(expression->expression, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
#line 139 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(return_->value)) {
#line 139 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(doof::unwrap_optional(return_->value), result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
#line 141 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(if_->condition, result);
#line 142 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(if_->body, result);
#line 143 "/src/emitter-expr-lambda.do"
            const auto& _iterable_10 = if_->elseIfs;
            for (const auto& branch : *_iterable_10) {
#line 144 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(branch->condition, result);
#line 145 "/src/emitter-expr-lambda.do"
                scanBlockForLambdas(branch->body, result);
            }
#line 147 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(if_->else_)) {
#line 147 "/src/emitter-expr-lambda.do"
                scanBlockForLambdas(doof::unwrap_optional(if_->else_), result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
#line 150 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(case_->subject, result);
#line 151 "/src/emitter-expr-lambda.do"
            const auto& _iterable_12 = case_->arms;
            for (const auto& arm : *_iterable_12) {
#line 152 "/src/emitter-expr-lambda.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 153 "/src/emitter-expr-lambda.do"
                        scanBlockForLambdas(block, result);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 154 "/src/emitter-expr-lambda.do"
                        scanExpressionForLambdas(expression, result);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
#line 159 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(while_->condition, result);
#line 160 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(while_->body, result);
#line 161 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(while_->then_)) {
#line 161 "/src/emitter-expr-lambda.do"
                scanBlockForLambdas(doof::unwrap_optional(while_->then_), result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
#line 164 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(for_->init)) {
#line 164 "/src/emitter-expr-lambda.do"
                scanStatementForLambdas(doof::unwrap_optional(for_->init), result);
            }
#line 165 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(for_->condition)) {
#line 165 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(doof::unwrap_optional(for_->condition), result);
            }
#line 166 "/src/emitter-expr-lambda.do"
            const auto& _iterable_14 = for_->update;
            for (const auto& update : *_iterable_14) {
#line 166 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(update, result);
            }
#line 167 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(for_->body, result);
#line 168 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(for_->then_)) {
#line 168 "/src/emitter-expr-lambda.do"
                scanBlockForLambdas(doof::unwrap_optional(for_->then_), result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
#line 171 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(forOf->iterable, result);
#line 172 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(forOf->body, result);
#line 173 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(forOf->then_)) {
#line 173 "/src/emitter-expr-lambda.do"
                scanBlockForLambdas(doof::unwrap_optional(forOf->then_), result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
#line 176 "/src/emitter-expr-lambda.do"
            const auto& _iterable_16 = with_->bindings;
            for (const auto& binding : *_iterable_16) {
#line 176 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(binding->value, result);
            }
#line 177 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(with_->body, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
#line 180 "/src/emitter-expr-lambda.do"
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 181 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(declaration->value, result);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 182 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(declaration->value, result);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 183 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(binding->value, result);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 184 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(declaration->value, result);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 185 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(expression->expression, result);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 186 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(destructuring->value, result);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
#line 189 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 190 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(block, result);
    }
    else {
    }
    }
}
#line 195 "/src/emitter-expr-lambda.do"
void scanExpressionForLambdas(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<std::vector<std::string>>& result) {
#line 196 "/src/emitter-expr-lambda.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject)) {
            const auto& as_ = std::get<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject);
#line 197 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(as_->expression, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 198 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(binary->left, result);
#line 199 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(binary->right, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 200 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(unary->operand, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
#line 201 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(assignment->target, result);
#line 202 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(assignment->value, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 203 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(member->object, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 204 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(index->object, result);
#line 205 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(index->index, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 206 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(call->callee, result);
#line 207 "/src/emitter-expr-lambda.do"
            const auto& _iterable_18 = call->args;
            for (const auto& argument : *_iterable_18) {
#line 207 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(argument->value, result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 208 "/src/emitter-expr-lambda.do"
            const auto& _iterable_20 = array->elements;
            for (const auto& element : *_iterable_20) {
#line 208 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(element, result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 210 "/src/emitter-expr-lambda.do"
            const auto& _iterable_22 = object->properties;
            for (const auto& property : *_iterable_22) {
#line 211 "/src/emitter-expr-lambda.do"
                if (!doof::is_null(property->key)) {
#line 211 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(doof::unwrap_optional(property->key), result);
                }
#line 212 "/src/emitter-expr-lambda.do"
                if (!doof::is_null(property->value)) {
#line 212 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(doof::unwrap_optional(property->value), result);
                }
            }
#line 214 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(object->spread)) {
#line 214 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(doof::unwrap_optional(object->spread), result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
#line 216 "/src/emitter-expr-lambda.do"
            const auto& _iterable_24 = tuple->elements;
            for (const auto& element : *_iterable_24) {
#line 216 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(element, result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 217 "/src/emitter-expr-lambda.do"
            const auto& _iterable_26 = string_->interpolations;
            for (const auto& interpolation : *_iterable_26) {
#line 217 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(interpolation, result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
#line 219 "/src/emitter-expr-lambda.do"
            {
                auto _case_subject = lambda->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 221 "/src/emitter-expr-lambda.do"
                    collectBlockCaptures(block, block->span.start.offset, block->span.end.offset, result, true);
#line 222 "/src/emitter-expr-lambda.do"
                    scanBlockForLambdas(block, result);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto body = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 225 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(body, std::visit([](auto&& _obj) { return _obj->span; }, body).start.offset, std::visit([](auto&& _obj) { return _obj->span; }, body).end.offset, result, true);
#line 226 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(body, result);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
#line 230 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(if_->condition, result);
#line 231 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(if_->then_, result);
#line 232 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(if_->else_, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
#line 233 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(case_->subject, result);
#line 234 "/src/emitter-expr-lambda.do"
            const auto& _iterable_28 = case_->arms;
            for (const auto& arm : *_iterable_28) {
#line 235 "/src/emitter-expr-lambda.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 236 "/src/emitter-expr-lambda.do"
                        scanBlockForLambdas(block, result);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 237 "/src/emitter-expr-lambda.do"
                        scanExpressionForLambdas(bodyExpression, result);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 240 "/src/emitter-expr-lambda.do"
            const auto& _iterable_30 = construct->args;
            for (const auto& property : *_iterable_30) {
#line 240 "/src/emitter-expr-lambda.do"
                if (!doof::is_null(property->value)) {
#line 240 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(doof::unwrap_optional(property->value), result);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 242 "/src/emitter-expr-lambda.do"
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 243 "/src/emitter-expr-lambda.do"
                    scanBlockForLambdas(block, result);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 244 "/src/emitter-expr-lambda.do"
                    scanExpressionForLambdas(inner, result);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
#line 247 "/src/emitter-expr-lambda.do"
            scanExpressionForLambdas(retire_->actor, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 248 "/src/emitter-expr-lambda.do"
            const auto& _iterable_32 = actor->args;
            for (const auto& argument : *_iterable_32) {
#line 248 "/src/emitter-expr-lambda.do"
                scanExpressionForLambdas(argument, result);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
#line 249 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(yieldBlock->body, result);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
#line 250 "/src/emitter-expr-lambda.do"
            scanBlockForLambdas(catch_->body, result);
    }
    else {
    }
    }
}
#line 255 "/src/emitter-expr-lambda.do"
void collectBlockCaptures(const std::shared_ptr<::app_src_ast_::Block>& block, int32_t bodyStart, int32_t bodyEnd, const std::shared_ptr<std::vector<std::string>>& result, bool mutableOnly) {
#line 256 "/src/emitter-expr-lambda.do"
    const auto& _iterable_34 = block->statements;
    for (const auto& statement : *_iterable_34) {
#line 256 "/src/emitter-expr-lambda.do"
        collectStatementCaptures(statement, bodyStart, bodyEnd, result, mutableOnly);
    }
}
#line 259 "/src/emitter-expr-lambda.do"
void collectStatementCaptures(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, int32_t bodyStart, int32_t bodyEnd, const std::shared_ptr<std::vector<std::string>>& result, bool mutableOnly) {
#line 260 "/src/emitter-expr-lambda.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 261 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(const_->value, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 262 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(readonly_->value, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 264 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(binding->value, bodyStart, bodyEnd, result, mutableOnly);
#line 265 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(binding->else_)) {
#line 265 "/src/emitter-expr-lambda.do"
                collectBlockCaptures(doof::unwrap_optional(binding->else_), bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 267 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(let_->value, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 268 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(expression->expression, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
#line 269 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(return_->value)) {
#line 269 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(doof::unwrap_optional(return_->value), bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
#line 271 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(if_->condition, bodyStart, bodyEnd, result, mutableOnly);
#line 272 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(if_->body, bodyStart, bodyEnd, result, mutableOnly);
#line 273 "/src/emitter-expr-lambda.do"
            const auto& _iterable_36 = if_->elseIfs;
            for (const auto& branch : *_iterable_36) {
#line 273 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(branch->condition, bodyStart, bodyEnd, result, mutableOnly);
#line 274 "/src/emitter-expr-lambda.do"
                collectBlockCaptures(branch->body, bodyStart, bodyEnd, result, mutableOnly);
            }
#line 275 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(if_->else_)) {
#line 275 "/src/emitter-expr-lambda.do"
                collectBlockCaptures(doof::unwrap_optional(if_->else_), bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
#line 277 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(case_->subject, bodyStart, bodyEnd, result, mutableOnly);
#line 278 "/src/emitter-expr-lambda.do"
            const auto& _iterable_38 = case_->arms;
            for (const auto& arm : *_iterable_38) {
#line 279 "/src/emitter-expr-lambda.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 280 "/src/emitter-expr-lambda.do"
                        collectBlockCaptures(block, bodyStart, bodyEnd, result, mutableOnly);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 281 "/src/emitter-expr-lambda.do"
                        collectExpressionCaptures(expression, bodyStart, bodyEnd, result, mutableOnly);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
#line 285 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(while_->condition, bodyStart, bodyEnd, result, mutableOnly);
#line 286 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(while_->body, bodyStart, bodyEnd, result, mutableOnly);
#line 287 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(while_->then_)) {
#line 287 "/src/emitter-expr-lambda.do"
                collectBlockCaptures(doof::unwrap_optional(while_->then_), bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
#line 290 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(for_->init)) {
#line 290 "/src/emitter-expr-lambda.do"
                collectStatementCaptures(doof::unwrap_optional(for_->init), bodyStart, bodyEnd, result, mutableOnly);
            }
#line 291 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(for_->condition)) {
#line 291 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(doof::unwrap_optional(for_->condition), bodyStart, bodyEnd, result, mutableOnly);
            }
#line 292 "/src/emitter-expr-lambda.do"
            const auto& _iterable_40 = for_->update;
            for (const auto& update : *_iterable_40) {
#line 292 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(update, bodyStart, bodyEnd, result, mutableOnly);
            }
#line 293 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(for_->body, bodyStart, bodyEnd, result, mutableOnly);
#line 294 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(for_->then_)) {
#line 294 "/src/emitter-expr-lambda.do"
                collectBlockCaptures(doof::unwrap_optional(for_->then_), bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
#line 297 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(forOf->iterable, bodyStart, bodyEnd, result, mutableOnly);
#line 298 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(forOf->body, bodyStart, bodyEnd, result, mutableOnly);
#line 299 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(forOf->then_)) {
#line 299 "/src/emitter-expr-lambda.do"
                collectBlockCaptures(doof::unwrap_optional(forOf->then_), bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
#line 301 "/src/emitter-expr-lambda.do"
            const auto& _iterable_42 = with_->bindings;
            for (const auto& binding : *_iterable_42) {
#line 301 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(binding->value, bodyStart, bodyEnd, result, mutableOnly);
            }
#line 302 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(with_->body, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
#line 304 "/src/emitter-expr-lambda.do"
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 305 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(declaration->value, bodyStart, bodyEnd, result, mutableOnly);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 306 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(declaration->value, bodyStart, bodyEnd, result, mutableOnly);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 307 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(binding->value, bodyStart, bodyEnd, result, mutableOnly);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 308 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(declaration->value, bodyStart, bodyEnd, result, mutableOnly);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 309 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(expression->expression, bodyStart, bodyEnd, result, mutableOnly);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 310 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(destructuring->value, bodyStart, bodyEnd, result, mutableOnly);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
#line 313 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 314 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(block, bodyStart, bodyEnd, result, mutableOnly);
    }
    else {
    }
    }
}
#line 319 "/src/emitter-expr-lambda.do"
void collectExpressionCaptures(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, int32_t bodyStart, int32_t bodyEnd, const std::shared_ptr<std::vector<std::string>>& result, bool mutableOnly) {
#line 320 "/src/emitter-expr-lambda.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 321 "/src/emitter-expr-lambda.do"
            collectIdentifierCapture(identifier, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
#line 322 "/src/emitter-expr-lambda.do"
            if (!mutableOnly) {
#line 322 "/src/emitter-expr-lambda.do"
                addUnique(result, std::string("this"));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject)) {
            const auto& as_ = std::get<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject);
#line 323 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(as_->expression, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 324 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(binary->left, bodyStart, bodyEnd, result, mutableOnly);
#line 325 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(binary->right, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 326 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(unary->operand, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
#line 327 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(assignment->target, bodyStart, bodyEnd, result, mutableOnly);
#line 328 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(assignment->value, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 329 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(member->object, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 330 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(index->object, bodyStart, bodyEnd, result, mutableOnly);
#line 331 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(index->index, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 332 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(call->callee, bodyStart, bodyEnd, result, mutableOnly);
#line 333 "/src/emitter-expr-lambda.do"
            const auto& _iterable_44 = call->args;
            for (const auto& argument : *_iterable_44) {
#line 333 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(argument->value, bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 334 "/src/emitter-expr-lambda.do"
            const auto& _iterable_46 = array->elements;
            for (const auto& element : *_iterable_46) {
#line 334 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(element, bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 336 "/src/emitter-expr-lambda.do"
            const auto& _iterable_48 = object->properties;
            for (const auto& property : *_iterable_48) {
#line 337 "/src/emitter-expr-lambda.do"
                if (!doof::is_null(property->key)) {
#line 337 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(doof::unwrap_optional(property->key), bodyStart, bodyEnd, result, mutableOnly);
                }
#line 338 "/src/emitter-expr-lambda.do"
                if (!doof::is_null(property->value)) {
#line 338 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(doof::unwrap_optional(property->value), bodyStart, bodyEnd, result, mutableOnly);
                }
            }
#line 340 "/src/emitter-expr-lambda.do"
            if (!doof::is_null(object->spread)) {
#line 340 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(doof::unwrap_optional(object->spread), bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
#line 342 "/src/emitter-expr-lambda.do"
            const auto& _iterable_50 = tuple->elements;
            for (const auto& element : *_iterable_50) {
#line 342 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(element, bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 343 "/src/emitter-expr-lambda.do"
            const auto& _iterable_52 = string_->interpolations;
            for (const auto& interpolation : *_iterable_52) {
#line 343 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(interpolation, bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
#line 345 "/src/emitter-expr-lambda.do"
            {
                auto _case_subject = lambda->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 346 "/src/emitter-expr-lambda.do"
                    collectBlockCaptures(block, bodyStart, bodyEnd, result, mutableOnly);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto body = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 347 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(body, bodyStart, bodyEnd, result, mutableOnly);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
#line 350 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(if_->condition, bodyStart, bodyEnd, result, mutableOnly);
#line 351 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(if_->then_, bodyStart, bodyEnd, result, mutableOnly);
#line 352 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(if_->else_, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
#line 353 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(case_->subject, bodyStart, bodyEnd, result, mutableOnly);
#line 354 "/src/emitter-expr-lambda.do"
            const auto& _iterable_54 = case_->arms;
            for (const auto& arm : *_iterable_54) {
#line 355 "/src/emitter-expr-lambda.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 356 "/src/emitter-expr-lambda.do"
                        collectBlockCaptures(block, bodyStart, bodyEnd, result, mutableOnly);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 357 "/src/emitter-expr-lambda.do"
                        collectExpressionCaptures(bodyExpression, bodyStart, bodyEnd, result, mutableOnly);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 360 "/src/emitter-expr-lambda.do"
            const auto& _iterable_56 = construct->args;
            for (const auto& property : *_iterable_56) {
#line 360 "/src/emitter-expr-lambda.do"
                if (!doof::is_null(property->value)) {
#line 360 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(doof::unwrap_optional(property->value), bodyStart, bodyEnd, result, mutableOnly);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 362 "/src/emitter-expr-lambda.do"
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 363 "/src/emitter-expr-lambda.do"
                    collectBlockCaptures(block, bodyStart, bodyEnd, result, mutableOnly);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 364 "/src/emitter-expr-lambda.do"
                    collectExpressionCaptures(inner, bodyStart, bodyEnd, result, mutableOnly);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
#line 367 "/src/emitter-expr-lambda.do"
            collectExpressionCaptures(retire_->actor, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 368 "/src/emitter-expr-lambda.do"
            const auto& _iterable_58 = actor->args;
            for (const auto& argument : *_iterable_58) {
#line 368 "/src/emitter-expr-lambda.do"
                collectExpressionCaptures(argument, bodyStart, bodyEnd, result, mutableOnly);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
#line 369 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(yieldBlock->body, bodyStart, bodyEnd, result, mutableOnly);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
#line 370 "/src/emitter-expr-lambda.do"
            collectBlockCaptures(catch_->body, bodyStart, bodyEnd, result, mutableOnly);
    }
    else {
    }
    }
}
#line 375 "/src/emitter-expr-lambda.do"
void collectIdentifierCapture(const std::shared_ptr<::app_src_ast_::Identifier>& identifier, int32_t bodyStart, int32_t bodyEnd, const std::shared_ptr<std::vector<std::string>>& result, bool mutableOnly) {
#line 376 "/src/emitter-expr-lambda.do"
    if (doof::is_null(identifier->resolvedBinding)) {
#line 376 "/src/emitter-expr-lambda.do"
        return;
    }
#line 377 "/src/emitter-expr-lambda.do"
    const auto binding = doof::unwrap_optional(identifier->resolvedBinding);
#line 378 "/src/emitter-expr-lambda.do"
    if (binding->kind == std::string("field")) {
#line 379 "/src/emitter-expr-lambda.do"
        if (!mutableOnly) {
#line 379 "/src/emitter-expr-lambda.do"
            addUnique(result, std::string("this"));
        }
#line 380 "/src/emitter-expr-lambda.do"
        return;
    }
#line 382 "/src/emitter-expr-lambda.do"
    if (binding->kind == std::string("method")) {
#line 383 "/src/emitter-expr-lambda.do"
        if (!mutableOnly) {
#line 383 "/src/emitter-expr-lambda.do"
            addUnique(result, std::string("this"));
        }
#line 384 "/src/emitter-expr-lambda.do"
        return;
    }
#line 389 "/src/emitter-expr-lambda.do"
    if (((binding->kind == std::string("module-let")) || (binding->kind == std::string("script-global"))) || (binding->kind == std::string("script-arguments"))) {
#line 389 "/src/emitter-expr-lambda.do"
        return;
    }
#line 390 "/src/emitter-expr-lambda.do"
    if (((!doof::is_null(binding->symbol)) || (binding->kind == std::string("builtin"))) || (binding->kind == std::string("import"))) {
#line 390 "/src/emitter-expr-lambda.do"
        return;
    }
#line 391 "/src/emitter-expr-lambda.do"
    const auto bindingStart = binding->span.start.offset;
#line 392 "/src/emitter-expr-lambda.do"
    if ((bindingStart >= bodyStart) && (bindingStart <= bodyEnd)) {
#line 392 "/src/emitter-expr-lambda.do"
        return;
    }
#line 393 "/src/emitter-expr-lambda.do"
    if (mutableOnly && !binding->mutable_) {
#line 393 "/src/emitter-expr-lambda.do"
        return;
    }
#line 394 "/src/emitter-expr-lambda.do"
    addUnique(result, ::app_src_emitter_expr_::cppIdentifier(identifier->name));
}
#line 397 "/src/emitter-expr-lambda.do"
void addUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 398 "/src/emitter-expr-lambda.do"
    const auto& _iterable_60 = values;
    for (const auto& existing : *_iterable_60) {
#line 398 "/src/emitter-expr-lambda.do"
        if (existing == value) {
#line 398 "/src/emitter-expr-lambda.do"
            return;
        }
    }
#line 399 "/src/emitter-expr-lambda.do"
    values->push_back(value);
}
#line 1 "<doof-generated>"
}
