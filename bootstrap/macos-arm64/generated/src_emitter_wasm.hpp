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
namespace app_src_ast_ { struct ExportDeclaration; }
namespace app_src_ast_ { struct FunctionDeclaration; }
namespace app_src_ast_ { struct Parameter; }
namespace app_src_ast_ { struct Program; }
namespace app_src_analyzer_ { struct AnalysisResult; }
namespace app_src_analyzer_ { struct ModuleInfo; }
namespace app_src_emitter_context_ { struct EmitContext; }
namespace app_src_semantic_ { struct ArrayResolvedType; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct EnumType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct JsonValueResolvedType; }
namespace app_src_semantic_ { struct NullType; }
namespace app_src_semantic_ { struct PrimitiveType; }
namespace app_src_semantic_ { struct ResultResolvedType; }
namespace app_src_semantic_ { struct UnionResolvedType; }
namespace app_src_semantic_ { struct VoidType; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_wasm_ {
    struct WasmEmission;
}

#include "src_ast.hpp"
#include "src_analyzer.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_names.hpp"
#include "src_emitter_types.hpp"
#include "src_json_semantics.hpp"
#include "src_semantic.hpp"

namespace app_src_emitter_wasm_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct WasmEmission : public std::enable_shared_from_this<WasmEmission> {
    std::string source;
    std::shared_ptr<std::vector<std::string>> exportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    WasmEmission(std::string source, std::shared_ptr<std::vector<std::string>> exportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : source(source), exportNames(exportNames) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<WasmEmission>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    doof::Result<std::shared_ptr<WasmEmission>, std::string> emitWasmSupport(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string entry);
    void collectExportedFunctions(std::shared_ptr<::app_src_analyzer_::ModuleInfo> info, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>> result);
    bool moduleExportsFunction(std::shared_ptr<::app_src_analyzer_::ModuleInfo> info, std::string name);
    doof::Result<void, std::string> validateWasmFunction(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis);
    bool isWasmJsonType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis);
    std::string wasmPreamble(std::shared_ptr<::app_src_analyzer_::ModuleInfo> info);
    std::string emitWasmWrapper(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string exportName, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitParameter(std::shared_ptr<::app_src_ast_::Parameter> parameter, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
    std::shared_ptr<::app_src_ast_::ClassDeclaration> findClass(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::shared_ptr<::app_src_semantic_::ClassType> type_);
}

namespace app_src_emitter_wasm_ {
}
