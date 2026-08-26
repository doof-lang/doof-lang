#include "src_cli.hpp"

namespace app_src_cli_ {


#line 38 "/src/cli.do"
std::string cliUsage() {
#line 39 "/src/cli.do"
    return std::string("usage: doof <build|run|profile|package|emit|check|test> [entry.do|package-dir] [options] [-- program-args...]\n       doof <script.do> [program-args...]\n\ncommands:\n  build   emit generated C++ and build the executable\n  run     emit, build, and run the executable\n  profile emit, build, and record a macOS Time Profiler trace\n  package build an optimized executable in the package dist directory\n  emit    check the source graph and write generated C++\n  check   check the source graph without writing output\n  test    discover and run exported test functions\n\noptions:\n  -o, --output-directory <path>  output root (package uses <path>/release)\n  --compiler <path>           C++ compiler command (default: CXX, cl.exe on Windows, or c++)\n  --target <kind>            override build target (macos-app, ios-app, or wasm)\n  --distdir <path>            packaged artifact directory\n  --macos-signing <kind>      developer-id or ad-hoc\n  --macos-sign-identity <id>  Developer ID Application identity\n  --macos-sandbox             enable App Sandbox entitlement\n  --macos-entitlements <path> merge additional entitlements plist\n  --ios-destination <kind>   iOS build destination: simulator or device\n  --ios-device <id>          connected iOS device identifier or name\n  --ios-sign-identity <id>   Apple signing identity for device/package builds\n  --ios-provisioning-profile <path> provisioning profile for device/package builds\n  --filter <text>             run tests whose id contains text\n  --list                      list tests without building or running\n  --coverage                  collect line coverage while running tests\n  --coverage-output <path>    write coverage JSON to this path\n  --trace-output <path>       write the profile trace to this .trace path\n  --time-limit <duration>     stop profiling after Nms, Ns, Nm, or Nh\n  --no-open                   do not open a completed trace in Instruments\n  -h, --help                  show this help\n  --                           pass remaining arguments to doof run/profile");
}
#line 75 "/src/cli.do"
bool validProfileTimeLimit(const std::string& value) {
#line 76 "/src/cli.do"
    auto unitLength = 1;
#line 77 "/src/cli.do"
    if (doof::string_endsWith(value, std::string("ms"))) {
#line 77 "/src/cli.do"
        (unitLength = 2);
    } else if ((!doof::string_endsWith(value, std::string("s")) && !doof::string_endsWith(value, std::string("m"))) && !doof::string_endsWith(value, std::string("h"))) {
#line 78 "/src/cli.do"
        return false;
    }
#line 79 "/src/cli.do"
    const auto digitCount = (static_cast<int32_t>(value.size()) - unitLength);
#line 80 "/src/cli.do"
    if (digitCount <= 0) {
#line 80 "/src/cli.do"
        return false;
    }
#line 81 "/src/cli.do"
    for (int32_t index = 0; index < digitCount; ++index) {
#line 82 "/src/cli.do"
        const auto digit = doof::string_at(value, index, "src/cli", 82);
#line 83 "/src/cli.do"
        if ((digit < U'\u0030') || (digit > U'\u0039')) {
#line 83 "/src/cli.do"
            return false;
        }
    }
#line 85 "/src/cli.do"
    return true;
}
#line 88 "/src/cli.do"
std::shared_ptr<CliParseResult> parseCli(const std::shared_ptr<std::vector<std::string>>& args) {
#line 89 "/src/cli.do"
    if (static_cast<int32_t>((args)->size()) == 0) {
#line 89 "/src/cli.do"
        return std::make_shared<CliParseResult>(nullptr, std::string("missing command"), false);
    }
#line 90 "/src/cli.do"
    if (((doof::array_at(args, 0, "src/cli", 90) == std::string("help")) || (doof::array_at(args, 0, "src/cli", 90) == std::string("-h"))) || (doof::array_at(args, 0, "src/cli", 90) == std::string("--help"))) {
#line 91 "/src/cli.do"
        return std::make_shared<CliParseResult>(nullptr, std::string(""), true);
    }
#line 94 "/src/cli.do"
    if (doof::string_endsWith(doof::array_at(args, 0, "src/cli", 94), std::string(".do"))) {
#line 95 "/src/cli.do"
        const auto request = std::make_shared<CliRequest>(std::string("run"), doof::array_at(args, 0, "src/cli", 95), std::string(""), std::string(""), std::string(""), false, false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string("simulator"), std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 96 "/src/cli.do"
        for (int32_t index = 1; index < static_cast<int32_t>((args)->size()); ++index) {
#line 96 "/src/cli.do"
            request->programArguments->push_back(doof::array_at(args, index, "src/cli", 96));
        }
#line 97 "/src/cli.do"
        return std::make_shared<CliParseResult>(request, std::string(""), false);
    }
#line 100 "/src/cli.do"
    const auto command = doof::array_at(args, 0, "src/cli", 100);
#line 101 "/src/cli.do"
    if (((((((command != std::string("build")) && (command != std::string("run"))) && (command != std::string("profile"))) && (command != std::string("package"))) && (command != std::string("emit"))) && (command != std::string("check"))) && (command != std::string("test"))) {
#line 102 "/src/cli.do"
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown command '") + command) + std::string("'")), false);
    }
#line 104 "/src/cli.do"
    const auto request = std::make_shared<CliRequest>(command, ((static_cast<int32_t>((args)->size()) < 2) ? std::string(".") : doof::array_at(args, 1, "src/cli", 104)), std::string(""), std::string(""), std::string(""), false, false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string(""), std::string(""), false, std::string(""), std::string("simulator"), std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 105 "/src/cli.do"
    auto index = ((static_cast<int32_t>((args)->size()) < 2) ? 1 : 2);
#line 106 "/src/cli.do"
    while (index < static_cast<int32_t>((args)->size())) {
#line 107 "/src/cli.do"
        const auto argument = doof::array_at(args, index, "src/cli", 107);
#line 108 "/src/cli.do"
        if (argument == std::string("--")) {
#line 109 "/src/cli.do"
            if ((command != std::string("run")) && (command != std::string("profile"))) {
#line 110 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("-- is only supported with the run and profile commands"), false);
            }
#line 112 "/src/cli.do"
            (index += 1);
#line 113 "/src/cli.do"
            while (index < static_cast<int32_t>((args)->size())) {
#line 114 "/src/cli.do"
                request->programArguments->push_back(doof::array_at(args, index, "src/cli", 114));
#line 115 "/src/cli.do"
                (index += 1);
            }
#line 117 "/src/cli.do"
            continue;
        }
#line 119 "/src/cli.do"
        if ((argument == std::string("-h")) || (argument == std::string("--help"))) {
#line 120 "/src/cli.do"
            return std::make_shared<CliParseResult>(nullptr, std::string(""), true);
        }
#line 122 "/src/cli.do"
        if ((argument == std::string("-o")) || (argument == std::string("--output-directory"))) {
#line 123 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 123 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, (std::string("missing value for ") + argument), false);
            }
#line 124 "/src/cli.do"
            (request->outputDirectory = doof::array_at(args, (index + 1), "src/cli", 124));
#line 125 "/src/cli.do"
            (index = (index + 2));
#line 126 "/src/cli.do"
            continue;
        }
#line 128 "/src/cli.do"
        if (argument == std::string("--compiler")) {
#line 129 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 129 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --compiler"), false);
            }
#line 130 "/src/cli.do"
            (request->compiler = doof::array_at(args, (index + 1), "src/cli", 130));
#line 131 "/src/cli.do"
            (index = (index + 2));
#line 132 "/src/cli.do"
            continue;
        }
#line 134 "/src/cli.do"
        if (argument == std::string("--target")) {
#line 135 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 135 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --target"), false);
            }
#line 136 "/src/cli.do"
            const auto value = doof::array_at(args, (index + 1), "src/cli", 136);
#line 137 "/src/cli.do"
            if (((value != std::string("macos-app")) && (value != std::string("ios-app"))) && (value != std::string("wasm"))) {
#line 138 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --target: ") + value), false);
            }
#line 140 "/src/cli.do"
            (request->targetOverride = value);
#line 141 "/src/cli.do"
            (index = (index + 2));
#line 142 "/src/cli.do"
            continue;
        }
#line 144 "/src/cli.do"
        if (argument == std::string("--distdir")) {
#line 145 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 145 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --distdir"), false);
            }
#line 146 "/src/cli.do"
            (request->distDirectory = doof::array_at(args, (index + 1), "src/cli", 146));
#line 147 "/src/cli.do"
            (index = (index + 2));
#line 148 "/src/cli.do"
            continue;
        }
#line 150 "/src/cli.do"
        if (argument == std::string("--macos-signing")) {
#line 151 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 151 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-signing"), false);
            }
#line 152 "/src/cli.do"
            const auto value = doof::array_at(args, (index + 1), "src/cli", 152);
#line 153 "/src/cli.do"
            if ((value != std::string("developer-id")) && (value != std::string("ad-hoc"))) {
#line 154 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --macos-signing: ") + value), false);
            }
#line 156 "/src/cli.do"
            (request->macosSigning = value);
#line 157 "/src/cli.do"
            (index = (index + 2));
#line 158 "/src/cli.do"
            continue;
        }
#line 160 "/src/cli.do"
        if (argument == std::string("--macos-sign-identity")) {
#line 161 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 161 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-sign-identity"), false);
            }
#line 162 "/src/cli.do"
            (request->macosSignIdentity = doof::array_at(args, (index + 1), "src/cli", 162));
#line 163 "/src/cli.do"
            (index = (index + 2));
#line 164 "/src/cli.do"
            continue;
        }
#line 166 "/src/cli.do"
        if (argument == std::string("--macos-sandbox")) {
#line 167 "/src/cli.do"
            (request->macosSandbox = true);
#line 168 "/src/cli.do"
            (index = (index + 1));
#line 169 "/src/cli.do"
            continue;
        }
#line 171 "/src/cli.do"
        if (argument == std::string("--macos-entitlements")) {
#line 172 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 172 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-entitlements"), false);
            }
#line 173 "/src/cli.do"
            (request->macosEntitlements = doof::array_at(args, (index + 1), "src/cli", 173));
#line 174 "/src/cli.do"
            (index = (index + 2));
#line 175 "/src/cli.do"
            continue;
        }
#line 177 "/src/cli.do"
        if (argument == std::string("--ios-destination")) {
#line 178 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 178 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-destination"), false);
            }
#line 179 "/src/cli.do"
            const auto value = doof::array_at(args, (index + 1), "src/cli", 179);
#line 180 "/src/cli.do"
            if ((value != std::string("simulator")) && (value != std::string("device"))) {
#line 181 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, (std::string("invalid value for --ios-destination: ") + value), false);
            }
#line 183 "/src/cli.do"
            (request->iosDestination = value);
#line 184 "/src/cli.do"
            (index += 2);
#line 185 "/src/cli.do"
            continue;
        }
#line 187 "/src/cli.do"
        if (argument == std::string("--ios-sign-identity")) {
#line 188 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 188 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-sign-identity"), false);
            }
#line 189 "/src/cli.do"
            (request->iosSignIdentity = doof::array_at(args, (index + 1), "src/cli", 189));
#line 190 "/src/cli.do"
            (index += 2);
#line 191 "/src/cli.do"
            continue;
        }
#line 193 "/src/cli.do"
        if (argument == std::string("--ios-device")) {
#line 194 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 194 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-device"), false);
            }
#line 195 "/src/cli.do"
            (request->iosDevice = doof::array_at(args, (index + 1), "src/cli", 195));
#line 196 "/src/cli.do"
            (index += 2);
#line 197 "/src/cli.do"
            continue;
        }
#line 199 "/src/cli.do"
        if (argument == std::string("--ios-provisioning-profile")) {
#line 200 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 200 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-provisioning-profile"), false);
            }
#line 201 "/src/cli.do"
            (request->iosProvisioningProfile = doof::array_at(args, (index + 1), "src/cli", 201));
#line 202 "/src/cli.do"
            (index += 2);
#line 203 "/src/cli.do"
            continue;
        }
#line 205 "/src/cli.do"
        if (argument == std::string("--filter")) {
#line 206 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 206 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --filter"), false);
            }
#line 207 "/src/cli.do"
            (request->filter = doof::array_at(args, (index + 1), "src/cli", 207));
#line 208 "/src/cli.do"
            (index = (index + 2));
#line 209 "/src/cli.do"
            continue;
        }
#line 211 "/src/cli.do"
        if (argument == std::string("--list")) {
#line 212 "/src/cli.do"
            (request->listOnly = true);
#line 213 "/src/cli.do"
            (index = (index + 1));
#line 214 "/src/cli.do"
            continue;
        }
#line 216 "/src/cli.do"
        if (argument == std::string("--coverage")) {
#line 217 "/src/cli.do"
            (request->coverage = true);
#line 218 "/src/cli.do"
            (index = (index + 1));
#line 219 "/src/cli.do"
            continue;
        }
#line 221 "/src/cli.do"
        if (argument == std::string("--coverage-output")) {
#line 222 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 222 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --coverage-output"), false);
            }
#line 223 "/src/cli.do"
            (request->coverageOutput = doof::array_at(args, (index + 1), "src/cli", 223));
#line 224 "/src/cli.do"
            (index = (index + 2));
#line 225 "/src/cli.do"
            continue;
        }
#line 227 "/src/cli.do"
        if (argument == std::string("--trace-output")) {
#line 228 "/src/cli.do"
            if (command != std::string("profile")) {
#line 228 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("--trace-output is only supported with the profile command"), false);
            }
#line 229 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 229 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --trace-output"), false);
            }
#line 230 "/src/cli.do"
            const auto value = doof::array_at(args, (index + 1), "src/cli", 230);
#line 231 "/src/cli.do"
            if (!doof::string_endsWith(value, std::string(".trace"))) {
#line 231 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("--trace-output must end with .trace"), false);
            }
#line 232 "/src/cli.do"
            (request->traceOutput = value);
#line 233 "/src/cli.do"
            (index += 2);
#line 234 "/src/cli.do"
            continue;
        }
#line 236 "/src/cli.do"
        if (argument == std::string("--time-limit")) {
#line 237 "/src/cli.do"
            if (command != std::string("profile")) {
#line 237 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("--time-limit is only supported with the profile command"), false);
            }
#line 238 "/src/cli.do"
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
#line 238 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --time-limit"), false);
            }
#line 239 "/src/cli.do"
            const auto value = doof::array_at(args, (index + 1), "src/cli", 239);
#line 240 "/src/cli.do"
            if (!validProfileTimeLimit(value)) {
#line 240 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("invalid --time-limit; expected Nms, Ns, Nm, or Nh"), false);
            }
#line 241 "/src/cli.do"
            (request->profileTimeLimit = value);
#line 242 "/src/cli.do"
            (index += 2);
#line 243 "/src/cli.do"
            continue;
        }
#line 245 "/src/cli.do"
        if (argument == std::string("--no-open")) {
#line 246 "/src/cli.do"
            if (command != std::string("profile")) {
#line 246 "/src/cli.do"
                return std::make_shared<CliParseResult>(nullptr, std::string("--no-open is only supported with the profile command"), false);
            }
#line 247 "/src/cli.do"
            (request->profileNoOpen = true);
#line 248 "/src/cli.do"
            (index += 1);
#line 249 "/src/cli.do"
            continue;
        }
#line 251 "/src/cli.do"
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown option '") + argument) + std::string("'")), false);
    }
#line 254 "/src/cli.do"
    return std::make_shared<CliParseResult>(request, std::string(""), false);
}
#line 1 "<doof-generated>"
}
