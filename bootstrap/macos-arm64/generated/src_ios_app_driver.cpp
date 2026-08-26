#include "src_ios_app_driver.hpp"

namespace app_src_ios_app_driver_ {
using namespace ::app_src_ios_app_;
using namespace ::app_src_ios_device_;
using namespace ::app_src_package_manifest_;
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
using namespace ::std_::parse::index;
using namespace ::std_::path::index;
int64_t MAX_IOS_COMMAND_OUTPUT_BYTES = 262144LL;

#line 27 "/src/ios-app-driver.do"
std::string outputPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
#line 28 "/src/ios-app-driver.do"
std::string parentPath(const std::string& path) {
    return ::std_::path::index::dirname(path);
}
#line 29 "/src/ios-app-driver.do"
std::string fileName(const std::string& path) {
    return ::std_::path::index::basename(path);
}
#line 31 "/src/ios-app-driver.do"
std::string hostPlatform() {
#line 32 "/src/ios-app-driver.do"
    const auto value = ::std_::os::index::platform();
#line 33 "/src/ios-app-driver.do"
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}
#line 36 "/src/ios-app-driver.do"
std::shared_ptr<IOSCommandResult> runIOSCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
#line 37 "/src/ios-app-driver.do"
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_IOS_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
#line 41 "/src/ios-app-driver.do"
        return std::make_shared<IOSCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error);
    }
    const auto executed = doof::success_value(_binding_value_1);
#line 42 "/src/ios-app-driver.do"
    return std::make_shared<IOSCommandResult>(executed->exitCode, executed->stdout_, std::string(""));
}
#line 45 "/src/ios-app-driver.do"
doof::Result<std::string, std::string> commandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
#line 46 "/src/ios-app-driver.do"
    const auto result = runIOSCommand(command, arguments);
#line 47 "/src/ios-app-driver.do"
    const auto output = ((result->error != std::string("")) ? result->error : doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size())))));
#line 48 "/src/ios-app-driver.do"
    if (result->exitCode != 0) {
#line 49 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ ((description + std::string(" failed")) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
#line 51 "/src/ios-app-driver.do"
    return doof::Success<std::string>{ output };
}
#line 54 "/src/ios-app-driver.do"
doof::Result<void, std::string> runRequiredCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
#line 55 "/src/ios-app-driver.do"
    auto _try_value_2 = commandText(command, arguments, description);
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_2))};
    const auto ignored = doof::success_value(_try_value_2);
#line 56 "/src/ios-app-driver.do"
    return doof::Success<void>{};
}
#line 59 "/src/ios-app-driver.do"
void ensureDirectory(const std::string& path) {
#line 60 "/src/ios-app-driver.do"
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
#line 60 "/src/ios-app-driver.do"
        return;
    }
#line 61 "/src/ios-app-driver.do"
    const auto parent = parentPath(path);
#line 62 "/src/ios-app-driver.do"
    if (parent != path) {
#line 62 "/src/ios-app-driver.do"
        ensureDirectory(parent);
    }
#line 63 "/src/ios-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 63, std::string("try! failed"));  }();
}
#line 66 "/src/ios-app-driver.do"
void copyPath(const std::string& sourcePath, const std::string& destinationPath) {
#line 67 "/src/ios-app-driver.do"
    if (::doof_fs::isDirectory(sourcePath)) {
#line 68 "/src/ios-app-driver.do"
        ensureDirectory(destinationPath);
#line 69 "/src/ios-app-driver.do"
        const auto& _iterable_4 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 69, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_4) {
#line 70 "/src/ios-app-driver.do"
            copyPath(outputPath(sourcePath, entry->name), outputPath(destinationPath, entry->name));
        }
#line 72 "/src/ios-app-driver.do"
        return;
    }
#line 74 "/src/ios-app-driver.do"
    ensureDirectory(parentPath(destinationPath));
#line 75 "/src/ios-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(destinationPath, [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 75, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }()); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 75, std::string("try! failed"));  }();
}
#line 78 "/src/ios-app-driver.do"
void removeTree(const std::string& path) {
#line 79 "/src/ios-app-driver.do"
    if (!::doof_fs::exists(path)) {
#line 79 "/src/ios-app-driver.do"
        return;
    }
#line 80 "/src/ios-app-driver.do"
    if (::doof_fs::isDirectory(path)) {
#line 81 "/src/ios-app-driver.do"
        const auto& _iterable_6 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 81, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_6) {
#line 81 "/src/ios-app-driver.do"
            removeTree(outputPath(path, entry->name));
        }
    }
#line 83 "/src/ios-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 83, std::string("try! failed"));  }();
}
#line 86 "/src/ios-app-driver.do"
void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 87 "/src/ios-app-driver.do"
    if (!doof::array_contains(values, value, "", 0)) {
#line 87 "/src/ios-app-driver.do"
        values->push_back(value);
    }
}
#line 91 "/src/ios-app-driver.do"
doof::Result<void, std::string> configureIOSNativeBuild(const std::string& outputDirectory, const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& destination, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native) {
#line 97 "/src/ios-app-driver.do"
    if (hostPlatform() != std::string("macos")) {
#line 97 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ std::string("iOS app builds are only supported on macOS") };
    }
#line 98 "/src/ios-app-driver.do"
    const auto sdk = ((destination == std::string("device")) ? std::string("iphoneos") : std::string("iphonesimulator"));
#line 99 "/src/ios-app-driver.do"
    auto _try_value_7 = commandText(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--sdk"), sdk, std::string("--show-sdk-path")}), std::string("resolving the iOS SDK"));
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_7))};
    const auto sdkPath = doof::success_value(_try_value_7);
#line 100 "/src/ios-app-driver.do"
    auto _try_value_8 = commandText(std::string("uname"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-m")}), std::string("resolving the host architecture"));
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
    const auto architecture = doof::success_value(_try_value_8);
#line 101 "/src/ios-app-driver.do"
    auto _try_value_9 = ::app_src_ios_app_::iosTargetTriple(config->minimumDeploymentTarget, destination, architecture);
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
    const auto target = doof::success_value(_try_value_9);
#line 102 "/src/ios-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(outputDirectory, std::string("Info.plist")), ::app_src_ios_app_::renderIOSInfoPlist(config)); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 102, std::string("try! failed"));  }();
#line 103 "/src/ios-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(outputDirectory, std::string("ios-main.mm")), ::app_src_ios_app_::renderIOSMainSource(config->executableName)); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 103, std::string("try! failed"));  }();
#line 104 "/src/ios-app-driver.do"
    appendUnique(native->sourceFiles, std::string("ios-main.mm"));
#line 105 "/src/ios-app-driver.do"
    appendUnique(native->frameworks, std::string("UIKit"));
#line 106 "/src/ios-app-driver.do"
    appendUnique(native->frameworks, std::string("Foundation"));
#line 107 "/src/ios-app-driver.do"
    const auto& _iterable_11 = std::make_shared<std::vector<std::shared_ptr<std::vector<std::string>>>>(std::vector<std::shared_ptr<std::vector<std::string>>>{native->compilerFlags, native->linkerFlags});
    for (const auto& values : *_iterable_11) {
#line 108 "/src/ios-app-driver.do"
        appendUnique(values, std::string("-isysroot"));
#line 109 "/src/ios-app-driver.do"
        appendUnique(values, sdkPath);
#line 110 "/src/ios-app-driver.do"
        appendUnique(values, std::string("-target"));
#line 111 "/src/ios-app-driver.do"
        appendUnique(values, target);
    }
#line 113 "/src/ios-app-driver.do"
    return doof::Success<void>{};
}
#line 116 "/src/ios-app-driver.do"
std::string globBaseDirectory(const std::string& pattern) {
#line 117 "/src/ios-app-driver.do"
    auto wildcard = static_cast<int32_t>(pattern.size());
#line 118 "/src/ios-app-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>(pattern.size()); ++index) {
#line 119 "/src/ios-app-driver.do"
        if (doof::string_substring(pattern, index, (index + 1)) == std::string("*")) {
#line 119 "/src/ios-app-driver.do"
            (wildcard = index);
#line 119 "/src/ios-app-driver.do"
            break;
        }
    }
#line 121 "/src/ios-app-driver.do"
    if (wildcard == static_cast<int32_t>(pattern.size())) {
#line 121 "/src/ios-app-driver.do"
        return parentPath(pattern);
    }
#line 122 "/src/ios-app-driver.do"
    auto slash = wildcard;
#line 123 "/src/ios-app-driver.do"
    while ((slash > 0) && (doof::string_substring(pattern, (slash - 1), slash) != std::string("/"))) {
#line 123 "/src/ios-app-driver.do"
        (slash -= 1);
    }
#line 124 "/src/ios-app-driver.do"
    return ((slash <= 1) ? std::string("/") : doof::string_substring(pattern, 0, (slash - 1)));
}
#line 127 "/src/ios-app-driver.do"
bool globMatches(const std::string& pattern, const std::string& value, int32_t patternIndex, int32_t valueIndex) {
#line 128 "/src/ios-app-driver.do"
    if (patternIndex == static_cast<int32_t>(pattern.size())) {
#line 128 "/src/ios-app-driver.do"
        return (valueIndex == static_cast<int32_t>(value.size()));
    }
#line 129 "/src/ios-app-driver.do"
    const auto current = doof::string_substring(pattern, patternIndex, (patternIndex + 1));
#line 130 "/src/ios-app-driver.do"
    if (current != std::string("*")) {
#line 131 "/src/ios-app-driver.do"
        return (((valueIndex < static_cast<int32_t>(value.size())) && (current == doof::string_substring(value, valueIndex, (valueIndex + 1)))) && globMatches(pattern, value, (patternIndex + 1), (valueIndex + 1)));
    }
#line 134 "/src/ios-app-driver.do"
    const auto doubleStar = (((patternIndex + 1) < static_cast<int32_t>(pattern.size())) && (doof::string_substring(pattern, (patternIndex + 1), (patternIndex + 2)) == std::string("*")));
#line 135 "/src/ios-app-driver.do"
    const auto nextPattern = (patternIndex + (doubleStar ? 2 : 1));
#line 136 "/src/ios-app-driver.do"
    if (globMatches(pattern, value, nextPattern, valueIndex)) {
#line 136 "/src/ios-app-driver.do"
        return true;
    }
#line 137 "/src/ios-app-driver.do"
    if (valueIndex >= static_cast<int32_t>(value.size())) {
#line 137 "/src/ios-app-driver.do"
        return false;
    }
#line 138 "/src/ios-app-driver.do"
    if (!doubleStar && (doof::string_substring(value, valueIndex, (valueIndex + 1)) == std::string("/"))) {
#line 138 "/src/ios-app-driver.do"
        return false;
    }
#line 139 "/src/ios-app-driver.do"
    return globMatches(pattern, value, patternIndex, (valueIndex + 1));
}
#line 142 "/src/ios-app-driver.do"
void collectResourceFiles(const std::string& path, const std::string& baseDirectory, const std::string& pattern, const std::shared_ptr<std::vector<std::string>>& results) {
#line 143 "/src/ios-app-driver.do"
    if (::doof_fs::isDirectory(path)) {
#line 144 "/src/ios-app-driver.do"
        const auto& _iterable_14 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 144, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_14) {
#line 144 "/src/ios-app-driver.do"
            collectResourceFiles(outputPath(path, entry->name), baseDirectory, pattern, results);
        }
#line 145 "/src/ios-app-driver.do"
        return;
    }
#line 147 "/src/ios-app-driver.do"
    const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
#line 148 "/src/ios-app-driver.do"
    const auto relative = (doof::string_startsWith(path, prefix) ? doof::string_substring(path, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(path.size())) : fileName(path));
#line 149 "/src/ios-app-driver.do"
    const auto relativePattern = (doof::string_startsWith(pattern, prefix) ? doof::string_substring(pattern, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(pattern.size())) : fileName(pattern));
#line 150 "/src/ios-app-driver.do"
    if (globMatches(relativePattern, relative, 0, 0)) {
#line 150 "/src/ios-app-driver.do"
        results->push_back(path);
    }
}
#line 153 "/src/ios-app-driver.do"
doof::Result<void, std::string> copyIOSResources(const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& appPath) {
#line 154 "/src/ios-app-driver.do"
    std::shared_ptr<std::vector<std::string>> destinations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 155 "/src/ios-app-driver.do"
    const auto& _iterable_16 = config->resources;
    for (const auto& resource : *_iterable_16) {
#line 156 "/src/ios-app-driver.do"
        std::shared_ptr<std::vector<std::string>> files = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 157 "/src/ios-app-driver.do"
        auto baseDirectory = globBaseDirectory(resource->sourcePath);
#line 158 "/src/ios-app-driver.do"
        if (doof::string_contains(resource->sourcePath, std::string("*"))) {
#line 159 "/src/ios-app-driver.do"
            if (::doof_fs::exists(baseDirectory)) {
#line 159 "/src/ios-app-driver.do"
                collectResourceFiles(baseDirectory, baseDirectory, resource->sourcePath, files);
            }
        } else if (::doof_fs::isDirectory(resource->sourcePath)) {
#line 161 "/src/ios-app-driver.do"
            collectResourceFiles(resource->sourcePath, resource->sourcePath, (resource->sourcePath + std::string("/**")), files);
#line 162 "/src/ios-app-driver.do"
            (baseDirectory = resource->sourcePath);
        } else if (::doof_fs::exists(resource->sourcePath)) {
#line 164 "/src/ios-app-driver.do"
            files->push_back(resource->sourcePath);
#line 165 "/src/ios-app-driver.do"
            (baseDirectory = parentPath(resource->sourcePath));
        }
#line 167 "/src/ios-app-driver.do"
        if (static_cast<int32_t>((files)->size()) == 0) {
#line 167 "/src/ios-app-driver.do"
            return doof::Failure<std::string>{ (std::string("No files matched resource pattern: ") + resource->sourcePath) };
        }
#line 168 "/src/ios-app-driver.do"
        const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
#line 169 "/src/ios-app-driver.do"
        const auto& _iterable_18 = files;
        for (const auto& sourcePath : *_iterable_18) {
#line 170 "/src/ios-app-driver.do"
            const auto relative = (doof::string_startsWith(sourcePath, prefix) ? doof::string_substring(sourcePath, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(sourcePath.size())) : fileName(sourcePath));
#line 171 "/src/ios-app-driver.do"
            const auto destinationRoot = ((resource->destination == std::string("")) ? appPath : outputPath(appPath, resource->destination));
#line 172 "/src/ios-app-driver.do"
            const auto destination = outputPath(destinationRoot, relative);
#line 173 "/src/ios-app-driver.do"
            if (doof::array_contains(destinations, destination, "", 0)) {
#line 173 "/src/ios-app-driver.do"
                return doof::Failure<std::string>{ (std::string("Duplicate iOS app resource destination: ") + destination) };
            }
#line 174 "/src/ios-app-driver.do"
            destinations->push_back(destination);
#line 175 "/src/ios-app-driver.do"
            copyPath(sourcePath, destination);
        }
    }
#line 178 "/src/ios-app-driver.do"
    return doof::Success<void>{};
}
#line 181 "/src/ios-app-driver.do"
doof::Result<void, std::string> compileIOSIcon(const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& appPath, const std::string& destination, const std::string& buildDirectory) {
#line 182 "/src/ios-app-driver.do"
    if (config->iconPath == std::string("")) {
#line 182 "/src/ios-app-driver.do"
        return doof::Success<void>{};
    }
#line 183 "/src/ios-app-driver.do"
    const auto catalogPath = outputPath(buildDirectory, std::string("Assets.xcassets"));
#line 184 "/src/ios-app-driver.do"
    const auto iconSetPath = outputPath(catalogPath, std::string("AppIcon.appiconset"));
#line 185 "/src/ios-app-driver.do"
    removeTree(catalogPath);
#line 186 "/src/ios-app-driver.do"
    ensureDirectory(iconSetPath);
#line 187 "/src/ios-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(iconSetPath, std::string("Contents.json")), (::app_src_ios_app_::renderIOSIconSetContents() + std::string("\n"))); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 187, std::string("try! failed"));  }();
#line 188 "/src/ios-app-driver.do"
    const auto names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("iphone_notification_20@2x.png"), std::string("iphone_notification_20@3x.png"), std::string("iphone_settings_29@2x.png"), std::string("iphone_settings_29@3x.png"), std::string("iphone_spotlight_40@2x.png"), std::string("iphone_spotlight_40@3x.png"), std::string("iphone_app_60@2x.png"), std::string("iphone_app_60@3x.png"), std::string("ipad_notification_20.png"), std::string("ipad_notification_20@2x.png"), std::string("ipad_settings_29.png"), std::string("ipad_settings_29@2x.png"), std::string("ipad_spotlight_40.png"), std::string("ipad_spotlight_40@2x.png"), std::string("ipad_app_76.png"), std::string("ipad_app_76@2x.png"), std::string("ipad_pro_83_5@2x.png"), std::string("app_store_1024.png")});
#line 196 "/src/ios-app-driver.do"
    const auto sizes = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{40, 60, 58, 87, 80, 120, 120, 180, 20, 40, 29, 58, 40, 80, 76, 152, 167, 1024});
#line 197 "/src/ios-app-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
#line 198 "/src/ios-app-driver.do"
        const auto size = doof::to_string(doof::array_at(sizes, index, "src/ios-app-driver", 198));
#line 199 "/src/ios-app-driver.do"
        auto _try_value_20 = runRequiredCommand(std::string("sips"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-z"), size, size, config->iconPath, std::string("--out"), outputPath(iconSetPath, doof::array_at(names, index, "src/ios-app-driver", 200))}), std::string("resizing the iOS app icon"));
        if (doof::is_failure(_try_value_20)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_20))};
    }
#line 204 "/src/ios-app-driver.do"
    const auto partialPlistPath = outputPath(buildDirectory, std::string(".doof-ios-icon-info.plist"));
#line 205 "/src/ios-app-driver.do"
    const auto platformName = ((destination == std::string("device")) ? std::string("iphoneos") : std::string("iphonesimulator"));
#line 206 "/src/ios-app-driver.do"
    auto _try_value_21 = runRequiredCommand(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("actool"), catalogPath, std::string("--compile"), appPath, std::string("--platform"), platformName, std::string("--minimum-deployment-target"), config->minimumDeploymentTarget, std::string("--app-icon"), std::string("AppIcon"), std::string("--target-device"), std::string("iphone"), std::string("--target-device"), std::string("ipad"), std::string("--output-partial-info-plist"), partialPlistPath}), std::string("compiling the iOS app icon catalog"));
    if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_21))};
#line 212 "/src/ios-app-driver.do"
    auto _try_value_22 = runRequiredCommand(std::string("/usr/libexec/PlistBuddy"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), (std::string("Merge ") + partialPlistPath), outputPath(appPath, std::string("Info.plist"))}), std::string("merging iOS app icon metadata"));
    if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_22))};
#line 216 "/src/ios-app-driver.do"
    if (::doof_fs::exists(partialPlistPath)) {
#line 216 "/src/ios-app-driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::remove(partialPlistPath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 216, std::string("try! failed"));  }();
    }
#line 217 "/src/ios-app-driver.do"
    return doof::Success<void>{};
}
#line 221 "/src/ios-app-driver.do"
doof::Result<std::string, std::string> assembleIOSApp(const std::string& buildDirectory, const std::string& executablePath, const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& destination) {
#line 227 "/src/ios-app-driver.do"
    if (hostPlatform() != std::string("macos")) {
#line 227 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ std::string("iOS app builds are only supported on macOS") };
    }
#line 228 "/src/ios-app-driver.do"
    if (static_cast<int32_t>((config->embeddedLibraries)->size()) > 0) {
#line 229 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ std::string("Self-hosted iOS embedded library bundling is not yet supported") };
    }
#line 231 "/src/ios-app-driver.do"
    const auto appPath = outputPath(buildDirectory, (config->executableName + std::string(".app")));
#line 232 "/src/ios-app-driver.do"
    removeTree(appPath);
#line 233 "/src/ios-app-driver.do"
    ensureDirectory(appPath);
#line 234 "/src/ios-app-driver.do"
    const auto bundleExecutable = outputPath(appPath, config->executableName);
#line 235 "/src/ios-app-driver.do"
    copyPath(executablePath, bundleExecutable);
#line 236 "/src/ios-app-driver.do"
    auto _try_value_23 = runRequiredCommand(std::string("chmod"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("+x"), bundleExecutable}), std::string("marking the iOS executable"));
    if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_23))};
#line 237 "/src/ios-app-driver.do"
    const auto infoPlistPath = outputPath(buildDirectory, std::string("Info.plist"));
#line 238 "/src/ios-app-driver.do"
    if (::doof_fs::exists(infoPlistPath)) {
#line 239 "/src/ios-app-driver.do"
        copyPath(infoPlistPath, outputPath(appPath, std::string("Info.plist")));
    } else {
#line 241 "/src/ios-app-driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(appPath, std::string("Info.plist")), ::app_src_ios_app_::renderIOSInfoPlist(config)); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 241, std::string("try! failed"));  }();
    }
#line 243 "/src/ios-app-driver.do"
    auto _try_value_24 = copyIOSResources(config, appPath);
    if (doof::is_failure(_try_value_24)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_24))};
#line 244 "/src/ios-app-driver.do"
    auto _try_value_25 = compileIOSIcon(config, appPath, destination, buildDirectory);
    if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
#line 245 "/src/ios-app-driver.do"
    return doof::Success<std::string>{ appPath };
}
#line 248 "/src/ios-app-driver.do"
void collectNestedCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results) {
#line 249 "/src/ios-app-driver.do"
    if (!::doof_fs::exists(path)) {
#line 249 "/src/ios-app-driver.do"
        return;
    }
#line 250 "/src/ios-app-driver.do"
    if (::doof_fs::isDirectory(path)) {
#line 251 "/src/ios-app-driver.do"
        const auto& _iterable_27 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 251, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_27) {
#line 251 "/src/ios-app-driver.do"
            collectNestedCode(outputPath(path, entry->name), results);
        }
#line 252 "/src/ios-app-driver.do"
        if (doof::string_endsWith(path, std::string(".framework")) || doof::string_endsWith(path, std::string(".appex"))) {
#line 252 "/src/ios-app-driver.do"
            results->push_back(path);
        }
#line 253 "/src/ios-app-driver.do"
        return;
    }
#line 255 "/src/ios-app-driver.do"
    if (doof::string_endsWith(path, std::string(".dylib")) || doof::string_endsWith(path, std::string(".so"))) {
#line 255 "/src/ios-app-driver.do"
        results->push_back(path);
    }
}
#line 259 "/src/ios-app-driver.do"
doof::Result<void, std::string> signAndArchiveIOSApp(const std::string& appPath, const std::string& archivePath, const std::string& bundleId, const std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>& config, const std::string& buildDirectory) {
#line 266 "/src/ios-app-driver.do"
    if (hostPlatform() != std::string("macos")) {
#line 266 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ std::string("iOS Ad Hoc packaging is only supported on macOS") };
    }
#line 267 "/src/ios-app-driver.do"
    if (config->provisioningProfilePath == std::string("")) {
#line 268 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ std::string("No iOS provisioning profile configured; pass --ios-provisioning-profile") };
    }
#line 270 "/src/ios-app-driver.do"
    if (!::doof_fs::exists(config->provisioningProfilePath)) {
#line 270 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ (std::string("Provisioning profile not found: ") + config->provisioningProfilePath) };
    }
#line 272 "/src/ios-app-driver.do"
    const auto workDirectory = outputPath(buildDirectory, std::string(".doof-ios-package"));
#line 273 "/src/ios-app-driver.do"
    removeTree(workDirectory);
#line 274 "/src/ios-app-driver.do"
    ensureDirectory(workDirectory);
#line 275 "/src/ios-app-driver.do"
    const auto decodedProfilePath = outputPath(workDirectory, std::string("profile.plist"));
#line 276 "/src/ios-app-driver.do"
    const auto entitlementsPath = outputPath(workDirectory, std::string("entitlements.plist"));
#line 277 "/src/ios-app-driver.do"
    auto _try_value_28 = ::app_src_ios_device_::parseProvisioningProfile(config->provisioningProfilePath, workDirectory);
    if (doof::is_failure(_try_value_28)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_28))};
    const auto profile = doof::success_value(_try_value_28);
#line 278 "/src/ios-app-driver.do"
    auto _try_value_29 = commandText(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("find-identity"), std::string("-v"), std::string("-p"), std::string("codesigning")}), std::string("listing code-signing identities"));
    if (doof::is_failure(_try_value_29)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_29))};
    const auto identitiesOutput = doof::success_value(_try_value_29);
#line 281 "/src/ios-app-driver.do"
    const auto identities = ::app_src_ios_device_::parseCodesignIdentities(identitiesOutput);
#line 282 "/src/ios-app-driver.do"
    auto _try_value_30 = ::app_src_ios_device_::resolveIOSAdHocSigningIdentity(profile, identities, config->identity);
    if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_30))};
    const auto identity = doof::success_value(_try_value_30);
#line 283 "/src/ios-app-driver.do"
    auto _try_value_31 = ::app_src_ios_device_::validateIOSAdHocSigning(profile, identities, identity, bundleId, ::std_::time::temporal::Instant::now()->toEpochMillis());
    if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_31))};
#line 284 "/src/ios-app-driver.do"
    auto _try_value_32 = ::app_src_ios_app_::iosExactApplicationIdentifier(profile->applicationIdentifier, bundleId);
    if (doof::is_failure(_try_value_32)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_32))};
    const auto exactApplicationIdentifier = doof::success_value(_try_value_32);
#line 285 "/src/ios-app-driver.do"
    auto _try_value_33 = runRequiredCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements"), std::string("xml1"), std::string("-o"), entitlementsPath, decodedProfilePath}), std::string("extracting iOS signing entitlements"));
    if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_33))};
#line 289 "/src/ios-app-driver.do"
    auto _try_value_34 = runRequiredCommand(std::string("/usr/libexec/PlistBuddy"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), (std::string("Set :application-identifier ") + exactApplicationIdentifier), entitlementsPath}), std::string("expanding the iOS application identifier entitlement"));
    if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_34))};
#line 293 "/src/ios-app-driver.do"
    const auto keychainGroupCountResult = commandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("keychain-access-groups"), std::string("raw"), std::string("-o"), std::string("-"), entitlementsPath}), std::string("reading keychain access groups"));
#line 297 "/src/ios-app-driver.do"
    auto keychainGroupCount = 0;
#line 298 "/src/ios-app-driver.do"
    {
        auto _case_subject = keychainGroupCountResult;
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
#line 300 "/src/ios-app-driver.do"
            {
                auto _case_subject = ::doof_parse::parseInt(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
#line 301 "/src/ios-app-driver.do"
                    (keychainGroupCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<::std_::parse::types::ParsingError>>(_case_subject)) {
            }
            }
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
#line 307 "/src/ios-app-driver.do"
    for (int32_t index = 0; index < keychainGroupCount; ++index) {
#line 308 "/src/ios-app-driver.do"
        auto _binding_value_36 = commandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), (std::string("keychain-access-groups.") + doof::to_string(index)), std::string("raw"), std::string("-o"), std::string("-"), entitlementsPath}), std::string("reading keychain access group"));
        if (doof::is_failure(_binding_value_36)) {
            const auto& group = _binding_value_36;
#line 311 "/src/ios-app-driver.do"
            continue;
        }
        const auto group = doof::success_value(_binding_value_36);
#line 312 "/src/ios-app-driver.do"
        if (doof::string_contains(group, std::string("*"))) {
#line 313 "/src/ios-app-driver.do"
            auto _try_value_37 = runRequiredCommand(std::string("/usr/libexec/PlistBuddy"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), (((std::string("Set :keychain-access-groups:") + doof::to_string(index)) + std::string(" ")) + exactApplicationIdentifier), entitlementsPath}), std::string("expanding a keychain access group entitlement"));
            if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_37))};
        }
    }
#line 319 "/src/ios-app-driver.do"
    copyPath(config->provisioningProfilePath, outputPath(appPath, std::string("embedded.mobileprovision")));
#line 320 "/src/ios-app-driver.do"
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 321 "/src/ios-app-driver.do"
    collectNestedCode(outputPath(appPath, std::string("Frameworks")), nested);
#line 322 "/src/ios-app-driver.do"
    collectNestedCode(outputPath(appPath, std::string("PlugIns")), nested);
#line 323 "/src/ios-app-driver.do"
    const auto& _iterable_39 = nested;
    for (const auto& path : *_iterable_39) {
#line 324 "/src/ios-app-driver.do"
        auto _try_value_40 = runRequiredCommand(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(path, identity, std::string("")), std::string("signing nested iOS code"));
        if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_40))};
    }
#line 326 "/src/ios-app-driver.do"
    auto _try_value_41 = runRequiredCommand(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(appPath, identity, entitlementsPath), std::string("signing the iOS app"));
    if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_41))};
#line 327 "/src/ios-app-driver.do"
    auto _try_value_42 = runRequiredCommand(std::string("codesign"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--verify"), std::string("--deep"), std::string("--strict"), std::string("--verbose=2"), appPath}), std::string("verifying the iOS app signature"));
    if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_42))};
#line 328 "/src/ios-app-driver.do"
    auto _try_value_43 = commandText(std::string("codesign"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--display"), std::string("--entitlements"), std::string("-"), std::string("--xml"), appPath}), std::string("inspecting signed iOS entitlements"));
    if (doof::is_failure(_try_value_43)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_43))};
    const auto signedEntitlements = doof::success_value(_try_value_43);
#line 331 "/src/ios-app-driver.do"
    if (doof::string_contains(signedEntitlements, std::string("invalid entitlements blob")) || !doof::string_contains(signedEntitlements, exactApplicationIdentifier)) {
#line 332 "/src/ios-app-driver.do"
        removeTree(workDirectory);
#line 333 "/src/ios-app-driver.do"
        return doof::Failure<std::string>{ ((std::string("Signed iOS entitlements do not contain the exact application identifier \"") + exactApplicationIdentifier) + std::string("\"")) };
    }
#line 336 "/src/ios-app-driver.do"
    const auto payloadDirectory = outputPath(workDirectory, std::string("Payload"));
#line 337 "/src/ios-app-driver.do"
    ensureDirectory(payloadDirectory);
#line 338 "/src/ios-app-driver.do"
    auto _try_value_44 = runRequiredCommand(std::string("ditto"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{appPath, outputPath(payloadDirectory, fileName(appPath))}), std::string("staging the iOS app payload"));
    if (doof::is_failure(_try_value_44)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_44))};
#line 339 "/src/ios-app-driver.do"
    ensureDirectory(parentPath(archivePath));
#line 340 "/src/ios-app-driver.do"
    if (::doof_fs::exists(archivePath)) {
#line 340 "/src/ios-app-driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::remove(archivePath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-app-driver", 340, std::string("try! failed"));  }();
    }
#line 341 "/src/ios-app-driver.do"
    auto _try_value_45 = runRequiredCommand(std::string("ditto"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), std::string("-k"), std::string("--sequesterRsrc"), std::string("--keepParent"), payloadDirectory, archivePath}), std::string("archiving the iOS app"));
    if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_45))};
#line 345 "/src/ios-app-driver.do"
    removeTree(workDirectory);
#line 346 "/src/ios-app-driver.do"
    return doof::Success<void>{};
}
#line 1 "<doof-generated>"
}
