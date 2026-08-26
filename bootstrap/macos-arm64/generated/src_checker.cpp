#include "src_checker.hpp"

namespace app_src_checker_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_semantic_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_statements_;
using namespace ::app_src_checker_expressions_;
using namespace ::app_src_checker_resolution_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_validation_;
using namespace ::app_src_checker_isolation_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_module_initialization_;

std::shared_ptr<::app_src_semantic_::CheckResult> ModuleChecker::check(const std::string& entry) {
    return checkModule(this->state, entry);
}
std::shared_ptr<::app_src_semantic_::CheckResult> checkModule(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& entry) {
    (state->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    (state->info = ::app_src_checker_interfaces_::findModule(state->result, (doof::string_endsWith(entry, std::string(".do")) ? entry : (entry + std::string(".do")))));
    if (doof::is_null(state->info)) {
        return std::make_shared<::app_src_semantic_::CheckResult>(state->diagnostics);
    }
    ::app_src_checker_interfaces_::discoverInterfaceImplementations(state->result);
    (state->moduleScope = std::make_shared<::app_src_semantic_::Scope>(nullptr, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false));
    ::app_src_checker_symbols_::predeclareModuleBindings(doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope), state->result);
    auto scriptEntry = false;
    auto rejectedWasmScript = false;
    if (state->info->path == state->entry) {
        const auto& _iterable_2 = state->info->program->statements;
        for (const auto& statement : *_iterable_2) {
            if (!isModuleDeclaration(statement)) {
                (scriptEntry = true);
            }
        }
    }
    if (scriptEntry && (state->entryMode == std::string("wasm"))) {
        const auto& _iterable_4 = state->info->program->statements;
        for (const auto& statement : *_iterable_4) {
            if (!isModuleDeclaration(statement)) {
                ::app_src_checker_common_::typeError(state, std::string("WebAssembly entry modules do not support top-level executable statements"), std::visit([](auto&& _obj) { return _obj->span; }, statement));
            }
        }
        (rejectedWasmScript = true);
        (scriptEntry = false);
    }
    if (scriptEntry) {
        const auto& _iterable_6 = state->info->program->statements;
        for (const auto& statement : *_iterable_6) {
            if (isExport(statement)) {
                ::app_src_checker_common_::typeError(state, std::string("Native script entry modules cannot export declarations"), std::visit([](auto&& _obj) { return _obj->span; }, statement));
            }
            if (scriptGlobalName(statement) == std::string("arguments")) {
                ::app_src_checker_common_::typeError(state, std::string("'arguments' is reserved by native script entry modules"), std::visit([](auto&& _obj) { return _obj->span; }, statement));
            }
        }
    }
    const auto scriptScope = std::make_shared<::app_src_semantic_::Scope>(state->moduleScope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), scriptEntry);
    if (scriptEntry) {
        ::app_src_checker_symbols_::declare(scriptScope, std::make_shared<::app_src_semantic_::Binding>(std::string("arguments"), std::string("script-arguments"), ::app_src_checker_types_::arrayType(::app_src_checker_types_::primitive(std::string("string")), false), false, ::app_src_checker_validation_::checkerSemanticSpan(state->info->program->span), state->info->path, nullptr, std::string(""), std::string(""), std::string("")));
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>> retiredActors = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{});
    const auto& _iterable_8 = state->info->program->statements;
    for (const auto& statement : *_iterable_8) {
        if (scriptEntry && isScriptGlobalDeclaration(statement)) {
            ::app_src_checker_statements_::checkStatement(state, statement, scriptScope, false);
            promoteScriptBinding(statement, scriptScope, doof::unwrap_optional(state->moduleScope));
        } else if (scriptEntry && !isModuleDeclaration(statement)) {
            ::app_src_checker_statements_::checkStatement(state, statement, scriptScope, false);
        } else {
            if ((!scriptEntry && !rejectedWasmScript) && !isModuleDeclaration(statement)) {
                ::app_src_checker_common_::typeError(state, std::string("Top-level executable statements are only allowed in a native entry module"), std::visit([](auto&& _obj) { return _obj->span; }, statement));
            }
            ::app_src_checker_statements_::checkStatement(state, statement, doof::unwrap_optional(state->moduleScope), false);
            if (!scriptEntry) {
                ::app_src_checker_module_initialization_::validateModuleInitializerStatement(state, statement);
            }
        }
        ::app_src_checker_actor_lifecycle_::reportRetiredActorUses(statement, retiredActors, state->info->path, state->diagnostics);
        ::app_src_checker_actor_lifecycle_::collectRetiredActorBindings(statement, retiredActors);
    }
    ::app_src_checker_statements_::validateInterfaces(state, doof::unwrap_optional(state->info));
    return std::make_shared<::app_src_semantic_::CheckResult>(state->diagnostics);
}
std::string scriptGlobalName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    auto declaration = statement;
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            (declaration = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(try_->binding));
    }
    else {
    }
    }
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return value->name;
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
bool isScriptValueDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool isScriptGlobalDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    if (isScriptValueDeclaration(statement)) {
        return true;
    }
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            return isScriptValueDeclaration(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(try_->binding));
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool isModuleDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    if (isScriptValueDeclaration(statement)) {
        return true;
    }
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool isExport(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return const_->exported;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return readonly_->exported;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            return fn->exported;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_->exported;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return interface_->exported;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            return enum_->exported;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            return alias->exported;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
void promoteScriptBinding(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_semantic_::Scope>& scriptScope, const std::shared_ptr<::app_src_semantic_::Scope>& moduleScope) {
    auto name = std::string("");
    auto declaration = statement;
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            (declaration = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(try_->binding));
    }
    else {
    }
    }
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            (name = value->name);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            (name = value->name);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            (name = value->name);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            (name = value->name);
    }
    else {
            return;
    }
    }
    if ((name == std::string("")) || (name == std::string("_"))) {
        return;
    }
    const auto& _iterable_10 = scriptScope->bindings;
    for (const auto& binding : *_iterable_10) {
        if ((binding->name == name) && (binding->kind != std::string("script-arguments"))) {
            (binding->kind = std::string("script-global"));
            moduleScope->bindings->push_back(binding);
            return;
        }
    }
}
std::shared_ptr<ModuleChecker> createChecker(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::string& entryMode) {
    const auto state = std::make_shared<::app_src_checker_state_::CheckerState>(result, (doof::string_endsWith(entry, std::string(".do")) ? entry : (entry + std::string(".do"))), entryMode, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), nullptr, nullptr, false);
    prepareClassFieldTypes(state);
    return std::make_shared<ModuleChecker>(state);
}
void prepareClassFieldTypes(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state) {
    auto changed = true;
    while (changed) {
        (changed = false);
        const auto& _iterable_12 = state->result->modules;
        for (const auto& module : *_iterable_12) {
            (state->info = module);
            (state->moduleScope = std::make_shared<::app_src_semantic_::Scope>(nullptr, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false));
            ::app_src_checker_symbols_::predeclareModuleBindings(module, doof::unwrap_optional(state->moduleScope), state->result);
            const auto& _iterable_14 = module->program->statements;
            for (const auto& statement : *_iterable_14) {
                {
                    auto _case_subject = statement;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                        const auto classScope = std::make_shared<::app_src_semantic_::Scope>(state->moduleScope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), class_->typeParams, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
                        const auto& _iterable_16 = class_->fields;
                        for (const auto& field : *_iterable_16) {
                            if (!doof::is_null(field->resolvedType)) {
                                continue;
                            }
                            const auto diagnosticCount = static_cast<int32_t>((state->diagnostics)->size());
                            auto fieldType = ::app_src_checker_types_::unknownType();
                            if (!doof::is_null(field->type_)) {
                                (fieldType = ::app_src_checker_resolution_::resolveType(state, doof::unwrap_optional(field->type_), module, classScope));
                            } else if (!doof::is_null(field->defaultValue)) {
                                const auto previousAllowsCaller = state->allowsCaller;
                                (state->allowsCaller = true);
                                (fieldType = ::app_src_checker_expressions_::checkExpression(state, doof::unwrap_optional(field->defaultValue), classScope, std::monostate{}));
                                (state->allowsCaller = previousAllowsCaller);
                            }
                            while (static_cast<int32_t>((state->diagnostics)->size()) > diagnosticCount) {
                                const auto ignored = [&]() -> std::shared_ptr<::app_src_semantic_::Diagnostic> { auto _try_value = doof::array_pop(state->diagnostics); if (doof::is_failure(_try_value)) doof::panic_at("src/checker", 229, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
                            }
                            if (std::visit([](auto&& _obj) { return _obj->kind; }, fieldType) == std::string("unknown")) {
                                continue;
                            }
                            if (field->readonly_ || field->const_) {
                                (fieldType = ::app_src_checker_types_::applyDeepReadonly(fieldType));
                            }
                            (field->resolvedType = ::app_src_checker_symbols_::optionalResolvedType((field->weak_ ? ::app_src_checker_types_::weakType(fieldType) : fieldType)));
                            (changed = true);
                        }
                }
                else {
                }
                }
            }
        }
    }
    (state->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    (state->info = nullptr);
    (state->moduleScope = nullptr);
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateCheckedTypes(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    return ::app_src_checker_validation_::validateCheckedTypes(result);
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateIsolationEffects(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
    ::app_src_checker_isolation_::validateIsolationEffects(result, diagnostics);
    return diagnostics;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateDeepReadonlyFields(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    return ::app_src_checker_actor_boundary_::validateDeepReadonlyFields(result);
}
}
