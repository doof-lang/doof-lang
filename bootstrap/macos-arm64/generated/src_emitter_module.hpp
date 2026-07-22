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
namespace app_src_ast_ { struct ClassDeclaration; }
namespace app_src_ast_ { struct ConstDeclaration; }
namespace app_src_ast_ { struct ExportDeclaration; }
namespace app_src_ast_ { struct FunctionDeclaration; }
namespace app_src_ast_ { struct ImmutableBinding; }
namespace app_src_ast_ { struct InterfaceDeclaration; }
namespace app_src_ast_ { struct LetDeclaration; }
namespace app_src_ast_ { struct Program; }
namespace app_src_ast_ { struct ReadonlyDeclaration; }
namespace app_src_ast_ { struct TypeAliasDeclaration; }
namespace app_src_analyzer_ { struct AnalysisResult; }
namespace app_src_analyzer_ { struct ModuleInfo; }
namespace app_src_emitter_context_ { struct EmitContext; }
namespace app_src_emitter_context_ { struct EmitModuleSurface; }
namespace app_src_emitter_header_ { struct HeaderPlan; }
namespace app_src_emitter_monomorphize_ { struct ClassInstantiation; }
namespace app_src_emitter_monomorphize_ { struct FunctionInstantiation; }
namespace app_src_emitter_monomorphize_ { struct InstantiationPlan; }
namespace app_src_emitter_monomorphize_ { struct MethodInstantiation; }
namespace app_src_semantic_ { struct ArrayResolvedType; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct ImportBinding; }
namespace app_src_semantic_ { struct InterfaceType; }
namespace app_src_semantic_ { struct MapResolvedType; }
namespace app_src_semantic_ { struct NamespaceBinding; }
namespace app_src_semantic_ { struct ResultResolvedType; }
namespace app_src_semantic_ { struct SetResolvedType; }
namespace app_src_semantic_ { struct StreamResolvedType; }
namespace app_src_semantic_ { struct TupleResolvedType; }
namespace app_src_semantic_ { struct TypeSubstitution; }
namespace app_src_semantic_ { struct UnionResolvedType; }
namespace app_src_semantic_ { struct WeakResolvedType; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_module_ {
    struct ModulePlan;
    struct ModuleGraphPlan;
    struct ModuleEmission;
    struct CoverageModuleMetadata;
    struct ModuleGraphEmission;
    struct CxxModuleEmitter;
}

#include "src_ast.hpp"
#include "src_analyzer.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_decl.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_metadata.hpp"
#include "src_emitter_header.hpp"
#include "src_emitter_monomorphize.hpp"
#include "src_emitter_names.hpp"
#include "src_semantic.hpp"

namespace app_src_emitter_module_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ModulePlan : public std::enable_shared_from_this<ModulePlan> {
    std::string path;
    std::string namespaceName;
    std::string headerName;
    std::string sourceName;
    std::shared_ptr<std::vector<std::string>> includes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    ModulePlan(std::string path, std::string namespaceName, std::string headerName, std::string sourceName, std::shared_ptr<std::vector<std::string>> includes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : path(path), namespaceName(namespaceName), headerName(headerName), sourceName(sourceName), includes(includes) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModulePlan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ModuleGraphPlan : public std::enable_shared_from_this<ModuleGraphPlan> {
    std::shared_ptr<std::vector<std::shared_ptr<ModulePlan>>> modules = std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{});
    ModuleGraphPlan(std::shared_ptr<std::vector<std::shared_ptr<ModulePlan>>> modules = std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{})) : modules(modules) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModuleGraphPlan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ModuleEmission : public std::enable_shared_from_this<ModuleEmission> {
    std::string modulePath;
    std::string header;
    std::string source;
    std::string headerName;
    std::string sourceName;
    int32_t coverageModuleId = -1;
    std::shared_ptr<std::vector<int32_t>> instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    ModuleEmission(std::string modulePath, std::string header, std::string source, std::string headerName, std::string sourceName, int32_t coverageModuleId = -1, std::shared_ptr<std::vector<int32_t>> instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{})) : modulePath(modulePath), header(header), source(source), headerName(headerName), sourceName(sourceName), coverageModuleId(coverageModuleId), instrumentedLines(instrumentedLines) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModuleEmission>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct CoverageModuleMetadata : public std::enable_shared_from_this<CoverageModuleMetadata> {
    int32_t moduleId;
    std::string modulePath;
    std::shared_ptr<std::vector<int32_t>> instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    CoverageModuleMetadata(int32_t moduleId, std::string modulePath, std::shared_ptr<std::vector<int32_t>> instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{})) : moduleId(moduleId), modulePath(modulePath), instrumentedLines(instrumentedLines) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<CoverageModuleMetadata>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ModuleGraphEmission : public std::enable_shared_from_this<ModuleGraphEmission> {
    std::shared_ptr<std::vector<std::shared_ptr<ModuleEmission>>> modules = std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{});
    std::shared_ptr<std::vector<std::shared_ptr<CoverageModuleMetadata>>> coverageModules = std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(std::vector<std::shared_ptr<CoverageModuleMetadata>>{});
    std::string wasmSupportSource = std::string("");
    std::shared_ptr<std::vector<std::string>> wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    ModuleGraphEmission(std::shared_ptr<std::vector<std::shared_ptr<ModuleEmission>>> modules = std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{}), std::shared_ptr<std::vector<std::shared_ptr<CoverageModuleMetadata>>> coverageModules = std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(std::vector<std::shared_ptr<CoverageModuleMetadata>>{}), std::string wasmSupportSource = std::string(""), std::shared_ptr<std::vector<std::string>> wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : modules(modules), coverageModules(coverageModules), wasmSupportSource(wasmSupportSource), wasmExportNames(wasmExportNames) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModuleGraphEmission>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct CxxModuleEmitter : public std::enable_shared_from_this<CxxModuleEmitter> {
    std::string moduleName;
    std::string headerNameOverride = std::string("");
    std::string sourceNameOverride = std::string("");
    std::string namespaceNameOverride = std::string("");
    std::string modulePath = std::string("");
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> moduleSurfaces;
    std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations = nullptr;
    int32_t coverageModuleId = -1;
    CxxModuleEmitter(std::string moduleName, std::string headerNameOverride, std::string sourceNameOverride, std::string namespaceNameOverride, std::string modulePath, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> moduleSurfaces, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations, int32_t coverageModuleId) : moduleName(moduleName), headerNameOverride(headerNameOverride), sourceNameOverride(sourceNameOverride), namespaceNameOverride(namespaceNameOverride), modulePath(modulePath), allPrograms(allPrograms), namespaceImports(namespaceImports), imports(imports), moduleSurfaces(moduleSurfaces), instantiations(instantiations), coverageModuleId(coverageModuleId) {}
    std::shared_ptr<ModuleEmission> emit(std::shared_ptr<::app_src_ast_::Program> program, std::shared_ptr<std::vector<std::string>> moduleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::string entryMode = std::string("executable"));
    std::shared_ptr<ModuleEmission> emitPlanned(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan, std::string entryMode, std::shared_ptr<std::vector<std::string>> moduleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
};
    std::shared_ptr<ModuleGraphPlan> planModuleGraph(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
    void addInclude(std::shared_ptr<ModulePlan> module, std::string sourceModule);
    std::string concreteImplementationIncludes(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> plan, std::shared_ptr<std::vector<std::string>> existingIncludes);
    bool containsString(std::shared_ptr<std::vector<std::string>> values, std::string value);
    std::string emitImportedNamespaces(std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    void addNamespace(std::shared_ptr<std::vector<std::string>> namespaces, std::string namespace_);
    std::shared_ptr<ModuleGraphEmission> emitModuleGraph(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string entry = std::string(""), std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations = nullptr, std::string entryMode = std::string("executable"), bool coverage = false);
    bool isCoverageEligible(std::string modulePath);
    std::shared_ptr<std::vector<int32_t>> sortedCoverageLines(std::shared_ptr<std::vector<int32_t>> lines);
    void configureInstantiationRegistry(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> plan);
    void addConcreteHeaderDeclarations(std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations);
    void addConcreteTypeForwardDeclarations(std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_);
    std::string emitConcreteFunctions(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations);
    void withInstantiation(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments);
    void clearInstantiation(std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> emitModuleSurfaces(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
    void collectGenericSurfaceSymbols(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<std::vector<std::string>> typeNames, std::shared_ptr<std::vector<std::string>> functionNames);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> infoNamespaceImports(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> infoImports(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path);
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> findGraphModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path);
    std::shared_ptr<ModuleEmission> emitModule(std::shared_ptr<::app_src_ast_::Program> program, std::string moduleName = std::string("main"));
    std::string emitSourceStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitNativeClassMethods(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitNativeClassMethodsForStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitMainWrapper(std::string moduleName, std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan);
    std::string emitAppEntryWrapper(std::string moduleName, std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan);
}

namespace app_src_emitter_module_ {
}
