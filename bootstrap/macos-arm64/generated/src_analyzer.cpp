#include "src_analyzer.hpp"

namespace app_src_analyzer_ {
using namespace ::app_src_parser_;
using namespace ::app_src_resolver_;
using namespace ::app_src_semantic_;
using namespace ::app_src_ast_;
using namespace ::std_::crypto::index;



std::shared_ptr<std::vector<std::string>> BUILTIN_TYPES;

#line 66 "/src/analyzer.do"
std::shared_ptr<AnalysisResult> ModuleAnalyzer::analyze(const std::string& entry) {
#line 67 "/src/analyzer.do"
    (this->modules = std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}));
#line 68 "/src/analyzer.do"
    (this->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
#line 69 "/src/analyzer.do"
    (this->inProgress = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 70 "/src/analyzer.do"
    (this->resolvedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 71 "/src/analyzer.do"
    (this->resolver->loadedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 72 "/src/analyzer.do"
    (this->resolver->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
#line 73 "/src/analyzer.do"
    (this->resolver->failedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 74 "/src/analyzer.do"
    const auto entryPath = (doof::string_endsWith(entry, std::string(".do")) ? entry : (entry + std::string(".do")));
#line 75 "/src/analyzer.do"
    parseReachableModules(entryPath);
#line 76 "/src/analyzer.do"
    orderModules(entryPath);
#line 77 "/src/analyzer.do"
    const auto ignored = resolveModule(entryPath);
#line 81 "/src/analyzer.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> orderedDiagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
#line 82 "/src/analyzer.do"
    const auto& _iterable_2 = this->resolver->diagnostics;
    for (const auto& diagnostic : *_iterable_2) {
#line 82 "/src/analyzer.do"
        orderedDiagnostics->push_back(diagnostic);
    }
#line 83 "/src/analyzer.do"
    const auto& _iterable_4 = this->diagnostics;
    for (const auto& diagnostic : *_iterable_4) {
#line 83 "/src/analyzer.do"
        orderedDiagnostics->push_back(diagnostic);
    }
#line 84 "/src/analyzer.do"
    return std::make_shared<AnalysisResult>(modules, orderedDiagnostics);
}
#line 87 "/src/analyzer.do"
void ModuleAnalyzer::queueModuleParse(const std::string& path, const std::optional<std::string>& inheritedMockRootPath, const std::shared_ptr<std::vector<std::string>>& scheduled, const std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>>& pending) {
#line 93 "/src/analyzer.do"
    if (contains(scheduled, path)) {
#line 93 "/src/analyzer.do"
        return;
    }
#line 94 "/src/analyzer.do"
    scheduled->push_back(path);
#line 95 "/src/analyzer.do"
    const auto source = this->resolver->find(path);
#line 96 "/src/analyzer.do"
    if (doof::is_null(source)) {
#line 97 "/src/analyzer.do"
        if (!this->resolver->failed(path)) {
#line 98 "/src/analyzer.do"
            this->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (std::string("Module not found: ") + path), emptySemanticSpan(), path, std::string("")));
        }
#line 105 "/src/analyzer.do"
        return;
    }
#line 108 "/src/analyzer.do"
    const auto sourceText = source->source;
#line 109 "/src/analyzer.do"
    const auto physicalPath = ((source->physicalPath == std::string("")) ? source->path : source->physicalPath);
#line 110 "/src/analyzer.do"
    const auto modulePath = path;
#line 111 "/src/analyzer.do"
    const auto mockRootPath = inheritedMockRootPath;
#line 112 "/src/analyzer.do"
    pending->push_back(doof::submit_async<std::shared_ptr<ModuleParseResult>>([sourceText, modulePath, physicalPath, mockRootPath]() -> std::shared_ptr<ModuleParseResult> {
#line 113 "/src/analyzer.do"
    const auto parser = std::make_shared<::app_src_parser_::Parser>(sourceText, std::make_shared<std::vector<::app_src_lexer_::Token>>(std::vector<::app_src_lexer_::Token>{}), 0, false, false, std::string(""), 0, 0, 0);
#line 114 "/src/analyzer.do"
    const auto parsed = [&]() -> doof::Result<std::shared_ptr<::app_src_ast_::Program>, std::string> { try { return doof::Success<std::shared_ptr<::app_src_ast_::Program>>{doof::callback<std::shared_ptr<::app_src_ast_::Program>()>([parser]() -> std::shared_ptr<::app_src_ast_::Program> { return parser->parse(); }).call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }();
#line 115 "/src/analyzer.do"
    auto _binding_value_5 = parsed;
    if (doof::is_failure(_binding_value_5)) {
        const auto failure = doof::failure_error(_binding_value_5);
#line 116 "/src/analyzer.do"
        if (parser->errorMessage == std::string("")) {
#line 116 "/src/analyzer.do"
            doof::panic(failure);
        }
#line 117 "/src/analyzer.do"
        return std::make_shared<ModuleParseResult>(modulePath, physicalPath, sourceText, mockRootPath, nullptr, parser->errorMessage, parser->errorLine, parser->errorColumn, parser->errorOffset);
    }
    const auto program = doof::success_value(_binding_value_5);
#line 123 "/src/analyzer.do"
    return std::make_shared<ModuleParseResult>(modulePath, physicalPath, sourceText, mockRootPath, program, std::string(""), 0, 0, 0);
}));
}
#line 127 "/src/analyzer.do"
void ModuleAnalyzer::parseReachableModules(const std::string& entryPath) {
#line 128 "/src/analyzer.do"
    std::shared_ptr<std::vector<std::string>> scheduled = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 129 "/src/analyzer.do"
    std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>> pending = std::make_shared<std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>>(std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>{});
#line 130 "/src/analyzer.do"
    queueModuleParse(entryPath, std::nullopt, scheduled, pending);
#line 131 "/src/analyzer.do"
    while (static_cast<int32_t>((pending)->size()) > 0) {
#line 132 "/src/analyzer.do"
        auto _binding_value_6 = doof::promise_take_first_completed(pending);
        if (doof::is_failure(_binding_value_6)) {
            const auto failure = doof::failure_error(_binding_value_6);
#line 132 "/src/analyzer.do"
            doof::panic((std::string("Parser worker failed: ") + failure));
        }
        const auto completed = doof::success_value(_binding_value_6);
#line 133 "/src/analyzer.do"
        if (doof::is_null(completed->program)) {
#line 134 "/src/analyzer.do"
            auto location = ::app_src_semantic_::SemanticLocation{completed->errorLine, completed->errorColumn, completed->errorOffset};
#line 135 "/src/analyzer.do"
            this->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), completed->errorMessage, ::app_src_semantic_::SemanticSpan{location, location}, completed->path, std::string("")));
#line 141 "/src/analyzer.do"
            continue;
        }
#line 143 "/src/analyzer.do"
        const auto program = doof::unwrap_optional(completed->program);
#line 144 "/src/analyzer.do"
        const auto mockImportDirectives = collectMockImportDirectives(program);
#line 145 "/src/analyzer.do"
        auto mockRootPath = completed->inheritedMockRootPath;
#line 146 "/src/analyzer.do"
        if ((doof::is_null(mockRootPath) && (static_cast<int32_t>((mockImportDirectives)->size()) > 0)) && doof::string_endsWith(completed->path, std::string(".test.do"))) {
#line 147 "/src/analyzer.do"
            (mockRootPath = completed->path);
        }
#line 149 "/src/analyzer.do"
        const auto info = std::make_shared<ModuleInfo>(completed->path, completed->physicalPath, ::std_::crypto::index::sha256HexString(completed->source), program, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), mockImportDirectives, mockRootPath, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
#line 157 "/src/analyzer.do"
        this->modules->push_back(info);
#line 158 "/src/analyzer.do"
        validateMockImportDirectives(info, completed->inheritedMockRootPath);
#line 159 "/src/analyzer.do"
        collectSymbols(info);
#line 160 "/src/analyzer.do"
        const auto& _iterable_8 = program->statements;
        for (const auto& statement : *_iterable_8) {
#line 161 "/src/analyzer.do"
            {
                auto _case_subject = statement;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
                    const auto& import_ = std::get<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject);
#line 163 "/src/analyzer.do"
                    const auto sourcePath = resolveImportPath(info, import_->source);
#line 164 "/src/analyzer.do"
                    queueModuleParse(sourcePath, info->mockRootPath, scheduled, pending);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                    const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
#line 167 "/src/analyzer.do"
                    if (!doof::is_null(list->source)) {
#line 168 "/src/analyzer.do"
                        const auto sourcePath = resolveImportPath(info, doof::unwrap_optional(list->source));
#line 169 "/src/analyzer.do"
                        queueModuleParse(sourcePath, info->mockRootPath, scheduled, pending);
                    }
            }
            else {
            }
            }
        }
    }
}
#line 178 "/src/analyzer.do"
void ModuleAnalyzer::orderModules(const std::string& entryPath) {
#line 179 "/src/analyzer.do"
    std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> ordered = std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{});
#line 180 "/src/analyzer.do"
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 181 "/src/analyzer.do"
    appendModuleOrder(entryPath, ordered, visited);
#line 182 "/src/analyzer.do"
    (this->modules = ordered);
}
#line 185 "/src/analyzer.do"
void ModuleAnalyzer::appendModuleOrder(const std::string& path, const std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>>& ordered, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 186 "/src/analyzer.do"
    if (contains(visited, path)) {
#line 186 "/src/analyzer.do"
        return;
    }
#line 187 "/src/analyzer.do"
    visited->push_back(path);
#line 188 "/src/analyzer.do"
    const auto info = findModule(path);
#line 189 "/src/analyzer.do"
    if (doof::is_null(info)) {
#line 189 "/src/analyzer.do"
        return;
    }
#line 190 "/src/analyzer.do"
    ordered->push_back(doof::unwrap_optional(info));
#line 191 "/src/analyzer.do"
    const auto& _iterable_10 = info->program->statements;
    for (const auto& statement : *_iterable_10) {
#line 192 "/src/analyzer.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
                const auto& import_ = std::get<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject);
#line 193 "/src/analyzer.do"
                appendModuleOrder(resolveImportPath(doof::unwrap_optional(info), import_->source), ordered, visited);
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
#line 194 "/src/analyzer.do"
                if (!doof::is_null(list->source)) {
#line 194 "/src/analyzer.do"
                    appendModuleOrder(resolveImportPath(doof::unwrap_optional(info), doof::unwrap_optional(list->source)), ordered, visited);
                }
        }
        else {
        }
        }
    }
}
#line 200 "/src/analyzer.do"
std::shared_ptr<ModuleInfo> ModuleAnalyzer::resolveModule(const std::string& path) {
#line 201 "/src/analyzer.do"
    const auto existing = findModule(path);
#line 202 "/src/analyzer.do"
    if (doof::is_null(existing)) {
#line 202 "/src/analyzer.do"
        return nullptr;
    }
#line 203 "/src/analyzer.do"
    if (contains(this->resolvedPaths, path)) {
#line 203 "/src/analyzer.do"
        return existing;
    }
#line 204 "/src/analyzer.do"
    if (contains(this->inProgress, path)) {
#line 204 "/src/analyzer.do"
        return existing;
    }
#line 205 "/src/analyzer.do"
    this->inProgress->push_back(path);
#line 206 "/src/analyzer.do"
    const auto info = doof::unwrap_optional(existing);
#line 207 "/src/analyzer.do"
    resolveImports(info);
#line 208 "/src/analyzer.do"
    resolveExportLists(info);
#line 209 "/src/analyzer.do"
    resolveNamedTypes(info);
#line 210 "/src/analyzer.do"
    const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(this->inProgress); if (doof::is_failure(_try_value)) doof::panic_at("src/analyzer", 210, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 211 "/src/analyzer.do"
    this->resolvedPaths->push_back(path);
#line 212 "/src/analyzer.do"
    const auto& _iterable_12 = info->diagnostics;
    for (const auto& item : *_iterable_12) {
#line 212 "/src/analyzer.do"
        this->diagnostics->push_back(item);
    }
#line 213 "/src/analyzer.do"
    return info;
}
#line 216 "/src/analyzer.do"
void ModuleAnalyzer::collectSymbols(const std::shared_ptr<ModuleInfo>& info) {
#line 217 "/src/analyzer.do"
    const auto& _iterable_14 = info->program->statements;
    for (const auto& statement : *_iterable_14) {
#line 218 "/src/analyzer.do"
        const auto symbol = symbolFor(statement, info->path);
#line 219 "/src/analyzer.do"
        if (doof::is_null(symbol)) {
#line 219 "/src/analyzer.do"
            continue;
        }
#line 220 "/src/analyzer.do"
        decorateDeclarationSymbol(statement, doof::unwrap_optional(symbol));
#line 221 "/src/analyzer.do"
        if (!doof::is_null(findSymbol(info, symbol->name))) {
#line 222 "/src/analyzer.do"
            addError(info, ((std::string("Duplicate module binding '") + symbol->name) + std::string("'")), std::visit([](auto&& _obj) { return _obj->span; }, statement));
#line 223 "/src/analyzer.do"
            continue;
        }
#line 225 "/src/analyzer.do"
        info->symbols->push_back(doof::unwrap_optional(symbol));
#line 226 "/src/analyzer.do"
        if (symbol->exported) {
#line 226 "/src/analyzer.do"
            info->exports->push_back(doof::unwrap_optional(symbol));
        }
    }
}
#line 230 "/src/analyzer.do"
void ModuleAnalyzer::decorateDeclarationSymbol(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 231 "/src/analyzer.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 232 "/src/analyzer.do"
            (class_->resolvedSymbol = symbol);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 233 "/src/analyzer.do"
            (interface_->resolvedSymbol = symbol);
    }
    else {
    }
    }
}
#line 238 "/src/analyzer.do"
std::shared_ptr<::app_src_semantic_::Symbol> ModuleAnalyzer::symbolFor(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::string& module) {
#line 239 "/src/analyzer.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 241 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>((value->struct_ ? std::string("struct") : std::string("class")), value->name, module, value->exported, std::string(""), value->native_, value->nativeHeader, value->nativeCppName, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), value->typeParams, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 248 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("interface"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 251 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("function"), value->name, module, value->exported, std::string(""), value->native_, value->nativeHeader, value->nativeCppName, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 257 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("type-alias"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 260 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("const"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 263 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("readonly"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 266 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("const"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 269 "/src/analyzer.do"
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("enum"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else {
#line 271 "/src/analyzer.do"
            return nullptr;
    }
    }
    doof::unreachable();
#line 273 "/src/analyzer.do"
    return nullptr;
}
#line 277 "/src/analyzer.do"
std::shared_ptr<::app_src_semantic_::Symbol> ModuleAnalyzer::exportedSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& exportedName) {
#line 278 "/src/analyzer.do"
    return std::make_shared<::app_src_semantic_::Symbol>(symbol->kind, exportedName, symbol->module, true, ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName), symbol->native_, symbol->nativeHeader, symbol->nativeCppName, symbol->implementations, symbol->implementedInterfaceTypes, symbol->typeParams, symbol->streamElementTypes);
}
#line 294 "/src/analyzer.do"
void ModuleAnalyzer::resolveImports(const std::shared_ptr<ModuleInfo>& info) {
#line 295 "/src/analyzer.do"
    const auto& _iterable_16 = info->program->statements;
    for (const auto& statement : *_iterable_16) {
#line 296 "/src/analyzer.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
                const auto& import_ = std::get<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject);
#line 298 "/src/analyzer.do"
                const auto sourcePath = resolveImportPath(info, import_->source);
#line 299 "/src/analyzer.do"
                if (doof::string_endsWith(info->path, std::string(".test.do")) && doof::string_endsWith(sourcePath, std::string(".test.do"))) {
#line 300 "/src/analyzer.do"
                    addError(info, ((((std::string("Test file \"") + info->path) + std::string("\" cannot import another test file \"")) + sourcePath) + std::string("\"")), import_->span);
#line 301 "/src/analyzer.do"
                    continue;
                }
#line 303 "/src/analyzer.do"
                const auto source = resolveModule(sourcePath);
#line 304 "/src/analyzer.do"
                const auto& _iterable_18 = import_->specifiers;
                for (const auto& specifier : *_iterable_18) {
#line 305 "/src/analyzer.do"
                    {
                        auto _case_subject = specifier;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedImport>>(_case_subject)) {
                            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedImport>>(_case_subject);
#line 307 "/src/analyzer.do"
                            std::shared_ptr<::app_src_semantic_::Symbol> imported = nullptr;
#line 308 "/src/analyzer.do"
                            if (!doof::is_null(source)) {
#line 308 "/src/analyzer.do"
                                (imported = findExport(doof::unwrap_optional(source), named->name));
                            }
#line 311 "/src/analyzer.do"
                            if ((!doof::is_null(source)) && doof::is_null(imported)) {
#line 312 "/src/analyzer.do"
                                addError(info, ((((std::string("Module '") + import_->source) + std::string("' does not export '")) + named->name) + std::string("'")), named->span);
                            }
#line 314 "/src/analyzer.do"
                            const auto localName = (doof::is_null(named->alias) ? named->name : doof::unwrap_optional(named->alias));
#line 315 "/src/analyzer.do"
                            if (hasModuleBinding(info, localName)) {
#line 316 "/src/analyzer.do"
                                addError(info, ((std::string("Duplicate module binding '") + localName) + std::string("'")), named->span);
#line 317 "/src/analyzer.do"
                                continue;
                            }
#line 319 "/src/analyzer.do"
                            if (doof::is_null(imported)) {
#line 320 "/src/analyzer.do"
                                info->imports->push_back(std::make_shared<::app_src_semantic_::ImportBinding>(localName, named->name, sourcePath, import_->typeOnly, nullptr));
                            } else {
#line 325 "/src/analyzer.do"
                                info->imports->push_back(std::make_shared<::app_src_semantic_::ImportBinding>(localName, named->name, sourcePath, import_->typeOnly, imported));
                            }
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamespaceImport>>(_case_subject)) {
                            const auto& namespace_ = std::get<std::shared_ptr<::app_src_ast_::NamespaceImport>>(_case_subject);
#line 332 "/src/analyzer.do"
                            if (hasModuleBinding(info, namespace_->alias)) {
#line 333 "/src/analyzer.do"
                                addError(info, ((std::string("Duplicate module binding '") + namespace_->alias) + std::string("'")), namespace_->span);
#line 334 "/src/analyzer.do"
                                continue;
                            }
#line 336 "/src/analyzer.do"
                            info->namespaceImports->push_back(std::make_shared<::app_src_semantic_::NamespaceBinding>(namespace_->alias, sourcePath, import_->typeOnly));
                    }
                    }
                }
        }
        else {
        }
        }
    }
}
#line 350 "/src/analyzer.do"
void ModuleAnalyzer::resolveExportLists(const std::shared_ptr<ModuleInfo>& info) {
#line 351 "/src/analyzer.do"
    const auto& _iterable_20 = info->program->statements;
    for (const auto& statement : *_iterable_20) {
#line 352 "/src/analyzer.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
#line 354 "/src/analyzer.do"
                if (!doof::is_null(list->source)) {
#line 355 "/src/analyzer.do"
                    const auto sourcePath = resolveImportPath(info, doof::unwrap_optional(list->source));
#line 356 "/src/analyzer.do"
                    const auto source = resolveModule(sourcePath);
#line 357 "/src/analyzer.do"
                    info->reExports->push_back(sourcePath);
#line 358 "/src/analyzer.do"
                    const auto& _iterable_22 = list->specifiers;
                    for (const auto& specifier : *_iterable_22) {
#line 359 "/src/analyzer.do"
                        std::shared_ptr<::app_src_semantic_::Symbol> exported = nullptr;
#line 360 "/src/analyzer.do"
                        if (!doof::is_null(source)) {
#line 360 "/src/analyzer.do"
                            (exported = findExport(doof::unwrap_optional(source), specifier->name));
                        }
#line 361 "/src/analyzer.do"
                        if ((!doof::is_null(source)) && doof::is_null(exported)) {
#line 362 "/src/analyzer.do"
                            addError(info, ((((std::string("Module '") + doof::unwrap_optional(list->source)) + std::string("' does not export '")) + specifier->name) + std::string("'")), specifier->span);
                        } else {
#line 364 "/src/analyzer.do"
                            if (!doof::is_null(exported)) {
#line 365 "/src/analyzer.do"
                                const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
#line 366 "/src/analyzer.do"
                                info->exports->push_back(exportedSymbol(doof::unwrap_optional(exported), exportedName));
                            }
                        }
                    }
#line 370 "/src/analyzer.do"
                    continue;
                }
#line 372 "/src/analyzer.do"
                const auto& _iterable_24 = list->specifiers;
                for (const auto& specifier : *_iterable_24) {
#line 373 "/src/analyzer.do"
                    const auto local = findSymbol(info, specifier->name);
#line 374 "/src/analyzer.do"
                    if (!doof::is_null(local)) {
#line 375 "/src/analyzer.do"
                        const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
#line 376 "/src/analyzer.do"
                        if (doof::is_null(findExport(info, exportedName))) {
#line 377 "/src/analyzer.do"
                            info->exports->push_back(exportedSymbol(doof::unwrap_optional(local), exportedName));
                        }
                    } else {
#line 380 "/src/analyzer.do"
                        addError(info, ((std::string("Cannot export unknown symbol '") + specifier->name) + std::string("'")), specifier->span);
                    }
                }
        }
        else {
        }
        }
    }
}
#line 389 "/src/analyzer.do"
void ModuleAnalyzer::resolveNamedTypes(const std::shared_ptr<ModuleInfo>& info) {
#line 390 "/src/analyzer.do"
    const auto& _iterable_26 = info->program->statements;
    for (const auto& statement : *_iterable_26) {
#line 390 "/src/analyzer.do"
        visitStatementTypes(statement, info);
    }
}
#line 393 "/src/analyzer.do"
void ModuleAnalyzer::visitStatementTypes(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<ModuleInfo>& info) {
#line 394 "/src/analyzer.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 395 "/src/analyzer.do"
            visitFunctionTypes(fn, info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 397 "/src/analyzer.do"
            visitTypeParameterConstraints(class_->typeParamConstraints, info, class_->typeParams);
#line 398 "/src/analyzer.do"
            const auto& _iterable_28 = class_->implements_;
            for (const auto& annotation : *_iterable_28) {
#line 398 "/src/analyzer.do"
                visitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(annotation), info, class_->typeParams);
            }
#line 399 "/src/analyzer.do"
            const auto& _iterable_30 = class_->fields;
            for (const auto& field : *_iterable_30) {
#line 399 "/src/analyzer.do"
                if (!doof::is_null(field->type_)) {
#line 399 "/src/analyzer.do"
                    visitType(doof::unwrap_optional(field->type_), info, class_->typeParams);
                }
            }
#line 400 "/src/analyzer.do"
            const auto& _iterable_32 = class_->methods;
            for (const auto& method : *_iterable_32) {
#line 400 "/src/analyzer.do"
                visitFunctionTypes(method, info, class_->typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 403 "/src/analyzer.do"
            visitTypeParameterConstraints(interface_->typeParamConstraints, info, interface_->typeParams);
#line 404 "/src/analyzer.do"
            const auto& _iterable_34 = interface_->fields;
            for (const auto& field : *_iterable_34) {
#line 404 "/src/analyzer.do"
                visitType(field->type_, info, interface_->typeParams);
            }
#line 405 "/src/analyzer.do"
            const auto& _iterable_36 = interface_->methods;
            for (const auto& method : *_iterable_36) {
#line 405 "/src/analyzer.do"
                visitFunctionTypes(method, info, interface_->typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 407 "/src/analyzer.do"
            visitTypeParameterConstraints(alias->typeParamConstraints, info, alias->typeParams);
#line 407 "/src/analyzer.do"
            visitType(alias->type_, info, alias->typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 408 "/src/analyzer.do"
            if (!doof::is_null(const_->type_)) {
#line 408 "/src/analyzer.do"
                visitType(doof::unwrap_optional(const_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 409 "/src/analyzer.do"
            if (!doof::is_null(readonly_->type_)) {
#line 409 "/src/analyzer.do"
                visitType(doof::unwrap_optional(readonly_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 410 "/src/analyzer.do"
            if (!doof::is_null(binding->type_)) {
#line 410 "/src/analyzer.do"
                visitType(doof::unwrap_optional(binding->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 411 "/src/analyzer.do"
            if (!doof::is_null(let_->type_)) {
#line 411 "/src/analyzer.do"
                visitType(doof::unwrap_optional(let_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else {
    }
    }
}
#line 416 "/src/analyzer.do"
void ModuleAnalyzer::visitFunctionTypes(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams) {
#line 417 "/src/analyzer.do"
    std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 418 "/src/analyzer.do"
    const auto& _iterable_38 = ownerTypeParams;
    for (const auto& parameter : *_iterable_38) {
#line 418 "/src/analyzer.do"
        typeParams->push_back(parameter);
    }
#line 419 "/src/analyzer.do"
    const auto& _iterable_40 = fn->typeParams;
    for (const auto& parameter : *_iterable_40) {
#line 419 "/src/analyzer.do"
        typeParams->push_back(parameter);
    }
#line 420 "/src/analyzer.do"
    visitTypeParameterConstraints(fn->typeParamConstraints, info, typeParams);
#line 421 "/src/analyzer.do"
    const auto& _iterable_42 = fn->params;
    for (const auto& parameter : *_iterable_42) {
#line 421 "/src/analyzer.do"
        if (!doof::is_null(parameter->type_)) {
#line 421 "/src/analyzer.do"
            visitType(doof::unwrap_optional(parameter->type_), info, typeParams);
        }
    }
#line 422 "/src/analyzer.do"
    if (!doof::is_null(fn->returnType)) {
#line 422 "/src/analyzer.do"
        visitType(doof::unwrap_optional(fn->returnType), info, typeParams);
    }
}
#line 425 "/src/analyzer.do"
void ModuleAnalyzer::visitTypeParameterConstraints(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& constraints, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& typeParams) {
#line 426 "/src/analyzer.do"
    const auto& _iterable_44 = constraints;
    for (const auto& constraint : *_iterable_44) {
#line 426 "/src/analyzer.do"
        if (!doof::is_null(constraint->type_)) {
#line 426 "/src/analyzer.do"
            visitType(doof::unwrap_optional(constraint->type_), info, typeParams);
        }
    }
}
#line 429 "/src/analyzer.do"
void ModuleAnalyzer::visitType(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& typeParams) {
#line 430 "/src/analyzer.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 432 "/src/analyzer.do"
            if (!isBuiltin(named->name) && !containsTypeParam(typeParams, named->name)) {
#line 433 "/src/analyzer.do"
                std::shared_ptr<::app_src_semantic_::Symbol> symbol = findSymbol(info, named->name);
#line 434 "/src/analyzer.do"
                if (doof::is_null(symbol)) {
#line 435 "/src/analyzer.do"
                    const auto& _iterable_46 = info->imports;
                    for (const auto& imported : *_iterable_46) {
#line 436 "/src/analyzer.do"
                        if (imported->localName == named->name) {
#line 436 "/src/analyzer.do"
                            (symbol = imported->symbol);
#line 436 "/src/analyzer.do"
                            break;
                        }
                    }
                }
#line 439 "/src/analyzer.do"
                if (doof::is_null(symbol)) {
#line 439 "/src/analyzer.do"
                    (symbol = findExport(info, named->name));
                }
#line 440 "/src/analyzer.do"
                if (doof::is_null(symbol)) {
#line 441 "/src/analyzer.do"
                    addError(info, ((std::string("Unknown type '") + named->name) + std::string("'")), named->span);
                } else if (!isTypeSymbol(doof::unwrap_optional(symbol))) {
#line 443 "/src/analyzer.do"
                    addError(info, ((std::string("Symbol '") + named->name) + std::string("' is not a type")), named->span);
#line 444 "/src/analyzer.do"
                    (symbol = nullptr);
                }
#line 446 "/src/analyzer.do"
                (named->resolvedSymbol = symbol);
            }
#line 448 "/src/analyzer.do"
            const auto& _iterable_48 = named->typeArgs;
            for (const auto& argument : *_iterable_48) {
#line 448 "/src/analyzer.do"
                visitType(argument, info, typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 450 "/src/analyzer.do"
            visitType(array->elementType, info, typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
#line 451 "/src/analyzer.do"
            const auto& _iterable_50 = union_->types;
            for (const auto& member : *_iterable_50) {
#line 451 "/src/analyzer.do"
                visitType(member, info, typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
#line 453 "/src/analyzer.do"
            const auto& _iterable_52 = function_->params;
            for (const auto& parameter : *_iterable_52) {
#line 453 "/src/analyzer.do"
                visitType(parameter->type_, info, typeParams);
            }
#line 454 "/src/analyzer.do"
            visitType(function_->returnType, info, typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
#line 456 "/src/analyzer.do"
            visitType(weak_->type_, info, typeParams);
    }
    }
}
#line 460 "/src/analyzer.do"
bool ModuleAnalyzer::containsTypeParam(const std::shared_ptr<std::vector<std::string>>& typeParams, const std::string& name) {
#line 461 "/src/analyzer.do"
    const auto& _iterable_54 = typeParams;
    for (const auto& typeParam : *_iterable_54) {
#line 461 "/src/analyzer.do"
        if (typeParam == name) {
#line 461 "/src/analyzer.do"
            return true;
        }
    }
#line 462 "/src/analyzer.do"
    return false;
}
#line 465 "/src/analyzer.do"
std::shared_ptr<ModuleInfo> ModuleAnalyzer::findModule(const std::string& path) {
#line 466 "/src/analyzer.do"
    const auto& _iterable_56 = this->modules;
    for (const auto& module : *_iterable_56) {
#line 466 "/src/analyzer.do"
        if (module->path == path) {
#line 466 "/src/analyzer.do"
            return module;
        }
    }
#line 467 "/src/analyzer.do"
    return nullptr;
}
#line 472 "/src/analyzer.do"
void ModuleAnalyzer::keepStatementTypes(const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<::app_src_ast_::ExportDeclaration>& export_, const std::shared_ptr<::app_src_ast_::ImportDeclaration>& import_, const std::shared_ptr<::app_src_ast_::MockImportDirective>& mockImport, const std::shared_ptr<::app_src_ast_::IfStatement>& if_, const std::shared_ptr<::app_src_ast_::CaseStatement>& case_, const std::shared_ptr<::app_src_ast_::WhileStatement>& while_, const std::shared_ptr<::app_src_ast_::ForStatement>& for_, const std::shared_ptr<::app_src_ast_::ForOfStatement>& forOf, const std::shared_ptr<::app_src_ast_::WithStatement>& with_, const std::shared_ptr<::app_src_ast_::ReturnStatement>& return_, const std::shared_ptr<::app_src_ast_::YieldStatement>& yield_, const std::shared_ptr<::app_src_ast_::BreakStatement>& break_, const std::shared_ptr<::app_src_ast_::ContinueStatement>& continue_, const std::shared_ptr<::app_src_ast_::ExpressionStatement>& expression, const std::shared_ptr<::app_src_ast_::DestructuringStatement>& destructuring) {
}
#line 492 "/src/analyzer.do"
std::string ModuleAnalyzer::resolveImportPath(const std::shared_ptr<ModuleInfo>& info, const std::string& specifier) {
#line 493 "/src/analyzer.do"
    if (doof::is_null(info->mockRootPath)) {
#line 493 "/src/analyzer.do"
        return this->resolver->resolve(info->path, specifier);
    }
#line 494 "/src/analyzer.do"
    const auto root = findModule(doof::unwrap_optional(info->mockRootPath));
#line 495 "/src/analyzer.do"
    if (doof::is_null(root) || (static_cast<int32_t>((root->mockImportDirectives)->size()) == 0)) {
#line 495 "/src/analyzer.do"
        return this->resolver->resolve(info->path, specifier);
    }
#line 496 "/src/analyzer.do"
    const auto replacement = findMockReplacement(doof::unwrap_optional(root), info->path, specifier);
#line 497 "/src/analyzer.do"
    if (doof::is_null(replacement)) {
#line 497 "/src/analyzer.do"
        return this->resolver->resolve(info->path, specifier);
    }
#line 498 "/src/analyzer.do"
    return this->resolver->resolve(doof::unwrap_optional(info->mockRootPath), replacement.value());
}
#line 502 "/src/analyzer.do"
std::optional<std::string> ModuleAnalyzer::findMockReplacement(const std::shared_ptr<ModuleInfo>& root, const std::string& sourcePath, const std::string& dependencySpecifier) {
#line 507 "/src/analyzer.do"
    const auto& _iterable_58 = root->mockImportDirectives;
    for (const auto& directive : *_iterable_58) {
#line 508 "/src/analyzer.do"
        if (this->resolver->resolve(root->path, directive->sourcePattern) != sourcePath) {
#line 508 "/src/analyzer.do"
            continue;
        }
#line 509 "/src/analyzer.do"
        const auto& _iterable_60 = directive->mappings;
        for (const auto& mapping : *_iterable_60) {
#line 510 "/src/analyzer.do"
            if (mapping->dependency == dependencySpecifier) {
#line 510 "/src/analyzer.do"
                return mapping->replacement;
            }
        }
    }
#line 513 "/src/analyzer.do"
    return std::nullopt;
}
#line 516 "/src/analyzer.do"
void ModuleAnalyzer::validateMockImportDirectives(const std::shared_ptr<ModuleInfo>& info, const std::optional<std::string>& inheritedMockRootPath) {
#line 517 "/src/analyzer.do"
    if (static_cast<int32_t>((info->mockImportDirectives)->size()) == 0) {
#line 517 "/src/analyzer.do"
        return;
    }
#line 518 "/src/analyzer.do"
    if (!doof::string_endsWith(info->path, std::string(".test.do"))) {
#line 519 "/src/analyzer.do"
        const auto& _iterable_62 = info->mockImportDirectives;
        for (const auto& directive : *_iterable_62) {
#line 520 "/src/analyzer.do"
            addError(info, std::string("mock import directives are only valid in .test.do files"), directive->span);
        }
    }
#line 523 "/src/analyzer.do"
    if ((!doof::is_null(inheritedMockRootPath)) && (inheritedMockRootPath != info->path)) {
#line 524 "/src/analyzer.do"
        const auto& _iterable_64 = info->mockImportDirectives;
        for (const auto& directive : *_iterable_64) {
#line 525 "/src/analyzer.do"
            addError(info, std::string("mock import directives are only valid in the root test file"), directive->span);
        }
    }
#line 529 "/src/analyzer.do"
    auto sawOrdinaryStatement = false;
#line 530 "/src/analyzer.do"
    const auto& _iterable_66 = info->program->statements;
    for (const auto& statement : *_iterable_66) {
#line 531 "/src/analyzer.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                const auto& directive = std::get<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject);
#line 533 "/src/analyzer.do"
                if (sawOrdinaryStatement) {
#line 534 "/src/analyzer.do"
                    addError(info, std::string("mock import directives must appear at the top of the file before other statements"), directive->span);
                }
        }
        else {
#line 537 "/src/analyzer.do"
                (sawOrdinaryStatement = true);
        }
        }
    }
#line 541 "/src/analyzer.do"
    const auto& _iterable_68 = info->mockImportDirectives;
    for (const auto& directive : *_iterable_68) {
#line 542 "/src/analyzer.do"
        const auto& _iterable_70 = directive->mappings;
        for (const auto& mapping : *_iterable_70) {
#line 543 "/src/analyzer.do"
            if (mapping->dependency == mapping->replacement) {
#line 544 "/src/analyzer.do"
                addError(info, ((std::string("mock import cannot substitute \"") + mapping->dependency) + std::string("\" with itself")), mapping->span);
            }
        }
    }
}
#line 551 "/src/analyzer.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> collectMockImportDirectives(const std::shared_ptr<::app_src_ast_::Program>& program) {
#line 552 "/src/analyzer.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> directives = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>>(std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>{});
#line 553 "/src/analyzer.do"
    const auto& _iterable_72 = program->statements;
    for (const auto& statement : *_iterable_72) {
#line 554 "/src/analyzer.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                const auto& directive = std::get<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject);
#line 555 "/src/analyzer.do"
                directives->push_back(directive);
        }
        else {
        }
        }
    }
#line 559 "/src/analyzer.do"
    return directives;
}
#line 562 "/src/analyzer.do"
std::shared_ptr<ModuleAnalyzer> createAnalyzer(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources) {
#line 563 "/src/analyzer.do"
    return std::make_shared<ModuleAnalyzer>(std::make_shared<::app_src_resolver_::ModuleResolver>(sources, ::app_src_resolver_::noSourceLoader, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{})), std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
#line 566 "/src/analyzer.do"
std::shared_ptr<ModuleAnalyzer> createAnalyzerWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader) {
#line 567 "/src/analyzer.do"
    return std::make_shared<ModuleAnalyzer>(std::make_shared<::app_src_resolver_::ModuleResolver>(sources, loader, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{})), std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
#line 570 "/src/analyzer.do"
std::shared_ptr<::app_src_semantic_::Symbol> findSymbol(const std::shared_ptr<ModuleInfo>& info, const std::string& name) {
#line 571 "/src/analyzer.do"
    const auto& _iterable_74 = info->symbols;
    for (const auto& symbol : *_iterable_74) {
#line 571 "/src/analyzer.do"
        if (symbol->name == name) {
#line 571 "/src/analyzer.do"
            return symbol;
        }
    }
#line 572 "/src/analyzer.do"
    return nullptr;
}
#line 575 "/src/analyzer.do"
std::shared_ptr<::app_src_semantic_::Symbol> findExport(const std::shared_ptr<ModuleInfo>& info, const std::string& name) {
#line 576 "/src/analyzer.do"
    const auto& _iterable_76 = info->exports;
    for (const auto& symbol : *_iterable_76) {
#line 576 "/src/analyzer.do"
        if (symbol->name == name) {
#line 576 "/src/analyzer.do"
            return symbol;
        }
    }
#line 577 "/src/analyzer.do"
    return nullptr;
}
#line 580 "/src/analyzer.do"
bool hasModuleBinding(const std::shared_ptr<ModuleInfo>& info, const std::string& name) {
#line 581 "/src/analyzer.do"
    if (!doof::is_null(findSymbol(info, name))) {
#line 581 "/src/analyzer.do"
        return true;
    }
#line 582 "/src/analyzer.do"
    const auto& _iterable_78 = info->imports;
    for (const auto& imported : *_iterable_78) {
#line 582 "/src/analyzer.do"
        if (imported->localName == name) {
#line 582 "/src/analyzer.do"
            return true;
        }
    }
#line 583 "/src/analyzer.do"
    const auto& _iterable_80 = info->namespaceImports;
    for (const auto& imported : *_iterable_80) {
#line 583 "/src/analyzer.do"
        if (imported->localName == name) {
#line 583 "/src/analyzer.do"
            return true;
        }
    }
#line 584 "/src/analyzer.do"
    return false;
}
#line 587 "/src/analyzer.do"
bool isTypeSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 588 "/src/analyzer.do"
    return (((((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("enum"))) || (symbol->kind == std::string("type-alias")));
}
#line 592 "/src/analyzer.do"
bool isBuiltin(const std::string& name) {
#line 593 "/src/analyzer.do"
    if ((name == std::string("JsonSerializable")) || (name == std::string("Reflectable"))) {
#line 593 "/src/analyzer.do"
        return true;
    }
#line 594 "/src/analyzer.do"
    const auto& _iterable_82 = BUILTIN_TYPES;
    for (const auto& builtin : *_iterable_82) {
#line 594 "/src/analyzer.do"
        if (builtin == name) {
#line 594 "/src/analyzer.do"
            return true;
        }
    }
#line 595 "/src/analyzer.do"
    return false;
}
#line 598 "/src/analyzer.do"
bool contains(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 599 "/src/analyzer.do"
    const auto& _iterable_84 = values;
    for (const auto& item : *_iterable_84) {
#line 599 "/src/analyzer.do"
        if (item == value) {
#line 599 "/src/analyzer.do"
            return true;
        }
    }
#line 600 "/src/analyzer.do"
    return false;
}
#line 603 "/src/analyzer.do"
void addError(const std::shared_ptr<ModuleInfo>& info, const std::string& message, ::app_src_ast_::SourceSpan span) {
#line 604 "/src/analyzer.do"
    info->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, semanticSpan(span), info->path, std::string("")));
}
#line 607 "/src/analyzer.do"
::app_src_semantic_::SemanticSpan semanticSpan(::app_src_ast_::SourceSpan span) {
#line 608 "/src/analyzer.do"
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
#line 614 "/src/analyzer.do"
::app_src_semantic_::SemanticSpan emptySemanticSpan() {
#line 615 "/src/analyzer.do"
    auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
#line 616 "/src/analyzer.do"
    return ::app_src_semantic_::SemanticSpan{zero, zero};
}
#line 1 "<doof-generated>"

void __doof_initialize_module() {
        BUILTIN_TYPES = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("byte"), std::string("int"), std::string("long"), std::string("float"), std::string("double"), std::string("string"), std::string("char"), std::string("bool"), std::string("none"), std::string("never"), std::string("void"), std::string("null"), std::string("JsonValue"), std::string("JsonObject"), std::string("SourceLocation"), std::string("WeakReferenceError"), std::string("Map"), std::string("ReadonlyMap"), std::string("Set"), std::string("ReadonlySet"), std::string("Result"), std::string("Stream"), std::string("Range"), std::string("Tuple"), std::string("Actor"), std::string("Promise")});
}
}
