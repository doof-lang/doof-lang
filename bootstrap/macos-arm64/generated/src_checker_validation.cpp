#include "src_checker_validation.hpp"

namespace app_src_checker_validation_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_symbols_;
#line 40 "/src/checker-validation.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateCheckedTypes(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 41 "/src/checker-validation.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
#line 42 "/src/checker-validation.do"
    const auto& _iterable_2 = result->modules;
    for (const auto& module : *_iterable_2) {
#line 43 "/src/checker-validation.do"
        const auto& _iterable_4 = module->program->statements;
        for (const auto& statement : *_iterable_4) {
#line 43 "/src/checker-validation.do"
            validateStatement(statement, module->path, diagnostics);
        }
    }
#line 45 "/src/checker-validation.do"
    return diagnostics;
}
#line 48 "/src/checker-validation.do"
void validateStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 49 "/src/checker-validation.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 50 "/src/checker-validation.do"
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(const_), const_->resolvedType, const_->type_, module, diagnostics);
#line 50 "/src/checker-validation.do"
            validateExpression(const_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 51 "/src/checker-validation.do"
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(readonly_), readonly_->resolvedType, readonly_->type_, module, diagnostics);
#line 51 "/src/checker-validation.do"
            validateExpression(readonly_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 53 "/src/checker-validation.do"
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), binding->resolvedType, binding->type_, module, diagnostics);
#line 54 "/src/checker-validation.do"
            validateExpression(binding->value, module, diagnostics);
#line 55 "/src/checker-validation.do"
            if (!doof::is_null(binding->else_)) {
#line 55 "/src/checker-validation.do"
                validateBlock(doof::unwrap_optional(binding->else_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 57 "/src/checker-validation.do"
            validateValue(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(let_), let_->resolvedType, let_->type_, module, diagnostics);
#line 57 "/src/checker-validation.do"
            validateExpression(let_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 58 "/src/checker-validation.do"
            validateFunction(fn, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 60 "/src/checker-validation.do"
            if (doof::is_null(class_->resolvedSymbol)) {
#line 60 "/src/checker-validation.do"
                addValidationError(module, class_->span, ((std::string("Class '") + class_->name) + std::string("' has no resolved symbol")), diagnostics);
            }
#line 61 "/src/checker-validation.do"
            validateTypeParameterConstraints(class_->typeParamConstraints, module, diagnostics);
#line 62 "/src/checker-validation.do"
            const auto& _iterable_6 = class_->implements_;
            for (const auto& implementation : *_iterable_6) {
#line 62 "/src/checker-validation.do"
                validateTypeAnnotation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(implementation), module, diagnostics);
            }
#line 63 "/src/checker-validation.do"
            const auto& _iterable_8 = class_->fields;
            for (const auto& field : *_iterable_8) {
#line 64 "/src/checker-validation.do"
                if (!doof::is_null(field->type_)) {
#line 64 "/src/checker-validation.do"
                    validateTypeAnnotation(doof::unwrap_optional(field->type_), module, diagnostics);
                }
#line 65 "/src/checker-validation.do"
                validateResolved(field->resolvedType, field->span, module, (std::string("field ") + class_->name), diagnostics);
#line 66 "/src/checker-validation.do"
                if (!doof::is_null(field->defaultValue)) {
#line 66 "/src/checker-validation.do"
                    validateExpression(doof::unwrap_optional(field->defaultValue), module, diagnostics);
                }
            }
#line 68 "/src/checker-validation.do"
            const auto& _iterable_10 = class_->methods;
            for (const auto& method : *_iterable_10) {
#line 68 "/src/checker-validation.do"
                validateFunction(method, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 71 "/src/checker-validation.do"
            if (doof::is_null(interface_->resolvedSymbol)) {
#line 71 "/src/checker-validation.do"
                addValidationError(module, interface_->span, ((std::string("Interface '") + interface_->name) + std::string("' has no resolved symbol")), diagnostics);
            }
#line 72 "/src/checker-validation.do"
            validateTypeParameterConstraints(interface_->typeParamConstraints, module, diagnostics);
#line 73 "/src/checker-validation.do"
            const auto& _iterable_12 = interface_->fields;
            for (const auto& field : *_iterable_12) {
#line 74 "/src/checker-validation.do"
                validateTypeAnnotation(field->type_, module, diagnostics);
#line 75 "/src/checker-validation.do"
                validateResolved(field->resolvedType, field->span, module, (std::string("interface field ") + interface_->name), diagnostics);
            }
#line 77 "/src/checker-validation.do"
            const auto& _iterable_14 = interface_->methods;
            for (const auto& method : *_iterable_14) {
#line 77 "/src/checker-validation.do"
                validateFunction(method, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 79 "/src/checker-validation.do"
            const auto& _iterable_16 = enum_->variants;
            for (const auto& variant : *_iterable_16) {
#line 79 "/src/checker-validation.do"
                if (!doof::is_null(variant->value)) {
#line 79 "/src/checker-validation.do"
                    validateExpression(doof::unwrap_optional(variant->value), module, diagnostics);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 81 "/src/checker-validation.do"
            validateTypeParameterConstraints(alias->typeParamConstraints, module, diagnostics);
#line 82 "/src/checker-validation.do"
            validateTypeAnnotation(alias->type_, module, diagnostics);
#line 83 "/src/checker-validation.do"
            validateResolved(alias->resolvedType, alias->span, module, (std::string("type alias ") + alias->name), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
#line 86 "/src/checker-validation.do"
            validateExpression(if_->condition, module, diagnostics);
#line 86 "/src/checker-validation.do"
            validateBlock(if_->body, module, diagnostics);
#line 87 "/src/checker-validation.do"
            const auto& _iterable_18 = if_->elseIfs;
            for (const auto& branch : *_iterable_18) {
#line 87 "/src/checker-validation.do"
                validateExpression(branch->condition, module, diagnostics);
#line 87 "/src/checker-validation.do"
                validateBlock(branch->body, module, diagnostics);
            }
#line 88 "/src/checker-validation.do"
            if (!doof::is_null(if_->else_)) {
#line 88 "/src/checker-validation.do"
                validateBlock(doof::unwrap_optional(if_->else_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
#line 91 "/src/checker-validation.do"
            if (doof::is_null(case_->resolvedCompletes)) {
#line 91 "/src/checker-validation.do"
                addValidationError(module, case_->span, std::string("Case statement has no resolved control-flow completion"), diagnostics);
            }
#line 92 "/src/checker-validation.do"
            validateExpression(case_->subject, module, diagnostics);
#line 93 "/src/checker-validation.do"
            const auto& _iterable_20 = case_->arms;
            for (const auto& arm : *_iterable_20) {
#line 94 "/src/checker-validation.do"
                const auto& _iterable_22 = arm->patterns;
                for (const auto& pattern : *_iterable_22) {
#line 94 "/src/checker-validation.do"
                    validatePattern(pattern, module, diagnostics);
                }
#line 95 "/src/checker-validation.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 96 "/src/checker-validation.do"
                        validateBlock(block, module, diagnostics);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 97 "/src/checker-validation.do"
                        validateExpression(expression, module, diagnostics);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
#line 101 "/src/checker-validation.do"
            validateExpression(while_->condition, module, diagnostics);
#line 101 "/src/checker-validation.do"
            validateBlock(while_->body, module, diagnostics);
#line 101 "/src/checker-validation.do"
            if (!doof::is_null(while_->then_)) {
#line 101 "/src/checker-validation.do"
                validateBlock(doof::unwrap_optional(while_->then_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
#line 103 "/src/checker-validation.do"
            if (!doof::is_null(for_->init)) {
#line 103 "/src/checker-validation.do"
                validateStatement(doof::unwrap_optional(for_->init), module, diagnostics);
            }
#line 104 "/src/checker-validation.do"
            if (!doof::is_null(for_->condition)) {
#line 104 "/src/checker-validation.do"
                validateExpression(doof::unwrap_optional(for_->condition), module, diagnostics);
            }
#line 105 "/src/checker-validation.do"
            const auto& _iterable_24 = for_->update;
            for (const auto& update : *_iterable_24) {
#line 105 "/src/checker-validation.do"
                validateExpression(update, module, diagnostics);
            }
#line 106 "/src/checker-validation.do"
            validateBlock(for_->body, module, diagnostics);
#line 106 "/src/checker-validation.do"
            if (!doof::is_null(for_->then_)) {
#line 106 "/src/checker-validation.do"
                validateBlock(doof::unwrap_optional(for_->then_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
#line 108 "/src/checker-validation.do"
            validateExpression(forOf->iterable, module, diagnostics);
#line 108 "/src/checker-validation.do"
            validateBlock(forOf->body, module, diagnostics);
#line 108 "/src/checker-validation.do"
            if (!doof::is_null(forOf->then_)) {
#line 108 "/src/checker-validation.do"
                validateBlock(doof::unwrap_optional(forOf->then_), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
#line 110 "/src/checker-validation.do"
            const auto& _iterable_26 = with_->bindings;
            for (const auto& binding : *_iterable_26) {
#line 111 "/src/checker-validation.do"
                if (!doof::is_null(binding->type_)) {
#line 111 "/src/checker-validation.do"
                    validateTypeAnnotation(doof::unwrap_optional(binding->type_), module, diagnostics);
                }
#line 112 "/src/checker-validation.do"
                validateResolved(binding->resolvedType, binding->span, module, (std::string("with binding ") + binding->name), diagnostics);
#line 113 "/src/checker-validation.do"
                validateExpression(binding->value, module, diagnostics);
            }
#line 115 "/src/checker-validation.do"
            validateBlock(with_->body, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
#line 117 "/src/checker-validation.do"
            if (!doof::is_null(return_->value)) {
#line 117 "/src/checker-validation.do"
                validateExpression(doof::unwrap_optional(return_->value), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
#line 118 "/src/checker-validation.do"
            validateExpression(yield_->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
#line 119 "/src/checker-validation.do"
            validateExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), module, diagnostics);
#line 119 "/src/checker-validation.do"
            validateResolved(assignment->resolvedType, assignment->span, module, std::string("yield-block assignment"), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 120 "/src/checker-validation.do"
            validateExpression(expression->expression, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 121 "/src/checker-validation.do"
            validateExpression(destructuring->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
#line 123 "/src/checker-validation.do"
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 124 "/src/checker-validation.do"
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 125 "/src/checker-validation.do"
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 126 "/src/checker-validation.do"
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 127 "/src/checker-validation.do"
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 128 "/src/checker-validation.do"
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(expression), module, diagnostics);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 129 "/src/checker-validation.do"
                    validateStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(destructuring), module, diagnostics);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 132 "/src/checker-validation.do"
            validateStatement(export_->declaration, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 133 "/src/checker-validation.do"
            validateBlock(block, module, diagnostics);
    }
    else {
    }
    }
}
#line 138 "/src/checker-validation.do"
void validateValue(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 139 "/src/checker-validation.do"
    if (!doof::is_null(annotation)) {
#line 139 "/src/checker-validation.do"
        validateTypeAnnotation(doof::unwrap_optional(annotation), module, diagnostics);
    }
#line 140 "/src/checker-validation.do"
    validateResolved(resolvedType, std::visit([](auto&& _obj) { return _obj->span; }, statement), module, std::string("value"), diagnostics);
}
#line 143 "/src/checker-validation.do"
void validateFunction(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 144 "/src/checker-validation.do"
    validateResolved(fn->resolvedType, fn->span, module, (std::string("function ") + fn->name), diagnostics);
#line 145 "/src/checker-validation.do"
    validateTypeParameterConstraints(fn->typeParamConstraints, module, diagnostics);
#line 146 "/src/checker-validation.do"
    if (!doof::is_null(fn->returnType)) {
#line 146 "/src/checker-validation.do"
        validateTypeAnnotation(doof::unwrap_optional(fn->returnType), module, diagnostics);
    }
#line 147 "/src/checker-validation.do"
    const auto& _iterable_28 = fn->params;
    for (const auto& parameter : *_iterable_28) {
#line 148 "/src/checker-validation.do"
        if (!doof::is_null(parameter->type_)) {
#line 148 "/src/checker-validation.do"
            validateTypeAnnotation(doof::unwrap_optional(parameter->type_), module, diagnostics);
        }
#line 149 "/src/checker-validation.do"
        validateResolved(parameter->resolvedType, parameter->span, module, (std::string("parameter ") + parameter->name), diagnostics);
#line 150 "/src/checker-validation.do"
        if (!doof::is_null(parameter->defaultValue)) {
#line 150 "/src/checker-validation.do"
            validateExpression(doof::unwrap_optional(parameter->defaultValue), module, diagnostics);
        }
    }
#line 152 "/src/checker-validation.do"
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 153 "/src/checker-validation.do"
            validateBlock(block, module, diagnostics);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 154 "/src/checker-validation.do"
            validateExpression(expression, module, diagnostics);
    }
    }
}
#line 158 "/src/checker-validation.do"
void validateTypeParameterConstraints(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& constraints, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 159 "/src/checker-validation.do"
    const auto& _iterable_30 = constraints;
    for (const auto& constraint : *_iterable_30) {
#line 160 "/src/checker-validation.do"
        if (doof::is_null(constraint->type_)) {
#line 160 "/src/checker-validation.do"
            continue;
        }
#line 161 "/src/checker-validation.do"
        {
            auto _case_subject = doof::unwrap_optional(constraint->type_);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 163 "/src/checker-validation.do"
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && ((named->name == std::string("JsonSerializable")) || (named->name == std::string("Reflectable")))) {
#line 163 "/src/checker-validation.do"
                    continue;
                }
        }
        else {
        }
        }
#line 167 "/src/checker-validation.do"
        validateTypeAnnotation(doof::unwrap_optional(constraint->type_), module, diagnostics);
    }
}
#line 171 "/src/checker-validation.do"
void validateBlock(const std::shared_ptr<::app_src_ast_::Block>& block, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 172 "/src/checker-validation.do"
    const auto& _iterable_32 = block->statements;
    for (const auto& statement : *_iterable_32) {
#line 172 "/src/checker-validation.do"
        validateStatement(statement, module, diagnostics);
    }
}
#line 175 "/src/checker-validation.do"
void validatePattern(const std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>& pattern, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 176 "/src/checker-validation.do"
    {
        auto _case_subject = pattern;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
            const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
#line 177 "/src/checker-validation.do"
            validateTypeAnnotation(type_->type_, module, diagnostics);
#line 177 "/src/checker-validation.do"
            validateResolved(type_->resolvedType, type_->span, module, std::string("case pattern"), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 178 "/src/checker-validation.do"
            validateExpression(value->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
            const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
#line 180 "/src/checker-validation.do"
            if (!doof::is_null(range->start)) {
#line 180 "/src/checker-validation.do"
                validateExpression(doof::unwrap_optional(range->start), module, diagnostics);
            }
#line 181 "/src/checker-validation.do"
            if (!doof::is_null(range->end)) {
#line 181 "/src/checker-validation.do"
                validateExpression(doof::unwrap_optional(range->end), module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
    }
    }
}
#line 187 "/src/checker-validation.do"
void validateExpression(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 188 "/src/checker-validation.do"
    validateResolved(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression), std::visit([](auto&& _obj) { return _obj->span; }, expression), module, (std::string("expression ") + std::visit([](auto&& _obj) { return _obj->kind; }, expression)), diagnostics);
#line 189 "/src/checker-validation.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 190 "/src/checker-validation.do"
            const auto& _iterable_34 = string_->interpolations;
            for (const auto& interpolation : *_iterable_34) {
#line 190 "/src/checker-validation.do"
                validateExpression(interpolation, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 191 "/src/checker-validation.do"
            validateExpression(binary->left, module, diagnostics);
#line 191 "/src/checker-validation.do"
            validateExpression(binary->right, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 192 "/src/checker-validation.do"
            validateExpression(unary->operand, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
#line 193 "/src/checker-validation.do"
            validateExpression(assignment->target, module, diagnostics);
#line 193 "/src/checker-validation.do"
            validateExpression(assignment->value, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 195 "/src/checker-validation.do"
            if (member->resolvedNamespaceAccess) {
#line 196 "/src/checker-validation.do"
                if (doof::is_null(member->resolvedNamespaceSymbol)) {
#line 197 "/src/checker-validation.do"
                    addValidationError(module, member->span, ((std::string("Namespace member '") + member->property) + std::string("' has no resolved symbol")), diagnostics);
                }
            } else {
#line 199 "/src/checker-validation.do"
                validateExpression(member->object, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 201 "/src/checker-validation.do"
            validateExpression(index->object, module, diagnostics);
#line 201 "/src/checker-validation.do"
            validateExpression(index->index, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 203 "/src/checker-validation.do"
            validateExpression(call->callee, module, diagnostics);
#line 204 "/src/checker-validation.do"
            const auto& _iterable_36 = call->typeArgs;
            for (const auto& argument : *_iterable_36) {
#line 204 "/src/checker-validation.do"
                validateTypeAnnotation(argument, module, diagnostics);
            }
#line 205 "/src/checker-validation.do"
            const auto& _iterable_38 = call->resolvedGenericTypeArgs;
            for (const auto& argument : *_iterable_38) {
#line 205 "/src/checker-validation.do"
                validateResolved(::app_src_checker_symbols_::optionalResolvedType(argument), call->span, module, std::string("generic call argument"), diagnostics);
            }
#line 206 "/src/checker-validation.do"
            const auto& _iterable_40 = call->args;
            for (const auto& argument : *_iterable_40) {
#line 206 "/src/checker-validation.do"
                validateExpression(argument->value, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 208 "/src/checker-validation.do"
            const auto& _iterable_42 = array->elements;
            for (const auto& item : *_iterable_42) {
#line 208 "/src/checker-validation.do"
                validateExpression(item, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 210 "/src/checker-validation.do"
            if (!doof::is_null(object->spread)) {
#line 210 "/src/checker-validation.do"
                validateExpression(doof::unwrap_optional(object->spread), module, diagnostics);
            }
#line 211 "/src/checker-validation.do"
            const auto& _iterable_44 = object->properties;
            for (const auto& property : *_iterable_44) {
#line 212 "/src/checker-validation.do"
                validateResolved(property->resolvedType, property->span, module, std::string("object property"), diagnostics);
#line 213 "/src/checker-validation.do"
                if (!doof::is_null(property->key)) {
#line 213 "/src/checker-validation.do"
                    validateExpression(doof::unwrap_optional(property->key), module, diagnostics);
                }
#line 214 "/src/checker-validation.do"
                if (!doof::is_null(property->value)) {
#line 214 "/src/checker-validation.do"
                    validateExpression(doof::unwrap_optional(property->value), module, diagnostics);
                }
            }
#line 216 "/src/checker-validation.do"
            if (!doof::is_null(object->resolvedType)) {
#line 217 "/src/checker-validation.do"
                {
                    auto _case_subject = doof::unwrap_optional(object->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 219 "/src/checker-validation.do"
                        if (doof::is_null(object->resolvedClass)) {
#line 219 "/src/checker-validation.do"
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
#line 225 "/src/checker-validation.do"
            const auto& _iterable_46 = tuple->elements;
            for (const auto& item : *_iterable_46) {
#line 225 "/src/checker-validation.do"
                validateExpression(item, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
#line 227 "/src/checker-validation.do"
            if (!doof::is_null(lambda->returnType)) {
#line 227 "/src/checker-validation.do"
                validateTypeAnnotation(doof::unwrap_optional(lambda->returnType), module, diagnostics);
            }
#line 228 "/src/checker-validation.do"
            const auto& _iterable_48 = lambda->params;
            for (const auto& parameter : *_iterable_48) {
#line 229 "/src/checker-validation.do"
                if (!doof::is_null(parameter->type_)) {
#line 229 "/src/checker-validation.do"
                    validateTypeAnnotation(doof::unwrap_optional(parameter->type_), module, diagnostics);
                }
#line 230 "/src/checker-validation.do"
                validateResolved(parameter->resolvedType, parameter->span, module, std::string("lambda parameter"), diagnostics);
#line 231 "/src/checker-validation.do"
                if (!doof::is_null(parameter->defaultValue)) {
#line 231 "/src/checker-validation.do"
                    validateExpression(doof::unwrap_optional(parameter->defaultValue), module, diagnostics);
                }
            }
#line 233 "/src/checker-validation.do"
            {
                auto _case_subject = lambda->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 234 "/src/checker-validation.do"
                    validateBlock(block, module, diagnostics);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 235 "/src/checker-validation.do"
                    validateExpression(expression, module, diagnostics);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
#line 238 "/src/checker-validation.do"
            validateExpression(if_->condition, module, diagnostics);
#line 238 "/src/checker-validation.do"
            validateExpression(if_->then_, module, diagnostics);
#line 238 "/src/checker-validation.do"
            validateExpression(if_->else_, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
#line 240 "/src/checker-validation.do"
            validateExpression(case_->subject, module, diagnostics);
#line 240 "/src/checker-validation.do"
            validateResolved(case_->resolvedType, case_->span, module, std::string("case expression"), diagnostics);
#line 241 "/src/checker-validation.do"
            const auto& _iterable_50 = case_->arms;
            for (const auto& arm : *_iterable_50) {
#line 242 "/src/checker-validation.do"
                const auto& _iterable_52 = arm->patterns;
                for (const auto& pattern : *_iterable_52) {
#line 242 "/src/checker-validation.do"
                    validatePattern(pattern, module, diagnostics);
                }
#line 243 "/src/checker-validation.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 244 "/src/checker-validation.do"
                        validateBlock(block, module, diagnostics);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 245 "/src/checker-validation.do"
                        validateExpression(bodyExpression, module, diagnostics);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
#line 249 "/src/checker-validation.do"
            validateBlock(yieldBlock->body, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
#line 250 "/src/checker-validation.do"
            validateBlock(catch_->body, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 252 "/src/checker-validation.do"
            if ((construct->type_ != std::string("Success")) && (construct->type_ != std::string("Failure"))) {
#line 253 "/src/checker-validation.do"
                validateResolved(construct->resolvedConstructedType, construct->span, module, std::string("constructed type"), diagnostics);
#line 254 "/src/checker-validation.do"
                if (doof::is_null(construct->resolvedClass)) {
#line 254 "/src/checker-validation.do"
                    addValidationError(module, construct->span, ((std::string("Construction of '") + construct->type_) + std::string("' has no resolved class")), diagnostics);
                } else {
#line 256 "/src/checker-validation.do"
                    const auto constructor = classConstructor(doof::unwrap_optional(construct->resolvedClass));
#line 257 "/src/checker-validation.do"
                    if (((!doof::is_null(constructor)) && doof::is_null(construct->resolvedConstructor)) && !spanInsideFunction(construct->span, doof::unwrap_optional(constructor))) {
#line 258 "/src/checker-validation.do"
                        addValidationError(module, construct->span, ((std::string("Construction of '") + construct->type_) + std::string("' has no resolved constructor")), diagnostics);
                    }
                }
            }
#line 262 "/src/checker-validation.do"
            if (!doof::is_null(construct->resolvedConstructor)) {
#line 263 "/src/checker-validation.do"
                validateResolved(construct->resolvedConstructor->resolvedType, construct->span, module, (std::string("constructor ") + construct->type_), diagnostics);
            }
#line 265 "/src/checker-validation.do"
            const auto& _iterable_54 = construct->typeArgs;
            for (const auto& argument : *_iterable_54) {
#line 265 "/src/checker-validation.do"
                validateTypeAnnotation(argument, module, diagnostics);
            }
#line 266 "/src/checker-validation.do"
            const auto& _iterable_56 = construct->args;
            for (const auto& property : *_iterable_56) {
#line 267 "/src/checker-validation.do"
                validateResolved(property->resolvedType, property->span, module, std::string("constructor property"), diagnostics);
#line 268 "/src/checker-validation.do"
                if (!doof::is_null(property->value)) {
#line 268 "/src/checker-validation.do"
                    validateExpression(doof::unwrap_optional(property->value), module, diagnostics);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 272 "/src/checker-validation.do"
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 273 "/src/checker-validation.do"
                    validateBlock(block, module, diagnostics);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 274 "/src/checker-validation.do"
                    validateExpression(inner, module, diagnostics);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
#line 277 "/src/checker-validation.do"
            validateExpression(retire_->actor, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 279 "/src/checker-validation.do"
            if (!doof::is_null(actor->resolvedConstructor)) {
#line 279 "/src/checker-validation.do"
                validateResolved(actor->resolvedConstructor->resolvedType, actor->span, module, std::string("actor constructor"), diagnostics);
            }
#line 280 "/src/checker-validation.do"
            const auto& _iterable_58 = actor->args;
            for (const auto& argument : *_iterable_58) {
#line 280 "/src/checker-validation.do"
                validateExpression(argument, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject)) {
            const auto& as_ = std::get<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject);
#line 282 "/src/checker-validation.do"
            validateExpression(as_->expression, module, diagnostics);
#line 282 "/src/checker-validation.do"
            validateTypeAnnotation(as_->targetType, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 284 "/src/checker-validation.do"
            if (doof::is_null(identifier->resolvedBinding)) {
#line 284 "/src/checker-validation.do"
                addValidationError(module, identifier->span, ((std::string("Identifier '") + identifier->name) + std::string("' has no resolved binding")), diagnostics);
            } else {
#line 285 "/src/checker-validation.do"
                validateResolved(doof::optional_value(identifier->resolvedBinding->type_), identifier->span, module, (std::string("binding ") + identifier->name), diagnostics);
            }
    }
    else {
    }
    }
}
#line 291 "/src/checker-validation.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> classConstructor(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
#line 292 "/src/checker-validation.do"
    const auto& _iterable_60 = class_->methods;
    for (const auto& method : *_iterable_60) {
#line 292 "/src/checker-validation.do"
        if (method->name == std::string("constructor")) {
#line 292 "/src/checker-validation.do"
            return method;
        }
    }
#line 293 "/src/checker-validation.do"
    return nullptr;
}
#line 296 "/src/checker-validation.do"
bool spanInsideFunction(::app_src_ast_::SourceSpan span, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 297 "/src/checker-validation.do"
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 298 "/src/checker-validation.do"
            return ((span.start.offset >= block->span.start.offset) && (span.end.offset <= block->span.end.offset));
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 299 "/src/checker-validation.do"
            return ((span.start.offset >= std::visit([](auto&& _obj) { return _obj->span; }, expression).start.offset) && (span.end.offset <= std::visit([](auto&& _obj) { return _obj->span; }, expression).end.offset));
    }
    }
#line 301 "/src/checker-validation.do"
    return false;
}
#line 304 "/src/checker-validation.do"
void validateTypeAnnotation(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 305 "/src/checker-validation.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 307 "/src/checker-validation.do"
            validateResolved(named->resolvedType, named->span, module, std::string("type annotation"), diagnostics);
#line 308 "/src/checker-validation.do"
            const auto& _iterable_62 = named->typeArgs;
            for (const auto& argument : *_iterable_62) {
#line 308 "/src/checker-validation.do"
                validateTypeAnnotation(argument, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 311 "/src/checker-validation.do"
            validateResolved(array->resolvedType, array->span, module, std::string("type annotation"), diagnostics);
#line 312 "/src/checker-validation.do"
            validateTypeAnnotation(array->elementType, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
#line 315 "/src/checker-validation.do"
            validateResolved(union_->resolvedType, union_->span, module, std::string("type annotation"), diagnostics);
#line 316 "/src/checker-validation.do"
            const auto& _iterable_64 = union_->types;
            for (const auto& member : *_iterable_64) {
#line 316 "/src/checker-validation.do"
                validateTypeAnnotation(member, module, diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
#line 319 "/src/checker-validation.do"
            validateResolved(function_->resolvedType, function_->span, module, std::string("type annotation"), diagnostics);
#line 320 "/src/checker-validation.do"
            const auto& _iterable_66 = function_->params;
            for (const auto& parameter : *_iterable_66) {
#line 320 "/src/checker-validation.do"
                validateTypeAnnotation(parameter->type_, module, diagnostics);
            }
#line 321 "/src/checker-validation.do"
            validateTypeAnnotation(function_->returnType, module, diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
#line 324 "/src/checker-validation.do"
            validateResolved(weak_->resolvedType, weak_->span, module, std::string("type annotation"), diagnostics);
#line 325 "/src/checker-validation.do"
            validateTypeAnnotation(weak_->type_, module, diagnostics);
    }
    }
}
#line 330 "/src/checker-validation.do"
void validateResolved(const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, ::app_src_ast_::SourceSpan span, const std::string& module, const std::string& owner, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 331 "/src/checker-validation.do"
    if (doof::is_null(resolvedType)) {
#line 331 "/src/checker-validation.do"
        addValidationError(module, span, (std::string("Missing resolved type for ") + owner), diagnostics);
#line 331 "/src/checker-validation.do"
        return;
    }
#line 332 "/src/checker-validation.do"
    {
        auto _case_subject = doof::unwrap_optional(resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 333 "/src/checker-validation.do"
            addValidationError(module, span, (std::string("Unknown resolved type for ") + owner), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 334 "/src/checker-validation.do"
            const auto& _iterable_68 = class_->typeArgs;
            for (const auto& argument : *_iterable_68) {
#line 334 "/src/checker-validation.do"
                validateResolved(doof::optional_value(argument), span, module, (owner + std::string(" type argument")), diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 335 "/src/checker-validation.do"
            validateResolved(doof::optional_value(array->elementType), span, module, (owner + std::string(" element")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 336 "/src/checker-validation.do"
            validateResolved(doof::optional_value(map->keyType), span, module, (owner + std::string(" key")), diagnostics);
#line 336 "/src/checker-validation.do"
            validateResolved(doof::optional_value(map->valueType), span, module, (owner + std::string(" value")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 337 "/src/checker-validation.do"
            validateResolved(doof::optional_value(set_->elementType), span, module, (owner + std::string(" element")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 338 "/src/checker-validation.do"
            validateResolved(doof::optional_value(stream->elementType), span, module, (owner + std::string(" element")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 339 "/src/checker-validation.do"
            validateResolved(doof::optional_value(result->valueType), span, module, (owner + std::string(" success")), diagnostics);
#line 339 "/src/checker-validation.do"
            validateResolved(doof::optional_value(result->errorType), span, module, (owner + std::string(" error")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 340 "/src/checker-validation.do"
            validateResolved(::app_src_checker_symbols_::optionalResolvedType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)), span, module, (owner + std::string(" actor state")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 341 "/src/checker-validation.do"
            validateResolved(doof::optional_value(promise->valueType), span, module, (owner + std::string(" promise value")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 342 "/src/checker-validation.do"
            validateResolved(doof::optional_value(weak_->inner), span, module, (owner + std::string(" weak target")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 343 "/src/checker-validation.do"
            const auto& _iterable_70 = tuple->elements;
            for (const auto& item : *_iterable_70) {
#line 343 "/src/checker-validation.do"
                validateResolved(doof::optional_value(item), span, module, (owner + std::string(" tuple element")), diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 345 "/src/checker-validation.do"
            if (static_cast<int32_t>((union_->types)->size()) == 0) {
#line 345 "/src/checker-validation.do"
                addValidationError(module, span, (std::string("Empty resolved union for ") + owner), diagnostics);
            }
#line 346 "/src/checker-validation.do"
            const auto& _iterable_72 = union_->types;
            for (const auto& member : *_iterable_72) {
#line 346 "/src/checker-validation.do"
                validateResolved(doof::optional_value(member), span, module, (owner + std::string(" union member")), diagnostics);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 349 "/src/checker-validation.do"
            const auto& _iterable_74 = function_->params;
            for (const auto& parameter : *_iterable_74) {
#line 349 "/src/checker-validation.do"
                validateResolved(doof::optional_value(parameter->type_), span, module, (owner + std::string(" parameter")), diagnostics);
            }
#line 350 "/src/checker-validation.do"
            validateResolved(doof::optional_value(function_->returnType), span, module, (owner + std::string(" return")), diagnostics);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 352 "/src/checker-validation.do"
            if (!doof::is_null(parameter->constraint)) {
#line 352 "/src/checker-validation.do"
                validateResolved(parameter->constraint, span, module, (owner + std::string(" constraint")), diagnostics);
            }
    }
    else {
    }
    }
}
#line 357 "/src/checker-validation.do"
void addValidationError(const std::string& module, ::app_src_ast_::SourceSpan span, const std::string& message, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 358 "/src/checker-validation.do"
    diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), ((((message + std::string(" at ")) + doof::to_string(span.start.line)) + std::string(":")) + doof::to_string(span.start.column)), checkerSemanticSpan(span), module, std::string("")));
}
#line 361 "/src/checker-validation.do"
::app_src_semantic_::SemanticSpan checkerSemanticSpan(::app_src_ast_::SourceSpan span) {
#line 362 "/src/checker-validation.do"
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
#line 1 "<doof-generated>"
}
