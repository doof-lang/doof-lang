#include "src_external_dependency.hpp"

namespace app_src_external_dependency_ {
using namespace ::app_src_package_manifest_;
using namespace ::std_::blob::index;
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::http::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
std::string EXTERNAL_SOURCE_MARKER;
int64_t MAX_EXTERNAL_COMMAND_OUTPUT_BYTES = 1048576LL;

std::string externalPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
doof::Result<void, std::string> ensureExternalDirectory(const std::string& path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return doof::Success<void>{};
    }
    const auto parent = ::std_::path::index::dirname(path);
    if (parent != path) {
        auto _try_value_1 = ensureExternalDirectory(parent);
        if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    }
    auto _binding_value_2 = ::doof_fs::mkdir(path);
    if (doof::is_failure(_binding_value_2)) {
        const auto error = doof::failure_error(_binding_value_2);
        return doof::Failure<std::string>{ (std::string("Could not create directory ") + path) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> removeExternalTree(const std::string& path) {
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
        const auto& _iterable_5 = entries;
        for (const auto& entry : *_iterable_5) {
            auto _try_value_6 = removeExternalTree(externalPath(path, entry->name));
            if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
        }
    }
    auto _binding_value_7 = ::doof_fs::remove(path);
    if (doof::is_failure(_binding_value_7)) {
        const auto error = doof::failure_error(_binding_value_7);
        return doof::Failure<std::string>{ (std::string("Could not remove ") + path) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> copyExternalPath(const std::string& sourcePath, const std::string& destinationPath) {
    if (::doof_fs::isDirectory(sourcePath)) {
        auto _try_value_8 = ensureExternalDirectory(destinationPath);
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
        auto _binding_value_9 = ::doof_fs::readDir(sourcePath);
        if (doof::is_failure(_binding_value_9)) {
            const auto error = doof::failure_error(_binding_value_9);
            return doof::Failure<std::string>{ (std::string("Could not read directory ") + sourcePath) };
        }
        const auto entries = doof::success_value(_binding_value_9);
        const auto& _iterable_11 = entries;
        for (const auto& entry : *_iterable_11) {
            auto _try_value_12 = copyExternalPath(externalPath(sourcePath, entry->name), externalPath(destinationPath, entry->name));
            if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
        }
        if (::std_::os::index::platform() != std::string("windows")) {
            auto _binding_value_13 = ::doof_fs::copyPermissions(sourcePath, destinationPath);
            if (doof::is_failure(_binding_value_13)) {
                const auto error = doof::failure_error(_binding_value_13);
                return doof::Failure<std::string>{ (((std::string("Could not copy permissions from ") + sourcePath) + std::string(" to ")) + destinationPath) };
            }
        }
        return doof::Success<void>{};
    }
    auto _try_value_14 = ensureExternalDirectory(::std_::path::index::dirname(destinationPath));
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
    auto _binding_value_15 = ::doof_fs::readBlob(sourcePath);
    if (doof::is_failure(_binding_value_15)) {
        const auto error = doof::failure_error(_binding_value_15);
        return doof::Failure<std::string>{ (std::string("Could not read ") + sourcePath) };
    }
    const auto blob = doof::success_value(_binding_value_15);
    auto _binding_value_16 = ::doof_fs::writeBlob(destinationPath, blob);
    if (doof::is_failure(_binding_value_16)) {
        const auto error = doof::failure_error(_binding_value_16);
        return doof::Failure<std::string>{ (std::string("Could not write ") + destinationPath) };
    }
    if (::std_::os::index::platform() != std::string("windows")) {
        auto _binding_value_17 = ::doof_fs::copyPermissions(sourcePath, destinationPath);
        if (doof::is_failure(_binding_value_17)) {
            const auto error = doof::failure_error(_binding_value_17);
            return doof::Failure<std::string>{ (((std::string("Could not copy permissions from ") + sourcePath) + std::string(" to ")) + destinationPath) };
        }
    }
    return doof::Success<void>{};
}
bool externalPathWithinRoot(const std::string& path, const std::string& root) {
    const auto boundary = (doof::string_endsWith(root, std::string("/")) ? root : (root + std::string("/")));
    return ((path == root) || doof::string_startsWith(path, boundary));
}
doof::Result<std::string, std::string> commandOutput(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::shared_ptr<::std_::os::index::ExecOptions>& options) {
    auto _binding_value_18 = ::std_::os::index::run(command, arguments, options);
    if (doof::is_failure(_binding_value_18)) {
        const auto error = doof::failure_error(_binding_value_18);
        return doof::Failure<std::string>{ ((command + std::string(": ")) + error) };
    }
    const auto result = doof::success_value(_binding_value_18);
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->stdout_, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->stdout_)->size()))));
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ (((command + std::string(" exited with code ")) + doof::to_string(result->exitCode)) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    return doof::Success<std::string>{ output };
}
std::string externalCommandFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>& command) {
    auto result = (((command->program + std::string("\n")) + command->workingDirectory) + std::string("\n"));
    const auto& _iterable_20 = command->args;
    for (const auto& argument : *_iterable_20) {
        (result += ((std::string("arg=") + argument) + std::string("\n")));
    }
    const auto& _iterable_22 = command->env;
    for (const auto& [key, value] : *_iterable_22) {
        (result += ((((std::string("env=") + key) + std::string("=")) + value) + std::string("\n")));
    }
    return result;
}
std::string externalSourceFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency) {
    auto value = ((((((((((((((((std::string("schema=1\nname=") + dependency->name) + std::string("\nkind=")) + dependency->kind) + std::string("\nurl=")) + dependency->url) + std::string("\ndestination=")) + dependency->destination) + std::string("\nsha256=")) + dependency->sha256) + std::string("\nstrip=")) + doof::to_string(dependency->stripComponents)) + std::string("\nref=")) + dependency->ref) + std::string("\ncommit=")) + dependency->commit) + std::string("\n"));
    const auto& _iterable_24 = dependency->copyFiles;
    for (const auto& copyFile : *_iterable_24) {
        (value += ((((std::string("copy=") + copyFile->source) + std::string("u0000")) + copyFile->destination) + std::string("\n")));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
std::string externalNativeFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<ExternalDependencyTarget>& target) {
    auto value = ((((((((std::string("schema=1\ntarget=") + target->nativeTarget) + std::string("\nsdk=")) + target->sdkPath) + std::string("\ntriple=")) + target->targetTriple) + std::string("\nhost=")) + target->configureHost) + std::string("\n"));
    const auto& _iterable_26 = dependency->commands;
    for (const auto& command : *_iterable_26) {
        (value += externalCommandFingerprint(command));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
bool markerMatches(const std::string& path, const std::string& fingerprint) {
    if (!::doof_fs::exists(path)) {
        return false;
    }
    auto _binding_value_27 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_27)) {
        const auto& source = _binding_value_27;
        return false;
    }
    const auto source = doof::success_value(_binding_value_27);
    auto _binding_value_28 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_28)) {
        const auto& parsed = _binding_value_28;
        return false;
    }
    const auto parsed = doof::success_value(_binding_value_28);
    {
        auto _case_subject = parsed;
        if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            if (![&]() -> bool { auto _map_has_29 = object; return _map_has_29->find(std::string("fingerprint")) != _map_has_29->end(); }()) {
                return false;
            }
            auto _binding_value_30 = doof::map_get(object, std::string("fingerprint"), "", 0);
            if (doof::is_failure(_binding_value_30)) {
                const auto& value = _binding_value_30;
                return false;
            }
            const auto value = doof::success_value(_binding_value_30);
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
bool markerContentMatches(const std::string& path, const std::string& expected) {
    if (!::doof_fs::exists(path)) {
        return false;
    }
    auto _binding_value_31 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_31)) {
        const auto& source = _binding_value_31;
        return false;
    }
    const auto source = doof::success_value(_binding_value_31);
    return (source == expected);
}
void externalJsonSet(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& key, const doof::JsonValue& value) {
    doof::map_set(object, key, value, "", 0);
}
std::shared_ptr<std::vector<doof::JsonValue>> externalCommandsJson(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>>>& commands) {
    std::shared_ptr<std::vector<doof::JsonValue>> values = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    const auto& _iterable_33 = commands;
    for (const auto& command : *_iterable_33) {
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
        externalJsonSet(object, std::string("program"), doof::json_value(command->program));
        std::shared_ptr<std::vector<doof::JsonValue>> arguments = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
        const auto& _iterable_35 = command->args;
        for (const auto& argument : *_iterable_35) {
            arguments->push_back(doof::json_value(argument));
        }
        externalJsonSet(object, std::string("args"), doof::json_value(arguments));
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> environment = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
        const auto& _iterable_37 = command->env;
        for (const auto& [key, value] : *_iterable_37) {
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
std::string externalSourceMarkerContent(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& fingerprint) {
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
        const auto& _iterable_39 = dependency->copyFiles;
        for (const auto& copyFile : *_iterable_39) {
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
std::string externalNativeMarkerContent(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<ExternalDependencyTarget>& target, const std::string& fingerprint) {
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
bool isEmptyExternalDirectory(const std::string& path) {
    if (!::doof_fs::isDirectory(path)) {
        return false;
    }
    auto _binding_value_40 = ::doof_fs::readDir(path);
    if (doof::is_failure(_binding_value_40)) {
        const auto& entries = _binding_value_40;
        return false;
    }
    const auto entries = doof::success_value(_binding_value_40);
    return (static_cast<int32_t>((entries)->size()) == 0);
}
doof::Result<void, std::string> copyArchiveContents(const std::string& sourceRoot, const std::string& destination) {
    if (!::doof_fs::isDirectory(sourceRoot)) {
        return doof::Failure<std::string>{ (std::string("stripped archive root is not a directory: ") + sourceRoot) };
    }
    auto _try_value_41 = ensureExternalDirectory(destination);
    if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_41))};
    auto _binding_value_42 = ::doof_fs::readDir(sourceRoot);
    if (doof::is_failure(_binding_value_42)) {
        const auto error = doof::failure_error(_binding_value_42);
        return doof::Failure<std::string>{ std::string("Could not read extracted archive") };
    }
    const auto entries = doof::success_value(_binding_value_42);
    const auto& _iterable_44 = entries;
    for (const auto& entry : *_iterable_44) {
        auto _try_value_45 = copyExternalPath(externalPath(sourceRoot, entry->name), externalPath(destination, entry->name));
        if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_45))};
    }
    return doof::Success<void>{};
}
doof::Result<std::string, std::string> strippedArchiveRoot(const std::string& extractRoot, int32_t count, const std::string& dependencyName) {
    auto current = extractRoot;
    for (int32_t ignored = 0; ignored < count; ++ignored) {
        auto _binding_value_47 = ::doof_fs::readDir(current);
        if (doof::is_failure(_binding_value_47)) {
            const auto error = doof::failure_error(_binding_value_47);
            return doof::Failure<std::string>{ (std::string("Could not inspect archive for ") + dependencyName) };
        }
        const auto entries = doof::success_value(_binding_value_47);
        auto selected = std::string("");
        auto selectedCount = 0;
        const auto& _iterable_49 = entries;
        for (const auto& entry : *_iterable_49) {
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
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> downloadExternalArchive(const std::string& url) {
    if (doof::string_startsWith(url, std::string("file://"))) {
        const auto path = doof::string_substring(url, 7, static_cast<int32_t>(url.size()));
        auto _binding_value_50 = ::doof_fs::readBlob(path);
        if (doof::is_failure(_binding_value_50)) {
            const auto error = doof::failure_error(_binding_value_50);
            return doof::Failure<std::string>{ (std::string("Could not read local archive ") + path) };
        }
        const auto blob = doof::success_value(_binding_value_50);
        return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ blob };
    }
    const auto client = ::std_::http::index::createClient();
    auto _binding_value_51 = ::std_::http::index::get(client, url);
    if (doof::is_failure(_binding_value_51)) {
        const auto error = doof::failure_error(_binding_value_51);
        return doof::Failure<std::string>{ (((((std::string("HTTP request failed [") + error->kind) + std::string(", code=")) + error->code) + std::string("]: ")) + error->message) };
    }
    const auto response = doof::success_value(_binding_value_51);
    if (!response->ok()) {
        return doof::Failure<std::string>{ (((std::string("HTTP request failed with status ") + doof::to_string(response->status)) + std::string(" ")) + response->statusText) };
    }
    return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ response->getBlob() };
}
doof::Result<void, std::string> acquireArchive(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& destination, const std::string& stagingRoot) {
    const auto archivePath = externalPath(stagingRoot, std::string("source"));
    const auto extractRoot = externalPath(stagingRoot, std::string("extract"));
    const auto payloadRoot = externalPath(stagingRoot, std::string("payload"));
    auto _try_value_52 = ensureExternalDirectory(extractRoot);
    if (doof::is_failure(_try_value_52)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_52))};
    auto _try_value_53 = downloadExternalArchive(dependency->url);
    if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_53))};
    const auto archive = doof::success_value(_try_value_53);
    auto _binding_value_54 = ::doof_fs::writeBlob(archivePath, archive);
    if (doof::is_failure(_binding_value_54)) {
        const auto error = doof::failure_error(_binding_value_54);
        return doof::Failure<std::string>{ std::string("Could not stage downloaded archive") };
    }
    const auto actualSha256 = ::std_::crypto::index::sha256Hex(archive);
    if (actualSha256 != dependency->sha256) {
        return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" checksum mismatch: expected ")) + dependency->sha256) + std::string(", got ")) + actualSha256) };
    }
    if (doof::string_endsWith(doof::string_toLowerCase(dependency->url), std::string(".zip"))) {
        auto _try_value_55 = commandOutput(std::string("unzip"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-q"), archivePath, std::string("-d"), extractRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
        if (doof::is_failure(_try_value_55)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_55))};
        const auto ignoredUnzip = doof::success_value(_try_value_55);
    } else {
        auto _try_value_56 = commandOutput(std::string("tar"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-xf"), archivePath, std::string("-C"), extractRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
        if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_56))};
        const auto ignoredTar = doof::success_value(_try_value_56);
    }
    auto _try_value_57 = strippedArchiveRoot(extractRoot, dependency->stripComponents, dependency->name);
    if (doof::is_failure(_try_value_57)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_57))};
    const auto sourceRoot = doof::success_value(_try_value_57);
    auto _try_value_58 = copyArchiveContents(sourceRoot, payloadRoot);
    if (doof::is_failure(_try_value_58)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_58))};
    const auto& _iterable_60 = dependency->copyFiles;
    for (const auto& copyFile : *_iterable_60) {
        const auto sourcePath = externalPath(payloadRoot, copyFile->source);
        const auto destinationPath = externalPath(payloadRoot, copyFile->destination);
        if (!externalPathWithinRoot(sourcePath, payloadRoot) || !externalPathWithinRoot(destinationPath, payloadRoot)) {
            return doof::Failure<std::string>{ ((std::string("External dependency ") + dependency->name) + std::string(" copyFiles entries must stay within the destination")) };
        }
        auto _try_value_61 = copyExternalPath(sourcePath, destinationPath);
        if (doof::is_failure(_try_value_61)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_61))};
    }
    auto _binding_value_62 = ::doof_fs::rename(payloadRoot, destination);
    if (doof::is_failure(_binding_value_62)) {
        const auto error = doof::failure_error(_binding_value_62);
        return doof::Failure<std::string>{ (std::string("Could not install external dependency ") + dependency->name) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> acquireGit(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& destination, const std::string& stagingRoot) {
    const auto repositoryRoot = externalPath(stagingRoot, std::string("repository"));
    auto _try_value_63 = commandOutput(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("clone"), std::string("--depth"), std::string("1"), std::string("--branch"), dependency->ref, dependency->url, repositoryRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_EXTERNAL_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_63))};
    const auto ignoredClone = doof::success_value(_try_value_63);
    auto _try_value_64 = commandOutput(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-C"), repositoryRoot, std::string("rev-parse"), std::string("HEAD")}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
    if (doof::is_failure(_try_value_64)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_64))};
    const auto actualCommit = doof::success_value(_try_value_64);
    if (doof::string_toLowerCase(actualCommit) != dependency->commit) {
        return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" commit mismatch: expected ")) + dependency->commit) + std::string(", got ")) + actualCommit) };
    }
    auto _try_value_65 = removeExternalTree(externalPath(repositoryRoot, std::string(".git")));
    if (doof::is_failure(_try_value_65)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_65))};
    auto _binding_value_66 = ::doof_fs::rename(repositoryRoot, destination);
    if (doof::is_failure(_binding_value_66)) {
        const auto error = doof::failure_error(_binding_value_66);
        return doof::Failure<std::string>{ (std::string("Could not install external dependency ") + dependency->name) };
    }
    return doof::Success<void>{};
}
std::string applyExternalDependencySubstitutions(const std::string& value, const std::string& packageRoot, const std::string& destination, const std::shared_ptr<ExternalDependencyTarget>& target) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("${packageRoot}"), packageRoot), std::string("${destination}"), destination), std::string("${jobs}"), doof::to_string(((target->jobs < 1) ? 1 : target->jobs))), std::string("${nativeTarget}"), target->nativeTarget), std::string("${sdkPath}"), target->sdkPath), std::string("${targetTriple}"), target->targetTriple), std::string("${configureHost}"), target->configureHost);
}
doof::Result<void, std::string> runExternalCommands(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& packageRoot, const std::string& destination, const std::shared_ptr<ExternalDependencyTarget>& target) {
    const auto nativeMarker = externalPath(destination, ((std::string(".doof-external-native-") + target->nativeTarget) + std::string(".json")));
    const auto fingerprint = externalNativeFingerprint(dependency, target);
    if (markerMatches(nativeMarker, fingerprint)) {
        const auto content = externalNativeMarkerContent(dependency, target, fingerprint);
        if (!markerContentMatches(nativeMarker, content)) {
            auto _binding_value_67 = ::doof_fs::writeText(nativeMarker, content);
            if (doof::is_failure(_binding_value_67)) {
                const auto error = doof::failure_error(_binding_value_67);
                return doof::Failure<std::string>{ std::string("Could not refresh external dependency native marker") };
            }
        }
        return doof::Success<void>{};
    }
    for (int32_t index = 0; index < static_cast<int32_t>((dependency->commands)->size()); ++index) {
        const auto command = doof::array_at(dependency->commands, index, "src/external-dependency", 332);
        const auto workingDirectory = ((command->workingDirectory == std::string("")) ? destination : externalPath(destination, applyExternalDependencySubstitutions(command->workingDirectory, packageRoot, destination, target)));
        if (!externalPathWithinRoot(workingDirectory, destination)) {
            return doof::Failure<std::string>{ ((std::string("External dependency ") + dependency->name) + std::string(" command workingDirectory must stay within the destination")) };
        }
        std::shared_ptr<doof::ordered_map<std::string, std::string>> environment = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
        const auto& _iterable_70 = command->env;
        for (const auto& [key, value] : *_iterable_70) {
            doof::map_set(environment, key, applyExternalDependencySubstitutions(value, packageRoot, destination, target), "", 0);
        }
        const auto program = applyExternalDependencySubstitutions(command->program, packageRoot, destination, target);
        std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_72 = command->args;
        for (const auto& argument : *_iterable_72) {
            arguments->push_back(applyExternalDependencySubstitutions(argument, packageRoot, destination, target));
        }
        auto _binding_value_73 = commandOutput(program, arguments, std::make_shared<::std_::os::index::ExecOptions>(workingDirectory, doof::map_drainToReadonly(environment, "", 0), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_EXTERNAL_COMMAND_OUTPUT_BYTES, nullptr));
        if (doof::is_failure(_binding_value_73)) {
            const auto error = doof::failure_error(_binding_value_73);
            return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" command ")) + doof::to_string((index + 1))) + std::string(" failed: ")) + error) };
        }
    }
    auto _binding_value_74 = ::doof_fs::writeText(nativeMarker, externalNativeMarkerContent(dependency, target, fingerprint));
    if (doof::is_failure(_binding_value_74)) {
        const auto error = doof::failure_error(_binding_value_74);
        return doof::Failure<std::string>{ std::string("Could not write external dependency native marker") };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> acquirePackageExternalDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<ExternalDependencyTarget>& target) {
    if (manifest->manifestPath == std::string("")) {
        return doof::Success<void>{};
    }
    const auto& _iterable_76 = manifest->externalDependencies;
    for (const auto& dependency : *_iterable_76) {
        const auto destination = externalPath(manifest->rootDirectory, dependency->destination);
        const auto sourceMarker = externalPath(destination, EXTERNAL_SOURCE_MARKER);
        const auto fingerprint = externalSourceFingerprint(dependency);
        if (!markerMatches(sourceMarker, fingerprint)) {
            if (::doof_fs::exists(destination)) {
                if (!::doof_fs::exists(sourceMarker) && !isEmptyExternalDirectory(destination)) {
                    return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" destination already exists without ")) + EXTERNAL_SOURCE_MARKER) + std::string(": ")) + destination) };
                }
                auto _try_value_77 = removeExternalTree(destination);
                if (doof::is_failure(_try_value_77)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_77))};
            }
            const auto parent = ::std_::path::index::dirname(destination);
            auto _try_value_78 = ensureExternalDirectory(parent);
            if (doof::is_failure(_try_value_78)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_78))};
            const auto stagingRoot = externalPath(parent, ((std::string(".doof-") + dependency->name) + std::string("-staging")));
            if (::doof_fs::exists(stagingRoot)) {
                auto _try_value_79 = removeExternalTree(stagingRoot);
                if (doof::is_failure(_try_value_79)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_79))};
            }
            auto _try_value_80 = ensureExternalDirectory(stagingRoot);
            if (doof::is_failure(_try_value_80)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_80))};
            const auto acquisition = ((dependency->kind == std::string("archive")) ? acquireArchive(dependency, destination, stagingRoot) : acquireGit(dependency, destination, stagingRoot));
            auto _binding_value_81 = acquisition;
            if (doof::is_failure(_binding_value_81)) {
                const auto error = doof::failure_error(_binding_value_81);
                auto _try_value_82 = removeExternalTree(destination);
                if (doof::is_failure(_try_value_82)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_82))};
                auto _try_value_83 = removeExternalTree(stagingRoot);
                if (doof::is_failure(_try_value_83)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_83))};
                return doof::Failure<std::string>{ (((std::string("Failed to acquire external dependency ") + dependency->name) + std::string(": ")) + error) };
            }
            auto _try_value_84 = removeExternalTree(stagingRoot);
            if (doof::is_failure(_try_value_84)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_84))};
        }
        const auto content = externalSourceMarkerContent(dependency, fingerprint);
        if (!markerContentMatches(sourceMarker, content)) {
            auto _binding_value_85 = ::doof_fs::writeText(sourceMarker, content);
            if (doof::is_failure(_binding_value_85)) {
                const auto error = doof::failure_error(_binding_value_85);
                return doof::Failure<std::string>{ std::string("Could not refresh external dependency marker") };
            }
        }
        if (static_cast<int32_t>((dependency->commands)->size()) > 0) {
            auto _binding_value_86 = runExternalCommands(dependency, manifest->rootDirectory, destination, target);
            if (doof::is_failure(_binding_value_86)) {
                const auto error = doof::failure_error(_binding_value_86);
                const auto nativeMarker = externalPath(destination, ((std::string(".doof-external-native-") + target->nativeTarget) + std::string(".json")));
                if (::doof_fs::exists(nativeMarker)) {
                    auto _try_value_87 = removeExternalTree(nativeMarker);
                    if (doof::is_failure(_try_value_87)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_87))};
                }
                return doof::Failure<std::string>{ (((((std::string("Failed to build external dependency ") + dependency->name) + std::string(" for ")) + target->nativeTarget) + std::string(": ")) + error) };
            }
        }
    }
    return doof::Success<void>{};
}

void __doof_initialize_module() {
        EXTERNAL_SOURCE_MARKER = std::string(".doof-external.json");
}
}
