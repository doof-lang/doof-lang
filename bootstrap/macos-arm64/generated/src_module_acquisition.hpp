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
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_module_acquisition_ {
    struct ModuleAcquisition;
}

namespace app_src_module_acquisition_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ModuleAcquisition : public std::enable_shared_from_this<ModuleAcquisition> {
    std::string logicalPrefix;
    std::string diskRoot;
    ModuleAcquisition(std::string logicalPrefix, std::string diskRoot) : logicalPrefix(logicalPrefix), diskRoot(diskRoot) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModuleAcquisition>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<ModuleAcquisition> acquiredPackageForModule(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>> acquisitions);
    std::optional<std::string> acquiredModuleDiskPath(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>> acquisitions);
    std::string acquiredManifestPath(std::shared_ptr<ModuleAcquisition> acquisition);
    bool acquisitionMatches(std::string prefix, std::string logicalPath);
    std::shared_ptr<ModuleAcquisition> selectedAcquisition(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>> acquisitions);
    std::string acquisitionJoinPath(std::string directory, std::string suffix);
}

namespace app_src_module_acquisition_ {
}
