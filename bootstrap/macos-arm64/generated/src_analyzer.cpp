#include "src_analyzer.hpp"

namespace app_src_analyzer_ {
using namespace ::app_src_parser_;
using namespace ::app_src_resolver_;
using namespace ::app_src_semantic_;
using namespace ::app_src_ast_;
using namespace ::std_::crypto::index;



std::shared_ptr<std::vector<std::string>> BUILTIN_TYPES;

std::shared_ptr<AnalysisResult> ModuleAnalyzer::analyze(const std::string& entry) {
    (this->modules = std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}));
    (this->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    (this->inProgress = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    (this->resolvedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    (this->resolver->loadedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    (this->resolver->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    (this->resolver->failedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto entryPath = (doof::string_endsWith(entry, std::string(".do")) ? entry : (entry + std::string(".do")));
    (static_cast<void>(parseReachableModules(entryPath)), std::monostate{});
    (static_cast<void>(orderModules(entryPath)), std::monostate{});
    const auto ignored = resolveModule(entryPath);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> orderedDiagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
    const auto& _iterable_2 = this->resolver->diagnostics;
    for (const auto& diagnostic : *_iterable_2) {
        (static_cast<void>(orderedDiagnostics->push_back(diagnostic)), std::monostate{});
    }
    const auto& _iterable_4 = this->diagnostics;
    for (const auto& diagnostic : *_iterable_4) {
        (static_cast<void>(orderedDiagnostics->push_back(diagnostic)), std::monostate{});
    }
    return std::make_shared<AnalysisResult>(this->modules, orderedDiagnostics);
}
void ModuleAnalyzer::queueModuleParse(const std::string& path, const std::optional<std::string>& inheritedMockRootPath, const std::shared_ptr<std::vector<std::string>>& scheduled, const std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>>& pending) {
    if (contains(scheduled, path)) {
        return;
    }
    (static_cast<void>(scheduled->push_back(path)), std::monostate{});
    const auto source = this->resolver->find(path);
    if (doof::is_null(source)) {
        if (!this->resolver->failed(path)) {
            (static_cast<void>(this->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (std::string("Module not found: ") + path), emptySemanticSpan(), path, std::string("")))), std::monostate{});
        }
        return;
    }
    const auto sourceText = source->source;
    const auto physicalPath = ((source->physicalPath == std::string("")) ? source->path : source->physicalPath);
    const auto modulePath = path;
    const auto mockRootPath = inheritedMockRootPath;
    (static_cast<void>(pending->push_back(doof::submit_async<std::shared_ptr<ModuleParseResult>>([sourceText, modulePath, physicalPath, mockRootPath]() -> std::shared_ptr<ModuleParseResult> {
    const auto parser = std::make_shared<::app_src_parser_::Parser>(sourceText, std::make_shared<std::vector<::app_src_lexer_::Token>>(std::vector<::app_src_lexer_::Token>{}), 0, false, false, 0, std::string(""), 0, 0, 0);
    const auto parsed = [&]() -> doof::Result<std::shared_ptr<::app_src_ast_::Program>, std::string> { try { return doof::Success<std::shared_ptr<::app_src_ast_::Program>>{doof::callback<std::shared_ptr<::app_src_ast_::Program>()>([parser]() -> std::shared_ptr<::app_src_ast_::Program> { return parser->parse(); }).call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }();
    auto _binding_value_5 = parsed;
    if (doof::is_failure(_binding_value_5)) {
        const auto failure = doof::failure_error(_binding_value_5);
        if (parser->errorMessage == std::string("")) {
            doof::panic(failure);
        }
        return std::make_shared<ModuleParseResult>(modulePath, physicalPath, sourceText, mockRootPath, nullptr, parser->errorMessage, parser->errorLine, parser->errorColumn, parser->errorOffset);
    }
    const auto program = doof::success_value(_binding_value_5);
    return std::make_shared<ModuleParseResult>(modulePath, physicalPath, sourceText, mockRootPath, program, std::string(""), 0, 0, 0);
}))), std::monostate{});
}
void ModuleAnalyzer::parseReachableModules(const std::string& entryPath) {
    std::shared_ptr<std::vector<std::string>> scheduled = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>> pending = std::make_shared<std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>>(std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>{});
    (static_cast<void>(queueModuleParse(entryPath, std::nullopt, scheduled, pending)), std::monostate{});
    while (static_cast<int32_t>((pending)->size()) > 0) {
        auto _binding_value_6 = doof::promise_take_first_completed(pending);
        if (doof::is_failure(_binding_value_6)) {
            const auto failure = doof::failure_error(_binding_value_6);
            doof::panic((std::string("Parser worker failed: ") + failure));
        }
        const auto completed = doof::success_value(_binding_value_6);
        if (doof::is_null(completed->program)) {
            auto location = ::app_src_semantic_::SemanticLocation{completed->errorLine, completed->errorColumn, completed->errorOffset};
            (static_cast<void>(this->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), completed->errorMessage, ::app_src_semantic_::SemanticSpan{location, location}, completed->path, std::string("")))), std::monostate{});
            continue;
        }
        const auto program = doof::unwrap_optional(completed->program);
        const auto mockImportDirectives = collectMockImportDirectives(program);
        auto mockRootPath = completed->inheritedMockRootPath;
        if ((doof::is_null(mockRootPath) && (static_cast<int32_t>((mockImportDirectives)->size()) > 0)) && doof::string_endsWith(completed->path, std::string(".test.do"))) {
            (mockRootPath = completed->path);
        }
        const auto info = std::make_shared<ModuleInfo>(completed->path, completed->physicalPath, ::std_::crypto::index::sha256HexString(completed->source), program, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), mockImportDirectives, mockRootPath, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
        (static_cast<void>(this->modules->push_back(info)), std::monostate{});
        (static_cast<void>(validateMockImportDirectives(info, completed->inheritedMockRootPath)), std::monostate{});
        (static_cast<void>(collectSymbols(info)), std::monostate{});
        const auto& _iterable_8 = program->statements;
        for (const auto& statement : *_iterable_8) {
            {
                auto _case_subject = statement;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
                    const auto& import_ = std::get<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject);
                    const auto sourcePath = resolveImportPath(info, import_->source);
                    (static_cast<void>(queueModuleParse(sourcePath, info->mockRootPath, scheduled, pending)), std::monostate{});
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                    const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
                    if (!doof::is_null(list->source)) {
                        const auto sourcePath = resolveImportPath(info, doof::unwrap_optional(list->source));
                        (static_cast<void>(queueModuleParse(sourcePath, info->mockRootPath, scheduled, pending)), std::monostate{});
                    }
            }
            else {
            }
            }
        }
    }
}
void ModuleAnalyzer::orderModules(const std::string& entryPath) {
    std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> ordered = std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{});
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    (static_cast<void>(appendModuleOrder(entryPath, ordered, visited)), std::monostate{});
    (this->modules = ordered);
}
void ModuleAnalyzer::appendModuleOrder(const std::string& path, const std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>>& ordered, const std::shared_ptr<std::vector<std::string>>& visited) {
    if (contains(visited, path)) {
        return;
    }
    (static_cast<void>(visited->push_back(path)), std::monostate{});
    const auto info = findModule(path);
    if (doof::is_null(info)) {
        return;
    }
    (static_cast<void>(ordered->push_back(doof::unwrap_optional(info))), std::monostate{});
    const auto& _iterable_10 = info->program->statements;
    for (const auto& statement : *_iterable_10) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
                const auto& import_ = std::get<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject);
                (static_cast<void>(appendModuleOrder(resolveImportPath(doof::unwrap_optional(info), import_->source), ordered, visited)), std::monostate{});
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
                if (!doof::is_null(list->source)) {
                    (static_cast<void>(appendModuleOrder(resolveImportPath(doof::unwrap_optional(info), doof::unwrap_optional(list->source)), ordered, visited)), std::monostate{});
                }
        }
        else {
        }
        }
    }
}
std::shared_ptr<ModuleInfo> ModuleAnalyzer::resolveModule(const std::string& path) {
    const auto existing = findModule(path);
    if (doof::is_null(existing)) {
        return nullptr;
    }
    if (contains(this->resolvedPaths, path)) {
        return existing;
    }
    if (contains(this->inProgress, path)) {
        return existing;
    }
    (static_cast<void>(this->inProgress->push_back(path)), std::monostate{});
    const auto info = doof::unwrap_optional(existing);
    (static_cast<void>(resolveImports(info)), std::monostate{});
    (static_cast<void>(resolveExportLists(info)), std::monostate{});
    (static_cast<void>(resolveNamedTypes(info)), std::monostate{});
    const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(this->inProgress); if (doof::is_failure(_try_value)) doof::panic_at("src/analyzer", 207, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    (static_cast<void>(this->resolvedPaths->push_back(path)), std::monostate{});
    const auto& _iterable_12 = info->diagnostics;
    for (const auto& item : *_iterable_12) {
        (static_cast<void>(this->diagnostics->push_back(item)), std::monostate{});
    }
    return info;
}
void ModuleAnalyzer::collectSymbols(const std::shared_ptr<ModuleInfo>& info) {
    const auto& _iterable_14 = info->program->statements;
    for (const auto& statement : *_iterable_14) {
        const auto symbol = symbolFor(statement, info->path);
        if (doof::is_null(symbol)) {
            continue;
        }
        (static_cast<void>(decorateDeclarationSymbol(statement, doof::unwrap_optional(symbol))), std::monostate{});
        if (!doof::is_null(findSymbol(info, symbol->name))) {
            (static_cast<void>(addError(info, ((std::string("Duplicate module binding '") + symbol->name) + std::string("'")), std::visit([](auto&& _obj) { return _obj->span; }, statement))), std::monostate{});
            continue;
        }
        (static_cast<void>(info->symbols->push_back(doof::unwrap_optional(symbol))), std::monostate{});
        if (symbol->exported) {
            (static_cast<void>(info->exports->push_back(doof::unwrap_optional(symbol))), std::monostate{});
        }
    }
}
void ModuleAnalyzer::decorateDeclarationSymbol(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            (class_->resolvedSymbol = symbol);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            (interface_->resolvedSymbol = symbol);
    }
    else {
    }
    }
}
std::shared_ptr<::app_src_semantic_::Symbol> ModuleAnalyzer::symbolFor(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::string& module) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>((value->struct_ ? std::string("struct") : std::string("class")), value->name, module, value->exported, std::string(""), value->native_, value->nativeHeader, value->nativeCppName, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), value->typeParams, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("interface"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("function"), value->name, module, value->exported, std::string(""), value->native_, value->nativeHeader, value->nativeCppName, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("type-alias"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("const"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("readonly"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("const"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("enum"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    }
    else {
            return nullptr;
    }
    }
    doof::unreachable();
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Symbol> ModuleAnalyzer::exportedSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& exportedName) {
    return std::make_shared<::app_src_semantic_::Symbol>(symbol->kind, exportedName, symbol->module, true, ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName), symbol->native_, symbol->nativeHeader, symbol->nativeCppName, symbol->implementations, symbol->implementedInterfaceTypes, symbol->typeParams, symbol->streamElementTypes);
}
void ModuleAnalyzer::resolveImports(const std::shared_ptr<ModuleInfo>& info) {
    const auto& _iterable_18 = info->program->statements;
    for (const auto& statement : *_iterable_18) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
                const auto& import_ = std::get<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject);
                const auto sourcePath = resolveImportPath(info, import_->source);
                if (doof::string_endsWith(info->path, std::string(".test.do")) && doof::string_endsWith(sourcePath, std::string(".test.do"))) {
                    (static_cast<void>(addError(info, ((((std::string("Test file \"") + info->path) + std::string("\" cannot import another test file \"")) + sourcePath) + std::string("\"")), import_->span)), std::monostate{});
                    continue;
                }
                const auto source = resolveModule(sourcePath);
                const auto& _iterable_16 = import_->specifiers;
                for (const auto& specifier : *_iterable_16) {
                    {
                        auto _case_subject = specifier;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedImport>>(_case_subject)) {
                            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedImport>>(_case_subject);
                            std::shared_ptr<::app_src_semantic_::Symbol> imported = nullptr;
                            if (!doof::is_null(source)) {
                                (imported = findExport(doof::unwrap_optional(source), named->name));
                            }
                            if ((!doof::is_null(source)) && doof::is_null(imported)) {
                                (static_cast<void>(addError(info, ((((std::string("Module '") + import_->source) + std::string("' does not export '")) + named->name) + std::string("'")), named->span)), std::monostate{});
                            }
                            const auto localName = (doof::is_null(named->alias) ? named->name : doof::unwrap_optional(named->alias));
                            if (hasModuleBinding(info, localName)) {
                                (static_cast<void>(addError(info, ((std::string("Duplicate module binding '") + localName) + std::string("'")), named->span)), std::monostate{});
                                continue;
                            }
                            if (doof::is_null(imported)) {
                                (static_cast<void>(info->imports->push_back(std::make_shared<::app_src_semantic_::ImportBinding>(localName, named->name, sourcePath, import_->typeOnly, nullptr))), std::monostate{});
                            } else {
                                (static_cast<void>(info->imports->push_back(std::make_shared<::app_src_semantic_::ImportBinding>(localName, named->name, sourcePath, import_->typeOnly, imported))), std::monostate{});
                            }
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamespaceImport>>(_case_subject)) {
                            const auto& namespace_ = std::get<std::shared_ptr<::app_src_ast_::NamespaceImport>>(_case_subject);
                            if (hasModuleBinding(info, namespace_->alias)) {
                                (static_cast<void>(addError(info, ((std::string("Duplicate module binding '") + namespace_->alias) + std::string("'")), namespace_->span)), std::monostate{});
                                continue;
                            }
                            (static_cast<void>(info->namespaceImports->push_back(std::make_shared<::app_src_semantic_::NamespaceBinding>(namespace_->alias, sourcePath, import_->typeOnly))), std::monostate{});
                    }
                    }
                }
        }
        else {
        }
        }
    }
}
void ModuleAnalyzer::resolveExportLists(const std::shared_ptr<ModuleInfo>& info) {
    const auto& _iterable_24 = info->program->statements;
    for (const auto& statement : *_iterable_24) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
                if (!doof::is_null(list->source)) {
                    const auto sourcePath = resolveImportPath(info, doof::unwrap_optional(list->source));
                    const auto source = resolveModule(sourcePath);
                    (static_cast<void>(info->reExports->push_back(sourcePath)), std::monostate{});
                    const auto& _iterable_20 = list->specifiers;
                    for (const auto& specifier : *_iterable_20) {
                        std::shared_ptr<::app_src_semantic_::Symbol> exported = nullptr;
                        if (!doof::is_null(source)) {
                            (exported = findExport(doof::unwrap_optional(source), specifier->name));
                        }
                        if ((!doof::is_null(source)) && doof::is_null(exported)) {
                            (static_cast<void>(addError(info, ((((std::string("Module '") + doof::unwrap_optional(list->source)) + std::string("' does not export '")) + specifier->name) + std::string("'")), specifier->span)), std::monostate{});
                        } else {
                            if (!doof::is_null(exported)) {
                                const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
                                (static_cast<void>(info->exports->push_back(exportedSymbol(doof::unwrap_optional(exported), exportedName))), std::monostate{});
                            }
                        }
                    }
                    continue;
                }
                const auto& _iterable_22 = list->specifiers;
                for (const auto& specifier : *_iterable_22) {
                    const auto local = findSymbol(info, specifier->name);
                    if (!doof::is_null(local)) {
                        const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
                        if (doof::is_null(findExport(info, exportedName))) {
                            (static_cast<void>(info->exports->push_back(exportedSymbol(doof::unwrap_optional(local), exportedName))), std::monostate{});
                        }
                    } else {
                        (static_cast<void>(addError(info, ((std::string("Cannot export unknown symbol '") + specifier->name) + std::string("'")), specifier->span)), std::monostate{});
                    }
                }
        }
        else {
        }
        }
    }
}
void ModuleAnalyzer::resolveNamedTypes(const std::shared_ptr<ModuleInfo>& info) {
    const auto& _iterable_26 = info->program->statements;
    for (const auto& statement : *_iterable_26) {
        (static_cast<void>(visitStatementTypes(statement, info)), std::monostate{});
    }
}
void ModuleAnalyzer::visitStatementTypes(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<ModuleInfo>& info) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            (static_cast<void>(visitFunctionTypes(fn, info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            (static_cast<void>(visitTypeParameterConstraints(class_->typeParamConstraints, info, class_->typeParams)), std::monostate{});
            const auto& _iterable_28 = class_->implements_;
            for (const auto& annotation : *_iterable_28) {
                (static_cast<void>(visitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(annotation), info, class_->typeParams)), std::monostate{});
            }
            const auto& _iterable_30 = class_->fields;
            for (const auto& field : *_iterable_30) {
                if (!doof::is_null(field->type_)) {
                    (static_cast<void>(visitType(doof::unwrap_optional(field->type_), info, class_->typeParams)), std::monostate{});
                }
            }
            const auto& _iterable_32 = class_->methods;
            for (const auto& method : *_iterable_32) {
                (static_cast<void>(visitFunctionTypes(method, info, class_->typeParams)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            (static_cast<void>(visitTypeParameterConstraints(interface_->typeParamConstraints, info, interface_->typeParams)), std::monostate{});
            const auto& _iterable_34 = interface_->fields;
            for (const auto& field : *_iterable_34) {
                (static_cast<void>(visitType(field->type_, info, interface_->typeParams)), std::monostate{});
            }
            const auto& _iterable_36 = interface_->methods;
            for (const auto& method : *_iterable_36) {
                (static_cast<void>(visitFunctionTypes(method, info, interface_->typeParams)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            (static_cast<void>(visitTypeParameterConstraints(alias->typeParamConstraints, info, alias->typeParams)), std::monostate{});
            (static_cast<void>(visitType(alias->type_, info, alias->typeParams)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            if (!doof::is_null(const_->type_)) {
                (static_cast<void>(visitType(doof::unwrap_optional(const_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            if (!doof::is_null(readonly_->type_)) {
                (static_cast<void>(visitType(doof::unwrap_optional(readonly_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            if (!doof::is_null(binding->type_)) {
                (static_cast<void>(visitType(doof::unwrap_optional(binding->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            if (!doof::is_null(let_->type_)) {
                (static_cast<void>(visitType(doof::unwrap_optional(let_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))), std::monostate{});
            }
    }
    else {
    }
    }
}
void ModuleAnalyzer::visitFunctionTypes(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams) {
    std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_38 = ownerTypeParams;
    for (const auto& parameter : *_iterable_38) {
        (static_cast<void>(typeParams->push_back(parameter)), std::monostate{});
    }
    const auto& _iterable_40 = fn->typeParams;
    for (const auto& parameter : *_iterable_40) {
        (static_cast<void>(typeParams->push_back(parameter)), std::monostate{});
    }
    (static_cast<void>(visitTypeParameterConstraints(fn->typeParamConstraints, info, typeParams)), std::monostate{});
    const auto& _iterable_42 = fn->params;
    for (const auto& parameter : *_iterable_42) {
        if (!doof::is_null(parameter->type_)) {
            (static_cast<void>(visitType(doof::unwrap_optional(parameter->type_), info, typeParams)), std::monostate{});
        }
    }
    if (!doof::is_null(fn->returnType)) {
        (static_cast<void>(visitType(doof::unwrap_optional(fn->returnType), info, typeParams)), std::monostate{});
    }
}
void ModuleAnalyzer::visitTypeParameterConstraints(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& constraints, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& typeParams) {
    const auto& _iterable_44 = constraints;
    for (const auto& constraint : *_iterable_44) {
        if (!doof::is_null(constraint->type_)) {
            (static_cast<void>(visitType(doof::unwrap_optional(constraint->type_), info, typeParams)), std::monostate{});
        }
    }
}
void ModuleAnalyzer::visitType(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& typeParams) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (!isBuiltin(named->name) && !containsTypeParam(typeParams, named->name)) {
                std::shared_ptr<::app_src_semantic_::Symbol> symbol = findSymbol(info, named->name);
                if (doof::is_null(symbol)) {
                    const auto& _iterable_46 = info->imports;
                    for (const auto& imported : *_iterable_46) {
                        if (imported->localName == named->name) {
                            (symbol = imported->symbol);
                            break;
                        }
                    }
                }
                if (doof::is_null(symbol)) {
                    (symbol = findExport(info, named->name));
                }
                if (doof::is_null(symbol)) {
                    (static_cast<void>(addError(info, ((std::string("Unknown type '") + named->name) + std::string("'")), named->span)), std::monostate{});
                } else if (!isTypeSymbol(doof::unwrap_optional(symbol))) {
                    (static_cast<void>(addError(info, ((std::string("Symbol '") + named->name) + std::string("' is not a type")), named->span)), std::monostate{});
                    (symbol = nullptr);
                }
                (named->resolvedSymbol = symbol);
            }
            const auto& _iterable_48 = named->typeArgs;
            for (const auto& argument : *_iterable_48) {
                (static_cast<void>(visitType(argument, info, typeParams)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            (static_cast<void>(visitType(array->elementType, info, typeParams)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            const auto& _iterable_50 = union_->types;
            for (const auto& member : *_iterable_50) {
                (static_cast<void>(visitType(member, info, typeParams)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
            const auto& _iterable_52 = function_->params;
            for (const auto& parameter : *_iterable_52) {
                (static_cast<void>(visitType(parameter->type_, info, typeParams)), std::monostate{});
            }
            (static_cast<void>(visitType(function_->returnType, info, typeParams)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
            (static_cast<void>(visitType(weak_->type_, info, typeParams)), std::monostate{});
    }
    }
}
bool ModuleAnalyzer::containsTypeParam(const std::shared_ptr<std::vector<std::string>>& typeParams, const std::string& name) {
    const auto& _iterable_54 = typeParams;
    for (const auto& typeParam : *_iterable_54) {
        if (typeParam == name) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<ModuleInfo> ModuleAnalyzer::findModule(const std::string& path) {
    const auto& _iterable_56 = this->modules;
    for (const auto& module : *_iterable_56) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
std::string ModuleAnalyzer::resolveImportPath(const std::shared_ptr<ModuleInfo>& info, const std::string& specifier) {
    if (doof::is_null(info->mockRootPath)) {
        return this->resolver->resolve(info->path, specifier);
    }
    const auto root = findModule(doof::unwrap_optional(info->mockRootPath));
    if (doof::is_null(root) || (static_cast<int32_t>((root->mockImportDirectives)->size()) == 0)) {
        return this->resolver->resolve(info->path, specifier);
    }
    const auto replacement = findMockReplacement(doof::unwrap_optional(root), info->path, specifier);
    if (doof::is_null(replacement)) {
        return this->resolver->resolve(info->path, specifier);
    }
    return this->resolver->resolve(doof::unwrap_optional(info->mockRootPath), replacement.value());
}
std::optional<std::string> ModuleAnalyzer::findMockReplacement(const std::shared_ptr<ModuleInfo>& root, const std::string& sourcePath, const std::string& dependencySpecifier) {
    const auto& _iterable_60 = root->mockImportDirectives;
    for (const auto& directive : *_iterable_60) {
        if (this->resolver->resolve(root->path, directive->sourcePattern) != sourcePath) {
            continue;
        }
        const auto& _iterable_58 = directive->mappings;
        for (const auto& mapping : *_iterable_58) {
            if (mapping->dependency == dependencySpecifier) {
                return mapping->replacement;
            }
        }
    }
    return std::nullopt;
}
void ModuleAnalyzer::validateMockImportDirectives(const std::shared_ptr<ModuleInfo>& info, const std::optional<std::string>& inheritedMockRootPath) {
    if (static_cast<int32_t>((info->mockImportDirectives)->size()) == 0) {
        return;
    }
    if (!doof::string_endsWith(info->path, std::string(".test.do"))) {
        const auto& _iterable_62 = info->mockImportDirectives;
        for (const auto& directive : *_iterable_62) {
            (static_cast<void>(addError(info, std::string("mock import directives are only valid in .test.do files"), directive->span)), std::monostate{});
        }
    }
    if ((!doof::is_null(inheritedMockRootPath)) && (inheritedMockRootPath != info->path)) {
        const auto& _iterable_64 = info->mockImportDirectives;
        for (const auto& directive : *_iterable_64) {
            (static_cast<void>(addError(info, std::string("mock import directives are only valid in the root test file"), directive->span)), std::monostate{});
        }
    }
    auto sawOrdinaryStatement = false;
    const auto& _iterable_66 = info->program->statements;
    for (const auto& statement : *_iterable_66) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                const auto& directive = std::get<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject);
                if (sawOrdinaryStatement) {
                    (static_cast<void>(addError(info, std::string("mock import directives must appear at the top of the file before other statements"), directive->span)), std::monostate{});
                }
        }
        else {
                (sawOrdinaryStatement = true);
        }
        }
    }
    const auto& _iterable_70 = info->mockImportDirectives;
    for (const auto& directive : *_iterable_70) {
        const auto& _iterable_68 = directive->mappings;
        for (const auto& mapping : *_iterable_68) {
            if (mapping->dependency == mapping->replacement) {
                (static_cast<void>(addError(info, ((std::string("mock import cannot substitute \"") + mapping->dependency) + std::string("\" with itself")), mapping->span)), std::monostate{});
            }
        }
    }
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> collectMockImportDirectives(const std::shared_ptr<::app_src_ast_::Program>& program) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> directives = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>>(std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>{});
    const auto& _iterable_72 = program->statements;
    for (const auto& statement : *_iterable_72) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                const auto& directive = std::get<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject);
                (static_cast<void>(directives->push_back(directive)), std::monostate{});
        }
        else {
        }
        }
    }
    return directives;
}
std::shared_ptr<ModuleAnalyzer> createAnalyzer(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources) {
    return std::make_shared<ModuleAnalyzer>(std::make_shared<::app_src_resolver_::ModuleResolver>(sources, ::app_src_resolver_::noSourceLoader, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{})), std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
std::shared_ptr<ModuleAnalyzer> createAnalyzerWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader) {
    return std::make_shared<ModuleAnalyzer>(std::make_shared<::app_src_resolver_::ModuleResolver>(sources, loader, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{})), std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
std::shared_ptr<::app_src_semantic_::Symbol> findSymbol(const std::shared_ptr<ModuleInfo>& info, const std::string& name) {
    const auto& _iterable_74 = info->symbols;
    for (const auto& symbol : *_iterable_74) {
        if (symbol->name == name) {
            return symbol;
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Symbol> findExport(const std::shared_ptr<ModuleInfo>& info, const std::string& name) {
    const auto& _iterable_76 = info->exports;
    for (const auto& symbol : *_iterable_76) {
        if (symbol->name == name) {
            return symbol;
        }
    }
    return nullptr;
}
bool hasModuleBinding(const std::shared_ptr<ModuleInfo>& info, const std::string& name) {
    if (!doof::is_null(findSymbol(info, name))) {
        return true;
    }
    const auto& _iterable_78 = info->imports;
    for (const auto& imported : *_iterable_78) {
        if (imported->localName == name) {
            return true;
        }
    }
    const auto& _iterable_80 = info->namespaceImports;
    for (const auto& imported : *_iterable_80) {
        if (imported->localName == name) {
            return true;
        }
    }
    return false;
}
bool isTypeSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
    return (((((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("enum"))) || (symbol->kind == std::string("type-alias")));
}
bool isBuiltin(const std::string& name) {
    if ((name == std::string("JsonSerializable")) || (name == std::string("Reflectable"))) {
        return true;
    }
    const auto& _iterable_82 = BUILTIN_TYPES;
    for (const auto& builtin : *_iterable_82) {
        if (builtin == name) {
            return true;
        }
    }
    return false;
}
bool contains(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto& _iterable_84 = values;
    for (const auto& item : *_iterable_84) {
        if (item == value) {
            return true;
        }
    }
    return false;
}
void addError(const std::shared_ptr<ModuleInfo>& info, const std::string& message, ::app_src_ast_::SourceSpan span) {
    (static_cast<void>(info->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, semanticSpan(span), info->path, std::string("")))), std::monostate{});
}
::app_src_semantic_::SemanticSpan semanticSpan(::app_src_ast_::SourceSpan span) {
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
::app_src_semantic_::SemanticSpan emptySemanticSpan() {
    auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
    return ::app_src_semantic_::SemanticSpan{zero, zero};
}

void __doof_initialize_module() {
        BUILTIN_TYPES = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("byte"), std::string("int"), std::string("long"), std::string("float"), std::string("double"), std::string("string"), std::string("char"), std::string("bool"), std::string("none"), std::string("never"), std::string("void"), std::string("null"), std::string("JsonValue"), std::string("JsonObject"), std::string("SourceLocation"), std::string("WeakReferenceError"), std::string("Map"), std::string("ReadonlyMap"), std::string("Set"), std::string("ReadonlySet"), std::string("Result"), std::string("Stream"), std::string("Range"), std::string("Tuple"), std::string("Actor"), std::string("Promise")});
}
}
