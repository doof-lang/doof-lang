#include "src_wasm_test_runner.hpp"

namespace app_src_wasm_test_runner_ {

std::shared_ptr<WasmTestRunnerPlan> planAppleWasmTestRunnerBuild(const std::string& sourcePath, const std::string& outputPath) {
    return std::make_shared<WasmTestRunnerPlan>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("swiftc"), sourcePath, std::string("-framework"), std::string("JavaScriptCore"), std::string("-o"), outputPath}));
}
std::shared_ptr<WasmTestRunnerPlan> planAppleWasmTestRun(const std::string& runnerPath, const std::string& modulePath, const std::string& testId) {
    return std::make_shared<WasmTestRunnerPlan>(runnerPath, std::make_shared<std::vector<std::string>>(std::vector<std::string>{modulePath, testId}));
}
}
