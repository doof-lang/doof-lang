#include "src_checker_expressions.hpp"

namespace app_src_checker_expressions_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_async_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_statements_;
using namespace ::app_src_checker_calls_;
using namespace ::app_src_checker_literals_;
using namespace ::app_src_checker_resolution_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_generics_;
using namespace ::app_src_checker_validation_;
using namespace ::app_src_checker_interfaces_;
#line 50 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkCaseExpression(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CaseExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 51 "/src/checker-expressions.do"
    const auto subjectType = checkExpression(state, expression->subject, scope, std::monostate{});
#line 52 "/src/checker-expressions.do"
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferredType = ::app_src_checker_types_::unknownType();
#line 53 "/src/checker-expressions.do"
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>> armPatterns = std::make_shared<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>>(std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>{});
#line 54 "/src/checker-expressions.do"
    const auto& _iterable_2 = expression->arms;
    for (const auto& arm : *_iterable_2) {
#line 55 "/src/checker-expressions.do"
        armPatterns->push_back(arm->patterns);
#line 56 "/src/checker-expressions.do"
        const auto armScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 57 "/src/checker-expressions.do"
        checkCasePatterns(state, arm->patterns, subjectType, armScope);
#line 58 "/src/checker-expressions.do"
        auto armExpected = expected;
#line 59 "/src/checker-expressions.do"
        if (doof::is_null(armExpected)) {
#line 60 "/src/checker-expressions.do"
            {
                auto _case_subject = inferredType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
            }
            else {
#line 62 "/src/checker-expressions.do"
                    (armExpected = doof::optional_value(inferredType));
            }
            }
        }
#line 65 "/src/checker-expressions.do"
        std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> armType = ::app_src_checker_types_::unknownType();
#line 66 "/src/checker-expressions.do"
        {
            auto _case_subject = arm->body;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 68 "/src/checker-expressions.do"
                (armScope->inValueYieldBlock = true);
#line 69 "/src/checker-expressions.do"
                (armScope->yieldType = [&]() -> std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (doof::is_null(armExpected)) { return ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()); } return armExpected; }());
#line 70 "/src/checker-expressions.do"
                const auto completes = ::app_src_checker_statements_::checkBlock(state, block, armScope, false);
#line 71 "/src/checker-expressions.do"
                if (completes) {
#line 71 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, std::string("Block case-expression arms must yield a value on every path"), block->span);
                }
#line 72 "/src/checker-expressions.do"
                (armType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_3 = armScope->yieldType; if (doof::is_null(_coalesce_3)) return ::app_src_checker_types_::unknownType(); return doof::unwrap_optional(_coalesce_3); }());
#line 73 "/src/checker-expressions.do"
                if (!completes && (std::visit([](auto&& _obj) { return _obj->kind; }, armType) == std::string("unknown"))) {
#line 73 "/src/checker-expressions.do"
                    (armType = ::app_src_checker_types_::neverType());
                }
        }
        else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 75 "/src/checker-expressions.do"
                (armType = checkExpression(state, bodyExpression, armScope, armExpected));
        }
        }
#line 77 "/src/checker-expressions.do"
        if (std::visit([](auto&& _obj) { return _obj->kind; }, inferredType) == std::string("unknown")) {
#line 77 "/src/checker-expressions.do"
            (inferredType = armType);
        } else {
#line 77 "/src/checker-expressions.do"
            (inferredType = ::app_src_checker_types_::joinTypes(inferredType, armType));
        }
    }
#line 79 "/src/checker-expressions.do"
    if (((std::visit([](auto&& _obj) { return _obj->kind; }, subjectType) != std::string("unknown")) && (std::visit([](auto&& _obj) { return _obj->kind; }, subjectType) != std::string("never"))) && !casePatternsExhaustive(state, subjectType, armPatterns)) {
#line 80 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, std::string("Case expression must be exhaustive"), expression->span);
    }
#line 82 "/src/checker-expressions.do"
    (expression->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(inferredType));
#line 83 "/src/checker-expressions.do"
    return inferredType;
}
#line 86 "/src/checker-expressions.do"
bool casePatternsExhaustive(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& subjectType, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>>& arms) {
#line 87 "/src/checker-expressions.do"
    const auto& _iterable_5 = arms;
    for (const auto& patterns : *_iterable_5) {
#line 88 "/src/checker-expressions.do"
        const auto& _iterable_7 = patterns;
        for (const auto& pattern : *_iterable_7) {
#line 89 "/src/checker-expressions.do"
            {
                auto _case_subject = pattern;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
#line 90 "/src/checker-expressions.do"
                    return true;
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                    const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
#line 91 "/src/checker-expressions.do"
                    if ((!doof::is_null(type_->resolvedType)) && ::app_src_checker_types_::sameType(subjectType, doof::unwrap_optional(type_->resolvedType))) {
#line 91 "/src/checker-expressions.do"
                        return true;
                    }
            }
            else {
            }
            }
        }
    }
#line 96 "/src/checker-expressions.do"
    {
        auto _case_subject = subjectType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive_ = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 98 "/src/checker-expressions.do"
            if (primitive_->name == std::string("int")) {
#line 98 "/src/checker-expressions.do"
                return integerPatternsExhaustive(arms);
            }
#line 99 "/src/checker-expressions.do"
            if (primitive_->name != std::string("bool")) {
#line 99 "/src/checker-expressions.do"
                return false;
            }
#line 100 "/src/checker-expressions.do"
            auto hasTrue = false;
#line 101 "/src/checker-expressions.do"
            auto hasFalse = false;
#line 102 "/src/checker-expressions.do"
            const auto& _iterable_9 = arms;
            for (const auto& patterns : *_iterable_9) {
#line 103 "/src/checker-expressions.do"
                const auto& _iterable_11 = patterns;
                for (const auto& pattern : *_iterable_11) {
#line 104 "/src/checker-expressions.do"
                    {
                        auto _case_subject = pattern;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 106 "/src/checker-expressions.do"
                            {
                                auto _case_subject = value->value;
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
                                    const auto& boolean = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
#line 107 "/src/checker-expressions.do"
                                    if (boolean->value) {
#line 107 "/src/checker-expressions.do"
                                        (hasTrue = true);
                                    } else {
#line 107 "/src/checker-expressions.do"
                                        (hasFalse = true);
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
#line 115 "/src/checker-expressions.do"
            return (hasTrue && hasFalse);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
#line 118 "/src/checker-expressions.do"
            auto hasSuccess = false;
#line 119 "/src/checker-expressions.do"
            auto hasFailure = false;
#line 120 "/src/checker-expressions.do"
            const auto& _iterable_13 = arms;
            for (const auto& patterns : *_iterable_13) {
#line 121 "/src/checker-expressions.do"
                const auto& _iterable_15 = patterns;
                for (const auto& pattern : *_iterable_15) {
#line 122 "/src/checker-expressions.do"
                    {
                        auto _case_subject = pattern;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                            const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
#line 124 "/src/checker-expressions.do"
                            {
                                auto _case_subject = type_->type_;
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                                    const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 126 "/src/checker-expressions.do"
                                    if (named->name == std::string("Success")) {
#line 126 "/src/checker-expressions.do"
                                        (hasSuccess = true);
                                    }
#line 127 "/src/checker-expressions.do"
                                    if (named->name == std::string("Failure")) {
#line 127 "/src/checker-expressions.do"
                                        (hasFailure = true);
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
#line 136 "/src/checker-expressions.do"
            return (hasSuccess && hasFailure);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 138 "/src/checker-expressions.do"
            return enumPatternsExhaustive(state, enum_, arms);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 139 "/src/checker-expressions.do"
            return unionPatternsExhaustive(union_, arms);
    }
    else {
    }
    }
#line 142 "/src/checker-expressions.do"
    return false;
}
#line 145 "/src/checker-expressions.do"
bool integerPatternsExhaustive(const std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>>& arms) {
#line 146 "/src/checker-expressions.do"
    std::shared_ptr<std::vector<bool>> hasLower = std::make_shared<std::vector<bool>>(std::vector<bool>{});
#line 147 "/src/checker-expressions.do"
    std::shared_ptr<std::vector<int32_t>> lowers = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 148 "/src/checker-expressions.do"
    std::shared_ptr<std::vector<bool>> hasUpper = std::make_shared<std::vector<bool>>(std::vector<bool>{});
#line 149 "/src/checker-expressions.do"
    std::shared_ptr<std::vector<int32_t>> uppers = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 150 "/src/checker-expressions.do"
    const auto& _iterable_17 = arms;
    for (const auto& patterns : *_iterable_17) {
#line 151 "/src/checker-expressions.do"
        const auto& _iterable_19 = patterns;
        for (const auto& pattern : *_iterable_19) {
#line 152 "/src/checker-expressions.do"
            {
                auto _case_subject = pattern;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
                    const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
#line 154 "/src/checker-expressions.do"
                    auto lower = 0;
#line 155 "/src/checker-expressions.do"
                    auto lowerPresent = (!doof::is_null(range->start));
#line 156 "/src/checker-expressions.do"
                    if (lowerPresent) {
#line 157 "/src/checker-expressions.do"
                        const auto resolvedLower = integerPatternValue(doof::unwrap_optional(range->start));
#line 158 "/src/checker-expressions.do"
                        if (doof::is_null(resolvedLower)) {
#line 158 "/src/checker-expressions.do"
                            continue;
                        }
#line 159 "/src/checker-expressions.do"
                        (lower = resolvedLower.value());
                    }
#line 161 "/src/checker-expressions.do"
                    auto upper = 0;
#line 162 "/src/checker-expressions.do"
                    auto upperPresent = (!doof::is_null(range->end));
#line 163 "/src/checker-expressions.do"
                    if (upperPresent) {
#line 164 "/src/checker-expressions.do"
                        const auto resolvedUpper = integerPatternValue(doof::unwrap_optional(range->end));
#line 165 "/src/checker-expressions.do"
                        if (doof::is_null(resolvedUpper)) {
#line 165 "/src/checker-expressions.do"
                            continue;
                        }
#line 166 "/src/checker-expressions.do"
                        (upper = resolvedUpper.value());
#line 167 "/src/checker-expressions.do"
                        if (!range->inclusive) {
#line 168 "/src/checker-expressions.do"
                            if (upper == (-2147483647 - 1)) {
#line 168 "/src/checker-expressions.do"
                                continue;
                            }
#line 169 "/src/checker-expressions.do"
                            (upper = (upper - 1));
                        }
                    }
#line 172 "/src/checker-expressions.do"
                    hasLower->push_back(lowerPresent);
#line 172 "/src/checker-expressions.do"
                    lowers->push_back(lower);
#line 173 "/src/checker-expressions.do"
                    hasUpper->push_back(upperPresent);
#line 173 "/src/checker-expressions.do"
                    uppers->push_back(upper);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 176 "/src/checker-expressions.do"
                    const auto resolved = integerPatternValue(value->value);
#line 177 "/src/checker-expressions.do"
                    if (!doof::is_null(resolved)) {
#line 178 "/src/checker-expressions.do"
                        hasLower->push_back(true);
#line 178 "/src/checker-expressions.do"
                        lowers->push_back(resolved.value());
#line 179 "/src/checker-expressions.do"
                        hasUpper->push_back(true);
#line 179 "/src/checker-expressions.do"
                        uppers->push_back(resolved.value());
                    }
            }
            else {
            }
            }
        }
    }
#line 186 "/src/checker-expressions.do"
    auto started = false;
#line 187 "/src/checker-expressions.do"
    auto currentUpper = 0;
#line 188 "/src/checker-expressions.do"
    for (int32_t index = 0; index < static_cast<int32_t>((hasLower)->size()); ++index) {
#line 189 "/src/checker-expressions.do"
        if (doof::array_at(hasLower, index, "src/checker-expressions", 189)) {
#line 189 "/src/checker-expressions.do"
            continue;
        }
#line 190 "/src/checker-expressions.do"
        if (!doof::array_at(hasUpper, index, "src/checker-expressions", 190)) {
#line 190 "/src/checker-expressions.do"
            return true;
        }
#line 191 "/src/checker-expressions.do"
        if (!started || (doof::array_at(uppers, index, "src/checker-expressions", 191) > currentUpper)) {
#line 191 "/src/checker-expressions.do"
            (currentUpper = doof::array_at(uppers, index, "src/checker-expressions", 191));
#line 191 "/src/checker-expressions.do"
            (started = true);
        }
    }
#line 193 "/src/checker-expressions.do"
    if (!started) {
#line 193 "/src/checker-expressions.do"
        return false;
    }
#line 194 "/src/checker-expressions.do"
    for (int32_t pass = 0; pass < static_cast<int32_t>((hasLower)->size()); ++pass) {
#line 195 "/src/checker-expressions.do"
        auto extended = false;
#line 196 "/src/checker-expressions.do"
        for (int32_t index = 0; index < static_cast<int32_t>((hasLower)->size()); ++index) {
#line 197 "/src/checker-expressions.do"
            if (!doof::array_at(hasLower, index, "src/checker-expressions", 197)) {
#line 197 "/src/checker-expressions.do"
                continue;
            }
#line 198 "/src/checker-expressions.do"
            const auto connects = ((doof::array_at(lowers, index, "src/checker-expressions", 198) <= currentUpper) || ((currentUpper < 2147483647) && (doof::array_at(lowers, index, "src/checker-expressions", 198) == (currentUpper + 1))));
#line 199 "/src/checker-expressions.do"
            if (!connects) {
#line 199 "/src/checker-expressions.do"
                continue;
            }
#line 200 "/src/checker-expressions.do"
            if (!doof::array_at(hasUpper, index, "src/checker-expressions", 200)) {
#line 200 "/src/checker-expressions.do"
                return true;
            }
#line 201 "/src/checker-expressions.do"
            if (doof::array_at(uppers, index, "src/checker-expressions", 201) > currentUpper) {
#line 201 "/src/checker-expressions.do"
                (currentUpper = doof::array_at(uppers, index, "src/checker-expressions", 201));
#line 201 "/src/checker-expressions.do"
                (extended = true);
            }
        }
#line 203 "/src/checker-expressions.do"
        if (currentUpper == 2147483647) {
#line 203 "/src/checker-expressions.do"
            return true;
        }
#line 204 "/src/checker-expressions.do"
        if (!extended) {
#line 204 "/src/checker-expressions.do"
            return false;
        }
    }
#line 206 "/src/checker-expressions.do"
    return (currentUpper == 2147483647);
}
#line 209 "/src/checker-expressions.do"
std::optional<int32_t> integerPatternValue(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 210 "/src/checker-expressions.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            const auto& literal = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
#line 211 "/src/checker-expressions.do"
            return literal->value;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 213 "/src/checker-expressions.do"
            if (unary->operator_ == std::string("-")) {
#line 214 "/src/checker-expressions.do"
                const auto value = integerPatternValue(unary->operand);
#line 215 "/src/checker-expressions.do"
                if (!doof::is_null(value)) {
#line 215 "/src/checker-expressions.do"
                    return -value.value();
                }
            }
    }
    else {
    }
    }
#line 220 "/src/checker-expressions.do"
    return std::nullopt;
}
#line 223 "/src/checker-expressions.do"
bool enumPatternsExhaustive(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::EnumType>& enum_, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>>& arms) {
#line 224 "/src/checker-expressions.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, enum_->symbol);
#line 225 "/src/checker-expressions.do"
    if (doof::is_null(declaration)) {
#line 225 "/src/checker-expressions.do"
        return false;
    }
#line 226 "/src/checker-expressions.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enumDeclaration = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 228 "/src/checker-expressions.do"
            const auto& _iterable_24 = enumDeclaration->variants;
            for (const auto& variant : *_iterable_24) {
#line 229 "/src/checker-expressions.do"
                auto found = false;
#line 230 "/src/checker-expressions.do"
                const auto& _iterable_26 = arms;
                for (const auto& patterns : *_iterable_26) {
#line 231 "/src/checker-expressions.do"
                    const auto& _iterable_28 = patterns;
                    for (const auto& pattern : *_iterable_28) {
#line 232 "/src/checker-expressions.do"
                        {
                            auto _case_subject = pattern;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                                const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 234 "/src/checker-expressions.do"
                                {
                                    auto _case_subject = value->value;
                                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
                                        const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 235 "/src/checker-expressions.do"
                                        if (dot->name == variant->name) {
#line 235 "/src/checker-expressions.do"
                                            (found = true);
                                        }
                                }
                                else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                                        const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 236 "/src/checker-expressions.do"
                                        if (member->property == variant->name) {
#line 236 "/src/checker-expressions.do"
                                            (found = true);
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
#line 244 "/src/checker-expressions.do"
                if (!found) {
#line 244 "/src/checker-expressions.do"
                    return false;
                }
            }
#line 246 "/src/checker-expressions.do"
            return true;
    }
    else {
    }
    }
#line 250 "/src/checker-expressions.do"
    return false;
}
#line 253 "/src/checker-expressions.do"
bool unionPatternsExhaustive(const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>>& arms) {
#line 254 "/src/checker-expressions.do"
    const auto& _iterable_30 = union_->types;
    for (const auto& member : *_iterable_30) {
#line 255 "/src/checker-expressions.do"
        auto found = false;
#line 256 "/src/checker-expressions.do"
        const auto& _iterable_32 = arms;
        for (const auto& patterns : *_iterable_32) {
#line 257 "/src/checker-expressions.do"
            const auto& _iterable_34 = patterns;
            for (const auto& pattern : *_iterable_34) {
#line 258 "/src/checker-expressions.do"
                {
                    auto _case_subject = pattern;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                        const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
#line 259 "/src/checker-expressions.do"
                        if ((!doof::is_null(type_->resolvedType)) && ::app_src_checker_types_::sameType(member, doof::unwrap_optional(type_->resolvedType))) {
#line 259 "/src/checker-expressions.do"
                            (found = true);
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                        const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 260 "/src/checker-expressions.do"
                        {
                            auto _case_subject = value->value;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
#line 260 "/src/checker-expressions.do"
                                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 260 "/src/checker-expressions.do"
                                    (found = true);
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
#line 265 "/src/checker-expressions.do"
        if (!found) {
#line 265 "/src/checker-expressions.do"
            return false;
        }
    }
#line 267 "/src/checker-expressions.do"
    return true;
}
#line 270 "/src/checker-expressions.do"
void checkCasePatterns(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>& patterns, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& subjectType, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 271 "/src/checker-expressions.do"
    const auto& _iterable_36 = patterns;
    for (const auto& pattern : *_iterable_36) {
#line 272 "/src/checker-expressions.do"
        {
            auto _case_subject = pattern;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
#line 274 "/src/checker-expressions.do"
                std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolved = ::app_src_checker_types_::unknownType();
#line 275 "/src/checker-expressions.do"
                auto contextualResultArm = false;
#line 276 "/src/checker-expressions.do"
                {
                    auto _case_subject = subjectType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
#line 278 "/src/checker-expressions.do"
                        {
                            auto _case_subject = type_->type_;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 280 "/src/checker-expressions.do"
                                if ((named->name == std::string("Success")) || (named->name == std::string("Failure"))) {
#line 281 "/src/checker-expressions.do"
                                    (contextualResultArm = true);
#line 282 "/src/checker-expressions.do"
                                    (resolved = subjectType);
#line 284 "/src/checker-expressions.do"
                                    const auto& _iterable_38 = named->typeArgs;
                                    for (const auto& argument : *_iterable_38) {
#line 284 "/src/checker-expressions.do"
                                        ::app_src_checker_resolution_::resolveType(state, argument, doof::unwrap_optional(state->info), scope);
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
#line 292 "/src/checker-expressions.do"
                if (!contextualResultArm) {
#line 292 "/src/checker-expressions.do"
                    (resolved = ::app_src_checker_resolution_::resolveType(state, type_->type_, doof::unwrap_optional(state->info), scope));
                }
#line 293 "/src/checker-expressions.do"
                {
                    auto _case_subject = type_->type_;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 294 "/src/checker-expressions.do"
                        (named->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(resolved));
                }
                else {
                }
                }
#line 297 "/src/checker-expressions.do"
                (type_->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(resolved));
#line 298 "/src/checker-expressions.do"
                if (!typesOverlap(subjectType, resolved)) {
#line 299 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, ((((std::string("Case type pattern \"") + ::app_src_checker_types_::typeName(resolved)) + std::string("\" cannot match subject type \"")) + ::app_src_checker_types_::typeName(subjectType)) + std::string("\"")), type_->span);
                }
#line 301 "/src/checker-expressions.do"
                if (type_->name != std::string("_")) {
#line 302 "/src/checker-expressions.do"
                    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(type_->name, std::string("case-binding"), resolved, false, ::app_src_checker_validation_::checkerSemanticSpan(type_->span), state->info->path, nullptr, ::app_src_checker_symbols_::casePatternName(type_), std::string(""), std::string("")));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 314 "/src/checker-expressions.do"
                const auto valueType = checkExpression(state, value->value, scope, ::app_src_checker_symbols_::optionalResolvedType(subjectType));
#line 315 "/src/checker-expressions.do"
                if (!typesOverlap(subjectType, valueType)) {
#line 316 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, ((((std::string("Case value pattern of type \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\" cannot match subject type \"")) + ::app_src_checker_types_::typeName(subjectType)) + std::string("\"")), value->span);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
                const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
#line 320 "/src/checker-expressions.do"
                validateCaseRangeBound(state, range->start, subjectType, scope, range->span);
#line 321 "/src/checker-expressions.do"
                validateCaseRangeBound(state, range->end, subjectType, scope, range->span);
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
        }
        }
    }
}
#line 328 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkExpression(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 329 "/src/checker-expressions.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
#line 331 "/src/checker-expressions.do"
            const auto yieldScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, true, [&]() -> std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (doof::is_null(expected)) { return ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()); } return expected; }(), false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 336 "/src/checker-expressions.do"
            const auto completes = ::app_src_checker_statements_::checkBlock(state, yieldBlock->body, yieldScope, false);
#line 337 "/src/checker-expressions.do"
            if (completes) {
#line 338 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, std::string("Yield blocks must yield a value on every path"), yieldBlock->body->span);
            }
#line 340 "/src/checker-expressions.do"
            auto resolved = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_39 = yieldScope->yieldType; if (doof::is_null(_coalesce_39)) return ::app_src_checker_types_::unknownType(); return doof::unwrap_optional(_coalesce_39); }();
#line 341 "/src/checker-expressions.do"
            if (!completes && (std::visit([](auto&& _obj) { return _obj->kind; }, resolved) == std::string("unknown"))) {
#line 341 "/src/checker-expressions.do"
                (resolved = ::app_src_checker_types_::neverType());
            }
#line 342 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(yieldBlock), resolved);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
#line 345 "/src/checker-expressions.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> errorTypes = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 346 "/src/checker-expressions.do"
            const auto catchScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, true, errorTypes, false);
#line 347 "/src/checker-expressions.do"
            ::app_src_checker_statements_::checkBlock(state, catch_->body, catchScope, false);
#line 348 "/src/checker-expressions.do"
            if (static_cast<int32_t>((errorTypes)->size()) == 0) {
#line 349 "/src/checker-expressions.do"
                state->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("warning"), std::string("catch block contains no 'try' statements"), ::app_src_checker_validation_::checkerSemanticSpan(catch_->span), state->info->path, std::string("")));
#line 355 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(catch_), ::app_src_checker_types_::noneType());
            }
#line 357 "/src/checker-expressions.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 358 "/src/checker-expressions.do"
            const auto& _iterable_41 = errorTypes;
            for (const auto& errorType : *_iterable_41) {
#line 358 "/src/checker-expressions.do"
                members->push_back(errorType);
            }
#line 359 "/src/checker-expressions.do"
            members->push_back(::app_src_checker_types_::noneType());
#line 360 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(catch_), ::app_src_checker_types_::unionType(members));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
#line 363 "/src/checker-expressions.do"
            if (!doof::is_null(expected)) {
#line 363 "/src/checker-expressions.do"
                {
                    auto _case_subject = doof::unwrap_optional(expected);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                        const auto& primitiveExpected = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 365 "/src/checker-expressions.do"
                        if ((((primitiveExpected->name == std::string("byte")) || (primitiveExpected->name == std::string("long"))) || (primitiveExpected->name == std::string("float"))) || (primitiveExpected->name == std::string("double"))) {
#line 366 "/src/checker-expressions.do"
                            return ::app_src_checker_common_::finish(state, expression, doof::unwrap_optional(expected));
                        }
                }
                else {
                }
                }
            }
#line 371 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::primitive(std::string("int")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
#line 374 "/src/checker-expressions.do"
            if (!doof::is_null(expected)) {
#line 374 "/src/checker-expressions.do"
                {
                    auto _case_subject = doof::unwrap_optional(expected);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                        const auto& primitiveExpected = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 375 "/src/checker-expressions.do"
                        if (primitiveExpected->name == std::string("double")) {
#line 375 "/src/checker-expressions.do"
                            return ::app_src_checker_common_::finish(state, expression, doof::unwrap_optional(expected));
                        }
                }
                else {
                }
                }
            }
#line 378 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::primitive(std::string("long")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
#line 381 "/src/checker-expressions.do"
            if (!doof::is_null(expected)) {
#line 381 "/src/checker-expressions.do"
                {
                    auto _case_subject = doof::unwrap_optional(expected);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                        const auto& primitiveExpected = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 382 "/src/checker-expressions.do"
                        if (primitiveExpected->name == std::string("double")) {
#line 382 "/src/checker-expressions.do"
                            return ::app_src_checker_common_::finish(state, expression, doof::unwrap_optional(expected));
                        }
                }
                else {
                }
                }
            }
#line 385 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::primitive(std::string("float")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
#line 388 "/src/checker-expressions.do"
            if (!doof::is_null(expected)) {
#line 388 "/src/checker-expressions.do"
                {
                    auto _case_subject = doof::unwrap_optional(expected);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                        const auto& primitiveExpected = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 389 "/src/checker-expressions.do"
                        if (primitiveExpected->name == std::string("float")) {
#line 389 "/src/checker-expressions.do"
                            return ::app_src_checker_common_::finish(state, expression, doof::unwrap_optional(expected));
                        }
                }
                else {
                }
                }
            }
#line 392 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::primitive(std::string("double")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 395 "/src/checker-expressions.do"
            auto diverges = false;
#line 396 "/src/checker-expressions.do"
            const auto& _iterable_43 = string_->interpolations;
            for (const auto& interpolation : *_iterable_43) {
#line 397 "/src/checker-expressions.do"
                const auto interpolationType = checkExpression(state, interpolation, scope, std::monostate{});
#line 398 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, interpolationType) == std::string("never")) {
#line 398 "/src/checker-expressions.do"
                    (diverges = true);
                } else if (!::app_src_checker_types_::isStringInterpolatable(interpolationType)) {
#line 400 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Type \"") + ::app_src_checker_types_::typeName(interpolationType)) + std::string("\" cannot be used in string interpolation")), std::visit([](auto&& _obj) { return _obj->span; }, interpolation));
                }
            }
#line 403 "/src/checker-expressions.do"
            if (diverges) {
#line 403 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::neverType());
            }
#line 404 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::primitive(std::string("string")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
#line 406 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::primitive(std::string("char")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
#line 407 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::primitive(std::string("bool")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
            const auto& noneLiteral = std::get<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject);
#line 409 "/src/checker-expressions.do"
            if ((noneLiteral->sourceSpelling != std::string("none")) && doof::is_null(noneLiteral->resolvedType)) {
#line 409 "/src/checker-expressions.do"
                ::app_src_checker_common_::deprecatedNoneAlias(state, noneLiteral->sourceSpelling, noneLiteral->span, std::string(""));
            }
#line 410 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::noneType());
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallerExpression>>(_case_subject)) {
#line 413 "/src/checker-expressions.do"
            if (!state->allowsCaller) {
#line 413 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, std::string("@caller is only valid as a parameter or class-field default value"), std::visit([](auto&& _obj) { return _obj->span; }, expression));
            }
#line 414 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_symbols_::builtinSourceLocationType()));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 416 "/src/checker-expressions.do"
            return checkDotShorthand(state, dot, expected);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 417 "/src/checker-expressions.do"
            return checkIdentifier(state, identifier, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 418 "/src/checker-expressions.do"
            return checkBinary(state, binary, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 419 "/src/checker-expressions.do"
            return checkUnary(state, unary, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject)) {
            const auto& as_ = std::get<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject);
#line 420 "/src/checker-expressions.do"
            return checkAs(state, as_, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
#line 421 "/src/checker-expressions.do"
            return checkAssignment(state, assignment, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 423 "/src/checker-expressions.do"
            auto objectType = ::app_src_checker_types_::unknownType();
#line 424 "/src/checker-expressions.do"
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> namespaceMember = std::monostate{};
#line 425 "/src/checker-expressions.do"
            auto namespaceName = std::string("");
#line 426 "/src/checker-expressions.do"
            {
                auto _case_subject = member->object;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                    const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 430 "/src/checker-expressions.do"
                    const auto localBinding = ::app_src_checker_symbols_::lookup(scope, identifier->name);
#line 431 "/src/checker-expressions.do"
                    if (doof::is_null(localBinding) && ::app_src_checker_symbols_::isNamespaceImport(doof::unwrap_optional(state->info), identifier->name)) {
#line 432 "/src/checker-expressions.do"
                        (namespaceName = identifier->name);
#line 433 "/src/checker-expressions.do"
                        (member->resolvedNamespaceAccess = true);
#line 434 "/src/checker-expressions.do"
                        if (::app_src_checker_symbols_::isTypeOnlyNamespaceImport(doof::unwrap_optional(state->info), identifier->name)) {
#line 435 "/src/checker-expressions.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Type-only namespace import '") + identifier->name) + std::string("' cannot be used as a value")), member->span);
#line 436 "/src/checker-expressions.do"
                            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::unknownType());
                        } else {
#line 438 "/src/checker-expressions.do"
                            (member->resolvedNamespaceSymbol = ::app_src_checker_symbols_::namespaceMemberSymbol(doof::unwrap_optional(state->info), identifier->name, member->property, state->result));
#line 439 "/src/checker-expressions.do"
                            (namespaceMember = doof::optional_value(::app_src_checker_symbols_::namespaceMemberType(doof::unwrap_optional(state->info), identifier->name, member->property, state->result)));
                        }
                    } else {
#line 442 "/src/checker-expressions.do"
                        (objectType = checkExpression(state, member->object, scope, std::monostate{}));
                    }
            }
            else {
#line 445 "/src/checker-expressions.do"
                    (objectType = checkExpression(state, member->object, scope, std::monostate{}));
            }
            }
#line 447 "/src/checker-expressions.do"
            if (!doof::is_null(namespaceMember)) {
#line 448 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(namespaceMember)) == std::string("unknown")) {
#line 449 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, ((((std::string("Namespace \"") + namespaceName) + std::string("\" has no member \"")) + member->property) + std::string("\"")), member->span);
                }
#line 451 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, expression, doof::unwrap_optional(namespaceMember));
            }
#line 453 "/src/checker-expressions.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, objectType) == std::string("never")) {
#line 453 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::neverType());
            }
#line 454 "/src/checker-expressions.do"
            std::shared_ptr<::app_src_semantic_::WeakResolvedType> weakReceiver = nullptr;
#line 455 "/src/checker-expressions.do"
            {
                auto _case_subject = objectType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                    const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 457 "/src/checker-expressions.do"
                    (weakReceiver = weak_);
#line 458 "/src/checker-expressions.do"
                    (objectType = weakAccessTarget(weak_->inner));
#line 459 "/src/checker-expressions.do"
                    if (!member->optional && !member->force) {
#line 460 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, std::string("Weak reference member access requires '\?.' or '!.'"), member->span);
                    }
            }
            else {
            }
            }
#line 465 "/src/checker-expressions.do"
            {
                auto _case_subject = member->object;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                    const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 467 "/src/checker-expressions.do"
                    if ((member->property == std::string("parse")) && legacyNumericParseType(identifier)) {
#line 468 "/src/checker-expressions.do"
                        const auto replacement = ((identifier->name == std::string("byte")) ? std::string("parseByte") : ((identifier->name == std::string("int")) ? std::string("parseInt") : ((identifier->name == std::string("long")) ? std::string("parseLong") : ((identifier->name == std::string("float")) ? std::string("parseFloat") : std::string("parseDouble")))));
#line 472 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, (((identifier->name + std::string(".parse was removed; import ")) + replacement) + std::string(" from \"std/parse\"")), member->span);
#line 473 "/src/checker-expressions.do"
                        return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::unknownType());
                    }
            }
            else {
            }
            }
#line 478 "/src/checker-expressions.do"
            const auto diagnosticCount = static_cast<int32_t>((state->diagnostics)->size());
#line 479 "/src/checker-expressions.do"
            const auto memberValue = ::app_src_checker_resolution_::memberType(state, objectType, member->property, member->span, true);
#line 480 "/src/checker-expressions.do"
            if (((std::visit([](auto&& _obj) { return _obj->kind; }, memberValue) == std::string("unknown")) && (std::visit([](auto&& _obj) { return _obj->kind; }, objectType) != std::string("unknown"))) && (static_cast<int32_t>((state->diagnostics)->size()) == diagnosticCount)) {
#line 481 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((((std::string("Type \"") + ::app_src_checker_types_::typeName(objectType)) + std::string("\" has no member \"")) + member->property) + std::string("\"")), member->span);
            }
#line 483 "/src/checker-expressions.do"
            (member->resolvedStaticOwner = ::app_src_checker_generics_::staticMemberOwner(objectType, member->property, state->result));
#line 484 "/src/checker-expressions.do"
            if ((!doof::is_null(member->resolvedStaticOwner)) && !isNamedStaticReceiver(member->object)) {
#line 485 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Static member '") + member->property) + std::string("' cannot be accessed through an instance with '.'; use '::'")), member->span);
            }
#line 487 "/src/checker-expressions.do"
            if ((doof::is_null(member->resolvedStaticOwner) && isNamedStaticReceiver(member->object)) && declaredInstanceMember(state, objectType, member->property)) {
#line 488 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Instance member '") + member->property) + std::string("' cannot be accessed through a class")), member->span);
            }
#line 490 "/src/checker-expressions.do"
            (member->resolvedCallableField = ::app_src_checker_calls_::callableField(state, objectType, member->property));
#line 491 "/src/checker-expressions.do"
            if (!doof::is_null(weakReceiver)) {
#line 492 "/src/checker-expressions.do"
                {
                    auto _case_subject = memberValue;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
#line 493 "/src/checker-expressions.do"
                        return ::app_src_checker_common_::finish(state, expression, memberValue);
                }
                else {
#line 495 "/src/checker-expressions.do"
                        if (member->optional) {
#line 495 "/src/checker-expressions.do"
                            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::resultType(::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{memberValue, ::app_src_checker_types_::noneType()})), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::weakReferenceErrorType())));
                        }
                }
                }
            }
#line 499 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, memberValue);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 502 "/src/checker-expressions.do"
            const auto objectType = checkExpression(state, index->object, scope, std::monostate{});
#line 503 "/src/checker-expressions.do"
            const auto indexValueType = checkExpression(state, index->index, scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::primitive(std::string("int"))));
#line 504 "/src/checker-expressions.do"
            const auto resolved = ::app_src_checker_resolution_::indexType(state, objectType, indexValueType, index->span);
#line 505 "/src/checker-expressions.do"
            if ((std::visit([](auto&& _obj) { return _obj->kind; }, objectType) == std::string("never")) || (std::visit([](auto&& _obj) { return _obj->kind; }, indexValueType) == std::string("never"))) {
#line 505 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::neverType());
            }
#line 506 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, resolved);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 508 "/src/checker-expressions.do"
            return ::app_src_checker_calls_::checkCall(state, call, scope, expected);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 509 "/src/checker-expressions.do"
            return ::app_src_checker_literals_::checkArray(state, array, scope, expected);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
#line 511 "/src/checker-expressions.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> elements = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 512 "/src/checker-expressions.do"
            auto diverges = false;
#line 513 "/src/checker-expressions.do"
            std::shared_ptr<::app_src_semantic_::TupleResolvedType> expectedTuple = nullptr;
#line 514 "/src/checker-expressions.do"
            if (!doof::is_null(expected)) {
#line 515 "/src/checker-expressions.do"
                {
                    auto _case_subject = doof::unwrap_optional(expected);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                        const auto& tupleExpected = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 515 "/src/checker-expressions.do"
                        (expectedTuple = tupleExpected);
                }
                else {
                }
                }
            }
#line 517 "/src/checker-expressions.do"
            for (int32_t index = 0; index < static_cast<int32_t>((tuple->elements)->size()); ++index) {
#line 518 "/src/checker-expressions.do"
                const auto item = doof::array_at(tuple->elements, index, "src/checker-expressions", 518);
#line 519 "/src/checker-expressions.do"
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> itemExpected = std::monostate{};
#line 520 "/src/checker-expressions.do"
                if ((!doof::is_null(expectedTuple)) && (index < static_cast<int32_t>((expectedTuple->elements)->size()))) {
#line 520 "/src/checker-expressions.do"
                    (itemExpected = ::app_src_checker_symbols_::optionalResolvedType(doof::array_at(expectedTuple->elements, index, "src/checker-expressions", 520)));
                }
#line 521 "/src/checker-expressions.do"
                const auto itemType = checkExpression(state, item, scope, itemExpected);
#line 522 "/src/checker-expressions.do"
                elements->push_back(itemType);
#line 523 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, itemType) == std::string("never")) {
#line 523 "/src/checker-expressions.do"
                    (diverges = true);
                }
            }
#line 525 "/src/checker-expressions.do"
            if (diverges) {
#line 525 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::neverType());
            }
#line 526 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::tupleType(elements));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 529 "/src/checker-expressions.do"
            return ::app_src_checker_literals_::checkObject(state, object, scope, expected);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
#line 531 "/src/checker-expressions.do"
            return ::app_src_checker_calls_::checkLambda(state, lambda, scope, expected);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
#line 533 "/src/checker-expressions.do"
            const auto conditionType = checkExpression(state, if_->condition, scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::primitive(std::string("bool"))));
#line 534 "/src/checker-expressions.do"
            ::app_src_checker_common_::requireBool(state, conditionType, std::visit([](auto&& _obj) { return _obj->span; }, if_->condition));
#line 535 "/src/checker-expressions.do"
            const auto thenType = checkExpression(state, if_->then_, scope, expected);
#line 536 "/src/checker-expressions.do"
            const auto elseType = checkExpression(state, if_->else_, scope, expected);
#line 537 "/src/checker-expressions.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, conditionType) == std::string("never")) {
#line 537 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::neverType());
            }
#line 538 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::joinTypes(thenType, elseType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
#line 540 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, checkCaseExpression(state, case_, scope, expected));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 541 "/src/checker-expressions.do"
            return ::app_src_checker_calls_::checkConstruct(state, construct, scope, expected);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 543 "/src/checker-expressions.do"
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 545 "/src/checker-expressions.do"
                    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedValue = std::monostate{};
#line 546 "/src/checker-expressions.do"
                    if (!doof::is_null(expected)) {
#line 547 "/src/checker-expressions.do"
                        {
                            auto _case_subject = doof::unwrap_optional(expected);
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
                                const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 548 "/src/checker-expressions.do"
                                (expectedValue = doof::optional_value(promise->valueType));
                        }
                        else {
                        }
                        }
                    }
#line 552 "/src/checker-expressions.do"
                    const auto asyncScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, true, [&]() -> std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (doof::is_null(expectedValue)) { return ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()); } return expectedValue; }(), false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 557 "/src/checker-expressions.do"
                    const auto completes = ::app_src_checker_statements_::checkBlock(state, block, asyncScope, false);
#line 558 "/src/checker-expressions.do"
                    if (completes) {
#line 558 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, std::string("Async blocks must yield a value on every path"), block->span);
                    }
#line 559 "/src/checker-expressions.do"
                    auto valueType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_45 = asyncScope->yieldType; if (doof::is_null(_coalesce_45)) return ::app_src_checker_types_::unknownType(); return doof::unwrap_optional(_coalesce_45); }();
#line 560 "/src/checker-expressions.do"
                    if (!completes && (std::visit([](auto&& _obj) { return _obj->kind; }, valueType) == std::string("unknown"))) {
#line 560 "/src/checker-expressions.do"
                        (valueType = ::app_src_checker_types_::neverType());
                    }
#line 561 "/src/checker-expressions.do"
                    const auto violation = ::app_src_checker_async_::asyncResultViolation(state->result, valueType);
#line 562 "/src/checker-expressions.do"
                    if (!doof::is_null(violation)) {
#line 563 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, (((std::string("Async block result type \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\" cannot cross from the worker: ")) + violation.value()), async_->span);
                    }
#line 565 "/src/checker-expressions.do"
                    return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::promiseType(valueType));
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 568 "/src/checker-expressions.do"
                    const auto innerType = checkExpression(state, inner, scope, std::monostate{});
#line 569 "/src/checker-expressions.do"
                    auto actorCall = false;
#line 570 "/src/checker-expressions.do"
                    auto isolatedCall = false;
#line 571 "/src/checker-expressions.do"
                    {
                        auto _case_subject = inner;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 573 "/src/checker-expressions.do"
                            (isolatedCall = (!doof::is_null(call->resolvedFunction)));
#line 574 "/src/checker-expressions.do"
                            {
                                auto _case_subject = call->callee;
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                                    const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 576 "/src/checker-expressions.do"
                                    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 577 "/src/checker-expressions.do"
                                        {
                                            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
#line 578 "/src/checker-expressions.do"
                                                (actorCall = true);
                                        }
                                        else {
                                        }
                                        }
                                    }
                            }
                            else {
                            }
                            }
#line 585 "/src/checker-expressions.do"
                            if (!actorCall && isolatedCall) {
#line 586 "/src/checker-expressions.do"
                                for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
#line 587 "/src/checker-expressions.do"
                                    const auto argumentType = std::visit([](auto&& _obj) { return _obj->resolvedType; }, doof::array_at(call->args, i, "src/checker-expressions", 587)->value);
#line 588 "/src/checker-expressions.do"
                                    if (doof::is_null(argumentType)) {
#line 588 "/src/checker-expressions.do"
                                        continue;
                                    }
#line 589 "/src/checker-expressions.do"
                                    const auto violation = ::app_src_checker_actor_boundary_::findActorBoundaryViolation(state->result, doof::unwrap_optional(argumentType));
#line 590 "/src/checker-expressions.do"
                                    if (!doof::is_null(violation)) {
#line 591 "/src/checker-expressions.do"
                                        ::app_src_checker_common_::typeError(state, (((((std::string("Async call argument ") + doof::to_string((i + 1))) + std::string(" of type \"")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(argumentType))) + std::string("\" cannot cross to the worker: ")) + violation->reason), doof::array_at(call->args, i, "src/checker-expressions", 593)->span);
                                    }
                                }
#line 597 "/src/checker-expressions.do"
                                {
                                    auto _case_subject = call->callee;
                                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                                        const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 599 "/src/checker-expressions.do"
                                        if (doof::is_null(member->resolvedStaticOwner) && (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)))) {
#line 600 "/src/checker-expressions.do"
                                            const auto receiverViolation = ::app_src_checker_actor_boundary_::findActorBoundaryViolation(state->result, doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)));
#line 601 "/src/checker-expressions.do"
                                            if (!doof::is_null(receiverViolation)) {
#line 602 "/src/checker-expressions.do"
                                                ::app_src_checker_common_::typeError(state, (((std::string("Async call receiver of type \"") + ::app_src_checker_types_::typeName(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)))) + std::string("\" cannot cross to the worker: ")) + receiverViolation->reason), std::visit([](auto&& _obj) { return _obj->span; }, member->object));
                                            }
                                        }
                                }
                                else {
                                }
                                }
#line 611 "/src/checker-expressions.do"
                                const auto resultViolation = ::app_src_checker_async_::asyncResultViolation(state->result, innerType);
#line 612 "/src/checker-expressions.do"
                                if (!doof::is_null(resultViolation)) {
#line 613 "/src/checker-expressions.do"
                                    ::app_src_checker_common_::typeError(state, (((std::string("Async call result type \"") + ::app_src_checker_types_::typeName(innerType)) + std::string("\" cannot cross from the worker: ")) + resultViolation.value()), async_->span);
                                }
                            }
                    }
                    else {
                    }
                    }
#line 622 "/src/checker-expressions.do"
                    if (!actorCall && !isolatedCall) {
#line 623 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, std::string("`async` requires an actor method call or an inferrably isolated function call"), async_->span);
                    }
#line 625 "/src/checker-expressions.do"
                    return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::promiseType(innerType));
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
#line 630 "/src/checker-expressions.do"
            const auto retiredType = checkExpression(state, retire_->actor, scope, std::monostate{});
#line 631 "/src/checker-expressions.do"
            {
                auto _case_subject = retiredType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                    const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 632 "/src/checker-expressions.do"
                    return ::app_src_checker_common_::finish(state, expression, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass));
            }
            else {
#line 633 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Cannot retire non-actor type \"") + ::app_src_checker_types_::typeName(retiredType)) + std::string("\"")), retire_->span);
#line 633 "/src/checker-expressions.do"
                    return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::unknownType());
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actorCreation = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 637 "/src/checker-expressions.do"
            const auto symbol = ::app_src_checker_symbols_::symbolFor(doof::unwrap_optional(state->info), actorCreation->className);
#line 638 "/src/checker-expressions.do"
            if (doof::is_null(symbol) || (symbol->kind != std::string("class"))) {
#line 639 "/src/checker-expressions.do"
                const auto& _iterable_48 = actorCreation->args;
                for (const auto& argument : *_iterable_48) {
#line 639 "/src/checker-expressions.do"
                    checkExpression(state, argument, scope, std::monostate{});
                }
#line 640 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Actor requires a class type; \"") + actorCreation->className) + std::string("\" is not a class")), actorCreation->span);
#line 641 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::unknownType());
            }
#line 643 "/src/checker-expressions.do"
            const auto inner = ::app_src_checker_types_::classType(actorCreation->className, doof::unwrap_optional(symbol), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
#line 644 "/src/checker-expressions.do"
            (actorCreation->resolvedConstructor = ::app_src_checker_generics_::constructorForClass(inner, state->result));
#line 645 "/src/checker-expressions.do"
            if (((!doof::is_null(actorCreation->resolvedConstructor)) && actorCreation->resolvedConstructor->private_) && (inner->symbol->module != state->info->path)) {
#line 646 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Constructor for \"") + inner->name) + std::string("\" is private")), actorCreation->span);
            }
#line 648 "/src/checker-expressions.do"
            if (!doof::is_null(actorCreation->resolvedConstructor)) {
#line 649 "/src/checker-expressions.do"
                const auto constructorType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_49 = actorCreation->resolvedConstructor->resolvedType; if (doof::is_null(_coalesce_49)) return ::app_src_checker_symbols_::methodSignature(doof::unwrap_optional(actorCreation->resolvedConstructor), ::app_src_checker_interfaces_::classModuleFor(state->result, inner->symbol), state->result); return doof::unwrap_optional(_coalesce_49); }();
#line 650 "/src/checker-expressions.do"
                {
                    auto _case_subject = constructorType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                        const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 652 "/src/checker-expressions.do"
                        if (!::app_src_checker_types_::sameType(function_->returnType, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(inner))) {
#line 653 "/src/checker-expressions.do"
                            ::app_src_checker_common_::typeError(state, ((((std::string("Actor constructor factory for \"") + inner->name) + std::string("\" must return ")) + inner->name) + std::string(" directly")), actorCreation->span);
                        }
                }
                else {
                }
                }
            }
#line 659 "/src/checker-expressions.do"
            const auto params = actorConstructorParameters(state, inner);
#line 660 "/src/checker-expressions.do"
            validateActorFieldConstructorVisibility(state, actorCreation, inner);
#line 661 "/src/checker-expressions.do"
            auto requiredCount = 0;
#line 662 "/src/checker-expressions.do"
            const auto& _iterable_51 = params;
            for (const auto& parameter : *_iterable_51) {
#line 662 "/src/checker-expressions.do"
                if (!parameter->hasDefault) {
#line 662 "/src/checker-expressions.do"
                    (requiredCount = (requiredCount + 1));
                }
            }
#line 663 "/src/checker-expressions.do"
            if ((static_cast<int32_t>((actorCreation->args)->size()) < requiredCount) || (static_cast<int32_t>((actorCreation->args)->size()) > static_cast<int32_t>((params)->size()))) {
#line 664 "/src/checker-expressions.do"
                const auto range = ((requiredCount == static_cast<int32_t>((params)->size())) ? doof::to_string(requiredCount) : ((doof::to_string(requiredCount) + std::string("-")) + doof::to_string(static_cast<int32_t>((params)->size()))));
#line 665 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, (((((std::string("Actor \"") + actorCreation->className) + std::string("\" expects ")) + range) + std::string(" constructor argument(s) but got ")) + doof::to_string(static_cast<int32_t>((actorCreation->args)->size()))), actorCreation->span);
            }
#line 667 "/src/checker-expressions.do"
            for (int32_t i = 0; i < static_cast<int32_t>((actorCreation->args)->size()); ++i) {
#line 668 "/src/checker-expressions.do"
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedArgument = std::monostate{};
#line 669 "/src/checker-expressions.do"
                if (i < static_cast<int32_t>((params)->size())) {
#line 669 "/src/checker-expressions.do"
                    (expectedArgument = ::app_src_checker_symbols_::optionalResolvedType(doof::array_at(params, i, "src/checker-expressions", 669)->type_));
                }
#line 670 "/src/checker-expressions.do"
                const auto actual = checkExpression(state, doof::array_at(actorCreation->args, i, "src/checker-expressions", 670), scope, expectedArgument);
#line 671 "/src/checker-expressions.do"
                if ((!doof::is_null(expectedArgument)) && !::app_src_checker_types_::isAssignable(actual, doof::unwrap_optional(expectedArgument))) {
#line 672 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, (((((std::string("Actor constructor argument ") + doof::to_string((i + 1))) + std::string(" has type ")) + ::app_src_checker_types_::typeName(actual)) + std::string("; expected ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expectedArgument))), std::visit([](auto&& _obj) { return _obj->span; }, doof::array_at(actorCreation->args, i, "src/checker-expressions", 672)));
                }
#line 674 "/src/checker-expressions.do"
                const auto violation = ::app_src_checker_actor_boundary_::findActorBoundaryViolation(state->result, actual);
#line 675 "/src/checker-expressions.do"
                if (!doof::is_null(violation)) {
#line 676 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, (((((std::string("Actor constructor argument ") + doof::to_string((i + 1))) + std::string(" of type \"")) + ::app_src_checker_types_::typeName(actual)) + std::string("\" cannot cross actor boundary: ")) + violation->reason), std::visit([](auto&& _obj) { return _obj->span; }, doof::array_at(actorCreation->args, i, "src/checker-expressions", 678)));
                }
            }
#line 682 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::actorType(inner));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
            const auto& this_ = std::get<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject);
#line 685 "/src/checker-expressions.do"
            std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 686 "/src/checker-expressions.do"
            while (!doof::is_null(current)) {
#line 687 "/src/checker-expressions.do"
                if (current->staticContext) {
#line 688 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, std::string("Cannot use 'this' in a static method"), this_->span);
#line 689 "/src/checker-expressions.do"
                    return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::unknownType());
                }
#line 691 "/src/checker-expressions.do"
                if (!doof::is_null(current->thisType)) {
#line 691 "/src/checker-expressions.do"
                    break;
                }
#line 692 "/src/checker-expressions.do"
                (current = current->parent);
            }
#line 694 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_symbols_::currentThisType(scope));
    }
    else {
#line 696 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::unknownType());
    }
    }
#line 698 "/src/checker-expressions.do"
    return ::app_src_checker_types_::unknownType();
}
#line 701 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> weakAccessTarget(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 702 "/src/checker-expressions.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 704 "/src/checker-expressions.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> present = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 705 "/src/checker-expressions.do"
            const auto& _iterable_54 = union_->types;
            for (const auto& member : *_iterable_54) {
#line 705 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 705 "/src/checker-expressions.do"
                    present->push_back(member);
                }
            }
#line 706 "/src/checker-expressions.do"
            if (static_cast<int32_t>((present)->size()) > 0) {
#line 706 "/src/checker-expressions.do"
                return ::app_src_checker_types_::unionType(present);
            }
    }
    else {
    }
    }
#line 710 "/src/checker-expressions.do"
    return type_;
}
#line 713 "/src/checker-expressions.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> actorConstructorParameters(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::ClassType>& inner) {
#line 714 "/src/checker-expressions.do"
    const auto constructor = ::app_src_checker_generics_::constructorForClass(inner, state->result);
#line 715 "/src/checker-expressions.do"
    if (!doof::is_null(constructor)) {
#line 716 "/src/checker-expressions.do"
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 717 "/src/checker-expressions.do"
        const auto& _iterable_56 = constructor->params;
        for (const auto& parameter : *_iterable_56) {
#line 718 "/src/checker-expressions.do"
            params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_57 = parameter->resolvedType; if (doof::is_null(_coalesce_57)) return ::app_src_checker_types_::unknownType(); return doof::unwrap_optional(_coalesce_57); }(), (!doof::is_null(parameter->defaultValue))));
        }
#line 724 "/src/checker-expressions.do"
        return params;
    }
#line 726 "/src/checker-expressions.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 727 "/src/checker-expressions.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, inner->symbol);
#line 728 "/src/checker-expressions.do"
    if (doof::is_null(declaration)) {
#line 728 "/src/checker-expressions.do"
        return params;
    }
#line 729 "/src/checker-expressions.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 731 "/src/checker-expressions.do"
            const auto& _iterable_59 = class_->fields;
            for (const auto& field : *_iterable_59) {
#line 732 "/src/checker-expressions.do"
                if (field->static_ || field->const_) {
#line 732 "/src/checker-expressions.do"
                    continue;
                }
#line 733 "/src/checker-expressions.do"
                const auto& _iterable_61 = field->names;
                for (const auto& name : *_iterable_61) {
#line 734 "/src/checker-expressions.do"
                    params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(name, ::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(inner), name, field->span, false), (!doof::is_null(field->defaultValue))));
                }
            }
    }
    else {
    }
    }
#line 744 "/src/checker-expressions.do"
    return params;
}
#line 747 "/src/checker-expressions.do"
void validateActorFieldConstructorVisibility(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_semantic_::ClassType>& inner) {
#line 748 "/src/checker-expressions.do"
    if ((!doof::is_null(expression->resolvedConstructor)) || (inner->symbol->module == state->info->path)) {
#line 748 "/src/checker-expressions.do"
        return;
    }
#line 749 "/src/checker-expressions.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, inner->symbol);
#line 750 "/src/checker-expressions.do"
    if (doof::is_null(declaration)) {
#line 750 "/src/checker-expressions.do"
        return;
    }
#line 751 "/src/checker-expressions.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& owner = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 753 "/src/checker-expressions.do"
            auto parameterIndex = 0;
#line 754 "/src/checker-expressions.do"
            const auto& _iterable_63 = owner->fields;
            for (const auto& field : *_iterable_63) {
#line 755 "/src/checker-expressions.do"
                if (field->static_ || field->const_) {
#line 755 "/src/checker-expressions.do"
                    continue;
                }
#line 756 "/src/checker-expressions.do"
                const auto& _iterable_65 = field->names;
                for (const auto& name : *_iterable_65) {
#line 757 "/src/checker-expressions.do"
                    if ((parameterIndex < static_cast<int32_t>((expression->args)->size())) && field->private_) {
#line 758 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, ((((std::string("Field '") + name) + std::string("' is private to module '")) + inner->symbol->module) + std::string("'")), std::visit([](auto&& _obj) { return _obj->span; }, doof::array_at(expression->args, parameterIndex, "src/checker-expressions", 758)));
                    }
#line 760 "/src/checker-expressions.do"
                    (parameterIndex += 1);
                }
            }
    }
    else {
    }
    }
}
#line 768 "/src/checker-expressions.do"
bool isNamedStaticReceiver(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 769 "/src/checker-expressions.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 771 "/src/checker-expressions.do"
            if (doof::is_null(identifier->resolvedBinding)) {
#line 771 "/src/checker-expressions.do"
                return false;
            }
#line 772 "/src/checker-expressions.do"
            const auto binding = doof::unwrap_optional(identifier->resolvedBinding);
#line 773 "/src/checker-expressions.do"
            if (((binding->kind == std::string("class")) || (binding->kind == std::string("struct"))) || (binding->kind == std::string("interface"))) {
#line 773 "/src/checker-expressions.do"
                return true;
            }
#line 774 "/src/checker-expressions.do"
            if ((binding->kind == std::string("import")) && (!doof::is_null(binding->symbol))) {
#line 775 "/src/checker-expressions.do"
                const auto kind = binding->symbol->kind;
#line 776 "/src/checker-expressions.do"
                return (((kind == std::string("class")) || (kind == std::string("struct"))) || (kind == std::string("interface")));
            }
    }
    else {
    }
    }
#line 781 "/src/checker-expressions.do"
    return false;
}
#line 784 "/src/checker-expressions.do"
bool declaredInstanceMember(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& receiver, const std::string& property) {
#line 785 "/src/checker-expressions.do"
    std::shared_ptr<::app_src_semantic_::Symbol> symbol = nullptr;
#line 786 "/src/checker-expressions.do"
    {
        auto _case_subject = receiver;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 787 "/src/checker-expressions.do"
            (symbol = class_->symbol);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 788 "/src/checker-expressions.do"
            (symbol = interface_->symbol);
    }
    else {
#line 789 "/src/checker-expressions.do"
            return false;
    }
    }
#line 791 "/src/checker-expressions.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
#line 792 "/src/checker-expressions.do"
    if (doof::is_null(declaration)) {
#line 792 "/src/checker-expressions.do"
        return false;
    }
#line 793 "/src/checker-expressions.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 795 "/src/checker-expressions.do"
            const auto& _iterable_67 = class_->fields;
            for (const auto& field : *_iterable_67) {
#line 795 "/src/checker-expressions.do"
                const auto& _iterable_69 = field->names;
                for (const auto& name : *_iterable_69) {
#line 795 "/src/checker-expressions.do"
                    if ((name == property) && !field->static_) {
#line 795 "/src/checker-expressions.do"
                        return true;
                    }
                }
            }
#line 796 "/src/checker-expressions.do"
            const auto& _iterable_71 = class_->methods;
            for (const auto& method : *_iterable_71) {
#line 796 "/src/checker-expressions.do"
                if ((method->name == property) && !method->static_) {
#line 796 "/src/checker-expressions.do"
                    return true;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 799 "/src/checker-expressions.do"
            const auto& _iterable_73 = interface_->fields;
            for (const auto& field : *_iterable_73) {
#line 799 "/src/checker-expressions.do"
                if (field->name == property) {
#line 799 "/src/checker-expressions.do"
                    return true;
                }
            }
#line 800 "/src/checker-expressions.do"
            const auto& _iterable_75 = interface_->methods;
            for (const auto& method : *_iterable_75) {
#line 800 "/src/checker-expressions.do"
                if ((method->name == property) && !method->static_) {
#line 800 "/src/checker-expressions.do"
                    return true;
                }
            }
    }
    else {
    }
    }
#line 804 "/src/checker-expressions.do"
    return false;
}
#line 807 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkDotShorthand(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::DotShorthand>& expression, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 808 "/src/checker-expressions.do"
    if (doof::is_null(expected)) {
#line 809 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, ((std::string("Cannot resolve shorthand .") + expression->name) + std::string(" without an expected class or enum type")), expression->span);
#line 810 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
    }
#line 812 "/src/checker-expressions.do"
    {
        auto _case_subject = doof::unwrap_optional(expected);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 814 "/src/checker-expressions.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, enum_->symbol);
#line 815 "/src/checker-expressions.do"
            auto found = false;
#line 816 "/src/checker-expressions.do"
            if (!doof::is_null(declaration)) {
#line 817 "/src/checker-expressions.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                        const auto& enumDeclaration = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 819 "/src/checker-expressions.do"
                        const auto& _iterable_77 = enumDeclaration->variants;
                        for (const auto& variant : *_iterable_77) {
#line 819 "/src/checker-expressions.do"
                            if (variant->name == expression->name) {
#line 819 "/src/checker-expressions.do"
                                (found = true);
                            }
                        }
                }
                else {
                }
                }
            }
#line 824 "/src/checker-expressions.do"
            if (!found) {
#line 825 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((((std::string("Enum \"") + enum_->name) + std::string("\" has no variant \"")) + expression->name) + std::string("\"")), expression->span);
#line 826 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
            }
#line 828 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerName = enum_->name);
#line 829 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerKind = std::string("enum"));
#line 830 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerModule = enum_->symbol->module);
#line 831 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerNative = enum_->symbol->native_);
#line 832 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerCppName = enum_->symbol->nativeCppName);
#line 833 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 836 "/src/checker-expressions.do"
            const auto diagnosticCount = static_cast<int32_t>((state->diagnostics)->size());
#line 837 "/src/checker-expressions.do"
            const auto value = ::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), expression->name, expression->span, true);
#line 838 "/src/checker-expressions.do"
            if (doof::is_null(::app_src_checker_generics_::staticMemberOwner(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), expression->name, state->result))) {
#line 839 "/src/checker-expressions.do"
                if (static_cast<int32_t>((state->diagnostics)->size()) == diagnosticCount) {
#line 840 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, ((((std::string("Type \"") + class_->name) + std::string("\" has no static member \"")) + expression->name) + std::string("\"")), expression->span);
                }
#line 842 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
            }
#line 844 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerName = class_->name);
#line 845 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerKind = std::string("class"));
#line 846 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerModule = class_->symbol->module);
#line 847 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerNative = class_->symbol->native_);
#line 848 "/src/checker-expressions.do"
            (expression->resolvedShorthandOwnerCppName = class_->symbol->nativeCppName);
#line 849 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), value);
    }
    else {
    }
    }
#line 853 "/src/checker-expressions.do"
    ::app_src_checker_common_::typeError(state, ((((std::string("Cannot resolve shorthand .") + expression->name) + std::string(" for expected type \"")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expected))) + std::string("\"")), expression->span);
#line 854 "/src/checker-expressions.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
}
#line 857 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkIdentifier(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::Identifier>& identifier, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 858 "/src/checker-expressions.do"
    std::shared_ptr<::app_src_semantic_::Binding> binding = ::app_src_checker_symbols_::lookup(scope, identifier->name);
#line 859 "/src/checker-expressions.do"
    if (doof::is_null(binding) && ::app_src_checker_symbols_::hasTypeParam(scope, identifier->name)) {
#line 860 "/src/checker-expressions.do"
        (binding = std::make_shared<::app_src_semantic_::Binding>(identifier->name, std::string("type-parameter"), ::app_src_checker_types_::typeParameter(identifier->name, ::app_src_checker_symbols_::typeParamConstraintName(scope, identifier->name), ::app_src_checker_symbols_::typeParamConstraint(scope, identifier->name)), false, ::app_src_checker_validation_::checkerSemanticSpan(identifier->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")));
    }
#line 865 "/src/checker-expressions.do"
    if (doof::is_null(binding)) {
#line 865 "/src/checker-expressions.do"
        (binding = implicitMethod(state, scope, identifier->name, identifier->span));
    }
#line 866 "/src/checker-expressions.do"
    if (doof::is_null(binding) && ::app_src_checker_symbols_::isBuiltinCallable(identifier->name)) {
#line 867 "/src/checker-expressions.do"
        (binding = std::make_shared<::app_src_semantic_::Binding>(identifier->name, std::string("builtin"), ::app_src_checker_symbols_::builtinCallable(identifier->name), false, ::app_src_checker_validation_::checkerSemanticSpan(identifier->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")));
    }
#line 869 "/src/checker-expressions.do"
    if (doof::is_null(binding)) {
#line 870 "/src/checker-expressions.do"
        const auto message = ::app_src_checker_symbols_::valueUseDiagnostic(doof::unwrap_optional(state->info), identifier->name);
#line 871 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, ((message == std::string("")) ? ((std::string("Unknown identifier '") + identifier->name) + std::string("'")) : message), identifier->span);
#line 872 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(identifier), ::app_src_checker_types_::unknownType());
    }
#line 874 "/src/checker-expressions.do"
    (identifier->resolvedBinding = binding);
#line 875 "/src/checker-expressions.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(identifier), binding->type_);
}
#line 878 "/src/checker-expressions.do"
bool legacyNumericParseType(const std::shared_ptr<::app_src_ast_::Identifier>& identifier) {
#line 879 "/src/checker-expressions.do"
    if (doof::is_null(identifier->resolvedBinding) || (identifier->resolvedBinding->kind != std::string("builtin"))) {
#line 879 "/src/checker-expressions.do"
        return false;
    }
#line 880 "/src/checker-expressions.do"
    const auto name = identifier->name;
#line 881 "/src/checker-expressions.do"
    return (((((name == std::string("byte")) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double")));
}
#line 884 "/src/checker-expressions.do"
std::shared_ptr<::app_src_semantic_::Binding> implicitMethod(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name, ::app_src_ast_::SourceSpan span) {
#line 885 "/src/checker-expressions.do"
    {
        auto _case_subject = ::app_src_checker_symbols_::currentThisType(scope);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& owner = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 887 "/src/checker-expressions.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, owner->symbol);
#line 888 "/src/checker-expressions.do"
            if (doof::is_null(declaration)) {
#line 888 "/src/checker-expressions.do"
                return nullptr;
            }
#line 889 "/src/checker-expressions.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 891 "/src/checker-expressions.do"
                    const auto& _iterable_79 = class_->methods;
                    for (const auto& method : *_iterable_79) {
#line 892 "/src/checker-expressions.do"
                        if (method->name == name) {
#line 893 "/src/checker-expressions.do"
                            const auto methodType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_80 = method->resolvedType; if (doof::is_null(_coalesce_80)) return ::app_src_checker_statements_::checkFunction(state, method, scope, owner); return doof::unwrap_optional(_coalesce_80); }();
#line 894 "/src/checker-expressions.do"
                            return std::make_shared<::app_src_semantic_::Binding>(name, std::string("method"), methodType, false, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, owner->symbol, std::string(""), std::string(""), std::string(""));
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
#line 906 "/src/checker-expressions.do"
    return nullptr;
}
#line 909 "/src/checker-expressions.do"
void addClassMethods(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& owner) {
#line 910 "/src/checker-expressions.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, owner->symbol);
#line 911 "/src/checker-expressions.do"
    if (doof::is_null(declaration)) {
#line 911 "/src/checker-expressions.do"
        return;
    }
#line 912 "/src/checker-expressions.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 914 "/src/checker-expressions.do"
            const auto& _iterable_82 = class_->methods;
            for (const auto& method : *_iterable_82) {
#line 915 "/src/checker-expressions.do"
                std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> methodType = ::app_src_checker_types_::unknownType();
#line 916 "/src/checker-expressions.do"
                if (!doof::is_null(method->resolvedType)) {
#line 917 "/src/checker-expressions.do"
                    (methodType = doof::unwrap_optional(method->resolvedType));
                } else {
#line 923 "/src/checker-expressions.do"
                    std::shared_ptr<std::vector<std::string>> methodTypeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 924 "/src/checker-expressions.do"
                    const auto& _iterable_84 = class_->typeParams;
                    for (const auto& typeParam : *_iterable_84) {
#line 924 "/src/checker-expressions.do"
                        methodTypeParams->push_back(typeParam);
                    }
#line 925 "/src/checker-expressions.do"
                    const auto& _iterable_86 = method->typeParams;
                    for (const auto& typeParam : *_iterable_86) {
#line 925 "/src/checker-expressions.do"
                        methodTypeParams->push_back(typeParam);
                    }
#line 926 "/src/checker-expressions.do"
                    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> parameters = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 927 "/src/checker-expressions.do"
                    const auto& _iterable_88 = method->params;
                    for (const auto& parameter : *_iterable_88) {
#line 928 "/src/checker-expressions.do"
                        const auto parameterType = (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(parameter->type_), doof::unwrap_optional(state->info), state->result, methodTypeParams));
#line 929 "/src/checker-expressions.do"
                        parameters->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, parameterType, (!doof::is_null(parameter->defaultValue))));
                    }
#line 931 "/src/checker-expressions.do"
                    const auto returnType = (doof::is_null(method->returnType) ? ::app_src_checker_types_::noneType() : ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(method->returnType), doof::unwrap_optional(state->info), state->result, methodTypeParams));
#line 932 "/src/checker-expressions.do"
                    (methodType = ::app_src_checker_types_::functionType(parameters, returnType, method->typeParams));
                }
#line 934 "/src/checker-expressions.do"
                ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(method->name, std::string("method"), methodType, false, ::app_src_checker_validation_::checkerSemanticSpan(method->span), state->info->path, owner->symbol, std::string(""), std::string(""), std::string("")));
            }
    }
    else {
    }
    }
}
#line 944 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkBinary(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::BinaryExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 945 "/src/checker-expressions.do"
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> left = ::app_src_checker_types_::unknownType();
#line 946 "/src/checker-expressions.do"
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> right = ::app_src_checker_types_::unknownType();
#line 947 "/src/checker-expressions.do"
    {
        auto _case_subject = expression->left;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
#line 949 "/src/checker-expressions.do"
            (right = checkExpression(state, expression->right, scope, std::monostate{}));
#line 950 "/src/checker-expressions.do"
            (left = checkExpression(state, expression->left, scope, ::app_src_checker_symbols_::optionalResolvedType(right)));
    }
    else {
#line 953 "/src/checker-expressions.do"
            {
                auto _case_subject = expression->right;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
#line 955 "/src/checker-expressions.do"
                    (left = checkExpression(state, expression->left, scope, std::monostate{}));
#line 956 "/src/checker-expressions.do"
                    const auto shorthandExpected = ((expression->operator_ == std::string("\?\?")) ? nonNoneType(state, left) : left);
#line 957 "/src/checker-expressions.do"
                    (right = checkExpression(state, expression->right, scope, ::app_src_checker_symbols_::optionalResolvedType(shorthandExpected)));
            }
            else {
#line 960 "/src/checker-expressions.do"
                    (left = checkExpression(state, expression->left, scope, std::monostate{}));
#line 961 "/src/checker-expressions.do"
                    (right = checkExpression(state, expression->right, scope, std::monostate{}));
            }
            }
    }
    }
#line 966 "/src/checker-expressions.do"
    const auto operator_ = expression->operator_;
#line 967 "/src/checker-expressions.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, left) == std::string("never")) {
#line 967 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::neverType());
    }
#line 968 "/src/checker-expressions.do"
    if ((operator_ == std::string("&&")) || (operator_ == std::string("||"))) {
#line 969 "/src/checker-expressions.do"
        ::app_src_checker_common_::requireBool(state, left, std::visit([](auto&& _obj) { return _obj->span; }, expression->left));
#line 969 "/src/checker-expressions.do"
        ::app_src_checker_common_::requireBool(state, right, std::visit([](auto&& _obj) { return _obj->span; }, expression->right));
#line 970 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::primitive(std::string("bool")));
    }
#line 972 "/src/checker-expressions.do"
    if (operator_ == std::string("\?\?")) {
#line 973 "/src/checker-expressions.do"
        if (!isFallibleType(left)) {
#line 973 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (std::string("Operator '\?\?' requires a nullable or Result left operand, got ") + ::app_src_checker_types_::typeName(left)), std::visit([](auto&& _obj) { return _obj->span; }, expression->left));
        }
#line 974 "/src/checker-expressions.do"
        const auto expectedFallback = fallibleValueType(left);
#line 975 "/src/checker-expressions.do"
        if (((!doof::is_null(expectedFallback)) && !::app_src_checker_types_::isAssignable(right, doof::unwrap_optional(expectedFallback))) && !::app_src_checker_types_::isAssignable(right, left)) {
#line 976 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (((std::string("Cannot use ") + ::app_src_checker_types_::typeName(right)) + std::string(" as fallback for ")) + ::app_src_checker_types_::typeName(left)), std::visit([](auto&& _obj) { return _obj->span; }, expression->right));
        }
#line 978 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), coalescedType(state, left, right));
    }
#line 980 "/src/checker-expressions.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, right) == std::string("never")) {
#line 980 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::neverType());
    }
#line 981 "/src/checker-expressions.do"
    if ((operator_ == std::string("..<")) || (operator_ == std::string(".."))) {
#line 982 "/src/checker-expressions.do"
        validateRangeOperand(state, operator_, std::string("left"), left, std::visit([](auto&& _obj) { return _obj->span; }, expression->left));
#line 983 "/src/checker-expressions.do"
        validateRangeOperand(state, operator_, std::string("right"), right, std::visit([](auto&& _obj) { return _obj->span; }, expression->right));
#line 984 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::rangeType());
    }
#line 986 "/src/checker-expressions.do"
    if ((operator_ == std::string("==")) || (operator_ == std::string("!="))) {
#line 987 "/src/checker-expressions.do"
        validateNoneComparison(state, operator_, left, right, expression->span);
#line 988 "/src/checker-expressions.do"
        if (((std::visit([](auto&& _obj) { return _obj->kind; }, left) != std::string("none")) && (std::visit([](auto&& _obj) { return _obj->kind; }, right) != std::string("none"))) && !typesOverlap(left, right)) {
#line 989 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' is not defined for ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), expression->span);
        }
#line 991 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::primitive(std::string("bool")));
    }
#line 993 "/src/checker-expressions.do"
    if ((((operator_ == std::string("<")) || (operator_ == std::string("<="))) || (operator_ == std::string(">"))) || (operator_ == std::string(">="))) {
#line 994 "/src/checker-expressions.do"
        if (!orderedTypes(left, right)) {
#line 994 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' is not defined for ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), expression->span);
        }
#line 995 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::primitive(std::string("bool")));
    }
#line 997 "/src/checker-expressions.do"
    if (((operator_ == std::string("+")) && (::app_src_checker_types_::typeName(left) == std::string("string"))) && (((::app_src_checker_types_::typeName(right) == std::string("string")) || (::app_src_checker_types_::typeName(right) == std::string("char"))) || (::app_src_checker_types_::typeName(right) == std::string("unknown")))) {
#line 997 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::primitive(std::string("string")));
    }
#line 998 "/src/checker-expressions.do"
    if (((operator_ == std::string("+")) && (::app_src_checker_types_::typeName(right) == std::string("string"))) && ((::app_src_checker_types_::typeName(left) == std::string("char")) || (::app_src_checker_types_::typeName(left) == std::string("unknown")))) {
#line 998 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::primitive(std::string("string")));
    }
#line 999 "/src/checker-expressions.do"
    if (::app_src_checker_types_::isNumeric(left) && ::app_src_checker_types_::isNumeric(right)) {
#line 1000 "/src/checker-expressions.do"
        if ((((operator_ == std::string("\\")) || (operator_ == std::string("%"))) || bitwiseOperator(operator_)) && (!isInteger(left) || !isInteger(right))) {
#line 1001 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' requires integer operands, got ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), expression->span);
        }
#line 1003 "/src/checker-expressions.do"
        if (((operator_ == std::string("/")) && isInteger(left)) && isInteger(right)) {
#line 1004 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, std::string("Operator '/' requires at least one floating-point operand"), expression->span);
        }
#line 1006 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::numericResult(left, right));
    }
#line 1008 "/src/checker-expressions.do"
    ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' is not defined for ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), expression->span);
#line 1009 "/src/checker-expressions.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
}
#line 1012 "/src/checker-expressions.do"
void validateNoneComparison(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& operator_, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& left, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& right, ::app_src_ast_::SourceSpan span) {
#line 1013 "/src/checker-expressions.do"
    if ((std::visit([](auto&& _obj) { return _obj->kind; }, left) == std::string("none")) && !admitsNone(right)) {
#line 1014 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' is not defined for ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), span);
    } else if ((std::visit([](auto&& _obj) { return _obj->kind; }, right) == std::string("none")) && !admitsNone(left)) {
#line 1016 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' is not defined for ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), span);
    }
}
#line 1020 "/src/checker-expressions.do"
bool admitsNone(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 1021 "/src/checker-expressions.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 1022 "/src/checker-expressions.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 1023 "/src/checker-expressions.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 1024 "/src/checker-expressions.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1026 "/src/checker-expressions.do"
            const auto& _iterable_90 = union_->types;
            for (const auto& member : *_iterable_90) {
#line 1026 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 1026 "/src/checker-expressions.do"
                    return true;
                }
            }
    }
    else {
    }
    }
#line 1030 "/src/checker-expressions.do"
    return false;
}
#line 1033 "/src/checker-expressions.do"
void validateRangeOperand(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& operator_, const std::string& side, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& operand, ::app_src_ast_::SourceSpan span) {
#line 1034 "/src/checker-expressions.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, operand) == std::string("unknown")) {
#line 1034 "/src/checker-expressions.do"
        return;
    }
#line 1035 "/src/checker-expressions.do"
    {
        auto _case_subject = operand;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive_ = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 1037 "/src/checker-expressions.do"
            if (((primitive_->name != std::string("byte")) && (primitive_->name != std::string("int"))) && (primitive_->name != std::string("long"))) {
#line 1038 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((((((std::string("Range operator \"") + operator_) + std::string("\" requires integer bounds, got ")) + side) + std::string(" bound of type \"")) + ::app_src_checker_types_::typeName(operand)) + std::string("\"")), span);
            } else if (primitive_->name == std::string("long")) {
#line 1040 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((((std::string("Range operator \"") + operator_) + std::string("\" currently requires int-compatible bounds, got ")) + side) + std::string(" bound of type \"long\"")), span);
            }
    }
    else {
#line 1043 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, ((((((std::string("Range operator \"") + operator_) + std::string("\" requires integer bounds, got ")) + side) + std::string(" bound of type \"")) + ::app_src_checker_types_::typeName(operand)) + std::string("\"")), span);
    }
    }
}
#line 1047 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> coalescedType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& left, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& right) {
#line 1048 "/src/checker-expressions.do"
    {
        auto _case_subject = left;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 1049 "/src/checker-expressions.do"
            return ::app_src_checker_types_::joinTypes(result->valueType, right);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1051 "/src/checker-expressions.do"
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> nonNull = std::monostate{};
#line 1052 "/src/checker-expressions.do"
            const auto& _iterable_92 = union_->types;
            for (const auto& member : *_iterable_92) {
#line 1053 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 1054 "/src/checker-expressions.do"
                    (nonNull = doof::optional_value((doof::is_null(nonNull) ? member : ::app_src_checker_types_::joinTypes(doof::unwrap_optional(nonNull), member))));
                }
            }
#line 1057 "/src/checker-expressions.do"
            if (doof::is_null(nonNull)) {
#line 1057 "/src/checker-expressions.do"
                return right;
            }
#line 1058 "/src/checker-expressions.do"
            return ::app_src_checker_types_::joinTypes(doof::unwrap_optional(nonNull), right);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 1060 "/src/checker-expressions.do"
            return right;
    }
    else {
#line 1061 "/src/checker-expressions.do"
            return left;
    }
    }
    doof::unreachable();
#line 1063 "/src/checker-expressions.do"
    return ::app_src_checker_types_::unknownType();
}
#line 1066 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkUnary(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::UnaryExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 1067 "/src/checker-expressions.do"
    const auto value = checkExpression(state, expression->operand, scope, std::monostate{});
#line 1071 "/src/checker-expressions.do"
    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, expression->operand) = ::app_src_checker_symbols_::optionalResolvedType(value));
#line 1072 "/src/checker-expressions.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, value) == std::string("never")) {
#line 1072 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::neverType());
    }
#line 1073 "/src/checker-expressions.do"
    if ((expression->operator_ == std::string("try!")) || (expression->operator_ == std::string("try\?"))) {
#line 1074 "/src/checker-expressions.do"
        {
            auto _case_subject = value;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 1076 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, result->valueType) == std::string("none")) {
#line 1077 "/src/checker-expressions.do"
                    if (expression->operator_ == std::string("try\?")) {
#line 1077 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, std::string("try\? requires a Result with a success value"), expression->span);
                    }
#line 1078 "/src/checker-expressions.do"
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), result->valueType);
                }
#line 1080 "/src/checker-expressions.do"
                if (expression->operator_ == std::string("try\?")) {
#line 1080 "/src/checker-expressions.do"
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{result->valueType, ::app_src_checker_types_::noneType()})));
                }
#line 1081 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), result->valueType);
        }
        else {
#line 1083 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, (expression->operator_ + std::string(" requires a Result expression")), expression->span);
        }
        }
#line 1085 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
    }
#line 1087 "/src/checker-expressions.do"
    if (!expression->prefix && (expression->operator_ == std::string("!"))) {
#line 1088 "/src/checker-expressions.do"
        {
            auto _case_subject = value;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 1089 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), result->valueType);
        }
        else {
        }
        }
#line 1092 "/src/checker-expressions.do"
        if (!isNullableType(value)) {
#line 1093 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (std::string("Postfix '!' requires a nullable or Result operand, got ") + ::app_src_checker_types_::typeName(value)), expression->span);
#line 1094 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
        }
#line 1096 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), nonNoneType(state, value));
    }
#line 1098 "/src/checker-expressions.do"
    if (expression->operator_ == std::string("!")) {
#line 1098 "/src/checker-expressions.do"
        ::app_src_checker_common_::requireBool(state, value, expression->span);
#line 1098 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::primitive(std::string("bool")));
    }
#line 1099 "/src/checker-expressions.do"
    if (((expression->operator_ == std::string("+")) || (expression->operator_ == std::string("-"))) || (expression->operator_ == std::string("~"))) {
#line 1100 "/src/checker-expressions.do"
        if (!::app_src_checker_types_::isNumeric(value)) {
#line 1100 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Unary '") + expression->operator_) + std::string("' requires a numeric operand")), expression->span);
        } else if ((expression->operator_ == std::string("~")) && !isInteger(value)) {
#line 1101 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, std::string("Unary '~' requires an integer operand"), expression->span);
        }
#line 1102 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), value);
    }
#line 1104 "/src/checker-expressions.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), value);
}
#line 1108 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkAs(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::AsExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 1109 "/src/checker-expressions.do"
    const auto sourceType = checkExpression(state, expression->expression, scope, std::monostate{});
#line 1110 "/src/checker-expressions.do"
    const auto targetType = ::app_src_checker_resolution_::resolveType(state, expression->targetType, doof::unwrap_optional(state->info), scope);
#line 1111 "/src/checker-expressions.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, sourceType) == std::string("never")) {
#line 1111 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::neverType());
    }
#line 1112 "/src/checker-expressions.do"
    {
        auto _case_subject = sourceType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 1114 "/src/checker-expressions.do"
            if (!isValidAsNarrow(state, result->valueType, targetType)) {
#line 1115 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot narrow \"") + ::app_src_checker_types_::typeName(sourceType)) + std::string("\" to \"")) + ::app_src_checker_types_::typeName(targetType)) + std::string("\" with \"as\"")), expression->span);
#line 1116 "/src/checker-expressions.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
            }
#line 1118 "/src/checker-expressions.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::resultType(targetType, ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{result->errorType, ::app_src_checker_types_::primitive(std::string("string"))}))));
    }
    else {
    }
    }
#line 1122 "/src/checker-expressions.do"
    if (!isValidAsNarrow(state, sourceType, targetType)) {
#line 1123 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, ((((std::string("Cannot narrow \"") + ::app_src_checker_types_::typeName(sourceType)) + std::string("\" to \"")) + ::app_src_checker_types_::typeName(targetType)) + std::string("\" with \"as\"")), expression->span);
#line 1124 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
    }
#line 1126 "/src/checker-expressions.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::resultType(targetType, ::app_src_checker_types_::primitive(std::string("string"))));
}
#line 1129 "/src/checker-expressions.do"
bool isValidAsNarrow(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& source, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& target) {
#line 1130 "/src/checker-expressions.do"
    if (::app_src_checker_types_::sameType(source, target)) {
#line 1130 "/src/checker-expressions.do"
        return true;
    }
#line 1131 "/src/checker-expressions.do"
    if (::app_src_checker_types_::isNumeric(source) && ::app_src_checker_types_::isNumeric(target)) {
#line 1131 "/src/checker-expressions.do"
        return true;
    }
#line 1132 "/src/checker-expressions.do"
    {
        auto _case_subject = source;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 1133 "/src/checker-expressions.do"
            return isJsonAsTarget(state, target);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1135 "/src/checker-expressions.do"
            const auto& _iterable_94 = union_->types;
            for (const auto& member : *_iterable_94) {
#line 1135 "/src/checker-expressions.do"
                if (isValidAsNarrow(state, member, target)) {
#line 1135 "/src/checker-expressions.do"
                    return true;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 1138 "/src/checker-expressions.do"
            {
                auto _case_subject = target;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 1139 "/src/checker-expressions.do"
                    return true;
            }
            else {
            }
            }
    }
    else {
    }
    }
#line 1145 "/src/checker-expressions.do"
    return false;
}
#line 1148 "/src/checker-expressions.do"
bool isJsonAsTarget(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& target) {
#line 1149 "/src/checker-expressions.do"
    {
        auto _case_subject = target;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitiveType = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 1151 "/src/checker-expressions.do"
            return (((primitiveType->name == std::string("bool")) || (primitiveType->name == std::string("string"))) || ::app_src_checker_types_::isNumeric(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(primitiveType)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 1153 "/src/checker-expressions.do"
            return ::app_src_checker_types_::isJsonValueType(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 1154 "/src/checker-expressions.do"
            return (::app_src_checker_types_::sameType(map->keyType, ::app_src_checker_types_::primitive(std::string("string"))) && ::app_src_checker_types_::isJsonValueType(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 1155 "/src/checker-expressions.do"
            return true;
    }
    else {
#line 1156 "/src/checker-expressions.do"
            return false;
    }
    }
    doof::unreachable();
#line 1158 "/src/checker-expressions.do"
    return false;
}
#line 1161 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> nonNoneType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& value) {
#line 1162 "/src/checker-expressions.do"
    {
        auto _case_subject = value;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1164 "/src/checker-expressions.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 1165 "/src/checker-expressions.do"
            const auto& _iterable_96 = union_->types;
            for (const auto& member : *_iterable_96) {
#line 1165 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 1165 "/src/checker-expressions.do"
                    members->push_back(member);
                }
            }
#line 1166 "/src/checker-expressions.do"
            if (static_cast<int32_t>((members)->size()) == 1) {
#line 1166 "/src/checker-expressions.do"
                return doof::array_at(members, 0, "src/checker-expressions", 1166);
            }
#line 1167 "/src/checker-expressions.do"
            if (static_cast<int32_t>((members)->size()) > 1) {
#line 1167 "/src/checker-expressions.do"
                return ::app_src_checker_types_::unionType(members);
            }
#line 1168 "/src/checker-expressions.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 1170 "/src/checker-expressions.do"
            return ::app_src_checker_types_::unknownType();
    }
    else {
#line 1171 "/src/checker-expressions.do"
            return value;
    }
    }
    doof::unreachable();
#line 1173 "/src/checker-expressions.do"
    return ::app_src_checker_types_::unknownType();
}
#line 1176 "/src/checker-expressions.do"
bool hasNoneMember(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& value) {
#line 1177 "/src/checker-expressions.do"
    const auto& _iterable_98 = value->types;
    for (const auto& member : *_iterable_98) {
#line 1177 "/src/checker-expressions.do"
        if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 1177 "/src/checker-expressions.do"
            return true;
        }
    }
#line 1178 "/src/checker-expressions.do"
    return false;
}
#line 1181 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkAssignment(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::AssignmentExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 1182 "/src/checker-expressions.do"
    const auto targetType = checkExpression(state, expression->target, scope, std::monostate{});
#line 1185 "/src/checker-expressions.do"
    ::app_src_checker_common_::finish(state, expression->target, targetType);
#line 1186 "/src/checker-expressions.do"
    {
        auto _case_subject = expression->target;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 1188 "/src/checker-expressions.do"
            const auto binding = ::app_src_checker_symbols_::lookup(scope, identifier->name);
#line 1189 "/src/checker-expressions.do"
            if (!doof::is_null(binding)) {
#line 1190 "/src/checker-expressions.do"
                (identifier->resolvedBinding = binding);
#line 1191 "/src/checker-expressions.do"
                (identifier->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
            }
    }
    else {
    }
    }
#line 1196 "/src/checker-expressions.do"
    const auto value = checkExpression(state, expression->value, scope, ::app_src_checker_symbols_::optionalResolvedType(targetType));
#line 1197 "/src/checker-expressions.do"
    validateAssignmentOperator(state, expression->operator_, targetType, value, expression->span);
#line 1198 "/src/checker-expressions.do"
    {
        auto _case_subject = expression->target;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 1200 "/src/checker-expressions.do"
            const auto target = ::app_src_checker_symbols_::lookup(scope, identifier->name);
#line 1201 "/src/checker-expressions.do"
            if (doof::is_null(target)) {
#line 1201 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Unknown assignment target '") + identifier->name) + std::string("'")), identifier->span);
            } else {
#line 1203 "/src/checker-expressions.do"
                ::app_src_checker_common_::validateAssignmentBinding(state, doof::unwrap_optional(target), identifier->span);
#line 1204 "/src/checker-expressions.do"
                if ((expression->operator_ == std::string("=")) && !::app_src_checker_types_::isAssignable(value, target->type_)) {
#line 1204 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(value)) + std::string(" to ")) + ::app_src_checker_types_::typeName(target->type_)), expression->span);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 1208 "/src/checker-expressions.do"
            const auto objectType = checkExpression(state, index->object, scope, std::monostate{});
#line 1209 "/src/checker-expressions.do"
            {
                auto _case_subject = objectType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 1211 "/src/checker-expressions.do"
                    checkExpression(state, index->index, scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::primitive(std::string("int"))));
#line 1212 "/src/checker-expressions.do"
                    if (array->readonly_) {
#line 1212 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, std::string("Cannot assign through readonly array"), expression->span);
                    }
#line 1213 "/src/checker-expressions.do"
                    if ((expression->operator_ == std::string("=")) && !::app_src_checker_types_::isAssignable(value, array->elementType)) {
#line 1213 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(value)) + std::string(" to ")) + ::app_src_checker_types_::typeName(array->elementType)), expression->span);
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                    const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 1216 "/src/checker-expressions.do"
                    const auto key = checkExpression(state, index->index, scope, ::app_src_checker_symbols_::optionalResolvedType(map->keyType));
#line 1217 "/src/checker-expressions.do"
                    if (!::app_src_checker_types_::isAssignable(key, map->keyType)) {
#line 1217 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, (((std::string("Cannot use ") + ::app_src_checker_types_::typeName(key)) + std::string(" as map key ")) + ::app_src_checker_types_::typeName(map->keyType)), std::visit([](auto&& _obj) { return _obj->span; }, index->index));
                    }
#line 1218 "/src/checker-expressions.do"
                    if (map->readonly_) {
#line 1218 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, std::string("Cannot assign through readonly map"), expression->span);
                    }
#line 1219 "/src/checker-expressions.do"
                    if ((expression->operator_ == std::string("=")) && !::app_src_checker_types_::isAssignable(value, map->valueType)) {
#line 1219 "/src/checker-expressions.do"
                        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(value)) + std::string(" to ")) + ::app_src_checker_types_::typeName(map->valueType)), expression->span);
                    }
            }
            else {
#line 1221 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, std::string("Index assignment requires an array or map"), expression->span);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 1225 "/src/checker-expressions.do"
            const auto objectType = checkExpression(state, member->object, scope, std::monostate{});
#line 1226 "/src/checker-expressions.do"
            const auto targetType = ::app_src_checker_resolution_::memberType(state, objectType, member->property, member->span, true);
#line 1227 "/src/checker-expressions.do"
            const auto fieldBinding = ::app_src_checker_resolution_::fieldAssignmentBinding(state, objectType, member->property, targetType);
#line 1228 "/src/checker-expressions.do"
            if (!doof::is_null(fieldBinding)) {
#line 1228 "/src/checker-expressions.do"
                ::app_src_checker_common_::validateAssignmentBinding(state, doof::unwrap_optional(fieldBinding), member->span);
            }
#line 1229 "/src/checker-expressions.do"
            if ((expression->operator_ == std::string("=")) && !::app_src_checker_types_::isAssignable(value, targetType)) {
#line 1229 "/src/checker-expressions.do"
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(value)) + std::string(" to ")) + ::app_src_checker_types_::typeName(targetType)), expression->span);
            }
    }
    else {
#line 1231 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, std::string("Assignment target must be a binding"), std::visit([](auto&& _obj) { return _obj->span; }, expression->target));
    }
    }
#line 1233 "/src/checker-expressions.do"
    if ((std::visit([](auto&& _obj) { return _obj->kind; }, targetType) == std::string("never")) || (std::visit([](auto&& _obj) { return _obj->kind; }, value) == std::string("never"))) {
#line 1233 "/src/checker-expressions.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::neverType());
    }
#line 1234 "/src/checker-expressions.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), value);
}
#line 1237 "/src/checker-expressions.do"
void validateAssignmentOperator(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& operator_, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& target, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& value, ::app_src_ast_::SourceSpan span) {
#line 1238 "/src/checker-expressions.do"
    if (operator_ == std::string("=")) {
#line 1238 "/src/checker-expressions.do"
        return;
    }
#line 1239 "/src/checker-expressions.do"
    if (operator_ == std::string("\?\?=")) {
#line 1240 "/src/checker-expressions.do"
        if (!isFallibleType(target)) {
#line 1240 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (std::string("Operator '\?\?=' requires a nullable or Result assignment target, got ") + ::app_src_checker_types_::typeName(target)), span);
#line 1240 "/src/checker-expressions.do"
            return;
        }
#line 1241 "/src/checker-expressions.do"
        {
            auto _case_subject = target;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 1243 "/src/checker-expressions.do"
                if (!::app_src_checker_types_::isAssignable(value, target) && !::app_src_checker_types_::isAssignable(value, result->valueType)) {
#line 1244 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(value)) + std::string(" through \?\?= to ")) + ::app_src_checker_types_::typeName(target)), span);
                }
        }
        else {
#line 1247 "/src/checker-expressions.do"
                if (!::app_src_checker_types_::isAssignable(value, target)) {
#line 1247 "/src/checker-expressions.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(value)) + std::string(" through \?\?= to ")) + ::app_src_checker_types_::typeName(target)), span);
                }
        }
        }
#line 1249 "/src/checker-expressions.do"
        return;
    }
#line 1251 "/src/checker-expressions.do"
    const auto base = doof::string_substring(operator_, 0, (static_cast<int32_t>(operator_.size()) - 1));
#line 1252 "/src/checker-expressions.do"
    const auto result = binaryOperatorType(state, base, target, value, span);
#line 1253 "/src/checker-expressions.do"
    if (!::app_src_checker_types_::isAssignable(result, target)) {
#line 1253 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' produces ")) + ::app_src_checker_types_::typeName(result)) + std::string(", which cannot be assigned to ")) + ::app_src_checker_types_::typeName(target)), span);
    }
}
#line 1256 "/src/checker-expressions.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> binaryOperatorType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& operator_, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& left, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& right, ::app_src_ast_::SourceSpan span) {
#line 1257 "/src/checker-expressions.do"
    if (((operator_ == std::string("+")) && (::app_src_checker_types_::typeName(left) == std::string("string"))) && ((::app_src_checker_types_::typeName(right) == std::string("string")) || (::app_src_checker_types_::typeName(right) == std::string("char")))) {
#line 1257 "/src/checker-expressions.do"
        return ::app_src_checker_types_::primitive(std::string("string"));
    }
#line 1258 "/src/checker-expressions.do"
    if (::app_src_checker_types_::isNumeric(left) && ::app_src_checker_types_::isNumeric(right)) {
#line 1259 "/src/checker-expressions.do"
        if ((((operator_ == std::string("\\")) || (operator_ == std::string("%"))) || bitwiseOperator(operator_)) && (!isInteger(left) || !isInteger(right))) {
#line 1260 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' requires integer operands, got ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), span);
        }
#line 1262 "/src/checker-expressions.do"
        if (((operator_ == std::string("/")) && isInteger(left)) && isInteger(right)) {
#line 1262 "/src/checker-expressions.do"
            ::app_src_checker_common_::typeError(state, std::string("Operator '/' requires at least one floating-point operand"), span);
        }
#line 1263 "/src/checker-expressions.do"
        return ::app_src_checker_types_::numericResult(left, right);
    }
#line 1265 "/src/checker-expressions.do"
    ::app_src_checker_common_::typeError(state, (((((std::string("Operator '") + operator_) + std::string("' is not defined for ")) + ::app_src_checker_types_::typeName(left)) + std::string(" and ")) + ::app_src_checker_types_::typeName(right)), span);
#line 1266 "/src/checker-expressions.do"
    return ::app_src_checker_types_::unknownType();
}
#line 1269 "/src/checker-expressions.do"
bool isInteger(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 1270 "/src/checker-expressions.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive_ = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 1271 "/src/checker-expressions.do"
            return (((primitive_->name == std::string("byte")) || (primitive_->name == std::string("int"))) || (primitive_->name == std::string("long")));
    }
    else {
    }
    }
#line 1274 "/src/checker-expressions.do"
    return false;
}
#line 1277 "/src/checker-expressions.do"
bool bitwiseOperator(const std::string& operator_) {
#line 1278 "/src/checker-expressions.do"
    return ((((((operator_ == std::string("&")) || (operator_ == std::string("|"))) || (operator_ == std::string("^"))) || (operator_ == std::string("<<"))) || (operator_ == std::string(">>"))) || (operator_ == std::string(">>>")));
}
#line 1281 "/src/checker-expressions.do"
bool isNullableType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 1282 "/src/checker-expressions.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 1283 "/src/checker-expressions.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1284 "/src/checker-expressions.do"
            const auto& _iterable_100 = union_->types;
            for (const auto& member : *_iterable_100) {
#line 1284 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 1284 "/src/checker-expressions.do"
                    return true;
                }
            }
    }
    else {
    }
    }
#line 1287 "/src/checker-expressions.do"
    return false;
}
#line 1290 "/src/checker-expressions.do"
bool isFallibleType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 1291 "/src/checker-expressions.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
#line 1291 "/src/checker-expressions.do"
            return true;
    }
    else {
#line 1291 "/src/checker-expressions.do"
            return isNullableType(type_);
    }
    }
    doof::unreachable();
}
#line 1294 "/src/checker-expressions.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> fallibleValueType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 1295 "/src/checker-expressions.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 1296 "/src/checker-expressions.do"
            return doof::optional_value(result->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1298 "/src/checker-expressions.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 1299 "/src/checker-expressions.do"
            const auto& _iterable_102 = union_->types;
            for (const auto& member : *_iterable_102) {
#line 1299 "/src/checker-expressions.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 1299 "/src/checker-expressions.do"
                    members->push_back(member);
                }
            }
#line 1300 "/src/checker-expressions.do"
            if (static_cast<int32_t>((members)->size()) == 1) {
#line 1300 "/src/checker-expressions.do"
                return doof::optional_value(doof::array_at(members, 0, "src/checker-expressions", 1300));
            }
#line 1301 "/src/checker-expressions.do"
            if (static_cast<int32_t>((members)->size()) > 1) {
#line 1301 "/src/checker-expressions.do"
                return doof::optional_value(::app_src_checker_types_::unionType(members));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 1303 "/src/checker-expressions.do"
            return doof::optional_value(::app_src_checker_types_::unknownType());
    }
    else {
    }
    }
#line 1306 "/src/checker-expressions.do"
    return std::monostate{};
}
#line 1309 "/src/checker-expressions.do"
bool orderedTypes(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& left, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& right) {
#line 1310 "/src/checker-expressions.do"
    if ((std::visit([](auto&& _obj) { return _obj->kind; }, left) == std::string("unknown")) || (std::visit([](auto&& _obj) { return _obj->kind; }, right) == std::string("unknown"))) {
#line 1310 "/src/checker-expressions.do"
        return true;
    }
#line 1311 "/src/checker-expressions.do"
    if (::app_src_checker_types_::isNumeric(left) && ::app_src_checker_types_::isNumeric(right)) {
#line 1311 "/src/checker-expressions.do"
        return true;
    }
#line 1312 "/src/checker-expressions.do"
    if (::app_src_checker_types_::sameType(left, right)) {
#line 1313 "/src/checker-expressions.do"
        {
            auto _case_subject = left;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                const auto& primitive_ = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 1314 "/src/checker-expressions.do"
                return ((primitive_->name == std::string("string")) || (primitive_->name == std::string("char")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 1315 "/src/checker-expressions.do"
                return true;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
#line 1316 "/src/checker-expressions.do"
                return true;
        }
        else {
        }
        }
    }
#line 1320 "/src/checker-expressions.do"
    return false;
}
#line 1323 "/src/checker-expressions.do"
bool typesOverlap(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& left, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& right) {
#line 1324 "/src/checker-expressions.do"
    if ((std::visit([](auto&& _obj) { return _obj->kind; }, left) == std::string("unknown")) || (std::visit([](auto&& _obj) { return _obj->kind; }, right) == std::string("unknown"))) {
#line 1324 "/src/checker-expressions.do"
        return true;
    }
#line 1325 "/src/checker-expressions.do"
    {
        auto _case_subject = left;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1327 "/src/checker-expressions.do"
            const auto& _iterable_104 = union_->types;
            for (const auto& member : *_iterable_104) {
#line 1327 "/src/checker-expressions.do"
                if (typesOverlap(member, right)) {
#line 1327 "/src/checker-expressions.do"
                    return true;
                }
            }
#line 1328 "/src/checker-expressions.do"
            return false;
    }
    else {
    }
    }
#line 1332 "/src/checker-expressions.do"
    {
        auto _case_subject = right;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 1334 "/src/checker-expressions.do"
            const auto& _iterable_106 = union_->types;
            for (const auto& member : *_iterable_106) {
#line 1334 "/src/checker-expressions.do"
                if (typesOverlap(left, member)) {
#line 1334 "/src/checker-expressions.do"
                    return true;
                }
            }
#line 1335 "/src/checker-expressions.do"
            return false;
    }
    else {
    }
    }
#line 1339 "/src/checker-expressions.do"
    return ((::app_src_checker_types_::isAssignable(left, right) || ::app_src_checker_types_::isAssignable(right, left)) || (::app_src_checker_types_::isNumeric(left) && ::app_src_checker_types_::isNumeric(right)));
}
#line 1342 "/src/checker-expressions.do"
void validateCaseRangeBound(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& bound, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& subjectType, const std::shared_ptr<::app_src_semantic_::Scope>& scope, ::app_src_ast_::SourceSpan span) {
#line 1343 "/src/checker-expressions.do"
    if (doof::is_null(bound)) {
#line 1343 "/src/checker-expressions.do"
        return;
    }
#line 1344 "/src/checker-expressions.do"
    const auto boundType = checkExpression(state, doof::unwrap_optional(bound), scope, ::app_src_checker_symbols_::optionalResolvedType(subjectType));
#line 1345 "/src/checker-expressions.do"
    if ((!isInteger(subjectType) || !isInteger(boundType)) || !typesOverlap(subjectType, boundType)) {
#line 1346 "/src/checker-expressions.do"
        ::app_src_checker_common_::typeError(state, ((((std::string("Case range bound of type \"") + ::app_src_checker_types_::typeName(boundType)) + std::string("\" cannot match subject type \"")) + ::app_src_checker_types_::typeName(subjectType)) + std::string("\"")), span);
    }
}
#line 1 "<doof-generated>"
}
