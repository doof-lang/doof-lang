#include "src_macos_app.hpp"

namespace app_src_macos_app_ {




std::string macOSPackageArchiveName(const std::string& executableName, const std::string& version) {
    auto safeVersion = std::string("");
    const auto allowed = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-");
    for (int32_t index = 0; index < static_cast<int32_t>(version.size()); ++index) {
        const auto character = doof::string_substring(version, index, (index + 1));
        (safeVersion = (safeVersion + (doof::string_contains(allowed, character) ? character : std::string("-"))));
    }
    return (((executableName + std::string("-")) + safeVersion) + std::string("-macos.zip"));
}
std::string renderMacOSInfoPlist(const std::shared_ptr<MacOSAppConfig>& config) {
    auto body = std::string("");
    (body = (body + plistString(std::string("CFBundleDevelopmentRegion"), std::string("en"))));
    (body = (body + plistString(std::string("CFBundleDisplayName"), config->displayName)));
    (body = (body + plistString(std::string("CFBundleExecutable"), config->executableName)));
    if (config->iconPath != std::string("")) {
        (body = (body + plistString(std::string("CFBundleIconFile"), (config->executableName + std::string(".icns")))));
    }
    (body = (body + plistString(std::string("CFBundleIdentifier"), config->bundleId)));
    (body = (body + plistString(std::string("CFBundleInfoDictionaryVersion"), std::string("6.0"))));
    (body = (body + plistString(std::string("CFBundleName"), config->displayName)));
    (body = (body + plistString(std::string("CFBundlePackageType"), std::string("APPL"))));
    (body = (body + plistString(std::string("CFBundleShortVersionString"), config->version)));
    (body = (body + plistString(std::string("CFBundleVersion"), config->version)));
    (body = (body + plistString(std::string("LSApplicationCategoryType"), config->category)));
    (body = (body + plistString(std::string("LSMinimumSystemVersion"), config->minimumSystemVersion)));
    (body = (body + std::string("\t<key>NSHighResolutionCapable</key>\n\t<true/>\n")));
    (body = (body + plistString(std::string("NSPrincipalClass"), std::string("NSApplication"))));
    if (!doof::is_null(config->infoPlist)) {
        const auto& _iterable_3 = doof::unwrap_optional(config->infoPlist);
        for (const auto& [key, value] : *_iterable_3) {
            (body = ((((body + std::string("\t<key>")) + escapePlistText(key)) + std::string("</key>\n")) + renderPlistValue(value, 1)));
        }
    }
    return ((std::string("<\?xml version=\"1.0\" encoding=\"UTF-8\"\?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n") + body) + std::string("</dict>\n</plist>\n"));
}
std::shared_ptr<std::vector<std::string>> macOSCodesignArguments(const std::string& targetPath, const std::string& identity, const std::string& signing, const std::string& entitlementsPath) {
    auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--force"), std::string("--sign"), identity});
    if (signing != std::string("ad-hoc")) {
        arguments->push_back(std::string("--options"));
        arguments->push_back(std::string("runtime"));
    }
    arguments->push_back(((signing == std::string("ad-hoc")) ? std::string("--timestamp=none") : std::string("--timestamp")));
    if (entitlementsPath != std::string("")) {
        arguments->push_back(std::string("--entitlements"));
        arguments->push_back(entitlementsPath);
    }
    arguments->push_back(targetPath);
    return arguments;
}
std::string plistString(const std::string& key, const std::string& value) {
    return ((((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n\t<string>")) + escapePlistText(value)) + std::string("</string>\n"));
}
std::string plistIndent(int32_t depth) {
    auto result = std::string("");
    for (int32_t ignored = 0; ignored < depth; ++ignored) {
        (result = (result + std::string("\t")));
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
            const auto& _iterable_6 = array;
            for (const auto& item : *_iterable_6) {
                (result = (result + renderPlistValue(item, (depth + 1))));
            }
            return ((result + indent) + std::string("</array>\n"));
    }
    else if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            auto result = (indent + std::string("<dict>\n"));
            const auto& _iterable_8 = object;
            for (const auto& [key, item] : *_iterable_8) {
                (result = ((((result + plistIndent((depth + 1))) + std::string("<key>")) + escapePlistText(key)) + std::string("</key>\n")));
                (result = (result + renderPlistValue(item, (depth + 1))));
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
