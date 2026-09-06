#include "src_profile_command.hpp"

namespace app_src_profile_command_ {
using namespace ::app_src_run_command_;
std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileSymbols(const std::string& binaryPath, const std::string& symbolsPath, const std::string& packageRoot) {
    return std::make_shared<::app_src_run_command_::RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("dsymutil"), binaryPath, std::string("-o"), symbolsPath}), packageRoot);
}
std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileCapture(const std::string& targetPath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot, const std::string& tracePath, const std::string& timeLimit, bool consoleTarget) {
    const auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("xctrace"), std::string("record"), std::string("--template"), std::string("Time Profiler"), std::string("--output"), tracePath});
    if (timeLimit != std::string("")) {
        (static_cast<void>(arguments->push_back(std::string("--time-limit"))), std::monostate{});
        (static_cast<void>(arguments->push_back(timeLimit)), std::monostate{});
    }
    if (consoleTarget) {
        (static_cast<void>(arguments->push_back(std::string("--target-stdin"))), std::monostate{});
        (static_cast<void>(arguments->push_back(std::string("-"))), std::monostate{});
        (static_cast<void>(arguments->push_back(std::string("--target-stdout"))), std::monostate{});
        (static_cast<void>(arguments->push_back(std::string("-"))), std::monostate{});
    }
    (static_cast<void>(arguments->push_back(std::string("--launch"))), std::monostate{});
    (static_cast<void>(arguments->push_back(std::string("--"))), std::monostate{});
    (static_cast<void>(arguments->push_back(targetPath)), std::monostate{});
    const auto& _iterable_2 = programArguments;
    for (const auto& argument : *_iterable_2) {
        (static_cast<void>(arguments->push_back(argument)), std::monostate{});
    }
    return std::make_shared<::app_src_run_command_::RunInvocation>(std::string("xcrun"), arguments, packageRoot);
}
std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileOpen(const std::string& tracePath, const std::string& packageRoot) {
    return std::make_shared<::app_src_run_command_::RunInvocation>(std::string("open"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{tracePath}), packageRoot);
}
}
