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
#line 48 "/src/checker-literals.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkOmittedCollectionLiteral(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 49 "/src/checker-literals.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 51 "/src/checker-literals.do"
            if (static_cast<int32_t>((named->typeArgs)->size()) != 0) {
#line 51 "/src/checker-literals.do"
                return std::monostate{};
            }
#line 52 "/src/checker-literals.do"
            if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
#line 53 "/src/checker-literals.do"
                {
                    auto _case_subject = expression;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
                        const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 55 "/src/checker-literals.do"
                        if (static_cast<int32_t>((array->elements)->size()) == 0) {
#line 56 "/src/checker-literals.do"
                            ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" element type from an empty set literal; provide a full ")) + named->name) + std::string("<T> annotation")), array->span);
#line 57 "/src/checker-literals.do"
                            return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::setType(::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlySet")))));
                        }
#line 59 "/src/checker-literals.do"
                        const auto inferred = checkArray(state, array, scope, std::monostate{});
#line 60 "/src/checker-literals.do"
                        {
                            auto _case_subject = inferred;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                                const auto& arrayType_ = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 62 "/src/checker-literals.do"
                                auto hasConcreteElement = true;
#line 63 "/src/checker-literals.do"
                                {
                                    auto _case_subject = arrayType_->elementType;
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 64 "/src/checker-literals.do"
                                        (hasConcreteElement = false);
#line 64 "/src/checker-literals.do"
                                        ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" element type from this set literal; provide a full ")) + named->name) + std::string("<T> annotation")), array->span);
                                }
                                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
#line 65 "/src/checker-literals.do"
                                        (hasConcreteElement = false);
#line 65 "/src/checker-literals.do"
                                        ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" element type from heterogeneous set elements; provide a full ")) + named->name) + std::string("<T> annotation")), array->span);
                                }
                                else {
                                }
                                }
#line 68 "/src/checker-literals.do"
                                if (hasConcreteElement && !::app_src_checker_types_::isSupportedHashCollectionType(arrayType_->elementType)) {
#line 69 "/src/checker-literals.do"
                                    ::app_src_checker_common_::typeError(state, ((std::string("Set element type \"") + ::app_src_checker_types_::typeName(arrayType_->elementType)) + std::string("\" is not supported; set elements must be byte, string, int, long, char, bool, or enum")), array->span);
                                }
#line 71 "/src/checker-literals.do"
                                return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::setType(arrayType_->elementType, (named->name == std::string("ReadonlySet")))));
                        }
                        else {
#line 73 "/src/checker-literals.do"
                                return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::setType(::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlySet")))));
                        }
                        }
                        doof::unreachable();
                }
                else {
#line 77 "/src/checker-literals.do"
                        ::app_src_checker_expressions_::checkExpression(state, expression, scope, std::monostate{});
#line 78 "/src/checker-literals.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Omitted type arguments for ") + named->name) + std::string(" require a same-site non-empty set literal")), std::visit([](auto&& _obj) { return _obj->span; }, expression));
#line 79 "/src/checker-literals.do"
                        return doof::optional_value(::app_src_checker_types_::setType(::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlySet"))));
                }
                }
                doof::unreachable();
            }
#line 83 "/src/checker-literals.do"
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
#line 84 "/src/checker-literals.do"
                {
                    auto _case_subject = expression;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
                        const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 86 "/src/checker-literals.do"
                        if (static_cast<int32_t>((object->properties)->size()) == 0) {
#line 87 "/src/checker-literals.do"
                            ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" type arguments from an empty map literal; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
#line 88 "/src/checker-literals.do"
                            return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::mapType(::app_src_checker_types_::unknownType(), ::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlyMap")))));
                        }
#line 90 "/src/checker-literals.do"
                        auto keyType = ::app_src_checker_types_::unknownType();
#line 91 "/src/checker-literals.do"
                        auto valueType = ::app_src_checker_types_::unknownType();
#line 92 "/src/checker-literals.do"
                        const auto& _iterable_2 = object->properties;
                        for (const auto& property : *_iterable_2) {
#line 93 "/src/checker-literals.do"
                            const auto propertyKeyType = (doof::is_null(property->key) ? ::app_src_checker_types_::primitive(std::string("string")) : ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->key), scope, std::monostate{}));
#line 94 "/src/checker-literals.do"
                            (keyType = ::app_src_checker_types_::joinTypes(keyType, propertyKeyType));
#line 95 "/src/checker-literals.do"
                            auto propertyType = ::app_src_checker_types_::unknownType();
#line 96 "/src/checker-literals.do"
                            if (!doof::is_null(property->value)) {
#line 96 "/src/checker-literals.do"
                                (propertyType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, std::monostate{}));
                            } else {
#line 98 "/src/checker-literals.do"
                                const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
#line 99 "/src/checker-literals.do"
                                if (doof::is_null(binding)) {
#line 99 "/src/checker-literals.do"
                                    ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
                                } else {
#line 100 "/src/checker-literals.do"
                                    (propertyType = binding->type_);
                                }
                            }
#line 102 "/src/checker-literals.do"
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(propertyType));
#line 103 "/src/checker-literals.do"
                            (valueType = ::app_src_checker_types_::joinTypes(valueType, propertyType));
                        }
#line 105 "/src/checker-literals.do"
                        {
                            auto _case_subject = keyType;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 106 "/src/checker-literals.do"
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" key type from this map literal; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
#line 107 "/src/checker-literals.do"
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" key type from heterogeneous map keys; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else {
#line 109 "/src/checker-literals.do"
                                if (!::app_src_checker_types_::isSupportedHashCollectionType(keyType)) {
#line 109 "/src/checker-literals.do"
                                    ::app_src_checker_common_::typeError(state, ((std::string("Map key type \"") + ::app_src_checker_types_::typeName(keyType)) + std::string("\" is not supported; map keys must be byte, string, int, long, char, bool, or enum")), object->span);
                                }
                        }
                        }
#line 112 "/src/checker-literals.do"
                        {
                            auto _case_subject = valueType;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 113 "/src/checker-literals.do"
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" type arguments from this map literal; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
#line 114 "/src/checker-literals.do"
                                ::app_src_checker_common_::typeError(state, ((((std::string("Cannot infer ") + named->name) + std::string(" value type from heterogeneous map values; provide a full ")) + named->name) + std::string("<K, V> annotation")), object->span);
                        }
                        else {
                        }
                        }
#line 117 "/src/checker-literals.do"
                        return doof::optional_value(::app_src_checker_common_::finish(state, expression, ::app_src_checker_types_::mapType(keyType, valueType, (named->name == std::string("ReadonlyMap")))));
                }
                else {
#line 120 "/src/checker-literals.do"
                        ::app_src_checker_expressions_::checkExpression(state, expression, scope, std::monostate{});
#line 121 "/src/checker-literals.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Omitted type arguments for ") + named->name) + std::string(" require a same-site non-empty map literal")), std::visit([](auto&& _obj) { return _obj->span; }, expression));
#line 122 "/src/checker-literals.do"
                        return doof::optional_value(::app_src_checker_types_::mapType(::app_src_checker_types_::unknownType(), ::app_src_checker_types_::unknownType(), (named->name == std::string("ReadonlyMap"))));
                }
                }
                doof::unreachable();
            }
    }
    else {
    }
    }
#line 129 "/src/checker-literals.do"
    return std::monostate{};
}
#line 132 "/src/checker-literals.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkArray(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ArrayLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 133 "/src/checker-literals.do"
    if (!doof::is_null(expected)) {
#line 134 "/src/checker-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 136 "/src/checker-literals.do"
                const auto& _iterable_4 = expression->elements;
                for (const auto& item : *_iterable_4) {
#line 137 "/src/checker-literals.do"
                    const auto actual = ::app_src_checker_expressions_::checkExpression(state, item, scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::jsonValueType()));
#line 138 "/src/checker-literals.do"
                    if (!::app_src_checker_types_::isAssignable(actual, ::app_src_checker_types_::jsonValueType())) {
#line 138 "/src/checker-literals.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to JsonValue")), std::visit([](auto&& _obj) { return _obj->span; }, item));
                    }
                }
#line 140 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 143 "/src/checker-literals.do"
                if (containsJsonValue(state, union_)) {
#line 144 "/src/checker-literals.do"
                    const auto& _iterable_6 = expression->elements;
                    for (const auto& item : *_iterable_6) {
#line 145 "/src/checker-literals.do"
                        const auto actual = ::app_src_checker_expressions_::checkExpression(state, item, scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::jsonValueType()));
#line 146 "/src/checker-literals.do"
                        if (!::app_src_checker_types_::isAssignable(actual, ::app_src_checker_types_::jsonValueType())) {
#line 146 "/src/checker-literals.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to JsonValue")), std::visit([](auto&& _obj) { return _obj->span; }, item));
                        }
                    }
#line 148 "/src/checker-literals.do"
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::jsonValueType());
                }
        }
        else {
        }
        }
    }
#line 154 "/src/checker-literals.do"
    if ((static_cast<int32_t>((expression->elements)->size()) == 0) && (!doof::is_null(expected))) {
#line 155 "/src/checker-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 156 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
#line 157 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else {
        }
        }
    }
#line 161 "/src/checker-literals.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedElement = std::monostate{};
#line 162 "/src/checker-literals.do"
    if (!doof::is_null(expected)) {
#line 163 "/src/checker-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 164 "/src/checker-literals.do"
                (expectedElement = doof::optional_value(array->elementType));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 165 "/src/checker-literals.do"
                (expectedElement = doof::optional_value(set->elementType));
        }
        else {
        }
        }
    }
#line 169 "/src/checker-literals.do"
    if (!doof::is_null(expectedElement)) {
#line 170 "/src/checker-literals.do"
        const auto& _iterable_8 = expression->elements;
        for (const auto& item : *_iterable_8) {
#line 171 "/src/checker-literals.do"
            const auto actual = ::app_src_checker_expressions_::checkExpression(state, item, scope, ::app_src_checker_symbols_::optionalResolvedType(doof::unwrap_optional(expectedElement)));
#line 172 "/src/checker-literals.do"
            if (!::app_src_checker_types_::isAssignable(actual, doof::unwrap_optional(expectedElement))) {
#line 172 "/src/checker-literals.do"
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actual)) + std::string(" to ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expectedElement))), std::visit([](auto&& _obj) { return _obj->span; }, item));
            }
        }
#line 174 "/src/checker-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 175 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::arrayType(doof::unwrap_optional(expectedElement), array->readonly_));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 176 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::setType(doof::unwrap_optional(expectedElement), set->readonly_));
        }
        else {
        }
        }
    }
#line 180 "/src/checker-literals.do"
    auto element = ::app_src_checker_types_::unknownType();
#line 181 "/src/checker-literals.do"
    const auto& _iterable_10 = expression->elements;
    for (const auto& item : *_iterable_10) {
#line 181 "/src/checker-literals.do"
        (element = ::app_src_checker_types_::joinTypes(element, ::app_src_checker_expressions_::checkExpression(state, item, scope, std::monostate{})));
    }
#line 182 "/src/checker-literals.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::arrayType(element, expression->readonly_));
}
#line 185 "/src/checker-literals.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 186 "/src/checker-literals.do"
    if (!doof::is_null(expected)) {
#line 187 "/src/checker-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 189 "/src/checker-literals.do"
                auto recognized = 0;
#line 190 "/src/checker-literals.do"
                auto hasValue = false;
#line 191 "/src/checker-literals.do"
                auto hasError = false;
#line 192 "/src/checker-literals.do"
                const auto& _iterable_12 = expression->properties;
                for (const auto& property : *_iterable_12) {
#line 193 "/src/checker-literals.do"
                    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> propertyExpected = std::monostate{};
#line 194 "/src/checker-literals.do"
                    if (property->name == std::string("value")) {
#line 194 "/src/checker-literals.do"
                        (recognized = (recognized + 1));
#line 194 "/src/checker-literals.do"
                        (hasValue = true);
#line 194 "/src/checker-literals.do"
                        (propertyExpected = doof::optional_value(result->valueType));
                    } else if (property->name == std::string("error")) {
#line 195 "/src/checker-literals.do"
                        (recognized = (recognized + 1));
#line 195 "/src/checker-literals.do"
                        (hasError = true);
#line 195 "/src/checker-literals.do"
                        (propertyExpected = doof::optional_value(result->errorType));
                    }
#line 196 "/src/checker-literals.do"
                    if (!doof::is_null(property->value)) {
#line 197 "/src/checker-literals.do"
                        (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, propertyExpected)));
                    } else {
#line 199 "/src/checker-literals.do"
                        const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
#line 200 "/src/checker-literals.do"
                        if (doof::is_null(binding)) {
#line 200 "/src/checker-literals.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
#line 200 "/src/checker-literals.do"
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()));
                        } else {
#line 201 "/src/checker-literals.do"
                            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
                        }
                    }
#line 203 "/src/checker-literals.do"
                    if ((!doof::is_null(propertyExpected)) && !::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), doof::unwrap_optional(propertyExpected))) {
#line 204 "/src/checker-literals.do"
                        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(propertyExpected))), property->span);
                    }
                }
#line 207 "/src/checker-literals.do"
                if (hasValue && hasError) {
#line 207 "/src/checker-literals.do"
                    ::app_src_checker_common_::typeError(state, std::string("Result object literal must contain either a 'value' field or an 'error' field, but not both"), expression->span);
                } else if (!hasValue && !hasError) {
#line 208 "/src/checker-literals.do"
                    ::app_src_checker_common_::typeError(state, std::string("Result object literal must contain a 'value' field or an 'error' field"), expression->span);
                } else if (recognized != static_cast<int32_t>((expression->properties)->size())) {
#line 209 "/src/checker-literals.do"
                    ::app_src_checker_common_::typeError(state, std::string("Result object literal only supports 'value' and 'error' fields"), expression->span);
                }
#line 210 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 213 "/src/checker-literals.do"
                const auto checkedClass = checkClassObject(state, expression, scope, class_, false);
#line 214 "/src/checker-literals.do"
                if (!doof::is_null(checkedClass)) {
#line 214 "/src/checker-literals.do"
                    return doof::unwrap_optional(checkedClass);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 217 "/src/checker-literals.do"
                if (supportsUnionObjectInference(union_)) {
#line 218 "/src/checker-literals.do"
                    return checkUnionObject(state, expression, scope, union_);
                }
        }
        else {
        }
        }
    }
#line 224 "/src/checker-literals.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedValue = std::monostate{};
#line 225 "/src/checker-literals.do"
    if (!doof::is_null(expected)) {
#line 226 "/src/checker-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 227 "/src/checker-literals.do"
                (expectedValue = doof::optional_value(::app_src_checker_types_::jsonValueType()));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 229 "/src/checker-literals.do"
                if (containsJsonValue(state, union_)) {
#line 229 "/src/checker-literals.do"
                    (expectedValue = doof::optional_value(::app_src_checker_types_::jsonValueType()));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 232 "/src/checker-literals.do"
                const auto& _iterable_14 = expression->properties;
                for (const auto& property : *_iterable_14) {
#line 233 "/src/checker-literals.do"
                    if (!doof::is_null(property->key)) {
#line 234 "/src/checker-literals.do"
                        const auto actualKey = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->key), scope, ::app_src_checker_symbols_::optionalResolvedType(map->keyType));
#line 235 "/src/checker-literals.do"
                        if (!::app_src_checker_types_::isAssignable(actualKey, map->keyType)) {
#line 235 "/src/checker-literals.do"
                            ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(actualKey)) + std::string(" to map key type ")) + ::app_src_checker_types_::typeName(map->keyType)), property->span);
                        }
                    } else if (!::app_src_checker_types_::sameType(map->keyType, ::app_src_checker_types_::primitive(std::string("string")))) {
#line 237 "/src/checker-literals.do"
                        ::app_src_checker_common_::typeError(state, (std::string("Cannot assign string to map key type ") + ::app_src_checker_types_::typeName(map->keyType)), property->span);
                    }
                }
#line 240 "/src/checker-literals.do"
                (expectedValue = doof::optional_value(map->valueType));
        }
        else {
        }
        }
    }
#line 245 "/src/checker-literals.do"
    const auto& _iterable_16 = expression->properties;
    for (const auto& property : *_iterable_16) {
#line 246 "/src/checker-literals.do"
        if (!doof::is_null(property->value)) {
#line 247 "/src/checker-literals.do"
            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, expectedValue)));
#line 248 "/src/checker-literals.do"
            if ((!doof::is_null(expectedValue)) && !::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), doof::unwrap_optional(expectedValue))) {
#line 249 "/src/checker-literals.do"
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(expectedValue))), property->span);
            }
        }
    }
#line 253 "/src/checker-literals.do"
    if (!doof::is_null(expected)) {
#line 254 "/src/checker-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 255 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 256 "/src/checker-literals.do"
                if (containsJsonValue(state, union_)) {
#line 256 "/src/checker-literals.do"
                    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::jsonValueType());
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 257 "/src/checker-literals.do"
                return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::unwrap_optional(expected));
        }
        else {
        }
        }
    }
#line 261 "/src/checker-literals.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), ::app_src_checker_types_::mapType(::app_src_checker_types_::primitive(std::string("string")), ::app_src_checker_types_::jsonValueType(), false));
}
#line 264 "/src/checker-literals.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkClassObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& class_, bool structural) {
#line 265 "/src/checker-literals.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
#line 266 "/src/checker-literals.do"
    if (doof::is_null(declaration)) {
#line 266 "/src/checker-literals.do"
        return std::monostate{};
    }
#line 267 "/src/checker-literals.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 269 "/src/checker-literals.do"
            (expression->resolvedClass = classDeclaration);
#line 270 "/src/checker-literals.do"
            const auto& _iterable_18 = expression->properties;
            for (const auto& property : *_iterable_18) {
#line 271 "/src/checker-literals.do"
                const auto field = ::app_src_checker_interfaces_::findClassField(classDeclaration->fields, property->name);
#line 272 "/src/checker-literals.do"
                if ((doof::is_null(field) || field->static_) || (!structural && field->const_)) {
#line 273 "/src/checker-literals.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("Unknown field '") + property->name) + std::string("' for ")) + class_->name), property->span);
#line 274 "/src/checker-literals.do"
                    decorateObjectProperty(state, property, scope, std::monostate{});
#line 275 "/src/checker-literals.do"
                    continue;
                }
#line 277 "/src/checker-literals.do"
                const auto fieldType = ::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), property->name, property->span, true);
#line 278 "/src/checker-literals.do"
                decorateObjectProperty(state, property, scope, ::app_src_checker_symbols_::optionalResolvedType(fieldType));
#line 279 "/src/checker-literals.do"
                if (!::app_src_checker_types_::isAssignable(doof::unwrap_optional(property->resolvedType), fieldType)) {
#line 279 "/src/checker-literals.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(doof::unwrap_optional(property->resolvedType))) + std::string(" to ")) + ::app_src_checker_types_::typeName(fieldType)), property->span);
                }
#line 280 "/src/checker-literals.do"
                if (structural && field->const_) {
#line 281 "/src/checker-literals.do"
                    if ((doof::is_null(property->value) || doof::is_null(field->defaultValue)) || !sameFixedFieldValue(doof::unwrap_optional(property->value), doof::unwrap_optional(field->defaultValue))) {
#line 282 "/src/checker-literals.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Field '") + property->name) + std::string("' must match its literal-valued declaration")), property->span);
                    }
                }
            }
#line 286 "/src/checker-literals.do"
            const auto& _iterable_20 = classDeclaration->fields;
            for (const auto& field : *_iterable_20) {
#line 287 "/src/checker-literals.do"
                if (field->static_ || (!structural && field->const_)) {
#line 287 "/src/checker-literals.do"
                    continue;
                }
#line 288 "/src/checker-literals.do"
                const auto& _iterable_22 = field->names;
                for (const auto& name : *_iterable_22) {
#line 289 "/src/checker-literals.do"
                    const auto required = (field->const_ || doof::is_null(field->defaultValue));
#line 290 "/src/checker-literals.do"
                    if (required && !::app_src_checker_symbols_::hasObjectProperty(expression->properties, name)) {
#line 290 "/src/checker-literals.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Missing required field '") + name) + std::string("'")), expression->span);
                    }
                }
            }
#line 293 "/src/checker-literals.do"
            return doof::optional_value(::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_)));
    }
    else {
    }
    }
#line 297 "/src/checker-literals.do"
    return std::monostate{};
}
#line 300 "/src/checker-literals.do"
bool supportsUnionObjectInference(const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
#line 301 "/src/checker-literals.do"
    auto hasNominal = false;
#line 302 "/src/checker-literals.do"
    const auto& _iterable_24 = union_->types;
    for (const auto& member : *_iterable_24) {
#line 303 "/src/checker-literals.do"
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 304 "/src/checker-literals.do"
                return false;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 305 "/src/checker-literals.do"
                return false;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 306 "/src/checker-literals.do"
                (hasNominal = true);
        }
        else {
        }
        }
    }
#line 310 "/src/checker-literals.do"
    return hasNominal;
}
#line 313 "/src/checker-literals.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkUnionObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
#line 314 "/src/checker-literals.do"
    if (!doof::is_null(expression->spread)) {
#line 315 "/src/checker-literals.do"
        decorateUnresolvedObject(state, expression, scope);
#line 316 "/src/checker-literals.do"
        ::app_src_checker_common_::typeError(state, std::string("Cannot infer a sum type member from an object literal with spread fields; use explicit Type { ... } construction"), expression->span);
#line 317 "/src/checker-literals.do"
        return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
    }
#line 319 "/src/checker-literals.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ClassType>>> matches = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ClassType>>>(std::vector<std::shared_ptr<::app_src_semantic_::ClassType>>{});
#line 320 "/src/checker-literals.do"
    std::shared_ptr<std::vector<std::string>> nominalNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 321 "/src/checker-literals.do"
    const auto& _iterable_26 = union_->types;
    for (const auto& member : *_iterable_26) {
#line 322 "/src/checker-literals.do"
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 324 "/src/checker-literals.do"
                nominalNames->push_back(class_->name);
#line 325 "/src/checker-literals.do"
                if (objectShapeMatchesClass(state, expression, class_)) {
#line 325 "/src/checker-literals.do"
                    matches->push_back(class_);
                }
        }
        else {
        }
        }
    }
#line 330 "/src/checker-literals.do"
    if (static_cast<int32_t>((matches)->size()) == 1) {
#line 331 "/src/checker-literals.do"
        const auto checked = checkClassObject(state, expression, scope, doof::array_at(matches, 0, "src/checker-literals", 331), true);
#line 332 "/src/checker-literals.do"
        if (!doof::is_null(checked)) {
#line 332 "/src/checker-literals.do"
            return doof::unwrap_optional(checked);
        }
    }
#line 334 "/src/checker-literals.do"
    decorateUnresolvedObject(state, expression, scope);
#line 335 "/src/checker-literals.do"
    if (static_cast<int32_t>((matches)->size()) == 0) {
#line 336 "/src/checker-literals.do"
        ::app_src_checker_common_::typeError(state, ((((std::string("Object literal does not match any constructible member of ") + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) + std::string("; candidates: ")) + joinNames(nominalNames)) + std::string(". Use explicit Type { ... } construction")), expression->span);
    } else {
#line 338 "/src/checker-literals.do"
        std::shared_ptr<std::vector<std::string>> matchingNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 339 "/src/checker-literals.do"
        const auto& _iterable_28 = matches;
        for (const auto& match : *_iterable_28) {
#line 339 "/src/checker-literals.do"
            matchingNames->push_back(match->name);
        }
#line 340 "/src/checker-literals.do"
        ::app_src_checker_common_::typeError(state, ((((std::string("Ambiguous object literal for ") + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) + std::string("; matching members: ")) + joinNames(matchingNames)) + std::string(". Use explicit Type { ... } construction")), expression->span);
    }
#line 342 "/src/checker-literals.do"
    return ::app_src_checker_common_::finish(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(expression), doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_));
}
#line 345 "/src/checker-literals.do"
bool objectShapeMatchesClass(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::ClassType>& class_) {
#line 346 "/src/checker-literals.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
#line 347 "/src/checker-literals.do"
    if (doof::is_null(declaration)) {
#line 347 "/src/checker-literals.do"
        return false;
    }
#line 348 "/src/checker-literals.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 350 "/src/checker-literals.do"
            const auto& _iterable_30 = expression->properties;
            for (const auto& property : *_iterable_30) {
#line 351 "/src/checker-literals.do"
                if (!doof::is_null(property->key)) {
#line 351 "/src/checker-literals.do"
                    return false;
                }
#line 352 "/src/checker-literals.do"
                const auto field = ::app_src_checker_interfaces_::findClassField(classDeclaration->fields, property->name);
#line 353 "/src/checker-literals.do"
                if (doof::is_null(field) || field->static_) {
#line 353 "/src/checker-literals.do"
                    return false;
                }
            }
#line 355 "/src/checker-literals.do"
            const auto& _iterable_32 = classDeclaration->fields;
            for (const auto& field : *_iterable_32) {
#line 356 "/src/checker-literals.do"
                if (field->static_) {
#line 356 "/src/checker-literals.do"
                    continue;
                }
#line 357 "/src/checker-literals.do"
                const auto& _iterable_34 = field->names;
                for (const auto& name : *_iterable_34) {
#line 358 "/src/checker-literals.do"
                    if ((field->const_ || doof::is_null(field->defaultValue)) && !::app_src_checker_symbols_::hasObjectProperty(expression->properties, name)) {
#line 358 "/src/checker-literals.do"
                        return false;
                    }
                }
            }
#line 361 "/src/checker-literals.do"
            return true;
    }
    else {
    }
    }
#line 365 "/src/checker-literals.do"
    return false;
}
#line 368 "/src/checker-literals.do"
void decorateObjectProperty(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectProperty>& property, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 369 "/src/checker-literals.do"
    if (!doof::is_null(property->key)) {
#line 369 "/src/checker-literals.do"
        ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->key), scope, std::monostate{});
    }
#line 370 "/src/checker-literals.do"
    if (!doof::is_null(property->value)) {
#line 370 "/src/checker-literals.do"
        (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(property->value), scope, expected)));
    } else {
#line 372 "/src/checker-literals.do"
        const auto binding = ::app_src_checker_symbols_::lookup(scope, property->name);
#line 373 "/src/checker-literals.do"
        if (doof::is_null(binding)) {
#line 373 "/src/checker-literals.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Unknown shorthand property '") + property->name) + std::string("'")), property->span);
#line 373 "/src/checker-literals.do"
            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::unknownType()));
        } else {
#line 374 "/src/checker-literals.do"
            (property->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
        }
    }
}
#line 378 "/src/checker-literals.do"
void decorateUnresolvedObject(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 379 "/src/checker-literals.do"
    if (!doof::is_null(expression->spread)) {
#line 379 "/src/checker-literals.do"
        ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(expression->spread), scope, std::monostate{});
    }
#line 380 "/src/checker-literals.do"
    const auto& _iterable_36 = expression->properties;
    for (const auto& property : *_iterable_36) {
#line 380 "/src/checker-literals.do"
        decorateObjectProperty(state, property, scope, std::monostate{});
    }
}
#line 383 "/src/checker-literals.do"
bool sameFixedFieldValue(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& actual, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expected) {
#line 384 "/src/checker-literals.do"
    {
        auto _case_subject = expected;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& expectedString = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 386 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
                    const auto& actualString = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 386 "/src/checker-literals.do"
                    return (actualString->value == expectedString->value);
            }
            else {
#line 386 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            const auto& expectedInt = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
#line 389 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
                    const auto& actualInt = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
#line 389 "/src/checker-literals.do"
                    return (actualInt->value == expectedInt->value);
            }
            else {
#line 389 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            const auto& expectedLong = std::get<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject);
#line 392 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
                    const auto& actualLong = std::get<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject);
#line 392 "/src/checker-literals.do"
                    return (actualLong->value == expectedLong->value);
            }
            else {
#line 392 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            const auto& expectedFloat = std::get<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject);
#line 395 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
                    const auto& actualFloat = std::get<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject);
#line 395 "/src/checker-literals.do"
                    return (actualFloat->value == expectedFloat->value);
            }
            else {
#line 395 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            const auto& expectedDouble = std::get<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject);
#line 398 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
                    const auto& actualDouble = std::get<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject);
#line 398 "/src/checker-literals.do"
                    return (actualDouble->value == expectedDouble->value);
            }
            else {
#line 398 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
            const auto& expectedChar = std::get<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject);
#line 401 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
                    const auto& actualChar = std::get<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject);
#line 401 "/src/checker-literals.do"
                    return (actualChar->value == expectedChar->value);
            }
            else {
#line 401 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
            const auto& expectedBool = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
#line 404 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
                    const auto& actualBool = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
#line 404 "/src/checker-literals.do"
                    return (actualBool->value == expectedBool->value);
            }
            else {
#line 404 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
#line 407 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
#line 407 "/src/checker-literals.do"
                    return true;
            }
            else {
#line 407 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& expectedMember = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 410 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                    const auto& actualMember = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 411 "/src/checker-literals.do"
                    return (actualMember->property == expectedMember->property);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
                    const auto& actualDot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 412 "/src/checker-literals.do"
                    return (actualDot->name == expectedMember->property);
            }
            else {
#line 413 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& expectedDot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 417 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                    const auto& actualMember = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 418 "/src/checker-literals.do"
                    return (actualMember->property == expectedDot->name);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
                    const auto& actualDot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 419 "/src/checker-literals.do"
                    return (actualDot->name == expectedDot->name);
            }
            else {
#line 420 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& expectedUnary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 424 "/src/checker-literals.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
                    const auto& actualUnary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 425 "/src/checker-literals.do"
                    return ((actualUnary->operator_ == expectedUnary->operator_) && sameFixedFieldValue(actualUnary->operand, expectedUnary->operand));
            }
            else {
#line 426 "/src/checker-literals.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 429 "/src/checker-literals.do"
            return false;
    }
    }
    doof::unreachable();
#line 431 "/src/checker-literals.do"
    return false;
}
#line 434 "/src/checker-literals.do"
std::string joinNames(const std::shared_ptr<std::vector<std::string>>& names) {
#line 435 "/src/checker-literals.do"
    auto result = std::string("");
#line 436 "/src/checker-literals.do"
    for (int32_t i = 0; i < static_cast<int32_t>((names)->size()); ++i) {
#line 437 "/src/checker-literals.do"
        if (i > 0) {
#line 437 "/src/checker-literals.do"
            (result = (result + std::string(", ")));
        }
#line 438 "/src/checker-literals.do"
        (result = (result + doof::array_at(names, i, "src/checker-literals", 438)));
    }
#line 440 "/src/checker-literals.do"
    return result;
}
#line 443 "/src/checker-literals.do"
bool containsJsonValue(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
#line 444 "/src/checker-literals.do"
    const auto& _iterable_39 = union_->types;
    for (const auto& member : *_iterable_39) {
#line 444 "/src/checker-literals.do"
        if (::app_src_checker_types_::isJsonValueType(member)) {
#line 444 "/src/checker-literals.do"
            return true;
        }
    }
#line 445 "/src/checker-literals.do"
    return false;
}
#line 1 "<doof-generated>"
}
