#include "src_checker_statements.hpp"

namespace app_src_checker_statements_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_expressions_;
using namespace ::app_src_checker_literals_;
using namespace ::app_src_checker_resolution_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_validation_;
#line 47 "/src/checker-statements.do"
bool checkStatement(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_semantic_::Scope>& scope, bool inLoop) {
#line 48 "/src/checker-statements.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 49 "/src/checker-statements.do"
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(const_), scope, std::string("const"), false, inLoop);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 50 "/src/checker-statements.do"
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(readonly_), scope, std::string("readonly"), false, inLoop);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 51 "/src/checker-statements.do"
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), scope, std::string("immutable-binding"), false, inLoop);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 52 "/src/checker-statements.do"
            return checkValueDeclaration(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(let_), scope, std::string("let"), true, inLoop);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 53 "/src/checker-statements.do"
            checkFunction(state, fn, scope, nullptr);
#line 53 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 54 "/src/checker-statements.do"
            checkClass(state, class_, scope);
#line 54 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 55 "/src/checker-statements.do"
            checkInterface(state, interface_, scope);
#line 55 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 56 "/src/checker-statements.do"
            checkEnum(state, enum_, scope);
#line 56 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 58 "/src/checker-statements.do"
            validateUniqueTypeParameters(state, alias->typeParams, alias->span);
#line 59 "/src/checker-statements.do"
            const auto aliasScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 60 "/src/checker-statements.do"
            populateTypeParameters(state, aliasScope, alias->typeParams, alias->typeParamConstraints);
#line 61 "/src/checker-statements.do"
            const auto resolvedAlias = ::app_src_checker_resolution_::resolveType(state, alias->type_, doof::unwrap_optional(state->info), aliasScope);
#line 62 "/src/checker-statements.do"
            (alias->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(resolvedAlias));
#line 63 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
#line 65 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
#line 67 "/src/checker-statements.do"
            const auto conditionType = ::app_src_checker_expressions_::checkExpression(state, if_->condition, scope, std::monostate{});
#line 68 "/src/checker-statements.do"
            ::app_src_checker_common_::requireBool(state, conditionType, std::visit([](auto&& _obj) { return _obj->span; }, if_->condition));
#line 69 "/src/checker-statements.do"
            const auto thenCompletes = checkBlock(state, if_->body, scope, inLoop);
#line 70 "/src/checker-statements.do"
            auto allComplete = thenCompletes;
#line 71 "/src/checker-statements.do"
            const auto& _iterable_2 = if_->elseIfs;
            for (const auto& branch : *_iterable_2) {
#line 72 "/src/checker-statements.do"
                const auto branchConditionType = ::app_src_checker_expressions_::checkExpression(state, branch->condition, scope, std::monostate{});
#line 73 "/src/checker-statements.do"
                ::app_src_checker_common_::requireBool(state, branchConditionType, std::visit([](auto&& _obj) { return _obj->span; }, branch->condition));
#line 74 "/src/checker-statements.do"
                auto branchCompletes = checkBlock(state, branch->body, scope, inLoop);
#line 75 "/src/checker-statements.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, branchConditionType) == std::string("never")) {
#line 75 "/src/checker-statements.do"
                    (branchCompletes = false);
                }
#line 76 "/src/checker-statements.do"
                (allComplete = (allComplete || branchCompletes));
            }
#line 78 "/src/checker-statements.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, conditionType) == std::string("never")) {
#line 78 "/src/checker-statements.do"
                return false;
            }
#line 79 "/src/checker-statements.do"
            if (doof::is_null(if_->else_)) {
#line 79 "/src/checker-statements.do"
                return true;
            }
#line 80 "/src/checker-statements.do"
            const auto elseCompletes = checkBlock(state, doof::unwrap_optional(if_->else_), scope, inLoop);
#line 81 "/src/checker-statements.do"
            return (allComplete || elseCompletes);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
#line 83 "/src/checker-statements.do"
            return checkCase(state, case_, scope, inLoop);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
#line 85 "/src/checker-statements.do"
            const auto conditionType = ::app_src_checker_expressions_::checkExpression(state, while_->condition, scope, std::monostate{});
#line 86 "/src/checker-statements.do"
            ::app_src_checker_common_::requireBool(state, conditionType, std::visit([](auto&& _obj) { return _obj->span; }, while_->condition));
#line 87 "/src/checker-statements.do"
            checkBlock(state, while_->body, scope, true);
#line 88 "/src/checker-statements.do"
            if (!doof::is_null(while_->then_)) {
#line 88 "/src/checker-statements.do"
                checkBlock(state, doof::unwrap_optional(while_->then_), scope, false);
            }
#line 89 "/src/checker-statements.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, conditionType) == std::string("never")) {
#line 89 "/src/checker-statements.do"
                return false;
            }
#line 90 "/src/checker-statements.do"
            {
                auto _case_subject = while_->condition;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
                    const auto& literal = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
#line 92 "/src/checker-statements.do"
                    if (literal->value && !::app_src_checker_symbols_::blockContainsLoopExit(while_->body)) {
#line 92 "/src/checker-statements.do"
                        return false;
                    }
            }
            else {
            }
            }
#line 96 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
#line 99 "/src/checker-statements.do"
            if (!doof::is_null(for_->init)) {
#line 99 "/src/checker-statements.do"
                checkStatement(state, doof::unwrap_optional(for_->init), scope, false);
            }
#line 100 "/src/checker-statements.do"
            if (!doof::is_null(for_->condition)) {
#line 101 "/src/checker-statements.do"
                const auto condition = doof::unwrap_optional(for_->condition);
#line 102 "/src/checker-statements.do"
                ::app_src_checker_common_::requireBool(state, ::app_src_checker_expressions_::checkExpression(state, condition, scope, std::monostate{}), std::visit([](auto&& _obj) { return _obj->span; }, condition));
            }
#line 104 "/src/checker-statements.do"
            const auto& _iterable_4 = for_->update;
            for (const auto& update : *_iterable_4) {
#line 104 "/src/checker-statements.do"
                ::app_src_checker_expressions_::checkExpression(state, update, scope, std::monostate{});
            }
#line 105 "/src/checker-statements.do"
            checkBlock(state, for_->body, scope, true);
#line 106 "/src/checker-statements.do"
            if (!doof::is_null(for_->then_)) {
#line 106 "/src/checker-statements.do"
                checkBlock(state, doof::unwrap_optional(for_->then_), scope, false);
            }
#line 107 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
#line 110 "/src/checker-statements.do"
            const auto iterable = ::app_src_checker_expressions_::checkExpression(state, forOf->iterable, scope, std::monostate{});
#line 111 "/src/checker-statements.do"
            const auto element = ::app_src_checker_symbols_::iterableElement(iterable);
#line 112 "/src/checker-statements.do"
            if (((std::visit([](auto&& _obj) { return _obj->kind; }, iterable) != std::string("unknown")) && (std::visit([](auto&& _obj) { return _obj->kind; }, iterable) != std::string("never"))) && (std::visit([](auto&& _obj) { return _obj->kind; }, element) == std::string("unknown"))) {
#line 113 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, (std::string("For-of requires an array, map, set, Range, or Stream value; got ") + ::app_src_checker_types_::typeName(iterable)), std::visit([](auto&& _obj) { return _obj->span; }, forOf->iterable));
            }
#line 115 "/src/checker-statements.do"
            if (static_cast<int32_t>((forOf->bindings)->size()) > 1) {
#line 116 "/src/checker-statements.do"
                auto validArity = false;
#line 117 "/src/checker-statements.do"
                {
                    auto _case_subject = element;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                        const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 118 "/src/checker-statements.do"
                        (validArity = (static_cast<int32_t>((tuple->elements)->size()) == static_cast<int32_t>((forOf->bindings)->size())));
                }
                else {
                }
                }
#line 121 "/src/checker-statements.do"
                if (!validArity) {
#line 122 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("For-of destructuring requires a tuple with ") + doof::to_string(static_cast<int32_t>((forOf->bindings)->size()))) + std::string(" elements; got ")) + ::app_src_checker_types_::typeName(element)), forOf->span);
                }
            }
#line 125 "/src/checker-statements.do"
            const auto bodyScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 126 "/src/checker-statements.do"
            {
                auto _case_subject = element;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                    const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 128 "/src/checker-statements.do"
                    if (static_cast<int32_t>((tuple->elements)->size()) == static_cast<int32_t>((forOf->bindings)->size())) {
#line 129 "/src/checker-statements.do"
                        for (int32_t i = 0; i < static_cast<int32_t>((forOf->bindings)->size()); ++i) {
#line 130 "/src/checker-statements.do"
                            const auto name = doof::array_at(forOf->bindings, i, "src/checker-statements", 130);
#line 131 "/src/checker-statements.do"
                            if (name != std::string("_")) {
#line 131 "/src/checker-statements.do"
                                declareUserBinding(state, bodyScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("for-binding"), doof::array_at(tuple->elements, i, "src/checker-statements", 131), false, ::app_src_checker_validation_::checkerSemanticSpan(forOf->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), forOf->span);
                            }
                        }
                    } else {
#line 134 "/src/checker-statements.do"
                        const auto& _iterable_7 = forOf->bindings;
                        for (const auto& name : *_iterable_7) {
#line 134 "/src/checker-statements.do"
                            if (name != std::string("_")) {
#line 134 "/src/checker-statements.do"
                                declareUserBinding(state, bodyScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("for-binding"), element, false, ::app_src_checker_validation_::checkerSemanticSpan(forOf->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), forOf->span);
                            }
                        }
                    }
            }
            else {
#line 138 "/src/checker-statements.do"
                    const auto& _iterable_9 = forOf->bindings;
                    for (const auto& name : *_iterable_9) {
#line 138 "/src/checker-statements.do"
                        if (name != std::string("_")) {
#line 138 "/src/checker-statements.do"
                            declareUserBinding(state, bodyScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("for-binding"), element, false, ::app_src_checker_validation_::checkerSemanticSpan(forOf->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), forOf->span);
                        }
                    }
            }
            }
#line 141 "/src/checker-statements.do"
            checkBlock(state, forOf->body, bodyScope, true);
#line 142 "/src/checker-statements.do"
            if (!doof::is_null(forOf->then_)) {
#line 142 "/src/checker-statements.do"
                checkBlock(state, doof::unwrap_optional(forOf->then_), scope, false);
            }
#line 143 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
#line 146 "/src/checker-statements.do"
            const auto bodyScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 147 "/src/checker-statements.do"
            auto bindingsComplete = true;
#line 148 "/src/checker-statements.do"
            const auto& _iterable_11 = with_->bindings;
            for (const auto& binding : *_iterable_11) {
#line 149 "/src/checker-statements.do"
                const auto valueType = ::app_src_checker_expressions_::checkExpression(state, binding->value, bodyScope, std::monostate{});
#line 150 "/src/checker-statements.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, valueType) == std::string("never")) {
#line 150 "/src/checker-statements.do"
                    (bindingsComplete = false);
                }
#line 151 "/src/checker-statements.do"
                const auto declaredType = (doof::is_null(binding->type_) ? valueType : ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(binding->type_), doof::unwrap_optional(state->info), scope));
#line 152 "/src/checker-statements.do"
                (binding->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
#line 153 "/src/checker-statements.do"
                if (!::app_src_checker_types_::isAssignable(valueType, declaredType)) {
#line 153 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(declaredType)), binding->span);
                }
#line 154 "/src/checker-statements.do"
                if (binding->name == std::string("_")) {
#line 155 "/src/checker-statements.do"
                    {
                        auto _case_subject = valueType;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
#line 156 "/src/checker-statements.do"
                            ::app_src_checker_common_::typeError(state, std::string("Scoped discard '_' cannot discard a Result; handle the Result before entering the with scope"), binding->span);
                    }
                    else {
                    }
                    }
                }
#line 160 "/src/checker-statements.do"
                if (binding->name != std::string("_")) {
#line 161 "/src/checker-statements.do"
                    declareUserBinding(state, bodyScope, std::make_shared<::app_src_semantic_::Binding>(binding->name, std::string("with"), declaredType, false, ::app_src_checker_validation_::checkerSemanticSpan(binding->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), binding->span);
                }
            }
#line 164 "/src/checker-statements.do"
            checkBlock(state, with_->body, bodyScope, inLoop);
#line 165 "/src/checker-statements.do"
            return bindingsComplete;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
#line 167 "/src/checker-statements.do"
            return checkReturn(state, return_, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
#line 169 "/src/checker-statements.do"
            const auto target = ::app_src_checker_symbols_::valueYieldScope(scope);
#line 170 "/src/checker-statements.do"
            if (doof::is_null(target)) {
#line 171 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("'yield' can only be used inside a value-producing block"), yield_->span);
#line 172 "/src/checker-statements.do"
                ::app_src_checker_expressions_::checkExpression(state, yield_->value, scope, std::monostate{});
#line 173 "/src/checker-statements.do"
                return false;
            }
#line 175 "/src/checker-statements.do"
            const auto expectedYield = target->yieldType;
#line 176 "/src/checker-statements.do"
            const auto valueType = ::app_src_checker_expressions_::checkExpression(state, yield_->value, scope, expectedYield);
#line 177 "/src/checker-statements.do"
            if (doof::is_null(expectedYield)) {
#line 177 "/src/checker-statements.do"
                (target->yieldType = ::app_src_checker_symbols_::optionalResolvedType(valueType));
            } else {
#line 179 "/src/checker-statements.do"
                const auto expectedType = doof::unwrap_optional(expectedYield);
#line 180 "/src/checker-statements.do"
                {
                    auto _case_subject = expectedType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 181 "/src/checker-statements.do"
                        (target->yieldType = ::app_src_checker_symbols_::optionalResolvedType(valueType));
                }
                else {
#line 183 "/src/checker-statements.do"
                        if (::app_src_checker_types_::isAssignable(valueType, expectedType)) {
                        } else if (::app_src_checker_types_::isAssignable(expectedType, valueType)) {
#line 184 "/src/checker-statements.do"
                            (target->yieldType = ::app_src_checker_symbols_::optionalResolvedType(valueType));
                        } else {
#line 185 "/src/checker-statements.do"
                            ::app_src_checker_common_::typeError(state, (((std::string("Cannot yield ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" from block yielding ")) + ::app_src_checker_types_::typeName(expectedType)), yield_->span);
                        }
                }
                }
            }
#line 189 "/src/checker-statements.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
#line 192 "/src/checker-statements.do"
            if (doof::is_null(scope->parent)) {
#line 193 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("'<-' yield-block reassignment is only allowed for local variables"), assignment->span);
            }
#line 195 "/src/checker-statements.do"
            const auto binding = lookupYieldBinding(scope, assignment->name);
#line 196 "/src/checker-statements.do"
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedType = std::monostate{};
#line 197 "/src/checker-statements.do"
            if (!doof::is_null(binding)) {
#line 197 "/src/checker-statements.do"
                (expectedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
            }
#line 198 "/src/checker-statements.do"
            const auto valueType = ::app_src_checker_expressions_::checkExpression(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), scope, expectedType);
#line 199 "/src/checker-statements.do"
            if (doof::is_null(binding)) {
#line 200 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Undefined identifier \"") + assignment->name) + std::string("\"")), assignment->span);
#line 201 "/src/checker-statements.do"
                return true;
            }
#line 203 "/src/checker-statements.do"
            ::app_src_checker_common_::validateAssignmentBinding(state, doof::unwrap_optional(binding), assignment->span);
#line 204 "/src/checker-statements.do"
            if (!::app_src_checker_types_::isAssignable(valueType, binding->type_)) {
#line 205 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(binding->type_)), assignment->span);
            }
#line 207 "/src/checker-statements.do"
            (assignment->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(binding->type_));
#line 208 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 211 "/src/checker-statements.do"
            const auto expressionType = ::app_src_checker_expressions_::checkExpression(state, expression->expression, scope, std::monostate{});
#line 212 "/src/checker-statements.do"
            {
                auto _case_subject = expressionType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
#line 213 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, std::string("Result value must be handled"), expression->span);
            }
            else {
            }
            }
#line 216 "/src/checker-statements.do"
            return (std::visit([](auto&& _obj) { return _obj->kind; }, expressionType) != std::string("never"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 219 "/src/checker-statements.do"
            checkDestructuring(state, destructuring, scope, std::monostate{});
#line 220 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
#line 222 "/src/checker-statements.do"
            return checkTry(state, try_, scope);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ContinueStatement>>(_case_subject)) {
            const auto& continue_ = std::get<std::shared_ptr<::app_src_ast_::ContinueStatement>>(_case_subject);
#line 224 "/src/checker-statements.do"
            if (!inLoop) {
#line 224 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("Continue is only valid inside a loop"), continue_->span);
            }
#line 225 "/src/checker-statements.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BreakStatement>>(_case_subject)) {
            const auto& break_ = std::get<std::shared_ptr<::app_src_ast_::BreakStatement>>(_case_subject);
#line 228 "/src/checker-statements.do"
            if (!inLoop) {
#line 228 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("Break is only valid inside a loop"), break_->span);
            }
#line 229 "/src/checker-statements.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 231 "/src/checker-statements.do"
            return checkBlock(state, block, scope, inLoop);
    }
    else {
#line 232 "/src/checker-statements.do"
            return true;
    }
    }
    doof::unreachable();
#line 234 "/src/checker-statements.do"
    return true;
}
#line 237 "/src/checker-statements.do"
bool checkValueDeclaration(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& declaration, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& kind, bool mutable_, bool inLoop) {
#line 238 "/src/checker-statements.do"
    auto name = std::string("");
#line 239 "/src/checker-statements.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation = std::monostate{};
#line 240 "/src/checker-statements.do"
    std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::NoneLiteral>(std::string("none-literal"), std::string("none"), std::monostate{}, std::visit([](auto&& _obj) { return _obj->span; }, declaration)));
#line 241 "/src/checker-statements.do"
    auto span = std::visit([](auto&& _obj) { return _obj->span; }, declaration);
#line 242 "/src/checker-statements.do"
    std::shared_ptr<::app_src_ast_::Block> elseBlock = nullptr;
#line 243 "/src/checker-statements.do"
    std::optional<std::string> failureName = std::nullopt;
#line 244 "/src/checker-statements.do"
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 245 "/src/checker-statements.do"
            (name = const_->name);
#line 245 "/src/checker-statements.do"
            (annotation = const_->type_);
#line 245 "/src/checker-statements.do"
            (value = const_->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 246 "/src/checker-statements.do"
            (name = readonly_->name);
#line 246 "/src/checker-statements.do"
            (annotation = readonly_->type_);
#line 246 "/src/checker-statements.do"
            (value = readonly_->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 247 "/src/checker-statements.do"
            (name = binding->name);
#line 247 "/src/checker-statements.do"
            (annotation = binding->type_);
#line 247 "/src/checker-statements.do"
            (value = binding->value);
#line 247 "/src/checker-statements.do"
            (elseBlock = binding->else_);
#line 247 "/src/checker-statements.do"
            (failureName = binding->failureName);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 248 "/src/checker-statements.do"
            (name = let_->name);
#line 248 "/src/checker-statements.do"
            (annotation = let_->type_);
#line 248 "/src/checker-statements.do"
            (value = let_->value);
    }
    else {
#line 249 "/src/checker-statements.do"
            return true;
    }
    }
#line 251 "/src/checker-statements.do"
    {
        auto _case_subject = value;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
#line 253 "/src/checker-statements.do"
            if (doof::is_null(scope->parent)) {
#line 254 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("'<-' yield blocks are only allowed in local declarations"), std::visit([](auto&& _obj) { return _obj->span; }, declaration));
            }
    }
    else {
    }
    }
#line 259 "/src/checker-statements.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferredCollectionType = std::monostate{};
#line 260 "/src/checker-statements.do"
    if ((!doof::is_null(annotation)) && doof::is_null(elseBlock)) {
#line 260 "/src/checker-statements.do"
        (inferredCollectionType = ::app_src_checker_literals_::checkOmittedCollectionLiteral(state, doof::unwrap_optional(annotation), value, scope));
    }
#line 261 "/src/checker-statements.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedValueType = std::monostate{};
#line 262 "/src/checker-statements.do"
    if (((!doof::is_null(annotation)) && doof::is_null(elseBlock)) && doof::is_null(inferredCollectionType)) {
#line 262 "/src/checker-statements.do"
        (expectedValueType = ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(annotation), doof::unwrap_optional(state->info), scope)));
    }
#line 263 "/src/checker-statements.do"
    auto valueType = (doof::is_null(inferredCollectionType) ? ::app_src_checker_expressions_::checkExpression(state, value, scope, expectedValueType) : doof::unwrap_optional(inferredCollectionType));
#line 264 "/src/checker-statements.do"
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> declaredType = valueType;
#line 265 "/src/checker-statements.do"
    if ((!doof::is_null(annotation)) && doof::is_null(inferredCollectionType)) {
#line 265 "/src/checker-statements.do"
        (declaredType = ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(annotation), doof::unwrap_optional(state->info), scope));
    }
#line 266 "/src/checker-statements.do"
    if (kind == std::string("readonly")) {
#line 267 "/src/checker-statements.do"
        (valueType = ::app_src_checker_types_::applyDeepReadonly(valueType));
#line 268 "/src/checker-statements.do"
        (declaredType = ::app_src_checker_types_::applyDeepReadonly(declaredType));
#line 269 "/src/checker-statements.do"
        (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, value) = ::app_src_checker_symbols_::optionalResolvedType(valueType));
    }
#line 271 "/src/checker-statements.do"
    if ((!doof::is_null(annotation)) && (!doof::is_null(inferredCollectionType))) {
#line 271 "/src/checker-statements.do"
        ::app_src_checker_symbols_::decorateAnnotationWithResolved(doof::unwrap_optional(annotation), declaredType);
    }
#line 272 "/src/checker-statements.do"
    if (!doof::is_null(elseBlock)) {
#line 273 "/src/checker-statements.do"
        std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> narrowedType = ::app_src_checker_types_::unknownType();
#line 274 "/src/checker-statements.do"
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> failureType = std::monostate{};
#line 275 "/src/checker-statements.do"
        auto validElseSubject = true;
#line 276 "/src/checker-statements.do"
        {
            auto _case_subject = valueType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 278 "/src/checker-statements.do"
                (narrowedType = result->valueType);
#line 279 "/src/checker-statements.do"
                (failureType = ::app_src_checker_symbols_::optionalResolvedType(result->errorType));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 282 "/src/checker-statements.do"
                if (::app_src_checker_expressions_::hasNoneMember(state, union_)) {
#line 283 "/src/checker-statements.do"
                    (narrowedType = ::app_src_checker_expressions_::nonNoneType(state, valueType));
                } else {
#line 285 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, std::string("declaration-else requires a nullable expression"), span);
#line 286 "/src/checker-statements.do"
                    (validElseSubject = false);
                }
        }
        else {
#line 289 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("declaration-else requires a Result or nullable expression"), span);
#line 289 "/src/checker-statements.do"
                (validElseSubject = false);
        }
        }
#line 291 "/src/checker-statements.do"
        if (doof::is_null(annotation)) {
#line 291 "/src/checker-statements.do"
            (declaredType = narrowedType);
        } else if (validElseSubject && !::app_src_checker_types_::isAssignable(narrowedType, declaredType)) {
#line 293 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(narrowedType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(declaredType)), span);
        }
#line 295 "/src/checker-statements.do"
        const auto elseScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 296 "/src/checker-statements.do"
        if (!doof::is_null(failureName)) {
#line 297 "/src/checker-statements.do"
            if (doof::is_null(failureType)) {
#line 298 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("declaration-else failure capture requires a Result expression"), span);
            } else if (failureName.value() != std::string("_")) {
#line 300 "/src/checker-statements.do"
                ::app_src_checker_symbols_::declare(elseScope, std::make_shared<::app_src_semantic_::Binding>(failureName.value(), std::string("else-failure"), doof::unwrap_optional(failureType), false, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")));
            }
        } else if (name != std::string("_")) {
#line 303 "/src/checker-statements.do"
            ::app_src_checker_symbols_::declare(elseScope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("else-subject"), valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")));
        }
#line 305 "/src/checker-statements.do"
        const auto handlerCompletes = checkBlock(state, doof::unwrap_optional(elseBlock), elseScope, inLoop);
#line 306 "/src/checker-statements.do"
        if ((name != std::string("_")) && handlerCompletes) {
#line 307 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, std::string("Declaration-else block must exit scope"), elseBlock->span);
        }
    } else if (!::app_src_checker_types_::isAssignable(valueType, declaredType)) {
#line 310 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(declaredType)), span);
    }
#line 312 "/src/checker-statements.do"
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 313 "/src/checker-statements.do"
            (const_->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 314 "/src/checker-statements.do"
            (readonly_->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 315 "/src/checker-statements.do"
            (binding->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 316 "/src/checker-statements.do"
            (let_->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(declaredType));
    }
    else {
    }
    }
#line 319 "/src/checker-statements.do"
    if (name != std::string("_")) {
#line 320 "/src/checker-statements.do"
        std::shared_ptr<::app_src_semantic_::Symbol> declarationSymbol = nullptr;
#line 321 "/src/checker-statements.do"
        if (doof::is_null(scope->parent)) {
#line 321 "/src/checker-statements.do"
            (declarationSymbol = ::app_src_checker_symbols_::symbolFor(doof::unwrap_optional(state->info), name));
        }
#line 322 "/src/checker-statements.do"
        const auto bindingKind = ((doof::is_null(scope->parent) && (kind == std::string("let"))) ? std::string("module-let") : kind);
#line 323 "/src/checker-statements.do"
        declareUserBinding(state, scope, std::make_shared<::app_src_semantic_::Binding>(name, bindingKind, declaredType, mutable_, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, declarationSymbol, std::string(""), std::string(""), std::string("")), span);
    }
#line 325 "/src/checker-statements.do"
    return (std::visit([](auto&& _obj) { return _obj->kind; }, valueType) != std::string("never"));
}
#line 328 "/src/checker-statements.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> checkFunction(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_semantic_::Scope>& outer, const std::shared_ptr<::app_src_semantic_::ClassType>& owner) {
#line 329 "/src/checker-statements.do"
    validateUniqueTypeParameters(state, fn->typeParams, fn->span);
#line 330 "/src/checker-statements.do"
    validateTypeParameterShadowing(state, fn->typeParams, outer, fn->span);
#line 331 "/src/checker-statements.do"
    const auto scope = std::make_shared<::app_src_semantic_::Scope>(outer, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, doof::optional_value((doof::is_null(owner) ? ::app_src_checker_types_::unknownType() : doof::unwrap_optional(owner))), fn->name, ((!doof::is_null(owner)) && fn->static_), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 332 "/src/checker-statements.do"
    populateTypeParameters(state, scope, fn->typeParams, fn->typeParamConstraints);
#line 333 "/src/checker-statements.do"
    if (!doof::is_null(owner)) {
#line 334 "/src/checker-statements.do"
        const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, owner->symbol);
#line 335 "/src/checker-statements.do"
        if (!doof::is_null(declaration)) {
#line 336 "/src/checker-statements.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 337 "/src/checker-statements.do"
                    populateTypeParameters(state, scope, classDeclaration->typeParams, classDeclaration->typeParamConstraints);
            }
            else {
            }
            }
        }
    }
#line 342 "/src/checker-statements.do"
    if ((!doof::is_null(owner)) && !fn->static_) {
#line 342 "/src/checker-statements.do"
        addClassFields(state, scope, doof::unwrap_optional(owner));
#line 342 "/src/checker-statements.do"
        ::app_src_checker_expressions_::addClassMethods(state, scope, doof::unwrap_optional(owner));
    }
#line 343 "/src/checker-statements.do"
    const auto returnType = (doof::is_null(fn->returnType) ? ::app_src_checker_types_::noneType() : ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(fn->returnType), doof::unwrap_optional(state->info), scope));
#line 344 "/src/checker-statements.do"
    (scope->returnType = doof::optional_value(returnType));
#line 345 "/src/checker-statements.do"
    const auto functionValue = ::app_src_checker_types_::functionType(functionParameters(state, fn, scope), returnType, fn->typeParams);
#line 346 "/src/checker-statements.do"
    (fn->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(functionValue));
#line 347 "/src/checker-statements.do"
    const auto& _iterable_13 = fn->params;
    for (const auto& parameter : *_iterable_13) {
#line 348 "/src/checker-statements.do"
        const auto parameterType = (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(parameter->type_), doof::unwrap_optional(state->info), scope));
#line 349 "/src/checker-statements.do"
        (parameter->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(parameterType));
#line 350 "/src/checker-statements.do"
        if (!doof::is_null(parameter->defaultValue)) {
#line 351 "/src/checker-statements.do"
            const auto previousAllowsCaller = state->allowsCaller;
#line 352 "/src/checker-statements.do"
            (state->allowsCaller = true);
#line 353 "/src/checker-statements.do"
            const auto defaultType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(parameter->defaultValue), scope, ::app_src_checker_symbols_::optionalResolvedType(parameterType));
#line 354 "/src/checker-statements.do"
            (state->allowsCaller = previousAllowsCaller);
#line 355 "/src/checker-statements.do"
            if (!::app_src_checker_types_::isAssignable(defaultType, parameterType)) {
#line 356 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, (((((std::string("Cannot use default value of type ") + ::app_src_checker_types_::typeName(defaultType)) + std::string(" for parameter '")) + parameter->name) + std::string("' of type ")) + ::app_src_checker_types_::typeName(parameterType)), std::visit([](auto&& _obj) { return _obj->span; }, doof::unwrap_optional(parameter->defaultValue)));
            }
        }
#line 359 "/src/checker-statements.do"
        if (!::app_src_checker_symbols_::declareShadowing(scope, std::make_shared<::app_src_semantic_::Binding>(parameter->name, std::string("parameter"), parameterType, false, ::app_src_checker_validation_::checkerSemanticSpan(parameter->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")))) {
#line 360 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Binding '") + parameter->name) + std::string("' is already declared in this scope")), parameter->span);
        }
    }
#line 363 "/src/checker-statements.do"
    if (fn->bodyless) {
#line 363 "/src/checker-statements.do"
        return functionValue;
    }
#line 364 "/src/checker-statements.do"
    auto actualReturn = ::app_src_checker_types_::noneType();
#line 365 "/src/checker-statements.do"
    auto completes = true;
#line 366 "/src/checker-statements.do"
    {
        auto _case_subject = fn->body;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 368 "/src/checker-statements.do"
            (actualReturn = ::app_src_checker_expressions_::checkExpression(state, expression, scope, ::app_src_checker_symbols_::optionalResolvedType(returnType)));
#line 369 "/src/checker-statements.do"
            if ((std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("never")) && !::app_src_checker_types_::isAssignable(actualReturn, returnType)) {
#line 370 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot return ") + ::app_src_checker_types_::typeName(actualReturn)) + std::string(" from function returning ")) + ::app_src_checker_types_::typeName(returnType)), std::visit([](auto&& _obj) { return _obj->span; }, expression));
            }
#line 372 "/src/checker-statements.do"
            if ((std::visit([](auto&& _obj) { return _obj->kind; }, returnType) == std::string("never")) && (std::visit([](auto&& _obj) { return _obj->kind; }, actualReturn) != std::string("never"))) {
#line 373 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Cannot return ") + ::app_src_checker_types_::typeName(actualReturn)) + std::string(" from function returning never")), std::visit([](auto&& _obj) { return _obj->span; }, expression));
            }
#line 375 "/src/checker-statements.do"
            (completes = false);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 377 "/src/checker-statements.do"
            (completes = checkBlock(state, block, scope, false));
#line 377 "/src/checker-statements.do"
            (actualReturn = inferredReturn(state, block));
    }
    }
#line 379 "/src/checker-statements.do"
    if ((completes && (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("none"))) && (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("unknown"))) {
#line 380 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, (((std::string("Function '") + fn->name) + std::string("' may complete without returning ")) + ::app_src_checker_types_::typeName(returnType)), fn->span);
    }
#line 382 "/src/checker-statements.do"
    if (!doof::is_null(fn->returnType)) {
#line 382 "/src/checker-statements.do"
        ::app_src_checker_symbols_::decorateAnnotationWithResolved(doof::unwrap_optional(fn->returnType), returnType);
    }
#line 383 "/src/checker-statements.do"
    const auto& _iterable_15 = fn->params;
    for (const auto& parameter : *_iterable_15) {
#line 384 "/src/checker-statements.do"
        if ((!doof::is_null(parameter->type_)) && (!doof::is_null(parameter->resolvedType))) {
#line 384 "/src/checker-statements.do"
            ::app_src_checker_symbols_::decorateAnnotationWithResolved(doof::unwrap_optional(parameter->type_), doof::unwrap_optional(parameter->resolvedType));
        }
    }
#line 386 "/src/checker-statements.do"
    return functionValue;
}
#line 389 "/src/checker-statements.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> functionParameters(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 390 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> parameters = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 391 "/src/checker-statements.do"
    const auto& _iterable_17 = fn->params;
    for (const auto& parameter : *_iterable_17) {
#line 392 "/src/checker-statements.do"
        parameters->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, ((!doof::is_null(parameter->resolvedType)) ? doof::unwrap_optional(parameter->resolvedType) : (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(parameter->type_), doof::unwrap_optional(state->info), state->result, scope->typeParams))), (!doof::is_null(parameter->defaultValue))));
    }
#line 398 "/src/checker-statements.do"
    return parameters;
}
#line 401 "/src/checker-statements.do"
void checkClass(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 402 "/src/checker-statements.do"
    validateUniqueTypeParameters(state, class_->typeParams, class_->span);
#line 403 "/src/checker-statements.do"
    validateUniqueClassMembers(state, class_);
#line 404 "/src/checker-statements.do"
    const auto symbol = ::app_src_checker_symbols_::symbolFor(doof::unwrap_optional(state->info), class_->name);
#line 405 "/src/checker-statements.do"
    if (doof::is_null(symbol)) {
#line 405 "/src/checker-statements.do"
        return;
    }
#line 406 "/src/checker-statements.do"
    const auto classScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 407 "/src/checker-statements.do"
    populateTypeParameters(state, classScope, class_->typeParams, class_->typeParamConstraints);
#line 408 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> ownerTypeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 409 "/src/checker-statements.do"
    const auto& _iterable_19 = class_->typeParams;
    for (const auto& typeParam : *_iterable_19) {
#line 409 "/src/checker-statements.do"
        ownerTypeArgs->push_back(::app_src_checker_types_::typeParameter(typeParam, std::string(""), std::monostate{}));
    }
#line 410 "/src/checker-statements.do"
    const auto owner = ::app_src_checker_types_::classType(class_->name, doof::unwrap_optional(symbol), ownerTypeArgs);
#line 411 "/src/checker-statements.do"
    const auto& _iterable_21 = class_->fields;
    for (const auto& field : *_iterable_21) {
#line 412 "/src/checker-statements.do"
        const auto& _iterable_23 = field->names;
        for (const auto& fieldName : *_iterable_23) {
#line 413 "/src/checker-statements.do"
            if (generatedMemberName(fieldName)) {
#line 413 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Member name \"") + fieldName) + std::string("\" is reserved for compiler-generated reflection and JSON support")), field->span);
            }
        }
#line 415 "/src/checker-statements.do"
        auto fieldType = ::app_src_checker_types_::unknownType();
#line 416 "/src/checker-statements.do"
        if (!doof::is_null(field->type_)) {
#line 417 "/src/checker-statements.do"
            (fieldType = ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(field->type_), doof::unwrap_optional(state->info), classScope));
        } else if (!doof::is_null(field->defaultValue)) {
#line 419 "/src/checker-statements.do"
            const auto previousAllowsCaller = state->allowsCaller;
#line 420 "/src/checker-statements.do"
            (state->allowsCaller = true);
#line 421 "/src/checker-statements.do"
            (fieldType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(field->defaultValue), classScope, std::monostate{}));
#line 422 "/src/checker-statements.do"
            (state->allowsCaller = previousAllowsCaller);
        }
#line 424 "/src/checker-statements.do"
        if (field->readonly_ || field->const_) {
#line 424 "/src/checker-statements.do"
            (fieldType = ::app_src_checker_types_::applyDeepReadonly(fieldType));
        }
#line 425 "/src/checker-statements.do"
        (field->resolvedType = ::app_src_checker_symbols_::optionalResolvedType((field->weak_ ? ::app_src_checker_types_::weakType(fieldType) : fieldType)));
#line 426 "/src/checker-statements.do"
        if (field->weak_ && !::app_src_checker_types_::isWeakReferenceTarget(fieldType)) {
#line 427 "/src/checker-statements.do"
            const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : doof::array_at(field->names, 0, "src/checker-statements", 427));
#line 428 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((((std::string("Field \"") + name) + std::string("\" has type \"")) + ::app_src_checker_types_::typeName(fieldType)) + std::string("\", which is not a valid weak reference target")), field->span);
        }
#line 430 "/src/checker-statements.do"
        if (class_->struct_ && (field->weak_ || containsWeakType(fieldType))) {
#line 431 "/src/checker-statements.do"
            const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : doof::array_at(field->names, 0, "src/checker-statements", 431));
#line 432 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Struct field \"") + name) + std::string("\" cannot be weak")), field->span);
        }
#line 434 "/src/checker-statements.do"
        if ((!doof::is_null(field->defaultValue)) && (!doof::is_null(field->type_))) {
#line 435 "/src/checker-statements.do"
            const auto previousAllowsCaller = state->allowsCaller;
#line 436 "/src/checker-statements.do"
            (state->allowsCaller = true);
#line 437 "/src/checker-statements.do"
            const auto defaultType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(field->defaultValue), classScope, ::app_src_checker_symbols_::optionalResolvedType(fieldType));
#line 438 "/src/checker-statements.do"
            (state->allowsCaller = previousAllowsCaller);
#line 439 "/src/checker-statements.do"
            if (!::app_src_checker_types_::isAssignable(defaultType, fieldType)) {
#line 440 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, (((std::string("Cannot use default value of type ") + ::app_src_checker_types_::typeName(defaultType)) + std::string(" for field of type ")) + ::app_src_checker_types_::typeName(fieldType)), std::visit([](auto&& _obj) { return _obj->span; }, doof::unwrap_optional(field->defaultValue)));
            }
        }
    }
#line 444 "/src/checker-statements.do"
    const auto& _iterable_25 = class_->methods;
    for (const auto& method : *_iterable_25) {
#line 445 "/src/checker-statements.do"
        ::app_src_checker_common_::deprecatedClassMethodFunction(state, method);
#line 446 "/src/checker-statements.do"
        if (generatedMemberName(method->name)) {
#line 446 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Method name \"") + method->name) + std::string("\" is reserved for compiler-generated reflection and JSON support")), method->span);
        }
#line 447 "/src/checker-statements.do"
        checkFunction(state, method, classScope, owner);
#line 448 "/src/checker-statements.do"
        if (method->name == std::string("constructor")) {
#line 448 "/src/checker-statements.do"
            validateConstructorDeclaration(state, class_, method, owner);
        }
    }
#line 450 "/src/checker-statements.do"
    const auto streamElement = classStreamElementType(class_);
#line 451 "/src/checker-statements.do"
    if (!doof::is_null(streamElement)) {
#line 451 "/src/checker-statements.do"
        symbol->streamElementTypes->push_back(doof::unwrap_optional(streamElement));
    }
#line 452 "/src/checker-statements.do"
    if (!doof::is_null(class_->destructor_)) {
#line 453 "/src/checker-statements.do"
        if (class_->struct_) {
#line 454 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Struct \"") + class_->name) + std::string("\" cannot declare a destructor")), class_->destructor_->span);
        } else {
#line 456 "/src/checker-statements.do"
            const auto destructorScope = std::make_shared<::app_src_semantic_::Scope>(classScope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), doof::optional_value(::app_src_checker_types_::noneType()), doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(owner), (class_->name + std::string(".destructor")), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 462 "/src/checker-statements.do"
            addClassFields(state, destructorScope, owner);
#line 463 "/src/checker-statements.do"
            ::app_src_checker_expressions_::addClassMethods(state, destructorScope, owner);
#line 464 "/src/checker-statements.do"
            checkBlock(state, doof::unwrap_optional(class_->destructor_), destructorScope, false);
        }
    }
#line 467 "/src/checker-statements.do"
    const auto& _iterable_27 = class_->implements_;
    for (const auto& interfaceRef : *_iterable_27) {
#line 468 "/src/checker-statements.do"
        const auto target = ::app_src_checker_resolution_::resolveType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(interfaceRef), doof::unwrap_optional(state->info), classScope);
#line 469 "/src/checker-statements.do"
        {
            auto _case_subject = target;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 470 "/src/checker-statements.do"
                if (interfaceRef->name != std::string("Stream")) {
#line 470 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Interface \"") + interfaceRef->name) + std::string("\" is not defined")), interfaceRef->span);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 472 "/src/checker-statements.do"
                if (!::app_src_checker_interfaces_::classSatisfiesConcreteInterface(state->result, class_, owner, interface_)) {
#line 473 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, ((((std::string("Class \"") + class_->name) + std::string("\" does not satisfy interface \"")) + ::app_src_checker_types_::typeName(target)) + std::string("\"")), interfaceRef->span);
                } else {
#line 475 "/src/checker-statements.do"
                    ::app_src_checker_interfaces_::addImplementedInterfaceType(doof::unwrap_optional(symbol), ::app_src_checker_types_::typeName(target));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 479 "/src/checker-statements.do"
                if (doof::is_null(streamElement) || !::app_src_checker_types_::sameType(doof::unwrap_optional(streamElement), stream->elementType)) {
#line 480 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, ((((std::string("Class \"") + class_->name) + std::string("\" does not satisfy interface \"")) + ::app_src_checker_types_::typeName(target)) + std::string("\"")), interfaceRef->span);
                }
        }
        else {
#line 483 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("\"") + interfaceRef->name) + std::string("\" is not an interface")), interfaceRef->span);
        }
        }
    }
}
#line 488 "/src/checker-statements.do"
void validateUniqueClassMembers(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
#line 489 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 490 "/src/checker-statements.do"
    const auto& _iterable_29 = class_->fields;
    for (const auto& field : *_iterable_29) {
#line 491 "/src/checker-statements.do"
        const auto& _iterable_31 = field->names;
        for (const auto& name : *_iterable_31) {
#line 492 "/src/checker-statements.do"
            if (::app_src_checker_symbols_::containsString(names, name)) {
#line 492 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((((std::string("Member \"") + name) + std::string("\" is already declared in class \"")) + class_->name) + std::string("\"")), field->span);
            } else {
#line 493 "/src/checker-statements.do"
                names->push_back(name);
            }
        }
    }
#line 496 "/src/checker-statements.do"
    const auto& _iterable_33 = class_->methods;
    for (const auto& method : *_iterable_33) {
#line 497 "/src/checker-statements.do"
        if (::app_src_checker_symbols_::containsString(names, method->name)) {
#line 497 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((((std::string("Member \"") + method->name) + std::string("\" is already declared in class \"")) + class_->name) + std::string("\"")), method->span);
        } else {
#line 498 "/src/checker-statements.do"
            names->push_back(method->name);
        }
    }
}
#line 502 "/src/checker-statements.do"
void validateConstructorDeclaration(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructor, const std::shared_ptr<::app_src_semantic_::ClassType>& owner) {
#line 503 "/src/checker-statements.do"
    if (!constructor->static_) {
#line 504 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, ((std::string("Constructor method for \"") + class_->name) + std::string("\" must be static")), constructor->span);
    }
#line 506 "/src/checker-statements.do"
    if (doof::is_null(constructor->resolvedType)) {
#line 506 "/src/checker-statements.do"
        return;
    }
#line 507 "/src/checker-statements.do"
    {
        auto _case_subject = doof::unwrap_optional(constructor->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 509 "/src/checker-statements.do"
            auto validReturn = ::app_src_checker_types_::sameType(function_->returnType, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(owner));
#line 510 "/src/checker-statements.do"
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 511 "/src/checker-statements.do"
                    (validReturn = ::app_src_checker_types_::sameType(result->valueType, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(owner)));
            }
            else {
            }
            }
#line 514 "/src/checker-statements.do"
            if (!validReturn) {
#line 515 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((((((std::string("Constructor method for \"") + class_->name) + std::string("\" must return ")) + class_->name) + std::string(" or Result<")) + class_->name) + std::string(", E>")), constructor->span);
            }
    }
    else {
    }
    }
}
#line 522 "/src/checker-statements.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> classStreamElementType(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
#line 523 "/src/checker-statements.do"
    std::shared_ptr<::app_src_semantic_::FunctionType> nextType = nullptr;
#line 524 "/src/checker-statements.do"
    std::shared_ptr<::app_src_semantic_::FunctionType> valueType = nullptr;
#line 525 "/src/checker-statements.do"
    const auto& _iterable_35 = class_->methods;
    for (const auto& method : *_iterable_35) {
#line 526 "/src/checker-statements.do"
        if (method->static_ || doof::is_null(method->resolvedType)) {
#line 526 "/src/checker-statements.do"
            continue;
        }
#line 527 "/src/checker-statements.do"
        {
            auto _case_subject = doof::unwrap_optional(method->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 529 "/src/checker-statements.do"
                if (method->name == std::string("next")) {
#line 529 "/src/checker-statements.do"
                    (nextType = function_);
                }
#line 530 "/src/checker-statements.do"
                if (method->name == std::string("value")) {
#line 530 "/src/checker-statements.do"
                    (valueType = function_);
                }
        }
        else {
        }
        }
    }
#line 535 "/src/checker-statements.do"
    if (doof::is_null(nextType) || doof::is_null(valueType)) {
#line 535 "/src/checker-statements.do"
        return std::monostate{};
    }
#line 536 "/src/checker-statements.do"
    if ((static_cast<int32_t>((nextType->params)->size()) != 0) || !::app_src_checker_types_::sameType(nextType->returnType, ::app_src_checker_types_::primitive(std::string("bool")))) {
#line 536 "/src/checker-statements.do"
        return std::monostate{};
    }
#line 537 "/src/checker-statements.do"
    if (static_cast<int32_t>((valueType->params)->size()) != 0) {
#line 537 "/src/checker-statements.do"
        return std::monostate{};
    }
#line 538 "/src/checker-statements.do"
    return doof::optional_value(valueType->returnType);
}
#line 541 "/src/checker-statements.do"
bool generatedMemberName(const std::string& name) {
#line 542 "/src/checker-statements.do"
    return (((name == std::string("metadata")) || (name == std::string("toJsonObject"))) || (name == std::string("fromJsonValue")));
}
#line 545 "/src/checker-statements.do"
bool containsWeakType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 546 "/src/checker-statements.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
#line 547 "/src/checker-statements.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 548 "/src/checker-statements.do"
            return containsWeakType(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 549 "/src/checker-statements.do"
            return (containsWeakType(map->keyType) || containsWeakType(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 550 "/src/checker-statements.do"
            return containsWeakType(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 551 "/src/checker-statements.do"
            const auto& _iterable_37 = tuple->elements;
            for (const auto& item : *_iterable_37) {
#line 551 "/src/checker-statements.do"
                if (containsWeakType(item)) {
#line 551 "/src/checker-statements.do"
                    return true;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 552 "/src/checker-statements.do"
            const auto& _iterable_39 = union_->types;
            for (const auto& member : *_iterable_39) {
#line 552 "/src/checker-statements.do"
                if (containsWeakType(member)) {
#line 552 "/src/checker-statements.do"
                    return true;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 553 "/src/checker-statements.do"
            return (containsWeakType(result->valueType) || containsWeakType(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 554 "/src/checker-statements.do"
            return containsWeakType(promise->valueType);
    }
    else {
    }
    }
#line 557 "/src/checker-statements.do"
    return false;
}
#line 560 "/src/checker-statements.do"
void checkInterface(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& interface_, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 561 "/src/checker-statements.do"
    validateUniqueTypeParameters(state, interface_->typeParams, interface_->span);
#line 562 "/src/checker-statements.do"
    validateUniqueInterfaceMembers(state, interface_);
#line 563 "/src/checker-statements.do"
    const auto interfaceScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 564 "/src/checker-statements.do"
    populateTypeParameters(state, interfaceScope, interface_->typeParams, interface_->typeParamConstraints);
#line 565 "/src/checker-statements.do"
    const auto& _iterable_41 = interface_->fields;
    for (const auto& field : *_iterable_41) {
#line 566 "/src/checker-statements.do"
        auto fieldType = ::app_src_checker_resolution_::resolveType(state, field->type_, doof::unwrap_optional(state->info), interfaceScope);
#line 567 "/src/checker-statements.do"
        if (field->readonly_) {
#line 567 "/src/checker-statements.do"
            (fieldType = ::app_src_checker_types_::applyDeepReadonly(fieldType));
        }
#line 568 "/src/checker-statements.do"
        (field->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(fieldType));
    }
#line 570 "/src/checker-statements.do"
    const auto& _iterable_43 = interface_->methods;
    for (const auto& method : *_iterable_43) {
#line 570 "/src/checker-statements.do"
        checkFunction(state, method, interfaceScope, nullptr);
    }
}
#line 573 "/src/checker-statements.do"
void validateUniqueInterfaceMembers(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& interface_) {
#line 574 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 575 "/src/checker-statements.do"
    const auto& _iterable_45 = interface_->fields;
    for (const auto& field : *_iterable_45) {
#line 576 "/src/checker-statements.do"
        if (::app_src_checker_symbols_::containsString(names, field->name)) {
#line 576 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((((std::string("Member \"") + field->name) + std::string("\" is already declared in interface \"")) + interface_->name) + std::string("\"")), field->span);
        } else {
#line 577 "/src/checker-statements.do"
            names->push_back(field->name);
        }
    }
#line 579 "/src/checker-statements.do"
    const auto& _iterable_47 = interface_->methods;
    for (const auto& method : *_iterable_47) {
#line 580 "/src/checker-statements.do"
        if (::app_src_checker_symbols_::containsString(names, method->name)) {
#line 580 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((((std::string("Member \"") + method->name) + std::string("\" is already declared in interface \"")) + interface_->name) + std::string("\"")), method->span);
        } else {
#line 581 "/src/checker-statements.do"
            names->push_back(method->name);
        }
    }
}
#line 588 "/src/checker-statements.do"
void populateTypeParameters(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& constraints) {
#line 589 "/src/checker-statements.do"
    const auto& _iterable_49 = names;
    for (const auto& name : *_iterable_49) {
#line 590 "/src/checker-statements.do"
        scope->typeParams->push_back(name);
#line 591 "/src/checker-statements.do"
        scope->typeParamConstraintNames->push_back(std::string(""));
#line 592 "/src/checker-statements.do"
        scope->typeParamConstraints->push_back(std::make_shared<::app_src_semantic_::ResolvedTypeConstraint>(std::monostate{}));
    }
#line 594 "/src/checker-statements.do"
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
#line 595 "/src/checker-statements.do"
        if ((index >= static_cast<int32_t>((constraints)->size())) || doof::is_null(doof::array_at(constraints, index, "src/checker-statements", 595)->type_)) {
#line 595 "/src/checker-statements.do"
            continue;
        }
#line 596 "/src/checker-statements.do"
        const auto annotation = doof::unwrap_optional(doof::array_at(constraints, index, "src/checker-statements", 596)->type_);
#line 597 "/src/checker-statements.do"
        {
            auto _case_subject = annotation;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 599 "/src/checker-statements.do"
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && ((named->name == std::string("JsonSerializable")) || (named->name == std::string("Reflectable")))) {
#line 600 "/src/checker-statements.do"
                    (doof::array_at(scope->typeParamConstraintNames, index, "src/checker-statements", 600) = named->name);
#line 601 "/src/checker-statements.do"
                    continue;
                }
        }
        else {
        }
        }
#line 606 "/src/checker-statements.do"
        (doof::array_at(scope->typeParamConstraints, index, "src/checker-statements", 606)->type_ = doof::optional_value(::app_src_checker_resolution_::resolveType(state, annotation, doof::unwrap_optional(state->info), scope)));
    }
}
#line 610 "/src/checker-statements.do"
void validateUniqueTypeParameters(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<std::vector<std::string>>& names, ::app_src_ast_::SourceSpan span) {
#line 611 "/src/checker-statements.do"
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
#line 612 "/src/checker-statements.do"
        for (int32_t previous = 0; previous < index; ++previous) {
#line 613 "/src/checker-statements.do"
            if (doof::array_at(names, previous, "src/checker-statements", 613) == doof::array_at(names, index, "src/checker-statements", 613)) {
#line 614 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Type parameter \"") + doof::array_at(names, index, "src/checker-statements", 614)) + std::string("\" is already declared in this declaration")), span);
#line 615 "/src/checker-statements.do"
                break;
            }
        }
    }
}
#line 621 "/src/checker-statements.do"
void validateTypeParameterShadowing(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<::app_src_semantic_::Scope>& outer, ::app_src_ast_::SourceSpan span) {
#line 622 "/src/checker-statements.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = outer;
#line 623 "/src/checker-statements.do"
    while (!doof::is_null(current)) {
#line 624 "/src/checker-statements.do"
        const auto& _iterable_54 = names;
        for (const auto& name : *_iterable_54) {
#line 625 "/src/checker-statements.do"
            const auto& _iterable_56 = current->typeParams;
            for (const auto& visible : *_iterable_56) {
#line 626 "/src/checker-statements.do"
                if (name == visible) {
#line 627 "/src/checker-statements.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Type parameter \"") + name) + std::string("\" shadows a type parameter from the enclosing declaration")), span);
                }
            }
        }
#line 631 "/src/checker-statements.do"
        (current = current->parent);
    }
}
#line 635 "/src/checker-statements.do"
void checkEnum(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::EnumDeclaration>& enum_, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 636 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 637 "/src/checker-statements.do"
    std::shared_ptr<std::vector<int64_t>> values = std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{});
#line 638 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::string>> valueNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 639 "/src/checker-statements.do"
    auto nextValue = 0LL;
#line 640 "/src/checker-statements.do"
    for (int32_t index = 0; index < static_cast<int32_t>((enum_->variants)->size()); ++index) {
#line 641 "/src/checker-statements.do"
        const auto variant = doof::array_at(enum_->variants, index, "src/checker-statements", 641);
#line 642 "/src/checker-statements.do"
        if (::app_src_checker_symbols_::containsString(names, variant->name)) {
#line 642 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((((std::string("Variant \"") + variant->name) + std::string("\" is already declared in enum \"")) + enum_->name) + std::string("\"")), variant->span);
        } else {
#line 643 "/src/checker-statements.do"
            names->push_back(variant->name);
        }
#line 644 "/src/checker-statements.do"
        std::optional<int64_t> value = nextValue;
#line 645 "/src/checker-statements.do"
        if (!doof::is_null(variant->value)) {
#line 646 "/src/checker-statements.do"
            const auto valueType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(variant->value), scope, ::app_src_checker_symbols_::optionalResolvedType(::app_src_checker_types_::primitive(std::string("int"))));
#line 647 "/src/checker-statements.do"
            if (!::app_src_checker_types_::isAssignable(valueType, ::app_src_checker_types_::primitive(std::string("int")))) {
#line 647 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, std::string("Enum value must be an int"), variant->span);
            }
#line 648 "/src/checker-statements.do"
            (value = enumConstantInt(doof::unwrap_optional(variant->value)));
#line 649 "/src/checker-statements.do"
            if (doof::is_null(value)) {
#line 649 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Enum variant \"") + variant->name) + std::string("\" value must be a compile-time int constant")), std::visit([](auto&& _obj) { return _obj->span; }, doof::unwrap_optional(variant->value)));
            }
        }
#line 651 "/src/checker-statements.do"
        if (!doof::is_null(value)) {
#line 652 "/src/checker-statements.do"
            if ((value.value() < -2147483648LL) || (value.value() > 2147483647LL)) {
#line 653 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Enum variant \"") + variant->name) + std::string("\" value is outside the int range")), variant->span);
            } else {
#line 655 "/src/checker-statements.do"
                for (int32_t previous = 0; previous < static_cast<int32_t>((values)->size()); ++previous) {
#line 656 "/src/checker-statements.do"
                    if (doof::array_at(values, previous, "src/checker-statements", 656) == value.value()) {
#line 657 "/src/checker-statements.do"
                        ::app_src_checker_common_::typeError(state, ((((std::string("Enum variant \"") + variant->name) + std::string("\" duplicates the value of \"")) + doof::array_at(valueNames, previous, "src/checker-statements", 657)) + std::string("\"")), variant->span);
#line 658 "/src/checker-statements.do"
                        break;
                    }
                }
#line 661 "/src/checker-statements.do"
                values->push_back(value.value());
#line 662 "/src/checker-statements.do"
                valueNames->push_back(variant->name);
            }
#line 664 "/src/checker-statements.do"
            (nextValue = (value.value() + 1LL));
        }
    }
}
#line 669 "/src/checker-statements.do"
std::optional<int64_t> enumConstantInt(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 670 "/src/checker-statements.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            const auto& literal = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
#line 671 "/src/checker-statements.do"
            return static_cast<int64_t>(literal->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 673 "/src/checker-statements.do"
            if (!unary->prefix || ((unary->operator_ != std::string("+")) && (unary->operator_ != std::string("-")))) {
#line 673 "/src/checker-statements.do"
                return std::nullopt;
            }
#line 674 "/src/checker-statements.do"
            const auto operand = enumConstantInt(unary->operand);
#line 675 "/src/checker-statements.do"
            if (doof::is_null(operand)) {
#line 675 "/src/checker-statements.do"
                return std::nullopt;
            }
#line 676 "/src/checker-statements.do"
            const auto result = ((unary->operator_ == std::string("-")) ? -operand.value() : operand.value());
#line 677 "/src/checker-statements.do"
            if ((result < -2147483648LL) || (result > 2147483647LL)) {
#line 677 "/src/checker-statements.do"
                return std::nullopt;
            }
#line 678 "/src/checker-statements.do"
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 681 "/src/checker-statements.do"
            const auto left = enumConstantInt(binary->left);
#line 682 "/src/checker-statements.do"
            const auto right = enumConstantInt(binary->right);
#line 683 "/src/checker-statements.do"
            if (doof::is_null(left) || doof::is_null(right)) {
#line 683 "/src/checker-statements.do"
                return std::nullopt;
            }
#line 684 "/src/checker-statements.do"
            auto result = 0LL;
#line 685 "/src/checker-statements.do"
            if (binary->operator_ == std::string("+")) {
#line 685 "/src/checker-statements.do"
                (result = (left.value() + right.value()));
            } else if (binary->operator_ == std::string("-")) {
#line 686 "/src/checker-statements.do"
                (result = (left.value() - right.value()));
            } else if (binary->operator_ == std::string("*")) {
#line 687 "/src/checker-statements.do"
                (result = (left.value() * right.value()));
            } else if (binary->operator_ == std::string("\\")) {
#line 689 "/src/checker-statements.do"
                if (right.value() == 0LL) {
#line 689 "/src/checker-statements.do"
                    return std::nullopt;
                }
#line 690 "/src/checker-statements.do"
                (result = (left.value() / right.value()));
            } else if (binary->operator_ == std::string("%")) {
#line 692 "/src/checker-statements.do"
                if (right.value() == 0LL) {
#line 692 "/src/checker-statements.do"
                    return std::nullopt;
                }
#line 693 "/src/checker-statements.do"
                (result = (left.value() % right.value()));
            } else {
#line 694 "/src/checker-statements.do"
                return std::nullopt;
            }
#line 695 "/src/checker-statements.do"
            if ((result < -2147483648LL) || (result > 2147483647LL)) {
#line 695 "/src/checker-statements.do"
                return std::nullopt;
            }
#line 696 "/src/checker-statements.do"
            return result;
    }
    else {
#line 698 "/src/checker-statements.do"
            return std::nullopt;
    }
    }
    doof::unreachable();
#line 700 "/src/checker-statements.do"
    return std::nullopt;
}
#line 703 "/src/checker-statements.do"
void validateInterfaces(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module) {
#line 704 "/src/checker-statements.do"
    const auto& _iterable_60 = module->symbols;
    for (const auto& symbol : *_iterable_60) {
#line 705 "/src/checker-statements.do"
        if ((symbol->kind != std::string("interface")) || (static_cast<int32_t>((symbol->implementations)->size()) > 0)) {
#line 705 "/src/checker-statements.do"
            continue;
        }
#line 706 "/src/checker-statements.do"
        const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, symbol);
#line 707 "/src/checker-statements.do"
        if (!doof::is_null(declaration)) {
#line 708 "/src/checker-statements.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 709 "/src/checker-statements.do"
                    if (static_cast<int32_t>((interface_->typeParams)->size()) == 0) {
#line 709 "/src/checker-statements.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Cannot emit interface \"") + symbol->name) + std::string("\" without implementing classes")), ::app_src_checker_interfaces_::symbolSpan(module, symbol->name));
                    }
            }
            else {
            }
            }
        }
    }
}
#line 716 "/src/checker-statements.do"
bool checkReturn(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::ReturnStatement>& statement, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 717 "/src/checker-statements.do"
    if (!doof::is_null(::app_src_checker_symbols_::valueYieldScope(scope))) {
#line 718 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, std::string("'return' cannot be used inside a value-producing block; use 'yield' to produce the block value"), statement->span);
#line 719 "/src/checker-statements.do"
        if (!doof::is_null(statement->value)) {
#line 719 "/src/checker-statements.do"
            ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(statement->value), scope, std::monostate{});
        }
#line 720 "/src/checker-statements.do"
        return false;
    }
#line 722 "/src/checker-statements.do"
    const auto target = ::app_src_checker_symbols_::returnScope(scope);
#line 723 "/src/checker-statements.do"
    if (doof::is_null(target)) {
#line 723 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, std::string("Return is only valid inside a function"), statement->span);
#line 723 "/src/checker-statements.do"
        return false;
    }
#line 724 "/src/checker-statements.do"
    const auto returnType = doof::unwrap_optional(target->returnType);
#line 725 "/src/checker-statements.do"
    (statement->resolvedExpectedType = ::app_src_checker_symbols_::optionalResolvedType(returnType));
#line 726 "/src/checker-statements.do"
    if (doof::is_null(statement->value)) {
#line 727 "/src/checker-statements.do"
        if ((std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("none")) && (std::visit([](auto&& _obj) { return _obj->kind; }, returnType) != std::string("unknown"))) {
#line 728 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, (std::string("Expected a return value of type ") + ::app_src_checker_types_::typeName(returnType)), statement->span);
        }
    } else {
#line 731 "/src/checker-statements.do"
        const auto valueType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(statement->value), scope, ::app_src_checker_symbols_::optionalResolvedType(returnType));
#line 732 "/src/checker-statements.do"
        if (!::app_src_checker_types_::isAssignable(valueType, returnType)) {
#line 732 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, (((std::string("Cannot return ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" from function returning ")) + ::app_src_checker_types_::typeName(returnType)), statement->span);
        }
    }
#line 734 "/src/checker-statements.do"
    return false;
}
#line 737 "/src/checker-statements.do"
bool checkBlock(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<::app_src_semantic_::Scope>& parent, bool inLoop) {
#line 738 "/src/checker-statements.do"
    const auto scope = std::make_shared<::app_src_semantic_::Scope>(parent, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 739 "/src/checker-statements.do"
    auto completes = true;
#line 740 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>> retiredActors = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{});
#line 741 "/src/checker-statements.do"
    const auto& _iterable_62 = block->statements;
    for (const auto& statement : *_iterable_62) {
#line 742 "/src/checker-statements.do"
        if (completes) {
#line 743 "/src/checker-statements.do"
            (completes = checkStatement(state, statement, scope, inLoop));
        } else {
#line 749 "/src/checker-statements.do"
            auto ignored = checkStatement(state, statement, scope, inLoop);
        }
#line 751 "/src/checker-statements.do"
        ::app_src_checker_actor_lifecycle_::reportRetiredActorUses(statement, retiredActors, state->info->path, state->diagnostics);
#line 752 "/src/checker-statements.do"
        ::app_src_checker_actor_lifecycle_::collectRetiredActorBindings(statement, retiredActors);
    }
#line 754 "/src/checker-statements.do"
    return completes;
}
#line 757 "/src/checker-statements.do"
bool checkTry(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::TryStatement>& statement, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 758 "/src/checker-statements.do"
    if ((!doof::is_null(::app_src_checker_symbols_::valueYieldScope(scope))) && doof::is_null(catchErrorScope(scope))) {
#line 759 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, std::string("'try' cannot be used inside a value-producing block; handle the Result outside the block"), statement->span);
    }
#line 761 "/src/checker-statements.do"
    std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::Identifier>(std::string("identifier"), std::string("<try>"), std::monostate{}, nullptr, statement->span));
#line 762 "/src/checker-statements.do"
    {
        auto _case_subject = statement->binding;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 763 "/src/checker-statements.do"
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 764 "/src/checker-statements.do"
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 765 "/src/checker-statements.do"
            (value = binding->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 766 "/src/checker-statements.do"
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 767 "/src/checker-statements.do"
            (value = expression->expression);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 768 "/src/checker-statements.do"
            (value = destructuring->value);
    }
    }
#line 770 "/src/checker-statements.do"
    const auto resultValue = ::app_src_checker_expressions_::checkExpression(state, value, scope, std::monostate{});
#line 771 "/src/checker-statements.do"
    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
#line 772 "/src/checker-statements.do"
    {
        auto _case_subject = resultValue;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 774 "/src/checker-statements.do"
            const auto collector = catchErrorScope(scope);
#line 775 "/src/checker-statements.do"
            if (!doof::is_null(collector)) {
#line 775 "/src/checker-statements.do"
                collector->catchErrorTypes->push_back(result->errorType);
            }
#line 776 "/src/checker-statements.do"
            {
                auto _case_subject = statement->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 778 "/src/checker-statements.do"
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, declaration->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
#line 779 "/src/checker-statements.do"
                    (declaration->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
#line 780 "/src/checker-statements.do"
                    declareUserBinding(state, scope, std::make_shared<::app_src_semantic_::Binding>(declaration->name, std::string("const"), result->valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(declaration->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), declaration->span);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 783 "/src/checker-statements.do"
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, declaration->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
#line 784 "/src/checker-statements.do"
                    (declaration->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
#line 785 "/src/checker-statements.do"
                    declareUserBinding(state, scope, std::make_shared<::app_src_semantic_::Binding>(declaration->name, std::string("readonly"), result->valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(declaration->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), declaration->span);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 788 "/src/checker-statements.do"
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, binding->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
#line 789 "/src/checker-statements.do"
                    (binding->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
#line 790 "/src/checker-statements.do"
                    declareUserBinding(state, scope, std::make_shared<::app_src_semantic_::Binding>(binding->name, std::string("immutable-binding"), result->valueType, false, ::app_src_checker_validation_::checkerSemanticSpan(binding->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), binding->span);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 796 "/src/checker-statements.do"
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, declaration->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
#line 797 "/src/checker-statements.do"
                    (declaration->resolvedType = ::app_src_checker_symbols_::optionalResolvedType(result->valueType));
#line 798 "/src/checker-statements.do"
                    declareUserBinding(state, scope, std::make_shared<::app_src_semantic_::Binding>(declaration->name, std::string("let"), result->valueType, true, ::app_src_checker_validation_::checkerSemanticSpan(declaration->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), declaration->span);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 800 "/src/checker-statements.do"
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, expression->expression) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 802 "/src/checker-statements.do"
                    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, destructuring->value) = ::app_src_checker_symbols_::optionalResolvedType(resultValue));
#line 803 "/src/checker-statements.do"
                    checkDestructuring(state, destructuring, scope, doof::optional_value(result->valueType));
            }
            }
    }
    else {
#line 807 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, std::string("try requires a Result expression"), std::visit([](auto&& _obj) { return _obj->span; }, value));
    }
    }
#line 809 "/src/checker-statements.do"
    return true;
}
#line 813 "/src/checker-statements.do"
void checkDestructuring(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::DestructuringStatement>& statement, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& sourceType) {
#line 814 "/src/checker-statements.do"
    const auto valueType = (doof::is_null(sourceType) ? ::app_src_checker_expressions_::checkExpression(state, statement->value, scope, std::monostate{}) : doof::unwrap_optional(sourceType));
#line 815 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> bindingTypes = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 817 "/src/checker-statements.do"
    if (doof::string_startsWith(statement->kind, std::string("array-destructuring"))) {
#line 818 "/src/checker-statements.do"
        {
            auto _case_subject = valueType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 819 "/src/checker-statements.do"
                const auto& _iterable_64 = statement->bindings;
                for (const auto& ignored : *_iterable_64) {
#line 819 "/src/checker-statements.do"
                    bindingTypes->push_back(array->elementType);
                }
        }
        else {
#line 820 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Array destructuring requires a T[] value, but got \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\"")), std::visit([](auto&& _obj) { return _obj->span; }, statement->value));
        }
        }
    } else if (doof::string_startsWith(statement->kind, std::string("positional-destructuring"))) {
#line 823 "/src/checker-statements.do"
        (bindingTypes = positionalDestructuringTypes(state, valueType, std::visit([](auto&& _obj) { return _obj->span; }, statement->value)));
#line 824 "/src/checker-statements.do"
        if (static_cast<int32_t>((bindingTypes)->size()) < static_cast<int32_t>((statement->bindings)->size())) {
#line 825 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, (((std::string("Positional destructuring expected at least ") + doof::to_string(static_cast<int32_t>((statement->bindings)->size()))) + std::string(" values, but got ")) + doof::to_string(static_cast<int32_t>((bindingTypes)->size()))), statement->span);
        }
    }
#line 829 "/src/checker-statements.do"
    if (doof::string_startsWith(statement->kind, std::string("named-destructuring"))) {
#line 830 "/src/checker-statements.do"
        const auto& _iterable_66 = statement->namedBindings;
        for (const auto& named : *_iterable_66) {
#line 831 "/src/checker-statements.do"
            const auto localName = [&]() -> std::string { auto _coalesce_67 = named->alias; if (doof::is_null(_coalesce_67)) return named->name; return doof::unwrap_optional(_coalesce_67); }();
#line 832 "/src/checker-statements.do"
            const auto fieldType = ::app_src_checker_resolution_::memberType(state, valueType, named->name, named->span, true);
#line 833 "/src/checker-statements.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, fieldType) == std::string("unknown")) {
#line 833 "/src/checker-statements.do"
                ::app_src_checker_common_::typeError(state, ((((std::string("Type \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\" has no field \"")) + named->name) + std::string("\"")), named->span);
            }
#line 834 "/src/checker-statements.do"
            if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
#line 834 "/src/checker-statements.do"
                validateDestructuringTarget(state, scope, localName, fieldType, named->span);
            } else {
#line 835 "/src/checker-statements.do"
                declareDestructuredBinding(state, scope, localName, fieldType, statement->bindingKind, named->span);
            }
        }
#line 837 "/src/checker-statements.do"
        return;
    }
#line 840 "/src/checker-statements.do"
    for (int32_t i = 0; i < static_cast<int32_t>((statement->bindings)->size()); ++i) {
#line 841 "/src/checker-statements.do"
        const auto name = doof::array_at(statement->bindings, i, "src/checker-statements", 841);
#line 842 "/src/checker-statements.do"
        if (name == std::string("_")) {
#line 842 "/src/checker-statements.do"
            continue;
        }
#line 843 "/src/checker-statements.do"
        const auto bindingType = ((i < static_cast<int32_t>((bindingTypes)->size())) ? doof::array_at(bindingTypes, i, "src/checker-statements", 843) : ::app_src_checker_types_::unknownType());
#line 844 "/src/checker-statements.do"
        if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
#line 844 "/src/checker-statements.do"
            validateDestructuringTarget(state, scope, name, bindingType, statement->span);
        } else {
#line 845 "/src/checker-statements.do"
            declareDestructuredBinding(state, scope, name, bindingType, statement->bindingKind, statement->span);
        }
    }
}
#line 849 "/src/checker-statements.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> positionalDestructuringTypes(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& valueType, ::app_src_ast_::SourceSpan span) {
#line 850 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> result = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 851 "/src/checker-statements.do"
    {
        auto _case_subject = valueType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 852 "/src/checker-statements.do"
            const auto& _iterable_70 = tuple->elements;
            for (const auto& element : *_iterable_70) {
#line 852 "/src/checker-statements.do"
                result->push_back(element);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 854 "/src/checker-statements.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
#line 855 "/src/checker-statements.do"
            if (!doof::is_null(declaration)) {
#line 855 "/src/checker-statements.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& owner = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 857 "/src/checker-statements.do"
                        const auto& _iterable_72 = owner->fields;
                        for (const auto& field : *_iterable_72) {
#line 858 "/src/checker-statements.do"
                            if (field->static_) {
#line 858 "/src/checker-statements.do"
                                continue;
                            }
#line 859 "/src/checker-statements.do"
                            const auto& _iterable_74 = field->names;
                            for (const auto& name : *_iterable_74) {
#line 859 "/src/checker-statements.do"
                                result->push_back(::app_src_checker_resolution_::memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), name, span, true));
                            }
                        }
                }
                else {
                }
                }
            }
    }
    else {
#line 865 "/src/checker-statements.do"
            ::app_src_checker_common_::typeError(state, ((std::string("Positional destructuring requires a tuple or nominal object value, but got \"") + ::app_src_checker_types_::typeName(valueType)) + std::string("\"")), span);
    }
    }
#line 867 "/src/checker-statements.do"
    return result;
}
#line 870 "/src/checker-statements.do"
void declareDestructuredBinding(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& bindingKind, ::app_src_ast_::SourceSpan span) {
#line 871 "/src/checker-statements.do"
    declareUserBinding(state, scope, std::make_shared<::app_src_semantic_::Binding>(name, ((bindingKind == std::string("let")) ? std::string("let") : std::string("immutable-binding")), type_, (bindingKind == std::string("let")), ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")), span);
}
#line 878 "/src/checker-statements.do"
void declareUserBinding(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::Binding>& binding, ::app_src_ast_::SourceSpan span) {
#line 879 "/src/checker-statements.do"
    if (!::app_src_checker_symbols_::declare(scope, binding)) {
#line 879 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, ((std::string("Binding '") + binding->name) + std::string("' is already declared in this scope")), span);
    }
}
#line 882 "/src/checker-statements.do"
void validateDestructuringTarget(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& valueType, ::app_src_ast_::SourceSpan span) {
#line 883 "/src/checker-statements.do"
    const auto target = ::app_src_checker_symbols_::lookup(scope, name);
#line 884 "/src/checker-statements.do"
    if (doof::is_null(target)) {
#line 884 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, ((std::string("Destructuring assignment target \"") + name) + std::string("\" is not defined")), span);
#line 884 "/src/checker-statements.do"
        return;
    }
#line 885 "/src/checker-statements.do"
    ::app_src_checker_common_::validateAssignmentBinding(state, doof::unwrap_optional(target), span);
#line 886 "/src/checker-statements.do"
    if (!::app_src_checker_types_::isAssignable(valueType, target->type_)) {
#line 886 "/src/checker-statements.do"
        ::app_src_checker_common_::typeError(state, (((std::string("Cannot assign ") + ::app_src_checker_types_::typeName(valueType)) + std::string(" to ")) + ::app_src_checker_types_::typeName(target->type_)), span);
    }
}
#line 889 "/src/checker-statements.do"
std::shared_ptr<::app_src_semantic_::Scope> catchErrorScope(const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 890 "/src/checker-statements.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 891 "/src/checker-statements.do"
    while (!doof::is_null(current)) {
#line 892 "/src/checker-statements.do"
        if (current->capturesTryErrors) {
#line 892 "/src/checker-statements.do"
            return current;
        }
#line 893 "/src/checker-statements.do"
        (current = current->parent);
    }
#line 895 "/src/checker-statements.do"
    return nullptr;
}
#line 898 "/src/checker-statements.do"
std::shared_ptr<::app_src_semantic_::Binding> lookupYieldBinding(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
#line 899 "/src/checker-statements.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 900 "/src/checker-statements.do"
    while (!doof::is_null(current)) {
#line 901 "/src/checker-statements.do"
        const auto& _iterable_76 = current->bindings;
        for (const auto& binding : *_iterable_76) {
#line 901 "/src/checker-statements.do"
            if (binding->name == name) {
#line 901 "/src/checker-statements.do"
                return binding;
            }
        }
#line 902 "/src/checker-statements.do"
        (current = current->parent);
    }
#line 904 "/src/checker-statements.do"
    return nullptr;
}
#line 907 "/src/checker-statements.do"
bool checkCase(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::CaseStatement>& statement, const std::shared_ptr<::app_src_semantic_::Scope>& scope, bool inLoop) {
#line 908 "/src/checker-statements.do"
    const auto subjectType = ::app_src_checker_expressions_::checkExpression(state, statement->subject, scope, std::monostate{});
#line 909 "/src/checker-statements.do"
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>> armPatterns = std::make_shared<std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>>(std::vector<std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>>>>>{});
#line 910 "/src/checker-statements.do"
    auto allArmsReturn = (static_cast<int32_t>((statement->arms)->size()) > 0);
#line 911 "/src/checker-statements.do"
    const auto& _iterable_78 = statement->arms;
    for (const auto& arm : *_iterable_78) {
#line 912 "/src/checker-statements.do"
        armPatterns->push_back(arm->patterns);
#line 913 "/src/checker-statements.do"
        const auto armScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 914 "/src/checker-statements.do"
        ::app_src_checker_expressions_::checkCasePatterns(state, arm->patterns, subjectType, armScope);
#line 915 "/src/checker-statements.do"
        auto armCompletes = true;
#line 916 "/src/checker-statements.do"
        {
            auto _case_subject = arm->body;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 917 "/src/checker-statements.do"
                (armCompletes = checkBlock(state, block, armScope, inLoop));
        }
        else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 918 "/src/checker-statements.do"
                (armCompletes = (std::visit([](auto&& _obj) { return _obj->kind; }, ::app_src_checker_expressions_::checkExpression(state, expression, armScope, std::monostate{})) != std::string("never")));
        }
        }
#line 920 "/src/checker-statements.do"
        if (armCompletes) {
#line 920 "/src/checker-statements.do"
            (allArmsReturn = false);
        }
    }
#line 922 "/src/checker-statements.do"
    const auto exhaustive = ::app_src_checker_expressions_::casePatternsExhaustive(state, subjectType, armPatterns);
#line 923 "/src/checker-statements.do"
    (statement->resolvedCompletes = ((std::visit([](auto&& _obj) { return _obj->kind; }, subjectType) == std::string("never")) ? false : !(exhaustive && allArmsReturn)));
#line 924 "/src/checker-statements.do"
    return doof::unwrap_optional(statement->resolvedCompletes);
}
#line 927 "/src/checker-statements.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferredReturn(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::Block>& block) {
#line 928 "/src/checker-statements.do"
    const auto& _iterable_80 = block->statements;
    for (const auto& statement : *_iterable_80) {
#line 929 "/src/checker-statements.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
                const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
#line 931 "/src/checker-statements.do"
                if (doof::is_null(return_->value)) {
#line 931 "/src/checker-statements.do"
                    return ::app_src_checker_types_::noneType();
                }
#line 932 "/src/checker-statements.do"
                const auto value = doof::unwrap_optional(return_->value);
#line 933 "/src/checker-statements.do"
                return [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_81 = std::visit([](auto&& _obj) { return _obj->resolvedType; }, value); if (doof::is_null(_coalesce_81)) return ::app_src_checker_types_::unknownType(); return doof::unwrap_optional(_coalesce_81); }();
        }
        else {
        }
        }
    }
#line 938 "/src/checker-statements.do"
    return ::app_src_checker_types_::noneType();
}
#line 941 "/src/checker-statements.do"
void addClassFields(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& owner) {
#line 942 "/src/checker-statements.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, owner->symbol);
#line 943 "/src/checker-statements.do"
    if (doof::is_null(declaration)) {
#line 943 "/src/checker-statements.do"
        return;
    }
#line 944 "/src/checker-statements.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 946 "/src/checker-statements.do"
            const auto& _iterable_83 = class_->fields;
            for (const auto& field : *_iterable_83) {
#line 947 "/src/checker-statements.do"
                const auto& _iterable_85 = field->names;
                for (const auto& name : *_iterable_85) {
#line 948 "/src/checker-statements.do"
                    ::app_src_checker_symbols_::declare(scope, std::make_shared<::app_src_semantic_::Binding>(name, std::string("field"), [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_86 = field->resolvedType; if (doof::is_null(_coalesce_86)) return ::app_src_checker_types_::unknownType(); return doof::unwrap_optional(_coalesce_86); }(), field->let_, ::app_src_checker_validation_::checkerSemanticSpan(field->span), state->info->path, nullptr, std::string(""), (field->readonly_ ? std::string("readonly") : (field->const_ ? std::string("const") : (field->let_ ? std::string("let") : std::string("implicit")))), class_->name));
                }
            }
    }
    else {
    }
    }
}
#line 1 "<doof-generated>"
}
