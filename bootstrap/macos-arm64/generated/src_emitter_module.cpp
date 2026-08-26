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


#line 44 "/src/emitter-module.do"
std::shared_ptr<ModuleGraphPlan> planModuleGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 45 "/src/emitter-module.do"
    const auto plan = std::make_shared<ModuleGraphPlan>(std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{}));
#line 46 "/src/emitter-module.do"
    const auto& _iterable_2 = result->modules;
    for (const auto& info : *_iterable_2) {
#line 47 "/src/emitter-module.do"
        const auto module = std::make_shared<ModulePlan>(info->path, ::app_src_emitter_names_::moduleNamespace(info->path), ::app_src_emitter_names_::moduleHeaderName(info->path), ::app_src_emitter_names_::moduleSourceName(info->path));
#line 53 "/src/emitter-module.do"
        plan->modules->push_back(module);
    }
#line 55 "/src/emitter-module.do"
    return plan;
}





#line 110 "/src/emitter-module.do"
std::shared_ptr<ModuleEmission> CxxModuleEmitter::emit(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& entryMode) {
#line 111 "/src/emitter-module.do"
    const auto context = ((this->modulePath == std::string("")) ? ::app_src_emitter_context_::createEmitContext(program) : ::app_src_emitter_context_::createEmitContextForModule(program, this->modulePath, this->allPrograms));
#line 112 "/src/emitter-module.do"
    (context->namespaceImports = this->namespaceImports);
#line 113 "/src/emitter-module.do"
    (context->sourcePath = sourcePathFor(this->sourcePaths, context->modulePath));
#line 114 "/src/emitter-module.do"
    (context->imports = this->imports);
#line 115 "/src/emitter-module.do"
    (context->moduleSurfaces = this->moduleSurfaces);
#line 116 "/src/emitter-module.do"
    (context->jsonEligibility = this->jsonEligibility);
#line 117 "/src/emitter-module.do"
    configureJsonDemandRegistry(context, this->jsonSerializationKeys, this->jsonDeserializationKeys);
#line 118 "/src/emitter-module.do"
    if (this->coverageModuleId >= 0) {
#line 119 "/src/emitter-module.do"
        (context->coverageEnabled = true);
#line 120 "/src/emitter-module.do"
        (context->coverageModuleId = this->coverageModuleId);
    }
#line 122 "/src/emitter-module.do"
    if (!doof::is_null(this->instantiations)) {
#line 122 "/src/emitter-module.do"
        configureInstantiationRegistry(context, doof::unwrap_optional(this->instantiations));
    }
#line 123 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>> sections = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>>(std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>{});
#line 124 "/src/emitter-module.do"
    std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan = nullptr;
#line 125 "/src/emitter-module.do"
    auto views = this->worldviewModules;
#line 126 "/src/emitter-module.do"
    if (static_cast<int32_t>((views)->size()) == 0) {
#line 126 "/src/emitter-module.do"
        (views = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{std::make_shared<::app_src_emitter_worldview_::WorldviewModule>(this->modulePath, program)}));
    }
#line 127 "/src/emitter-module.do"
    const auto& _iterable_4 = views;
    for (const auto& view : *_iterable_4) {
#line 128 "/src/emitter-module.do"
        const auto sectionContext = ::app_src_emitter_context_::createEmitContextForModule(view->program, view->path, this->allPrograms);
#line 129 "/src/emitter-module.do"
        (sectionContext->imports = surfaceImports(this->moduleSurfaces, view->path));
#line 130 "/src/emitter-module.do"
        (sectionContext->sourcePath = sourcePathFor(this->sourcePaths, view->path));
#line 131 "/src/emitter-module.do"
        (sectionContext->moduleSurfaces = this->moduleSurfaces);
#line 132 "/src/emitter-module.do"
        (sectionContext->jsonEligibility = this->jsonEligibility);
#line 133 "/src/emitter-module.do"
        configureJsonDemandRegistry(sectionContext, this->jsonSerializationKeys, this->jsonDeserializationKeys);
#line 134 "/src/emitter-module.do"
        if (!doof::is_null(this->instantiations)) {
#line 134 "/src/emitter-module.do"
            configureInstantiationRegistry(sectionContext, doof::unwrap_optional(this->instantiations));
        }
#line 135 "/src/emitter-module.do"
        const auto sectionPlan = ::app_src_emitter_header_::planHeader(view->program, sectionContext);
#line 136 "/src/emitter-module.do"
        if (!doof::is_null(this->instantiations)) {
#line 137 "/src/emitter-module.do"
            addConcreteHeaderDeclarations(sectionPlan, sectionContext, doof::unwrap_optional(this->instantiations), view->program, this->worldviewInterfaceKeys);
        }
#line 139 "/src/emitter-module.do"
        const auto sectionNamespace = ((view->path == this->modulePath) ? ((this->namespaceNameOverride != std::string("")) ? this->namespaceNameOverride : ((this->modulePath == std::string("")) ? (this->moduleName + std::string("_")) : ::app_src_emitter_names_::moduleNamespace(view->path))) : ::app_src_emitter_names_::moduleNamespace(view->path));
#line 142 "/src/emitter-module.do"
        sections->push_back(std::make_shared<::app_src_emitter_header_::HeaderSection>(sectionNamespace, sectionPlan));
#line 143 "/src/emitter-module.do"
        if (view->path == this->modulePath) {
#line 143 "/src/emitter-module.do"
            (plan = sectionPlan);
        }
    }
#line 145 "/src/emitter-module.do"
    if (doof::is_null(plan)) {
#line 145 "/src/emitter-module.do"
        doof::panic((std::string("worldview omitted root module ") + this->modulePath));
    }
#line 146 "/src/emitter-module.do"
    (context->scriptEntry = (((entryMode == std::string("executable")) || (entryMode == std::string("ios-app"))) && hasScriptStatements(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}))));
#line 147 "/src/emitter-module.do"
    return emitPlanned(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}), context, doof::unwrap_optional(plan), sections, entryMode);
}
#line 150 "/src/emitter-module.do"
std::shared_ptr<ModuleEmission> CxxModuleEmitter::emitPlanned(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>>& sections, const std::string& entryMode) {
#line 151 "/src/emitter-module.do"
    const auto headerName = ((this->headerNameOverride == std::string("")) ? (this->moduleName + std::string(".hpp")) : this->headerNameOverride);
#line 152 "/src/emitter-module.do"
    const auto sourceName = ((this->sourceNameOverride == std::string("")) ? (this->moduleName + std::string(".cpp")) : this->sourceNameOverride);
#line 153 "/src/emitter-module.do"
    const auto namespaceName = ((this->namespaceNameOverride == std::string("")) ? (this->moduleName + std::string("_")) : this->namespaceNameOverride);
#line 154 "/src/emitter-module.do"
    const auto header = ::app_src_emitter_header_::renderProjectedHeader(sections);
#line 155 "/src/emitter-module.do"
    const auto sourceBuilder = ::doof::StringBuilder::constructor();
#line 156 "/src/emitter-module.do"
    sourceBuilder->append(((std::string("#include \"") + headerName) + std::string("\"\n\n")));
#line 157 "/src/emitter-module.do"
    const auto& _iterable_6 = this->initializationModuleNamespaces;
    for (const auto& namespace_ : *_iterable_6) {
#line 158 "/src/emitter-module.do"
        sourceBuilder->append(((std::string("namespace ") + namespace_) + std::string(" { void __doof_initialize_module(); }\n")));
    }
#line 160 "/src/emitter-module.do"
    if (static_cast<int32_t>((this->initializationModuleNamespaces)->size()) > 0) {
#line 160 "/src/emitter-module.do"
        sourceBuilder->append(std::string("\n"));
    }
#line 161 "/src/emitter-module.do"
    sourceBuilder->append(((std::string("namespace ") + namespaceName) + std::string(" {\n")));
#line 162 "/src/emitter-module.do"
    sourceBuilder->append(emitImportedNamespaces(context, this->worldviewModules));
#line 163 "/src/emitter-module.do"
    if (context->scriptEntry) {
#line 163 "/src/emitter-module.do"
        sourceBuilder->append(emitScriptStorage(programs, context));
    }
#line 164 "/src/emitter-module.do"
    const auto& _iterable_8 = programs;
    for (const auto& program : *_iterable_8) {
#line 165 "/src/emitter-module.do"
        const auto& _iterable_10 = program->statements;
        for (const auto& statement : *_iterable_10) {
#line 166 "/src/emitter-module.do"
            if (!(context->scriptEntry && (!doof::is_null(scriptGlobalDeclaration(statement))))) {
#line 167 "/src/emitter-module.do"
                sourceBuilder->append(emitSourceStatement(statement, context));
            }
        }
    }
#line 171 "/src/emitter-module.do"
    sourceBuilder->append(::app_src_emitter_context_::generatedLineDirective());
#line 172 "/src/emitter-module.do"
    sourceBuilder->append(emitModuleInitializer(programs, context, !context->scriptEntry));
#line 173 "/src/emitter-module.do"
    if (context->scriptEntry) {
#line 173 "/src/emitter-module.do"
        sourceBuilder->append(emitScriptRunner(programs, context));
    }
#line 174 "/src/emitter-module.do"
    if (!doof::is_null(this->instantiations)) {
#line 174 "/src/emitter-module.do"
        sourceBuilder->append(emitConcreteFunctions(context, doof::unwrap_optional(this->instantiations)));
    }
#line 175 "/src/emitter-module.do"
    sourceBuilder->append(std::string("}\n"));
#line 176 "/src/emitter-module.do"
    const auto nativeMethods = emitNativeClassMethods(programs, context);
#line 177 "/src/emitter-module.do"
    if (nativeMethods != std::string("")) {
#line 178 "/src/emitter-module.do"
        sourceBuilder->append((((std::string("\nusing namespace ::") + namespaceName) + std::string(";\n\n")) + nativeMethods));
    }
#line 180 "/src/emitter-module.do"
    const auto initializationCall = emitGraphInitializationCall(this->initializationModuleNamespaces);
#line 181 "/src/emitter-module.do"
    if ((entryMode == std::string("executable")) && (plan->hasMain || context->scriptEntry)) {
#line 181 "/src/emitter-module.do"
        sourceBuilder->append((::app_src_emitter_context_::generatedLineDirective() + emitMainWrapper(namespaceName, plan, context->scriptEntry, initializationCall)));
    }
#line 182 "/src/emitter-module.do"
    if ((entryMode == std::string("ios-app")) && (plan->hasMain || context->scriptEntry)) {
#line 182 "/src/emitter-module.do"
        sourceBuilder->append((::app_src_emitter_context_::generatedLineDirective() + emitAppEntryWrapper(namespaceName, plan, context->scriptEntry, initializationCall)));
    }
#line 183 "/src/emitter-module.do"
    const auto source = sourceBuilder->drainToString();
#line 184 "/src/emitter-module.do"
    return std::make_shared<ModuleEmission>(context->modulePath, header, source, headerName, sourceName, context->coverageModuleId, sortedCoverageLines(context->coverageInstrumentedLines), false, std::string(""));
}
#line 192 "/src/emitter-module.do"
std::string sourcePathFor(const std::shared_ptr<doof::ordered_map<std::string, std::string>>& paths, const std::string& modulePath) {
#line 193 "/src/emitter-module.do"
    auto _binding_value_11 = doof::map_get(paths, modulePath, "", 0);
    if (doof::is_failure(_binding_value_11)) {
        const auto& path = _binding_value_11;
#line 193 "/src/emitter-module.do"
        return modulePath;
    }
    const auto path = doof::success_value(_binding_value_11);
#line 194 "/src/emitter-module.do"
    return path;
}
#line 197 "/src/emitter-module.do"
bool hasScriptStatements(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs) {
#line 198 "/src/emitter-module.do"
    const auto& _iterable_13 = programs;
    for (const auto& program : *_iterable_13) {
#line 198 "/src/emitter-module.do"
        const auto& _iterable_15 = program->statements;
        for (const auto& statement : *_iterable_15) {
#line 199 "/src/emitter-module.do"
            if (!isModuleDeclaration(statement)) {
#line 199 "/src/emitter-module.do"
                return true;
            }
        }
    }
#line 201 "/src/emitter-module.do"
    return false;
}
#line 204 "/src/emitter-module.do"
bool isValueDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 205 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
#line 206 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
#line 207 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
#line 208 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
#line 209 "/src/emitter-module.do"
            return true;
    }
    else {
#line 210 "/src/emitter-module.do"
            return false;
    }
    }
    doof::unreachable();
#line 212 "/src/emitter-module.do"
    return false;
}
#line 215 "/src/emitter-module.do"
bool isModuleDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 216 "/src/emitter-module.do"
    if (isValueDeclaration(statement)) {
#line 216 "/src/emitter-module.do"
        return true;
    }
#line 217 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
#line 218 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
#line 219 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
#line 220 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
#line 221 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
#line 222 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
#line 223 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
#line 224 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
#line 225 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
#line 226 "/src/emitter-module.do"
            return true;
    }
    else {
#line 227 "/src/emitter-module.do"
            return false;
    }
    }
    doof::unreachable();
#line 229 "/src/emitter-module.do"
    return false;
}
#line 232 "/src/emitter-module.do"
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> scriptGlobalDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 233 "/src/emitter-module.do"
    if (isValueDeclaration(statement)) {
#line 233 "/src/emitter-module.do"
        return doof::optional_value(statement);
    }
#line 234 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
#line 235 "/src/emitter-module.do"
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 236 "/src/emitter-module.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 237 "/src/emitter-module.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 238 "/src/emitter-module.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 239 "/src/emitter-module.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else {
            }
            }
    }
    else {
    }
    }
#line 244 "/src/emitter-module.do"
    return std::monostate{};
}
#line 247 "/src/emitter-module.do"
std::string scriptDeclarationName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 248 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 249 "/src/emitter-module.do"
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 250 "/src/emitter-module.do"
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 251 "/src/emitter-module.do"
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 252 "/src/emitter-module.do"
            return value->name;
    }
    else {
#line 253 "/src/emitter-module.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 255 "/src/emitter-module.do"
    return std::string("");
}
#line 258 "/src/emitter-module.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> scriptDeclarationType(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 259 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 260 "/src/emitter-module.do"
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 261 "/src/emitter-module.do"
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 262 "/src/emitter-module.do"
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 263 "/src/emitter-module.do"
            return value->resolvedType;
    }
    else {
#line 264 "/src/emitter-module.do"
            return std::monostate{};
    }
    }
    doof::unreachable();
#line 266 "/src/emitter-module.do"
    return std::monostate{};
}
#line 269 "/src/emitter-module.do"
bool scriptDeclarationMutable(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 270 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
#line 271 "/src/emitter-module.do"
            return true;
    }
    else {
#line 272 "/src/emitter-module.do"
            return false;
    }
    }
    doof::unreachable();
#line 274 "/src/emitter-module.do"
    return false;
}
#line 277 "/src/emitter-module.do"
std::string emitScriptStorage(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 278 "/src/emitter-module.do"
    auto source = std::string("\n");
#line 279 "/src/emitter-module.do"
    const auto& _iterable_17 = programs;
    for (const auto& program : *_iterable_17) {
#line 279 "/src/emitter-module.do"
        const auto& _iterable_19 = program->statements;
        for (const auto& statement : *_iterable_19) {
#line 280 "/src/emitter-module.do"
            const auto declaration = scriptGlobalDeclaration(statement);
#line 281 "/src/emitter-module.do"
            if (doof::is_null(declaration)) {
#line 281 "/src/emitter-module.do"
                continue;
            }
#line 282 "/src/emitter-module.do"
            const auto name = scriptDeclarationName(doof::unwrap_optional(declaration));
#line 283 "/src/emitter-module.do"
            const auto type_ = scriptDeclarationType(doof::unwrap_optional(declaration));
#line 284 "/src/emitter-module.do"
            if (((name == std::string("")) || (name == std::string("_"))) || doof::is_null(type_)) {
#line 284 "/src/emitter-module.do"
                continue;
            }
#line 285 "/src/emitter-module.do"
            const auto cppName = ::app_src_emitter_expr_::cppIdentifier(name);
#line 286 "/src/emitter-module.do"
            const auto typeText = ::app_src_emitter_types_::emitContextType(doof::unwrap_optional(type_), context);
#line 287 "/src/emitter-module.do"
            (source = (((((source + std::string("std::optional<")) + typeText) + std::string("> __doof_script_storage_")) + cppName) + std::string(";\n")));
#line 288 "/src/emitter-module.do"
            const auto returnType = (scriptDeclarationMutable(doof::unwrap_optional(declaration)) ? (typeText + std::string("&")) : ((std::string("const ") + typeText) + std::string("&")));
#line 289 "/src/emitter-module.do"
            (source = ((((((((((source + returnType) + std::string(" __doof_script_get_")) + cppName) + std::string("() { if (!__doof_script_storage_")) + cppName) + std::string(".has_value()) doof::panic(\"Entry binding '")) + name) + std::string("' was accessed before initialization\"); return *__doof_script_storage_")) + cppName) + std::string("; }\n")));
        }
    }
#line 291 "/src/emitter-module.do"
    return (source + std::string("\n"));
}
#line 294 "/src/emitter-module.do"
std::string emitScriptRunner(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 295 "/src/emitter-module.do"
    const auto previousTryPanics = context->tryPanics;
#line 296 "/src/emitter-module.do"
    (context->tryPanics = true);
#line 297 "/src/emitter-module.do"
    auto source = std::string("\nvoid __doof_run_script(std::shared_ptr<std::vector<std::string>> arguments) {\n");
#line 298 "/src/emitter-module.do"
    const auto& _iterable_21 = programs;
    for (const auto& program : *_iterable_21) {
#line 298 "/src/emitter-module.do"
        const auto& _iterable_23 = program->statements;
        for (const auto& statement : *_iterable_23) {
#line 299 "/src/emitter-module.do"
            const auto declaration = scriptGlobalDeclaration(statement);
#line 300 "/src/emitter-module.do"
            if (!doof::is_null(declaration)) {
#line 301 "/src/emitter-module.do"
                (source = (source + ::app_src_emitter_stmt_::emitStatement(statement, 1, context)));
#line 302 "/src/emitter-module.do"
                const auto name = scriptDeclarationName(doof::unwrap_optional(declaration));
#line 303 "/src/emitter-module.do"
                if ((name != std::string("")) && (name != std::string("_"))) {
#line 303 "/src/emitter-module.do"
                    (source = (((((source + std::string("    __doof_script_storage_")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(".emplace(")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(");\n")));
                }
            } else if (!isModuleDeclaration(statement)) {
#line 305 "/src/emitter-module.do"
                (source = (source + ::app_src_emitter_stmt_::emitStatement(statement, 1, context)));
            }
        }
    }
#line 308 "/src/emitter-module.do"
    (context->tryPanics = previousTryPanics);
#line 309 "/src/emitter-module.do"
    return (source + std::string("}\n"));
}
#line 312 "/src/emitter-module.do"
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 313 "/src/emitter-module.do"
    const auto& _iterable_25 = values;
    for (const auto& existing : *_iterable_25) {
#line 313 "/src/emitter-module.do"
        if (existing == value) {
#line 313 "/src/emitter-module.do"
            return true;
        }
    }
#line 314 "/src/emitter-module.do"
    return false;
}
#line 317 "/src/emitter-module.do"
std::string emitImportedNamespaces(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>& worldviewModules) {
#line 318 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::string>> namespaces = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 319 "/src/emitter-module.do"
    const auto& _iterable_27 = context->imports;
    for (const auto& imported : *_iterable_27) {
#line 320 "/src/emitter-module.do"
        if (!worldviewContainsModule(worldviewModules, imported->sourceModule)) {
#line 320 "/src/emitter-module.do"
            continue;
        }
#line 321 "/src/emitter-module.do"
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(imported->sourceModule);
#line 322 "/src/emitter-module.do"
        addNamespace(namespaces, namespace_);
    }
#line 324 "/src/emitter-module.do"
    const auto& _iterable_29 = context->namespaceImports;
    for (const auto& imported : *_iterable_29) {
#line 325 "/src/emitter-module.do"
        if (!worldviewContainsModule(worldviewModules, imported->sourceModule)) {
#line 325 "/src/emitter-module.do"
            continue;
        }
#line 326 "/src/emitter-module.do"
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(imported->sourceModule);
#line 327 "/src/emitter-module.do"
        addNamespace(namespaces, namespace_);
    }
#line 329 "/src/emitter-module.do"
    auto result = std::string("");
#line 330 "/src/emitter-module.do"
    const auto& _iterable_31 = namespaces;
    for (const auto& namespace_ : *_iterable_31) {
#line 330 "/src/emitter-module.do"
        (result = (((result + std::string("using namespace ::")) + namespace_) + std::string(";\n")));
    }
#line 331 "/src/emitter-module.do"
    return result;
}
#line 334 "/src/emitter-module.do"
bool worldviewContainsModule(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>& modules, const std::string& path) {
#line 335 "/src/emitter-module.do"
    const auto& _iterable_33 = modules;
    for (const auto& module : *_iterable_33) {
#line 335 "/src/emitter-module.do"
        if (module->path == path) {
#line 335 "/src/emitter-module.do"
            return true;
        }
    }
#line 336 "/src/emitter-module.do"
    return false;
}
#line 339 "/src/emitter-module.do"
void addNamespace(const std::shared_ptr<std::vector<std::string>>& namespaces, const std::string& namespace_) {
#line 340 "/src/emitter-module.do"
    const auto& _iterable_35 = namespaces;
    for (const auto& existing : *_iterable_35) {
#line 340 "/src/emitter-module.do"
        if (existing == namespace_) {
#line 340 "/src/emitter-module.do"
            return;
        }
    }
#line 341 "/src/emitter-module.do"
    namespaces->push_back(namespace_);
}
#line 345 "/src/emitter-module.do"
std::shared_ptr<ModuleGraphEmission> emitModuleGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<ModuleEmissionCacheKey>>>& reusableModules, const std::string& configurationFingerprint, bool physicalSourcePaths) {
#line 355 "/src/emitter-module.do"
    const auto graph = std::make_shared<ModuleGraphEmission>(std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{}), std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(std::vector<std::shared_ptr<CoverageModuleMetadata>>{}), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 356 "/src/emitter-module.do"
    const auto concretePlan = [&]() -> std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> { auto _coalesce_36 = instantiations; if (doof::is_null(_coalesce_36)) return ::app_src_emitter_monomorphize_::buildInstantiationPlan(result); return doof::unwrap_optional(_coalesce_36); }();
#line 357 "/src/emitter-module.do"
    const auto plan = planModuleGraph(result);
#line 358 "/src/emitter-module.do"
    const auto initializationOrder = planModuleInitializationOrder(result, entry, entryMode);
#line 359 "/src/emitter-module.do"
    const auto graphPrograms = allPrograms(result);
#line 360 "/src/emitter-module.do"
    const auto graphSurfaces = emitModuleSurfaces(result);
#line 361 "/src/emitter-module.do"
    const auto moduleIndex = indexGraphModules(result);
#line 362 "/src/emitter-module.do"
    const auto reusableFingerprints = indexReusableModuleFingerprints(reusableModules);
#line 363 "/src/emitter-module.do"
    const auto instantiationFingerprintInput = moduleInstantiationFingerprintInput(concretePlan);
#line 364 "/src/emitter-module.do"
    const auto jsonEligibility = std::make_shared<::app_src_json_semantics_::JsonEligibilityCache>(std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}), std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}));
#line 365 "/src/emitter-module.do"
    const auto worldviewGraphIndex = ::app_src_emitter_worldview_::indexWorldviewGraph(result);
#line 366 "/src/emitter-module.do"
    std::shared_ptr<doof::ordered_map<std::string, std::string>> sourcePaths = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
#line 367 "/src/emitter-module.do"
    const auto& _iterable_38 = result->modules;
    for (const auto& info : *_iterable_38) {
#line 368 "/src/emitter-module.do"
        doof::map_set(sourcePaths, info->path, ((physicalSourcePaths && (info->physicalPath != std::string(""))) ? info->physicalPath : info->path), "", 0);
    }
#line 370 "/src/emitter-module.do"
    auto nextCoverageModuleId = 0;
#line 371 "/src/emitter-module.do"
    const auto& _iterable_40 = plan->modules;
    for (const auto& module : *_iterable_40) {
#line 372 "/src/emitter-module.do"
        const auto info = indexedGraphModule(moduleIndex, module->path);
#line 373 "/src/emitter-module.do"
        if (doof::is_null(info)) {
#line 373 "/src/emitter-module.do"
            continue;
        }
#line 374 "/src/emitter-module.do"
        auto coverageModuleId = -1;
#line 375 "/src/emitter-module.do"
        if (coverage && isCoverageEligible(module->path)) {
#line 376 "/src/emitter-module.do"
            (coverageModuleId = nextCoverageModuleId);
#line 377 "/src/emitter-module.do"
            (nextCoverageModuleId += 1);
        }
#line 379 "/src/emitter-module.do"
        const auto fingerprint = moduleEmissionFingerprint(result, moduleIndex, module->path, entry, entryMode, coverage, initializationOrder, ((configurationFingerprint + std::string("\nphysical-source-paths:")) + doof::to_string(physicalSourcePaths)), instantiationFingerprintInput);
#line 383 "/src/emitter-module.do"
        if (!coverage && reusableModuleMatches(reusableFingerprints, module->path, fingerprint)) {
#line 384 "/src/emitter-module.do"
            graph->modules->push_back(std::make_shared<ModuleEmission>(module->path, std::string(""), std::string(""), module->headerName, module->sourceName, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), true, fingerprint));
#line 388 "/src/emitter-module.do"
            continue;
        }
#line 390 "/src/emitter-module.do"
        const auto emitter = std::make_shared<CxxModuleEmitter>(module->namespaceName, module->headerName, module->sourceName, module->namespaceName, module->path, graphPrograms, infoNamespaceImports(result, module->path), infoImports(result, module->path), graphSurfaces, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), concretePlan, coverageModuleId, ((module->path == entry) ? moduleInitializationNamespaces(initializationOrder) : std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), jsonEligibility, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), sourcePaths);
#line 406 "/src/emitter-module.do"
        const auto worldview = ::app_src_emitter_worldview_::planWorldview(result, module->path, concretePlan, worldviewGraphIndex);
#line 407 "/src/emitter-module.do"
        (emitter->worldviewModules = worldview->modules);
#line 408 "/src/emitter-module.do"
        (emitter->worldviewInterfaceKeys = worldview->interfaceKeys);
#line 409 "/src/emitter-module.do"
        const auto emitted = emitter->emit(info->program, ((module->path == entry) ? entryMode : std::string("none")));
#line 410 "/src/emitter-module.do"
        (emitted->fingerprint = fingerprint);
#line 411 "/src/emitter-module.do"
        graph->modules->push_back(emitted);
#line 412 "/src/emitter-module.do"
        if (coverageModuleId >= 0) {
#line 413 "/src/emitter-module.do"
            graph->coverageModules->push_back(std::make_shared<CoverageModuleMetadata>(coverageModuleId, module->path, emitted->instrumentedLines));
        }
    }
#line 420 "/src/emitter-module.do"
    return graph;
}
#line 423 "/src/emitter-module.do"
std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>> indexGraphModules(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 424 "/src/emitter-module.do"
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>> indexed = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>{});
#line 425 "/src/emitter-module.do"
    const auto& _iterable_42 = result->modules;
    for (const auto& module : *_iterable_42) {
#line 425 "/src/emitter-module.do"
        doof::map_set(indexed, module->path, module, "", 0);
    }
#line 426 "/src/emitter-module.do"
    return indexed;
}
#line 429 "/src/emitter-module.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> indexedGraphModule(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>& indexed, const std::string& path) {
#line 430 "/src/emitter-module.do"
    auto _binding_value_43 = doof::map_get(indexed, path, "", 0);
    if (doof::is_failure(_binding_value_43)) {
        const auto& module = _binding_value_43;
#line 430 "/src/emitter-module.do"
        return nullptr;
    }
    const auto module = doof::success_value(_binding_value_43);
#line 431 "/src/emitter-module.do"
    return module;
}
#line 434 "/src/emitter-module.do"
std::shared_ptr<doof::ordered_map<std::string, std::string>> indexReusableModuleFingerprints(const std::shared_ptr<std::vector<std::shared_ptr<ModuleEmissionCacheKey>>>& keys) {
#line 435 "/src/emitter-module.do"
    std::shared_ptr<doof::ordered_map<std::string, std::string>> indexed = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
#line 436 "/src/emitter-module.do"
    const auto& _iterable_45 = keys;
    for (const auto& key : *_iterable_45) {
#line 437 "/src/emitter-module.do"
        if (![&]() -> bool { auto _map_has_46 = indexed; return _map_has_46->find(key->modulePath) != _map_has_46->end(); }()) {
#line 437 "/src/emitter-module.do"
            doof::map_set(indexed, key->modulePath, key->fingerprint, "", 0);
        }
    }
#line 439 "/src/emitter-module.do"
    return indexed;
}
#line 442 "/src/emitter-module.do"
bool reusableModuleMatches(const std::shared_ptr<doof::ordered_map<std::string, std::string>>& indexed, const std::string& path, const std::string& fingerprint) {
#line 443 "/src/emitter-module.do"
    auto _binding_value_47 = doof::map_get(indexed, path, "", 0);
    if (doof::is_failure(_binding_value_47)) {
        const auto& cached = _binding_value_47;
#line 443 "/src/emitter-module.do"
        return false;
    }
    const auto cached = doof::success_value(_binding_value_47);
#line 444 "/src/emitter-module.do"
    return (cached == fingerprint);
}
#line 449 "/src/emitter-module.do"
std::string moduleInstantiationFingerprintInput(const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
#line 450 "/src/emitter-module.do"
    auto value = std::string("");
#line 451 "/src/emitter-module.do"
    const auto& _iterable_49 = instantiations->functions;
    for (const auto& item : *_iterable_49) {
#line 451 "/src/emitter-module.do"
        (value = ((value + std::string("\nfunction:")) + item->key));
    }
#line 452 "/src/emitter-module.do"
    const auto& _iterable_51 = instantiations->classes;
    for (const auto& item : *_iterable_51) {
#line 452 "/src/emitter-module.do"
        (value = ((value + std::string("\nclass:")) + item->key));
    }
#line 453 "/src/emitter-module.do"
    const auto& _iterable_53 = instantiations->methods;
    for (const auto& item : *_iterable_53) {
#line 453 "/src/emitter-module.do"
        (value = ((value + std::string("\nmethod:")) + item->key));
    }
#line 454 "/src/emitter-module.do"
    const auto& _iterable_55 = instantiations->interfaces;
    for (const auto& item : *_iterable_55) {
#line 455 "/src/emitter-module.do"
        (value = ((value + std::string("\ninterface:")) + item->key));
#line 456 "/src/emitter-module.do"
        const auto& _iterable_57 = item->implementations;
        for (const auto& implementation : *_iterable_57) {
#line 457 "/src/emitter-module.do"
            (value = ((((value + std::string(":")) + implementation->modulePath) + std::string(":")) + implementation->typeName));
        }
    }
#line 460 "/src/emitter-module.do"
    const auto& _iterable_59 = instantiations->nativeTemplateClassKeys;
    for (const auto& key : *_iterable_59) {
#line 460 "/src/emitter-module.do"
        (value = ((value + std::string("\nnative:")) + key));
    }
#line 461 "/src/emitter-module.do"
    const auto& _iterable_61 = instantiations->jsonSerializationKeys;
    for (const auto& key : *_iterable_61) {
#line 461 "/src/emitter-module.do"
        (value = ((value + std::string("\njson-serialize:")) + key));
    }
#line 462 "/src/emitter-module.do"
    const auto& _iterable_63 = instantiations->jsonDeserializationKeys;
    for (const auto& key : *_iterable_63) {
#line 462 "/src/emitter-module.do"
        (value = ((value + std::string("\njson-deserialize:")) + key));
    }
#line 463 "/src/emitter-module.do"
    return value;
}
#line 466 "/src/emitter-module.do"
std::string moduleEmissionFingerprint(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>& moduleIndex, const std::string& path, const std::string& entry, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::string>>& initializationOrder, const std::string& configurationFingerprint, const std::string& instantiationFingerprintInput) {
#line 477 "/src/emitter-module.do"
    auto value = (((((((std::string("doof-module-emission-2\n") + configurationFingerprint) + std::string("\n")) + path) + std::string("\n")) + entryMode) + std::string("\n")) + doof::to_string(coverage));
#line 479 "/src/emitter-module.do"
    std::shared_ptr<doof::ordered_set<std::string>> reachable = std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{});
#line 480 "/src/emitter-module.do"
    collectModuleDependencyClosure(moduleIndex, path, reachable);
#line 481 "/src/emitter-module.do"
    const auto& _iterable_65 = result->modules;
    for (const auto& candidate : *_iterable_65) {
#line 482 "/src/emitter-module.do"
        if (reachable->count(candidate->path) > 0) {
#line 483 "/src/emitter-module.do"
            (value = ((((value + std::string("\nsource:")) + candidate->path) + std::string(":")) + candidate->sourceHash));
        }
    }
#line 489 "/src/emitter-module.do"
    (value = (value + instantiationFingerprintInput));
#line 490 "/src/emitter-module.do"
    if (path == entry) {
#line 491 "/src/emitter-module.do"
        const auto& _iterable_67 = initializationOrder;
        for (const auto& initialized : *_iterable_67) {
#line 491 "/src/emitter-module.do"
            (value = ((value + std::string("\ninitialize:")) + initialized));
        }
    }
#line 493 "/src/emitter-module.do"
    return ::std_::crypto::index::sha256HexString(value);
}
#line 496 "/src/emitter-module.do"
void collectModuleDependencyClosure(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>& moduleIndex, const std::string& path, const std::shared_ptr<doof::ordered_set<std::string>>& reachable) {
#line 497 "/src/emitter-module.do"
    if (reachable->count(path) > 0) {
#line 497 "/src/emitter-module.do"
        return;
    }
#line 498 "/src/emitter-module.do"
    reachable->insert(path);
#line 499 "/src/emitter-module.do"
    const auto module = indexedGraphModule(moduleIndex, path);
#line 500 "/src/emitter-module.do"
    if (doof::is_null(module)) {
#line 500 "/src/emitter-module.do"
        return;
    }
#line 501 "/src/emitter-module.do"
    const auto& _iterable_69 = module->imports;
    for (const auto& imported : *_iterable_69) {
#line 501 "/src/emitter-module.do"
        collectModuleDependencyClosure(moduleIndex, imported->sourceModule, reachable);
    }
#line 502 "/src/emitter-module.do"
    const auto& _iterable_71 = module->namespaceImports;
    for (const auto& imported : *_iterable_71) {
#line 502 "/src/emitter-module.do"
        collectModuleDependencyClosure(moduleIndex, imported->sourceModule, reachable);
    }
#line 503 "/src/emitter-module.do"
    const auto& _iterable_73 = module->reExports;
    for (const auto& reExport : *_iterable_73) {
#line 503 "/src/emitter-module.do"
        collectModuleDependencyClosure(moduleIndex, reExport, reachable);
    }
}
#line 506 "/src/emitter-module.do"
bool isCoverageEligible(const std::string& modulePath) {
#line 507 "/src/emitter-module.do"
    return ((!doof::string_endsWith(modulePath, std::string(".test.do")) && !doof::string_contains(modulePath, std::string("/.doof-tests/"))) && !doof::string_startsWith(modulePath, std::string("/std/")));
}
#line 512 "/src/emitter-module.do"
std::shared_ptr<std::vector<int32_t>> sortedCoverageLines(const std::shared_ptr<std::vector<int32_t>>& lines) {
#line 513 "/src/emitter-module.do"
    std::shared_ptr<std::vector<int32_t>> result = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 514 "/src/emitter-module.do"
    auto last = -1;
#line 515 "/src/emitter-module.do"
    for (int32_t count = 0; count < static_cast<int32_t>((lines)->size()); ++count) {
#line 516 "/src/emitter-module.do"
        std::optional<int32_t> candidate = std::nullopt;
#line 517 "/src/emitter-module.do"
        const auto& _iterable_76 = lines;
        for (const auto& line : *_iterable_76) {
#line 518 "/src/emitter-module.do"
            if ((line > last) && (doof::is_null(candidate) || (line < candidate.value()))) {
#line 518 "/src/emitter-module.do"
                (candidate = line);
            }
        }
#line 520 "/src/emitter-module.do"
        if (!doof::is_null(candidate)) {
#line 520 "/src/emitter-module.do"
            result->push_back(candidate.value());
#line 520 "/src/emitter-module.do"
            (last = candidate.value());
        }
    }
#line 522 "/src/emitter-module.do"
    return result;
}
#line 525 "/src/emitter-module.do"
void configureInstantiationRegistry(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& plan) {
#line 526 "/src/emitter-module.do"
    const auto& _iterable_78 = plan->nativeTemplateClassKeys;
    for (const auto& key : *_iterable_78) {
#line 526 "/src/emitter-module.do"
        context->nativeTemplateClassKeys->push_back(key);
    }
#line 527 "/src/emitter-module.do"
    const auto& _iterable_80 = plan->functions;
    for (const auto& instantiation : *_iterable_80) {
#line 528 "/src/emitter-module.do"
        context->concreteFunctionKeys->push_back(instantiation->key);
#line 529 "/src/emitter-module.do"
        context->concreteFunctionNames->push_back(instantiation->emittedName);
    }
#line 531 "/src/emitter-module.do"
    const auto& _iterable_82 = plan->classes;
    for (const auto& instantiation : *_iterable_82) {
#line 532 "/src/emitter-module.do"
        context->concreteClassKeys->push_back(instantiation->key);
#line 533 "/src/emitter-module.do"
        context->concreteClassNames->push_back(instantiation->emittedName);
    }
#line 535 "/src/emitter-module.do"
    const auto& _iterable_84 = plan->methods;
    for (const auto& instantiation : *_iterable_84) {
#line 536 "/src/emitter-module.do"
        context->concreteMethodKeys->push_back(instantiation->key);
#line 537 "/src/emitter-module.do"
        context->concreteMethodNames->push_back(instantiation->emittedName);
    }
#line 539 "/src/emitter-module.do"
    const auto& _iterable_86 = plan->interfaces;
    for (const auto& instantiation : *_iterable_86) {
#line 540 "/src/emitter-module.do"
        context->concreteInterfaceKeys->push_back(instantiation->key);
#line 541 "/src/emitter-module.do"
        context->concreteInterfaceNames->push_back(instantiation->emittedName);
    }
#line 543 "/src/emitter-module.do"
    const auto& _iterable_88 = plan->jsonSerializationKeys;
    for (const auto& key : *_iterable_88) {
#line 543 "/src/emitter-module.do"
        context->jsonSerializationKeys->push_back(key);
    }
#line 544 "/src/emitter-module.do"
    const auto& _iterable_90 = plan->jsonDeserializationKeys;
    for (const auto& key : *_iterable_90) {
#line 544 "/src/emitter-module.do"
        context->jsonDeserializationKeys->push_back(key);
    }
}
#line 547 "/src/emitter-module.do"
void configureJsonDemandRegistry(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::string>>& serializationKeys, const std::shared_ptr<std::vector<std::string>>& deserializationKeys) {
#line 548 "/src/emitter-module.do"
    const auto& _iterable_92 = serializationKeys;
    for (const auto& key : *_iterable_92) {
#line 548 "/src/emitter-module.do"
        context->jsonSerializationKeys->push_back(key);
    }
#line 549 "/src/emitter-module.do"
    const auto& _iterable_94 = deserializationKeys;
    for (const auto& key : *_iterable_94) {
#line 549 "/src/emitter-module.do"
        context->jsonDeserializationKeys->push_back(key);
    }
}
#line 552 "/src/emitter-module.do"
void addConcreteHeaderDeclarations(const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<std::vector<std::string>>& interfaceKeys) {
#line 559 "/src/emitter-module.do"
    const auto& _iterable_96 = instantiations->interfaces;
    for (const auto& interface_ : *_iterable_96) {
#line 560 "/src/emitter-module.do"
        if (!containsString(interfaceKeys, interface_->key)) {
#line 560 "/src/emitter-module.do"
            continue;
        }
#line 561 "/src/emitter-module.do"
        if ((interface_->name != std::string("Stream")) && (interface_->modulePath != context->modulePath)) {
#line 561 "/src/emitter-module.do"
            continue;
        }
#line 562 "/src/emitter-module.do"
        if ((interface_->name != std::string("Stream")) && !programDeclares(program, interface_->name)) {
#line 562 "/src/emitter-module.do"
            continue;
        }
#line 563 "/src/emitter-module.do"
        auto alternatives = std::string("");
#line 564 "/src/emitter-module.do"
        const auto& _iterable_98 = interface_->implementations;
        for (const auto& implementation : *_iterable_98) {
#line 565 "/src/emitter-module.do"
            if (alternatives != std::string("")) {
#line 565 "/src/emitter-module.do"
                (alternatives = (alternatives + std::string(", ")));
            }
#line 566 "/src/emitter-module.do"
            auto typeName = implementation->typeName;
#line 567 "/src/emitter-module.do"
            if (implementation->modulePath != context->modulePath) {
#line 568 "/src/emitter-module.do"
                const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(implementation->modulePath);
#line 569 "/src/emitter-module.do"
                plan->typeOnlyForwardDeclarations->push_back(((((std::string("namespace ") + namespace_) + std::string(" { struct ")) + implementation->typeName) + std::string("; }\n")));
#line 570 "/src/emitter-module.do"
                (typeName = (((std::string("::") + namespace_) + std::string("::")) + typeName));
            }
#line 572 "/src/emitter-module.do"
            (alternatives = (((alternatives + std::string("std::shared_ptr<")) + typeName) + std::string(">")));
        }
#line 574 "/src/emitter-module.do"
        if (alternatives == std::string("")) {
#line 574 "/src/emitter-module.do"
            (alternatives = std::string("std::monostate"));
        }
#line 575 "/src/emitter-module.do"
        plan->interfaceAliases->push_back(((((std::string("using ") + interface_->emittedName) + std::string(" = std::variant<")) + alternatives) + std::string(">;\n")));
    }
#line 577 "/src/emitter-module.do"
    const auto& _iterable_100 = instantiations->classes;
    for (const auto& instantiation : *_iterable_100) {
#line 578 "/src/emitter-module.do"
        if (instantiation->modulePath != context->modulePath) {
#line 578 "/src/emitter-module.do"
            continue;
        }
#line 579 "/src/emitter-module.do"
        if (!programDeclares(program, instantiation->declaration->name)) {
#line 579 "/src/emitter-module.do"
            continue;
        }
#line 580 "/src/emitter-module.do"
        const auto& _iterable_102 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_102) {
#line 580 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
#line 581 "/src/emitter-module.do"
        plan->classForwardDeclarations->push_back(((std::string("struct ") + instantiation->emittedName) + std::string(";\n")));
#line 582 "/src/emitter-module.do"
        (context->substitution = instantiation->substitution);
#line 583 "/src/emitter-module.do"
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{});
#line 584 "/src/emitter-module.do"
        const auto& _iterable_104 = instantiations->methods;
        for (const auto& method : *_iterable_104) {
#line 584 "/src/emitter-module.do"
            if (method->ownerKey == instantiation->key) {
#line 584 "/src/emitter-module.do"
                methods->push_back(method);
            }
        }
#line 585 "/src/emitter-module.do"
        plan->classDefinitions->push_back(::app_src_emitter_decl_::emitClassDeclaration(instantiation->declaration, context, instantiation->emittedName, methods));
#line 586 "/src/emitter-module.do"
        clearInstantiation(context);
    }
#line 588 "/src/emitter-module.do"
    const auto& _iterable_106 = instantiations->functions;
    for (const auto& instantiation : *_iterable_106) {
#line 589 "/src/emitter-module.do"
        if (instantiation->modulePath != context->modulePath) {
#line 589 "/src/emitter-module.do"
            continue;
        }
#line 590 "/src/emitter-module.do"
        if (!programDeclares(program, instantiation->declaration->name)) {
#line 590 "/src/emitter-module.do"
            continue;
        }
#line 591 "/src/emitter-module.do"
        const auto& _iterable_108 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_108) {
#line 591 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
#line 592 "/src/emitter-module.do"
        (context->substitution = instantiation->substitution);
#line 593 "/src/emitter-module.do"
        const auto signature = ::app_src_emitter_decl_::emitFunctionDeclaration(instantiation->declaration, instantiation->emittedName, context->modulePath, context);
#line 594 "/src/emitter-module.do"
        if (instantiation->declaration->native_) {
#line 594 "/src/emitter-module.do"
            plan->nativeAdapterSignatures->push_back(signature);
        } else {
#line 595 "/src/emitter-module.do"
            plan->functionSignatures->push_back(signature);
        }
#line 596 "/src/emitter-module.do"
        clearInstantiation(context);
    }
}
#line 600 "/src/emitter-module.do"
bool programDeclares(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& name) {
#line 601 "/src/emitter-module.do"
    const auto& _iterable_110 = program->statements;
    for (const auto& statement : *_iterable_110) {
#line 601 "/src/emitter-module.do"
        if (headerDeclarationName(statement) == name) {
#line 601 "/src/emitter-module.do"
            return true;
        }
    }
#line 602 "/src/emitter-module.do"
    return false;
}
#line 605 "/src/emitter-module.do"
std::string headerDeclarationName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 606 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 607 "/src/emitter-module.do"
            return headerDeclarationName(export_->declaration);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 608 "/src/emitter-module.do"
            return class_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 609 "/src/emitter-module.do"
            return interface_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 610 "/src/emitter-module.do"
            return fn->name;
    }
    else {
#line 611 "/src/emitter-module.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 613 "/src/emitter-module.do"
    return std::string("");
}
#line 616 "/src/emitter-module.do"
void addConcreteTypeForwardDeclarations(const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 617 "/src/emitter-module.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 619 "/src/emitter-module.do"
            if ((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) {
#line 620 "/src/emitter-module.do"
                const auto declaration = ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(class_->symbol->module)) + std::string(" { struct ")) + class_->name) + std::string("; }\n"));
#line 621 "/src/emitter-module.do"
                if (!containsString(plan->typeOnlyForwardDeclarations, declaration)) {
#line 621 "/src/emitter-module.do"
                    plan->typeOnlyForwardDeclarations->push_back(declaration);
                }
            }
#line 623 "/src/emitter-module.do"
            const auto& _iterable_112 = class_->typeArgs;
            for (const auto& argument : *_iterable_112) {
#line 623 "/src/emitter-module.do"
                addConcreteTypeForwardDeclarations(plan, context, argument);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 625 "/src/emitter-module.do"
            const auto& _iterable_114 = interface_->typeArgs;
            for (const auto& argument : *_iterable_114) {
#line 625 "/src/emitter-module.do"
                addConcreteTypeForwardDeclarations(plan, context, argument);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 626 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 627 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, map->keyType);
#line 627 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, map->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 628 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 629 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 630 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, result_->valueType);
#line 630 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, result_->errorType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 631 "/src/emitter-module.do"
            const auto& _iterable_116 = tuple->elements;
            for (const auto& element : *_iterable_116) {
#line 631 "/src/emitter-module.do"
                addConcreteTypeForwardDeclarations(plan, context, element);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 632 "/src/emitter-module.do"
            const auto& _iterable_118 = union_->types;
            for (const auto& member : *_iterable_118) {
#line 632 "/src/emitter-module.do"
                addConcreteTypeForwardDeclarations(plan, context, member);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 633 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 635 "/src/emitter-module.do"
            const auto& _iterable_120 = function_->params;
            for (const auto& parameter : *_iterable_120) {
#line 635 "/src/emitter-module.do"
                addConcreteTypeForwardDeclarations(plan, context, parameter->type_);
            }
#line 636 "/src/emitter-module.do"
            addConcreteTypeForwardDeclarations(plan, context, function_->returnType);
    }
    else {
    }
    }
}
#line 642 "/src/emitter-module.do"
std::string emitConcreteFunctions(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
#line 643 "/src/emitter-module.do"
    auto result = std::string("");
#line 644 "/src/emitter-module.do"
    const auto& _iterable_122 = instantiations->functions;
    for (const auto& instantiation : *_iterable_122) {
#line 645 "/src/emitter-module.do"
        if (instantiation->modulePath != context->modulePath) {
#line 645 "/src/emitter-module.do"
            continue;
        }
#line 646 "/src/emitter-module.do"
        (context->substitution = instantiation->substitution);
#line 647 "/src/emitter-module.do"
        if (instantiation->declaration->native_) {
#line 647 "/src/emitter-module.do"
            (result = (result + ::app_src_emitter_decl_::emitNativeFunctionAdapterDefinition(instantiation->declaration, instantiation->emittedName, context)));
        } else {
#line 648 "/src/emitter-module.do"
            (result = (result + ::app_src_emitter_decl_::emitFunctionDefinition(instantiation->declaration, context, instantiation->emittedName)));
        }
#line 649 "/src/emitter-module.do"
        clearInstantiation(context);
    }
#line 651 "/src/emitter-module.do"
    return result;
}
#line 654 "/src/emitter-module.do"
void withInstantiation(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 655 "/src/emitter-module.do"
    (context->substitution = std::make_shared<::app_src_semantic_::TypeSubstitution>(names, arguments));
}
#line 658 "/src/emitter-module.do"
void clearInstantiation(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 659 "/src/emitter-module.do"
    (context->substitution = nullptr);
}
#line 662 "/src/emitter-module.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> emitModuleSurfaces(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 663 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> surfaces = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{});
#line 664 "/src/emitter-module.do"
    const auto& _iterable_124 = result->modules;
    for (const auto& module : *_iterable_124) {
#line 665 "/src/emitter-module.do"
        std::shared_ptr<std::vector<std::string>> genericTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 666 "/src/emitter-module.do"
        std::shared_ptr<std::vector<std::string>> genericFunctions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 667 "/src/emitter-module.do"
        const auto& _iterable_126 = module->program->statements;
        for (const auto& statement : *_iterable_126) {
#line 667 "/src/emitter-module.do"
            collectGenericSurfaceSymbols(statement, genericTypes, genericFunctions);
        }
#line 668 "/src/emitter-module.do"
        surfaces->push_back(std::make_shared<::app_src_emitter_context_::EmitModuleSurface>(module->path, module->exports, module->imports, genericTypes, genericFunctions));
    }
#line 670 "/src/emitter-module.do"
    return surfaces;
}
#line 673 "/src/emitter-module.do"
void collectGenericSurfaceSymbols(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<std::vector<std::string>>& typeNames, const std::shared_ptr<std::vector<std::string>>& functionNames) {
#line 674 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 675 "/src/emitter-module.do"
            if (static_cast<int32_t>((class_->typeParams)->size()) > 0) {
#line 675 "/src/emitter-module.do"
                typeNames->push_back(class_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 676 "/src/emitter-module.do"
            if (static_cast<int32_t>((interface_->typeParams)->size()) > 0) {
#line 676 "/src/emitter-module.do"
                typeNames->push_back(interface_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 677 "/src/emitter-module.do"
            if (static_cast<int32_t>((alias->typeParams)->size()) > 0) {
#line 677 "/src/emitter-module.do"
                typeNames->push_back(alias->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 678 "/src/emitter-module.do"
            if (static_cast<int32_t>((function_->typeParams)->size()) > 0) {
#line 678 "/src/emitter-module.do"
                functionNames->push_back(function_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 679 "/src/emitter-module.do"
            collectGenericSurfaceSymbols(export_->declaration, typeNames, functionNames);
    }
    else {
    }
    }
}
#line 684 "/src/emitter-module.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 685 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
#line 686 "/src/emitter-module.do"
    const auto& _iterable_128 = result->modules;
    for (const auto& module : *_iterable_128) {
#line 686 "/src/emitter-module.do"
        programs->push_back(module->program);
    }
#line 687 "/src/emitter-module.do"
    return programs;
}
#line 690 "/src/emitter-module.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> surfaceImports(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>& surfaces, const std::string& path) {
#line 691 "/src/emitter-module.do"
    const auto& _iterable_130 = surfaces;
    for (const auto& surface : *_iterable_130) {
#line 691 "/src/emitter-module.do"
        if (surface->path == path) {
#line 691 "/src/emitter-module.do"
            return surface->imports;
        }
    }
#line 692 "/src/emitter-module.do"
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
}
#line 695 "/src/emitter-module.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> infoNamespaceImports(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 696 "/src/emitter-module.do"
    const auto& _iterable_132 = result->modules;
    for (const auto& module : *_iterable_132) {
#line 696 "/src/emitter-module.do"
        if (module->path == path) {
#line 696 "/src/emitter-module.do"
            return module->namespaceImports;
        }
    }
#line 697 "/src/emitter-module.do"
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{});
}
#line 700 "/src/emitter-module.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> infoImports(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 701 "/src/emitter-module.do"
    const auto& _iterable_134 = result->modules;
    for (const auto& module : *_iterable_134) {
#line 701 "/src/emitter-module.do"
        if (module->path == path) {
#line 701 "/src/emitter-module.do"
            return module->imports;
        }
    }
#line 702 "/src/emitter-module.do"
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
}
#line 705 "/src/emitter-module.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findGraphModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 706 "/src/emitter-module.do"
    const auto& _iterable_136 = result->modules;
    for (const auto& module : *_iterable_136) {
#line 706 "/src/emitter-module.do"
        if (module->path == path) {
#line 706 "/src/emitter-module.do"
            return module;
        }
    }
#line 707 "/src/emitter-module.do"
    return nullptr;
}
#line 710 "/src/emitter-module.do"
std::shared_ptr<std::vector<std::string>> planModuleInitializationOrder(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::string& entryMode) {
#line 715 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::string>> order = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 716 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::string>> visiting = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 717 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 718 "/src/emitter-module.do"
    visitInitializationModule(result, entry, entry, entryMode, visiting, visited, order);
#line 719 "/src/emitter-module.do"
    return order;
}
#line 722 "/src/emitter-module.do"
void visitInitializationModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path, const std::string& entry, const std::string& entryMode, const std::shared_ptr<std::vector<std::string>>& visiting, const std::shared_ptr<std::vector<std::string>>& visited, const std::shared_ptr<std::vector<std::string>>& order) {
#line 731 "/src/emitter-module.do"
    if (containsString(visited, path) || containsString(visiting, path)) {
#line 731 "/src/emitter-module.do"
        return;
    }
#line 732 "/src/emitter-module.do"
    const auto info = findGraphModule(result, path);
#line 733 "/src/emitter-module.do"
    if (doof::is_null(info)) {
#line 733 "/src/emitter-module.do"
        return;
    }
#line 734 "/src/emitter-module.do"
    visiting->push_back(path);
#line 735 "/src/emitter-module.do"
    const auto& _iterable_138 = info->imports;
    for (const auto& imported : *_iterable_138) {
#line 736 "/src/emitter-module.do"
        if (!imported->typeOnly) {
#line 736 "/src/emitter-module.do"
            visitInitializationModule(result, imported->sourceModule, entry, entryMode, visiting, visited, order);
        }
    }
#line 738 "/src/emitter-module.do"
    const auto& _iterable_140 = info->namespaceImports;
    for (const auto& imported : *_iterable_140) {
#line 739 "/src/emitter-module.do"
        if (!imported->typeOnly) {
#line 739 "/src/emitter-module.do"
            visitInitializationModule(result, imported->sourceModule, entry, entryMode, visiting, visited, order);
        }
    }
#line 741 "/src/emitter-module.do"
    const auto& _iterable_142 = info->reExports;
    for (const auto& reExport : *_iterable_142) {
#line 741 "/src/emitter-module.do"
        visitInitializationModule(result, reExport, entry, entryMode, visiting, visited, order);
    }
#line 742 "/src/emitter-module.do"
    auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(visiting); if (doof::is_failure(_try_value)) doof::panic_at("src/emitter-module", 742, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 743 "/src/emitter-module.do"
    visited->push_back(path);
#line 744 "/src/emitter-module.do"
    const auto scriptEntry = (((path == entry) && ((entryMode == std::string("executable")) || (entryMode == std::string("ios-app")))) && hasScriptStatements(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{info->program})));
#line 746 "/src/emitter-module.do"
    if (!scriptEntry && moduleHasDeferredInitialization(info->program)) {
#line 746 "/src/emitter-module.do"
        order->push_back(path);
    }
}
#line 749 "/src/emitter-module.do"
std::shared_ptr<std::vector<std::string>> moduleInitializationNamespaces(const std::shared_ptr<std::vector<std::string>>& paths) {
#line 750 "/src/emitter-module.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 751 "/src/emitter-module.do"
    const auto& _iterable_144 = paths;
    for (const auto& path : *_iterable_144) {
#line 751 "/src/emitter-module.do"
        result->push_back(::app_src_emitter_names_::moduleNamespace(path));
    }
#line 752 "/src/emitter-module.do"
    return result;
}
#line 755 "/src/emitter-module.do"
std::shared_ptr<ModuleEmission> emitModule(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& moduleName, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
#line 756 "/src/emitter-module.do"
    if (doof::is_null(instantiations)) {
#line 756 "/src/emitter-module.do"
        return std::make_shared<CxxModuleEmitter>(moduleName, std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), nullptr, -1, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<::app_src_json_semantics_::JsonEligibilityCache>(std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}), std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}))->emit(program, std::string("executable"));
    }
#line 757 "/src/emitter-module.do"
    return std::make_shared<CxxModuleEmitter>(moduleName, std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), nullptr, -1, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<::app_src_json_semantics_::JsonEligibilityCache>(std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}), std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{})), instantiations->jsonSerializationKeys, instantiations->jsonDeserializationKeys, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}))->emit(program, std::string("executable"));
}
#line 764 "/src/emitter-module.do"
std::string emitSourceStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 765 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 767 "/src/emitter-module.do"
            if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
#line 767 "/src/emitter-module.do"
                return std::string("");
            }
#line 768 "/src/emitter-module.do"
            return ::app_src_emitter_decl_::emitFunctionDefinition(fn, context, ((fn->name == std::string("main")) ? std::string("doof_main") : fn->name));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 771 "/src/emitter-module.do"
            if (class_->native_) {
#line 771 "/src/emitter-module.do"
                return std::string("");
            }
#line 772 "/src/emitter-module.do"
            auto result = (std::string("\n") + ::app_src_emitter_decl_::emitStaticClassFieldDefinitions(class_, context));
#line 773 "/src/emitter-module.do"
            if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
#line 774 "/src/emitter-module.do"
                const auto& _iterable_146 = class_->methods;
                for (const auto& method : *_iterable_146) {
#line 774 "/src/emitter-module.do"
                    (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(class_, method, context)));
                }
            }
#line 776 "/src/emitter-module.do"
            (result = (result + ::app_src_emitter_json_::emitGeneratedJsonMethods(class_, context)));
#line 777 "/src/emitter-module.do"
            (result = (result + ::app_src_emitter_metadata_::emitMetadataDefinition(class_, context)));
#line 778 "/src/emitter-module.do"
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 780 "/src/emitter-module.do"
            return ::app_src_emitter_json_::emitInterfaceJsonDefinition(interface_, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 781 "/src/emitter-module.do"
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(const_), const_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 782 "/src/emitter-module.do"
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(readonly_), readonly_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 783 "/src/emitter-module.do"
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(binding), binding->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 784 "/src/emitter-module.do"
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(let_), let_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 785 "/src/emitter-module.do"
            return emitSourceStatement(export_->declaration, context);
    }
    else {
#line 786 "/src/emitter-module.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 788 "/src/emitter-module.do"
    return std::string("");
}
#line 791 "/src/emitter-module.do"
std::string emitModuleStorage(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 796 "/src/emitter-module.do"
    const auto initializer = (isCxxConstantInitializer(value) ? ::app_src_emitter_expr_::emitExpression(value, context, moduleValueType(declaration)) : std::string(""));
#line 797 "/src/emitter-module.do"
    return ::app_src_emitter_decl_::emitModuleValueStorage(declaration, context, initializer);
}
#line 800 "/src/emitter-module.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> moduleValueType(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration) {
#line 803 "/src/emitter-module.do"
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 804 "/src/emitter-module.do"
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 805 "/src/emitter-module.do"
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 806 "/src/emitter-module.do"
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 807 "/src/emitter-module.do"
            return value->resolvedType;
    }
    }
    doof::unreachable();
#line 809 "/src/emitter-module.do"
    return std::monostate{};
}
#line 812 "/src/emitter-module.do"
bool isCxxConstantInitializer(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value) {
#line 813 "/src/emitter-module.do"
    {
        auto _case_subject = value;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
#line 814 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
#line 815 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
#line 816 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
#line 817 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
#line 818 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
#line 819 "/src/emitter-module.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 820 "/src/emitter-module.do"
            return (dot->resolvedShorthandOwnerKind == std::string("enum"));
    }
    else {
#line 821 "/src/emitter-module.do"
            return false;
    }
    }
    doof::unreachable();
#line 823 "/src/emitter-module.do"
    return false;
}
#line 826 "/src/emitter-module.do"
bool moduleHasDeferredInitialization(const std::shared_ptr<::app_src_ast_::Program>& program) {
#line 827 "/src/emitter-module.do"
    const auto& _iterable_148 = program->statements;
    for (const auto& statement : *_iterable_148) {
#line 828 "/src/emitter-module.do"
        if (statementHasDeferredInitialization(statement)) {
#line 828 "/src/emitter-module.do"
            return true;
        }
    }
#line 830 "/src/emitter-module.do"
    return false;
}
#line 833 "/src/emitter-module.do"
bool statementHasDeferredInitialization(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 834 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 835 "/src/emitter-module.do"
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 836 "/src/emitter-module.do"
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 837 "/src/emitter-module.do"
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 838 "/src/emitter-module.do"
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 840 "/src/emitter-module.do"
            if (class_->native_ || (static_cast<int32_t>((class_->typeParams)->size()) > 0)) {
#line 840 "/src/emitter-module.do"
                return false;
            }
#line 841 "/src/emitter-module.do"
            const auto& _iterable_150 = class_->fields;
            for (const auto& field : *_iterable_150) {
#line 841 "/src/emitter-module.do"
                if (field->static_ && (!doof::is_null(field->defaultValue))) {
#line 841 "/src/emitter-module.do"
                    return true;
                }
            }
#line 842 "/src/emitter-module.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 844 "/src/emitter-module.do"
            return statementHasDeferredInitialization(export_->declaration);
    }
    else {
#line 845 "/src/emitter-module.do"
            return false;
    }
    }
    doof::unreachable();
#line 847 "/src/emitter-module.do"
    return false;
}
#line 850 "/src/emitter-module.do"
std::string emitModuleInitializer(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, bool includeValues) {
#line 851 "/src/emitter-module.do"
    auto assignments = std::string("");
#line 852 "/src/emitter-module.do"
    if (includeValues) {
#line 853 "/src/emitter-module.do"
        const auto& _iterable_152 = programs;
        for (const auto& program : *_iterable_152) {
#line 854 "/src/emitter-module.do"
            const auto& _iterable_154 = program->statements;
            for (const auto& statement : *_iterable_154) {
#line 855 "/src/emitter-module.do"
                (assignments = (assignments + emitModuleInitializerStatement(statement, context)));
            }
        }
    }
#line 859 "/src/emitter-module.do"
    if (assignments == std::string("")) {
#line 859 "/src/emitter-module.do"
        return std::string("");
    }
#line 860 "/src/emitter-module.do"
    return ((std::string("\nvoid __doof_initialize_module() {\n") + assignments) + std::string("}\n"));
}
#line 863 "/src/emitter-module.do"
std::string emitModuleInitializerStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 864 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 865 "/src/emitter-module.do"
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 866 "/src/emitter-module.do"
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 867 "/src/emitter-module.do"
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 868 "/src/emitter-module.do"
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 870 "/src/emitter-module.do"
            auto result = std::string("");
#line 871 "/src/emitter-module.do"
            if (class_->native_ || (static_cast<int32_t>((class_->typeParams)->size()) > 0)) {
#line 871 "/src/emitter-module.do"
                return result;
            }
#line 872 "/src/emitter-module.do"
            const auto& _iterable_156 = class_->fields;
            for (const auto& field : *_iterable_156) {
#line 873 "/src/emitter-module.do"
                if (!field->static_ || doof::is_null(field->defaultValue)) {
#line 873 "/src/emitter-module.do"
                    continue;
                }
#line 874 "/src/emitter-module.do"
                const auto& _iterable_158 = field->names;
                for (const auto& name : *_iterable_158) {
#line 875 "/src/emitter-module.do"
                    (result = (((((((result + std::string("        ")) + class_->name) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType)) + std::string(";\n")));
                }
            }
#line 879 "/src/emitter-module.do"
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 881 "/src/emitter-module.do"
            return emitModuleInitializerStatement(export_->declaration, context);
    }
    else {
#line 882 "/src/emitter-module.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 884 "/src/emitter-module.do"
    return std::string("");
}
#line 887 "/src/emitter-module.do"
std::string emitModuleValueAssignment(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 892 "/src/emitter-module.do"
    if (isCxxConstantInitializer(value)) {
#line 892 "/src/emitter-module.do"
        return std::string("");
    }
#line 893 "/src/emitter-module.do"
    const auto name = scriptDeclarationName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration));
#line 894 "/src/emitter-module.do"
    if ((name == std::string("")) || (name == std::string("_"))) {
#line 894 "/src/emitter-module.do"
        return std::string("");
    }
#line 895 "/src/emitter-module.do"
    return ((((std::string("        ") + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, moduleValueType(declaration))) + std::string(";\n"));
}
#line 898 "/src/emitter-module.do"
std::string emitGraphInitializationCall(const std::shared_ptr<std::vector<std::string>>& namespaces) {
#line 899 "/src/emitter-module.do"
    auto result = std::string("");
#line 900 "/src/emitter-module.do"
    const auto& _iterable_160 = namespaces;
    for (const auto& namespace_ : *_iterable_160) {
#line 900 "/src/emitter-module.do"
        (result = (((result + std::string("::")) + namespace_) + std::string("::__doof_initialize_module(); ")));
    }
#line 901 "/src/emitter-module.do"
    return result;
}
#line 904 "/src/emitter-module.do"
std::string emitNativeClassMethods(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 905 "/src/emitter-module.do"
    auto result = std::string("");
#line 906 "/src/emitter-module.do"
    const auto& _iterable_162 = programs;
    for (const auto& program : *_iterable_162) {
#line 907 "/src/emitter-module.do"
        const auto& _iterable_164 = program->statements;
        for (const auto& statement : *_iterable_164) {
#line 908 "/src/emitter-module.do"
            (result = (result + emitNativeClassMethodsForStatement(statement, context)));
        }
    }
#line 911 "/src/emitter-module.do"
    return result;
}
#line 914 "/src/emitter-module.do"
std::string emitNativeClassMethodsForStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 915 "/src/emitter-module.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 917 "/src/emitter-module.do"
            if (!class_->native_) {
#line 917 "/src/emitter-module.do"
                return std::string("");
            }
#line 918 "/src/emitter-module.do"
            auto result = std::string("");
#line 919 "/src/emitter-module.do"
            const auto& _iterable_166 = class_->methods;
            for (const auto& method : *_iterable_166) {
#line 920 "/src/emitter-module.do"
                if (!method->bodyless) {
#line 920 "/src/emitter-module.do"
                    (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(class_, method, context)));
                }
            }
#line 922 "/src/emitter-module.do"
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 924 "/src/emitter-module.do"
            return emitNativeClassMethodsForStatement(export_->declaration, context);
    }
    else {
#line 925 "/src/emitter-module.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 927 "/src/emitter-module.do"
    return std::string("");
}
#line 931 "/src/emitter-module.do"
std::string emitMainWrapper(const std::string& moduleName, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, bool hasScript, const std::string& initializationCall) {
#line 932 "/src/emitter-module.do"
    if (!hasScript) {
#line 933 "/src/emitter-module.do"
        const auto signature = (plan->mainAcceptsArgs ? std::string("int main(int argc, char** argv)") : std::string("int main()"));
#line 934 "/src/emitter-module.do"
        const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string(""));
#line 935 "/src/emitter-module.do"
        const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
#line 936 "/src/emitter-module.do"
        const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
#line 937 "/src/emitter-module.do"
        const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
#line 938 "/src/emitter-module.do"
        const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
#line 939 "/src/emitter-module.do"
        return (((((((((std::string("\n") + signature) + std::string(" { try { ")) + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
    }
#line 941 "/src/emitter-module.do"
    const auto needsArguments = (plan->mainAcceptsArgs || hasScript);
#line 942 "/src/emitter-module.do"
    const auto signature = (needsArguments ? std::string("int main(int argc, char** argv)") : std::string("int main()"));
#line 943 "/src/emitter-module.do"
    const auto argumentSetup = (needsArguments ? std::string("std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); ") : std::string(""));
#line 944 "/src/emitter-module.do"
    const auto scriptCall = (hasScript ? (moduleName + std::string("::__doof_run_script(arguments); ")) : std::string(""));
#line 945 "/src/emitter-module.do"
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(arguments)")) : (moduleName + std::string("::doof_main()")));
#line 946 "/src/emitter-module.do"
    const auto success = (!plan->hasMain ? (scriptCall + std::string("return 0;")) : (plan->mainReturnsInt ? (((scriptCall + std::string("return ")) + call) + std::string(";")) : ((scriptCall + call) + std::string("; return 0;"))));
#line 947 "/src/emitter-module.do"
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
#line 948 "/src/emitter-module.do"
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
#line 949 "/src/emitter-module.do"
    return (((((((((std::string("\n") + signature) + std::string(" { try { ")) + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
}
#line 953 "/src/emitter-module.do"
std::string emitAppEntryWrapper(const std::string& moduleName, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, bool hasScript, const std::string& initializationCall) {
#line 954 "/src/emitter-module.do"
    if (!hasScript) {
#line 955 "/src/emitter-module.do"
        const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string("(void)argc; (void)argv; "));
#line 956 "/src/emitter-module.do"
        const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
#line 957 "/src/emitter-module.do"
        const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
#line 958 "/src/emitter-module.do"
        const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
#line 959 "/src/emitter-module.do"
        const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
#line 960 "/src/emitter-module.do"
        return (((((((std::string("\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { ") + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
    }
#line 962 "/src/emitter-module.do"
    const auto needsArguments = (plan->mainAcceptsArgs || hasScript);
#line 963 "/src/emitter-module.do"
    const auto argumentSetup = (needsArguments ? std::string("std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); ") : std::string("(void)argc; (void)argv; "));
#line 964 "/src/emitter-module.do"
    const auto scriptCall = (hasScript ? (moduleName + std::string("::__doof_run_script(arguments); ")) : std::string(""));
#line 965 "/src/emitter-module.do"
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(arguments)")) : (moduleName + std::string("::doof_main()")));
#line 966 "/src/emitter-module.do"
    const auto success = (!plan->hasMain ? (scriptCall + std::string("return 0;")) : (plan->mainReturnsInt ? (((scriptCall + std::string("return ")) + call) + std::string(";")) : ((scriptCall + call) + std::string("; return 0;"))));
#line 967 "/src/emitter-module.do"
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
#line 968 "/src/emitter-module.do"
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
#line 969 "/src/emitter-module.do"
    return (((((((std::string("\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { ") + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
}
#line 1 "<doof-generated>"
}
