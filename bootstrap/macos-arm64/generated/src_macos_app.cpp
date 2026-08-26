#include "src_macos_app.hpp"

namespace app_src_macos_app_ {




#line 42 "/src/macos-app.do"
std::string macOSPackageArchiveName(const std::string& executableName, const std::string& version) {
#line 43 "/src/macos-app.do"
    auto safeVersion = std::string("");
#line 44 "/src/macos-app.do"
    const auto allowed = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-");
#line 45 "/src/macos-app.do"
    for (int32_t index = 0; index < static_cast<int32_t>(version.size()); ++index) {
#line 46 "/src/macos-app.do"
        const auto character = doof::string_substring(version, index, (index + 1));
#line 47 "/src/macos-app.do"
        (safeVersion = (safeVersion + (doof::string_contains(allowed, character) ? character : std::string("-"))));
    }
#line 49 "/src/macos-app.do"
    return (((executableName + std::string("-")) + safeVersion) + std::string("-macos.zip"));
}
#line 53 "/src/macos-app.do"
std::string renderMacOSInfoPlist(const std::shared_ptr<MacOSAppConfig>& config) {
#line 54 "/src/macos-app.do"
    auto body = std::string("");
#line 55 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleDevelopmentRegion"), std::string("en"))));
#line 56 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleDisplayName"), config->displayName)));
#line 57 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleExecutable"), config->executableName)));
#line 58 "/src/macos-app.do"
    if (config->iconPath != std::string("")) {
#line 58 "/src/macos-app.do"
        (body = (body + plistString(std::string("CFBundleIconFile"), (config->executableName + std::string(".icns")))));
    }
#line 59 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleIdentifier"), config->bundleId)));
#line 60 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleInfoDictionaryVersion"), std::string("6.0"))));
#line 61 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleName"), config->displayName)));
#line 62 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundlePackageType"), std::string("APPL"))));
#line 63 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleShortVersionString"), config->version)));
#line 64 "/src/macos-app.do"
    (body = (body + plistString(std::string("CFBundleVersion"), config->version)));
#line 65 "/src/macos-app.do"
    (body = (body + plistString(std::string("LSApplicationCategoryType"), config->category)));
#line 66 "/src/macos-app.do"
    (body = (body + plistString(std::string("LSMinimumSystemVersion"), config->minimumSystemVersion)));
#line 67 "/src/macos-app.do"
    (body = (body + std::string("\t<key>NSHighResolutionCapable</key>\n\t<true/>\n")));
#line 68 "/src/macos-app.do"
    (body = (body + plistString(std::string("NSPrincipalClass"), std::string("NSApplication"))));
#line 69 "/src/macos-app.do"
    if (!doof::is_null(config->infoPlist)) {
#line 70 "/src/macos-app.do"
        const auto& _iterable_3 = doof::unwrap_optional(config->infoPlist);
        for (const auto& [key, value] : *_iterable_3) {
#line 71 "/src/macos-app.do"
            (body = ((((body + std::string("\t<key>")) + escapePlistText(key)) + std::string("</key>\n")) + renderPlistValue(value, 1)));
        }
    }
#line 74 "/src/macos-app.do"
    return ((std::string("<\?xml version=\"1.0\" encoding=\"UTF-8\"\?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n") + body) + std::string("</dict>\n</plist>\n"));
}
#line 80 "/src/macos-app.do"
std::shared_ptr<std::vector<std::string>> macOSCodesignArguments(const std::string& targetPath, const std::string& identity, const std::string& signing, const std::string& entitlementsPath) {
#line 86 "/src/macos-app.do"
    auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--force"), std::string("--sign"), identity});
#line 90 "/src/macos-app.do"
    if (signing != std::string("ad-hoc")) {
#line 91 "/src/macos-app.do"
        arguments->push_back(std::string("--options"));
#line 92 "/src/macos-app.do"
        arguments->push_back(std::string("runtime"));
    }
#line 94 "/src/macos-app.do"
    arguments->push_back(((signing == std::string("ad-hoc")) ? std::string("--timestamp=none") : std::string("--timestamp")));
#line 95 "/src/macos-app.do"
    if (entitlementsPath != std::string("")) {
#line 96 "/src/macos-app.do"
        arguments->push_back(std::string("--entitlements"));
#line 97 "/src/macos-app.do"
        arguments->push_back(entitlementsPath);
    }
#line 99 "/src/macos-app.do"
    arguments->push_back(targetPath);
#line 100 "/src/macos-app.do"
    return arguments;
}
#line 103 "/src/macos-app.do"
std::string plistString(const std::string& key, const std::string& value) {
#line 104 "/src/macos-app.do"
    return ((((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n\t<string>")) + escapePlistText(value)) + std::string("</string>\n"));
}
#line 107 "/src/macos-app.do"
std::string plistIndent(int32_t depth) {
#line 108 "/src/macos-app.do"
    auto result = std::string("");
#line 109 "/src/macos-app.do"
    for (int32_t ignored = 0; ignored < depth; ++ignored) {
#line 109 "/src/macos-app.do"
        (result = (result + std::string("\t")));
    }
#line 110 "/src/macos-app.do"
    return result;
}
#line 113 "/src/macos-app.do"
std::string renderPlistValue(const doof::JsonValue& value, int32_t depth) {
#line 114 "/src/macos-app.do"
    const auto indent = plistIndent(depth);
#line 115 "/src/macos-app.do"
    {
        auto _case_subject = value;
        if (doof::json_is_null(_case_subject)) {
#line 116 "/src/macos-app.do"
            return (indent + std::string("<string></string>\n"));
    }
    else if (doof::json_is_boolean(_case_subject)) {
            const auto boolean = doof::json_as_bool(_case_subject);
#line 117 "/src/macos-app.do"
            return (indent + (boolean ? std::string("<true/>\n") : std::string("<false/>\n")));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_int(_case_subject);
#line 118 "/src/macos-app.do"
            return (((indent + std::string("<integer>")) + doof::to_string(number)) + std::string("</integer>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_long(_case_subject);
#line 119 "/src/macos-app.do"
            return (((indent + std::string("<integer>")) + doof::to_string(number)) + std::string("</integer>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_float(_case_subject);
#line 120 "/src/macos-app.do"
            return (((indent + std::string("<real>")) + doof::to_string(number)) + std::string("</real>\n"));
    }
    else if (doof::json_is_number(_case_subject)) {
            const auto number = doof::json_as_double(_case_subject);
#line 121 "/src/macos-app.do"
            return (((indent + std::string("<real>")) + doof::to_string(number)) + std::string("</real>\n"));
    }
    else if (doof::json_is_string(_case_subject)) {
            const auto text = doof::json_as_string(_case_subject);
#line 122 "/src/macos-app.do"
            return (((indent + std::string("<string>")) + escapePlistText(text)) + std::string("</string>\n"));
    }
    else if (doof::json_is_array(_case_subject)) {
            const auto array = std::get<doof::JsonArray>(doof::json_storage(_case_subject));
#line 124 "/src/macos-app.do"
            auto result = (indent + std::string("<array>\n"));
#line 125 "/src/macos-app.do"
            const auto& _iterable_6 = array;
            for (const auto& item : *_iterable_6) {
#line 125 "/src/macos-app.do"
                (result = (result + renderPlistValue(item, (depth + 1))));
            }
#line 126 "/src/macos-app.do"
            return ((result + indent) + std::string("</array>\n"));
    }
    else if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
#line 129 "/src/macos-app.do"
            auto result = (indent + std::string("<dict>\n"));
#line 130 "/src/macos-app.do"
            const auto& _iterable_8 = object;
            for (const auto& [key, item] : *_iterable_8) {
#line 131 "/src/macos-app.do"
                (result = ((((result + plistIndent((depth + 1))) + std::string("<key>")) + escapePlistText(key)) + std::string("</key>\n")));
#line 132 "/src/macos-app.do"
                (result = (result + renderPlistValue(item, (depth + 1))));
            }
#line 134 "/src/macos-app.do"
            return ((result + indent) + std::string("</dict>\n"));
    }
    }
#line 137 "/src/macos-app.do"
    doof::panic(std::string("unhandled plist value"));
}
#line 140 "/src/macos-app.do"
std::string escapePlistText(const std::string& value) {
#line 141 "/src/macos-app.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("&"), std::string("&amp;")), std::string("<"), std::string("&lt;")), std::string(">"), std::string("&gt;")), std::string("\""), std::string("&quot;")), std::string("'"), std::string("&apos;"));
}
#line 1 "<doof-generated>"
}
