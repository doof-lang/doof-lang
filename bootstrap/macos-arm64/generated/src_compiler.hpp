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
namespace app_src_analyzer_ { struct AnalysisResult; }
namespace app_src_analyzer_ { struct ModuleInfo; }
namespace app_src_emitter_module_ { struct ModuleGraphEmission; }
namespace app_src_emitter_names_ { struct ModuleNamespaceMapping; }
namespace app_src_checker_ { struct ModuleChecker; }
namespace app_src_semantic_ { struct CheckResult; }
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct SemanticLocation; }
namespace app_src_semantic_ { struct SemanticSpan; }
namespace app_src_semantic_ { struct SourceFile; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_compiler_ {
    struct Compilation;
}

#include "src_analyzer.hpp"
#include "src_emitter_module.hpp"
#include "src_emitter_monomorphize.hpp"
#include "src_emitter_wasm.hpp"
#include "src_emitter_names.hpp"
#include "src_checker.hpp"
#include "src_diagnostics.hpp"
#include "src_resolver.hpp"
#include "src_semantic.hpp"

namespace app_src_compiler_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct Compilation : public std::enable_shared_from_this<Compilation> {
    std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> emission;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    Compilation(std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> emission, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : emission(emission), diagnostics(diagnostics) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Compilation>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<Compilation> compile(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, std::string entry, bool coverage = false);
    std::shared_ptr<Compilation> compileWithLoader(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, std::string entry, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), std::string entryMode = std::string("executable"), bool coverage = false);
    std::shared_ptr<Compilation> compileInternal(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, std::string entry, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings, std::string entryMode = std::string("executable"), bool coverage = false);
    void checkModuleDependencies(std::string path, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<::app_src_checker_::ModuleChecker> checker, std::shared_ptr<std::vector<std::string>> checkedPaths, std::shared_ptr<std::vector<std::string>> visitingPaths, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    bool containsPath(std::shared_ptr<std::vector<std::string>> paths, std::string path);
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> findAnalysisModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path);
}

namespace app_src_compiler_ {
}
