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
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_pkg_config_ {
    struct PkgConfigCommandResult;
}

#include "src_package_manifest.hpp"

namespace app_src_pkg_config_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct PkgConfigCommandResult : public std::enable_shared_from_this<PkgConfigCommandResult> {
    int32_t exitCode;
    std::string output = std::string("");
    std::string error = std::string("");
    PkgConfigCommandResult(int32_t exitCode, std::string output = std::string(""), std::string error = std::string("")) : exitCode(exitCode), output(output), error(error) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PkgConfigCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    doof::Result<void, std::string> applyPkgConfigResult(std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> native, std::string packageName, std::string mode, std::shared_ptr<PkgConfigCommandResult> result);
    std::shared_ptr<std::vector<std::string>> pkgConfigTokens(std::string output);
    void applyPkgConfigTokens(std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> native, std::shared_ptr<std::vector<std::string>> tokens, std::string mode);
    void appendUnique(std::shared_ptr<std::vector<std::string>> target, std::string value);
}

namespace app_src_pkg_config_ {
}
