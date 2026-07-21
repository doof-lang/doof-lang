#include "src_checker.hpp"
#include <cmath>
#include "src_analyzer.hpp"
#include "src_semantic.hpp"
#include "src_checker_state.hpp"
#include "src_checker_statements.hpp"
#include "src_checker_actor_lifecycle.hpp"
#include "src_checker_interfaces.hpp"
#include "src_checker_symbols.hpp"
#include "src_checker_validation.hpp"
#include "src_checker_isolation.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_checker_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_semantic_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_statements_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_validation_;
using namespace ::app_src_checker_isolation_;

std::shared_ptr<::app_src_semantic_::CheckResult> ModuleChecker::check(std::string entry) {
    return checkModule(this->state, entry);
}
std::shared_ptr<::app_src_semantic_::CheckResult> checkModule(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::string entry) {
    (state->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    (state->info = ::app_src_checker_interfaces_::findModule(state->result, (doof::string_endsWith(entry, std::string(".do")) ? entry : (entry + std::string(".do")))));
    if (doof::is_null(state->info)) {
        return std::make_shared<::app_src_semantic_::CheckResult>(state->diagnostics);
    }
    ::app_src_checker_interfaces_::discoverInterfaceImplementations(state->result);
    (state->moduleScope = std::make_shared<::app_src_semantic_::Scope>(nullptr, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})));
    ::app_src_checker_symbols_::predeclareModuleBindings(doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope), state->result);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>> retiredActors = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{});
    const auto& _iterable_1 = state->info->program->statements;
    for (const auto& statement : *_iterable_1) {
        ::app_src_checker_statements_::checkStatement(state, statement, doof::unwrap_optional(state->moduleScope));
        ::app_src_checker_actor_lifecycle_::reportRetiredActorUses(statement, retiredActors, state->info->path, state->diagnostics);
        ::app_src_checker_actor_lifecycle_::collectRetiredActorBindings(statement, retiredActors);
    }
    ::app_src_checker_statements_::validateInterfaces(state, doof::unwrap_optional(state->info));
    ::app_src_checker_isolation_::validateIsolationEffects(state->result, doof::unwrap_optional(state->info), state->diagnostics);
    return std::make_shared<::app_src_semantic_::CheckResult>(state->diagnostics);
}
std::shared_ptr<ModuleChecker> createChecker(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    return std::make_shared<ModuleChecker>(std::make_shared<::app_src_checker_state_::CheckerState>(result, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), nullptr, nullptr));
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateCheckedTypes(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    return ::app_src_checker_validation_::validateCheckedTypes(result);
}
}
