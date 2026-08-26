#include "src_ios_app.hpp"

namespace app_src_ios_app_ {




#line 36 "/src/ios-app.do"
std::string iosPackageArchiveName(const std::string& executableName, const std::string& version) {
#line 37 "/src/ios-app.do"
    auto safeVersion = std::string("");
#line 38 "/src/ios-app.do"
    const auto allowed = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-");
#line 39 "/src/ios-app.do"
    for (int32_t index = 0; index < static_cast<int32_t>(version.size()); ++index) {
#line 40 "/src/ios-app.do"
        const auto character = doof::string_substring(version, index, (index + 1));
#line 41 "/src/ios-app.do"
        (safeVersion = (safeVersion + (doof::string_contains(allowed, character) ? character : std::string("-"))));
    }
#line 43 "/src/ios-app.do"
    return (((executableName + std::string("-")) + safeVersion) + std::string("-ios.ipa"));
}
#line 47 "/src/ios-app.do"
doof::Result<std::string, std::string> iosExactApplicationIdentifier(const std::string& profileApplicationIdentifier, const std::string& bundleId) {
#line 51 "/src/ios-app.do"
    const auto separator = doof::string_indexOf(profileApplicationIdentifier, std::string("."));
#line 52 "/src/ios-app.do"
    if (separator < 0) {
#line 53 "/src/ios-app.do"
        return doof::Failure<std::string>{ std::string("Provisioning profile application-identifier is malformed") };
    }
#line 55 "/src/ios-app.do"
    const auto prefix = doof::string_substring(profileApplicationIdentifier, 0, separator);
#line 56 "/src/ios-app.do"
    const auto provisionedBundleId = doof::string_substring(profileApplicationIdentifier, (separator + 1), static_cast<int32_t>(profileApplicationIdentifier.size()));
#line 57 "/src/ios-app.do"
    const auto matches = (((provisionedBundleId == bundleId) || (provisionedBundleId == std::string("*"))) || (doof::string_endsWith(provisionedBundleId, std::string(".*")) && doof::string_startsWith(bundleId, doof::string_substring(provisionedBundleId, 0, (static_cast<int32_t>(provisionedBundleId.size()) - 1)))));
#line 59 "/src/ios-app.do"
    if (!matches) {
#line 60 "/src/ios-app.do"
        return doof::Failure<std::string>{ ((((std::string("Provisioning profile application-identifier \"") + profileApplicationIdentifier) + std::string("\" does not match bundle id \"")) + bundleId) + std::string("\"")) };
    }
#line 65 "/src/ios-app.do"
    return doof::Success<std::string>{ ((prefix + std::string(".")) + bundleId) };
}
#line 68 "/src/ios-app.do"
doof::Result<std::string, std::string> iosTargetTriple(const std::string& minimumDeploymentTarget, const std::string& destination, const std::string& architecture) {
#line 69 "/src/ios-app.do"
    if (destination == std::string("device")) {
#line 69 "/src/ios-app.do"
        return doof::Success<std::string>{ (std::string("arm64-apple-ios") + minimumDeploymentTarget) };
    }
#line 70 "/src/ios-app.do"
    if (destination != std::string("simulator")) {
#line 70 "/src/ios-app.do"
        return doof::Failure<std::string>{ (std::string("Unknown iOS destination: ") + destination) };
    }
#line 71 "/src/ios-app.do"
    if (architecture == std::string("arm64")) {
#line 71 "/src/ios-app.do"
        return doof::Success<std::string>{ ((std::string("arm64-apple-ios") + minimumDeploymentTarget) + std::string("-simulator")) };
    }
#line 72 "/src/ios-app.do"
    if ((architecture == std::string("x86_64")) || (architecture == std::string("x64"))) {
#line 73 "/src/ios-app.do"
        return doof::Success<std::string>{ ((std::string("x86_64-apple-ios") + minimumDeploymentTarget) + std::string("-simulator")) };
    }
#line 75 "/src/ios-app.do"
    return doof::Failure<std::string>{ (std::string("Unsupported macOS host architecture for iOS simulator builds: ") + architecture) };
}
#line 78 "/src/ios-app.do"
std::shared_ptr<std::vector<std::string>> iosCodesignArguments(const std::string& targetPath, const std::string& identity, const std::string& entitlementsPath) {
#line 79 "/src/ios-app.do"
    auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--force"), std::string("--sign"), identity});
#line 80 "/src/ios-app.do"
    if (entitlementsPath != std::string("")) {
#line 81 "/src/ios-app.do"
        arguments->push_back(std::string("--entitlements"));
#line 82 "/src/ios-app.do"
        arguments->push_back(entitlementsPath);
#line 83 "/src/ios-app.do"
        arguments->push_back(std::string("--generate-entitlement-der"));
    }
#line 85 "/src/ios-app.do"
    arguments->push_back(std::string("--timestamp=none"));
#line 86 "/src/ios-app.do"
    arguments->push_back(targetPath);
#line 87 "/src/ios-app.do"
    return arguments;
}
#line 91 "/src/ios-app.do"
std::string renderIOSInfoPlist(const std::shared_ptr<IOSAppConfig>& config) {
#line 92 "/src/ios-app.do"
    auto body = std::string("");
#line 93 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleDevelopmentRegion"), std::string("en")));
#line 94 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleDisplayName"), config->displayName));
#line 95 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleExecutable"), config->executableName));
#line 96 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleIdentifier"), config->bundleId));
#line 97 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleInfoDictionaryVersion"), std::string("6.0")));
#line 98 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleName"), config->displayName));
#line 99 "/src/ios-app.do"
    (body += plistString(std::string("CFBundlePackageType"), std::string("APPL")));
#line 100 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleShortVersionString"), config->version));
#line 101 "/src/ios-app.do"
    (body += plistString(std::string("CFBundleVersion"), config->version));
#line 102 "/src/ios-app.do"
    (body += std::string("\t<key>LSRequiresIPhoneOS</key>\n\t<true/>\n"));
#line 103 "/src/ios-app.do"
    (body += plistString(std::string("MinimumOSVersion"), config->minimumDeploymentTarget));
#line 104 "/src/ios-app.do"
    (body += std::string("\t<key>UIDeviceFamily</key>\n\t<array>\n\t\t<integer>1</integer>\n\t\t<integer>2</integer>\n\t</array>\n"));
#line 105 "/src/ios-app.do"
    (body += plistString(std::string("UILaunchStoryboardName"), std::string("")));
#line 106 "/src/ios-app.do"
    (body += std::string("\t<key>UIApplicationSceneManifest</key>\n\t<dict>\n\t\t<key>UIApplicationSupportsMultipleScenes</key>\n\t\t<false/>\n\t</dict>\n"));
#line 107 "/src/ios-app.do"
    if (!doof::is_null(config->infoPlist)) {
#line 108 "/src/ios-app.do"
        const auto& _iterable_3 = doof::unwrap_optional(config->infoPlist);
        for (const auto& [key, value] : *_iterable_3) {
#line 109 "/src/ios-app.do"
            (body += (((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n")) + renderPlistValue(value, 1)));
        }
    }
#line 112 "/src/ios-app.do"
    return ((std::string("<\?xml version=\"1.0\" encoding=\"UTF-8\"\?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n") + body) + std::string("</dict>\n</plist>\n"));
}
#line 118 "/src/ios-app.do"
std::string renderIOSMainSource(const std::string& executableName) {
#line 119 "/src/ios-app.do"
    const auto delegateName = (objectiveCIdentifier(executableName) + std::string("AppDelegate"));
#line 120 "/src/ios-app.do"
    return (((((((((((((((((((std::string("#import <UIKit/UIKit.h>\n#include <thread>\n\nextern \"C\" int doof_entry_main(int argc, char** argv);\n\n@interface ") + delegateName) + std::string(" : UIResponder <UIApplicationDelegate>\n")) + std::string("@property(nonatomic, strong) UIWindow* window;\n@end\n\n")) + std::string("@implementation ")) + delegateName) + std::string("\n")) + std::string("- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {\n")) + std::string("  (void)application;\n  (void)launchOptions;\n")) + std::string("  self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];\n")) + std::string("  UIViewController* rootViewController = [[UIViewController alloc] init];\n")) + std::string("  rootViewController.view.backgroundColor = UIColor.systemBackgroundColor;\n")) + std::string("  self.window.rootViewController = rootViewController;\n  [self.window makeKeyAndVisible];\n")) + std::string("  std::thread([] { (void)doof_entry_main(0, nullptr); }).detach();\n")) + std::string("  return YES;\n}\n@end\n\n")) + std::string("int main(int argc, char* argv[]) {\n  @autoreleasepool {\n")) + std::string("    return UIApplicationMain(argc, argv, nil, @\"")) + escapeObjectiveCString(delegateName)) + std::string("\");\n")) + std::string("  }\n}\n"));
}
#line 138 "/src/ios-app.do"
std::string renderIOSIconSetContents() {
#line 139 "/src/ios-app.do"
    return std::string("{\n  \"images\": [\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"20x20\", \"filename\": \"iphone_notification_20@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"20x20\", \"filename\": \"iphone_notification_20@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"29x29\", \"filename\": \"iphone_settings_29@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"29x29\", \"filename\": \"iphone_settings_29@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"40x40\", \"filename\": \"iphone_spotlight_40@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"40x40\", \"filename\": \"iphone_spotlight_40@3x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"2x\", \"size\": \"60x60\", \"filename\": \"iphone_app_60@2x.png\" },\n    { \"idiom\": \"iphone\", \"scale\": \"3x\", \"size\": \"60x60\", \"filename\": \"iphone_app_60@3x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"20x20\", \"filename\": \"ipad_notification_20.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"20x20\", \"filename\": \"ipad_notification_20@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"29x29\", \"filename\": \"ipad_settings_29.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"29x29\", \"filename\": \"ipad_settings_29@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"40x40\", \"filename\": \"ipad_spotlight_40.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"40x40\", \"filename\": \"ipad_spotlight_40@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"1x\", \"size\": \"76x76\", \"filename\": \"ipad_app_76.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"76x76\", \"filename\": \"ipad_app_76@2x.png\" },\n    { \"idiom\": \"ipad\", \"scale\": \"2x\", \"size\": \"83.5x83.5\", \"filename\": \"ipad_pro_83_5@2x.png\" },\n    { \"idiom\": \"ios-marketing\", \"scale\": \"1x\", \"size\": \"1024x1024\", \"filename\": \"app_store_1024.png\" }\n  ],\n  \"info\": { \"author\": \"doof\", \"version\": 1 }\n}");
}
#line 164 "/src/ios-app.do"
std::string objectiveCIdentifier(const std::string& value) {
#line 165 "/src/ios-app.do"
    const auto first = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_");
#line 166 "/src/ios-app.do"
    const auto rest = (first + std::string("0123456789"));
#line 167 "/src/ios-app.do"
    auto result = std::string("");
#line 168 "/src/ios-app.do"
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
#line 169 "/src/ios-app.do"
        const auto character = doof::string_substring(value, index, (index + 1));
#line 170 "/src/ios-app.do"
        (result += (doof::string_contains(rest, character) ? character : std::string("_")));
    }
#line 172 "/src/ios-app.do"
    if (result == std::string("")) {
#line 172 "/src/ios-app.do"
        return std::string("DoofApp");
    }
#line 173 "/src/ios-app.do"
    return (doof::string_contains(first, doof::string_substring(result, 0, 1)) ? result : (std::string("Doof_") + result));
}
#line 176 "/src/ios-app.do"
std::string escapeObjectiveCString(const std::string& value) {
#line 177 "/src/ios-app.do"
    return doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
}
#line 180 "/src/ios-app.do"
std::string plistString(const std::string& key, const std::string& value) {
#line 181 "/src/ios-app.do"
    return ((((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n\t<string>")) + escapePlistText(value)) + std::string("</string>\n"));
}
#line 184 "/src/ios-app.do"
std::string plistIndent(int32_t depth) {
#line 185 "/src/ios-app.do"
    auto result = std::string("");
#line 186 "/src/ios-app.do"
    for (int32_t ignored = 0; ignored < depth; ++ignored) {
#line 186 "/src/ios-app.do"
        (result += std::string("\t"));
    }
#line 187 "/src/ios-app.do"
    return result;
}
#line 190 "/src/ios-app.do"
std::string renderPlistValue(const doof::JsonValue& value, int32_t depth) {
#line 191 "/src/ios-app.do"
    const auto indent = plistIndent(depth);
#line 192 "/src/ios-app.do"
    {
        auto _case_subject = value;
        if (doof::json_is_null(_case_subject)) {
#line 193 "/src/ios-app.do"
            return (indent + std::string("<string></string>\n"));
    }
    else if (doof::json_is_boolean(_case_subject)) {
            const auto boolean = doof::json_as_bool(_case_subject);
#line 194 "/src/ios-app.do"
            return (indent + (boolean ? std::string("<true/>\n") : std::string("<false/>\n")));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_int(_case_subject);
#line 195 "/src/ios-app.do"
            return (((indent + std::string("<integer>")) + doof::to_string(number)) + std::string("</integer>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_long(_case_subject);
#line 196 "/src/ios-app.do"
            return (((indent + std::string("<integer>")) + doof::to_string(number)) + std::string("</integer>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_float(_case_subject);
#line 197 "/src/ios-app.do"
            return (((indent + std::string("<real>")) + doof::to_string(number)) + std::string("</real>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_double(_case_subject);
#line 198 "/src/ios-app.do"
            return (((indent + std::string("<real>")) + doof::to_string(number)) + std::string("</real>\n"));
    }
    else if (doof::json_is_string(_case_subject)) {
            const auto text = doof::json_as_string(_case_subject);
#line 199 "/src/ios-app.do"
            return (((indent + std::string("<string>")) + escapePlistText(text)) + std::string("</string>\n"));
    }
    else if (doof::json_is_array(_case_subject)) {
            const auto array = std::get<doof::JsonArray>(doof::json_storage(_case_subject));
#line 201 "/src/ios-app.do"
            auto result = (indent + std::string("<array>\n"));
#line 202 "/src/ios-app.do"
            const auto& _iterable_7 = array;
            for (const auto& item : *_iterable_7) {
#line 202 "/src/ios-app.do"
                (result += renderPlistValue(item, (depth + 1)));
            }
#line 203 "/src/ios-app.do"
            return ((result + indent) + std::string("</array>\n"));
    }
    else if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
#line 206 "/src/ios-app.do"
            auto result = (indent + std::string("<dict>\n"));
#line 207 "/src/ios-app.do"
            const auto& _iterable_9 = object;
            for (const auto& [key, item] : *_iterable_9) {
#line 208 "/src/ios-app.do"
                (result += (((plistIndent((depth + 1)) + std::string("<key>")) + escapePlistText(key)) + std::string("</key>\n")));
#line 209 "/src/ios-app.do"
                (result += renderPlistValue(item, (depth + 1)));
            }
#line 211 "/src/ios-app.do"
            return ((result + indent) + std::string("</dict>\n"));
    }
    }
#line 214 "/src/ios-app.do"
    doof::panic(std::string("unhandled plist value"));
}
#line 217 "/src/ios-app.do"
std::string escapePlistText(const std::string& value) {
#line 218 "/src/ios-app.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("&"), std::string("&amp;")), std::string("<"), std::string("&lt;")), std::string(">"), std::string("&gt;")), std::string("\""), std::string("&quot;")), std::string("'"), std::string("&apos;"));
}
#line 1 "<doof-generated>"
}
