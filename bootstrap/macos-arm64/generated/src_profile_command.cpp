#include "src_profile_command.hpp"

namespace app_src_profile_command_ {
using namespace ::app_src_run_command_;
#line 9 "/src/profile-command.do"
std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileSymbols(const std::string& binaryPath, const std::string& symbolsPath, const std::string& packageRoot) {
#line 10 "/src/profile-command.do"
    return std::make_shared<::app_src_run_command_::RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("dsymutil"), binaryPath, std::string("-o"), symbolsPath}), packageRoot);
}
#line 18 "/src/profile-command.do"
std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileCapture(const std::string& targetPath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot, const std::string& tracePath, const std::string& timeLimit, bool consoleTarget) {
#line 26 "/src/profile-command.do"
    const auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("xctrace"), std::string("record"), std::string("--template"), std::string("Time Profiler"), std::string("--output"), tracePath});
#line 27 "/src/profile-command.do"
    if (timeLimit != std::string("")) {
#line 28 "/src/profile-command.do"
        arguments->push_back(std::string("--time-limit"));
#line 29 "/src/profile-command.do"
        arguments->push_back(timeLimit);
    }
#line 31 "/src/profile-command.do"
    if (consoleTarget) {
#line 32 "/src/profile-command.do"
        arguments->push_back(std::string("--target-stdin"));
#line 33 "/src/profile-command.do"
        arguments->push_back(std::string("-"));
#line 34 "/src/profile-command.do"
        arguments->push_back(std::string("--target-stdout"));
#line 35 "/src/profile-command.do"
        arguments->push_back(std::string("-"));
    }
#line 37 "/src/profile-command.do"
    arguments->push_back(std::string("--launch"));
#line 38 "/src/profile-command.do"
    arguments->push_back(std::string("--"));
#line 39 "/src/profile-command.do"
    arguments->push_back(targetPath);
#line 40 "/src/profile-command.do"
    const auto& _iterable_2 = programArguments;
    for (const auto& argument : *_iterable_2) {
#line 40 "/src/profile-command.do"
        arguments->push_back(argument);
    }
#line 41 "/src/profile-command.do"
    return std::make_shared<::app_src_run_command_::RunInvocation>(std::string("xcrun"), arguments, packageRoot);
}
#line 45 "/src/profile-command.do"
std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileOpen(const std::string& tracePath, const std::string& packageRoot) {
#line 46 "/src/profile-command.do"
    return std::make_shared<::app_src_run_command_::RunInvocation>(std::string("open"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{tracePath}), packageRoot);
}
#line 1 "<doof-generated>"
}
