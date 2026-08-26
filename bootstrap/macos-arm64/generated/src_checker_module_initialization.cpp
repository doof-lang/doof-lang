#include "src_checker_module_initialization.hpp"

namespace app_src_checker_module_initialization_ {
using namespace ::app_src_ast_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_semantic_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_types_;
#line 25 "/src/checker-module-initialization.do"
void validateModuleInitializerStatement(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 26 "/src/checker-module-initialization.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 27 "/src/checker-module-initialization.do"
            validateValue(state, value->name, value->value, value->resolvedType);
#line 27 "/src/checker-module-initialization.do"
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 28 "/src/checker-module-initialization.do"
            validateValue(state, value->name, value->value, value->resolvedType);
#line 28 "/src/checker-module-initialization.do"
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 29 "/src/checker-module-initialization.do"
            validateValue(state, value->name, value->value, value->resolvedType);
#line 29 "/src/checker-module-initialization.do"
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 30 "/src/checker-module-initialization.do"
            validateValue(state, value->name, value->value, value->resolvedType);
#line 30 "/src/checker-module-initialization.do"
            (value->moduleInitializerChecked = true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 32 "/src/checker-module-initialization.do"
            const auto& _iterable_2 = class_->fields;
            for (const auto& field : *_iterable_2) {
#line 33 "/src/checker-module-initialization.do"
                if (!field->static_ || doof::is_null(field->defaultValue)) {
#line 33 "/src/checker-module-initialization.do"
                    continue;
                }
#line 34 "/src/checker-module-initialization.do"
                validateField(state, class_, field);
#line 35 "/src/checker-module-initialization.do"
                (field->moduleInitializerChecked = true);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 38 "/src/checker-module-initialization.do"
            validateModuleInitializerStatement(state, export_->declaration);
    }
    else {
    }
    }
}
#line 43 "/src/checker-module-initialization.do"
void validateValue(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& name, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 44 "/src/checker-module-initialization.do"
    if (!literalTree(state, value)) {
#line 45 "/src/checker-module-initialization.do"
        ::app_src_checker_common_::typeError(state, ((std::string("Module initializer for '") + name) + std::string("' must be a literal tree; move executable initialization into main() or an explicitly called function")), std::visit([](auto&& _obj) { return _obj->span; }, value));
#line 50 "/src/checker-module-initialization.do"
        return;
    }
#line 52 "/src/checker-module-initialization.do"
    if ((!doof::is_null(type_)) && !supportsDirectStorage(doof::unwrap_optional(type_))) {
#line 53 "/src/checker-module-initialization.do"
        ::app_src_checker_common_::typeError(state, ((((std::string("Module initializer for '") + name) + std::string("' has type ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(type_))) + std::string(", which cannot use direct default-constructed assignable storage")), std::visit([](auto&& _obj) { return _obj->span; }, value));
    }
}
#line 62 "/src/checker-module-initialization.do"
void validateField(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::ClassField>& field) {
#line 63 "/src/checker-module-initialization.do"
    if (!literalTree(state, doof::unwrap_optional(field->defaultValue))) {
#line 64 "/src/checker-module-initialization.do"
        ::app_src_checker_common_::typeError(state, ((((std::string("Static field initializer for '") + owner->name) + std::string(".")) + doof::array_at(field->names, 0, "src/checker-module-initialization", 66)) + std::string("' must be a literal tree; move executable initialization into an explicitly called function")), std::visit([](auto&& _obj) { return _obj->span; }, doof::unwrap_optional(field->defaultValue)));
#line 70 "/src/checker-module-initialization.do"
        return;
    }
#line 72 "/src/checker-module-initialization.do"
    if ((!doof::is_null(field->resolvedType)) && !supportsDirectStorage(doof::unwrap_optional(field->resolvedType))) {
#line 73 "/src/checker-module-initialization.do"
        ::app_src_checker_common_::typeError(state, ((((((std::string("Static field initializer for '") + owner->name) + std::string(".")) + doof::array_at(field->names, 0, "src/checker-module-initialization", 75)) + std::string("' has type ")) + ::app_src_checker_types_::typeName(doof::unwrap_optional(field->resolvedType))) + std::string(", which cannot use direct default-constructed assignable storage")), std::visit([](auto&& _obj) { return _obj->span; }, doof::unwrap_optional(field->defaultValue)));
    }
}
#line 82 "/src/checker-module-initialization.do"
bool literalTree(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 83 "/src/checker-module-initialization.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
#line 84 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
#line 85 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
#line 86 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
#line 87 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
#line 88 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
#line 89 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
#line 90 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 91 "/src/checker-module-initialization.do"
            return (static_cast<int32_t>((string_->interpolations)->size()) == 0);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 93 "/src/checker-module-initialization.do"
            return ((unary->prefix && ((unary->operator_ == std::string("-")) || (unary->operator_ == std::string("+")))) && numericLiteral(unary->operand));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 97 "/src/checker-module-initialization.do"
            return ((constantBinaryOperator(binary->operator_) && literalTree(state, binary->left)) && literalTree(state, binary->right));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 100 "/src/checker-module-initialization.do"
            return directScalarConstantBinding(state, identifier);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 102 "/src/checker-module-initialization.do"
            const auto& _iterable_4 = array->elements;
            for (const auto& element : *_iterable_4) {
#line 102 "/src/checker-module-initialization.do"
                if (!literalTree(state, element)) {
#line 102 "/src/checker-module-initialization.do"
                    return false;
                }
            }
#line 103 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
#line 106 "/src/checker-module-initialization.do"
            const auto& _iterable_6 = tuple->elements;
            for (const auto& element : *_iterable_6) {
#line 106 "/src/checker-module-initialization.do"
                if (!literalTree(state, element)) {
#line 106 "/src/checker-module-initialization.do"
                    return false;
                }
            }
#line 107 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 110 "/src/checker-module-initialization.do"
            if ((!doof::is_null(object->spread)) && !literalTree(state, doof::unwrap_optional(object->spread))) {
#line 110 "/src/checker-module-initialization.do"
                return false;
            }
#line 111 "/src/checker-module-initialization.do"
            const auto& _iterable_8 = object->properties;
            for (const auto& property : *_iterable_8) {
#line 111 "/src/checker-module-initialization.do"
                if (!literalProperty(state, property)) {
#line 111 "/src/checker-module-initialization.do"
                    return false;
                }
            }
#line 112 "/src/checker-module-initialization.do"
            if ((!doof::is_null(object->resolvedClass)) && !literalClassDefaults(state, doof::unwrap_optional(object->resolvedClass), object->properties)) {
#line 112 "/src/checker-module-initialization.do"
                return false;
            }
#line 113 "/src/checker-module-initialization.do"
            return (doof::is_null(object->resolvedClass) || !object->resolvedClass->native_);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 116 "/src/checker-module-initialization.do"
            if ((doof::is_null(construct->resolvedClass) || construct->resolvedClass->native_) || (!doof::is_null(construct->resolvedConstructor))) {
#line 116 "/src/checker-module-initialization.do"
                return false;
            }
#line 117 "/src/checker-module-initialization.do"
            const auto& _iterable_10 = construct->args;
            for (const auto& argument : *_iterable_10) {
#line 117 "/src/checker-module-initialization.do"
                if (!literalProperty(state, argument)) {
#line 117 "/src/checker-module-initialization.do"
                    return false;
                }
            }
#line 118 "/src/checker-module-initialization.do"
            return literalClassDefaults(state, doof::unwrap_optional(construct->resolvedClass), construct->args);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 121 "/src/checker-module-initialization.do"
            if ((doof::is_null(call->resolvedClass) || call->resolvedClass->native_) || (!doof::is_null(call->resolvedConstructor))) {
#line 121 "/src/checker-module-initialization.do"
                return false;
            }
#line 122 "/src/checker-module-initialization.do"
            const auto& _iterable_12 = call->args;
            for (const auto& argument : *_iterable_12) {
#line 122 "/src/checker-module-initialization.do"
                if (!literalTree(state, argument->value)) {
#line 122 "/src/checker-module-initialization.do"
                    return false;
                }
            }
#line 123 "/src/checker-module-initialization.do"
            return literalPositionalClassDefaults(state, doof::unwrap_optional(call->resolvedClass), static_cast<int32_t>((call->args)->size()));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 125 "/src/checker-module-initialization.do"
            return (dot->resolvedShorthandOwnerKind == std::string("enum"));
    }
    else {
#line 126 "/src/checker-module-initialization.do"
            return false;
    }
    }
    doof::unreachable();
#line 128 "/src/checker-module-initialization.do"
    return false;
}
#line 131 "/src/checker-module-initialization.do"
bool constantBinaryOperator(const std::string& operator_) {
#line 132 "/src/checker-module-initialization.do"
    return ((((((operator_ == std::string("+")) || (operator_ == std::string("-"))) || (operator_ == std::string("*"))) || (operator_ == std::string("/"))) || (operator_ == std::string("\\"))) || (operator_ == std::string("%")));
}
#line 136 "/src/checker-module-initialization.do"
bool directScalarConstantBinding(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::Identifier>& identifier) {
#line 137 "/src/checker-module-initialization.do"
    if ((doof::is_null(identifier->resolvedBinding) || identifier->resolvedBinding->mutable_) || doof::is_null(identifier->resolvedBinding->symbol)) {
#line 139 "/src/checker-module-initialization.do"
        return false;
    }
#line 141 "/src/checker-module-initialization.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(identifier->resolvedBinding->symbol));
#line 142 "/src/checker-module-initialization.do"
    if (doof::is_null(declaration)) {
#line 142 "/src/checker-module-initialization.do"
        return false;
    }
#line 143 "/src/checker-module-initialization.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 144 "/src/checker-module-initialization.do"
            return scalarConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 145 "/src/checker-module-initialization.do"
            return scalarConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 146 "/src/checker-module-initialization.do"
            return scalarConstantInitializer(value->value);
    }
    else {
#line 147 "/src/checker-module-initialization.do"
            return false;
    }
    }
    doof::unreachable();
#line 149 "/src/checker-module-initialization.do"
    return false;
}
#line 152 "/src/checker-module-initialization.do"
bool scalarConstantInitializer(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 153 "/src/checker-module-initialization.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
#line 154 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
#line 155 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
#line 156 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
#line 157 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
#line 158 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
#line 159 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 160 "/src/checker-module-initialization.do"
            return (dot->resolvedShorthandOwnerKind == std::string("enum"));
    }
    else {
#line 161 "/src/checker-module-initialization.do"
            return false;
    }
    }
    doof::unreachable();
#line 163 "/src/checker-module-initialization.do"
    return false;
}
#line 166 "/src/checker-module-initialization.do"
bool numericLiteral(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 167 "/src/checker-module-initialization.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
#line 168 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
#line 169 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
#line 170 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
#line 171 "/src/checker-module-initialization.do"
            return true;
    }
    else {
#line 172 "/src/checker-module-initialization.do"
            return false;
    }
    }
    doof::unreachable();
#line 174 "/src/checker-module-initialization.do"
    return false;
}
#line 177 "/src/checker-module-initialization.do"
bool literalProperty(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ObjectProperty>& property) {
#line 178 "/src/checker-module-initialization.do"
    if ((!doof::is_null(property->key)) && !literalTree(state, doof::unwrap_optional(property->key))) {
#line 178 "/src/checker-module-initialization.do"
        return false;
    }
#line 179 "/src/checker-module-initialization.do"
    if (doof::is_null(property->value)) {
#line 179 "/src/checker-module-initialization.do"
        return false;
    }
#line 180 "/src/checker-module-initialization.do"
    return literalTree(state, doof::unwrap_optional(property->value));
}
#line 183 "/src/checker-module-initialization.do"
bool literalPositionalClassDefaults(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, int32_t suppliedCount) {
#line 184 "/src/checker-module-initialization.do"
    auto position = 0;
#line 185 "/src/checker-module-initialization.do"
    const auto& _iterable_14 = class_->fields;
    for (const auto& field : *_iterable_14) {
#line 186 "/src/checker-module-initialization.do"
        if (field->static_) {
#line 186 "/src/checker-module-initialization.do"
            continue;
        }
#line 187 "/src/checker-module-initialization.do"
        if (field->const_) {
#line 188 "/src/checker-module-initialization.do"
            if ((!doof::is_null(field->defaultValue)) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
#line 188 "/src/checker-module-initialization.do"
                return false;
            }
#line 189 "/src/checker-module-initialization.do"
            continue;
        }
#line 191 "/src/checker-module-initialization.do"
        const auto& _iterable_16 = field->names;
        for (const auto& name : *_iterable_16) {
#line 192 "/src/checker-module-initialization.do"
            if (((position >= suppliedCount) && (!doof::is_null(field->defaultValue))) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
#line 193 "/src/checker-module-initialization.do"
                return false;
            }
#line 195 "/src/checker-module-initialization.do"
            (position = (position + 1));
        }
    }
#line 198 "/src/checker-module-initialization.do"
    return true;
}
#line 201 "/src/checker-module-initialization.do"
bool literalClassDefaults(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>>& supplied) {
#line 202 "/src/checker-module-initialization.do"
    const auto& _iterable_18 = class_->fields;
    for (const auto& field : *_iterable_18) {
#line 203 "/src/checker-module-initialization.do"
        if (field->static_) {
#line 203 "/src/checker-module-initialization.do"
            continue;
        }
#line 204 "/src/checker-module-initialization.do"
        const auto& _iterable_20 = field->names;
        for (const auto& name : *_iterable_20) {
#line 205 "/src/checker-module-initialization.do"
            if (suppliedProperty(supplied, name)) {
#line 205 "/src/checker-module-initialization.do"
                continue;
            }
#line 206 "/src/checker-module-initialization.do"
            if (field->const_) {
#line 207 "/src/checker-module-initialization.do"
                if ((!doof::is_null(field->defaultValue)) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
#line 207 "/src/checker-module-initialization.do"
                    return false;
                }
#line 208 "/src/checker-module-initialization.do"
                continue;
            }
#line 210 "/src/checker-module-initialization.do"
            if ((!doof::is_null(field->defaultValue)) && !literalTree(state, doof::unwrap_optional(field->defaultValue))) {
#line 210 "/src/checker-module-initialization.do"
                return false;
            }
        }
    }
#line 213 "/src/checker-module-initialization.do"
    return true;
}
#line 216 "/src/checker-module-initialization.do"
bool suppliedProperty(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>>& properties, const std::string& name) {
#line 217 "/src/checker-module-initialization.do"
    const auto& _iterable_22 = properties;
    for (const auto& property : *_iterable_22) {
#line 217 "/src/checker-module-initialization.do"
        if (property->name == name) {
#line 217 "/src/checker-module-initialization.do"
            return true;
        }
    }
#line 218 "/src/checker-module-initialization.do"
    return false;
}
#line 223 "/src/checker-module-initialization.do"
bool supportsDirectStorage(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 224 "/src/checker-module-initialization.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
#line 225 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 226 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 227 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 228 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 229 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 230 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
#line 231 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 232 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 233 "/src/checker-module-initialization.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 234 "/src/checker-module-initialization.do"
            return supportsDirectStorage(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 236 "/src/checker-module-initialization.do"
            const auto& _iterable_24 = tuple->elements;
            for (const auto& element : *_iterable_24) {
#line 236 "/src/checker-module-initialization.do"
                if (!supportsDirectStorage(element)) {
#line 236 "/src/checker-module-initialization.do"
                    return false;
                }
            }
#line 237 "/src/checker-module-initialization.do"
            return true;
    }
    else {
#line 239 "/src/checker-module-initialization.do"
            return false;
    }
    }
    doof::unreachable();
#line 241 "/src/checker-module-initialization.do"
    return false;
}
#line 1 "<doof-generated>"
}
