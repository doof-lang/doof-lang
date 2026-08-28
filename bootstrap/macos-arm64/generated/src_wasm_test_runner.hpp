#pragma once
#include "doof_runtime.hpp"
namespace app_src_wasm_test_runner_ {
    struct WasmTestRunnerPlan;
}

namespace app_src_wasm_test_runner_ {
    struct WasmTestRunnerPlan : public std::enable_shared_from_this<WasmTestRunnerPlan> {
    std::string command;
    std::shared_ptr<std::vector<std::string>> arguments;
    WasmTestRunnerPlan(std::string command, std::shared_ptr<std::vector<std::string>> arguments) : command(command), arguments(arguments) {}
};
}

namespace app_src_wasm_test_runner_ {
    std::shared_ptr<WasmTestRunnerPlan> planAppleWasmTestRunnerBuild(const std::string& sourcePath, const std::string& outputPath);
    std::shared_ptr<WasmTestRunnerPlan> planAppleWasmTestRun(const std::string& runnerPath, const std::string& modulePath, const std::string& testId);
}
