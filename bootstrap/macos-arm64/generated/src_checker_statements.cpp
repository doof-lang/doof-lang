#include "src_checker_statements.hpp"
#include <cmath>
#include "src_semantic.hpp"
#include "src_analyzer.hpp"
#include "src_ast.hpp"
#include "src_checker_types.hpp"
#include "src_json_semantics.hpp"
#include "src_checker_actor_boundary.hpp"
#include "src_checker_actor_lifecycle.hpp"
#include "src_checker_state.hpp"
#include "src_checker_expressions.hpp"
#include "src_checker_literals.hpp"
#include "src_checker_resolution.hpp"
#include "src_checker_common.hpp"
#include "src_checker_symbols.hpp"
#include "src_checker_interfaces.hpp"
#include "src_checker_validation.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_checker_statements_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_expressions_;
using namespace ::app_src_checker_literals_;
using namespace ::app_src_checker_resolution_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_validation_;
bool checkStatement(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(const_), scope, std::string("const"), false);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(readonly_), scope, std::string("readonly"), false);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), scope, std::string("immutable-binding"), false);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(let_), scope, std::string("let"), true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            checkFunction(state, fn, scope, nullptr);
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            checkClass(state, class_, scope);
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            checkInterface(state, interface_, scope);
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            checkEnum(state, enum_, scope);
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            const auto aliasScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
            populateTypeParameters(state, aliasScope, alias->typeParams, alias->typeParamConstraints);
            const auto resolvedAlias = ::app_src_checker_resolution_::resolveType(state, alias->type_, doof::unwrap_optional(state->info), aliasScope);
            (alias->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(resolvedAlias));
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
            const auto conditionType = ::app_src_checker_expressions_::checkExpression(state, if_->condition, scope, std::monostate{});
            ::app_src_checker_common_::requireBool(state, conditionType, std::visit([](auto&& _obj) { return _obj->span; }, if_->condition));
            const auto thenCompletes = checkBlock(state, if_->body, scope);
            auto allComplete = thenCompletes;
            const auto& _iterable_1 = if_->elseIfs;
            for (const auto& branch : *_iterable_1) {
                const auto branchConditionType = ::app_src_checker_expressions_::checkExpression(state, branch->condition, scope, std::monostate{});
                ::app_src_checker_common_::requireBool(state, branchConditionType, std::visit([](auto&& _obj) { return _obj->span; }, branch->condition));
                auto branchCompletes = checkBlock(state, branch->body, scope);
                if (std::visit([](auto&& _obj) { return _obj->kind; }, branchConditionType) == std::string("never")) {
                    (branchCompletes = false);
                }
                (allComplete = (allComplete || branchCompletes));
            }
            if (std::visit([](auto&& _obj) { return _obj->kind; }, conditionType) == std::string("never")) {
                return false;
            }
            if (doof::is_null(if_->else_)) {
                return true;
            }
            const auto elseCompletes = checkBlock(state, doof::unwrap_optional(if_->else_), scope);
            return (allComplete || elseCompletes);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
            return checkCase(state, case_, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
            const auto conditionType = ::app_src_checker_expressions_::checkExpression(state, while_->condition, scope, std::monostate{});
            ::app_src_checker_common_::requireBool(state, conditionType, std::visit([](auto&& _obj) { return _obj->span; }, while_->condition));
            checkBlock(state, while_->body, scope);
            if (!doof::is_null(while_->then_)) {
                checkBlock(state, doof::unwrap_optional(while_->then_), scope);
            }
            if (std::visit([](auto&& _obj) { return _obj->kind; }, conditionType) == std::string("never")) {
                return false;
            }
            {
                auto _case_subject = while_->condition;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
                    const auto& literal = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
                    if (literal->value && !::app_src_checker_symbols_::blockContainsLoopExit(while_->body)) {
                        return false;
                    }
            }
            else {
            }
            }
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
            if (!doof::is_null(for_->init)) {
                checkStatement(state, doof::unwrap_optional(for_->init), scope);
            }
            if (!doof::is_null(for_->condition)) {
                const auto condition = doof::unwrap_optional(for_->condition);
                ::app_src_checker_common_::requireBool(state, ::app_src_checker_expressions_::checkExpression(state, condition, scope, std::monostate{}), std::visit([](auto&& _obj) { return _obj->span; }, condition));
            }
            const auto& _iterable_2 = for_->update;
            for (const auto& update : *_iterable_2) {
                ::app_src_checker_expressions_::checkExpression(state, update, scope, std::monostate{});
            }
            checkBlock(state, for_->body, scope);
            if (!doof::is_null(for_->then_)) {
                checkBlock(state, doof::unwrap_optional(for_->then_), scope);
            }
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
            const auto iterable = ::app_src_checker_expressions_::checkExpression(state, forOf->iterable, scope, std::monostate{});
            const auto element = ::app_src_checker_symbols_::iterableElement(iterable);
            const auto bodyScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
            {
                auto _case_subject = element;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                    const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
                    if (static_cast<int32_t>((tuple->elements)->size()) == static_cast<int32_t>((forOf->bindings)->size())) {
                        for (int32_t i = 0; i < static_cast<int32_t>((forOf->bindings)->size()); ++i) {
                            const auto name = (*forOf->bindings)[i];
                            if (name != std::string("_")) {
                                ::app_src_checker_symbols_::declare(bodyScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("for-binding"), (*tuple->elements)[i], false, ::app_src_checker_validation_::checkerSemanticSpan(forOf->span), state->info->path, nullptr, std::string("")));
                            }
                        }
                    } else {
                        const auto& _iterable_3 = forOf->bindings;
                        for (const auto& name : *_iterable_3) {
                            if (name != std::string("_")) {
                                ::app_src_checker_symbols_::declare(bodyScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("for-binding"), element, false, ::app_src_checker_validation_::checkerSemanticSpan(forOf->span), state->info->path, nullptr, std::string("")));
                            }
                        }
                    }
            }
            else {
                    const auto& _iterable_4 = forOf->bindings;
                    for (const auto& name : *_iterable_4) {
                        if (name != std::string("_")) {
                            ::app_src_checker_symbols_::declare(bodyScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("for-binding"), element, false, ::app_src_checker_validation_::checkerSemanticSpan(forOf->span), state->info->path, nullptr, std::string("")));
                        }
                    }
            }
            }
            checkBlock(state, forOf->body, bodyScope);
            if (!doof::is_null(forOf->then_)) {
                checkBlock(state, doof::unwrap_optional(forOf->then_), scope);
            }
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
            const auto bodyScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
            auto bindingsComplete = true;
            const auto& _iterable_5 = with_->bindings;
            for (const auto& binding : *_iterable_5) {
                const auto valueType = ::app_src_checker_expressions_::checkExpression(state, binding->value, bodyScope, std::monostate{});
                if (std::visit([](auto&& _obj) { return _obj->kind; }, valueType) == std::string("never")) {
                    (bindingsComplete = false);
                }
                const auto declaredType = (doof::is_null(binding->type_) ? valueType : ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(binding->type_), doof::unwrap_optional(state->info), scope));
                (binding->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
                if (!::app_src_checker_types_::isAssignable(valueType, declaredType)) {
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(declaredType)), binding->span);
                }
                ::app_src_checker_symbols_::declare(bodyScope, std::make_shared<::app_src_semantic_::Binding>(binding->name, std::string("with"), declaredType, false, ::app_src_checker_validation_::checkerSemanticSpan(binding->span), state->info->path, nullptr, std::string("")));
            }
            checkBlock(state, with_->body, bodyScope);
            return bindingsComplete;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
            return checkReturn(state, return_, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
            const auto target = ::app_src_checker_symbols_::valueYieldScope(scope);
            if (doof::is_null(target)) {
                ::app_src_checker_common_::typeError(state, std::string("'yield' can only be used inside a value-producing block"), yield_->span);
                ::app_src_checker_expressions_::checkExpression(state, yield_->value, scope, std::monostate{});
                return false;
            }
            const auto expectedYield = target->yieldType;
            const auto valueType = ::app_src_checker_expressions_::checkExpression(state, yield_->value, scope, expectedYield);
            if (doof::is_null(expectedYield)) {
                (target->yieldType = ::app_src_checker_symbols_::optionalResolvedType(valueType));
            } else {
                const auto expectedType = doof::unwrap_optional(expectedYield);
                {
                    auto _case_subject = expectedType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
                        (target->yieldType = ::app_src_checker_symbols_::optionalResolvedType(valueType));
                }
                else {
                        if (::app_src_checker_types_::isAssignable(valueType, expectedType)) {
                        } else if (::app_src_checker_types_::isAssignable(expectedType, valueType)) {
                            (target->yieldType = ::app_src_checker_symbols_::optionalResolvedType(valueType));
                        } else {
                            ::app_src_checker_common_::typeError(state, (((std::string("Cannot yield ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" from block yielding ")) + ::app_src_checker_types_::typeName(expectedType)), yield_->span);
                        }
                }
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
            if (doof::is_null(scope->parent)) {
                ::app_src_checker_common_::typeError(state, std::string("'<-' yield-block reassignment is only allowed for local variables"), assignment->span);
            }
            const auto binding = lookupYieldBinding(scope, assignment->name);
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedType = std::monostate{};
            if (!doof::is_null(binding)) {
                (expectedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
            }
            const auto valueType = ::app_src_checker_expressions_::checkExpression(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), scope, expectedType);
            if (doof::is_null(binding)) {
                ::app_src_checker_common_::typeError(state, ((std::string("Undefined identifier \"") + assignment->name) + std::string("\"")), assignment->span);
                return true;
            }
            if (!binding->mutable_) {
                ::app_src_checker_common_::typeError(state, ((std::string("Cannot assign to \"") + assignment->name) + std::string("\" because it is immutable")), assignment->span);
            }
            if (!::app_src_checker_types_::isAssignable(valueType, binding->type_)) {
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(binding->type_)), assignment->span);
            }
            (assignment->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
            const auto expressionType = ::app_src_checker_expressions_::checkExpression(state, expression->expression, scope, std::monostate{});
            {
                auto _case_subject = expressionType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    ::app_src_checker_common_::typeError(state, std::string("Result value must be handled"), expression->span);
            }
            else {
            }
            }
            return (std::visit([](auto&& _obj) { return _obj->kind; }, expressionType) != std::string("never"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
            checkDestructuring(state, destructuring, scope, std::monostate{});
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            return checkTry(state, try_, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ContinueStatement>>(_case_subject)) {
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BreakStatement>>(_case_subject)) {
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            return checkBlock(state, block, scope);
    }
    else {
            return true;
    }
    }
    doof::unreachable();
    return true;
}
bool checkValueDeclaration(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> declaration, std::shared_ptr<::app_src_semantic_::Scope> scope, std::string kind, bool mutable_) {
    auto name = std::string("");
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation = std::monostate{};
    std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::NoneLiteral>(std::string("none-literal"), std::string("none"), std::monostate{}, std::visit([](auto&& _obj) { return _obj->span; }, declaration)));
    auto span = std::visit([](auto&& _obj) { return _obj->span; }, declaration);
    std::shared_ptr<::app_src_ast_::Block> elseBlock = nullptr;
    std::optional<std::string> failureName = std::nullopt;
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            (name = const_->name);
            (annotation = const_->type_);
            (value = const_->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            (name = readonly_->name);
            (annotation = readonly_->type_);
            (value = readonly_->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            (name = binding->name);
            (annotation = binding->type_);
            (value = binding->value);
            (elseBlock = binding->else_);
            (failureName = binding->failureName);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            (name = let_->name);
            (annotation = let_->type_);
            (value = let_->value);
    }
    else {
            return true;
    }
    }
    {
        auto _case_subject = value;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            if (doof::is_null(scope->parent)) {
                ::app_src_checker_common_::typeError(state, std::string("'<-' yield blocks are only allowed in local declarations"), std::visit([](auto&& _obj) { return _obj->span; }, declaration));
            }
    }
    else {
    }
    }
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferredCollectionType = std::monostate{};
    if ((!doof::is_null(annotation)) && doof::is_null(elseBlock)) {
        (inferredCollectionType = ::app_src_checker_literals_::checkOmittedCollectionLiteral(state, doof::unwrap_optional(annotation), value, scope));
    }
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedValueType = std::monostate{};
    if (((!doof::is_null(annotation)) && doof::is_null(elseBlock)) && doof::is_null(inferredCollectionType)) {
        (expectedValueType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(annotation), doof::unwrap_optional(state->info), scope)));
    }
    auto valueType = (doof::is_null(inferredCollectionType) ? ::app_src_checker_expressions_::checkExpression(state, value, scope, expectedValueType) : doof::unwrap_optional(inferredCollectionType));
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> declaredType = valueType;
    if ((!doof::is_null(annotation)) && doof::is_null(inferredCollectionType)) {
        (declaredType = ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(annotation), doof::unwrap_optional(state->info), scope));
    }
    if (kind == std::string("readonly")) {
        (valueType = ::app_src_checker_types_::applyDeepReadonly(valueType));
        (declaredType = ::app_src_checker_types_::applyDeepReadonly(declaredType));
        (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, value) = ::app_src_checker_symbols_::optionalResolvedType(valueType));
    }
    if ((!doof::is_null(annotation)) && (!doof::is_null(inferredCollectionType))) {
        ::app_src_checker_symbols_::decorateAnnotationWithResolved(doof::unwrap_optional(annotation), declaredType);
    }
    if (!doof::is_null(elseBlock)) {
        std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> narrowedType = ::app_src_checker_types_::unknownType();
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> failureType = std::monostate{};
        auto validElseSubject = true;
        {
            auto _case_subject = valueType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                (narrowedType = result->valueType);
                (failureType = ::app_src_checker_symbols_::optionalResolvedType(result->errorType));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                if (::app_src_checker_expressions_::hasNoneMember(state, union_)) {
                    (narrowedType = ::app_src_checker_expressions_::nonNoneType(state, valueType));
                } else {
                    ::app_src_checker_common_::typeError(state, std::string("declaration-else requires a nullable expression"), span);
                    (validElseSubject = false);
                }
        }
        else {
                ::app_src_checker_common_::typeError(state, std::string("declaration-else requires a Result or nullable expression"), span);
                (validElseSubject = false);
        }
        }
        if (doof::is_null(annotation)) {
            (declaredType = narrowedType);
        } else if (validElseSubject && !::app_src_checker_types_::isAssignable(narrowedType, declaredType)) {
            ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(narrowedType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(declaredType)), span);
        }
        const auto elseScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
        if (!doof::is_null(failureName)) {
            if (doof::is_null(failureType)) {
                ::app_src_checker_common_::typeError(state, std::string("declaration-else failure capture requires a Result expression"), span);
            } else if (failureName.value() != std::string("_")) {
                ::app_src_checker_symbols_::declare(elseScope, std::make_shared<::app_src_semantic_::Binding>(failureName.value(), std::string("else-failure"), doof::unwrap_optional(failureType), false, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, nullptr, std::string("")));
            }
        } else if (name != std::string("_")) {
            ::app_src_checker_symbols_::declare(elseScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("else-subject"), valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, nullptr, std::string("")));
        }
        const auto handlerCompletes = checkBlock(state, doof::unwrap_optional(elseBlock), elseScope);
        if ((name != std::string("_")) && handlerCompletes) {
            ::app_src_checker_common_::typeError(state, std::string("Declaration-else block must exit scope"), elseBlock->span);
        }
    } else if (!::app_src_checker_types_::isAssignable(valueType, declaredType)) {
        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(declaredType)), span);
    }
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            (const_->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            (readonly_->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            (binding->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            (let_->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else {
    }
    }
    if (name != std::string("_")) {
        std::shared_ptr<::app_src_semantic_::Symbol> declarationSymbol = nullptr;
        if (doof::is_null(scope->parent)) {
            (declarationSymbol = ::app_src_checker_symbols_::symbolFor(doof::unwrap_optional(state->info), name));
        }
        ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(name, kind, declaredType, mutable_, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, declarationSymbol, std::string("")));
    }
    return (std::visit([](auto&& _obj) { return _obj->kind; }, valueType) != std::string("never"));
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkFunction(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::shared_ptr<::app_src_semantic_::Scope> outer, std::shared_ptr<::app_src_semantic_::ClassType> owner) {
    const auto scope = std::make_shared<::app_src_semantic_::Scope>(outer, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, doof::optional_value((doof::is_null(owner) ? ::app_src_checker_types_::unknownType() : doof::unwrap_optional(owner))), fn->name, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    populateTypeParameters(state, scope, fn->typeParams, fn->typeParamConstraints);
    if (!doof::is_null(owner)) {
        const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, owner->symbol);
        if (!doof::is_null(declaration)) {
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                    populateTypeParameters(state, scope, classDeclaration->typeParams, classDeclaration->typeParamConstraints);
            }
            else {
            }
            }
        }
    }
    if (!doof::is_null(owner)) {
        addClassFields(state, scope, doof::unwrap_optional(owner));
        ::app_src_checker_expressions_::addClassMethods(state, scope, doof::unwrap_optional(owner));
    }
    const auto returnType = (doof::is_null(fn->returnType) ? ::app_src_checker_types_::noneType() : ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(fn->returnType), doof::unwrap_optional(state->info), scope));
    (scope->returnType = doof::optional_value(returnType));
    const auto functionValue = ::app_src_checker_types_::functionType(functionParameters(state, fn, scope), returnType, fn->typeParams);
    (fn->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(functionValue));
    const auto& _iterable_6 = fn->params;
    for (const auto& parameter : *_iterable_6) {
        const auto parameterType = (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(parameter->type_), doof::unwrap_optional(state->info), scope));
        (parameter->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(parameterType));
        if (!doof::is_null(parameter->defaultValue)) {
            ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(parameter->defaultValue), scope, ::app_src_checker_symbols_::optionalResolvedType(parameterType));
        }
        ::app_src_checker_symbols_::declareShadowing(scope, std::make_shared<::app_src_semantic_::Binding>(parameter->name, std::string("parameter"), parameterType, false, ::app_src_checker_validation_::checkerSemanticSpan(parameter->span), state->info->path, nullptr, std::string("")));
    }
    if (fn->bodyless) {
        return functionValue;
    }
    auto actualReturn = ::app_src_checker_types_::noneType();
    auto completes = true;
    {
        auto _case_subject = fn->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            (actualReturn = ::app_src_checker_expressions_::checkExpression(state, expression, scope, ::app_src_checker_symbols_::optionalResolvedType(returnType)));
            if (doof::is_null(fn->returnType) && !::app_src_checker_types_::isAssignable(actualReturn, returnType)) {
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot return ") + ::app_src_checker_types_::typeName(actualReturn)) + std::string(" from function returning ")) + ::app_src_checker_types_::typeName(returnType)), std::visit([](auto&& _obj) { return _obj->span; }, expression));
            }
            if ((std::visit([](auto&& _obj) { return _obj->kind; }, returnType) == std::string("never")) && (std::visit([](auto&& _obj) { return _obj->kind; }, actualReturn) != std::string("never"))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Cannot return ") + ::app_src_checker_types_::typeName(actualReturn)) + std::string(" from function returning never")), std::visit([](auto&& _obj) { return _obj->span; }, expression));
            }
            (completes = false);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            (completes = checkBlock(state, block, scope));
            (actualReturn = inferredReturn(state, block));
    }
    }
    if ((completes && (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("none"))) && (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("unknown"))) {
        ::app_src_checker_common_::typeError(state, (((std::string("Function '") + fn->name) + std::string("' may complete without returning ")) + ::app_src_checker_types_::typeName(returnType)), fn->span);
    }
    if (!doof::is_null(fn->returnType)) {
        ::app_src_checker_symbols_::decorateAnnotationWithResolved(doof::unwrap_optional(fn->returnType), returnType);
    }
    const auto& _iterable_7 = fn->params;
    for (const auto& parameter : *_iterable_7) {
        if ((!doof::is_null(parameter->type_)) && (!doof::is_null(parameter->resolvedType))) {
            ::app_src_checker_symbols_::decorateAnnotationWithResolved(doof::unwrap_optional(parameter->type_), doof::unwrap_optional(parameter->resolvedType));
        }
    }
    return functionValue;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> functionParameters(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> parameters = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
    const auto& _iterable_8 = fn->params;
    for (const auto& parameter : *_iterable_8) {
        parameters->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, ((!doof::is_null(parameter->resolvedType)) ? doof::unwrap_optional(parameter->resolvedType) : (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(parameter->type_), doof::unwrap_optional(state->info), state->result, scope->typeParams))), (!doof::is_null(parameter->defaultValue))));
    }
    return parameters;
}
void checkClass(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    const auto symbol = ::app_src_checker_symbols_::symbolFor(doof::unwrap_optional(state->info), class_->name);
    if (doof::is_null(symbol)) {
        return;
    }
    const auto classScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    populateTypeParameters(state, classScope, class_->typeParams, class_->typeParamConstraints);
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> ownerTypeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    const auto& _iterable_9 = class_->typeParams;
    for (const auto& typeParam : *_iterable_9) {
        ownerTypeArgs->push_back(::app_src_checker_types_::typeParameter(typeParam, std::string(""), std::monostate{}));
    }
    const auto owner = ::app_src_checker_types_::classType(class_->name, doof::unwrap_optional(symbol), ownerTypeArgs);
    const auto& _iterable_10 = class_->fields;
    for (const auto& field : *_iterable_10) {
        const auto& _iterable_11 = field->names;
        for (const auto& fieldName : *_iterable_11) {
            if (generatedMemberName(fieldName)) {
                ::app_src_checker_common_::typeError(state, ((std::string("Member name \"") + fieldName) + std::string("\" is reserved for compiler-generated reflection and JSON support")), field->span);
            }
        }
        auto fieldType = ::app_src_checker_types_::unknownType();
        if (!doof::is_null(field->type_)) {
            (fieldType = ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(field->type_), doof::unwrap_optional(state->info), classScope));
        } else if (!doof::is_null(field->defaultValue)) {
            (fieldType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(field->defaultValue), classScope, std::monostate{}));
        }
        if (field->readonly_ || field->const_) {
            (fieldType = ::app_src_checker_types_::applyDeepReadonly(fieldType));
        }
        (field->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(fieldType));
        if (class_->struct_ && (field->weak_ || containsWeakType(fieldType))) {
            const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : (*field->names)[0]);
            ::app_src_checker_common_::typeError(state, ((std::string("Struct field \"") + name) + std::string("\" cannot be weak")), field->span);
        }
        if ((!doof::is_null(field->defaultValue)) && (!doof::is_null(field->type_))) {
            ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(field->defaultValue), classScope, ::app_src_checker_symbols_::optionalResolvedType(fieldType));
        }
    }
    const auto& _iterable_12 = class_->methods;
    for (const auto& method : *_iterable_12) {
        if (generatedMemberName(method->name)) {
            ::app_src_checker_common_::typeError(state, ((std::string("Method name \"") + method->name) + std::string("\" is reserved for compiler-generated reflection and JSON support")), method->span);
        }
        checkFunction(state, method, classScope, owner);
    }
    if (!doof::is_null(class_->destructor_)) {
        if (class_->struct_) {
            ::app_src_checker_common_::typeError(state, ((std::string("Struct \"") + class_->name) + std::string("\" cannot declare a destructor")), class_->destructor_->span);
        } else {
            const auto destructorScope = std::make_shared<::app_src_semantic_::Scope>(classScope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), doof::optional_value(::app_src_checker_types_::noneType()), doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(owner), (class_->name + std::string(".destructor")), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
            addClassFields(state, destructorScope, owner);
            ::app_src_checker_expressions_::addClassMethods(state, destructorScope, owner);
            checkBlock(state, doof::unwrap_optional(class_->destructor_), destructorScope);
        }
    }
    const auto& _iterable_13 = class_->implements_;
    for (const auto& interfaceRef : *_iterable_13) {
        const auto target = ::app_src_checker_resolution_::resolveType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(interfaceRef), doof::unwrap_optional(state->info), classScope);
        {
            auto _case_subject = target;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
                if (interfaceRef->name != std::string("Stream")) {
                    ::app_src_checker_common_::typeError(state, ((std::string("Interface \"") + interfaceRef->name) + std::string("\" is not defined")), interfaceRef->span);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
                if (!::app_src_checker_interfaces_::classSatisfiesConcreteInterface(state->result, class_, owner, interface_)) {
                    ::app_src_checker_common_::typeError(state, ((((std::string("Class \"") + class_->name) + std::string("\" does not satisfy interface \"")) + ::app_src_checker_types_::typeName(target)) + std::string("\"")), interfaceRef->span);
                } else {
                    ::app_src_checker_interfaces_::addImplementedInterfaceType(doof::unwrap_optional(symbol), ::app_src_checker_types_::typeName(target));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                if (!::app_src_checker_types_::isAssignable(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(owner), target)) {
                    ::app_src_checker_common_::typeError(state, ((((std::string("Class \"") + class_->name) + std::string("\" does not satisfy interface \"")) + ::app_src_checker_types_::typeName(target)) + std::string("\"")), interfaceRef->span);
                }
        }
        else {
                ::app_src_checker_common_::typeError(state, ((std::string("\"") + interfaceRef->name) + std::string("\" is not an interface")), interfaceRef->span);
        }
        }
    }
}
bool generatedMemberName(std::string name) {
    return (((name == std::string("metadata")) || (name == std::string("toJsonObject"))) || (name == std::string("fromJsonValue")));
}
bool containsWeakType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return containsWeakType(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return (containsWeakType(map->keyType) || containsWeakType(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return containsWeakType(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_14 = tuple->elements;
            for (const auto& item : *_iterable_14) {
                if (containsWeakType(item)) {
                    return true;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_15 = union_->types;
            for (const auto& member : *_iterable_15) {
                if (containsWeakType(member)) {
                    return true;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return (containsWeakType(result->valueType) || containsWeakType(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            return containsWeakType(promise->valueType);
    }
    else {
    }
    }
    return false;
}
void checkInterface(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::InterfaceDeclaration> interface_, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    const auto interfaceScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    populateTypeParameters(state, interfaceScope, interface_->typeParams, interface_->typeParamConstraints);
    const auto& _iterable_16 = interface_->fields;
    for (const auto& field : *_iterable_16) {
        auto fieldType = ::app_src_checker_resolution_::resolveType(state, field->type_, doof::unwrap_optional(state->info), interfaceScope);
        if (field->readonly_) {
            (fieldType = ::app_src_checker_types_::applyDeepReadonly(fieldType));
        }
        (field->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(fieldType));
    }
    const auto& _iterable_17 = interface_->methods;
    for (const auto& method : *_iterable_17) {
        checkFunction(state, method, interfaceScope, nullptr);
    }
}
void populateTypeParameters(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_semantic_::Scope> scope, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints) {
    const auto& _iterable_18 = names;
    for (const auto& name : *_iterable_18) {
        scope->typeParams->push_back(name);
        scope->typeParamConstraintNames->push_back(std::string(""));
        scope->typeParamConstraints->push_back(std::make_shared<::app_src_semantic_::ResolvedTypeConstraint>(std::monostate{}));
    }
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
        if ((index >= static_cast<int32_t>((constraints)->size())) || doof::is_null((*constraints)[index]->type_)) {
            continue;
        }
        const auto annotation = doof::unwrap_optional((*constraints)[index]->type_);
        {
            auto _case_subject = annotation;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && ((named->name == std::string("JsonSerializable")) || (named->name == std::string("Reflectable")))) {
                    ((*scope->typeParamConstraintNames)[index] = named->name);
                    continue;
                }
        }
        else {
        }
        }
        ((*scope->typeParamConstraints)[index]->type_ = doof::optional_value(::app_src_checker_resolution_::resolveType(state, annotation, doof::unwrap_optional(state->info), scope)));
    }
}
void checkEnum(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::EnumDeclaration> enum_, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    const auto& _iterable_19 = enum_->variants;
    for (const auto& variant : *_iterable_19) {
        if (!doof::is_null(variant->value)) {
            const auto valueType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(variant->value), scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::primitive(std::string("int"))));
            if (!::app_src_checker_types_::isAssignable(valueType, ::app_src_checker_types_::primitive(std::string("int")))) {
                ::app_src_checker_common_::typeError(state, std::string("Enum value must be an int"), variant->span);
            }
        }
    }
}
void validateInterfaces(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_analyzer_::ModuleInfo> module) {
    const auto& _iterable_20 = module->symbols;
    for (const auto& symbol : *_iterable_20) {
        if ((symbol->kind != std::string("interface")) || (static_cast<int32_t>((symbol->implementations)->size()) > 0)) {
            continue;
        }
        const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, symbol);
        if (!doof::is_null(declaration)) {
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                    if (static_cast<int32_t>((interface_->typeParams)->size()) == 0) {
                        ::app_src_checker_common_::typeError(state, ((std::string("Cannot emit interface \"") + symbol->name) + std::string("\" without implementing classes")), ::app_src_checker_interfaces_::symbolSpan(module, symbol->name));
                    }
            }
            else {
            }
            }
        }
    }
}
bool checkReturn(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::ReturnStatement> statement, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    if (!doof::is_null(::app_src_checker_symbols_::valueYieldScope(scope))) {
        ::app_src_checker_common_::typeError(state, std::string("'return' cannot be used inside a value-producing block; use 'yield' to produce the block value"), statement->span);
        if (!doof::is_null(statement->value)) {
            ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(statement->value), scope, std::monostate{});
        }
        return false;
    }
    const auto target = ::app_src_checker_symbols_::returnScope(scope);
    if (doof::is_null(target)) {
        ::app_src_checker_common_::typeError(state, std::string("Return is only valid inside a function"), statement->span);
        return false;
    }
    const auto returnType = doof::unwrap_optional(target->returnType);
    (statement->resolvedExpectedType = ::app_src_checker_symbols_::optionalResolvedType(returnType));
    if (doof::is_null(statement->value)) {
        if ((std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("none")) && (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("unknown"))) {
            ::app_src_checker_common_::typeError(state, (std::string("Expected a return value of type ") + ::app_src_checker_types_::typeName(returnType)), statement->span);
        }
    } else {
        const auto valueType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(statement->value), scope, ::app_src_checker_symbols_::optionalResolvedType(returnType));
        if (!::app_src_checker_types_::isAssignable(valueType, returnType)) {
            ::app_src_checker_common_::typeError(state, (((std::string("Cannot return ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" from function returning ")) + ::app_src_checker_types_::typeName(returnType)), statement->span);
        }
    }
    return false;
}
bool checkBlock(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::Block> block, std::shared_ptr<::app_src_semantic_::Scope> parent) {
    const auto scope = std::make_shared<::app_src_semantic_::Scope>(parent, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    auto completes = true;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>> retiredActors = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{});
    const auto& _iterable_21 = block->statements;
    for (const auto& statement : *_iterable_21) {
        if (completes) {
            (completes = checkStatement(state, statement, scope));
        } else {
            auto ignored = checkStatement(state, statement, scope);
        }
        ::app_src_checker_actor_lifecycle_::reportRetiredActorUses(statement, retiredActors, state->info->path, state->diagnostics);
        ::app_src_checker_actor_lifecycle_::collectRetiredActorBindings(statement, retiredActors);
    }
    return completes;
}
bool checkTry(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::TryStatement> statement, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    if ((!doof::is_null(::app_src_checker_symbols_::valueYieldScope(scope))) && doof::is_null(catchErrorScope(scope))) {
        ::app_src_checker_common_::typeError(state, std::string("'try' cannot be used inside a value-producing block; handle the Result outside the block"), statement->span);
    }
    std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::Identifier>(std::string("identifier"), std::string("<try>"), std::monostate{}, nullptr, statement->span));
    {
        auto _case_subject = statement->binding;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            (value = binding->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
            (value = expression->expression);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
            (value = destructuring->value);
    }
    }
    const auto resultValue = ::app_src_checker_expressions_::checkExpression(state, value, scope, std::monostate{});
    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
    {
        auto _case_subject = resultValue;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            const auto collector = catchErrorScope(scope);
            if (!doof::is_null(collector)) {
                collector->catchErrorTypes->push_back(result->errorType);
            }
            {
                auto _case_subject = statement->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, declaration->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
                    (declaration->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
                    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(declaration->name, std::string("const"), result->valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(declaration->span), state->info->path, nullptr, std::string("")));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, declaration->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
                    (declaration->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
                    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(declaration->name, std::string("readonly"), result->valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(declaration->span), state->info->path, nullptr, std::string("")));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, binding->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
                    (binding->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
                    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(binding->name, std::string("immutable-binding"), result->valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(binding->span), state->info->path, nullptr, std::string("")));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, declaration->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
                    (declaration->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
                    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(declaration->name, std::string("let"), result->valueType, true, ::app_src_checker_validation_::checkerSemanticSpan(declaration->span), state->info->path, nullptr, std::string("")));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, expression->expression) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, destructuring->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
                    checkDestructuring(state, destructuring, scope, doof::optional_value(result->valueType));
            }
            }
    }
    else {
            ::app_src_checker_common_::typeError(state, std::string("try requires a Result expression"), std::visit([](auto&& _obj) { return _obj->span; }, value));
    }
    }
    return true;
}
void checkDestructuring(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::DestructuringStatement> statement, std::shared_ptr<::app_src_semantic_::Scope> scope, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> sourceType) {
    const auto valueType = (doof::is_null(sourceType) ? ::app_src_checker_expressions_::checkExpression(state, statement->value, scope, std::monostate{}) : doof::unwrap_optional(sourceType));
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> bindingTypes = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    if (doof::string_startsWith(statement->kind, std::string("array-destructuring"))) {
        {
            auto _case_subject = valueType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                const auto& _iterable_22 = statement->bindings;
                for (const auto& ignored : *_iterable_22) {
                    bindingTypes->push_back(array->elementType);
                }
        }
        else {
                ::app_src_checker_common_::typeError(state, ((std::string("Array destructuring requires a T[] value, but got \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\"")), std::visit([](auto&& _obj) { return _obj->span; }, statement->value));
        }
        }
    } else if (doof::string_startsWith(statement->kind, std::string("positional-destructuring"))) {
        (bindingTypes = positionalDestructuringTypes(state, valueType, std::visit([](auto&& _obj) { return _obj->span; }, statement->value)));
        if (static_cast<int32_t>((bindingTypes)->size()) < static_cast<int32_t>((statement->bindings)->size())) {
            ::app_src_checker_common_::typeError(state, (((std::string("Positional destructuring expected at least ") + doof::to_string(static_cast<int32_t>((statement->bindings)->size()))) + std::string(" values, but got ")) + doof::to_string(static_cast<int32_t>((bindingTypes)->size()))), statement->span);
        }
    }
    if (doof::string_startsWith(statement->kind, std::string("named-destructuring"))) {
        const auto& _iterable_23 = statement->namedBindings;
        for (const auto& named : *_iterable_23) {
            const auto localName = (doof::is_null(named->alias) ? named->name : doof::unwrap_optional(named->alias));
            const auto fieldType = ::app_src_checker_resolution_::memberType(state, valueType, named->name, named->span);
            if (std::visit([](auto&& _obj) { return _obj->kind; }, fieldType) == std::string("unknown")) {
                ::app_src_checker_common_::typeError(state, ((((std::string("Type \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\" has no field \"")) + named->name) + std::string("\"")), named->span);
            }
            if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
                validateDestructuringTarget(state, scope, localName, fieldType, named->span);
            } else {
                declareDestructuredBinding(state, scope, localName, fieldType, statement->bindingKind, named->span);
            }
        }
        return;
    }
    for (int32_t i = 0; i < static_cast<int32_t>((statement->bindings)->size()); ++i) {
        const auto name = (*statement->bindings)[i];
        if (name == std::string("_")) {
            continue;
        }
        const auto bindingType = ((i < static_cast<int32_t>((bindingTypes)->size())) ? (*bindingTypes)[i] : ::app_src_checker_types_::unknownType());
        if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
            validateDestructuringTarget(state, scope, name, bindingType, statement->span);
        } else {
            declareDestructuredBinding(state, scope, name, bindingType, statement->bindingKind, statement->span);
        }
    }
}
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> positionalDestructuringTypes(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType, ::app_src_ast_::SourceSpan span) {
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> result = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    {
        auto _case_subject = valueType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_24 = tuple->elements;
            for (const auto& element : *_iterable_24) {
                result->push_back(element);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
            if (!doof::is_null(declaration)) {
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& owner = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                        const auto& _iterable_25 = owner->fields;
                        for (const auto& field : *_iterable_25) {
                            if (field->static_) {
                                continue;
                            }
                            const auto& _iterable_26 = field->names;
                            for (const auto& name : *_iterable_26) {
                                result->push_back(::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), name, field->span));
                            }
                        }
                }
                else {
                }
                }
            }
    }
    else {
            ::app_src_checker_common_::typeError(state, ((std::string("Positional destructuring requires a tuple or nominal object value, but got \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\"")), span);
    }
    }
    return result;
}
void declareDestructuredBinding(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_semantic_::Scope> scope, std::string name, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::string bindingKind, ::app_src_ast_::SourceSpan span) {
    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(name, ((bindingKind == std::string("let")) ? std::string("let") : std::string("immutable-binding")), type_, (bindingKind == std::string("let")), ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, nullptr, std::string("")));
}
void validateDestructuringTarget(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_semantic_::Scope> scope, std::string name, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> valueType, ::app_src_ast_::SourceSpan span) {
    const auto target = ::app_src_checker_symbols_::lookup(scope, name);
    if (doof::is_null(target)) {
        ::app_src_checker_common_::typeError(state, ((std::string("Destructuring assignment target \"") + name) + std::string("\" is not defined")), span);
        return;
    }
    if (!target->mutable_) {
        ::app_src_checker_common_::typeError(state, ((std::string("Cannot assign to \"") + name) + std::string("\" because it is immutable")), span);
    }
    if (!::app_src_checker_types_::isAssignable(valueType, target->type_)) {
        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(target->type_)), span);
    }
}
std::shared_ptr<::app_src_semantic_::Scope> catchErrorScope(std::shared_ptr<::app_src_semantic_::Scope> scope) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        if (current->capturesTryErrors) {
            return current;
        }
        (current = current->parent);
    }
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Binding> lookupYieldBinding(std::shared_ptr<::app_src_semantic_::Scope> scope, std::string name) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        const auto& _iterable_27 = current->bindings;
        for (const auto& binding : *_iterable_27) {
            if (binding->name == name) {
                return binding;
            }
        }
        (current = current->parent);
    }
    return nullptr;
}
bool checkCase(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::CaseStatement> statement, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    const auto subjectType = ::app_src_checker_expressions_::checkExpression(state, statement->subject, scope, std::monostate{});
    auto exhaustive = false;
    auto hasSuccessArm = false;
    auto hasFailureArm = false;
    auto allArmsReturn = (static_cast<int32_t>((statement->arms)->size()) > 0);
    const auto& _iterable_28 = statement->arms;
    for (const auto& arm : *_iterable_28) {
        const auto armScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
        ::app_src_checker_expressions_::checkCasePatterns(state, arm->patterns, subjectType, armScope);
        const auto& _iterable_29 = arm->patterns;
        for (const auto& pattern : *_iterable_29) {
            {
                auto _case_subject = pattern;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
                    (exhaustive = true);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                    const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
                    {
                        auto _case_subject = type_->type_;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                            if (named->name == std::string("Success")) {
                                (hasSuccessArm = true);
                            }
                            if (named->name == std::string("Failure")) {
                                (hasFailureArm = true);
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
        auto armCompletes = true;
        {
            auto _case_subject = arm->body;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                (armCompletes = checkBlock(state, block, armScope));
        }
        else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                (armCompletes = (std::visit([](auto&& _obj) { return _obj->kind; }, ::app_src_checker_expressions_::checkExpression(state, expression, armScope, std::monostate{})) != std::string("never")));
        }
        }
        if (armCompletes) {
            (allArmsReturn = false);
        }
    }
    {
        auto _case_subject = subjectType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            if (hasSuccessArm && hasFailureArm) {
                (exhaustive = true);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            if (enumCaseExhaustive(state, enum_, statement->arms)) {
                (exhaustive = true);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            if (unionCaseExhaustive(union_, statement->arms)) {
                (exhaustive = true);
            }
    }
    else {
    }
    }
    (statement->resolvedCompletes = ((std::visit([](auto&& _obj) { return _obj->kind; }, subjectType) == std::string("never")) ? false : !(exhaustive && allArmsReturn)));
    return doof::unwrap_optional(statement->resolvedCompletes);
}
bool enumCaseExhaustive(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_semantic_::EnumType> enum_, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CaseArm>>> arms) {
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, enum_->symbol);
    if (doof::is_null(declaration)) {
        return false;
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enumDeclaration = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            const auto& _iterable_30 = enumDeclaration->variants;
            for (const auto& variant : *_iterable_30) {
                auto found = false;
                const auto& _iterable_31 = arms;
                for (const auto& arm : *_iterable_31) {
                    const auto& _iterable_32 = arm->patterns;
                    for (const auto& pattern : *_iterable_32) {
                        {
                            auto _case_subject = pattern;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                                const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
                                {
                                    auto _case_subject = value->value;
                                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
                                        const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
                                        if (dot->name == variant->name) {
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
                if (!found) {
                    return false;
                }
            }
            return true;
    }
    else {
    }
    }
    return false;
}
bool unionCaseExhaustive(std::shared_ptr<::app_src_semantic_::UnionResolvedType> union_, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CaseArm>>> arms) {
    const auto& _iterable_33 = union_->types;
    for (const auto& member : *_iterable_33) {
        auto found = false;
        const auto& _iterable_34 = arms;
        for (const auto& arm : *_iterable_34) {
            const auto& _iterable_35 = arm->patterns;
            for (const auto& pattern : *_iterable_35) {
                {
                    auto _case_subject = pattern;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                        const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
                        if ((!doof::is_null(type_->resolvedType)) && ::app_src_checker_types_::sameType(member, doof::unwrap_optional(type_->resolvedType))) {
                            (found = true);
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                        const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
                        {
                            auto _case_subject = value->value;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
                                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
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
        if (!found) {
            return false;
        }
    }
    return true;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferredReturn(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_ast_::Block> block) {
    const auto& _iterable_36 = block->statements;
    for (const auto& statement : *_iterable_36) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
                const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
                if (doof::is_null(return_->value)) {
                    return ::app_src_checker_types_::noneType();
                }
                const auto value = doof::unwrap_optional(return_->value);
                return (doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, value)) ? ::app_src_checker_types_::unknownType() : doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, value)));
        }
        else {
        }
        }
    }
    return ::app_src_checker_types_::noneType();
}
void addClassFields(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<::app_src_semantic_::Scope> scope, std::shared_ptr<::app_src_semantic_::ClassType> owner) {
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, owner->symbol);
    if (doof::is_null(declaration)) {
        return;
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            const auto& _iterable_37 = class_->fields;
            for (const auto& field : *_iterable_37) {
                const auto& _iterable_38 = field->names;
                for (const auto& name : *_iterable_38) {
                    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("field"), (doof::is_null(field->resolvedType) ? ::app_src_checker_types_::unknownType() : doof::unwrap_optional(field->resolvedType)), (!field->readonly_ && !field->const_), ::app_src_checker_validation_::checkerSemanticSpan(field->span), state->info->path, nullptr, std::string("")));
                }
            }
    }
    else {
    }
    }
}
}
