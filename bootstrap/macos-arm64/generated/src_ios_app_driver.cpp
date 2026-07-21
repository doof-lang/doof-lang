#include "src_ios_app_driver.hpp"
#include <cmath>
#include "src_ios_app.hpp"
#include "src_ios_device.hpp"
#include "src_package_manifest.hpp"
#include "std_blob_index.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "std_time_index.hpp"
#include "std_http_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_ios_app_driver_ {
using namespace ::app_src_ios_app_;
using namespace ::app_src_ios_device_;
using namespace ::app_src_package_manifest_;
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
using namespace ::std_::time::index;
const auto MAX_IOS_COMMAND_OUTPUT_BYTES = 262144LL;

doof::JsonObject IOSCommandResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["output"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->output->size()); for (const auto& _element : *this->output) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["error"] = doof::json_value(this->error);
    return _json;
}
doof::Result<std::shared_ptr<IOSCommandResult>, std::string> IOSCommandResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    std::optional<std::shared_ptr<std::vector<uint8_t>>> _field_output;
    if (auto _iterator_output = _object->find("output"); _iterator_output != _object->end()) {
        if (!(doof::json_is_array(_iterator_output->second))) { return doof::Failure<std::string>{"Field \"output\" expected array but got " + std::string(doof::json_type_name(_iterator_output->second))}; }
        _field_output = [&]() { const auto* _array = doof::json_as_array(_iterator_output->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    }
    std::optional<std::string> _field_error;
    if (auto _iterator_error = _object->find("error"); _iterator_error != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_error->second) : doof::json_is_string(_iterator_error->second)))) { return doof::Failure<std::string>{"Field \"error\" expected string but got " + std::string(doof::json_type_name(_iterator_error->second))}; }
        _field_error = (_lenient ? doof::json_as_string_lenient(_iterator_error->second) : doof::json_as_string(_iterator_error->second));
    } else {
        _field_error = std::string("");
    }
    return doof::Success<std::shared_ptr<IOSCommandResult>>{std::make_shared<IOSCommandResult>(_field_exitCode, _field_output.value(), _field_error.value())};
}
std::string outputPath(std::string directory, std::string name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
std::string parentPath(std::string path) {
    return ::std_::path::index::dirname(path);
}
std::string fileName(std::string path) {
    return ::std_::path::index::basename(path);
}
std::string hostPlatform() {
    const auto value = ::std_::os::index::platform();
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}
std::shared_ptr<IOSCommandResult> runIOSCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments) {
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, MAX_IOS_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return std::make_shared<IOSCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error);
    }
    const auto executed = doof::success_value(_binding_value_1);
    return std::make_shared<IOSCommandResult>(executed->exitCode, executed->stdout, std::string(""));
}
doof::Result<std::string, std::string> commandText(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description) {
    const auto result = runIOSCommand(command, arguments);
    const auto output = ((result->error != std::string("")) ? result->error : doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size())))));
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ ((description + std::string(" failed")) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    return doof::Success<std::string>{ output };
}
doof::Result<void, std::string> runRequiredCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description) {
    auto _try_value_2 = commandText(command, arguments, description);
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::failure_error(_try_value_2)};
    const auto ignored = doof::success_value(_try_value_2);
    return doof::Success<void>{};
}
void ensureDirectory(std::string path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return;
    }
    const auto parent = parentPath(path);
    if (parent != path) {
        ensureDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
}
void copyPath(std::string sourcePath, std::string destinationPath) {
    if (::doof_fs::isDirectory(sourcePath)) {
        ensureDirectory(destinationPath);
        const auto& _iterable_3 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_3) {
            copyPath(outputPath(sourcePath, entry->name), outputPath(destinationPath, entry->name));
        }
        return;
    }
    ensureDirectory(parentPath(destinationPath));
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(destinationPath, [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(sourcePath); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }()); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
}
void removeTree(std::string path) {
    if (!::doof_fs::exists(path)) {
        return;
    }
    if (::doof_fs::isDirectory(path)) {
        const auto& _iterable_4 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_4) {
            removeTree(outputPath(path, entry->name));
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
}
void appendUnique(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    if (!doof::array_contains(values, value, "", 0)) {
        values->push_back(value);
    }
}
doof::Result<void, std::string> configureIOSNativeBuild(std::string outputDirectory, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string destination, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> native) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS app builds are only supported on macOS") };
    }
    const auto sdk = ((destination == std::string("device")) ? std::string("iphoneos") : std::string("iphonesimulator"));
    auto _try_value_5 = commandText(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--sdk"), sdk, std::string("--show-sdk-path")}), std::string("resolving the iOS SDK"));
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::failure_error(_try_value_5)};
    const auto sdkPath = doof::success_value(_try_value_5);
    auto _try_value_6 = commandText(std::string("uname"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-m")}), std::string("resolving the host architecture"));
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::failure_error(_try_value_6)};
    const auto architecture = doof::success_value(_try_value_6);
    auto _try_value_7 = ::app_src_ios_app_::iosTargetTriple(config->minimumDeploymentTarget, destination, architecture);
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::failure_error(_try_value_7)};
    const auto target = doof::success_value(_try_value_7);
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(outputDirectory, std::string("Info.plist")), ::app_src_ios_app_::renderIOSInfoPlist(config)); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(outputDirectory, std::string("ios-main.mm")), ::app_src_ios_app_::renderIOSMainSource(config->executableName)); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    appendUnique(native->sourceFiles, std::string("ios-main.mm"));
    appendUnique(native->frameworks, std::string("UIKit"));
    appendUnique(native->frameworks, std::string("Foundation"));
    const auto& _iterable_8 = std::make_shared<std::vector<std::shared_ptr<std::vector<std::string>>>>(std::vector<std::shared_ptr<std::vector<std::string>>>{native->compilerFlags, native->linkerFlags});
    for (const auto& values : *_iterable_8) {
        appendUnique(values, std::string("-isysroot"));
        appendUnique(values, sdkPath);
        appendUnique(values, std::string("-target"));
        appendUnique(values, target);
    }
    return doof::Success<void>{};
}
std::string globBaseDirectory(std::string pattern) {
    auto wildcard = static_cast<int32_t>(pattern.size());
    for (int32_t index = 0; index < static_cast<int32_t>(pattern.size()); ++index) {
        if (doof::string_substring(pattern, index, (index + 1)) == std::string("*")) {
            (wildcard = index);
            break;
        }
    }
    if (wildcard == static_cast<int32_t>(pattern.size())) {
        return parentPath(pattern);
    }
    auto slash = wildcard;
    while ((slash > 0) && (doof::string_substring(pattern, (slash - 1), slash) != std::string("/"))) {
        (slash -= 1);
    }
    return ((slash <= 1) ? std::string("/") : doof::string_substring(pattern, 0, (slash - 1)));
}
bool globMatches(std::string pattern, std::string value, int32_t patternIndex, int32_t valueIndex) {
    if (patternIndex == static_cast<int32_t>(pattern.size())) {
        return (valueIndex == static_cast<int32_t>(value.size()));
    }
    const auto current = doof::string_substring(pattern, patternIndex, (patternIndex + 1));
    if (current != std::string("*")) {
        return (((valueIndex < static_cast<int32_t>(value.size())) && (current == doof::string_substring(value, valueIndex, (valueIndex + 1)))) && globMatches(pattern, value, (patternIndex + 1), (valueIndex + 1)));
    }
    const auto doubleStar = (((patternIndex + 1) < static_cast<int32_t>(pattern.size())) && (doof::string_substring(pattern, (patternIndex + 1), (patternIndex + 2)) == std::string("*")));
    const auto nextPattern = (patternIndex + (doubleStar ? 2 : 1));
    if (globMatches(pattern, value, nextPattern, valueIndex)) {
        return true;
    }
    if (valueIndex >= static_cast<int32_t>(value.size())) {
        return false;
    }
    if (!doubleStar && (doof::string_substring(value, valueIndex, (valueIndex + 1)) == std::string("/"))) {
        return false;
    }
    return globMatches(pattern, value, patternIndex, (valueIndex + 1));
}
void collectResourceFiles(std::string path, std::string baseDirectory, std::string pattern, std::shared_ptr<std::vector<std::string>> results) {
    if (::doof_fs::isDirectory(path)) {
        const auto& _iterable_9 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_9) {
            collectResourceFiles(outputPath(path, entry->name), baseDirectory, pattern, results);
        }
        return;
    }
    const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
    const auto relative = (doof::string_startsWith(path, prefix) ? doof::string_substring(path, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(path.size())) : fileName(path));
    const auto relativePattern = (doof::string_startsWith(pattern, prefix) ? doof::string_substring(pattern, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(pattern.size())) : fileName(pattern));
    if (globMatches(relativePattern, relative, 0, 0)) {
        results->push_back(path);
    }
}
doof::Result<void, std::string> copyIOSResources(std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string appPath) {
    std::shared_ptr<std::vector<std::string>> destinations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_10 = config->resources;
    for (const auto& resource : *_iterable_10) {
        std::shared_ptr<std::vector<std::string>> files = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        auto baseDirectory = globBaseDirectory(resource->sourcePath);
        if (doof::string_contains(resource->sourcePath, std::string("*"))) {
            if (::doof_fs::exists(baseDirectory)) {
                collectResourceFiles(baseDirectory, baseDirectory, resource->sourcePath, files);
            }
        } else if (::doof_fs::isDirectory(resource->sourcePath)) {
            collectResourceFiles(resource->sourcePath, resource->sourcePath, (resource->sourcePath + std::string("/**")), files);
            (baseDirectory = resource->sourcePath);
        } else if (::doof_fs::exists(resource->sourcePath)) {
            files->push_back(resource->sourcePath);
            (baseDirectory = parentPath(resource->sourcePath));
        }
        if (static_cast<int32_t>((files)->size()) == 0) {
            return doof::Failure<std::string>{ (std::string("No files matched resource pattern: ") + resource->sourcePath) };
        }
        const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
        const auto& _iterable_11 = files;
        for (const auto& sourcePath : *_iterable_11) {
            const auto relative = (doof::string_startsWith(sourcePath, prefix) ? doof::string_substring(sourcePath, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(sourcePath.size())) : fileName(sourcePath));
            const auto destinationRoot = ((resource->destination == std::string("")) ? appPath : outputPath(appPath, resource->destination));
            const auto destination = outputPath(destinationRoot, relative);
            if (doof::array_contains(destinations, destination, "", 0)) {
                return doof::Failure<std::string>{ (std::string("Duplicate iOS app resource destination: ") + destination) };
            }
            destinations->push_back(destination);
            copyPath(sourcePath, destination);
        }
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> compileIOSIcon(std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string appPath, std::string destination, std::string buildDirectory) {
    if (config->iconPath == std::string("")) {
        return doof::Success<void>{};
    }
    const auto catalogPath = outputPath(buildDirectory, std::string("Assets.xcassets"));
    const auto iconSetPath = outputPath(catalogPath, std::string("AppIcon.appiconset"));
    removeTree(catalogPath);
    ensureDirectory(iconSetPath);
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(iconSetPath, std::string("Contents.json")), (::app_src_ios_app_::renderIOSIconSetContents() + std::string("\n"))); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    const auto names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("iphone_notification_20@2x.png"), std::string("iphone_notification_20@3x.png"), std::string("iphone_settings_29@2x.png"), std::string("iphone_settings_29@3x.png"), std::string("iphone_spotlight_40@2x.png"), std::string("iphone_spotlight_40@3x.png"), std::string("iphone_app_60@2x.png"), std::string("iphone_app_60@3x.png"), std::string("ipad_notification_20.png"), std::string("ipad_notification_20@2x.png"), std::string("ipad_settings_29.png"), std::string("ipad_settings_29@2x.png"), std::string("ipad_spotlight_40.png"), std::string("ipad_spotlight_40@2x.png"), std::string("ipad_app_76.png"), std::string("ipad_app_76@2x.png"), std::string("ipad_pro_83_5@2x.png"), std::string("app_store_1024.png")});
    const auto sizes = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{40, 60, 58, 87, 80, 120, 120, 180, 20, 40, 29, 58, 40, 80, 76, 152, 167, 1024});
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
        const auto size = doof::to_string((*sizes)[index]);
        auto _try_value_12 = runRequiredCommand(std::string("sips"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-z"), size, size, config->iconPath, std::string("--out"), outputPath(iconSetPath, (*names)[index])}), std::string("resizing the iOS app icon"));
        if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::failure_error(_try_value_12)};
    }
    const auto partialPlistPath = outputPath(buildDirectory, std::string(".doof-ios-icon-info.plist"));
    const auto platformName = ((destination == std::string("device")) ? std::string("iphoneos") : std::string("iphonesimulator"));
    auto _try_value_13 = runRequiredCommand(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("actool"), catalogPath, std::string("--compile"), appPath, std::string("--platform"), platformName, std::string("--minimum-deployment-target"), config->minimumDeploymentTarget, std::string("--app-icon"), std::string("AppIcon"), std::string("--target-device"), std::string("iphone"), std::string("--target-device"), std::string("ipad"), std::string("--output-partial-info-plist"), partialPlistPath}), std::string("compiling the iOS app icon catalog"));
    if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::failure_error(_try_value_13)};
    auto _try_value_14 = runRequiredCommand(std::string("/usr/libexec/PlistBuddy"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), (std::string("Merge ") + partialPlistPath), outputPath(appPath, std::string("Info.plist"))}), std::string("merging iOS app icon metadata"));
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::failure_error(_try_value_14)};
    if (::doof_fs::exists(partialPlistPath)) {
        [&]() -> void { auto _try_value = ::doof_fs::remove(partialPlistPath); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    }
    return doof::Success<void>{};
}
doof::Result<std::string, std::string> assembleIOSApp(std::string buildDirectory, std::string executablePath, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string destination) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS app builds are only supported on macOS") };
    }
    if (static_cast<int32_t>((config->embeddedLibraries)->size()) > 0) {
        return doof::Failure<std::string>{ std::string("Self-hosted iOS embedded library bundling is not yet supported") };
    }
    const auto appPath = outputPath(buildDirectory, (config->executableName + std::string(".app")));
    removeTree(appPath);
    ensureDirectory(appPath);
    const auto bundleExecutable = outputPath(appPath, config->executableName);
    copyPath(executablePath, bundleExecutable);
    auto _try_value_15 = runRequiredCommand(std::string("chmod"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("+x"), bundleExecutable}), std::string("marking the iOS executable"));
    if (doof::is_failure(_try_value_15)) return doof::Failure<std::string>{doof::failure_error(_try_value_15)};
    const auto infoPlistPath = outputPath(buildDirectory, std::string("Info.plist"));
    if (::doof_fs::exists(infoPlistPath)) {
        copyPath(infoPlistPath, outputPath(appPath, std::string("Info.plist")));
    } else {
        [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(appPath, std::string("Info.plist")), ::app_src_ios_app_::renderIOSInfoPlist(config)); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    }
    auto _try_value_16 = copyIOSResources(config, appPath);
    if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::failure_error(_try_value_16)};
    auto _try_value_17 = compileIOSIcon(config, appPath, destination, buildDirectory);
    if (doof::is_failure(_try_value_17)) return doof::Failure<std::string>{doof::failure_error(_try_value_17)};
    return doof::Success<std::string>{ appPath };
}
void collectNestedCode(std::string path, std::shared_ptr<std::vector<std::string>> results) {
    if (!::doof_fs::exists(path)) {
        return;
    }
    if (::doof_fs::isDirectory(path)) {
        const auto& _iterable_18 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_18) {
            collectNestedCode(outputPath(path, entry->name), results);
        }
        if (doof::string_endsWith(path, std::string(".framework")) || doof::string_endsWith(path, std::string(".appex"))) {
            results->push_back(path);
        }
        return;
    }
    if (doof::string_endsWith(path, std::string(".dylib")) || doof::string_endsWith(path, std::string(".so"))) {
        results->push_back(path);
    }
}
doof::Result<void, std::string> signAndArchiveIOSApp(std::string appPath, std::string archivePath, std::string bundleId, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> config, std::string buildDirectory) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS Ad Hoc packaging is only supported on macOS") };
    }
    if (config->provisioningProfilePath == std::string("")) {
        return doof::Failure<std::string>{ std::string("No iOS provisioning profile configured; pass --ios-provisioning-profile") };
    }
    if (!::doof_fs::exists(config->provisioningProfilePath)) {
        return doof::Failure<std::string>{ (std::string("Provisioning profile not found: ") + config->provisioningProfilePath) };
    }
    const auto workDirectory = outputPath(buildDirectory, std::string(".doof-ios-package"));
    removeTree(workDirectory);
    ensureDirectory(workDirectory);
    const auto decodedProfilePath = outputPath(workDirectory, std::string("profile.plist"));
    const auto entitlementsPath = outputPath(workDirectory, std::string("entitlements.plist"));
    auto _try_value_19 = ::app_src_ios_device_::parseProvisioningProfile(config->provisioningProfilePath, workDirectory);
    if (doof::is_failure(_try_value_19)) return doof::Failure<std::string>{doof::failure_error(_try_value_19)};
    const auto profile = doof::success_value(_try_value_19);
    auto _try_value_20 = commandText(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("find-identity"), std::string("-v"), std::string("-p"), std::string("codesigning")}), std::string("listing code-signing identities"));
    if (doof::is_failure(_try_value_20)) return doof::Failure<std::string>{doof::failure_error(_try_value_20)};
    const auto identitiesOutput = doof::success_value(_try_value_20);
    const auto identities = ::app_src_ios_device_::parseCodesignIdentities(identitiesOutput);
    auto _try_value_21 = ::app_src_ios_device_::resolveIOSAdHocSigningIdentity(profile, identities, config->identity);
    if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::failure_error(_try_value_21)};
    const auto identity = doof::success_value(_try_value_21);
    auto _try_value_22 = ::app_src_ios_device_::validateIOSAdHocSigning(profile, identities, identity, bundleId, ::std_::time::temporal::Instant::now()->toEpochMillis());
    if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::failure_error(_try_value_22)};
    auto _try_value_23 = ::app_src_ios_app_::iosExactApplicationIdentifier(profile->applicationIdentifier, bundleId);
    if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::failure_error(_try_value_23)};
    const auto exactApplicationIdentifier = doof::success_value(_try_value_23);
    auto _try_value_24 = runRequiredCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements"), std::string("xml1"), std::string("-o"), entitlementsPath, decodedProfilePath}), std::string("extracting iOS signing entitlements"));
    if (doof::is_failure(_try_value_24)) return doof::Failure<std::string>{doof::failure_error(_try_value_24)};
    auto _try_value_25 = runRequiredCommand(std::string("/usr/libexec/PlistBuddy"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), (std::string("Set :application-identifier ") + exactApplicationIdentifier), entitlementsPath}), std::string("expanding the iOS application identifier entitlement"));
    if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::failure_error(_try_value_25)};
    const auto keychainGroupCountResult = commandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("keychain-access-groups"), std::string("raw"), std::string("-o"), std::string("-"), entitlementsPath}), std::string("reading keychain access groups"));
    auto keychainGroupCount = 0;
    {
        auto _case_subject = keychainGroupCountResult;
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
            {
                auto _case_subject = doof::parse_int(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
                    (keychainGroupCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<doof::ParseError>>(_case_subject)) {
            }
            }
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
    for (int32_t index = 0; index < keychainGroupCount; ++index) {
        auto _binding_value_26 = commandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), (std::string("keychain-access-groups.") + doof::to_string(index)), std::string("raw"), std::string("-o"), std::string("-"), entitlementsPath}), std::string("reading keychain access group"));
        if (doof::is_failure(_binding_value_26)) {
            const auto& group = _binding_value_26;
            continue;
        }
        const auto group = doof::success_value(_binding_value_26);
        if (doof::string_contains(group, std::string("*"))) {
            auto _try_value_27 = runRequiredCommand(std::string("/usr/libexec/PlistBuddy"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), (((std::string("Set :keychain-access-groups:") + doof::to_string(index)) + std::string(" ")) + exactApplicationIdentifier), entitlementsPath}), std::string("expanding a keychain access group entitlement"));
            if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::failure_error(_try_value_27)};
        }
    }
    copyPath(config->provisioningProfilePath, outputPath(appPath, std::string("embedded.mobileprovision")));
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectNestedCode(outputPath(appPath, std::string("Frameworks")), nested);
    collectNestedCode(outputPath(appPath, std::string("PlugIns")), nested);
    const auto& _iterable_28 = nested;
    for (const auto& path : *_iterable_28) {
        auto _try_value_29 = runRequiredCommand(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(path, identity, std::string("")), std::string("signing nested iOS code"));
        if (doof::is_failure(_try_value_29)) return doof::Failure<std::string>{doof::failure_error(_try_value_29)};
    }
    auto _try_value_30 = runRequiredCommand(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(appPath, identity, entitlementsPath), std::string("signing the iOS app"));
    if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::failure_error(_try_value_30)};
    auto _try_value_31 = runRequiredCommand(std::string("codesign"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--verify"), std::string("--deep"), std::string("--strict"), std::string("--verbose=2"), appPath}), std::string("verifying the iOS app signature"));
    if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::failure_error(_try_value_31)};
    auto _try_value_32 = commandText(std::string("codesign"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--display"), std::string("--entitlements"), std::string("-"), std::string("--xml"), appPath}), std::string("inspecting signed iOS entitlements"));
    if (doof::is_failure(_try_value_32)) return doof::Failure<std::string>{doof::failure_error(_try_value_32)};
    const auto signedEntitlements = doof::success_value(_try_value_32);
    if (doof::string_contains(signedEntitlements, std::string("invalid entitlements blob")) || !doof::string_contains(signedEntitlements, exactApplicationIdentifier)) {
        removeTree(workDirectory);
        return doof::Failure<std::string>{ ((std::string("Signed iOS entitlements do not contain the exact application identifier \"") + exactApplicationIdentifier) + std::string("\"")) };
    }
    const auto payloadDirectory = outputPath(workDirectory, std::string("Payload"));
    ensureDirectory(payloadDirectory);
    auto _try_value_33 = runRequiredCommand(std::string("ditto"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{appPath, outputPath(payloadDirectory, fileName(appPath))}), std::string("staging the iOS app payload"));
    if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::failure_error(_try_value_33)};
    ensureDirectory(parentPath(archivePath));
    if (::doof_fs::exists(archivePath)) {
        [&]() -> void { auto _try_value = ::doof_fs::remove(archivePath); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    }
    auto _try_value_34 = runRequiredCommand(std::string("ditto"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), std::string("-k"), std::string("--sequesterRsrc"), std::string("--keepParent"), payloadDirectory, archivePath}), std::string("archiving the iOS app"));
    if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::failure_error(_try_value_34)};
    removeTree(workDirectory);
    return doof::Success<void>{};
}
}
