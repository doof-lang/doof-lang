#include "src_checker_validation.hpp"
#include <cmath>
#include "src_semantic.hpp"
#include "src_analyzer.hpp"
#include "src_ast.hpp"
#include "src_checker_types.hpp"
#include "src_json_semantics.hpp"
#include "src_checker_actor_boundary.hpp"
#include "src_checker_actor_lifecycle.hpp"
#include "src_checker_symbols.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_checker_validation_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_symbols_;
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateCheckedTypes(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
    const auto& _iterable_1 = result->modules;
    for (const auto& module : *_iterable_1) {
        const auto& _iterable_2 = module->program->statements;
        for (const auto& statement : *_iterable_2) {
            validateStatement(statement, module->path, diagnostics);
        }
    }
    return diagnostics;
}
void validateStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(const_), const_->resolvedType, const_->type_, module, diagnostics);
            validateExpression(const_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(readonly_), readonly_->resolvedType, readonly_->type_, module, diagnostics);
            validateExpression(readonly_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), binding->resolvedType, binding->type_, module, diagnostics);
            validateExpression(binding->value, module, diagnostics);
            if (!doof::is_null(binding->else_)) {
                validateBlock(doof::unwrap_optional(binding->else_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(let_), let_->resolvedType, let_->type_, module, diagnostics);
            validateExpression(let_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            validateFunction(fn, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (doof::is_null(class_->resolvedSymbol)) {
                addValidationError(module, class_->span, ((std::string("Class '") + class_->name) + std::string("' has no resolved symbol")), diagnostics);
            }
            validateTypeParameterConstraints(class_->typeParamConstraints, module, diagnostics);
            const auto& _iterable_3 = class_->implements_;
            for (const auto& implementation : *_iterable_3) {
                validateTypeAnnotation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(implementation), module, diagnostics);
            }
            const auto& _iterable_4 = class_->fields;
            for (const auto& field : *_iterable_4) {
                if (!doof::is_null(field->type_)) {
                    validateTypeAnnotation(doof::unwrap_optional(field->type_), module, diagnostics);
                }
                validateResolved(field->resolvedType, field->span, module, (std::string("field ") + class_->name), diagnostics);
                if (!doof::is_null(field->defaultValue)) {
                    validateExpression(doof::unwrap_optional(field->defaultValue), module, diagnostics);
                }
            }
            const auto& _iterable_5 = class_->methods;
            for (const auto& method : *_iterable_5) {
                validateFunction(method, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            if (doof::is_null(interface_->resolvedSymbol)) {
                addValidationError(module, interface_->span, ((std::string("Interface '") + interface_->name) + std::string("' has no resolved symbol")), diagnostics);
            }
            validateTypeParameterConstraints(interface_->typeParamConstraints, module, diagnostics);
            const auto& _iterable_6 = interface_->fields;
            for (const auto& field : *_iterable_6) {
                validateTypeAnnotation(field->type_, module, diagnostics);
                validateResolved(field->resolvedType, field->span, module, (std::string("interface field ") + interface_->name), diagnostics);
            }
            const auto& _iterable_7 = interface_->methods;
            for (const auto& method : *_iterable_7) {
                validateFunction(method, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            const auto& _iterable_8 = enum_->variants;
            for (const auto& variant : *_iterable_8) {
                if (!doof::is_null(variant->value)) {
                    validateExpression(doof::unwrap_optional(variant->value), module, diagnostics);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            validateTypeParameterConstraints(alias->typeParamConstraints, module, diagnostics);
            validateTypeAnnotation(alias->type_, module, diagnostics);
            validateResolved(alias->resolvedType, alias->span, module, (std::string("type alias ") + alias->name), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
            validateExpression(if_->condition, module, diagnostics);
            validateBlock(if_->body, module, diagnostics);
            const auto& _iterable_9 = if_->elseIfs;
            for (const auto& branch : *_iterable_9) {
                validateExpression(branch->condition, module, diagnostics);
                validateBlock(branch->body, module, diagnostics);
            }
            if (!doof::is_null(if_->else_)) {
                validateBlock(doof::unwrap_optional(if_->else_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
            validateExpression(case_->subject, module, diagnostics);
            const auto& _iterable_10 = case_->arms;
            for (const auto& arm : *_iterable_10) {
                const auto& _iterable_11 = arm->patterns;
                for (const auto& pattern : *_iterable_11) {
                    validatePattern(pattern, module, diagnostics);
                }
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                        validateBlock(block, module, diagnostics);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                        validateExpression(expression, module, diagnostics);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
            validateExpression(while_->condition, module, diagnostics);
            validateBlock(while_->body, module, diagnostics);
            if (!doof::is_null(while_->then_)) {
                validateBlock(doof::unwrap_optional(while_->then_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
            if (!doof::is_null(for_->init)) {
                validateStatement(doof::unwrap_optional(for_->init), module, diagnostics);
            }
            if (!doof::is_null(for_->condition)) {
                validateExpression(doof::unwrap_optional(for_->condition), module, diagnostics);
            }
            const auto& _iterable_12 = for_->update;
            for (const auto& update : *_iterable_12) {
                validateExpression(update, module, diagnostics);
            }
            validateBlock(for_->body, module, diagnostics);
            if (!doof::is_null(for_->then_)) {
                validateBlock(doof::unwrap_optional(for_->then_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
            validateExpression(forOf->iterable, module, diagnostics);
            validateBlock(forOf->body, module, diagnostics);
            if (!doof::is_null(forOf->then_)) {
                validateBlock(doof::unwrap_optional(forOf->then_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
            const auto& _iterable_13 = with_->bindings;
            for (const auto& binding : *_iterable_13) {
                if (!doof::is_null(binding->type_)) {
                    validateTypeAnnotation(doof::unwrap_optional(binding->type_), module, diagnostics);
                }
                validateResolved(binding->resolvedType, binding->span, module, (std::string("with binding ") + binding->name), diagnostics);
                validateExpression(binding->value, module, diagnostics);
            }
            validateBlock(with_->body, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
            if (!doof::is_null(return_->value)) {
                validateExpression(doof::unwrap_optional(return_->value), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
            validateExpression(yield_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
            validateExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), module, diagnostics);
            validateResolved(assignment->resolvedType, assignment->span, module, std::string("yield-block assignment"), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
            validateExpression(expression->expression, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
            validateExpression(destructuring->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(expression), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(destructuring), module, diagnostics);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            validateStatement(export_->declaration, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            validateBlock(block, module, diagnostics);
    }
    else {
    }
    }
}
void validateValue(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    if (!doof::is_null(annotation)) {
        validateTypeAnnotation(doof::unwrap_optional(annotation), module, diagnostics);
    }
    validateResolved(resolvedType, std::visit([](auto&& _obj) { return _obj->span; }, statement), module, std::string("value"), diagnostics);
}
void validateFunction(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    validateResolved(fn->resolvedType, fn->span, module, (std::string("function ") + fn->name), diagnostics);
    validateTypeParameterConstraints(fn->typeParamConstraints, module, diagnostics);
    if (!doof::is_null(fn->returnType)) {
        validateTypeAnnotation(doof::unwrap_optional(fn->returnType), module, diagnostics);
    }
    const auto& _iterable_14 = fn->params;
    for (const auto& parameter : *_iterable_14) {
        if (!doof::is_null(parameter->type_)) {
            validateTypeAnnotation(doof::unwrap_optional(parameter->type_), module, diagnostics);
        }
        validateResolved(parameter->resolvedType, parameter->span, module, (std::string("parameter ") + parameter->name), diagnostics);
        if (!doof::is_null(parameter->defaultValue)) {
            validateExpression(doof::unwrap_optional(parameter->defaultValue), module, diagnostics);
        }
    }
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            validateBlock(block, module, diagnostics);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            validateExpression(expression, module, diagnostics);
    }
    }
}
void validateTypeParameterConstraints(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    const auto& _iterable_15 = constraints;
    for (const auto& constraint : *_iterable_15) {
        if (doof::is_null(constraint->type_)) {
            continue;
        }
        {
            auto _case_subject = doof::unwrap_optional(constraint->type_);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && ((named->name == std::string("JsonSerializable")) || (named->name == std::string("Reflectable")))) {
                    continue;
                }
        }
        else {
        }
        }
        validateTypeAnnotation(doof::unwrap_optional(constraint->type_), module, diagnostics);
    }
}
void validateBlock(std::shared_ptr<::app_src_ast_::Block> block, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    const auto& _iterable_16 = block->statements;
    for (const auto& statement : *_iterable_16) {
        validateStatement(statement, module, diagnostics);
    }
}
void validatePattern(std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>> pattern, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    {
        auto _case_subject = pattern;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
            const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
            validateTypeAnnotation(type_->type_, module, diagnostics);
            validateResolved(type_->resolvedType, type_->span, module, std::string("case pattern"), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
            validateExpression(value->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
            const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
            if (!doof::is_null(range->start)) {
                validateExpression(doof::unwrap_optional(range->start), module, diagnostics);
            }
            if (!doof::is_null(range->end)) {
                validateExpression(doof::unwrap_optional(range->end), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
    }
    }
}
void validateExpression(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    validateResolved(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression), std::visit([](auto&& _obj) { return _obj->span; }, expression), module, (std::string("expression ") + std::visit([](auto&& _obj) { return _obj->kind; }, expression)), diagnostics);
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
            const auto& _iterable_17 = string_->interpolations;
            for (const auto& interpolation : *_iterable_17) {
                validateExpression(interpolation, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
            validateExpression(binary->left, module, diagnostics);
            validateExpression(binary->right, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
            validateExpression(unary->operand, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
            validateExpression(assignment->target, module, diagnostics);
            validateExpression(assignment->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            validateExpression(member->object, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
            validateExpression(index->object, module, diagnostics);
            validateExpression(index->index, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
            validateExpression(call->callee, module, diagnostics);
            const auto& _iterable_18 = call->typeArgs;
            for (const auto& argument : *_iterable_18) {
                validateTypeAnnotation(argument, module, diagnostics);
            }
            const auto& _iterable_19 = call->resolvedGenericTypeArgs;
            for (const auto& argument : *_iterable_19) {
                validateResolved(::app_src_checker_symbols_::optionalResolvedType(argument), call->span, module, std::string("generic call argument"), diagnostics);
            }
            const auto& _iterable_20 = call->args;
            for (const auto& argument : *_iterable_20) {
                validateExpression(argument->value, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
            const auto& _iterable_21 = array->elements;
            for (const auto& item : *_iterable_21) {
                validateExpression(item, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
            if (!doof::is_null(object->spread)) {
                validateExpression(doof::unwrap_optional(object->spread), module, diagnostics);
            }
            const auto& _iterable_22 = object->properties;
            for (const auto& property : *_iterable_22) {
                validateResolved(property->resolvedType, property->span, module, std::string("object property"), diagnostics);
                if (!doof::is_null(property->key)) {
                    validateExpression(doof::unwrap_optional(property->key), module, diagnostics);
                }
                if (!doof::is_null(property->value)) {
                    validateExpression(doof::unwrap_optional(property->value), module, diagnostics);
                }
            }
            if (!doof::is_null(object->resolvedType)) {
                {
                    auto _case_subject = doof::unwrap_optional(object->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        if (doof::is_null(object->resolvedClass)) {
                            addValidationError(module, object->span, std::string("Class object literal has no resolved class"), diagnostics);
                        }
                }
                else {
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
            const auto& _iterable_23 = tuple->elements;
            for (const auto& item : *_iterable_23) {
                validateExpression(item, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
            if (!doof::is_null(lambda->returnType)) {
                validateTypeAnnotation(doof::unwrap_optional(lambda->returnType), module, diagnostics);
            }
            const auto& _iterable_24 = lambda->params;
            for (const auto& parameter : *_iterable_24) {
                if (!doof::is_null(parameter->type_)) {
                    validateTypeAnnotation(doof::unwrap_optional(parameter->type_), module, diagnostics);
                }
                validateResolved(parameter->resolvedType, parameter->span, module, std::string("lambda parameter"), diagnostics);
                if (!doof::is_null(parameter->defaultValue)) {
                    validateExpression(doof::unwrap_optional(parameter->defaultValue), module, diagnostics);
                }
            }
            {
                auto _case_subject = lambda->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                    validateBlock(block, module, diagnostics);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                    validateExpression(expression, module, diagnostics);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
            validateExpression(if_->condition, module, diagnostics);
            validateExpression(if_->then_, module, diagnostics);
            validateExpression(if_->else_, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
            validateExpression(case_->subject, module, diagnostics);
            validateResolved(case_->resolvedType, case_->span, module, std::string("case expression"), diagnostics);
            const auto& _iterable_25 = case_->arms;
            for (const auto& arm : *_iterable_25) {
                const auto& _iterable_26 = arm->patterns;
                for (const auto& pattern : *_iterable_26) {
                    validatePattern(pattern, module, diagnostics);
                }
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                        validateBlock(block, module, diagnostics);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                        validateExpression(bodyExpression, module, diagnostics);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
            validateBlock(yieldBlock->body, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
            validateBlock(catch_->body, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
            if ((construct->type_ != std::string("Success")) && (construct->type_ != std::string("Failure"))) {
                validateResolved(construct->resolvedConstructedType, construct->span, module, std::string("constructed type"), diagnostics);
                if (doof::is_null(construct->resolvedClass)) {
                    addValidationError(module, construct->span, ((std::string("Construction of '") + construct->type_) + std::string("' has no resolved class")), diagnostics);
                } else {
                    const auto constructor = classConstructor(doof::unwrap_optional(construct->resolvedClass));
                    if (((!doof::is_null(constructor)) && doof::is_null(construct->resolvedConstructor)) && !spanInsideFunction(construct->span, doof::unwrap_optional(constructor))) {
                        addValidationError(module, construct->span, ((std::string("Construction of '") + construct->type_) + std::string("' has no resolved constructor")), diagnostics);
                    }
                }
            }
            if (!doof::is_null(construct->resolvedConstructor)) {
                validateResolved(construct->resolvedConstructor->resolvedType, construct->span, module, (std::string("constructor ") + construct->type_), diagnostics);
            }
            const auto& _iterable_27 = construct->typeArgs;
            for (const auto& argument : *_iterable_27) {
                validateTypeAnnotation(argument, module, diagnostics);
            }
            const auto& _iterable_28 = construct->args;
            for (const auto& property : *_iterable_28) {
                validateResolved(property->resolvedType, property->span, module, std::string("constructor property"), diagnostics);
                if (!doof::is_null(property->value)) {
                    validateExpression(doof::unwrap_optional(property->value), module, diagnostics);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                    validateBlock(block, module, diagnostics);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                    validateExpression(inner, module, diagnostics);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
            validateExpression(retire_->actor, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
            const auto& _iterable_29 = actor->args;
            for (const auto& argument : *_iterable_29) {
                validateExpression(argument, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject)) {
            const auto& as_ = std::get<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject);
            validateExpression(as_->expression, module, diagnostics);
            validateTypeAnnotation(as_->targetType, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (doof::is_null(identifier->resolvedBinding)) {
                addValidationError(module, identifier->span, ((std::string("Identifier '") + identifier->name) + std::string("' has no resolved binding")), diagnostics);
            } else {
                validateResolved(doof::optional_value(identifier->resolvedBinding->type_), identifier->span, module, (std::string("binding ") + identifier->name), diagnostics);
            }
    }
    else {
    }
    }
}
std::shared_ptr<::app_src_ast_::FunctionDeclaration> classConstructor(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_) {
    const auto& _iterable_30 = class_->methods;
    for (const auto& method : *_iterable_30) {
        if (method->name == std::string("constructor")) {
            return method;
        }
    }
    return nullptr;
}
bool spanInsideFunction(::app_src_ast_::SourceSpan span, std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn) {
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            return ((span.start.offset >= block->span.start.offset) && (span.end.offset <= block->span.end.offset));
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            return ((span.start.offset >= std::visit([](auto&& _obj) { return _obj->span; }, expression).start.offset) && (span.end.offset <= std::visit([](auto&& _obj) { return _obj->span; }, expression).end.offset));
    }
    }
    return false;
}
void validateTypeAnnotation(std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            validateResolved(named->resolvedType, named->span, module, std::string("type annotation"), diagnostics);
            const auto& _iterable_31 = named->typeArgs;
            for (const auto& argument : *_iterable_31) {
                validateTypeAnnotation(argument, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            validateResolved(array->resolvedType, array->span, module, std::string("type annotation"), diagnostics);
            validateTypeAnnotation(array->elementType, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            validateResolved(union_->resolvedType, union_->span, module, std::string("type annotation"), diagnostics);
            const auto& _iterable_32 = union_->types;
            for (const auto& member : *_iterable_32) {
                validateTypeAnnotation(member, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
            validateResolved(function_->resolvedType, function_->span, module, std::string("type annotation"), diagnostics);
            const auto& _iterable_33 = function_->params;
            for (const auto& parameter : *_iterable_33) {
                validateTypeAnnotation(parameter->type_, module, diagnostics);
            }
            validateTypeAnnotation(function_->returnType, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
            validateResolved(weak_->resolvedType, weak_->span, module, std::string("type annotation"), diagnostics);
            validateTypeAnnotation(weak_->type_, module, diagnostics);
    }
    }
}
void validateResolved(std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, ::app_src_ast_::SourceSpan span, std::string module, std::string owner, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    if (doof::is_null(resolvedType)) {
        addValidationError(module, span, (std::string("Missing resolved type for ") + owner), diagnostics);
        return;
    }
    {
        auto _case_subject = doof::unwrap_optional(resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
            addValidationError(module, span, (std::string("Unknown resolved type for ") + owner), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto& _iterable_34 = class_->typeArgs;
            for (const auto& argument : *_iterable_34) {
                validateResolved(doof::optional_value(argument), span, module, (owner + std::string(" type argument")), diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            validateResolved(doof::optional_value(array->elementType), span, module, (owner + std::string(" element")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            validateResolved(doof::optional_value(map->keyType), span, module, (owner + std::string(" key")), diagnostics);
            validateResolved(doof::optional_value(map->valueType), span, module, (owner + std::string(" value")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            validateResolved(doof::optional_value(set_->elementType), span, module, (owner + std::string(" element")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            validateResolved(doof::optional_value(stream->elementType), span, module, (owner + std::string(" element")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            validateResolved(doof::optional_value(result->valueType), span, module, (owner + std::string(" success")), diagnostics);
            validateResolved(doof::optional_value(result->errorType), span, module, (owner + std::string(" error")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            validateResolved(::app_src_checker_symbols_::optionalResolvedType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)), span, module, (owner + std::string(" actor state")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            validateResolved(doof::optional_value(promise->valueType), span, module, (owner + std::string(" promise value")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            validateResolved(doof::optional_value(weak_->inner), span, module, (owner + std::string(" weak target")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_35 = tuple->elements;
            for (const auto& item : *_iterable_35) {
                validateResolved(doof::optional_value(item), span, module, (owner + std::string(" tuple element")), diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            if (static_cast<int32_t>((union_->types)->size()) == 0) {
                addValidationError(module, span, (std::string("Empty resolved union for ") + owner), diagnostics);
            }
            const auto& _iterable_36 = union_->types;
            for (const auto& member : *_iterable_36) {
                validateResolved(doof::optional_value(member), span, module, (owner + std::string(" union member")), diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_37 = function_->params;
            for (const auto& parameter : *_iterable_37) {
                validateResolved(doof::optional_value(parameter->type_), span, module, (owner + std::string(" parameter")), diagnostics);
            }
            validateResolved(doof::optional_value(function_->returnType), span, module, (owner + std::string(" return")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
            if (!doof::is_null(parameter->constraint)) {
                validateResolved(parameter->constraint, span, module, (owner + std::string(" constraint")), diagnostics);
            }
    }
    else {
    }
    }
}
void addValidationError(std::string module, ::app_src_ast_::SourceSpan span, std::string message, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), ((((message + std::string(" at ")) + doof::to_string(span.start.line)) + std::string(":")) + doof::to_string(span.start.column)), checkerSemanticSpan(span), module, std::string("")));
}
::app_src_semantic_::SemanticSpan checkerSemanticSpan(::app_src_ast_::SourceSpan span) {
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
}
