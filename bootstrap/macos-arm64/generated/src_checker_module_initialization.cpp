#include "src_checker_module_initialization.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_checker_state.hpp"
#include "src_semantic.hpp"
#include "src_checker_common.hpp"
#include "src_checker_symbols.hpp"
#include "src_checker_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_checker_module_initialization_ {
using namespace ::app_src_ast_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_semantic_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_types_;
void validateModuleInitializerStatement(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            validateValue(state, value->name, value->value, value->resolvedType);
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            validateValue(state, value->name, value->value, value->resolvedType);
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            validateValue(state, value->name, value->value, value->resolvedType);
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            validateValue(state, value->name, value->value, value->resolvedType);
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            const auto& _iterable_1 = class_->fields;
            for (const auto& field : *_iterable_1) {
                if (!field->static_ || doof::is_null(field->defaultValue)) {
                    continue;
                }
                validateField(state, class_, field);
                (field->moduleInitializerChecked = true);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            validateModuleInitializerStatement(state, export_->declaration);
    }
    else {
    }
    }
}
void validateValue(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::string name, std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    if (!literalTree(state, value)) {
        ::app_src_checker_common_::typeError(state, ((std::string("Module initializer for '") + name) + std::string("' must be a literal tree; move executable initialization into main() or an explicitly called function")), std::visit([](auto&& _obj) { return _obj->span; }, value));
        return;
    }
    if ((!doof::is_null(type_)) && !supportsDirectStorage(doof::unwrap_optional(type_))) {
        ::app_src_checker_common_::typeError(state, ((((std::string("Module initializer for '") + name) + std::string("' has type ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(type_))) + std::string(", which cannot use direct default-constructed assignable storage")), std::visit([](auto&& _obj) { return _obj->span; }, value));
    }
}
void validateField(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_ast_::ClassField> field) {
    if (!literalTree(state, doof::unwrap_optional(field->defaultValue))) {
        ::app_src_checker_common_::typeError(state, ((((std::string("Static field initializer for '") + owner->name) + std::string(".")) + (*field->names)[0]) + std::string("' must be a literal tree; move executable initialization into an explicitly called function")), std::visit([](auto&& _obj) { return _obj->span; }, doof::unwrap_optional(field->defaultValue)));
        return;
    }
    if ((!doof::is_null(field->resolvedType)) && !supportsDirectStorage(doof::unwrap_optional(field->resolvedType))) {
        ::app_src_checker_common_::typeError(state, ((((((std::string("Static field initializer for '") + owner->name) + std::string(".")) + (*field->names)[0]) + std::string("' has type ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(field->resolvedType))) + std::string(", which cannot use direct default-constructed assignable storage")), std::visit([](auto&& _obj) { return _obj->span; }, doof::unwrap_optional(field->defaultValue)));
    }
}
bool literalTree(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression) {
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
            return (static_cast<int32_t>((string_->interpolations)->size()) == 0);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
            return ((unary->prefix && ((unary->operator_ == std::string("-")) || (unary->operator_ == std::string("+")))) && numericLiteral(unary->operand));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
            return ((constantBinaryOperator(binary->operator_) && literalTree(state, binary->left)) && literalTree(state, binary->right));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            return directScalarConstantBinding(state, identifier);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
            const auto& _iterable_2 = array->elements;
            for (const auto& element : *_iterable_2) {
                if (!literalTree(state, element)) {
                    return false;
                }
            }
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
            const auto& _iterable_3 = tuple->elements;
            for (const auto& element : *_iterable_3) {
                if (!literalTree(state, element)) {
                    return false;
                }
            }
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
            if ((!doof::is_null(object->spread)) && !literalTree(state, doof::unwrap_optional(object->spread))) {
                return false;
            }
            const auto& _iterable_4 = object->properties;
            for (const auto& property : *_iterable_4) {
                if (!literalProperty(state, property)) {
                    return false;
                }
            }
            if ((!doof::is_null(object->resolvedClass)) && !literalClassDefaults(state, doof::unwrap_optional(object->resolvedClass), object->properties)) {
                return false;
            }
            return (doof::is_null(object->resolvedClass) || !object->resolvedClass->native_);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
            if ((doof::is_null(construct->resolvedClass) || construct->resolvedClass->native_) || (!doof::is_null(construct->resolvedConstructor))) {
                return false;
            }
            const auto& _iterable_5 = construct->args;
            for (const auto& argument : *_iterable_5) {
                if (!literalProperty(state, argument)) {
                    return false;
                }
            }
            return literalClassDefaults(state, doof::unwrap_optional(construct->resolvedClass), construct->args);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
            if ((doof::is_null(call->resolvedClass) || call->resolvedClass->native_) || (!doof::is_null(call->resolvedConstructor))) {
                return false;
            }
            const auto& _iterable_6 = call->args;
            for (const auto& argument : *_iterable_6) {
                if (!literalTree(state, argument->value)) {
                    return false;
                }
            }
            return literalPositionalClassDefaults(state, doof::unwrap_optional(call->resolvedClass), static_cast<int32_t>((call->args)->size()));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
            return (dot->resolvedShorthandOwnerKind == std::string("enum"));
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool constantBinaryOperator(std::string operator_) {
    return ((((((operator_ == std::string("+")) || (operator_ == std::string("-"))) || (operator_ == std::string("*"))) || (operator_ == std::string("/"))) || (operator_ == std::string("\\"))) || (operator_ == std::string("%")));
}
bool directScalarConstantBinding(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::Identifier> identifier) {
    if ((doof::is_null(identifier->resolvedBinding) || identifier->resolvedBinding->mutable_) || doof::is_null(identifier->resolvedBinding->symbol)) {
        return false;
    }
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(identifier->resolvedBinding->symbol));
    if (doof::is_null(declaration)) {
        return false;
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return scalarConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return scalarConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return scalarConstantInitializer(value->value);
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool scalarConstantInitializer(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression) {
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
            return (dot->resolvedShorthandOwnerKind == std::string("enum"));
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool numericLiteral(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression) {
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool literalProperty(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::ObjectProperty> property) {
    if ((!doof::is_null(property->key)) && !literalTree(state, doof::unwrap_optional(property->key))) {
        return false;
    }
    if (doof::is_null(property->value)) {
        return false;
    }
    return literalTree(state, doof::unwrap_optional(property->value));
}
bool literalPositionalClassDefaults(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, int32_t suppliedCount) {
    auto position = 0;
    const auto& _iterable_7 = class_->fields;
    for (const auto& field : *_iterable_7) {
        if (field->static_) {
            continue;
        }
        if (field->const_) {
            if ((!doof::is_null(field->defaultValue)) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
                return false;
            }
            continue;
        }
        const auto& _iterable_8 = field->names;
        for (const auto& name : *_iterable_8) {
            if (((position >= suppliedCount) && (!doof::is_null(field->defaultValue))) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
                return false;
            }
            (position = (position + 1));
        }
    }
    return true;
}
bool literalClassDefaults(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>> supplied) {
    const auto& _iterable_9 = class_->fields;
    for (const auto& field : *_iterable_9) {
        if (field->static_) {
            continue;
        }
        const auto& _iterable_10 = field->names;
        for (const auto& name : *_iterable_10) {
            if (suppliedProperty(supplied, name)) {
                continue;
            }
            if (field->const_) {
                if ((!doof::is_null(field->defaultValue)) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
                    return false;
                }
                continue;
            }
            if ((!doof::is_null(field->defaultValue)) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
                return false;
            }
        }
    }
    return true;
}
bool suppliedProperty(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>> properties, std::string name) {
    const auto& _iterable_11 = properties;
    for (const auto& property : *_iterable_11) {
        if (property->name == name) {
            return true;
        }
    }
    return false;
}
bool supportsDirectStorage(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return supportsDirectStorage(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_12 = tuple->elements;
            for (const auto& element : *_iterable_12) {
                if (!supportsDirectStorage(element)) {
                    return false;
                }
            }
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
}
