#include "src_checker_arguments.hpp"

namespace app_src_checker_arguments_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_expressions_;
using namespace ::app_src_checker_properties_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_common_;

std::shared_ptr<std::vector<std::shared_ptr<SuppliedArgument>>> callArguments(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>>& args) {
    std::shared_ptr<std::vector<std::shared_ptr<SuppliedArgument>>> result = std::make_shared<std::vector<std::shared_ptr<SuppliedArgument>>>(std::vector<std::shared_ptr<SuppliedArgument>>{});
    const auto& _iterable_2 = args;
    for (const auto& argument : *_iterable_2) {
        result->push_back(std::make_shared<SuppliedArgument>(argument->name, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(argument->value), nullptr, argument->span));
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<SuppliedArgument>>> propertyArguments(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>>& properties) {
    std::shared_ptr<std::vector<std::shared_ptr<SuppliedArgument>>> result = std::make_shared<std::vector<std::shared_ptr<SuppliedArgument>>>(std::vector<std::shared_ptr<SuppliedArgument>>{});
    const auto& _iterable_4 = properties;
    for (const auto& property : *_iterable_4) {
        result->push_back(std::make_shared<SuppliedArgument>(property->name, std::monostate{}, property, property->span));
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<SuppliedArgument>>> positionalArguments(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>& values) {
    std::shared_ptr<std::vector<std::shared_ptr<SuppliedArgument>>> result = std::make_shared<std::vector<std::shared_ptr<SuppliedArgument>>>(std::vector<std::shared_ptr<SuppliedArgument>>{});
    const auto& _iterable_6 = values;
    for (const auto& value : *_iterable_6) {
        result->push_back(std::make_shared<SuppliedArgument>(std::nullopt, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(value), nullptr, std::visit([](auto&& _obj) { return _obj->span; }, value)));
    }
    return result;
}
void checkArguments(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<std::vector<std::shared_ptr<SuppliedArgument>>>& args, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>& params, const std::shared_ptr<::app_src_semantic_::Scope>& scope, ::app_src_ast_::SourceSpan span, const std::string& countSubject, const std::string& argumentPrefix, bool contextual, bool validateTypes, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>& spread, std::optional<::app_src_ast_::SourceSpan> spreadSpan, bool namedSyntax) {
    auto named = namedSyntax;
    const auto& _iterable_8 = args;
    for (const auto& argument : *_iterable_8) {
        if (!doof::is_null(argument->name)) {
            static_cast<void>((named = true));
        }
    }
    std::shared_ptr<std::vector<std::string>> used = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    if (!named) {
        auto requiredCount = 0;
        for (int32_t i = 0; i < static_cast<int32_t>((params)->size()); ++i) {
            if (!doof::array_at(params, i, "src/checker-arguments", 49)->hasDefault) {
                static_cast<void>((requiredCount = (i + 1)));
            }
        }
        if ((static_cast<int32_t>((args)->size()) < requiredCount) || (static_cast<int32_t>((args)->size()) > static_cast<int32_t>((params)->size()))) {
            const auto range = ((requiredCount == static_cast<int32_t>((params)->size())) ? doof::to_string(requiredCount) : ((doof::to_string(requiredCount) + std::string("-")) + doof::to_string(static_cast<int32_t>((params)->size()))));
            const auto prefix = ((countSubject == std::string("")) ? std::string("Expected ") : (countSubject + std::string(" expects ")));
            const auto suffix = ((countSubject == std::string("")) ? std::string(" argument(s)") : std::string(" constructor argument(s)"));
            ::app_src_checker_common_::typeError(state, ((((prefix + range) + suffix) + std::string(" but got ")) + doof::to_string(static_cast<int32_t>((args)->size()))), span);
        }
    }
    for (int32_t i = 0; i < static_cast<int32_t>((args)->size()); ++i) {
        const auto argument = doof::array_at(args, i, "src/checker-arguments", 58);
        auto index = i;
        if (named) {
            if (doof::is_null(argument->name)) {
                ::app_src_checker_common_::typeError(state, ((countSubject == std::string("")) ? std::string("Named calls cannot contain positional arguments") : std::string("Named construction cannot contain positional arguments")), argument->span);
                checkArgumentValue(state, argument, scope, std::monostate{});
                continue;
            }
            static_cast<void>((index = ::app_src_checker_symbols_::functionParameterIndex(params, doof::unwrap_optional(argument->name))));
            if (index < 0) {
                ::app_src_checker_common_::typeError(state, ((std::string("Unknown named argument '") + doof::unwrap_optional(argument->name)) + std::string("'")), argument->span);
                checkArgumentValue(state, argument, scope, std::monostate{});
                continue;
            }
            if (::app_src_checker_symbols_::containsString(used, doof::unwrap_optional(argument->name))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Duplicate named argument '") + doof::unwrap_optional(argument->name)) + std::string("'")), argument->span);
            }
            used->push_back(doof::unwrap_optional(argument->name));
        }
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
        if (index < static_cast<int32_t>((params)->size())) {
            static_cast<void>((expected = doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::array_at(params, index, "src/checker-arguments", 76)->type_)));
        }
        const auto actual = checkArgumentValue(state, argument, scope, [&]() -> std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (contextual) { return expected; } return std::monostate{}; }());
        if ((validateTypes && (!doof::is_null(expected))) && !::app_src_checker_interfaces_::isAssignableWithInterfaces(state->result, actual, doof::unwrap_optional(expected))) {
            const auto label = (named ? ((std::string("'") + doof::unwrap_optional(argument->name)) + std::string("'")) : doof::to_string((i + 1)));
            ::app_src_checker_common_::typeError(state, ((((((argumentPrefix + std::string(" ")) + label) + std::string(" has type ")) + ::app_src_checker_types_::typeName(actual)) + std::string("; expected ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expected))), argument->span);
        }
    }
    if (named) {
        const auto& _iterable_13 = params;
        for (const auto& parameter : *_iterable_13) {
            if (::app_src_checker_symbols_::containsString(used, parameter->name)) {
                continue;
            }
            const auto spreadIndex = ::app_src_checker_symbols_::functionParameterIndex(spread, parameter->name);
            if (spreadIndex >= 0) {
                const auto actual = doof::array_at(spread, spreadIndex, "src/checker-arguments", 88)->type_;
                if (!::app_src_checker_interfaces_::isAssignableWithInterfaces(state->result, actual, parameter->type_)) {
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign spread field ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to ")) + ::app_src_checker_types_::typeName(parameter->type_)), [&]() -> ::app_src_ast_::SourceSpan { auto _coalesce_11 = spreadSpan; if (doof::is_null(_coalesce_11)) return span; return doof::unwrap_optional(_coalesce_11); }());
                }
            } else if (!parameter->hasDefault) {
                ::app_src_checker_common_::typeError(state, ((std::string("Missing required argument '") + parameter->name) + std::string("'")), span);
            }
        }
    }
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkArgumentValue(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<SuppliedArgument>& argument, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    if (!doof::is_null(argument->property)) {
        return ::app_src_checker_properties_::checkPropertyValue(state, doof::unwrap_optional(argument->property), scope, expected);
    }
    return ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(argument->value), scope, expected);
}
}
