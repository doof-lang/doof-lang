#include "src_macos_app.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_macos_app_ {

doof::JsonObject MacOSAppResource::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["sourcePath"] = doof::json_value(this->sourcePath);
    (*_json)["destination"] = doof::json_value(this->destination);
    return _json;
}
doof::Result<std::shared_ptr<MacOSAppResource>, std::string> MacOSAppResource::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
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
    return doof::Success<std::shared_ptr<MacOSAppResource>>{std::make_shared<MacOSAppResource>(_field_sourcePath, _field_destination)};
}

doof::JsonObject MacOSEmbeddedLibrary::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["library"] = doof::json_value(this->library);
    (*_json)["path"] = doof::json_value(this->path);
    return _json;
}
doof::Result<std::shared_ptr<MacOSEmbeddedLibrary>, std::string> MacOSEmbeddedLibrary::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_library;
    if (auto _iterator_library = _object->find("library"); _iterator_library != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_library->second) : doof::json_is_string(_iterator_library->second)))) { return doof::Failure<std::string>{"Field \"library\" expected string but got " + std::string(doof::json_type_name(_iterator_library->second))}; }
        _field_library = (_lenient ? doof::json_as_string_lenient(_iterator_library->second) : doof::json_as_string(_iterator_library->second));
    } else {
        _field_library = std::string("");
    }
    std::optional<std::string> _field_path;
    if (auto _iterator_path = _object->find("path"); _iterator_path != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
        _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    } else {
        _field_path = std::string("");
    }
    return doof::Success<std::shared_ptr<MacOSEmbeddedLibrary>>{std::make_shared<MacOSEmbeddedLibrary>(_field_library.value(), _field_path.value())};
}

doof::JsonObject MacOSAppConfig::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["executableName"] = doof::json_value(this->executableName);
    (*_json)["bundleId"] = doof::json_value(this->bundleId);
    (*_json)["displayName"] = doof::json_value(this->displayName);
    (*_json)["version"] = doof::json_value(this->version);
    (*_json)["iconPath"] = doof::json_value(this->iconPath);
    (*_json)["infoPlist"] = (this->infoPlist ? doof::json_value(this->infoPlist) : doof::json_value(nullptr));
    (*_json)["resources"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->resources->size()); for (const auto& _element : *this->resources) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["embeddedLibraries"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->embeddedLibraries->size()); for (const auto& _element : *this->embeddedLibraries) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["category"] = doof::json_value(this->category);
    (*_json)["minimumSystemVersion"] = doof::json_value(this->minimumSystemVersion);
    return _json;
}
doof::Result<std::shared_ptr<MacOSAppConfig>, std::string> MacOSAppConfig::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
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
        _field_iconPath = std::string("");
    }
    std::optional<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>> _field_infoPlist;
    if (auto _iterator_infoPlist = _object->find("infoPlist"); _iterator_infoPlist != _object->end()) {
        if (!(doof::json_is_null(_iterator_infoPlist->second) || doof::json_is_object(_iterator_infoPlist->second))) { return doof::Failure<std::string>{"Field \"infoPlist\" expected object or null but got " + std::string(doof::json_type_name(_iterator_infoPlist->second))}; }
        _field_infoPlist = (doof::json_is_null(_iterator_infoPlist->second) ? nullptr : [&]() { const auto* _object_value = doof::json_as_object(_iterator_infoPlist->second); auto _values = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = _entry.second; } return _values; }());
    } else {
        _field_infoPlist = std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>{nullptr};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>>> _field_resources;
    if (auto _iterator_resources = _object->find("resources"); _iterator_resources != _object->end()) {
        if (!(doof::json_is_array(_iterator_resources->second))) { return doof::Failure<std::string>{"Field \"resources\" expected array but got " + std::string(doof::json_type_name(_iterator_resources->second))}; }
        _field_resources = [&]() { const auto* _array = doof::json_as_array(_iterator_resources->second); auto _values = std::make_shared<std::vector<std::shared_ptr<MacOSAppResource>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(MacOSAppResource::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_resources = std::make_shared<std::vector<std::shared_ptr<MacOSAppResource>>>(std::vector<std::shared_ptr<MacOSAppResource>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>>> _field_embeddedLibraries;
    if (auto _iterator_embeddedLibraries = _object->find("embeddedLibraries"); _iterator_embeddedLibraries != _object->end()) {
        if (!(doof::json_is_array(_iterator_embeddedLibraries->second))) { return doof::Failure<std::string>{"Field \"embeddedLibraries\" expected array but got " + std::string(doof::json_type_name(_iterator_embeddedLibraries->second))}; }
        _field_embeddedLibraries = [&]() { const auto* _array = doof::json_as_array(_iterator_embeddedLibraries->second); auto _values = std::make_shared<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(MacOSEmbeddedLibrary::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>{});
    }
    std::optional<std::string> _field_category;
    if (auto _iterator_category = _object->find("category"); _iterator_category != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_category->second) : doof::json_is_string(_iterator_category->second)))) { return doof::Failure<std::string>{"Field \"category\" expected string but got " + std::string(doof::json_type_name(_iterator_category->second))}; }
        _field_category = (_lenient ? doof::json_as_string_lenient(_iterator_category->second) : doof::json_as_string(_iterator_category->second));
    } else {
        _field_category = std::string("public.app-category.developer-tools");
    }
    std::optional<std::string> _field_minimumSystemVersion;
    if (auto _iterator_minimumSystemVersion = _object->find("minimumSystemVersion"); _iterator_minimumSystemVersion != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_minimumSystemVersion->second) : doof::json_is_string(_iterator_minimumSystemVersion->second)))) { return doof::Failure<std::string>{"Field \"minimumSystemVersion\" expected string but got " + std::string(doof::json_type_name(_iterator_minimumSystemVersion->second))}; }
        _field_minimumSystemVersion = (_lenient ? doof::json_as_string_lenient(_iterator_minimumSystemVersion->second) : doof::json_as_string(_iterator_minimumSystemVersion->second));
    } else {
        _field_minimumSystemVersion = std::string("11.0");
    }
    return doof::Success<std::shared_ptr<MacOSAppConfig>>{std::make_shared<MacOSAppConfig>(_field_executableName, _field_bundleId, _field_displayName, _field_version, _field_iconPath.value(), _field_infoPlist.value(), _field_resources.value(), _field_embeddedLibraries.value(), _field_category.value(), _field_minimumSystemVersion.value())};
}

doof::JsonObject MacOSPackageConfig::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["distDirectory"] = doof::json_value(this->distDirectory);
    (*_json)["signing"] = doof::json_value(this->signing);
    (*_json)["identity"] = doof::json_value(this->identity);
    (*_json)["sandbox"] = doof::json_value(this->sandbox);
    (*_json)["entitlementsPath"] = doof::json_value(this->entitlementsPath);
    return _json;
}
doof::Result<std::shared_ptr<MacOSPackageConfig>, std::string> MacOSPackageConfig::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_distDirectory;
    if (auto _iterator_distDirectory = _object->find("distDirectory"); _iterator_distDirectory != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_distDirectory->second) : doof::json_is_string(_iterator_distDirectory->second)))) { return doof::Failure<std::string>{"Field \"distDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_distDirectory->second))}; }
        _field_distDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_distDirectory->second) : doof::json_as_string(_iterator_distDirectory->second));
    } else {
        _field_distDirectory = std::string("");
    }
    std::optional<std::string> _field_signing;
    if (auto _iterator_signing = _object->find("signing"); _iterator_signing != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_signing->second) : doof::json_is_string(_iterator_signing->second)))) { return doof::Failure<std::string>{"Field \"signing\" expected string but got " + std::string(doof::json_type_name(_iterator_signing->second))}; }
        _field_signing = (_lenient ? doof::json_as_string_lenient(_iterator_signing->second) : doof::json_as_string(_iterator_signing->second));
    } else {
        _field_signing = std::string("developer-id");
    }
    std::optional<std::string> _field_identity;
    if (auto _iterator_identity = _object->find("identity"); _iterator_identity != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_identity->second) : doof::json_is_string(_iterator_identity->second)))) { return doof::Failure<std::string>{"Field \"identity\" expected string but got " + std::string(doof::json_type_name(_iterator_identity->second))}; }
        _field_identity = (_lenient ? doof::json_as_string_lenient(_iterator_identity->second) : doof::json_as_string(_iterator_identity->second));
    } else {
        _field_identity = std::string("");
    }
    std::optional<bool> _field_sandbox;
    if (auto _iterator_sandbox = _object->find("sandbox"); _iterator_sandbox != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_sandbox->second) : doof::json_is_boolean(_iterator_sandbox->second)))) { return doof::Failure<std::string>{"Field \"sandbox\" expected boolean but got " + std::string(doof::json_type_name(_iterator_sandbox->second))}; }
        _field_sandbox = (_lenient ? doof::json_as_bool_lenient(_iterator_sandbox->second) : doof::json_as_bool(_iterator_sandbox->second));
    } else {
        _field_sandbox = false;
    }
    std::optional<std::string> _field_entitlementsPath;
    if (auto _iterator_entitlementsPath = _object->find("entitlementsPath"); _iterator_entitlementsPath != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_entitlementsPath->second) : doof::json_is_string(_iterator_entitlementsPath->second)))) { return doof::Failure<std::string>{"Field \"entitlementsPath\" expected string but got " + std::string(doof::json_type_name(_iterator_entitlementsPath->second))}; }
        _field_entitlementsPath = (_lenient ? doof::json_as_string_lenient(_iterator_entitlementsPath->second) : doof::json_as_string(_iterator_entitlementsPath->second));
    } else {
        _field_entitlementsPath = std::string("");
    }
    return doof::Success<std::shared_ptr<MacOSPackageConfig>>{std::make_shared<MacOSPackageConfig>(_field_distDirectory.value(), _field_signing.value(), _field_identity.value(), _field_sandbox.value(), _field_entitlementsPath.value())};
}
std::string macOSPackageArchiveName(std::string executableName, std::string version) {
    auto safeVersion = std::string("");
    const auto allowed = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-");
    for (int32_t index = 0; index < static_cast<int32_t>(version.size()); ++index) {
        const auto character = doof::string_substring(version, index, (index + 1));
        (safeVersion = (safeVersion + (doof::string_contains(allowed, character) ? character : std::string("-"))));
    }
    return (((executableName + std::string("-")) + safeVersion) + std::string("-macos.zip"));
}
std::string renderMacOSInfoPlist(std::shared_ptr<MacOSAppConfig> config) {
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
        const auto& _iterable_1 = doof::unwrap_optional(config->infoPlist);
        for (const auto& [key, value] : *_iterable_1) {
            (body = ((((body + std::string("\t<key>")) + escapePlistText(key)) + std::string("</key>\n")) + renderPlistValue(value, 1)));
        }
    }
    return ((((std::string("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") + std::string("<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n")) + std::string("<plist version=\"1.0\">\n<dict>\n")) + body) + std::string("</dict>\n</plist>\n"));
}
std::shared_ptr<std::vector<std::string>> macOSCodesignArguments(std::string targetPath, std::string identity, std::string signing, std::string entitlementsPath) {
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
std::string plistString(std::string key, std::string value) {
    return ((((std::string("\t<key>") + escapePlistText(key)) + std::string("</key>\n\t<string>")) + escapePlistText(value)) + std::string("</string>\n"));
}
std::string plistIndent(int32_t depth) {
    auto result = std::string("");
    for (int32_t ignored = 0; ignored < depth; ++ignored) {
        (result = (result + std::string("\t")));
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
                (result = (result + renderPlistValue(item, (depth + 1))));
            }
            return ((result + indent) + std::string("</array>\n"));
    }
    else if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            auto result = (indent + std::string("<dict>\n"));
            const auto& _iterable_3 = object;
            for (const auto& [key, item] : *_iterable_3) {
                (result = ((((result + plistIndent((depth + 1))) + std::string("<key>")) + escapePlistText(key)) + std::string("</key>\n")));
                (result = (result + renderPlistValue(item, (depth + 1))));
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
