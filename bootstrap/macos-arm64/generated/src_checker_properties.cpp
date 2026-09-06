#include "src_checker_properties.hpp"

namespace app_src_checker_properties_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_expressions_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_interfaces_;
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkPropertyValue(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectProperty>& property, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> actual = ::app_src_checker_types_::unknownType();
    if (!doof::is_null(property->value)) {
        static_cast<void>((actual = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, expected)));
    } else {
        const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
        if (doof::is_null(binding)) {
            ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
        } else {
            static_cast<void>((property->resolvedBinding = binding));
            static_cast<void>((actual = binding->type_));
        }
    }
    static_cast<void>((property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(actual)));
    return actual;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkAssignableProperty(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectProperty>& property, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    const auto actual = checkPropertyValue(state, property, scope, expected);
    if ((!doof::is_null(expected)) && !::app_src_checker_interfaces_::isAssignableWithInterfaces(state->result, actual, doof::unwrap_optional(expected))) {
        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expected))), property->span);
    }
    return actual;
}
bool sameFixedFieldValue(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& actual, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expected) {
    {
        auto _case_subject = expected;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& expectedString = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
                    const auto& actualString = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
                    return (actualString->value == expectedString->value);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            const auto& expectedInt = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
                    const auto& actualInt = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
                    return (actualInt->value == expectedInt->value);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            const auto& expectedLong = std::get<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
                    const auto& actualLong = std::get<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject);
                    return (actualLong->value == expectedLong->value);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            const auto& expectedFloat = std::get<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
                    const auto& actualFloat = std::get<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject);
                    return (actualFloat->value == expectedFloat->value);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            const auto& expectedDouble = std::get<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
                    const auto& actualDouble = std::get<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject);
                    return (actualDouble->value == expectedDouble->value);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
            const auto& expectedChar = std::get<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
                    const auto& actualChar = std::get<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject);
                    return (actualChar->value == expectedChar->value);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
            const auto& expectedBool = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
                    const auto& actualBool = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
                    return (actualBool->value == expectedBool->value);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
                    return true;
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& expectedMember = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                    const auto& actualMember = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                    return (actualMember->property == expectedMember->property);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
                    const auto& actualDot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
                    return (actualDot->name == expectedMember->property);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& expectedDot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                    const auto& actualMember = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                    return (actualMember->property == expectedDot->name);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
                    const auto& actualDot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
                    return (actualDot->name == expectedDot->name);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& expectedUnary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
                    const auto& actualUnary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
                    return ((actualUnary->operator_ == expectedUnary->operator_) && sameFixedFieldValue(actualUnary->operand, expectedUnary->operand));
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
}
