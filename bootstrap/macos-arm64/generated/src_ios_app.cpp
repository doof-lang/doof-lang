#include "src_ios_app.hpp"

namespace app_src_ios_app_ {




std::string iosPackageArchiveName(const std::string& executableName, const std::string& version) {
    auto safeVersion = std::string("");
    const auto allowed = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-");
    for (int32_t index = 0; index < static_cast<int32_t>(version.size()); ++index) {
        const auto character = doof::string_substring(version, index, (index + 1));
        (safeVersion = (safeVersion + (doof::string_contains(allowed, character) ? character : std::string("-"))));
    }
    return (((executableName + std::string("-")) + safeVersion) + std::string("-ios.ipa"));
}
doof::Result<std::string, std::string> iosExactApplicationIdentifier(const std::string& profileApplicationIdentifier, const std::string& bundleId) {
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
doof::Result<std::string, std::string> iosTargetTriple(const std::string& minimumDeploymentTarget, const std::string& destination, const std::string& architecture) {
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
std::shared_ptr<std::vector<std::string>> iosCodesignArguments(const std::string& targetPath, const std::string& identity, const std::string& entitlementsPath) {
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
std::string renderIOSInfoPlist(const std::shared_ptr<IOSAppConfig>& config) {
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
        const auto& _iterable_3 = doof::unwrap_optional(config->infoPlist);
        for (const auto& [key, value] : *_iterable_3) {
            (body += (((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n")) + renderPlistValue(value, 1)));
        }
    }
    return ((std::string("<\?xml version=\"1.0\" encoding=\"UTF-8\"\?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n") + body) + std::string("</dict>\n</plist>\n"));
}
std::string renderIOSMainSource(const std::string& executableName) {
    const auto delegateName = (objectiveCIdentifier(executableName) + std::string("AppDelegate"));
    return (((((((((((((((((((std::string("#import <UIKit/UIKit.h>\n#include <thread>\n\nextern \"C\" int doof_entry_main(int argc, char** argv);\n\n@interface ") + delegateName) + std::string(" : UIResponder <UIApplicationDelegate>\n")) + std::string("@property(nonatomic, strong) UIWindow* window;\n@end\n\n")) + std::string("@implementation ")) + delegateName) + std::string("\n")) + std::string("- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {\n")) + std::string("  (void)application;\n  (void)launchOptions;\n")) + std::string("  self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];\n")) + std::string("  UIViewController* rootViewController = [[UIViewController alloc] init];\n")) + std::string("  rootViewController.view.backgroundColor = UIColor.systemBackgroundColor;\n")) + std::string("  self.window.rootViewController = rootViewController;\n  [self.window makeKeyAndVisible];\n")) + std::string("  std::thread([] { (void)doof_entry_main(0, nullptr); }).detach();\n")) + std::string("  return YES;\n}\n@end\n\n")) + std::string("int main(int argc, char* argv[]) {\n  @autoreleasepool {\n")) + std::string("    return UIApplicationMain(argc, argv, nil, @\"")) + escapeObjectiveCString(delegateName)) + std::string("\");\n")) + std::string("  }\n}\n"));
}
std::string renderIOSIconSetContents() {
    return std::string("{\n  \"images\": [\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"20x20\", \"filename\": \"iphone_notification_20@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"20x20\", \"filename\": \"iphone_notification_20@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"29x29\", \"filename\": \"iphone_settings_29@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"29x29\", \"filename\": \"iphone_settings_29@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"40x40\", \"filename\": \"iphone_spotlight_40@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"40x40\", \"filename\": \"iphone_spotlight_40@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"60x60\", \"filename\": \"iphone_app_60@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"60x60\", \"filename\": \"iphone_app_60@3x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"20x20\", \"filename\": \"ipad_notification_20.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"20x20\", \"filename\": \"ipad_notification_20@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"29x29\", \"filename\": \"ipad_settings_29.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"29x29\", \"filename\": \"ipad_settings_29@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"40x40\", \"filename\": \"ipad_spotlight_40.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"40x40\", \"filename\": \"ipad_spotlight_40@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"76x76\", \"filename\": \"ipad_app_76.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"76x76\", \"filename\": \"ipad_app_76@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"83.5x83.5\", \"filename\": \"ipad_pro_83_5@2x.png\" },\n    { \"idiom\": \"ios-marketing\", \"scale\": \"1x\", \"size\": \"1024x1024\", \"filename\": \"app_store_1024.png\" }\n  ],\n  \"info\": { \"author\": \"doof\", \"version\": 1 }\n}");
}
std::string objectiveCIdentifier(const std::string& value) {
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
std::string escapeObjectiveCString(const std::string& value) {
    return doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
}
std::string plistString(const std::string& key, const std::string& value) {
    return ((((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n\t<string>")) + escapePlistText(value)) + std::string("</string>\n"));
}
std::string plistIndent(int32_t depth) {
    auto result = std::string("");
    for (int32_t ignored = 0; ignored < depth; ++ignored) {
        (result += std::string("\t"));
    }
    return result;
}
std::string renderPlistValue(const doof::JsonValue& value, int32_t depth) {
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
            const auto& _iterable_7 = array;
            for (const auto& item : *_iterable_7) {
                (result += renderPlistValue(item, (depth + 1)));
            }
            return ((result + indent) + std::string("</array>\n"));
    }
    else if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            auto result = (indent + std::string("<dict>\n"));
            const auto& _iterable_9 = object;
            for (const auto& [key, item] : *_iterable_9) {
                (result += (((plistIndent((depth + 1)) + std::string("<key>")) + escapePlistText(key)) + std::string("</key>\n")));
                (result += renderPlistValue(item, (depth + 1)));
            }
            return ((result + indent) + std::string("</dict>\n"));
    }
    }
    doof::panic(std::string("unhandled plist value"));
}
std::string escapePlistText(const std::string& value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("&"), std::string("&amp;")), std::string("<"), std::string("&lt;")), std::string(">"), std::string("&gt;")), std::string("\""), std::string("&quot;")), std::string("'"), std::string("&apos;"));
}
}
