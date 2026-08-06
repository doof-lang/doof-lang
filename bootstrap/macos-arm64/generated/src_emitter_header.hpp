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
namespace app_src_ast_ { struct EnumDeclaration; }
namespace app_src_ast_ { struct ExportDeclaration; }
namespace app_src_ast_ { struct FunctionDeclaration; }
namespace app_src_ast_ { struct InterfaceDeclaration; }
namespace app_src_ast_ { struct ImmutableBinding; }
namespace app_src_ast_ { struct Program; }
namespace app_src_ast_ { struct ReadonlyDeclaration; }
namespace app_src_ast_ { struct TypeAliasDeclaration; }
namespace app_src_emitter_context_ { struct EmitContext; }
namespace app_src_emitter_context_ { struct EmitModuleSurface; }
namespace app_src_semantic_ { struct ArrayResolvedType; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct EnumType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct ImportBinding; }
namespace app_src_semantic_ { struct InterfaceType; }
namespace app_src_semantic_ { struct MapResolvedType; }
namespace app_src_semantic_ { struct PrimitiveType; }
namespace app_src_semantic_ { struct ResultResolvedType; }
namespace app_src_semantic_ { struct SetResolvedType; }
namespace app_src_semantic_ { struct StreamResolvedType; }
namespace app_src_semantic_ { struct Symbol; }
namespace app_src_semantic_ { struct TupleResolvedType; }
namespace app_src_semantic_ { struct UnionResolvedType; }
namespace app_src_semantic_ { struct WeakResolvedType; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_header_ {
    struct HeaderPlan;
}

#include "src_ast.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_decl.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_types.hpp"
#include "src_semantic.hpp"
#include "src_emitter_names.hpp"

namespace app_src_emitter_header_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct HeaderPlan : public std::enable_shared_from_this<HeaderPlan> {
    std::shared_ptr<std::vector<std::string>> functionSignatures = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> nativeAdapterSignatures = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> genericFunctionDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> earlyModuleValueDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> moduleValueDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> earlyClassDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> classDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> interfaceAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> enumDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> typeAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> classForwardDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> typeOnlyForwardDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> typeOnlyModuleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> moduleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> nativeIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> nativeAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> nativeNamespaces = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    bool hasMain = false;
    bool mainReturnsInt = false;
    bool mainAcceptsArgs = false;
    HeaderPlan(std::shared_ptr<std::vector<std::string>> functionSignatures = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> nativeAdapterSignatures = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> genericFunctionDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> earlyModuleValueDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> moduleValueDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> earlyClassDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> classDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> interfaceAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> enumDefinitions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> typeAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> classForwardDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> typeOnlyForwardDeclarations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> typeOnlyModuleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> moduleIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> nativeIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> nativeAliases = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> nativeNamespaces = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool hasMain = false, bool mainReturnsInt = false, bool mainAcceptsArgs = false) : functionSignatures(functionSignatures), nativeAdapterSignatures(nativeAdapterSignatures), genericFunctionDefinitions(genericFunctionDefinitions), earlyModuleValueDeclarations(earlyModuleValueDeclarations), moduleValueDeclarations(moduleValueDeclarations), earlyClassDefinitions(earlyClassDefinitions), classDefinitions(classDefinitions), interfaceAliases(interfaceAliases), enumDefinitions(enumDefinitions), typeAliases(typeAliases), classForwardDeclarations(classForwardDeclarations), typeOnlyForwardDeclarations(typeOnlyForwardDeclarations), typeOnlyModuleIncludes(typeOnlyModuleIncludes), moduleIncludes(moduleIncludes), nativeIncludes(nativeIncludes), nativeAliases(nativeAliases), nativeNamespaces(nativeNamespaces), hasMain(hasMain), mainReturnsInt(mainReturnsInt), mainAcceptsArgs(mainAcceptsArgs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<HeaderPlan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<HeaderPlan> planHeader(const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::shared_ptr<HeaderPlan> planHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    void collectNativeModuleSurfaceAliases(const std::string& modulePath, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    bool surfaceTypeIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>& surface, const std::string& name);
    bool isNativeAliasType(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol);
    void collect(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    bool classCanEmitBeforeModuleIncludes(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_);
    bool typeNeedsCompleteNominalDefinition(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_);
    bool isNativeTemplateClass(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& name);
    void collectNativeClassAliases(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    void collectNativeTypeAliases(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    bool surfaceSymbolIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol);
    bool surfaceFunctionIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol);
    void addNativeSymbolAlias(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan);
    std::string renderHeader(const std::shared_ptr<HeaderPlan>& plan, const std::string& guardName);
    void collectModuleValueDeclaration(const std::shared_ptr<HeaderPlan>& plan, const std::string& declaration, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_);
    bool moduleValueDeclarationNeedsIncludes(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_);
    std::string emitModuleValueDeclaration(const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    void addUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
    bool hasNonTypeOnlyImport(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>& imports, const std::string& sourceModule);
    bool containsValue(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
    std::string nativeNamespace(const std::string& cppName);
    std::string emitEnumDeclaration(const std::shared_ptr<::app_src_ast_::EnumDeclaration>& declaration, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::string emitTypeAlias(const std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>& alias, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    bool functionReturnsInt(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn);
}

namespace app_src_emitter_header_ {
}
