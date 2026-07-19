#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace app_src_parser_ { struct Parser; }
namespace app_src_resolver_ { struct ModuleResolver; }
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct ImportBinding; }
namespace app_src_semantic_ { struct NamespaceBinding; }
namespace app_src_semantic_ { struct SemanticLocation; }
namespace app_src_semantic_ { struct SemanticSpan; }
namespace app_src_semantic_ { struct SourceFile; }
namespace app_src_semantic_ { struct Symbol; }
namespace app_src_ast_ { struct ArrayType; }
namespace app_src_ast_ { struct AstLocation; }
namespace app_src_ast_ { struct ClassDeclaration; }
namespace app_src_ast_ { struct ConstDeclaration; }
namespace app_src_ast_ { struct EnumDeclaration; }
namespace app_src_ast_ { struct Block; }
namespace app_src_ast_ { struct ExportDeclaration; }
namespace app_src_ast_ { struct ExportList; }
namespace app_src_ast_ { struct ForOfStatement; }
namespace app_src_ast_ { struct ForStatement; }
namespace app_src_ast_ { struct FunctionDeclaration; }
namespace app_src_ast_ { struct AstFunctionType; }
namespace app_src_ast_ { struct IfStatement; }
namespace app_src_ast_ { struct ImmutableBinding; }
namespace app_src_ast_ { struct InterfaceDeclaration; }
namespace app_src_ast_ { struct LetDeclaration; }
namespace app_src_ast_ { struct NamedImport; }
namespace app_src_ast_ { struct NamedType; }
namespace app_src_ast_ { struct NamespaceImport; }
namespace app_src_ast_ { struct ReadonlyDeclaration; }
namespace app_src_ast_ { struct ReturnStatement; }
namespace app_src_ast_ { struct YieldStatement; }
namespace app_src_ast_ { struct WhileStatement; }
namespace app_src_ast_ { struct WithStatement; }
namespace app_src_ast_ { struct BreakStatement; }
namespace app_src_ast_ { struct ContinueStatement; }
namespace app_src_ast_ { struct ExpressionStatement; }
namespace app_src_ast_ { struct DestructuringStatement; }
namespace app_src_ast_ { struct ImportDeclaration; }
namespace app_src_ast_ { struct TypeAliasDeclaration; }
namespace app_src_ast_ { struct UnionType; }
namespace app_src_ast_ { struct CaseStatement; }
namespace app_src_ast_ { struct MockImportDirective; }
namespace app_src_ast_ { struct WeakType; }
namespace app_src_ast_ { struct YieldBlockAssignmentStatement; }
namespace app_src_ast_ { struct TypeParameterConstraint; }
namespace app_src_ast_ { struct Program; }
namespace app_src_ast_ { struct SourceSpan; }
namespace app_src_ast_ { struct TryStatement; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_analyzer_ {
    struct ModuleInfo;
    struct AnalysisResult;
    struct ModuleAnalyzer;
}

#include "src_parser.hpp"
#include "src_resolver.hpp"
#include "src_semantic.hpp"
#include "src_ast.hpp"

namespace app_src_analyzer_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ModuleInfo : public std::enable_shared_from_this<ModuleInfo> {
    std::string path;
    std::shared_ptr<::app_src_ast_::Program> program;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> symbols;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> exports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports;
    std::shared_ptr<std::vector<std::string>> reExports = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> mockImportDirectives;
    std::optional<std::string> mockRootPath = std::nullopt;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    ModuleInfo(std::string path, std::shared_ptr<::app_src_ast_::Program> program, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> symbols, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> exports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports, std::shared_ptr<std::vector<std::string>> reExports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> mockImportDirectives, std::optional<std::string> mockRootPath, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : path(path), program(program), symbols(symbols), exports(exports), imports(imports), namespaceImports(namespaceImports), reExports(reExports), mockImportDirectives(mockImportDirectives), mockRootPath(mockRootPath), diagnostics(diagnostics) {}
};
    struct AnalysisResult : public std::enable_shared_from_this<AnalysisResult> {
    std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules = std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{});
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    AnalysisResult(std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : modules(modules), diagnostics(diagnostics) {}
};
    struct ModuleAnalyzer : public std::enable_shared_from_this<ModuleAnalyzer> {
    std::shared_ptr<::app_src_resolver_::ModuleResolver> resolver;
    std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules = std::make_shared<std::vector<std::shared_ptr<ModuleInfo>>>(std::vector<std::shared_ptr<ModuleInfo>>{});
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    std::shared_ptr<std::vector<std::string>> inProgress = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    ModuleAnalyzer(std::shared_ptr<::app_src_resolver_::ModuleResolver> resolver, std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics, std::shared_ptr<std::vector<std::string>> inProgress) : resolver(resolver), modules(modules), diagnostics(diagnostics), inProgress(inProgress) {}
    std::shared_ptr<AnalysisResult> analyze(std::string entry);
    std::shared_ptr<ModuleInfo> analyzeModule(std::string path, std::optional<std::string> inheritedMockRootPath);
    void collectSymbols(std::shared_ptr<ModuleInfo> info);
    void decorateDeclarationSymbol(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<::app_src_semantic_::Symbol> symbol);
    std::shared_ptr<::app_src_semantic_::Symbol> symbolFor(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::string module);
    std::shared_ptr<::app_src_semantic_::Symbol> exportedSymbol(std::shared_ptr<::app_src_semantic_::Symbol> symbol, std::string exportedName);
    void resolveImports(std::shared_ptr<ModuleInfo> info);
    void resolveExportLists(std::shared_ptr<ModuleInfo> info);
    void resolveNamedTypes(std::shared_ptr<ModuleInfo> info);
    void visitStatementTypes(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<ModuleInfo> info);
    void visitFunctionTypes(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::shared_ptr<ModuleInfo> info, std::shared_ptr<std::vector<std::string>> ownerTypeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    void visitTypeParameterConstraints(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints, std::shared_ptr<ModuleInfo> info, std::shared_ptr<std::vector<std::string>> typeParams);
    void visitType(std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::shared_ptr<ModuleInfo> info, std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    bool containsTypeParam(std::shared_ptr<std::vector<std::string>> typeParams, std::string name);
    std::shared_ptr<ModuleInfo> findModule(std::string path);
    void keepStatementTypes(std::shared_ptr<::app_src_ast_::Block> block = nullptr, std::shared_ptr<::app_src_ast_::ExportDeclaration> export_ = nullptr, std::shared_ptr<::app_src_ast_::ImportDeclaration> import_ = nullptr, std::shared_ptr<::app_src_ast_::MockImportDirective> mockImport = nullptr, std::shared_ptr<::app_src_ast_::IfStatement> if_ = nullptr, std::shared_ptr<::app_src_ast_::CaseStatement> case_ = nullptr, std::shared_ptr<::app_src_ast_::WhileStatement> while_ = nullptr, std::shared_ptr<::app_src_ast_::ForStatement> for_ = nullptr, std::shared_ptr<::app_src_ast_::ForOfStatement> forOf = nullptr, std::shared_ptr<::app_src_ast_::WithStatement> with_ = nullptr, std::shared_ptr<::app_src_ast_::ReturnStatement> return_ = nullptr, std::shared_ptr<::app_src_ast_::YieldStatement> yield_ = nullptr, std::shared_ptr<::app_src_ast_::BreakStatement> break_ = nullptr, std::shared_ptr<::app_src_ast_::ContinueStatement> continue_ = nullptr, std::shared_ptr<::app_src_ast_::ExpressionStatement> expression = nullptr, std::shared_ptr<::app_src_ast_::DestructuringStatement> destructuring = nullptr);
    std::string resolveImportPath(std::shared_ptr<ModuleInfo> info, std::string specifier);
    void validateMockImportDirectives(std::shared_ptr<ModuleInfo> info, std::optional<std::string> inheritedMockRootPath);
};
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> collectMockImportDirectives(std::shared_ptr<::app_src_ast_::Program> program);
    std::string relativeModuleSpecifier(std::string fromModule, std::string toModule);
    std::shared_ptr<std::vector<std::string>> parentPathComponents(std::string path);
    std::string moduleSpecifierPath(std::string path);
    std::optional<std::string> findMockReplacement(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> directives, std::string sourceSpecifier, std::string dependencySpecifier);
    std::shared_ptr<ModuleAnalyzer> createAnalyzer(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources);
    std::shared_ptr<ModuleAnalyzer> createAnalyzerWithLoader(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader);
    std::shared_ptr<::app_src_semantic_::Symbol> findSymbol(std::shared_ptr<ModuleInfo> info, std::string name);
    std::shared_ptr<::app_src_semantic_::Symbol> findExport(std::shared_ptr<ModuleInfo> info, std::string name);
    bool isBuiltin(std::string name);
    bool contains(std::shared_ptr<std::vector<std::string>> values, std::string value);
    void addError(std::shared_ptr<ModuleInfo> info, std::string message, ::app_src_ast_::SourceSpan span);
    ::app_src_semantic_::SemanticSpan semanticSpan(::app_src_ast_::SourceSpan span);
    ::app_src_semantic_::SemanticSpan emptySemanticSpan();
}

namespace app_src_analyzer_ {
}
