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
namespace app_src_semantic_ { struct Binding; }
namespace app_src_semantic_ { struct CheckResult; }
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct Scope; }
namespace app_src_checker_state_ { struct CheckerState; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_checker_ {
    struct ModuleChecker;
}

#include "src_analyzer.hpp"
#include "src_semantic.hpp"
#include "src_checker_state.hpp"
#include "src_checker_statements.hpp"
#include "src_checker_actor_lifecycle.hpp"
#include "src_checker_interfaces.hpp"
#include "src_checker_symbols.hpp"
#include "src_checker_validation.hpp"
#include "src_checker_isolation.hpp"

namespace app_src_checker_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ModuleChecker : public std::enable_shared_from_this<ModuleChecker> {
    std::shared_ptr<::app_src_checker_state_::CheckerState> state;
    ModuleChecker(std::shared_ptr<::app_src_checker_state_::CheckerState> state) : state(state) {}
    std::shared_ptr<::app_src_semantic_::CheckResult> check(std::string entry);
};
    std::shared_ptr<::app_src_semantic_::CheckResult> checkModule(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::string entry);
    std::shared_ptr<ModuleChecker> createChecker(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateCheckedTypes(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
}

namespace app_src_checker_ {
}
