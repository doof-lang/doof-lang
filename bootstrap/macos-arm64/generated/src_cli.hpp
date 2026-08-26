#pragma once
#include "doof_runtime.hpp"
namespace app_src_cli_ {
    struct CliRequest;
    struct CliParseResult;
}

namespace app_src_cli_ {
    struct CliRequest : public std::enable_shared_from_this<CliRequest> {
    std::string command;
    std::string entry;
    std::string outputDirectory = std::string("");
    std::string compiler = std::string("");
    std::string filter = std::string("");
    bool listOnly = false;
    bool coverage = false;
    std::string coverageOutput = std::string("");
    std::string traceOutput = std::string("");
    std::string profileTimeLimit = std::string("");
    bool profileNoOpen = false;
    std::string distDirectory = std::string("");
    std::string macosSigning = std::string("");
    std::string macosSignIdentity = std::string("");
    bool macosSandbox = false;
    std::string macosEntitlements = std::string("");
    std::string iosDestination = std::string("simulator");
    std::string iosDevice = std::string("");
    std::string iosSignIdentity = std::string("");
    std::string iosProvisioningProfile = std::string("");
    std::string targetOverride = std::string("");
    std::shared_ptr<std::vector<std::string>> programArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    CliRequest(std::string command, std::string entry, std::string outputDirectory = std::string(""), std::string compiler = std::string(""), std::string filter = std::string(""), bool listOnly = false, bool coverage = false, std::string coverageOutput = std::string(""), std::string traceOutput = std::string(""), std::string profileTimeLimit = std::string(""), bool profileNoOpen = false, std::string distDirectory = std::string(""), std::string macosSigning = std::string(""), std::string macosSignIdentity = std::string(""), bool macosSandbox = false, std::string macosEntitlements = std::string(""), std::string iosDestination = std::string("simulator"), std::string iosDevice = std::string(""), std::string iosSignIdentity = std::string(""), std::string iosProvisioningProfile = std::string(""), std::string targetOverride = std::string(""), std::shared_ptr<std::vector<std::string>> programArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : command(command), entry(entry), outputDirectory(outputDirectory), compiler(compiler), filter(filter), listOnly(listOnly), coverage(coverage), coverageOutput(coverageOutput), traceOutput(traceOutput), profileTimeLimit(profileTimeLimit), profileNoOpen(profileNoOpen), distDirectory(distDirectory), macosSigning(macosSigning), macosSignIdentity(macosSignIdentity), macosSandbox(macosSandbox), macosEntitlements(macosEntitlements), iosDestination(iosDestination), iosDevice(iosDevice), iosSignIdentity(iosSignIdentity), iosProvisioningProfile(iosProvisioningProfile), targetOverride(targetOverride), programArguments(programArguments) {}
};
    struct CliParseResult : public std::enable_shared_from_this<CliParseResult> {
    std::shared_ptr<CliRequest> request;
    std::string error = std::string("");
    bool help = false;
    CliParseResult(std::shared_ptr<CliRequest> request, std::string error = std::string(""), bool help = false) : request(request), error(error), help(help) {}
};
}

namespace app_src_cli_ {
    std::string cliUsage();
    bool validProfileTimeLimit(const std::string& value);
    std::shared_ptr<CliParseResult> parseCli(const std::shared_ptr<std::vector<std::string>>& args);
}
