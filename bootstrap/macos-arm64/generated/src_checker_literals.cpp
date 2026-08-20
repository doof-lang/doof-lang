#include "src_checker_literals.hpp"

namespace app_src_checker_literals_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_expressions_;
using namespace ::app_src_checker_resolution_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkOmittedCollectionLiteral(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (static_cast<int32_t>((named->typeArgs)->size()) != 0) {
                return std::monostate{};
            }
            if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
                {
                    auto _case_subject = expression;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
                        const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
                        if (static_cast<int32_t>((array->elements)->size()) == 0) {
                            ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" element type from an empty set literal; provide a full ")) + named->name) + std::string("<T> annotation")), array->span);
                            return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::setType(::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlySet")))));
                        }
                        const auto inferred = checkArray(state, array, scope, std::monostate{});
                        {
                            auto _case_subject = inferred;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                                const auto& arrayType_ = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                                auto hasConcreteElement = true;
                                {
                                    auto _case_subject = arrayType_->elementType;
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
                                        (hasConcreteElement = false);
                                        ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" element type from this set literal; provide a full ")) + named->name) + std::string("<T> annotation")), array->span);
                                }
                                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                                        (hasConcreteElement = false);
                                        ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" element type from heterogeneous set elements; provide a full ")) + named->name) + std::string("<T> annotation")), array->span);
                                }
                                else {
                                }
                                }
                                if (hasConcreteElement && !::app_src_checker_types_::isSupportedHashCollectionType(arrayType_->elementType)) {
                                    ::app_src_checker_common_::typeError(state, ((std::string("Set element type \"") + ::app_src_checker_types_::typeName(arrayType_->elementType)) + std::string("\" is not supported; set elements must be byte, string, int, long, char, bool, or enum")), array->span);
                                }
                                return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::setType(arrayType_->elementType, (named->name == std::string("ReadonlySet")))));
                        }
                        else {
                                return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::setType(::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlySet")))));
                        }
                        }
                        doof::unreachable();
                }
                else {
                        ::app_src_checker_expressions_::checkExpression(state, expression, scope, std::monostate{});
                        ::app_src_checker_common_::typeError(state, ((std::string("Omitted type arguments for ") + named->name) + std::string(" require a same-site non-empty set literal")), std::visit([](auto&& _obj) { return _obj->span; }, expression));
                        return doof::optional_value(::app_src_checker_types_::setType(::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlySet"))));
                }
                }
                doof::unreachable();
            }
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
                {
                    auto _case_subject = expression;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
                        const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
                        if (static_cast<int32_t>((object->properties)->size()) == 0) {
                            ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" type arguments from an empty map literal; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                            return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::mapType(::app_src_checker_types_::unknownType(), ::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlyMap")))));
                        }
                        auto keyType = ::app_src_checker_types_::unknownType();
                        auto valueType = ::app_src_checker_types_::unknownType();
                        const auto& _iterable_2 = object->properties;
                        for (const auto& property : *_iterable_2) {
                            const auto propertyKeyType = (doof::is_null(property->key) ? ::app_src_checker_types_::primitive(std::string("string")) : ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->key), scope, std::monostate{}));
                            (keyType = ::app_src_checker_types_::joinTypes(keyType, propertyKeyType));
                            auto propertyType = ::app_src_checker_types_::unknownType();
                            if (!doof::is_null(property->value)) {
                                (propertyType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, std::monostate{}));
                            } else {
                                const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
                                if (doof::is_null(binding)) {
                                    ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
                                } else {
                                    (propertyType = binding->type_);
                                }
                            }
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(propertyType));
                            (valueType = ::app_src_checker_types_::joinTypes(valueType, propertyType));
                        }
                        {
                            auto _case_subject = keyType;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" key type from this map literal; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" key type from heterogeneous map keys; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else {
                                if (!::app_src_checker_types_::isSupportedHashCollectionType(keyType)) {
                                    ::app_src_checker_common_::typeError(state, ((std::string("Map key type \"") + ::app_src_checker_types_::typeName(keyType)) + std::string("\" is not supported; map keys must be byte, string, int, long, char, bool, or enum")), object->span);
                                }
                        }
                        }
                        {
                            auto _case_subject = valueType;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" type arguments from this map literal; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" value type from heterogeneous map values; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else {
                        }
                        }
                        return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::mapType(keyType, valueType, (named->name == std::string("ReadonlyMap")))));
                }
                else {
                        ::app_src_checker_expressions_::checkExpression(state, expression, scope, std::monostate{});
                        ::app_src_checker_common_::typeError(state, ((std::string("Omitted type arguments for ") + named->name) + std::string(" require a same-site non-empty map literal")), std::visit([](auto&& _obj) { return _obj->span; }, expression));
                        return doof::optional_value(::app_src_checker_types_::mapType(::app_src_checker_types_::unknownType(), ::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlyMap"))));
                }
                }
                doof::unreachable();
            }
    }
    else {
    }
    }
    return std::monostate{};
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkArray(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ArrayLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                const auto& _iterable_4 = expression->elements;
                for (const auto& item : *_iterable_4) {
                    const auto actual = ::app_src_checker_expressions_::checkExpression(state, item, scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::jsonValueType()));
                    if (!::app_src_checker_types_::isAssignable(actual, ::app_src_checker_types_::jsonValueType())) {
                        ::app_src_checker_common_::typeError(state, ((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to JsonValue")), std::visit([](auto&& _obj) { return _obj->span; }, item));
                    }
                }
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                if (containsJsonValue(state, union_)) {
                    const auto& _iterable_6 = expression->elements;
                    for (const auto& item : *_iterable_6) {
                        const auto actual = ::app_src_checker_expressions_::checkExpression(state, item, scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::jsonValueType()));
                        if (!::app_src_checker_types_::isAssignable(actual, ::app_src_checker_types_::jsonValueType())) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to JsonValue")), std::visit([](auto&& _obj) { return _obj->span; }, item));
                        }
                    }
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::jsonValueType());
                }
        }
        else {
        }
        }
    }
    if ((static_cast<int32_t>((expression->elements)->size()) == 0) && (!doof::is_null(expected))) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else {
        }
        }
    }
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedElement = std::monostate{};
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                (expectedElement = doof::optional_value(array->elementType));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
                (expectedElement = doof::optional_value(set->elementType));
        }
        else {
        }
        }
    }
    if (!doof::is_null(expectedElement)) {
        const auto& _iterable_8 = expression->elements;
        for (const auto& item : *_iterable_8) {
            const auto actual = ::app_src_checker_expressions_::checkExpression(state, item, scope, ::app_src_checker_symbols_::optionalResolvedType(doof::unwrap_optional(expectedElement)));
            if (!::app_src_checker_types_::isAssignable(actual, doof::unwrap_optional(expectedElement))) {
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expectedElement))), std::visit([](auto&& _obj) { return _obj->span; }, item));
            }
        }
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::arrayType(doof::unwrap_optional(expectedElement), array->readonly_));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::setType(doof::unwrap_optional(expectedElement), set->readonly_));
        }
        else {
        }
        }
    }
    auto element = ::app_src_checker_types_::unknownType();
    const auto& _iterable_10 = expression->elements;
    for (const auto& item : *_iterable_10) {
        (element = ::app_src_checker_types_::joinTypes(element, ::app_src_checker_expressions_::checkExpression(state, item, scope, std::monostate{})));
    }
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::arrayType(element, expression->readonly_));
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                auto recognized = 0;
                auto hasValue = false;
                auto hasError = false;
                const auto& _iterable_12 = expression->properties;
                for (const auto& property : *_iterable_12) {
                    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> propertyExpected = std::monostate{};
                    if (property->name == std::string("value")) {
                        (recognized = (recognized + 1));
                        (hasValue = true);
                        (propertyExpected = doof::optional_value(result->valueType));
                    } else if (property->name == std::string("error")) {
                        (recognized = (recognized + 1));
                        (hasError = true);
                        (propertyExpected = doof::optional_value(result->errorType));
                    }
                    if (!doof::is_null(property->value)) {
                        (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, propertyExpected)));
                    } else {
                        const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
                        if (doof::is_null(binding)) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()));
                        } else {
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
                        }
                    }
                    if ((!doof::is_null(propertyExpected)) && !::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), doof::unwrap_optional(propertyExpected))) {
                        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(propertyExpected))), property->span);
                    }
                }
                if (hasValue && hasError) {
                    ::app_src_checker_common_::typeError(state, std::string("Result object literal must contain either a 'value' field or an 'error' field, but not both"), expression->span);
                } else if (!hasValue && !hasError) {
                    ::app_src_checker_common_::typeError(state, std::string("Result object literal must contain a 'value' field or an 'error' field"), expression->span);
                } else if (recognized != static_cast<int32_t>((expression->properties)->size())) {
                    ::app_src_checker_common_::typeError(state, std::string("Result object literal only supports 'value' and 'error' fields"), expression->span);
                }
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                const auto checkedClass = checkClassObject(state, expression, scope, class_, false);
                if (!doof::is_null(checkedClass)) {
                    return doof::unwrap_optional(checkedClass);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                if (supportsUnionObjectInference(union_)) {
                    return checkUnionObject(state, expression, scope, union_);
                }
        }
        else {
        }
        }
    }
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedValue = std::monostate{};
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                (expectedValue = doof::optional_value(::app_src_checker_types_::jsonValueType()));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                if (containsJsonValue(state, union_)) {
                    (expectedValue = doof::optional_value(::app_src_checker_types_::jsonValueType()));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
                const auto& _iterable_14 = expression->properties;
                for (const auto& property : *_iterable_14) {
                    if (!doof::is_null(property->key)) {
                        const auto actualKey = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->key), scope, ::app_src_checker_symbols_::optionalResolvedType(map->keyType));
                        if (!::app_src_checker_types_::isAssignable(actualKey, map->keyType)) {
                            ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actualKey)) + std::string(" to map key type ")) + ::app_src_checker_types_::typeName(map->keyType)), property->span);
                        }
                    } else if (!::app_src_checker_types_::sameType(map->keyType, ::app_src_checker_types_::primitive(std::string("string")))) {
                        ::app_src_checker_common_::typeError(state, (std::string("Cannot assign string to map key type ") + ::app_src_checker_types_::typeName(map->keyType)), property->span);
                    }
                }
                (expectedValue = doof::optional_value(map->valueType));
        }
        else {
        }
        }
    }
    const auto& _iterable_16 = expression->properties;
    for (const auto& property : *_iterable_16) {
        if (!doof::is_null(property->value)) {
            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, expectedValue)));
            if ((!doof::is_null(expectedValue)) && !::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), doof::unwrap_optional(expectedValue))) {
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expectedValue))), property->span);
            }
        }
    }
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                if (containsJsonValue(state, union_)) {
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::jsonValueType());
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else {
        }
        }
    }
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::mapType(::app_src_checker_types_::primitive(std::string("string")), ::app_src_checker_types_::jsonValueType(), false));
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkClassObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& class_, bool structural) {
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
    if (doof::is_null(declaration)) {
        return std::monostate{};
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            (expression->resolvedClass = classDeclaration);
            const auto& _iterable_18 = expression->properties;
            for (const auto& property : *_iterable_18) {
                const auto field = ::app_src_checker_interfaces_::findClassField(classDeclaration->fields, property->name);
                if ((doof::is_null(field) || field->static_) || (!structural && field->const_)) {
                    ::app_src_checker_common_::typeError(state, (((std::string("Unknown field '") + property->name) + std::string("' for ")) + class_->name), property->span);
                    decorateObjectProperty(state, property, scope, std::monostate{});
                    continue;
                }
                const auto fieldType = ::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), property->name, property->span);
                decorateObjectProperty(state, property, scope, ::app_src_checker_symbols_::optionalResolvedType(fieldType));
                if (!::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), fieldType)) {
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(fieldType)), property->span);
                }
                if (structural && field->const_) {
                    if ((doof::is_null(property->value) || doof::is_null(field->defaultValue)) || !sameFixedFieldValue(doof::unwrap_optional(property->value), doof::unwrap_optional(field->defaultValue))) {
                        ::app_src_checker_common_::typeError(state, ((std::string("Field '") + property->name) + std::string("' must match its literal-valued declaration")), property->span);
                    }
                }
            }
            const auto& _iterable_20 = classDeclaration->fields;
            for (const auto& field : *_iterable_20) {
                if (field->static_ || (!structural && field->const_)) {
                    continue;
                }
                const auto& _iterable_22 = field->names;
                for (const auto& name : *_iterable_22) {
                    const auto required = (field->const_ || doof::is_null(field->defaultValue));
                    if (required && !::app_src_checker_symbols_::hasObjectProperty(expression->properties, name)) {
                        ::app_src_checker_common_::typeError(state, ((std::string("Missing required field '") + name) + std::string("'")), expression->span);
                    }
                }
            }
            return doof::optional_value(::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_)));
    }
    else {
    }
    }
    return std::monostate{};
}
bool supportsUnionObjectInference(const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
    auto hasNominal = false;
    const auto& _iterable_24 = union_->types;
    for (const auto& member : *_iterable_24) {
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                return false;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                return false;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                (hasNominal = true);
        }
        else {
        }
        }
    }
    return hasNominal;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkUnionObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
    if (!doof::is_null(expression->spread)) {
        decorateUnresolvedObject(state, expression, scope);
        ::app_src_checker_common_::typeError(state, std::string("Cannot infer a sum type member from an object literal with spread fields; use explicit Type { ... } construction"), expression->span);
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ClassType>>> matches = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ClassType>>>(std::vector<std::shared_ptr<::app_src_semantic_::ClassType>>{});
    std::shared_ptr<std::vector<std::string>> nominalNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_26 = union_->types;
    for (const auto& member : *_iterable_26) {
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                nominalNames->push_back(class_->name);
                if (objectShapeMatchesClass(state, expression, class_)) {
                    matches->push_back(class_);
                }
        }
        else {
        }
        }
    }
    if (static_cast<int32_t>((matches)->size()) == 1) {
        const auto checked = checkClassObject(state, expression, scope, doof::array_at(matches, 0, "src/checker-literals", 331), true);
        if (!doof::is_null(checked)) {
            return doof::unwrap_optional(checked);
        }
    }
    decorateUnresolvedObject(state, expression, scope);
    if (static_cast<int32_t>((matches)->size()) == 0) {
        ::app_src_checker_common_::typeError(state, ((((std::string("Object literal does not match any constructible member of ") + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) + std::string("; candidates: ")) + joinNames(nominalNames)) + std::string(". Use explicit Type { ... } construction")), expression->span);
    } else {
        std::shared_ptr<std::vector<std::string>> matchingNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_28 = matches;
        for (const auto& match : *_iterable_28) {
            matchingNames->push_back(match->name);
        }
        ::app_src_checker_common_::typeError(state, ((((std::string("Ambiguous object literal for ") + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) + std::string("; matching members: ")) + joinNames(matchingNames)) + std::string(". Use explicit Type { ... } construction")), expression->span);
    }
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
}
bool objectShapeMatchesClass(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::ClassType>& class_) {
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
    if (doof::is_null(declaration)) {
        return false;
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            const auto& _iterable_30 = expression->properties;
            for (const auto& property : *_iterable_30) {
                if (!doof::is_null(property->key)) {
                    return false;
                }
                const auto field = ::app_src_checker_interfaces_::findClassField(classDeclaration->fields, property->name);
                if (doof::is_null(field) || field->static_) {
                    return false;
                }
            }
            const auto& _iterable_32 = classDeclaration->fields;
            for (const auto& field : *_iterable_32) {
                if (field->static_) {
                    continue;
                }
                const auto& _iterable_34 = field->names;
                for (const auto& name : *_iterable_34) {
                    if ((field->const_ || doof::is_null(field->defaultValue)) && !::app_src_checker_symbols_::hasObjectProperty(expression->properties, name)) {
                        return false;
                    }
                }
            }
            return true;
    }
    else {
    }
    }
    return false;
}
void decorateObjectProperty(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectProperty>& property, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    if (!doof::is_null(property->key)) {
        ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->key), scope, std::monostate{});
    }
    if (!doof::is_null(property->value)) {
        (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, expected)));
    } else {
        const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
        if (doof::is_null(binding)) {
            ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()));
        } else {
            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
        }
    }
}
void decorateUnresolvedObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
    if (!doof::is_null(expression->spread)) {
        ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(expression->spread), scope, std::monostate{});
    }
    const auto& _iterable_36 = expression->properties;
    for (const auto& property : *_iterable_36) {
        decorateObjectProperty(state, property, scope, std::monostate{});
    }
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
std::string joinNames(const std::shared_ptr<std::vector<std::string>>& names) {
    auto result = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((names)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        (result = (result + doof::array_at(names, i, "src/checker-literals", 438)));
    }
    return result;
}
bool containsJsonValue(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
    const auto& _iterable_39 = union_->types;
    for (const auto& member : *_iterable_39) {
        if (::app_src_checker_types_::isJsonValueType(member)) {
            return true;
        }
    }
    return false;
}
}
