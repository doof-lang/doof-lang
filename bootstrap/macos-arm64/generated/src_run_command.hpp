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

namespace app_src_run_command_ {
    struct RunInvocation;
}

namespace app_src_run_command_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct RunInvocation : public std::enable_shared_from_this<RunInvocation> {
    std::string command;
    std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::string directory;
    RunInvocation(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string directory) : command(command), arguments(arguments), directory(directory) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<RunInvocation>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<RunInvocation> planNativeProgramRun(const std::string& executablePath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planMacOSAppRun(const std::string& appPath, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSSimulatorInstall(const std::string& appPath, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSSimulatorLaunch(const std::string& bundleId, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSDeviceInstall(const std::string& appPath, const std::string& deviceIdentifier, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSDeviceLaunch(const std::string& bundleId, const std::string& deviceIdentifier, const std::string& packageRoot);
}

namespace app_src_run_command_ {
}
