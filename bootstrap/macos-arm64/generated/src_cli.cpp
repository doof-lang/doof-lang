#include "src_cli.hpp"

namespace app_src_cli_ {


std::string cliUsage() {
    return std::string("usage: doof <build|run|profile|package|emit|check|test> [entry.do|package-dir] [options] [-- program-args...]\n       doof <script.do> [program-args...]\n\ncommands:\n  build   emit generated C++ and build the executable\n  run     emit, build, and run the executable\n  profile emit, build, and record a macOS Time Profiler trace\n  package build an optimized executable in the package dist directory\n  emit    check the source graph and write generated C++\n  check   check the source graph without writing output\n  test    discover and run exported test functions\n\noptions:\n  -o, --output-directory <path>  output root (package uses <path>/release)\n  --compiler <path>           C++ compiler command (default: CXX, cl.exe on Windows, or c++)\n  --target <kind>            override build target (macos-app, ios-app, or wasm)\n  --distdir <path>            packaged artifact directory\n  --macos-signing <kind>      developer-id or ad-hoc\n  --macos-sign-identity <id>  Developer ID Application identity\n  --macos-sandbox             enable App Sandbox entitlement\n  --macos-entitlements <path> merge additional entitlements plist\n  --ios-destination <kind>   iOS build destination: simulator or device\n  --ios-device <id>          connected iOS device identifier or name\n  --ios-sign-identity <id>   Apple signing identity for device/package builds\n  --ios-provisioning-profile <path> provisioning profile for device/package builds\n  --filter <text>             run tests whose id contains text\n  --list                      list tests without building or running\n  --coverage                  collect line coverage while running tests\n  --coverage-output <path>    write coverage JSON to this path\n  --trace-output <path>       write the profile trace to this .trace path\n  --time-limit <duration>     stop profiling after Nms, Ns, Nm, or Nh\n  --no-open                   do not open a completed trace in Instruments\n  -h, --help                  show this help\n  --                           pass remaining arguments to doof run/profile");
}
bool validProfileTimeLimit(const std::string& value) {
    auto unitLength = 1;
    if (doof::string_endsWith(value, std::string("ms"))) {
        static_cast<void>((unitLength = 2));
    } else if ((!doof::string_endsWith(value, std::string("s")) && !doof::string_endsWith(value, std::string("m"))) && !doof::string_endsWith(value, std::string("h"))) {
        return false;
    }
    const auto digitCount = (static_cast<int32_t>(value.size()) - unitLength);
    if (digitCount <= 0) {
        return false;
    }
    for (int32_t index = 0; index < digitCount; ++index) {
        const auto digit = doof::string_at(value, index, "src/cli", 82);
        if ((digit < U'\u0030') || (digit > U'\u0039')) {
            return false;
        }
    }
    return true;
}
std::shared_ptr<CliParseResult> parseCli(const std::shared_ptr<std::vector<std::string>>& args) {
    if (static_cast<int32_t>((args)->size()) == 0) {
        return std::make_shared<CliParseResult>(nullptr, std::string("missing command"), false);
    }
    if (((doof::array_at(args, 0, "src/cli", 90) == std::string("help")) || (doof::array_at(args, 0, "src/cli", 90) == std::string("-h"))) || (doof::array_at(args, 0, "src/cli", 90) == std::string("--help"))) {
        return std::make_shared<CliParseResult>(nullptr, std::string(""), true);
    }
    if (doof::string_endsWith(doof::array_at(args, 0, "src/cli", 94), std::string(".do"))) {
        const auto request = std::make_shared<CliRequest>(std::string("run"), doof::array_at(args, 0, "src/cli", 95), std::string(""), std::string(""), std::string(""), false, false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string("simulator"), std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        for (int32_t index = 1; index < static_cast<int32_t>((args)->size()); ++index) {
            request->programArguments->push_back(doof::array_at(args, index, "src/cli", 96));
        }
        return std::make_shared<CliParseResult>(request, std::string(""), false);
    }
    const auto command = doof::array_at(args, 0, "src/cli", 100);
    if (((((((command != std::string("build")) && (command != std::string("run"))) && (command != std::string("profile"))) && (command != std::string("package"))) && (command != std::string("emit"))) && (command != std::string("check"))) && (command != std::string("test"))) {
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown command '") + command) + std::string("'")), false);
    }
    const auto request = std::make_shared<CliRequest>(command, ((static_cast<int32_t>((args)->size()) < 2) ? std::string(".") : doof::array_at(args, 1, "src/cli", 104)), std::string(""), std::string(""), std::string(""), false, false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string("simulator"), std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    auto index = ((static_cast<int32_t>((args)->size()) < 2) ? 1 : 2);
    while (index < static_cast<int32_t>((args)->size())) {
        const auto argument = doof::array_at(args, index, "src/cli", 107);
        if (argument == std::string("--")) {
            if ((command != std::string("run")) && (command != std::string("profile"))) {
                return std::make_shared<CliParseResult>(nullptr, std::string("-- is only supported with the run and profile commands"), false);
            }
            static_cast<void>((index += 1));
            while (index < static_cast<int32_t>((args)->size())) {
                request->programArguments->push_back(doof::array_at(args, index, "src/cli", 114));
                static_cast<void>((index += 1));
            }
            continue;
        }
        if ((argument == std::string("-h")) || (argument == std::string("--help"))) {
            return std::make_shared<CliParseResult>(nullptr, std::string(""), true);
        }
        if ((argument == std::string("-o")) || (argument == std::string("--output-directory"))) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, (std::string("missing value for ") + argument), false);
            }
            static_cast<void>((request->outputDirectory = doof::array_at(args, (index + 1), "src/cli", 124)));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--compiler")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --compiler"), false);
            }
            static_cast<void>((request->compiler = doof::array_at(args, (index + 1), "src/cli", 130)));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--target")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --target"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 136);
            if (((value != std::string("macos-app")) && (value != std::string("ios-app"))) && (value != std::string("wasm"))) {
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --target: ") + value), false);
            }
            static_cast<void>((request->targetOverride = value));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--distdir")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --distdir"), false);
            }
            static_cast<void>((request->distDirectory = doof::array_at(args, (index + 1), "src/cli", 146)));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--macos-signing")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-signing"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 152);
            if ((value != std::string("developer-id")) && (value != std::string("ad-hoc"))) {
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --macos-signing: ") + value), false);
            }
            static_cast<void>((request->macosSigning = value));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--macos-sign-identity")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-sign-identity"), false);
            }
            static_cast<void>((request->macosSignIdentity = doof::array_at(args, (index + 1), "src/cli", 162)));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--macos-sandbox")) {
            static_cast<void>((request->macosSandbox = true));
            static_cast<void>((index = (index + 1)));
            continue;
        }
        if (argument == std::string("--macos-entitlements")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-entitlements"), false);
            }
            static_cast<void>((request->macosEntitlements = doof::array_at(args, (index + 1), "src/cli", 173)));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--ios-destination")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-destination"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 179);
            if ((value != std::string("simulator")) && (value != std::string("device"))) {
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --ios-destination: ") + value), false);
            }
            static_cast<void>((request->iosDestination = value));
            static_cast<void>((index += 2));
            continue;
        }
        if (argument == std::string("--ios-sign-identity")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-sign-identity"), false);
            }
            static_cast<void>((request->iosSignIdentity = doof::array_at(args, (index + 1), "src/cli", 189)));
            static_cast<void>((index += 2));
            continue;
        }
        if (argument == std::string("--ios-device")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-device"), false);
            }
            static_cast<void>((request->iosDevice = doof::array_at(args, (index + 1), "src/cli", 195)));
            static_cast<void>((index += 2));
            continue;
        }
        if (argument == std::string("--ios-provisioning-profile")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-provisioning-profile"), false);
            }
            static_cast<void>((request->iosProvisioningProfile = doof::array_at(args, (index + 1), "src/cli", 201)));
            static_cast<void>((index += 2));
            continue;
        }
        if (argument == std::string("--filter")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --filter"), false);
            }
            static_cast<void>((request->filter = doof::array_at(args, (index + 1), "src/cli", 207)));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--list")) {
            static_cast<void>((request->listOnly = true));
            static_cast<void>((index = (index + 1)));
            continue;
        }
        if (argument == std::string("--coverage")) {
            static_cast<void>((request->coverage = true));
            static_cast<void>((index = (index + 1)));
            continue;
        }
        if (argument == std::string("--coverage-output")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --coverage-output"), false);
            }
            static_cast<void>((request->coverageOutput = doof::array_at(args, (index + 1), "src/cli", 223)));
            static_cast<void>((index = (index + 2)));
            continue;
        }
        if (argument == std::string("--trace-output")) {
            if (command != std::string("profile")) {
                return std::make_shared<CliParseResult>(nullptr, std::string("--trace-output is only supported with the profile command"), false);
            }
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --trace-output"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 230);
            if (!doof::string_endsWith(value, std::string(".trace"))) {
                return std::make_shared<CliParseResult>(nullptr, std::string("--trace-output must end with .trace"), false);
            }
            static_cast<void>((request->traceOutput = value));
            static_cast<void>((index += 2));
            continue;
        }
        if (argument == std::string("--time-limit")) {
            if (command != std::string("profile")) {
                return std::make_shared<CliParseResult>(nullptr, std::string("--time-limit is only supported with the profile command"), false);
            }
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --time-limit"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 239);
            if (!validProfileTimeLimit(value)) {
                return std::make_shared<CliParseResult>(nullptr, std::string("invalid --time-limit; expected Nms, Ns, Nm, or Nh"), false);
            }
            static_cast<void>((request->profileTimeLimit = value));
            static_cast<void>((index += 2));
            continue;
        }
        if (argument == std::string("--no-open")) {
            if (command != std::string("profile")) {
                return std::make_shared<CliParseResult>(nullptr, std::string("--no-open is only supported with the profile command"), false);
            }
            static_cast<void>((request->profileNoOpen = true));
            static_cast<void>((index += 1));
            continue;
        }
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown option '") + argument) + std::string("'")), false);
    }
    return std::make_shared<CliParseResult>(request, std::string(""), false);
}
}
