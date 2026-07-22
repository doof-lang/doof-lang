#include "src_emitter_expr_control.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_case_pattern.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_stmt.hpp"
#include "src_emitter_expr_utils.hpp"
#include "src_emitter_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_expr_control_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_case_pattern_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
std::string emitDotShorthand(std::shared_ptr<::app_src_ast_::DotShorthand> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if ((expression->resolvedShorthandOwnerKind != std::string("enum")) && (expression->resolvedShorthandOwnerKind != std::string("class"))) {
        doof::panic((std::string("Cannot emit unresolved dot shorthand .") + expression->name));
    }
    auto owner = expression->resolvedShorthandOwnerName;
    if (expression->resolvedShorthandOwnerNative) {
        if (expression->resolvedShorthandOwnerCppName != std::string("")) {
            (owner = (std::string("::") + expression->resolvedShorthandOwnerCppName));
        } else {
            (owner = (std::string("::") + owner));
        }
    } else if (((context->modulePath != std::string("")) && (expression->resolvedShorthandOwnerModule != std::string(""))) && (expression->resolvedShorthandOwnerModule != context->modulePath)) {
        (owner = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(expression->resolvedShorthandOwnerModule)) + std::string("::")) + owner));
    }
    return ((owner + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(expression->name));
}
std::string emitIfExpression(std::shared_ptr<::app_src_ast_::IfExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return ((((((std::string("(") + ::app_src_emitter_expr_::emitExpression(expression->condition, context, std::monostate{})) + std::string(" ? ")) + ::app_src_emitter_expr_::emitExpression(expression->then_, context, std::monostate{})) + std::string(" : ")) + ::app_src_emitter_expr_::emitExpression(expression->else_, context, std::monostate{})) + std::string(")"));
}
std::string emitYieldBlockExpression(std::shared_ptr<::app_src_ast_::YieldBlockExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected) {
    const auto resultType = (doof::is_null(expected) ? expression->resolvedType : expected);
    if (doof::is_null(resultType)) {
        doof::panic(std::string("Yield block has no resolved result type"));
    }
    const auto previousYieldState = context->inValueYieldBlock;
    (context->inValueYieldBlock = true);
    const auto body = ::app_src_emitter_stmt_::emitBlock(expression->body, 1, context);
    (context->inValueYieldBlock = previousYieldState);
    return ((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(doof::unwrap_optional(resultType), context->modulePath)) + std::string(" {\n")) + body) + std::string("}()"));
}
std::string emitCatchExpression(std::shared_ptr<::app_src_ast_::CatchExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (doof::is_null(expression->resolvedType)) {
        doof::panic(std::string("Catch expression has no resolved result type"));
    }
    const auto resultType = doof::unwrap_optional(expression->resolvedType);
    const auto resultCppType = ::app_src_emitter_types_::emitType(resultType, context->modulePath);
    (context->tryCounter = (context->tryCounter + 1));
    const auto catchVar = (std::string("_catch_") + doof::to_string(context->tryCounter));
    const auto previousCatchVar = context->catchVarName;
    const auto previousCatchType = context->catchResultType;
    (context->catchVarName = catchVar);
    (context->catchResultType = doof::optional_value(resultType));
    const auto body = ::app_src_emitter_stmt_::emitBlock(expression->body, 2, context);
    (context->catchVarName = previousCatchVar);
    (context->catchResultType = previousCatchType);
    return (((((((((((((((std::string("[&]() -> ") + resultCppType) + std::string(" {\n")) + std::string("    ")) + resultCppType) + std::string(" ")) + catchVar) + std::string(" = ")) + catchNullValue(resultCppType)) + std::string(";\n")) + std::string("    do {\n")) + body) + std::string("    } while (false);\n")) + std::string("    return ")) + catchVar) + std::string(";\n}()"));
}
std::string catchNullValue(std::string resultCppType) {
    if (doof::string_startsWith(resultCppType, std::string("std::optional<"))) {
        return std::string("std::nullopt");
    }
    if (doof::string_startsWith(resultCppType, std::string("std::shared_ptr<")) || doof::string_startsWith(resultCppType, std::string("std::weak_ptr<"))) {
        return std::string("nullptr");
    }
    return std::string("std::monostate{}");
}
std::string emitCaseExpression(std::shared_ptr<::app_src_ast_::CaseExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected) {
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resultType = std::monostate{};
    if (!doof::is_null(expected)) {
        (resultType = doof::optional_value(doof::unwrap_optional(expected)));
    } else if (!doof::is_null(expression->resolvedType)) {
        (resultType = doof::optional_value(doof::unwrap_optional(expression->resolvedType)));
    }
    if (doof::is_null(resultType)) {
        doof::panic(std::string("Case expression has no resolved result type"));
    }
    auto output = ((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(doof::unwrap_optional(resultType), context->modulePath)) + std::string(" {\n"));
    (output = (((output + std::string("    auto _case_subject = ")) + ::app_src_emitter_expr_::emitExpression(expression->subject, context, std::monostate{})) + std::string(";\n")));
    const auto subjectResult = caseSubjectResultType(expression->subject);
    const auto& _iterable_1 = expression->arms;
    for (const auto& arm : *_iterable_1) {
        const auto& _iterable_2 = arm->patterns;
        for (const auto& pattern : *_iterable_2) {
            auto condition = std::string("true");
            auto binding = std::string("");
            {
                auto _case_subject = pattern;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                    const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
                    const auto bindingName = ((type_->name == std::string("_")) ? std::string("") : ::app_src_emitter_expr_::cppIdentifier(type_->name));
                    const auto emitted = ::app_src_emitter_case_pattern_::emitCaseTypePattern(type_, ::app_src_emitter_types_::specializeEmitType(subjectResult, context), std::string("_case_subject"), bindingName, context->modulePath);
                    (condition = emitted->condition);
                    (binding = emitted->binding);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
                    (condition = (std::string("_case_subject == ") + ::app_src_emitter_expr_::emitExpression(value->value, context, std::monostate{})));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
                    const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
                    (condition = emitRangePatternCondition(range, std::string("_case_subject"), context));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
                    (condition = std::string("true"));
            }
            }
            (output = (((output + std::string("    if (")) + condition) + std::string(") {\n")));
            if (binding != std::string("")) {
                (output = ((output + std::string("        ")) + binding));
            }
            {
                auto _case_subject = arm->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                    const auto previousYieldState = context->inValueYieldBlock;
                    (context->inValueYieldBlock = true);
                    (output = (output + ::app_src_emitter_stmt_::emitBlock(block, 2, context)));
                    (context->inValueYieldBlock = previousYieldState);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                    const auto emittedBody = ::app_src_emitter_expr_::emitExpression(bodyExpression, context, resultType);
                    if (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(resultType)) == std::string("none")) {
                        (output = (((output + std::string("        ")) + emittedBody) + std::string(";\n        return std::monostate{};\n")));
                    } else {
                        (output = (((output + std::string("        return ")) + emittedBody) + std::string(";\n")));
                    }
            }
            }
            (output = (output + std::string("    }\n")));
        }
    }
    return (output + std::string("    throw std::runtime_error(\"non-exhaustive case expression\");\n}()"));
}
std::string emitRangePatternCondition(std::shared_ptr<::app_src_ast_::RangePattern> pattern, std::string subject, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto condition = std::string("");
    if (!doof::is_null(pattern->start)) {
        (condition = ((subject + std::string(" >= ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->start), context, std::monostate{})));
    }
    if (!doof::is_null(pattern->end)) {
        const auto operator_ = (pattern->inclusive ? std::string(" <= ") : std::string(" < "));
        if (condition != std::string("")) {
            (condition = (condition + std::string(" && ")));
        }
        (condition = (((condition + subject) + operator_) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->end), context, std::monostate{})));
    }
    return condition;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> caseSubjectResultType(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> subject) {
    if (doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, subject))) {
        doof::panic(std::string("Case expression subject has no resolved type"));
    }
    return doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, subject));
}
}
