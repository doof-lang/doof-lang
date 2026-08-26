#include "src_emitter_expr_control.hpp"

namespace app_src_emitter_expr_control_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_case_pattern_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
#line 12 "/src/emitter-expr-control.do"
std::string emitDotShorthand(const std::shared_ptr<::app_src_ast_::DotShorthand>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 13 "/src/emitter-expr-control.do"
    if ((expression->resolvedShorthandOwnerKind != std::string("enum")) && (expression->resolvedShorthandOwnerKind != std::string("class"))) {
#line 14 "/src/emitter-expr-control.do"
        doof::panic((std::string("Cannot emit unresolved dot shorthand .") + expression->name));
    }
#line 16 "/src/emitter-expr-control.do"
    auto owner = expression->resolvedShorthandOwnerName;
#line 17 "/src/emitter-expr-control.do"
    if (expression->resolvedShorthandOwnerNative) {
#line 18 "/src/emitter-expr-control.do"
        if (expression->resolvedShorthandOwnerCppName != std::string("")) {
#line 18 "/src/emitter-expr-control.do"
            (owner = (std::string("::") + expression->resolvedShorthandOwnerCppName));
        } else {
#line 19 "/src/emitter-expr-control.do"
            (owner = (std::string("::") + owner));
        }
    } else if (((context->modulePath != std::string("")) && (expression->resolvedShorthandOwnerModule != std::string(""))) && (expression->resolvedShorthandOwnerModule != context->modulePath)) {
#line 21 "/src/emitter-expr-control.do"
        (owner = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(expression->resolvedShorthandOwnerModule)) + std::string("::")) + owner));
    }
#line 23 "/src/emitter-expr-control.do"
    return ((owner + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(expression->name));
}
#line 26 "/src/emitter-expr-control.do"
std::string emitIfExpression(const std::shared_ptr<::app_src_ast_::IfExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 32 "/src/emitter-expr-control.do"
    if ((!doof::is_null(expression->resolvedType)) && ::app_src_emitter_expr_utils_::hasNoneMember(doof::optional_value(doof::unwrap_optional(expression->resolvedType)))) {
#line 33 "/src/emitter-expr-control.do"
        const auto resultType = doof::unwrap_optional(expression->resolvedType);
#line 34 "/src/emitter-expr-control.do"
        return ((((((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(resultType, context->modulePath)) + std::string(" { if (")) + ::app_src_emitter_expr_::emitExpression(expression->condition, context, std::monostate{})) + std::string(") { return ")) + ::app_src_emitter_expr_::emitExpression(expression->then_, context, doof::optional_value(resultType))) + std::string("; } return ")) + ::app_src_emitter_expr_::emitExpression(expression->else_, context, doof::optional_value(resultType))) + std::string("; }()"));
    }
#line 36 "/src/emitter-expr-control.do"
    return ((((((std::string("(") + ::app_src_emitter_expr_::emitExpression(expression->condition, context, std::monostate{})) + std::string(" \? ")) + ::app_src_emitter_expr_::emitExpression(expression->then_, context, std::monostate{})) + std::string(" : ")) + ::app_src_emitter_expr_::emitExpression(expression->else_, context, std::monostate{})) + std::string(")"));
}
#line 39 "/src/emitter-expr-control.do"
std::string emitYieldBlockExpression(const std::shared_ptr<::app_src_ast_::YieldBlockExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 40 "/src/emitter-expr-control.do"
    const auto resultType = [&]() -> std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (doof::is_null(expected)) { return expression->resolvedType; } return expected; }();
#line 41 "/src/emitter-expr-control.do"
    if (doof::is_null(resultType)) {
#line 41 "/src/emitter-expr-control.do"
        doof::panic(std::string("Yield block has no resolved result type"));
    }
#line 42 "/src/emitter-expr-control.do"
    const auto previousYieldState = context->inValueYieldBlock;
#line 43 "/src/emitter-expr-control.do"
    (context->inValueYieldBlock = true);
#line 44 "/src/emitter-expr-control.do"
    const auto body = ::app_src_emitter_stmt_::emitBlock(expression->body, 1, context);
#line 45 "/src/emitter-expr-control.do"
    (context->inValueYieldBlock = previousYieldState);
#line 46 "/src/emitter-expr-control.do"
    return ((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(doof::unwrap_optional(resultType), context->modulePath)) + std::string(" {\n")) + body) + std::string("}()"));
}
#line 49 "/src/emitter-expr-control.do"
std::string emitCatchExpression(const std::shared_ptr<::app_src_ast_::CatchExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 50 "/src/emitter-expr-control.do"
    if (doof::is_null(expression->resolvedType)) {
#line 50 "/src/emitter-expr-control.do"
        doof::panic(std::string("Catch expression has no resolved result type"));
    }
#line 51 "/src/emitter-expr-control.do"
    const auto resultType = doof::unwrap_optional(expression->resolvedType);
#line 52 "/src/emitter-expr-control.do"
    const auto resultCppType = ::app_src_emitter_types_::emitType(resultType, context->modulePath);
#line 53 "/src/emitter-expr-control.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 54 "/src/emitter-expr-control.do"
    const auto catchVar = (std::string("_catch_") + doof::to_string(context->tryCounter));
#line 55 "/src/emitter-expr-control.do"
    const auto previousCatchVar = context->catchVarName;
#line 56 "/src/emitter-expr-control.do"
    const auto previousCatchType = context->catchResultType;
#line 57 "/src/emitter-expr-control.do"
    (context->catchVarName = catchVar);
#line 58 "/src/emitter-expr-control.do"
    (context->catchResultType = doof::optional_value(resultType));
#line 59 "/src/emitter-expr-control.do"
    const auto body = ::app_src_emitter_stmt_::emitBlock(expression->body, 2, context);
#line 60 "/src/emitter-expr-control.do"
    (context->catchVarName = previousCatchVar);
#line 61 "/src/emitter-expr-control.do"
    (context->catchResultType = previousCatchType);
#line 62 "/src/emitter-expr-control.do"
    return (((((((((((((((std::string("[&]() -> ") + resultCppType) + std::string(" {\n")) + std::string("    ")) + resultCppType) + std::string(" ")) + catchVar) + std::string(" = ")) + catchNullValue(resultCppType)) + std::string(";\n")) + std::string("    do {\n")) + body) + std::string("    } while (false);\n")) + std::string("    return ")) + catchVar) + std::string(";\n}()"));
}
#line 68 "/src/emitter-expr-control.do"
std::string catchNullValue(const std::string& resultCppType) {
#line 69 "/src/emitter-expr-control.do"
    if (doof::string_startsWith(resultCppType, std::string("std::optional<"))) {
#line 69 "/src/emitter-expr-control.do"
        return std::string("std::nullopt");
    }
#line 70 "/src/emitter-expr-control.do"
    if (doof::string_startsWith(resultCppType, std::string("std::shared_ptr<")) || doof::string_startsWith(resultCppType, std::string("std::weak_ptr<"))) {
#line 70 "/src/emitter-expr-control.do"
        return std::string("nullptr");
    }
#line 71 "/src/emitter-expr-control.do"
    return std::string("std::monostate{}");
}
#line 74 "/src/emitter-expr-control.do"
std::string emitCaseExpression(const std::shared_ptr<::app_src_ast_::CaseExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 75 "/src/emitter-expr-control.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resultType = std::monostate{};
#line 76 "/src/emitter-expr-control.do"
    if (!doof::is_null(expected)) {
#line 76 "/src/emitter-expr-control.do"
        (resultType = doof::optional_value(doof::unwrap_optional(expected)));
    } else if (!doof::is_null(expression->resolvedType)) {
#line 77 "/src/emitter-expr-control.do"
        (resultType = doof::optional_value(doof::unwrap_optional(expression->resolvedType)));
    }
#line 78 "/src/emitter-expr-control.do"
    if (doof::is_null(resultType)) {
#line 78 "/src/emitter-expr-control.do"
        doof::panic(std::string("Case expression has no resolved result type"));
    }
#line 79 "/src/emitter-expr-control.do"
    auto output = ((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(doof::unwrap_optional(resultType), context->modulePath)) + std::string(" {\n"));
#line 80 "/src/emitter-expr-control.do"
    (output = (((output + std::string("    auto _case_subject = ")) + ::app_src_emitter_expr_::emitExpression(expression->subject, context, std::monostate{})) + std::string(";\n")));
#line 81 "/src/emitter-expr-control.do"
    const auto subjectResult = caseSubjectResultType(expression->subject);
#line 82 "/src/emitter-expr-control.do"
    const auto& _iterable_2 = expression->arms;
    for (const auto& arm : *_iterable_2) {
#line 83 "/src/emitter-expr-control.do"
        const auto& _iterable_4 = arm->patterns;
        for (const auto& pattern : *_iterable_4) {
#line 84 "/src/emitter-expr-control.do"
            auto condition = std::string("true");
#line 85 "/src/emitter-expr-control.do"
            auto binding = std::string("");
#line 86 "/src/emitter-expr-control.do"
            {
                auto _case_subject = pattern;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                    const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
#line 88 "/src/emitter-expr-control.do"
                    const auto bindingName = ((type_->name == std::string("_")) ? std::string("") : ::app_src_emitter_expr_::cppIdentifier(type_->name));
#line 89 "/src/emitter-expr-control.do"
                    const auto emitted = ::app_src_emitter_case_pattern_::emitCaseTypePattern(type_, ::app_src_emitter_types_::specializeEmitType(subjectResult, context), std::string("_case_subject"), bindingName, context->modulePath);
#line 90 "/src/emitter-expr-control.do"
                    (condition = emitted->condition);
#line 91 "/src/emitter-expr-control.do"
                    (binding = emitted->binding);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 93 "/src/emitter-expr-control.do"
                    (condition = (std::string("_case_subject == ") + ::app_src_emitter_expr_::emitExpression(value->value, context, std::monostate{})));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
                    const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
#line 94 "/src/emitter-expr-control.do"
                    (condition = emitRangePatternCondition(range, std::string("_case_subject"), context));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
#line 95 "/src/emitter-expr-control.do"
                    (condition = std::string("true"));
            }
            }
#line 97 "/src/emitter-expr-control.do"
            (output = (((output + std::string("    if (")) + condition) + std::string(") {\n")));
#line 98 "/src/emitter-expr-control.do"
            if (binding != std::string("")) {
#line 98 "/src/emitter-expr-control.do"
                (output = ((output + std::string("        ")) + binding));
            }
#line 99 "/src/emitter-expr-control.do"
            {
                auto _case_subject = arm->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 101 "/src/emitter-expr-control.do"
                    const auto previousYieldState = context->inValueYieldBlock;
#line 102 "/src/emitter-expr-control.do"
                    (context->inValueYieldBlock = true);
#line 103 "/src/emitter-expr-control.do"
                    (output = (output + ::app_src_emitter_stmt_::emitBlock(block, 2, context)));
#line 104 "/src/emitter-expr-control.do"
                    (context->inValueYieldBlock = previousYieldState);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 107 "/src/emitter-expr-control.do"
                    const auto emittedBody = ::app_src_emitter_expr_::emitExpression(bodyExpression, context, resultType);
#line 108 "/src/emitter-expr-control.do"
                    if (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(resultType)) == std::string("none")) {
#line 109 "/src/emitter-expr-control.do"
                        (output = (((output + std::string("        ")) + emittedBody) + std::string(";\n        return std::monostate{};\n")));
                    } else {
#line 111 "/src/emitter-expr-control.do"
                        (output = (((output + std::string("        return ")) + emittedBody) + std::string(";\n")));
                    }
            }
            }
#line 115 "/src/emitter-expr-control.do"
            (output = (output + std::string("    }\n")));
        }
    }
#line 118 "/src/emitter-expr-control.do"
    return (output + std::string("    throw std::runtime_error(\"non-exhaustive case expression\");\n}()"));
}
#line 121 "/src/emitter-expr-control.do"
std::string emitRangePatternCondition(const std::shared_ptr<::app_src_ast_::RangePattern>& pattern, const std::string& subject, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 122 "/src/emitter-expr-control.do"
    auto condition = std::string("");
#line 123 "/src/emitter-expr-control.do"
    if (!doof::is_null(pattern->start)) {
#line 123 "/src/emitter-expr-control.do"
        (condition = ((subject + std::string(" >= ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->start), context, std::monostate{})));
    }
#line 124 "/src/emitter-expr-control.do"
    if (!doof::is_null(pattern->end)) {
#line 125 "/src/emitter-expr-control.do"
        const auto operator_ = (pattern->inclusive ? std::string(" <= ") : std::string(" < "));
#line 126 "/src/emitter-expr-control.do"
        if (condition != std::string("")) {
#line 126 "/src/emitter-expr-control.do"
            (condition = (condition + std::string(" && ")));
        }
#line 127 "/src/emitter-expr-control.do"
        (condition = (((condition + subject) + operator_) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->end), context, std::monostate{})));
    }
#line 129 "/src/emitter-expr-control.do"
    return condition;
}
#line 132 "/src/emitter-expr-control.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> caseSubjectResultType(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& subject) {
#line 133 "/src/emitter-expr-control.do"
    if (doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, subject))) {
#line 134 "/src/emitter-expr-control.do"
        doof::panic(std::string("Case expression subject has no resolved type"));
    }
#line 136 "/src/emitter-expr-control.do"
    return doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, subject));
}
#line 1 "<doof-generated>"
}
