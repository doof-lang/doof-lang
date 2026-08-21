#pragma once
#include "doof_runtime.hpp"
namespace app_src_run_command_ {
    struct RunInvocation;
}

namespace app_src_run_command_ {
    struct RunInvocation : public std::enable_shared_from_this<RunInvocation> {
    std::string command;
    std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::string directory;
    RunInvocation(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string directory) : command(command), arguments(arguments), directory(directory) {}
};
}

namespace app_src_run_command_ {
    std::shared_ptr<RunInvocation> planNativeProgramRun(const std::string& executablePath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planMacOSAppRun(const std::string& appPath, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSSimulatorInstall(const std::string& appPath, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSSimulatorLaunch(const std::string& bundleId, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSDeviceInstall(const std::string& appPath, const std::string& deviceIdentifier, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSDeviceLaunch(const std::string& bundleId, const std::string& deviceIdentifier, const std::string& packageRoot);
}
