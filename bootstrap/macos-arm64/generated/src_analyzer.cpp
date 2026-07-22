#include "src_analyzer.hpp"
#include <cmath>
#include "src_parser.hpp"
#include "src_resolver.hpp"
#include "src_semantic.hpp"
#include "src_ast.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_analyzer_ {
using namespace ::app_src_parser_;
using namespace ::app_src_resolver_;
using namespace ::app_src_semantic_;
using namespace ::app_src_ast_;


const auto BUILTIN_TYPES = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("byte"), std::string("int"), std::string("long"), std::string("float"), std::string("double"), std::string("string"), std::string("char"), std::string("bool"), std::string("none"), std::string("never"), std::string("void"), std::string("null"), std::string("JsonValue"), std::string("JsonObject"), std::string("SourceLocation"), std::string("ParseError"), std::string("Map"), std::string("ReadonlyMap"), std::string("Set"), std::string("ReadonlySet"), std::string("Result"), std::string("Stream"), std::string("Range"), std::string("Tuple"), std::string("Actor"), std::string("Promise")});

std::shared_ptr<AnalysisResult> ModuleAnalyzer::analyze(std::string entry) {
    (this->modules = std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}));
    (this->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    (this->inProgress = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    (this->resolver->loadedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    (this->resolver->diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    (this->resolver->failedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto ignored = analyzeModule((doof::string_endsWith(entry, std::string(".do")) ? entry : (entry + std::string(".do"))), std::nullopt);
    const auto& _iterable_1 = this->resolver->diagnostics;
    for (const auto& diagnostic : *_iterable_1) {
        this->diagnostics->push_back(diagnostic);
    }
    return std::make_shared<AnalysisResult>(modules, diagnostics);
}
std::shared_ptr<ModuleInfo> ModuleAnalyzer::analyzeModule(std::string path, std::optional<std::string> inheritedMockRootPath) {
    const auto existing = findModule(path);
    if (!doof::is_null(existing)) {
        return existing;
    }
    if (contains(this->inProgress, path)) {
        return nullptr;
    }
    const auto source = this->resolver->find(path);
    if (doof::is_null(source)) {
        if (!this->resolver->failed(path)) {
            this->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (std::string("Module not found: ") + path), emptySemanticSpan(), path, std::string("")));
        }
        return nullptr;
    }
    this->inProgress->push_back(path);
    const auto parser = std::make_shared<::app_src_parser_::Parser>(source->source, std::make_shared<std::vector<::app_src_lexer_::Token>>(std::vector<::app_src_lexer_::Token>{}), 0, false, std::string(""), 0, 0, 0);
    const auto parsed = [&]() -> doof::Result<std::shared_ptr<::app_src_ast_::Program>, std::string> { try { return doof::Success<std::shared_ptr<::app_src_ast_::Program>>{doof::callback<std::shared_ptr<::app_src_ast_::Program>()>([parser]() -> std::shared_ptr<::app_src_ast_::Program> { return parser->parse(); }).call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }();
    auto _binding_value_2 = parsed;
    if (doof::is_failure(_binding_value_2)) {
        const auto failure = doof::failure_error(_binding_value_2);
        if (parser->errorMessage == std::string("")) {
            doof::panic(failure);
        }
        auto location = ::app_src_semantic_::SemanticLocation{parser->errorLine, parser->errorColumn, parser->errorOffset};
        this->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), parser->errorMessage, ::app_src_semantic_::SemanticSpan{location, location}, path, std::string("")));
        const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(this->inProgress); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        return nullptr;
    }
    const auto program = doof::success_value(_binding_value_2);
    const auto mockImportDirectives = collectMockImportDirectives(program);
    auto mockRootPath = inheritedMockRootPath;
    if ((doof::is_null(mockRootPath) && (static_cast<int32_t>((mockImportDirectives)->size()) > 0)) && doof::string_endsWith(path, std::string(".test.do"))) {
        (mockRootPath = path);
    }
    const auto info = std::make_shared<ModuleInfo>(path, program, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), mockImportDirectives, mockRootPath, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}));
    this->modules->push_back(info);
    validateMockImportDirectives(info, inheritedMockRootPath);
    collectSymbols(info);
    resolveImports(info);
    resolveExportLists(info);
    resolveNamedTypes(info);
    const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(this->inProgress); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    const auto& _iterable_3 = info->diagnostics;
    for (const auto& item : *_iterable_3) {
        this->diagnostics->push_back(item);
    }
    return info;
}
void ModuleAnalyzer::collectSymbols(std::shared_ptr<ModuleInfo> info) {
    const auto& _iterable_4 = info->program->statements;
    for (const auto& statement : *_iterable_4) {
        const auto symbol = symbolFor(statement, info->path);
        if (doof::is_null(symbol)) {
            continue;
        }
        decorateDeclarationSymbol(statement, doof::unwrap_optional(symbol));
        info->symbols->push_back(doof::unwrap_optional(symbol));
        if (symbol->exported) {
            info->exports->push_back(doof::unwrap_optional(symbol));
        }
    }
}
void ModuleAnalyzer::decorateDeclarationSymbol(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<::app_src_semantic_::Symbol> symbol) {
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
std::shared_ptr<::app_src_semantic_::Symbol> ModuleAnalyzer::symbolFor(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::string module) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>((value->struct_ ? std::string("struct") : std::string("class")), value->name, module, value->exported, std::string(""), value->native_, value->nativeHeader, value->nativeCppName, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("interface"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("function"), value->name, module, value->exported, std::string(""), value->native_, value->nativeHeader, value->nativeCppName, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("type-alias"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("const"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("readonly"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("const"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            return std::make_shared<::app_src_semantic_::Symbol>(std::string("enum"), value->name, module, value->exported, std::string(""), false, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else {
            return nullptr;
    }
    }
    doof::unreachable();
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Symbol> ModuleAnalyzer::exportedSymbol(std::shared_ptr<::app_src_semantic_::Symbol> symbol, std::string exportedName) {
    return std::make_shared<::app_src_semantic_::Symbol>(symbol->kind, exportedName, symbol->module, true, ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName), symbol->native_, symbol->nativeHeader, symbol->nativeCppName, symbol->implementations, symbol->implementedInterfaceTypes);
}
void ModuleAnalyzer::resolveImports(std::shared_ptr<ModuleInfo> info) {
    const auto& _iterable_5 = info->program->statements;
    for (const auto& statement : *_iterable_5) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
                const auto& import_ = std::get<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject);
                const auto sourcePath = resolveImportPath(info, import_->source);
                if ((doof::string_endsWith(info->path, std::string(".test.do")) && (info->mockRootPath == info->path)) && doof::string_endsWith(sourcePath, std::string(".test.do"))) {
                    addError(info, ((((std::string("Test file \"") + info->path) + std::string("\" cannot import another test file \"")) + sourcePath) + std::string("\"")), import_->span);
                    continue;
                }
                const auto source = analyzeModule(sourcePath, info->mockRootPath);
                const auto& _iterable_6 = import_->specifiers;
                for (const auto& specifier : *_iterable_6) {
                    {
                        auto _case_subject = specifier;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedImport>>(_case_subject)) {
                            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedImport>>(_case_subject);
                            std::shared_ptr<::app_src_semantic_::Symbol> imported = nullptr;
                            if (!doof::is_null(source)) {
                                (imported = findExport(doof::unwrap_optional(source), named->name));
                            }
                            if ((!doof::is_null(source)) && doof::is_null(imported)) {
                                addError(info, ((((std::string("Module '") + import_->source) + std::string("' does not export '")) + named->name) + std::string("'")), named->span);
                            }
                            const auto localName = (doof::is_null(named->alias) ? named->name : doof::unwrap_optional(named->alias));
                            if (doof::is_null(imported)) {
                                info->imports->push_back(std::make_shared<::app_src_semantic_::ImportBinding>(localName, named->name, sourcePath, import_->typeOnly, nullptr));
                            } else {
                                info->imports->push_back(std::make_shared<::app_src_semantic_::ImportBinding>(localName, named->name, sourcePath, import_->typeOnly, imported));
                            }
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamespaceImport>>(_case_subject)) {
                            const auto& namespace_ = std::get<std::shared_ptr<::app_src_ast_::NamespaceImport>>(_case_subject);
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
void ModuleAnalyzer::resolveExportLists(std::shared_ptr<ModuleInfo> info) {
    const auto& _iterable_7 = info->program->statements;
    for (const auto& statement : *_iterable_7) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
                const auto& list = std::get<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject);
                if (!doof::is_null(list->source)) {
                    const auto sourcePath = resolveImportPath(info, doof::unwrap_optional(list->source));
                    const auto source = analyzeModule(sourcePath, info->mockRootPath);
                    info->reExports->push_back(sourcePath);
                    const auto& _iterable_8 = list->specifiers;
                    for (const auto& specifier : *_iterable_8) {
                        std::shared_ptr<::app_src_semantic_::Symbol> exported = nullptr;
                        if (!doof::is_null(source)) {
                            (exported = findExport(doof::unwrap_optional(source), specifier->name));
                        }
                        if ((!doof::is_null(source)) && doof::is_null(exported)) {
                            addError(info, ((((std::string("Module '") + doof::unwrap_optional(list->source)) + std::string("' does not export '")) + specifier->name) + std::string("'")), specifier->span);
                        } else {
                            if (!doof::is_null(exported)) {
                                const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
                                info->exports->push_back(exportedSymbol(doof::unwrap_optional(exported), exportedName));
                            }
                        }
                    }
                    continue;
                }
                const auto& _iterable_9 = list->specifiers;
                for (const auto& specifier : *_iterable_9) {
                    const auto local = findSymbol(info, specifier->name);
                    if (!doof::is_null(local)) {
                        const auto exportedName = (doof::is_null(specifier->alias) ? specifier->name : doof::unwrap_optional(specifier->alias));
                        if (doof::is_null(findExport(info, exportedName))) {
                            info->exports->push_back(exportedSymbol(doof::unwrap_optional(local), exportedName));
                        }
                    } else {
                        addError(info, ((std::string("Cannot export unknown symbol '") + specifier->name) + std::string("'")), specifier->span);
                    }
                }
        }
        else {
        }
        }
    }
}
void ModuleAnalyzer::resolveNamedTypes(std::shared_ptr<ModuleInfo> info) {
    const auto& _iterable_10 = info->program->statements;
    for (const auto& statement : *_iterable_10) {
        visitStatementTypes(statement, info);
    }
}
void ModuleAnalyzer::visitStatementTypes(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<ModuleInfo> info) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            visitFunctionTypes(fn, info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            visitTypeParameterConstraints(class_->typeParamConstraints, info, class_->typeParams);
            const auto& _iterable_11 = class_->implements_;
            for (const auto& annotation : *_iterable_11) {
                visitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>>(annotation), info, class_->typeParams);
            }
            const auto& _iterable_12 = class_->fields;
            for (const auto& field : *_iterable_12) {
                if (!doof::is_null(field->type_)) {
                    visitType(doof::unwrap_optional(field->type_), info, class_->typeParams);
                }
            }
            const auto& _iterable_13 = class_->methods;
            for (const auto& method : *_iterable_13) {
                visitFunctionTypes(method, info, class_->typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            visitTypeParameterConstraints(interface_->typeParamConstraints, info, interface_->typeParams);
            const auto& _iterable_14 = interface_->fields;
            for (const auto& field : *_iterable_14) {
                visitType(field->type_, info, interface_->typeParams);
            }
            const auto& _iterable_15 = interface_->methods;
            for (const auto& method : *_iterable_15) {
                visitFunctionTypes(method, info, interface_->typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            visitTypeParameterConstraints(alias->typeParamConstraints, info, alias->typeParams);
            visitType(alias->type_, info, alias->typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            if (!doof::is_null(const_->type_)) {
                visitType(doof::unwrap_optional(const_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            if (!doof::is_null(readonly_->type_)) {
                visitType(doof::unwrap_optional(readonly_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            if (!doof::is_null(binding->type_)) {
                visitType(doof::unwrap_optional(binding->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            if (!doof::is_null(let_->type_)) {
                visitType(doof::unwrap_optional(let_->type_), info, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
    }
    else {
    }
    }
}
void ModuleAnalyzer::visitFunctionTypes(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::shared_ptr<ModuleInfo> info, std::shared_ptr<std::vector<std::string>> ownerTypeParams) {
    std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_16 = ownerTypeParams;
    for (const auto& parameter : *_iterable_16) {
        typeParams->push_back(parameter);
    }
    const auto& _iterable_17 = fn->typeParams;
    for (const auto& parameter : *_iterable_17) {
        typeParams->push_back(parameter);
    }
    visitTypeParameterConstraints(fn->typeParamConstraints, info, typeParams);
    const auto& _iterable_18 = fn->params;
    for (const auto& parameter : *_iterable_18) {
        if (!doof::is_null(parameter->type_)) {
            visitType(doof::unwrap_optional(parameter->type_), info, typeParams);
        }
    }
    if (!doof::is_null(fn->returnType)) {
        visitType(doof::unwrap_optional(fn->returnType), info, typeParams);
    }
}
void ModuleAnalyzer::visitTypeParameterConstraints(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints, std::shared_ptr<ModuleInfo> info, std::shared_ptr<std::vector<std::string>> typeParams) {
    const auto& _iterable_19 = constraints;
    for (const auto& constraint : *_iterable_19) {
        if (!doof::is_null(constraint->type_)) {
            visitType(doof::unwrap_optional(constraint->type_), info, typeParams);
        }
    }
}
void ModuleAnalyzer::visitType(std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::shared_ptr<ModuleInfo> info, std::shared_ptr<std::vector<std::string>> typeParams) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (!isBuiltin(named->name) && !containsTypeParam(typeParams, named->name)) {
                std::shared_ptr<::app_src_semantic_::Symbol> symbol = findSymbol(info, named->name);
                if (doof::is_null(symbol)) {
                    const auto& _iterable_20 = info->imports;
                    for (const auto& imported : *_iterable_20) {
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
                    addError(info, ((std::string("Unknown type '") + named->name) + std::string("'")), named->span);
                }
                (named->resolvedSymbol = symbol);
            }
            const auto& _iterable_21 = named->typeArgs;
            for (const auto& argument : *_iterable_21) {
                visitType(argument, info, typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            visitType(array->elementType, info, typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            const auto& _iterable_22 = union_->types;
            for (const auto& member : *_iterable_22) {
                visitType(member, info, typeParams);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
            const auto& _iterable_23 = function_->params;
            for (const auto& parameter : *_iterable_23) {
                visitType(parameter->type_, info, typeParams);
            }
            visitType(function_->returnType, info, typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
            visitType(weak_->type_, info, typeParams);
    }
    }
}
bool ModuleAnalyzer::containsTypeParam(std::shared_ptr<std::vector<std::string>> typeParams, std::string name) {
    const auto& _iterable_24 = typeParams;
    for (const auto& typeParam : *_iterable_24) {
        if (typeParam == name) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<ModuleInfo> ModuleAnalyzer::findModule(std::string path) {
    const auto& _iterable_25 = this->modules;
    for (const auto& module : *_iterable_25) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
void ModuleAnalyzer::keepStatementTypes(std::shared_ptr<::app_src_ast_::Block> block, std::shared_ptr<::app_src_ast_::ExportDeclaration> export_, std::shared_ptr<::app_src_ast_::ImportDeclaration> import_, std::shared_ptr<::app_src_ast_::MockImportDirective> mockImport, std::shared_ptr<::app_src_ast_::IfStatement> if_, std::shared_ptr<::app_src_ast_::CaseStatement> case_, std::shared_ptr<::app_src_ast_::WhileStatement> while_, std::shared_ptr<::app_src_ast_::ForStatement> for_, std::shared_ptr<::app_src_ast_::ForOfStatement> forOf, std::shared_ptr<::app_src_ast_::WithStatement> with_, std::shared_ptr<::app_src_ast_::ReturnStatement> return_, std::shared_ptr<::app_src_ast_::YieldStatement> yield_, std::shared_ptr<::app_src_ast_::BreakStatement> break_, std::shared_ptr<::app_src_ast_::ContinueStatement> continue_, std::shared_ptr<::app_src_ast_::ExpressionStatement> expression, std::shared_ptr<::app_src_ast_::DestructuringStatement> destructuring) {
}
std::string ModuleAnalyzer::resolveImportPath(std::shared_ptr<ModuleInfo> info, std::string specifier) {
    if (doof::is_null(info->mockRootPath)) {
        return this->resolver->resolve(info->path, specifier);
    }
    const auto root = findModule(doof::unwrap_optional(info->mockRootPath));
    if (doof::is_null(root) || (static_cast<int32_t>((root->mockImportDirectives)->size()) == 0)) {
        return this->resolver->resolve(info->path, specifier);
    }
    const auto sourceSpecifier = relativeModuleSpecifier(doof::unwrap_optional(info->mockRootPath), info->path);
    const auto replacement = findMockReplacement(root->mockImportDirectives, sourceSpecifier, specifier);
    if (doof::is_null(replacement)) {
        return this->resolver->resolve(info->path, specifier);
    }
    return this->resolver->resolve(doof::unwrap_optional(info->mockRootPath), replacement.value());
}
void ModuleAnalyzer::validateMockImportDirectives(std::shared_ptr<ModuleInfo> info, std::optional<std::string> inheritedMockRootPath) {
    if (static_cast<int32_t>((info->mockImportDirectives)->size()) == 0) {
        return;
    }
    if (!doof::string_endsWith(info->path, std::string(".test.do"))) {
        const auto& _iterable_26 = info->mockImportDirectives;
        for (const auto& directive : *_iterable_26) {
            addError(info, std::string("mock import directives are only valid in .test.do files"), directive->span);
        }
    }
    if ((!doof::is_null(inheritedMockRootPath)) && (inheritedMockRootPath != info->path)) {
        const auto& _iterable_27 = info->mockImportDirectives;
        for (const auto& directive : *_iterable_27) {
            addError(info, std::string("mock import directives are only valid in the root test file"), directive->span);
        }
    }
    auto sawOrdinaryStatement = false;
    const auto& _iterable_28 = info->program->statements;
    for (const auto& statement : *_iterable_28) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                const auto& directive = std::get<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject);
                if (sawOrdinaryStatement) {
                    addError(info, std::string("mock import directives must appear at the top of the file before other statements"), directive->span);
                }
        }
        else {
                (sawOrdinaryStatement = true);
        }
        }
    }
    const auto& _iterable_29 = info->mockImportDirectives;
    for (const auto& directive : *_iterable_29) {
        const auto& _iterable_30 = directive->mappings;
        for (const auto& mapping : *_iterable_30) {
            if (mapping->dependency == mapping->replacement) {
                addError(info, ((std::string("mock import cannot substitute \"") + mapping->dependency) + std::string("\" with itself")), mapping->span);
            }
        }
    }
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> collectMockImportDirectives(std::shared_ptr<::app_src_ast_::Program> program) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> directives = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>>(std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>{});
    const auto& _iterable_31 = program->statements;
    for (const auto& statement : *_iterable_31) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
                const auto& directive = std::get<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject);
                directives->push_back(directive);
        }
        else {
        }
        }
    }
    return directives;
}
std::string relativeModuleSpecifier(std::string fromModule, std::string toModule) {
    const auto fromComponents = parentPathComponents(doof::string_replaceAll(fromModule, std::string("\\"), std::string("/")));
    const auto toComponents = doof::string_split(moduleSpecifierPath(doof::string_replaceAll(toModule, std::string("\\"), std::string("/"))), std::string("/"));
    auto common = 0;
    while (((common < static_cast<int32_t>((fromComponents)->size())) && (common < static_cast<int32_t>((toComponents)->size()))) && ((*fromComponents)[common] == (*toComponents)[common])) {
        (common = (common + 1));
    }
    auto result = std::string("");
    for (int32_t ignored = common; ignored < static_cast<int32_t>((fromComponents)->size()); ++ignored) {
        (result = (result + std::string("../")));
    }
    for (int32_t index = common; index < static_cast<int32_t>((toComponents)->size()); ++index) {
        if ((result != std::string("")) && !doof::string_endsWith(result, std::string("/"))) {
            (result = (result + std::string("/")));
        }
        (result = (result + (*toComponents)[index]));
    }
    return (doof::string_startsWith(result, std::string(".")) ? result : (std::string("./") + result));
}
std::shared_ptr<std::vector<std::string>> parentPathComponents(std::string path) {
    const auto components = doof::string_split(path, std::string("/"));
    if (static_cast<int32_t>((components)->size()) > 0) {
        const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    }
    return components;
}
std::string moduleSpecifierPath(std::string path) {
    if (doof::string_endsWith(path, std::string("/index.do"))) {
        return doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 9));
    }
    if (doof::string_endsWith(path, std::string(".do"))) {
        return doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 3));
    }
    return path;
}
std::optional<std::string> findMockReplacement(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> directives, std::string sourceSpecifier, std::string dependencySpecifier) {
    const auto& _iterable_32 = directives;
    for (const auto& directive : *_iterable_32) {
        if (directive->sourcePattern != sourceSpecifier) {
            continue;
        }
        const auto& _iterable_33 = directive->mappings;
        for (const auto& mapping : *_iterable_33) {
            if (mapping->dependency == dependencySpecifier) {
                return mapping->replacement;
            }
        }
    }
    return std::nullopt;
}
std::shared_ptr<ModuleAnalyzer> createAnalyzer(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources) {
    return std::make_shared<ModuleAnalyzer>(std::make_shared<::app_src_resolver_::ModuleResolver>(sources, ::app_src_resolver_::noSourceLoader, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{})), std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
std::shared_ptr<ModuleAnalyzer> createAnalyzerWithLoader(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader) {
    return std::make_shared<ModuleAnalyzer>(std::make_shared<::app_src_resolver_::ModuleResolver>(sources, loader, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{})), std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
std::shared_ptr<::app_src_semantic_::Symbol> findSymbol(std::shared_ptr<ModuleInfo> info, std::string name) {
    const auto& _iterable_34 = info->symbols;
    for (const auto& symbol : *_iterable_34) {
        if (symbol->name == name) {
            return symbol;
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Symbol> findExport(std::shared_ptr<ModuleInfo> info, std::string name) {
    const auto& _iterable_35 = info->exports;
    for (const auto& symbol : *_iterable_35) {
        if (symbol->name == name) {
            return symbol;
        }
    }
    return nullptr;
}
bool isBuiltin(std::string name) {
    if ((name == std::string("JsonSerializable")) || (name == std::string("Reflectable"))) {
        return true;
    }
    const auto& _iterable_36 = BUILTIN_TYPES;
    for (const auto& builtin : *_iterable_36) {
        if (builtin == name) {
            return true;
        }
    }
    return false;
}
bool contains(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto& _iterable_37 = values;
    for (const auto& item : *_iterable_37) {
        if (item == value) {
            return true;
        }
    }
    return false;
}
void addError(std::shared_ptr<ModuleInfo> info, std::string message, ::app_src_ast_::SourceSpan span) {
    info->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, semanticSpan(span), info->path, std::string("")));
}
::app_src_semantic_::SemanticSpan semanticSpan(::app_src_ast_::SourceSpan span) {
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
::app_src_semantic_::SemanticSpan emptySemanticSpan() {
    auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
    return ::app_src_semantic_::SemanticSpan{zero, zero};
}
}
