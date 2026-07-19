#include "src_ios_app.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_ios_app_ {

doof::JsonObject IOSAppResource::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["sourcePath"] = doof::json_value(this->sourcePath);
    (*_json)["destination"] = doof::json_value(this->destination);
    return _json;
}
doof::Result<std::shared_ptr<IOSAppResource>, std::string> IOSAppResource::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_sourcePath = _object->find("sourcePath");
    if (_iterator_sourcePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourcePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourcePath->second) : doof::json_is_string(_iterator_sourcePath->second)))) { return doof::Failure<std::string>{"Field \"sourcePath\" expected string but got " + std::string(doof::json_type_name(_iterator_sourcePath->second))}; }
    auto _field_sourcePath = (_lenient ? doof::json_as_string_lenient(_iterator_sourcePath->second) : doof::json_as_string(_iterator_sourcePath->second));
    auto _iterator_destination = _object->find("destination");
    if (_iterator_destination == _object->end()) { return doof::Failure<std::string>{"Missing required field \"destination\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_destination->second) : doof::json_is_string(_iterator_destination->second)))) { return doof::Failure<std::string>{"Field \"destination\" expected string but got " + std::string(doof::json_type_name(_iterator_destination->second))}; }
    auto _field_destination = (_lenient ? doof::json_as_string_lenient(_iterator_destination->second) : doof::json_as_string(_iterator_destination->second));
    return doof::Success<std::shared_ptr<IOSAppResource>>{std::make_shared<IOSAppResource>(_field_sourcePath, _field_destination)};
}

doof::JsonObject IOSEmbeddedLibrary::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["library"] = doof::json_value(this->library);
    (*_json)["path"] = doof::json_value(this->path);
    return _json;
}
doof::Result<std::shared_ptr<IOSEmbeddedLibrary>, std::string> IOSEmbeddedLibrary::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_library;
    if (auto _iterator_library = _object->find("library"); _iterator_library != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_library->second) : doof::json_is_string(_iterator_library->second)))) { return doof::Failure<std::string>{"Field \"library\" expected string but got " + std::string(doof::json_type_name(_iterator_library->second))}; }
        _field_library = (_lenient ? doof::json_as_string_lenient(_iterator_library->second) : doof::json_as_string(_iterator_library->second));
    } else {
        _field_library = std::string{std::string("")};
    }
    std::optional<std::string> _field_path;
    if (auto _iterator_path = _object->find("path"); _iterator_path != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
        _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    } else {
        _field_path = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<IOSEmbeddedLibrary>>{std::make_shared<IOSEmbeddedLibrary>(_field_library.value(), _field_path.value())};
}

doof::JsonObject IOSAppConfig::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["executableName"] = doof::json_value(this->executableName);
    (*_json)["bundleId"] = doof::json_value(this->bundleId);
    (*_json)["displayName"] = doof::json_value(this->displayName);
    (*_json)["version"] = doof::json_value(this->version);
    (*_json)["iconPath"] = doof::json_value(this->iconPath);
    (*_json)["infoPlist"] = (this->infoPlist ? doof::json_value(this->infoPlist) : doof::json_value(nullptr));
    (*_json)["resources"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->resources->size()); for (const auto& _element : *this->resources) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["embeddedLibraries"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->embeddedLibraries->size()); for (const auto& _element : *this->embeddedLibraries) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["minimumDeploymentTarget"] = doof::json_value(this->minimumDeploymentTarget);
    return _json;
}
doof::Result<std::shared_ptr<IOSAppConfig>, std::string> IOSAppConfig::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_executableName = _object->find("executableName");
    if (_iterator_executableName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"executableName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_executableName->second) : doof::json_is_string(_iterator_executableName->second)))) { return doof::Failure<std::string>{"Field \"executableName\" expected string but got " + std::string(doof::json_type_name(_iterator_executableName->second))}; }
    auto _field_executableName = (_lenient ? doof::json_as_string_lenient(_iterator_executableName->second) : doof::json_as_string(_iterator_executableName->second));
    auto _iterator_bundleId = _object->find("bundleId");
    if (_iterator_bundleId == _object->end()) { return doof::Failure<std::string>{"Missing required field \"bundleId\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_bundleId->second) : doof::json_is_string(_iterator_bundleId->second)))) { return doof::Failure<std::string>{"Field \"bundleId\" expected string but got " + std::string(doof::json_type_name(_iterator_bundleId->second))}; }
    auto _field_bundleId = (_lenient ? doof::json_as_string_lenient(_iterator_bundleId->second) : doof::json_as_string(_iterator_bundleId->second));
    auto _iterator_displayName = _object->find("displayName");
    if (_iterator_displayName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"displayName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_displayName->second) : doof::json_is_string(_iterator_displayName->second)))) { return doof::Failure<std::string>{"Field \"displayName\" expected string but got " + std::string(doof::json_type_name(_iterator_displayName->second))}; }
    auto _field_displayName = (_lenient ? doof::json_as_string_lenient(_iterator_displayName->second) : doof::json_as_string(_iterator_displayName->second));
    auto _iterator_version = _object->find("version");
    if (_iterator_version == _object->end()) { return doof::Failure<std::string>{"Missing required field \"version\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_version->second) : doof::json_is_string(_iterator_version->second)))) { return doof::Failure<std::string>{"Field \"version\" expected string but got " + std::string(doof::json_type_name(_iterator_version->second))}; }
    auto _field_version = (_lenient ? doof::json_as_string_lenient(_iterator_version->second) : doof::json_as_string(_iterator_version->second));
    std::optional<std::string> _field_iconPath;
    if (auto _iterator_iconPath = _object->find("iconPath"); _iterator_iconPath != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_iconPath->second) : doof::json_is_string(_iterator_iconPath->second)))) { return doof::Failure<std::string>{"Field \"iconPath\" expected string but got " + std::string(doof::json_type_name(_iterator_iconPath->second))}; }
        _field_iconPath = (_lenient ? doof::json_as_string_lenient(_iterator_iconPath->second) : doof::json_as_string(_iterator_iconPath->second));
    } else {
        _field_iconPath = std::string{std::string("")};
    }
    std::optional<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>> _field_infoPlist;
    if (auto _iterator_infoPlist = _object->find("infoPlist"); _iterator_infoPlist != _object->end()) {
        if (!(doof::json_is_null(_iterator_infoPlist->second) || doof::json_is_object(_iterator_infoPlist->second))) { return doof::Failure<std::string>{"Field \"infoPlist\" expected object or null but got " + std::string(doof::json_type_name(_iterator_infoPlist->second))}; }
        _field_infoPlist = (doof::json_is_null(_iterator_infoPlist->second) ? nullptr : [&]() { const auto* _object_value = doof::json_as_object(_iterator_infoPlist->second); auto _values = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = _entry.second; } return _values; }());
    } else {
        _field_infoPlist = std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>{nullptr};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>>> _field_resources;
    if (auto _iterator_resources = _object->find("resources"); _iterator_resources != _object->end()) {
        if (!(doof::json_is_array(_iterator_resources->second))) { return doof::Failure<std::string>{"Field \"resources\" expected array but got " + std::string(doof::json_type_name(_iterator_resources->second))}; }
        _field_resources = [&]() { const auto* _array = doof::json_as_array(_iterator_resources->second); auto _values = std::make_shared<std::vector<std::shared_ptr<IOSAppResource>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(IOSAppResource::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_resources = std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>>{std::make_shared<std::vector<std::shared_ptr<IOSAppResource>>>(std::vector<std::shared_ptr<IOSAppResource>>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>>> _field_embeddedLibraries;
    if (auto _iterator_embeddedLibraries = _object->find("embeddedLibraries"); _iterator_embeddedLibraries != _object->end()) {
        if (!(doof::json_is_array(_iterator_embeddedLibraries->second))) { return doof::Failure<std::string>{"Field \"embeddedLibraries\" expected array but got " + std::string(doof::json_type_name(_iterator_embeddedLibraries->second))}; }
        _field_embeddedLibraries = [&]() { const auto* _array = doof::json_as_array(_iterator_embeddedLibraries->second); auto _values = std::make_shared<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(IOSEmbeddedLibrary::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_embeddedLibraries = std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>>{std::make_shared<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<IOSEmbeddedLibrary>>{})};
    }
    std::optional<std::string> _field_minimumDeploymentTarget;
    if (auto _iterator_minimumDeploymentTarget = _object->find("minimumDeploymentTarget"); _iterator_minimumDeploymentTarget != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_minimumDeploymentTarget->second) : doof::json_is_string(_iterator_minimumDeploymentTarget->second)))) { return doof::Failure<std::string>{"Field \"minimumDeploymentTarget\" expected string but got " + std::string(doof::json_type_name(_iterator_minimumDeploymentTarget->second))}; }
        _field_minimumDeploymentTarget = (_lenient ? doof::json_as_string_lenient(_iterator_minimumDeploymentTarget->second) : doof::json_as_string(_iterator_minimumDeploymentTarget->second));
    } else {
        _field_minimumDeploymentTarget = std::string{std::string("16.0")};
    }
    return doof::Success<std::shared_ptr<IOSAppConfig>>{std::make_shared<IOSAppConfig>(_field_executableName, _field_bundleId, _field_displayName, _field_version, _field_iconPath.value(), _field_infoPlist.value(), _field_resources.value(), _field_embeddedLibraries.value(), _field_minimumDeploymentTarget.value())};
}

doof::JsonObject IOSPackageConfig::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["identity"] = doof::json_value(this->identity);
    (*_json)["provisioningProfilePath"] = doof::json_value(this->provisioningProfilePath);
    return _json;
}
doof::Result<std::shared_ptr<IOSPackageConfig>, std::string> IOSPackageConfig::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_identity;
    if (auto _iterator_identity = _object->find("identity"); _iterator_identity != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_identity->second) : doof::json_is_string(_iterator_identity->second)))) { return doof::Failure<std::string>{"Field \"identity\" expected string but got " + std::string(doof::json_type_name(_iterator_identity->second))}; }
        _field_identity = (_lenient ? doof::json_as_string_lenient(_iterator_identity->second) : doof::json_as_string(_iterator_identity->second));
    } else {
        _field_identity = std::string{std::string("")};
    }
    std::optional<std::string> _field_provisioningProfilePath;
    if (auto _iterator_provisioningProfilePath = _object->find("provisioningProfilePath"); _iterator_provisioningProfilePath != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_provisioningProfilePath->second) : doof::json_is_string(_iterator_provisioningProfilePath->second)))) { return doof::Failure<std::string>{"Field \"provisioningProfilePath\" expected string but got " + std::string(doof::json_type_name(_iterator_provisioningProfilePath->second))}; }
        _field_provisioningProfilePath = (_lenient ? doof::json_as_string_lenient(_iterator_provisioningProfilePath->second) : doof::json_as_string(_iterator_provisioningProfilePath->second));
    } else {
        _field_provisioningProfilePath = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<IOSPackageConfig>>{std::make_shared<IOSPackageConfig>(_field_identity.value(), _field_provisioningProfilePath.value())};
}
std::string iosPackageArchiveName(std::string executableName, std::string version) {
    auto safeVersion = std::string("");
    const auto allowed = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-");
    for (int32_t index = 0; index < static_cast<int32_t>(version.size()); ++index) {
        const auto character = doof::string_substring(version, index, (index + 1));
        (safeVersion = (safeVersion + (doof::string_contains(allowed, character) ? character : std::string("-"))));
    }
    return (((executableName + std::string("-")) + safeVersion) + std::string("-ios.ipa"));
}
doof::Result<std::string, std::string> iosExactApplicationIdentifier(std::string profileApplicationIdentifier, std::string bundleId) {
    const auto separator = doof::string_indexOf(profileApplicationIdentifier, std::string("."));
    if (separator < 0) {
        return doof::Failure<std::string>{ std::string("Provisioning profile application-identifier is malformed") };
    }
    const auto prefix = doof::string_substring(profileApplicationIdentifier, 0, separator);
    const auto provisionedBundleId = doof::string_substring(profileApplicationIdentifier, (separator + 1), static_cast<int32_t>(profileApplicationIdentifier.size()));
    const auto matches = (((provisionedBundleId == bundleId) || (provisionedBundleId == std::string("*"))) || (doof::string_endsWith(provisionedBundleId, std::string(".*")) && doof::string_startsWith(bundleId, doof::string_substring(provisionedBundleId, 0, (static_cast<int32_t>(provisionedBundleId.size()) - 1)))));
    if (!matches) {
        return doof::Failure<std::string>{ ((((std::string("Provisioning profile application-identifier \"") + profileApplicationIdentifier) + std::string("\" does not match bundle id \"")) + bundleId) + std::string("\"")) };
    }
    return doof::Success<std::string>{ ((prefix + std::string(".")) + bundleId) };
}
doof::Result<std::string, std::string> iosTargetTriple(std::string minimumDeploymentTarget, std::string destination, std::string architecture) {
    if (destination == std::string("device")) {
        return doof::Success<std::string>{ (std::string("arm64-apple-ios") + minimumDeploymentTarget) };
    }
    if (destination != std::string("simulator")) {
        return doof::Failure<std::string>{ (std::string("Unknown iOS destination: ") + destination) };
    }
    if (architecture == std::string("arm64")) {
        return doof::Success<std::string>{ ((std::string("arm64-apple-ios") + minimumDeploymentTarget) + std::string("-simulator")) };
    }
    if ((architecture == std::string("x86_64")) || (architecture == std::string("x64"))) {
        return doof::Success<std::string>{ ((std::string("x86_64-apple-ios") + minimumDeploymentTarget) + std::string("-simulator")) };
    }
    return doof::Failure<std::string>{ (std::string("Unsupported macOS host architecture for iOS simulator builds: ") + architecture) };
}
std::shared_ptr<std::vector<std::string>> iosCodesignArguments(std::string targetPath, std::string identity, std::string entitlementsPath) {
    auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--force"), std::string("--sign"), identity});
    if (entitlementsPath != std::string("")) {
        arguments->push_back(std::string("--entitlements"));
        arguments->push_back(entitlementsPath);
        arguments->push_back(std::string("--generate-entitlement-der"));
    }
    arguments->push_back(std::string("--timestamp=none"));
    arguments->push_back(targetPath);
    return arguments;
}
std::string renderIOSInfoPlist(std::shared_ptr<IOSAppConfig> config) {
    auto body = std::string("");
    (body += plistString(std::string("CFBundleDevelopmentRegion"), std::string("en")));
    (body += plistString(std::string("CFBundleDisplayName"), config->displayName));
    (body += plistString(std::string("CFBundleExecutable"), config->executableName));
    (body += plistString(std::string("CFBundleIdentifier"), config->bundleId));
    (body += plistString(std::string("CFBundleInfoDictionaryVersion"), std::string("6.0")));
    (body += plistString(std::string("CFBundleName"), config->displayName));
    (body += plistString(std::string("CFBundlePackageType"), std::string("APPL")));
    (body += plistString(std::string("CFBundleShortVersionString"), config->version));
    (body += plistString(std::string("CFBundleVersion"), config->version));
    (body += std::string("\t<key>LSRequiresIPhoneOS</key>\n\t<true/>\n"));
    (body += plistString(std::string("MinimumOSVersion"), config->minimumDeploymentTarget));
    (body += std::string("\t<key>UIDeviceFamily</key>\n\t<array>\n\t\t<integer>1</integer>\n\t\t<integer>2</integer>\n\t</array>\n"));
    (body += plistString(std::string("UILaunchStoryboardName"), std::string("")));
    (body += std::string("\t<key>UIApplicationSceneManifest</key>\n\t<dict>\n\t\t<key>UIApplicationSupportsMultipleScenes</key>\n\t\t<false/>\n\t</dict>\n"));
    if (!doof::is_null(config->infoPlist)) {
        const auto& _iterable_1 = doof::unwrap_optional(config->infoPlist);
        for (const auto& [key, value] : *_iterable_1) {
            (body += (((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n")) + renderPlistValue(value, 1)));
        }
    }
    return ((((std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") + std::string("<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n")) + std::string("<plist version=\"1.0\">\n<dict>\n")) + body) + std::string("</dict>\n</plist>\n"));
}
std::string renderIOSMainSource(std::string executableName) {
    const auto delegateName = (objectiveCIdentifier(executableName) + std::string("AppDelegate"));
    return (((((((((((((((((((((std::string("#import <UIKit/UIKit.h>\n#include <thread>\n\n") + std::string("extern \"C\" int doof_entry_main(int argc, char** argv);\n\n")) + std::string("@interface ")) + delegateName) + std::string(" : UIResponder <UIApplicationDelegate>\n")) + std::string("@property(nonatomic, strong) UIWindow* window;\n@end\n\n")) + std::string("@implementation ")) + delegateName) + std::string("\n")) + std::string("- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {\n")) + std::string("  (void)application;\n  (void)launchOptions;\n")) + std::string("  self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];\n")) + std::string("  UIViewController* rootViewController = [[UIViewController alloc] init];\n")) + std::string("  rootViewController.view.backgroundColor = UIColor.systemBackgroundColor;\n")) + std::string("  self.window.rootViewController = rootViewController;\n  [self.window makeKeyAndVisible];\n")) + std::string("  std::thread([] { (void)doof_entry_main(0, nullptr); }).detach();\n")) + std::string("  return YES;\n}\n@end\n\n")) + std::string("int main(int argc, char* argv[]) {\n  @autoreleasepool {\n")) + std::string("    return UIApplicationMain(argc, argv, nil, @\"")) + escapeObjectiveCString(delegateName)) + std::string("\");\n")) + std::string("  }\n}\n"));
}
std::string renderIOSIconSetContents() {
    return std::string("{\n  \"images\": [\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"20x20\", \"filename\": \"iphone_notification_20@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"20x20\", \"filename\": \"iphone_notification_20@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"29x29\", \"filename\": \"iphone_settings_29@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"29x29\", \"filename\": \"iphone_settings_29@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"40x40\", \"filename\": \"iphone_spotlight_40@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"40x40\", \"filename\": \"iphone_spotlight_40@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"60x60\", \"filename\": \"iphone_app_60@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"60x60\", \"filename\": \"iphone_app_60@3x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"20x20\", \"filename\": \"ipad_notification_20.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"20x20\", \"filename\": \"ipad_notification_20@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"29x29\", \"filename\": \"ipad_settings_29.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"29x29\", \"filename\": \"ipad_settings_29@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"40x40\", \"filename\": \"ipad_spotlight_40.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"40x40\", \"filename\": \"ipad_spotlight_40@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"76x76\", \"filename\": \"ipad_app_76.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"76x76\", \"filename\": \"ipad_app_76@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"83.5x83.5\", \"filename\": \"ipad_pro_83_5@2x.png\" },\n    { \"idiom\": \"ios-marketing\", \"scale\": \"1x\", \"size\": \"1024x1024\", \"filename\": \"app_store_1024.png\" }\n  ],\n  \"info\": { \"author\": \"doof\", \"version\": 1 }\n}");
}
std::string objectiveCIdentifier(std::string value) {
    const auto first = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_");
    const auto rest = (first + std::string("0123456789"));
    auto result = std::string("");
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
        const auto character = doof::string_substring(value, index, (index + 1));
        (result += (doof::string_contains(rest, character) ? character : std::string("_")));
    }
    if (result == std::string("")) {
        return std::string("DoofApp");
    }
    return (doof::string_contains(first, doof::string_substring(result, 0, 1)) ? result : (std::string("Doof_") + result));
}
std::string escapeObjectiveCString(std::string value) {
    return doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
}
std::string plistString(std::string key, std::string value) {
    return ((((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n\t<string>")) + escapePlistText(value)) + std::string("</string>\n"));
}
std::string plistIndent(int32_t depth) {
    auto result = std::string("");
    for (int32_t ignored = 0; ignored < depth; ++ignored) {
        (result += std::string("\t"));
    }
    return result;
}
std::string renderPlistValue(doof::JsonValue value, int32_t depth) {
    const auto indent = plistIndent(depth);
    {
        auto _case_subject = value;
        if (doof::json_is_null(_case_subject)) {
            return (indent + std::string("<string></string>\n"));
    }
    else if (doof::json_is_boolean(_case_subject)) {
            const auto boolean = doof::json_as_bool(_case_subject);
            return (indent + (boolean ? std::string("<true/>\n") : std::string("<false/>\n")));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_int(_case_subject);
            return (((indent + std::string("<integer>")) + doof::to_string(number)) + std::string("</integer>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_long(_case_subject);
            return (((indent + std::string("<integer>")) + doof::to_string(number)) + std::string("</integer>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_float(_case_subject);
            return (((indent + std::string("<real>")) + doof::to_string(number)) + std::string("</real>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_double(_case_subject);
            return (((indent + std::string("<real>")) + doof::to_string(number)) + std::string("</real>\n"));
    }
    else if (doof::json_is_string(_case_subject)) {
            const auto text = doof::json_as_string(_case_subject);
            return (((indent + std::string("<string>")) + escapePlistText(text)) + std::string("</string>\n"));
    }
    else if (doof::json_is_array(_case_subject)) {
            const auto array = std::get<doof::JsonArray>(doof::json_storage(_case_subject));
            auto result = (indent + std::string("<array>\n"));
            const auto& _iterable_2 = array;
            for (const auto& item : *_iterable_2) {
                (result += renderPlistValue(item, (depth + 1)));
            }
            return ((result + indent) + std::string("</array>\n"));
    }
    else if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            auto result = (indent + std::string("<dict>\n"));
            const auto& _iterable_3 = object;
            for (const auto& [key, item] : *_iterable_3) {
                (result += (((plistIndent((depth + 1)) + std::string("<key>")) + escapePlistText(key)) + std::string("</key>\n")));
                (result += renderPlistValue(item, (depth + 1)));
            }
            return ((result + indent) + std::string("</dict>\n"));
    }
    }
    doof::panic(std::string("unhandled plist value"));
}
std::string escapePlistText(std::string value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("&"), std::string("&amp;")), std::string("<"), std::string("&lt;")), std::string(">"), std::string("&gt;")), std::string("\""), std::string("&quot;")), std::string("'"), std::string("&apos;"));
}
}
