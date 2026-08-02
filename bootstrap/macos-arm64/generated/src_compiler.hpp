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
namespace app_src_emitter_module_ { struct ModuleEmissionCacheKey; }
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
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sourceFiles;
    std::shared_ptr<std::vector<std::string>> resolutionProbes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    Compilation(std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> emission, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sourceFiles, std::shared_ptr<std::vector<std::string>> resolutionProbes) : emission(emission), diagnostics(diagnostics), sourceFiles(sourceFiles), resolutionProbes(resolutionProbes) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Compilation>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<Compilation> compile(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, bool coverage = false);
    std::shared_ptr<Compilation> compileWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), const std::string& entryMode = std::string("executable"), bool coverage = false, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), const std::string& emissionConfigurationFingerprint = std::string(""));
    std::shared_ptr<Compilation> checkWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::string& entryMode = std::string("executable"));
    std::shared_ptr<Compilation> compileInternal(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode = std::string("executable"), bool coverage = false, bool emit = true, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), const std::string& emissionConfigurationFingerprint = std::string(""));
    void checkModuleDependencies(const std::string& path, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<::app_src_checker_::ModuleChecker>& checker, const std::shared_ptr<std::vector<std::string>>& checkedPaths, const std::shared_ptr<std::vector<std::string>>& visitingPaths, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics);
    bool containsPath(const std::shared_ptr<std::vector<std::string>>& paths, const std::string& path);
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> findAnalysisModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path);
}

namespace app_src_compiler_ {
}
