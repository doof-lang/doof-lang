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

namespace app_src_profile_command_ {
    std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileSymbols(const std::string& binaryPath, const std::string& symbolsPath, const std::string& packageRoot);
    std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileCapture(const std::string& targetPath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot, const std::string& tracePath, const std::string& timeLimit = std::string(""), bool consoleTarget = true);
    std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileOpen(const std::string& tracePath, const std::string& packageRoot);
}
