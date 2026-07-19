#include "src_cli.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_cli_ {

doof::JsonObject CliRequest::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["command"] = doof::json_value(this->command);
    (*_json)["entry"] = doof::json_value(this->entry);
    (*_json)["outputDirectory"] = doof::json_value(this->outputDirectory);
    (*_json)["compiler"] = doof::json_value(this->compiler);
    (*_json)["filter"] = doof::json_value(this->filter);
    (*_json)["listOnly"] = doof::json_value(this->listOnly);
    (*_json)["coverage"] = doof::json_value(this->coverage);
    (*_json)["coverageOutput"] = doof::json_value(this->coverageOutput);
    (*_json)["distDirectory"] = doof::json_value(this->distDirectory);
    (*_json)["macosSigning"] = doof::json_value(this->macosSigning);
    (*_json)["macosSignIdentity"] = doof::json_value(this->macosSignIdentity);
    (*_json)["macosSandbox"] = doof::json_value(this->macosSandbox);
    (*_json)["macosEntitlements"] = doof::json_value(this->macosEntitlements);
    (*_json)["iosDestination"] = doof::json_value(this->iosDestination);
    (*_json)["iosDevice"] = doof::json_value(this->iosDevice);
    (*_json)["iosSignIdentity"] = doof::json_value(this->iosSignIdentity);
    (*_json)["iosProvisioningProfile"] = doof::json_value(this->iosProvisioningProfile);
    (*_json)["targetOverride"] = doof::json_value(this->targetOverride);
    (*_json)["programArguments"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->programArguments->size()); for (const auto& _element : *this->programArguments) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<CliRequest>, std::string> CliRequest::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_command = _object->find("command");
    if (_iterator_command == _object->end()) { return doof::Failure<std::string>{"Missing required field \"command\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_command->second) : doof::json_is_string(_iterator_command->second)))) { return doof::Failure<std::string>{"Field \"command\" expected string but got " + std::string(doof::json_type_name(_iterator_command->second))}; }
    auto _field_command = (_lenient ? doof::json_as_string_lenient(_iterator_command->second) : doof::json_as_string(_iterator_command->second));
    auto _iterator_entry = _object->find("entry");
    if (_iterator_entry == _object->end()) { return doof::Failure<std::string>{"Missing required field \"entry\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_entry->second) : doof::json_is_string(_iterator_entry->second)))) { return doof::Failure<std::string>{"Field \"entry\" expected string but got " + std::string(doof::json_type_name(_iterator_entry->second))}; }
    auto _field_entry = (_lenient ? doof::json_as_string_lenient(_iterator_entry->second) : doof::json_as_string(_iterator_entry->second));
    std::optional<std::string> _field_outputDirectory;
    if (auto _iterator_outputDirectory = _object->find("outputDirectory"); _iterator_outputDirectory != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputDirectory->second) : doof::json_is_string(_iterator_outputDirectory->second)))) { return doof::Failure<std::string>{"Field \"outputDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_outputDirectory->second))}; }
        _field_outputDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_outputDirectory->second) : doof::json_as_string(_iterator_outputDirectory->second));
    } else {
        _field_outputDirectory = std::string{std::string("")};
    }
    std::optional<std::string> _field_compiler;
    if (auto _iterator_compiler = _object->find("compiler"); _iterator_compiler != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_compiler->second) : doof::json_is_string(_iterator_compiler->second)))) { return doof::Failure<std::string>{"Field \"compiler\" expected string but got " + std::string(doof::json_type_name(_iterator_compiler->second))}; }
        _field_compiler = (_lenient ? doof::json_as_string_lenient(_iterator_compiler->second) : doof::json_as_string(_iterator_compiler->second));
    } else {
        _field_compiler = std::string{std::string("")};
    }
    std::optional<std::string> _field_filter;
    if (auto _iterator_filter = _object->find("filter"); _iterator_filter != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_filter->second) : doof::json_is_string(_iterator_filter->second)))) { return doof::Failure<std::string>{"Field \"filter\" expected string but got " + std::string(doof::json_type_name(_iterator_filter->second))}; }
        _field_filter = (_lenient ? doof::json_as_string_lenient(_iterator_filter->second) : doof::json_as_string(_iterator_filter->second));
    } else {
        _field_filter = std::string{std::string("")};
    }
    std::optional<bool> _field_listOnly;
    if (auto _iterator_listOnly = _object->find("listOnly"); _iterator_listOnly != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_listOnly->second) : doof::json_is_boolean(_iterator_listOnly->second)))) { return doof::Failure<std::string>{"Field \"listOnly\" expected boolean but got " + std::string(doof::json_type_name(_iterator_listOnly->second))}; }
        _field_listOnly = (_lenient ? doof::json_as_bool_lenient(_iterator_listOnly->second) : doof::json_as_bool(_iterator_listOnly->second));
    } else {
        _field_listOnly = bool{false};
    }
    std::optional<bool> _field_coverage;
    if (auto _iterator_coverage = _object->find("coverage"); _iterator_coverage != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_coverage->second) : doof::json_is_boolean(_iterator_coverage->second)))) { return doof::Failure<std::string>{"Field \"coverage\" expected boolean but got " + std::string(doof::json_type_name(_iterator_coverage->second))}; }
        _field_coverage = (_lenient ? doof::json_as_bool_lenient(_iterator_coverage->second) : doof::json_as_bool(_iterator_coverage->second));
    } else {
        _field_coverage = bool{false};
    }
    std::optional<std::string> _field_coverageOutput;
    if (auto _iterator_coverageOutput = _object->find("coverageOutput"); _iterator_coverageOutput != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_coverageOutput->second) : doof::json_is_string(_iterator_coverageOutput->second)))) { return doof::Failure<std::string>{"Field \"coverageOutput\" expected string but got " + std::string(doof::json_type_name(_iterator_coverageOutput->second))}; }
        _field_coverageOutput = (_lenient ? doof::json_as_string_lenient(_iterator_coverageOutput->second) : doof::json_as_string(_iterator_coverageOutput->second));
    } else {
        _field_coverageOutput = std::string{std::string("")};
    }
    std::optional<std::string> _field_distDirectory;
    if (auto _iterator_distDirectory = _object->find("distDirectory"); _iterator_distDirectory != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_distDirectory->second) : doof::json_is_string(_iterator_distDirectory->second)))) { return doof::Failure<std::string>{"Field \"distDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_distDirectory->second))}; }
        _field_distDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_distDirectory->second) : doof::json_as_string(_iterator_distDirectory->second));
    } else {
        _field_distDirectory = std::string{std::string("")};
    }
    std::optional<std::string> _field_macosSigning;
    if (auto _iterator_macosSigning = _object->find("macosSigning"); _iterator_macosSigning != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_macosSigning->second) : doof::json_is_string(_iterator_macosSigning->second)))) { return doof::Failure<std::string>{"Field \"macosSigning\" expected string but got " + std::string(doof::json_type_name(_iterator_macosSigning->second))}; }
        _field_macosSigning = (_lenient ? doof::json_as_string_lenient(_iterator_macosSigning->second) : doof::json_as_string(_iterator_macosSigning->second));
    } else {
        _field_macosSigning = std::string{std::string("")};
    }
    std::optional<std::string> _field_macosSignIdentity;
    if (auto _iterator_macosSignIdentity = _object->find("macosSignIdentity"); _iterator_macosSignIdentity != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_macosSignIdentity->second) : doof::json_is_string(_iterator_macosSignIdentity->second)))) { return doof::Failure<std::string>{"Field \"macosSignIdentity\" expected string but got " + std::string(doof::json_type_name(_iterator_macosSignIdentity->second))}; }
        _field_macosSignIdentity = (_lenient ? doof::json_as_string_lenient(_iterator_macosSignIdentity->second) : doof::json_as_string(_iterator_macosSignIdentity->second));
    } else {
        _field_macosSignIdentity = std::string{std::string("")};
    }
    std::optional<bool> _field_macosSandbox;
    if (auto _iterator_macosSandbox = _object->find("macosSandbox"); _iterator_macosSandbox != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_macosSandbox->second) : doof::json_is_boolean(_iterator_macosSandbox->second)))) { return doof::Failure<std::string>{"Field \"macosSandbox\" expected boolean but got " + std::string(doof::json_type_name(_iterator_macosSandbox->second))}; }
        _field_macosSandbox = (_lenient ? doof::json_as_bool_lenient(_iterator_macosSandbox->second) : doof::json_as_bool(_iterator_macosSandbox->second));
    } else {
        _field_macosSandbox = bool{false};
    }
    std::optional<std::string> _field_macosEntitlements;
    if (auto _iterator_macosEntitlements = _object->find("macosEntitlements"); _iterator_macosEntitlements != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_macosEntitlements->second) : doof::json_is_string(_iterator_macosEntitlements->second)))) { return doof::Failure<std::string>{"Field \"macosEntitlements\" expected string but got " + std::string(doof::json_type_name(_iterator_macosEntitlements->second))}; }
        _field_macosEntitlements = (_lenient ? doof::json_as_string_lenient(_iterator_macosEntitlements->second) : doof::json_as_string(_iterator_macosEntitlements->second));
    } else {
        _field_macosEntitlements = std::string{std::string("")};
    }
    std::optional<std::string> _field_iosDestination;
    if (auto _iterator_iosDestination = _object->find("iosDestination"); _iterator_iosDestination != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_iosDestination->second) : doof::json_is_string(_iterator_iosDestination->second)))) { return doof::Failure<std::string>{"Field \"iosDestination\" expected string but got " + std::string(doof::json_type_name(_iterator_iosDestination->second))}; }
        _field_iosDestination = (_lenient ? doof::json_as_string_lenient(_iterator_iosDestination->second) : doof::json_as_string(_iterator_iosDestination->second));
    } else {
        _field_iosDestination = std::string{std::string("simulator")};
    }
    std::optional<std::string> _field_iosDevice;
    if (auto _iterator_iosDevice = _object->find("iosDevice"); _iterator_iosDevice != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_iosDevice->second) : doof::json_is_string(_iterator_iosDevice->second)))) { return doof::Failure<std::string>{"Field \"iosDevice\" expected string but got " + std::string(doof::json_type_name(_iterator_iosDevice->second))}; }
        _field_iosDevice = (_lenient ? doof::json_as_string_lenient(_iterator_iosDevice->second) : doof::json_as_string(_iterator_iosDevice->second));
    } else {
        _field_iosDevice = std::string{std::string("")};
    }
    std::optional<std::string> _field_iosSignIdentity;
    if (auto _iterator_iosSignIdentity = _object->find("iosSignIdentity"); _iterator_iosSignIdentity != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_iosSignIdentity->second) : doof::json_is_string(_iterator_iosSignIdentity->second)))) { return doof::Failure<std::string>{"Field \"iosSignIdentity\" expected string but got " + std::string(doof::json_type_name(_iterator_iosSignIdentity->second))}; }
        _field_iosSignIdentity = (_lenient ? doof::json_as_string_lenient(_iterator_iosSignIdentity->second) : doof::json_as_string(_iterator_iosSignIdentity->second));
    } else {
        _field_iosSignIdentity = std::string{std::string("")};
    }
    std::optional<std::string> _field_iosProvisioningProfile;
    if (auto _iterator_iosProvisioningProfile = _object->find("iosProvisioningProfile"); _iterator_iosProvisioningProfile != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_iosProvisioningProfile->second) : doof::json_is_string(_iterator_iosProvisioningProfile->second)))) { return doof::Failure<std::string>{"Field \"iosProvisioningProfile\" expected string but got " + std::string(doof::json_type_name(_iterator_iosProvisioningProfile->second))}; }
        _field_iosProvisioningProfile = (_lenient ? doof::json_as_string_lenient(_iterator_iosProvisioningProfile->second) : doof::json_as_string(_iterator_iosProvisioningProfile->second));
    } else {
        _field_iosProvisioningProfile = std::string{std::string("")};
    }
    std::optional<std::string> _field_targetOverride;
    if (auto _iterator_targetOverride = _object->find("targetOverride"); _iterator_targetOverride != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_targetOverride->second) : doof::json_is_string(_iterator_targetOverride->second)))) { return doof::Failure<std::string>{"Field \"targetOverride\" expected string but got " + std::string(doof::json_type_name(_iterator_targetOverride->second))}; }
        _field_targetOverride = (_lenient ? doof::json_as_string_lenient(_iterator_targetOverride->second) : doof::json_as_string(_iterator_targetOverride->second));
    } else {
        _field_targetOverride = std::string{std::string("")};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_programArguments;
    if (auto _iterator_programArguments = _object->find("programArguments"); _iterator_programArguments != _object->end()) {
        if (!(doof::json_is_array(_iterator_programArguments->second))) { return doof::Failure<std::string>{"Field \"programArguments\" expected array but got " + std::string(doof::json_type_name(_iterator_programArguments->second))}; }
        _field_programArguments = [&]() { const auto* _array = doof::json_as_array(_iterator_programArguments->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_programArguments = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    return doof::Success<std::shared_ptr<CliRequest>>{std::make_shared<CliRequest>(_field_command, _field_entry, _field_outputDirectory.value(), _field_compiler.value(), _field_filter.value(), _field_listOnly.value(), _field_coverage.value(), _field_coverageOutput.value(), _field_distDirectory.value(), _field_macosSigning.value(), _field_macosSignIdentity.value(), _field_macosSandbox.value(), _field_macosEntitlements.value(), _field_iosDestination.value(), _field_iosDevice.value(), _field_iosSignIdentity.value(), _field_iosProvisioningProfile.value(), _field_targetOverride.value(), _field_programArguments.value())};
}

doof::JsonObject CliParseResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["request"] = (this->request ? doof::json_value(this->request->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["error"] = doof::json_value(this->error);
    (*_json)["help"] = doof::json_value(this->help);
    return _json;
}
doof::Result<std::shared_ptr<CliParseResult>, std::string> CliParseResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_request = _object->find("request");
    if (_iterator_request == _object->end()) { return doof::Failure<std::string>{"Missing required field \"request\""}; }
    if (!(doof::json_is_null(_iterator_request->second) || doof::json_is_object(_iterator_request->second))) { return doof::Failure<std::string>{"Field \"request\" expected object or null but got " + std::string(doof::json_type_name(_iterator_request->second))}; }
    auto _field_request = (doof::json_is_null(_iterator_request->second) ? nullptr : doof::success_value(CliRequest::fromJsonValue(_iterator_request->second, _lenient)));
    std::optional<std::string> _field_error;
    if (auto _iterator_error = _object->find("error"); _iterator_error != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_error->second) : doof::json_is_string(_iterator_error->second)))) { return doof::Failure<std::string>{"Field \"error\" expected string but got " + std::string(doof::json_type_name(_iterator_error->second))}; }
        _field_error = (_lenient ? doof::json_as_string_lenient(_iterator_error->second) : doof::json_as_string(_iterator_error->second));
    } else {
        _field_error = std::string{std::string("")};
    }
    std::optional<bool> _field_help;
    if (auto _iterator_help = _object->find("help"); _iterator_help != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_help->second) : doof::json_is_boolean(_iterator_help->second)))) { return doof::Failure<std::string>{"Field \"help\" expected boolean but got " + std::string(doof::json_type_name(_iterator_help->second))}; }
        _field_help = (_lenient ? doof::json_as_bool_lenient(_iterator_help->second) : doof::json_as_bool(_iterator_help->second));
    } else {
        _field_help = bool{false};
    }
    return doof::Success<std::shared_ptr<CliParseResult>>{std::make_shared<CliParseResult>(_field_request, _field_error.value(), _field_help.value())};
}
std::string cliUsage() {
    return ((((((((((((((((((((((((((((std::string("usage: doof <build|run|package|emit|check|test> [entry.do|package-dir] [options] [-- program-args...]\n") + std::string("\n")) + std::string("commands:\n")) + std::string("  build   emit generated C++ and build the executable\n")) + std::string("  run     emit, build, and run the executable\n")) + std::string("  package build an optimized executable in the package dist directory\n")) + std::string("  emit    check the source graph and write generated C++\n")) + std::string("  check   check the source graph without writing output\n")) + std::string("  test    discover and run exported test functions\n")) + std::string("\n")) + std::string("options:\n")) + std::string("  -o, --output-directory <path>  output root (package uses <path>/release)\n")) + std::string("  --compiler <path>           C++ compiler command (default: CXX or c++)\n")) + std::string("  --target <kind>            override build target (macos-app, ios-app, or wasm)\n")) + std::string("  --distdir <path>            packaged artifact directory\n")) + std::string("  --macos-signing <kind>      developer-id or ad-hoc\n")) + std::string("  --macos-sign-identity <id>  Developer ID Application identity\n")) + std::string("  --macos-sandbox             enable App Sandbox entitlement\n")) + std::string("  --macos-entitlements <path> merge additional entitlements plist\n")) + std::string("  --ios-destination <kind>   iOS build destination: simulator or device\n")) + std::string("  --ios-device <id>          connected iOS device identifier or name\n")) + std::string("  --ios-sign-identity <id>   Apple signing identity for device/package builds\n")) + std::string("  --ios-provisioning-profile <path> provisioning profile for device/package builds\n")) + std::string("  --filter <text>             run tests whose id contains text\n")) + std::string("  --list                      list tests without building or running\n")) + std::string("  --coverage                  collect line coverage while running tests\n")) + std::string("  --coverage-output <path>    write coverage JSON to this path\n")) + std::string("  -h, --help                  show this help\n")) + std::string("  --                           pass remaining arguments to doof run"));
}
std::shared_ptr<CliParseResult> parseCli(std::shared_ptr<std::vector<std::string>> args) {
    if (static_cast<int32_t>((args)->size()) == 0) {
        return std::make_shared<CliParseResult>(nullptr, std::string("missing command"), false);
    }
    if ((((*args)[0] == std::string("help")) || ((*args)[0] == std::string("-h"))) || ((*args)[0] == std::string("--help"))) {
        return std::make_shared<CliParseResult>(nullptr, std::string(""), true);
    }
    const auto command = (*args)[0];
    if ((((((command != std::string("build")) && (command != std::string("run"))) && (command != std::string("package"))) && (command != std::string("emit"))) && (command != std::string("check"))) && (command != std::string("test"))) {
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown command '") + command) + std::string("'")), false);
    }
    const auto request = std::make_shared<CliRequest>(command, ((static_cast<int32_t>((args)->size()) < 2) ? std::string(".") : (*args)[1]), std::string(""), std::string(""), std::string(""), false, false, std::string(""), std::string(""), std::string(""), std::string(""), false, std::string(""), std::string("simulator"), std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    auto index = ((static_cast<int32_t>((args)->size()) < 2) ? 1 : 2);
    while (index < static_cast<int32_t>((args)->size())) {
        const auto argument = (*args)[index];
        if (argument == std::string("--")) {
            if (command != std::string("run")) {
                return std::make_shared<CliParseResult>(nullptr, std::string("-- is only supported with the run command"), false);
            }
            (index += 1);
            while (index < static_cast<int32_t>((args)->size())) {
                request->programArguments->push_back((*args)[index]);
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
            (request->outputDirectory = (*args)[(index + 1)]);
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--compiler")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --compiler"), false);
            }
            (request->compiler = (*args)[(index + 1)]);
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--target")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --target"), false);
            }
            const auto value = (*args)[(index + 1)];
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
            (request->distDirectory = (*args)[(index + 1)]);
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--macos-signing")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --macos-signing"), false);
            }
            const auto value = (*args)[(index + 1)];
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
            (request->macosSignIdentity = (*args)[(index + 1)]);
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
            (request->macosEntitlements = (*args)[(index + 1)]);
            (index = (index + 2));
            continue;
        }
        if (argument == std::string("--ios-destination")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-destination"), false);
            }
            const auto value = (*args)[(index + 1)];
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
            (request->iosSignIdentity = (*args)[(index + 1)]);
            (index += 2);
            continue;
        }
        if (argument == std::string("--ios-device")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-device"), false);
            }
            (request->iosDevice = (*args)[(index + 1)]);
            (index += 2);
            continue;
        }
        if (argument == std::string("--ios-provisioning-profile")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --ios-provisioning-profile"), false);
            }
            (request->iosProvisioningProfile = (*args)[(index + 1)]);
            (index += 2);
            continue;
        }
        if (argument == std::string("--filter")) {
            if ((index + 1) >= static_cast<int32_t>((args)->size())) {
                return std::make_shared<CliParseResult>(nullptr, std::string("missing value for --filter"), false);
            }
            (request->filter = (*args)[(index + 1)]);
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
            (request->coverageOutput = (*args)[(index + 1)]);
            (index = (index + 2));
            continue;
        }
        return std::make_shared<CliParseResult>(nullptr, ((std::string("unknown option '") + argument) + std::string("'")), false);
    }
    return std::make_shared<CliParseResult>(request, std::string(""), false);
}
}
