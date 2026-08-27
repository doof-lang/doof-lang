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
    std::string outputDirectory;
    std::string compiler;
    std::string filter;
    bool listOnly;
    bool coverage;
    std::string coverageOutput;
    std::string traceOutput;
    std::string profileTimeLimit;
    bool profileNoOpen;
    std::string distDirectory;
    std::string macosSigning;
    std::string macosSignIdentity;
    bool macosSandbox;
    std::string macosEntitlements;
    std::string iosDestination;
    std::string iosDevice;
    std::string iosSignIdentity;
    std::string iosProvisioningProfile;
    std::string targetOverride;
    std::shared_ptr<std::vector<std::string>> programArguments;
    CliRequest(std::string command, std::string entry, std::string outputDirectory, std::string compiler, std::string filter, bool listOnly, bool coverage, std::string coverageOutput, std::string traceOutput, std::string profileTimeLimit, bool profileNoOpen, std::string distDirectory, std::string macosSigning, std::string macosSignIdentity, bool macosSandbox, std::string macosEntitlements, std::string iosDestination, std::string iosDevice, std::string iosSignIdentity, std::string iosProvisioningProfile, std::string targetOverride, std::shared_ptr<std::vector<std::string>> programArguments) : command(command), entry(entry), outputDirectory(outputDirectory), compiler(compiler), filter(filter), listOnly(listOnly), coverage(coverage), coverageOutput(coverageOutput), traceOutput(traceOutput), profileTimeLimit(profileTimeLimit), profileNoOpen(profileNoOpen), distDirectory(distDirectory), macosSigning(macosSigning), macosSignIdentity(macosSignIdentity), macosSandbox(macosSandbox), macosEntitlements(macosEntitlements), iosDestination(iosDestination), iosDevice(iosDevice), iosSignIdentity(iosSignIdentity), iosProvisioningProfile(iosProvisioningProfile), targetOverride(targetOverride), programArguments(programArguments) {}
};
    struct CliParseResult : public std::enable_shared_from_this<CliParseResult> {
    std::shared_ptr<CliRequest> request;
    std::string error;
    bool help;
    CliParseResult(std::shared_ptr<CliRequest> request, std::string error, bool help) : request(request), error(error), help(help) {}
};
}

namespace app_src_cli_ {
    std::string cliUsage();
    bool validProfileTimeLimit(const std::string& value);
    std::shared_ptr<CliParseResult> parseCli(const std::shared_ptr<std::vector<std::string>>& args);
}
