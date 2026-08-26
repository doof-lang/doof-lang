#include "src_checker_calls.hpp"

namespace app_src_checker_calls_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_statements_;
using namespace ::app_src_checker_expressions_;
using namespace ::app_src_checker_resolution_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_generics_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_validation_;
#line 49 "/src/checker-calls.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkCall(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 50 "/src/checker-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 52 "/src/checker-calls.do"
            if (((identifier->name == std::string("Success")) || (identifier->name == std::string("Failure"))) && doof::is_null(::app_src_checker_symbols_::lookup(scope, identifier->name))) {
#line 53 "/src/checker-calls.do"
                std::shared_ptr<::app_src_semantic_::ResultResolvedType> expectedResult = nullptr;
#line 54 "/src/checker-calls.do"
                if (!doof::is_null(expected)) {
#line 55 "/src/checker-calls.do"
                    {
                        auto _case_subject = doof::unwrap_optional(expected);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 56 "/src/checker-calls.do"
                            (expectedResult = result);
                    }
                    else {
                    }
                    }
                }
#line 60 "/src/checker-calls.do"
                std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = ::app_src_checker_types_::unknownType();
#line 61 "/src/checker-calls.do"
                if (static_cast<int32_t>((expression->args)->size()) > 0) {
#line 62 "/src/checker-calls.do"
                    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedValue = std::monostate{};
#line 63 "/src/checker-calls.do"
                    if (!doof::is_null(expectedResult)) {
#line 63 "/src/checker-calls.do"
                        (expectedValue = doof::optional_value(((identifier->name == std::string("Success")) ? expectedResult->valueType : expectedResult->errorType)));
                    }
#line 64 "/src/checker-calls.do"
                    (valueType = ::app_src_checker_expressions_::checkExpression(state, doof::array_at(expression->args, 0, "src/checker-calls", 64)->value, scope, expectedValue));
                }
#line 66 "/src/checker-calls.do"
                if (!doof::is_null(expectedResult)) {
#line 67 "/src/checker-calls.do"
                    (valueType = ((static_cast<int32_t>((expression->args)->size()) == 0) ? ((identifier->name == std::string("Success")) ? expectedResult->valueType : expectedResult->errorType) : valueType));
#line 68 "/src/checker-calls.do"
                    (identifier->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), valueType, false)}), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(expectedResult)), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))));
#line 69 "/src/checker-calls.do"
                    (identifier->resolvedBinding = std::make_shared<::app_src_semantic_::Binding>(identifier->name, std::string("builtin"), ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), valueType, false)}), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(expectedResult)), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), false, ::app_src_checker_validation_::checkerSemanticSpan(identifier->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")));
#line 70 "/src/checker-calls.do"
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(expectedResult)));
                }
#line 72 "/src/checker-calls.do"
                ::app_src_checker_common_::typeError(state, (identifier->name + std::string(" requires an expected Result type")), identifier->span);
#line 73 "/src/checker-calls.do"
                if (identifier->name == std::string("Success")) {
#line 73 "/src/checker-calls.do"
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::resultType(valueType, ::app_src_checker_types_::unknownType()));
                }
#line 74 "/src/checker-calls.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::resultType(::app_src_checker_types_::unknownType(), valueType));
            }
    }
    else {
    }
    }
#line 79 "/src/checker-calls.do"
    const auto calleeType = ::app_src_checker_expressions_::checkExpression(state, expression->callee, scope, std::monostate{});
#line 80 "/src/checker-calls.do"
    (expression->resolvedFunction = ::app_src_checker_generics_::functionDeclarationForCallee(expression->callee, calleeType, state->result));
#line 81 "/src/checker-calls.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, calleeType) == std::string("never")) {
#line 82 "/src/checker-calls.do"
        const auto& _iterable_2 = expression->args;
        for (const auto& argument : *_iterable_2) {
#line 82 "/src/checker-calls.do"
            ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, std::monostate{});
        }
#line 83 "/src/checker-calls.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::neverType());
    }
#line 85 "/src/checker-calls.do"
    {
        auto _case_subject = calleeType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& resolvedFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 87 "/src/checker-calls.do"
            std::shared_ptr<::app_src_semantic_::FunctionType> effectiveFunction = resolvedFunction;
#line 88 "/src/checker-calls.do"
            auto genericInferenceFailed = false;
#line 89 "/src/checker-calls.do"
            if (static_cast<int32_t>((expression->typeArgs)->size()) > 0) {
#line 90 "/src/checker-calls.do"
                if (static_cast<int32_t>((expression->typeArgs)->size()) != static_cast<int32_t>((resolvedFunction->typeParams)->size())) {
#line 91 "/src/checker-calls.do"
                    ::app_src_checker_common_::typeError(state, (((((std::string("Generic call requires ") + doof::to_string(static_cast<int32_t>((resolvedFunction->typeParams)->size()))) + std::string(" type argument")) + ((static_cast<int32_t>((resolvedFunction->typeParams)->size()) == 1) ? std::string("") : std::string("s"))) + std::string("; received ")) + doof::to_string(static_cast<int32_t>((expression->typeArgs)->size()))), expression->span);
                } else {
#line 96 "/src/checker-calls.do"
                    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> resolvedTypeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 97 "/src/checker-calls.do"
                    const auto& _iterable_4 = expression->typeArgs;
                    for (const auto& argument : *_iterable_4) {
#line 97 "/src/checker-calls.do"
                        resolvedTypeArgs->push_back(::app_src_checker_resolution_::resolveType(state, argument, doof::unwrap_optional(state->info), scope));
                    }
#line 98 "/src/checker-calls.do"
                    (expression->resolvedGenericTypeArgs = resolvedTypeArgs);
#line 99 "/src/checker-calls.do"
                    applyTypeArgumentConstraints(state, expression->resolvedFunction, resolvedTypeArgs, expression->span, scope);
#line 100 "/src/checker-calls.do"
                    const auto substituted = ::app_src_checker_types_::substituteTypeParams(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(resolvedFunction), resolvedFunction->typeParams, resolvedTypeArgs);
#line 101 "/src/checker-calls.do"
                    {
                        auto _case_subject = substituted;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 102 "/src/checker-calls.do"
                            (effectiveFunction = function_);
                    }
                    else {
                    }
                    }
                }
            } else if (static_cast<int32_t>((resolvedFunction->typeParams)->size()) > 0) {
#line 107 "/src/checker-calls.do"
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> inferred = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 108 "/src/checker-calls.do"
                auto complete = true;
#line 109 "/src/checker-calls.do"
                const auto& _iterable_6 = resolvedFunction->typeParams;
                for (const auto& typeParam : *_iterable_6) {
#line 110 "/src/checker-calls.do"
                    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferredType = std::monostate{};
#line 111 "/src/checker-calls.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 112 "/src/checker-calls.do"
                        const auto parameterIndex = (doof::is_null(doof::array_at(expression->args, i, "src/checker-calls", 112)->name) ? i : ::app_src_checker_symbols_::functionParameterIndex(resolvedFunction->params, doof::unwrap_optional(doof::array_at(expression->args, i, "src/checker-calls", 112)->name)));
#line 113 "/src/checker-calls.do"
                        if ((parameterIndex < 0) || (parameterIndex >= static_cast<int32_t>((resolvedFunction->params)->size()))) {
#line 113 "/src/checker-calls.do"
                            continue;
                        }
#line 114 "/src/checker-calls.do"
                        const auto parameterType = doof::array_at(resolvedFunction->params, parameterIndex, "src/checker-calls", 114)->type_;
#line 117 "/src/checker-calls.do"
                        auto inferenceExpected = genericInferenceExpected(parameterType, resolvedFunction->typeParams);
#line 118 "/src/checker-calls.do"
                        {
                            auto _case_subject = doof::array_at(expression->args, i, "src/checker-calls", 118)->value;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
#line 119 "/src/checker-calls.do"
                                (inferenceExpected = doof::optional_value(parameterType));
                        }
                        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
#line 120 "/src/checker-calls.do"
                                if (doof::is_null(inferenceExpected)) {
#line 120 "/src/checker-calls.do"
                                    continue;
                                }
                        }
                        else {
                        }
                        }
#line 123 "/src/checker-calls.do"
                        const auto actual = ::app_src_checker_expressions_::checkExpression(state, doof::array_at(expression->args, i, "src/checker-calls", 123)->value, scope, inferenceExpected);
#line 124 "/src/checker-calls.do"
                        const auto candidate = ::app_src_checker_generics_::inferTypeArgument(parameterType, actual, typeParam);
#line 125 "/src/checker-calls.do"
                        if (!doof::is_null(candidate)) {
#line 126 "/src/checker-calls.do"
                            auto candidateIsSelf = false;
#line 127 "/src/checker-calls.do"
                            {
                                auto _case_subject = doof::unwrap_optional(candidate);
                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                                    const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 127 "/src/checker-calls.do"
                                    (candidateIsSelf = (parameter->name == typeParam));
                            }
                            else {
                            }
                            }
#line 128 "/src/checker-calls.do"
                            auto inferredIsSelf = false;
#line 129 "/src/checker-calls.do"
                            if (!doof::is_null(inferredType)) {
#line 129 "/src/checker-calls.do"
                                {
                                    auto _case_subject = doof::unwrap_optional(inferredType);
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                                        const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 129 "/src/checker-calls.do"
                                        (inferredIsSelf = (parameter->name == typeParam));
                                }
                                else {
                                }
                                }
                            }
#line 130 "/src/checker-calls.do"
                            if (candidateIsSelf && (!doof::is_null(inferredType))) {
#line 130 "/src/checker-calls.do"
                                continue;
                            }
#line 131 "/src/checker-calls.do"
                            if (doof::is_null(inferredType) || (inferredIsSelf && !candidateIsSelf)) {
#line 131 "/src/checker-calls.do"
                                (inferredType = candidate);
                            } else if (::app_src_checker_types_::sameType(doof::unwrap_optional(inferredType), doof::unwrap_optional(candidate))) {
                            } else if (::app_src_checker_types_::isAssignable(doof::unwrap_optional(candidate), doof::unwrap_optional(inferredType))) {
                            } else if (::app_src_checker_types_::isAssignable(doof::unwrap_optional(inferredType), doof::unwrap_optional(candidate))) {
#line 134 "/src/checker-calls.do"
                                (inferredType = candidate);
                            } else {
#line 135 "/src/checker-calls.do"
                                (complete = false);
                            }
                        }
                    }
#line 138 "/src/checker-calls.do"
                    if (doof::is_null(inferredType)) {
#line 138 "/src/checker-calls.do"
                        (complete = false);
#line 138 "/src/checker-calls.do"
                        inferred->push_back(::app_src_checker_types_::typeParameter(typeParam, std::string(""), std::monostate{}));
                    } else {
#line 139 "/src/checker-calls.do"
                        inferred->push_back(doof::unwrap_optional(inferredType));
                    }
                }
#line 141 "/src/checker-calls.do"
                if (complete) {
#line 142 "/src/checker-calls.do"
                    (expression->resolvedGenericTypeArgs = inferred);
#line 143 "/src/checker-calls.do"
                    applyTypeArgumentConstraints(state, expression->resolvedFunction, inferred, expression->span, scope);
#line 144 "/src/checker-calls.do"
                    const auto substituted = ::app_src_checker_types_::substituteTypeParams(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(resolvedFunction), resolvedFunction->typeParams, inferred);
#line 145 "/src/checker-calls.do"
                    {
                        auto _case_subject = substituted;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 146 "/src/checker-calls.do"
                            (effectiveFunction = function_);
                    }
                    else {
                    }
                    }
                } else {
#line 150 "/src/checker-calls.do"
                    (genericInferenceFailed = true);
#line 151 "/src/checker-calls.do"
                    ::app_src_checker_common_::typeError(state, std::string("Cannot infer consistent type arguments for generic call; provide explicit type arguments"), expression->span);
                }
            }
#line 154 "/src/checker-calls.do"
            auto named = false;
#line 155 "/src/checker-calls.do"
            const auto& _iterable_9 = expression->args;
            for (const auto& argument : *_iterable_9) {
#line 155 "/src/checker-calls.do"
                if (!doof::is_null(argument->name)) {
#line 155 "/src/checker-calls.do"
                    (named = true);
                }
            }
#line 156 "/src/checker-calls.do"
            if (named) {
#line 157 "/src/checker-calls.do"
                std::shared_ptr<std::vector<std::string>> used = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 158 "/src/checker-calls.do"
                const auto& _iterable_11 = expression->args;
                for (const auto& argument : *_iterable_11) {
#line 159 "/src/checker-calls.do"
                    if (doof::is_null(argument->name)) {
#line 160 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, std::string("Named calls cannot contain positional arguments"), argument->span);
#line 161 "/src/checker-calls.do"
                        ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, std::monostate{});
#line 162 "/src/checker-calls.do"
                        continue;
                    }
#line 164 "/src/checker-calls.do"
                    const auto index = ::app_src_checker_symbols_::functionParameterIndex(effectiveFunction->params, doof::unwrap_optional(argument->name));
#line 165 "/src/checker-calls.do"
                    if (index < 0) {
#line 166 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Unknown named argument '") + doof::unwrap_optional(argument->name)) + std::string("'")), argument->span);
#line 167 "/src/checker-calls.do"
                        ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, std::monostate{});
#line 168 "/src/checker-calls.do"
                        continue;
                    }
#line 170 "/src/checker-calls.do"
                    if (::app_src_checker_symbols_::containsString(used, doof::unwrap_optional(argument->name))) {
#line 170 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Duplicate named argument '") + doof::unwrap_optional(argument->name)) + std::string("'")), argument->span);
                    }
#line 171 "/src/checker-calls.do"
                    used->push_back(doof::unwrap_optional(argument->name));
#line 172 "/src/checker-calls.do"
                    const auto expected = doof::array_at(effectiveFunction->params, index, "src/checker-calls", 172)->type_;
#line 173 "/src/checker-calls.do"
                    const auto actual = ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, [&]() -> std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (genericInferenceFailed) { return std::monostate{}; } return ::app_src_checker_symbols_::optionalResolvedType(expected); }());
#line 174 "/src/checker-calls.do"
                    if (!genericInferenceFailed && !::app_src_checker_types_::isAssignable(actual, expected)) {
#line 174 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, (((((std::string("Argument '") + doof::unwrap_optional(argument->name)) + std::string("' has type ")) + ::app_src_checker_types_::typeName(actual)) + std::string("; expected ")) + ::app_src_checker_types_::typeName(expected)), argument->span);
                    }
                }
#line 176 "/src/checker-calls.do"
                const auto& _iterable_13 = effectiveFunction->params;
                for (const auto& parameter : *_iterable_13) {
#line 177 "/src/checker-calls.do"
                    if (!parameter->hasDefault && !::app_src_checker_symbols_::containsString(used, parameter->name)) {
#line 178 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Missing required argument '") + parameter->name) + std::string("'")), expression->span);
                    }
                }
            } else {
#line 182 "/src/checker-calls.do"
                auto requiredCount = 0;
#line 183 "/src/checker-calls.do"
                const auto& _iterable_15 = effectiveFunction->params;
                for (const auto& parameter : *_iterable_15) {
#line 183 "/src/checker-calls.do"
                    if (!parameter->hasDefault) {
#line 183 "/src/checker-calls.do"
                        (requiredCount = (requiredCount + 1));
                    }
                }
#line 184 "/src/checker-calls.do"
                if ((static_cast<int32_t>((expression->args)->size()) < requiredCount) || (static_cast<int32_t>((expression->args)->size()) > static_cast<int32_t>((effectiveFunction->params)->size()))) {
#line 185 "/src/checker-calls.do"
                    const auto range = ((requiredCount == static_cast<int32_t>((effectiveFunction->params)->size())) ? doof::to_string(requiredCount) : ((doof::to_string(requiredCount) + std::string("-")) + doof::to_string(static_cast<int32_t>((effectiveFunction->params)->size()))));
#line 186 "/src/checker-calls.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("Expected ") + range) + std::string(" argument(s) but got ")) + doof::to_string(static_cast<int32_t>((expression->args)->size()))), expression->span);
                }
#line 188 "/src/checker-calls.do"
                for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 189 "/src/checker-calls.do"
                    const auto expected = ((i < static_cast<int32_t>((effectiveFunction->params)->size())) ? doof::array_at(effectiveFunction->params, i, "src/checker-calls", 189)->type_ : ::app_src_checker_types_::unknownType());
#line 190 "/src/checker-calls.do"
                    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> argumentExpected = [&]() -> std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (genericInferenceFailed) { return std::monostate{}; } return doof::optional_value(expected); }();
#line 191 "/src/checker-calls.do"
                    if (::app_src_checker_symbols_::isBuiltinPrintlnCall(expression->callee)) {
#line 191 "/src/checker-calls.do"
                        (argumentExpected = std::monostate{});
                    }
#line 192 "/src/checker-calls.do"
                    const auto actual = ::app_src_checker_expressions_::checkExpression(state, doof::array_at(expression->args, i, "src/checker-calls", 192)->value, scope, argumentExpected);
#line 193 "/src/checker-calls.do"
                    if (!genericInferenceFailed && !::app_src_checker_types_::isAssignable(actual, expected)) {
#line 193 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, (((((std::string("Argument ") + doof::to_string((i + 1))) + std::string(" has type ")) + ::app_src_checker_types_::typeName(actual)) + std::string("; expected ")) + ::app_src_checker_types_::typeName(expected)), doof::array_at(expression->args, i, "src/checker-calls", 193)->span);
                    }
                }
            }
#line 196 "/src/checker-calls.do"
            validateActorMethodBoundary(state, expression, effectiveFunction);
#line 197 "/src/checker-calls.do"
            if (callArgumentsDiverge(expression)) {
#line 197 "/src/checker-calls.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::neverType());
            }
#line 198 "/src/checker-calls.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), checkedMemberCallReturnType(expression, effectiveFunction->returnType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 201 "/src/checker-calls.do"
            auto effectiveClass = class_;
#line 202 "/src/checker-calls.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
#line 203 "/src/checker-calls.do"
            if (static_cast<int32_t>((expression->typeArgs)->size()) > 0) {
#line 204 "/src/checker-calls.do"
                std::shared_ptr<std::vector<std::string>> declaredTypeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 205 "/src/checker-calls.do"
                std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints = (doof::is_null(expression->resolvedClass) ? std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>(std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>{}) : expression->resolvedClass->typeParamConstraints);
#line 206 "/src/checker-calls.do"
                if (!doof::is_null(declaration)) {
#line 206 "/src/checker-calls.do"
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 206 "/src/checker-calls.do"
                            (declaredTypeParams = classDeclaration->typeParams);
#line 206 "/src/checker-calls.do"
                            (constraints = classDeclaration->typeParamConstraints);
                    }
                    else {
                    }
                    }
                }
#line 207 "/src/checker-calls.do"
                if (static_cast<int32_t>((expression->typeArgs)->size()) != static_cast<int32_t>((declaredTypeParams)->size())) {
#line 208 "/src/checker-calls.do"
                    ::app_src_checker_common_::typeError(state, (((((std::string("Generic construction requires ") + doof::to_string(static_cast<int32_t>((declaredTypeParams)->size()))) + std::string(" type argument")) + ((static_cast<int32_t>((declaredTypeParams)->size()) == 1) ? std::string("") : std::string("s"))) + std::string("; received ")) + doof::to_string(static_cast<int32_t>((expression->typeArgs)->size()))), expression->span);
                } else {
#line 210 "/src/checker-calls.do"
                    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> resolvedTypeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 211 "/src/checker-calls.do"
                    const auto& _iterable_18 = expression->typeArgs;
                    for (const auto& argument : *_iterable_18) {
#line 211 "/src/checker-calls.do"
                        resolvedTypeArgs->push_back(::app_src_checker_resolution_::resolveType(state, argument, doof::unwrap_optional(state->info), scope));
                    }
#line 212 "/src/checker-calls.do"
                    (expression->resolvedGenericTypeArgs = resolvedTypeArgs);
#line 213 "/src/checker-calls.do"
                    (effectiveClass = ::app_src_checker_types_::classType(class_->name, class_->symbol, resolvedTypeArgs));
#line 214 "/src/checker-calls.do"
                    ::app_src_checker_resolution_::validateTypeArgumentConstraints(state, declaredTypeParams, constraints, resolvedTypeArgs, expression->span, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), scope);
                }
            } else if ((!doof::is_null(declaration)) && (static_cast<int32_t>((class_->typeArgs)->size()) == 0)) {
#line 217 "/src/checker-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 219 "/src/checker-calls.do"
                        const auto inferred = inferClassTypeArguments(state, expression, scope, class_, classDeclaration);
#line 220 "/src/checker-calls.do"
                        if ((static_cast<int32_t>((inferred)->size()) == static_cast<int32_t>((classDeclaration->typeParams)->size())) && (static_cast<int32_t>((inferred)->size()) > 0)) {
#line 221 "/src/checker-calls.do"
                            (effectiveClass = ::app_src_checker_types_::classType(class_->name, class_->symbol, inferred));
#line 222 "/src/checker-calls.do"
                            (expression->resolvedGenericTypeArgs = inferred);
#line 223 "/src/checker-calls.do"
                            ::app_src_checker_resolution_::validateTypeArgumentConstraints(state, classDeclaration->typeParams, classDeclaration->typeParamConstraints, inferred, expression->span, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), scope);
                        }
                }
                else {
                }
                }
            }
#line 229 "/src/checker-calls.do"
            if (!::app_src_checker_generics_::insideConstructorFactory(scope, effectiveClass)) {
#line 229 "/src/checker-calls.do"
                (expression->resolvedConstructor = ::app_src_checker_generics_::constructorForClass(effectiveClass, state->result));
            }
#line 230 "/src/checker-calls.do"
            const auto constructorMethod = expression->resolvedConstructor;
#line 231 "/src/checker-calls.do"
            if (!doof::is_null(constructorMethod)) {
#line 232 "/src/checker-calls.do"
                validateConstructorVisibility(state, effectiveClass, doof::unwrap_optional(constructorMethod), expression->span);
#line 233 "/src/checker-calls.do"
                auto constructorType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_19 = constructorMethod->resolvedType; if (doof::is_null(_coalesce_19)) return ::app_src_checker_symbols_::methodSignature(doof::unwrap_optional(constructorMethod), ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result); return doof::unwrap_optional(_coalesce_19); }();
#line 234 "/src/checker-calls.do"
                if (!doof::is_null(declaration)) {
#line 235 "/src/checker-calls.do"
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 236 "/src/checker-calls.do"
                            (constructorType = ::app_src_checker_types_::substituteTypeParams(constructorType, classDeclaration->typeParams, effectiveClass->typeArgs));
                    }
                    else {
                    }
                    }
                }
#line 240 "/src/checker-calls.do"
                {
                    auto _case_subject = constructorType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                        const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 242 "/src/checker-calls.do"
                        validateConstructorCallArguments(state, expression, function_->params, scope, effectiveClass);
#line 243 "/src/checker-calls.do"
                        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), function_->returnType);
                }
                else {
                }
                }
            }
#line 248 "/src/checker-calls.do"
            std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> constructorParams = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 249 "/src/checker-calls.do"
            if (!doof::is_null(declaration)) {
#line 250 "/src/checker-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 252 "/src/checker-calls.do"
                        (expression->resolvedClass = classDeclaration);
#line 253 "/src/checker-calls.do"
                        const auto& _iterable_21 = classDeclaration->fields;
                        for (const auto& field : *_iterable_21) {
#line 254 "/src/checker-calls.do"
                            if (field->static_ || field->const_) {
#line 254 "/src/checker-calls.do"
                                continue;
                            }
#line 255 "/src/checker-calls.do"
                            const auto& _iterable_23 = field->names;
                            for (const auto& name : *_iterable_23) {
#line 256 "/src/checker-calls.do"
                                constructorParams->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(name, ::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(effectiveClass), name, field->span, false), (!doof::is_null(field->defaultValue))));
                            }
                        }
                }
                else {
                }
                }
            }
#line 267 "/src/checker-calls.do"
            validateFieldConstructorVisibility(state, expression, effectiveClass, declaration);
#line 268 "/src/checker-calls.do"
            validateConstructorCallArguments(state, expression, constructorParams, scope, effectiveClass);
#line 269 "/src/checker-calls.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(effectiveClass));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 272 "/src/checker-calls.do"
            const auto& _iterable_25 = expression->args;
            for (const auto& argument : *_iterable_25) {
#line 272 "/src/checker-calls.do"
                ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, std::monostate{});
            }
#line 273 "/src/checker-calls.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
    }
    else {
#line 275 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Expression of type ") + ::app_src_checker_types_::typeName(calleeType)) + std::string(" is not callable")), expression->span);
#line 275 "/src/checker-calls.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
    }
    }
    doof::unreachable();
#line 277 "/src/checker-calls.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
}
#line 284 "/src/checker-calls.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> genericInferenceExpected(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& pattern, const std::shared_ptr<std::vector<std::string>>& typeParams) {
#line 285 "/src/checker-calls.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> unknownArguments = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 286 "/src/checker-calls.do"
    const auto& _iterable_27 = typeParams;
    for (const auto& _discard_26_0 : *_iterable_27) {
#line 286 "/src/checker-calls.do"
        unknownArguments->push_back(::app_src_checker_types_::unknownType());
    }
#line 287 "/src/checker-calls.do"
    const auto substituted = ::app_src_checker_types_::substituteTypeParams(pattern, typeParams, unknownArguments);
#line 288 "/src/checker-calls.do"
    if (::app_src_checker_types_::sameType(pattern, substituted)) {
#line 288 "/src/checker-calls.do"
        return doof::optional_value(pattern);
    }
#line 289 "/src/checker-calls.do"
    return std::monostate{};
}
#line 292 "/src/checker-calls.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkedMemberCallReturnType(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& returnType) {
#line 293 "/src/checker-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 295 "/src/checker-calls.do"
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 296 "/src/checker-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
#line 298 "/src/checker-calls.do"
                        if (member->optional) {
#line 299 "/src/checker-calls.do"
                            {
                                auto _case_subject = returnType;
                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 301 "/src/checker-calls.do"
                                    return ::app_src_checker_types_::resultType(::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{result->valueType, ::app_src_checker_types_::noneType()})), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{result->errorType, ::app_src_checker_types_::weakReferenceErrorType()})));
                            }
                            else {
#line 303 "/src/checker-calls.do"
                                    return ::app_src_checker_types_::resultType(::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{returnType, ::app_src_checker_types_::noneType()})), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::weakReferenceErrorType()));
                            }
                            }
                            doof::unreachable();
                        }
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
#line 313 "/src/checker-calls.do"
    return returnType;
}
#line 316 "/src/checker-calls.do"
bool callArgumentsDiverge(const std::shared_ptr<::app_src_ast_::CallExpression>& expression) {
#line 317 "/src/checker-calls.do"
    const auto& _iterable_29 = expression->args;
    for (const auto& argument : *_iterable_29) {
#line 318 "/src/checker-calls.do"
        if ((!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, argument->value))) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, argument->value))) == std::string("never"))) {
#line 318 "/src/checker-calls.do"
            return true;
        }
    }
#line 320 "/src/checker-calls.do"
    return false;
}
#line 323 "/src/checker-calls.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> inferClassTypeArguments(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& class_, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& declaration) {
#line 324 "/src/checker-calls.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> patterns = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 325 "/src/checker-calls.do"
    const auto constructor = ::app_src_checker_generics_::constructorForClass(class_, state->result);
#line 326 "/src/checker-calls.do"
    if (!doof::is_null(constructor)) {
#line 327 "/src/checker-calls.do"
        const auto signature = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_30 = constructor->resolvedType; if (doof::is_null(_coalesce_30)) return ::app_src_checker_symbols_::methodSignature(doof::unwrap_optional(constructor), ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result); return doof::unwrap_optional(_coalesce_30); }();
#line 328 "/src/checker-calls.do"
        {
            auto _case_subject = signature;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 329 "/src/checker-calls.do"
                (patterns = function_->params);
        }
        else {
        }
        }
    } else {
#line 333 "/src/checker-calls.do"
        const auto& _iterable_32 = declaration->fields;
        for (const auto& field : *_iterable_32) {
#line 334 "/src/checker-calls.do"
            if (field->static_) {
#line 334 "/src/checker-calls.do"
                continue;
            }
#line 335 "/src/checker-calls.do"
            const auto& _iterable_34 = field->names;
            for (const auto& name : *_iterable_34) {
#line 336 "/src/checker-calls.do"
                patterns->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(name, ::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), name, field->span, false), (!doof::is_null(field->defaultValue))));
            }
        }
    }
#line 340 "/src/checker-calls.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> inferred = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 341 "/src/checker-calls.do"
    const auto& _iterable_36 = declaration->typeParams;
    for (const auto& typeParam : *_iterable_36) {
#line 342 "/src/checker-calls.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> candidate = std::monostate{};
#line 343 "/src/checker-calls.do"
        for (int32_t index = 0; index < static_cast<int32_t>((expression->args)->size()); ++index) {
#line 344 "/src/checker-calls.do"
            const auto parameterIndex = (doof::is_null(doof::array_at(expression->args, index, "src/checker-calls", 344)->name) ? index : ::app_src_checker_symbols_::functionParameterIndex(patterns, doof::unwrap_optional(doof::array_at(expression->args, index, "src/checker-calls", 344)->name)));
#line 345 "/src/checker-calls.do"
            if ((parameterIndex < 0) || (parameterIndex >= static_cast<int32_t>((patterns)->size()))) {
#line 345 "/src/checker-calls.do"
                continue;
            }
#line 346 "/src/checker-calls.do"
            const auto actual = ::app_src_checker_expressions_::checkExpression(state, doof::array_at(expression->args, index, "src/checker-calls", 346)->value, scope, ::app_src_checker_symbols_::optionalResolvedType(doof::array_at(patterns, parameterIndex, "src/checker-calls", 346)->type_));
#line 347 "/src/checker-calls.do"
            const auto next = ::app_src_checker_generics_::inferTypeArgument(doof::array_at(patterns, parameterIndex, "src/checker-calls", 347)->type_, actual, typeParam);
#line 348 "/src/checker-calls.do"
            if (!doof::is_null(next)) {
#line 348 "/src/checker-calls.do"
                (candidate = next);
            }
        }
#line 350 "/src/checker-calls.do"
        if (doof::is_null(candidate)) {
#line 350 "/src/checker-calls.do"
            return std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
        }
#line 351 "/src/checker-calls.do"
        inferred->push_back(doof::unwrap_optional(candidate));
    }
#line 353 "/src/checker-calls.do"
    return inferred;
}
#line 356 "/src/checker-calls.do"
void applyTypeArgumentConstraints(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments, ::app_src_ast_::SourceSpan span, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 357 "/src/checker-calls.do"
    if (doof::is_null(declaration)) {
#line 357 "/src/checker-calls.do"
        return;
    }
#line 358 "/src/checker-calls.do"
    ::app_src_checker_resolution_::validateTypeArgumentConstraints(state, declaration->typeParams, declaration->typeParamConstraints, arguments, span, doof::unwrap_optional(state->info), scope);
}
#line 363 "/src/checker-calls.do"
void validatePositionalConstructorArguments(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>& params, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& class_) {
#line 364 "/src/checker-calls.do"
    auto requiredCount = 0;
#line 365 "/src/checker-calls.do"
    const auto& _iterable_39 = params;
    for (const auto& parameter : *_iterable_39) {
#line 365 "/src/checker-calls.do"
        if (!parameter->hasDefault) {
#line 365 "/src/checker-calls.do"
            (requiredCount = (requiredCount + 1));
        }
    }
#line 366 "/src/checker-calls.do"
    if ((static_cast<int32_t>((expression->args)->size()) < requiredCount) || (static_cast<int32_t>((expression->args)->size()) > static_cast<int32_t>((params)->size()))) {
#line 367 "/src/checker-calls.do"
        const auto range = ((requiredCount == static_cast<int32_t>((params)->size())) ? doof::to_string(requiredCount) : ((doof::to_string(requiredCount) + std::string("-")) + doof::to_string(static_cast<int32_t>((params)->size()))));
#line 368 "/src/checker-calls.do"
        const auto kind = ((class_->symbol->kind == std::string("struct")) ? std::string("Struct") : std::string("Class"));
#line 369 "/src/checker-calls.do"
        ::app_src_checker_common_::typeError(state, ((((((kind + std::string(" \"")) + class_->name) + std::string("\" expects ")) + range) + std::string(" constructor argument(s) but got ")) + doof::to_string(static_cast<int32_t>((expression->args)->size()))), expression->span);
    }
#line 371 "/src/checker-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 372 "/src/checker-calls.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
#line 373 "/src/checker-calls.do"
        if (i < static_cast<int32_t>((params)->size())) {
#line 373 "/src/checker-calls.do"
            (expected = doof::optional_value(doof::array_at(params, i, "src/checker-calls", 373)->type_));
        }
#line 374 "/src/checker-calls.do"
        const auto actual = ::app_src_checker_expressions_::checkExpression(state, doof::array_at(expression->args, i, "src/checker-calls", 374)->value, scope, expected);
#line 375 "/src/checker-calls.do"
        if ((!doof::is_null(expected)) && !::app_src_checker_types_::isAssignable(actual, doof::unwrap_optional(expected))) {
#line 376 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, (((((std::string("Argument ") + doof::to_string((i + 1))) + std::string(" has type ")) + ::app_src_checker_types_::typeName(actual)) + std::string("; expected ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expected))), doof::array_at(expression->args, i, "src/checker-calls", 376)->span);
        }
    }
}
#line 381 "/src/checker-calls.do"
void validateConstructorCallArguments(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>& params, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& class_) {
#line 382 "/src/checker-calls.do"
    auto named = false;
#line 383 "/src/checker-calls.do"
    const auto& _iterable_42 = expression->args;
    for (const auto& argument : *_iterable_42) {
#line 383 "/src/checker-calls.do"
        if (!doof::is_null(argument->name)) {
#line 383 "/src/checker-calls.do"
            (named = true);
        }
    }
#line 384 "/src/checker-calls.do"
    if (!named) {
#line 384 "/src/checker-calls.do"
        validatePositionalConstructorArguments(state, expression, params, scope, class_);
#line 384 "/src/checker-calls.do"
        return;
    }
#line 386 "/src/checker-calls.do"
    std::shared_ptr<std::vector<std::string>> used = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 387 "/src/checker-calls.do"
    const auto& _iterable_44 = expression->args;
    for (const auto& argument : *_iterable_44) {
#line 388 "/src/checker-calls.do"
        if (doof::is_null(argument->name)) {
#line 389 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, std::string("Named construction cannot contain positional arguments"), argument->span);
#line 390 "/src/checker-calls.do"
            ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, std::monostate{});
#line 391 "/src/checker-calls.do"
            continue;
        }
#line 393 "/src/checker-calls.do"
        const auto index = ::app_src_checker_symbols_::functionParameterIndex(params, doof::unwrap_optional(argument->name));
#line 394 "/src/checker-calls.do"
        if (index < 0) {
#line 395 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Unknown named argument '") + doof::unwrap_optional(argument->name)) + std::string("'")), argument->span);
#line 396 "/src/checker-calls.do"
            ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, std::monostate{});
#line 397 "/src/checker-calls.do"
            continue;
        }
#line 399 "/src/checker-calls.do"
        if (::app_src_checker_symbols_::containsString(used, doof::unwrap_optional(argument->name))) {
#line 399 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Duplicate named argument '") + doof::unwrap_optional(argument->name)) + std::string("'")), argument->span);
        }
#line 400 "/src/checker-calls.do"
        used->push_back(doof::unwrap_optional(argument->name));
#line 401 "/src/checker-calls.do"
        const auto expected = doof::array_at(params, index, "src/checker-calls", 401)->type_;
#line 402 "/src/checker-calls.do"
        const auto actual = ::app_src_checker_expressions_::checkExpression(state, argument->value, scope, ::app_src_checker_symbols_::optionalResolvedType(expected));
#line 403 "/src/checker-calls.do"
        if (!::app_src_checker_types_::isAssignable(actual, expected)) {
#line 403 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, (((((std::string("Argument '") + doof::unwrap_optional(argument->name)) + std::string("' has type ")) + ::app_src_checker_types_::typeName(actual)) + std::string("; expected ")) + ::app_src_checker_types_::typeName(expected)), argument->span);
        }
    }
#line 405 "/src/checker-calls.do"
    const auto& _iterable_46 = params;
    for (const auto& parameter : *_iterable_46) {
#line 406 "/src/checker-calls.do"
        if (!parameter->hasDefault && !::app_src_checker_symbols_::containsString(used, parameter->name)) {
#line 407 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Missing required argument '") + parameter->name) + std::string("'")), expression->span);
        }
    }
}
#line 412 "/src/checker-calls.do"
void validateFieldConstructorVisibility(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_semantic_::ClassType>& class_, const std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& declaration) {
#line 413 "/src/checker-calls.do"
    if (doof::is_null(declaration) || (class_->symbol->module == state->info->path)) {
#line 413 "/src/checker-calls.do"
        return;
    }
#line 414 "/src/checker-calls.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& owner = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 416 "/src/checker-calls.do"
            for (int32_t index = 0; index < static_cast<int32_t>((expression->args)->size()); ++index) {
#line 417 "/src/checker-calls.do"
                const auto argument = doof::array_at(expression->args, index, "src/checker-calls", 417);
#line 418 "/src/checker-calls.do"
                std::shared_ptr<::app_src_ast_::ClassField> field = nullptr;
#line 419 "/src/checker-calls.do"
                auto fieldName = [&]() -> std::string { auto _coalesce_48 = argument->name; if (doof::is_null(_coalesce_48)) return std::string(""); return doof::unwrap_optional(_coalesce_48); }();
#line 420 "/src/checker-calls.do"
                if (!doof::is_null(argument->name)) {
#line 421 "/src/checker-calls.do"
                    (field = constructionField(owner, doof::unwrap_optional(argument->name)));
                } else {
#line 423 "/src/checker-calls.do"
                    auto parameterIndex = 0;
#line 424 "/src/checker-calls.do"
                    const auto& _iterable_50 = owner->fields;
                    for (const auto& candidate : *_iterable_50) {
#line 425 "/src/checker-calls.do"
                        if (candidate->static_ || candidate->const_) {
#line 425 "/src/checker-calls.do"
                            continue;
                        }
#line 426 "/src/checker-calls.do"
                        const auto& _iterable_52 = candidate->names;
                        for (const auto& name : *_iterable_52) {
#line 427 "/src/checker-calls.do"
                            if (parameterIndex == index) {
#line 427 "/src/checker-calls.do"
                                (field = candidate);
#line 427 "/src/checker-calls.do"
                                (fieldName = name);
#line 427 "/src/checker-calls.do"
                                break;
                            }
#line 428 "/src/checker-calls.do"
                            (parameterIndex += 1);
                        }
#line 430 "/src/checker-calls.do"
                        if (!doof::is_null(field)) {
#line 430 "/src/checker-calls.do"
                            break;
                        }
                    }
                }
#line 433 "/src/checker-calls.do"
                if ((!doof::is_null(field)) && field->private_) {
#line 434 "/src/checker-calls.do"
                    ::app_src_checker_common_::typeError(state, ((((std::string("Field '") + fieldName) + std::string("' is private to module '")) + class_->symbol->module) + std::string("'")), argument->span);
                }
            }
    }
    else {
    }
    }
}
#line 444 "/src/checker-calls.do"
void validateActorMethodBoundary(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_semantic_::FunctionType>& method) {
#line 445 "/src/checker-calls.do"
    std::shared_ptr<::app_src_semantic_::ActorType> actor = nullptr;
#line 446 "/src/checker-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 448 "/src/checker-calls.do"
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 449 "/src/checker-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                        const auto& actorType_ = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 450 "/src/checker-calls.do"
                        (actor = actorType_);
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
#line 457 "/src/checker-calls.do"
    if (doof::is_null(actor)) {
#line 457 "/src/checker-calls.do"
        return;
    }
#line 458 "/src/checker-calls.do"
    const auto& _iterable_54 = method->params;
    for (const auto& parameter : *_iterable_54) {
#line 459 "/src/checker-calls.do"
        const auto violation = ::app_src_checker_actor_boundary_::findActorBoundaryViolation(state->result, parameter->type_);
#line 460 "/src/checker-calls.do"
        if (!doof::is_null(violation)) {
#line 461 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, (((((((std::string("Actor method parameter \"") + parameter->name) + std::string("\" of type \"")) + ::app_src_checker_types_::typeName(parameter->type_)) + std::string("\" cannot cross actor boundary for \"")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(actor)))) + std::string("\": ")) + violation->reason), expression->span);
        }
    }
#line 467 "/src/checker-calls.do"
    const auto returnViolation = ::app_src_checker_actor_boundary_::findActorBoundaryViolation(state->result, method->returnType);
#line 468 "/src/checker-calls.do"
    if (!doof::is_null(returnViolation)) {
#line 469 "/src/checker-calls.do"
        ::app_src_checker_common_::typeError(state, (((((std::string("Actor method return type \"") + ::app_src_checker_types_::typeName(method->returnType)) + std::string("\" cannot cross actor boundary for \"")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(actor)))) + std::string("\": ")) + returnViolation->reason), expression->span);
    }
}
#line 476 "/src/checker-calls.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkLambda(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::LambdaExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 477 "/src/checker-calls.do"
    const auto expectedFunction = contextualFunctionType(expected);
#line 481 "/src/checker-calls.do"
    if ((expression->parameterless && (static_cast<int32_t>((expression->params)->size()) == 0)) && (!doof::is_null(expectedFunction))) {
#line 482 "/src/checker-calls.do"
        const auto& _iterable_56 = expectedFunction->params;
        for (const auto& expectedParameter : *_iterable_56) {
#line 483 "/src/checker-calls.do"
            expression->params->push_back(std::make_shared<::app_src_ast_::Parameter>(expectedParameter->name, std::string(""), std::monostate{}, std::monostate{}, doof::optional_value(expectedParameter->type_), expression->span));
        }
    }
#line 492 "/src/checker-calls.do"
    const auto lambdaScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 493 "/src/checker-calls.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 494 "/src/checker-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->params)->size()); ++i) {
#line 495 "/src/checker-calls.do"
        const auto parameter = doof::array_at(expression->params, i, "src/checker-calls", 495);
#line 496 "/src/checker-calls.do"
        const auto parameterType = (doof::is_null(parameter->type_) ? (((!doof::is_null(expectedFunction)) && (i < static_cast<int32_t>((expectedFunction->params)->size()))) ? doof::array_at(expectedFunction->params, i, "src/checker-calls", 496)->type_ : ::app_src_checker_types_::unknownType()) : ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(parameter->type_), doof::unwrap_optional(state->info), lambdaScope));
#line 497 "/src/checker-calls.do"
        (parameter->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(parameterType));
#line 498 "/src/checker-calls.do"
        params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, parameterType, (!doof::is_null(parameter->defaultValue))));
#line 499 "/src/checker-calls.do"
        if ((parameter->name != std::string("_")) && !::app_src_checker_symbols_::declare(lambdaScope, std::make_shared<::app_src_semantic_::Binding>(parameter->name, std::string("parameter"), parameterType, false, ::app_src_checker_validation_::checkerSemanticSpan(parameter->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")))) {
#line 500 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Binding '") + parameter->name) + std::string("' is already declared in this scope")), parameter->span);
        }
    }
#line 503 "/src/checker-calls.do"
    auto returnType = (doof::is_null(expectedFunction) ? ::app_src_checker_types_::unknownType() : expectedFunction->returnType);
#line 504 "/src/checker-calls.do"
    if (!doof::is_null(expression->returnType)) {
#line 505 "/src/checker-calls.do"
        (returnType = ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(expression->returnType), doof::unwrap_optional(state->info), lambdaScope));
#line 506 "/src/checker-calls.do"
        ::app_src_checker_symbols_::decorateAnnotationWithResolved(doof::unwrap_optional(expression->returnType), returnType);
    }
#line 511 "/src/checker-calls.do"
    (lambdaScope->returnType = doof::optional_value(returnType));
#line 512 "/src/checker-calls.do"
    {
        auto _case_subject = expression->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 513 "/src/checker-calls.do"
            ::app_src_checker_statements_::checkBlock(state, block, lambdaScope, false);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expressionBody = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 514 "/src/checker-calls.do"
            (returnType = ::app_src_checker_expressions_::checkExpression(state, expressionBody, lambdaScope, ::app_src_checker_symbols_::optionalResolvedType(returnType)));
    }
    }
#line 516 "/src/checker-calls.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::functionType(params, returnType, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
}
#line 522 "/src/checker-calls.do"
std::shared_ptr<::app_src_semantic_::FunctionType> contextualFunctionType(const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 523 "/src/checker-calls.do"
    if (doof::is_null(expected)) {
#line 523 "/src/checker-calls.do"
        return nullptr;
    }
#line 524 "/src/checker-calls.do"
    {
        auto _case_subject = doof::unwrap_optional(expected);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 525 "/src/checker-calls.do"
            return function_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 527 "/src/checker-calls.do"
            std::shared_ptr<::app_src_semantic_::FunctionType> found = nullptr;
#line 528 "/src/checker-calls.do"
            const auto& _iterable_59 = union_->types;
            for (const auto& member : *_iterable_59) {
#line 529 "/src/checker-calls.do"
                {
                    auto _case_subject = member;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                        const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 531 "/src/checker-calls.do"
                        if (!doof::is_null(found)) {
#line 531 "/src/checker-calls.do"
                            return nullptr;
                        }
#line 532 "/src/checker-calls.do"
                        (found = function_);
                }
                else {
                }
                }
            }
#line 537 "/src/checker-calls.do"
            return found;
    }
    else {
#line 539 "/src/checker-calls.do"
            return nullptr;
    }
    }
    doof::unreachable();
}
#line 543 "/src/checker-calls.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkConstruct(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 544 "/src/checker-calls.do"
    if ((expression->type_ == std::string("Success")) || (expression->type_ == std::string("Failure"))) {
#line 545 "/src/checker-calls.do"
        std::shared_ptr<::app_src_semantic_::ResultResolvedType> expectedResult = nullptr;
#line 546 "/src/checker-calls.do"
        if (!doof::is_null(expected)) {
#line 547 "/src/checker-calls.do"
            {
                auto _case_subject = doof::unwrap_optional(expected);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 548 "/src/checker-calls.do"
                    (expectedResult = result);
            }
            else {
            }
            }
        }
#line 552 "/src/checker-calls.do"
        std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType = ::app_src_checker_types_::unknownType();
#line 553 "/src/checker-calls.do"
        const auto& _iterable_61 = expression->args;
        for (const auto& property : *_iterable_61) {
#line 554 "/src/checker-calls.do"
            if (!doof::is_null(property->value)) {
#line 555 "/src/checker-calls.do"
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> propertyExpected = std::monostate{};
#line 556 "/src/checker-calls.do"
                if (!doof::is_null(expectedResult)) {
#line 557 "/src/checker-calls.do"
                    (propertyExpected = doof::optional_value(((expression->type_ == std::string("Success")) ? expectedResult->valueType : expectedResult->errorType)));
                }
#line 559 "/src/checker-calls.do"
                (valueType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, propertyExpected));
#line 560 "/src/checker-calls.do"
                (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(valueType));
            }
        }
#line 563 "/src/checker-calls.do"
        if (!doof::is_null(expectedResult)) {
#line 563 "/src/checker-calls.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(expectedResult)));
        }
#line 564 "/src/checker-calls.do"
        if (expression->type_ == std::string("Success")) {
#line 564 "/src/checker-calls.do"
            return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::resultType(valueType, ::app_src_checker_types_::unknownType()));
        }
#line 565 "/src/checker-calls.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::resultType(::app_src_checker_types_::unknownType(), valueType));
    }
#line 567 "/src/checker-calls.do"
    const auto symbol = ::app_src_checker_symbols_::valueSymbolFor(doof::unwrap_optional(state->info), expression->type_);
#line 568 "/src/checker-calls.do"
    if (doof::is_null(symbol)) {
#line 569 "/src/checker-calls.do"
        const auto message = ::app_src_checker_symbols_::valueUseDiagnostic(doof::unwrap_optional(state->info), expression->type_);
#line 570 "/src/checker-calls.do"
        ::app_src_checker_common_::typeError(state, ((message == std::string("")) ? ((std::string("Unknown constructed type '") + expression->type_) + std::string("'")) : message), expression->span);
#line 571 "/src/checker-calls.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::unknownType());
    }
#line 573 "/src/checker-calls.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
#line 574 "/src/checker-calls.do"
    if (!doof::is_null(declaration)) {
#line 575 "/src/checker-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(declaration);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 576 "/src/checker-calls.do"
                (expression->resolvedClass = classDeclaration);
        }
        else {
        }
        }
    }
#line 580 "/src/checker-calls.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> resolvedTypeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 581 "/src/checker-calls.do"
    const auto& _iterable_63 = expression->typeArgs;
    for (const auto& argument : *_iterable_63) {
#line 581 "/src/checker-calls.do"
        resolvedTypeArgs->push_back(::app_src_checker_resolution_::resolveType(state, argument, doof::unwrap_optional(state->info), scope));
    }
#line 582 "/src/checker-calls.do"
    if ((static_cast<int32_t>((resolvedTypeArgs)->size()) == 0) && (!doof::is_null(expected))) {
#line 583 "/src/checker-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& expectedClass = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 585 "/src/checker-calls.do"
                if ((expectedClass->symbol->module == symbol->module) && (expectedClass->symbol->name == symbol->name)) {
#line 586 "/src/checker-calls.do"
                    const auto& _iterable_65 = expectedClass->typeArgs;
                    for (const auto& argument : *_iterable_65) {
#line 586 "/src/checker-calls.do"
                        resolvedTypeArgs->push_back(argument);
                    }
                }
        }
        else {
        }
        }
    }
#line 592 "/src/checker-calls.do"
    if (!doof::is_null(expression->resolvedClass)) {
#line 593 "/src/checker-calls.do"
        ::app_src_checker_resolution_::validateTypeArgumentConstraints(state, expression->resolvedClass->typeParams, expression->resolvedClass->typeParamConstraints, resolvedTypeArgs, expression->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
    }
#line 595 "/src/checker-calls.do"
    const auto constructed = ::app_src_checker_types_::classType(expression->type_, doof::unwrap_optional(symbol), resolvedTypeArgs);
#line 596 "/src/checker-calls.do"
    (expression->resolvedConstructedType = ::app_src_checker_symbols_::optionalResolvedType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(constructed)));
#line 597 "/src/checker-calls.do"
    const auto constructorMethod = ::app_src_checker_generics_::constructorForClass(constructed, state->result);
#line 598 "/src/checker-calls.do"
    if ((!doof::is_null(constructorMethod)) && !::app_src_checker_generics_::insideConstructorFactory(scope, constructed)) {
#line 599 "/src/checker-calls.do"
        (expression->resolvedConstructor = constructorMethod);
#line 600 "/src/checker-calls.do"
        validateConstructorVisibility(state, constructed, doof::unwrap_optional(constructorMethod), expression->span);
#line 601 "/src/checker-calls.do"
        const auto constructorType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_66 = constructorMethod->resolvedType; if (doof::is_null(_coalesce_66)) return ::app_src_checker_symbols_::methodSignature(doof::unwrap_optional(constructorMethod), ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), state->result); return doof::unwrap_optional(_coalesce_66); }();
#line 602 "/src/checker-calls.do"
        {
            auto _case_subject = constructorType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 604 "/src/checker-calls.do"
                std::shared_ptr<std::vector<std::string>> used = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 605 "/src/checker-calls.do"
                const auto& _iterable_68 = expression->args;
                for (const auto& property : *_iterable_68) {
#line 606 "/src/checker-calls.do"
                    if (::app_src_checker_symbols_::containsString(used, property->name)) {
#line 606 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Duplicate named argument '") + property->name) + std::string("'")), property->span);
                    }
#line 607 "/src/checker-calls.do"
                    used->push_back(property->name);
#line 608 "/src/checker-calls.do"
                    const auto parameterIndex = ::app_src_checker_symbols_::functionParameterIndex(function_->params, property->name);
#line 609 "/src/checker-calls.do"
                    if (parameterIndex < 0) {
#line 610 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Unknown named argument '") + property->name) + std::string("'")), property->span);
#line 611 "/src/checker-calls.do"
                        if (!doof::is_null(property->value)) {
#line 611 "/src/checker-calls.do"
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, std::monostate{})));
                        }
#line 612 "/src/checker-calls.do"
                        continue;
                    }
#line 614 "/src/checker-calls.do"
                    const auto parameterType = doof::array_at(function_->params, parameterIndex, "src/checker-calls", 614)->type_;
#line 615 "/src/checker-calls.do"
                    if (!doof::is_null(property->value)) {
#line 616 "/src/checker-calls.do"
                        (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, ::app_src_checker_symbols_::optionalResolvedType(parameterType))));
                    } else {
#line 618 "/src/checker-calls.do"
                        const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
#line 619 "/src/checker-calls.do"
                        if (doof::is_null(binding)) {
#line 619 "/src/checker-calls.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
#line 619 "/src/checker-calls.do"
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()));
                        } else {
#line 620 "/src/checker-calls.do"
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
                        }
                    }
#line 622 "/src/checker-calls.do"
                    if (!::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), parameterType)) {
#line 623 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(parameterType)), property->span);
                    }
                }
#line 626 "/src/checker-calls.do"
                const auto& _iterable_70 = function_->params;
                for (const auto& parameter : *_iterable_70) {
#line 627 "/src/checker-calls.do"
                    if (!parameter->hasDefault && !::app_src_checker_symbols_::hasObjectProperty(expression->args, parameter->name)) {
#line 628 "/src/checker-calls.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Missing required argument '") + parameter->name) + std::string("'")), expression->span);
                    }
                }
#line 631 "/src/checker-calls.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), function_->returnType);
        }
        else {
        }
        }
    }
#line 636 "/src/checker-calls.do"
    if (!doof::is_null(expression->resolvedClass)) {
#line 636 "/src/checker-calls.do"
        checkConstructionFields(state, expression, scope, constructed, doof::unwrap_optional(expression->resolvedClass));
    }
#line 637 "/src/checker-calls.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(constructed));
}
#line 640 "/src/checker-calls.do"
void validateConstructorVisibility(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::ClassType>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructor, ::app_src_ast_::SourceSpan span) {
#line 641 "/src/checker-calls.do"
    if (constructor->private_ && (owner->symbol->module != state->info->path)) {
#line 642 "/src/checker-calls.do"
        ::app_src_checker_common_::typeError(state, ((std::string("Constructor for \"") + owner->name) + std::string("\" is private")), span);
    }
}
#line 646 "/src/checker-calls.do"
void checkConstructionFields(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& constructed, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& declaration) {
#line 647 "/src/checker-calls.do"
    std::shared_ptr<std::vector<std::string>> used = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 648 "/src/checker-calls.do"
    const auto& _iterable_72 = expression->args;
    for (const auto& property : *_iterable_72) {
#line 649 "/src/checker-calls.do"
        if (::app_src_checker_symbols_::containsString(used, property->name)) {
#line 649 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, ((((std::string("Duplicate field '") + property->name) + std::string("' in ")) + declaration->name) + std::string(" construction")), property->span);
        }
#line 650 "/src/checker-calls.do"
        used->push_back(property->name);
#line 651 "/src/checker-calls.do"
        const auto field = constructionField(declaration, property->name);
#line 652 "/src/checker-calls.do"
        if ((doof::is_null(field) || field->static_) || field->const_) {
#line 653 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, (((std::string("Unknown field '") + property->name) + std::string("' for ")) + declaration->name), property->span);
#line 654 "/src/checker-calls.do"
            if (!doof::is_null(property->value)) {
#line 654 "/src/checker-calls.do"
                (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, std::monostate{})));
            } else {
#line 656 "/src/checker-calls.do"
                const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
#line 657 "/src/checker-calls.do"
                if (doof::is_null(binding)) {
#line 657 "/src/checker-calls.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
#line 657 "/src/checker-calls.do"
                    (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()));
                } else {
#line 658 "/src/checker-calls.do"
                    (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
                }
            }
#line 660 "/src/checker-calls.do"
            continue;
        }
#line 662 "/src/checker-calls.do"
        const auto expected = ::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(constructed), property->name, property->span, true);
#line 663 "/src/checker-calls.do"
        if (!doof::is_null(property->value)) {
#line 664 "/src/checker-calls.do"
            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, ::app_src_checker_symbols_::optionalResolvedType(expected))));
        } else {
#line 666 "/src/checker-calls.do"
            const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
#line 667 "/src/checker-calls.do"
            if (doof::is_null(binding)) {
#line 667 "/src/checker-calls.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
#line 667 "/src/checker-calls.do"
                (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()));
            } else {
#line 668 "/src/checker-calls.do"
                (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
            }
        }
#line 670 "/src/checker-calls.do"
        if (!::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), expected)) {
#line 671 "/src/checker-calls.do"
            ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(expected)), property->span);
        }
    }
#line 674 "/src/checker-calls.do"
    const auto& _iterable_74 = declaration->fields;
    for (const auto& field : *_iterable_74) {
#line 675 "/src/checker-calls.do"
        if ((field->static_ || field->const_) || (!doof::is_null(field->defaultValue))) {
#line 675 "/src/checker-calls.do"
            continue;
        }
#line 676 "/src/checker-calls.do"
        const auto& _iterable_76 = field->names;
        for (const auto& name : *_iterable_76) {
#line 677 "/src/checker-calls.do"
            if (!::app_src_checker_symbols_::containsString(used, name)) {
#line 677 "/src/checker-calls.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Missing required field '") + name) + std::string("'")), expression->span);
            }
        }
    }
}
#line 682 "/src/checker-calls.do"
std::shared_ptr<::app_src_ast_::ClassField> constructionField(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& declaration, const std::string& name) {
#line 683 "/src/checker-calls.do"
    const auto& _iterable_78 = declaration->fields;
    for (const auto& field : *_iterable_78) {
#line 684 "/src/checker-calls.do"
        const auto& _iterable_80 = field->names;
        for (const auto& fieldName : *_iterable_80) {
#line 684 "/src/checker-calls.do"
            if (fieldName == name) {
#line 684 "/src/checker-calls.do"
                return field;
            }
        }
    }
#line 686 "/src/checker-calls.do"
    return nullptr;
}
#line 689 "/src/checker-calls.do"
bool callableField(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& objectType, const std::string& property) {
#line 690 "/src/checker-calls.do"
    std::shared_ptr<::app_src_semantic_::Symbol> symbol = nullptr;
#line 691 "/src/checker-calls.do"
    {
        auto _case_subject = objectType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 692 "/src/checker-calls.do"
            (symbol = class_->symbol);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 693 "/src/checker-calls.do"
            (symbol = interface_->symbol);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 695 "/src/checker-calls.do"
            auto found = false;
#line 696 "/src/checker-calls.do"
            const auto& _iterable_82 = union_->types;
            for (const auto& member : *_iterable_82) {
#line 697 "/src/checker-calls.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 697 "/src/checker-calls.do"
                    continue;
                }
#line 698 "/src/checker-calls.do"
                (found = true);
#line 699 "/src/checker-calls.do"
                if (!callableField(state, member, property)) {
#line 699 "/src/checker-calls.do"
                    return false;
                }
            }
#line 701 "/src/checker-calls.do"
            return found;
    }
    else {
#line 703 "/src/checker-calls.do"
            return false;
    }
    }
#line 705 "/src/checker-calls.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
#line 706 "/src/checker-calls.do"
    if (doof::is_null(declaration)) {
#line 706 "/src/checker-calls.do"
        return false;
    }
#line 707 "/src/checker-calls.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 709 "/src/checker-calls.do"
            const auto& _iterable_84 = class_->fields;
            for (const auto& field : *_iterable_84) {
#line 710 "/src/checker-calls.do"
                const auto& _iterable_86 = field->names;
                for (const auto& name : *_iterable_86) {
#line 710 "/src/checker-calls.do"
                    if (name == property) {
#line 710 "/src/checker-calls.do"
                        return true;
                    }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 714 "/src/checker-calls.do"
            const auto& _iterable_88 = interface_->fields;
            for (const auto& field : *_iterable_88) {
#line 714 "/src/checker-calls.do"
                if (field->name == property) {
#line 714 "/src/checker-calls.do"
                    return true;
                }
            }
    }
    else {
    }
    }
#line 718 "/src/checker-calls.do"
    return false;
}
#line 1 "<doof-generated>"
}
