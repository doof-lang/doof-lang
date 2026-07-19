#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_cli_ {
    struct CliRequest;
    struct CliParseResult;
}

namespace app_src_cli_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct CliRequest : public std::enable_shared_from_this<CliRequest> {
    std::string command;
    std::string entry;
    std::string outputDirectory = std::string("");
    std::string compiler = std::string("");
    std::string filter = std::string("");
    bool listOnly = false;
    bool coverage = false;
    std::string coverageOutput = std::string("");
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
    CliRequest(std::string command, std::string entry, std::string outputDirectory = std::string(""), std::string compiler = std::string(""), std::string filter = std::string(""), bool listOnly = false, bool coverage = false, std::string coverageOutput = std::string(""), std::string distDirectory = std::string(""), std::string macosSigning = std::string(""), std::string macosSignIdentity = std::string(""), bool macosSandbox = false, std::string macosEntitlements = std::string(""), std::string iosDestination = std::string("simulator"), std::string iosDevice = std::string(""), std::string iosSignIdentity = std::string(""), std::string iosProvisioningProfile = std::string(""), std::string targetOverride = std::string(""), std::shared_ptr<std::vector<std::string>> programArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : command(command), entry(entry), outputDirectory(outputDirectory), compiler(compiler), filter(filter), listOnly(listOnly), coverage(coverage), coverageOutput(coverageOutput), distDirectory(distDirectory), macosSigning(macosSigning), macosSignIdentity(macosSignIdentity), macosSandbox(macosSandbox), macosEntitlements(macosEntitlements), iosDestination(iosDestination), iosDevice(iosDevice), iosSignIdentity(iosSignIdentity), iosProvisioningProfile(iosProvisioningProfile), targetOverride(targetOverride), programArguments(programArguments) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<CliRequest>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct CliParseResult : public std::enable_shared_from_this<CliParseResult> {
    std::shared_ptr<CliRequest> request;
    std::string error = std::string("");
    bool help = false;
    CliParseResult(std::shared_ptr<CliRequest> request, std::string error = std::string(""), bool help = false) : request(request), error(error), help(help) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<CliParseResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string cliUsage();
    std::shared_ptr<CliParseResult> parseCli(std::shared_ptr<std::vector<std::string>> args);
}

namespace app_src_cli_ {
}
