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
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct Scope; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_checker_state_ {
    struct CheckerState;
}

#include "src_analyzer.hpp"
#include "src_semantic.hpp"

namespace app_src_checker_state_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct CheckerState : public std::enable_shared_from_this<CheckerState> {
    std::shared_ptr<::app_src_analyzer_::AnalysisResult> result;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> info = nullptr;
    std::shared_ptr<::app_src_semantic_::Scope> moduleScope = nullptr;
    CheckerState(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics, std::shared_ptr<::app_src_analyzer_::ModuleInfo> info, std::shared_ptr<::app_src_semantic_::Scope> moduleScope) : result(result), diagnostics(diagnostics), info(info), moduleScope(moduleScope) {}
};
}

namespace app_src_checker_state_ {
}
