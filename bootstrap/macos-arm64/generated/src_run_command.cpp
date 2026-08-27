#include "src_run_command.hpp"

namespace app_src_run_command_ {

std::shared_ptr<RunInvocation> planNativeProgramRun(const std::string& executablePath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot) {
    return std::make_shared<RunInvocation>(executablePath, programArguments, packageRoot);
}
std::shared_ptr<RunInvocation> planMacOSAppRun(const std::string& appPath, const std::string& packageRoot) {
    return std::make_shared<RunInvocation>(std::string("open"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-n"), appPath}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSSimulatorInstall(const std::string& appPath, const std::string& packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("simctl"), std::string("install"), std::string("booted"), appPath}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSSimulatorLaunch(const std::string& bundleId, const std::string& packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("simctl"), std::string("launch"), std::string("booted"), bundleId}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSDeviceInstall(const std::string& appPath, const std::string& deviceIdentifier, const std::string& packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("device"), std::string("install"), std::string("app"), std::string("--device"), deviceIdentifier, appPath}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSDeviceLaunch(const std::string& bundleId, const std::string& deviceIdentifier, const std::string& packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("device"), std::string("process"), std::string("launch"), std::string("--device"), deviceIdentifier, std::string("--terminate-existing"), bundleId}), packageRoot);
}
}
