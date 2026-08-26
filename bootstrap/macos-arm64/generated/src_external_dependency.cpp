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

#line 27 "/src/external-dependency.do"
std::string externalPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
#line 29 "/src/external-dependency.do"
doof::Result<void, std::string> ensureExternalDirectory(const std::string& path) {
#line 30 "/src/external-dependency.do"
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
#line 30 "/src/external-dependency.do"
        return doof::Success<void>{};
    }
#line 31 "/src/external-dependency.do"
    const auto parent = ::std_::path::index::dirname(path);
#line 32 "/src/external-dependency.do"
    if (parent != path) {
#line 32 "/src/external-dependency.do"
        auto _try_value_1 = ensureExternalDirectory(parent);
        if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    }
#line 33 "/src/external-dependency.do"
    auto _binding_value_2 = ::doof_fs::mkdir(path);
    if (doof::is_failure(_binding_value_2)) {
        const auto error = doof::failure_error(_binding_value_2);
#line 33 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (std::string("Could not create directory ") + path) };
    }
#line 34 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 37 "/src/external-dependency.do"
doof::Result<void, std::string> removeExternalTree(const std::string& path) {
#line 38 "/src/external-dependency.do"
    if (!::doof_fs::exists(path)) {
#line 38 "/src/external-dependency.do"
        return doof::Success<void>{};
    }
#line 39 "/src/external-dependency.do"
    if (::doof_fs::isDirectory(path)) {
#line 40 "/src/external-dependency.do"
        auto _binding_value_3 = ::doof_fs::readDir(path);
        if (doof::is_failure(_binding_value_3)) {
            const auto error = doof::failure_error(_binding_value_3);
#line 40 "/src/external-dependency.do"
            return doof::Failure<std::string>{ (std::string("Could not read directory ") + path) };
        }
        const auto entries = doof::success_value(_binding_value_3);
#line 41 "/src/external-dependency.do"
        const auto& _iterable_5 = entries;
        for (const auto& entry : *_iterable_5) {
#line 41 "/src/external-dependency.do"
            auto _try_value_6 = removeExternalTree(externalPath(path, entry->name));
            if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
        }
    }
#line 43 "/src/external-dependency.do"
    auto _binding_value_7 = ::doof_fs::remove(path);
    if (doof::is_failure(_binding_value_7)) {
        const auto error = doof::failure_error(_binding_value_7);
#line 43 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (std::string("Could not remove ") + path) };
    }
#line 44 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 47 "/src/external-dependency.do"
doof::Result<void, std::string> copyExternalPath(const std::string& sourcePath, const std::string& destinationPath) {
#line 48 "/src/external-dependency.do"
    if (::doof_fs::isDirectory(sourcePath)) {
#line 49 "/src/external-dependency.do"
        auto _try_value_8 = ensureExternalDirectory(destinationPath);
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
#line 50 "/src/external-dependency.do"
        auto _binding_value_9 = ::doof_fs::readDir(sourcePath);
        if (doof::is_failure(_binding_value_9)) {
            const auto error = doof::failure_error(_binding_value_9);
#line 50 "/src/external-dependency.do"
            return doof::Failure<std::string>{ (std::string("Could not read directory ") + sourcePath) };
        }
        const auto entries = doof::success_value(_binding_value_9);
#line 51 "/src/external-dependency.do"
        const auto& _iterable_11 = entries;
        for (const auto& entry : *_iterable_11) {
#line 52 "/src/external-dependency.do"
            auto _try_value_12 = copyExternalPath(externalPath(sourcePath, entry->name), externalPath(destinationPath, entry->name));
            if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
        }
#line 54 "/src/external-dependency.do"
        return doof::Success<void>{};
    }
#line 56 "/src/external-dependency.do"
    auto _try_value_13 = ensureExternalDirectory(::std_::path::index::dirname(destinationPath));
    if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
#line 57 "/src/external-dependency.do"
    auto _binding_value_14 = ::doof_fs::readBlob(sourcePath);
    if (doof::is_failure(_binding_value_14)) {
        const auto error = doof::failure_error(_binding_value_14);
#line 57 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (std::string("Could not read ") + sourcePath) };
    }
    const auto blob = doof::success_value(_binding_value_14);
#line 58 "/src/external-dependency.do"
    auto _binding_value_15 = ::doof_fs::writeBlob(destinationPath, blob);
    if (doof::is_failure(_binding_value_15)) {
        const auto error = doof::failure_error(_binding_value_15);
#line 58 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (std::string("Could not write ") + destinationPath) };
    }
#line 59 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 62 "/src/external-dependency.do"
bool externalPathWithinRoot(const std::string& path, const std::string& root) {
#line 63 "/src/external-dependency.do"
    const auto boundary = (doof::string_endsWith(root, std::string("/")) ? root : (root + std::string("/")));
#line 64 "/src/external-dependency.do"
    return ((path == root) || doof::string_startsWith(path, boundary));
}
#line 67 "/src/external-dependency.do"
doof::Result<std::string, std::string> commandOutput(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::shared_ptr<::std_::os::index::ExecOptions>& options) {
#line 68 "/src/external-dependency.do"
    auto _binding_value_16 = ::std_::os::index::run(command, arguments, options);
    if (doof::is_failure(_binding_value_16)) {
        const auto error = doof::failure_error(_binding_value_16);
#line 68 "/src/external-dependency.do"
        return doof::Failure<std::string>{ ((command + std::string(": ")) + error) };
    }
    const auto result = doof::success_value(_binding_value_16);
#line 69 "/src/external-dependency.do"
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->stdout_, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->stdout_)->size()))));
#line 70 "/src/external-dependency.do"
    if (result->exitCode != 0) {
#line 71 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (((command + std::string(" exited with code ")) + doof::to_string(result->exitCode)) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
#line 73 "/src/external-dependency.do"
    return doof::Success<std::string>{ output };
}
#line 76 "/src/external-dependency.do"
std::string externalCommandFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>& command) {
#line 77 "/src/external-dependency.do"
    auto result = (((command->program + std::string("\n")) + command->workingDirectory) + std::string("\n"));
#line 78 "/src/external-dependency.do"
    const auto& _iterable_18 = command->args;
    for (const auto& argument : *_iterable_18) {
#line 78 "/src/external-dependency.do"
        (result += ((std::string("arg=") + argument) + std::string("\n")));
    }
#line 79 "/src/external-dependency.do"
    const auto& _iterable_20 = command->env;
    for (const auto& [key, value] : *_iterable_20) {
#line 79 "/src/external-dependency.do"
        (result += ((((std::string("env=") + key) + std::string("=")) + value) + std::string("\n")));
    }
#line 80 "/src/external-dependency.do"
    return result;
}
#line 83 "/src/external-dependency.do"
std::string externalSourceFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency) {
#line 84 "/src/external-dependency.do"
    auto value = ((((((((((((((((std::string("schema=1\nname=") + dependency->name) + std::string("\nkind=")) + dependency->kind) + std::string("\nurl=")) + dependency->url) + std::string("\ndestination=")) + dependency->destination) + std::string("\nsha256=")) + dependency->sha256) + std::string("\nstrip=")) + doof::to_string(dependency->stripComponents)) + std::string("\nref=")) + dependency->ref) + std::string("\ncommit=")) + dependency->commit) + std::string("\n"));
#line 87 "/src/external-dependency.do"
    const auto& _iterable_22 = dependency->copyFiles;
    for (const auto& copyFile : *_iterable_22) {
#line 88 "/src/external-dependency.do"
        (value += ((((std::string("copy=") + copyFile->source) + std::string("u0000")) + copyFile->destination) + std::string("\n")));
    }
#line 90 "/src/external-dependency.do"
    return ::std_::crypto::index::sha256HexString(value);
}
#line 93 "/src/external-dependency.do"
std::string externalNativeFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<ExternalDependencyTarget>& target) {
#line 97 "/src/external-dependency.do"
    auto value = ((((((((std::string("schema=1\ntarget=") + target->nativeTarget) + std::string("\nsdk=")) + target->sdkPath) + std::string("\ntriple=")) + target->targetTriple) + std::string("\nhost=")) + target->configureHost) + std::string("\n"));
#line 99 "/src/external-dependency.do"
    const auto& _iterable_24 = dependency->commands;
    for (const auto& command : *_iterable_24) {
#line 99 "/src/external-dependency.do"
        (value += externalCommandFingerprint(command));
    }
#line 100 "/src/external-dependency.do"
    return ::std_::crypto::index::sha256HexString(value);
}
#line 103 "/src/external-dependency.do"
bool markerMatches(const std::string& path, const std::string& fingerprint) {
#line 104 "/src/external-dependency.do"
    if (!::doof_fs::exists(path)) {
#line 104 "/src/external-dependency.do"
        return false;
    }
#line 105 "/src/external-dependency.do"
    auto _binding_value_25 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_25)) {
        const auto& source = _binding_value_25;
#line 105 "/src/external-dependency.do"
        return false;
    }
    const auto source = doof::success_value(_binding_value_25);
#line 106 "/src/external-dependency.do"
    auto _binding_value_26 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_26)) {
        const auto& parsed = _binding_value_26;
#line 106 "/src/external-dependency.do"
        return false;
    }
    const auto parsed = doof::success_value(_binding_value_26);
#line 107 "/src/external-dependency.do"
    {
        auto _case_subject = parsed;
        if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
#line 109 "/src/external-dependency.do"
            if (![&]() -> bool { auto _map_has_27 = object; return _map_has_27->find(std::string("fingerprint")) != _map_has_27->end(); }()) {
#line 109 "/src/external-dependency.do"
                return false;
            }
#line 110 "/src/external-dependency.do"
            auto _binding_value_28 = doof::map_get(object, std::string("fingerprint"), "", 0);
            if (doof::is_failure(_binding_value_28)) {
                const auto& value = _binding_value_28;
#line 110 "/src/external-dependency.do"
                return false;
            }
            const auto value = doof::success_value(_binding_value_28);
#line 111 "/src/external-dependency.do"
            {
                auto _case_subject = value;
                if (doof::json_is_string(_case_subject)) {
                    const auto text = doof::json_as_string(_case_subject);
#line 112 "/src/external-dependency.do"
                    return (text == fingerprint);
            }
            else {
#line 113 "/src/external-dependency.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 116 "/src/external-dependency.do"
            return false;
    }
    }
    doof::unreachable();
}
#line 120 "/src/external-dependency.do"
bool markerContentMatches(const std::string& path, const std::string& expected) {
#line 121 "/src/external-dependency.do"
    if (!::doof_fs::exists(path)) {
#line 121 "/src/external-dependency.do"
        return false;
    }
#line 122 "/src/external-dependency.do"
    auto _binding_value_29 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_29)) {
        const auto& source = _binding_value_29;
#line 122 "/src/external-dependency.do"
        return false;
    }
    const auto source = doof::success_value(_binding_value_29);
#line 123 "/src/external-dependency.do"
    return (source == expected);
}
#line 126 "/src/external-dependency.do"
void externalJsonSet(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& key, const doof::JsonValue& value) {
#line 127 "/src/external-dependency.do"
    doof::map_set(object, key, value, "", 0);
}
#line 130 "/src/external-dependency.do"
std::shared_ptr<std::vector<doof::JsonValue>> externalCommandsJson(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>>>& commands) {
#line 131 "/src/external-dependency.do"
    std::shared_ptr<std::vector<doof::JsonValue>> values = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
#line 132 "/src/external-dependency.do"
    const auto& _iterable_31 = commands;
    for (const auto& command : *_iterable_31) {
#line 133 "/src/external-dependency.do"
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 134 "/src/external-dependency.do"
        externalJsonSet(object, std::string("program"), doof::json_value(command->program));
#line 135 "/src/external-dependency.do"
        std::shared_ptr<std::vector<doof::JsonValue>> arguments = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
#line 136 "/src/external-dependency.do"
        const auto& _iterable_33 = command->args;
        for (const auto& argument : *_iterable_33) {
#line 136 "/src/external-dependency.do"
            arguments->push_back(doof::json_value(argument));
        }
#line 137 "/src/external-dependency.do"
        externalJsonSet(object, std::string("args"), doof::json_value(arguments));
#line 138 "/src/external-dependency.do"
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> environment = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 139 "/src/external-dependency.do"
        const auto& _iterable_35 = command->env;
        for (const auto& [key, value] : *_iterable_35) {
#line 139 "/src/external-dependency.do"
            externalJsonSet(environment, key, doof::json_value(value));
        }
#line 140 "/src/external-dependency.do"
        externalJsonSet(object, std::string("env"), doof::json_value(environment));
#line 141 "/src/external-dependency.do"
        if (command->workingDirectory != std::string("")) {
#line 141 "/src/external-dependency.do"
            externalJsonSet(object, std::string("workingDirectory"), doof::json_value(command->workingDirectory));
        }
#line 142 "/src/external-dependency.do"
        values->push_back(doof::json_value(object));
    }
#line 144 "/src/external-dependency.do"
    return values;
}
#line 147 "/src/external-dependency.do"
std::string externalSourceMarkerContent(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& fingerprint) {
#line 148 "/src/external-dependency.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> marker = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 149 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("schemaVersion"), doof::json_value(1));
#line 150 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("name"), doof::json_value(dependency->name));
#line 151 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("kind"), doof::json_value(dependency->kind));
#line 152 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("url"), doof::json_value(dependency->url));
#line 153 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("destination"), doof::json_value(dependency->destination));
#line 154 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("acquiredAt"), doof::json_value(std::string("")));
#line 155 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("platform"), doof::json_value(::std_::os::index::platform()));
#line 156 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("fingerprint"), doof::json_value(fingerprint));
#line 157 "/src/external-dependency.do"
    if (dependency->kind == std::string("archive")) {
#line 158 "/src/external-dependency.do"
        externalJsonSet(marker, std::string("sha256"), doof::json_value(dependency->sha256));
#line 159 "/src/external-dependency.do"
        externalJsonSet(marker, std::string("stripComponents"), doof::json_value(dependency->stripComponents));
#line 160 "/src/external-dependency.do"
        std::shared_ptr<std::vector<doof::JsonValue>> copies = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
#line 161 "/src/external-dependency.do"
        const auto& _iterable_37 = dependency->copyFiles;
        for (const auto& copyFile : *_iterable_37) {
#line 162 "/src/external-dependency.do"
            std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> copy = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 163 "/src/external-dependency.do"
            externalJsonSet(copy, std::string("from"), doof::json_value(copyFile->source));
#line 164 "/src/external-dependency.do"
            externalJsonSet(copy, std::string("to"), doof::json_value(copyFile->destination));
#line 165 "/src/external-dependency.do"
            copies->push_back(doof::json_value(copy));
        }
#line 167 "/src/external-dependency.do"
        externalJsonSet(marker, std::string("copyFiles"), doof::json_value(copies));
    } else {
#line 169 "/src/external-dependency.do"
        externalJsonSet(marker, std::string("ref"), doof::json_value(dependency->ref));
#line 170 "/src/external-dependency.do"
        externalJsonSet(marker, std::string("commit"), doof::json_value(dependency->commit));
    }
#line 172 "/src/external-dependency.do"
    return (::doof_json::format(doof::json_value(marker)) + std::string("\n"));
}
#line 175 "/src/external-dependency.do"
std::string externalNativeMarkerContent(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<ExternalDependencyTarget>& target, const std::string& fingerprint) {
#line 180 "/src/external-dependency.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> marker = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 181 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("schemaVersion"), doof::json_value(1));
#line 182 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("nativeTarget"), doof::json_value(target->nativeTarget));
#line 183 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("builtAt"), doof::json_value(std::string("")));
#line 184 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("sdkPath"), doof::json_value(target->sdkPath));
#line 185 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("targetTriple"), doof::json_value(target->targetTriple));
#line 186 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("configureHost"), doof::json_value(target->configureHost));
#line 187 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("commands"), doof::json_value(externalCommandsJson(dependency->commands)));
#line 188 "/src/external-dependency.do"
    externalJsonSet(marker, std::string("fingerprint"), doof::json_value(fingerprint));
#line 189 "/src/external-dependency.do"
    return (::doof_json::format(doof::json_value(marker)) + std::string("\n"));
}
#line 192 "/src/external-dependency.do"
bool isEmptyExternalDirectory(const std::string& path) {
#line 193 "/src/external-dependency.do"
    if (!::doof_fs::isDirectory(path)) {
#line 193 "/src/external-dependency.do"
        return false;
    }
#line 194 "/src/external-dependency.do"
    auto _binding_value_38 = ::doof_fs::readDir(path);
    if (doof::is_failure(_binding_value_38)) {
        const auto& entries = _binding_value_38;
#line 194 "/src/external-dependency.do"
        return false;
    }
    const auto entries = doof::success_value(_binding_value_38);
#line 195 "/src/external-dependency.do"
    return (static_cast<int32_t>((entries)->size()) == 0);
}
#line 198 "/src/external-dependency.do"
doof::Result<void, std::string> copyArchiveContents(const std::string& sourceRoot, const std::string& destination) {
#line 199 "/src/external-dependency.do"
    if (!::doof_fs::isDirectory(sourceRoot)) {
#line 199 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (std::string("stripped archive root is not a directory: ") + sourceRoot) };
    }
#line 200 "/src/external-dependency.do"
    auto _try_value_39 = ensureExternalDirectory(destination);
    if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
#line 201 "/src/external-dependency.do"
    auto _binding_value_40 = ::doof_fs::readDir(sourceRoot);
    if (doof::is_failure(_binding_value_40)) {
        const auto error = doof::failure_error(_binding_value_40);
#line 201 "/src/external-dependency.do"
        return doof::Failure<std::string>{ std::string("Could not read extracted archive") };
    }
    const auto entries = doof::success_value(_binding_value_40);
#line 202 "/src/external-dependency.do"
    const auto& _iterable_42 = entries;
    for (const auto& entry : *_iterable_42) {
#line 202 "/src/external-dependency.do"
        auto _try_value_43 = copyExternalPath(externalPath(sourceRoot, entry->name), externalPath(destination, entry->name));
        if (doof::is_failure(_try_value_43)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_43))};
    }
#line 203 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 206 "/src/external-dependency.do"
doof::Result<std::string, std::string> strippedArchiveRoot(const std::string& extractRoot, int32_t count, const std::string& dependencyName) {
#line 207 "/src/external-dependency.do"
    auto current = extractRoot;
#line 208 "/src/external-dependency.do"
    for (int32_t ignored = 0; ignored < count; ++ignored) {
#line 209 "/src/external-dependency.do"
        auto _binding_value_45 = ::doof_fs::readDir(current);
        if (doof::is_failure(_binding_value_45)) {
            const auto error = doof::failure_error(_binding_value_45);
#line 209 "/src/external-dependency.do"
            return doof::Failure<std::string>{ (std::string("Could not inspect archive for ") + dependencyName) };
        }
        const auto entries = doof::success_value(_binding_value_45);
#line 210 "/src/external-dependency.do"
        auto selected = std::string("");
#line 211 "/src/external-dependency.do"
        auto selectedCount = 0;
#line 212 "/src/external-dependency.do"
        const auto& _iterable_47 = entries;
        for (const auto& entry : *_iterable_47) {
#line 213 "/src/external-dependency.do"
            if (entry->name == std::string("__MACOSX")) {
#line 213 "/src/external-dependency.do"
                continue;
            }
#line 214 "/src/external-dependency.do"
            (selected = entry->name);
#line 215 "/src/external-dependency.do"
            (selectedCount += 1);
        }
#line 217 "/src/external-dependency.do"
        if (selectedCount != 1) {
#line 218 "/src/external-dependency.do"
            return doof::Failure<std::string>{ ((((std::string("External dependency ") + dependencyName) + std::string(" archive cannot strip ")) + doof::to_string(count)) + std::string(" component(s) from multiple roots")) };
        }
#line 220 "/src/external-dependency.do"
        (current = externalPath(current, selected));
    }
#line 222 "/src/external-dependency.do"
    return doof::Success<std::string>{ current };
}
#line 225 "/src/external-dependency.do"
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> downloadExternalArchive(const std::string& url) {
#line 228 "/src/external-dependency.do"
    if (doof::string_startsWith(url, std::string("file://"))) {
#line 229 "/src/external-dependency.do"
        const auto path = doof::string_substring(url, 7, static_cast<int32_t>(url.size()));
#line 230 "/src/external-dependency.do"
        auto _binding_value_48 = ::doof_fs::readBlob(path);
        if (doof::is_failure(_binding_value_48)) {
            const auto error = doof::failure_error(_binding_value_48);
#line 230 "/src/external-dependency.do"
            return doof::Failure<std::string>{ (std::string("Could not read local archive ") + path) };
        }
        const auto blob = doof::success_value(_binding_value_48);
#line 231 "/src/external-dependency.do"
        return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ blob };
    }
#line 233 "/src/external-dependency.do"
    const auto client = ::std_::http::index::createClient();
#line 234 "/src/external-dependency.do"
    auto _binding_value_49 = ::std_::http::index::get(client, url);
    if (doof::is_failure(_binding_value_49)) {
        const auto error = doof::failure_error(_binding_value_49);
#line 235 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (((((std::string("HTTP request failed [") + error->kind) + std::string(", code=")) + error->code) + std::string("]: ")) + error->message) };
    }
    const auto response = doof::success_value(_binding_value_49);
#line 237 "/src/external-dependency.do"
    if (!response->ok()) {
#line 238 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (((std::string("HTTP request failed with status ") + doof::to_string(response->status)) + std::string(" ")) + response->statusText) };
    }
#line 240 "/src/external-dependency.do"
    return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ response->getBlob() };
}
#line 243 "/src/external-dependency.do"
doof::Result<void, std::string> acquireArchive(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& destination, const std::string& stagingRoot) {
#line 244 "/src/external-dependency.do"
    const auto archivePath = externalPath(stagingRoot, std::string("source"));
#line 245 "/src/external-dependency.do"
    const auto extractRoot = externalPath(stagingRoot, std::string("extract"));
#line 246 "/src/external-dependency.do"
    const auto payloadRoot = externalPath(stagingRoot, std::string("payload"));
#line 247 "/src/external-dependency.do"
    auto _try_value_50 = ensureExternalDirectory(extractRoot);
    if (doof::is_failure(_try_value_50)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_50))};
#line 248 "/src/external-dependency.do"
    auto _try_value_51 = downloadExternalArchive(dependency->url);
    if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_51))};
    const auto archive = doof::success_value(_try_value_51);
#line 249 "/src/external-dependency.do"
    auto _binding_value_52 = ::doof_fs::writeBlob(archivePath, archive);
    if (doof::is_failure(_binding_value_52)) {
        const auto error = doof::failure_error(_binding_value_52);
#line 249 "/src/external-dependency.do"
        return doof::Failure<std::string>{ std::string("Could not stage downloaded archive") };
    }
#line 250 "/src/external-dependency.do"
    const auto actualSha256 = ::std_::crypto::index::sha256Hex(archive);
#line 251 "/src/external-dependency.do"
    if (actualSha256 != dependency->sha256) {
#line 252 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" checksum mismatch: expected ")) + dependency->sha256) + std::string(", got ")) + actualSha256) };
    }
#line 254 "/src/external-dependency.do"
    if (doof::string_endsWith(doof::string_toLowerCase(dependency->url), std::string(".zip"))) {
#line 255 "/src/external-dependency.do"
        auto _try_value_53 = commandOutput(std::string("unzip"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-q"), archivePath, std::string("-d"), extractRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
        if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_53))};
        const auto ignoredUnzip = doof::success_value(_try_value_53);
    } else {
#line 257 "/src/external-dependency.do"
        auto _try_value_54 = commandOutput(std::string("tar"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-xf"), archivePath, std::string("-C"), extractRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
        if (doof::is_failure(_try_value_54)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_54))};
        const auto ignoredTar = doof::success_value(_try_value_54);
    }
#line 259 "/src/external-dependency.do"
    auto _try_value_55 = strippedArchiveRoot(extractRoot, dependency->stripComponents, dependency->name);
    if (doof::is_failure(_try_value_55)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_55))};
    const auto sourceRoot = doof::success_value(_try_value_55);
#line 260 "/src/external-dependency.do"
    auto _try_value_56 = copyArchiveContents(sourceRoot, payloadRoot);
    if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_56))};
#line 261 "/src/external-dependency.do"
    const auto& _iterable_58 = dependency->copyFiles;
    for (const auto& copyFile : *_iterable_58) {
#line 262 "/src/external-dependency.do"
        const auto sourcePath = externalPath(payloadRoot, copyFile->source);
#line 263 "/src/external-dependency.do"
        const auto destinationPath = externalPath(payloadRoot, copyFile->destination);
#line 264 "/src/external-dependency.do"
        if (!externalPathWithinRoot(sourcePath, payloadRoot) || !externalPathWithinRoot(destinationPath, payloadRoot)) {
#line 265 "/src/external-dependency.do"
            return doof::Failure<std::string>{ ((std::string("External dependency ") + dependency->name) + std::string(" copyFiles entries must stay within the destination")) };
        }
#line 267 "/src/external-dependency.do"
        auto _try_value_59 = copyExternalPath(sourcePath, destinationPath);
        if (doof::is_failure(_try_value_59)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_59))};
    }
#line 269 "/src/external-dependency.do"
    auto _binding_value_60 = ::doof_fs::rename(payloadRoot, destination);
    if (doof::is_failure(_binding_value_60)) {
        const auto error = doof::failure_error(_binding_value_60);
#line 269 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (std::string("Could not install external dependency ") + dependency->name) };
    }
#line 270 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 273 "/src/external-dependency.do"
doof::Result<void, std::string> acquireGit(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& destination, const std::string& stagingRoot) {
#line 274 "/src/external-dependency.do"
    const auto repositoryRoot = externalPath(stagingRoot, std::string("repository"));
#line 275 "/src/external-dependency.do"
    auto _try_value_61 = commandOutput(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("clone"), std::string("--depth"), std::string("1"), std::string("--branch"), dependency->ref, dependency->url, repositoryRoot}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_EXTERNAL_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_try_value_61)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_61))};
    const auto ignoredClone = doof::success_value(_try_value_61);
#line 279 "/src/external-dependency.do"
    auto _try_value_62 = commandOutput(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-C"), repositoryRoot, std::string("rev-parse"), std::string("HEAD")}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
    if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_62))};
    const auto actualCommit = doof::success_value(_try_value_62);
#line 280 "/src/external-dependency.do"
    if (doof::string_toLowerCase(actualCommit) != dependency->commit) {
#line 281 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" commit mismatch: expected ")) + dependency->commit) + std::string(", got ")) + actualCommit) };
    }
#line 283 "/src/external-dependency.do"
    auto _try_value_63 = removeExternalTree(externalPath(repositoryRoot, std::string(".git")));
    if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_63))};
#line 284 "/src/external-dependency.do"
    auto _binding_value_64 = ::doof_fs::rename(repositoryRoot, destination);
    if (doof::is_failure(_binding_value_64)) {
        const auto error = doof::failure_error(_binding_value_64);
#line 284 "/src/external-dependency.do"
        return doof::Failure<std::string>{ (std::string("Could not install external dependency ") + dependency->name) };
    }
#line 285 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 289 "/src/external-dependency.do"
std::string applyExternalDependencySubstitutions(const std::string& value, const std::string& packageRoot, const std::string& destination, const std::shared_ptr<ExternalDependencyTarget>& target) {
#line 295 "/src/external-dependency.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("${packageRoot}"), packageRoot), std::string("${destination}"), destination), std::string("${jobs}"), doof::to_string(((target->jobs < 1) ? 1 : target->jobs))), std::string("${nativeTarget}"), target->nativeTarget), std::string("${sdkPath}"), target->sdkPath), std::string("${targetTriple}"), target->targetTriple), std::string("${configureHost}"), target->configureHost);
}
#line 304 "/src/external-dependency.do"
doof::Result<void, std::string> runExternalCommands(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& packageRoot, const std::string& destination, const std::shared_ptr<ExternalDependencyTarget>& target) {
#line 310 "/src/external-dependency.do"
    const auto nativeMarker = externalPath(destination, ((std::string(".doof-external-native-") + target->nativeTarget) + std::string(".json")));
#line 311 "/src/external-dependency.do"
    const auto fingerprint = externalNativeFingerprint(dependency, target);
#line 312 "/src/external-dependency.do"
    if (markerMatches(nativeMarker, fingerprint)) {
#line 313 "/src/external-dependency.do"
        const auto content = externalNativeMarkerContent(dependency, target, fingerprint);
#line 314 "/src/external-dependency.do"
        if (!markerContentMatches(nativeMarker, content)) {
#line 315 "/src/external-dependency.do"
            auto _binding_value_65 = ::doof_fs::writeText(nativeMarker, content);
            if (doof::is_failure(_binding_value_65)) {
                const auto error = doof::failure_error(_binding_value_65);
#line 316 "/src/external-dependency.do"
                return doof::Failure<std::string>{ std::string("Could not refresh external dependency native marker") };
            }
        }
#line 319 "/src/external-dependency.do"
        return doof::Success<void>{};
    }
#line 321 "/src/external-dependency.do"
    for (int32_t index = 0; index < static_cast<int32_t>((dependency->commands)->size()); ++index) {
#line 322 "/src/external-dependency.do"
        const auto command = doof::array_at(dependency->commands, index, "src/external-dependency", 322);
#line 323 "/src/external-dependency.do"
        const auto workingDirectory = ((command->workingDirectory == std::string("")) ? destination : externalPath(destination, applyExternalDependencySubstitutions(command->workingDirectory, packageRoot, destination, target)));
#line 326 "/src/external-dependency.do"
        if (!externalPathWithinRoot(workingDirectory, destination)) {
#line 327 "/src/external-dependency.do"
            return doof::Failure<std::string>{ ((std::string("External dependency ") + dependency->name) + std::string(" command workingDirectory must stay within the destination")) };
        }
#line 329 "/src/external-dependency.do"
        std::shared_ptr<doof::ordered_map<std::string, std::string>> environment = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
#line 330 "/src/external-dependency.do"
        const auto& _iterable_68 = command->env;
        for (const auto& [key, value] : *_iterable_68) {
#line 331 "/src/external-dependency.do"
            doof::map_set(environment, key, applyExternalDependencySubstitutions(value, packageRoot, destination, target), "", 0);
        }
#line 333 "/src/external-dependency.do"
        const auto program = applyExternalDependencySubstitutions(command->program, packageRoot, destination, target);
#line 334 "/src/external-dependency.do"
        std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 335 "/src/external-dependency.do"
        const auto& _iterable_70 = command->args;
        for (const auto& argument : *_iterable_70) {
#line 336 "/src/external-dependency.do"
            arguments->push_back(applyExternalDependencySubstitutions(argument, packageRoot, destination, target));
        }
#line 338 "/src/external-dependency.do"
        auto _binding_value_71 = commandOutput(program, arguments, std::make_shared<::std_::os::index::ExecOptions>(workingDirectory, doof::map_drainToReadonly(environment, "", 0), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_EXTERNAL_COMMAND_OUTPUT_BYTES, nullptr));
        if (doof::is_failure(_binding_value_71)) {
            const auto error = doof::failure_error(_binding_value_71);
#line 342 "/src/external-dependency.do"
            return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" command ")) + doof::to_string((index + 1))) + std::string(" failed: ")) + error) };
        }
    }
#line 345 "/src/external-dependency.do"
    auto _binding_value_72 = ::doof_fs::writeText(nativeMarker, externalNativeMarkerContent(dependency, target, fingerprint));
    if (doof::is_failure(_binding_value_72)) {
        const auto error = doof::failure_error(_binding_value_72);
#line 346 "/src/external-dependency.do"
        return doof::Failure<std::string>{ std::string("Could not write external dependency native marker") };
    }
#line 348 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 352 "/src/external-dependency.do"
doof::Result<void, std::string> acquirePackageExternalDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<ExternalDependencyTarget>& target) {
#line 356 "/src/external-dependency.do"
    if (manifest->manifestPath == std::string("")) {
#line 356 "/src/external-dependency.do"
        return doof::Success<void>{};
    }
#line 357 "/src/external-dependency.do"
    const auto& _iterable_74 = manifest->externalDependencies;
    for (const auto& dependency : *_iterable_74) {
#line 358 "/src/external-dependency.do"
        const auto destination = externalPath(manifest->rootDirectory, dependency->destination);
#line 359 "/src/external-dependency.do"
        const auto sourceMarker = externalPath(destination, EXTERNAL_SOURCE_MARKER);
#line 360 "/src/external-dependency.do"
        const auto fingerprint = externalSourceFingerprint(dependency);
#line 361 "/src/external-dependency.do"
        if (!markerMatches(sourceMarker, fingerprint)) {
#line 362 "/src/external-dependency.do"
            if (::doof_fs::exists(destination)) {
#line 363 "/src/external-dependency.do"
                if (!::doof_fs::exists(sourceMarker) && !isEmptyExternalDirectory(destination)) {
#line 364 "/src/external-dependency.do"
                    return doof::Failure<std::string>{ (((((std::string("External dependency ") + dependency->name) + std::string(" destination already exists without ")) + EXTERNAL_SOURCE_MARKER) + std::string(": ")) + destination) };
                }
#line 366 "/src/external-dependency.do"
                auto _try_value_75 = removeExternalTree(destination);
                if (doof::is_failure(_try_value_75)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_75))};
            }
#line 368 "/src/external-dependency.do"
            const auto parent = ::std_::path::index::dirname(destination);
#line 369 "/src/external-dependency.do"
            auto _try_value_76 = ensureExternalDirectory(parent);
            if (doof::is_failure(_try_value_76)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_76))};
#line 370 "/src/external-dependency.do"
            const auto stagingRoot = externalPath(parent, ((std::string(".doof-") + dependency->name) + std::string("-staging")));
#line 371 "/src/external-dependency.do"
            if (::doof_fs::exists(stagingRoot)) {
#line 371 "/src/external-dependency.do"
                auto _try_value_77 = removeExternalTree(stagingRoot);
                if (doof::is_failure(_try_value_77)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_77))};
            }
#line 372 "/src/external-dependency.do"
            auto _try_value_78 = ensureExternalDirectory(stagingRoot);
            if (doof::is_failure(_try_value_78)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_78))};
#line 373 "/src/external-dependency.do"
            const auto acquisition = ((dependency->kind == std::string("archive")) ? acquireArchive(dependency, destination, stagingRoot) : acquireGit(dependency, destination, stagingRoot));
#line 376 "/src/external-dependency.do"
            auto _binding_value_79 = acquisition;
            if (doof::is_failure(_binding_value_79)) {
                const auto error = doof::failure_error(_binding_value_79);
#line 377 "/src/external-dependency.do"
                auto _try_value_80 = removeExternalTree(destination);
                if (doof::is_failure(_try_value_80)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_80))};
#line 378 "/src/external-dependency.do"
                auto _try_value_81 = removeExternalTree(stagingRoot);
                if (doof::is_failure(_try_value_81)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_81))};
#line 379 "/src/external-dependency.do"
                return doof::Failure<std::string>{ (((std::string("Failed to acquire external dependency ") + dependency->name) + std::string(": ")) + error) };
            }
#line 381 "/src/external-dependency.do"
            auto _try_value_82 = removeExternalTree(stagingRoot);
            if (doof::is_failure(_try_value_82)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_82))};
        }
#line 385 "/src/external-dependency.do"
        const auto content = externalSourceMarkerContent(dependency, fingerprint);
#line 386 "/src/external-dependency.do"
        if (!markerContentMatches(sourceMarker, content)) {
#line 387 "/src/external-dependency.do"
            auto _binding_value_83 = ::doof_fs::writeText(sourceMarker, content);
            if (doof::is_failure(_binding_value_83)) {
                const auto error = doof::failure_error(_binding_value_83);
#line 388 "/src/external-dependency.do"
                return doof::Failure<std::string>{ std::string("Could not refresh external dependency marker") };
            }
        }
#line 391 "/src/external-dependency.do"
        if (static_cast<int32_t>((dependency->commands)->size()) > 0) {
#line 392 "/src/external-dependency.do"
            auto _binding_value_84 = runExternalCommands(dependency, manifest->rootDirectory, destination, target);
            if (doof::is_failure(_binding_value_84)) {
                const auto error = doof::failure_error(_binding_value_84);
#line 393 "/src/external-dependency.do"
                const auto nativeMarker = externalPath(destination, ((std::string(".doof-external-native-") + target->nativeTarget) + std::string(".json")));
#line 394 "/src/external-dependency.do"
                if (::doof_fs::exists(nativeMarker)) {
#line 394 "/src/external-dependency.do"
                    auto _try_value_85 = removeExternalTree(nativeMarker);
                    if (doof::is_failure(_try_value_85)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_85))};
                }
#line 395 "/src/external-dependency.do"
                return doof::Failure<std::string>{ (((((std::string("Failed to build external dependency ") + dependency->name) + std::string(" for ")) + target->nativeTarget) + std::string(": ")) + error) };
            }
        }
    }
#line 399 "/src/external-dependency.do"
    return doof::Success<void>{};
}
#line 1 "<doof-generated>"

void __doof_initialize_module() {
        EXTERNAL_SOURCE_MARKER = std::string(".doof-external.json");
}
}
