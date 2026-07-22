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
namespace app_src_ast_ { struct Program; }
namespace app_src_ast_ { struct SourceSpan; }
namespace app_src_semantic_ { struct ActorType; }
namespace app_src_semantic_ { struct ArrayResolvedType; }
namespace app_src_semantic_ { struct ClassMetadataResolvedType; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct EnumType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct ImportBinding; }
namespace app_src_semantic_ { struct InterfaceType; }
namespace app_src_semantic_ { struct JsonValueResolvedType; }
namespace app_src_semantic_ { struct MapResolvedType; }
namespace app_src_semantic_ { struct MethodReflectionResolvedType; }
namespace app_src_semantic_ { struct NamespaceBinding; }
namespace app_src_semantic_ { struct NoneType; }
namespace app_src_semantic_ { struct PrimitiveType; }
namespace app_src_semantic_ { struct PromiseType; }
namespace app_src_semantic_ { struct RangeResolvedType; }
namespace app_src_semantic_ { struct ResultResolvedType; }
namespace app_src_semantic_ { struct SetResolvedType; }
namespace app_src_semantic_ { struct StreamResolvedType; }
namespace app_src_semantic_ { struct Symbol; }
namespace app_src_semantic_ { struct TupleResolvedType; }
namespace app_src_semantic_ { struct TypeParameterType; }
namespace app_src_semantic_ { struct TypeSubstitution; }
namespace app_src_semantic_ { struct UnionResolvedType; }
namespace app_src_semantic_ { struct UnknownType; }
namespace app_src_semantic_ { struct WeakResolvedType; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_context_ {
    struct EmitModuleSurface;
    struct SourceLocationSpanOverride;
    struct EmitContext;
}

#include "src_ast.hpp"
#include "src_semantic.hpp"

namespace app_src_emitter_context_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct EmitModuleSurface : public std::enable_shared_from_this<EmitModuleSurface> {
    std::string path;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> exports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports;
    std::shared_ptr<std::vector<std::string>> genericTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> genericFunctions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    EmitModuleSurface(std::string path, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> exports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports, std::shared_ptr<std::vector<std::string>> genericTypes, std::shared_ptr<std::vector<std::string>> genericFunctions) : path(path), exports(exports), imports(imports), genericTypes(genericTypes), genericFunctions(genericFunctions) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<EmitModuleSurface>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct SourceLocationSpanOverride : public std::enable_shared_from_this<SourceLocationSpanOverride> {
    ::app_src_ast_::SourceSpan span;
    SourceLocationSpanOverride(::app_src_ast_::SourceSpan span) : span(span) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<SourceLocationSpanOverride>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct EmitContext : public std::enable_shared_from_this<EmitContext> {
    std::string modulePath = std::string("");
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports;
    std::shared_ptr<std::vector<std::shared_ptr<EmitModuleSurface>>> moduleSurfaces = std::make_shared<std::vector<std::shared_ptr<EmitModuleSurface>>>(std::vector<std::shared_ptr<EmitModuleSurface>>{});
    std::string currentClass = std::string("");
    bool currentClassNative = false;
    bool currentFunctionStatic = false;
    std::string currentReturnErrorType = std::string("");
    std::string currentFunctionName = std::string("");
    bool inValueYieldBlock = false;
    std::string catchVarName = std::string("");
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> catchResultType = std::monostate{};
    std::shared_ptr<SourceLocationSpanOverride> sourceLocationSpanOverride = nullptr;
    std::shared_ptr<std::vector<std::string>> genericTypeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution = nullptr;
    std::shared_ptr<std::vector<std::string>> concreteFunctionNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> concreteFunctionKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> concreteClassNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> concreteClassKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> nativeTemplateClassKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> concreteMethodNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> concreteMethodKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> concreteInterfaceNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> concreteInterfaceKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> capturedMutables = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    int32_t tryCounter = 0;
    bool coverageEnabled = false;
    int32_t coverageModuleId = -1;
    std::shared_ptr<std::vector<int32_t>> coverageInstrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    EmitContext(std::string modulePath, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports, std::shared_ptr<std::vector<std::shared_ptr<EmitModuleSurface>>> moduleSurfaces, std::string currentClass, bool currentClassNative, bool currentFunctionStatic, std::string currentReturnErrorType, std::string currentFunctionName, bool inValueYieldBlock, std::string catchVarName, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> catchResultType, std::shared_ptr<SourceLocationSpanOverride> sourceLocationSpanOverride, std::shared_ptr<std::vector<std::string>> genericTypeParams, std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution, std::shared_ptr<std::vector<std::string>> concreteFunctionNames, std::shared_ptr<std::vector<std::string>> concreteFunctionKeys, std::shared_ptr<std::vector<std::string>> concreteClassNames, std::shared_ptr<std::vector<std::string>> concreteClassKeys, std::shared_ptr<std::vector<std::string>> nativeTemplateClassKeys, std::shared_ptr<std::vector<std::string>> concreteMethodNames, std::shared_ptr<std::vector<std::string>> concreteMethodKeys, std::shared_ptr<std::vector<std::string>> concreteInterfaceNames, std::shared_ptr<std::vector<std::string>> concreteInterfaceKeys, std::shared_ptr<std::vector<std::string>> capturedMutables, int32_t tryCounter, bool coverageEnabled, int32_t coverageModuleId, std::shared_ptr<std::vector<int32_t>> coverageInstrumentedLines) : modulePath(modulePath), allPrograms(allPrograms), namespaceImports(namespaceImports), imports(imports), moduleSurfaces(moduleSurfaces), currentClass(currentClass), currentClassNative(currentClassNative), currentFunctionStatic(currentFunctionStatic), currentReturnErrorType(currentReturnErrorType), currentFunctionName(currentFunctionName), inValueYieldBlock(inValueYieldBlock), catchVarName(catchVarName), catchResultType(catchResultType), sourceLocationSpanOverride(sourceLocationSpanOverride), genericTypeParams(genericTypeParams), substitution(substitution), concreteFunctionNames(concreteFunctionNames), concreteFunctionKeys(concreteFunctionKeys), concreteClassNames(concreteClassNames), concreteClassKeys(concreteClassKeys), nativeTemplateClassKeys(nativeTemplateClassKeys), concreteMethodNames(concreteMethodNames), concreteMethodKeys(concreteMethodKeys), concreteInterfaceNames(concreteInterfaceNames), concreteInterfaceKeys(concreteInterfaceKeys), capturedMutables(capturedMutables), tryCounter(tryCounter), coverageEnabled(coverageEnabled), coverageModuleId(coverageModuleId), coverageInstrumentedLines(coverageInstrumentedLines) {}
};
    void recordCoverageLine(std::shared_ptr<EmitContext> context, int32_t line);
    bool isCapturedMutable(std::shared_ptr<EmitContext> context, std::string name);
    std::shared_ptr<EmitContext> createEmitContext(std::shared_ptr<::app_src_ast_::Program> program);
    std::shared_ptr<EmitContext> createEmitContextForPrograms(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs);
    std::shared_ptr<EmitContext> createEmitContextForModule(std::shared_ptr<::app_src_ast_::Program> program, std::string modulePath, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{}));
}

namespace app_src_emitter_context_ {
}
