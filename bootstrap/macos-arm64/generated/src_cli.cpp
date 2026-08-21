#include "src_cli.hpp"

namespace app_src_cli_ {


std::string cliUsage() {
    return std::string("usage: doof <build|run|package|emit|check|test> [entry.do|package-dir] [options] [-- program-args...]\n       doof <script.do> [program-args...]\n\ncommands:\n  build   emit generated C++ and build the executable\n  run     emit, build, and run the executable\n  package build an optimized executable in the package dist directory\n  emit    check the source graph and write generated C++\n  check   check the source graph without writing output\n  test    discover and run exported test functions\n\noptions:\n  -o, --output-directory <path>  output root (package uses <path>/release)\n  --compiler <path>           C++ compiler command (default: CXX, cl.exe on Windows, or c++)\n  --target <kind>            override build target (macos-app, ios-app, or wasm)\n  --distdir <path>            packaged artifact directory\n  --macos-signing <kind>      developer-id or ad-hoc\n  --macos-sign-identity <id>  Developer ID Application identity\n  --macos-sandbox             enable App Sandbox entitlement\n  --macos-entitlements <path> merge additional entitlements plist\n  --ios-destination <kind>   iOS build destination: simulator or device\n  --ios-device <id>          connected iOS device identifier or name\n  --ios-sign-identity <id>   Apple signing identity for device/package builds\n  --ios-provisioning-profile <path> provisioning profile for device/package builds\n  --filter <text>             run tests whose id contains text\n  --list                      list tests without building or running\n  --coverage                  collect line coverage while running tests\n  --coverage-output <path>    write coverage JSON to this path\n  -h, --help                  show this help\n  --                           pass remaining arguments to doof run");
}
std::shared_ptr<CliParseResult> parseCli(const std::shared_ptr<std::vector<std::string>>& args) {
    if (static_cast<int32_t>((args)->size()) == 0) {
        return std::make_shared<CliParseResult>(nullptr, std::string("missing command"), false);
    }
    if (((doof::array_at(args, 0, "src/cli", 70) == std::string("help")) || (doof::array_at(args, 0, "src/cli", 70) == std::string("-h"))) || (doof::array_at(args, 0, "src/cli", 70) == std::string("--help"))) {
        return std::make_shared<CliParseResult>(nullptr, std::string(""), true);
    }
    if (doof::string_endsWith(doof::array_at(args, 0, "src/cli", 74), std::string(".do"))) {
        const auto request = std::make_shared<CliRequest>(std::string("run"), doof::array_at(args, 0, "src/cli", 75), std::string(""), std::string(""), std::string(""), false, false, std::string(""), std::string(""), std::string(""), std::string(""), false, std::string(""), std::string("simulator"), std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        for (int32_t index = 1; index < static_cast<int32_t>((args)->size()); ++index) {
            request->programArguments->push_back(doof::array_at(args, index, "src/cli", 76));
        }
        return std::make_shared<CliParseResult>(request, std::string(""), false);
    }
    const auto command = doof::array_at(args, 0, "src/cli", 80);
    if ((((((command != std::string("build")) && (command != std::string("run"))) && (command != std::string("package"))) && (command != std::string("emit"))) && (command != std::string("check"))) && (command != std::string("test"))) {
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown command '") + command) + std::string("'")), false);
    }
    const auto request = std::make_shared<CliRequest>(command, ((static_cast<int32_t>((args)->size()) < 2) ? std::string(".") : doof::array_at(args, 1, "src/cli", 84)), std::string(""), std::string(""), std::string(""), false, false, std::string(""), std::string(""), std::string(""), std::string(""), false, std::string(""), std::string("simulator"), std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    auto index = ((static_cast<int32_t>((args)->size()) < 2) ? 1 : 2);
    while (index < static_cast<int32_t>((args)->size())) {
        const auto argument = doof::array_at(args, index, "src/cli", 87);
        if (argument == std::string("--")) {
            if (command != std::string("run")) {
                return std::make_shared<CliParseResult>(nullptr, std::string("-- is only supported with the run command"), false);
            }
            (index += 1);
            while (index < static_cast<int32_t>((args)->size())) {
                request->programArguments->push_back(doof::array_at(args, index, "src/cli", 94));
                (index += 1);
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
            (request->outputDirectory = doof::array_at(args, (index + 1), "src/cli", 104));
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--compiler")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --compiler"), false);
            }
            (request->compiler = doof::array_at(args, (index + 1), "src/cli", 110));
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--target")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --target"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 116);
            if (((value != std::string("macos-app")) && (value != std::string("ios-app"))) && (value != std::string("wasm"))) {
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --target: ") + value), false);
            }
            (request->targetOverride = value);
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--distdir")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --distdir"), false);
            }
            (request->distDirectory = doof::array_at(args, (index + 1), "src/cli", 126));
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--macos-signing")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-signing"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 132);
            if ((value != std::string("developer-id")) && (value != std::string("ad-hoc"))) {
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --macos-signing: ") + value), false);
            }
            (request->macosSigning = value);
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--macos-sign-identity")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-sign-identity"), false);
            }
            (request->macosSignIdentity = doof::array_at(args, (index + 1), "src/cli", 142));
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--macos-sandbox")) {
            (request->macosSandbox = true);
            (index = (index + 1));
            continue;
        }
        if (argument == std::string("--macos-entitlements")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-entitlements"), false);
            }
            (request->macosEntitlements = doof::array_at(args, (index + 1), "src/cli", 153));
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--ios-destination")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-destination"), false);
            }
            const auto value = doof::array_at(args, (index + 1), "src/cli", 159);
            if ((value != std::string("simulator")) && (value != std::string("device"))) {
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --ios-destination: ") + value), false);
            }
            (request->iosDestination = value);
            (index += 2);
            continue;
        }
        if (argument == std::string("--ios-sign-identity")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-sign-identity"), false);
            }
            (request->iosSignIdentity = doof::array_at(args, (index + 1), "src/cli", 169));
            (index += 2);
            continue;
        }
        if (argument == std::string("--ios-device")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-device"), false);
            }
            (request->iosDevice = doof::array_at(args, (index + 1), "src/cli", 175));
            (index += 2);
            continue;
        }
        if (argument == std::string("--ios-provisioning-profile")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-provisioning-profile"), false);
            }
            (request->iosProvisioningProfile = doof::array_at(args, (index + 1), "src/cli", 181));
            (index += 2);
            continue;
        }
        if (argument == std::string("--filter")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --filter"), false);
            }
            (request->filter = doof::array_at(args, (index + 1), "src/cli", 187));
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--list")) {
            (request->listOnly = true);
            (index = (index + 1));
            continue;
        }
        if (argument == std::string("--coverage")) {
            (request->coverage = true);
            (index = (index + 1));
            continue;
        }
        if (argument == std::string("--coverage-output")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --coverage-output"), false);
            }
            (request->coverageOutput = doof::array_at(args, (index + 1), "src/cli", 203));
            (index = (index + 2));
            continue;
        }
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown option '") + argument) + std::string("'")), false);
    }
    return std::make_shared<CliParseResult>(request, std::string(""), false);
}
}
