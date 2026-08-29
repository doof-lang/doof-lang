#include "src_emitter_module.hpp"

namespace app_src_emitter_module_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_decl_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_metadata_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_header_;
using namespace ::app_src_emitter_worldview_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_names_;
using namespace ::std_::crypto::index;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_string_builder_;
using namespace ::app_src_semantic_;


std::shared_ptr<ModuleGraphPlan> planModuleGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    const auto plan = std::make_shared<ModuleGraphPlan>(std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{}));
    const auto& _iterable_2 = result->modules;
    for (const auto& info : *_iterable_2) {
        const auto module = std::make_shared<ModulePlan>(info->path, ::app_src_emitter_names_::moduleNamespace(info->path), ::app_src_emitter_names_::moduleHeaderName(info->path), ::app_src_emitter_names_::moduleSourceName(info->path));
        plan->modules->push_back(module);
    }
    return plan;
}





std::shared_ptr<ModuleEmission> CxxModuleEmitter::emit(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& entryMode) {
    const auto context = ::app_src_emitter_context_::createEmitContextForModule(program, this->modulePath, this->allPrograms);
    (context->namespaceImports = this->namespaceImports);
    (context->sourcePath = sourcePathFor(this->sourcePaths, context->modulePath));
    (context->imports = this->imports);
    (context->moduleSurfaces = this->moduleSurfaces);
    (context->jsonEligibility = this->jsonEligibility);
    if (this->coverageModuleId >= 0) {
        (context->coverageEnabled = true);
        (context->coverageModuleId = this->coverageModuleId);
    }
    if (!doof::is_null(this->instantiations)) {
        configureInstantiationRegistry(context, doof::unwrap_optional(this->instantiations));
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>> sections = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>>(std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>{});
    std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan = nullptr;
    auto views = this->worldviewModules;
    if (static_cast<int32_t>((views)->size()) == 0) {
        (views = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{std::make_shared<::app_src_emitter_worldview_::WorldviewModule>(this->modulePath, program)}));
    }
    const auto& _iterable_4 = views;
    for (const auto& view : *_iterable_4) {
        const auto sectionContext = ::app_src_emitter_context_::createEmitContextForModule(view->program, view->path, this->allPrograms);
        (sectionContext->imports = surfaceImports(this->moduleSurfaces, view->path));
        (sectionContext->sourcePath = sourcePathFor(this->sourcePaths, view->path));
        (sectionContext->moduleSurfaces = this->moduleSurfaces);
        (sectionContext->jsonEligibility = this->jsonEligibility);
        if (!doof::is_null(this->instantiations)) {
            configureInstantiationRegistry(sectionContext, doof::unwrap_optional(this->instantiations));
        }
        const auto sectionPlan = ::app_src_emitter_header_::planHeader(view->program, sectionContext, (doof::is_null(this->instantiations) ? std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{}) : this->instantiations->methods));
        if (!doof::is_null(this->instantiations)) {
            addConcreteHeaderDeclarations(sectionPlan, sectionContext, doof::unwrap_optional(this->instantiations), view->program, this->worldviewInterfaceKeys);
        }
        const auto sectionNamespace = ((view->path == this->modulePath) ? this->namespaceNameOverride : ::app_src_emitter_names_::moduleNamespace(view->path));
        sections->push_back(std::make_shared<::app_src_emitter_header_::HeaderSection>(sectionNamespace, sectionPlan));
        if (view->path == this->modulePath) {
            (plan = sectionPlan);
        }
    }
    if (doof::is_null(plan)) {
        doof::panic((std::string("worldview omitted root module ") + this->modulePath));
    }
    (context->scriptEntry = (((entryMode == std::string("executable")) || (entryMode == std::string("ios-app"))) && hasScriptStatements(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}))));
    return emitPlanned(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}), context, doof::unwrap_optional(plan), sections, entryMode);
}
std::shared_ptr<ModuleEmission> CxxModuleEmitter::emitPlanned(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>>& sections, const std::string& entryMode) {
    const auto headerName = this->headerNameOverride;
    const auto sourceName = this->sourceNameOverride;
    const auto namespaceName = this->namespaceNameOverride;
    const auto header = ::app_src_emitter_header_::renderProjectedHeader(sections);
    const auto sourceBuilder = ::doof::StringBuilder::constructor();
    sourceBuilder->append(((std::string("#include \"") + headerName) + std::string("\"\n\n")));
    const auto& _iterable_6 = this->initializationModuleNamespaces;
    for (const auto& namespace_ : *_iterable_6) {
        sourceBuilder->append(((std::string("namespace ") + namespace_) + std::string(" { void __doof_initialize_module(); }\n")));
    }
    if (static_cast<int32_t>((this->initializationModuleNamespaces)->size()) > 0) {
        sourceBuilder->append(std::string("\n"));
    }
    sourceBuilder->append(((std::string("namespace ") + namespaceName) + std::string(" {\n")));
    sourceBuilder->append(emitImportedNamespaces(context, this->worldviewModules));
    if (context->scriptEntry) {
        sourceBuilder->append(emitScriptStorage(programs, context));
    }
    const auto& _iterable_8 = programs;
    for (const auto& program : *_iterable_8) {
        const auto& _iterable_10 = program->statements;
        for (const auto& statement : *_iterable_10) {
            if (!(context->scriptEntry && (!doof::is_null(scriptGlobalDeclaration(statement))))) {
                sourceBuilder->append(emitSourceStatement(statement, context));
            }
        }
    }
    sourceBuilder->append(::app_src_emitter_context_::generatedLineDirective());
    sourceBuilder->append(emitModuleInitializer(programs, context, !context->scriptEntry));
    if (context->scriptEntry) {
        sourceBuilder->append(emitScriptRunner(programs, context));
    }
    if (!doof::is_null(this->instantiations)) {
        sourceBuilder->append(emitConcreteClassDefinitions(context, doof::unwrap_optional(this->instantiations)));
        sourceBuilder->append(emitConcreteMethodDefinitions(context, doof::unwrap_optional(this->instantiations)));
        sourceBuilder->append(emitConcreteFunctions(context, doof::unwrap_optional(this->instantiations)));
    }
    sourceBuilder->append(std::string("}\n"));
    const auto nativeMethods = emitNativeClassMethods(programs, context);
    if (nativeMethods != std::string("")) {
        sourceBuilder->append((((std::string("\nusing namespace ::") + namespaceName) + std::string(";\n\n")) + nativeMethods));
    }
    const auto initializationCall = emitGraphInitializationCall(this->initializationModuleNamespaces);
    if ((entryMode == std::string("executable")) && (plan->hasMain || context->scriptEntry)) {
        sourceBuilder->append((::app_src_emitter_context_::generatedLineDirective() + emitMainWrapper(namespaceName, plan, context->scriptEntry, initializationCall)));
    }
    if ((entryMode == std::string("ios-app")) && (plan->hasMain || context->scriptEntry)) {
        sourceBuilder->append((::app_src_emitter_context_::generatedLineDirective() + emitAppEntryWrapper(namespaceName, plan, context->scriptEntry, initializationCall)));
    }
    const auto source = sourceBuilder->drainToString();
    return std::make_shared<ModuleEmission>(context->modulePath, header, source, headerName, sourceName, context->coverageModuleId, sortedCoverageLines(context->coverageInstrumentedLines), false, std::string(""));
}
std::string sourcePathFor(const std::shared_ptr<doof::ordered_map<std::string, std::string>>& paths, const std::string& modulePath) {
    auto _binding_value_11 = doof::map_get(paths, modulePath, "", 0);
    if (doof::is_failure(_binding_value_11)) {
        const auto& path = _binding_value_11;
        return modulePath;
    }
    const auto path = doof::success_value(_binding_value_11);
    return path;
}
bool hasScriptStatements(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs) {
    const auto& _iterable_13 = programs;
    for (const auto& program : *_iterable_13) {
        const auto& _iterable_15 = program->statements;
        for (const auto& statement : *_iterable_15) {
            if (!isModuleDeclaration(statement)) {
                return true;
            }
        }
    }
    return false;
}
bool isValueDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
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
bool isModuleDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    if (isValueDeclaration(statement)) {
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
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> scriptGlobalDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    if (isValueDeclaration(statement)) {
        return doof::optional_value(statement);
    }
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else {
            }
            }
    }
    else {
    }
    }
    return std::monostate{};
}
std::string scriptDeclarationName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
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
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> scriptDeclarationType(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else {
            return std::monostate{};
    }
    }
    doof::unreachable();
    return std::monostate{};
}
bool scriptDeclarationMutable(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
std::string emitScriptStorage(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto source = std::string("\n");
    const auto& _iterable_17 = programs;
    for (const auto& program : *_iterable_17) {
        const auto& _iterable_19 = program->statements;
        for (const auto& statement : *_iterable_19) {
            const auto declaration = scriptGlobalDeclaration(statement);
            if (doof::is_null(declaration)) {
                continue;
            }
            const auto name = scriptDeclarationName(doof::unwrap_optional(declaration));
            const auto type_ = scriptDeclarationType(doof::unwrap_optional(declaration));
            if (((name == std::string("")) || (name == std::string("_"))) || doof::is_null(type_)) {
                continue;
            }
            const auto cppName = ::app_src_emitter_expr_::cppIdentifier(name);
            const auto typeText = ::app_src_emitter_types_::emitContextType(doof::unwrap_optional(type_), context);
            (source = (((((source + std::string("std::optional<")) + typeText) + std::string("> __doof_script_storage_")) + cppName) + std::string(";\n")));
            const auto returnType = (scriptDeclarationMutable(doof::unwrap_optional(declaration)) ? (typeText + std::string("&")) : ((std::string("const ") + typeText) + std::string("&")));
            (source = ((((((((((source + returnType) + std::string(" __doof_script_get_")) + cppName) + std::string("() { if (!__doof_script_storage_")) + cppName) + std::string(".has_value()) doof::panic(\"Entry binding '")) + name) + std::string("' was accessed before initialization\"); return *__doof_script_storage_")) + cppName) + std::string("; }\n")));
        }
    }
    return (source + std::string("\n"));
}
std::string emitScriptRunner(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto previousTryPanics = context->tryPanics;
    (context->tryPanics = true);
    auto source = std::string("\nvoid __doof_run_script(std::shared_ptr<std::vector<std::string>> arguments) {\n");
    const auto& _iterable_21 = programs;
    for (const auto& program : *_iterable_21) {
        const auto& _iterable_23 = program->statements;
        for (const auto& statement : *_iterable_23) {
            const auto declaration = scriptGlobalDeclaration(statement);
            if (!doof::is_null(declaration)) {
                (source = (source + ::app_src_emitter_stmt_::emitStatement(statement, 1, context)));
                const auto name = scriptDeclarationName(doof::unwrap_optional(declaration));
                if ((name != std::string("")) && (name != std::string("_"))) {
                    (source = (((((source + std::string("    __doof_script_storage_")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(".emplace(")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(");\n")));
                }
            } else if (!isModuleDeclaration(statement)) {
                (source = (source + ::app_src_emitter_stmt_::emitStatement(statement, 1, context)));
            }
        }
    }
    (context->tryPanics = previousTryPanics);
    return (source + std::string("}\n"));
}
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto& _iterable_25 = values;
    for (const auto& existing : *_iterable_25) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
std::string emitImportedNamespaces(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>& worldviewModules) {
    std::shared_ptr<std::vector<std::string>> namespaces = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_27 = context->imports;
    for (const auto& imported : *_iterable_27) {
        if (!worldviewContainsModule(worldviewModules, imported->sourceModule)) {
            continue;
        }
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(imported->sourceModule);
        addNamespace(namespaces, namespace_);
    }
    const auto& _iterable_29 = context->namespaceImports;
    for (const auto& imported : *_iterable_29) {
        if (!worldviewContainsModule(worldviewModules, imported->sourceModule)) {
            continue;
        }
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(imported->sourceModule);
        addNamespace(namespaces, namespace_);
    }
    auto result = std::string("");
    const auto& _iterable_31 = namespaces;
    for (const auto& namespace_ : *_iterable_31) {
        (result = (((result + std::string("using namespace ::")) + namespace_) + std::string(";\n")));
    }
    return result;
}
bool worldviewContainsModule(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>& modules, const std::string& path) {
    const auto& _iterable_33 = modules;
    for (const auto& module : *_iterable_33) {
        if (module->path == path) {
            return true;
        }
    }
    return false;
}
void addNamespace(const std::shared_ptr<std::vector<std::string>>& namespaces, const std::string& namespace_) {
    const auto& _iterable_35 = namespaces;
    for (const auto& existing : *_iterable_35) {
        if (existing == namespace_) {
            return;
        }
    }
    namespaces->push_back(namespace_);
}
std::shared_ptr<ModuleGraphEmission> emitModuleGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<ModuleEmissionCacheKey>>>& reusableModules, const std::string& configurationFingerprint, bool physicalSourcePaths) {
    const auto graph = std::make_shared<ModuleGraphEmission>(std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{}), std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(std::vector<std::shared_ptr<CoverageModuleMetadata>>{}), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto concretePlan = [&]() -> std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> { auto _coalesce_36 = instantiations; if (doof::is_null(_coalesce_36)) return ::app_src_emitter_monomorphize_::buildInstantiationPlan(result); return doof::unwrap_optional(_coalesce_36); }();
    const auto plan = planModuleGraph(result);
    const auto initializationOrder = planModuleInitializationOrder(result, entry, entryMode);
    const auto graphPrograms = allPrograms(result);
    const auto graphSurfaces = emitModuleSurfaces(result);
    const auto moduleIndex = indexGraphModules(result);
    const auto reusableFingerprints = indexReusableModuleFingerprints(reusableModules);
    const auto instantiationFingerprintInput = moduleInstantiationFingerprintInput(concretePlan);
    const auto jsonEligibility = std::make_shared<::app_src_json_semantics_::JsonEligibilityCache>(std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}), std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}));
    const auto worldviewGraphIndex = ::app_src_emitter_worldview_::indexWorldviewGraph(result);
    std::shared_ptr<doof::ordered_map<std::string, std::string>> sourcePaths = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    const auto& _iterable_38 = result->modules;
    for (const auto& info : *_iterable_38) {
        doof::map_set(sourcePaths, info->path, ((physicalSourcePaths && (info->physicalPath != std::string(""))) ? info->physicalPath : info->path), "", 0);
    }
    auto nextCoverageModuleId = 0;
    const auto& _iterable_40 = plan->modules;
    for (const auto& module : *_iterable_40) {
        const auto info = indexedGraphModule(moduleIndex, module->path);
        if (doof::is_null(info)) {
            continue;
        }
        auto coverageModuleId = -1;
        if (coverage && isCoverageEligible(module->path)) {
            (coverageModuleId = nextCoverageModuleId);
            (nextCoverageModuleId += 1);
        }
        const auto fingerprint = moduleEmissionFingerprint(result, moduleIndex, module->path, entry, entryMode, coverage, initializationOrder, ((configurationFingerprint + std::string("\nphysical-source-paths:")) + doof::to_string(physicalSourcePaths)), instantiationFingerprintInput);
        if (!coverage && reusableModuleMatches(reusableFingerprints, module->path, fingerprint)) {
            graph->modules->push_back(std::make_shared<ModuleEmission>(module->path, std::string(""), std::string(""), module->headerName, module->sourceName, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), true, fingerprint));
            continue;
        }
        const auto emitter = std::make_shared<CxxModuleEmitter>(module->headerName, module->sourceName, module->namespaceName, module->path, graphPrograms, infoNamespaceImports(result, module->path), infoImports(result, module->path), graphSurfaces, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), concretePlan, coverageModuleId, ((module->path == entry) ? moduleInitializationNamespaces(initializationOrder) : std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), jsonEligibility, sourcePaths);
        const auto worldview = ::app_src_emitter_worldview_::planWorldview(result, module->path, concretePlan, worldviewGraphIndex);
        (emitter->worldviewModules = worldview->modules);
        (emitter->worldviewInterfaceKeys = worldview->interfaceKeys);
        const auto emitted = emitter->emit(info->program, ((module->path == entry) ? entryMode : std::string("none")));
        (emitted->fingerprint = fingerprint);
        graph->modules->push_back(emitted);
        if (coverageModuleId >= 0) {
            graph->coverageModules->push_back(std::make_shared<CoverageModuleMetadata>(coverageModuleId, module->path, emitted->instrumentedLines));
        }
    }
    return graph;
}
std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>> indexGraphModules(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>> indexed = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>{});
    const auto& _iterable_42 = result->modules;
    for (const auto& module : *_iterable_42) {
        doof::map_set(indexed, module->path, module, "", 0);
    }
    return indexed;
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> indexedGraphModule(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>& indexed, const std::string& path) {
    auto _binding_value_43 = doof::map_get(indexed, path, "", 0);
    if (doof::is_failure(_binding_value_43)) {
        const auto& module = _binding_value_43;
        return nullptr;
    }
    const auto module = doof::success_value(_binding_value_43);
    return module;
}
std::shared_ptr<doof::ordered_map<std::string, std::string>> indexReusableModuleFingerprints(const std::shared_ptr<std::vector<std::shared_ptr<ModuleEmissionCacheKey>>>& keys) {
    std::shared_ptr<doof::ordered_map<std::string, std::string>> indexed = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    const auto& _iterable_45 = keys;
    for (const auto& key : *_iterable_45) {
        if (![&]() -> bool { auto _map_has_46 = indexed; return _map_has_46->find(key->modulePath) != _map_has_46->end(); }()) {
            doof::map_set(indexed, key->modulePath, key->fingerprint, "", 0);
        }
    }
    return indexed;
}
bool reusableModuleMatches(const std::shared_ptr<doof::ordered_map<std::string, std::string>>& indexed, const std::string& path, const std::string& fingerprint) {
    auto _binding_value_47 = doof::map_get(indexed, path, "", 0);
    if (doof::is_failure(_binding_value_47)) {
        const auto& cached = _binding_value_47;
        return false;
    }
    const auto cached = doof::success_value(_binding_value_47);
    return (cached == fingerprint);
}
std::string moduleInstantiationFingerprintInput(const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
    auto value = std::string("");
    const auto& _iterable_49 = instantiations->functions;
    for (const auto& item : *_iterable_49) {
        (value = ((value + std::string("\nfunction:")) + item->key));
    }
    const auto& _iterable_51 = instantiations->classes;
    for (const auto& item : *_iterable_51) {
        (value = ((value + std::string("\nclass:")) + item->key));
    }
    const auto& _iterable_53 = instantiations->methods;
    for (const auto& item : *_iterable_53) {
        (value = ((value + std::string("\nmethod:")) + item->key));
    }
    const auto& _iterable_55 = instantiations->interfaces;
    for (const auto& item : *_iterable_55) {
        (value = ((value + std::string("\ninterface:")) + item->key));
        const auto& _iterable_57 = item->implementations;
        for (const auto& implementation : *_iterable_57) {
            (value = ((((value + std::string(":")) + implementation->modulePath) + std::string(":")) + implementation->typeName));
        }
    }
    const auto& _iterable_59 = instantiations->jsonSerializationKeys;
    for (const auto& key : *_iterable_59) {
        (value = ((value + std::string("\njson-serialize:")) + key));
    }
    const auto& _iterable_61 = instantiations->jsonDeserializationKeys;
    for (const auto& key : *_iterable_61) {
        (value = ((value + std::string("\njson-deserialize:")) + key));
    }
    return value;
}
std::string moduleEmissionFingerprint(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>& moduleIndex, const std::string& path, const std::string& entry, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::string>>& initializationOrder, const std::string& configurationFingerprint, const std::string& instantiationFingerprintInput) {
    auto value = (((((((std::string("doof-module-emission-2\n") + configurationFingerprint) + std::string("\n")) + path) + std::string("\n")) + entryMode) + std::string("\n")) + doof::to_string(coverage));
    std::shared_ptr<doof::ordered_set<std::string>> reachable = std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{});
    collectModuleDependencyClosure(moduleIndex, path, reachable);
    const auto& _iterable_63 = result->modules;
    for (const auto& candidate : *_iterable_63) {
        if (reachable->count(candidate->path) > 0) {
            (value = ((((value + std::string("\nsource:")) + candidate->path) + std::string(":")) + candidate->sourceHash));
        }
    }
    (value = (value + instantiationFingerprintInput));
    if (path == entry) {
        const auto& _iterable_65 = initializationOrder;
        for (const auto& initialized : *_iterable_65) {
            (value = ((value + std::string("\ninitialize:")) + initialized));
        }
    }
    return ::std_::crypto::index::sha256HexString(value);
}
void collectModuleDependencyClosure(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>& moduleIndex, const std::string& path, const std::shared_ptr<doof::ordered_set<std::string>>& reachable) {
    if (reachable->count(path) > 0) {
        return;
    }
    reachable->insert(path);
    const auto module = indexedGraphModule(moduleIndex, path);
    if (doof::is_null(module)) {
        return;
    }
    const auto& _iterable_67 = module->imports;
    for (const auto& imported : *_iterable_67) {
        collectModuleDependencyClosure(moduleIndex, imported->sourceModule, reachable);
    }
    const auto& _iterable_69 = module->namespaceImports;
    for (const auto& imported : *_iterable_69) {
        collectModuleDependencyClosure(moduleIndex, imported->sourceModule, reachable);
    }
    const auto& _iterable_71 = module->reExports;
    for (const auto& reExport : *_iterable_71) {
        collectModuleDependencyClosure(moduleIndex, reExport, reachable);
    }
}
bool isCoverageEligible(const std::string& modulePath) {
    return ((!doof::string_endsWith(modulePath, std::string(".test.do")) && !doof::string_contains(modulePath, std::string("/.doof-tests/"))) && !doof::string_startsWith(modulePath, std::string("/std/")));
}
std::shared_ptr<std::vector<int32_t>> sortedCoverageLines(const std::shared_ptr<std::vector<int32_t>>& lines) {
    std::shared_ptr<std::vector<int32_t>> result = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    auto last = -1;
    for (int32_t count = 0; count < static_cast<int32_t>((lines)->size()); ++count) {
        std::optional<int32_t> candidate = std::nullopt;
        const auto& _iterable_74 = lines;
        for (const auto& line : *_iterable_74) {
            if ((line > last) && (doof::is_null(candidate) || (line < candidate.value()))) {
                (candidate = line);
            }
        }
        if (!doof::is_null(candidate)) {
            result->push_back(candidate.value());
            (last = candidate.value());
        }
    }
    return result;
}
void configureInstantiationRegistry(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& plan) {
    const auto& _iterable_76 = plan->functions;
    for (const auto& instantiation : *_iterable_76) {
        context->concreteFunctionKeys->push_back(instantiation->key);
        context->concreteFunctionNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_78 = plan->classes;
    for (const auto& instantiation : *_iterable_78) {
        context->concreteClassKeys->push_back(instantiation->key);
        context->concreteClassNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_80 = plan->methods;
    for (const auto& instantiation : *_iterable_80) {
        context->concreteMethodKeys->push_back(instantiation->key);
        context->concreteMethodNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_82 = plan->interfaces;
    for (const auto& instantiation : *_iterable_82) {
        context->concreteInterfaceKeys->push_back(instantiation->key);
        context->concreteInterfaceNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_84 = plan->jsonSerializationKeys;
    for (const auto& key : *_iterable_84) {
        context->jsonSerializationKeys->push_back(key);
    }
    const auto& _iterable_86 = plan->jsonDeserializationKeys;
    for (const auto& key : *_iterable_86) {
        context->jsonDeserializationKeys->push_back(key);
    }
}
void addConcreteHeaderDeclarations(const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<std::vector<std::string>>& interfaceKeys) {
    const auto& _iterable_88 = instantiations->methods;
    for (const auto& instantiation : *_iterable_88) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        if (!programDeclares(program, instantiation->owner->name)) {
            continue;
        }
        const auto& _iterable_90 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_90) {
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
    }
    const auto& _iterable_92 = instantiations->interfaces;
    for (const auto& interface_ : *_iterable_92) {
        if (!containsString(interfaceKeys, interface_->key)) {
            continue;
        }
        if ((interface_->name != std::string("Stream")) && (interface_->modulePath != context->modulePath)) {
            continue;
        }
        if ((interface_->name != std::string("Stream")) && !programDeclares(program, interface_->name)) {
            continue;
        }
        auto alternatives = std::string("");
        const auto& _iterable_94 = interface_->implementations;
        for (const auto& implementation : *_iterable_94) {
            if (alternatives != std::string("")) {
                (alternatives = (alternatives + std::string(", ")));
            }
            auto typeName = implementation->typeName;
            if (implementation->modulePath != context->modulePath) {
                const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(implementation->modulePath);
                plan->typeOnlyForwardDeclarations->push_back(((((std::string("namespace ") + namespace_) + std::string(" { struct ")) + implementation->typeName) + std::string("; }\n")));
                (typeName = (((std::string("::") + namespace_) + std::string("::")) + typeName));
            }
            (alternatives = (((alternatives + std::string("std::shared_ptr<")) + typeName) + std::string(">")));
        }
        if (alternatives == std::string("")) {
            (alternatives = std::string("std::monostate"));
        }
        ::app_src_emitter_header_::reserveHeaderNamespaceName(plan, interface_->emittedName);
        plan->interfaceAliases->push_back(((((std::string("using ") + interface_->emittedName) + std::string(" = std::variant<")) + alternatives) + std::string(">;\n")));
    }
    const auto& _iterable_96 = instantiations->classes;
    for (const auto& instantiation : *_iterable_96) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        if (!programDeclares(program, instantiation->declaration->name)) {
            continue;
        }
        const auto& _iterable_98 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_98) {
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
        plan->classForwardDeclarations->push_back(((std::string("struct ") + instantiation->emittedName) + std::string(";\n")));
        ::app_src_emitter_header_::reserveHeaderNamespaceName(plan, instantiation->emittedName);
        (context->substitution = instantiation->substitution);
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{});
        const auto& _iterable_100 = instantiations->methods;
        for (const auto& method : *_iterable_100) {
            if (method->ownerKey == instantiation->key) {
                methods->push_back(method);
            }
        }
        plan->classDefinitions->push_back(::app_src_emitter_decl_::emitClassDeclaration(instantiation->declaration, context, instantiation->emittedName, methods));
        clearInstantiation(context);
    }
    const auto& _iterable_102 = instantiations->functions;
    for (const auto& instantiation : *_iterable_102) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        if (!programDeclares(program, instantiation->declaration->name)) {
            continue;
        }
        const auto& _iterable_104 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_104) {
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
        (context->substitution = instantiation->substitution);
        const auto signature = ::app_src_emitter_decl_::emitFunctionDeclaration(instantiation->declaration, instantiation->emittedName, context->modulePath, context);
        ::app_src_emitter_header_::reserveHeaderNamespaceName(plan, instantiation->emittedName);
        if (instantiation->declaration->native_) {
            plan->nativeAdapterSignatures->push_back(signature);
        } else {
            plan->functionSignatures->push_back(signature);
        }
        clearInstantiation(context);
    }
}
bool programDeclares(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& name) {
    const auto& _iterable_106 = program->statements;
    for (const auto& statement : *_iterable_106) {
        if (headerDeclarationName(statement) == name) {
            return true;
        }
    }
    return false;
}
std::string headerDeclarationName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return headerDeclarationName(export_->declaration);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return interface_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            return fn->name;
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
void addConcreteTypeForwardDeclarations(const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if ((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) {
                const auto typeName = concreteClassTypeName(context, class_);
                const auto declaration = ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(class_->symbol->module)) + std::string(" { struct ")) + typeName) + std::string("; }\n"));
                if (!containsString(plan->typeOnlyForwardDeclarations, declaration)) {
                    plan->typeOnlyForwardDeclarations->push_back(declaration);
                }
            }
            const auto& _iterable_108 = class_->typeArgs;
            for (const auto& argument : *_iterable_108) {
                addConcreteTypeForwardDeclarations(plan, context, argument);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            if ((enum_->symbol->module != std::string("")) && (enum_->symbol->module != context->modulePath)) {
                const auto declaration = ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(enum_->symbol->module)) + std::string(" { enum class ")) + enum_->name) + std::string("; }\n"));
                if (!containsString(plan->typeOnlyForwardDeclarations, declaration)) {
                    plan->typeOnlyForwardDeclarations->push_back(declaration);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto& _iterable_110 = interface_->typeArgs;
            for (const auto& argument : *_iterable_110) {
                addConcreteTypeForwardDeclarations(plan, context, argument);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, map->keyType);
            addConcreteTypeForwardDeclarations(plan, context, map->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, result_->valueType);
            addConcreteTypeForwardDeclarations(plan, context, result_->errorType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, promise->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_112 = tuple->elements;
            for (const auto& element : *_iterable_112) {
                addConcreteTypeForwardDeclarations(plan, context, element);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_114 = union_->types;
            for (const auto& member : *_iterable_114) {
                addConcreteTypeForwardDeclarations(plan, context, member);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_116 = function_->params;
            for (const auto& parameter : *_iterable_116) {
                addConcreteTypeForwardDeclarations(plan, context, parameter->type_);
            }
            addConcreteTypeForwardDeclarations(plan, context, function_->returnType);
    }
    else {
    }
    }
}
std::string concreteClassTypeName(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::ClassType>& class_) {
    if (static_cast<int32_t>((class_->typeArgs)->size()) == 0) {
        return class_->name;
    }
    const auto key = ::app_src_emitter_monomorphize_::classInstantiationKey(class_->symbol->module, class_->name, class_->typeArgs);
    for (int32_t index = 0; index < static_cast<int32_t>((context->concreteClassKeys)->size()); ++index) {
        if (doof::array_at(context->concreteClassKeys, index, "src/emitter-module", 654) == key) {
            return doof::array_at(context->concreteClassNames, index, "src/emitter-module", 654);
        }
    }
    doof::panic((std::string("Missing concrete class instantiation for ") + key));
    return std::string("");
}
std::string emitConcreteFunctions(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
    auto result = std::string("");
    const auto& _iterable_119 = instantiations->functions;
    for (const auto& instantiation : *_iterable_119) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        (context->substitution = instantiation->substitution);
        if (instantiation->declaration->native_) {
            (result = (result + ::app_src_emitter_decl_::emitNativeFunctionAdapterDefinition(instantiation->declaration, instantiation->emittedName, context)));
        } else {
            (result = (result + ::app_src_emitter_decl_::emitFunctionDefinition(instantiation->declaration, context, instantiation->emittedName)));
        }
        clearInstantiation(context);
    }
    return result;
}
std::string emitConcreteClassDefinitions(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
    auto result = std::string("");
    const auto& _iterable_121 = instantiations->classes;
    for (const auto& instantiation : *_iterable_121) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        (context->substitution = instantiation->substitution);
        (result = (result + ::app_src_emitter_decl_::emitStaticClassFieldDefinitions(instantiation->declaration, context, instantiation->emittedName)));
        const auto& _iterable_123 = instantiation->declaration->methods;
        for (const auto& method : *_iterable_123) {
            if (static_cast<int32_t>((method->typeParams)->size()) == 0) {
                (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(instantiation->declaration, method, context, instantiation->emittedName, std::string(""))));
            }
        }
        (result = (result + ::app_src_emitter_decl_::emitClassDestructorDefinition(instantiation->declaration, context, instantiation->emittedName)));
        clearInstantiation(context);
    }
    return result;
}
std::string emitConcreteMethodDefinitions(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
    auto result = std::string("");
    const auto& _iterable_125 = instantiations->methods;
    for (const auto& instantiation : *_iterable_125) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        (context->substitution = instantiation->substitution);
        (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(instantiation->owner, instantiation->declaration, context, instantiation->ownerEmittedName, instantiation->emittedName)));
        clearInstantiation(context);
    }
    return result;
}
void clearInstantiation(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    (context->substitution = nullptr);
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> emitModuleSurfaces(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> surfaces = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{});
    const auto& _iterable_127 = result->modules;
    for (const auto& module : *_iterable_127) {
        std::shared_ptr<std::vector<std::string>> genericTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_129 = module->program->statements;
        for (const auto& statement : *_iterable_129) {
            collectGenericSurfaceSymbols(statement, genericTypes);
        }
        surfaces->push_back(std::make_shared<::app_src_emitter_context_::EmitModuleSurface>(module->path, module->exports, module->imports, genericTypes));
    }
    return surfaces;
}
void collectGenericSurfaceSymbols(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<std::vector<std::string>>& typeNames) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (static_cast<int32_t>((class_->typeParams)->size()) > 0) {
                typeNames->push_back(class_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            if (static_cast<int32_t>((interface_->typeParams)->size()) > 0) {
                typeNames->push_back(interface_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            if (static_cast<int32_t>((alias->typeParams)->size()) > 0) {
                typeNames->push_back(alias->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            collectGenericSurfaceSymbols(export_->declaration, typeNames);
    }
    else {
    }
    }
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
    const auto& _iterable_131 = result->modules;
    for (const auto& module : *_iterable_131) {
        programs->push_back(module->program);
    }
    return programs;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> surfaceImports(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>& surfaces, const std::string& path) {
    const auto& _iterable_133 = surfaces;
    for (const auto& surface : *_iterable_133) {
        if (surface->path == path) {
            return surface->imports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> infoNamespaceImports(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
    const auto& _iterable_135 = result->modules;
    for (const auto& module : *_iterable_135) {
        if (module->path == path) {
            return module->namespaceImports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{});
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> infoImports(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
    const auto& _iterable_137 = result->modules;
    for (const auto& module : *_iterable_137) {
        if (module->path == path) {
            return module->imports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findGraphModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
    const auto& _iterable_139 = result->modules;
    for (const auto& module : *_iterable_139) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::string>> planModuleInitializationOrder(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::string& entryMode) {
    std::shared_ptr<std::vector<std::string>> order = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> visiting = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    visitInitializationModule(result, entry, entry, entryMode, visiting, visited, order);
    return order;
}
void visitInitializationModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path, const std::string& entry, const std::string& entryMode, const std::shared_ptr<std::vector<std::string>>& visiting, const std::shared_ptr<std::vector<std::string>>& visited, const std::shared_ptr<std::vector<std::string>>& order) {
    if (containsString(visited, path) || containsString(visiting, path)) {
        return;
    }
    const auto info = findGraphModule(result, path);
    if (doof::is_null(info)) {
        return;
    }
    visiting->push_back(path);
    const auto& _iterable_141 = info->imports;
    for (const auto& imported : *_iterable_141) {
        if (!imported->typeOnly) {
            visitInitializationModule(result, imported->sourceModule, entry, entryMode, visiting, visited, order);
        }
    }
    const auto& _iterable_143 = info->namespaceImports;
    for (const auto& imported : *_iterable_143) {
        if (!imported->typeOnly) {
            visitInitializationModule(result, imported->sourceModule, entry, entryMode, visiting, visited, order);
        }
    }
    const auto& _iterable_145 = info->reExports;
    for (const auto& reExport : *_iterable_145) {
        visitInitializationModule(result, reExport, entry, entryMode, visiting, visited, order);
    }
    auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(visiting); if (doof::is_failure(_try_value)) doof::panic_at("src/emitter-module", 785, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    visited->push_back(path);
    const auto scriptEntry = (((path == entry) && ((entryMode == std::string("executable")) || (entryMode == std::string("ios-app")))) && hasScriptStatements(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{info->program})));
    if (!scriptEntry && moduleHasDeferredInitialization(info->program)) {
        order->push_back(path);
    }
}
std::shared_ptr<std::vector<std::string>> moduleInitializationNamespaces(const std::shared_ptr<std::vector<std::string>>& paths) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_147 = paths;
    for (const auto& path : *_iterable_147) {
        result->push_back(::app_src_emitter_names_::moduleNamespace(path));
    }
    return result;
}
std::string emitSourceStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
                return std::string("");
            }
            return ::app_src_emitter_decl_::emitFunctionDefinition(fn, context, ((fn->name == std::string("main")) ? std::string("doof_main") : fn->name));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (class_->native_) {
                return std::string("");
            }
            auto result = (std::string("\n") + ::app_src_emitter_decl_::emitStaticClassFieldDefinitions(class_, context, std::string("")));
            if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
                const auto& _iterable_149 = class_->methods;
                for (const auto& method : *_iterable_149) {
                    (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(class_, method, context, std::string(""), std::string(""))));
                }
                (result = (result + ::app_src_emitter_decl_::emitClassDestructorDefinition(class_, context, std::string(""))));
            }
            (result = (result + ::app_src_emitter_json_::emitGeneratedJsonMethods(class_, context)));
            (result = (result + ::app_src_emitter_metadata_::emitMetadataDefinition(class_, context)));
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return ::app_src_emitter_json_::emitInterfaceJsonDefinition(interface_, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(const_), const_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(readonly_), readonly_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(binding), binding->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(let_), let_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return emitSourceStatement(export_->declaration, context);
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitModuleStorage(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto initializer = (isCxxConstantInitializer(value) ? ::app_src_emitter_expr_::emitExpression(value, context, moduleValueType(declaration)) : std::string(""));
    return ::app_src_emitter_decl_::emitModuleValueStorage(declaration, context, initializer);
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> moduleValueType(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration) {
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    }
    doof::unreachable();
    return std::monostate{};
}
bool isCxxConstantInitializer(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value) {
    {
        auto _case_subject = value;
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
bool moduleHasDeferredInitialization(const std::shared_ptr<::app_src_ast_::Program>& program) {
    const auto& _iterable_151 = program->statements;
    for (const auto& statement : *_iterable_151) {
        if (statementHasDeferredInitialization(statement)) {
            return true;
        }
    }
    return false;
}
bool statementHasDeferredInitialization(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (class_->native_ || (static_cast<int32_t>((class_->typeParams)->size()) > 0)) {
                return false;
            }
            const auto& _iterable_153 = class_->fields;
            for (const auto& field : *_iterable_153) {
                if (field->static_ && (!doof::is_null(field->defaultValue))) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return statementHasDeferredInitialization(export_->declaration);
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
std::string emitModuleInitializer(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, bool includeValues) {
    auto assignments = std::string("");
    if (includeValues) {
        const auto& _iterable_155 = programs;
        for (const auto& program : *_iterable_155) {
            const auto& _iterable_157 = program->statements;
            for (const auto& statement : *_iterable_157) {
                (assignments = (assignments + emitModuleInitializerStatement(statement, context)));
            }
        }
    }
    if (assignments == std::string("")) {
        return std::string("");
    }
    return ((std::string("\nvoid __doof_initialize_module() {\n") + assignments) + std::string("}\n"));
}
std::string emitModuleInitializerStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            auto result = std::string("");
            if (class_->native_ || (static_cast<int32_t>((class_->typeParams)->size()) > 0)) {
                return result;
            }
            const auto& _iterable_159 = class_->fields;
            for (const auto& field : *_iterable_159) {
                if (!field->static_ || doof::is_null(field->defaultValue)) {
                    continue;
                }
                const auto& _iterable_161 = field->names;
                for (const auto& name : *_iterable_161) {
                    (result = (((((((result + std::string("        ")) + class_->name) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType)) + std::string(";\n")));
                }
            }
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return emitModuleInitializerStatement(export_->declaration, context);
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitModuleValueAssignment(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (isCxxConstantInitializer(value)) {
        return std::string("");
    }
    const auto name = scriptDeclarationName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration));
    if ((name == std::string("")) || (name == std::string("_"))) {
        return std::string("");
    }
    return ((((std::string("        ") + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, moduleValueType(declaration))) + std::string(";\n"));
}
std::string emitGraphInitializationCall(const std::shared_ptr<std::vector<std::string>>& namespaces) {
    auto result = std::string("");
    const auto& _iterable_163 = namespaces;
    for (const auto& namespace_ : *_iterable_163) {
        (result = (((result + std::string("::")) + namespace_) + std::string("::__doof_initialize_module(); ")));
    }
    return result;
}
std::string emitNativeClassMethods(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto result = std::string("");
    const auto& _iterable_165 = programs;
    for (const auto& program : *_iterable_165) {
        const auto& _iterable_167 = program->statements;
        for (const auto& statement : *_iterable_167) {
            (result = (result + emitNativeClassMethodsForStatement(statement, context)));
        }
    }
    return result;
}
std::string emitNativeClassMethodsForStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (!class_->native_) {
                return std::string("");
            }
            auto result = std::string("");
            const auto& _iterable_169 = class_->methods;
            for (const auto& method : *_iterable_169) {
                if (!method->bodyless) {
                    (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(class_, method, context, std::string(""), std::string(""))));
                }
            }
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return emitNativeClassMethodsForStatement(export_->declaration, context);
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitMainWrapper(const std::string& moduleName, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, bool hasScript, const std::string& initializationCall) {
    if (!hasScript) {
        const auto signature = (plan->mainAcceptsArgs ? std::string("int main(int argc, char** argv)") : std::string("int main()"));
        const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string(""));
        const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
        const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
        const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
        const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
        return (((((((((std::string("\n") + signature) + std::string(" { try { ")) + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
    }
    const auto needsArguments = (plan->mainAcceptsArgs || hasScript);
    const auto signature = (needsArguments ? std::string("int main(int argc, char** argv)") : std::string("int main()"));
    const auto argumentSetup = (needsArguments ? std::string("std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); ") : std::string(""));
    const auto scriptCall = (hasScript ? (moduleName + std::string("::__doof_run_script(arguments); ")) : std::string(""));
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(arguments)")) : (moduleName + std::string("::doof_main()")));
    const auto success = (!plan->hasMain ? (scriptCall + std::string("return 0;")) : (plan->mainReturnsInt ? (((scriptCall + std::string("return ")) + call) + std::string(";")) : ((scriptCall + call) + std::string("; return 0;"))));
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
    return (((((((((std::string("\n") + signature) + std::string(" { try { ")) + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
}
std::string emitAppEntryWrapper(const std::string& moduleName, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, bool hasScript, const std::string& initializationCall) {
    if (!hasScript) {
        const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string("(void)argc; (void)argv; "));
        const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
        const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
        const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
        const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
        return (((((((std::string("\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { ") + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
    }
    const auto needsArguments = (plan->mainAcceptsArgs || hasScript);
    const auto argumentSetup = (needsArguments ? std::string("std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); ") : std::string("(void)argc; (void)argv; "));
    const auto scriptCall = (hasScript ? (moduleName + std::string("::__doof_run_script(arguments); ")) : std::string(""));
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(arguments)")) : (moduleName + std::string("::doof_main()")));
    const auto success = (!plan->hasMain ? (scriptCall + std::string("return 0;")) : (plan->mainReturnsInt ? (((scriptCall + std::string("return ")) + call) + std::string(";")) : ((scriptCall + call) + std::string("; return 0;"))));
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
    return (((((((std::string("\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { ") + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
}
}
