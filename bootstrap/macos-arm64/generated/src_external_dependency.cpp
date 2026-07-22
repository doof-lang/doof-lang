#include "src_external_dependency.hpp"
#include <cmath>
#include "src_package_manifest.hpp"
#include "std_blob_index.hpp"
#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_external_dependency_ {
using namespace ::app_src_package_manifest_;
using namespace ::std_::blob::index;
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::http::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
const auto EXTERNAL_SOURCE_MARKER = std::string(".doof-external.json");
const auto MAX_EXTERNAL_COMMAND_OUTPUT_BYTES = 1048576LL;

doof::JsonObject ExternalDependencyTarget::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["nativeTarget"] = doof::json_value(this->nativeTarget);
    (*_json)["sdkPath"] = doof::json_value(this->sdkPath);
    (*_json)["targetTriple"] = doof::json_value(this->targetTriple);
    (*_json)["configureHost"] = doof::json_value(this->configureHost);
    (*_json)["jobs"] = doof::json_value(this->jobs);
    return _json;
}
doof::Result<std::shared_ptr<ExternalDependencyTarget>, std::string> ExternalDependencyTarget::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_nativeTarget = _object->find("nativeTarget");
    if (_iterator_nativeTarget == _object->end()) { return doof::Failure<std::string>{"Missing required field \"nativeTarget\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_nativeTarget->second) : doof::json_is_string(_iterator_nativeTarget->second)))) { return doof::Failure<std::string>{"Field \"nativeTarget\" expected string but got " + std::string(doof::json_type_name(_iterator_nativeTarget->second))}; }
    auto _field_nativeTarget = (_lenient ? doof::json_as_string_lenient(_iterator_nativeTarget->second) : doof::json_as_string(_iterator_nativeTarget->second));
    std::optional<std::string> _field_sdkPath;
    if (auto _iterator_sdkPath = _object->find("sdkPath"); _iterator_sdkPath != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sdkPath->second) : doof::json_is_string(_iterator_sdkPath->second)))) { return doof::Failure<std::string>{"Field \"sdkPath\" expected string but got " + std::string(doof::json_type_name(_iterator_sdkPath->second))}; }
        _field_sdkPath = (_lenient ? doof::json_as_string_lenient(_iterator_sdkPath->second) : doof::json_as_string(_iterator_sdkPath->second));
    } else {
        _field_sdkPath = std::string("");
    }
    std::optional<std::string> _field_targetTriple;
    if (auto _iterator_targetTriple = _object->find("targetTriple"); _iterator_targetTriple != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_targetTriple->second) : doof::json_is_string(_iterator_targetTriple->second)))) { return doof::Failure<std::string>{"Field \"targetTriple\" expected string but got " + std::string(doof::json_type_name(_iterator_targetTriple->second))}; }
        _field_targetTriple = (_lenient ? doof::json_as_string_lenient(_iterator_targetTriple->second) : doof::json_as_string(_iterator_targetTriple->second));
    } else {
        _field_targetTriple = std::string("");
    }
    std::optional<std::string> _field_configureHost;
    if (auto _iterator_configureHost = _object->find("configureHost"); _iterator_configureHost != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_configureHost->second) : doof::json_is_string(_iterator_configureHost->second)))) { return doof::Failure<std::string>{"Field \"configureHost\" expected string but got " + std::string(doof::json_type_name(_iterator_configureHost->second))}; }
        _field_configureHost = (_lenient ? doof::json_as_string_lenient(_iterator_configureHost->second) : doof::json_as_string(_iterator_configureHost->second));
    } else {
        _field_configureHost = std::string("");
    }
    std::optional<int32_t> _field_jobs;
    if (auto _iterator_jobs = _object->find("jobs"); _iterator_jobs != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_jobs->second) : doof::json_is_number(_iterator_jobs->second)))) { return doof::Failure<std::string>{"Field \"jobs\" expected number but got " + std::string(doof::json_type_name(_iterator_jobs->second))}; }
        _field_jobs = (_lenient ? doof::json_as_int_lenient(_iterator_jobs->second) : doof::json_as_int(_iterator_jobs->second));
    } else {
        _field_jobs = 1;
    }
    return doof::Success<std::shared_ptr<ExternalDependencyTarget>>{std::make_shared<ExternalDependencyTarget>(_field_nativeTarget, _field_sdkPath.value(), _field_targetTriple.value(), _field_configureHost.value(), _field_jobs.value())};
}
std::string externalPath(std::string directory, std::string name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
doof::Result<void, std::string> ensureExternalDirectory(std::string path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return doof::Success<void>{};
    }
    const auto parent = ::std_::path::index::dirname(path);
    if (parent != path) {
        auto _try_value_1 = ensureExternalDirectory(parent);
        if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::failure_error(_try_value_1)};
    }
    auto _binding_value_2 = ::doof_fs::mkdir(path);
    if (doof::is_failure(_binding_value_2)) {
        const auto error = doof::failure_error(_binding_value_2);
        return doof::Failure<std::string>{ (std::string("Could not create directory ") + path) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> removeExternalTree(std::string path) {
    if (!::doof_fs::exists(path)) {
        return doof::Success<void>{};
    }
    if (::doof_fs::isDirectory(path)) {
        auto _binding_value_3 = ::doof_fs::readDir(path);
        if (doof::is_failure(_binding_value_3)) {
            const auto error = doof::failure_error(_binding_value_3);
            return doof::Failure<std::string>{ (std::string("Could not read directory ") + path) };
        }
        const auto entries = doof::success_value(_binding_value_3);
        const auto& _iterable_4 = entries;
        for (const auto& entry : *_iterable_4) {
            auto _try_value_5 = removeExternalTree(externalPath(path, entry->name));
            if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::failure_error(_try_value_5)};
        }
    }
    auto _binding_value_6 = ::doof_fs::remove(path);
    if (doof::is_failure(_binding_value_6)) {
        const auto error = doof::failure_error(_binding_value_6);
        return doof::Failure<std::string>{ (std::string("Could not remove ") + path) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> copyExternalPath(std::string sourcePath, std::string destinationPath) {
    if (::doof_fs::isDirectory(sourcePath)) {
        auto _try_value_7 = ensureExternalDirectory(destinationPath);
        if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::failure_error(_try_value_7)};
        auto _binding_value_8 = ::doof_fs::readDir(sourcePath);
        if (doof::is_failure(_binding_value_8)) {
            const auto error = doof::failure_error(_binding_value_8);
            return doof::Failure<std::string>{ (std::string("Could not read directory ") + sourcePath) };
        }
        const auto entries = doof::success_value(_binding_value_8);
        const auto& _iterable_9 = entries;
        for (const auto& entry : *_iterable_9) {
            auto _try_value_10 = copyExternalPath(externalPath(sourcePath, entry->name), externalPath(destinationPath, entry->name));
            if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::failure_error(_try_value_10)};
        }
        return doof::Success<void>{};
    }
    auto _try_value_11 = ensureExternalDirectory(::std_::path::index::dirname(destinationPath));
    if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::failure_error(_try_value_11)};
    auto _binding_value_12 = ::doof_fs::readBlob(sourcePath);
    if (doof::is_failure(_binding_value_12)) {
        const auto error = doof::failure_error(_binding_value_12);
        return doof::Failure<std::string>{ (std::string("Could not read ") + sourcePath) };
    }
    const auto blob = doof::success_value(_binding_value_12);
    auto _binding_value_13 = ::doof_fs::writeBlob(destinationPath, blob);
    if (doof::is_failure(_binding_value_13)) {
        const auto error = doof::failure_error(_binding_value_13);
        return doof::Failure<std::string>{ (std::string("Could not write ") + destinationPath) };
    }
    return doof::Success<void>{};
}
bool externalPathWithinRoot(std::string path, std::string root) {
    const auto boundary = (doof::string_endsWith(root, std::string("/")) ? root : (root + std::string("/")));
    return ((path == root) || doof::string_startsWith(path, boundary));
}
doof::Result<std::string, std::string> commandOutput(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::shared_ptr<::std_::os::index::ExecOptions> options) {
    auto _binding_value_14 = ::std_::os::index::run(command, arguments, options);
    if (doof::is_failure(_binding_value_14)) {
        const auto error = doof::failure_error(_binding_value_14);
        return doof::Failure<std::string>{ ((command + std::string(": ")) + error) };
    }
    const auto result = doof::success_value(_binding_value_14);
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->stdout, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->stdout)->size()))));
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ (((command + std::string(" exited with code ")) + doof::to_string(result->exitCode)) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    return doof::Success<std::string>{ output };
}
std::string externalCommandFingerprint(std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand> command) {
    auto result = (((command->program + std::string("\n")) + command->workingDirectory) + std::string("\n"));
    const auto& _iterable_15 = command->args;
    for (const auto& argument : *_iterable_15) {
        (result += ((std::string("arg=") + argument) + std::string("\n")));
    }
    const auto& _iterable_16 = command->env;
    for (const auto& [key, value] : *_iterable_16) {
        (result += ((((std::string("env=") + key) + std::string("=")) + value) + std::string("\n")));
    }
    return result;
}
std::string externalSourceFingerprint(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency) {
    auto value = ((((((((((((((((std::string("schema=1\nname=") + dependency->name) + std::string("\nkind=")) + dependency->kind) + std::string("\nurl=")) + dependency->url) + std::string("\ndestination=")) + dependency->destination) + std::string("\nsha256=")) + dependency->sha256) + std::string("\nstrip=")) + doof::to_string(dependency->stripComponents)) + std::string("\nref=")) + dependency->ref) + std::string("\ncommit=")) + dependency->commit) + std::string("\n"));
    const auto& _iterable_17 = dependency->copyFiles;
    for (const auto& copyFile : *_iterable_17) {
        (value += ((((std::string("copy=") + copyFile->source) + std::string("u0000")) + copyFile->destination) + std::string("\n")));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
std::string externalNativeFingerprint(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::shared_ptr<ExternalDependencyTarget> target) {
    auto value = ((((((((std::string("schema=1\ntarget=") + target->nativeTarget) + std::string("\nsdk=")) + target->sdkPath) + std::string("\ntriple=")) + target->targetTriple) + std::string("\nhost=")) + target->configureHost) + std::string("\n"));
    const auto& _iterable_18 = dependency->commands;
    for (const auto& command : *_iterable_18) {
        (value += externalCommandFingerprint(command));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
bool markerMatches(std::string path, std::string fingerprint) {
    if (!::doof_fs::exists(path)) {
        return false;
    }
    auto _binding_value_19 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_19)) {
        const auto& source = _binding_value_19;
        return false;
    }
    const auto source = doof::success_value(_binding_value_19);
    auto _binding_value_20 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_20)) {
        const auto& parsed = _binding_value_20;
        return false;
    }
    const auto parsed = doof::success_value(_binding_value_20);
    {
        auto _case_subject = parsed;
        if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            if (!(object->find(std::string("fingerprint")) != object->end())) {
                return false;
            }
            auto _binding_value_21 = doof::map_get(object, std::string("fingerprint"), "", 0);
            if (doof::is_failure(_binding_value_21)) {
                const auto& value = _binding_value_21;
                return false;
            }
            const auto value = doof::success_value(_binding_value_21);
            {
                auto _case_subject = value;
                if (doof::json_is_string(_case_subject)) {
                    const auto text = doof::json_as_string(_case_subject);
                    return (text == fingerprint);
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
            return false;
    }
    }
    doof::unreachable();
}
bool markerContentMatches(std::string path, std::string expected) {
    if (!::doof_fs::exists(path)) {
        return false;
    }
    auto _binding_value_22 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_22)) {
        const auto& source = _binding_value_22;
        return false;
    }
    const auto source = doof::success_value(_binding_value_22);
    return (source == expected);
}
void externalJsonSet(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string key, doof::JsonValue value) {
    doof::map_set(object, key, value, "", 0);
}
std::shared_ptr<std::vector<doof::JsonValue>> externalCommandsJson(std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>>> commands) {
    std::shared_ptr<std::vector<doof::JsonValue>> values = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    const auto& _iterable_23 = commands;
    for (const auto& command : *_iterable_23) {
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
        externalJsonSet(object, std::string("program"), doof::json_value(command->program));
        std::shared_ptr<std::vector<doof::JsonValue>> arguments = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
        const auto& _iterable_24 = command->args;
        for (const auto& argument : *_iterable_24) {
            arguments->push_back(doof::json_value(argument));
        }
        externalJsonSet(object, std::string("args"), doof::json_value(arguments));
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> environment = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
        const auto& _iterable_25 = command->env;
        for (const auto& [key, value] : *_iterable_25) {
            externalJsonSet(environment, key, doof::json_value(value));
        }
        externalJsonSet(object, std::string("env"), doof::json_value(environment));
        if (command->workingDirectory != std::string("")) {
            externalJsonSet(object, std::string("workingDirectory"), doof::json_value(command->workingDirectory));
        }
        values->push_back(doof::json_value(object));
    }
    return values;
}
std::string externalSourceMarkerContent(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string fingerprint) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> marker = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    externalJsonSet(marker, std::string("schemaVersion"), doof::json_value(1));
    externalJsonSet(marker, std::string("name"), doof::json_value(dependency->name));
    externalJsonSet(marker, std::string("kind"), doof::json_value(dependency->kind));
    externalJsonSet(marker, std::string("url"), doof::json_value(dependency->url));
    externalJsonSet(marker, std::string("destination"), doof::json_value(dependency->destination));
    externalJsonSet(marker, std::string("acquiredAt"), doof::json_value(std::string("")));
    externalJsonSet(marker, std::string("platform"), doof::json_value(::std_::os::index::platform()));
    externalJsonSet(marker, std::string("fingerprint"), doof::json_value(fingerprint));
    if (dependency->kind == std::string("archive")) {
        externalJsonSet(marker, std::string("sha256"), doof::json_value(dependency->sha256));
        externalJsonSet(marker, std::string("stripComponents"), doof::json_value(dependency->stripComponents));
        std::shared_ptr<std::vector<doof::JsonValue>> copies = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
        const auto& _iterable_26 = dependency->copyFiles;
        for (const auto& copyFile : *_iterable_26) {
            std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> copy = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
            externalJsonSet(copy, std::string("from"), doof::json_value(copyFile->source));
            externalJsonSet(copy, std::string("to"), doof::json_value(copyFile->destination));
            copies->push_back(doof::json_value(copy));
        }
        externalJsonSet(marker, std::string("copyFiles"), doof::json_value(copies));
    } else {
        externalJsonSet(marker, std::string("ref"), doof::json_value(dependency->ref));
        externalJsonSet(marker, std::string("commit"), doof::json_value(dependency->commit));
    }
    return (::doof_json::format(doof::json_value(marker)) + std::string("\n"));
}
std::string externalNativeMarkerContent(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::shared_ptr<ExternalDependencyTarget> target, std::string fingerprint) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> marker = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    externalJsonSet(marker, std::string("schemaVersion"), doof::json_value(1));
    externalJsonSet(marker, std::string("nativeTarget"), doof::json_value(target->nativeTarget));
    externalJsonSet(marker, std::string("builtAt"), doof::json_value(std::string("")));
    externalJsonSet(marker, std::string("sdkPath"), doof::json_value(target->sdkPath));
    externalJsonSet(marker, std::string("targetTriple"), doof::json_value(target->targetTriple));
    externalJsonSet(marker, std::string("configureHost"), doof::json_value(target->configureHost));
    externalJsonSet(marker, std::string("commands"), doof::json_value(externalCommandsJson(dependency->commands)));
    externalJsonSet(marker, std::string("fingerprint"), doof::json_value(fingerprint));
    return (::doof_json::format(doof::json_value(marker)) + std::string("\n"));
}
bool isEmptyExternalDirectory(std::string path) {
    if (!::doof_fs::isDirectory(path)) {
        return false;
    }
    auto _binding_value_27 = ::doof_fs::readDir(path);
    if (doof::is_failure(_binding_value_27)) {
        const auto& entries = _binding_value_27;
        return false;
    }
    const auto entries = doof::success_value(_binding_value_27);
    return (static_cast<int32_t>((entries)->size()) == 0);
}
doof::Result<void, std::string> copyArchiveContents(std::string sourceRoot, std::string destination) {
    if (!::doof_fs::isDirectory(sourceRoot)) {
        return doof::Failure<std::string>{ (std::string("stripped archive root is not a directory: ") + sourceRoot) };
    }
    auto _try_value_28 = ensureExternalDirectory(destination);
    if (doof::is_failure(_try_value_28)) return doof::Failure<std::string>{doof::failure_error(_try_value_28)};
    auto _binding_value_29 = ::doof_fs::readDir(sourceRoot);
    if (doof::is_failure(_binding_value_29)) {
        const auto error = doof::failure_error(_binding_value_29);
        return doof::Failure<std::string>{ std::string("Could not read extracted archive") };
    }
    const auto entries = doof::success_value(_binding_value_29);
    const auto& _iterable_30 = entries;
    for (const auto& entry : *_iterable_30) {
        auto _try_value_31 = copyExternalPath(externalPath(sourceRoot, entry->name), externalPath(destination, entry->name));
        if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::failure_error(_try_value_31)};
    }
    return doof::Success<void>{};
}
doof::Result<std::string, std::string> strippedArchiveRoot(std::string extractRoot, int32_t count, std::string dependencyName) {
    auto current = extractRoot;
    for (int32_t ignored = 0; ignored < count; ++ignored) {
        auto _binding_value_32 = ::doof_fs::readDir(current);
        if (doof::is_failure(_binding_value_32)) {
            const auto error = doof::failure_error(_binding_value_32);
            return doof::Failure<std::string>{ (std::string("Could not inspect archive for ") + dependencyName) };
        }
        const auto entries = doof::success_value(_binding_value_32);
        auto selected = std::string("");
        auto selectedCount = 0;
        const auto& _iterable_33 = entries;
        for (const auto& entry : *_iterable_33) {
            if (entry->name == std::string("__MACOSX")) {
                continue;
            }
            (selected = entry->name);
            (selectedCount += 1);
        }
        if (selectedCount != 1) {
            return doof::Failure<std::string>{ ((((std::string("External dependency ") + dependencyName) + std::string(" archive cannot strip ")) + doof::to_string(count)) + std::string(" component(s) from multiple roots")) };
        }
        (current = externalPath(current, selected));
    }
    return doof::Success<std::string>{ current };
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> downloadExternalArchive(std::string url) {
    if (doof::string_startsWith(url, std::string("file://"))) {
        const auto path = doof::string_substring(url, 7, static_cast<int32_t>(url.size()));
        auto _binding_value_34 = ::doof_fs::readBlob(path);
        if (doof::is_failure(_binding_value_34)) {
            const auto error = doof::failure_error(_binding_value_34);
            return doof::Failure<std::string>{ (std::string("Could not read local archive ") + path) };
        }
        const auto blob = doof::success_value(_binding_value_34);
        return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ blob };
    }
    const auto client = ::std_::http::index::createClient();
    auto _binding_value_35 = ::std_::http::index::get(client, url);
    if (doof::is_failure(_binding_value_35)) {
        const auto error = doof::failure_error(_binding_value_35);
        return doof::Failure<std::string>{ (((((std::string("HTTP request failed [") + error->kind) + std::string(", code=")) + error->code) + std::string("]: ")) + error->message) };
    }
    const auto response = doof::success_value(_binding_value_35);
    if (!response->ok()) {
        return doof::Failure<std::string>{ (((std::string("HTTP request failed with status ") + doof::to_string(response->status)) + std::string(" ")) + response->statusText) };
    }
    return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ response->getBlob() };
}
doof::Result<void, std::string> acquireArchive(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string destination, std::string stagingRoot) {
    const auto archivePath = externalPath(stagingRoot, std::string("source"));
    const auto extractRoot = externalPath(stagingRoot, std::string("extract"));
    const auto payloadRoot = externalPath(stagingRoot, std::string("payload"));
    auto _try_value_36 = ensureExternalDirectory(extractRoot);
    if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::failure_error(_try_value_36)};
    auto _try_value_37 = downloadExternalArchive(dependency->url);
    if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::failure_error(_try_value_37)};
    const auto archive = doof::success_value(_try_value_37);
    auto _binding_value_38 = ::doof_fs::writeBlob(archivePath, archive);
    if (doof::is_failure(_binding_value_38)) {
        const auto error = doof::failure_error(_binding_value_38);
        return doof::Failure<std::string>{ std::string("Could not stage downloaded archive") };
    }
    const auto actualSha256 = ::std_::crypto::index::sha256Hex(archive);
    if (actualSha256 != dependency->sha256) {
        return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" checksum mismatch: expected ")) + dependency->sha256) + std::string(", got ")) + actualSha256) };
    }
    if (doof::string_endsWith(doof::string_toLowerCase(dependency->url), std::string(".zip"))) {
        auto _try_value_39 = commandOutput(std::string("unzip"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-q"), archivePath, std::string("-d"), extractRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, std::nullopt, nullptr));
        if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::failure_error(_try_value_39)};
        const auto ignoredUnzip = doof::success_value(_try_value_39);
    } else {
        auto _try_value_40 = commandOutput(std::string("tar"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-xf"), archivePath, std::string("-C"), extractRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, std::nullopt, nullptr));
        if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::failure_error(_try_value_40)};
        const auto ignoredTar = doof::success_value(_try_value_40);
    }
    auto _try_value_41 = strippedArchiveRoot(extractRoot, dependency->stripComponents, dependency->name);
    if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::failure_error(_try_value_41)};
    const auto sourceRoot = doof::success_value(_try_value_41);
    auto _try_value_42 = copyArchiveContents(sourceRoot, payloadRoot);
    if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::failure_error(_try_value_42)};
    const auto& _iterable_43 = dependency->copyFiles;
    for (const auto& copyFile : *_iterable_43) {
        const auto sourcePath = externalPath(payloadRoot, copyFile->source);
        const auto destinationPath = externalPath(payloadRoot, copyFile->destination);
        if (!externalPathWithinRoot(sourcePath, payloadRoot) || !externalPathWithinRoot(destinationPath, payloadRoot)) {
            return doof::Failure<std::string>{ ((std::string("External dependency ") + dependency->name) + std::string(" copyFiles entries must stay within the destination")) };
        }
        auto _try_value_44 = copyExternalPath(sourcePath, destinationPath);
        if (doof::is_failure(_try_value_44)) return doof::Failure<std::string>{doof::failure_error(_try_value_44)};
    }
    auto _binding_value_45 = ::doof_fs::rename(payloadRoot, destination);
    if (doof::is_failure(_binding_value_45)) {
        const auto error = doof::failure_error(_binding_value_45);
        return doof::Failure<std::string>{ (std::string("Could not install external dependency ") + dependency->name) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> acquireGit(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string destination, std::string stagingRoot) {
    const auto repositoryRoot = externalPath(stagingRoot, std::string("repository"));
    auto _try_value_46 = commandOutput(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("clone"), std::string("--depth"), std::string("1"), std::string("--branch"), dependency->ref, dependency->url, repositoryRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, MAX_EXTERNAL_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::failure_error(_try_value_46)};
    const auto ignoredClone = doof::success_value(_try_value_46);
    auto _try_value_47 = commandOutput(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-C"), repositoryRoot, std::string("rev-parse"), std::string("HEAD")}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, std::nullopt, nullptr));
    if (doof::is_failure(_try_value_47)) return doof::Failure<std::string>{doof::failure_error(_try_value_47)};
    const auto actualCommit = doof::success_value(_try_value_47);
    if (doof::string_toLowerCase(actualCommit) != dependency->commit) {
        return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" commit mismatch: expected ")) + dependency->commit) + std::string(", got ")) + actualCommit) };
    }
    auto _try_value_48 = removeExternalTree(externalPath(repositoryRoot, std::string(".git")));
    if (doof::is_failure(_try_value_48)) return doof::Failure<std::string>{doof::failure_error(_try_value_48)};
    auto _binding_value_49 = ::doof_fs::rename(repositoryRoot, destination);
    if (doof::is_failure(_binding_value_49)) {
        const auto error = doof::failure_error(_binding_value_49);
        return doof::Failure<std::string>{ (std::string("Could not install external dependency ") + dependency->name) };
    }
    return doof::Success<void>{};
}
std::string applyExternalDependencySubstitutions(std::string value, std::string packageRoot, std::string destination, std::shared_ptr<ExternalDependencyTarget> target) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("${packageRoot}"), packageRoot), std::string("${destination}"), destination), std::string("${jobs}"), doof::to_string(((target->jobs < 1) ? 1 : target->jobs))), std::string("${nativeTarget}"), target->nativeTarget), std::string("${sdkPath}"), target->sdkPath), std::string("${targetTriple}"), target->targetTriple), std::string("${configureHost}"), target->configureHost);
}
doof::Result<void, std::string> runExternalCommands(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string packageRoot, std::string destination, std::shared_ptr<ExternalDependencyTarget> target) {
    const auto nativeMarker = externalPath(destination, ((std::string(".doof-external-native-") + target->nativeTarget) + std::string(".json")));
    const auto fingerprint = externalNativeFingerprint(dependency, target);
    if (markerMatches(nativeMarker, fingerprint)) {
        const auto content = externalNativeMarkerContent(dependency, target, fingerprint);
        if (!markerContentMatches(nativeMarker, content)) {
            auto _binding_value_50 = ::doof_fs::writeText(nativeMarker, content);
            if (doof::is_failure(_binding_value_50)) {
                const auto error = doof::failure_error(_binding_value_50);
                return doof::Failure<std::string>{ std::string("Could not refresh external dependency native marker") };
            }
        }
        return doof::Success<void>{};
    }
    for (int32_t index = 0; index < static_cast<int32_t>((dependency->commands)->size()); ++index) {
        const auto command = (*dependency->commands)[index];
        const auto workingDirectory = ((command->workingDirectory == std::string("")) ? destination : externalPath(destination, applyExternalDependencySubstitutions(command->workingDirectory, packageRoot, destination, target)));
        if (!externalPathWithinRoot(workingDirectory, destination)) {
            return doof::Failure<std::string>{ ((std::string("External dependency ") + dependency->name) + std::string(" command workingDirectory must stay within the destination")) };
        }
        std::shared_ptr<doof::ordered_map<std::string, std::string>> environment = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
        const auto& _iterable_51 = command->env;
        for (const auto& [key, value] : *_iterable_51) {
            doof::map_set(environment, key, applyExternalDependencySubstitutions(value, packageRoot, destination, target), "", 0);
        }
        const auto program = applyExternalDependencySubstitutions(command->program, packageRoot, destination, target);
        std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_52 = command->args;
        for (const auto& argument : *_iterable_52) {
            arguments->push_back(applyExternalDependencySubstitutions(argument, packageRoot, destination, target));
        }
        auto _binding_value_53 = commandOutput(program, arguments, std::make_shared<::std_::os::index::ExecOptions>(workingDirectory, doof::map_buildReadonly(environment, "", 0), true, false, true, false, MAX_EXTERNAL_COMMAND_OUTPUT_BYTES, nullptr));
        if (doof::is_failure(_binding_value_53)) {
            const auto error = doof::failure_error(_binding_value_53);
            return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" command ")) + doof::to_string((index + 1))) + std::string(" failed: ")) + error) };
        }
    }
    auto _binding_value_54 = ::doof_fs::writeText(nativeMarker, externalNativeMarkerContent(dependency, target, fingerprint));
    if (doof::is_failure(_binding_value_54)) {
        const auto error = doof::failure_error(_binding_value_54);
        return doof::Failure<std::string>{ std::string("Could not write external dependency native marker") };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> acquirePackageExternalDependencies(std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::shared_ptr<ExternalDependencyTarget> target) {
    if (manifest->manifestPath == std::string("")) {
        return doof::Success<void>{};
    }
    const auto& _iterable_55 = manifest->externalDependencies;
    for (const auto& dependency : *_iterable_55) {
        const auto destination = externalPath(manifest->rootDirectory, dependency->destination);
        const auto sourceMarker = externalPath(destination, EXTERNAL_SOURCE_MARKER);
        const auto fingerprint = externalSourceFingerprint(dependency);
        if (!markerMatches(sourceMarker, fingerprint)) {
            if (::doof_fs::exists(destination)) {
                if (!::doof_fs::exists(sourceMarker) && !isEmptyExternalDirectory(destination)) {
                    return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" destination already exists without ")) + EXTERNAL_SOURCE_MARKER) + std::string(": ")) + destination) };
                }
                auto _try_value_56 = removeExternalTree(destination);
                if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::failure_error(_try_value_56)};
            }
            const auto parent = ::std_::path::index::dirname(destination);
            auto _try_value_57 = ensureExternalDirectory(parent);
            if (doof::is_failure(_try_value_57)) return doof::Failure<std::string>{doof::failure_error(_try_value_57)};
            const auto stagingRoot = externalPath(parent, ((std::string(".doof-") + dependency->name) + std::string("-staging")));
            if (::doof_fs::exists(stagingRoot)) {
                auto _try_value_58 = removeExternalTree(stagingRoot);
                if (doof::is_failure(_try_value_58)) return doof::Failure<std::string>{doof::failure_error(_try_value_58)};
            }
            auto _try_value_59 = ensureExternalDirectory(stagingRoot);
            if (doof::is_failure(_try_value_59)) return doof::Failure<std::string>{doof::failure_error(_try_value_59)};
            const auto acquisition = ((dependency->kind == std::string("archive")) ? acquireArchive(dependency, destination, stagingRoot) : acquireGit(dependency, destination, stagingRoot));
            auto _binding_value_60 = acquisition;
            if (doof::is_failure(_binding_value_60)) {
                const auto error = doof::failure_error(_binding_value_60);
                auto _try_value_61 = removeExternalTree(destination);
                if (doof::is_failure(_try_value_61)) return doof::Failure<std::string>{doof::failure_error(_try_value_61)};
                auto _try_value_62 = removeExternalTree(stagingRoot);
                if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::failure_error(_try_value_62)};
                return doof::Failure<std::string>{ (((std::string("Failed to acquire external dependency ") + dependency->name) + std::string(": ")) + error) };
            }
            auto _try_value_63 = removeExternalTree(stagingRoot);
            if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::failure_error(_try_value_63)};
        }
        const auto content = externalSourceMarkerContent(dependency, fingerprint);
        if (!markerContentMatches(sourceMarker, content)) {
            auto _binding_value_64 = ::doof_fs::writeText(sourceMarker, content);
            if (doof::is_failure(_binding_value_64)) {
                const auto error = doof::failure_error(_binding_value_64);
                return doof::Failure<std::string>{ std::string("Could not refresh external dependency marker") };
            }
        }
        if (static_cast<int32_t>((dependency->commands)->size()) > 0) {
            auto _binding_value_65 = runExternalCommands(dependency, manifest->rootDirectory, destination, target);
            if (doof::is_failure(_binding_value_65)) {
                const auto error = doof::failure_error(_binding_value_65);
                const auto nativeMarker = externalPath(destination, ((std::string(".doof-external-native-") + target->nativeTarget) + std::string(".json")));
                if (::doof_fs::exists(nativeMarker)) {
                    auto _try_value_66 = removeExternalTree(nativeMarker);
                    if (doof::is_failure(_try_value_66)) return doof::Failure<std::string>{doof::failure_error(_try_value_66)};
                }
                return doof::Failure<std::string>{ (((((std::string("Failed to build external dependency ") + dependency->name) + std::string(" for ")) + target->nativeTarget) + std::string(": ")) + error) };
            }
        }
    }
    return doof::Success<void>{};
}
}
