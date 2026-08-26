#include "src_run_command.hpp"

namespace app_src_run_command_ {

#line 13 "/src/run-command.do"
std::shared_ptr<RunInvocation> planNativeProgramRun(const std::string& executablePath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot) {
#line 18 "/src/run-command.do"
    return std::make_shared<RunInvocation>(executablePath, programArguments, packageRoot);
}
#line 22 "/src/run-command.do"
std::shared_ptr<RunInvocation> planMacOSAppRun(const std::string& appPath, const std::string& packageRoot) {
#line 23 "/src/run-command.do"
    return std::make_shared<RunInvocation>(std::string("open"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-n"), appPath}), packageRoot);
}
#line 27 "/src/run-command.do"
std::shared_ptr<RunInvocation> planIOSSimulatorInstall(const std::string& appPath, const std::string& packageRoot) {
#line 28 "/src/run-command.do"
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("simctl"), std::string("install"), std::string("booted"), appPath}), packageRoot);
}
#line 36 "/src/run-command.do"
std::shared_ptr<RunInvocation> planIOSSimulatorLaunch(const std::string& bundleId, const std::string& packageRoot) {
#line 37 "/src/run-command.do"
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("simctl"), std::string("launch"), std::string("booted"), bundleId}), packageRoot);
}
#line 45 "/src/run-command.do"
std::shared_ptr<RunInvocation> planIOSDeviceInstall(const std::string& appPath, const std::string& deviceIdentifier, const std::string& packageRoot) {
#line 50 "/src/run-command.do"
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("device"), std::string("install"), std::string("app"), std::string("--device"), deviceIdentifier, appPath}), packageRoot);
}
#line 58 "/src/run-command.do"
std::shared_ptr<RunInvocation> planIOSDeviceLaunch(const std::string& bundleId, const std::string& deviceIdentifier, const std::string& packageRoot) {
#line 63 "/src/run-command.do"
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("device"), std::string("process"), std::string("launch"), std::string("--device"), deviceIdentifier, std::string("--terminate-existing"), bundleId}), packageRoot);
}
#line 1 "<doof-generated>"
}
